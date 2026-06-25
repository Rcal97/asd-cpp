cmake_minimum_required(VERSION 3.10)
project(Percorsi)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(percorsi
    main.cpp
    Graph.cpp
)

target_include_directories(percorsi PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})