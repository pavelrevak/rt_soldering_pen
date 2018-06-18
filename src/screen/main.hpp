#pragma once

#include "lib/font.hpp"
#include "lib/preset.hpp"
#include "lib/heating.hpp"
#include "screen/screen.hpp"

namespace screen {

class Main : public Screen {

    static const int PRESET_TEMPERATURE_STEP = 10 * 1000;  //  10 degree C
    static const int ROUNDING_TEMPERATURE = 500;
    static const int IDLE_MESSAGE_MS = 5000;

    Board::Display::Fb &fb = Board::display.get_fb();
    Preset &preset;
    Heating &heating;

    bool _show_energy = true;

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
    void energy(int x, int y, int energy_mwh) {
        char tmps[20];
        if (energy_mwh < 100000) {
            Str::d2a(energy_mwh / 10, 2, 2, '\240', tmps);
        } else {
            Str::d2a(energy_mwh / 100, 3, 1, '\240', tmps);
        }
        x = fb.draw_text(x, y, tmps, Font::num7);
        fb.draw_text(x, y, "Wh", Font::sans8);
    }

    int edit_blink = 0;

    void draw_pen_temperature() {
        temperature(48, 10, heating.get_real_pen_temperature_mc(), Font::num22, Font::num9);
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
        voltage(106, 14, heating.get_supply_voltage_mv_idle());
        if (heating.get_supply_voltage_mv_drop() < 0) {
            voltage(100, 25, heating.get_supply_voltage_mv_drop());
        }
        if (!preset.is_standby()) {
            watts(106, 0, heating.get_power_mw());
        }
    }

    int status_blink = 0;

    void draw_state() {
        if (status_blink++ >= 6) status_blink = 0;
        if (preset.is_standby()) {
            if (heating.getPenSensorStatus() == Heating::PenSensorStatus::OK) {
                if (heating.getHeatingElementStatus() == Heating::HeatingElementStatus::BROKEN) {
                    fb.draw_text(75, 0, "BROKEN TIP", Font::sans8);
                    return;  // do not show energy
                }
                if (heating.getHeatingElementStatus() == Heating::HeatingElementStatus::SHORTED) {
                    fb.draw_text(70, 0, "SHORTED TIP", Font::sans8);
                    return;  // do not show energy
                }
                if (heating.get_real_pen_temperature_mc() < 50000 || status_blink < 4) {
                    fb.draw_text(87, 0, "STANDBY", Font::sans8);
                }
            } else if (heating.getPenSensorStatus() == Heating::PenSensorStatus::BROKEN) {
                fb.draw_text(83, 0, "NO RT TIP", Font::sans8);
            }
        } else if (heating.get_steady_ms() > IDLE_MESSAGE_MS && status_blink < 4) {
            fb.draw_text(83, 0, "IDLE", Font::sans8);
        } else {
            status_blink = 0;
        }
        energy(45, 0, heating.get_energy_mwh());
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

    Main(Preset &preset, Heating &heating) : preset(preset), heating(heating) {}

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

    void redraw() {
        draw_preset();
        draw_pen_temperature();
        draw_power();
        draw_state();
    }

};

}
