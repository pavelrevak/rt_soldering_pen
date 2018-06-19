#pragma once

#include "board/gpio.hpp"
#include "board/i2c.hpp"
#include "lib/ssd1306.hpp"
#include "lib/framebuffer.hpp"

namespace board {

class Display {
    board::I2c &i2c;

    GpioPin<io::base::GPIOA, 15> oled_nrst;

    static const int DISPLAY_WIDTH = 128;
    static const int DISPLAY_HEIGHT = 32;
    typedef uint32_t HEIGHT_TYPE;

public:
    typedef FrameBuffer<DISPLAY_WIDTH, DISPLAY_HEIGHT, HEIGHT_TYPE> Fb;

private:
    unsigned char init_cmds[32] = {
        Ssd1306::CO_CMD,
        Ssd1306::DISPLAYOFF,
        Ssd1306::SETDISPLAYCLOCKDIV, 0xf0,
        Ssd1306::SETMULTIPLEX, (unsigned char)(DISPLAY_HEIGHT - 1),
        Ssd1306::SETDISPLAYOFFSET, 0x00,
        Ssd1306::SETSTARTLINE,
        Ssd1306::SETSEGMENTREMAP,
        Ssd1306::CHARGEPUMP, 0x14,
        Ssd1306::MEMORYMODE, 0x01,
        Ssd1306::COMSCANDEC,
        Ssd1306::SETCOMPINS, 0x02,
        Ssd1306::SETCONTRAST, 0x22,  // 0xcf
        Ssd1306::SETPRECHARGE, 0x00,
        Ssd1306::SETVCOMDESELECT, 0x40,
        Ssd1306::DISPLAYALLON_RESUME,
        Ssd1306::NORMALDISPLAY,
        Ssd1306::COLUMNADDR, 0, (unsigned char)(DISPLAY_WIDTH - 1),
        Ssd1306::PAGEADDR, 0, (unsigned char)(DISPLAY_HEIGHT / 8 - 1),
        Ssd1306::DISPLAYON,
    };

    struct {
        unsigned char dummy[3];  // dummy bytes to keep alignment of frame buffer
        unsigned char display_buffer_cmds[1] = {
            Ssd1306::CO_DATA,
        };
        Fb fb;
    } fb_cmds;

public:
    inline Fb &get_fb() {
        return fb_cmds.fb;
    }

    Display(board::I2c &i2c) : i2c(i2c) {}

    void init_hw() {
        oled_nrst.clr();
        oled_nrst.configure_output().configure_otype(gpio::Otype::PUSH_PULL).configure_ospeed(gpio::Ospeed::LOW).clr();
    }

    void redraw() {
        i2c.write(0x3c, fb_cmds.display_buffer_cmds, sizeof(fb_cmds.display_buffer_cmds) + sizeof(fb_cmds.fb));
    }

    void init() {
        fb_cmds.fb.clear();
        oled_nrst.set();
        i2c.write(0x3c, init_cmds, sizeof(init_cmds));
        while (i2c.is_busy());
        redraw();
    }
};

extern Display display;

}
