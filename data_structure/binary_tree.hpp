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

#ifndef DATA_STRUCTURE_BINARY_TREE_HPP
#define DATA_STRUCTURE_BINARY_TREE_HPP

#include "queue.hpp"

namespace data_structure {
    template <typename T, typename Allocator = allocator<type_holder<T>>>
    class binary_tree final {
    public:
        using allocator_type = Allocator;
        using size_type = allocator_traits_t(allocator_type, size_type);
        using difference_type = allocator_traits_t(allocator_type, difference_type);
        using value_type = T;
        using reference = allocator_traits_t(allocator_type, reference);
        using const_reference = allocator_traits_t(allocator_type, const_reference);
        using rvalue_reference = allocator_traits_t(allocator_type, rvalue_reference);
        using pointer = allocator_traits_t(allocator_type, pointer);
        using const_pointer = allocator_traits_t(allocator_type, const_pointer);
        using iterator = __dsa::binary_tree_iterator<value_type, false>;
        using const_iterator = __dsa::binary_tree_iterator<value_type, true>;
        using reverse_iterator = ds::reverse_iterator<iterator>;
        using const_reverse_iterator = ds::reverse_iterator<const_iterator>;
    private:
        using node_value_type = __dsa::binary_tree_node<value_type>;
        using node_type = node_value_type *;
        using alloc_traits = allocator_traits<allocator_type>;
        static_assert(is_same_v<value_type, typename alloc_traits::value_type>,
                "The Allocator::value_type must be the same as template argument value_type!");
    public:
        enum class order {
            pre, in, post, level
        };
        enum class direction {
            left, right
        };
    private:
        node_type root;
    private:
        [[nodiscard]]
        static node_type node_allocate();
        static void deallocate_from(node_type) noexcept;
        [[nodiscard]]
        static size_type level_auxiliary(node_type) noexcept;
        template <typename UnaryPrediction>
        static void pre_traversal(UnaryPrediction, node_type)
                noexcept(has_nothrow_function_call_operator_v<UnaryPrediction, reference>);
        template <typename UnaryPrediction>
        static void in_traversal(UnaryPrediction, node_type)
                noexcept(has_nothrow_function_call_operator_v<UnaryPrediction, reference>);
        template <typename UnaryPrediction>
        static void post_traversal(UnaryPrediction, node_type)
                noexcept(has_nothrow_function_call_operator_v<UnaryPrediction, reference>);
        template <typename UnaryPrediction>
        static void level_traversal(UnaryPrediction, node_type)
                noexcept(has_nothrow_function_call_operator_v<UnaryPrediction, reference>);
        [[nodiscard]]
        static size_type size_auxiliary(node_type) noexcept;
        [[nodiscard]]
        static node_type copy_from_rhs(node_type);
    public:
        constexpr binary_tree() noexcept = default;
        explicit binary_tree(const_reference);
        explicit binary_tree(rvalue_reference);
        explicit binary_tree(const_iterator);
        binary_tree(const binary_tree &);
        binary_tree(binary_tree &&) noexcept;
        template <typename AllocatorRHS>
        explicit binary_tree(const binary_tree<value_type, AllocatorRHS> &);
        template <typename AllocatorRHS>
        explicit binary_tree(binary_tree<value_type, AllocatorRHS> &&) noexcept;
        ~binary_tree() noexcept;
    public:
        binary_tree &operator=(const binary_tree &);
        binary_tree &operator=(binary_tree &&) noexcept;
        template <typename AllocatorRHS>
        binary_tree &operator=(const binary_tree<value_type, AllocatorRHS> &);
        template <typename AllocatorRHS>
        binary_tree &operator=(binary_tree<value_type, AllocatorRHS> &&) noexcept;
    public:
        void assign(const_reference) noexcept(is_nothrow_copy_assignable_v<value_type>);
        [[nodiscard]]
        iterator begin() noexcept;
        [[nodiscard]]
        const_iterator begin() const noexcept;
        [[nodiscard]]
        iterator tbegin() noexcept;
        [[nodiscard]]
        const_iterator tbegin() const noexcept;
        [[nodiscard]]
        constexpr iterator end() noexcept;
        [[nodiscard]]
        constexpr const_iterator end() const noexcept;
        [[nodiscard]]
        const_iterator cbegin() const noexcept;
        [[nodiscard]]
        const_iterator ctbegin() const noexcept;
        [[nodiscard]]
        constexpr const_iterator cend() const noexcept;
        [[nodiscard]]
        reverse_iterator rbegin() noexcept;
        [[nodiscard]]
        const_reverse_iterator rbegin() const noexcept;
        [[nodiscard]]
        reverse_iterator rtbegin() noexcept;
        [[nodiscard]]
        const_reverse_iterator rtbegin() const noexcept;
        [[nodiscard]]
        constexpr reverse_iterator rend() noexcept;
        [[nodiscard]]
        constexpr const_reverse_iterator rend() const noexcept;
        [[nodiscard]]
        const_reverse_iterator crbegin() const noexcept;
        [[nodiscard]]
        const_reverse_iterator crtbegin() const noexcept;
        [[nodiscard]]
        constexpr const_reverse_iterator crend() const noexcept;
        [[nodiscard]]
        size_type size() const noexcept;
        [[nodiscard]]
        static size_type size(const_iterator) noexcept;
        [[nodiscard]]
        size_type level() const noexcept;
        [[nodiscard]]
        static size_type level(const_iterator) noexcept;
        [[nodiscard]]
        constexpr bool empty() const noexcept;
        [[nodiscard]]
        constexpr size_type max_size() const noexcept;
        [[nodiscard]]
        reference top() noexcept;
        [[nodiscard]]
        const_reference top() const noexcept;
        void swap(binary_tree &) noexcept;
        template <typename AllocatorRHS>
        void swap(binary_tree<value_type, AllocatorRHS> &) noexcept;
        static void swap_children(const_iterator) noexcept;
        void clear() noexcept;
        template <typename UnaryPrediction>
        void traversal(UnaryPrediction, binary_tree::order = binary_tree::order::in)
                noexcept(has_nothrow_function_call_operator_v<UnaryPrediction, reference>);
        template <typename UnaryPrediction>
        static void traversal(const_iterator, UnaryPrediction, binary_tree::order = binary_tree::order::in)
                noexcept(has_nothrow_function_call_operator_v<UnaryPrediction, reference>);
        template <typename ...Args>
        void initialize_top(Args &&...args);
        iterator insert_under(const_iterator, const_reference, binary_tree::direction);
        iterator insert_under(const_iterator, rvalue_reference, binary_tree::direction);
        iterator insert_under(const_iterator, const binary_tree &,
                binary_tree::direction = binary_tree::direction::left);
        iterator insert_under(const_iterator, binary_tree &&,
                binary_tree::direction = binary_tree::direction::left) noexcept;
        int insert_under(const_iterator, const_reference);
        void erase_under(const_iterator, binary_tree::direction) noexcept;
        void erase_under(const_iterator) noexcept;
        template <typename ...Args>
        iterator emplace_under(const_iterator, binary_tree::direction, Args &&...);
        void push_front(const_reference, binary_tree::direction = binary_tree::direction::left);
        void push_front(rvalue_reference, binary_tree::direction = binary_tree::direction::left);
        template <typename ...Args>
        void emplace_front(binary_tree::direction, Args &&...);
    public:
        static bool rotate(const_iterator, binary_tree::direction) noexcept;
    };
    template <typename T, typename AllocatorLHS, typename AllocatorRHS = AllocatorLHS>
    void swap(binary_tree<T, AllocatorLHS> &, binary_tree<T, AllocatorRHS> &) noexcept;
    template <typename T, typename AllocatorLHS, typename AllocatorRHS = AllocatorLHS>
    bool operator==(const binary_tree<T, AllocatorLHS> &, const binary_tree<T, AllocatorRHS> &)
            noexcept(has_nothrow_equal_to_operator_v<T>);
    template <typename T, typename AllocatorLHS, typename AllocatorRHS = AllocatorLHS>
    bool operator!=(const binary_tree<T, AllocatorLHS> &, const binary_tree<T, AllocatorRHS> &)
            noexcept(has_nothrow_equal_to_operator_v<T>);
}

