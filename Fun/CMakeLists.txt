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
        FunParser
        FunParser.y
        ${CMAKE_CURRENT_BINARY_DIR}/FunParser.cpp
)

FLEX_TARGET(
        FunScanner
        FunScanner.l
        ${CMAKE_CURRENT_BINARY_DIR}/FunScanner.cpp)

ADD_FLEX_BISON_DEPENDENCY(FunScanner FunParser)

add_library(
        Fun
        
        FunLexer.cpp
        FunLexer.h
        
        Utils.cpp
        Utils.h
        
        Nodes.cpp
        Nodes.h
        
        Visitor.cpp
        Visitor.h
        
        Compiler.cpp
        Compiler.h
        
        Interpreter.cpp
        Interpreter.h
        
        Printer.cpp
        Printer.h
        
        ${BISON_FunParser_OUTPUTS}
        ${FLEX_FunScanner_OUTPUTS}
)
