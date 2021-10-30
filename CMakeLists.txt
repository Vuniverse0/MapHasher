cmake_minimum_required(VERSION 3.16)
project(CordsSorter)

set(CMAKE_CXX_STANDARD 20)

add_executable(CordsSorter main.cpp HashTable.h HashTable.cpp OpenTable.cpp OpenTable.h global_and_aliasing.h functions.cpp functions.h)