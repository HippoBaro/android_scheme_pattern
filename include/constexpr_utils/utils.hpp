//
// Created by Hippolyte Barraud on 23/09/2017.
//

#ifndef CELLPHONE_PASSWORD_UTILS_HPP
#define CELLPHONE_PASSWORD_UTILS_HPP

#include <array>

namespace hippobaro {

    //std::abs if not constexpr for some obscure reason
    template<typename T>
    constexpr int abs(T value) {
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

    template<typename T, unsigned long len>
    constexpr std::array<T, len>& operator+=(std::array<T, len>& thi, const std::array<T, len>& oth) {
        for (size_t i = 0; i < len; ++i)
            thi.at(i) += oth.at(i);
        return thi;
    }

    template<typename T, unsigned long len>
    constexpr std::array<T, len> operator+(const std::array<T, len>& a, const std::array<T, len>& b) {
        std::array<T, len> sum = a;
        sum += b;
        return sum;
    }

    template<typename T, size_t len>
    inline constexpr auto length(std::array<T *, len> const& array) {
        size_t i = 0;
        for (; i < len; ++i) {
            if (array[i] == nullptr)
                break;
        }
        return i;
    }
}

#endif //CELLPHONE_PASSWORD_UTILS_HPP
