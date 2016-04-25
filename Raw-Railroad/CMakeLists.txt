cmake_minimum_required(VERSION 3.0)

find_package(BISON)
find_package(FLEX)

include_directories(
        ${CMAKE_CURRENT_BINARY_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}
)

BISON_TARGET(
        MyParser
        MyParser.y
        ${CMAKE_CURRENT_BINARY_DIR}/MyParser.cpp
)

FLEX_TARGET(
        MyScanner
        MyScanner.l
        ${CMAKE_CURRENT_BINARY_DIR}/MyScanner.cpp)

ADD_FLEX_BISON_DEPENDENCY(MyScanner MyParser)

add_executable(
        Raw-Railroad
        
        main.cpp
        MyAst.cpp
        MyAst.h
        
        MyLexer.cpp
        
        Expr.cpp
        Expr.h
        
        IdExpr.cpp
        IdExpr.h
        
        NumExpr.cpp
        NumExpr.h
        
        AssignExpr.cpp
        AssignExpr.h
        
        ${BISON_MyParser_OUTPUTS}
        ${FLEX_MyScanner_OUTPUTS}
)
