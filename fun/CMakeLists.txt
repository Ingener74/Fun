cmake_minimum_required(VERSION 3.0)

find_package(BISON)
find_package(FLEX)

include_directories(
        ${CMAKE_CURRENT_BINARY_DIR}
        .
        AstNodes
        AstVisitors
)

BISON_TARGET(
        Parser
        Parser.y
        ${CMAKE_CURRENT_BINARY_DIR}/Parser.cpp
)

FLEX_TARGET(
        Scanner
        Scanner.l
        ${CMAKE_CURRENT_BINARY_DIR}/Scanner.cpp)

ADD_FLEX_BISON_DEPENDENCY(Scanner Parser)

add_library(
        fun_backend
        
        Errors.cpp
        Errors.h
        
        Lexer.cpp
        Lexer.h
        
        Utils.cpp
        Utils.h

        AST.cpp
        AST.h

        Debugger.cpp
        Debugger.h
        
        Visitor.cpp
        Visitor.h
        
        Compiler.cpp
        Compiler.h
        
        Interpreter.cpp
        Interpreter.h
        
        Printer.cpp
        Printer.h
        
        VirtualMachine.cpp
        VirtualMachine.h
        
        ${BISON_Parser_OUTPUTS}
        ${FLEX_Scanner_OUTPUTS}
)
set_target_properties(fun_backend PROPERTIES OUTPUT_NAME fun)

if(NOT EXISTS ${SYSROOT})
    add_dependencies(fun_backend ext_POCO ext_gtest)
endif()

# fun executable
add_executable(fun_command_line_frontend main.cpp)

target_link_libraries(fun_command_line_frontend fun_backend ${POCO_LIBRARIES})
set_target_properties(fun_command_line_frontend PROPERTIES OUTPUT_NAME fun)

add_custom_command(OUTPUT Test0  COMMAND ../Liquid-Metaphor/Liquid-Metaphor -f ../../Fun/tests/test-0.fun)
add_custom_command(OUTPUT Test1  COMMAND ../Liquid-Metaphor/Liquid-Metaphor -f ../../Fun/tests/test-1.fun)
add_custom_command(OUTPUT Test2  COMMAND ../Liquid-Metaphor/Liquid-Metaphor -f ../../Fun/tests/test-2.fun)
add_custom_command(OUTPUT Test3  COMMAND ../Liquid-Metaphor/Liquid-Metaphor -f ../../Fun/tests/test-3.fun)
add_custom_command(OUTPUT Test4  COMMAND ../Liquid-Metaphor/Liquid-Metaphor -f ../../Fun/tests/test-4.fun)
add_custom_command(OUTPUT Test5  COMMAND ../Liquid-Metaphor/Liquid-Metaphor -f ../../Fun/tests/test-5.fun)
add_custom_command(OUTPUT Test6  COMMAND ../Liquid-Metaphor/Liquid-Metaphor -f ../../Fun/tests/test-6.fun)
add_custom_command(OUTPUT Test7  COMMAND ../Liquid-Metaphor/Liquid-Metaphor -f ../../Fun/tests/test-7.fun)
add_custom_command(OUTPUT Test8  COMMAND ../Liquid-Metaphor/Liquid-Metaphor -f ../../Fun/tests/test-8.fun)
add_custom_command(OUTPUT Test9  COMMAND ../Liquid-Metaphor/Liquid-Metaphor -f ../../Fun/tests/test-9.fun)
add_custom_command(OUTPUT Test10 COMMAND ../Liquid-Metaphor/Liquid-Metaphor -f ../../Fun/tests/test-10.fun)
add_custom_command(OUTPUT Test11 COMMAND ../Liquid-Metaphor/Liquid-Metaphor -f ../../Fun/tests/test-11.fun)

add_custom_command(OUTPUT Test12 COMMAND ../Liquid-Metaphor/Liquid-Metaphor -r -f ../../Fun/tests/interpret/test-0.fun)
add_custom_command(OUTPUT Test13 COMMAND ../Liquid-Metaphor/Liquid-Metaphor -r -f ../../Fun/tests/interpret/test-1.fun)
add_custom_command(OUTPUT Test14 COMMAND ../Liquid-Metaphor/Liquid-Metaphor -r -f ../../Fun/tests/interpret/test-2.fun)
add_custom_command(OUTPUT Test15 COMMAND ../Liquid-Metaphor/Liquid-Metaphor -r -f ../../Fun/tests/interpret/test-3.fun)
add_custom_command(OUTPUT Test16 COMMAND ../Liquid-Metaphor/Liquid-Metaphor -r -f ../../Fun/tests/interpret/test-4.fun)

add_custom_target(TestFun
    DEPENDS Test0 Test1 Test2 Test3 Test4 Test5 Test6 Test7 Test8 Test9 Test10 Test11 Test12 Test13 Test14 Test15 Test16
)

add_subdirectory(unittests)
