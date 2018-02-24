#include "board/systick.hpp"

namespace Board {

Systick systick;

}

void SYSTICK_handler() {
    Board::systick.handler();
}
