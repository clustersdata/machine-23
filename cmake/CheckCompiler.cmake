if(CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  set(COMPILER_IS_GNU_OR_CLANG TRUE)
else()
  set(COMPILER_IS_GNU_OR_CLANG FALSE)
endif()
