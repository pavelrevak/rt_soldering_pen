#pragma once

#include <cstdint>
#include <cstddef>

#include "iofile.hpp"

class IStream {
protected:
    IFile *file_in = NULL;

public:
    // static IStream cin;

    IStream() {}

    IStream(IFile &file) {
        file_in = &file;
    }

    void set_file_in(IFile &file) {
        file_in = &file;
    }
};

class OStream {
protected:
    OFile *file_out = NULL;

public:
    // static OStream cout;
    // static OStream cerr;
    // static OStream clog;

    OStream() {}

    OStream(OFile &file) {
        file_out = &file;
    }

    void set_file_out(OFile &file) {
        file_out = &file;
    }

    OStream &a(char ch) {
        file_out->write_char(ch);
        return *this;
    }
    OStream &c(char ch) {
        if (ch == '\n') file_out->write_char('\r');
        file_out->write_char(ch);
        return *this;
    }
    OStream &d(const char *data, int count=1) {
        file_out->write_data(data, count);
        return *this;
    }
    OStream &s(const char *data) {
        while (*data != 0) (*this) << *data++;
        return *this;
    }
    OStream &h(unsigned int x, int count=2) {
        if (--count > 0) h(x >> 4, count);
        x &= 0xf;
        file_out->write_char((x < 10) ? '0' + x : 'a' - 10 + x);
        return *this;
    }
    OStream &u(unsigned int x, int count=1) {
        if (--count > 0 || x >= 10) u(x / 10, count);
        x %= 10;
        file_out->write_char('0' + x);
        return *this;
    }
    OStream &i(int x, int count=1) {
        if (x < 0) {
            x = -x;
            count--;
            file_out->write_char('-');
        }
        return u(x, count);
    }
    OStream &ull(unsigned long long x, int count=1) {
        if (--count > 0 || x >= 10) u(x / 10, count);
        x %= 10;
        file_out->write_char('0' + x);
        return *this;
    }
    OStream &ll(long long x, int count=1) {
        if (x < 0) {
            x = -x;
            count--;
            file_out->write_char('-');
        }
        return u(x, count);
    }
    OStream &f(double x, int count=1, int precision=3) {
        if (x < 0) {
            x = -x;
            count--;
            file_out->write_char('-');
        }
        u(x, count);
        file_out->write_char('.');
        while (precision--) {
            x *= 10;
            int c = x;
            c %= 10;
            file_out->write_char('0' + c);
        }
        return *this;
    }
    inline OStream &operator<<(char ch) {
        return c(ch);
    }
    inline OStream &operator<<(const char *data) {
        return s(data);
    }
    inline OStream &operator<<(unsigned int x) {
        return u(x);
    }
    inline OStream &operator<<(int x) {
        return i(x);
    }
    inline OStream &operator<<(double x) {
        return f(x);
    }
    inline OStream &operator<<(float x) {
        return f(x);
    }
    inline OStream &operator<<(bool x) {
        return u(x);
    }
    inline OStream &operator<<(unsigned long long x) {
        return ll(x);
    }
    inline OStream &operator<<(long long x) {
        return ull(x);
    }
    inline OStream &operator<<(void *x) {
        return h((unsigned int)x, 2 * sizeof(void *));
    }
    // inline OStream &operator<<(OStream &(*f)(OStream &)) {
    //     return (*f)(*this);
    // }
};

struct IOStream : public IStream, public OStream {
    static const char endl = '\n';
    static const char cr = '\r';
};
