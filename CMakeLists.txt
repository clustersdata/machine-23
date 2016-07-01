cmake_minimum_required(VERSION 2.8)

project(jonotree)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)

set(PROJECT_SOURCE_DIR ${CMAKE_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/src)

enable_testing()

add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(app)

