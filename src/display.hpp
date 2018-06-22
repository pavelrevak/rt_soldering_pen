#pragma once

#include "board/display.hpp"
#include "lib/button.hpp"
#include "screen/screen.hpp"
#include "screen/main.hpp"
#include "screen/info.hpp"

class Display {
    screen::ScreenHolder _screen_holder;

    screen::Main _screen_main;
    screen::Info _screen_info;

    screen::Screen *_screens[static_cast<int>(screen::ScreenId::COUNT)] = {
        &_screen_main,
        &_screen_info,
    };

    static const int BUTTONS_SAMPLE_TICKS = board::Clock::CORE_FREQ / 1000 * 10;  // ticks
    int _buttons_sample_ticks = 0;
    lib::Button _button_up;
    lib::Button _button_dw;
    lib::Button _button_both;

    void _buttons_process_fast(unsigned delta_ticks) {
        _buttons_sample_ticks += delta_ticks;
        if (_buttons_sample_ticks < BUTTONS_SAMPLE_TICKS) return;
        _buttons_sample_ticks -= BUTTONS_SAMPLE_TICKS;
        bool btn_state_up = board::buttons.is_pressed_up();
        bool btn_state_dw = board::buttons.is_pressed_dw();
        _button_up.process(btn_state_up, btn_state_dw, 10);
        _button_dw.process(btn_state_dw, btn_state_up, 10);
        _button_both.process(btn_state_up && btn_state_dw, false, 10);
    }

    void _buttons_process() {
        lib::Button::Action btn_action_up = _button_up.get_status();
        lib::Button::Action btn_action_dw = _button_dw.get_status();
        lib::Button::Action btn_action_both = _button_both.get_status();
        if (_screen_holder.get()->button_up(btn_action_up)) _button_up.block();
        if (_screen_holder.get()->button_dw(btn_action_dw)) _button_dw.block();
        if (_screen_holder.get()->button_both(btn_action_both)) _button_both.block();
    }

    void _draw() {
        if (board::i2c.is_busy()) return;
        auto &fb = board::display.get_fb();
        fb.clear();
        _screen_holder.get()->draw();
        board::display.redraw();
    }

public:

    Display(Heating &heating) :
        _screen_holder(_screens),
        _screen_main(_screen_holder, heating),
        _screen_info(_screen_holder, heating) {}

    void process(unsigned delta_ticks) {
        _buttons_process_fast(delta_ticks);
    }

    void draw() {
        _buttons_process();
        _draw();
    }

};
