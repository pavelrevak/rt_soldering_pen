#pragma once

#include "screen/screen.hpp"
#include "lib/font.hpp"
#include "lib/stringstream.hpp"
#include "preset.hpp"
#include "heating.hpp"
#include "settings.hpp"

namespace screen {

class Main : public Screen {

    static const int PRESET_TEMPERATURE_STEP = 5 * 1000;  //  10 degree C
    static const int ROUNDING_TEMPERATURE = 500;
    static const int IDLE_MESSAGE_MS = 5000;
    static const int WARN_HOT_TIP_TEMP = 50 * 1000;

    board::Display::Fb &_fb = board::display.get_fb();
    Heating &_heating;
    Preset &_preset;
    Settings &_settings;

    void _preset_selected(int x, int y, bool is_on) {
        x = _fb.draw_char(x, y, is_on ? '\275' : '\274' , lib::Font::num13);
    }

    /** display temperature in 1/1000 degree Celsius */
    template<class Tfl, class Tfs>
    void _temperature(int x, int y, int temperature, const Tfl font_large, const Tfs font_small) {
        lib::StringStream<4> ss;
        if (_settings.get_fahrenheit()) {
            // Fahrenheit
            ss.i(temperature * 9 / 5000 + 32, 3, ' ');
        } else {
            // Celsius
            ss.i(temperature / 1000, 3, ' ');
        }
        x = _fb.draw_text(x, y, ss.get_str(), font_large);
        if (_settings.get_fahrenheit()) {
            // Fahrenheit
            _fb.draw_text(x, y, "\260F", font_small);
        } else {
            // Celsius
            _fb.draw_text(x, y, "\260C", font_small);
        }
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
        if (energy_mwh < 10000) {
            ss.dec(energy_mwh / 10, 1, 2, '\240');
        } else {
            ss.dec(energy_mwh / 100, 2, 1, '\240');
        }
        x = _fb.draw_text(x, y, ss.get_str(), lib::Font::num7);
        _fb.draw_text(x, y, "Wh", lib::Font::sans8);
    }

    int _edit_blink = 0;

    void _draw_tip_temperature(int offset) {
        _temperature(offset, 10, _heating.get_real_tip_temperature_mc() + 500, lib::Font::num22, lib::Font::num7);
    }

    int status_blink = 0;

    void _draw_tip_temperature_large(int offset) {
        if (status_blink++ >= 3) status_blink = 0;
        if (_preset.is_standby()) {
            if (_heating.getTipSensorStatus() == Heating::TipSensorStatus::OK) {
                if (
                    (_heating.getHeatingElementStatus() == Heating::HeatingElementStatus::BROKEN) ||
                    (_heating.getHeatingElementStatus() == Heating::HeatingElementStatus::SHORTED)
                ) {
                    _fb.draw_text(offset, 0, "Err", lib::Font::num32);
                    return;  // do not show energy
                }
            } else if (_heating.getTipSensorStatus() == Heating::TipSensorStatus::BROKEN) {
                _fb.draw_text(offset, 0, " --", lib::Font::num32);
                return;
            } else if (_heating.getTipSensorStatus() == Heating::TipSensorStatus::OVERHEAT) {
                _fb.draw_text(offset, 0, " 0H", lib::Font::num32);
                return;
            }
            // during standby and temperature is higher than 50 degree Celsius, temperature will blink
            if (_heating.get_real_tip_temperature_mc() >= WARN_HOT_TIP_TEMP && status_blink > 2) return;
        }
        _temperature(offset, 0, _heating.get_real_tip_temperature_mc() + 500, lib::Font::num32, lib::Font::num13);
    }

    void _draw_preset(int offset) {
        if (_preset.is_editing() && _edit_blink++ > 5) _edit_blink = 0;
        if (_preset.get_selected() == 0) _preset_selected(offset, 0, !_preset.is_standby());
        if (_preset.get_selected() == 1) _preset_selected(offset, 19, !_preset.is_standby());
        if (!_preset.is_editing(0) || _edit_blink < 5) {
            _temperature(offset + 6, 0, _preset.get_preset(0), lib::Font::num13, lib::Font::num7);
        }
        if (!_preset.is_editing(1) || _edit_blink < 5) {
            _temperature(offset + 6, 19, _preset.get_preset(1), lib::Font::num13, lib::Font::num7);
        }
    }

