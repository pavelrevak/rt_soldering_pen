#include "board/clock.hpp"
#include "board/systick.hpp"
#include "board/debug.hpp"
#include "board/adc.hpp"
#include "board/i2c.hpp"
#include "board/buttons.hpp"
#include "board/display.hpp"
#include "board/watchdog.hpp"
#include "heating.hpp"
#include "display.hpp"

class MainClass {
    unsigned last_ticks = 0;

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
        board::clock.init_hw();
        board::systick.init_hw();
        board::debug.init_hw();
        board::heater.init_hw();
        board::buttons.init_hw();
        board::adc.init_hw();
        board::i2c.init_hw();
        board::display.init_hw();
        board::Watchdog::enable(200, 100);  // time and window in ms
    }

public:
    MainClass() : _display(_heating) {}

    void run() {
        _init_hw();
        io::Nvic::isr_enable();

        board::display.init();
        _heating.init();
        _heating.start();

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
