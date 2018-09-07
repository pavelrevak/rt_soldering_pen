#pragma once

#include <cstdint>
#include "io/reg/cortexm/systick.hpp"

/**
 * Systick driver
 * configure systick to count tick of main oscillator
 */
namespace board {

class Systick {
    volatile uint32_t tick_counter = 0;

public:
    static const unsigned int DIV_BITS = 24;

    void init_hw() {
        io::SYSTICK.CSR.r = 0;
        io::SYSTICK.LOAD.RELOAD = (1 << DIV_BITS) - 1;
        io::SYSTICK.VAL.CURRENT = 0;
        io::Systick::Csr csr;
        csr.r = 0;
        csr.b.CLKSOURCE = static_cast<uint32_t>(io::Systick::Csr::Clksource::PROCESSOR);
        csr.b.ENABLE = true;
        csr.b.TICKINT = true;
        io::SYSTICK.CSR.r = csr.r;
    }

    /** Reentrant read of CPU ticks in 64bits
     * @return number of ticks from MCU start (64 bit number)
     */
    uint64_t get_ticks() const {
        uint64_t ticks;
        uint32_t minor;
        do {
            ticks = tick_counter;
            minor = io::SYSTICK.VAL.CURRENT;
        } while (ticks != tick_counter);
        ticks += 1;
        ticks <<= DIV_BITS;
        ticks -= minor;
        return ticks;
    }

    /** Read of CPU ticks with width of DIV_BITS
     * THIS COUNTER IS COUNTDOWN
     * @return number of ticks from MCU start trimmed by DIV_BITS (24 bits)
     */
    inline uint32_t get_counter() const {
        return io::SYSTICK.VAL.CURRENT;
    }

    /**
     * Interrupt handler
     * need to call manually from interrupt handler routine
     */
    inline void handler() {
        tick_counter++;
    }

    static Systick &get_instance() {
        static Systick instance;
        return instance;
    }

};

}
