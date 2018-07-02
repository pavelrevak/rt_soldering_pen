#pragma once

#include "board/clock.hpp"
#include "board/heater.hpp"
#include "board/adc.hpp"
#include "lib/pid.hpp"
#include "preset.hpp"

/** Class for controlling heating and measuring cycle
*/
class Heating {

    static const int PERIOD_TIME_MS = 150;  // ms
    static const int STANDBY_TIME_MS = 30000;  // s
    static const int PERIOD_TIME_MIN_MS = 50;  // ms
    static const int PID_K_PROPORTIONAL = 700;
    static const int PID_K_INTEGRAL = 200;
    static const int PID_K_DERIVATE = 100;
    static const int HEATING_POWER_MAX = 40 * 1000;  // 20.0 W
    static const int IDLE_MIN_TIME_MS = 8;  // ms
    static const int STABILIZE_TIME_MS = 2;  // ms
    static const int HEATING_MIN_POWER_MW = 100;  // mW
    static const int PEN_MAX_CURRENT_MA = 6000;  // mA
    static const int SUPPLY_VOLTAGE_HEATING_MIN_MV = 4300; // mV
    static const int PEN_RESISTANCE_SHORTED = 500;  // mOhm
    static const int PEN_RESISTANCE_MIN = 1500;  // mOhm
    static const int PEN_RESISTANCE_MAX = 2500;  // mOhm
    static const int PEN_RESISTANCE_BROKEN = 100000;  // mOhm

public:

    enum class State {
        STOP,
        START,
        HEATING,
        STABILIZE,
        IDLE,
    } _state = State::STOP;

    enum class HeatingElementStatus {
        UNKNOWN,
        OK,
        SHORTED,
        LOW_RESISTANCE,
        HIGH_RESISTANCE,
        BROKEN,
    } _heating_element_status = HeatingElementStatus::UNKNOWN;


    enum class PenSensorStatus {
        UNKNOWN,
        OK,
        BROKEN,
        SHORTED,
    } _pen_sensor_status = PenSensorStatus::UNKNOWN;

private:

    Preset _preset;
    lib::Pid _pid;

    uint64_t _uptime_ticks = 0;
    int64_t _requested_power_uw_period_ticks = 0;  // uW * _period_ticks
    int64_t _energy_uw_ticks = 0;  // uW * CORE_FREQ
    int64_t _steady_ticks = 0;  // ticks when power is steady
    int _period_ticks = 0;
    int _remaining_ticks = 0;

    int _measure_ticks = 0;
    int _measurements_count = 0;

    int _requested_power_mw = 0;  // mW
    int _power_mw = 0;  // mW
    int _cpu_voltage_mv_heat = 0;  // mV
    int _cpu_voltage_mv_idle = 0;  // mV
    int _supply_voltage_mv_heat = 0;  // mV
    int _supply_voltage_mv_idle = 0;  // mV
    int _supply_voltage_mv_drop = 0;  // mV
    int _pen_current_ma = 0;  // mA
    int _pen_current_ma_error = 0;  // mA
    int _pen_resistance_mo = 0;  // mOhm
    int _pen_temperature_mc = 0;  // 1/1000 degree C
    int _cpu_temperature_mc = 0;  // 1/1000 degree C

    int _average_requested_power = 0;
    int _average_requested_power_short = 0;

    int64_t _ms2ticks(int64_t time_ms) {
        return time_ms * board::Clock::CORE_FREQ / 1000;
    }

    int _ticks2ms(int64_t ticks) {
        return ticks * 1000 / board::Clock::CORE_FREQ;
    }

    void _state_stop() {
        bool stop = getPenSensorStatus() != Heating::PenSensorStatus::OK;
        stop |= getHeatingElementStatus() == Heating::HeatingElementStatus::SHORTED;
        stop |= getHeatingElementStatus() == Heating::HeatingElementStatus::BROKEN;
        stop |= get_steady_ms() > STANDBY_TIME_MS;
        if (stop) {
            _preset.set_standby();
        }
    }

