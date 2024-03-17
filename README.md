# data_structure #

![](https://img.shields.io/badge/Refactoring-8A2BE2)
![](https://img.shields.io/badge/License-Apache%202.0-brightgreen)

In computer science, a data structure is a data organization, management, and storage format that enables efficient access and modification. More precisely, a data structure is a collection of data values, the relationships among them, and the functions or operations that can be applied to the data.

Data structures serve as the basis for abstract data types (ADT). The ADT defines the logical form of the data type. The data structure implements the physical form of the data type.

Different types of data structures are suited to different kinds of applications, and some are highly specialized to specific tasks. For example, relational databases commonly use B-tree indexes for data retrieval, while compiler implementations usually use hash tables to look up identifiers.

Data structures provide a means to manage large amounts of data efficiently for uses such as large databases and internet indexing services. Usually, efficient data structures are key to designing efficient algorithms. Some formal design methods and programming languages emphasize data structures, rather than algorithms, as the key organizing factor in software design. Data structures can be used to organize the storage and retrieval of information stored in both main memory and secondary memory.

## Usage ##

The project is being refactored.

## Enviorment ##

<table style="border: 3px solid #000">
<thead>
    <tr style="text-align: center; border-bottom: 2px solid #000;">
        <th style="border-right:2px solid #000">Device</th>
        <th>CPU</th>
        <th>Memory</th>
        <th>GPU</th>
        <th>Hard Disk</th>
        <th>System</th>
    </tr>
</thead>
<tr style="text-align: center;">
    <th rowspan="2" style="border-right:2px solid #000">Apple Mac mini M2</th>
    <td rowspan="2">Apple M2</td>
    <td rowspan="2">8 GB</td>
    <td rowspan="2">Apple M2</td>
    <td rowspan="2">Apple SSD AP0256Z</td>
    <td>macOS Sonoma 14.4</td>
</tr>
<tr style="text-align: center; border-bottom: 1.5px solid #000;">
    <td><img src="https://img.shields.io/badge/Virtual-black" alt="Virtual" />Windows 11 Arm 23H2</td>
</tr>
<tr style="text-align: center;">
    <th rowspan="2" style="border-right:2px solid #000">Apple MacBook Pro M3 Max</th>
    <td rowspan="2">Apple M3 Max</td>
    <td rowspan="2">128 GB</td>
    <td rowspan="2">Apple M3 Max</td>
    <td rowspan="2">Apple SSD AP1024Z</td>
    <td>macOS Sonoma 14.4</td>
</tr>
<tr style="text-align: center; border-bottom: 1.5px solid #000;">
    <td><img src="https://img.shields.io/badge/Virtual-black" alt="Virtual" />CentOS 9 Stream</td>
</tr>
<tr style="text-align: center;">
    <th rowspan="2" style="border-right:2px solid #000">Apple MacBook Pro Intel</th>
    <td rowspan="2">Intel Core i7 9750H</td>
    <td rowspan="2">16 GB</td>
    <td rowspan="2">Intel UHD Graphics 630 & AMD Radeon Pro 555X</td>
    <td>Apple SSD AP0256M</td>
    <td>macOS Sonoma 14.4</td>
</tr>
<tr style="text-align: center;">
    <td>Samsung 980 500GB driven by UGREEN</td>
    <td><img src="https://img.shields.io/badge/BootCamp-black" alt="BootCamp" />Windows 11 23H2</td>
</tr>
</table>

## Development ##

### Status ###

<table style="border: 3px solid #000">
<thead>
    <tr style="text-align: center; border-bottom: 2px solid #000;">
        <th>Name</th>
        <th>Structure</th>
        <th>Status</th>
        <th>Header</th>
    </tr>
</thead>
<tr style="text-align: center;">
    <td>Config</td>
    <td>Basic</td>
    <td><img src="https://img.shields.io/badge/Development-Done-green" alt="Done" /></td>
    <td><code>__config.hpp</code></td>
</tr>
<tr style="text-align: center;">
    <td>Meta</td>
    <td>Extra</td>
    <td><img src="https://img.shields.io/badge/Development-Under-blue" alt="Done" /></td>
    <td><code>meta.hpp</code></td>
</tr>
<tr style="text-align: center;">
    <td>Type Traits</td>
    <td>Infrastructure</td>
    <td><img src="https://img.shields.io/badge/Development-Done-green" alt="Done" /></td>
    <td><code>type_traits.hpp</code></td>
</tr>
<tr style="text-align: center;">
    <td>Allocator</td>
    <td>Infrastructure</td>
    <td><img src="https://img.shields.io/badge/Development-Unconfirmed-EE3F4D" alt="Done" /></td>
    <td><code>type_traits.hpp</code></td>
</tr>
<tr style="text-align: center;">
    <td>Memory Pool</td>
    <td>Infrastructure</td>
    <td><img src="https://img.shields.io/badge/Development-Refactoring-8A2BE2" alt="Done" /></td>
    <td><code>memory.hpp</code></td>
</tr>
<tr style="text-align: center;">
    <td>Buffer</td>
    <td>Linear</td>
    <td><img src="https://img.shields.io/badge/Development-Refactoring-8A2BE2" alt="Done" /></td>
    <td><code>buffer.hpp</code></td>
</tr>
<tr style="text-align: center;">
    <td>Vector</td>
    <td>Linear</td>
    <td><img src="https://img.shields.io/badge/Development-Refactoring-8A2BE2" alt="Done" /></td>
    <td><code>vector.hpp</code></td>
</tr>
<tr style="text-align: center;">
    <td>Array</td>
    <td>Linear</td>
    <td><img src="https://img.shields.io/badge/Development-Refactoring-8A2BE2" alt="Done" /></td>
    <td><code>array.hpp</code></td>
</tr>
<tr style="text-align: center;">
    <td>Forward List</td>
    <td>Linear</td>
    <td><img src="https://img.shields.io/badge/Development-Refactoring-8A2BE2" alt="Done" /></td>
    <td><code>forward_list.hpp</code></td>
</tr>
<tr style="text-align: center;">
    <td>List</td>
    <td>Linear</td>
    <td><img src="https://img.shields.io/badge/Development-Refactoring-8A2BE2" alt="Done" /></td>
    <td><code>list.hpp</code></td>
</tr>
<tr style="text-align: center;">
    <td>Deque</td>
    <td>Linear</td>
    <td><img src="https://img.shields.io/badge/Development-Refactoring-8A2BE2" alt="Done" /></td>
    <td><code>deque.hpp</code></td>
</tr>
<tr style="text-align: center;">
    <td>Stack</td>
    <td>Adaptor</td>
    <td><img src="https://img.shields.io/badge/Development-Refactoring-8A2BE2" alt="Done" /></td>
    <td><code>stack.hpp</code></td>
</tr>
<tr style="text-align: center;">
    <td>Queue</td>
    <td>Adaptor</td>
    <td><img src="https://img.shields.io/badge/Development-Refactoring-8A2BE2" alt="Done" /></td>
    <td><code>queue.hpp</code></td>
</tr>
<tr style="text-align: center;">
    <td>Priority Queue</td>
    <td>Adaptor</td>
    <td><img src="https://img.shields.io/badge/Development-Refactoring-8A2BE2" alt="Done" /></td>
    <td><code>priority_queue.hpp</code></td>
</tr>
<tr style="text-align: center;">
    <td>Skip List</td>
    <td>Linear</td>
    <td><img src="https://img.shields.io/badge/Development-Refactoring-8A2BE2" alt="Done" /></td>
    <td><code>skip_list.hpp</code></td>
</tr>
<tr style="text-align: center;">
    <td>Hash Table</td>
    <td>Linear</td>
    <td><img src="https://img.shields.io/badge/Development-Refactoring-8A2BE2" alt="Done" /></td>
    <td><code>hash_table.hpp</code></td>
</tr>
<tr style="text-align: center;">
    <td>Hash Array</td>
    <td>Linear</td>
    <td><img src="https://img.shields.io/badge/Development-Refactoring-8A2BE2" alt="Done" /></td>
    <td><code>hash_array.hpp</code></td>
</tr>
<tr style="text-align: center;">
    <td>Contiguous Forward List</td>
    <td>Linear</td>
    <td><img src="https://img.shields.io/badge/Development-Refactoring-8A2BE2" alt="Done" /></td>
    <td><code>contiguous_forward_list.hpp</code></td>
</tr>
<tr style="text-align: center;">
    <td>Contiguous List</td>
    <td>Linear</td>
    <td><img src="https://img.shields.io/badge/Development-Pending-BE7E4A" alt="Done" /></td>
    <td><code>contiguous_list.hpp</code></td>
</tr>
<tr style="text-align: center;">
    <td>Bits</td>
    <td>Linear</td>
    <td><img src="https://img.shields.io/badge/Development-Pending-BE7E4A" alt="Done" /></td>
    <td><code>bits.hpp</code></td>
</tr>
<tr style="text-align: center;">
    <td>Matrix</td>
    <td>Linear</td>
    <td><img src="https://img.shields.io/badge/Development-Pending-BE7E4A" alt="Done" /></td>
    <td><code>matrix.hpp</code></td>
</tr>
<tr style="text-align: center;">
    <td>String</td>
    <td>Linear</td>
    <td><img src="https://img.shields.io/badge/Development-Pending-BE7E4A" alt="Done" /></td>
    <td><code>string.hpp</code></td>
</tr>
<tr style="text-align: center;">
    <td>Generalized List</td>
    <td>Linear</td>
    <td><img src="https://img.shields.io/badge/Development-Pending-BE7E4A" alt="Done" /></td>
    <td><code>generalized_list.hpp</code></td>
</tr>
<tr style="text-align: center;">
    <td>Tree</td>
    <td>Tree</td>
    <td><img src="https://img.shields.io/badge/Development-Refactoring-8A2BE2" alt="Done" /></td>
    <td><code>tree.hpp</code></td>
</tr>
<tr style="text-align: center;">
    <td>Binary Tree</td>
    <td>Tree</td>
    <td><img src="https://img.shields.io/badge/Development-Refactoring-8A2BE2" alt="Done" /></td>
    <td><code>binary_tree.hpp</code></td>
</tr>
<tr style="text-align: center;">
    <td>Leftist Tree</td>
    <td>Tree</td>
    <td><img src="https://img.shields.io/badge/Development-Refactoring-8A2BE2" alt="Done" /></td>
    <td><code>leftist_tree.hpp</code></td>
</tr>
<tr style="text-align: center;">
    <td>Winner Tree</td>
    <td>Tree</td>
    <td><img src="https://img.shields.io/badge/Development-Refactoring-8A2BE2" alt="Done" /></td>
    <td><code>winner_tree.hpp</code></td>
</tr>
<tr style="text-align: center;">
    <td>Loser Tree</td>
    <td>Alias</td>
    <td><img src="https://img.shields.io/badge/Development-Refactoring-8A2BE2" alt="Done" /></td>
    <td><code>loser_tree.hpp</code></td>
</tr>
<tr style="text-align: center;">
    <td>Huffman Tree</td>
    <td>Application</td>
    <td><img src="https://img.shields.io/badge/Development-Pending-BE7E4A" alt="Done" /></td>
    <td><code>huffman_tree.hpp</code></td>
</tr>
<tr style="text-align: center;">
    <td>Binary Search Tree</td>
    <td>Tree</td>
    <td><img src="https://img.shields.io/badge/Development-Pending-BE7E4A" alt="Done" /></td>
    <td><code>binary_search_tree.hpp</code></td>
</tr>
<tr style="text-align: center;">
    <td>Adelson-Velsky and Landis Tree</td>
    <td>Tree</td>
    <td><img src="https://img.shields.io/badge/Development-Pending-BE7E4A" alt="Done" /></td>
    <td><code>avl_tree.hpp</code></td>
</tr>
<tr style="text-align: center;">
    <td>Red-Black Tree</td>
    <td>Tree</td>
    <td><img src="https://img.shields.io/badge/Development-Pending-BE7E4A" alt="Done" /></td>
    <td><code>red_black_tree.hpp</code></td>
</tr>
<tr style="text-align: center;">
    <td>Splay Tree</td>
    <td>Adaptor</td>
    <td><img src="https://img.shields.io/badge/Development-Refactoring-8A2BE2" alt="Done" /></td>
    <td><code>splay_tree.hpp</code></td>
</tr>
<tr style="text-align: center;">
    <td>B Tree</td>
    <td>Tree</td>
    <td><img src="https://img.shields.io/badge/Development-Pending-BE7E4A" alt="Done" /></td>
    <td><code>b_tree.hpp</code></td>
</tr>
<tr style="text-align: center;">
    <td>B<sup>+</sup> Tree</td>
    <td>Tree</td>
    <td><img src="https://img.shields.io/badge/Development-Pending-BE7E4A" alt="Done" /></td>
    <td><code>b_plus_tree.hpp</code></td>
</tr>
<tr style="text-align: center;">
    <td>B<sup>*</sup> Tree</td>
    <td>Tree</td>
    <td><img src="https://img.shields.io/badge/Development-Pending-BE7E4A" alt="Done" /></td>
    <td><code>b_star_tree.hpp</code></td>
</tr>
<tr style="text-align: center;">
    <td>Graph</td>
    <td>Graph</td>
    <td><img src="https://img.shields.io/badge/Development-Pending-BE7E4A" alt="Done" /></td>
    <td><code>graph.hpp</code></td>
</tr>
</table>

### Unit Test ###

<table style="border: 3px solid #000">
<thead style="border-bottom: 2px solid #000;">
    <tr style="text-align: center;">
        <th rowspan="2" style="border-right:2px solid #000">Name</th>
        <th rowspan="2">System</th>
        <th colspan="4">Compiler</th>
    </tr>
    <tr style="text-align: center;">
        <th>Apple Clang</th>
        <th>Clang</th>
        <th>GCC</th>
        <th>MSVC</th>
    </tr>
</thead>
<tr style="text-align: center;">
    <td rowspan="4" style="border-right:2px solid #000"><code>buffer</code></td>
    <td>macOS</td>
    <td></td>
    <td></td>
    <td></td>
    <td><img src="https://img.shields.io/badge/None-gray" alt="None" /></td>
</tr>
<tr style="text-align: center;">
    <td>Windows</td>
    <td><img src="https://img.shields.io/badge/None-gray" alt="None" /></td>
    <td></td>
    <td></td>
    <td></td>
</tr>
<tr style="text-align: center;">
    <td>CentOS</td>
    <td><img src="https://img.shields.io/badge/None-gray" alt="None" /></td>
    <td></td>
    <td></td>
    <td><img src="https://img.shields.io/badge/None-gray" alt="None" /></td>
</tr>
<tr style="text-align: center;">
    <td>Windows Arm</td>
    <td><img src="https://img.shields.io/badge/None-gray" alt="None" /></td>
    <td></td>
    <td></td>
    <td></td>
</tr>
</table>

### Benchmark ###

<table style="border: 3px solid #000">
<thead style="border-bottom: 2px solid #000;">
    <tr style="text-align: center;">
        <th rowspan="2" style="border-right:2px solid #000">Name</th>
        <th rowspan="2">Enviorment</th>
        <th colspan="4">Compiler</th>
    </tr>
    <tr style="text-align: center;">
        <th>Apple Clang</th>
        <th>Clang</th>
        <th>GCC</th>
        <th>MSVC</th>
    </tr>
</thead>
<tr style="text-align: center;">
    <td rowspan="6" style="border-right:2px solid #000"><code>buffer</code></td>
    <td>macOS (M3 Max)</td>
    <td></td>
    <td></td>
    <td></td>
    <td><img src="https://img.shields.io/badge/None-gray" alt="None" /></td>
</tr>
<tr style="text-align: center;">
    <td>macOS (M2)</td>
    <td></td>
    <td></td>
    <td></td>
    <td><img src="https://img.shields.io/badge/None-gray" alt="None" /></td>
</tr>
<tr style="text-align: center;">
    <td>macOS (Intel)</td>
    <td></td>
    <td></td>
    <td></td>
    <td><img src="https://img.shields.io/badge/None-gray" alt="None" /></td>
</tr>
<tr style="text-align: center;">
    <td>Windows 11 (BootCamp in Intel)</td>
    <td><img src="https://img.shields.io/badge/None-gray" alt="None" /></td>
    <td></td>
    <td></td>
    <td></td>
</tr>
<tr style="text-align: center;">
    <td>Windows 11 Arm (Virtual in M2)</td>
    <td><img src="https://img.shields.io/badge/None-gray" alt="None" /></td>
    <td></td>
    <td></td>
    <td></td>
</tr>
<tr style="text-align: center;">
    <td>CentOS (Virtual in M3 Max)</td>
    <td><img src="https://img.shields.io/badge/None-gray" alt="None" /></td>
    <td></td>
    <td></td>
    <td><img src="https://img.shields.io/badge/None-gray" alt="None" /></td>
</tr>
</table>