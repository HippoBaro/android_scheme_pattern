//
// Created by Hippolyte Barraud on 21/09/2017.
//

#ifndef CELLPHONE_PASSWORD_PASSWORD_NODE_HPP
#define CELLPHONE_PASSWORD_PASSWORD_NODE_HPP

#include <cstdint>
#include <array>
#include <constexpr_utils/utils.hpp>
#include <constexpr_utils/stack.hpp>
#include <iostream>

namespace hippobaro::password_cellphone {

    std::mutex mutex;

    template<int Columns, int Rows>
    class password_node {

    public:

        struct path_node {
            password_node<Columns, Rows> const * node;
            std::array<bool, Columns * Rows> visited;

            constexpr explicit path_node(password_node<Columns, Rows> const *const node) : node(node), visited() {
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

        // This functions gets all nodes that lie in a straight line between two other nodes.
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

            // If the tested node is this node, then we know we can't jump to it.
            if (this == &(*nodes)[target])
                return false;

            // First, we get all points that may lie between this node and the destination.
            // In a 3*3 matrix, only one node may exist between two points, but in larger matrices multiples ones
            // could.
            auto interPoints = get_inter_points(&(*nodes)[target]);

            // If there is indeed one or more points that separates us from the destination we need to check if they
            // satisfy the requirement to allow a jump.
            if (hippobaro::length(interPoints) > 0) {
                for (auto &&between : interPoints) {
                    if (!between)
                        continue;

                    // Here we test if those points have been previously visited in the current path.
                    // If one of them has not been, then we can't jump.
                    path_node tmp(between);
                    if (!path.contains(&tmp))
                        return false;
                }
            }

            // Finally, we check if the destination node has been visited in the current stack
            // AND if this node has previously visited it.
            path_node tmp(&(*nodes)[target]);
            return !path.contains(&tmp) && !path.peek()->visited[target];
        }

        constexpr auto can_jump(node_stack &path) const {
            for (int i = 0; i < Columns * Rows; ++i) {
                if (can_jump_to(path, i))
                    return i;
            }
            return -1;
        }

        auto print_path(node_stack & path) const {
            std::lock_guard<std::mutex> lock(mutex);
            for (int j = 0; j < Columns * Rows; ++j) {
                if (path[j])
                    std::cout << "[" << path[j]->node->coordinates.first << "," << path[j]->node->coordinates.second << "]";
                if (j + 1 < Columns * Rows && path[j + 1])
                    std::cout <<  "--";
            }
            std::cout << std::endl;
        }

        constexpr auto traverse(node_stack & path) const -> std::array<uint64_t, Columns * Rows> {
            std::array<uint64_t, Columns * Rows> pathslen = {};
            int i = 0;

            // First, we push this node on the stack
            path_node path_node(this);
            path.push(&path_node);

            // Then, we jump to every possible cells around.
            while ((i = can_jump(path)) > -1) {
                // We mark the destination node as VISITED so that we don't jump multiple time to it.
                path.peek()->visited[i] = true;
                // And we jump
                pathslen += (*nodes)[i].traverse(path);
            }
            // When we can't jump anymore, we have successfully discovered on new path.
            // So we add it to the result array.
            ++pathslen[path.length()-1];

#ifdef PRINT_RESULT
            print_path(path);
#endif

            // Finally, we pop this node from the stack.
            while (path.pop()->node != this);

            return pathslen;
        }

    };
}

#endif //CELLPHONE_PASSWORD_PASSWORD_NODE_HPP
