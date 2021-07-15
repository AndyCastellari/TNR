cmake_minimum_required(VERSION 2.8.9)

cmake_policy(SET CMP0048 NEW)
project (TNRtester VERSION 1.3.1 LANGUAGES CXX)

if (NOT TARGET gtest)
    add_subdirectory(../../googletest GoogleTestFramework)
#    add_subdirectory(../../GoogleTestFramework GoogleTestFramework)
endif ()

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(TNRtester src/TNR_tester.cpp src/PODTester.cpp src/JSONTester.cpp)

add_dependencies(TNRtester gtest)

target_link_libraries(TNRtester TNRlib gtest gtest_main)

configure_file(src/testobject1.json testobject1.json COPYONLY)

enable_testing()

add_test(TNRUnitTests TNRtester )
