# data_structure #

![](https://img.shields.io/badge/Build-Failed-red)
![](https://img.shields.io/badge/License-Apache%202.0-brightgreen)

In computer science, a data structure is a data organization, management, and storage format that enables efficient access and modification. More precisely, a data structure is a collection of data values, the relationships among them, and the functions or operations that can be applied to the data.

Data structures serve as the basis for abstract data types (ADT). The ADT defines the logical form of the data type. The data structure implements the physical form of the data type.

Different types of data structures are suited to different kinds of applications, and some are highly specialized to specific tasks. For example, relational databases commonly use B-tree indexes for data retrieval, while compiler implementations usually use hash tables to look up identifiers.

Data structures provide a means to manage large amounts of data efficiently for uses such as large databases and internet indexing services. Usually, efficient data structures are key to designing efficient algorithms. Some formal design methods and programming languages emphasize data structures, rather than algorithms, as the key organizing factor in software design. Data structures can be used to organize the storage and retrieval of information stored in both main memory and secondary memory.

## Usage ##

Appreciative only.

**There may exist compile errors in headers not mentioned.** (This part will be removed when all headers uploaded are complete.)
- \_\_config.hpp ![](https://img.shields.io/badge/Build-OK-success)
- meta.hpp ![](https://img.shields.io/badge/Build-OK-success)
- memory.hpp ![](https://img.shields.io/badge/Build-OK-success)
- buffer.hpp ![](https://img.shields.io/badge/Build-OK-success)
- type_traits.hpp ![](https://img.shields.io/badge/Build-OK-success)

## Compiler Support ##

- Apple clang version 13.1.6 (clang-1316.0.21.2.5) with compile flag `-std=c++2b` ![](https://img.shields.io/badge/Build-Supported-green)
- GCC version 12.2 ![](https://img.shields.io/badge/Build-Failed-red)
- MSVC_x64 version v19.latest ![](https://img.shields.io/badge/Build-Unknown-yellow)
- ICC_x64 version 2021.6.0 ![](https://img.shields.io/badge/Build-Unknown-yellow)

## Finished ##

### Headers ###

- allocator.hpp
- type_traits.hpp
- concepts.hpp (moduled)

### Structures ###

#### Linear ####

- buffer
- vector
- array
- forward_list
- list
- deque
- stack (adaptor)
- queue (adaptor)
- priority_queue (adaptor)
- skip_list
- hash_table
- static_forward_list (adaptor)

#### Tree ####

- tree
- binary_tree
- leftist_tree (adaptor)
- winner_tree
- loser_tree (alias)

### Algorithms ###

- ranking_sort
- selection_sort
- bubble_sort
- insertion_sort
- binary_search
- bucket_sort
- radix_sort
- make_heap
- push_heap
- pop_heap
- quick_sort
- merge_sort

## TODOs ##

### Array ###
- bits
- matrix
- string
- generalized_list

### List ###
- static_list

### Hash ###
- hash_array

### Tree ###
- huffman_tree
- binary_search_tree
- avl_tree
- red_black_tree (rb_tree)
- splay_tree
- b_tree

### Graph ###
- graph [matrix, list]

### Other ###
- dictionary (Adaptor)

## Release Note ##

There isn't any release note for this project, and I may stop updating temporarily for many reasons (such as preparation for Master's application last time) (｡ì _ í｡).
