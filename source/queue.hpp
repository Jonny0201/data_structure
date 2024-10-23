/*
    * Copyright © [2019 - 2024] [Jonny]
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

#ifndef DATA_STRUCTURE_QUEUE_HPP
#define DATA_STRUCTURE_QUEUE_HPP

#include "deque.hpp"

namespace data_structure {

__DATA_STRUCTURE_START(queue implementation)
template <typename T, typename Container>
class queue {
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
            "The value type of queue should be same as the container's value_type!");
private:
    Container container;
public:
    constexpr queue() = default;
    explicit constexpr queue(const Container &container) : container {container} {}
    explicit constexpr queue(Container &&container) : container {ds::move(container)} {}
    constexpr queue(const queue &) = default;
    constexpr queue(queue &&) noexcept = default;
    constexpr ~queue() noexcept = default;
public:
    constexpr queue &operator=(const queue &) = default;
    constexpr queue &operator=(queue &&) noexcept = default;
    constexpr queue &operator=(const Container &rhs) {
        this->container = rhs;
        return *this;
    }
    constexpr queue &operator=(Container &&rhs) noexcept {
        this->container = ds::move(rhs);
        return *this;
    }
public:
    [[nodiscard]]
    constexpr reference front() noexcept {
        return this->container.front();
    }
    [[nodiscard]]
    constexpr const_reference front() const noexcept {
        return this->container.front();
    }
    [[nodiscard]]
    constexpr reference back() noexcept {
        return this->container.back();
    }
    [[nodiscard]]
    constexpr const_reference back() const noexcept {
        return this->container.back();
    }
    [[nodiscard]]
    constexpr bool empty() const noexcept {
        return this->container.empty();
    }
    [[nodiscard]]
    constexpr size_type size() const noexcept {
        return this->container.size();
    }
    constexpr void swap(queue &rhs) noexcept {
        this->container.swap(rhs.container);
    }
    constexpr void push(const_reference value) {
        this->container.emplace_back(value);
    }
    constexpr void push(rvalue_reference value) {
        this->container.emplace_back(ds::move(value));
    }
    template <typename ...Args>
    constexpr void emplace(Args &&...args) {
        this->container.emplace_back(ds::forward<Args>(args)...);
    }
    constexpr void pop() noexcept {
        this->container.pop_back();
    }
};
__DATA_STRUCTURE_END(queue implementation)

}       // namespace data_structure

#endif      // DATA_STRUCTURE_QUEUE_HPP