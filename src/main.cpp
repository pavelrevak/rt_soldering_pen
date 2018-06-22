#include <string.h>

#include "board/clock.hpp"
#include "board/systick.hpp"
#include "board/debug.hpp"
#include "board/adc.hpp"
#include "board/i2c.hpp"
#include "board/buttons.hpp"
#include "board/display.hpp"
#include "lib/button.hpp"
#include "lib/pid.hpp"
#include "screen/screen.hpp"
#include "heating.hpp"
#include "preset.hpp"
#include "display.hpp"

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
    lib::Pid _pid;
    Display _display;

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
        _display.process_fast(delta_ticks);
        if (_heating.process(delta_ticks)) return;
        bool stop = _heating.getPenSensorStatus() != Heating::PenSensorStatus::OK;
        stop |= _heating.getHeatingElementStatus() == Heating::HeatingElementStatus::SHORTED;
        stop |= _heating.getHeatingElementStatus() == Heating::HeatingElementStatus::BROKEN;
        stop |= _heating.get_steady_ms() > STANDBY_TIME_MS;
        if (stop) {
            _preset.set_standby();
        }
        _display.process();
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
    MainClass() : _display(_preset, _heating) {}

    void run() {
        _init_hw();
        io::Nvic::isr_enable();

        board::display.init();
        _pid.set_constants(PID_K_PROPORTIONAL, PID_K_INTEGRAL, PID_K_DERIVATE, 1000 / PERIOD_TIME_MS, HEATING_POWER_MAX);
        _heating_start();

        board::debug.dbg << lib::IOStream::endl;
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
