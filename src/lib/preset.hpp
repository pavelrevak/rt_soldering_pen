#pragma once

class Preset {

    static const int PRESETS = 2;
    static const int NO_EDIT = -1;

    // temperatures are in 1/1000 degree C

    static const int MIN_TEMPERATURE = 20 * 1000;
    static const int MAX_TEMPERATURE = 400 * 1000;
    static const int PRESET_TEMPERATURE_MIN = 20 * 1000;  // 20 degree C
    static const int PRESET_TEMPERATURE_MAX = 400 * 1000;  // 400 degree C
    static const int STANDBY_TEMPERATURE = 20 * 1000;  //  20 degree C

    int temperatures[PRESETS] = {
        300 * 1000,
        250 * 1000,
    };
    int selected = 0;
    int edited = NO_EDIT;
    bool standby = true;

public:
    inline void set_standby() {
        standby = true;
    }

    inline bool is_standby() {
        return standby;
    }

    inline void select(int preset) {
        if ((preset < 0) && (preset >= PRESETS)) return;
        selected = preset;
        standby = false;
    }

    inline void edit_select(int preset) {
        if ((preset < 0) && (preset >= PRESETS)) return;
        edited = preset;
    }

    inline void edit_end() {
        edited = NO_EDIT;
    }

    inline int get_temperature() {
        if (standby) return STANDBY_TEMPERATURE;
        return temperatures[selected];
    }

    inline int get_preset(int preset) {
        return temperatures[preset];
    }

    inline int get_selected() {
        return selected;
    }

    inline int get_edited() {
        return edited;
    }

    inline bool is_editing() {
        return edited != NO_EDIT;
    }

    inline bool is_editing(int preset) {
        return edited == preset;
    }

    void edit_add(int val) {
        if (edited == NO_EDIT) return;
        temperatures[edited] += val;
        if (temperatures[edited] < MIN_TEMPERATURE) {
            temperatures[edited] = MIN_TEMPERATURE;
        } if (temperatures[edited] > MAX_TEMPERATURE) {
            temperatures[edited] = MAX_TEMPERATURE;
        }
    }

};
