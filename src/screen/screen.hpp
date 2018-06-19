#pragma once

#include "board/display.hpp"
#include "lib/button.hpp"

namespace screen {

class Screen {

    board::Display::Fb &fb = board::display.get_fb();

public:

    virtual bool button_up(const lib::Button::Action) { return false; };
    virtual bool button_dw(const lib::Button::Action) { return false; };
    virtual bool button_both(const lib::Button::Action) { return false; };
    virtual void redraw() = 0;

};

}
