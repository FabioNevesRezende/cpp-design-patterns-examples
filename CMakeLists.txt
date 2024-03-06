cmake_minimum_required(VERSION 3.28)

set(CMAKE_CXX_STANDARD 23)

add_executable(adapter adapter.cpp)
add_executable(bridge bridge.cpp)
add_executable(composite composite.cpp)