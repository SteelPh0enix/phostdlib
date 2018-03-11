cmake_minimum_required(VERSION 3.9)
project(phostdlib)

set(CXX_ERROR_FLAGS "-Wall -Wextra -Wpedantic")
set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} ${CXX_ERROR_FLAGS})

include_directories(include)
add_executable(test_array test_array.cpp)
add_executable(test_test test_test.cpp)
add_executable(test_vector test_vector.cpp)
add_executable(test_utility test_utility.cpp)