#include "board/debug.hpp"

void USART1_handler() {
    board::Debug::get_instance().uart.handler();
}
