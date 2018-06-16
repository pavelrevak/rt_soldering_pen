#pragma once

#include "board/clock.hpp"
#include "board/heater.hpp"
#include "board/adc.hpp"

class Heating {

    static const int IDLE_MIN_TIME_MS = 8;  // ms
    static const int STABILIZE_TIME_MS = 2;  // ms
    static const int HEATING_MIN_POWER_MW = 100;  // 0.1 W

    int64_t _power_raw = 0;  // uW * _period_ticks
    int64_t _requested_power_raw = 0;  // uW * _period_ticks
    int64_t _energy_raw = 0;  // uW * CORE_FREQ
    int64_t _steady_ticks = 0;  // ticks when power is steady
    int _period_ms = 0;
    int _period_ticks = 0;
    int _remaining_ticks = 0;

    int _measure_ticks = 0;
    int _measurements_count = 0;

    int _requested_power_mw = 0;  // mW
    int _cpu_voltage_mv_heat = 0;  // mV
    int _cpu_voltage_mv_idle = 0;  // mV
    int _supply_voltage_mv_heat = 0;  // mV
    int _supply_voltage_mv_idle = 0;  // mV
    int _pen_current_ma = 0;  // mA
    int _pen_temperature_mc = 0;  // 0.001 degree C
    int _cpu_temperature_mc = 0;  // 0.001 degree C

    int _average_requested_power = 0;
    int _average_requested_power_short = 0;

    int64_t _ms2ticks(int64_t time_ms) {
        return time_ms * Board::Clock::CORE_FREQ / 1000;
    }

    int _ticks2ms(int64_t ticks) {
        return ticks * 1000 / Board::Clock::CORE_FREQ;
    }

    enum class State {
        STOP,
        START,
        HEATING,
        STABILIZE,
        IDLE,
    } _state = State::STOP;

    void _state_start() {
        // reset meters
        _measure_ticks = 0;
        _measurements_count = 0;
        _cpu_voltage_mv_heat = 0;
        _supply_voltage_mv_heat = 0;
        _pen_current_ma = 0;
        if (_requested_power_mw < HEATING_MIN_POWER_MW) {
            Board::adc.measure_idle_start();
            _requested_power_mw = 0;
            _requested_power_raw = 0;
            _steady_ticks = 0;
            _state = State::IDLE;
            return;
        }
        // calculating derivation of requested power
        // (for auto standby)
        // TODO rework this code
        _average_requested_power_short *= 2;
        _average_requested_power_short += _requested_power_mw;
        _average_requested_power_short /= 3;
        _average_requested_power *= 9;
        _average_requested_power += _requested_power_mw;
        _average_requested_power /= 10;
        int derivate_requested_power = _average_requested_power_short - _average_requested_power;
        if ((derivate_requested_power > 150) || derivate_requested_power < -200) {
            _steady_ticks = 0;
        }
        // enable heater
        Board::heater.on();
        // measure start
        Board::adc.measure_heat_start();
        heating_element_status = HeatingElementStatus::UNKNOWN;
        _state = State::HEATING;
    }

    void _state_heating(unsigned delta_ticks) {
        _measure_ticks += delta_ticks;
        if (!Board::adc.measure_is_done()) return;
        _cpu_voltage_mv_heat += Board::adc.get_cpu_voltage();
        _supply_voltage_mv_heat += Board::adc.get_supply_voltage();
        _pen_current_ma += Board::adc.get_pen_current();
        _measurements_count++;
        _power_raw += (int64_t)Board::adc.get_supply_voltage() * Board::adc.get_pen_current() * _measure_ticks;
        _measure_ticks = 0;
        if (_power_raw < _requested_power_raw) {
            if (_remaining_ticks < _ms2ticks(STABILIZE_TIME_MS + IDLE_MIN_TIME_MS)) {
                Board::adc.measure_heat_start();
                return;
            }
        }
        // disable heater
        Board::heater.off();
        _energy_raw += _power_raw;
        _cpu_voltage_mv_heat /= _measurements_count;
        _supply_voltage_mv_heat /= _measurements_count;
        _pen_current_ma /= _measurements_count;
        _measure_ticks = 0;
        _state = State::IDLE;
    }

