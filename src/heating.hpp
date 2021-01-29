#pragma once

#include "board/clock.hpp"
#include "board/heater.hpp"
#include "board/hwid.hpp"
#include "board/adc.hpp"
#include "lib/pid.hpp"
#include "preset.hpp"

/** Class for controlling heating and measuring cycle
*/
class Heating {
 public:
    static const int PERIOD_TIME_MS = 125;  // ms
    static const int STANDBY_TIME_MS = 30000;  // ms
    static const int PID_K_PROPORTIONAL = 450;
    static const int PID_K_INTEGRAL = 1000;
    static const int PID_K_DERIVATE = 50;
    static const int RTM_HEATING_POWER_MAX_MW = 40 * 1000;  // mW
    static const int RTU_HEATING_POWER_MAX_MW = 150 * 100;  // mW
    static const int IDLE_MIN_TIME_MS = 3;  // ms
    static const int STABILIZE_TIME_MS = 2;  // ms
    static const int HEATING_MIN_POWER_MW = 100;  // mW
    static const int TIP_MAX_CURRENT_MA = 9000;  // mA
    static const int SUPPLY_VOLTAGE_HEATING_MIN_MV = 4300;  // mV
    static const int RTM_SUPPLY_VOLTAGE_MAX_MV = 14000;  // mV
    static const int RTU_SUPPLY_VOTLAGE_MAX_MV = 25000;  // mV
    static const int TIP_RESISTANCE_SHORTED_MO = 500;  // mOhm
    static const int RTM_TIP_RESISTANCE_MIN_MO = 1500;  // mOhm
    static const int RTM_TIP_RESISTANCE_MAX_MO = 2500;  // mOhm
    static const int RTU_TIP_RESISTANCE_MIN_MO = 3000;  // mOhm
    static const int RTU_TIP_RESISTANCE_MAX_MO = 4000;  // mOhm
    static const int TIP_RESISTANCE_BROKEN_MO = 100000;  // mOhm
    static const int OVERHEAT_TEMPERATURE_MC_HW0X = 500 * 1000;  // 1/1000 degree Celsius
    static const int OVERHEAT_TEMPERATURE_MC = 600 * 1000;  // 1/1000 degree Celsius

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

    enum class TipSensorStatus {
        UNKNOWN,
        OK,
        OVERHEAT,
        BROKEN,
        SHORTED,
    } _tip_sensor_status = TipSensorStatus::UNKNOWN;
    
    enum class TipType {
        UNKNOWN,
        RTM,
        RTU,
    } _tip_type = TipType::UNKNOWN;

 private:
    Settings &_settings;
    Preset _preset;
    lib::Pid _pid;

    uint64_t _uptime_ticks = 0;
    int64_t _requested_power_uw_period_ticks = 0;  // uW * _required_period_ticks
    int64_t _energy_uw_ticks = 0;  // uW * CORE_FREQ
    int64_t _steady_ticks = 0;  // ticks when power is steady
    unsigned _required_period_ticks = 0;
    unsigned _period_ticks = 0;

    unsigned _measure_ticks = 0;
    int _measurements_count = 0;

    int _requested_power_mw = 0;  // mW
    int _power_mw = 0;  // mW
    int _cpu_voltage_mv_heat = 0;  // mV
    int _cpu_voltage_mv_idle = 0;  // mV
    int _supply_voltage_mv_heat = 0;  // mV
    int _supply_voltage_mv_idle = 0;  // mV
    int _supply_voltage_mv_drop = 0;  // mV
    int _heater_current_ma = 0;  // mA
    int _heater_current_ma_error = 0;  // mA
    int _heater_resistance_mo = 0;  // mOhm
    int _tip_temperature_mc = 0;  // 1/1000 degree C
    int _cpu_temperature_mc = 0;  // 1/1000 degree C

    int _average_requested_power = 0;
    int _average_requested_power_short = 0;

    int64_t _ms2ticks(const int64_t time_ms) const {
        return time_ms * board::Clock::CORE_FREQ / 1000;
    }

    int _ticks2ms(const int64_t ticks) const {
        return static_cast<int>(ticks * 1000 / board::Clock::CORE_FREQ);
    }

