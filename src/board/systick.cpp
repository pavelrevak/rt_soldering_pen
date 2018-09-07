#include "board/systick.hpp"

void SYSTICK_handler() {
    board::Systick::get_instance().handler();
}
