cmake_minimum_required(VERSION 2.8.9)

cmake_policy(SET CMP0048 NEW)
project (TNRtester VERSION 1.3.1 LANGUAGES CXX)

add_executable(TNRtester src/TNR_tester.cpp src/PODTester.cpp src/JSONTester.cpp)

target_link_libraries(TNRtester TNRlib)

configure_file(src/testobject1.json testobject1.json COPYONLY)

enable_testing()

add_test(TNRUnitTests TNRtester )