#pragma once

#include "io/reg/cortexm/nvic.hpp"
#include "io/reg/stm32/f0/isr.hpp"
#include "io/reg/stm32/f0/adc.hpp"
#include "io/reg/stm32/f0/dma.hpp"
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

    uint16_t measured[4];

    volatile unsigned measured_counter = 0;
    unsigned old_measured_counter = 0;

    void measure_start(const int count) {
        // Configure DMA for ADC
        r_dma.IFCR.clear_flags(DMA_CH_ADC);
        r_dma_adc.CCR.r = 0x00000000;
        r_dma_adc.CMAR.MAR = reinterpret_cast<size_t>(&measured);
        r_dma_adc.CPAR.PAR = reinterpret_cast<size_t>(&r_adc.DR.DATA);
        r_dma_adc.CNDTR.NDT = count;
        io::Dma::Channel::Ccr dma_adc_ccr(0x00000000);
        dma_adc_ccr.b.EN = true;
        dma_adc_ccr.b.TCIE = true;
        dma_adc_ccr.b.HTIE = true;
        dma_adc_ccr.b.TEIE = true;
        dma_adc_ccr.b.MINC = true;
        dma_adc_ccr.b.PSIZE = io::Dma::Channel::Ccr::Size::SIZE_16;
        dma_adc_ccr.b.MSIZE = io::Dma::Channel::Ccr::Size::SIZE_16;
        dma_adc_ccr.b.PL = io::Dma::Channel::Ccr::Pl::LOW;
        r_dma_adc.CCR.r = dma_adc_ccr.r;
        // start ADC
        r_adc.CR.b.ADSTART = true;
    }

public:

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

        // enable interrupt
        io::NVIC.iser(io::isr::DMA1_CH1_isr);
    }

    void measure_heat_start() {
        io::Adc::Chselr chselr(0x00000000);
        chselr.b.CHSEL0 = true;  // pen_current
        chselr.b.CHSEL3 = true;  // supply_voltage
        chselr.b.CHSEL17 = true;  // cpu_reference
        r_adc.CHSELR.r = chselr.r;
        measure_start(3);
    }

    void measure_idle_start() {
        io::Adc::Chselr chselr(0x00000000);
        chselr.b.CHSEL1 = true;  // pen_temperature
        chselr.b.CHSEL3 = true;  // supply_voltage
        chselr.b.CHSEL16 = true;  // cpu_temperature
        chselr.b.CHSEL17 = true;  // cpu_reference
        r_adc.CHSELR.r = chselr.r;
        measure_start(4);
    }

    void dma_handler() {
        if (r_dma.ISR.TCIF(DMA_CH_ADC)) {
            measured_counter++;
        }
        r_dma.IFCR.clear_flags(DMA_CH_ADC);
    }

    bool measure_is_done() {
        if (old_measured_counter != measured_counter) {
            old_measured_counter = measured_counter;
            return true;
        }
        return false;
    }

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
};

extern Adc adc;

}
