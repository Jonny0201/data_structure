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

#ifndef DATA_STRUCTURE_ITERATOR_HPP
#define DATA_STRUCTURE_ITERATOR_HPP

#include "type_traits.hpp"
#include "memory.hpp"

__DATA_STRUCTURE_START(iterator tag)
namespace data_structure {
    struct iterator_tag {};
    struct output_iterator_tag : iterator_tag {};
    struct input_iterator_tag : iterator_tag {};
    struct forward_iterator_tag : input_iterator_tag {};
    struct bidirectional_iterator_tag : forward_iterator_tag {};
    struct random_access_iterator_tag : bidirectional_iterator_tag {};
}
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(iterator traits)
namespace data_structure {
    template <typename Iterator>
    struct iterator_traits {
        using size_type = typename Iterator::size_type;
        using difference_type = typename Iterator::difference_type;
        using value_type = typename Iterator::value_type;
        using reference = typename Iterator::reference;
        using const_reference = typename Iterator::const_reference;
        using rvalue_reference = typename Iterator::rvalue_reference;
        using pointer = typename Iterator::pointer;
        using const_pointer = typename Iterator::const_pointer;
        using iterator_category = typename Iterator::iterator_category;
    };
    template <typename T>
    struct iterator_traits<T *> {
        using size_type = size_t;
        using difference_type = ptrdiff_t;
        using value_type = T;
        using reference = add_lvalue_reference_t<value_type>;
        using const_reference = add_const_reference_t<value_type>;
        using rvalue_reference = add_rvalue_reference_t<value_type>;
        using pointer = add_pointer_t<value_type>;
        using const_pointer = add_const_pointer_t<value_type>;
        using iterator_category = random_access_iterator_tag;
    };

    /* TODO : refactor it by modules in C++ 20 */
    #define iterator_traits_t(type, trait_name) typename iterator_traits<type>::trait_name

    namespace __data_structure_auxiliary {
        template <bool, typename T, typename = void>
        struct has_iterator_category_impl : false_type {
            using is_iterator = false_type;
            using is_input_iterator = false_type;
            using is_output_iterator = false_type;
            using is_forward_iterator = false_type;
            using is_bidirectional_iterator = false_type;
            using is_random_access_iterator = false_type;
        };
        template <typename T>
        struct has_iterator_category_impl<false, T, void_t<typename T::iterator_category>> : true_type {
            using is_iterator = is_base_of<iterator_tag, typename T::iterator_category>;
            using is_input_iterator = is_base_of<input_iterator_tag, typename T::iterator_category>;
            using is_output_iterator = is_same<output_iterator_tag, typename T::iterator_category>;
            using is_forward_iterator = is_base_of<forward_iterator_tag, typename T::iterator_category>;
            using is_bidirectional_iterator =
            is_base_of<bidirectional_iterator_tag, typename T::iterator_category>;
            using is_random_access_iterator =
            is_base_of<random_access_iterator_tag, typename T::iterator_category>;
        };
        template <typename T>
        struct has_iterator_category_impl<true, T, void> : true_type {
            using is_iterator = true_type;
            using is_input_iterator = true_type;
            using is_output_iterator = true_type;
            using is_forward_iterator = true_type;
            using is_bidirectional_iterator = true_type;
            using is_random_access_iterator = true_type;
        };
    }

    template <typename T>
    struct has_iterator_category : __dsa::has_iterator_category_impl<is_pointer_v<T>, T> {};
    template <typename T>
    constexpr inline auto has_iterator_category_v {has_iterator_category<T>::value};

    template <typename T>
    struct is_iterator : __dsa::has_iterator_category_impl<is_pointer_v<T>, T> {};
    template <typename T>
    constexpr inline auto is_iterator_v {is_iterator<T>::value};

    template <typename T>
    struct is_output_iterator :
            __dsa::has_iterator_category_impl<is_pointer_v<T>, T>::is_output_iterator {};
    template <typename T>
    constexpr inline auto is_output_iterator_v {is_output_iterator<T>::value};

    template <typename T>
    struct is_input_iterator :
            __dsa::has_iterator_category_impl<is_pointer_v<T>, T>::is_input_iterator {};
    template <typename T>
    constexpr inline auto is_input_iterator_v {is_input_iterator<T>::value};

    template <typename T>
    struct is_forward_iterator :
            __dsa::has_iterator_category_impl<is_pointer_v<T>, T>::is_forward_iterator {};
    template <typename T>
    constexpr inline auto is_forward_iterator_v {is_forward_iterator<T>::value};

    template <typename T>
    struct is_bidirectional_iterator :
            __dsa::has_iterator_category_impl<is_pointer_v<T>, T>::is_bidirectional_iterator {};
    template <typename T>
    constexpr inline auto is_bidirectional_iterator_v {is_bidirectional_iterator<T>::value};

