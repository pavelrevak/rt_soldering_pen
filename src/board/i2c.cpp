#include "board/i2c.hpp"

void I2C1_handler() {
    board::I2c::get_instance().handler();
}
