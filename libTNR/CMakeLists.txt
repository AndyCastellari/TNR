cmake_minimum_required(VERSION 3.3.1)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 14)

project(TNRlib)
 
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

    target_compile_options(TNRlib PRIVATE -Wall -Wextra)

    target_link_libraries(TNRlib)
endif()

 

 
