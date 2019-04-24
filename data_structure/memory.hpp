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

#ifndef DATA_STRUCTURE_MEMORY_HPP
#define DATA_STRUCTURE_MEMORY_HPP

#include <memory>
#include <initializer_list>
#include <limits>
#include "meta.hpp"

namespace data_structure {
    template <typename T>
    constexpr inline auto address_of(T &arg) noexcept {
        return reinterpret_cast<T *>(
                &const_cast<char &>(reinterpret_cast<const volatile char &>(arg)));
    }
    template <typename T>
    constexpr inline auto addressof(T &arg) noexcept {
        return address_of(arg);
    }
}

namespace data_structure {
    template <bool>
    class __memory_pool_thread_support {};
    template <>
    class __memory_pool_thread_support<true> {
    protected:
        static bool mutex;
    protected:
        static bool wait_mutex() noexcept {
            if(mutex) {
                return true;
            }
            mutex = true;
            return false;
        }
    };
    bool __memory_pool_thread_support<true>::mutex {false};

    template <bool Thread = false, decltype(sizeof 0) Align = 8, decltype(sizeof 0) MaxBytes = 128>
    class __memory_pool : private __memory_pool_thread_support<Thread> {
    private:
        enum {
            align = Align,
            max_bytes = MaxBytes,
            free_list_extent = max_bytes / align
        };
        union free_list_node {
            free_list_node *free_list_link;
            char client_data[0];        //client_data[1] for compatibility
        };
        enum : bool {
            thread_support = Thread
        };
    private:
        using __base = __memory_pool_thread_support<thread_support>;
    public:
        using size_type = decltype(sizeof 0);
        using difference_type = decltype(static_cast<char *>(nullptr) - static_cast<char *>(nullptr));
        using pointer = void *;
        using const_pointer = const void *;
        using volatile_pointer = volatile void *;
        using cv_pointer = const volatile void *;
    private:
        static free_list_node *volatile free_list[free_list_extent];
        static char *start;
        static char *end;
        static size_type chunk_size;
#ifdef DATA_STRUCTURE_DEALLOCATE_MEMORY_POOL_MANUALLY
    private:
        static void **record;
        static size_type chunk_counter;
#endif
    private:
        constexpr static size_type round_up(size_type bytes) noexcept {
            return (bytes + align - 1) & ~(align - 1);
        }
        constexpr static size_type free_list_index(size_type bytes) noexcept {
            return (bytes + align - 1) / align - 1;
        }
    private:
        static void *refill(size_type);
        static void *refill(size_type, dynamic) noexcept;
        static char *chunk_alloc(size_type, size_type &);
        static char *chunk_alloc(size_type, size_type &, dynamic) noexcept;
    protected:
        void *operator new (size_type size) {
            return ::operator new (size);
        }
        void *operator new (size_type size, dynamic) noexcept {
            return ::operator new (size, std::nothrow);
        }
        void operator delete (void *p) noexcept {
            ::operator delete (p);
        }
        void operator delete (void *p, dynamic) noexcept {
            ::operator delete (p, std::nothrow);
        }
        void operator delete (void *p, size_type) noexcept {
            ::operator delete (p);
        }
        void operator delete(void *p, size_type, dynamic) noexcept {
            ::operator delete (p, std::nothrow);
        }
    public:
        static void *allocate(size_type);
        static void *allocate(size_type, dynamic) noexcept;
        static void deallocate(void *, size_type) noexcept;
        //static void *reallocate(void *, size_type, size_type);
        //static void *reallocate(void *, size_type, size_type, dynamic) noexcept;
    public:
        constexpr __memory_pool() noexcept = default;
        constexpr __memory_pool(const __memory_pool &) noexcept = default;
        constexpr __memory_pool(__memory_pool &&) noexcept = default;
    public:
        __memory_pool &operator=(const __memory_pool &) noexcept = default;
        __memory_pool &operator=(__memory_pool &&) noexcept = default;
        constexpr operator bool() const noexcept {
            return this->start;
        }
#ifdef DATA_STRUCTURE_DEALLOCATE_MEMORY_POOL_MANUALLY
    public:
        static void release() noexcept;
#endif
    };
    template <bool Thread, decltype(sizeof 0) Align, decltype(sizeof 0) MaxBytes>
    typename __memory_pool<Thread, Align, MaxBytes>::free_list_node *volatile
    __memory_pool<Thread, Align, MaxBytes>::free_list[free_list_extent] {};
    template <bool Thread, decltype(sizeof 0) Align, decltype(sizeof 0) MaxBytes>
    char *__memory_pool<Thread, Align, MaxBytes>::start {nullptr};
    template <bool Thread, decltype(sizeof 0) Align, decltype(sizeof 0) MaxBytes>
    char *__memory_pool<Thread, Align, MaxBytes>::end {nullptr};
    template <bool Thread, decltype(sizeof 0) Align, decltype(sizeof 0) MaxBytes>
    typename __memory_pool<Thread, Align, MaxBytes>::size_type
    __memory_pool<Thread, Align, MaxBytes>::chunk_size {0};
}

