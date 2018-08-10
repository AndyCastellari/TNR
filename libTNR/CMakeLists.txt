cmake_minimum_required(VERSION 3.3.1)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 14)

cmake_policy(SET CMP0048 NEW)
project(TNRlib VERSION 1.3.1 LANGUAGES CXX)

if(NOT TARGET TNRlib)
    set(TNRlib_SRC 
    	BaseBinaryArchiveReadWrite.cpp
		BasicJSONParser.cpp
		FormattedTextReadWriteIf.cpp
		ObjectMap.cpp
		SimpleTextReadWriteIf.cpp
		StreamReadWriteIf.cpp
		TextLogWriteIf.cpp
		tnr.cpp
    )
 
    add_library(TNRlib STATIC ${TNRlib_SRC})

    target_include_directories(TNRlib PUBLIC ${CMAKE_CURRENT_LIST_DIR})

    target_include_directories(TNRlib PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../../rapidjson/include/)

# Set default compile flags for GCC
if(CMAKE_COMPILER_IS_GNUCXX)
    message(STATUS "GCC detected, adding compile flags")
#    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++98 -pedantic -Wall -Wextra")
    target_compile_options(TNRlib PRIVATE -Wall -Wextra)
endif(CMAKE_COMPILER_IS_GNUCXX)

    target_link_libraries(TNRlib)
endif()

 

 
