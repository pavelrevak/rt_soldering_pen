#pragma once

class Str {
public:
    static char *u2a(unsigned number, unsigned digits_count, const unsigned base, const bool uc, const char precedense, char *buffer);
    static char *i2a(int number, unsigned digits_count, const char precedense, char *buffer);
    static char *d2a(int number, unsigned digits_count, unsigned decimals_count, unsigned precedense, char *buffer);
};
