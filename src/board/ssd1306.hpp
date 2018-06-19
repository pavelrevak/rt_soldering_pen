#pragma once

namespace board {

class Ssd1306 {
public:
    static const unsigned char CO_CMD = 0x00;
    static const unsigned char CMD = 0x80;
    static const unsigned char CO_DATA = 0x40;
    static const unsigned char DATA = 0xc0;

    static const unsigned char CHARGEPUMP = 0x8d;
    static const unsigned char COLUMNADDR = 0x21;
    static const unsigned char COMSCANDEC = 0xc8;
    static const unsigned char COMSCANINC = 0xc0;
    static const unsigned char DISPLAYALLON = 0xa5;
    static const unsigned char DISPLAYALLON_RESUME = 0xa4;
    static const unsigned char DISPLAYOFF = 0xae;
    static const unsigned char DISPLAYON = 0xaf;
    static const unsigned char EXTERNALVCC = 0x1;
    static const unsigned char INVERTDISPLAY = 0xa7;
    static const unsigned char MEMORYMODE = 0x20;
    static const unsigned char NORMALDISPLAY = 0xa6;
    static const unsigned char PAGEADDR = 0x22;
    static const unsigned char SEGREMAP = 0xa0;
    static const unsigned char SETCOMPINS = 0xda;
    static const unsigned char SETCONTRAST = 0x81;
    static const unsigned char SETDISPLAYCLOCKDIV = 0xd5;
    static const unsigned char SETDISPLAYOFFSET = 0xd3;
    static const unsigned char SETHIGHCOLUMN = 0x10;
    static const unsigned char SETLOWCOLUMN = 0x00;
    static const unsigned char SETSTARTPAGE = 0xb0;
    static const unsigned char SETMULTIPLEX = 0xa8;
    static const unsigned char SETPRECHARGE = 0xd9;
    static const unsigned char SETSEGMENTREMAP = 0xa1;
    static const unsigned char SETSTARTLINE = 0x40;
    static const unsigned char SETVCOMDESELECT = 0xdb;
    static const unsigned char SWITCHCAPVCC = 0x2;

};

}
