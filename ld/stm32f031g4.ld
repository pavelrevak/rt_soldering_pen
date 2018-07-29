MEMORY {
    FLASH(rx) : ORIGIN = 0x08000000, LENGTH = 15K
    FLASH_NV(rx) : ORIGIN = 0x08000000 + 15K, LENGTH = 1K
    SRAM(rwx) : ORIGIN = 0x20000000, LENGTH = 4K
}

INCLUDE "io/ld/_common/flash.ld"
INCLUDE "io/ld/_common/sram.ld"
INCLUDE "ld/flash_nv.ld"

__flash_block_size = 1K;