    void _state_start() {
        // reset meters
        _measure_ticks = 0;
        _measurements_count = 0;
        _cpu_voltage_mv_heat = 0;
        _supply_voltage_mv_heat = 0;
        _pen_current_ma = 0;
        _power_mw = 0;
        if (_requested_power_mw < HEATING_MIN_POWER_MW) {
            board::adc.measure_idle_start();
            _requested_power_mw = 0;
            _requested_power_uw_period_ticks = 0;
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
        // enable heater (PWM ON)
        board::heater.on();
        // measure start
        board::adc.measure_heat_start();
        _heating_element_status = HeatingElementStatus::UNKNOWN;
        _pen_sensor_status = PenSensorStatus::UNKNOWN;
        _state = State::HEATING;
    }

    int _get_compensated_pen_current() {
        int current = board::adc.get_pen_current_ma();
        current -= _pen_current_ma_error;
        return current;
    }

    void _cumulate_heating_measured_values() {
        _cpu_voltage_mv_heat += board::adc.get_cpu_voltage_mv();
        _supply_voltage_mv_heat += board::adc.get_supply_voltage_mv();
        _pen_current_ma += _get_compensated_pen_current();
        _measurements_count++;
    }

    int64_t _get_power_energy_uw_period_ticks() {
        int64_t energy = _supply_voltage_mv_heat / _measurements_count;
        energy *= _pen_current_ma / _measurements_count;
        energy *= _measure_ticks;
        if (energy < 0) energy *= -1;
        return energy;
    }

    bool _check_heating_limits() {
        // check over current
        if ((_pen_current_ma / _measurements_count) > PEN_MAX_CURRENT_MA) return true;
        // check reached power
        if (_get_power_energy_uw_period_ticks() > _requested_power_uw_period_ticks) return true;
        // check low voltage
        if (_supply_voltage_mv_heat / _measurements_count < SUPPLY_VOLTAGE_HEATING_MIN_MV) return true;
        // check reached time
        if (_remaining_ticks <= _ms2ticks(STABILIZE_TIME_MS + IDLE_MIN_TIME_MS)) return true;
        // OK
        return false;
    }

    void _calculate_total_energy() {
        int64_t power_uw_period_ticks = _supply_voltage_mv_heat;
        power_uw_period_ticks *= _pen_current_ma;
        power_uw_period_ticks *= _measure_ticks;
        _power_mw = power_uw_period_ticks / _period_ticks / 1000;
        _energy_uw_ticks += power_uw_period_ticks;
        _measure_ticks = 0;
    }

    void _average_heating_measured_values() {
        _cpu_voltage_mv_heat /= _measurements_count;
        _supply_voltage_mv_heat /= _measurements_count;
        _pen_current_ma /= _measurements_count;
        if (_pen_current_ma < 0) _pen_current_ma *= -1;
    }

    void _calculate_pen_resistance() {
        if (_pen_current_ma > 0) {
            _pen_resistance_mo = _supply_voltage_mv_heat * 1000 / _pen_current_ma;
            if (_pen_resistance_mo < 1000000) return;
        }
        _pen_resistance_mo = 999999;
    }

    void _calculate_voltage_drop() {
        _supply_voltage_mv_drop = _supply_voltage_mv_heat - _supply_voltage_mv_idle;
    }

    void _check_heating_element() {
        if (_pen_resistance_mo < PEN_RESISTANCE_SHORTED) {
            _heating_element_status = HeatingElementStatus::SHORTED;
        } else if (_pen_resistance_mo < PEN_RESISTANCE_MIN) {
            _heating_element_status = HeatingElementStatus::LOW_RESISTANCE;
        } else if (_pen_resistance_mo > PEN_RESISTANCE_BROKEN) {
            _heating_element_status = HeatingElementStatus::BROKEN;
        } else if (_pen_resistance_mo > PEN_RESISTANCE_MAX) {
            _heating_element_status = HeatingElementStatus::HIGH_RESISTANCE;
        } else {
            _heating_element_status = HeatingElementStatus::OK;
        }
    }

    void _state_heating(unsigned delta_ticks) {
        _measure_ticks += delta_ticks;
        if (board::adc.process() != board::Adc::State::DONE) return;
        _cumulate_heating_measured_values();
        if (!_check_heating_limits()) {
            // continue heating
            board::adc.measure_heat_start();
        } else {
            // disable heater (PWM OFF)
            board::heater.off();
            _average_heating_measured_values();
            _calculate_total_energy();
            _calculate_pen_resistance();
            _calculate_voltage_drop();
            _check_heating_element();
            _state = State::STABILIZE;
        }
    }

    void _state_stabilize(unsigned delta_ticks) {
        _measure_ticks += delta_ticks;
        if (_measure_ticks < _ms2ticks(STABILIZE_TIME_MS)) return;
        board::adc.measure_idle_start();
        _measure_ticks = 0;
        _measurements_count = 0;
        _cpu_voltage_mv_idle = 0;
        _supply_voltage_mv_idle = 0;
        _pen_current_ma_error = 0;
        _cpu_temperature_mc = 0;
        _pen_temperature_mc = 0;
        _state = State::IDLE;
    }

    void _cumulate_idle_measured_values() {
        _cpu_voltage_mv_idle += board::adc.get_cpu_voltage_mv();
        _supply_voltage_mv_idle += board::adc.get_supply_voltage_mv();
        _pen_current_ma_error += board::adc.get_pen_current_ma();
        _cpu_temperature_mc += board::adc.get_cpu_temperature_mc();
        _pen_temperature_mc += board::adc.get_pen_temperature_mc();
        _measurements_count++;
    }

    void _average_idle_measured_values() {
        _cpu_voltage_mv_idle /= _measurements_count;
        _supply_voltage_mv_idle /= _measurements_count;
        _pen_current_ma_error /= _measurements_count;
        _cpu_temperature_mc /= _measurements_count;
        _pen_temperature_mc /= _measurements_count;
    }

    void _check_pen_sensor() {
        if (board::adc.is_pen_sensor_ok()) {
            _pen_sensor_status = PenSensorStatus::OK;
        } else {
            _pen_sensor_status = PenSensorStatus::BROKEN;
            _heating_element_status = HeatingElementStatus::UNKNOWN;
        }
    }

    void _state_idle() {
        if (board::adc.process() != board::Adc::State::DONE) return;
        _cumulate_idle_measured_values();
        if (_remaining_ticks > 0) {
            // continue in idle
            board::adc.measure_idle_start();
        } else {
            _average_idle_measured_values();
            _check_pen_sensor();
            _state_stop();
            _state = State::STOP;
        }
    }

public:
    /** Getter for actual power

    Return:
        Actual power in mW
    */
    int get_power_mw() {
        return _power_mw;
    }

    /** Getter for requested power

    Return:
        requested power in mW
    */
    int get_requested_power_mw() {
        return _requested_power_mw;
    }

    /** Getter for measured pen resistance

    Return:
       pen resistance in mOhm
    */
    int get_pen_resistance_mo() {
        return _pen_resistance_mo;
    }

    /** Getter for total consumed energy

    Return:
        total energy in mWh
    */
    int get_energy_mwh() {
        return _energy_uw_ticks / board::Clock::CORE_FREQ / 1000 / 3600;
    }

    /** Getter how long is pen steady

    Return:
        steady time in ms
    */
    int get_steady_ms() {
        return _steady_ticks / (board::Clock::CORE_FREQ / 1000);
    }

    /** Getter for CPU voltage during heating

    Return:
        CPU voltage during heating in mV
    */
    int get_cpu_voltage_mv_heat() {
        return _cpu_voltage_mv_heat;
    }

    /** Getter for CPU voltage during idle

    Return:
        CPU voltage during idle in mV
    */
    int get_cpu_voltage_mv_idle() {
        return _cpu_voltage_mv_idle;
    }

    /** Getter for supply voltage during heating

    Return:
        supply voltage during heating in mV
    */
    int get_supply_voltage_mv_heat() {
        return _supply_voltage_mv_heat;
    }

    /** Getter for supply voltage during idle

    Return:
        supply voltage during idle in mV
    */
    int get_supply_voltage_mv_idle() {
        return _supply_voltage_mv_idle;
    }

    /** Getter for pen current during heat

    Return:
        pen current during heat in mA
    */
    int get_pen_current_ma() {
        return _pen_current_ma;
    }

    /** Getter for pen current during idle

    Return:
        pen current during idle in mA
    */
    int get_pen_current_ma_error() {
        return _pen_current_ma_error;
    }

    /** Getter for supply voltage drop

    Return:
        supply voltage drop when heating in mV
    */
    int get_supply_voltage_mv_drop() {
        return _supply_voltage_mv_drop;
    }

    /** Getter for CPU temperature
    (used for measuring temperature of other end of thermo coupler in pen)

    Return:
        CPU temperature in 1/1000 degree Celsius
    */
    int get_cpu_temperature_mc() {
        return _cpu_temperature_mc;
    }

    /** Getter for PEN temperature difference
    (temperature difference between both ends of thermo coupler)

    Return:
        PEN temperature in 1/1000 degree Celsius
    */
    int get_pen_temperature_mc() {
        return _pen_temperature_mc;
    }

    /** Getter for real PEN temperature

    Return:
        PEN temperature in 1/1000 degree Celsius
    */
    int get_real_pen_temperature_mc() {
        return _cpu_temperature_mc + _pen_temperature_mc;
    }

    /** Getter pen heating element state
    indicate if PEN is OK, shorted, broken, with low or high resistance

    Return:
        state from enum HeatingElementStatus
    */
    HeatingElementStatus getHeatingElementStatus() {
        return _heating_element_status;
    }

    /** Getter pen temperature sensor state
    indicate if PEN temperature sensor is OK, broken or shorted
    (TODO: shorted detection is currently not implemented)

    Return:
        state from enum PenSensorStatus
    */
    PenSensorStatus getPenSensorStatus() {
        return _pen_sensor_status;
    }

    /** Initialize module
    */
    void init() {
        _pid.set_constants(PID_K_PROPORTIONAL, PID_K_INTEGRAL, PID_K_DERIVATE, 1000 / PERIOD_TIME_MS, HEATING_POWER_MAX);
    }

    Preset &get_preset() {
        return _preset;
    }

    /** Start heating cycle
    */
    void start() {
        int power_mw = 0;
        if (getPenSensorStatus() != Heating::PenSensorStatus::OK) {
            _pid.reset();
        } else {
            power_mw = _pid.process(get_real_pen_temperature_mc(), _preset.get_temperature());
        }
        _period_ticks = PERIOD_TIME_MS * (board::Clock::CORE_FREQ / 1000);
        _remaining_ticks += _period_ticks;
        _requested_power_mw = power_mw;
        _requested_power_uw_period_ticks = (uint64_t)power_mw * _period_ticks * 1000;
        _state = State::START;
    }

    /** Process state machine

    Main application always wait for state STOP,
    after STOP can be heating cycle started again,
    but manually by calling start()

    Arguments:
        delta_ticks: number of ticks between each process call

    Return:
        actual state of heating cycle
    */
    State process(unsigned delta_ticks) {
        _uptime_ticks += delta_ticks;
        _remaining_ticks -= delta_ticks;
        _steady_ticks += delta_ticks;
        switch (_state) {
        case State::STOP:
            break;
        case State::START:
            _state_start();
            break;
        case State::HEATING:
            _state_heating(delta_ticks);
            break;
        case State::STABILIZE:
            _state_stabilize(delta_ticks);
            break;
        case State::IDLE:
            _state_idle();
            break;
        }
        return _state;
    }

};