    void _state_stabilize(unsigned delta_ticks) {
        _measure_ticks += delta_ticks;
        if (_measure_ticks < _ms2ticks(STABILIZE_TIME_MS)) return;
        Board::adc.measure_idle_start();
        _measure_ticks = 0;
        _measurements_count = 0;
        _cpu_voltage_mv_idle = 0;
        _supply_voltage_mv_idle = 0;
        _cpu_temperature_mc = 0;
        _pen_temperature_mc = 0;
        _state = State::IDLE;
    }

    void _state_idle(unsigned delta_ticks) {
        _measure_ticks += delta_ticks;
        if (!Board::adc.measure_is_done()) return;
        _cpu_voltage_mv_idle += Board::adc.get_cpu_voltage();
        _supply_voltage_mv_idle += Board::adc.get_supply_voltage();
        _cpu_temperature_mc += Board::adc.get_cpu_temperature();
        // TODO check pen status
        _pen_temperature_mc += Board::adc.get_pen_temperature();
        _measurements_count++;
        if (_remaining_ticks > 0) {
            Board::adc.measure_idle_start();
            return;
        }
        _cpu_voltage_mv_idle /= _measurements_count;
        _supply_voltage_mv_idle /= _measurements_count;
        _cpu_temperature_mc /= _measurements_count;
        _pen_temperature_mc /= _measurements_count;
        _state = State::STOP;
    }

public:
    static const int PERIOD_TIME_MIN_MS = 50;  // ms -> TODO duplicate

    enum class HeatingElementStatus {
        UNKNOWN,
        OK,
        BROKEN,
        SHORTED,
        WRONG_RESISTANCE,
    } heating_element_status = HeatingElementStatus::UNKNOWN;

    void start(const int power, const int period_time_ms) {
        _period_ms = period_time_ms;
        _period_ticks = period_time_ms * (Board::Clock::CORE_FREQ / 1000);
        // ignore very low requested power
        _remaining_ticks += _period_ticks;
        _requested_power_mw = power;
        _requested_power_raw = power * 1000 * _period_ticks;
        _state = State::START;
    }

    /**
     * @brief process _state machine
     * @details process _state machine
     *
     * @param delta_ticks number of ticks between calls
     * @return true if heating is processed false if heating is done
     */
    bool process(unsigned delta_ticks) {
        _remaining_ticks -= delta_ticks;
        _steady_ticks += delta_ticks;
        switch (_state) {
        case State::STOP:
            return false;
        case State::START:
            _state_start();
            return true;
        case State::HEATING:
            _state_heating(delta_ticks);
            return true;
        case State::STABILIZE:
            _state_stabilize(delta_ticks);
            return true;
        case State::IDLE:
            _state_idle(delta_ticks);
            return true;
        }
        return true;
    }

    int get_power_mw() {
        return _power_raw / 1000 / _period_ticks;
    }

    int get_energy_mwh() {
        return _energy_raw / Board::Clock::CORE_FREQ / 1000 / 3600;
    }

    int get_steady_ms() {
        return _steady_ticks / (Board::Clock::CORE_FREQ / 1000);
    }

    int get_cpu_voltage_mv_heat() {
        return _cpu_voltage_mv_heat;
    }

    int get_cpu_voltage_mv_idle() {
        return _cpu_voltage_mv_idle;
    }

    int get_supply_voltage_mv_heat() {
        return _supply_voltage_mv_heat;
    }

    int get_supply_voltage_mv_idle() {
        return _supply_voltage_mv_idle;
    }

    int get_supply_voltage_mv_drop() {
        return _supply_voltage_mv_heat - _supply_voltage_mv_idle;
    }

    int get_cpu_temperature_mc() {
        return _cpu_temperature_mc;
    }

    int get_pen_temperature_mc() {
        return _pen_temperature_mc;
    }

    int get_calculated_pen_temperature_mc() {
        return _cpu_temperature_mc + _pen_temperature_mc;
    }
};
