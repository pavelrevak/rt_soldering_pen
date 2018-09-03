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
    IFile *file_in = nullptr;

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
    OFile *file_out = nullptr;

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

    Return:
        reference to instance of this stream
    */
    OStream &c(char ch) {
        file_out->write_char(ch);
        return *this;
    }

    /** Print character into stream and change line-end to windows style

    Arguments:
        ch: character

    Return:
        reference to instance of this stream
    */
    OStream &a(char ch) {
        if (ch == '\n') c('\r');
        return c(ch);
    }

    /** Print data bytes into stream

    Arguments:
        data: data bytes
        count: number of bytes

    Return:
        reference to instance of this stream
    */
    OStream &d(const char *data, int count=1) {
        file_out->write_data(data, count);
        return *this;
    }

    /** Print string into stream

    Arguments:
        data: string

    Return:
        reference to instance of this stream
    */
    OStream &s(const char *data) {
        while (*data != 0) c(*data++);
        return *this;
    }

    /** Print hexadecimal number into stream

    Arguments:
        x: number to convert into hexadecimal number
        count: number of characters

    Return:
        reference to instance of this stream

    */
    template<class T>
    OStream &hex(T x, int count) {
        while (count-- > 0) {
            char digit = (x >> (count << 2)) & 0x0f;
            c(static_cast<char>((digit < 10) ? '0' + digit : 'a' - 10 + digit));
        }
        return *this;
    }

    /** Print 8-bit hexadecimal number into stream

    Arguments:
        x: number to convert into hexadecimal number
        count: number of characters

    Return:
        reference to instance of this stream
    */
    OStream &h(uint8_t x, int count=2) {
        return hex(x, count);
    }

    /** Print 16-bit hexadecimal number into stream

    Arguments:
        x: number to convert into hexadecimal number
        count: number of characters

    Return:
        reference to instance of this stream
    */
    OStream &h(uint16_t x, int count=4) {
        return hex(x, count);
    }

    /** Print 32-bit hexadecimal number into stream

    Arguments:
        x: number to convert into hexadecimal number
        count: number of characters

    Return:
        reference to instance of this stream
    */
    OStream &h(uint32_t x, int count=8) {
        return hex(x, count);
    }

    /** Print 64-bit hexadecimal number into stream

    Arguments:
        x: number to convert into hexadecimal number
        count: number of characters

    Return:
        reference to instance of this stream
    */
    OStream &h(uint64_t x, int count=16) {
        return hex(x, count);
    }

    /** Print address as hexadecimal number into stream

    Arguments:
        x: number to convert into hexadecimal number

    Return:
        reference to instance of this stream
    */
    OStream &h(size_t x) {
        return hex(x, sizeof(size_t) * 2);
    }

    /** Print unsigned number into stream

    Arguments:
        x: number to print into stream
        count: number of digits
        pre: precedence character

    Return:
        reference to instance of this stream
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
            char digit = static_cast<char>(x / modulo);
            x %= modulo;
            modulo /= 10;
            c(static_cast<char>(digit + '0'));
        }
        return *this;
    }

    /** Print signed number into stream

    Arguments:
        x: number to print into stream
        count: number of digits
        pre: precedence character
        neg: force negative sign

    Return:
        reference to instance of this stream
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
            char digit = static_cast<char>(x / modulo);
            x %= modulo;
            modulo /= 10;
            c(static_cast<char>(digit + '0'));
        }
        return *this;
    }

    /** Print decimal number into stream

    Arguments:
        x: number to print into stream
        count: number of digits before decimal point
        dp: number of digits after decimal point
        pre: precedence character

    Return:
        reference to instance of this stream
    */
    template<class T>
    OStream &dec(T x, int count=1, int dp=0, const char pre='0') {
        bool neg = x < 0;
        if (neg) {
            x = -x;
        }
        T modulo = 1;
        for (int j = 0; j < dp; j++) {
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

    Return:
        reference to instance of this stream
    */
    OStream &operator<<(char ch) {
        return c(ch);
    }

    /** Stream operator to print string

    Return:
        reference to instance of this stream
    */
    OStream &operator<<(const char *data) {
        return s(data);
    }

    /** Stream operator to print unsigned number

    Return:
        reference to instance of this stream
    */
    OStream &operator<<(unsigned x) {
        return u(x);
    }

    /** Stream operator to print unsigned long long number

    Return:
        reference to instance of this stream
    */
    OStream &operator<<(unsigned long long x) {
        return u(x);
    }

    /** Stream operator to print signed long long number

    Return:
        reference to instance of this stream
    */
    OStream &operator<<(int x) {
        return i(x);
    }

    /** Stream operator to print signed long long number

    Return:
        reference to instance of this stream
    */
    OStream &operator<<(long long x) {
        return i(x);
    }

    /** Stream operator boolean value

    Return:
        reference to instance of this stream
    */
    OStream &operator<<(bool x) {
        return a(x ? '1' : '0');
    }

    /** stream operator to print hexadecimal pointer address
    (nonstandard feature, used for debug)

    Return:
        reference to instance of this stream
    */
    OStream &operator<<(void *x) {
        return h(reinterpret_cast<size_t>(x));
    }

};

/** Input and output stream class
*/
struct IOStream : public IStream, public OStream {
    static const char endl = '\n';
    static const char cr = '\r';

};

}