namespace data_structure {
    template <bool Thread, decltype(sizeof 0) Align, decltype(sizeof 0) MaxBytes>
    void *__memory_pool<Thread, Align, MaxBytes>::allocate(size_type size) {
        if(size > max_bytes) {
            return operator new (size);
        }
        if constexpr(thread_support) {
            while(__base::wait_mutex()) {}
        }
        auto first {*(free_list + free_list_index(size))};
        if(not first) {
            return refill(round_up(size));
        }
        auto result_node {first};
        first = result_node->free_list_link;
        if constexpr(thread_support) {
            __base::mutex = false;
        }
        return result_node;
    }
    template <bool Thread, decltype(sizeof 0) Align, decltype(sizeof 0) MaxBytes>
    void *__memory_pool<Thread, Align, MaxBytes>::allocate(size_type size, dynamic) noexcept {
        if(size > max_bytes) {
            return operator new (size, {});
        }
        if constexpr(thread_support) {
            while(__base::wait_mutex()) {}
        }
        auto first {*(free_list + free_list_index(size))};
        if(not first) {
            return refill(round_up(size), {});
        }
        auto result_node {first};
        first = result_node->free_list_link;
        if constexpr(thread_support) {
            __base::mutex = false;
        }
        return result_node;
    }
    template <bool Thread, decltype(sizeof 0) Align, decltype(sizeof 0) MaxBytes>
    void __memory_pool<Thread, Align, MaxBytes>::deallocate(void *p, size_type size) noexcept {
        if(size > max_bytes) {
            operator delete (p, size);
            return;
        }
        if constexpr(thread_support) {
            while(__base::wait_mutex()) {}
        }
        auto first {*(free_list + free_list_index(size))};
        auto return_node {reinterpret_cast<free_list_node *>(p)};
        return_node->free_list_link = first;
        first = return_node;
        if constexpr(thread_support) {
            __base::mutex = false;
        }
    }
    template <bool Thread, decltype(sizeof 0) Align, decltype(sizeof 0) MaxBytes>
    void *__memory_pool<Thread, Align, MaxBytes>::refill(size_type size) {
        size_type nodes {16};
        auto chunk {chunk_alloc(size, nodes)};
        if(nodes == 1) {
            return chunk;
        }
        auto current_node {reinterpret_cast<free_list_node *>(chunk + size)};
        *(free_list + free_list_index(size)) = current_node;
        while(--nodes > 1) {
            auto next_node {
                reinterpret_cast<free_list_node *>(reinterpret_cast<char *>(current_node) + size)
            };
            current_node->free_list_link = next_node;
            current_node = next_node;
        }
        current_node->free_list_link = nullptr;
        return chunk;
    }
    template <bool Thread, decltype(sizeof 0) Align, decltype(sizeof 0) MaxBytes>
    void *__memory_pool<Thread, Align, MaxBytes>::refill(size_type size, dynamic) noexcept {
        size_type nodes {16};
        auto chunk {chunk_alloc(size, nodes, {})};
        if(nodes == 1) {
            return chunk;
        }
        auto current_node {reinterpret_cast<free_list_node *>(chunk + size)};
        *(free_list + free_list_index(size)) = current_node;
        while(--nodes > 2) {
            auto next_node {
                    reinterpret_cast<free_list_node *>(reinterpret_cast<char *>(current_node) + size)
            };
            current_node->free_list_link = next_node;
            current_node = next_node;
        }
        current_node->free_list_link = nullptr;
        return chunk;
    }
    template <bool Thread, decltype(sizeof 0) Align, decltype(sizeof 0) MaxBytes>
    char *__memory_pool<Thread, Align, MaxBytes>::chunk_alloc(size_type size, size_type &nodes) {
        auto total_bytes {size * nodes};
        auto bytes_left {static_cast<size_type>(end - start)};
        if(bytes_left >= total_bytes) {
            auto result {start};
            start += total_bytes;
            return result;
        }else if(bytes_left >= size) {
            nodes = bytes_left / size;
            auto result {start};
            start += nodes * size;
            return result;
        }
        auto bytes_to_get {2 * total_bytes + round_up(chunk_size >> 4)};
        if(bytes_left > 0) {
            auto first {*(free_list + free_list_index(bytes_left))};
            auto new_first {reinterpret_cast<free_list_node *>(start)};
            new_first->free_list_link = first;
            first = new_first;
        }
        start = reinterpret_cast<char *>(operator new (max_bytes, {}));
        if(not start) {
            start = reinterpret_cast<char *>(operator new (bytes_to_get, {}));
            if(start) {
                chunk_size += bytes_to_get;
                end = start + chunk_size;
                return chunk_alloc(size, nodes);
            }
            for(auto i {size}; i <= max_bytes; i += align) {
                auto first {*(free_list + free_list_index(i))};
                if(first) {
                    start = reinterpret_cast<char *>(first);
                    first = first->free_list_link;
                    end = start + i;
                    return chunk_alloc(size, nodes);
                }
            }
        }
        chunk_size += bytes_to_get;
        end = start + bytes_to_get;
        return chunk_alloc(size, nodes);
    }
    template <bool Thread, decltype(sizeof 0) Align, decltype(sizeof 0) MaxBytes>
    char *__memory_pool<Thread, Align, MaxBytes>::chunk_alloc(size_type size, size_type &nodes, dynamic)
            noexcept {
        auto total_bytes {size * nodes};
        auto bytes_left {static_cast<size_type>(end - start)};
        if(bytes_left >= total_bytes) {
            auto result {start};
            start += total_bytes;
            return result;
        }else if(bytes_left >= size) {
            nodes = bytes_left / size;
            auto result {start};
            start += nodes * size;
            return result;
        }
        auto bytes_to_get {2 * total_bytes + round_up(chunk_size >> 4)};
        if(bytes_left > 0) {
            auto first {*(free_list + free_list_index(bytes_left))};
            auto new_first {reinterpret_cast<free_list_node *>(start)};
            new_first->free_list_link = first;
            first = new_first;
        }
        start = reinterpret_cast<char *>(operator new (max_bytes, {}));
        if(not start) {
            start = reinterpret_cast<char *>(operator new (bytes_to_get, {}));
            if(start) {
                chunk_size += bytes_to_get;
                end = start + chunk_size;
                return chunk_alloc(size, nodes);
            }
            for(auto i {size}; i <= max_bytes; i += align) {
                auto first {*(free_list + free_list_index(i))};
                if(first) {
                    start = reinterpret_cast<char *>(first);
                    first = first->free_list_link;
                    end = start + i;
                    return chunk_alloc(size, nodes);
                }
            }
        }
        chunk_size += bytes_to_get;
        end = start + bytes_to_get;
        return chunk_alloc(size, nodes);
    }
}

#endif //DATA_STRUCTURE_MEMORY_HPP
