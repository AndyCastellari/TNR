cmake_minimum_required(VERSION 2.8.9)

project (tnrtool)

add_executable(tnrtool tnrtool.cpp)

target_link_libraries(tnrtool TNRlib)


