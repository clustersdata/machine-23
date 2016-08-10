cmake_minimum_required(VERSION 3.0)

project(jmachine)

if(NOT CMAKE_BUILD_TYPE)
  message(STATUS "Setting build type to 'Release' as none was specified.")
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
  # Set the possible values of build type for cmake-gui
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release"
    "MinSizeRel" "RelWithDebInfo")
endif()

if(CMAKE_VERSION VERSION_LESS "3.1")
  message("Warning: cmake version less than 3.1")
  if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    # using regular Clang or AppleClang
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
  endif()
  if (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
  endif()
else()
  message("cmake version at least 3.1; setting CMAKE_CXX_VERSION = 11")
  set(CMAKE_CXX_STANDARD 11)
endif()


#message("The CXX compiler flags are ${CMAKE_CXX_FLAGS}")


set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)
set(PROJECT_SOURCE_DIR ${CMAKE_SOURCE_DIR})

find_package(Qt5Widgets REQUIRED)
find_package(Qt5PrintSupport REQUIRED)

set(CMAKE_AUTOMOC ON)

include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${PROJECT_SOURCE_DIR}/external/qcustomplot)

enable_testing()

message("Adding targets")
add_subdirectory(src)
add_subdirectory(app)
add_subdirectory(external)

message("Adding tests")
add_subdirectory(tests)


message("The compiler is ${CMAKE_CXX_COMPILER_ID}")
message("The build type is ${CMAKE_BUILD_TYPE}")
