
file(GLOB source_files "*.cpp")
file(GLOB header_files "*.h")
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_library(qcustomplot STATIC ${source_files} ${header_files})
qt5_use_moduleS(qcustomplot Widgets PrintSupport)
target_link_libraries(qcustomplot ${QT5_LIBRARIES})




