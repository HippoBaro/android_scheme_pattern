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

#ifdef COMPILE_TIME_EVAL
#define OPTIONAL_CONSTEXPR constexpr
#else
#define OPTIONAL_CONSTEXPR
#endif

namespace hippobaro::password_cellphone {
    template<int Columns, int Rows>
    class password_space {
    private:

        // To reduce the number of pointer jumps, we setup the nodes in a contiguous memory location.
        std::array<password_node<Columns, Rows>, Columns * Rows> _nodes;

    public:
        constexpr password_space() : _nodes() {

            auto abs = 0;
            for (int r = 0; r < Rows; ++r) {
                for (int c = 0; c < Columns; ++c) {
                    _nodes[abs].coordinates.first = c;
                    _nodes[abs].coordinates.second = r;
                    _nodes[abs].nodes = &_nodes;

                    ++abs;
                }
            }
        }

        constexpr auto resolve_dumb(password_node<Columns, Rows> const& node) const {
            hippobaro::stack<typename password_node<Columns, Rows>::path_node, Columns * Rows> path;
            return node.traverse(path);
        }

        constexpr auto resolve_symmetry(password_node<Columns, Rows> const& node) const {
            std::array<uint64_t, Columns * Rows> pathslen = {};
            if (node.coordinates.second < Rows / 2 + Rows % 2) {
                if (node.coordinates.first < Columns / 2 + Columns % 2) {
                    auto result = resolve_dumb(node);

                    // Horizontal symmetry
                    if (node.coordinates.first < (Columns / 2 + Columns % 2) - 1 || Columns % 2 == 0) {
                        for (auto &&item : result) {
                            item *= 2;
                        }
                    }

                    // Vertical symmetry
                    if (node.coordinates.second < (Rows / 2 + Rows % 2) - 1 || Rows % 2 == 0) {
                        for (auto &&item : result) {
                            item *= 2;
                        }
                    }
                    pathslen += result;
                }
            }
            return pathslen;
        }

        constexpr auto resolve_select_method(password_node<Columns, Rows> const &node) const
        {
#ifdef USE_SYMMETRY
            return resolve_symmetry(node);
#else
            return resolve_dumb(node);
#endif
        }

        OPTIONAL_CONSTEXPR auto resolve() const {
            std::array<uint64_t, Columns * Rows> pathslen = {};

#ifdef COMPILE_TIME_EVAL
            //If constexpr is enabled, we naively loop over each nodes and computes the results.
            for (auto &&node : _nodes) {
                 pathslen += resolve_select_method(node);
            }
#else
            //If we compute at runtime, then we can take advantages of multi-cores to speed-up the process.
            std::vector<std::unique_ptr<std::thread>> threads;
            std::mutex mutex;

            for (auto &&node : _nodes) {
                threads.emplace_back(std::make_unique<std::thread>([this, &node, &pathslen, &mutex] {
                    auto t = resolve_select_method(node);
                    {
                        std::lock_guard<std::mutex> lock(mutex);
                        pathslen += t;
                    }

                }));
            }
            for(auto &&thread : threads) {
                thread->join();
            };
#endif
            return pathslen;
        }
    };
};

#endif //CELLPHONE_PASSWORD_PASSWORD_SPACE_HPP