#include "board/debug.hpp"

namespace Board {

Debug debug;

}

void USART1_handler() {
    Board::debug.uart.handler();
}
