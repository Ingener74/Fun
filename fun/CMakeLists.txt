cmake_minimum_required(VERSION 3.0)

find_package(BISON)
find_package(FLEX)

include_directories(
        ${CMAKE_CURRENT_BINARY_DIR}
        .
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

set(fun_backend_SOURCES
        Fun.cpp
        Fun.h
        AST.cpp
        AST.h
        Compiler.cpp
        Compiler.h
        Debugger.cpp
        Debugger.h
        Declarations.h
        Errors.cpp
        Errors.h
        Interpreter.cpp
        Interpreter.h
        Lexer.cpp
        Lexer.h
        Printer.cpp
        Printer.h
        Utils.cpp
        Utils.h
        VirtualMachine.cpp
        VirtualMachine.h
        Visitor.cpp
        Visitor.h
        
        debuggers/EmptyDebugger.cpp
        debuggers/EmptyDebugger.h
        debuggers/CommandLineDebugger.cpp
        debuggers/CommandLineDebugger.h
        debuggers/TcpSocketDebugger.cpp
        debuggers/TcpSocketDebugger.h
        
        ${BISON_Parser_OUTPUTS}
        ${FLEX_Scanner_OUTPUTS}
)

add_library(fun_backend ${fun_backend_SOURCES})
set_target_properties(fun_backend PROPERTIES OUTPUT_NAME fun)

if(NOT EXISTS ${SYSROOT})
    add_dependencies(fun_backend ext_POCO ext_gtest)
endif()

# fun executable
add_executable(fun_command_line_frontend main.cpp)

target_link_libraries(fun_command_line_frontend fun_backend ${POCO_LIBRARIES})
set_target_properties(fun_command_line_frontend PROPERTIES OUTPUT_NAME fun)

add_subdirectory(unittests)
