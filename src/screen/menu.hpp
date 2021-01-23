#pragma once

#include "screen/screen.hpp"
#include "lib/font.hpp"
#include "lib/stringstream.hpp"
#include "preset.hpp"
#include "heating.hpp"
#include "meta.hpp"
#include "settings.hpp"

namespace screen {

class Menu : public Screen {

    board::Display::Fb &_fb = board::display.get_fb();
    Heating &_heating;
    Settings &_settings;

    struct MenuItem {
        enum class ItemType : uint8_t {
            TEXT,
            VALUE_INT,
            VALUE_DEC,
            VALUE_BINARY,
            END,
        };

        const char *label;
        const char *suffix;
        int value;
        uint8_t dp;
        ItemType item_type;
        bool editable;
    };

    enum MenuItems {
        ITEM_ABOUT,
        ITEM_BRIGHTNESS,
        ITEM_ADVANCED_MODE,
        ITEM_FAHRENHEIT,
        ITEM_LEFT_HANDED,
        ITEM_HIGH_POWER,
        ITEM_TOTAL_ENERGY,
        ITEM_HEATER_POWER,
        ITEM_HEATER_CURRENT,
        ITEM_HEATER_RESISTANCE,
        ITEM_CPU_TEMPERATURE,
        ITEM_CPU_SUPPLY,
        ITEM_CURRENT_SENSOR_ERROR,
        ITEMS_COUNT,
    };

    int _scroll_position = 0;
    int _cursor_position = ITEM_ABOUT;

    MenuItem _menu_items[ITEMS_COUNT] = {
        {
            Meta::project,
            Meta::version,
            0,
            0,
            MenuItem::ItemType::TEXT,
            false,
        }, {
            "High brightness:",
            nullptr,
            0,
            0,
            MenuItem::ItemType::VALUE_BINARY,
            true,
        }, {
            "Advanced mode:",
            nullptr,
            0,
            0,
            MenuItem::ItemType::VALUE_BINARY,
            true,
        }, {
            "Fahrenheit:",
            nullptr,
            0,
            0,
            MenuItem::ItemType::VALUE_BINARY,
            true,
        }, {
            "Left handed:",
            nullptr,
            0,
            0,
            MenuItem::ItemType::VALUE_BINARY,
            true,
        }, {
            "High power:";
            mullptr,
            0,
            0,
            MenuItem::ItemType::VALUE_BINARY,
            true,
        }, {
            "Total energy:",
            " Wh",
            0,
            3,
            MenuItem::ItemType::VALUE_DEC,
            false,
        }, {
            "Heater power:",
            " W",
            0,
            2,
            MenuItem::ItemType::VALUE_DEC,
            false,
        }, {
            "Heater current:",
            " A",
            0,
            2,
            MenuItem::ItemType::VALUE_DEC,
            false,
        }, {
            "Heater resistance:",
            " Ohm",
            0,
            2,
            MenuItem::ItemType::VALUE_DEC,
            false,
        }, {
            "CPU temperature:",
            " \260C",
            0,
            1,
            MenuItem::ItemType::VALUE_DEC,
            false,
        }, {
            "CPU supply:",
            " V",
            0,
            3,
            MenuItem::ItemType::VALUE_DEC,
            false,
        }, {
            "Current sensor err:",
            " mA",
            0,
            0,
            MenuItem::ItemType::VALUE_INT,
            false,
        }
    };

    void _draw_menu_item_cursor(int y_pos, const MenuItem &menu_item) {
        if (menu_item.editable) {
            _fb.draw_char(0, y_pos, '\276', lib::Font::sans8);
        } else {
            _fb.draw_char(0, y_pos, '\274', lib::Font::sans8);
        }
    }

    void _draw_menu_item_label(int y_pos, MenuItem &menu_item) {
        _fb.draw_text(6, y_pos, menu_item.label, lib::Font::sans8);
    }

