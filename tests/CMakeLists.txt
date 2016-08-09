# add_executable(DataNode DataNode.cpp)
# add_executable(DataSet DataSet.cpp)


# target_link_libraries(DataNode jmaclib)
# target_link_libraries(DataSet jmaclib)

# add_test(DataNode DataNode)
# add_test(DataSet DataSet)


file(GLOB test_sources "*.cpp")
file(GLOB test_headers "*.h")

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

foreach(source_file ${test_sources})
  #message("test sources is ${test_sources}")
  #message("source file is ${source_file}")
  get_filename_component(base_name ${source_file} NAME_WE)
  #message("base name is ${base_name}")
  add_executable(${base_name} ${source_file} ${test_headers} ${mocfiles})
  target_link_libraries(${base_name} jmaclib qcustomplot ${QT5_LIBRARIES})
  qt5_use_modules(${base_name} Widgets PrintSupport)
  add_test(${base_name} ${base_name})
  message(STATUS "Added test ${base_name}")
endforeach(source_file)


#add_custom_target(check ALL COMMAND ${CMAKE_CTEST_COMMAND})
add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND})