    template <typename T>
    struct is_random_access_iterator :
            __dsa::has_iterator_category_impl<is_pointer_v<T>, T>::is_random_access_iterator {};
    template <typename T>
    constexpr inline auto is_random_access_iterator_v {is_random_access_iterator<T>::value};
}
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(wrap_iterator)
namespace data_structure {
    template <typename Iterator>
    class wrap_iterator {
    public:
        using iterator_type = Iterator;
        using size_type = iterator_traits_t(iterator_type, size_type);
        using difference_type = iterator_traits_t(iterator_type, difference_type);
        using value_type = iterator_traits_t(iterator_type, value_type);
        using reference = iterator_traits_t(iterator_type, reference);
        using const_reference = iterator_traits_t(iterator_type, const_reference);
        using rvalue_reference = iterator_traits_t(iterator_type, rvalue_reference);
        using pointer = iterator_traits_t(iterator_type, pointer);
        using const_pointer = iterator_traits_t(iterator_type, const_pointer);
        using iterator_category = iterator_traits_t(iterator_type, iterator_category);
        static_assert(is_pointer<iterator_type>::value,
                "The class template wrap_iterator is only available for pointer type!");
    private:
        iterator_type iter;
    private:
        template <typename IteratorRHS>
        explicit constexpr wrap_iterator(const wrap_iterator<IteratorRHS> &rhs,
                enable_if_t<is_nothrow_convertible_v<IteratorRHS, iterator_type>> *)
                noexcept : iter {rhs.base()} {}
        template <typename IteratorRHS>
        constexpr wrap_iterator &operator_assignment_auxiliary(const wrap_iterator<IteratorRHS> &rhs,
                enable_if_t<is_nothrow_convertible_v<IteratorRHS, iterator_type>> *)
                noexcept {
            this->iter = rhs.base();
            return *this;
        }
    public:
        constexpr wrap_iterator() noexcept = default;
        explicit constexpr wrap_iterator(iterator_type iterator) noexcept : iter {iterator} {}
        template <typename IteratorRHS>
        constexpr wrap_iterator(const wrap_iterator<IteratorRHS> &rhs)
                noexcept : wrap_iterator(rhs, nullptr) {}
        constexpr wrap_iterator(const wrap_iterator &) noexcept = default;
        constexpr wrap_iterator(wrap_iterator &&) noexcept = default;
        ~wrap_iterator() noexcept = default;
    public:
        constexpr wrap_iterator &operator=(const wrap_iterator &) noexcept = default;
        constexpr wrap_iterator &operator=(wrap_iterator &&) noexcept = default;
        template <typename IteratorRHS>
        constexpr wrap_iterator &operator=(const wrap_iterator<IteratorRHS> &rhs) noexcept {
            return this->operator_assignment_auxiliary(rhs, nullptr);
        }
        reference operator*() noexcept {
            return *this->iter;
        }
        pointer operator->() noexcept {
            return ds::address_of(**this);
        }
        reference operator[](difference_type n) noexcept {
            return *(this->iter + n);
        };
        wrap_iterator &operator++() & noexcept {
            ++this->iter;
            return *this;
        }
        wrap_iterator operator++(int) & noexcept {
            auto backup {*this};
            ++*this;
            return backup;
        }
        wrap_iterator &operator--() & noexcept {
            --this->iter;
            return *this;
        }
        wrap_iterator operator--(int) & noexcept {
            auto backup {*this};
            --*this;
            return backup;
        }
        wrap_iterator &operator+=(difference_type n) & noexcept {
            this->iter += n;
            return *this;
        }
        wrap_iterator &operator-=(difference_type n) & noexcept {
            return *this += -n;
        }
        wrap_iterator operator+(difference_type n) noexcept {
            auto backup {*this};
            return backup += n;
        }
        wrap_iterator operator-(difference_type n) noexcept {
            return *this + -n;
        }
        explicit operator bool() const noexcept {
            return static_cast<bool>(this->iter);
        }
    public:
        iterator_type base() const noexcept {
            return this->iter;
        }
    };
    template <typename IteratorLHS, typename IteratorRHS = IteratorLHS>
    inline auto operator-(const wrap_iterator<IteratorLHS> &lhs,
            const wrap_iterator<IteratorRHS> &rhs) noexcept -> decltype(lhs.base() - rhs.base()) {
        return lhs.base() - rhs.base();
    }
    template <typename IteratorLHS, typename IteratorRHS = IteratorLHS>
    inline bool operator==(const wrap_iterator<IteratorLHS> &lhs,
            const wrap_iterator<IteratorRHS> &rhs) noexcept {
        return lhs.base() == rhs.base();
    }
    template <typename IteratorLHS, typename IteratorRHS = IteratorLHS>
    inline bool operator!=(const wrap_iterator<IteratorLHS> &lhs,
            const wrap_iterator<IteratorRHS> &rhs) noexcept {
        return not(lhs == rhs);
    }
    template <typename IteratorLHS, typename IteratorRHS = IteratorLHS>
    inline bool operator<(const wrap_iterator<IteratorLHS> &lhs,
            const wrap_iterator<IteratorRHS> &rhs) noexcept {
        return lhs.base() - rhs.base() < 0;
    }
    template <typename IteratorLHS, typename IteratorRHS = IteratorLHS>
    inline bool operator>(const wrap_iterator<IteratorLHS> &lhs,
            const wrap_iterator<IteratorRHS> &rhs) noexcept {
        return rhs < lhs;
    }
    template <typename IteratorLHS, typename IteratorRHS = IteratorLHS>
    inline bool operator<=(const wrap_iterator<IteratorLHS> &lhs,
            const wrap_iterator<IteratorRHS> &rhs) noexcept {
        return not(lhs > rhs);
    }
    template <typename IteratorLHS, typename IteratorRHS = IteratorLHS>
    inline bool operator>=(const wrap_iterator<IteratorLHS> &lhs,
            const wrap_iterator<IteratorRHS> &rhs) noexcept {
        return not(lhs < rhs);
    }
}
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(reverse_iterator)
namespace data_structure {
    template <typename Iterator>
    class reverse_iterator {
    public:
        using iterator_type = Iterator;
        using size_type = iterator_traits_t(iterator_type, size_type);
        using difference_type = iterator_traits_t(iterator_type, difference_type);
        using value_type = iterator_traits_t(iterator_type, value_type);
        using reference = iterator_traits_t(iterator_type, reference);
        using const_reference = iterator_traits_t(iterator_type, const_reference);
        using rvalue_reference = iterator_traits_t(iterator_type, rvalue_reference);
        using pointer = iterator_traits_t(iterator_type, pointer);
        using const_pointer = iterator_traits_t(iterator_type, const_pointer);
        using iterator_category = iterator_traits_t(iterator_type, iterator_category);
        static_assert(is_bidirectional_iterator_v<iterator_type>,
                "The template argument must be at least a bidirectional iterator!");
    private:
        iterator_type iter;
    private:
        template <typename IteratorRHS>
        constexpr reverse_iterator(const reverse_iterator<IteratorRHS> &rhs,
                enable_if_t<is_convertible_v<IteratorRHS, iterator_type>> *)
                noexcept(is_nothrow_constructible_v<IteratorRHS, iterator_type>) : iter {rhs.base()} {}
        template <typename IteratorRHS>
        constexpr reverse_iterator &operator_assignment_auxiliary(const reverse_iterator<IteratorRHS> &rhs,
                enable_if_t<is_convertible_v<IteratorRHS, iterator_type>> *)
                noexcept(is_nothrow_assignable_v<IteratorRHS, iterator_type>) {
            this->iter = rhs.base();
            return *this;
        }
    public:
        constexpr reverse_iterator() = default;
        explicit constexpr reverse_iterator(iterator_type iterator)
                noexcept(is_nothrow_copy_constructible_v<iterator_type>) : iter {iterator} {}
        template <typename IteratorRHS>
        explicit constexpr reverse_iterator(const reverse_iterator<IteratorRHS> &rhs)
                noexcept(is_nothrow_constructible_v<iterator_type, IteratorRHS>) :
                reverse_iterator(rhs, nullptr) {}
        constexpr reverse_iterator(const reverse_iterator &) = default;
        constexpr reverse_iterator(reverse_iterator &&) = default;
        ~reverse_iterator() noexcept = default;
    public:
        constexpr reverse_iterator &operator=(const reverse_iterator &) = default;
        constexpr reverse_iterator &operator=(reverse_iterator &&) = default;
        template <typename IteratorRHS>
        constexpr reverse_iterator &operator=(const reverse_iterator<IteratorRHS> &rhs)
                noexcept(is_nothrow_assignable_v<iterator_type, IteratorRHS>) {
            return this->operator_assignment_auxiliary(rhs, nullptr);
        }
    public:
        reference operator*() noexcept(has_nothrow_dereference_operator_v<iterator_type>) {
            return *this->iter;
        }
        pointer operator->() noexcept(has_nothrow_dereference_operator_v<iterator_type>) {
            return const_cast<pointer>(ds::address_of(**this));
        }
        enable_if_t<is_random_access_iterator_v<iterator_type>, reference> operator[](difference_type n)
                noexcept(has_nothrow_subscript_operator_v<iterator_type>) {
            return this->iter[n];
        }
        reverse_iterator &operator++() & noexcept(has_nothrow_pre_increment_operator_v<iterator_type>) {
            --this->iter;
            return *this;
        }
        reverse_iterator operator++(int) & noexcept(has_nothrow_post_increment_operator_v<iterator_type>) {
            auto backup {*this};
            --this->iter;
            return backup;
        }
        reverse_iterator &operator--() & noexcept(has_nothrow_pre_decrement_operator_v<iterator_type>) {
            ++this->iter;
            return *this;
        }
        reverse_iterator operator--(int) & noexcept(has_nothrow_post_decrement_operator_v<iterator_type>) {
            auto backup {*this};
            ++this->iter;
            return backup;
        }
        enable_if_t<is_random_access_iterator_v<iterator_type>, reverse_iterator &>
        operator+=(difference_type n) & noexcept(
                has_nothrow_minus_assignment_operator_v<iterator_type, difference_type>) {
            this->iter -= n;
            return *this;
        }
        enable_if_t<is_random_access_iterator_v<iterator_type>, reverse_iterator &>
        operator-=(difference_type n) & noexcept(
                has_nothrow_plus_assignment_operator_v<iterator_type, difference_type>) {
            return *this += -n;
        }
        enable_if_t<is_random_access_iterator_v<iterator_type>, reverse_iterator> operator+(difference_type n)
                noexcept(has_nothrow_minus_assignment_operator_v<iterator_type, difference_type>) {
            auto backup {*this};
            backup += n;
            return backup;
        }
        enable_if_t<is_random_access_iterator_v<iterator_type>, reverse_iterator> operator-(difference_type n)
                noexcept(has_nothrow_minus_assignment_operator_v<iterator_type, difference_type>) {
            return *this + -n;
        }
        operator iterator_type() const noexcept {
            return this->iter;
        }
        explicit operator enable_if_t<is_static_castable_v<iterator_type, bool>, bool>() const
                noexcept(is_nothrow_static_castable_v<iterator_type, bool>) {
            return static_cast<bool>(this->iter);
        }
    public:
        iterator_type base() const noexcept {
            return this->iter;
        }
    };
    template <typename IteratorLHS, typename IteratorRHS = IteratorLHS>
    inline auto operator-(const reverse_iterator<IteratorLHS> &lhs, const reverse_iterator<IteratorRHS> &rhs)
           noexcept(has_nothrow_minus_operator_v<IteratorLHS, IteratorRHS>) ->
           decltype(lhs.base() - rhs.base()) {
        return rhs.base() - lhs.base();
    }
    template <typename IteratorLHS, typename IteratorRHS = IteratorLHS>
    inline auto operator==(const reverse_iterator<IteratorLHS> &lhs, const reverse_iterator<IteratorRHS> &rhs)
            noexcept(has_nothrow_equal_to_operator_v<IteratorLHS, IteratorRHS>) ->
            decltype(rhs.base() == lhs.base()) {
        return rhs.base() == lhs.base();
    }
    template <typename IteratorLHS, typename IteratorRHS = IteratorLHS>
    inline bool operator!=(const reverse_iterator<IteratorLHS> &lhs, const reverse_iterator<IteratorRHS> &rhs)
            noexcept(has_nothrow_not_equal_to_operator_v<IteratorLHS, IteratorRHS>) {
        return lhs.base() not_eq rhs.base();
    }
    template <typename IteratorLHS, typename IteratorRHS = IteratorLHS>
    inline auto operator<(const reverse_iterator<IteratorLHS> &lhs, const reverse_iterator<IteratorRHS> &rhs)
            noexcept(has_nothrow_less_operator_v<IteratorLHS, IteratorRHS>) ->
            decltype(lhs.base() < rhs.base()) {
        return lhs.base() < rhs.base();
    }
    template <typename IteratorLHS, typename IteratorRHS = IteratorLHS>
    inline auto operator<=(const reverse_iterator<IteratorLHS> &lhs, const reverse_iterator<IteratorRHS> &rhs)
            noexcept(has_nothrow_less_equal_to_operator_v<IteratorLHS, IteratorRHS>) ->
            decltype(lhs.base() <= rhs.base()) {
        return lhs.base() <= rhs.base();
    }
    template <typename IteratorLHS, typename IteratorRHS = IteratorLHS>
    inline auto operator>(const reverse_iterator<IteratorLHS> &lhs, const reverse_iterator<IteratorRHS> &rhs)
            noexcept(has_nothrow_greater_operator_v<IteratorLHS, IteratorRHS>) ->
            decltype(lhs.base() > rhs.base()) {
        return lhs.base() > rhs.base();
    }
    template <typename IteratorLHS, typename IteratorRHS = IteratorLHS>
    inline auto operator>=(const reverse_iterator<IteratorLHS> &lhs, const reverse_iterator<IteratorRHS> &rhs)
            noexcept(has_nothrow_greater_equal_to_operator_v<IteratorLHS, IteratorRHS>) ->
            decltype(lhs.base() >= rhs.base()) {
        return lhs.base() >= rhs.base();
    }
}
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(special iterator, forward_list_iterator)
namespace data_structure::__data_structure_auxiliary {
    template <typename T>
    struct forward_list_node {
        T value;
        forward_list_node *next;
    };
    template <typename T, bool IsConst = false>
    class forward_list_iterator final {
        template <typename, typename> friend class forward_list;
        template <typename Type, bool IsConstLHS, bool IsConstRHS>
        friend bool operator==(const forward_list_iterator<Type, IsConstLHS> &,
                const forward_list_iterator<Type, IsConstRHS> &) noexcept;
        template <typename Type, bool IsConstLHS, bool IsConstRHS>
        friend bool operator!=(const forward_list_iterator<Type, IsConstLHS> &,
                const forward_list_iterator<Type, IsConstRHS> &) noexcept;
    private:
        using node_type = forward_list_node<T> *;
    public:
        using size_type = size_t;
        using difference_type = ptrdiff_t;
        using value_type = T;
        using reference = add_lvalue_reference_t<T>;
        using const_reference = add_const_reference_t<T>;
        using rvalue_reference = add_rvalue_reference_t<T>;
        using pointer = add_pointer_t<T>;
        using const_pointer = add_const_pointer_t<T>;
        using iterator_category = forward_iterator_tag;
    private:
        node_type node;
    public:
        constexpr forward_list_iterator() noexcept = default;
        constexpr explicit forward_list_iterator(node_type node) noexcept : node {node} {}
        constexpr forward_list_iterator(const forward_list_iterator &) noexcept = default;
        constexpr forward_list_iterator(forward_list_iterator &&) noexcept = default;
        ~forward_list_iterator() noexcept = default;
    public:
        forward_list_iterator &operator=(const forward_list_iterator &) noexcept = default;
        forward_list_iterator &operator=(forward_list_iterator &&) noexcept = default;
        reference operator*() noexcept {
            return this->node->value;
        }
        pointer operator->() noexcept {
            return ds::address_of(**this);
        }
        forward_list_iterator &operator++() & noexcept {
            this->node = this->node->next;
            return *this;
        }
        forward_list_iterator operator++(int) & noexcept {
            auto tmp {*this};
            ++*this;
            return tmp;
        }
        explicit operator bool() const noexcept {
            return this->node;
        }
        operator forward_list_iterator<value_type, true>() const noexcept {
            return forward_list_iterator<value_type, true>(const_cast<forward_list_iterator *>(this)->node);
        }
    };
    template <typename T>
    class forward_list_iterator<T, true> final {
        template <typename, typename> friend class forward_list;
        template <typename Type, bool IsConstLHS, bool IsConstRHS>
        friend bool operator==(const forward_list_iterator<Type, IsConstLHS> &,
                const forward_list_iterator<Type, IsConstRHS> &) noexcept;
        template <typename Type, bool IsConstLHS, bool IsConstRHS>
        friend bool operator!=(const forward_list_iterator<Type, IsConstLHS> &,
                const forward_list_iterator<Type, IsConstRHS> &) noexcept;
    private:
        using node_type = forward_list_node<T> *;
    public:
        using size_type = size_t;
        using difference_type = ptrdiff_t;
        using value_type = T;
        using reference = add_const_reference_t<T>;
        using const_reference = reference;
        using rvalue_reference = add_rvalue_reference_t<T>;
        using pointer = add_const_pointer_t<T>;
        using const_pointer = pointer;
        using iterator_category = forward_iterator_tag;
    private:
        node_type node;
    public:
        constexpr forward_list_iterator() noexcept = default;
        constexpr explicit forward_list_iterator(node_type node) : node {node} {}
        constexpr forward_list_iterator(const forward_list_iterator &) noexcept = default;
        constexpr forward_list_iterator(forward_list_iterator &&) noexcept = default;
        ~forward_list_iterator() noexcept = default;
    public:
        forward_list_iterator &operator=(const forward_list_iterator &) noexcept = default;
        forward_list_iterator &operator=(forward_list_iterator &&) noexcept = default;
        const_reference operator*() const noexcept {
            return this->node->value;
        }
        const_pointer operator->() const noexcept {
            return ds::address_of(**this);
        }
        forward_list_iterator &operator++() & noexcept {
            this->node = this->node->next;
            return *this;
        }
        forward_list_iterator operator++(int) & noexcept {
            auto tmp {*this};
            ++*this;
            return tmp;
        }
        explicit operator bool() const noexcept {
            return this->node;
        }
    };
    template <typename T, bool IsConstLHS, bool IsConstRHS = IsConstLHS>
    inline bool operator==(const forward_list_iterator<T, IsConstLHS> &lhs,
            const forward_list_iterator<T, IsConstRHS> &rhs) noexcept {
        return lhs.node == rhs.node;
    }
    template <typename T, bool IsConstLHS, bool IsConstRHS = IsConstLHS>
    inline bool operator!=(const forward_list_iterator<T, IsConstLHS> &lhs,
            const forward_list_iterator<T, IsConstRHS> &rhs) noexcept {
        return not(lhs == rhs);
    }
}
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(special iterator, list_iterator)
namespace data_structure::__data_structure_auxiliary {
    template <typename T>
    struct list_node  {
        T value;
        list_node *next;
        list_node *previous;
    };
    template <typename T, bool IsConst = false>
    class list_iterator final {
        template <typename, typename> friend class list;
        template <typename Type, bool IsConstLHS, bool IsConstRHS>
        friend bool operator==(const list_iterator<Type, IsConstLHS> &,
                const list_iterator<Type, IsConstRHS> &) noexcept;
        template <typename Type, bool IsConstLHS, bool IsConstRHS>
        friend bool operator!=(const list_iterator<Type, IsConstLHS> &,
                const list_iterator<Type, IsConstRHS> &) noexcept;
    private:
        using node_type = list_node<T> *;
    public:
        using size_type = size_t;
        using difference_type = ptrdiff_t;
        using value_type = T;
        using reference = add_lvalue_reference_t<T>;
        using const_reference = add_const_reference_t<T>;
        using rvalue_reference = add_rvalue_reference_t<T>;
        using pointer = add_pointer_t<T>;
        using const_pointer = add_const_pointer_t<T>;
        using iterator_category = bidirectional_iterator_tag;
    private:
        node_type node;
    public:
        constexpr list_iterator() noexcept = default;
        explicit constexpr list_iterator(node_type node) noexcept: node {node} {}
        constexpr list_iterator(const list_iterator &) noexcept = default;
        constexpr list_iterator(list_iterator &&) noexcept = default;
        ~list_iterator() noexcept = default;
    public:
        list_iterator &operator=(const list_iterator &) noexcept = default;
        list_iterator &operator=(list_iterator &&) noexcept = default;
        reference operator*() noexcept {
            return this->node->value;
        }
        pointer operator->() noexcept {
            return ds::address_of(**this);
        }
        list_iterator &operator++() & noexcept {
            this->node = this->node->next;
            return *this;
        }
        list_iterator operator++(int) & noexcept {
            auto tmp {*this};
            ++*this;
            return tmp;
        }
        list_iterator &operator--() & noexcept {
            this->node = this->node->previous;
            return *this;
        }
        list_iterator operator--(int) & noexcept {
            auto tmp {*this};
            --*this;
            return tmp;
        }
        operator list_iterator<value_type, true>() const noexcept {
            return list_iterator<value_type, true>(const_cast<list_iterator *>(this)->node);
        }
        explicit operator bool() const noexcept {
            return this->node;
        }
    };
    template <typename T>
    class list_iterator<T, true> final {
        template <typename, typename>
        friend class list;
        template <typename Type, bool IsConstLHS, bool IsConstRHS>
        friend bool operator==(const list_iterator<Type, IsConstLHS> &,
                const list_iterator<Type, IsConstRHS> &) noexcept;
        template <typename Type, bool IsConstLHS, bool IsConstRHS>
        friend bool operator!=(const list_iterator<Type, IsConstLHS> &,
                const list_iterator<Type, IsConstRHS> &) noexcept;
    private:
        using node_type = list_node<T> *;
    public:
        using size_type = size_t;
        using difference_type = ptrdiff_t;
        using value_type = T;
        using reference = add_const_reference_t<T>;
        using const_reference = reference;
        using rvalue_reference = add_rvalue_reference_t<T>;
        using pointer = add_const_pointer_t<T>;
        using const_pointer = pointer;
        using iterator_category = bidirectional_iterator_tag;
    private:
        node_type node;
    public:
        constexpr list_iterator() noexcept = default;
        explicit constexpr list_iterator(node_type node) noexcept: node {node} {}
        constexpr list_iterator(const list_iterator &) noexcept = default;
        constexpr list_iterator(list_iterator &&) noexcept = default;
        ~list_iterator() noexcept = default;
    public:
        list_iterator &operator=(const list_iterator &) noexcept = default;
        list_iterator &operator=(list_iterator &&) noexcept = default;
        reference operator*() const noexcept {
            return this->node->value;
        }
        pointer operator->() const noexcept {
            return ds::address_of(**this);
        }
        list_iterator &operator++() & noexcept {
            this->node = this->node->next;
            return *this;
        }
        list_iterator operator++(int) & noexcept {
            auto tmp {*this};
            ++*this;
            return tmp;
        }
        list_iterator &operator--() & noexcept {
            this->node = this->node->previous;
            return *this;
        }
        list_iterator operator--(int) & noexcept {
            auto tmp {*this};
            --*this;
            return tmp;
        }
        explicit operator bool() const noexcept {
            return this->node;
        }
    };
    template <typename NodeType, bool IsConstLHS, bool IsConstRHS = IsConstLHS>
    inline bool operator==(const list_iterator<NodeType, IsConstLHS> &lhs,
            const list_iterator<NodeType, IsConstRHS> &rhs) noexcept {
        return lhs.node == rhs.node;
    }
    template <typename NodeType, bool IsConstLHS, bool IsConstRHS = IsConstLHS>
    inline bool operator!=(const list_iterator<NodeType, IsConstLHS> &lhs,
            const list_iterator<NodeType, IsConstRHS> &rhs) noexcept {
        return not(lhs == rhs);
    }
}
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(special iterator, static_forward_list_iterator)
namespace data_structure::__data_structure_auxiliary {
    template <typename T>
    struct static_forward_list_node {
    public:
        constexpr static inline ptrdiff_t null {-1};
        constexpr static inline ptrdiff_t empty {-2};
    public:
        T value;
        ptrdiff_t next;
    public:
        void set_null() noexcept {
            this->next = this->null;
        }
        void set_empty() noexcept {
            this->next = this->empty;
        }
        [[nodiscard]]
        bool is_null() const noexcept {
            return this->next == this->null;
        }
        [[nodiscard]]
        bool is_empty() const noexcept {
            return this->next == this->empty;
        }
    };
    template <typename T, typename Container, bool IsConst = false>
    class static_forward_list_iterator final {
        template <typename Type, typename ContainerTp, bool IsConstLHS, bool IsConstRHS>
        friend bool operator==(const static_forward_list_iterator<Type, ContainerTp, IsConstLHS> &,
                const static_forward_list_iterator<Type, ContainerTp, IsConstRHS> &) noexcept;
        template <typename Type, typename ContainerTp, bool IsConstLHS, bool IsConstRHS>
        friend bool operator!=(const static_forward_list_iterator<Type, ContainerTp, IsConstLHS> &,
                const static_forward_list_iterator<Type, ContainerTp, IsConstRHS> &) noexcept;
        template <typename, typename> friend class static_forward_list;
    private:
        using container_type = typename add_lvalue_reference<Container>::type;
    public:
        using size_type = size_t;
        using difference_type = ptrdiff_t;
        using value_type = T;
        using reference = add_lvalue_reference_t<T>;
        using const_reference = add_const_reference_t<T>;;
        using rvalue_reference = add_rvalue_reference_t<T>;
        using pointer = add_pointer_t<T>;
        using const_pointer = add_const_pointer_t<T>;
        using iterator_category = forward_iterator_tag;
    private:
        bool head;
        ptrdiff_t node;
        container_type c;
    public:
        constexpr static_forward_list_iterator() noexcept = default;
        constexpr static_forward_list_iterator(ptrdiff_t node, container_type c, bool head = false)
                noexcept : head {head}, node {node}, c {c} {}
        constexpr static_forward_list_iterator(const static_forward_list_iterator &) noexcept = default;
        constexpr static_forward_list_iterator(static_forward_list_iterator &&) noexcept = default;
        ~static_forward_list_iterator() noexcept = default;
    public:
        constexpr static_forward_list_iterator &
        operator=(const static_forward_list_iterator &) noexcept = default;
        constexpr static_forward_list_iterator & operator=(static_forward_list_iterator &&) noexcept = default;
        reference operator*() noexcept {
            return this->head ? *static_cast<pointer>(nullptr) : this->c[this->node].value;
        }
        pointer operator->() noexcept {
            return ds::address_of(**this);
        }
        static_forward_list_iterator &operator++() & noexcept {
            if(this->head) {
                this->head = false;
                return *this;
            }
            this->node = this->c[this->node].next;
            return *this;
        }
        static_forward_list_iterator operator++(int) & noexcept {
            auto tmp {*this};
            ++*this;
            return tmp;
        }
        operator static_forward_list_iterator<value_type, Container, true>() const noexcept {
            return static_forward_list_iterator<value_type, Container, true>(
                    const_cast<static_forward_list_iterator *>(this)->node,
                    const_cast<static_forward_list_iterator *>(this)->c);
        };
        explicit operator bool() const noexcept {
            return this->node == static_forward_list_node<value_type>::empty;
        }
    };
    template <typename T, typename Container>
    class static_forward_list_iterator<T, Container, true> final {
        template <typename Type, typename ContainerTp, bool IsConstLHS, bool IsConstRHS>
        friend bool operator==(const static_forward_list_iterator<Type, ContainerTp, IsConstLHS> &,
                const static_forward_list_iterator<Type, ContainerTp, IsConstRHS> &) noexcept;
        template <typename Type, typename ContainerTp, bool IsConstLHS, bool IsConstRHS>
        friend bool operator!=(const static_forward_list_iterator<Type, ContainerTp, IsConstLHS> &,
                const static_forward_list_iterator<Type, ContainerTp, IsConstRHS> &) noexcept;
        template <typename, typename> friend class static_forward_list;
    private:
        using container_type = typename add_lvalue_reference<Container>::type;
    public:
        using size_type = size_t;
        using difference_type = ptrdiff_t;
        using value_type = T;
        using reference = add_const_reference_t<T>;
        using const_reference = reference;
        using rvalue_reference = add_rvalue_reference_t<T>;
        using pointer = add_const_pointer_t<T>;
        using const_pointer = pointer;
        using iterator_category = forward_iterator_tag;
    private:
        bool head;
        ptrdiff_t node;
        container_type c;
    public:
        constexpr static_forward_list_iterator() noexcept = default;
        constexpr static_forward_list_iterator(ptrdiff_t node, container_type c, bool head = false)
                noexcept : head {head}, node {node}, c {c} {}
        constexpr static_forward_list_iterator(const static_forward_list_iterator &) noexcept = default;
        constexpr static_forward_list_iterator(static_forward_list_iterator &&) noexcept = default;
        ~static_forward_list_iterator() noexcept = default;
    public:
        constexpr static_forward_list_iterator &operator=(const static_forward_list_iterator &) noexcept = default;
        constexpr static_forward_list_iterator &operator=(static_forward_list_iterator &&) noexcept = default;
        const_reference operator*() const noexcept {
            return this->head ? *static_cast<pointer>(nullptr) : this->c[this->node].value;
        }
        const_pointer operator->() const noexcept {
            return ds::address_of(**this);
        }
        static_forward_list_iterator &operator++() & noexcept {
            if(this->head) {
                this->head = false;
                return *this;
            }
            this->node = this->c[this->node].next;
            return *this;
        }
        static_forward_list_iterator operator++(int) & noexcept {
            auto tmp {*this};
            ++*this;
            return tmp;
        }
        explicit operator bool() const noexcept {
            return this->node == static_forward_list_node<value_type>::empty;
        }
    };
    template <typename T, typename Container, bool IsConstLHS, bool IsConstRHS = IsConstLHS>
    inline bool operator==(const static_forward_list_iterator<T, Container, IsConstLHS> &lhs,
            const static_forward_list_iterator<T, Container, IsConstRHS> &rhs) noexcept {
        return lhs.head == rhs.head and lhs.node == rhs.node and ds::address_of(lhs.c) == ds::address_of(rhs.c);
    }
    template <typename T, typename Container, bool IsConstLHS, bool IsConstRHS = IsConstLHS>
    inline bool operator!=(const static_forward_list_iterator<T, Container, IsConstLHS> &lhs,
            const static_forward_list_iterator<T, Container, IsConstRHS> &rhs) noexcept {
        return not(lhs == rhs);
    }
}
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(special iterator, deque_iterator)
namespace data_structure {
    template <typename T, typename MapPointer, size_t BufferSize = 64, bool IsConst = false>
    class deque_iterator final {
        template <typename Type, typename MapPointerT, size_t Buffer, bool Const>
        friend bool operator==(const deque_iterator<Type, MapPointerT, Buffer, Const> &lhs,
                const deque_iterator<Type, MapPointerT, Buffer, Const> &rhs) noexcept;
        template <typename Type, typename MapPointerT, size_t Buffer, bool Const>
        friend bool operator<(const deque_iterator<Type, MapPointerT, Buffer, Const> &lhs,
                const deque_iterator<Type, MapPointerT, Buffer, Const> &rhs) noexcept;
        template <typename, typename> friend class deque;
    public:
        using size_type = size_t;
        using difference_type = ptrdiff_t;
        using value_type = T;
        using reference = add_lvalue_reference_t<value_type>;
        using const_reference = add_const_reference_t<value_type>;
        using rvalue_reference = add_rvalue_reference_t<value_type>;
        using pointer = add_pointer_t<value_type>;
        using const_pointer = add_const_pointer_t<value_type>;
        using iterator_category = random_access_iterator_tag;
        static_assert(BufferSize > 0, "The template argument BufferSize cannot be zero!");
    private:
        using map_pointer = MapPointer;
    private:
        constexpr static auto buffer_size {BufferSize};
        constexpr static auto last_position {deque_iterator::buffer_size - 1};
    private:
        pointer iter;
        map_pointer map;
    public:
        constexpr deque_iterator() noexcept = default;
        constexpr deque_iterator(pointer iter, map_pointer map) : iter {iter}, map {map} {}
        constexpr deque_iterator(const deque_iterator &) noexcept = default;
        constexpr deque_iterator(deque_iterator &&) noexcept = default;
        ~deque_iterator() noexcept = default;
    public:
        constexpr deque_iterator &operator=(const deque_iterator &) noexcept = default;
        constexpr deque_iterator &operator=(deque_iterator &&) noexcept = default;
    public:
        reference operator*() noexcept {
            return *this->iter;
        }
        pointer operator->() noexcept {
            return ds::address_of(**this);
        }
        reference operator[](difference_type n) noexcept {
            return *(*this + n);
        }
        deque_iterator &operator++() & noexcept {
            if(++this->iter == *this->map + static_cast<difference_type>(this->buffer_size)) {
                this->iter = *++this->map;
            }
            return *this;
        }
        deque_iterator operator++(int) & noexcept {
            auto tmp {*this};
            ++*this;
            return tmp;
        }
        deque_iterator &operator--() & noexcept {
            if(--this->iter == *this->map - 1) {
                this->iter = *--this->map + static_cast<difference_type>(this->last_position);
            }
            return *this;
        }
        deque_iterator operator--(int) & noexcept {
            auto tmp {*this};
            --*this;
            return tmp;
        }
        deque_iterator &operator+=(difference_type n) & noexcept {
            const auto offset {n + (this->iter - *this->map)};
            if(offset >= 0 and offset < this->buffer_size) {
                this->iter += n;
            }else {
                const auto node_offset {
                    offset > 0 ? offset / this->buffer_size : (-offset - 1) / this->buffer_size - 1};
                this->map += node_offset;
                this->iter = *this->map + (offset - node_offset * this->buffer_size);
            }
            return *this;
        }
        deque_iterator &operator-=(difference_type n) &noexcept {
            return *this += -n;
        }
        deque_iterator operator+(difference_type n) const noexcept {
            auto tmp {*this};
            return tmp += n;
        }
        deque_iterator operator-(difference_type n) const noexcept {
            auto tmp {*this};
            return tmp += -n;
        }
        difference_type operator-(const deque_iterator &rhs) const noexcept {
            return this->buffer_size * (this->map - rhs.map - 1) +
                    (this->iter - *this->map) + (const_cast<deque_iterator &>(rhs).after_tail() - rhs.iter);
        }
        explicit operator bool() const noexcept {
            return this->iter;
        }
        operator deque_iterator<T, MapPointer, BufferSize, true>() const noexcept {
            return deque_iterator<T, MapPointer, BufferSize, true>(
                    const_cast<deque_iterator *>(this)->iter, const_cast<deque_iterator *>(this)->map);
        }
    private:
        void next() noexcept {
            ++this->map;
            this->iter = *this->map;
        }
        void previous() noexcept {
            --this->map;
            this->iter = *this->map + static_cast<difference_type>(this->buffer_size - 1);
        }
        [[nodiscard]]
        difference_type offset() const noexcept {
            return this->iter - *this->map;
        }
        [[nodiscard]]
        difference_type surplus() const noexcept {
            return this->buffer_size - this->offset();
        }
        [[nodiscard]]
        pointer after_tail() noexcept {
            return *this->map + static_cast<difference_type>(this->buffer_size);
        }
        [[nodiscard]]
        pointer first() noexcept {
            return *this->map;
        }
    };
    template <typename T, typename MapPointer, size_t BufferSize>
    class deque_iterator<T, MapPointer, BufferSize, true> final {
        template <typename Type, typename MapPointerT, size_t Buffer, bool Const>
        friend bool operator==(const deque_iterator<Type, MapPointerT, Buffer, Const> &lhs,
                const deque_iterator<Type, MapPointerT, Buffer, Const> &rhs) noexcept;
        template <typename Type, typename MapPointerT, size_t Buffer, bool Const>
        friend bool operator<(const deque_iterator<Type, MapPointerT, Buffer, Const> &lhs,
                const deque_iterator<Type, MapPointerT, Buffer, Const> &rhs) noexcept;
        template <typename, typename> friend class deque;
    public:
        using size_type = size_t;
        using difference_type = ptrdiff_t;
        using value_type = T;
        using reference = add_const_reference_t<value_type>;
        using const_reference = reference;
        using rvalue_reference = add_rvalue_reference_t<value_type>;
        using pointer = add_const_pointer_t<value_type>;
        using const_pointer = pointer;
        using iterator_category = random_access_iterator_tag;
        static_assert(BufferSize > 0, "The template argument BufferSize cannot be zero!");
    private:
        using map_pointer = MapPointer;
        using iterator_type = typename add_pointer<value_type>::type;
    private:
        constexpr static inline auto buffer_size {BufferSize};
        constexpr static inline auto last_position {deque_iterator::buffer_size - 1};
    private:
        iterator_type iter;
        map_pointer map;
    public:
        constexpr deque_iterator() noexcept = default;
        constexpr deque_iterator(iterator_type iter, map_pointer map) : iter {iter}, map {map} {}
        constexpr deque_iterator(const deque_iterator &) noexcept = default;
        constexpr deque_iterator(deque_iterator &&) noexcept = default;
        ~deque_iterator() noexcept = default;
    public:
        constexpr deque_iterator &operator=(const deque_iterator &) noexcept = default;
        constexpr deque_iterator &operator=(deque_iterator &&) noexcept = default;
    public:
        const_reference operator*() const noexcept {
            return *this->iter;
        }
        const_pointer operator->() const noexcept {
            return ds::address_of(**this);
        }
        const_reference operator[](difference_type n) const noexcept {
            return *(*this + n);
        }
        deque_iterator &operator++() & noexcept {
            if(++this->iter == *this->map + static_cast<difference_type>(this->buffer_size)) {
                this->iter = *++this->map;
            }
            return *this;
        }
        deque_iterator operator++(int) & noexcept {
            auto tmp {*this};
            ++*this;
            return tmp;
        }
        deque_iterator &operator--() & noexcept {
            if(--this->iter == *this->map - 1) {
                this->iter = *--this->map + static_cast<difference_type>(this->last_position);
            }
            return *this;
        }
        deque_iterator operator--(int) & noexcept {
            auto tmp {*this};
            --*this;
            return tmp;
        }
        deque_iterator &operator+=(difference_type n) & noexcept {
            const auto offset {n + (this->iter - *this->map)};
            if(offset >= 0 and offset < this->buffer_size) {
                this->iter += n;
            }else {
                const auto node_offset {
                        offset > 0 ? offset / this->buffer_size : -((-offset - 1) / this->buffer_size) - 1};
                this->map += node_offset;
                this->iter = *this->map + (offset - node_offset * this->buffer_size);
            }
            return *this;
        }
        deque_iterator &operator-=(difference_type n) &noexcept {
            return *this += -n;
        }
        deque_iterator operator+(difference_type n) const noexcept {
            auto tmp {*this};
            return tmp += n;
        }
        deque_iterator operator-(difference_type n) const noexcept {
            auto tmp {*this};
            return tmp += -n;
        }
        difference_type operator-(const deque_iterator &rhs) const noexcept {
            return this->buffer_size * (this->map - rhs.map - 1) +
                   (this->iter - *this->map) + (const_cast<deque_iterator &>(rhs).after_tail() - rhs.iter);
        }
        explicit operator bool() const noexcept {
            return this->iter;
        }
    private:
        void next() noexcept {
            ++this->map;
            this->iter = *this->map;
        }
        void previous() noexcept {
            --this->map;
            this->iter = *this->map + static_cast<difference_type>(this->buffer_size - 1);
        }
        [[nodiscard]]
        difference_type offset() const noexcept {
            return this->iter - *this->map;
        }
        [[nodiscard]]
        difference_type surplus() const noexcept {
            return this->buffer_size - this->offset();
        }
        [[nodiscard]]
        pointer after_tail() noexcept {
            return *this->map + static_cast<difference_type>(this->buffer_size);
        }
        [[nodiscard]]
        pointer first() noexcept {
            return *this->map;
        }
    };

