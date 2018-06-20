#pragma once

#include <cstring>
#include <cstdint>
#include <cmath>

namespace lib {

template <int WIDTH, int HEIGHT, typename FB_t>
class FrameBuffer {
    union {
        FB_t fb[WIDTH];
        unsigned char buffer[WIDTH * sizeof(FB_t)];
    };
public:

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
                fb[x--] |= (y < 0) ? (*bitmap++ >> (-y)) : (*bitmap++ << y);
            }
        }
        while (width-- && x < WIDTH) {
            fb[x++] |= (y < 0) ? (*bitmap++ >> (-y)) : (*bitmap++ << y);
        }
    }

    inline void draw_hline(int x, int y, int len) {
        if (len < 0) {
            draw_hline(x + len + 1, y, -len);
        }
        y = 1 << y;
        while (len-- && x < WIDTH) {
            fb[x++] |= y;
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
        fb[x] |= ((1 << len) - 1) << y;
    }

    template <typename F>
    int draw_char(int x, int y, const char ch, const F *font) {
        int spacing = font[1];
        font += 2;
        while (*font != ch) {
            if (*font == 0) return x;
            font++;
            font += *font + 1;
        }
        font++;
        int width = *font++;
        draw_bitmap(x, y, width, font);
        return width + spacing;
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
