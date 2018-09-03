#pragma once

#include <stdlib.h>

#include "io/reg/cortexm/nvic.hpp"
#include "io/reg/stm32/f0/isr.hpp"
#include "io/reg/stm32/f0/i2c.hpp"
#include "io/reg/stm32/f0/dma.hpp"
#include "board/gpio.hpp"

namespace board {

class I2c {
private:
    static const unsigned DMA_CH_I2C_TX = 2;
    io::I2c &r_i2c = io::I2C(io::base::I2C1);
    io::Dma &r_dma = io::DMA(io::base::DMA1);
    io::Dma::Channel &r_dma_i2c_tx = r_dma.CHANNEL(DMA_CH_I2C_TX);

    GpioPin<io::base::GPIOA, 9> scl;
    GpioPin<io::base::GPIOA, 10> sda;

    static const size_t BLOCK_SIZE = 255;

    size_t data_len = 0;

    volatile bool busy = false;

public:
    void init_hw() {
        // GPIO
        sda.configure_af(4).configure_otype(gpio::Otype::OPEN_DRAIN).configure_pull(gpio::Pull::PULL_UP);
        scl.configure_af(4).configure_otype(gpio::Otype::OPEN_DRAIN).configure_pull(gpio::Pull::PULL_UP);

        // I2C
        r_i2c.TIMINGR.b.PRESC = 0;
        r_i2c.TIMINGR.b.SCLL = 9;
        r_i2c.TIMINGR.b.SCLH = 3;
        r_i2c.TIMINGR.b.SDADEL = 1;
        r_i2c.TIMINGR.b.SCLDEL = 3;
        r_i2c.CR1.r = 0;
        r_i2c.CR1.b.TCIE = true;
        r_i2c.CR1.b.STOPIE = true;
        r_i2c.CR1.b.TXDMAEN = true;
        r_i2c.CR1.b.PE = true;

        // enable interrupt
        io::NVIC.iser(io::isr::I2C1_isr);
    }

    bool write(const uint8_t addr, const uint8_t *data, size_t len) {
        if (busy) return false;
        busy = true;

        data_len = len;
        r_dma.IFCR.clear_flags(DMA_CH_I2C_TX);
        r_dma_i2c_tx.CCR.r = 0x00000000;
        r_dma_i2c_tx.CMAR.MAR = reinterpret_cast<const uint32_t>(data);
        r_dma_i2c_tx.CPAR.PAR = reinterpret_cast<const uint32_t>(&r_i2c.TXDR.TXDATA);
        r_dma_i2c_tx.CNDTR.NDT = data_len;
        io::Dma::Channel::Ccr dma_i2c_tx_ccr(0x00000000);
        dma_i2c_tx_ccr.b.EN = true;
        dma_i2c_tx_ccr.b.DIR = true;
        dma_i2c_tx_ccr.b.MINC = true;
        dma_i2c_tx_ccr.b.PSIZE = static_cast<uint32_t>(io::Dma::Channel::Ccr::Size::SIZE_8);
        dma_i2c_tx_ccr.b.MSIZE = static_cast<uint32_t>(io::Dma::Channel::Ccr::Size::SIZE_8);
        dma_i2c_tx_ccr.b.PL = static_cast<uint32_t>(io::Dma::Channel::Ccr::Pl::LOW);
        r_dma_i2c_tx.CCR.r = dma_i2c_tx_ccr.r;

        size_t block_len = (data_len > BLOCK_SIZE) ? BLOCK_SIZE : data_len;
        data_len -= block_len;

        io::I2c::Cr2 cr2(0);
        cr2.b.SADD = 0x03ff & (addr << 1);
        cr2.b.NBYTES = 0xff & block_len;
        cr2.b.RELOAD = data_len > 0;
        cr2.b.AUTOEND = data_len == 0;
        r_i2c.CR2.r = cr2.r;
        r_i2c.CR2.b.START = true;

        return true;
    }

    void handler() {
        if (data_len > 0 && r_i2c.ISR.b.TCR) {
            size_t block_len = (data_len > BLOCK_SIZE) ? BLOCK_SIZE : data_len;
            data_len -= block_len;
            io::I2c::Cr2 cr2(r_i2c.CR2.r);
            cr2.b.NBYTES = 0xff & block_len;
            cr2.b.RELOAD = data_len > 0;
            cr2.b.AUTOEND = data_len == 0;
            r_i2c.CR2.r = cr2.r;
        }
        if (r_i2c.ISR.b.STOPF) {
            io::I2c::Icr icr(0);
            icr.b.STOPCF = true;
            r_i2c.ICR.r = icr.r;
            busy = false;
        }
    }

    bool is_busy() {
        return busy;
    }
};

extern I2c i2c;

}
