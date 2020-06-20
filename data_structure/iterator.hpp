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

namespace data_structure {
    struct iterator_tag {};
    struct output_iterator_tag : iterator_tag {};
    struct input_iterator_tag : iterator_tag {};
    struct forward_iterator_tag : input_iterator_tag {};
    struct bidirectional_iterator_tag : forward_iterator_tag {};
    struct random_access_iterator_tag : bidirectional_iterator_tag {};
}

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
        using reference = typename add_lvalue_reference<value_type>::type;
        using const_reference = typename add_const_reference<value_type>::type;
        using rvalue_reference = typename add_rvalue_reference<value_type>::type;
        using pointer = typename add_pointer<value_type>::type;
        using const_pointer = typename add_const_pointer<value_type>::type;
        using iterator_category = random_access_iterator_tag;
    };
}

namespace data_structure {
    namespace __data_structure_auxiliary {
        template <typename T>
        constexpr inline true_type test_iterator_category(
                typename T::iterator_category * = nullptr) noexcept {
            static_assert(is_type<T>::value, "The function has_iterator_category() cannot be called!");
            return {};
        }
        template <typename T>
        constexpr inline true_type test_iterator_category(
                typename enable_if<is_pointer<T>::value, T>::type = nullptr) noexcept {
            static_assert(is_type<T>::value, "The function has_iterator_category() cannot be called!");
            return {};
        }
        template <typename T>
        constexpr inline false_type test_iterator_category(...) noexcept {
            static_assert(is_type<T>::value, "The function has_iterator_category() cannot be called!");
            return {};
        }
        template <typename T>
        struct has_iterator_category {
            using value_type = bool;
            using result = decltype(test_iterator_category<T>(0));
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return has_iterator_category<T>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return has_iterator_category<T>::value;
            }
        };
        template <typename Iterator, bool HasIteratorCategory = has_iterator_category<Iterator>::value>
        struct is_iterator_auxiliary {
            using value_type = bool;
            using result = typename conditional<
                    is_same<typename __dsa::has_iterator_category<Iterator>::result, true_type>::value,
                    typename conditional<is_base_of<iterator_tag,
                                    typename iterator_traits<Iterator>::iterator_category>::value,
                            true_type, false_type>::type,
                    false_type>::result;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_iterator_auxiliary<Iterator, HasIteratorCategory>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_iterator_auxiliary<Iterator, HasIteratorCategory>::value;
            }
        };
        template <typename Iterator>
        struct is_iterator_auxiliary<Iterator, false> {
            using value_type = bool;
            using result = false_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_iterator_auxiliary<Iterator, false>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_iterator_auxiliary<Iterator, false>::value;
            }
        };
        template <typename Iterator, bool HasIteratorCategory = has_iterator_category<Iterator>::value>
        struct is_output_iterator_auxiliary {
            using value_type = bool;
            using result = typename conditional<
                    is_same<typename __dsa::has_iterator_category<Iterator>::result, true_type>::value,
                    typename conditional<is_base_of<output_iterator_tag,
                                    typename iterator_traits<Iterator>::iterator_category>::value,
                            true_type, false_type>::type,
                    false_type>::result;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_output_iterator_auxiliary<Iterator, HasIteratorCategory>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_output_iterator_auxiliary<Iterator, HasIteratorCategory>::value;
            }
        };
        template <typename Iterator>
        struct is_output_iterator_auxiliary<Iterator, false> {
            using value_type = bool;
            using result = false_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_output_iterator_auxiliary<Iterator, false>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_output_iterator_auxiliary<Iterator, false>::value;
            }
        };
        template <typename Iterator, bool HasIteratorCategory = has_iterator_category<Iterator>::value>
        struct is_input_iterator_auxiliary {
            using value_type = bool;
            using result = typename conditional<
                    is_same<typename __dsa::has_iterator_category<Iterator>::result, true_type>::value,
                    typename conditional<is_base_of<input_iterator_tag,
                                    typename iterator_traits<Iterator>::iterator_category>::value,
                            true_type, false_type>::type,
                    false_type>::result;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_input_iterator_auxiliary<Iterator, HasIteratorCategory>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_input_iterator_auxiliary<Iterator, HasIteratorCategory>::value;
            }
        };
        template <typename Iterator>
        struct is_input_iterator_auxiliary<Iterator, false> {
            using value_type = bool;
            using result = false_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_input_iterator_auxiliary<Iterator, false>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_input_iterator_auxiliary<Iterator, false>::value;
            }
        };
        template <typename Iterator, bool HasIteratorCategory = has_iterator_category<Iterator>::value>
        struct is_forward_iterator_auxiliary {
            using value_type = bool;
            using result = typename conditional<
                    is_same<typename __dsa::has_iterator_category<Iterator>::result, true_type>::value,
                    typename conditional<is_base_of<forward_iterator_tag,
                                    typename iterator_traits<Iterator>::iterator_category>::value,
                            true_type, false_type>::type,
                    false_type>::result;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_forward_iterator_auxiliary<Iterator, HasIteratorCategory>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_forward_iterator_auxiliary<Iterator, HasIteratorCategory>::value;
            }
        };
        template <typename Iterator>
        struct is_forward_iterator_auxiliary<Iterator, false> {
            using value_type = bool;
            using result = false_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_forward_iterator_auxiliary<Iterator, false>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_forward_iterator_auxiliary<Iterator, false>::value;
            }
        };
        template <typename Iterator, bool HasIteratorCategory = has_iterator_category<Iterator>::value>
        struct is_bidirectional_iterator_auxiliary {
            using value_type = bool;
            using result = typename conditional<
                    is_same<typename __dsa::has_iterator_category<Iterator>::result, true_type>::value,
                    typename conditional<is_base_of<bidirectional_iterator_tag,
                            typename iterator_traits<Iterator>::iterator_category>::value,
                            true_type, false_type>::type,
                    false_type>::result;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_bidirectional_iterator_auxiliary<Iterator, HasIteratorCategory>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_bidirectional_iterator_auxiliary<Iterator, HasIteratorCategory>::value;
            }
        };
        template <typename Iterator>
        struct is_bidirectional_iterator_auxiliary<Iterator, false> {
            using value_type = bool;
            using result = false_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_bidirectional_iterator_auxiliary<Iterator, false>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_bidirectional_iterator_auxiliary<Iterator, false>::value;
            }
        };
        template <typename Iterator, bool HasIteratorCategory = has_iterator_category<Iterator>::value>
        struct is_random_access_iterator_auxiliary {
            using value_type = bool;
            using result = typename conditional<
                    is_same<typename __dsa::has_iterator_category<Iterator>::result, true_type>::value,
                    typename conditional<is_base_of<random_access_iterator_tag,
                            typename iterator_traits<Iterator>::iterator_category>::value,
                            true_type, false_type>::type,
                    false_type>::result;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_random_access_iterator_auxiliary<Iterator, HasIteratorCategory>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_random_access_iterator_auxiliary<Iterator, HasIteratorCategory>::value;
            }
        };
        template <typename Iterator>
        struct is_random_access_iterator_auxiliary<Iterator, false> {
            using value_type = bool;
            using result = false_type;
            constexpr static inline auto value {static_cast<value_type>(result())};
            constexpr value_type operator()() const noexcept {
                return is_random_access_iterator_auxiliary<Iterator, false>::value;
            }
            constexpr explicit operator value_type() const noexcept {
                return is_random_access_iterator_auxiliary<Iterator, false>::value;
            }
        };
    }
    template <typename Iterator>
    struct is_iterator {
        using value_type = bool;
        using result = typename __dsa::is_iterator_auxiliary<Iterator>::result;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_iterator<Iterator>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_iterator<Iterator>::value;
        }
    };
    template <typename Iterator>
    struct is_output_iterator {
        using value_type = bool;
        using result = typename __dsa::is_output_iterator_auxiliary<Iterator>::result;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_output_iterator<Iterator>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_output_iterator<Iterator>::value;
        }
    };
    template <typename Iterator>
    struct is_input_iterator {
        using value_type = bool;
        using result = typename __dsa::is_input_iterator_auxiliary<Iterator>::result;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_input_iterator<Iterator>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_input_iterator<Iterator>::value;
        }
    };
    template <typename Iterator>
    struct is_forward_iterator {
        using value_type = bool;
        using result = typename __dsa::is_forward_iterator_auxiliary<Iterator>::result;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_forward_iterator<Iterator>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_forward_iterator<Iterator>::value;
        }
    };
    template <typename Iterator>
    struct is_bidirectional_iterator {
        using value_type = bool;
        using result = typename __dsa::is_bidirectional_iterator_auxiliary<Iterator>::result;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_bidirectional_iterator<Iterator>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_bidirectional_iterator<Iterator>::value;
        }
    };
    template <typename Iterator>
    struct is_random_access_iterator {
        using value_type = bool;
        using result = typename __dsa::is_random_access_iterator_auxiliary<Iterator>::result;
        constexpr static inline auto value {static_cast<value_type>(result())};
        constexpr value_type operator()() const noexcept {
            return is_random_access_iterator<Iterator>::value;
        }
        constexpr explicit operator value_type() const noexcept {
            return is_random_access_iterator<Iterator>::value;
        }
    };
}

