#pragma once

#include "io/reg/stm32/f0/usart.hpp"
#include "lib/iofile.hpp"
#include "lib/fifo.hpp"

/** USART driver
*/

namespace board {

template <size_t UART_BASE, int FIFO_IN_SIZE=0, int FIFO_OUT_SIZE=0>
class Usart : public lib::IOFile {

    io::Usart &r_usart = io::USART(UART_BASE);

    lib::Fifo<char, FIFO_IN_SIZE> fifo_in;
    lib::Fifo<char, FIFO_OUT_SIZE> fifo_out;

public:
    ~Usart() {
        close();
    }

    Usart &set_baud_rate(int baud_rate, int base_frequency) {
        // BRR (only for OVER16)
        r_usart.BRR.r = base_frequency / baud_rate;
        return *this;
    }

    Usart &enable_rx(bool en=true) {
        r_usart.CR1.b.RE = en;
        r_usart.CR1.b.RXNEIE = en && FIFO_IN_SIZE;
        return *this;
    }

    Usart &enable_tx(bool en=true) {
        r_usart.CR1.b.TE = en;
        return *this;
    }

    Usart &enable(bool en=true) {
        r_usart.CR1.b.UE = en;
        return *this;
    }

    void write_char(char data) override {
        if (FIFO_OUT_SIZE) {
            while (fifo_out.is_full());
            r_usart.CR1.b.TXEIE = false;
            if (fifo_out.has_data() || !r_usart.ISR.b.TXE) {
                fifo_out.push(data);
                r_usart.CR1.b.TXEIE = true;
                return;
            }
        } else {
            while (!r_usart.ISR.b.TXE);
        }
        r_usart.TDR.DR = data;
    }

    int read_char() {
        if (FIFO_IN_SIZE) {
            char data;
            if (fifo_in.pull(data)) return data;
        } else if (r_usart.ISR.b.RXNE) return r_usart.RDR.DR;
        return -1;
    }

    int read_data(char *, int) {
        return 0;
    }

    void handler() {
        if (r_usart.ISR.b.RXNE) {
            char data = r_usart.RDR.DR;
            if (FIFO_IN_SIZE) {
                fifo_in.push(data);
            }
        }
        if (r_usart.ISR.b.TXE) {
            if (FIFO_OUT_SIZE) {
                char data;
                if (fifo_out.pull(data)) r_usart.TDR.DR = data;
                if (fifo_out.is_empty()) {
                    r_usart.CR1.b.TXEIE = false;
                }
            } else {
                r_usart.CR1.b.TXEIE = false;
            }
        }
    }

    void close() {
        r_usart.CR1.r = 0;
        r_usart.CR2.r = 0;
        r_usart.CR3.r = 0;
        r_usart.BRR.r = 0;
        if (FIFO_OUT_SIZE) fifo_out.reset();
        if (FIFO_IN_SIZE) fifo_in.reset();
    }

};

}
