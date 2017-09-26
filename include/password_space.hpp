//
// Created by Hippolyte Barraud on 21/09/2017.
//

#ifndef CELLPHONE_PASSWORD_PASSWORD_SPACE_HPP
#define CELLPHONE_PASSWORD_PASSWORD_SPACE_HPP

#include <cstdint>
#include <future>
#include <vector>
#include <numeric>
#include "password_node.hpp"

namespace hippobaro::password_cellphone {
    template<int Columns, int Rows>
    class password_space {
    private:
        std::array<password_node<Columns, Rows>, Columns * Rows> _nodes;

    public:
        constexpr password_space() : _nodes() {

            auto abs = 0;
            for (int c = 0; c < Columns; ++c) {
                for (int r = 0; r < Rows; ++r) {

                    _nodes[abs].coordinates.first = r;
                    _nodes[abs].coordinates.second = c;
                    _nodes[abs].nodes = &_nodes;
                    _nodes[abs].index = abs;

                    ++abs;
                }
            }
        }

        OPTIONAL_CONSTEXPR auto resolve() -> std::array<uint64_t, Columns * Rows> {
#ifdef COMPILE_TIME_EVAL
            std::array<uint64_t, Columns * Rows> pathslen = {};
            for (auto &&node : _nodes) {
                hippobaro::stack<typename password_node<Columns, Rows>::path_node, Columns * Rows> path;
                pathslen += node.traverse(path);
            }
#else
            std::array<uint64_t, Columns * Rows> pathslen = {};
            std::vector<std::unique_ptr<std::thread>> threads;
            for (auto &&node : _nodes) {
                threads.emplace_back(std::make_unique<std::thread>([&node, &pathslen] {
                    hippobaro::stack<typename password_node<Columns, Rows>::path_node, Columns * Rows> path;
                    pathslen += node.traverse(path);
                }));
            }
            for(auto &&thread : threads) {
                thread->join();
            };
#endif
            return pathslen;
        }
    };
}

#endif //CELLPHONE_PASSWORD_PASSWORD_SPACE_HPP
