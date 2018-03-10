#pragma once

class Button {
    static const int LONG_DOWN_CYCLES = 6;
    static const int LONG_REPEAT_CYCLES = 7;
    static const int REPEAT_CYCLES = 1;
    int press_cycles = 0;
    unsigned pressed = 0;
    unsigned released = 0;
    bool down = false;
    bool others = false;

public:
    enum class Action {
        NONE,
        PRESSED,
        RELEASED_SHORT,
        PRESSED_LONG,
        REPEAT,
        RELEASED_LONG,
    };

    void process_fast(bool is_pressed, bool others_pressed) {
        if ((is_pressed && others) || others_pressed) {
            down = false;
            others = true;
            pressed = 0;
            released = 0;
            return;
        } else {
            others = false;
        }
        if (down == is_pressed) {
            return;
        }
        down = is_pressed;
        if (is_pressed) {
            press_cycles = 0;
            pressed++;
        } else {
            released++;
            down = 0;
        }
    }

    Action process() {
        if (down) {
            press_cycles++;
            if (press_cycles == LONG_DOWN_CYCLES) {
                return Action::PRESSED_LONG;
            }
        }
        if (pressed) {
            pressed--;
            return Action::PRESSED;
        }
        if (released) {
            released--;
            if (press_cycles >= LONG_DOWN_CYCLES) {
                return Action::RELEASED_LONG;
            } else {
                return Action::RELEASED_SHORT;
            }
        }
        if (down && (press_cycles >= (LONG_REPEAT_CYCLES))) {
            press_cycles -= REPEAT_CYCLES;
            return Action::REPEAT;
        }
        return Action::NONE;
    }
};
