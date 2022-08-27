/*
    * Copyright © [2019 - 2022] [Jonny Charlotte]
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

#include "__config.hpp"
#include "meta.hpp"

namespace data_structure {
    template <typename T>
    constexpr inline T *address_of(T &arg) noexcept {
        return reinterpret_cast<T *>(&const_cast<char &>(reinterpret_cast<const volatile char &>(arg)));
    }
}

namespace data_structure {
    template <size_t Align = 8, size_t MaxBytes = 128>
    class memory_pool {
    private:
        union free_list_node {
            free_list_node *free_list_link;
            char client_data[sizeof free_list_link];
        };
    private:
        constexpr static auto align {Align};
        constexpr static auto max_bytes {MaxBytes};
        constexpr static auto free_list_extent {max_bytes / align};
    private:
        static free_list_node *volatile free_list[free_list_extent];
        static char *start;
        static char *end;
        static size_t chunk_size;
#ifdef DATA_STRUCTURE_DEALLOCATE_MEMORY_POOL_MANUALLY
    private:
        static void **chunk_record;
        static size_t chunk_size;
#endif
    private:
        static constexpr size_t round_up(size_t bytes) noexcept {
            return (bytes + align - 1) & ~(align - 1);
        }
        static constexpr size_t free_list_index(size_t bytes) noexcept {
            return (bytes + align - 1) / align - 1;
        }
    private:
        static void *refill(size_t);
        static char *chunk_alloc(size_t, size_t &);
    protected:
        void *operator new(size_t size) {
            return ::operator new(size);
        }
        void *operator new(size_t size, meta::dynamic) noexcept {
            return ::operator new(size, std::nothrow);
        }
        void *operator new[](size_t size) {
            return ::operator new[](size);
        }
        void *operator new[](size_t size, meta::dynamic) noexcept {
            return ::operator new[](size, std::nothrow);
        }
        void *operator new(size_t size, align_val_t align) {
            return ::operator new(size, align);
        }
        void *operator new(size_t size, align_val_t align, meta::dynamic) noexcept {
            return ::operator new(size, align, std::nothrow);
        }
        void *operator new[](size_t size, align_val_t align) {
            return ::operator new[](size, align);
        }
        void *operator new[](size_t size, align_val_t align, meta::dynamic) noexcept {
            return ::operator new[](size, align, std::nothrow);
        }
        void operator delete(void *p) noexcept {
            ::operator delete(p);
        }
        void operator delete(void *p, meta::dynamic) noexcept {
            ::operator delete(p, std::nothrow);
        }
        void operator delete[](void *p) noexcept {
            ::operator delete[](p);
        }
        void operator delete[](void *p, meta::dynamic) noexcept {
            ::operator delete[](p, std::nothrow);
        }
        void operator delete(void *p, size_t size) noexcept {
            ::operator delete(p, size);
        }
        void operator delete[](void *p, size_t size) noexcept {
            ::operator delete[](p, size);
        }
        void operator delete(void *p, align_val_t align) noexcept {
            ::operator delete(p, align);
        }
        void operator delete(void *p, align_val_t align, meta::dynamic) noexcept {
            ::operator delete(p, align, std::nothrow);
        }
        void operator delete[](void *p, align_val_t align) noexcept {
            ::operator delete[](p, align);
        }
        void operator delete[](void *p, align_val_t align, meta::dynamic) noexcept {
            ::operator delete[](p, align, std::nothrow);
        }
        void operator delete(void *p, size_t size, align_val_t align) noexcept {
            ::operator delete(p, size, align);
        }
        void operator delete[](void *p, size_t size, align_val_t align) noexcept {
            ::operator delete(p, size, align);
        }
        void operator delete(void *p, size_t size, align_val_t align, meta::dynamic) noexcept {
            ::operator delete(p, size, align);
        }
        void operator delete[](void *p, size_t size, align_val_t align, meta::dynamic) noexcept {
            ::operator delete(p, size, align);
        }
        void operator delete(void *p, void *place) noexcept {
            ::operator delete(p, place);
        }
        void operator delete[](void *p, void *place) noexcept {
            ::operator delete(p, place);
        }
    public:
        template <bool NoThrow = false>
        static void *allocate(size_t);
        static void deallocate(void *, size_t) noexcept;
    public:
        constexpr memory_pool() noexcept = default;
        constexpr memory_pool(const memory_pool &) noexcept = default;
        constexpr memory_pool(memory_pool &&) noexcept = default;
        ~memory_pool() noexcept = default;
    public:
        constexpr memory_pool &operator=(const memory_pool &) noexcept = default;
        constexpr memory_pool &operator=(memory_pool &&) noexcept = default;
        explicit constexpr operator bool() const noexcept {
            return this->start;
        }
#ifdef DATA_STRUCTURE_DEALLOCATE_MEMORY_POOL_MANUALLY
    public:
        static void release() noexcept;
#endif
    };
}

namespace data_structure {
    template <size_t Align, size_t MaxBytes>
    typename memory_pool<Align, MaxBytes>::free_list_node *volatile
            memory_pool<Align, MaxBytes>::free_list[free_list_extent] {};
    template <size_t Align, size_t MaxBytes>
    char *memory_pool<Align, MaxBytes>::start {};
    template <size_t Align, size_t MaxBytes>
    char *memory_pool<Align, MaxBytes>::end {};
    template <size_t Align, size_t MaxBytes>
    size_t memory_pool<Align, MaxBytes>::chunk_size {0};
#ifdef DATA_STRUCTURE_DEALLOCATE_MEMORY_POOL_MANUALLY
    template <size_t Align, size_t MaxBytes>
    void **memory_pool<Align, MaxByes>::chunk_record {};
    template <size_t Align, size_t MaxBytes>
    size_t memory_pool<Align, MaxBytes>::chunk_record_size {0};
#endif

    template <size_t Align, size_t MaxBytes>
    template <bool NoThrow>
    void *memory_pool<Align, MaxBytes>::allocate(size_t size) {
        if(size > max_bytes) {
            if constexpr(NoThrow) {
                return memory_pool::operator new(size, {});
            }else {
                return memory_pool::operator new(size);
            }
        }
        auto first {*(free_list + free_list_index(size))};
        if(not first) {
            return refill(round_up(size));
        }
        auto result_node {first};
        first = result_node->free_list_link;
        return result_node;
    }
    template <size_t Align, size_t MaxBytes>
    void memory_pool<Align, MaxBytes>::deallocate(void *p, size_t size) noexcept {
        if(size > max_bytes) {
            memory_pool::operator delete(p, size);
            return;
        }
        auto &first {*(free_list + free_list_index(size))};
        auto return_node {static_cast<free_list_node *>(p)};
        return_node->free_list_link = first;
        first = return_node;
    }
    template <size_t Align, size_t MaxBytes>
    void *memory_pool<Align, MaxBytes>::refill(size_t size) {
        size_t nodes {16};
        auto chunk {chunk_alloc(size, nodes)};
        if(nodes == 1) {
            return chunk;
        }
        auto current_node {reinterpret_cast<free_list_node *>(chunk + size)};
        *(free_list + free_list_index(size)) = current_node;
        while(--nodes > 1) {
            auto next_node {reinterpret_cast<free_list_node *>(reinterpret_cast<char *>(current_node) + size)};
            current_node->free_list_link = next_node;
            current_node = next_node;
        }
        current_node->free_list_link = nullptr;
        return chunk;
    }
    template <size_t Align, size_t MaxBytes>
    char *memory_pool<Align, MaxBytes>::chunk_alloc(size_t size, size_t &nodes) {
        auto total_bytes {size * nodes};
        auto bytes_left {static_cast<size_t>(end - start)};
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
            auto &first {*(free_list + free_list_index(bytes_left))};
            auto new_first {reinterpret_cast<free_list_node *>(start)};
            new_first->free_list_link = first;
            first = new_first;
        }
        start = static_cast<char *>(memory_pool::operator new(bytes_to_get, {}));
        if(not start) {
            for(auto i {size}; i <= max_bytes; i += align) {
                auto &first {*(free_list + free_list_index(i))};
                if(first) {
                    start = reinterpret_cast<char *>(first);
                    first = first->free_list_link;
                    end = start + i;
                    return chunk_alloc(size, nodes);
                }
            }
            end = nullptr;
            start = static_cast<char *>(memory_pool::operator new(bytes_to_get));
            if(start) {
                chunk_size += bytes_to_get;
                end = start + chunk_size;
#ifdef DATA_STRUCTURE_DEALLOCATE_MEMORY_POOL_MANUALLY
                void **new_chunk_record = new void *[chunk_size + 1];
                ds::memory_set(new_chunk_record, chunk_record, sizeof(void *) * chunk_record);
                new_chunk_record[chunk_size++] = start;
                delete[] chunk_record;
                chunk_record = new_chunk_record;
#endif
                return chunk_alloc(size, nodes);
            }
        }
        chunk_size += bytes_to_get;
        end = start + bytes_to_get;
#ifdef DATA_STRUCTURE_DEALLOCATE_MEMORY_POOL_MANUALLY
        void **new_chunk_record = new void *[chunk_size + 1];
        ds::memory_set(new_chunk_record, chunk_record, sizeof(void *) * chunk_record);
        new_chunk_record[chunk_size++] = start;
        delete[] chunk_record;
        chunk_record = new_chunk_record;
#endif
        return chunk_alloc(size, nodes);
    }
#ifdef DATA_STRUCTURE_DEALLOCATE_MEMORY_POOL_MANUALLY
    template <size_t Align, size_t MaxBytes>
    void memory_pool<Align, MaxBytes>::release() noexcept {
        for(auto i {0}; i < chunk_size; ++i) {
            memory_pool::operator delete(chunk_record[i]);
        }
        chunk_record = nullptr;
        chunk_record_size = chunk_size = 0;
        start = end = nullptr;
        ds::memory_default_initialization(free_list, sizeof free_list);
    }
#endif
}

#endif //DATA_STRUCTURE_MEMORY_HPP
