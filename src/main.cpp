#include "board/clock.hpp"
#include "board/systick.hpp"
// #include "board/debug.hpp"
#include "board/adc.hpp"
#include "board/i2c.hpp"
#include "board/buttons.hpp"
#include "board/display.hpp"
#include "board/watchdog.hpp"
#include "heating.hpp"
#include "display.hpp"
#include "settings.hpp"

class MainClass {
    unsigned last_ticks = 0;

    Settings _settings;
    Heating _heating;
    Display _display;

    void _process(unsigned delta_ticks) {
        _display.process(delta_ticks);
        if (_heating.process(delta_ticks) == Heating::State::STOP) {
            _display.draw();
            _heating.start();
            board::Watchdog::refresh();
        }
    }

    void _init_hw() {
        board::Clock::get_instance().init_hw();
        board::Systick::get_instance().init_hw();
        // board::debug.init_hw();
        board::Heater::get_instance().init_hw();
        board::Buttons::get_instance().init_hw();
        board::Adc::get_instance().init_hw();
        board::I2c::get_instance().init_hw();
        board::display.init_hw();
        board::Watchdog::enable(200, 100);  // time and window in ms
    }

public:
    MainClass() :
    _heating(_settings),
    _display(_heating, _settings) {}

    void run() {
        _init_hw();
        io::Nvic::isr_enable();

        board::display.init();
        _heating.init();
        _heating.start();

        // board::debug.dbg << lib::IOStream::endl << "started.." << lib::IOStream::endl;
        last_ticks = board::Systick::get_instance().get_counter();

        while (true) {
            unsigned delta_ticks = last_ticks;
            last_ticks = board::Systick::get_instance().get_counter();
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
