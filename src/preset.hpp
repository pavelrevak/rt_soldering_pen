#pragma once

#include "lib/minmax.hpp"

class Preset {

    static const int PRESETS = 2;
    static const int NO_EDIT = -1;

    // temperatures are in 1/1000 degree C

    static const int PRESET_TEMPERATURE_MIN = 50 * 1000;
    static const int PRESET_TEMPERATURE_MAX = 400 * 1000;

    int _temperatures[PRESETS] = {
        300 * 1000,
        250 * 1000,
    };
    int _selected = 0;
    int _edited = NO_EDIT;
    bool _standby = true;

public:
    /** Enter standby mode
    */
    void set_standby() {
        _standby = true;
    }

    /** check if is in standby mode

    Return:
        true if is in standby mode
    */
    bool is_standby() const {
        return _standby;
    }

    /** Select preset number of temperature

    Arguments:
        preset: preset number to enable
    */
    void select(int preset) {
        if ((preset < 0) && (preset >= PRESETS)) return;
        _selected = preset;
        _standby = false;
    }

    /** Select preset number of temperature for editing

    Arguments:
        preset: preset number to edit
    */
    void edit_select(int preset) {
        if ((preset < 0) && (preset >= PRESETS)) return;
        _edited = preset;
    }

    /** Stop editing
    */
    void edit_end() {
        _edited = NO_EDIT;
    }

    /** Read selected temperature

    Return:
        selected temperature or if is in standby it return default standby temperature
    */
    int get_temperature() const {
        if (_standby) return 0;
        return _temperatures[_selected];
    }

    /** Read preset temperature

    Arguments:
        preset: preset temperature to edit

    Return:
        preset temperature
    */
    int get_preset(const int preset) const {
        if ((preset < 0) && (preset >= PRESETS)) return 0;
        return _temperatures[preset];
    }

    /** Read selected preset

    Return:
        selected preset
    */
    int get_selected() const {
        return _selected;
    }

    /** Read edited preset

    Return:
        edited preset
    */
    int get_edited() const {
        return _edited;
    }

    /** Read if is editing

    Return:
        true if is editing
    */
    bool is_editing() const {
        return _edited != NO_EDIT;
    }

    /** Read if preset is editing

    Arguments:
        preset: preset

    Return:
        true if preset is editing
    */
    bool is_editing(int preset) const {
        return _edited == preset;
    }

    /** Add to edited value

    Arguments:
        val: value to add (positive) subtract (negative) from edited temperature
    */
    void edit_add(int val) {
        if (_edited == NO_EDIT) return;
        _temperatures[_edited] = lib::minmax(
            _temperatures[_edited] + val,
            PRESET_TEMPERATURE_MIN,
            PRESET_TEMPERATURE_MAX);
    }

};