namespace data_structure {
    template <typename Iterator>
    class wrap_iterator final {
    public:
        using iterator_type = Iterator;
        using size_type = typename iterator_traits<iterator_type>::size_type;
        using difference_type = typename iterator_traits<iterator_type>::difference_type;
        using value_type = typename iterator_traits<iterator_type>::value_type;
        using reference = typename iterator_traits<iterator_type>::reference;
        using const_reference = typename iterator_traits<iterator_type>::const_reference;
        using rvalue_reference = typename iterator_traits<iterator_type>::rvalue_reference;
        using pointer = typename iterator_traits<iterator_type>::pointer;
        using const_pointer = typename iterator_traits<iterator_type>::const_pointer;
        using iterator_category = typename iterator_traits<iterator_type>::iterator_category;
        static_assert(is_pointer<iterator_type>::value, "The class wrap_iterator is only for pointer type!");
    private:
        iterator_type iter;
    private:
        template <typename IteratorRHS>
        explicit constexpr wrap_iterator(const wrap_iterator<IteratorRHS> &rhs, typename enable_if<
                is_nothrow_convertible<IteratorRHS, iterator_type>::value, void>::type *)
                noexcept : iter {rhs.base()} {}
        template <typename IteratorRHS>
        constexpr wrap_iterator &operator_assignment_auxiliary(const wrap_iterator<IteratorRHS> &rhs,
                typename enable_if<is_nothrow_convertible<IteratorRHS, iterator_type>::value, void>::type *)
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
        reference operator*() const noexcept {
            return *this->iter;
        }
        pointer operator->() const noexcept {
            return this->iter;
        }
        reference operator[](difference_type n) const noexcept {
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

namespace data_structure {
    template <typename Iterator>
    class reverse_iterator {
    public:
        using iterator_type = Iterator;
        using size_type = typename iterator_traits<iterator_type>::size_type;
        using difference_type = typename iterator_traits<iterator_type>::difference_type;
        using value_type = typename iterator_traits<iterator_type>::value_type;
        using reference = typename iterator_traits<iterator_type>::reference;
        using const_reference = typename iterator_traits<iterator_type>::const_reference;
        using rvalue_reference = typename iterator_traits<iterator_type>::rvalue_reference;
        using pointer = typename iterator_traits<iterator_type>::pointer;
        using const_pointer = typename iterator_traits<iterator_type>::const_pointer;
        using iterator_category = typename iterator_traits<iterator_type>::iterator_category;
        static_assert(is_base_of<bidirectional_iterator_tag, iterator_category>::value,
                "The template argument must be at least a bidirectional iterator!");
    private:
        using if_random_access_iterator = typename is_random_access_iterator<iterator_type>::result;
    private:
        iterator_type iter;
    private:
        template <typename IteratorRHS>
        constexpr reverse_iterator(const reverse_iterator<IteratorRHS> &rhs, typename enable_if<
                is_convertible<IteratorRHS, iterator_type>::value, void>::type *)
                noexcept(is_nothrow_constructible<IteratorRHS, iterator_type>::value) : iter {rhs.base()} {}
        template <typename IteratorRHS>
        constexpr reverse_iterator &operator_assignment_auxiliary(const reverse_iterator<IteratorRHS> &rhs,
                typename enable_if<is_convertible<IteratorRHS, iterator_type>::value, void>::type *)
                noexcept(is_nothrow_assignable<IteratorRHS, iterator_type>::value) {
            this->iter = rhs.base();
            return *this;
        }
    public:
        constexpr reverse_iterator() = default;
        constexpr reverse_iterator(iterator_type iterator)
                noexcept(is_nothrow_copy_constructible<iterator_type>::value) : iter {iterator} {}
        template <typename IteratorRHS>
        constexpr reverse_iterator(const reverse_iterator<IteratorRHS> &rhs)
                noexcept(is_nothrow_constructible<iterator_type, IteratorRHS>::value) :
                reverse_iterator(rhs, nullptr) {}
        constexpr reverse_iterator(const reverse_iterator &) = default;
        constexpr reverse_iterator(reverse_iterator &&) = default;
        ~reverse_iterator() = default;
    public:
        constexpr reverse_iterator &operator=(const reverse_iterator &) = default;
        constexpr reverse_iterator &operator=(reverse_iterator &&) = default;
        template <typename IteratorRHS>
        constexpr reverse_iterator &operator=(const reverse_iterator<IteratorRHS> &rhs)
                noexcept(is_nothrow_assignable<iterator_type, IteratorRHS>::value) {
            return this->operator_assignment_auxiliary(rhs, nullptr);
        }
    public:
        reference operator*() const noexcept(has_nothrow_dereference_operator<iterator_type>::value) {
            return *this->iter;
        }
        pointer operator->() const noexcept {
            return static_cast<pointer>(ds::address_of(this->iter));
        }
        template <bool Boolean = true>
        typename enable_if<if_random_access_iterator()() and Boolean, reference>::type
        operator[](difference_type n)
                noexcept(has_nothrow_minus_assignment_operator<iterator_type, difference_type>::value and
                        has_nothrow_dereference_operator<iterator_type>::value) {
            return *(this->iter - n);
        }
        reverse_iterator &operator++() & noexcept(has_nothrow_pre_increment_operator<iterator_type>::value) {
            --this->iter;
            return *this;
        }
        reverse_iterator operator++(int) &
                noexcept(has_nothrow_post_increment_operator<iterator_type>::value) {
            auto backup {*this};
            --this->iter;
            return backup;
        }
        reverse_iterator &operator--() & noexcept(has_nothrow_pre_decrement_operator<iterator_type>::value) {
            ++this->iter;
            return *this;
        }
        reverse_iterator operator--(int) &
                noexcept(has_nothrow_post_decrement_operator<iterator_type>::value) {
            auto backup {*this};
            ++this->iter;
            return backup;
        }
        template <bool Boolean = true>
        typename enable_if<if_random_access_iterator()() and Boolean, reverse_iterator &>::type
        operator+=(difference_type n) &
                noexcept(has_nothrow_minus_assignment_operator<iterator_type, difference_type>::value) {
            this->iter -= n;
            return *this;
        }
        template <bool Boolean = true>
        typename enable_if<if_random_access_iterator()() and Boolean, reverse_iterator &>::type
        operator-=(difference_type n) &
                noexcept(has_nothrow_plus_assignment_operator<iterator_type, difference_type>::value) {
            return *this += -n;
        }
        template <bool Boolean = true>
        typename enable_if<if_random_access_iterator() and Boolean, reverse_iterator>::type
        operator+(difference_type n)
                noexcept(has_nothrow_minus_assignment_operator<iterator_type, difference_type>::value) {
            auto backup {*this};
            backup += n;
            return backup;
        }
        template <bool Boolean = true>
        typename enable_if<if_random_access_iterator()() and Boolean, reverse_iterator>::type
        operator-(difference_type n)
                noexcept(has_nothrow_minus_assignment_operator<iterator_type, difference_type>::value) {
            return *this + -n;
        }
        template <bool Boolean = true>
        explicit operator typename enable_if<is_convertible<iterator_type, bool>::value and Boolean, bool>::type()
                const noexcept(is_nothrow_convertible<iterator_type, bool>::value) {
            return static_cast<bool>(this->iter);
        }
    public:
        iterator_type base() const noexcept(is_nothrow_copy_constructible<iterator_type>::value) {
            return this->iter;
        }
    };
    template <typename IteratorLHS, typename IteratorRHS = IteratorLHS>
    inline auto operator-(const reverse_iterator<IteratorLHS> &lhs, const reverse_iterator<IteratorRHS> &rhs)
           noexcept((is_nothrow_convertible<IteratorLHS, IteratorRHS>::value or
                   is_nothrow_convertible<IteratorRHS, IteratorLHS>::value) and
                   is_nothrow_copy_constructible<IteratorLHS>::value and
                   is_nothrow_copy_constructible<IteratorRHS>::value and
                   has_nothrow_minus_operator<IteratorRHS, IteratorLHS>::value)
           -> typename enable_if<is_random_access_iterator<IteratorLHS>::value and
                   is_random_access_iterator<IteratorRHS>::value, decltype(lhs.base() - rhs.base())>::type {
        return rhs.base() - lhs.base();
    }
    template <typename IteratorLHS, typename IteratorRHS = IteratorLHS>
    inline bool operator==(const reverse_iterator<IteratorLHS> &lhs, const reverse_iterator<IteratorRHS> &rhs)
            noexcept((is_nothrow_convertible<IteratorLHS, IteratorRHS>::value or
                      is_nothrow_convertible<IteratorRHS, IteratorLHS>::value) and
                     is_nothrow_copy_constructible<IteratorLHS>::value and
                     is_nothrow_copy_constructible<IteratorRHS>::value and
                     has_nothrow_equal_to_operator<IteratorLHS, IteratorRHS>::value) {
        return rhs.base() == lhs.base();
    }
    template <typename IteratorLHS, typename IteratorRHS = IteratorLHS>
    inline bool operator!=(const reverse_iterator<IteratorLHS> &lhs, const reverse_iterator<IteratorRHS> &rhs)
            noexcept(has_nothrow_equal_to_operator<const reverse_iterator<IteratorLHS> &,
                    const reverse_iterator<IteratorRHS> &>::value) {
        return not(lhs == rhs);
    }
    template <typename IteratorLHS, typename IteratorRHS = IteratorLHS>
    inline typename enable_if<is_random_access_iterator<IteratorLHS>::value and
            is_random_access_iterator<IteratorRHS>::value, bool>::type
    operator<(const reverse_iterator<IteratorLHS> &lhs, const reverse_iterator<IteratorRHS> &rhs)
            noexcept((is_nothrow_convertible<IteratorLHS, IteratorRHS>::value or
                      is_nothrow_convertible<IteratorRHS, IteratorLHS>::value) and
                     is_nothrow_copy_constructible<IteratorLHS>::value and
                     is_nothrow_copy_constructible<IteratorRHS>::value and
                     has_nothrow_less_operator<IteratorLHS, IteratorRHS>::value) {
        return lhs < rhs;
    }
    template <typename IteratorLHS, typename IteratorRHS = IteratorLHS>
    inline typename enable_if<is_random_access_iterator<IteratorLHS>::value and
            is_random_access_iterator<IteratorRHS>::value, bool>::type
    operator>(const reverse_iterator<IteratorLHS> &lhs, const reverse_iterator<IteratorRHS> &rhs)
            noexcept(has_nothrow_less_operator<const reverse_iterator<IteratorRHS> &,
                    const reverse_iterator<IteratorLHS> &>::value) {
        return rhs < lhs;
    }
    template <typename IteratorLHS, typename IteratorRHS = IteratorLHS>
    inline typename enable_if<is_random_access_iterator<IteratorLHS>::value and
            is_random_access_iterator<IteratorRHS>::value, bool>::type
    operator<=(const reverse_iterator<IteratorLHS> &lhs, const reverse_iterator<IteratorRHS> &rhs)
            noexcept(has_nothrow_less_operator<const reverse_iterator<IteratorRHS> &,
                    const reverse_iterator<IteratorLHS> &>::value) {
        return not (lhs > rhs);
    }
    template <typename IteratorLHS, typename IteratorRHS = IteratorLHS>
    inline typename enable_if<is_random_access_iterator<IteratorLHS>::value and
            is_random_access_iterator<IteratorRHS>::value, bool>::type
    operator>=(const reverse_iterator<IteratorLHS> &lhs, const reverse_iterator<IteratorRHS> &rhs)
            noexcept(has_nothrow_less_operator<const reverse_iterator<IteratorLHS> &,
                    const reverse_iterator<IteratorRHS> &>::value) {
        return not(lhs < rhs);
    }
}

namespace data_structure {
    namespace __data_structure_auxiliary {
        template <typename T>
        struct forward_list_node final {
        public:
            using void_pointer = void *;
            using next_type = forward_list_node *;
            using value_type = T;
            using reference = typename add_lvalue_reference<value_type>::type;
            using const_reference = typename add_const_reference<value_type>::type;
            using rvalue_reference = typename add_rvalue_reference<value_type>::type;
            using pointer = typename add_pointer<value_type>::type;
            using const_pointer = typename add_const_pointer<value_type>::type;
        public:
            next_type next;
            value_type value;
        };

        template <typename T>
        inline constexpr typename T::previous_type test_previous_type_auxiliary(int) noexcept {
            static_assert(is_type<T>::value, "The function test_previous_type_auxiliary cannot be called!");
            return {};
        }
        template <typename T>
        inline constexpr void test_previous_type_auxiliary(...) noexcept {
            static_assert(is_type<T>::value, "The function test_previous_type_auxiliary cannot be called!");
        }
        template <typename T>
        inline constexpr typename T::next_type test_next_type_auxiliary(int) noexcept {
            static_assert(is_type<T>::value, "The function test_next_type_auxiliary cannot be called!");
            return {};
        }
        template <typename T>
        inline constexpr void test_next_type_auxiliary(...) noexcept {
            static_assert(is_type<T>::value, "The function test_next_type_auxiliary cannot be called!");
        }

        template <typename NodeType>
        struct node_type_traits final {
            using node_type = NodeType;
            using void_pointer = typename node_type::void_pointer;
            using next_type = decltype(test_next_type_auxiliary<node_type>(0));
            using previous_type = decltype(test_previous_type_auxiliary<node_type>(0));
            using value_type = typename node_type::value_type;
            using reference = typename node_type::reference;
            using const_reference = typename node_type::const_reference;
            using rvalue_reference = typename node_type::rvalue_reference;
            using pointer = typename node_type::pointer;
            using const_pointer = typename node_type::const_pointer;
        };
        template <typename T>
        struct node_type_traits<T *> final {
        public:
            using node_type = T *;
            using void_pointer = void *;
            using next_type = node_type;
            using previous_type = node_type;
            using value_type = typename remove_cvpointer<T *>::type;
            using reference = typename add_lvalue_reference<value_type>::type;
            using const_reference = typename add_const_reference<value_type>::type;
            using rvalue_reference = typename add_rvalue_reference<value_type>::type;
            using pointer = typename add_pointer<value_type>::type;
            using const_pointer = typename add_const_pointer<value_type>::type;
        };
    }
    template <typename NodeType, bool IsConst = false>
    class forward_list_iterator final {
        template <typename T, typename Allocator>
        friend class forward_list;
        template <typename NodeTp, bool IsConstLHS, bool IsConstRHS>
        friend bool operator==(const forward_list_iterator<NodeTp, IsConstLHS> &,
                const forward_list_iterator<NodeTp, IsConstRHS> &) noexcept;
        template <typename NodeTp, bool IsConstLHS, bool IsConstRHS>
        friend bool operator!=(const forward_list_iterator<NodeTp, IsConstLHS> &,
                const forward_list_iterator<NodeTp, IsConstRHS> &) noexcept;
    private:
        using node_type = typename add_pointer<NodeType>::type;
        using node_type_traits = __data_structure_auxiliary::node_type_traits<NodeType>;
    public:
        using size_type = size_t;
        using difference_type = ptrdiff_t;
        using value_type = typename node_type_traits::value_type;
        using reference = typename node_type_traits::reference;
        using const_reference = typename node_type_traits::const_reference;
        using rvalue_reference = typename node_type_traits::rvalue_reference;
        using pointer = typename node_type_traits::pointer;
        using const_pointer = typename node_type_traits::const_pointer;
        using iterator_category = forward_iterator_tag;
    private:
        node_type node;
    public:
        constexpr forward_list_iterator() noexcept = default;
        explicit constexpr forward_list_iterator(node_type node) noexcept : node {node} {}
        constexpr forward_list_iterator(const forward_list_iterator &) noexcept = default;
        constexpr forward_list_iterator(forward_list_iterator &&) noexcept = default;
        ~forward_list_iterator() noexcept = default;
    public:
        forward_list_iterator &operator=(const forward_list_iterator &) noexcept = default;
        forward_list_iterator &operator=(forward_list_iterator &&) noexcept = default;
        reference operator*() const noexcept {
            return this->node->value;
        }
        pointer operator->() const noexcept {
            return &**this;
        }
        forward_list_iterator &operator++() noexcept {
            this->node = this->node->next;
            return *this;
        }
        forward_list_iterator operator++(int) noexcept {
            auto tmp {*this};
            ++*this;
            return tmp;
        }
        explicit operator bool() const noexcept {
            return this->node;
        }
        operator forward_list_iterator<NodeType, true>() const noexcept {
            return forward_list_iterator<NodeType, true>(this->node);
        }
    };
    template <typename NodeType>
    class forward_list_iterator<NodeType, true> final {
        template <typename T, typename Allocator>
        friend class forward_list;
        template <typename NodeTp, bool IsConstLHS, bool IsConstRHS>
        friend bool operator==(const forward_list_iterator<NodeTp, IsConstLHS> &,
                const forward_list_iterator<NodeTp, IsConstRHS> &) noexcept;
        template <typename NodeTp, bool IsConstLHS, bool IsConstRHS>
        friend bool operator!=(const forward_list_iterator<NodeTp, IsConstLHS> &,
                const forward_list_iterator<NodeTp, IsConstRHS> &) noexcept;
    private:
        using node_type = typename add_pointer<NodeType>::type;
        using node_type_traits = __data_structure_auxiliary::node_type_traits<NodeType>;
    public:
        using size_type = size_t;
        using difference_type = ptrdiff_t;
        using value_type = typename node_type_traits::value_type;
        using reference = typename node_type_traits::reference;
        using const_reference = typename node_type_traits::const_reference;
        using rvalue_reference = typename node_type_traits::rvalue_reference;
        using pointer = typename node_type_traits::pointer;
        using const_pointer = typename node_type_traits::const_pointer;
        using iterator_category = forward_iterator_tag;
    private:
        node_type node;
    public:
        constexpr forward_list_iterator() noexcept = default;
        explicit constexpr forward_list_iterator(node_type node) : node {node} {}
        constexpr forward_list_iterator(const forward_list_iterator &) noexcept = default;
        constexpr forward_list_iterator(forward_list_iterator &&) noexcept = default;
        ~forward_list_iterator() noexcept = default;
    public:
        forward_list_iterator &operator=(const forward_list_iterator &) noexcept = default;
        forward_list_iterator &operator=(forward_list_iterator &&) noexcept = default;
        forward_list_iterator &operator=(forward_list_iterator<node_type, false> &&rhs) noexcept {
            this->node = move(rhs.node);
            return *this;
        }
        const_reference operator*() const noexcept {
            return this->node->value;
        }
        const_pointer operator->() const noexcept {
            return &**this;
        }
        forward_list_iterator &operator++() noexcept {
            this->node = this->node->next;
            return *this;
        }
        forward_list_iterator operator++(int) noexcept {
            auto tmp {*this};
            ++*this;
            return tmp;
        }
        operator forward_list_iterator<NodeType, false>() const noexcept {
            return forward_list_iterator<NodeType, false>(this->node);
        }
        explicit operator bool() const noexcept {
            return this->node;
        }
    };
    template <typename NodeType, bool IsConstLHS, bool IsConstRHS = IsConstLHS>
    inline bool operator==(const forward_list_iterator<NodeType, IsConstLHS> &lhs,
            const forward_list_iterator<NodeType, IsConstRHS> &rhs) noexcept {
        return lhs.node == rhs.node;
    }
    template <typename NodeType, bool IsConstLHS, bool IsConstRHS = IsConstLHS>
    inline bool operator!=(const forward_list_iterator<NodeType, IsConstLHS> &lhs,
            const forward_list_iterator<NodeType, IsConstRHS> &rhs) noexcept {
        return not(lhs == rhs);
    }
}

namespace data_structure {
    namespace __data_structure_auxiliary {
        template <typename T>
        struct list_node final {
        public:
            using void_pointer = void *;
            using next_type = list_node *;
            using previous_type = list_node *;
            using value_type = T;
            using reference = typename add_lvalue_reference<value_type>::type;
            using const_reference = typename add_const_reference<value_type>::type;
            using rvalue_reference = typename add_rvalue_reference<value_type>::type;
            using pointer = typename add_pointer<value_type>::type;
            using const_pointer = typename add_const_pointer<value_type>::type;
        public:
            next_type next;
            previous_type previous;
            value_type value;
        };
    }
    template <typename NodeType, bool IsConst = false>
    class list_iterator final {
        template <typename, typename>
        friend class list;
        template <typename NodeTp, bool IsConstLHS, bool IsConstRHS>
        friend bool operator==(const list_iterator<NodeTp, IsConstLHS> &,
                const list_iterator<NodeTp, IsConstRHS> &) noexcept;
        template <typename NodeTp, bool IsConstLHS, bool IsConstRHS>
        friend bool operator!=(const list_iterator<NodeTp, IsConstLHS> &,
                const list_iterator<NodeTp, IsConstRHS> &) noexcept;
    private:
        using node_type = typename add_pointer<NodeType>::type;
        using node_type_traits = __data_structure_auxiliary::node_type_traits<NodeType>;
    public:
        using size_type = size_t;
        using difference_type = ptrdiff_t;
        using value_type = typename node_type_traits::value_type;
        using reference = typename node_type_traits::reference;
        using const_reference = typename node_type_traits::const_reference;
        using rvalue_reference = typename node_type_traits::rvalue_reference;
        using pointer = typename node_type_traits::pointer;
        using const_pointer = typename node_type_traits::const_pointer;
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
            return &**this;
        }
        list_iterator &operator++() noexcept {
            this->node = this->node->next;
            return *this;
        }
        list_iterator operator++(int) noexcept {
            auto tmp {*this};
            ++*this;
            return tmp;
        }
        list_iterator &operator--() noexcept {
            this->node = this->node->previous;
            return *this;
        }
        list_iterator operator--(int) noexcept {
            auto tmp {*this};
            --*this;
            return tmp;
        }
        operator list_iterator<NodeType, true>() const noexcept {
            return list_iterator<NodeType, true>(this->node);
        }
        explicit operator bool() const noexcept {
            return this->node;
        }
    };
    template <typename NodeType>
    class list_iterator<NodeType, true> final {
        template <typename, typename>
        friend class list;
        template <typename NodeTp, bool IsConstLHS, bool IsConstRHS>
        friend bool operator==(const list_iterator<NodeTp, IsConstLHS> &,
                const list_iterator<NodeTp, IsConstRHS> &) noexcept;
        template <typename NodeTp, bool IsConstLHS, bool IsConstRHS>
        friend bool operator!=(const list_iterator<NodeTp, IsConstLHS> &,
                const list_iterator<NodeTp, IsConstRHS> &) noexcept;
    private:
        using node_type = typename add_pointer<NodeType>::type;
        using node_type_traits = __data_structure_auxiliary::node_type_traits<NodeType>;
    public:
        using size_type = size_t;
        using difference_type = ptrdiff_t;
        using value_type = typename node_type_traits::value_type;
        using reference = typename node_type_traits::reference;
        using const_reference = typename node_type_traits::const_reference;
        using rvalue_reference = typename node_type_traits::rvalue_reference;
        using pointer = typename node_type_traits::pointer;
        using const_pointer = typename node_type_traits::const_pointer;
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
        const_reference operator*() const noexcept {
            return this->node->value;
        }
        const_pointer operator->() const noexcept {
            return &**this;
        }
        list_iterator &operator++() noexcept {
            this->node = this->node->next;
            return *this;
        }
        list_iterator operator++(int) noexcept {
            auto tmp {*this};
            ++*this;
            return tmp;
        }
        list_iterator &operator--() noexcept {
            this->node = this->node->previous;
            return *this;
        }
        list_iterator operator--(int) noexcept {
            auto tmp {*this};
            --*this;
            return tmp;
        }
        operator list_iterator<NodeType, false>() const noexcept {
            return list_iterator<NodeType, false>(this->node);
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

#endif //DATA_STRUCTURE_ITERATOR_HPP
