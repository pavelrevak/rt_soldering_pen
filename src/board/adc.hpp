#pragma once

#include "io/reg/cortexm/nvic.hpp"
#include "io/reg/stm32/f0/isr.hpp"
#include "io/reg/stm32/f0/adc.hpp"
#include "io/reg/stm32/f0/dma.hpp"
#include "io/reg/stm32/f0/sysmem.hpp"
#include "board/gpio.hpp"

namespace Board {

class Adc {
private:
    static const unsigned DMA_CH_ADC = 1;

    io::Adc &r_adc = io::ADC;
    io::Dma &r_dma = io::DMA1;
    io::Dma::Channel &r_dma_adc = r_dma.CHANNEL(DMA_CH_ADC);

    GpioPin<io::base::GPIOA, 0> pen_current_input;
    GpioPin<io::base::GPIOA, 1> pen_temperature_input;
    GpioPin<io::base::GPIOA, 3> supply_voltage_input;

    volatile uint16_t measured[4];

    void start_dma_measure(const int count) {
        // Configure DMA for ADC
        r_dma.IFCR.clear_flags(DMA_CH_ADC);
        r_dma_adc.CCR.r = 0x00000000;
        r_dma_adc.CMAR.MAR = reinterpret_cast<size_t>(&measured);
        r_dma_adc.CPAR.PAR = reinterpret_cast<size_t>(&r_adc.DR.DATA);
        r_dma_adc.CNDTR.NDT = count;
        io::Dma::Channel::Ccr dma_adc_ccr(0x00000000);
        dma_adc_ccr.b.EN = true;
        dma_adc_ccr.b.MINC = true;
        dma_adc_ccr.b.PSIZE = io::Dma::Channel::Ccr::Size::SIZE_16;
        dma_adc_ccr.b.MSIZE = io::Dma::Channel::Ccr::Size::SIZE_16;
        dma_adc_ccr.b.PL = io::Dma::Channel::Ccr::Pl::LOW;
        r_dma_adc.CCR.r = dma_adc_ccr.r;
        // start ADC
        r_adc.CR.b.ADSTART = true;
    }

    enum class MeasureMode {
        NONE,
        IDLE,
        HEAT,
    } measure_mode = MeasureMode::NONE;

    static const int INDEX_HEAT_PEN_CURRENT = 0;
    static const int INDEX_HEAT_SUPPLY_VOLTAGE = 1;
    static const int INDEX_HEAT_CPU_REFERENCE = 2;
    static const int INDEX_IDLE_PEN_TEMPERATURE = 0;
    static const int INDEX_IDLE_SUPPLY_VOLTAGE = 1;
    static const int INDEX_IDLE_CPU_TEMPERATURE = 2;
    static const int INDEX_IDLE_CPU_REFERENCE = 3;

    static const uint16_t MAX_VALUE = 0xfff0;

    inline uint16_t get_measured(const int index) {
        return measured[index];
    }

    int actual_cpu_voltage = 0;
    int actual_cpu_temperature = 0;
    int actual_supply_voltage = 0;
    int actual_pen_temperature = 0;
    int actual_pen_current = 0;
    bool pen_sensor_ok = false;

    void calculate_cpu_voltage(const int index) {
        int tmp = (io::SYSMEM.VREFINT_CAL << 4) * 3300;
        tmp /= get_measured(index);
        actual_cpu_voltage = tmp;
    }

    void calculate_cpu_temperature(const int index) {
        int tmp = get_measured(index);
        tmp *= actual_cpu_voltage;
        tmp /= 3300;
        tmp -= (io::SYSMEM.TEMP30_CAL << 4);
        tmp *= 110 * 1000 - 30 * 1000;
        tmp /= (io::SYSMEM.TEMP110_CAL << 4) - (io::SYSMEM.TEMP30_CAL << 4);
        tmp += 30 * 1000;
        actual_cpu_temperature = tmp;
    }

