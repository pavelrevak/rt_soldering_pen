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

    struct MenuItem {
        const char *label;
        const char *suffix;
        int value;
        uint8_t dp;
        enum class ItemType : uint8_t {
            TEXT,
            VALUE_INT,
            VALUE_DEC,
            END,
        } item_type;
    };

    MenuItem menu_item_info = {
        Meta::project,
        Meta::version,
        0,
        0,
        MenuItem::ItemType::TEXT,
    };

    MenuItem menu_item_total_energy = {
        "Total energy:",
        " Wh",
        0,
        3,
        MenuItem::ItemType::VALUE_DEC,
    };

    MenuItem menu_item_heating_power = {
        "Heating power:",
        " W",
        0,
        2,
        MenuItem::ItemType::VALUE_DEC,
    };

    MenuItem menu_item_heater_current = {
        "Heater current:",
        " A",
        0,
        2,
        MenuItem::ItemType::VALUE_DEC,
    };

    MenuItem menu_item_heater_resistance = {
        "Heater resistance:",
        " Ohm",
        0,
        2,
        MenuItem::ItemType::VALUE_DEC,
    };

    MenuItem menu_item_tip_temperature = {
        "Tip temperature:",
        " \260C",
        0,
        1,
        MenuItem::ItemType::VALUE_DEC,
    };

    MenuItem menu_item_cpu_temperature = {
        "CPU temp:",
        " \260C",
        0,
        1,
        MenuItem::ItemType::VALUE_DEC,
    };

    MenuItem menu_item_supply_idle = {
        "Supply idle:",
        " V",
        0,
        2,
        MenuItem::ItemType::VALUE_DEC,
    };

    MenuItem menu_item_supply_heat = {
        "Supply heat:",
        " V",
        0,
        2,
        MenuItem::ItemType::VALUE_DEC,
    };

    MenuItem menu_item_supply_drop = {
        "Supply drop:",
        " V",
        0,
        3,
        MenuItem::ItemType::VALUE_DEC,
    };

    MenuItem menu_item_cpu_supply_idle = {
        "CPU supply idle:",
        " V",
        0,
        3,
        MenuItem::ItemType::VALUE_DEC,
    };

    MenuItem menu_item_cpu_supply_heat = {
        "CPU supply heat:",
        " V",
        0,
        3,
        MenuItem::ItemType::VALUE_DEC,
    };

    MenuItem menu_item_current_sensor_error = {
        "Current sensor err:",
        " mA",
        0,
        0,
        MenuItem::ItemType::VALUE_INT,
    };

    MenuItem menu_item_steady_timer = {
        "Steady timer:",
        " s",
        0,
        2,
        MenuItem::ItemType::VALUE_INT,
    };

    MenuItem *menu_items[14] = {
        &menu_item_info,
        &menu_item_total_energy,
        &menu_item_heating_power,
        &menu_item_heater_current,
        &menu_item_heater_resistance,
        &menu_item_tip_temperature,
        &menu_item_cpu_temperature,
        &menu_item_supply_idle,
        &menu_item_supply_heat,
        &menu_item_supply_drop,
        &menu_item_cpu_supply_idle,
        &menu_item_cpu_supply_heat,
        &menu_item_current_sensor_error,
        &menu_item_steady_timer,
    };

    void _draw_menu_item(int y_pos, MenuItem &menu_item) {
        _fb.draw_text(0, y_pos, menu_item.label, lib::Font::sans8);
        int x_pos = 128;
        lib::StringStream<20> ss;
        switch (menu_item.item_type) {
        case MenuItem::ItemType::VALUE_INT:
            ss.i(menu_item.value);
            break;
        case MenuItem::ItemType::VALUE_DEC:
            ss.dec(menu_item.value, 1, menu_item.dp);
            break;
        default:
            break;
        }
        if (menu_item.suffix) {
            ss << menu_item.suffix;
        }
        x_pos -= lib::Font::text_width(ss.get_str(), lib::Font::sans8);
        _fb.draw_text(x_pos, y_pos, ss.get_str(), lib::Font::sans8);
    }

    int last_line = 0;

    void _draw_info() {
        int line = 0;
        int pos_y = 0;
        for (auto *menu_item : menu_items) {
            if (line >= scroll_position && line < scroll_position + 3) {
                _draw_menu_item(pos_y, *menu_item);
                pos_y += 11;
            }
            line++;
        }

        last_line = line;
    }

    void _update_values() {
        menu_item_total_energy.value = _heating.get_energy_mwh();
        menu_item_heating_power.value = _heating.get_power_mw() / 10;
        menu_item_heater_current.value = _heating.get_heater_current_ma() / 10;
        menu_item_heater_resistance.value = _heating.get_heater_resistance_mo() / 10;
        menu_item_tip_temperature.value = _heating.get_real_tip_temperature_mc() / 100;
        menu_item_cpu_temperature.value = _heating.get_cpu_temperature_mc() / 100;
        menu_item_supply_idle.value = _heating.get_supply_voltage_mv_idle() / 10;
        menu_item_supply_heat.value = _heating.get_supply_voltage_mv_heat() / 10;
        menu_item_supply_drop.value = _heating.get_supply_voltage_mv_drop() / 10;
        menu_item_cpu_supply_idle.value = _heating.get_cpu_voltage_mv_idle();
        menu_item_cpu_supply_heat.value = _heating.get_cpu_voltage_mv_heat();
        menu_item_current_sensor_error.value = _heating.get_heater_current_ma_error();
        menu_item_steady_timer.value = _heating.get_steady_ms() / 1000;;
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
        _update_values();
        _draw_info();
    }

};

}
