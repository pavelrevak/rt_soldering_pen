#pragma once

/**
 * Configure Clock module in CPU
 *
 * CPU frequency is set to 8MHz, although CPU is faster,
 * higher frequency is not needed, because STM32F0 is very fast,
 * also higher frequency generate more heat and this can have
 * bad influence to internal temperature sensor.
 */

#include "io/reg/stm32/f0/flash.hpp"
#include "io/reg/stm32/f0/rcc.hpp"

namespace Board {

class Clock {
public:
    static const unsigned CORE_FREQ = 8000000;

    void init_hw() {
        // Set flash latency
        io::FLASH.ACR.b.LATENCY = 0;

        // Enable HSI oscillator 8MHz
        io::RCC.CR.b.HSION = true;
        while (!io::RCC.CR.b.HSIRDY);
        io::RCC.CFGR.b.SW = io::Rcc::Cfgr::Sw::HSI;

        // Set prescalers for AHB and APB
        io::RCC.CFGR.b.HPRE = io::Rcc::Cfgr::Hpre::DIV_1;
        io::RCC.CFGR.b.PPRE = io::Rcc::Cfgr::Ppre::DIV_1;

        // Enable clock for peripherals
        io::RCC.AHBENR.b.GPIOA = true;
        io::RCC.AHBENR.b.GPIOB = true;
        io::RCC.APB2ENR.b.USART1 = true;
        io::RCC.AHBENR.b.DMA1 = true;
        io::RCC.APB2ENR.b.ADC = true;
        io::RCC.APB1ENR.b.I2C1 = true;
    }
};

extern Clock clock;

}
