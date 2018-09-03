#pragma once

#include "board/display.hpp"
#include "lib/button.hpp"
#include "screen/screen.hpp"
#include "screen/main.hpp"
#include "screen/menu.hpp"
#include "settings.hpp"

class Display {
    screen::ScreenHolder _screen_holder;

    screen::Main _screen_main;
    screen::Menu _screen_menu;

    Settings &_settings;

    screen::Screen *_screens[static_cast<int>(screen::ScreenId::COUNT)] = {
        &_screen_main,
        &_screen_menu,
    };

    static const unsigned BUTTONS_SAMPLE_TICKS = board::Clock::CORE_FREQ / 1000 * 10;  // ticks
    unsigned _buttons_sample_ticks = 0;
    lib::Button _button_up;
    lib::Button _button_dw;
    lib::Button _button_both;

    bool rotation_last = false;

    void _buttons_process_fast(unsigned delta_ticks) {
        _buttons_sample_ticks += delta_ticks;
        if (_buttons_sample_ticks < BUTTONS_SAMPLE_TICKS) return;
        _buttons_sample_ticks -= BUTTONS_SAMPLE_TICKS;
        bool btn_state_up;
        bool btn_state_dw;
        if (_settings.get_left_handed()) {
            btn_state_up = board::buttons.is_pressed_dw();
            btn_state_dw = board::buttons.is_pressed_up();
        } else {
            btn_state_up = board::buttons.is_pressed_up();
            btn_state_dw = board::buttons.is_pressed_dw();
        }
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
        bool rotation = _settings.get_left_handed();
        if (rotation_last != rotation) {
            rotation_last = rotation;
            board::display.rotate(rotation, rotation);
        }
        auto &fb = board::display.get_fb();
        fb.clear();
        _screen_holder.get()->draw();
        board::display.redraw();
    }

public:

    Display(Heating &heating, Settings &settings) :
        _screen_holder(_screens),
        _screen_main(_screen_holder, heating, settings),
        _screen_menu(_screen_holder, heating, settings),
        _settings(settings) {}

    void process(unsigned delta_ticks) {
        _buttons_process_fast(delta_ticks);
    }

    void draw() {
        _buttons_process();
        _draw();
    }

};
