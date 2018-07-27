#pragma once

#include <cstdint>

namespace lib {

class Font {
public:
    // static const uint8_t sans5[];
    static const uint8_t sans8[];
    static const uint8_t num7[];
    // static const uint16_t num9[];
    // static const uint16_t num11[];
    static const uint16_t num13[];
    static const uint32_t num22[];
    static const uint32_t num32[];

    template <typename F>
    static int char_width(const char ch, const F *font) {
        int spacing = font[1];
        font += 2;
        while (*font != ch) {
            if (*font == 0) return 0;
            font++;
            font += *font + 1;
        }
        font++;
        return *font + spacing;
    }

    template <typename F>
    static int text_width(const char *text, const F *font) {
        int width = 0;
        while (*text) {
            width += char_width(*text++, font);
        }
        return width - font[1];
    }
};

}
