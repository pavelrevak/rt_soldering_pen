#pragma once

#include <cstdint>
#include "board/gpio.hpp"
#include "board/i2c.hpp"
#include "board/ssd1306.hpp"
#include "lib/framebuffer.hpp"

namespace board {

class Display {
    board::I2c &_i2c;

    GpioPin<io::base::GPIOA, 15> _oled_nrst;

    typedef uint32_t HEIGHT_TYPE;

public:
    static const int DISPLAY_WIDTH = 128;
    static const int DISPLAY_HEIGHT = 32;

    typedef lib::FrameBuffer<DISPLAY_WIDTH, DISPLAY_HEIGHT, HEIGHT_TYPE> Fb;

private:

    static const uint8_t init_cmds[32];

    struct FbCmds {
        char dummy[3] = {'F', 'B', ':'};  // dummy bytes to keep alignment of frame buffer
        uint8_t display_buffer_cmds[1] = {
            Ssd1306::CO_DATA,
        };
        Fb fb;
        static constexpr size_t FB_SIZE = sizeof(display_buffer_cmds) + sizeof(fb);
    } fb_cmds;


public:
    inline Fb &get_fb() {
        return fb_cmds.fb;
    }

    Display(board::I2c &i2c) : _i2c(i2c) {}

    void init_hw() {
        _oled_nrst.clr();
        _oled_nrst.configure_output().configure_otype(gpio::Otype::PUSH_PULL).configure_ospeed(gpio::Ospeed::LOW).clr();
    }

    void redraw() {
        while (_i2c.is_busy());
        _i2c.write(0x3c, fb_cmds.display_buffer_cmds, FbCmds::FB_SIZE);
    }

    void init() {
        fb_cmds.fb.clear();
        _oled_nrst.set();
        _i2c.write(0x3c, init_cmds, sizeof(init_cmds));
        redraw();
    }

    void rotate(bool x, bool y) {
        uint8_t rotate_cmds[3] {
            Ssd1306::CO_CMD,
            x ? Ssd1306::SETSEGREMAPINC : Ssd1306::SETSEGREMAPDEC,
            y ? Ssd1306::COMSCANINC : Ssd1306::COMSCANDEC,
        };
        while (_i2c.is_busy());
        _i2c.write(0x3c, rotate_cmds, sizeof(rotate_cmds));
    }
};

extern Display display;

}
