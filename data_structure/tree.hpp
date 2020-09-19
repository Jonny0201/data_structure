/*
    * Copyright © [2019 - 2020] [Jonny Charlotte]
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

#ifndef DATA_STRUCTURE_TREE_HPP
#define DATA_STRUCTURE_TREE_HPP

#include "queue.hpp"

namespace data_structure {
    template <typename T, typename Allocator = allocator<type_holder<T>>>
    class tree {
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
        using iterator = __dsa::tree_iterator<value_type, false>;
        using const_iterator = __dsa::tree_iterator<value_type, true>;
        using reverse_iterator = void;
        using const_reverse_iterator = add_const_t<void>;
        static_assert(is_same_v<value_type, allocator_traits_t(allocator_type, value_type)>,
                "The tree holds different value_type!");
    private:
        using alloc_traits = allocator_traits<allocator_type>;
        using node_value_type = __dsa::tree_node<value_type>;
        using node_type = node_value_type *;
    public:
        enum class order {
            pre, post, level
        };
    private:
        node_type root;
    private:
        [[nodiscard]]
        static node_type allocate();
        [[nodiscard]]
        static node_type *next_allocate(size_type);
        static void handle_exception(node_type *, size_type, size_type) noexcept;
        static ptrdiff_t locate(node_type, node_type) noexcept;
        static void erase_auxiliary(node_type) noexcept;
        static void copy_to_this(node_type, node_type);
        size_type level_auxiliary(node_type, size_type = 1) const noexcept;
    private:
        void constructor_setting() noexcept(is_nothrow_default_constructible_v<value_type>);
        template <typename Value>
        void constructor_setting(Value &&) noexcept(is_nothrow_constructible_v<value_type, Value>);
        template <typename UnaryPredicate>
        void pre_traversal(UnaryPredicate, node_type)
                noexcept(has_nothrow_function_call_operator_v<UnaryPredicate, reference>);
        template <typename UnaryPredicate>
        void post_traversal(UnaryPredicate, node_type)
                noexcept(has_nothrow_function_call_operator_v<UnaryPredicate, reference>);
        template <typename UnaryPredicate>
        void level_traversal(UnaryPredicate, node_type);
    private:
        explicit tree(node_type) noexcept;
    public:
        tree();
        explicit tree(const_reference);
        explicit tree(rvalue_reference);
        tree(const tree &);
        tree(tree &&) noexcept;
        template <typename AllocatorRHS>
        explicit tree(const tree<value_type, AllocatorRHS> &);
        template <typename AllocatorRHS>
        explicit tree(tree<value_type, AllocatorRHS> &&) noexcept;
        ~tree() noexcept;
    public:
        tree &operator=(const tree &);
        tree &operator=(tree &&) noexcept;
        template <typename AllocatorRHS>
        tree &operator=(const tree<value_type, AllocatorRHS> &);
        template <typename AllocatorRHS>
        tree &operator=(tree<value_type, AllocatorRHS> &&) noexcept;
    public:
        void assign(const_reference) noexcept(is_nothrow_copy_assignable_v<value_type>);
        [[nodiscard]]
        iterator begin() noexcept;
        [[nodiscard]]
        const_iterator begin() const noexcept;
        [[nodiscard]]
        constexpr iterator end() noexcept;
        [[nodiscard]]
        constexpr const_iterator end() const noexcept;
        [[nodiscard]]
        const_iterator cbegin() const noexcept;
        [[nodiscard]]
        constexpr const_iterator cend() const noexcept;
        consteval reverse_iterator rbegin() noexcept;
        consteval const_reverse_iterator rbegin() const noexcept;
        consteval reverse_iterator rend() noexcept;
        consteval const_reverse_iterator rend() const noexcept;
        consteval const_reverse_iterator crbegin() const noexcept;
        consteval const_reverse_iterator crend() const noexcept;
        [[nodiscard]]
        size_type size() const noexcept;
        [[nodiscard]]
        size_type level() const noexcept;
        [[nodiscard]]
        constexpr bool empty() const noexcept;
        [[nodiscard]]
        constexpr size_type max_size() const noexcept;
        [[nodiscard]]
        reference top() noexcept;
        [[nodiscard]]
        const_reference top() const noexcept;
        void swap(tree &) noexcept;
        template <typename AllocatorRHS>
        void swap(tree<value_type, AllocatorRHS> &) noexcept;
        void clear() noexcept;
        template <typename UnaryPredicate>
        void traversal(UnaryPredicate, tree::order = tree::order::level)
                noexcept(has_nothrow_function_call_operator_v<UnaryPredicate, reference>);
        iterator insert_under(const_iterator, const_reference, size_type = 1, difference_type = -1);
        iterator insert_under(const_iterator, rvalue_reference, difference_type = -1);
        template <typename Iterator>
        iterator insert_under(const_iterator, enable_if_t<is_iterator_v<Iterator>, Iterator>,
                Iterator, difference_type = -1);
        iterator insert_under(const_iterator, initializer_list<value_type>, difference_type = -1);
        iterator insert_under(const_iterator, const tree &, difference_type = -1);
        template <typename AllocatorRHS>
        iterator insert_under(const_iterator, const tree<value_type, AllocatorRHS> &, difference_type = -1);
        iterator insert_under(const_iterator, tree &&, difference_type = -1) noexcept;
        template <typename AllocatorRHS>
        iterator insert_under(const_iterator, tree<value_type, AllocatorRHS> &&, difference_type = -1) noexcept;
        iterator erase_under(const_iterator, difference_type = 0, size_type = 1);
        void erase(const_iterator);
        template <typename ...Args>
        iterator emplace_under(const_iterator, Args &&...);
        void push_front(const_reference);
        void push_front(rvalue_reference);
        template <typename ...Args>
        void emplace_front(Args &&...);
        void pop_front();
    };
}

namespace data_structure {
    /* private functions */
    template <typename T, typename Allocator>
    inline typename tree<T, Allocator>::node_type tree<T, Allocator>::allocate() {
        return reinterpret_cast<node_type>(alloc_traits::operator new(sizeof(node_value_type)));
    }
    template <typename T, typename Allocator>
    inline void tree<T, Allocator>::constructor_setting()
            noexcept(is_nothrow_default_constructible_v<value_type>) {
        alloc_traits::construct(ds::address_of(this->root->value));
        this->root->next = this->root->previous = nullptr;
        this->root->next_size = 0;
    }
    template <typename T, typename Allocator>
    inline typename tree<T, Allocator>::node_type *tree<T, Allocator>::next_allocate(size_type size) {
        return reinterpret_cast<node_type *>(alloc_traits::operator new(sizeof(node_type) * size));
    }
    template <typename T, typename Allocator>
    inline void tree<T, Allocator>::handle_exception(node_type *node,
            size_type start, size_type size) noexcept {
        for(auto i {start}; size > 0; ++i, static_cast<void>(--size)) {
            alloc_traits::destroy(ds::address_of(node[i]->value));
            alloc_traits::operator delete(node[i]);
        }
    }
    template <typename T, typename Allocator>
    inline ptrdiff_t tree<T, Allocator>::locate(node_type locate_node, node_type previous) noexcept {
        for(ptrdiff_t i {0}; i < previous->next_size; ++i) {
            if(locate_node == previous->next[i]) {
                return i;
            }
        }
        return -1;
    }
    template <typename T, typename Allocator>
    void tree<T, Allocator>::erase_auxiliary(node_type node) noexcept {
        if(not node) {
            return;
        }
        for(auto i {0}; i < node->next_size; ++i) {
            tree::erase_auxiliary(node->next[i]);
        }
        alloc_traits::destroy(ds::address_of(node->value));
        alloc_traits::operator delete(node->next);
        alloc_traits::operator delete(node);
    }
    template <typename T, typename Allocator>
    void tree<T, Allocator>::copy_to_this(node_type copy, node_type to) {
        if(not copy->next) {
            to->next = nullptr;
            to->next_size = 0;
            return;
        }
        to->next = tree::next_allocate(copy->next_size);
        for(auto i {0}; i < copy->next_size; ++i) {
            try {
                to->next[i] = tree::allocate();
            }catch(...) {
                tree::handle_exception(to->next, 0, i);
                alloc_traits::operator delete(to->next);
                to->next_size = 0;
                throw;
            }
            if constexpr(is_nothrow_copy_constructible_v<value_type>) {
                alloc_traits::construct(ds::address_of(to->next[i]->value), copy->next[i]->value);
            }else {
                try {
                    alloc_traits::construct(ds::address_of(to->next[i]->value), copy->next[i]->value);
                }catch(...) {
                    alloc_traits::operator delete(to->next[i]);
                    tree::handle_exception(to->next, 0, i);
                    alloc_traits::operator delete(to->next);
                    to->next_size = 0;
                    throw;
                }
            }
            to->next[i]->previous = copy;
        }
        for(auto i {0}; i < copy->next_size; ++i) {
            try {
                tree::copy_to_this(copy->next[i], to->next[i]);
            }catch(...) {
                for(auto j {i}; j < copy->next_size; ++j) {
                    to->next[j] = nullptr;
                    to->next_size = 0;
                }
                throw;
            }
        }
        to->next_size = copy->next_size;
    }
    template <typename T, typename Allocator>
    typename tree<T, Allocator>::size_type tree<T, Allocator>::level_auxiliary(
            node_type root, size_type level) const noexcept {
        size_type r {level};
        if(root->next) {
            for(auto i {0}; i < root->next_size; ++i) {
                if(const auto next_level {tree::level_auxiliary(root->next[i], level + 1)};
                        next_level > r) {
                    r = next_level;
                }
            }
        }
        return r;
    }
    template <typename T, typename Allocator>
    template <typename Value>
    inline void tree<T, Allocator>::constructor_setting(Value &&value)
            noexcept(is_nothrow_constructible_v<value_type, Value>) {
        alloc_traits::construct(ds::address_of(this->root->value), ds::forward<Value>(value));
        this->root->next = nullptr;
        this->root->previous = nullptr;
        this->root->next_size = 0;
    }
    template <typename T, typename Allocator>
    template <typename UnaryPredicate>
    void tree<T, Allocator>::pre_traversal(UnaryPredicate pred, node_type node)
            noexcept(has_nothrow_function_call_operator_v<UnaryPredicate, reference>) {
        pred(node->value);
        for(auto i {0}; i < node->next_size; ++i) {
            if(node->next[i]) {
                pre_traversal<add_lvalue_reference_t<UnaryPredicate>>(pred, node->next[i]);
            }
        }
    }
    template <typename T, typename Allocator>
    template <typename UnaryPredicate>
    void tree<T, Allocator>::post_traversal(UnaryPredicate pred, node_type node)
            noexcept(has_nothrow_function_call_operator_v<UnaryPredicate, reference>) {
        for(auto i {0}; i < node->next_size; ++i) {
            if(node->next[i]) {
                post_traversal<add_lvalue_reference_t<UnaryPredicate>>(pred, node->next[i]);
            }
        }
        pred(node->value);
    }
    template <typename T, typename Allocator>
    template <typename UnaryPredicate>
    void tree<T, Allocator>::level_traversal(UnaryPredicate pred, node_type node) {
        queue<node_type> q;
        q.push(node);
        while(not q.empty()) {
            auto &front {q.front()};
            pred(front->value);
            for(auto i {0}; i < front->next_size; ++i) {
                q.push(front->next[i]);
            }
            q.pop();
        }
    }
    template <typename T, typename Allocator>
    inline tree<T, Allocator>::tree(node_type node) noexcept : root {node} {}

    /* public functions */
    template <typename T, typename Allocator>
    inline tree<T, Allocator>::tree() : root {this->allocate()} {
        this->constructor_setting();
    }
    template <typename T, typename Allocator>
    inline tree<T, Allocator>::tree(const_reference value) : root {this->allocate()} {
        this->constructor_setting(value);
    }
    template <typename T, typename Allocator>
    inline tree<T, Allocator>::tree(rvalue_reference value) : root {this->allocate()} {
        this->constructor_setting(ds::move(value));
    }
    template <typename T, typename Allocator>
    tree<T, Allocator>::tree(const tree &rhs) : root {this->allocate()} {
        this->constructor_setting(rhs.top());
        this->copy_to_this(rhs.root, this->root);
    }
    template <typename T, typename Allocator>
    inline tree<T, Allocator>::tree(tree &&rhs) noexcept : root {rhs.root} {
        rhs.root = nullptr;
    }
    template <typename T, typename Allocator>
    template <typename AllocatorRHS>
    inline tree<T, Allocator>::tree(const tree<value_type, AllocatorRHS> &rhs) :
            tree(*reinterpret_cast<const tree *>(&rhs)) {}
    template <typename T, typename Allocator>
    template <typename AllocatorRHS>
    inline tree<T, Allocator>::tree(tree<value_type, AllocatorRHS> &&rhs) noexcept : root {rhs.root} {
        rhs.root = nullptr;
    }
    template <typename T, typename Allocator>
    inline tree<T, Allocator>::~tree() noexcept {
        this->erase_auxiliary(this->root);
    }
    template <typename T, typename Allocator>
    tree<T, Allocator> &tree<T, Allocator>::operator=(const tree &rhs) {
        if(&rhs == this) {
            return *this;
        }
        this->erase_under(this->cbegin(), 0, this->root->next_size);
        this->root->value = rhs.root->value;
        alloc_traits::operator delete(this->root->next);
        this->copy_to_this(rhs.root, this->root);
        return *this;
    }
    template <typename T, typename Allocator>
    inline tree<T, Allocator> &tree<T, Allocator>::operator=(tree &&rhs) noexcept {
        if(&rhs == this) {
            return *this;
        }
        this->~tree();
        this->root = rhs.root;
        rhs.root = nullptr;
        return *this;
    }
    template <typename T, typename Allocator>
    template <typename AllocatorRHS>
    tree<T, Allocator> &tree<T, Allocator>::operator=(const tree<value_type, AllocatorRHS> &rhs) {
        this->erase_under(this->cbegin(), 0, this->root->next_size);
        this->root->value = rhs.root->value;
        alloc_traits::operator delete(this->root->next);
        this->copy_to_this(rhs.root, this->root);
        return *this;
    }
    template <typename T, typename Allocator>
    template <typename AllocatorRHS>
    inline tree<T, Allocator> &tree<T, Allocator>::operator=(tree<value_type, AllocatorRHS> &&rhs) noexcept {
        this->~tree();
        this->root = rhs.root;
        rhs.root = nullptr;
        return *this;
    }
    template <typename T, typename Allocator>
    inline void tree<T, Allocator>::assign(const_reference value)
            noexcept(is_nothrow_copy_assignable_v<value_type>) {
        this->traversal([&value](reference v) noexcept(is_nothrow_copy_assignable_v<value_type>) -> void {
            v = value;
        });
    }
    template <typename T, typename Allocator>
    inline typename tree<T, Allocator>::iterator tree<T, Allocator>::begin() noexcept {
        return iterator(this->root);
    }
    template <typename T, typename Allocator>
    inline typename tree<T, Allocator>::const_iterator tree<T, Allocator>::begin() const noexcept {
        return const_iterator(this->root);
    }
    template <typename T, typename Allocator>
    inline constexpr typename tree<T, Allocator>::iterator tree<T, Allocator>::end() noexcept {
        return {};
    }
    template <typename T, typename Allocator>
    inline constexpr typename tree<T, Allocator>::const_iterator tree<T, Allocator>::end() const noexcept {
        return {};
    }
    template <typename T, typename Allocator>
    inline typename tree<T, Allocator>::const_iterator tree<T, Allocator>::cbegin() const noexcept {
        return const_iterator(this->root);
    }
    template <typename T, typename Allocator>
    inline constexpr typename tree<T, Allocator>::const_iterator tree<T, Allocator>::cend() const noexcept {
        return {};
    }
    template <typename T, typename Allocator>
    inline consteval typename tree<T, Allocator>::reverse_iterator tree<T, Allocator>::rbegin() noexcept {
        static_assert(not is_type_v<value_type>, "There is no any reverse iterator for tree!");
    }
    template <typename T, typename Allocator>
    inline consteval typename tree<T, Allocator>::const_reverse_iterator
    tree<T, Allocator>::rbegin() const noexcept {
        static_assert(not is_type_v<value_type>, "There is no any reverse iterator for tree!");
    }
    template <typename T, typename Allocator>
    inline consteval typename tree<T, Allocator>::reverse_iterator tree<T, Allocator>::rend() noexcept {
        static_assert(not is_type_v<value_type>, "There is no any reverse iterator for tree!");
    }
    template <typename T, typename Allocator>
    inline consteval typename tree<T, Allocator>::const_reverse_iterator
    tree<T, Allocator>::rend() const noexcept {
        static_assert(not is_type_v<value_type>, "There is no any reverse iterator for tree!");
    }
    template <typename T, typename Allocator>
    inline consteval typename tree<T, Allocator>::const_reverse_iterator
    tree<T, Allocator>::crbegin() const noexcept {
        static_assert(not is_type_v<value_type>, "There is no any reverse iterator for tree!");
    }
    template <typename T, typename Allocator>
    inline consteval typename tree<T, Allocator>::const_reverse_iterator
    tree<T, Allocator>::crend() const noexcept {
        static_assert(not is_type_v<value_type>, "There is no any reverse iterator for tree!");
    }
    template <typename T, typename Allocator>
    inline typename tree<T, Allocator>::size_type tree<T, Allocator>::size() const noexcept {
        size_type size {0};
        this->traversal([&size](reference) mutable noexcept -> void {
            ++size;
        });
        return size;
    }
    template <typename T, typename Allocator>
    inline typename tree<T, Allocator>::size_type tree<T, Allocator>::level() const noexcept {
        return this->level_auxiliary(this->root);
    }
    template <typename T, typename Allocator>
    inline constexpr bool tree<T, Allocator>::empty() const noexcept {
        return false;
    }
    template <typename T, typename Allocator>
    inline constexpr typename tree<T, Allocator>::size_type tree<T, Allocator>::max_size() const noexcept {
        return std::numeric_limits<size_type>::max() / sizeof(node_value_type);
    }
    template <typename T, typename Allocator>
    inline typename tree<T, Allocator>::reference tree<T, Allocator>::top() noexcept {
        return this->root->value;
    }
    template <typename T, typename Allocator>
    inline typename tree<T, Allocator>::const_reference tree<T, Allocator>::top() const noexcept {
        return this->root->value;
    }
    template <typename T, typename Allocator>
    inline void tree<T, Allocator>::swap(tree &rhs) noexcept {
        ds::swap(this->root, rhs.root);
    }
    template <typename T, typename Allocator>
    template <typename AllocatorRHS>
    inline void tree<T, Allocator>::swap(tree<value_type, AllocatorRHS> &rhs) noexcept {
        ds::swap(this->root, rhs.root);
    }
    template <typename T, typename Allocator>
    inline void tree<T, Allocator>::clear() noexcept {
        this->erase_under(this->cbegin(), 0, this->root->next_size);
    }
    template <typename T, typename Allocator>
    template <typename UnaryPredicate>
    inline void tree<T, Allocator>::traversal(UnaryPredicate pred, tree::order order)
            noexcept(has_nothrow_function_call_operator_v<UnaryPredicate, reference>) {
        switch(order) {
            case tree::order::pre:
                this->pre_traversal<add_lvalue_reference_t<UnaryPredicate>>(pred, this->root);
                break;
            case tree::order::post:
                this->post_traversal<add_lvalue_reference_t<UnaryPredicate>>(pred, this->root);
                break;
            case tree::order::level:
                this->level_traversal<add_lvalue_reference_t<UnaryPredicate>>(pred, this->root);
                break;
            default:
                break;
        }
    }
    template <typename T, typename Allocator>
    typename tree<T, Allocator>::iterator tree<T, Allocator>::insert_under(const_iterator parent,
            const_reference value, size_type size, difference_type pos) {
        if(not parent) {
            return this->end();
        }
        const auto new_size {parent.node->next_size + size};
        auto next {this->next_allocate(new_size)};
        if(pos == -1) {
            ds::memory_copy(next, parent.node->next, sizeof(node_type) * parent.node->next_size);
        }else {
            ds::memory_copy(next, parent.node->next, sizeof(node_type) * pos);
            ds::memory_copy(next + (pos + size), parent.node->next + pos,
                    sizeof(node_type) * (parent.node->next_size - pos));
        }
        for(auto i {0}; i < size; ++i) {
            node_type new_node;
            try {
                new_node = this->allocate();
            }catch(...) {
                this->handle_exception(next, pos, i);
                alloc_traits::operator delete(next);
                throw;
            }
            if constexpr(is_nothrow_copy_constructible_v<value_type>) {
                alloc_traits::construct(ds::address_of(new_node->value), value);
            }else {
                try {
                    alloc_traits::construct(ds::address_of(new_node->value), value);
                }catch(...) {
                    this->handle_exception(next, pos, i);
                    alloc_traits::operator delete(new_node);
                    alloc_traits::operator delete(next);
                    throw;
                }
            }
            next[pos + i] = new_node;
            new_node->previous = parent.node;
            new_node->next = nullptr;
            new_node->next_size = 0;
        }
        alloc_traits::operator delete(parent.node->next);
        parent.node->next = next;
        parent.node->next_size = new_size;
        return iterator(next[pos]);
    }
    template <typename T, typename Allocator>
    inline typename tree<T, Allocator>::iterator tree<T, Allocator>::insert_under(
            const_iterator parent, rvalue_reference value, difference_type pos) {
        return this->emplace_under(parent, pos, ds::move(value));
    }
    template <typename T, typename Allocator>
    template <typename Iterator>
    typename tree<T, Allocator>::iterator tree<T, Allocator>::insert_under(const_iterator parent,
            enable_if_t<is_iterator_v<Iterator>, Iterator> begin, Iterator end, difference_type pos) {
        if(not parent) {
            return this->end();
        }
        const auto old_size {parent.node->next_size};
        if constexpr(is_forward_iterator_v<Iterator>) {
            const auto size {ds::distance(begin, end)};
            const auto new_size {parent.node->next_size + size};
            auto next {this->next_allocate(new_size)};
            if(pos == -1) {
                ds::memory_copy(next, parent.node->next, sizeof(node_type) * parent.node->next_size);
            }else {
                ds::memory_copy(next, parent.node->next, sizeof(node_type) * pos);
                ds::memory_copy(next + (pos + size), parent.node->next + pos,
                                sizeof(node_type) * (parent.node->next_size - pos));
            }
            for(auto i {0}; i < size; ++i) {
                node_type new_node;
                try {
                    new_node = this->allocate();
                }catch(...) {
                    this->handle_exception(next, pos, i);
                    alloc_traits::operator delete(next);
                    throw;
                }
                if constexpr(is_nothrow_copy_constructible_v<value_type>) {
                    alloc_traits::construct(ds::address_of(new_node->value), *begin++);
                }else {
                    try {
                        alloc_traits::construct(ds::address_of(new_node->value), *begin++);
                    }catch(...) {
                        this->handle_exception(next, pos, i);
                        alloc_traits::operator delete(new_node);
                        alloc_traits::operator delete(next);
                        throw;
                    }
                }
                if(pos == -1) {
                    next[parent.node->next_size + i] = new_node;
                }else {
                    next[pos + i] = new_node;
                }
                new_node->previous = parent.node;
                new_node->next = nullptr;
                new_node->next_size = 0;
            }
            alloc_traits::operator delete(parent.node->next);
            parent.node->next = next;
            parent.node->next_size = new_size;
        }else {
            while(begin not_eq end) {
                this->emplace_under(parent, pos, ds::move(*begin++));
            }
        }
        if(pos == -1) {
            return iterator(parent.node->next[old_size]);
        }
        return iterator(parent.node->next[pos]);
    }
    template <typename T, typename Allocator>
    inline typename tree<T, Allocator>::iterator tree<T, Allocator>::insert_under(const_iterator parent,
            initializer_list<value_type> init_list, difference_type pos) {
        return this->insert_under(parent, init_list.begin(), init_list.end(), pos);
    }
    template <typename T, typename Allocator>
    inline typename tree<T, Allocator>::iterator tree<T, Allocator>::insert_under(const_iterator parent,
            const tree &rhs, difference_type pos) {
        auto tmp {rhs};
        return this->insert_under(parent, ds::move(tmp), pos);
    }
    template <typename T, typename Allocator>
    typename tree<T, Allocator>::iterator tree<T, Allocator>::insert_under(const_iterator parent,
            tree &&rhs, difference_type pos) noexcept {
        if(not parent) {
            return this->end();
        }
        auto next {this->next_allocate(parent.node->next_size + 1)};
        if(pos == -1) {
            ds::memory_copy(next, parent.node, sizeof(node_type) * parent.node->next_size);
            next[parent.node->next_size] = rhs.root;
        }else {
            ds::memory_copy(next, parent.node, sizeof(node_type) * pos);
            ds::memory_copy(next + (pos + 1), parent.node + pos,
                    sizeof(node_type) * parent.node->next_size - pos);
            next[pos] = rhs.root;
        }
        rhs.root = nullptr;
        ++parent.node->next_size;
        return iterator(next[pos]);
    }
    template <typename T, typename Allocator>
    template <typename AllocatorRHS>
    inline typename tree<T, Allocator>::iterator tree<T, Allocator>::insert_under(const_iterator parent,
            const tree<value_type, AllocatorRHS> &rhs, difference_type pos) {
        return this->insert_under(parent, *reinterpret_cast<const tree *>(&rhs), pos);
    }
    template <typename T, typename Allocator>
    template <typename AllocatorRHS>
    inline typename tree<T, Allocator>::iterator tree<T, Allocator>::insert_under(const_iterator parent,
            tree<value_type, AllocatorRHS> &&rhs, difference_type pos) noexcept {
        return this->insert_under(parent, ds::move(*reinterpret_cast<tree *>(&rhs)), pos);
    }
    template <typename T, typename Allocator>
    typename tree<T, Allocator>::iterator tree<T, Allocator>::erase_under(
            const_iterator parent, difference_type pos, size_type size) {
        if(not parent or pos >= parent.node->next_size) {
            return this->end();
        }
        if(pos == 0 and size >= parent.node->next_size) {
            for(auto i {0}; i < parent.node->next_size; ++i) {
                this->erase_auxiliary(parent.node->next[i]);
            }
            parent.node->next_size = 0;
            alloc_traits::operator delete(parent.node->next);
            parent.node->next = nullptr;
            return this->end();
        }
        if(pos + size > parent.node->next_size) {
            auto next {this->next_allocate(pos)};
            ds::memory_copy(next, parent.node->next + pos, sizeof(node_type) * pos);
            for(auto i {pos}; i < parent.node->next_size; ++i) {
                this->erase_auxiliary(parent.node->next[i]);
            }
            alloc_traits::operator delete(parent.node->next);
            parent.node->next = next;
            parent.node->next_size = pos;
            return this->end();
        }
        const auto new_size {parent.node->next_size - size};
        auto next {this->next_allocate(new_size)};
        ds::memory_copy(next, parent.node->next, sizeof(node_type) * pos);
        const auto disconnexion_start {static_cast<ptrdiff_t>(pos + size)};
        ds::memory_copy(next + pos, parent.node->next + disconnexion_start,
                sizeof(node_type) * (parent.node->next_size - disconnexion_start));
        for(auto i {pos}; size > 0; --size) {
            this->erase_auxiliary(parent.node->next[i++]);
        }
        alloc_traits::operator delete(parent.node->next);
        parent.node->next = next;
        parent.node->next_size = new_size;
        return iterator(next[pos]);
    }
    template <typename T, typename Allocator>
    void tree<T, Allocator>::erase(const_iterator pos) {
        if(not pos or pos == this->cbegin()) {
            return;
        }
        const auto size {pos.node->previous->next_size};
        if(size > 1) {
            auto next {this->next_allocate(size - 1)};
            const auto position {this->locate(pos.node, pos.node->previous)};
            ds::memory_copy(next, pos.node->previous->next, position * sizeof(node_type));
            ds::memory_copy(next + position, pos.node->previous->next + (position + 1),
                    (pos.node->previous->next_size - (position + 1)) * sizeof(node_type));
            alloc_traits::operator delete(pos.node->previous->next);
            pos.node->previous->next = next;
        }else {
            alloc_traits::operator delete(pos.node->previous->next);
            pos.node->previous->next = nullptr;
        }
        --pos.node->previous->next_size;
        this->erase_auxiliary(pos.node);
    }
    template <typename T, typename Allocator>
    template <typename ...Args>
    inline typename tree<T, Allocator>::iterator tree<T, Allocator>::emplace_under(
            const_iterator parent, Args &&...args) {
        if(not parent) {
            return this->end();
        }
        auto next {this->next_allocate(parent.node->next_size + 1)};
        ds::memory_copy(next + 1, parent.node->next, sizeof(node_type) * parent.node->next_size);
        try {
            next[0] = this->allocate();
        }catch(...) {
            alloc_traits::operator delete(next);
            throw;
        }
        if constexpr(is_nothrow_move_constructible_v<value_type>) {
            alloc_traits::constrct(ds::address_of(next[0]->value), ds::forward<Args>(args)...);
        }else {
            try {
                alloc_traits::constrct(ds::address_of(next[0]->value), ds::forward<Args>(args)...);
            }catch(...) {
                alloc_traits::operator delete(next[0]);
                alloc_traits::operator delete(next);
                throw;
            }
        }
        next[0]->previous = parent.node;
        next[0]->next = nullptr;
        next[0]->next_size = 0;
        alloc_traits::operator delete(parent.node->next);
        parent.node->next = next;
        ++parent.node->next_size;
        return iterator(next[0]);
    }
    template <typename T, typename Allocator>
    inline void tree<T, Allocator>::push_front(const_reference value) {
        this->emplace_under(this->cbegin(), value);
    }
    template <typename T, typename Allocator>
    inline void tree<T, Allocator>::push_front(rvalue_reference value) {
        this->emplace_under(this->cbegin(), ds::move(value));
    }
    template <typename T, typename Allocator>
    template <typename ...Args>
    inline void tree<T, Allocator>::emplace_front(Args &&...args) {
        this->emplace_under(this->cbegin(), ds::forward<Args>(args)...);
    }
    template <typename T, typename Allocator>
    inline void tree<T, Allocator>::pop_front() {
        auto erase_node {this->cbegin()};
        this->erase(++erase_node);
    }
}

#endif //DATA_STRUCTURE_TREE_HPP
