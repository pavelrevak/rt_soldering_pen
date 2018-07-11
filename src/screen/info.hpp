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

    MenuItem menu_items[14] = {
        {
            Meta::project,
            Meta::version,
            0,
            0,
            MenuItem::ItemType::TEXT,
        }, {
            "Total energy:",
            " Wh",
            0,
            3,
            MenuItem::ItemType::VALUE_DEC,
        }, {
            "Heating power:",
            " W",
            0,
            2,
            MenuItem::ItemType::VALUE_DEC,
        }, {
            "Tip current:",
            " A",
            0,
            2,
            MenuItem::ItemType::VALUE_DEC,
        }, {
            "Heater resistance:",
            " Ohm",
            0,
            2,
            MenuItem::ItemType::VALUE_DEC,
        }, {
            "Tip temperature:",
            " \260C",
            0,
            1,
            MenuItem::ItemType::VALUE_DEC,
        }, {
            "CPU temp:",
            " \260C",
            0,
            1,
            MenuItem::ItemType::VALUE_DEC,
        }, {
            "Supply idle:",
            " V",
            0,
            2,
            MenuItem::ItemType::VALUE_DEC,
        }, {
            "Supply heat:",
            " V",
            0,
            2,
            MenuItem::ItemType::VALUE_DEC,
        }, {
            "Supply drop:",
            " V",
            0,
            3,
            MenuItem::ItemType::VALUE_DEC,
        }, {
            "CPU supply idle:",
            " V",
            0,
            3,
            MenuItem::ItemType::VALUE_DEC,
        }, {
            "CPU supply heat:",
            " V",
            0,
            3,
            MenuItem::ItemType::VALUE_DEC,
        }, {
            "Current sensor err:",
            " mA",
            0,
            0,
            MenuItem::ItemType::VALUE_INT,
        }, {
            "Steady timer:",
            " s",
            0,
            2,
            MenuItem::ItemType::VALUE_INT,
        },
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
        for (auto &menu_item : menu_items) {
            if (line >= scroll_position && line < scroll_position + 3) {
                _draw_menu_item(pos_y, menu_item);
                pos_y += 11;
            }
            line++;
        }

        last_line = line;
    }

    void _update_values() {
        menu_items[1].value = _heating.get_energy_mwh();
        menu_items[2].value = _heating.get_power_mw() / 10;
        menu_items[3].value = _heating.get_heater_current_ma() / 10;
        menu_items[4].value = _heating.get_heater_resistance_mo() / 10;
        menu_items[5].value = _heating.get_real_tip_temperature_mc() / 100;
        menu_items[6].value = _heating.get_cpu_temperature_mc() / 100;
        menu_items[7].value = _heating.get_supply_voltage_mv_idle() / 10;
        menu_items[8].value = _heating.get_supply_voltage_mv_heat() / 10;
        menu_items[9].value = _heating.get_supply_voltage_mv_drop() / 10;
        menu_items[10].value = _heating.get_cpu_voltage_mv_idle();
        menu_items[11].value = _heating.get_cpu_voltage_mv_heat();
        menu_items[12].value = _heating.get_heater_current_ma_error();
        menu_items[13].value = _heating.get_steady_ms();
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
