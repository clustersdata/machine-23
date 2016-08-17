cmake_minimum_required(VERSION 3.0)

set(CMAKE_VERBOSE_MAKEFILE OFF)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

project(jmachine)

option(BUILD_COVERAGE "Build with -coverage flag" OFF)
option(BUILD_OPTIMIZED_DEBUG "Build with debug optimizations (gcc only)" OFF)

# detect enviroment and set up project options
include(CheckCompiler)
include(EnableModernCxx)


find_package(Qt5Widgets REQUIRED)
find_package(Qt5PrintSupport REQUIRED)

set(CMAKE_AUTOMOC ON)

include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/external/qcustomplot)

enable_testing()

message("Adding targets")
add_subdirectory(src)
add_subdirectory(app)
add_subdirectory(external)

message("Adding tests")
add_subdirectory(tests)


message("The compiler is ${CMAKE_CXX_COMPILER_ID}")
message("The build type is ${CMAKE_BUILD_TYPE}")


# code coverage report
if(BUILD_COVERAGE)
  include(CodeCoverage)
  set(ignore_dirs "'/usr/*'")
  #list(APPEND ignore_dirs "'*/tests/*'")
  list(APPEND ignore_dirs "'*/external/*'")
  add_coverage_target(coverage "${ignore_dirs}")
endif()
