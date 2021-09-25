/*
    * Copyright © [2019 - 2021] [Jonny Charlotte]
    *
    * Licensed under the Apache License, Version 2.0 (the "License");
    * you may not use this file except in compliance with the License.
    * You may obtain a copy of the License at
    *
    *     http://www.apache.org/licenses/LICENSE-2.0
    *
    * Unless required by applicable law or agreed to in writing, software
    * distributed under the License is distributed on an "AS IS" BASIS,
    * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    * See the License for the specific language governing permissions and
    * limitations under the License.
*/

#ifndef DATA_STRUCTURE_LEFTIST_TREE_HPP
#define DATA_STRUCTURE_LEFTIST_TREE_HPP

#include "binary_tree.hpp"

namespace data_structure::__data_structure_auxiliary {
    struct leftist_tree_default_condition {
        template <typename TreeIterator>
        static size_t leftist_tree_level(TreeIterator root) noexcept {
            if(not root) {
                return 0;
            }
            auto left_level {leftist_tree_level(root.left_child())};
            auto right_level {leftist_tree_level(root.right_child())};
            return left_level > right_level ? left_level + 1 : right_level + 1;
        }
        template <typename TreeIterator>
        inline bool operator()(TreeIterator root) noexcept {
            return leftist_tree_level(root.left_child()) >= leftist_tree_level(root.right_child());
        }
    };
}