namespace data_structure {
    /* private functions */
    template <typename T, typename Allocator>
    inline typename binary_tree<T, Allocator>::node_type binary_tree<T, Allocator>::node_allocate() {
        return reinterpret_cast<node_type>(alloc_traits::operator new(sizeof(node_value_type)));
    }
    template <typename T, typename Allocator>
    void binary_tree<T, Allocator>::deallocate_from(node_type root) noexcept {
        if(root->left_child) {
            binary_tree::deallocate_from(root->left_child);
        }
        if(root->right_child) {
            binary_tree::deallocate_from(root->right_child);
        }
        alloc_traits::destroy(ds::address_of(root->value));
        alloc_traits::operator delete(root);
    }
    template <typename T, typename Allocator>
    typename binary_tree<T, Allocator>::size_type
    binary_tree<T, Allocator>::level_auxiliary(node_type root) noexcept {
        if(not root) {
            return 0;
        }
        size_type level {1};
        if(root->left_child) {
            if(auto left_level {binary_tree::level_auxiliary(root->left_child) + 1}; left_level > level) {
                level = left_level;
            }
        }
        if(root->right_child) {
            if(auto right_level {binary_tree::level_auxiliary(root->right_child) + 1}; right_level > level) {
                level = right_level;
            }
        }
        return level;
    }
    template <typename T, typename Allocator>
    template <typename UnaryPrediction>
    void binary_tree<T, Allocator>::pre_traversal(UnaryPrediction pred, node_type root)
            noexcept(has_nothrow_function_call_operator_v<UnaryPrediction, reference>) {
        if(root) {
            pred(root->value);
            binary_tree::pre_traversal<add_lvalue_reference_t<UnaryPrediction>>(pred, root->left_child);
            binary_tree::pre_traversal<add_lvalue_reference_t<UnaryPrediction>>(pred, root->right_child);
        }
    }
    template <typename T, typename Allocator>
    template <typename UnaryPrediction>
    void binary_tree<T, Allocator>::in_traversal(UnaryPrediction pred, node_type root)
            noexcept(has_nothrow_function_call_operator_v<UnaryPrediction, reference>) {
        if(root) {
            binary_tree::in_traversal<add_lvalue_reference_t<UnaryPrediction>>(pred, root->left_child);
            pred(root->value);
            binary_tree::in_traversal<add_lvalue_reference_t<UnaryPrediction>>(pred, root->right_child);
        }
    }
    template <typename T, typename Allocator>
    template <typename UnaryPrediction>
    void binary_tree<T, Allocator>::post_traversal(UnaryPrediction pred, node_type root)
            noexcept(has_nothrow_function_call_operator_v<UnaryPrediction, reference>) {
        if(root) {
            binary_tree::post_traversal<add_lvalue_reference_t<UnaryPrediction>>(pred, root->left_child);
            binary_tree::post_traversal<add_lvalue_reference_t<UnaryPrediction>>(pred, root->right_child);
            pred(root->value);
        }
    }
    template <typename T, typename Allocator>
    template <typename UnaryPrediction>
    void binary_tree<T, Allocator>::level_traversal(UnaryPrediction pred, node_type root)
            noexcept(has_nothrow_function_call_operator_v<UnaryPrediction, reference>) {
        if(root) {
            queue<node_type> q;
            q.push(root);
            while(not q.empty()) {
                auto &front = q.front();
                pred(front->value);
                if(front->left_child) {
                    q.push(front->left_child);
                }
                if(front->right_child) {
                    q.push(front->right_child);
                }
                q.pop();
            }
        }
    }
    template <typename T, typename Allocator>
    typename binary_tree<T, Allocator>::size_type
    binary_tree<T, Allocator>::size_auxiliary(node_type start) noexcept {
        return start ? size_auxiliary(start->left_child) + size_auxiliary(start->right_child) + 1 : 0;
    }
    template <typename T, typename Allocator>
    typename binary_tree<T, Allocator>::node_type
    binary_tree<T, Allocator>::copy_from_rhs(node_type rhs) {
        if(not rhs) {
            return nullptr;
        }
        auto new_node {binary_tree::node_allocate()};
        if constexpr(is_nothrow_copy_constructible_v<value_type>) {
            alloc_traits::construct(ds::address_of(new_node->value), rhs->value);
        }else {
            try {
                alloc_traits::construct(ds::address_of(new_node->value), rhs->value);
            }catch(...) {
                alloc_traits::operator delete(new_node);
                throw;
            }
        }
        if(auto left_child {binary_tree::copy_from_rhs(rhs->left_child)}; left_child) {
            left_child->parent = new_node;
            new_node->left_child = left_child;
        }else {
            new_node->left_child = nullptr;
        }
        if(auto right_child {binary_tree::copy_from_rhs(rhs->right_child)}; right_child) {
            right_child->parent = new_node;
            new_node->right_child = right_child;
        }else {
            new_node->right_child = nullptr;
        }
        return new_node;
    }

