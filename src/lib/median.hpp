#pragma once

#include <stdlib.h>

namespace lib {

template <class T, int SIZE>
class Median {
    T sorted[SIZE];
    int values_count = 0;

    static int compare(const void *a, const void *b) {
        return *(T *)a - *(T *)b;
    }

public:
    bool add(const T val) {
        if (values_count >= SIZE) return false;
        sorted[values_count++] = val;
        return true;
    }

    T median() {
        qsort(sorted, SIZE, sizeof(T), compare);
        return sorted[SIZE / 2];
    }
};

}
