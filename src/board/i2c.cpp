#include "board/i2c.hpp"

namespace Board {

I2c i2c;

}

void I2C1_handler() {
    Board::i2c.handler();
}
