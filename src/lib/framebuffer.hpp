#pragma once

#include <cstring>
#include <cstdint>
#include <cmath>

namespace lib {

template <size_t BUFFER_WIDTH, size_t BUFFER_HEIGHT, typename FB_t>
class FrameBuffer {

    static_assert(BUFFER_HEIGHT <= sizeof(FB_t) * 8);

    union {
        FB_t fb[BUFFER_WIDTH];
        unsigned char buffer[BUFFER_WIDTH * sizeof(FB_t)];
    };

public:
    static const int WIDTH = BUFFER_WIDTH;
    static const int HEIGHT = BUFFER_HEIGHT;

    inline unsigned char *get_buffer() {
        return buffer;
    }

    inline void clear() {
        memset(fb, 0, WIDTH * sizeof(FB_t));
    }

    inline void draw_pixel(int x, int y) {
        if (x < 0  || x >= WIDTH || y < 0 || y >= HEIGHT) return;
        fb[x] |= 1 << y;
    }

    template <typename B>
    inline void draw_bitmap(int x, int y, int width, const B *bitmap) {
        if (x >= WIDTH) return;
        if (y >= HEIGHT) return;
        if (width < 0) {
            while (width++ && x > 0) {
                fb[x--] |= (y < 0) ? static_cast<FB_t>(*bitmap++ >> (-y)) : static_cast<FB_t>(*bitmap++ << y);
            }
        }
        while (width-- && x < WIDTH) {
            fb[x++] |= (y < 0) ? static_cast<FB_t>(*bitmap++ >> (-y)) : static_cast<FB_t>(*bitmap++ << y);
        }
    }

    inline void draw_hline(int x, int y, int len) {
        if (len < 0) {
            draw_hline(x + len + 1, y, -len);
        }
        y = 1 << y;
        while (len-- && x < WIDTH) {
            fb[x++] |= static_cast<FB_t>(y);
        }
    }

    inline void draw_vline(int x, int y, int len) {
        if (len < 0) {
            draw_vline(x, y + len + 1, -len);
        }
        if (x >= WIDTH) return;
        if (y < 0) {
            y = 0;
            len += y;
        }
        fb[x] |= static_cast<FB_t>(((1 << len) - 1) << y);
    }

    template <typename F>
    int draw_char(int x, int y, const char ch, const F *font) {
        unsigned spacing = font[1];
        font += 2;
        while (*font != ch) {
            if (*font == 0) return 0;
            font++;
            font += *font + 1;
        }
        font++;
        int width = static_cast<int>(*font++);
        draw_bitmap(x, y, width, font);
        return width + static_cast<int>(spacing);
    }

    template <typename F>
    int draw_text(int x, int y, const char *text, const F *font) {
        while (*text) {
            x += draw_char(x, y, *text++, font);
        }
        return x;
    }
};

}
