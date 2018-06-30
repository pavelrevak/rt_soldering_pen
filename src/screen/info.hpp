#pragma once

#include "screen/screen.hpp"
#include "lib/font.hpp"
#include "lib/stringstream.hpp"
#include "preset.hpp"
#include "heating.hpp"
#include "meta.hpp"

namespace screen {

class Info : public Screen {

    board::Display::Fb &_fb = board::display.get_fb();
    Heating &_heating;

    int scroll_position = 0;

    void _draw_line(int line, const char *text, const char *value=nullptr) {
        line -= scroll_position;
        // if ((line < 0) && (line > 3)) return;
        _fb.draw_text(0, line * 11, text, lib::Font::sans8);
        if (value) {
            int w = lib::Font::text_width(value, lib::Font::sans8);
            _fb.draw_text(128 - w, line * 11, value, lib::Font::sans8);
        }
    }

    int last_line = 0;

    void _draw_state() {
        lib::StringStream<10> ss;
        int line = 0;

        if (line >= scroll_position && line < scroll_position + 3) {
            _draw_line(line, Meta::project, Meta::version);
        }
        line++;

        if (line >= scroll_position && line < scroll_position + 3) {
            ss.reset().dec(_heating.get_energy_mwh(), 2, 3, '\240').s(" Wh");
            _draw_line(line, "Total energy: ", ss.get_str());
        }
        line++;

        if (line >= scroll_position && line < scroll_position + 3) {
            ss.reset().dec(_heating.get_power_mw() / 10, 2, 2, '\240').s(" W");
            _draw_line(line, "Heating power: ", ss.get_str());
        }
        line++;

        if (line >= scroll_position && line < scroll_position + 3) {
            ss.reset().dec(_heating.get_pen_current_ma_heat() / 10, 2, 2, '\240').s(" A");
            _draw_line(line, "Heating current: ", ss.get_str());
        }
        line++;

        if (line >= scroll_position && line < scroll_position + 3) {
            ss.reset().dec(_heating.get_pen_resistance_mo() / 10, 2, 2, '\240').s(" Ohm");
            _draw_line(line, "Pen resistance: ", ss.get_str());
        }
        line++;

        if (line >= scroll_position && line < scroll_position + 3) {
            ss.reset().dec(_heating.get_real_pen_temperature_mc() / 100, 3, 1, '\240').s(" \260C");
            _draw_line(line, "Pen temp: ", ss.get_str());
        }
        line++;

        if (line >= scroll_position && line < scroll_position + 3) {
            ss.reset().dec(_heating.get_cpu_temperature_mc() / 100, 3, 1, '\240').s(" \260C");
            _draw_line(line, "CPU temp: ", ss.get_str());
        }
        line++;

        if (line >= scroll_position && line < scroll_position + 3) {
            ss.reset().dec(_heating.get_supply_voltage_mv_idle() / 10, 2, 2, '\240').s(" V");
            _draw_line(line, "Supply idle: ", ss.get_str());
        }
        line++;

        if (line >= scroll_position && line < scroll_position + 3) {
            ss.reset().dec(_heating.get_supply_voltage_mv_heat() / 10, 2, 2, '\240').s(" V");
            _draw_line(line, "Supply heat: ", ss.get_str());
        }
        line++;

        if (line >= scroll_position && line < scroll_position + 3) {
            ss.reset().dec(_heating.get_supply_voltage_mv_drop() / 10, 2, 2, '\240').s(" V");
            _draw_line(line, "Supply drop: ", ss.get_str());
        }
        line++;

        if (line >= scroll_position && line < scroll_position + 3) {
            ss.reset().dec(_heating.get_cpu_voltage_mv_idle() / 10, 2, 2, '\240').s(" V");
            _draw_line(line, "CPU idle: ", ss.get_str());
        }
        line++;

        if (line >= scroll_position && line < scroll_position + 3) {
            ss.reset().dec(_heating.get_cpu_voltage_mv_heat() / 10, 2, 2, '\240').s(" V");
            _draw_line(line, "CPU heat: ", ss.get_str());
        }
        line++;

        if (line >= scroll_position && line < scroll_position + 3) {
            ss.reset().i(_heating.get_pen_current_ma_idle(), 3, '\240').s(" mA");
            _draw_line(line, "Current sensor err: ", ss.get_str());
        }
        line++;

        if (line >= scroll_position && line < scroll_position + 3) {
            ss.reset().i(_heating.get_steady_ms() / 1000, 3, '\240').s(" s");
            _draw_line(line, "Steady timer: ", ss.get_str());
        }
        line++;

        last_line = line;
    }

public:

    Info(ScreenHolder &screen_holder, Heating &heating) :
        Screen(screen_holder),
        _heating(heating) {}

    bool button_up(const lib::Button::Action action) override {
        switch (action) {
            case lib::Button::Action::RELEASED_SHORT:
            case lib::Button::Action::PRESSED_LONG:
            case lib::Button::Action::REPEAT:
                if (scroll_position > 0) scroll_position--;
                break;
            default:
                break;
        }
        return false;
    }

    bool button_dw(const lib::Button::Action action) override {
        switch (action) {
            case lib::Button::Action::RELEASED_SHORT:
            case lib::Button::Action::PRESSED_LONG:
            case lib::Button::Action::REPEAT:
                if (scroll_position < last_line - 2) scroll_position++;
                break;
            default:
                break;
        }
        return false;
    }

    bool button_both(const lib::Button::Action action) override {
        switch (action) {
            case lib::Button::Action::RELEASED_SHORT:
                change_screen(ScreenId::MAIN);
                return true;
            case lib::Button::Action::PRESSED_LONG:
                // enter MENU
                break;
            default:
                break;
        }
        return false;
    }

    void draw() override {
        _draw_state();
    }

};

}
