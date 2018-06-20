#pragma once

#include <cstdint>
#include <cstddef>

#include "iofile.hpp"

namespace lib {

/** Input stream
(not implemented)
*/
class IStream {
protected:
    IFile *file_in = NULL;

public:
    IStream() {}

    IStream(IFile &file) {
        file_in = &file;
    }

    /** Set input file

    Arguments:
        file: input file to set as this input stream
    */
    void set_file_in(IFile &file) {
        file_in = &file;
    }
};


/** Output stream
*/
class OStream {
protected:
    OFile *file_out = NULL;

public:
    OStream() {}

    OStream(OFile &file) {
        file_out = &file;
    }

    /** Set output file

    Arguments:
        file: output file to set as this output stream
    */
    void set_file_out(OFile &file) {
        file_out = &file;
    }

    /** Print character into stream

    Arguments:
        ch: character
    */
    OStream &c(char ch) {
        file_out->write_char(ch);
        return *this;
    }

    /** Print character into stream and change line-end to windows style

    Arguments:
        ch: character
    */
    OStream &a(char ch) {
        if (ch == '\n') c('\r');
        return c(ch);
    }

    /** Print data bytes into stream

    Arguments:
        data: data bytes
        count: number of bytes
    */
    OStream &d(const char *data, int count=1) {
        file_out->write_data(data, count);
        return *this;
    }

    /** Print string into stream

    Arguments:
        data: string
    */
    OStream &s(const char *data) {
        while (*data != 0) c(*data++);
        return *this;
    }

    /** Print hexadecimal number into stream

    Arguments:
        x: number to convert into hexadecimal number
        count: number of characters
    */
    template<class T>
    OStream &hex(T x, int count) {
        // TODO remove recursive calling
        if (--count > 0) hex(x >> 4, count);
        x &= 0xf;
        return c((x < 10) ? '0' + x : 'a' - 10 + x);
    }

    /** Print 8-bit hexadecimal number into stream

    Arguments:
        x: number to convert into hexadecimal number
        count: number of characters
    */
    OStream &h(uint8_t x, int count=2) {
        return hex(x, count);
    }

    /** Print 16-bit hexadecimal number into stream

    Arguments:
        x: number to convert into hexadecimal number
        count: number of characters
    */
    OStream &h(uint16_t x, int count=4) {
        return hex(x, count);
    }

    /** Print 32-bit hexadecimal number into stream

    Arguments:
        x: number to convert into hexadecimal number
        count: number of characters
    */
    OStream &h(uint32_t x, int count=8) {
        return hex(x, count);
    }

    /** Print 64-bit hexadecimal number into stream

    Arguments:
        x: number to convert into hexadecimal number
        count: number of characters
    */
    OStream &h(uint64_t x, int count=16) {
        return hex(x, count);
    }

    /** Print unsigned number into stream

    Arguments:
        x: number to print into stream
        count: number of digits
        pre: precedence character
    */
    template<class T>
    OStream &u(T x, int count=1, const char pre='0') {
        T modulo = 1;
        while ((x / modulo) >= 10) {
            modulo *= 10;
            count--;
        }
        while (count > 1) {
            c(pre);
            count--;
        }
        while (modulo) {
            char digit = x / modulo;
            x %= modulo;
            modulo /= 10;
            c(digit + '0');
        }
        return *this;
    }

    /** Print signed number into stream

    Arguments:
        x: number to print into stream
        count: number of digits
        pre: precedence character
        neg: force negative sign
    */
    template<class T>
    OStream &i(T x, int count=1, const char pre='0', bool neg=false) {
        if (x < 0) {
            neg = true;
            x = -x;
        }
        if (neg) {
            count--;
        }
        T modulo = 1;
        while ((x / modulo) >= 10) {
            modulo *= 10;
            count--;
        }
        if (neg && pre == '0') {
            c('-');
        }
        while (count > 1) {
            c(pre);
            count--;
        }
        if (neg && pre != '0') {
            c('-');
        }
        while (modulo) {
            char digit = x / modulo;
            x %= modulo;
            modulo /= 10;
            c(digit + '0');
        }
        return *this;
    }

    /** Print decimal number into stream

    Arguments:
        x: number to print into stream
        count: number of digits before decimal point
        dp: number of digits after decimal point
        pre: precedence character
    */
    template<class T>
    OStream &dec(T x, int count=1, int dp=0, const char pre='0') {
        bool neg = x < 0;
        if (neg) {
            x = -x;
        }
        T modulo = 1;
        for (int i = 0; i < dp; i++) {
            modulo *= 10;
        }
        i(x / modulo, count, pre, neg);
        if (dp) {
            c('.');
            u(x % modulo, dp);
        }
        return *this;
    }

    /** Stream operator to print character
    */
    OStream &operator<<(char ch) {
        return c(ch);
    }

    /** Stream operator to print string
    */
    OStream &operator<<(const char *data) {
        return s(data);
    }

    /** Stream operator to print unsigned number
    */
    OStream &operator<<(unsigned x) {
        return u(x);
    }

    /** Stream operator to print unsigned long long number
    */
    OStream &operator<<(unsigned long long x) {
        return u(x);
    }

    /** Stream operator to print signed long long number
    */
    OStream &operator<<(int x) {
        return i(x);
    }

    /** Stream operator to print signed long long number
    */
    OStream &operator<<(long long x) {
        return i(x);
    }

    /** Stream operator boolean value
    */
    OStream &operator<<(bool x) {
        return a(x ? '1' : '0');
    }

    /** stream operator to print hexadecimal pointer address
    (nonstandard feature, used for debug)
    */
    OStream &operator<<(void *x) {
        return h((uint32_t)x);
    }

    // OStream &operator<<(OStream &(*f)(OStream &)) {
    //     return (*f)(*this);
    // }
};

struct IOStream : public IStream, public OStream {
    static const char endl = '\n';
    static const char cr = '\r';
};

}
