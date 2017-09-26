//
// Created by Hippolyte Barraud on 21/09/2017.
//

#ifndef CELLPHONE_PASSWORD_PASSWORD_NODE_HPP
#define CELLPHONE_PASSWORD_PASSWORD_NODE_HPP

#include <cstdint>
#include <array>
#include<iostream>
#include <constexpr_utils/utils.hpp>
#include <constexpr_utils/stack.hpp>

namespace hippobaro::password_cellphone {

    template<int Columns, int Rows>
    class password_node {

    public:

        struct path_node {
            password_node<Columns, Rows> * node;
            std::array<bool, Columns * Rows> visited;

            constexpr explicit path_node(password_node<Columns, Rows> *const node) : node(node), visited() {
                hippobaro::fill(visited, false);
            }

            constexpr bool operator==(const path_node &rhs) const {
                return node == rhs.node;
            }

            constexpr bool operator!=(const path_node &rhs) const {
                return !(rhs == *this);
            }
        };

        using node_stack = hippobaro::stack<path_node, Columns * Rows>;

        std::array<password_node<Columns, Rows>, Columns * Rows> * nodes;
        std::pair<int, int> coordinates;

    public:

        constexpr password_node() : nodes(nullptr), coordinates() {}

        constexpr auto get_inter_points(password_node<Columns, Rows> *const target) const -> std::array<password_node<Columns, Rows> *, Columns>{
            std::array<password_node<Columns, Rows> *, Columns> ret = {};
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

        constexpr auto can_jump_to(node_stack &path, int target) const {
            if (this == &(*nodes)[target])
                return false;

            auto interPoints = get_inter_points(&(*nodes)[target]);

            if (hippobaro::length(interPoints) > 0) {
                for (auto &&between : interPoints) {
                    if (!between)
                        continue;
                    path_node tmp(between);
                    if (path.contains(&tmp) == -1)
                        return false;
                }
            }
            path_node tmp(&(*nodes)[target]);
            return path.contains(&tmp) == -1 && !path.peek()->visited[target];
        }

        constexpr auto can_jump(node_stack &path) const {
            for (int i = 0; i < Columns * Rows; ++i) {
                if (can_jump_to(path, i))
                    return i;
            }
            return -1;
        }

        constexpr auto traverse(node_stack & path) -> std::array<uint64_t, Columns * Rows> {
            std::array<uint64_t, Columns * Rows> pathslen = {};
            int i = 0;

            path_node path_node(this);
            path.push(&path_node);
            while ((path.length() < Columns * Rows) && (i = can_jump(path)) > -1) {
                path.peek()->visited[i] = true;
                pathslen += (*nodes)[i].traverse(path);
            }
            pathslen[path.length()-1]++;

            while (path.pop()->node != this);
            return pathslen;
        }

    };
}

#endif //CELLPHONE_PASSWORD_PASSWORD_NODE_HPP
