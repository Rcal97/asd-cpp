cmake_minimum_required(VERSION 3.10)
project(HashRBTree)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(hashRBTree
    main.cpp
    HashRBTree.cpp
)

target_include_directories(hashRBTree PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})