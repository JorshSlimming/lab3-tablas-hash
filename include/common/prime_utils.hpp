#pragma once

#include <cstddef>

namespace lab3 {

inline bool is_prime(std::size_t value) {
    if (value < 2) {
        return false;
    }
    if (value == 2) {
        return true;
    }
    if (value % 2 == 0) {
        return false;
    }

    for (std::size_t divisor = 3; divisor * divisor <= value; divisor += 2) {
        if (value % divisor == 0) {
            return false;
        }
    }
    return true;
}

inline std::size_t next_prime(std::size_t value) {
    if (value <= 2) {
        return 2;
    }
    if (value % 2 == 0) {
        ++value;
    }
    while (!is_prime(value)) {
        value += 2;
    }
    return value;
}

}  // namespace lab3
