cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Algorithms-and-Data-Structures)

include(cmake/function.cmake)

add_subdirectory(lib_easy_example)
add_subdirectory(lib_vector)
add_subdirectory(lib_stack)
add_subdirectory(main)
add_subdirectory(lib_queue)
# add_subdirectory(multi_stack)
add_subdirectory(lib_DoubleLinkedList)

option(BTEST "build test?" ON)

if(BTEST)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    add_subdirectory("third_party/gtest" EXCLUDE_FROM_ALL)
    enable_testing()
    add_subdirectory(tests)
endif()