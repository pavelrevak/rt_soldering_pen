#pragma once

#include "lib/nv.hpp"

class Settings {

    enum Keys : uint32_t {
        ADVANCED_MODE,
        FAHRENHEIT,
        LEFT_HANDED,
    };

    lib::Nv nv;

    static const size_t MIN_FREE = 3;

    bool _advanced_mode;
    bool _fahrenheit;
    bool _left_handed;

public:

    Settings() {
        _advanced_mode = nv.load_bool(ADVANCED_MODE);
        _fahrenheit = nv.load_bool(FAHRENHEIT);
        _left_handed = nv.load_bool(LEFT_HANDED);
    }

    void save() {
        if (nv.free() <= MIN_FREE) nv.erase();
        nv.save_bool(ADVANCED_MODE, _advanced_mode);
        nv.save_bool(FAHRENHEIT, _fahrenheit);
        nv.save_bool(LEFT_HANDED, _left_handed);
    }

    bool get_advanced_mode() {
        return _advanced_mode;
    }

    void toggle_advanced_mode() {
        _advanced_mode = ! _advanced_mode;
    }

    void set_advanced_mode(bool val=true) {
        _fahrenheit = val;
    }

    bool get_fahrenheit() {
        return _fahrenheit;
    }

    void toggle_fahrenheit() {
        _fahrenheit = ! _fahrenheit;
    }

    void set_fahrenheit(bool val=true) {
        _fahrenheit = val;
    }

    bool get_left_handed() {
        return _left_handed;
    }

    void toggle_left_handed() {
        _left_handed = ! _left_handed;
    }

    void set_left_handed(bool val=true) {
        _left_handed = val;
    }

};
