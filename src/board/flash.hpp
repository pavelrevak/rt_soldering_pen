#pragma once

#include "io/reg/stm32/f0/flash.hpp"

extern uint8_t _settings_start;
extern uint8_t _settings_end;

extern unsigned __flash_block_size;

namespace board {

class Flash {

public:

    static const uint16_t ERASED_DATA = 0xffff;
    static const size_t BLOCK_SIZE = 1024;

    static void flash_unlock() {
        if (io::FLASH.CR.b.LOCK) {
            // unlock FLASH
            io::FLASH.KEYR = 0x45670123;
            io::FLASH.KEYR = 0xcdef89ab;
            while (io::FLASH.CR.b.LOCK);
        }
    }

    static void flash_erase_block(const volatile void *dst) {
        flash_unlock();
        // erase block at address
        io::FLASH.CR.b.PER = true;
        io::FLASH.AR = reinterpret_cast<uint32_t>(dst);
        io::FLASH.CR.b.STRT = true;
        // wait until page is erased
        while (io::FLASH.SR.b.BSY);
        io::FLASH.CR.b.PER = false;
    }

    static bool flash_write16(const volatile uint16_t *dst, uint16_t data) {
        flash_unlock();
        // enable programming
        io::FLASH.CR.b.PG = true;
        volatile uint16_t *destination = const_cast<volatile uint16_t *>(dst);
        *destination++ = data;
        // wait until half-word is flashed
        while (io::FLASH.SR.b.BSY);
        // check for errors
        if (io::FLASH.SR.b.PGERR || io::FLASH.SR.b.WRPRTERR) return true;
        // EOP should be set, erase flag
        if (io::FLASH.SR.b.EOP) {
            io::FLASH.SR.b.EOP = true;
        }
        // disable programming
        io::FLASH.CR.b.PG = false;
        return true;
    }
};

}
