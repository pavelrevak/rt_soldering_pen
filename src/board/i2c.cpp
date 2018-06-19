#include "board/i2c.hpp"

namespace board {

I2c i2c;

}

void I2C1_handler() {
    board::i2c.handler();
}
