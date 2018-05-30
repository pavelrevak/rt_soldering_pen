#pragma once

#include "board/display.hpp"
#include "lib/button.hpp"

namespace screen {

class Screen {

    Board::Display::Fb &fb = Board::display.get_fb();

public:

    virtual bool button_up(const Button::Action) { return false; };
    virtual bool button_dw(const Button::Action) { return false; };
    virtual bool button_both(const Button::Action) { return false; };
    virtual void redraw() = 0;

};

}