    void _draw_menu_item_value(int y_pos, MenuItem &menu_item) {
        int x_pos = 128;
        lib::StringStream<20> ss;
        switch (menu_item.item_type) {
        case MenuItem::ItemType::VALUE_INT:
            ss.i(menu_item.value);
            break;
        case MenuItem::ItemType::VALUE_DEC:
            ss.dec(menu_item.value, 1, menu_item.dp);
            break;
        case MenuItem::ItemType::VALUE_BINARY:
            if (menu_item.value) {
                ss << "ON";
            } else {
                ss << "OFF";
            }
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

    void _draw_menu_item(int y_pos, MenuItem &menu_item, bool show_cursor=false) {
        if (show_cursor) {
            _draw_menu_item_cursor(y_pos, menu_item);
        }
        _draw_menu_item_label(y_pos, menu_item);
        _draw_menu_item_value(y_pos, menu_item);
    }

    void _draw_menu() {
        int line = 0;
        int pos_y = 0;
        if (_cursor_position < _scroll_position) _scroll_position = _cursor_position;
        if (_cursor_position > _scroll_position + 1) _scroll_position = _cursor_position - 2;
        for (auto menu_item : _menu_items) {
            if (line >= _scroll_position && line < _scroll_position + 3) {
                _draw_menu_item(pos_y, menu_item, line == _cursor_position);
                pos_y += 11;
            }
            line++;
        }
    }

    void _update_values() {
        _menu_items[ITEM_BRIGHTNESS].value = _settings.get_brightness();
        _menu_items[ITEM_ADVANCED_MODE].value = _settings.get_advanced_mode();
        _menu_items[ITEM_FAHRENHEIT].value = _settings.get_fahrenheit();
        _menu_items[ITEM_LEFT_HANDED].value = _settings.get_left_handed();
        _menu_items[ITEM_TOTAL_ENERGY].value = _heating.get_energy_mwh();
        _menu_items[ITEM_HEATER_POWER].value = _heating.get_power_mw() / 10;
        _menu_items[ITEM_HEATER_CURRENT].value = _heating.get_heater_current_ma() / 10;
        _menu_items[ITEM_HEATER_RESISTANCE].value = _heating.get_heater_resistance_mo() / 10;
        _menu_items[ITEM_CPU_TEMPERATURE].value = _heating.get_cpu_temperature_mc() / 100;
        _menu_items[ITEM_CPU_SUPPLY].value = _heating.get_cpu_voltage_mv_idle();
        _menu_items[ITEM_CURRENT_SENSOR_ERROR].value = _heating.get_heater_current_ma_error();
    }

    void button_long_menu_item() {
        switch (_cursor_position) {
        case ITEM_BRIGHTNESS:
            _settings.toggle_brightness();
            break;
        case ITEM_ADVANCED_MODE:
            _settings.toggle_advanced_mode();
            break;
        case ITEM_FAHRENHEIT:
            _settings.toggle_fahrenheit();
            break;
        case ITEM_LEFT_HANDED:
            _settings.toggle_left_handed();
            break;
        }
    }

public:

    Menu(ScreenHolder &screen_holder, Heating &heating, Settings &settings) :
        Screen(screen_holder),
        _heating(heating),
        _settings(settings) {}

    bool button_up(const lib::Button::Action action) override {
        switch (action) {
            case lib::Button::Action::RELEASED_SHORT:
            case lib::Button::Action::PRESSED_LONG:
            case lib::Button::Action::REPEAT:
                if (_cursor_position > 0) _cursor_position--;
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
                if (_cursor_position < ITEMS_COUNT - 1) _cursor_position++;
                break;
            default:
                break;
        }
        return false;
    }

    bool button_both(const lib::Button::Action action) override {
        switch (action) {
            case lib::Button::Action::RELEASED_SHORT:
                _settings.save();
                change_screen(ScreenId::MAIN);
                return true;
            case lib::Button::Action::PRESSED_LONG:
                button_long_menu_item();
                break;
            default:
                break;
        }
        return false;
    }

    void draw() override {
        _update_values();
        _draw_menu();
    }

};

}
