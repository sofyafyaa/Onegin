cmake_minimum_required(VERSION 3.0.0)
project(Onegin VERSION 0.1.0)

add_library(onegin STATIC onegin.cpp)
add_executable(main main.cpp)

target_link_libraries(main onegin)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/sonnet.txt
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/logs.txt
DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/output.txt
DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Eugene_Oneguine.txt
DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

set(CMAKE_CXX_FLAGS "-O0 -std=c++17 -Wall")
include(CPack)