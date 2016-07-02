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

if(ENABLE_LIQUID_METAPHOR)
    add_custom_command(OUTPUT Test0
        COMMAND ../Liquid-Metaphor/Liquid-Metaphor ../../Fun/tests/test-0.fun
    )

    add_custom_command(OUTPUT Test1
        COMMAND ../Liquid-Metaphor/Liquid-Metaphor ../../Fun/tests/test-1.fun
    )

    add_custom_command(OUTPUT Test2
        COMMAND ../Liquid-Metaphor/Liquid-Metaphor ../../Fun/tests/test-2.fun
    )

    add_custom_command(OUTPUT Test3
        COMMAND ../Liquid-Metaphor/Liquid-Metaphor ../../Fun/tests/test-3.fun
    )
    
    add_custom_command(OUTPUT Test4
        COMMAND ../Liquid-Metaphor/Liquid-Metaphor ../../Fun/tests/test-4.fun
    )

    add_custom_target(TestFun
        DEPENDS Test0 Test1 Test2 Test3 Test4
    )
endif()