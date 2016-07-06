cmake_minimum_required(VERSION 3.0)

project(jmachine)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)
set(PROJECT_SOURCE_DIR ${CMAKE_SOURCE_DIR})

set(CXX_STANDARD "c++14")

find_package(Qt5Widgets REQUIRED)
find_package(Qt5PrintSupport REQUIRED)

set(CMAKE_AUTOMOC ON)

include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${PROJECT_SOURCE_DIR}/external/qcustomplot)


enable_testing()

add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(app)
add_subdirectory(external)
