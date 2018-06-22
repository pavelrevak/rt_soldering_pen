#pragma once

#include "screen/screen.hpp"
#include "lib/font.hpp"
#include "lib/stringstream.hpp"
#include "preset.hpp"
#include "heating.hpp"

namespace screen {

class Main : public Screen {

    static const int PRESET_TEMPERATURE_STEP = 10 * 1000;  //  10 degree C
    static const int ROUNDING_TEMPERATURE = 500;
    static const int IDLE_MESSAGE_MS = 5000;

    board::Display::Fb &_fb = board::display.get_fb();
    Heating &_heating;
    Preset &_preset;

    void _preset_selected(int x, int y, bool is_on) {
        x = _fb.draw_text(x, y, is_on ? "\275" : "\274" , lib::Font::num13);
    }

    /** display temperature in 1/1000 degree Celsius */
    template<class Tfl, class Tfs>
    void _temperature(int x, int y, int temperature, const Tfl font_large, const Tfs font_small) {
        lib::StringStream<4> ss;
        ss.i(temperature / 1000, 3, '\240');
        x = _fb.draw_text(x, y, ss.get_str(), font_large);
        _fb.draw_text(x, y, "\260C", font_small);
    }

    /** display voltage in millivolts */
    void _voltage_mv(int x, int y, int voltage_mv) {
        lib::StringStream<5> ss;
        if (voltage_mv < 10 * 1000) {
            ss.dec(voltage_mv / 10, 1, 2, '\240');
        } else {
            ss.dec(voltage_mv / 100, 2, 1, '\240');
        }
        x = _fb.draw_text(x, y, ss.get_str(), lib::Font::num7);
        _fb.draw_char(x, y, 'V', lib::Font::sans8);
    }

    /** display drop voltage in millivolts */
    void _drop_voltage_mv(int x, int y, int voltage_mv) {
        lib::StringStream<6> ss;
        ss.dec(voltage_mv / 10, 2, 2, '\240');
        x = _fb.draw_text(x, y, ss.get_str(), lib::Font::num7);
        _fb.draw_char(x, y, 'V', lib::Font::sans8);
    }

    /** display current in mA */
    void _current_ma(int x, int y, int current_ma) {
        lib::StringStream<7> ss;
        ss.dec(current_ma, 2, 3, '\240');
        x = _fb.draw_text(x, y, ss.get_str(), lib::Font::num7);
        _fb.draw_char(x, y, 'A', lib::Font::sans8);
    }

    /** display power in milliwatts */
    void _watts_mw(int x, int y, int watts_mw) {
        lib::StringStream<5> ss;
        ss.dec(watts_mw / 100, 2, 1, '\240');
        x = _fb.draw_text(x, y, ss.get_str(), lib::Font::num7);
        _fb.draw_char(x, y, 'W', lib::Font::sans8);
    }

    /** display power in milliwatts */
    void _energy(int x, int y, int energy_mwh) {
        lib::StringStream<5> ss;
        if (energy_mwh < 100000) {
            ss.dec(energy_mwh / 10, 2, 2, '\240');
        } else {
            ss.dec(energy_mwh / 100, 3, 1, '\240');
        }
        x = _fb.draw_text(x, y, ss.get_str(), lib::Font::num7);
        _fb.draw_text(x, y, "Wh", lib::Font::sans8);
    }

    int _edit_blink = 0;

    void _draw_pen_temperature() {
        _temperature(48, 10, _heating.get_real_pen_temperature_mc() + 500, lib::Font::num22, lib::Font::num9);
    }

    void _draw_preset() {
        if (_preset.is_editing() && _edit_blink++ > 5) _edit_blink = 0;
        if (_preset.get_selected() == 0) _preset_selected(0, 0, !_preset.is_standby());
        if (_preset.get_selected() == 1) _preset_selected(0, 19, !_preset.is_standby());
        if (!_preset.is_editing(0) || _edit_blink < 5) {
            _temperature(6, 0, _preset.get_preset(0), lib::Font::num13, lib::Font::num7);
        }
        if (!_preset.is_editing(1) || _edit_blink < 5) {
            _temperature(6, 19, _preset.get_preset(1), lib::Font::num13, lib::Font::num7);
        }
    }

