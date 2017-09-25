//
// Created by Hippolyte Barraud on 21/09/2017.
//

#ifndef CELLPHONE_PASSWORD_PASSWORD_SPACE_HPP
#define CELLPHONE_PASSWORD_PASSWORD_SPACE_HPP

#include <cstdint>
#include "password_node.hpp"

namespace hippobaro::password_cellphone {
    template<int Collumns, int Rows>
    class password_space {
    private:
        std::array<password_node<Collumns, Rows>, Collumns * Rows> _nodes;

    public:
        constexpr password_space() : _nodes() {

            auto abs = 0;
            for (int c = 0; c < Collumns; ++c) {
                for (int r = 0; r < Rows; ++r) {

                    _nodes[abs].coordinates.first = r;
                    _nodes[abs].coordinates.second = c;
                    _nodes[abs].nodes = &_nodes;
                    _nodes[abs].index = abs+1;

                    ++abs;
                }
            }
        }

        constexpr auto resolve() {
            hippobaro::stack<password_node<Collumns, Rows>, Collumns * Rows> path;
            auto ret = 0;
            for (auto &&node : _nodes) {
                ret += node.traverse(path);
                hippobaro::fill(node.visited, false);
                path.reset();
            }
            return ret;
        }
    };
}

#endif //CELLPHONE_PASSWORD_PASSWORD_SPACE_HPP
