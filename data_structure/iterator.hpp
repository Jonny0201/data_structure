/*
    * Copyright © [2019] [Jonny Charlotte]
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
        using size_type = decltype(sizeof 0);
        using difference_type = decltype(static_cast<int *>(nullptr) - static_cast<int *>(nullptr));
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
    class __wrap_iterator {
    private:
        using iterator_type = Iterator;
    public:
        using size_type = typename iterator_traits<iterator_type>::size_type;
        using difference_type = typename iterator_traits<iterator_type>::difference_type;
        using value_type = typename iterator_traits<iterator_type>::value_type;
        using reference = typename iterator_traits<iterator_type>::reference;
        using const_reference = typename iterator_traits<iterator_type>::const_reference;
        using rvalue_reference = typename iterator_traits<iterator_type>::rvalue_reference;
        using pointer = typename iterator_traits<iterator_type>::pointer;
        using const_pointer = typename iterator_traits<iterator_type>::const_pointer;
        using iterator_category = typename iterator_traits<iterator_type>::iterator_category;
    private:
        iterator_type iter;
    private:
        template <typename IteratorRHS>
        constexpr __wrap_iterator(const __wrap_iterator<IteratorRHS> &iter,
                typename enable_if<is_constructible<iterator_type, IteratorRHS>::value>::type *) noexcept :
                iter {iter.base()} {}
    public:
        constexpr __wrap_iterator() noexcept = default;
        constexpr __wrap_iterator(iterator_type iter) noexcept : iter {iter} {}
        template <typename IteratorRHS>
        constexpr __wrap_iterator(const __wrap_iterator<IteratorRHS> &iter) noexcept :
                __wrap_iterator(iter, nullptr) {}
        constexpr __wrap_iterator(const __wrap_iterator &rhs) noexcept = default;
        constexpr __wrap_iterator(__wrap_iterator &&rhs) noexcept = default;
        ~__wrap_iterator() noexcept = default;
    public:
        __wrap_iterator &operator=(const __wrap_iterator &) noexcept = default;
        __wrap_iterator &operator=(__wrap_iterator &&) noexcept = default;
        reference operator*() const noexcept {
            return *this->iter;
        }
        pointer operator->() const noexcept {
            return this->iter;
        }
        __wrap_iterator &operator++() noexcept {
            ++this->iter;
            return *this;
        }
        __wrap_iterator operator++(int) noexcept {
            auto tmp {*this};
            ++this->iter;
            return tmp;
        }
        __wrap_iterator &operator--() noexcept {
            --this->iter;
            return *this;
        }
        __wrap_iterator operator--(int) noexcept {
            auto tmp {*this};
            --this->iter;
            return tmp;
        }
        __wrap_iterator &operator+=(difference_type n) noexcept {
            this->iter += n;
            return *this;
        }
        __wrap_iterator operator+(difference_type n) const noexcept {
            auto tmp {*this};
            tmp += n;
            return tmp;
        }
        __wrap_iterator &operator-=(difference_type n) noexcept {
            return *this += -n;
        }
        __wrap_iterator operator-(difference_type n) const noexcept {
            auto tmp {*this};
            tmp -= n;
            return tmp;
        }
        reference operator[](difference_type n) const noexcept {
            return *(this->iter + n);
        }
    public:
        iterator_type base() const noexcept {
            return this->iter;
        }
    };
    template <typename IteratorLHS, typename IteratorRHS>
    inline bool operator-(const __wrap_iterator<IteratorLHS> &lhs,
            const __wrap_iterator<IteratorRHS> &rhs) noexcept {
        return lhs.base() - rhs.base();
    }
    template <typename IteratorLHS, typename IteratorRHS>
    inline bool operator==(const __wrap_iterator<IteratorLHS> &lhs,
            const __wrap_iterator<IteratorRHS> &rhs) noexcept {
        return lhs.base() == rhs.base();
    }
    template <typename IteratorLHS, typename IteratorRHS>
    inline bool operator!=(const __wrap_iterator<IteratorLHS> &lhs,
                           const __wrap_iterator<IteratorRHS> &rhs) noexcept {
        return not(lhs == rhs);
    }
    template <typename IteratorLHS, typename IteratorRHS>
    inline bool operator<(const __wrap_iterator<IteratorLHS> &lhs,
                           const __wrap_iterator<IteratorRHS> &rhs) noexcept {
        return lhs.base() - rhs.base() < 0;
    }
    template <typename IteratorLHS, typename IteratorRHS>
    inline bool operator<=(const __wrap_iterator<IteratorLHS> &lhs,
                           const __wrap_iterator<IteratorRHS> &rhs) noexcept {
        return lhs.base() - rhs.base() <= 0;
    }
    template <typename IteratorLHS, typename IteratorRHS>
    inline bool operator>(const __wrap_iterator<IteratorLHS> &lhs,
                           const __wrap_iterator<IteratorRHS> &rhs) noexcept {
        return not(lhs <= rhs);
    }
    template <typename IteratorLHS, typename IteratorRHS>
    inline bool operator>=(const __wrap_iterator<IteratorLHS> &lhs,
                           const __wrap_iterator<IteratorRHS> &rhs) noexcept {
        return not(lhs < rhs);
    }
}

namespace data_structure {
    template <typename Iterator>
    class reverse_iterator {
    private:
        using iterator_type = Iterator;
    public:
        using size_type = typename iterator_traits<iterator_type>::size_type;
        using difference_type = typename iterator_traits<iterator_type>::difference_type;
        using value_type = typename iterator_traits<iterator_type>::value_type;
        using reference = typename iterator_traits<iterator_type>::reference;
        using const_reference = typename iterator_traits<iterator_type>::const_reference;
        using rvalue_reference = typename iterator_traits<iterator_type>::rvalue_reference;
        using pointer = typename iterator_traits<iterator_type>::pointer;
        using const_pointer = typename iterator_traits<iterator_type>::const_pointer;
        using iterator_category = typename iterator_traits<iterator_type>::iterator_category;
    private:
        iterator_type iter;
    private:
        template <typename IteratorRHS>
        constexpr reverse_iterator(const reverse_iterator<IteratorRHS> &iter,
                                   typename enable_if<is_constructible<iterator_type, IteratorRHS>::value>::type *)
        noexcept(is_nothrow_constructible<iterator_type, IteratorRHS>::value) :
                iter {iter.base()} {}
    public:
        constexpr reverse_iterator() = default;
        constexpr reverse_iterator(iterator_type iter)
        noexcept(is_nothrow_copy_constructible<iterator_type>::value) : iter {iter} {}
        template <typename IteratorRHS>
        constexpr reverse_iterator(const reverse_iterator<IteratorRHS> &iter)
        noexcept(is_nothrow_constructible<iterator_type, IteratorRHS>::value) :
                reverse_iterator(iter, nullptr) {}
        constexpr reverse_iterator(const reverse_iterator &rhs)
        noexcept(is_nothrow_copy_constructible<iterator_type>::value) = default;
        constexpr reverse_iterator(reverse_iterator &&rhs)
        noexcept(is_nothrow_move_constructible<iterator_type>::value) = default;
        ~reverse_iterator() noexcept(is_nothrow_destructible<iterator_type>::value) = default;
    public:
        reverse_iterator &operator=(const reverse_iterator &)
        noexcept(is_nothrow_copy_assignable<iterator_type>::value) = default;
        reverse_iterator &operator=(reverse_iterator &&)
        noexcept(is_nothrow_move_assignable<iterator_type>::value) = default;
        reference operator*() const
        noexcept(is_nothrow_copy_constructible<iterator_type>::value and
                 has_nothrow_dereference_operator<iterator_type>::value and
                 has_nothrow_pre_decrement_operator<iterator_type>::value) {
            auto tmp {this->iter};
            return *--tmp;
        }
        pointer operator->() const noexcept(has_nothrow_dereference_operator<reverse_iterator>::value) {
            return address_of(this->operator*());
        }
        reverse_iterator &operator++() noexcept(has_nothrow_pre_decrement_operator<iterator_type>::value) {
            --this->iter;
            return *this;
        }
        reverse_iterator operator++(int)
        noexcept(has_nothrow_pre_increment_operator<reverse_iterator>::value) {
            auto tmp {*this};
            ++*this;
            return tmp;
        }
        reverse_iterator &operator--() noexcept(has_nothrow_pre_increment_operator<iterator_type>::value) {
            ++this->iter;
            return *this;
        }
        reverse_iterator operator--(int)
        noexcept(has_nothrow_pre_increment_operator<reverse_iterator>::value) {
            auto tmp {*this};
            --*this;
            return tmp;
        }
        reverse_iterator &operator+=(difference_type n)
        noexcept(has_nothrow_minus_assignment_operator<iterator_type>::value) {
            this->iter -= n;
            return *this;
        }
        reverse_iterator operator+(difference_type n) const
        noexcept(has_nothrow_minus_operator<iterator_type>::value and
                 is_nothrow_constructible<reverse_iterator, iterator_type>::value) {
            return reverse_iterator {this->iter - n};
        }
        reverse_iterator &operator-=(difference_type n)
        noexcept(has_nothrow_plus_assignment_operator<iterator_type>::value) {
            this->iter += n;
            return *this;
        }
        reverse_iterator operator-(difference_type n) const
        noexcept(has_nothrow_plus_operator<iterator_type>::value and
                 is_nothrow_constructible<reverse_iterator, iterator_type>::value) {
            return reverse_iterator {this->iter + n};
        }
        reference operator[](difference_type n) const
        noexcept(has_nothrow_subscripting_operator<iterator_type, difference_type>::value) {
            return this->iter[n];
        }
    public:
        iterator_type base() const noexcept(has_nothrow_dereference_operator<reverse_iterator>::value) {
            return this->operator->();
        }
    };
    template <typename IteratorLHS, typename IteratorRHS>
    inline bool operator-(const reverse_iterator<IteratorLHS> &lhs,
                          const reverse_iterator<IteratorRHS> &rhs) noexcept {
        return lhs.base() - rhs.base();
    }
    template <typename IteratorLHS, typename IteratorRHS>
    inline bool operator==(const reverse_iterator<IteratorLHS> &lhs,
                           const reverse_iterator<IteratorRHS> &rhs) noexcept {
        return lhs.base() == rhs.base();
    }
    template <typename IteratorLHS, typename IteratorRHS>
    inline bool operator!=(const reverse_iterator<IteratorLHS> &lhs,
                           const reverse_iterator<IteratorRHS> &rhs) noexcept {
        return not(lhs == rhs);
    }
    template <typename IteratorLHS, typename IteratorRHS>
    inline bool operator<(const reverse_iterator<IteratorLHS> &lhs,
                          const reverse_iterator<IteratorRHS> &rhs) noexcept {
        return lhs.base() - rhs.base() < 0;
    }
    template <typename IteratorLHS, typename IteratorRHS>
    inline bool operator<=(const reverse_iterator<IteratorLHS> &lhs,
                           const reverse_iterator<IteratorRHS> &rhs) noexcept {
        return lhs.base() - rhs.base() <= 0;
    }
    template <typename IteratorLHS, typename IteratorRHS>
    inline bool operator>(const reverse_iterator<IteratorLHS> &lhs,
                          const reverse_iterator<IteratorRHS> &rhs) noexcept {
        return not(lhs <= rhs);
    }
    template <typename IteratorLHS, typename IteratorRHS>
    inline bool operator>=(const reverse_iterator<IteratorLHS> &lhs,
                           const reverse_iterator<IteratorRHS> &rhs) noexcept {
        return not(lhs < rhs);
    }
}

#endif //DATA_STRUCTURE_ITERATOR_HPP