namespace data_structure {
    template <typename T, typename BinaryTree = binary_tree<T>>
    class leftist_tree final {
    public:
        using container_type = BinaryTree;
        using size_type = typename container_type::size_type;
        using difference_type = typename container_type::difference_type;
        using value_type = T;
        using reference = typename container_type::reference;
        using const_reference = typename container_type::const_reference;
        using rvalue_reference = typename container_type::rvalue_reference;
        using pointer = typename container_type::pointer;
        using const_pointer = typename container_type::const_pointer;
        using iterator = typename container_type::iterator;
        using const_iterator = typename container_type::const_iterator;
        using reverse_iterator = typename container_type::reverse_iterator;
        using const_reverse_iterator = typename container_type::const_reverse_iterator;
        static_assert(is_same<value_type, typename container_type::value_type>::value,
                "The stack holds different value_type!");
    public:
        using order = typename container_type::order;
        using direction = typename container_type::direction;
    private:
        container_type tree;
    private:
        template <typename Condition>
        void keep_leftist(const_iterator root, Condition condition) {
            if(root) {
                this->keep_leftist<add_lvalue_reference_t<Condition>>(root.left_child(), condition);
                this->keep_leftist<add_lvalue_reference_t<Condition>>(root.right_child(), condition);
                if(not condition(root)) {
                    this->swap_children(root);
                }
            }
        }
    public:
        constexpr leftist_tree() = default;
        template <typename Condition = __dsa::leftist_tree_default_condition>
        explicit leftist_tree(const container_type &tree, Condition condition = {})
                noexcept(is_nothrow_copy_constructible_v<container_type>) : tree {tree} {
            this->keep_leftist<add_lvalue_reference_t<Condition>>(this->tree.ctbegin(), condition);
        }
        template <typename Condition = __dsa::leftist_tree_default_condition>
        explicit leftist_tree(container_type &&tree, Condition condition = {})
                noexcept(is_nothrow_move_constructible_v<container_type>) : tree {ds::move(tree)} {
            this->keep_leftist<add_lvalue_reference_t<Condition>>(this->tree.ctbegin(), condition);
        }
        leftist_tree(const leftist_tree &) = default;
        leftist_tree(leftist_tree &&) noexcept = default;
        ~leftist_tree() noexcept = default;
    public:
        leftist_tree &operator=(const leftist_tree &) = default;
        leftist_tree &operator=(leftist_tree &&) noexcept = default;
    public:
        void assign(const_reference value) noexcept(is_nothrow_copy_assignable_v<value_type>) {
            this->tree.assign(value);
        }
        [[nodiscard]]
        iterator begin() noexcept {
            return this->tree.begin();
        }
        [[nodiscard]]
        const_iterator begin() const noexcept {
            return this->tree.begin();
        }
        [[nodiscard]]
        iterator tbegin() noexcept {
            return this->tree.tbegin();
        }
        [[nodiscard]]
        const_iterator tbegin() const noexcept {
            return this->tree.tbegin();
        }
        [[nodiscard]]
        constexpr iterator end() noexcept {
            return this->tree.end();
        }
        [[nodiscard]]
        constexpr const_iterator end() const noexcept {
            return this->tree.end();
        }
        [[nodiscard]]
        const_iterator cbegin() const noexcept {
            return this->tree.cbegin();
        }
        [[nodiscard]]
        const_iterator ctbegin() const noexcept {
            return this->tree.ctbegin();
        }
        [[nodiscard]]
        constexpr const_iterator cend() const noexcept {
            return this->tree.cend();
        }
        [[nodiscard]]
        reverse_iterator rbegin() noexcept {
            return this->tree.rbegin();
        }
        [[nodiscard]]
        const_reverse_iterator rbegin() const noexcept {
            return this->tree.rbegin();
        }
        [[nodiscard]]
        reverse_iterator rtbegin() noexcept {
            return this->tree.rtbegin();
        }
        [[nodiscard]]
        const_reverse_iterator rtbegin() const noexcept {
            return this->tree.rtbegin();
        }
        [[nodiscard]]
        constexpr reverse_iterator rend() noexcept {
            return this->tree.rend();
        }
        [[nodiscard]]
        constexpr const_reverse_iterator rend() const noexcept {
            return this->tree.rend();
        }
        [[nodiscard]]
        const_reverse_iterator crbegin() const noexcept {
            return this->tree.crbegin();
        }
        [[nodiscard]]
        const_reverse_iterator crtbegin() const noexcept {
            return this->tree.crtbegin();
        }
        [[nodiscard]]
        constexpr const_reverse_iterator crend() const noexcept {
            return this->tree.crend();
        }
        [[nodiscard]]
        size_type size() const noexcept {
            return this->tree.size();
        }
        [[nodiscard]]
        size_type size(const_iterator start) noexcept {
            return this->tree.size(start);
        }
        [[nodiscard]]
        size_type level() const noexcept {
            return this->tree.level();
        }
        [[nodiscard]]
        size_type level(const_iterator start) noexcept {
            return this->tree.level(start);
        }
        [[nodiscard]]
        constexpr bool empty() const noexcept {
            return this->tree.empty();
        }
        [[nodiscard]]
        constexpr size_type max_size() const noexcept {
            return this->tree.max_size();
        }
        [[nodiscard]]
        reference top() noexcept {
            return this->tree.top();
        }
        [[nodiscard]]
        const_reference top() const noexcept {
            return this->tree.top();
        }
        void swap(leftist_tree &rhs) noexcept {
            this->tree.swap(rhs.tree);
        }
        void swap(container_type &rhs) noexcept {
            this->tree.swap(rhs);
        }
        void swap_children(const_iterator pos) noexcept {
            this->tree.swap_children(pos);
        }
        void clear() noexcept {
            this->tree.clear();
        }
        template <typename UnaryPrediction>
        void traversal(UnaryPrediction pred, leftist_tree::order order = leftist_tree::order::in)
                noexcept(has_nothrow_function_call_operator_v<UnaryPrediction, reference>) {
            this->tree.template traversal<add_lvalue_reference_t<UnaryPrediction>>(pred, order);
        }
        template <typename UnaryPrediction>
        void traversal(const_iterator start, UnaryPrediction pred,
                leftist_tree::order order = leftist_tree::order::in)
                noexcept(has_nothrow_function_call_operator_v<UnaryPrediction, reference>) {
            this->tree.template traversal<add_lvalue_reference_t<UnaryPrediction>>(pred, order);
        }
        template <typename ...Args>
        void initialize_top(Args &&...args) {
            this->initialize_top(ds::forward<Args>(args)...);
        }
        template <typename Condition = __dsa::leftist_tree_default_condition>
        iterator insert_under(const_iterator pos, const_reference value,
                leftist_tree::direction direction, Condition condition = {}) {
            return this->tree.emplace_under(pos, direction, condition, value);
        }
        template <typename Condition = __dsa::leftist_tree_default_condition>
        iterator insert_under(const_iterator pos, rvalue_reference value,
                leftist_tree::direction direction, Condition condition = {}) {
            return this->tree.emplace_under(pos, direction, condition, ds::move(value));
        }
        template <typename Condition = __dsa::leftist_tree_default_condition>
        iterator insert_under(const_iterator pos, const leftist_tree &rhs,
                leftist_tree::direction direction = leftist_tree::direction::left, Condition condition = {}) {
            auto r {this->tree.insert_under(pos, rhs.tree, direction)};
            this->keep_leftist<add_lvalue_reference_t<Condition>>(pos, condition);
            return r;
        }
        template <typename Condition = __dsa::leftist_tree_default_condition>
        iterator insert_under(const_iterator pos, leftist_tree && rhs,
                leftist_tree::direction direction = leftist_tree::direction::left,
                Condition condition = {}) noexcept {
            auto r {this->tree.insert_under(pos, ds::move(rhs.tree), direction)};
            this->keep_leftist<add_lvalue_reference_t<Condition>>(pos, condition);
            return r;
        }
        template <typename Condition = __dsa::leftist_tree_default_condition>
        int insert_under(const_iterator pos, const_reference value, Condition condition = {}) {
            auto r {this->tree.insert_under(pos, value)};
            this->keep_leftist<add_lvalue_reference_t<Condition>>(pos, condition);
            return r;
        }
        void erase_under(const_iterator pos, leftist_tree::direction direction) noexcept {
            this->tree.erase_under(pos, direction);
            if(direction == leftist_tree::direction::left and pos.node->right_child) {
                ds::swap(pos.node->left_child, pos.node->right_child);
            }
        }
        void erase_under(const_iterator pos) noexcept {
            this->tree.erase_under(pos);
        }
        template <typename Condition = __dsa::leftist_tree_default_condition, typename ...Args>
        iterator emplace_under(const_iterator pos, leftist_tree::direction direction,
                Condition condition = {}, Args &&...args) {
            auto r {this->tree.emplace_under(pos, direction, ds::forward<Args>(args)...)};
            this->keep_leftist<add_lvalue_reference_t<Condition>>(pos, condition);
            return r;
        }
        void push_front(const_reference value) {
            this->tree.push_front(value, leftist_tree::direction::left);
        }
        void push_front(rvalue_reference value) {
            this->tree.push_front(ds::move(value), leftist_tree::direction::left);
        }
        template <typename ...Args>
        void emplace_front(Args &&...args) {
            this->tree.emplace_front(leftist_tree::direction::left, ds::forward<Args>(args)...);
        }
    public:
        auto rotate(const_iterator pos, leftist_tree::direction direction) noexcept {
            if constexpr(not is_void_v<decltype(this->tree.rotate(pos, direction))>) {
                return this->tree.rotate(pos, direction);
            }
            this->tree.rotate(pos, direction);
        }
    };
}

#endif //DATA_STRUCTURE_LEFTIST_TREE_HPP
