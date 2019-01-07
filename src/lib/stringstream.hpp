#pragma once

#include <cstdint>
#include "lib/iostream.hpp"

namespace lib {

template<size_t SIZE>
class StringFile : public lib::OFile {
    char _buffer[SIZE] = {0};
    char *_ptr = _buffer;
    size_t _size = SIZE;

public:
    void write_char(char data) override {
        if (_size > 0) {
            _size--;
            *_ptr++ = data;
            *_ptr = 0;
        }
    }

    void write_data(const char *data, int len) override {
        while (len > 0 && _size >= 1) {
            len--;
            _size--;
            *_ptr++ = *data++;
        }
        *_ptr = 0;
    }

    void reset() {
        _ptr = _buffer;
        _size = SIZE;
        *_ptr = 0;
    }

    char *get_str() {
        return _buffer;
    }
};

template<size_t SIZE>
class StringStream : public OStream {
    StringFile<SIZE> str_file;

public:
    StringStream() : OStream(str_file) {}

    StringStream &reset() {
        str_file.reset();
        return *this;
    }

    char *get_str() {
        return str_file.get_str();
    }

};

}