    void calculate_supply_voltage(const int index) {
        int tmp = get_measured(index);
        tmp *= actual_cpu_voltage;
        tmp /= MAX_VALUE;
        tmp *= 68 + 10;  // divider with 68 and 10 kOhm
        tmp /= 10;
        actual_supply_voltage = tmp;
    }

    void calculate_pen_temperature(const int index) {
        int tmp = get_measured(index);
        pen_sensor_ok = tmp <= 65000;
        if (!pen_sensor_ok) {
            actual_pen_temperature = 0;
            return;
        }
        tmp *= actual_cpu_voltage;
        tmp /= MAX_VALUE;
        tmp *= 500 * 1000;  // 500 degrees at 3mV
        tmp /= 3000;
        actual_pen_temperature = tmp;
    }

    void calculate_pen_current(const int index) {
        int tmp = get_measured(index);
        tmp -= MAX_VALUE / 2;
        tmp *= actual_cpu_voltage;
        tmp /= MAX_VALUE;
        tmp *= 1000;  // mA
        tmp /= 110;  // 110 mV / A
        if (tmp < 0) tmp = -tmp;
        actual_pen_current = tmp;
    }

    void calculate_idle() {
        calculate_cpu_voltage(INDEX_IDLE_CPU_REFERENCE);
        calculate_cpu_temperature(INDEX_IDLE_CPU_TEMPERATURE);
        calculate_supply_voltage(INDEX_IDLE_SUPPLY_VOLTAGE);
        calculate_pen_temperature(INDEX_IDLE_PEN_TEMPERATURE);
    }

    void calculate_heat() {
        calculate_cpu_voltage(INDEX_HEAT_CPU_REFERENCE);
        calculate_supply_voltage(INDEX_HEAT_SUPPLY_VOLTAGE);
        calculate_pen_current(INDEX_HEAT_PEN_CURRENT);
    }

public:

    inline int get_cpu_voltage() {
        return actual_cpu_voltage;
    }

    inline int get_cpu_temperature() {
        return actual_cpu_temperature;
    }

    inline int get_supply_voltage() {
        return actual_supply_voltage;
    }

    inline int get_pen_temperature() {
        return actual_pen_temperature;
    }

    inline int get_pen_current() {
        return actual_pen_current;
    }

    inline bool is_pen_sensor_ok() {
        return pen_sensor_ok;
    }

    void init_hw() {
        // GPIO
        pen_current_input.configure_analog();
        pen_temperature_input.configure_analog();
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

    void measure_idle_start() {
        measure_mode = MeasureMode::IDLE;
        io::Adc::Chselr chselr(0x00000000);
        chselr.b.CHSEL1 = true;  // pen_temperature
        chselr.b.CHSEL3 = true;  // supply_voltage
        chselr.b.CHSEL16 = true;  // cpu_temperature
        chselr.b.CHSEL17 = true;  // cpu_reference
        r_adc.CHSELR.r = chselr.r;
        start_dma_measure(4);
    }

    void measure_heat_start() {
        measure_mode = MeasureMode::HEAT;
        io::Adc::Chselr chselr(0x00000000);
        chselr.b.CHSEL0 = true;  // pen_current
        chselr.b.CHSEL3 = true;  // supply_voltage
        chselr.b.CHSEL17 = true;  // cpu_reference
        r_adc.CHSELR.r = chselr.r;
        start_dma_measure(3);
    }

    bool measure_is_done() {
        if (!r_dma.ISR.TCIF(DMA_CH_ADC)) return false;
        r_dma.IFCR.clear_flags(DMA_CH_ADC);
        switch (measure_mode) {
            case MeasureMode::NONE: return false;
            case MeasureMode::IDLE: calculate_idle(); break;
            case MeasureMode::HEAT: calculate_heat(); break;
        }
        measure_mode = MeasureMode::NONE;
        return true;
    }
};

extern Adc adc;

}
