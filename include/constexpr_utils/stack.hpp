//
// Created by Hippolyte Barraud on 25/09/2017.
//

#ifndef CELLPHONE_PASSWORD_STACK_HPP
#define CELLPHONE_PASSWORD_STACK_HPP

#include <array>
#include "utils.hpp"

namespace hippobaro {
    template <typename T, int Size>
    class stack {
    private:
        std::array<T *, Size> _array;

    public:

        constexpr stack() {
            hippobaro::fill(_array, nullptr);
        }

        constexpr void push(T * const value) {
            for (auto && node : _array) {
                if (node == nullptr) {
                    node = value;
                    return;
                }
            }
        }

        constexpr auto peek() -> T * const {
            if (length() == 0)
                return nullptr;
            return  _array[length() - 1];
        }

        constexpr auto pop() -> T * const {
            auto ret = peek();
            _array[length() - 1] = nullptr;
            return ret;
        }

        constexpr inline auto length() {
            return hippobaro::length(_array);
        }

        constexpr inline auto reset() {
            hippobaro::fill(_array, nullptr);
        }

        constexpr auto contains(T *const target) -> int {
            for (int j = 0; j < length(); ++j) {
                if (_array[j] == target)
                    return (int)length() - j;
            }
            return -1;
        }

        constexpr auto any_of(std::function<bool(T *const)> predicate) -> int {
            for (size_t j = 0; j < length(); ++j) {
                if (predicate(_array[j]))
                    return (int)(length() - j);
            }
            return -1;
        }

        constexpr T * const & operator[](size_t n) const {return _array[n];}
    };
}

#endif //CELLPHONE_PASSWORD_STACK_HPP