    /* public functions */
    template <typename T, typename Allocator>
    binary_tree<T, Allocator>::binary_tree(const_reference value) : root {this->node_allocate()} {
        if constexpr(is_nothrow_copy_constructible_v<value_type>) {
            alloc_traits::construct(ds::address_of(this->root->value), value);
        }else {
            try {
                alloc_traits::construct(ds::address_of(this->root->value), value);
            }catch(...) {
                alloc_traits::operator delete(this->root);
            }
        }
        this->root->left_child = this->root->right_child = this->root->parent = nullptr;
    }
    template <typename T, typename Allocator>
    binary_tree<T, Allocator>::binary_tree(rvalue_reference value) : root {this->node_allocate()} {
        if constexpr(is_nothrow_move_constructible_v<value_type> or
                (not is_nothrow_move_constructible_v<value_type> and is_nothrow_copy_constructible_v<value_type>)) {
            alloc_traits::construct(ds::address_of(this->root->value),
                    ds::move_if<is_nothrow_move_constructible_v<value_type>>(value));
        }else {
            try {
                alloc_traits::construct(ds::address_of(this->root->value), value);
            }catch(...) {
                alloc_traits::operator delete(this->root);
            }
        }
        this->root->left_child = this->root->right_child = this->root->parent = nullptr;
    }
    template <typename T, typename Allocator>
    binary_tree<T, Allocator>::binary_tree(const_iterator pos) : root {this->copy_from_rhs(pos.node)} {
        if(this->root) {
            this->root->parent = nullptr;
        }
    }
    template <typename T, typename Allocator>
    binary_tree<T, Allocator>::binary_tree(const binary_tree &rhs) : root {this->copy_from_rhs(rhs.root)} {
        if(this->root) {
            this->root->parent = nullptr;
        }
    }
    template <typename T, typename Allocator>
    binary_tree<T, Allocator>::binary_tree(binary_tree &&rhs) noexcept : root {rhs.root} {
        rhs.root = nullptr;
    }
    template <typename T, typename Allocator>
    template <typename AllocatorRHS>
    binary_tree<T, Allocator>::binary_tree(const binary_tree<value_type, AllocatorRHS> &rhs) :
            binary_tree(*reinterpret_cast<binary_tree *>(&rhs)) {}
    template <typename T, typename Allocator>
    template <typename AllocatorRHS>
    binary_tree<T, Allocator>::binary_tree(binary_tree<value_type, AllocatorRHS> &&rhs) noexcept :
            binary_tree(*reinterpret_cast<binary_tree *>(&rhs)) {}
    template <typename T, typename Allocator>
    binary_tree<T, Allocator>::~binary_tree() noexcept {
        this->deallocate_from(this->root);
    }
    template <typename T, typename Allocator>
    binary_tree<T, Allocator> &binary_tree<T, Allocator>::operator=(const binary_tree &rhs) {
        if(&rhs not_eq this) {
            auto new_root {copy_from_rhs(rhs.root)};
            if(new_root) {
                new_root->parent = nullptr;
            }
            this->~binary_tree();
            this->root = new_root;
        }
        return *this;
    }
    template <typename T, typename Allocator>
    binary_tree<T, Allocator> &binary_tree<T, Allocator>::operator=(binary_tree &&rhs) noexcept {
        if(&rhs not_eq this) {
            this->~binary_tree();
            this->root = rhs.root;
            rhs.root = nullptr;
        }
        return *this;
    }
    template <typename T, typename Allocator>
    template <typename AllocatorRHS>
    binary_tree<T, Allocator> &binary_tree<T, Allocator>::operator=(
            const binary_tree<value_type, AllocatorRHS> &rhs) {
        auto new_root {this->copy_from_rhs(reinterpret_cast<binary_tree *>(&rhs)->root)};
        if(new_root) {
            new_root->parent = nullptr;
        }
        this->~binary_tree();
        this->root = new_root;
        return *this;
    }
    template <typename T, typename Allocator>
    template <typename AllocatorRHS>
    binary_tree<T, Allocator> &binary_tree<T, Allocator>::operator=(
            binary_tree<value_type, AllocatorRHS> &&rhs) noexcept {
        this->~binary_tree();
        this->root = rhs.root;
        rhs.root = nullptr;
        return *this;
    }
    template <typename T, typename Allocator>
    void binary_tree<T, Allocator>::assign(const_reference value)
            noexcept(is_nothrow_copy_assignable_v<value_type>) {
        this->traversal([&value](reference v) noexcept(is_nothrow_copy_assignable_v<value_type>) -> void {
            v = value;
        });
    }
    template <typename T, typename Allocator>
    typename binary_tree<T, Allocator>::iterator binary_tree<T, Allocator>::begin() noexcept {
        auto cursor {this->root};
        while(cursor->left_child) {
            cursor = cursor->left_child;
        }
        return iterator(cursor);
    }
    template <typename T, typename Allocator>
    inline typename binary_tree<T, Allocator>::const_iterator binary_tree<T, Allocator>::begin() const noexcept {
        return const_cast<binary_tree *>(this)->begin();
    }
    template <typename T, typename Allocator>
    inline typename binary_tree<T, Allocator>::iterator binary_tree<T, Allocator>::tbegin() noexcept {
        return iterator(this->root);
    }
    template <typename T, typename Allocator>
    inline typename binary_tree<T, Allocator>::const_iterator binary_tree<T, Allocator>::tbegin() const noexcept {
        return const_iterator(this->root);
    }
    template <typename T, typename Allocator>
    inline constexpr typename binary_tree<T, Allocator>::iterator binary_tree<T, Allocator>::end() noexcept {
        return {};
    }
    template <typename T, typename Allocator>
    inline constexpr typename binary_tree<T, Allocator>::const_iterator
    binary_tree<T, Allocator>::end() const noexcept {
        return {};
    }
    template <typename T, typename Allocator>
    inline typename binary_tree<T, Allocator>::const_iterator binary_tree<T, Allocator>::cbegin() const noexcept {
        return this->begin();
    }
    template <typename T, typename Allocator>
    inline typename binary_tree<T, Allocator>::const_iterator binary_tree<T, Allocator>::ctbegin() const noexcept {
        return this->tbegin();
    }
    template <typename T, typename Allocator>
    inline constexpr typename binary_tree<T, Allocator>::const_iterator
    binary_tree<T, Allocator>::cend() const noexcept {
        return {};
    }
    template <typename T, typename Allocator>
    typename binary_tree<T, Allocator>::reverse_iterator binary_tree<T, Allocator>::rbegin() noexcept {
        auto cursor {this->root};
        while(cursor->right_child) {
            cursor = cursor->right_child;
        }
        return reverse_iterator(iterator(cursor));
    }
    template <typename T, typename Allocator>
    inline typename binary_tree<T, Allocator>::const_reverse_iterator
    binary_tree<T, Allocator>::rbegin() const noexcept {
        return const_cast<binary_tree *>(this)->rbegin();
    }
    template <typename T, typename Allocator>
    inline typename binary_tree<T, Allocator>::reverse_iterator binary_tree<T, Allocator>::rtbegin() noexcept {
        return reverse_iterator(iterator(this->root));
    }
    template <typename T, typename Allocator>
    inline typename binary_tree<T, Allocator>::const_reverse_iterator
    binary_tree<T, Allocator>::rtbegin() const noexcept {
        return reverse_iterator(const_iterator(this->root));
    }
    template <typename T, typename Allocator>
    inline constexpr typename binary_tree<T, Allocator>::reverse_iterator
    binary_tree<T, Allocator>::rend() noexcept {
        return {};
    }
    template <typename T, typename Allocator>
    inline constexpr typename binary_tree<T, Allocator>::const_reverse_iterator
    binary_tree<T, Allocator>::rend() const noexcept {
        return {};
    }
    template <typename T, typename Allocator>
    inline typename binary_tree<T, Allocator>::const_reverse_iterator
    binary_tree<T, Allocator>::crbegin() const noexcept {
        return this->rbegin();
    }
    template <typename T, typename Allocator>
    inline typename binary_tree<T, Allocator>::const_reverse_iterator
    binary_tree<T, Allocator>::crtbegin() const noexcept {
        return this->rtbegin();
    }
    template <typename T, typename Allocator>
    inline constexpr typename binary_tree<T, Allocator>::const_reverse_iterator
    binary_tree<T, Allocator>::crend() const noexcept {
        return {};
    }
    template <typename T, typename Allocator>
    typename binary_tree<T, Allocator>::size_type binary_tree<T, Allocator>::size() const noexcept {
        size_type size {0};
        for(auto it {this->cbegin()}; it not_eq this->cend(); ++it, static_cast<void>(++size));
        return size;
    }
    template <typename T, typename Allocator>
    inline typename binary_tree<T, Allocator>::size_type
    binary_tree<T, Allocator>::size(const_iterator start) noexcept {
        return binary_tree::size_auxiliary(start.node);
    }
    template <typename T, typename Allocator>
    inline typename binary_tree<T, Allocator>::size_type binary_tree<T, Allocator>::level() const noexcept {
        return this->level_auxiliary(this->root);
    }
    template <typename T, typename Allocator>
    inline typename binary_tree<T, Allocator>::size_type
    binary_tree<T, Allocator>::level(const_iterator start) noexcept {
        return binary_tree::level_auxiliary(start.node);
    }
    template <typename T, typename Allocator>
    inline constexpr bool binary_tree<T, Allocator>::empty() const noexcept {
        return this->root;
    }
    template <typename T, typename Allocator>
    inline constexpr typename binary_tree<T, Allocator>::size_type
    binary_tree<T, Allocator>::max_size() const noexcept {
        return std::numeric_limits<size_type>::max() / sizeof(node_value_type);
    }
    template <typename T, typename Allocator>
    inline typename binary_tree<T, Allocator>::reference binary_tree<T, Allocator>::top() noexcept {
        return this->root->value;
    }
    template <typename T, typename Allocator>
    inline typename binary_tree<T, Allocator>::const_reference
    binary_tree<T, Allocator>::top() const noexcept {
        return this->root->value;
    }
    template <typename T, typename Allocator>
    inline void binary_tree<T, Allocator>::swap(binary_tree &rhs) noexcept {
        if(not(this == &rhs)) {
            ds::swap(this->root, rhs.root);
        }
    }
    template <typename T, typename Allocator>
    template <typename AllocatorRHS>
    inline void binary_tree<T, Allocator>::swap(binary_tree<value_type, AllocatorRHS> &rhs) noexcept {
        this->swap(*reinterpret_cast<binary_tree *>(rhs));
    }
    template <typename T, typename Allocator>
    inline void binary_tree<T, Allocator>::swap_children(const_iterator pos) noexcept {
        if(pos) {
            ds::swap(pos.node->left_child, pos.node->right_child);
        }
    }
    template <typename T, typename Allocator>
    inline void binary_tree<T, Allocator>::clear() noexcept {
        this->deallocate_from(this->root);
        this->root = nullptr;
    }
    template <typename T, typename Allocator>
    template <typename UnaryPrediction>
    inline void binary_tree<T, Allocator>::traversal(UnaryPrediction pred, binary_tree::order order)
            noexcept(has_nothrow_function_call_operator_v<UnaryPrediction, reference>) {
        switch(order) {
            case binary_tree::order::pre :
                this->pre_traversal<add_lvalue_reference_t<UnaryPrediction>>(pred, this->root);
                break;
            case binary_tree::order::in :
                this->in_traversal<add_lvalue_reference_t<UnaryPrediction>>(pred, this->root);
                break;
            case binary_tree::order::post :
                this->post_traversal<add_lvalue_reference_t<UnaryPrediction>>(pred, this->root);
                break;
            case binary_tree::order::level :
                this->level_traversal<add_lvalue_reference_t<UnaryPrediction>>(pred, this->root);
                break;
            default :
                break;
        }
    }
    template <typename T, typename Allocator>
    template <typename UnaryPrediction>
    inline void binary_tree<T, Allocator>::traversal(const_iterator start, UnaryPrediction pred,
            binary_tree::order order) noexcept(has_nothrow_function_call_operator_v<UnaryPrediction, reference>) {
        switch(order) {
            case binary_tree::order::pre :
                binary_tree::pre_traversal<add_lvalue_reference_t<UnaryPrediction>>(pred, start.node);
                break;
            case binary_tree::order::in :
                binary_tree::in_traversal<add_lvalue_reference_t<UnaryPrediction>>(pred, start.node);
                break;
            case binary_tree::order::post :
                binary_tree::post_traversal<add_lvalue_reference_t<UnaryPrediction>>(pred, start.node);
                break;
            case binary_tree::order::level :
                binary_tree::level_traversal<add_lvalue_reference_t<UnaryPrediction>>(pred, start.node);
                break;
            default :
                break;
        }
    }
    template <typename T, typename Allocator>
    template <typename ...Args>
    void binary_tree<T, Allocator>::initialize_top(Args &&...args) {
        if(this->root == nullptr) {
            this->root = this->node_allocate();
            if constexpr(is_nothrow_constructible_v<value_type, Args...>) {
                alloc_traits::construct(ds::address_of(this->root->value), ds::forward<Args>(args)...);
            }else {
                try {
                    alloc_traits::construct(ds::address_of(this->root->value), ds::forward<Args>(args)...);
                }catch(...) {
                    alloc_traits::operator delete(this->root);
                    throw;
                }
            }
            this->root->parent = this->root->left_child = this->root->right_child = nullptr;
        }
    }
    template <typename T, typename Allocator>
    inline typename binary_tree<T, Allocator>::iterator binary_tree<T, Allocator>::insert_under(
            const_iterator pos, const_reference value, binary_tree::direction direction) {
        return this->emplace_under(pos, direction, value);
    }
    template <typename T, typename Allocator>
    inline typename binary_tree<T, Allocator>::iterator binary_tree<T, Allocator>::insert_under(
            const_iterator pos, rvalue_reference value, binary_tree::direction direction) {
        return this->emplace_under(pos, direction, ds::move(value));
    }
    template <typename T, typename Allocator>
    inline typename binary_tree<T, Allocator>::iterator binary_tree<T, Allocator>::insert_under(
            const_iterator pos, const binary_tree &rhs, binary_tree::direction direction) {
        if(not pos) {
            return {};
        }
        if(direction == binary_tree::direction::left) {
            if(pos.node->left_child) {
                return pos;
            }
            pos.node->left_child = this->copy_from_rhs(rhs.root);
            if(pos.node->left_child) {
                pos.node->left_child->parent = nullptr;
            }
            return iterator(pos.node->left_child);
        }
        if(pos.node->right_child) {
            return pos;
        }
        pos.node->right_child = this->copy_from_rhs(rhs.root);
        if(pos.node->right_child) {
            pos.node->right_child->parent = nullptr;
        }
        return iterator(pos.node->right_child);
    }
    template <typename T, typename Allocator>
    inline typename binary_tree<T, Allocator>::iterator binary_tree<T, Allocator>::insert_under(
            const_iterator pos, binary_tree &&rhs, binary_tree::direction direction) noexcept {
        if(direction == binary_tree::direction::left) {
            if(pos.node->left_child) {
                return pos;
            }
            pos.node->left_child = rhs.root;
            rhs.root = nullptr;
            return iterator(pos.node->left_child);
        }
        if(pos.node->right_child) {
            return pos;
        }
        pos.node->right_child = rhs.root;
        rhs.root = nullptr;
        return iterator(pos.node->right_child);
    }
    template <typename T, typename Allocator>
    inline int binary_tree<T, Allocator>::insert_under(const_iterator pos, const_reference value) {
        auto left_inserted {false}, right_inserted {false};
        if(this->emplace_under(pos, binary_tree::direction::left, value) not_eq pos) {
            left_inserted = true;
        }
        if(this->emplace_under(pos, binary_tree::direction::right, value) not_eq pos) {
            right_inserted = true;
        }
        return left_inserted ? right_inserted ? 2 : -1 : right_inserted ? 1 : 0;
    }
    template <typename T, typename Allocator>
    inline void binary_tree<T, Allocator>::erase_under(
            const_iterator pos, binary_tree::direction direction) noexcept {
        if(not pos) {
            return;
        }
        if(direction == binary_tree::direction::left) {
            if(pos.node->left_child) {
                alloc_traits::destroy(pos.node->left_child->value);
                alloc_traits::operator delete(pos.node->left_child);
                pos.node->left_child = nullptr;
            }
        }else {
            if(pos.node->right_child) {
                alloc_traits::destroy(pos.node->right_child->value);
                alloc_traits::operator delete(pos.node->right_child);
                pos.node->right_child = nullptr;
            }
        }
    }
    template <typename T, typename Allocator>
    inline void binary_tree<T, Allocator>::erase_under(const_iterator pos) noexcept {
        if(not pos) {
            return;
        }
        if(pos.node->left_child) {
            this->deallocate_from(pos.node->left_child);
        }
        if(pos.node->right_child) {
            this->deallocate_from(pos.node->right_child);
        }
    }
    template <typename T, typename Allocator>
    template <typename ...Args>
    typename binary_tree<T, Allocator>::iterator binary_tree<T, Allocator>::emplace_under(
            const_iterator pos, binary_tree::direction direction, Args &&...args) {
        if(not pos) {
            return {};
        }
        if(direction == binary_tree::direction::left) {
            if(pos.node->left_child) {
                return iterator(pos.node);
            }
            auto new_node {this->node_allocate()};
            if constexpr(is_nothrow_constructible_v<value_type, Args...>) {
                alloc_traits::construct(ds::address_of(new_node->value), ds::forward<Args>(args)...);
            }else {
                try {
                    alloc_traits::construct(ds::address_of(new_node->value), ds::forward<Args>(args)...);
                }catch(...) {
                    alloc_traits::operator delete(new_node);
                    throw;
                }
            }
            new_node->left_child = nullptr;
            new_node->right_child = nullptr;
            new_node->parent = pos.node;
            pos.node->left_child = new_node;
            return iterator(new_node);
        }
        if(pos.node->right_child) {
            return iterator(pos.node);
        }
        auto new_node {this->node_allocate()};
        if constexpr(is_nothrow_constructible_v<value_type, Args...>) {
            alloc_traits::construct(ds::address_of(new_node->value), ds::forward<Args>(args)...);
        }else {
            try {
                alloc_traits::construct(ds::address_of(new_node->value), ds::forward<Args>(args)...);
            }catch(...) {
                alloc_traits::operator delete(new_node);
                throw;
            }
        }
        new_node->left_child = nullptr;
        new_node->right_child = nullptr;
        new_node->parent = pos.node;
        pos.node->right_child = new_node;
        return iterator(new_node);
    }
    template <typename T, typename Allocator>
    inline void binary_tree<T, Allocator>::push_front(const_reference value, binary_tree::direction direction) {
        this->emplace_front(direction, value);
    }
    template <typename T, typename Allocator>
    inline void binary_tree<T, Allocator>::push_front(rvalue_reference value, binary_tree::direction direction) {
        this->emplace_front(direction, ds::move(value));
    }
    template <typename T, typename Allocator>
    template <typename ...Args>
    void binary_tree<T, Allocator>::emplace_front(binary_tree::direction direction, Args &&...args) {
        auto new_node {this->node_allocate()};
        if constexpr(is_nothrow_constructible_v<value_type, Args...>) {
            alloc_traits::construct(ds::address_of(new_node->value), ds::forward<Args>(args)...);
        }else {
            try {
                alloc_traits::construct(ds::address_of(new_node->value), ds::forward<Args>(args)...);
            }catch(...) {
                alloc_traits::operator delete(new_node);
                throw;
            }
        }
        new_node->parent = nullptr;
        if(this->root) {
            this->root->parent = new_node;
            if(direction == binary_tree::direction::left) {
                new_node->left_child = this->root;
                new_node->right_child = nullptr;
            }else {
                new_node->right_child = this->root;
                new_node->left_child = nullptr;
            }
        }else {
            this->root = new_node;
            this->root->left_child = this->root->right_child = nullptr;
        }
    }
    template <typename T, typename Allocator>
    bool binary_tree<T, Allocator>::rotate(const_iterator pos, binary_tree::direction direction) noexcept {
        if(not pos.node->parent) {
            return false;
        }
        if(direction == binary_tree::direction::left) {
            if(pos.node not_eq pos.node->parent->right_child) {
                return false;
            }
            auto dropped_node {pos.node->left_child}, rotating_node {pos.node->parent};
            auto parent_node {rotating_node->parent};
            pos.node->left_child = rotating_node;
            rotating_node->parent = pos.node;
            rotating_node->right_child = dropped_node;
            dropped_node->parent = rotating_node;
            if(parent_node->left_child == rotating_node) {
                parent_node->left_child = pos.node;
            }else {
                parent_node->right_child = pos.node;
            }
            pos.node->parent = parent_node;
        }else {
            if(pos.node not_eq pos.node->parent->left_child) {
                return false;
            }
            auto dropped_node {pos.node->right_child}, rotating_node {pos.node->parent};
            auto parent_node {rotating_node->parent};
            pos.node->right_child = rotating_node;
            rotating_node->parent = pos.node;
            rotating_node->left_child = dropped_node;
            dropped_node->parent = rotating_node;
            if(parent_node->left_child == rotating_node) {
                parent_node->left_child = pos.node;
            }else {
                parent_node->right_child = pos.node;
            }
            pos.node->parent = parent_node;
        }
        return true;
    }
}

