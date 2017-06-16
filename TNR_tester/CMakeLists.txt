cmake_minimum_required(VERSION 2.8.9)

project (TNRtester)

add_executable(TNRtester src/TNR_tester.cpp src/PODTester.cpp src/JSONTester.cpp)

target_link_libraries(TNRtester TNRlib)


