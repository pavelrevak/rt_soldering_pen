#pragma once

#include "io/reg/cortexm/nvic.hpp"
#include "io/reg/stm32/f0/isr.hpp"
#include "io/reg/stm32/f0/adc.hpp"
#include "io/reg/stm32/f0/dma.hpp"
#include "io/reg/stm32/f0/sysmem.hpp"
#include "board/hwid.hpp"
#include "board/gpio.hpp"

namespace board {

class Adc {

 public:

    enum class State {
        DONE,
        MEASURE_IDLE,
        MEASURE_HEAT,
    } _measure_state = State::DONE;

 private:
    struct HwConfiguration {
        const int32_t TEMP_SENS_MV_AT_500_DG;
        const int32_t SUPPLY_VOLTAGE_DIV_R1;
        const int32_t SUPPLY_VOLTAGE_DIV_R2;
        const int32_t CURRENT_SENS_MV_AT_1_AMP;
    };

    HwConfiguration _hw0x = {
        3000,  // TEMP_SENS_MV_AT_500_DG
        10,  // SUPPLY_VOLTAGE_DIV_R1
        68,  // SUPPLY_VOLTAGE_DIV_R2
        110,  // CURRENT_SENS_MV_AT_1_AMP
    };

    HwConfiguration _hw1x = {
        1450,  // TEMP_SENS_MV_AT_500_DG
        10,  // SUPPLY_VOLTAGE_DIV_R1
        82,  // SUPPLY_VOLTAGE_DIV_R2
        90,  // CURRENT_SENS_MV_AT_1_AMP
    };

    HwConfiguration *_conf = nullptr;

    static const unsigned DMA_CH_ADC = 1;
    static const uint16_t MAX_VALUE = 0xfff0;
    static const int TIP_SENSOR_MAX_VALUE = 60000;
    static const int TIP_SENSOR_ZERO_VALUE = 200;

    io::Adc &r_adc = io::ADC;
    io::Dma &r_dma = io::DMA1;
    io::Dma::Channel &r_dma_adc = r_dma.CHANNEL(DMA_CH_ADC);

    GpioPin<io::base::GPIOA, 0> heater_current_input;
    GpioPin<io::base::GPIOA, 1> tip_temperature_input;
    GpioPin<io::base::GPIOA, 3> supply_voltage_input;

    struct RawMeasured {};

    struct RawMeasuredIdle : public RawMeasured {
        uint16_t heater_current;
        uint16_t tip_temperature;
        uint16_t supply_voltage;
        uint16_t cpu_temperature;
        uint16_t cpu_reference;
    } _raw_measured_idle;

    static constexpr int RAW_MEASURE_IDLE_ITEMS = sizeof(RawMeasuredIdle) / sizeof(uint16_t);

    struct RawMeasuredHeat : public RawMeasured {
        uint16_t heater_current;
        uint16_t supply_voltage;
        uint16_t cpu_reference;
    } _raw_measured_heat;

    static constexpr int RAW_MEASURE_HEAT_ITEMS = sizeof(RawMeasuredHeat) / sizeof(uint16_t);

    int _actual_cpu_voltage_mv = 0;
    int _actual_supply_voltage_mv = 0;
    int _actual_cpu_temperature_mc = 0;
    int _actual_tip_temperature_mc = 0;
    int _actual_heater_current_ma = 0;
    bool _tip_sensor_ok = false;
    bool _tip_sensor_zero = true;

    void _start_dma_measure(RawMeasured &raw_measured, const size_t count) {
        // Configure DMA for ADC
        r_dma.IFCR.clear_flags(DMA_CH_ADC);
        r_dma_adc.CCR.r = 0x00000000;
        r_dma_adc.CMAR.MAR(&raw_measured);
        r_dma_adc.CPAR.PAR(&r_adc.DR.DATA);
        r_dma_adc.CNDTR.NDT = count;
        io::Dma::Channel::Ccr dma_adc_ccr(0x00000000);
        dma_adc_ccr.b.EN = true;
        dma_adc_ccr.b.MINC = true;
        dma_adc_ccr.PSIZE(io::Dma::Channel::Ccr::Size::SIZE_16);
        dma_adc_ccr.MSIZE(io::Dma::Channel::Ccr::Size::SIZE_16);
        dma_adc_ccr.PL(io::Dma::Channel::Ccr::Pl::LOW);
        r_dma_adc.CCR.r = dma_adc_ccr.r;
        // start ADC
        r_adc.CR.b.ADSTART = true;
    }

