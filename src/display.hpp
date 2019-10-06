#pragma once

#include "board/display.hpp"
#include "lib/button.hpp"
#include "screen/screen.hpp"
#include "screen/main.hpp"
#include "screen/menu.hpp"
#include "heating.hpp"
#include "settings.hpp"

class Display {
    screen::ScreenHolder _screen_holder;

    screen::Main _screen_main;
    screen::Menu _screen_menu;

    Heating &_heating;
    Settings &_settings;

    screen::Screen *_screens[static_cast<int>(screen::ScreenId::COUNT)] = {
        &_screen_main,
        &_screen_menu,
    };

    static const unsigned BUTTONS_SAMPLE_MS = 10;  // ticks
    static const unsigned DECREASE_BRIGHTNESS_SEC = 120;
    static const unsigned DISPLAY_OFF_SEC = 900;

    static const unsigned BUTTONS_SAMPLE_TICKS = board::Clock::CORE_FREQ / 1000 * BUTTONS_SAMPLE_MS;
    static const unsigned DECREASE_BRIGHTNESS_FRAMES_COUNT = DECREASE_BRIGHTNESS_SEC * 1000 / Heating::PERIOD_TIME_MS;
    static const unsigned DISPLAY_OFF_FRAMES_COUNT = DISPLAY_OFF_SEC * 1000 / Heating::PERIOD_TIME_MS;

    unsigned _buttons_sample_ticks = 0;
    lib::Button _button_up;
    lib::Button _button_dw;
    lib::Button _button_both;


    unsigned _sleep_frames_count = 0;

    bool rotation_last = false;
    uint8_t brightness_last = 0;

    void _buttons_process_fast(unsigned delta_ticks) {
        _buttons_sample_ticks += delta_ticks;
        if (_buttons_sample_ticks < BUTTONS_SAMPLE_TICKS) return;
        _buttons_sample_ticks -= BUTTONS_SAMPLE_TICKS;
        bool btn_state_up;
        bool btn_state_dw;
        if (_settings.get_left_handed()) {
            btn_state_up = board::Buttons::get_instance().is_pressed_dw();
            btn_state_dw = board::Buttons::get_instance().is_pressed_up();
        } else {
            btn_state_up = board::Buttons::get_instance().is_pressed_up();
            btn_state_dw = board::Buttons::get_instance().is_pressed_dw();
        }
        _button_up.process(btn_state_up, btn_state_dw, BUTTONS_SAMPLE_MS);
        _button_dw.process(btn_state_dw, btn_state_up, BUTTONS_SAMPLE_MS);
        _button_both.process(btn_state_up && btn_state_dw, false, BUTTONS_SAMPLE_MS);
    }

    void _buttons_process() {
        lib::Button::Action btn_action_up = _button_up.get_status();
        lib::Button::Action btn_action_dw = _button_dw.get_status();
        lib::Button::Action btn_action_both = _button_both.get_status();
        if (_sleep_frames_count > DISPLAY_OFF_FRAMES_COUNT) {
            // exit display off when both buttons are pressed
            if (btn_action_both > lib::Button::Action::DOWN) {
                _button_both.block();
                reset_sleep_counter();
            }
            return;
        }
        if (_screen_holder.get()->button_up(btn_action_up)) _button_up.block();
        if (_screen_holder.get()->button_dw(btn_action_dw)) _button_dw.block();
        if (_screen_holder.get()->button_both(btn_action_both)) _button_both.block();
        // rest timer if is in not in standby or on every button press
        if (!_heating.get_preset().is_standby()
                || (btn_action_up != lib::Button::Action::NONE)
                || (btn_action_dw != lib::Button::Action::NONE)
                || (btn_action_both != lib::Button::Action::NONE)) {
            reset_sleep_counter();
        }
    }

    void _draw() {
        // do not spend time when I2C is busy
        if (board::I2c::get_instance().is_busy()) return;
        uint8_t brightness = 1;
        if (_sleep_frames_count < DECREASE_BRIGHTNESS_FRAMES_COUNT) {
            brightness = _settings.get_brightness_level();
        }
        if (brightness_last != brightness) {
            brightness_last = brightness;
            board::display.brightness(brightness);
            return;
        }
        bool rotation = _settings.get_left_handed();
        if (rotation_last != rotation) {
            rotation_last = rotation;
            board::display.rotate(rotation, rotation);
            return;
        }
        auto &fb = board::display.get_fb();
        fb.clear();
        if (_sleep_frames_count <= DISPLAY_OFF_FRAMES_COUNT) {
            _screen_holder.get()->draw();
            _sleep_frames_count++;
        }
        board::display.redraw();
    }

 public:
    Display(Heating &heating, Settings &settings) :
        _screen_holder(_screens),
        _screen_main(_screen_holder, heating, settings),
        _screen_menu(_screen_holder, heating, settings),
        _heating(heating),
        _settings(settings) {}

    void process(unsigned delta_ticks) {
        _buttons_process_fast(delta_ticks);
    }

    void draw() {
        _buttons_process();
        _draw();
    }

    void reset_sleep_counter() {
        _sleep_frames_count = 0;
    }
};
