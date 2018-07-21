#pragma once

#include <stdlib.h>
#include "board/flash.hpp"

namespace lib {

class Nv {

    struct Header {
        uint16_t key : 12;
        uint16_t size : 3;
        uint16_t val : 1;
    };

    const Header &_to_head(const volatile uint16_t *val) {
        union {
            const volatile uint16_t *raw;
            const Header *header;
        };
        raw = val;
        return *header;
    }

    uint16_t _from_head(const uint16_t key, const uint8_t size, const bool val) {
        union {
            Header header;
            uint16_t raw;
        };
        header.key = key;
        header.size = size;
        header.val = val;
        return raw;
    }

    // uint16_t database[board::Flash::BLOCK_SIZE / 2];
    static const volatile uint16_t _nv[board::Flash::BLOCK_SIZE / sizeof(uint16_t)];
    const volatile uint16_t *_last_data = nullptr;

    const volatile uint16_t *_find_key(const uint16_t key, const uint16_t size=0) {
        const volatile uint16_t *header_last = nullptr;
        const volatile uint16_t *nv = _nv;
        while (*nv != board::Flash::ERASED_DATA) {
            const Header &header = _to_head(nv);
            if ((header.key == key) && (header.size == size)) {
                header_last = nv;
            }
            nv += header.size + 1;
        }
        return header_last;
    }

    void _add_data(const uint16_t key, const bool val, const uint16_t *data=nullptr, uint16_t size=0) {
        uint16_t header = _from_head(key, size, val);
        board::Flash::flash_write16(_last_data++, header);
        while (size--) {
            board::Flash::flash_write16(_last_data++, *data++);
        }
    }

public:

    Nv() {
        _last_data = _nv;
        while (*_last_data != board::Flash::ERASED_DATA) {
            _last_data++;
        }
    }

    bool load_bool(const uint16_t key, const bool devault_val=false) {
        const volatile uint16_t *header = _find_key(key);
        if (header == nullptr) return devault_val;
        return _to_head(header).val;
    }

    void save_bool(const uint16_t key, const bool val) {
        const volatile uint16_t *header = _find_key(key);
        if (header != nullptr && _to_head(header).val == val) return;
        _add_data(key, val);
    }

    void erase() {
        board::Flash::flash_erase_block(_nv);
        _last_data = _nv;
    }

    size_t free() {
        return (board::Flash::BLOCK_SIZE / sizeof(uint16_t)) - (_last_data - _nv);
    }

    // void save_16(const uint16_t key, const uint16_t val) {
    //     const uint16_t *header = _find_key(key, 1);
    //     if (header != nullptr && _to_head(header).val == val) return;
    //     _add_data(key, val);
    // }

    // uint16_t load_16(const uint16_t key, const uint16_t default=0) {

    // }

    // void save_32(uint16_t key, uint32_t val) {

    // }

    // uint16_t load_32(uint16_t key, uint32_t default=0) {

    // }

    // void save_64(uint16_t key, uint64_t val) {

    // }

    // uint16_t load_64(uint16_t key, uint64_t default=0) {

    // }

};

}
