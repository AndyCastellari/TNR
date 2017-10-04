cmake_minimum_required(VERSION 3.3.1)

cmake_policy(SET CMP0048 NEW)
project(TNR VERSION 1.3.1 LANGUAGES CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 14)

set(CMAKE_POSITION_INDEPENDENT_CODE TRUE)

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/libTNR ${CMAKE_CURRENT_BINARY_DIR}/libTNR)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/TNR_tester ${CMAKE_CURRENT_BINARY_DIR}/TNR_tester)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/tnrtool ${CMAKE_CURRENT_BINARY_DIR}/tnrtool)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/tnrtool ${CMAKE_CURRENT_BINARY_DIR}/tnrdsltool)

enable_testing()

 
