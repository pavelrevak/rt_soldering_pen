#pragma once

#include "board/gpio.hpp"

namespace Board {

class Buttons {
public:

    GpioPin<io::base::GPIOB, 5> up;
    GpioPin<io::base::GPIOB, 4> down;

    void init_hw() {
        // GPIO
        up.configure_input().configure_pull(gpio::Pull::PULL_UP);
        down.configure_input().configure_pull(gpio::Pull::PULL_UP);
    }

    inline bool is_pressed_up() {
        return !up.get_input();
    }

    inline bool is_pressed_down() {
        return !down.get_input();
    }

};

extern Buttons buttons;

}
