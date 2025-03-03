cmake_minimum_required(VERSION 3.10)

project(dsa)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

add_executable(avltree avltree.c)
add_executable(bstree bstree.c)
add_executable(rbtree rbtree.c)
add_executable(btree btree.c)
add_executable(dlist dlist.c)
add_executable(list list.c)
add_executable(queue list.c)
add_executable(hashmap hashmap.c)
add_executable(heap heap.c)
add_executable(qsort qsort.c)
add_executable(graph graph.c)
