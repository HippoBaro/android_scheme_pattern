//
// Created by Hippolyte Barraud on 23/09/2017.
//

#ifndef CELLPHONE_PASSWORD_UTILS_HPP
#define CELLPHONE_PASSWORD_UTILS_HPP

#ifdef NDEBUG
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
        for (int i = 0; i < len; ++i) {
            array[i] = value;
        }
    }

    template<typename T, size_t len>
    inline constexpr auto fill(std::array<T, len> & array, std::nullptr_t) {
        for (int i = 0; i < len; ++i) {
            array[i] = nullptr;
        }
    }

    template<typename T, size_t len>
    inline constexpr auto lengh(std::array<T *, len> & array) {
        int i = 0;
        for (; i < 9; ++i) {
            if (array[i] == nullptr)
                break;
        }
        return i;
    }
}

#endif //CELLPHONE_PASSWORD_UTILS_HPP
