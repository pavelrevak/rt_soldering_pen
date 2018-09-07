#pragma once

#include "board/gpio.hpp"

namespace board {

class Buttons {
public:

    GpioPin<io::base::GPIOB, 5> up;
    GpioPin<io::base::GPIOB, 4> dw;

    void init_hw() {
        // GPIO
        up.configure_input().configure_pull(gpio::Pull::PULL_UP);
        dw.configure_input().configure_pull(gpio::Pull::PULL_UP);
    }

    bool is_pressed_up() {
        return !up.get_input();
    }

    bool is_pressed_dw() {
        return !dw.get_input();
    }

    static Buttons &get_instance() {
        static Buttons instance;
        return instance;
    }

};

}
