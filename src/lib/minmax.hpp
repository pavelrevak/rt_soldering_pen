#pragma once

namespace lib {

template <typename T>
T minmax(const T val, const T min, const T max) {
    if (val < min) return min;
    if (val > max) return max;
    return val;
}

template <typename T>
void minmax(T *val, const T min, const T max) {
    if (*val < min) {
        *val = min;
    } else if (*val > max) {
        *val = max;
    }
}

template <typename T>
bool interval(const T val, const T min, const T max) {
    if (val < min) return false;
    if (val > max) return false;
    return true;
}

}
