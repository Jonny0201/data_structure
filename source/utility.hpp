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

#ifndef DATA_STRUCTURE_UTILITY_HPP
#define DATA_STRUCTURE_UTILITY_HPP

#include "type_traits.hpp"

namespace data_structure {

__DATA_STRUCTURE_START(move and forward)
template <typename T>
inline constexpr remove_reference_t<T> &&move(T &&value) noexcept {
    return static_cast<remove_reference_t<T> &&>(value);
}
template <bool Conditional, typename T>
inline constexpr conditional_t<Conditional, remove_reference_t<T> &&, const T &>
move_if(T &value) noexcept {
    return ds::move(value);
}
template <typename T>
inline constexpr T &&forward(remove_reference_t<T> &value) noexcept {
    return static_cast<T &&>(value);
}
template <typename T>
inline constexpr T &&forward(remove_reference_t<T> &&value) noexcept {
    static_assert(is_lvalue_reference_v<T>, "Cannot forward an rvalue as an lvalue!");
    return static_cast<T &&>(value);
}
__DATA_STRUCTURE_END

__DATA_STRUCTURE_START(transaction tool)
template <typename Rollback>
class transaction {
private:
    Rollback rollback_block;
    bool done;
public:
    explicit transaction(Rollback rollback_block) noexcept(is_nothrow_move_constructible_v<Rollback>) :
            rollback_block {ds::move(rollback_block)}, done {} {}
    transaction(const transaction &) = delete;
    transaction(transaction &&rhs) noexcept(is_nothrow_move_constructible_v<Rollback>) :
            rollback_block {ds::move(rhs.rollback_block)}, done {} {
        rhs.done = true;
    }
    ~transaction() noexcept {
        if(not this->done) {
            this->rollback_block();
        }
    }
public:
    transaction &operator=(const transaction &) = delete;
    transaction &operator=(transaction &&) = delete;
public:
    void complete() noexcept {
        this->done = true;
    }
    void rollback() noexcept {
        this->rollback_block();
        this->done = true;
    }
    Rollback &get_rollback() & noexcept {
        return this->rollback_block;
    }
};
__DATA_STRUCTURE_END

}       // namespace data_structure

#endif //DATA_STRUCTURE_UTILITY_HPP