#include "board/i2c.hpp"

namespace board {

I2c i2c_driver;

}

void I2C1_handler() {
    board::i2c_driver.handler();
}
