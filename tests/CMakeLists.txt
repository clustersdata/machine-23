add_executable(test_DataNode test_DataNode.cpp)
add_executable(test_DataSet test_DataSet.cpp)


target_link_libraries(test_DataNode jmaclib)
target_link_libraries(test_DataSet jmaclib)

add_test(DataNodeTest test_DataNode)
add_test(DataSetTest test_DataSet)
