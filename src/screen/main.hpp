#include "lib/font.hpp"
#include "lib/preset.hpp"
#include "screen/screen.hpp"

namespace screen {

class Main : public Screen {

    static const int PRESET_TEMPERATURE_STEP = 10 * 1000;  //  10 degree C
    static const int ROUNDING_TEMPERATURE = 500;

    Board::Display::Fb &fb = Board::display.get_fb();
    Preset &preset;

    int pen_temperature = 0;
    int supply_voltage_idle = 0;
    int supply_voltage_drop = 0;
    int heating_power = 0;
    int total_power = 0;
    int idle_seconds = 0;

    void preset_selected(int x, int y, bool is_on) {
        x = fb.draw_text(x, y, is_on ? "\275" : "\274" , Font::num13);
    }

    /** display temperature in 1/1000 degree Celsius */
    template<class Tfl, class Tfs>
    void temperature(int x, int y, int value, const Tfl font_large, const Tfs font_small) {
        char tmps[20];
        Str::i2a(value / 1000, 3, '\240', tmps);
        x = fb.draw_text(x, y, tmps, font_large);
        fb.draw_text(x, y, "\260C", font_small);
    }

    /** display voltage in millivolts */
    void voltage(int x, int y, int voltage) {
        char tmps[20];
        if (voltage < 10 * 1000) {
            Str::d2a((voltage) / 10, 1, 2, '\240', tmps);
        } else {
            Str::d2a((voltage) / 100, 1, 1, '\240', tmps);
        }
        x = fb.draw_text(x, y, tmps, Font::num7);
        fb.draw_char(x, y, 'V', Font::sans8);
    }

    /** display power in milliwatts */
    void watts(int x, int y, int watts) {
        char tmps[20];
        Str::d2a(watts / 100, 2, 1, '\240', tmps);
        x = fb.draw_text(x, y, tmps, Font::num7);
        fb.draw_char(x, y, 'W', Font::sans8);
    }

    /** display power in milliwatts */
    void watt_hours(int x, int y, int watt_hours) {
        char tmps[20];
        if (watt_hours < 100000) {
            Str::d2a(watt_hours / 10, 2, 2, '\240', tmps);
        } else {
            Str::d2a(watt_hours / 100, 3, 1, '\240', tmps);
        }
        x = fb.draw_text(x, y, tmps, Font::num7);
        fb.draw_text(x, y, "Wh", Font::sans8);
    }

    int edit_blink = 0;

    void draw_pen_temperature() {
        temperature(48, 10, pen_temperature, Font::num22, Font::num9);
    }

    void draw_preset() {
        if (preset.is_editing() && edit_blink++ > 5) edit_blink = 0;
        if (preset.get_selected() == 0) preset_selected(0, 0, !preset.is_standby());
        if (preset.get_selected() == 1) preset_selected(0, 19, !preset.is_standby());
        if (!preset.is_editing(0) || edit_blink < 5) {
            temperature(6, 0, preset.get_preset(0), Font::num13, Font::num7);
        }
        if (!preset.is_editing(1) || edit_blink < 5) {
            temperature(6, 19, preset.get_preset(1), Font::num13, Font::num7);
        }
    }

    void draw_power() {
        voltage(106, 14, supply_voltage_idle);
        if (supply_voltage_drop) {
            voltage(100, 25, supply_voltage_drop);
        }
        if (!preset.is_standby()) {
            watts(106, 0, heating_power);
        }
        watt_hours(45, 0, total_power);
    }

    int status_blink = 0;

    void draw_state() {
        if (status_blink++ >= 6) status_blink = 0;
        if (preset.is_standby()) {
            if (pen_temperature < 50000 || status_blink < 4) {
                fb.draw_text(87, 0, "STANDBY", Font::sans8);
            }
        } else if (idle_seconds > 5 && status_blink < 4) {
            fb.draw_text(83, 0, "IDLE", Font::sans8);
        } else {
            status_blink = 0;
        }
    }

    bool button_up_edit(const Button::Action action) {
        switch (action) {
            case Button::Action::RELEASED_SHORT:
            case Button::Action::PRESSED_LONG:
            case Button::Action::REPEAT:
                preset.edit_add(PRESET_TEMPERATURE_STEP);
                edit_blink = 0;
            default:
                break;
        }
        return false;
    }

    bool button_dw_edit(const Button::Action action) {
        switch (action) {
            case Button::Action::RELEASED_SHORT:
            case Button::Action::PRESSED_LONG:
            case Button::Action::REPEAT:
                preset.edit_add(-PRESET_TEMPERATURE_STEP);
                edit_blink = 0;
            default:
                break;
        }
        return false;
    }

    bool button_both_edit(const Button::Action action) {
        switch (action) {
            case Button::Action::RELEASED_SHORT:
                preset.edit_end();
                break;
            default:
                break;
        }
        return false;
    }

public:

    Main(Preset &preset) : preset(preset) {}

    bool button_up(const Button::Action action) {
        if (preset.is_editing()) return button_up_edit(action);
        switch (action) {
            case Button::Action::RELEASED_SHORT:
                preset.select(0);
                // standby_ticks = 0;
                break;
            case Button::Action::PRESSED_LONG:
                // edit preset 1
                preset.edit_select(0);
                edit_blink = 5;
                return true;
            default:
                break;
        }
        return false;
    }

    bool button_dw(const Button::Action action) {
        if (preset.is_editing()) return button_dw_edit(action);
        switch (action) {
            case Button::Action::RELEASED_SHORT:
                preset.select(1);
                // standby_ticks = 0;
                break;
            case Button::Action::PRESSED_LONG:
                // edit preset 2
                preset.edit_select(1);
                edit_blink = 5;
                return true;
            default:
                break;
        }
        return false;
    }

    bool button_both(const Button::Action action) {
        if (preset.is_editing()) return button_both_edit(action);
        switch (action) {
            case Button::Action::RELEASED_SHORT:
                preset.set_standby();
                break;
            case Button::Action::PRESSED_LONG:
                // enter MENU
                break;
            default:
                break;
        }
        return false;
    }

    void set_pen_temperature(const int temperature) {
        pen_temperature = temperature + ROUNDING_TEMPERATURE;
    }

    void set_supply_voltage_idle(const int voltage) {
        supply_voltage_idle = voltage;
    }

    void set_supply_voltage_drop(const int voltage) {
        supply_voltage_drop = voltage;
    }

    void set_heating_power(const int power) {
        heating_power = power;
    }

    void set_total_power(const int power) {
        total_power = power;
    }

    void set_idle_seconds(const int seconds) {
        idle_seconds = seconds;
    }

    void redraw() {
        draw_preset();
        draw_pen_temperature();
        draw_power();
        draw_state();
    }

};

}
