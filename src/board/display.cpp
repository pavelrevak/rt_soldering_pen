#include "board/display.hpp"

namespace board {

Display display(i2c);

const uint8_t Display::init_cmds[] = {
    Ssd1306::CO_CMD,
    Ssd1306::DISPLAYOFF,
    Ssd1306::SETDISPLAYCLOCKDIV, 0xf0,
    Ssd1306::SETMULTIPLEX, (uint8_t)(DISPLAY_HEIGHT - 1),
    Ssd1306::SETDISPLAYOFFSET, 0x00,
    Ssd1306::SETSTARTLINE,
    Ssd1306::SETSEGREMAPDEC,
    Ssd1306::CHARGEPUMP, 0x14,
    Ssd1306::MEMORYMODE, 0x01,
    Ssd1306::COMSCANDEC,
    Ssd1306::SETCOMPINS, 0x02,
    Ssd1306::SETCONTRAST, 0x22,  // 0xcf
    Ssd1306::SETPRECHARGE, 0x00,
    Ssd1306::SETVCOMDESELECT, 0x40,
    Ssd1306::DISPLAYALLON_RESUME,
    Ssd1306::NORMALDISPLAY,
    Ssd1306::COLUMNADDR, 0, (uint8_t)(DISPLAY_WIDTH - 1),
    Ssd1306::PAGEADDR, 0, (uint8_t)(DISPLAY_HEIGHT / 8 - 1),
    Ssd1306::DISPLAYON,
};

}
