cmake_minimum_required(VERSION 2.8.9)

cmake_policy(SET CMP0048 NEW)
project (TnrDslParser VERSION 1.3.1 LANGUAGES CXX)

add_executable(tnrdsltool tnrdsltool.cpp
        TNRDSLBaseVisitor.cpp
        TNRDSLLexer.cpp
        TNRDSLParser.cpp
        TnrVisitor.cpp TnrVisitor.h ObjectBuilder.cpp ObjectBuilder.h)

target_include_directories(TNRlib PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../../tclap-1.2.2/include/
#        ${CMAKE_CURRENT_LIST_DIR}/../../antlr4-cpp-runtime/run/usr/local/include/antlr4-runtime)
 ${CMAKE_CURRENT_LIST_DIR}/../../antlr4-cpp-runtime/usr/local/include/antlr4-runtime)

target_link_libraries(tnrdsltool TNRlib
        ${CMAKE_CURRENT_LIST_DIR}/../../antlr4-cpp-runtime/dist/libantlr4-runtime.a
        )

add_custom_target(Antlr
        COMMAND java -jar /usr/local/lib/antlr-4.7.2-complete.jar -Dlanguage=Cpp -visitor -no-listener TNRDSL.g4
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_dependencies(tnrdsltool Antlr)
#        SOURCES ../grammar/MyGrammar.g)
# copy files to test tnrtool
#configure_file(testObject1.json testObject1.json COPYONLY)
#configure_file(testObject2.json testObject2.json COPYONLY)
#configure_file(testObject3.json testObject3.json COPYONLY)

#configure_file(testObject1.bin testObject1.bin COPYONLY)
#configure_file(testObject2.bin testObject2.bin COPYONLY)
#configure_file(testObject3.bin testObject3.bin COPYONLY)

#configure_file(test2.sh test2.sh COPYONLY)
#configure_file(test3.sh test3.sh COPYONLY)

#enable_testing()

#add_test(script_test2 test2.sh)
#add_test(script_test3 test3.sh)
