cmake_minimum_required(VERSION 2.8.9)

project (tnrtool)

add_executable(tnrtool tnrtool.cpp)

target_include_directories(TNRlib PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../../tclap-1.2.1/include/)

target_link_libraries(tnrtool TNRlib)


