#include "board/adc.hpp"

namespace Board {

Adc adc;

}

void DMA1_CH1_handler() {
    Board::adc.dma_handler();
}
