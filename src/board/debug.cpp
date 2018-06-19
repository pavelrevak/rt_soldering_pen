#include "board/debug.hpp"

namespace board {

Debug debug;

}

void USART1_handler() {
    board::debug.uart.handler();
}
