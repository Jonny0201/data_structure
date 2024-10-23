/*
    * Copyright © [2019 - 2021] [Jonny]
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

#ifndef DATA_STRUCTURE_STACK_HPP
#define DATA_STRUCTURE_STACK_HPP

#include "deque.hpp"

namespace data_structure {

__DATA_STRUCTURE_START(stack implementation)
template <typename T, typename Container>
class stack {
public:
    using container_type = Container;
    using size_type = typename container_type::size_type;
    using difference_type = typename container_type::difference_type;
    using value_type = T;
    using reference = typename container_type::reference;
    using const_reference = typename container_type::const_reference;
    using rvalue_reference = typename container_type::rvalue_reference;
    using pointer = typename container_type::pointer;
    using const_pointer = typename container_type::const_pointer;
    static_assert(is_same<T, typename container_type::value_type>::value,
            "The value type of stack should be same as the container's value_type!");
private:
    Container container;
public:
    constexpr stack() = default;
    explicit constexpr stack(const Container &container) : container {container} {}
    explicit constexpr stack(Container &&container) noexcept : container {ds::move(container)} {}
    constexpr stack(const stack &) = default;
    constexpr stack(stack &&) noexcept = default;
    constexpr ~stack() noexcept = default;
public:
    constexpr stack &operator=(const stack &) = default;
    constexpr stack &operator=(stack &&) noexcept = default;
    constexpr stack &operator=(const Container &rhs) {
        this->container = rhs;
        return *this;
    }
    constexpr stack &operator=(Container &&rhs) noexcept {
        this->container = ds::move(rhs);
        return *this;
    }
public:
    [[nodiscard]]
    constexpr reference top() noexcept {
        return this->container.back();
    }
    [[nodiscard]]
    constexpr const_reference top() const noexcept {
        return this->container.back();
    }
    [[nodiscard]]
    constexpr size_type size() const noexcept {
        return this->container.size();
    }
    void swap(stack &rhs) noexcept {
        this->container.swap(rhs.container);
    }
    void push(const_reference value) {
        this->container.emplace_back(value);
    }
    void push(rvalue_reference value) {
        this->container.emplace_back(ds::move(value));
    }
    template <typename ...Args>
    void emplace(Args &&...args) {
        this->container.emplace_back(ds::forward<Args>(args)...);
    }
    void pop() noexcept {
        this->container.pop_back();
    }
};
__DATA_STRUCTURE_END(stack implementation)

}       // namespace data_structure

#endif      // DATA_STRUCTURE_STACK_HPP