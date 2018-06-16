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
#include "lib/preset.hpp"
#include "lib/pid.hpp"
#include "lib/heating.hpp"
#include "screen/main.hpp"

class MainClass {
    unsigned last_ticks = 0;

    static const int PERIOD_TIME_MS = 150;  // ms
    static const int IDLE_TIME_MIN_MS = 8;  // ms
    static const int STANDBY_TIME_S = 30;  // s
    static const int PID_K_PROPORTIONAL = 700;
    static const int PID_K_INTEGRAL = 200;
    static const int PID_K_DERIVATE = 100;
    static const int HEATING_POWER_MAX = 40 * 1000;  // 20.0 W

    int64_t _uptime_ticks = 0;
    int _pen_temperature_mc = 10000000;

    Preset preset;
    Heating heating;
    Pid pid;

    screen::Main screen_main;
    screen::Screen *current_screen = &screen_main;

    enum class TempSensorStatus {
        UNKNOWN,
        OK,
        BROKEN,
        SHORTED,
    } temp_sensor_status = TempSensorStatus::UNKNOWN;

    static const unsigned BUTTONS_SAMPLE_TICKS = Board::Clock::CORE_FREQ / 1000 * 10;
    unsigned buttons_sample_ticks = 0;
    Button button_up;
    Button button_dw;
    Button button_both;

    void _buttons_process_fast(unsigned delta_ticks) {
        buttons_sample_ticks += delta_ticks;
        if (buttons_sample_ticks < BUTTONS_SAMPLE_TICKS) return;
        buttons_sample_ticks -= BUTTONS_SAMPLE_TICKS;
        bool btn_up = Board::buttons.is_pressed_up();
        bool btn_dw = Board::buttons.is_pressed_dw();
        button_up.process(btn_up, btn_dw, 10);
        button_dw.process(btn_dw, btn_up, 10);
        button_both.process(btn_up && btn_dw, false, 10);
    }

    enum class Screen {
        MAIN,
        INFO,
        SETUP,
    } screen = Screen::MAIN;

    void _buttons_process() {
        Button::Action btn_up = button_up.get_status();
        Button::Action btn_dw = button_dw.get_status();
        Button::Action btn_both = button_both.get_status();
        switch (screen) {
            case Screen::MAIN:
                if (current_screen->button_up(btn_up)) button_up.block();
                if (current_screen->button_dw(btn_dw)) button_dw.block();
                if (current_screen->button_both(btn_both)) button_both.block();
                break;
            case Screen::INFO:
                break;
            case Screen::SETUP:
                break;
        }
    }

    void _display_process_main() {
        if (Board::i2c.is_busy()) return;
        auto &fb = Board::display.get_fb();
        fb.clear();
        current_screen->redraw();
        Board::display.redraw();
    }

    void _display_process() {
        switch (screen) {
        case Screen::MAIN:
            _display_process_main();
            break;
        case Screen::INFO:
            break;
        case Screen::SETUP:
            break;
        }
    }

    void _heating_start() {
        int power_mw = 0;
        if (temp_sensor_status != TempSensorStatus::OK) {
            pid.reset();
        } else {
            power_mw = pid.process(_pen_temperature_mc, preset.get_temperature());
        }
        heating.start(power_mw, PERIOD_TIME_MS);
    }

    void _update_screen() {
        screen_main.set_supply_voltage_drop(heating.get_supply_voltage_mv_drop());
        screen_main.set_energy(heating.get_energy_mwh());
        screen_main.set_pen_temperature(heating.get_calculated_pen_temperature_mc());
        screen_main.set_supply_voltage_idle(heating.get_supply_voltage_mv_idle());
        int steady_ms = heating.get_steady_ms();
        screen_main.set_idle_ms(steady_ms);
        if (steady_ms > STANDBY_TIME_S * 1000) {
            preset.set_standby();
        }
    }

    void _process(unsigned delta_ticks) {
        _uptime_ticks += delta_ticks;
        _buttons_process_fast(delta_ticks);
        if (heating.process(delta_ticks)) return;
        _pen_temperature_mc = heating.get_calculated_pen_temperature_mc();
        if (Board::adc.is_pen_sensor_ok()) {
            temp_sensor_status = TempSensorStatus::OK;
            screen_main.pen_state();
        } else {
            temp_sensor_status = TempSensorStatus::BROKEN;
            preset.set_standby();
            screen_main.pen_state(false);
        }
        _buttons_process();
        _update_screen();
        _display_process();
        _heating_start();
    }

    void _init_hw() {
        Board::clock.init_hw();
        Board::systick.init_hw();
        Board::debug.init_hw();
        Board::heater.init_hw();
        Board::buttons.init_hw();
        Board::adc.init_hw();
        Board::i2c.init_hw();
        Board::display.init_hw();
    }

public:
    MainClass() : screen_main(preset) {}

    void run() {
        _init_hw();
        io::Nvic::isr_enable();

        Board::display.init();
        pid.set_constants(PID_K_PROPORTIONAL, PID_K_INTEGRAL, PID_K_DERIVATE, 1000 / PERIOD_TIME_MS, HEATING_POWER_MAX);
        _heating_start();

        Board::debug.dbg << IOStream::endl;
        last_ticks = Board::systick.get_counter();

        while (true) {
            unsigned delta_ticks = last_ticks;
            last_ticks = Board::systick.get_counter();
            delta_ticks = ((1 << Board::Systick::DIV_BITS) - 1) & (delta_ticks - last_ticks);
            _process(delta_ticks);
        }
    }
};

void main_app() {
    MainClass main_class;
    // start application
    main_class.run();
}
