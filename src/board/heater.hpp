#pragma once

#include "board/gpio.hpp"

namespace board {

class Heater {

    // GpioPin<io::base::GPIOB, 6> output;  // V0.1
    GpioPin<io::base::GPIOB, 3> output;  // V0.2+

public:

    void init_hw() {
        output.configure_output().configure_otype(gpio::Otype::PUSH_PULL).configure_ospeed(gpio::Ospeed::LOW).clr();
    }

    void on() {
        output.set();
    }

    void off() {
        output.clr();
    }

    static Heater &get_instance() {
        static Heater instance;
        return instance;
    }

};

}