    void _calculate_cpu_voltage(const uint16_t raw_cpu_reference) {
        int tmp = (io::SYSMEM.VREFINT_CAL << 4) * 3300;
        tmp /= raw_cpu_reference;
        _actual_cpu_voltage_mv = tmp;
    }

    void _calculate_cpu_temperature(const uint16_t raw_cpu_temperature) {
        int tmp = raw_cpu_temperature;
        tmp *= _actual_cpu_voltage_mv;
        tmp /= 3300;
        tmp -= (io::SYSMEM.TEMP30_CAL << 4);
        tmp *= 110 * 1000 - 30 * 1000;
        tmp /= (io::SYSMEM.TEMP110_CAL << 4) - (io::SYSMEM.TEMP30_CAL << 4);
        tmp += 30 * 1000;
        _actual_cpu_temperature_mc = tmp;
    }

    void _calculate_supply_voltage(const uint16_t raw_supply_voltage) {
        int tmp = raw_supply_voltage;
        tmp *= _actual_cpu_voltage_mv;
        tmp /= MAX_VALUE;
        tmp *= _conf->SUPPLY_VOLTAGE_DIV_R2 + _conf->SUPPLY_VOLTAGE_DIV_R1;
        tmp /= _conf->SUPPLY_VOLTAGE_DIV_R1;
        _actual_supply_voltage_mv = tmp;
    }

    void _calculate_tip_temperature(const uint16_t raw_tip_temperature) {
        int tmp = raw_tip_temperature;
        _tip_sensor_zero = tmp < TIP_SENSOR_ZERO_VALUE;
        _tip_sensor_ok = tmp <= TIP_SENSOR_MAX_VALUE;
        if (!_tip_sensor_ok) {
            _actual_tip_temperature_mc = 0;
            return;
        }
        tmp *= _actual_cpu_voltage_mv;
        tmp /= MAX_VALUE;
        tmp *= 500 * 1000;  // 500 degrees at 3V
        tmp /= _conf->TEMP_SENS_MV_AT_500_DG;
        _actual_tip_temperature_mc = tmp;
    }

    void _calculate_heater_current(const uint16_t raw_heater_current) {
        int tmp = raw_heater_current;
        tmp -= MAX_VALUE / 2;
        tmp *= _actual_cpu_voltage_mv;
        tmp /= MAX_VALUE;
        tmp *= 1000;  // mA
        tmp /= _conf->CURRENT_SENS_MV_AT_1_AMP;
        _actual_heater_current_ma = tmp;
    }

    void _calculate_idle() {
        _calculate_cpu_voltage(_raw_measured_idle.cpu_reference);
        _calculate_cpu_temperature(_raw_measured_idle.cpu_temperature);
        _calculate_supply_voltage(_raw_measured_idle.supply_voltage);
        _calculate_tip_temperature(_raw_measured_idle.tip_temperature);
        _calculate_heater_current(_raw_measured_idle.heater_current);
    }

    void _calculate_heat() {
        _calculate_cpu_voltage(_raw_measured_heat.cpu_reference);
        _calculate_supply_voltage(_raw_measured_heat.supply_voltage);
        _calculate_heater_current(_raw_measured_heat.heater_current);
    }

    void _process_measure() {
        if (r_dma.ISR.TCIF(DMA_CH_ADC)) {
            r_dma.IFCR.clear_flags(DMA_CH_ADC);
            _measure_state = State::DONE;
        }
    }

    void _process_idle() {
        _process_measure();
        if (_measure_state == State::DONE) {
            _calculate_idle();
        }
    }

    void _process_heat() {
        _process_measure();
        if (_measure_state == State::DONE) {
            _calculate_heat();
        }
    }

 public:
    /** Last measured CPU voltage

    Return:
        CPU voltage in mV
    */
    int get_cpu_voltage_mv() {
        return _actual_cpu_voltage_mv;
    }