    void _draw_power() {
        _voltage_mv(106, 14, _heating.get_supply_voltage_mv_idle());
        if (_heating.get_supply_voltage_mv_drop() < 0) {
            _drop_voltage_mv(101, 25, _heating.get_supply_voltage_mv_drop());
        }
        if (!_preset.is_standby()) {
            _watts_mw(106, 0, _heating.get_power_mw());
        }
    }

    int status_blink = 0;

    void _draw_state() {
        if (status_blink++ >= 6) status_blink = 0;
        if (_preset.is_standby()) {
            if (_heating.getPenSensorStatus() == Heating::PenSensorStatus::OK) {
                if (_heating.getHeatingElementStatus() == Heating::HeatingElementStatus::BROKEN) {
                    _fb.draw_text(55, 0, "BROKEN RT TIP!", lib::Font::sans8);
                    return;  // do not show energy
                }
                if (_heating.getHeatingElementStatus() == Heating::HeatingElementStatus::SHORTED) {
                    _fb.draw_text(50, 0, "SHORTED RT TIP!", lib::Font::sans8);
                    return;  // do not show energy
                }
                if (_heating.get_real_pen_temperature_mc() < 50000 || status_blink < 4) {
                    _fb.draw_text(87, 0, "STANDBY", lib::Font::sans8);
                }
            } else if (_heating.getPenSensorStatus() == Heating::PenSensorStatus::BROKEN) {
                _fb.draw_text(83, 0, "NO RT TIP", lib::Font::sans8);
            }
        } else if (_heating.get_steady_ms() > IDLE_MESSAGE_MS && status_blink < 4) {
            _fb.draw_text(83, 0, "IDLE", lib::Font::sans8);
        } else {
            status_blink = 0;
        }
        _energy(45, 0, _heating.get_energy_mwh());
    }

    bool _button_up_edit(const lib::Button::Action action) {
        switch (action) {
            case lib::Button::Action::RELEASED_SHORT:
            case lib::Button::Action::PRESSED_LONG:
            case lib::Button::Action::REPEAT:
                _preset.edit_add(PRESET_TEMPERATURE_STEP);
                _edit_blink = 0;
            default:
                break;
        }
        return false;
    }

    bool _button_dw_edit(const lib::Button::Action action) {
        switch (action) {
            case lib::Button::Action::RELEASED_SHORT:
            case lib::Button::Action::PRESSED_LONG:
            case lib::Button::Action::REPEAT:
                _preset.edit_add(-PRESET_TEMPERATURE_STEP);
                _edit_blink = 0;
            default:
                break;
        }
        return false;
    }

    bool _button_both_edit(const lib::Button::Action action) {
        switch (action) {
            case lib::Button::Action::RELEASED_SHORT:
                _preset.edit_end();
                break;
            default:
                break;
        }
        return false;
    }

public:

    Main(ScreenHolder &screen_holder, Heating &heating) :
        Screen(screen_holder),
        _heating(heating),
        _preset(heating.get_preset()) {}

    bool button_up(const lib::Button::Action action) override {
        if (_preset.is_editing()) return _button_up_edit(action);
        switch (action) {
            case lib::Button::Action::RELEASED_SHORT:
                _preset.select(0);
                // standby_ticks = 0;
                break;
            case lib::Button::Action::PRESSED_LONG:
                // edit preset 1
                _preset.edit_select(0);
                _edit_blink = 5;
                return true;
            default:
                break;
        }
        return false;
    }

    bool button_dw(const lib::Button::Action action) override {
        if (_preset.is_editing()) return _button_dw_edit(action);
        switch (action) {
            case lib::Button::Action::RELEASED_SHORT:
                _preset.select(1);
                // standby_ticks = 0;
                break;
            case lib::Button::Action::PRESSED_LONG:
                // edit preset 2
                _preset.edit_select(1);
                _edit_blink = 5;
                return true;
            default:
                break;
        }
        return false;
    }

    bool button_both(const lib::Button::Action action) override {
        if (_preset.is_editing()) return _button_both_edit(action);
        switch (action) {
            case lib::Button::Action::RELEASED_SHORT:
                _preset.set_standby();
                break;
            case lib::Button::Action::PRESSED_LONG:
                change_screen(ScreenId::INFO);
                return true;
            default:
                break;
        }
        return false;
    }

    void draw() override {
        _draw_preset();
        _draw_pen_temperature();
        _draw_power();
        _draw_state();
    }

};

}
