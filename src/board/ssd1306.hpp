#pragma once

#include <cstdint>

namespace board {

class Ssd1306 {
public:
    static const uint8_t CO_CMD = 0x00;
    static const uint8_t CMD = 0x80;
    static const uint8_t CO_DATA = 0x40;
    static const uint8_t DATA = 0xc0;

    static const uint8_t CHARGEPUMP = 0x8d;
    static const uint8_t COLUMNADDR = 0x21;
    static const uint8_t COMSCANDEC = 0xc8;
    static const uint8_t COMSCANINC = 0xc0;
    static const uint8_t DISPLAYALLON = 0xa5;
    static const uint8_t DISPLAYALLON_RESUME = 0xa4;
    static const uint8_t DISPLAYOFF = 0xae;
    static const uint8_t DISPLAYON = 0xaf;
    static const uint8_t EXTERNALVCC = 0x1;
    static const uint8_t INVERTDISPLAY = 0xa7;
    static const uint8_t MEMORYMODE = 0x20;
    static const uint8_t NORMALDISPLAY = 0xa6;
    static const uint8_t PAGEADDR = 0x22;
    static const uint8_t SEGREMAP = 0xa0;
    static const uint8_t SETCOMPINS = 0xda;
    static const uint8_t SETCONTRAST = 0x81;
    static const uint8_t SETDISPLAYCLOCKDIV = 0xd5;
    static const uint8_t SETDISPLAYOFFSET = 0xd3;
    static const uint8_t SETHIGHCOLUMN = 0x10;
    static const uint8_t SETLOWCOLUMN = 0x00;
    static const uint8_t SETSTARTPAGE = 0xb0;
    static const uint8_t SETMULTIPLEX = 0xa8;
    static const uint8_t SETPRECHARGE = 0xd9;
    static const uint8_t SETSEGMENTREMAP = 0xa1;
    static const uint8_t SETSTARTLINE = 0x40;
    static const uint8_t SETVCOMDESELECT = 0xdb;
    static const uint8_t SWITCHCAPVCC = 0x2;

};

}
