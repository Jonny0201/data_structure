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

#ifndef DATA_STRUCTURE_DATA_STRUCTURE_HPP
#define DATA_STRUCTURE_DATA_STRUCTURE_HPP

#include "type_traits.hpp"
#include "iterator.hpp"
#include "allocator.hpp"
#include "functional.hpp"
#include "memory.hpp"
#include "vector.hpp"
#include "meta.hpp"
#include "algorithm.hpp"
#include "preprocessor.hpp"
#include "__config.hpp"

namespace data_structure {
    using size_t = decltype(sizeof 0);
    using ptrdiff_t = decltype(static_cast<int *>(nullptr) - static_cast<int *>(nullptr));
}

namespace ds = data_structure;

#endif //DATA_STRUCTURE_DATA_STRUCTURE_HPP
