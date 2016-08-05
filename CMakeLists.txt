cmake_minimum_required(VERSION 3.0)

if(CMAKE_VERSION VERSION_LESS "3.1")
  message("Warning: cmake version less than 3.1")
  if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    # using regular Clang or AppleClang
    add_definitions(-std=c++11)
  endif()
  if (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    add_definitions(-std=c++11)
  endif()
else()
  message("cmake version at least 3.1; setting CMAKE_CXX_VERSION = 11")
  set(CMAKE_CXX_VERSION 11)
endif()
    

project(jmachine)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)
set(PROJECT_SOURCE_DIR ${CMAKE_SOURCE_DIR})

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
