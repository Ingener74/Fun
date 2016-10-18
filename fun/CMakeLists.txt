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
        
        AST.cpp
        AST.h
        Compiler.cpp
        Compiler.h
        Debugger.cpp
        Debugger.h
        Declarations.h
        Errors.cpp
        Errors.h
        fun.h
        Interpreter.cpp
        Interpreter.h
        Lexer.cpp
        Lexer.h
        main.cpp
        Printer.cpp
        Printer.h
        Utils.cpp
        Utils.h
        VirtualMachine.cpp
        VirtualMachine.h
        Visitor.cpp
        Visitor.h
        
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

add_subdirectory(unittests)
