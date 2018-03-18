#pragma once

class Button {
    static const unsigned LONG_DOWN_MILISECONDS = 1000;
    unsigned pressed_miliseconds = 0;
    unsigned released_short_counter = 0;
    bool down = false;
    bool others = false;
    bool pressed_long = false;
    bool repeat = false;

public:
    enum class Action {
        NONE,
        DOWN,
        RELEASED_SHORT,
        PRESSED_LONG,
        REPEAT,
    };

    void process(bool pressed, bool others_pressed, unsigned delta_ms) {
        if (pressed && others) return;
        others = others_pressed;
        if (others) {
            down = false;
            pressed_miliseconds = 0;
            return;
        }
        if (pressed) {
            pressed_miliseconds += delta_ms;
            if (pressed_miliseconds >= LONG_DOWN_MILISECONDS) {
                pressed_long = true;
            }
        }
        if (down == pressed) return;
        down = pressed;
        if (pressed) {
            pressed_miliseconds = 0;
        } else if (pressed_miliseconds < LONG_DOWN_MILISECONDS) {
            released_short_counter++;
        }
    }

    Action get_status() {
        if (pressed_long) {
            pressed_long = false;
            if (repeat) {
                return Action::REPEAT;
            }
            repeat = true;
            return Action::PRESSED_LONG;
        } else {
            repeat = false;
        }
        if (released_short_counter) {
            released_short_counter--;
            return Action::RELEASED_SHORT;
        }
        if (down) return Action::DOWN;
        return Action::NONE;
    }
};
