cmake_minimum_required(VERSION 2.8.9)

cmake_policy(SET CMP0048 NEW)
project (tnrtool VERSION 1.3.1 LANGUAGES CXX)

add_executable(tnrtool tnrtool.cpp)

target_include_directories(TNRlib PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../../tclap/include/)

target_link_libraries(tnrtool TNRlib)

# copy files to test tnrtool
configure_file(testObject1.json testObject1.json COPYONLY)
configure_file(testObject2.json testObject2.json COPYONLY)
configure_file(testObject3.json testObject3.json COPYONLY)

configure_file(testObject1.bin testObject1.bin COPYONLY)
configure_file(testObject2.bin testObject2.bin COPYONLY)
configure_file(testObject3.bin testObject3.bin COPYONLY)

configure_file(test2.sh test2.sh COPYONLY)
configure_file(test3.sh test3.sh COPYONLY)

enable_testing()

add_test(script_test2 test2.sh)
add_test(script_test3 test3.sh)