    /** Last measured supply voltage

    Return:
        supply voltage in mV
    */
    int get_supply_voltage_mv() {
        return _actual_supply_voltage_mv;
    }

    /** Last measured CPU temperature

    Return:
        CPU temperature in 1/1000 degree Celsius
    */
    int get_cpu_temperature_mc() {
        return _actual_cpu_temperature_mc;
    }

    /** Last measured tip sensor temperature

    Return:
        CPU temperature in 1/1000 degree Celsius
    */
    int get_tip_temperature_mc() {
        return _actual_tip_temperature_mc;
    }

    /** Last measured heater current

    Return:
        heater current in mA
    */
    int get_heater_current_ma() {
        return _actual_heater_current_ma;
    }

    /** Last state of tip temperature sensor

    Return:
        true if is OK
    */
    bool is_tip_sensor_ok() {
        return _tip_sensor_ok;
    }

    /** Last state of tip temperature sensor

    Return:
        true if is OK
    */
    bool is_tip_sensor_zero() {
        return _tip_sensor_zero;
    }

    /** HW initialization
    */
    void init_hw() {
        // GPIO
        switch (HwId::get_instance().get_hw_revision()) {
        case HwId::HwRevision::UNKNOWN:
            _conf = nullptr;
            break;
        case HwId::HwRevision::HW_0X:
            _conf = &_hw0x;
            break;
        case HwId::HwRevision::HW_1X:
            _conf = &_hw1x;
            break;
        }
        heater_current_input.configure_analog();
        tip_temperature_input.configure_analog();
        supply_voltage_input.configure_analog();
        // ADC
        r_adc.CFGR2.b.CKMODE = io::Adc::Cfgr2::Ckmode::PCLK_DIV4;
        r_adc.CR.b.ADCAL = true;
        while (r_adc.CR.b.ADCAL);
        while (!r_adc.CR.b.ADEN) {
            r_adc.CR.b.ADEN = true;
        }
        while (!r_adc.ISR.b.ADRDY);
        r_adc.SMPR.b.SMP = io::Adc::Smpr::Smp::SMP_71_5;
        io::Adc::Cfgr1 cfgr1(0x00000000);
        cfgr1.b.RES = io::Adc::Cfgr1::Res::RES_12;
        cfgr1.b.ALIGN = true;
        cfgr1.b.DMAEN = true;
        r_adc.CFGR1.r = cfgr1.r;
        io::Adc::Ccr ccr(0x00000000);
        ccr.b.VREFEN = true;
        ccr.b.TSEN = true;
        r_adc.CCR.r = ccr.r;
    }

    /** Start measure during idle
    */
    void measure_idle_start() {
        _measure_state = State::MEASURE_IDLE;
        io::Adc::Chselr chselr(0x00000000);
        chselr.b.CHSEL0 = true;  // heater_current
        chselr.b.CHSEL1 = true;  // tip_temperature
        chselr.b.CHSEL3 = true;  // supply_voltage
        chselr.b.CHSEL16 = true;  // cpu_temperature
        chselr.b.CHSEL17 = true;  // cpu_reference
        r_adc.CHSELR.r = chselr.r;
        _start_dma_measure(_raw_measured_idle, RAW_MEASURE_IDLE_ITEMS);
    }

    /** Start measure during heating
    */
    void measure_heat_start() {
        _measure_state = State::MEASURE_HEAT;
        io::Adc::Chselr chselr(0x00000000);
        chselr.b.CHSEL0 = true;  // heater_current
        chselr.b.CHSEL3 = true;  // supply_voltage
        chselr.b.CHSEL17 = true;  // cpu_reference
        r_adc.CHSELR.r = chselr.r;
        _start_dma_measure(_raw_measured_heat, RAW_MEASURE_HEAT_ITEMS);
    }

    /** process measurement

    This method is used also for waiting when measurement is DONE

    Return:
        actual State
    */
    State process() {
        switch (_measure_state) {
        case State::MEASURE_IDLE:
            _process_idle();
            break;
        case State::MEASURE_HEAT:
            _process_heat();
            break;
        case State::DONE:
            break;
        }
        return _measure_state;
    }

    static Adc &get_instance() {
        static Adc instance;
        return instance;
    }
};

}  // namespace board
