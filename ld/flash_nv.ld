SECTIONS {
    .text_nv (NOLOAD) : {
        __nv_start = .;
        *(.nv)
        __nv_end = .;
    } >FLASH_NV
}
