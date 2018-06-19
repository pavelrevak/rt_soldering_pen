#pragma once

#include "io/reg/cortexm/nvic.hpp"
#include "io/reg/stm32/f0/isr.hpp"
#include "board/gpio.hpp"
#include "board/usart.hpp"
#include "board/clock.hpp"
#include "lib/iostream.hpp"

namespace board {

class Debug {
public:

    GpioPin<io::base::GPIOB, 0> output;
    GpioPin<io::base::GPIOA, 2> debug_tx;

    Usart<io::base::USART1, 0, 500> uart;
    OStream dbg;

    void init_hw() {
        output.configure_output().configure_otype(gpio::Otype::PUSH_PULL).configure_ospeed(gpio::Ospeed::LOW).clr();
        debug_tx.configure_af(1).configure_otype(gpio::Otype::PUSH_PULL).configure_ospeed(gpio::Ospeed::MEDIUM);
        // USART
        uart.set_baud_rate(115200, board::Clock::CORE_FREQ).enable().enable_tx();
        dbg.set_file_out(uart);

        // NVIC
        io::NVIC.iser(io::isr::USART1_isr);
    }
};

extern Debug debug;

}