    void _draw_power(int offset) {
        _voltage_mv(offset + 5, 14, _heating.get_supply_voltage_mv_idle());
        if (_heating.get_supply_voltage_mv_drop() < 0) {
            _drop_voltage_mv(offset, 25, _heating.get_supply_voltage_mv_drop());
        }
        if (!_preset.is_standby()) {
            _watts_mw(offset + 5, 0, _heating.get_power_mw());
        }
    }

    void _draw_power_bargraph(int offset) {
        if (_preset.is_standby()) return;

        int power = _heating.get_power_mw();
        int len = power * 15 / 40000;  // default for 40W power limit
        
        /* account for 150W power limit of RTU tips */
        if (_heating.getTipType() == Heating::TipType::RTU) {
            len = power * 15 / 150000;
        }

        if (len == 0 && power > 0) len = 1;
        if (len > 15) len = 15;

        for (int i = 0; i < len; i++) {
            _fb.draw_hline(offset, 31 - i * 2, 3);
        }
    }

    void _draw_state(int offset) {
        if (status_blink++ >= 6) status_blink = 0;
        if (_preset.is_standby()) {
            if (_heating.getTipSensorStatus() == Heating::TipSensorStatus::OK) {
                if (_heating.getHeatingElementStatus() == Heating::HeatingElementStatus::BROKEN) {
                    _fb.draw_text(offset + 10, 0, "BROKEN RT TIP!", lib::Font::sans8);
                    return;  // do not show energy
                }
                if (_heating.getHeatingElementStatus() == Heating::HeatingElementStatus::SHORTED) {
                    _fb.draw_text(offset + 4, 0, "SHORTED RT TIP!", lib::Font::sans8);
                    return;  // do not show energy
                }
                if (_heating.get_real_tip_temperature_mc() < WARN_HOT_TIP_TEMP || status_blink < 4) {
                    _fb.draw_text(offset + 39, 0, "STANDBY", lib::Font::sans8);
                }
            } else if (_heating.getTipSensorStatus() == Heating::TipSensorStatus::BROKEN) {
                _fb.draw_text(offset + 35, 0, "NO RT TIP", lib::Font::sans8);
            } else if (_heating.getTipSensorStatus() == Heating::TipSensorStatus::OVERHEAT) {
                _fb.draw_text(offset + 35, 0, "OVERHEAT!", lib::Font::sans8);
            }
        } else if (_heating.get_steady_ms() > IDLE_MESSAGE_MS && status_blink < 4) {
            _fb.draw_text(offset + 35, 0, "IDLE", lib::Font::sans8);
        } else {
            status_blink = 0;
        }
        _energy(offset, 0, _heating.get_energy_mwh());
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
                _settings.save();
                break;
            default:
                break;
        }
        return false;
    }

public:

    Main(ScreenHolder &screen_holder, Heating &heating, Settings &settings) :
        Screen(screen_holder),
        _heating(heating),
        _preset(heating.get_preset()),
        _settings(settings) {}

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
                change_screen(ScreenId::MENU);
                return true;
            default:
                break;
        }
        return false;
    }

    void draw() override {
        if (_settings.get_left_handed()) {
            _draw_preset(86);
            if (_settings.get_advanced_mode()) {
                _draw_tip_temperature(0);
                _draw_power(53);
                _draw_state(0);
            } else {
                _draw_tip_temperature_large(8);
                _draw_power_bargraph(0);
            }
        } else {
            _draw_preset(0);
            if (_settings.get_advanced_mode()) {
                _draw_tip_temperature(48);
                _draw_power(101);
                _draw_state(48);
            } else {
                _draw_tip_temperature_large(50);
                _draw_power_bargraph(125);
            }
        }
    }

};

}
