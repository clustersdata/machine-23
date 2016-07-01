file(GLOB app_source "*.cpp")
file(GLOB app_headers ".h")

add_executable(app ${app_source} ${app_headers})
target_link_libraries(app jmaclib)

