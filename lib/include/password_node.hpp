//
// Created by Hippolyte Barraud on 21/09/2017.
//

#ifndef CELLPHONE_PASSWORD_PASSWORD_NODE_HPP
#define CELLPHONE_PASSWORD_PASSWORD_NODE_HPP

#include <cstdint>
#include <array>
#include <constexpr_utils/utils.hpp>

namespace hippobaro::password_cellphone {

    template<int Collumns, int Rows>
    class password_node {

    public:
        std::array<password_node<Collumns, Rows>, Collumns * Rows> * nodes;
        std::array<bool, Collumns * Rows> visited;
        std::pair<int, int> coordinates;
        int index;

    public:

        OPTIONAL_CONSTEXPR password_node() : nodes(nullptr), visited(), coordinates(), index(-1) {}

        OPTIONAL_CONSTEXPR void add_to_path(std::array<password_node<Collumns, Rows> *, Collumns * Rows> & path) {
            for (auto && node : path) {
                if (node == nullptr) {
                    node = this;
                    return;
                }
            }
        }

        OPTIONAL_CONSTEXPR auto in_path(std::array<password_node<Collumns, Rows> *, Collumns * Rows> & path, password_node<Collumns, Rows> *const target) {
            for (int j = 0; j < Collumns * Rows; ++j) {
                if (path[j] == target)
                    return hippobaro::length(path) - j;
            }
            return -1;
        }

        OPTIONAL_CONSTEXPR auto get_inter_points(password_node<Collumns, Rows> *const target) -> std::array<password_node<Collumns, Rows> *, Collumns>{
            std::array<password_node<Collumns, Rows> *, Collumns> ret = {};
            hippobaro::fill(ret, nullptr);

            auto between = 0;
            for (auto && node : *nodes) {
                if (&node == this || &node == target)
                    continue;

                auto dxc = node.coordinates.first - this->coordinates.first;
                auto dyc = node.coordinates.second - this->coordinates.second;

                auto dxl = target->coordinates.first - this->coordinates.first;
                auto dyl = target->coordinates.second - this->coordinates.second;

                auto cross = dxc * dyl - dyc * dxl;

                if (cross == 0) {
                    if (hippobaro::abs(dxl) >= hippobaro::abs(dyl)) {
                        if (dxl > 0 ?
                            this->coordinates.first <= node.coordinates.first &&
                            node.coordinates.first <= target->coordinates.first :
                            target->coordinates.first <= node.coordinates.first &&
                            node.coordinates.first <= this->coordinates.first)
                            ret[between++] = &node;
                    } else {
                        if (dyl > 0 ?
                            this->coordinates.second <= node.coordinates.second &&
                            node.coordinates.second <= target->coordinates.second :
                            target->coordinates.second <= node.coordinates.second &&
                            node.coordinates.second <= this->coordinates.second)
                            ret[between++] = &node;
                    }

                }
            }
            if (hippobaro::length(ret) > 1)
                return ret;
            return ret;
        }

        OPTIONAL_CONSTEXPR auto can_jump_to(std::array<password_node<Collumns, Rows> *, Collumns * Rows> &path, int target) {
            if (this == &(*nodes)[target])
                return false;

            auto interPoints = get_inter_points(&(*nodes)[target]);

            if (hippobaro::length(interPoints) > 0) {
                for (auto &&between : interPoints) {
                    if (in_path(path, between) == -1)
                        return false;
                }
            }
            return in_path(path, &(*nodes)[target]) == -1 && !visited[target];
        }

        OPTIONAL_CONSTEXPR auto can_jump(std::array<password_node<Collumns, Rows> *, Collumns * Rows> &path) {
            for (int i = 0; i < Collumns * Rows; ++i) {
                if (can_jump_to(path, i))
                    return i;
            }

            return -1;
        }

        OPTIONAL_CONSTEXPR auto clean_path(std::array<password_node<Collumns, Rows> *, Collumns * Rows> &path) {
            int i = 0;
            for (; i < Collumns * Rows; ++i) {
                if (path[i] == this)
                    break;
            }
            for (++i; i < Collumns * Rows; ++i) {
                if (path[i])
                    hippobaro::fill(path[i]->visited, false);
                path[i] = nullptr;
            }
        }

        OPTIONAL_CONSTEXPR auto traverse(std::array<password_node<Collumns, Rows> *, Collumns * Rows> & path) -> uint64_t {
            add_to_path(path);
            uint64_t paths = 1;
            int i = 0;
            while ((hippobaro::length(path) < Collumns * Rows) && (i = can_jump(path)) > -1) {
                visited[i] = true;
                paths += (*nodes)[i].traverse(path);
                clean_path(path);
            }

#ifndef NDEBUG
            for (int j = 0; j < Collumns * Rows; ++j) {
                if (path[j])
                    std::cout << "[" << path[j]->coordinates.first << "," << path[j]->coordinates.second << "](" << path[j]->index << ")";
                if (j + 1 < Collumns * Rows && path[j + 1])
                    std::cout <<  " --> ";
            }
            std::cout << std::endl;
#endif

            if (hippobaro::length(path) < 4) {
                paths--;
            }
            return paths;
        }
/*
        0,0   1,0   2,0

        0,1   1,1   2,1

        0,2   1,2   2,2
*/

/*
        1   4   7

        2   5   8

        3   6   9
*/

    };
}

#endif //CELLPHONE_PASSWORD_PASSWORD_NODE_HPP
