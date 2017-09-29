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
        size_t _index;

    public:

        constexpr stack() : _array(), _index(0) {
            hippobaro::fill(_array, nullptr);
        }

        constexpr void push(T * const value) {
           _array[_index++] = value;
        }

        constexpr auto peek() -> T * const {
            if (length() == 0)
                return nullptr;
            return  _array[length() - 1];
        }

        constexpr auto pop() -> T * const {
            auto ret = peek();
            _array[--_index] = nullptr;
            return ret;
        }

        constexpr inline auto length() const {
            return _index;
        }

        constexpr auto contains(T *const target) const {
            for (size_t j = 0; j < length(); ++j) {
                if (!_array[j])
                    continue;
                if (*(_array[j]) == *target)
                    return true;
            }
            return false;
        }

        constexpr T * const & operator[](size_t n) const {return _array[n];}
    };
}

#endif //CELLPHONE_PASSWORD_STACK_HPP