namespace data_structure {
    template <typename T, typename AllocatorLHS, typename AllocatorRHS>
    inline void swap(binary_tree<T, AllocatorLHS> &lhs, binary_tree<T, AllocatorRHS> &rhs) noexcept {
        lhs.swap(rhs);
    }
    template <typename T, typename AllocatorLHS, typename AllocatorRHS>
    bool operator==(const binary_tree<T, AllocatorLHS> &lhs, const binary_tree<T, AllocatorRHS> &rhs)
            noexcept(has_nothrow_equal_to_operator_v<T>) {
        if(lhs.size() not_eq rhs.size()) {
            return false;
        }
        auto lhs_end {lhs.cend()};
        for(auto lhs_cursor {lhs.cbegin()}, rhs_cursor {rhs.cbegin()};; ++lhs_cursor, ++rhs_cursor) {
            if(lhs_cursor == lhs_end) {
                break;
            }
            if(*lhs_cursor not_eq *rhs_cursor) {
                return false;
            }
        }
        return true;
    }
    template <typename T, typename AllocatorLHS, typename AllocatorRHS>
    inline bool operator!=(const binary_tree<T, AllocatorLHS> &lhs, const binary_tree<T, AllocatorRHS> &rhs)
            noexcept(has_nothrow_equal_to_operator_v<T>) {
        return not(lhs == rhs);
    }
}

#endif //DATA_STRUCTURE_BINARY_TREE_HPP