    template <typename T, typename MapPointer, size_t BufferSize, bool IsConst>
    bool operator==(const deque_iterator<T, MapPointer, BufferSize, IsConst> &lhs,
            const deque_iterator<T, MapPointer, BufferSize, IsConst> &rhs) noexcept {
        return lhs.iter == rhs.iter and lhs.map == rhs.map;
    }
    template <typename T, typename MapPointer, size_t BufferSize, bool IsConst>
    bool operator!=(const deque_iterator<T, MapPointer, BufferSize, IsConst> &lhs,
            const deque_iterator<T, MapPointer, BufferSize, IsConst> &rhs) noexcept {
        return not(lhs == rhs);
    }
    template <typename T, typename MapPointer, size_t BufferSize, bool IsConst>
    bool operator<(const deque_iterator<T, MapPointer, BufferSize, IsConst> &lhs,
            const deque_iterator<T, MapPointer, BufferSize, IsConst> &rhs) noexcept {
        return lhs.map == rhs.map ? lhs.iter - rhs.iter < 0 : lhs.map - rhs.map < 0;
    }
    template <typename T, typename MapPointer, size_t BufferSize, bool IsConst>
    bool operator<=(const deque_iterator<T, MapPointer, BufferSize, IsConst> &lhs,
            const deque_iterator<T, MapPointer, BufferSize, IsConst> &rhs) noexcept {
        return not(rhs < lhs);
    }
    template <typename T, typename MapPointer, size_t BufferSize, bool IsConst>
    bool operator>(const deque_iterator<T, MapPointer, BufferSize, IsConst> &lhs,
            const deque_iterator<T, MapPointer, BufferSize, IsConst> &rhs) noexcept {
        return lhs < rhs;
    }
    template <typename T, typename MapPointer, size_t BufferSize, bool IsConst>
    bool operator>=(const deque_iterator<T, MapPointer, BufferSize, IsConst> &lhs,
            const deque_iterator<T, MapPointer, BufferSize, IsConst> &rhs) noexcept {
        return not(lhs < rhs);
    }
}
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(special iterator, skip_list_iterator)
namespace data_structure::__data_structure_auxiliary {
    template <typename T>
    struct skip_list_node {
    public:
        T value;
        skip_list_node **next;
        size_t max_level;
    public:
        void next_allocate() {
            this->next = new skip_list_node *[this->max_level + 1];
        }
    };
    template <typename T, bool IsConst = false>
    class skip_list_iterator final {
        template <typename Type, bool IsConstLHS, bool IsConstRHS>
        friend bool operator==(const skip_list_iterator<Type, IsConstLHS> &,
                const skip_list_iterator<Type, IsConstRHS> &) noexcept;
    public:
        using size_type = size_t;
        using difference_type = ptrdiff_t;
        using value_type = T;
        using reference = add_lvalue_reference_t<value_type>;
        using const_reference = add_const_reference_t<value_type>;
        using rvalue_reference = add_rvalue_reference_t<value_type>;
        using pointer = add_pointer_t<value_type>;
        using const_pointer = add_const_pointer_t<value_type>;
        using iterator_category = forward_iterator_tag;
    private:
        using node_type = skip_list_node<T> *;
    private:
        node_type iter;
        size_t level;
    public:
        constexpr skip_list_iterator() noexcept = default;
        constexpr skip_list_iterator(node_type iter, size_t level) noexcept : iter {iter}, level {level} {}
        constexpr skip_list_iterator(const skip_list_iterator &) noexcept = default;
        constexpr skip_list_iterator(skip_list_iterator &&) noexcept = default;
        ~skip_list_iterator() noexcept = default;
    public:
        constexpr skip_list_iterator &operator=(const skip_list_iterator &) noexcept = default;
        constexpr skip_list_iterator &operator=(skip_list_iterator &&) noexcept = default;
        reference operator*() noexcept {
            return this->iter->value;
        }
        pointer operator->() noexcept {
            return ds::address_of(**this);
        }
        skip_list_iterator &operator++() & noexcept {
            this->iter = this->iter->next[this->level];
        }
        skip_list_iterator operator++(int) & noexcept {
            auto tmp {*this};
            ++*this;
            return tmp;
        }
        skip_list_iterator &operator+() & noexcept {
            ++this->level;
            return *this;
        }
        skip_list_iterator &operator-() & noexcept {
            --this->level;
            return *this;
        }
        explicit operator bool() const noexcept {
            return this->node;
        }
        operator skip_list_iterator<T, true>() const noexcept {
            return skip_list_iterator<T, true>(const_cast<skip_list_iterator *>(this)->iter,
                    const_cast<skip_list_iterator *>(this)->level);
        }
    };
    template <typename T>
    class skip_list_iterator<T, true> final {
        template <typename Type, bool IsConstLHS, bool IsConstRHS>
        friend bool operator==(const skip_list_iterator<Type, IsConstLHS> &,
                const skip_list_iterator<Type, IsConstRHS> &) noexcept;
    public:
        using size_type = size_t;
        using difference_type = ptrdiff_t;
        using value_type = T;
        using reference = add_const_reference_t<value_type>;
        using const_reference = reference;
        using rvalue_reference = add_rvalue_reference_t<value_type>;
        using pointer = add_const_pointer_t<value_type>;
        using const_pointer = pointer;
        using iterator_category = forward_iterator_tag;
    private:
        using node_type = skip_list_node<T> *;
    private:
        node_type iter;
        size_t level;
    public:
        constexpr skip_list_iterator() noexcept = default;
        constexpr skip_list_iterator(node_type iter, size_t level) noexcept : iter {iter}, level {level} {}
        constexpr skip_list_iterator(const skip_list_iterator &) noexcept = default;
        constexpr skip_list_iterator(skip_list_iterator &&) noexcept = default;
        ~skip_list_iterator() noexcept = default;
    public:
        constexpr skip_list_iterator &operator=(const skip_list_iterator &) noexcept = default;
        constexpr skip_list_iterator &operator=(skip_list_iterator &&) noexcept = default;
        reference operator*() const noexcept {
            return this->iter->value;
        }
        pointer operator->() const noexcept {
            return ds::address_of(**this);
        }
        skip_list_iterator &operator++() & noexcept {
            this->iter = this->iter->next[this->level];
        }
        skip_list_iterator operator++(int) & noexcept {
            auto tmp {*this};
            ++*this;
            return tmp;
        }
        skip_list_iterator &operator+() & noexcept {
            ++this->level;
            return *this;
        }
        skip_list_iterator &operator-() & noexcept {
            --this->level;
            return *this;
        }
        explicit operator bool() const noexcept {
            return this->node;
        }
    };
    template <typename T, bool IsConstLHS, bool IsConstRHS = IsConstLHS>
    inline bool operator==(const skip_list_iterator<T, IsConstLHS> &lhs,
            const skip_list_iterator<T,IsConstRHS> &rhs) noexcept {
        return lhs.iter == rhs.iter and lhs.level == rhs.level;
    }
    template <typename T, bool IsConstLHS, bool IsConstRHS = IsConstLHS>
    inline bool operator<(const skip_list_iterator<T, IsConstLHS> &lhs,
            const skip_list_iterator<T, IsConstRHS> &rhs) noexcept {
        return not(lhs == rhs);
    }
}
__DATA_STRUCTURE_END

#undef __DATA_STRUCTURE_ITERATOR_CHECKER_IMPL

#endif //DATA_STRUCTURE_ITERATOR_HPP
