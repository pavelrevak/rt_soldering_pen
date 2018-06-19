#include <string.h>

#include "board/clock.hpp"
#include "board/systick.hpp"
#include "board/debug.hpp"
#include "board/adc.hpp"
#include "board/i2c.hpp"
#include "board/buttons.hpp"
#include "board/display.hpp"
#include "lib/str.hpp"
#include "lib/button.hpp"
#include "lib/pid.hpp"
#include "screen/main.hpp"
#include "heating.hpp"
#include "preset.hpp"

class MainClass {
    unsigned last_ticks = 0;

    static const int PERIOD_TIME_MS = 150;  // ms
    static const int IDLE_TIME_MIN_MS = 8;  // ms
    static const int STANDBY_TIME_MS = 30000;  // s
    static const int PID_K_PROPORTIONAL = 700;
    static const int PID_K_INTEGRAL = 200;
    static const int PID_K_DERIVATE = 100;
    static const int HEATING_POWER_MAX = 40 * 1000;  // 20.0 W

    uint64_t _uptime_ticks = 0;

    Preset _preset;
    Heating _heating;
    Pid _pid;

    enum class Screen {
        MAIN,
        INFO,
        SETUP,
    } _screen = Screen::MAIN;

    screen::Main _screen_main;
    screen::Screen *_current_screen = &_screen_main;

    static const int BUTTONS_SAMPLE_TICKS = board::Clock::CORE_FREQ / 1000 * 10;  // ticks
    int _buttons_sample_ticks = 0;
    lib::Button _button_up;
    lib::Button _button_dw;
    lib::Button _button_both;

    void _buttons_process_fast(unsigned delta_ticks) {
        _buttons_sample_ticks += delta_ticks;
        if (_buttons_sample_ticks < BUTTONS_SAMPLE_TICKS) return;
        _buttons_sample_ticks -= BUTTONS_SAMPLE_TICKS;
        bool btn_up = board::buttons.is_pressed_up();
        bool btn_dw = board::buttons.is_pressed_dw();
        _button_up.process(btn_up, btn_dw, 10);
        _button_dw.process(btn_dw, btn_up, 10);
        _button_both.process(btn_up && btn_dw, false, 10);
    }

    void _buttons_process() {
        lib::Button::Action btn_up = _button_up.get_status();
        lib::Button::Action btn_dw = _button_dw.get_status();
        lib::Button::Action btn_both = _button_both.get_status();
        switch (_screen) {
            case Screen::MAIN:
                if (_current_screen->button_up(btn_up)) _button_up.block();
                if (_current_screen->button_dw(btn_dw)) _button_dw.block();
                if (_current_screen->button_both(btn_both)) _button_both.block();
                break;
            case Screen::INFO:
                break;
            case Screen::SETUP:
                break;
        }
    }

    void _display_process() {
        if (board::i2c.is_busy()) return;
        auto &fb = board::display.get_fb();
        fb.clear();
        switch (_screen) {
        case Screen::MAIN:
            _current_screen->redraw();
            break;
        case Screen::INFO:
            break;
        case Screen::SETUP:
            break;
        }
        board::display.redraw();
    }

    void _heating_start() {
        int power_mw = 0;
        if (_heating.getPenSensorStatus() != Heating::PenSensorStatus::OK) {
            _pid.reset();
        } else {
            power_mw = _pid.process(_heating.get_real_pen_temperature_mc(), _preset.get_temperature() + 500);
        }
        _heating.start(power_mw, PERIOD_TIME_MS);
    }

    void _process(unsigned delta_ticks) {
        _uptime_ticks += delta_ticks;
        _buttons_process_fast(delta_ticks);
        if (_heating.process(delta_ticks)) return;
        bool stop = _heating.getPenSensorStatus() != Heating::PenSensorStatus::OK;
        stop |= _heating.getHeatingElementStatus() == Heating::HeatingElementStatus::SHORTED;
        stop |= _heating.getHeatingElementStatus() == Heating::HeatingElementStatus::BROKEN;
        stop |= _heating.get_steady_ms() > STANDBY_TIME_MS;
        if (stop) {
            _preset.set_standby();
        }
        _buttons_process();
        _display_process();
        _heating_start();
    }

    void _init_hw() {
        board::clock.init_hw();
        board::systick.init_hw();
        board::debug.init_hw();
        board::heater.init_hw();
        board::buttons.init_hw();
        board::adc.init_hw();
        board::i2c.init_hw();
        board::display.init_hw();
    }

public:
    MainClass() : _screen_main(_preset, _heating) {}

    void run() {
        _init_hw();
        io::Nvic::isr_enable();

        board::display.init();
        _pid.set_constants(PID_K_PROPORTIONAL, PID_K_INTEGRAL, PID_K_DERIVATE, 1000 / PERIOD_TIME_MS, HEATING_POWER_MAX);
        _heating_start();

        board::debug.dbg << IOStream::endl;
        last_ticks = board::systick.get_counter();

        while (true) {
            unsigned delta_ticks = last_ticks;
            last_ticks = board::systick.get_counter();
            delta_ticks = ((1 << board::Systick::DIV_BITS) - 1) & (delta_ticks - last_ticks);
            _process(delta_ticks);
        }
    }
};

void main_app() {
    MainClass main_class;
    // start application
    main_class.run();
}
