#pragma once

#include "screen/screen.hpp"
#include "lib/font.hpp"
#include "preset.hpp"
#include "heating.hpp"

namespace screen {

class Main : public Screen {

    static const int PRESET_TEMPERATURE_STEP = 10 * 1000;  //  10 degree C
    static const int ROUNDING_TEMPERATURE = 500;
    static const int IDLE_MESSAGE_MS = 5000;

    Board::Display::Fb &_fb = Board::display.get_fb();
    Preset &_preset;
    Heating &_heating;

    bool _show_energy = true;

    void _preset_selected(int x, int y, bool is_on) {
        x = _fb.draw_text(x, y, is_on ? "\275" : "\274" , Font::num13);
    }

    /** display temperature in 1/1000 degree Celsius */
    template<class Tfl, class Tfs>
    void _temperature(int x, int y, int value, const Tfl font_large, const Tfs font_small) {
        char tmps[20];
        Str::i2a(value / 1000, 3, '\240', tmps);
        x = _fb.draw_text(x, y, tmps, font_large);
        _fb.draw_text(x, y, "\260C", font_small);
    }

    /** display voltage in millivolts */
    void _voltage(int x, int y, int voltage) {
        char tmps[20];
        if (voltage < 10 * 1000) {
            Str::d2a((voltage) / 10, 1, 2, '\240', tmps);
        } else {
            Str::d2a((voltage) / 100, 1, 1, '\240', tmps);
        }
        x = _fb.draw_text(x, y, tmps, Font::num7);
        _fb.draw_char(x, y, 'V', Font::sans8);
    }

    /** display power in milliwatts */
    void _watts(int x, int y, int watts) {
        char tmps[20];
        Str::d2a(watts / 100, 2, 1, '\240', tmps);
        x = _fb.draw_text(x, y, tmps, Font::num7);
        _fb.draw_char(x, y, 'W', Font::sans8);
    }

    /** display power in milliwatts */
    void _energy(int x, int y, int energy_mwh) {
        char tmps[20];
        if (energy_mwh < 100000) {
            Str::d2a(energy_mwh / 10, 2, 2, '\240', tmps);
        } else {
            Str::d2a(energy_mwh / 100, 3, 1, '\240', tmps);
        }
        x = _fb.draw_text(x, y, tmps, Font::num7);
        _fb.draw_text(x, y, "Wh", Font::sans8);
    }

    int _edit_blink = 0;

    void _draw_pen_temperature() {
        _temperature(48, 10, _heating.get_real_pen_temperature_mc(), Font::num22, Font::num9);
    }

    void _draw_preset() {
        if (_preset.is_editing() && _edit_blink++ > 5) _edit_blink = 0;
        if (_preset.get_selected() == 0) _preset_selected(0, 0, !_preset.is_standby());
        if (_preset.get_selected() == 1) _preset_selected(0, 19, !_preset.is_standby());
        if (!_preset.is_editing(0) || _edit_blink < 5) {
            _temperature(6, 0, _preset.get_preset(0), Font::num13, Font::num7);
        }
        if (!_preset.is_editing(1) || _edit_blink < 5) {
            _temperature(6, 19, _preset.get_preset(1), Font::num13, Font::num7);
        }
    }

    void _draw_power() {
        _voltage(106, 14, _heating.get_supply_voltage_mv_idle());
        if (_heating.get_supply_voltage_mv_drop() < 0) {
            _voltage(100, 25, _heating.get_supply_voltage_mv_drop());
        }
        if (!_preset.is_standby()) {
            _watts(106, 0, _heating.get_power_mw());
        }
    }

    int status_blink = 0;

    void _draw_state() {
        if (status_blink++ >= 6) status_blink = 0;
        if (_preset.is_standby()) {
            if (_heating.getPenSensorStatus() == Heating::PenSensorStatus::OK) {
                if (_heating.getHeatingElementStatus() == Heating::HeatingElementStatus::BROKEN) {
                    _fb.draw_text(55, 0, "BROKEN RT TIP!", Font::sans8);
                    return;  // do not show energy
                }
                if (_heating.getHeatingElementStatus() == Heating::HeatingElementStatus::SHORTED) {
                    _fb.draw_text(50, 0, "SHORTED RT TIP!", Font::sans8);
                    return;  // do not show energy
                }
                if (_heating.get_real_pen_temperature_mc() < 50000 || status_blink < 4) {
                    _fb.draw_text(87, 0, "STANDBY", Font::sans8);
                }
            } else if (_heating.getPenSensorStatus() == Heating::PenSensorStatus::BROKEN) {
                _fb.draw_text(83, 0, "NO RT TIP", Font::sans8);
            }
        } else if (_heating.get_steady_ms() > IDLE_MESSAGE_MS && status_blink < 4) {
            _fb.draw_text(83, 0, "IDLE", Font::sans8);
        } else {
            status_blink = 0;
        }
        _energy(45, 0, _heating.get_energy_mwh());
    }

    bool button_up_edit(const Button::Action action) {
        switch (action) {
            case Button::Action::RELEASED_SHORT:
            case Button::Action::PRESSED_LONG:
            case Button::Action::REPEAT:
                _preset.edit_add(PRESET_TEMPERATURE_STEP);
                _edit_blink = 0;
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
                _preset.edit_add(-PRESET_TEMPERATURE_STEP);
                _edit_blink = 0;
            default:
                break;
        }
        return false;
    }

    bool button_both_edit(const Button::Action action) {
        switch (action) {
            case Button::Action::RELEASED_SHORT:
                _preset.edit_end();
                break;
            default:
                break;
        }
        return false;
    }

public:

    Main(Preset &preset, Heating &heating) : _preset(preset), _heating(heating) {}

    bool button_up(const Button::Action action) {
        if (_preset.is_editing()) return button_up_edit(action);
        switch (action) {
            case Button::Action::RELEASED_SHORT:
                _preset.select(0);
                // standby_ticks = 0;
                break;
            case Button::Action::PRESSED_LONG:
                // edit preset 1
                _preset.edit_select(0);
                _edit_blink = 5;
                return true;
            default:
                break;
        }
        return false;
    }

    bool button_dw(const Button::Action action) {
        if (_preset.is_editing()) return button_dw_edit(action);
        switch (action) {
            case Button::Action::RELEASED_SHORT:
                _preset.select(1);
                // standby_ticks = 0;
                break;
            case Button::Action::PRESSED_LONG:
                // edit preset 2
                _preset.edit_select(1);
                _edit_blink = 5;
                return true;
            default:
                break;
        }
        return false;
    }

    bool button_both(const Button::Action action) {
        if (_preset.is_editing()) return button_both_edit(action);
        switch (action) {
            case Button::Action::RELEASED_SHORT:
                _preset.set_standby();
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
        _draw_preset();
        _draw_pen_temperature();
        _draw_power();
        _draw_state();
    }

};

}
