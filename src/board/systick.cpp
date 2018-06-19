#include "board/systick.hpp"

namespace board {

Systick systick;

}

void SYSTICK_handler() {
    board::systick.handler();
}
