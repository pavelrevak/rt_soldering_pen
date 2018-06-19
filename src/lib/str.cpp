#include "str.hpp"

namespace lib {

char *Str::u2a(unsigned number, unsigned digits_count, const unsigned base, const bool uc, const char precedense, char *buffer) {
    unsigned modulo = 1;
    while ((number / modulo) >= base) {
        modulo *= base;
        digits_count--;
    }
    while (digits_count-- > 1) {
        *buffer++ = precedense;
    }
    while (modulo) {
        int digit = number / modulo;
        number %= modulo;
        modulo /= base;
        *buffer++ = digit + ((digit < 10) ? '0' : (uc ? 'A' : 'a') - 10);
    }
    *buffer = 0;
    return buffer;
}

char *Str::i2a(int number, unsigned digits_count, const char precedense, char *buffer) {
    if (number < 0) {
        number = -number;
        *buffer++ = '-';
        digits_count--;
    }
    return u2a(number, digits_count, 10, false, precedense, buffer);
}

char *Str::d2a(int number, unsigned digits_count, unsigned decimals_count, unsigned precedense, char *buffer) {
    if (number < 0) {
        number =- number;
        *buffer++ = '-';
        digits_count--;
    }
    int modulo = 1;
    for (unsigned i = 0; i < decimals_count; i++) {
        modulo *= 10;
    }
    buffer = u2a(number / modulo, digits_count, 10, false, precedense, buffer);
    *buffer++ = '.';
    return u2a(number % modulo, decimals_count, 10, false, '0', buffer);
}

}
