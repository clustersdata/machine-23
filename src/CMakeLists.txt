

file(GLOB source_files "*.cpp")
file(GLOB header_files "*.h")

add_library(jmaclib ${source_files} ${header_files})

message(STATUS "added target 'jmaclib'")
