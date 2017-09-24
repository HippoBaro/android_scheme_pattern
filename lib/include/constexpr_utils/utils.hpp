//
// Created by Hippolyte Barraud on 23/09/2017.
//

#ifndef CELLPHONE_PASSWORD_UTILS_HPP
#define CELLPHONE_PASSWORD_UTILS_HPP

#ifdef COMPILE_TIME_EVAL
#define OPTIONAL_CONSTEXPR constexpr
#else
#define OPTIONAL_CONSTEXPR
#endif

#include <array>

namespace hippobaro {

    constexpr int abs(int value) {
        if (value < 0)
            return value * -1;
        return value;
    }

    template<typename T, size_t len>
    inline constexpr auto fill(std::array<T, len> & array, T value) {
        for (size_t i = 0; i < len; ++i) {
            array[i] = value;
        }
    }

    template<typename T, size_t len>
    inline constexpr auto fill(std::array<T, len> & array, std::nullptr_t) {
        for (size_t i = 0; i < len; ++i) {
            array[i] = nullptr;
        }
    }

    template<typename T, size_t len>
    inline constexpr auto length(std::array<T *, len> & array) {
        size_t i = 0;
        for (; i < len; ++i) {
            if (array[i] == nullptr)
                break;
        }
        return i;
    }
}

#endif //CELLPHONE_PASSWORD_UTILS_HPP
