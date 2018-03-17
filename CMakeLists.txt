cmake_minimum_required(VERSION 3.9)
project(phostdlib)

set(CXX_ERROR_FLAGS "-Wall -Wextra -Wpedantic")
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} ${CXX_ERROR_FLAGS})

set(phostdlib_include_directory "${CMAKE_CURRENT_SOURCE_DIR}/include")
include_directories("${phostdlib_include_directory}")
set(BUILD_TESTS TRUE CACHE BOOL "Select to build tests")

if (BUILD_TESTS)
    add_subdirectory(tests)
endif()