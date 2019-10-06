#pragma once

#include "lib/nv.hpp"

class Settings {

    struct Default {
        static const uint16_t PRESET_TEMPERATURE1 = 300;
        static const uint16_t PRESET_TEMPERATURE2 = 250;
        static const uint16_t STANDBY_TIMEOUT = 30;
    };

    enum Keys : uint32_t {
        ADVANCED_MODE,
        FAHRENHEIT,
        LEFT_HANDED,
        BRIGHTNESS,
        PRESET_TEMPERATURE1,
        PRESET_TEMPERATURE2,
        STANDBY_TIMEOUT,
    };

    lib::Nv nv;

    uint16_t _preset_temperatures[2];
    uint16_t _standby_timeout;
    bool _advanced_mode;
    bool _fahrenheit;
    bool _left_handed;
    bool _brightness;

    static const size_t MIN_FREE = 7;

public:

    Settings() {
        _advanced_mode = nv.load_bool(ADVANCED_MODE, false);
        _fahrenheit = nv.load_bool(FAHRENHEIT, false);
        _left_handed = nv.load_bool(LEFT_HANDED, false);
        _brightness = nv.load_bool(BRIGHTNESS, false);
        _preset_temperatures[0] = nv.load_u16(PRESET_TEMPERATURE1, Default::PRESET_TEMPERATURE1);
        _preset_temperatures[1] = nv.load_u16(PRESET_TEMPERATURE2, Default::PRESET_TEMPERATURE2);
        _standby_timeout = nv.load_u16(STANDBY_TIMEOUT, Default::STANDBY_TIMEOUT);
    }

    void save() {
        if (nv.free() <= MIN_FREE) nv.erase();
        nv.save_bool(ADVANCED_MODE, _advanced_mode);
        nv.save_bool(FAHRENHEIT, _fahrenheit);
        nv.save_bool(LEFT_HANDED, _left_handed);
        nv.save_bool(BRIGHTNESS, _brightness);
        nv.save_u16(PRESET_TEMPERATURE1, _preset_temperatures[0]);
        nv.save_u16(PRESET_TEMPERATURE2, _preset_temperatures[1]);
    }


    bool get_advanced_mode() const {
        return _advanced_mode;
    }

    void toggle_advanced_mode() {
        _advanced_mode = ! _advanced_mode;
    }

    void set_advanced_mode(const bool val=true) {
        _fahrenheit = val;
    }


    bool get_fahrenheit() const {
        return _fahrenheit;
    }

    void toggle_fahrenheit() {
        _fahrenheit = ! _fahrenheit;
    }

    void set_fahrenheit(const bool val=true) {
        _fahrenheit = val;
    }


    bool get_left_handed() const {
        return _left_handed;
    }

    void toggle_left_handed() {
        _left_handed = ! _left_handed;
    }

    void set_left_handed(const bool val=true) {
        _left_handed = val;
    }

    static const uint8_t BRIGHTNESS_LOW = 40;
    static const uint8_t BRIGHTNESS_HIGH = 240;

    uint8_t get_brightness_level() const {
        return _brightness ? BRIGHTNESS_HIGH : BRIGHTNESS_LOW;
    }

    bool get_brightness() const {
        return _brightness;
    }

    void toggle_brightness() {
        _brightness = ! _brightness;
    }

    void set_brightness(const bool val=true) {
        _brightness = val;
    }


    int get_preset_temperature(const int preset) const {
        return static_cast<int>(_preset_temperatures[preset]) * 1000;
    }

    void set_preset_temperature(const int preset, const int val) {
        _preset_temperatures[preset] = static_cast<uint16_t>(val / 1000);
    }


    int get_standby_timeout() const {
        return static_cast<int>(_standby_timeout) * 1000;
    }

    void set_standby_timeout(const int val) {
        _standby_timeout = static_cast<uint16_t>(val / 1000);
    }
};