    void _state_stop() {
        bool stop = getTipSensorStatus() != Heating::TipSensorStatus::OK;
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
        _heater_current_ma = 0;
        _power_mw = 0;
        _tip_type = TipType::UNKNOWN;
        if (_requested_power_mw < HEATING_MIN_POWER_MW) {
            board::Adc::get_instance().measure_idle_start();
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
        board::Heater::get_instance().on();
        // measure start
        board::Adc::get_instance().measure_heat_start();
        _heating_element_status = HeatingElementStatus::UNKNOWN;
        _tip_sensor_status = TipSensorStatus::UNKNOWN;
        _state = State::HEATING;
    }

    int _get_compensated_heater_current() {
        int current = board::Adc::get_instance().get_heater_current_ma();
        current -= _heater_current_ma_error;
        return current;
    }

    void _cumulate_heating_measured_values() {
        _cpu_voltage_mv_heat += board::Adc::get_instance().get_cpu_voltage_mv();
        _supply_voltage_mv_heat += board::Adc::get_instance().get_supply_voltage_mv();
        _heater_current_ma += _get_compensated_heater_current();
        _measurements_count++;
    }

    int64_t _get_power_energy_uw_period_ticks() const {
        int64_t energy = _supply_voltage_mv_heat / _measurements_count;
        energy *= _heater_current_ma / _measurements_count;
        energy *= _measure_ticks;
        if (energy < 0) energy *= -1;
        return energy;
    }

    bool _check_heating_limits() const {
        // check over current
        if ((_heater_current_ma / _measurements_count) > TIP_MAX_CURRENT_MA) return true;
        // check reached power
        if (_get_power_energy_uw_period_ticks() > _requested_power_uw_period_ticks) return true;
        // check low voltage
        if (_supply_voltage_mv_heat / _measurements_count < SUPPLY_VOLTAGE_HEATING_MIN_MV) return true;
        // check reached time
        if (_period_ticks > (_required_period_ticks - _ms2ticks(STABILIZE_TIME_MS + IDLE_MIN_TIME_MS))) return true;
        // OK
        return false;
    }

    void _calculate_total_energy() {
        int64_t power_uw_period_ticks = _supply_voltage_mv_heat;
        power_uw_period_ticks *= _heater_current_ma;
        power_uw_period_ticks *= _measure_ticks;
        _power_mw = static_cast<int>(power_uw_period_ticks / _required_period_ticks / 1000);
        _energy_uw_ticks += power_uw_period_ticks;
        _measure_ticks = 0;
    }

    void _average_heating_measured_values() {
        _cpu_voltage_mv_heat /= _measurements_count;
        _supply_voltage_mv_heat /= _measurements_count;
        _heater_current_ma /= _measurements_count;
        if (_heater_current_ma < 0) _heater_current_ma *= -1;
    }

    void _calculate_tip_resistance() {
        if (_heater_current_ma > 0) {
            _heater_resistance_mo = _supply_voltage_mv_heat * 1000 / _heater_current_ma;
            if (_heater_resistance_mo < 1000000) return;
        }
        _heater_resistance_mo = 999999;
    }

    void _calculate_voltage_drop() {
        _supply_voltage_mv_drop = _supply_voltage_mv_heat - _supply_voltage_mv_idle;
    }

    void _check_heating_element() {
        if (_heater_resistance_mo < TIP_RESISTANCE_SHORTED_MO) {
            _heating_element_status = HeatingElementStatus::SHORTED;
        } else if (_heater_resistance_mo < RTM_TIP_RESISTANCE_MIN_MO) {
            _heating_element_status = HeatingElementStatus::LOW_RESISTANCE;
        } else if (_heater_resistance_mo > RTM_TIP_RESISTANCE_MAX_MO && _heater_resistance_mo < RTU_TIP_RESISTANCE_MIN_MO) {
            _heating_element_status = HeatingElementStatus::LOW_RESISTANCE;
        } else if (_heater_resistance_mo > TIP_RESISTANCE_BROKEN_MO) {
            _heating_element_status = HeatingElementStatus::BROKEN;
        } else if (_heater_resistance_mo > RTU_TIP_RESISTANCE_MAX_MO) {
            _heating_element_status = HeatingElementStatus::HIGH_RESISTANCE;
        } else {
            _heating_element_status = HeatingElementStatus::OK;
        }
    }
    
    void _check_tip_type() {
        if (_heater_resistance_mo > RTU_TIP_RESISTANCE_MIN_MO && _heater_resistance_mo < RTU_TIP_RESISTANCE_MAX_MO) {
            _tip_type = TipType::RTU;
        } else if (_heater_resistance_mo > RTM_TIP_RESISTANCE_MIN_MO && _heater_resistance_mo < RTM_TIP_RESISTANCE_MAX_MO){
            _tip_type = TipType::RTM;
        } else {
            _tip_type = TipType::UNKNOWN;
        }
    }

    void _state_heating(const unsigned delta_ticks) {
        _measure_ticks += delta_ticks;
        if (board::Adc::get_instance().process() != board::Adc::State::DONE) return;
        _cumulate_heating_measured_values();
        if (!_check_heating_limits()) {
            // continue heating
            board::Adc::get_instance().measure_heat_start();
        } else {
            // disable heater (PWM OFF)
            board::Heater::get_instance().off();
            _average_heating_measured_values();
            _calculate_total_energy();
            _calculate_tip_resistance();
            _check_tip_type();
            _calculate_voltage_drop();
            _check_heating_element();
            _state = State::STABILIZE;
        }
    }

    void _state_stabilize(const unsigned delta_ticks) {
        _measure_ticks += delta_ticks;
        if (_measure_ticks < _ms2ticks(STABILIZE_TIME_MS)) return;
        board::Adc::get_instance().measure_idle_start();
        _measure_ticks = 0;
        _measurements_count = 0;
        _cpu_voltage_mv_idle = 0;
        _supply_voltage_mv_idle = 0;
        _heater_current_ma_error = 0;
        _cpu_temperature_mc = 0;
        _tip_temperature_mc = 0;
        _state = State::IDLE;
    }

    void _cumulate_idle_measured_values() {
        _cpu_voltage_mv_idle += board::Adc::get_instance().get_cpu_voltage_mv();
        _supply_voltage_mv_idle += board::Adc::get_instance().get_supply_voltage_mv();
        _heater_current_ma_error += board::Adc::get_instance().get_heater_current_ma();
        _cpu_temperature_mc += board::Adc::get_instance().get_cpu_temperature_mc();
        _tip_temperature_mc += board::Adc::get_instance().get_tip_temperature_mc();
        _measurements_count++;
    }

    void _average_idle_measured_values() {
        _cpu_voltage_mv_idle /= _measurements_count;
        _supply_voltage_mv_idle /= _measurements_count;
        _heater_current_ma_error /= _measurements_count;
        _cpu_temperature_mc /= _measurements_count;
        _tip_temperature_mc /= _measurements_count;
    }

    void _check_tip_sensor() {
        if (board::Adc::get_instance().is_tip_sensor_ok()) {
            int overheat_temperature_mc = OVERHEAT_TEMPERATURE_MC;
            if (board::HwId::get_instance().get_hw_revision() == board::HwId::HwRevision::HW_0X) {
                overheat_temperature_mc = OVERHEAT_TEMPERATURE_MC_HW0X;
            }
            if (get_real_tip_temperature_mc() < overheat_temperature_mc) {
                _tip_sensor_status = TipSensorStatus::OK;
            } else {
                _tip_sensor_status = TipSensorStatus::OVERHEAT;
            }
        } else {
            _tip_sensor_status = TipSensorStatus::BROKEN;
            _heating_element_status = HeatingElementStatus::UNKNOWN;
        }
    }

    void _state_idle() {
        if (board::Adc::get_instance().process() != board::Adc::State::DONE) return;
        _cumulate_idle_measured_values();
        if (_period_ticks < _required_period_ticks) {
            // continue in idle
            board::Adc::get_instance().measure_idle_start();
        } else {
            _average_idle_measured_values();
            _check_tip_sensor();
            _state_stop();
            _state = State::STOP;
        }
    }

 public:
    Heating(Settings &settings) :
    _settings(settings),
    _preset(settings) {}

    /** Getter for actual power

    Return:
        Actual power in mW
    */
    int get_power_mw() const {
        return _power_mw;
    }

    /** Getter for requested power

    Return:
        requested power in mW
    */
    int get_requested_power_mw() const {
        return _requested_power_mw;
    }

    /** Getter for measured heater resistance

    Return:
       heater resistance in mOhm
    */
    int get_heater_resistance_mo() const {
        return _heater_resistance_mo;
    }

    /** Getter for total consumed energy

    Return:
        total energy in mWh
    */
    int get_energy_mwh() const {
        return static_cast<int>(_energy_uw_ticks / board::Clock::CORE_FREQ / 1000 / 3600);
    }

    /** Getter how long is steady

    Return:
        steady time in ms
    */
    int get_steady_ms() const {
        return static_cast<int>(_steady_ticks / (board::Clock::CORE_FREQ / 1000));
    }

    /** Getter for CPU voltage during heating

    Return:
        CPU voltage during heating in mV
    */
    int get_cpu_voltage_mv_heat() const {
        return _cpu_voltage_mv_heat;
    }

    /** Getter for CPU voltage during idle

    Return:
        CPU voltage during idle in mV
    */
    int get_cpu_voltage_mv_idle() const {
        return _cpu_voltage_mv_idle;
    }

    /** Getter for supply voltage during heating

    Return:
        supply voltage during heating in mV
    */
    int get_supply_voltage_mv_heat() const {
        return _supply_voltage_mv_heat;
    }

    /** Getter for supply voltage during idle

    Return:
        supply voltage during idle in mV
    */
    int get_supply_voltage_mv_idle() const {
        return _supply_voltage_mv_idle;
    }

    /** Getter for heater current during heat

    Return:
        heater current during heat in mA
    */
    int get_heater_current_ma() const {
        return _heater_current_ma;
    }

    /** Getter for heater current during idle

    Return:
        heater current during idle in mA
    */
    int get_heater_current_ma_error() const {
        return _heater_current_ma_error;
    }

    /** Getter for supply voltage drop

    Return:
        supply voltage drop when heating in mV
    */
    int get_supply_voltage_mv_drop() const {
        return _supply_voltage_mv_drop;
    }

    /** Getter for CPU temperature
    (used for measuring temperature of other end of thermo coupler in tip)

    Return:
        CPU temperature in 1/1000 degree Celsius
    */
    int get_cpu_temperature_mc() const {
        return _cpu_temperature_mc;
    }

    /** Getter for TIP temperature difference
    (temperature difference between both ends of thermo coupler)

    Return:
        TIP temperature in 1/1000 degree Celsius
    */
    int get_tip_temperature_mc() const {
        return _tip_temperature_mc;
    }

    /** Getter for real TIP temperature

    Return:
        TIP temperature in 1/1000 degree Celsius
    */
    int get_real_tip_temperature_mc() const {
        return _cpu_temperature_mc + _tip_temperature_mc;
    }

    /** Getter tip heating element state
    indicate if TIP is OK, shorted, broken, with low or high resistance

    Return:
        state from enum HeatingElementStatus
    */
    HeatingElementStatus getHeatingElementStatus() const {
        return _heating_element_status;
    }

    /** Getter tip temperature sensor state
    indicate if TIP temperature sensor is OK, broken or shorted
    (TODO: shorted detection is currently not implemented)

    Return:
        state from enum TipSensorStatus
    */
    TipSensorStatus getTipSensorStatus() const {
        return _tip_sensor_status;
    }
    
    /** Getter tip type
    indicate whether RTM or RTU tip is detected

    Return:
        state from enum TipType
    */
    TipType getTipType() const {
        return _tip_type;
    }

    /** Initialize module
    */
    void init() {
//        _pid.set_constants(PID_K_PROPORTIONAL, PID_K_INTEGRAL, PID_K_DERIVATE, PERIOD_TIME_MS, HEATING_POWER_MAX_MW);
    }

    Preset &get_preset() {
        return _preset;
    }

    /** Start heating cycle
    */
    void start() {
        if (_tip_type == TipType::RTU) {
            _pid.set_constants(PID_K_PROPORTIONAL, PID_K_INTEGRAL, PID_K_DERIVATE, PERIOD_TIME_MS, RTU_HEATING_POWER_MAX_MW);
        } else {
            _pid.set_constants(PID_K_PROPORTIONAL, PID_K_INTEGRAL, PID_K_DERIVATE, PERIOD_TIME_MS, RTM_HEATING_POWER_MAX_MW);
        }
        if (_preset.is_standby() || getTipSensorStatus() != Heating::TipSensorStatus::OK) {
            _pid.reset();
            _requested_power_mw = 0;
        } else {
            _requested_power_mw = _pid.process(get_real_tip_temperature_mc(), _preset.get_temperature());
        }
        _required_period_ticks = PERIOD_TIME_MS * (board::Clock::CORE_FREQ / 1000);
        if (_period_ticks < _required_period_ticks) {
            _period_ticks = 0;
        } else {
            _period_ticks -= _required_period_ticks;
        }
        _requested_power_uw_period_ticks = 1000ll * _requested_power_mw * _required_period_ticks;
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
    State process(const unsigned delta_ticks) {
        _uptime_ticks += delta_ticks;
        _period_ticks += delta_ticks;
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
