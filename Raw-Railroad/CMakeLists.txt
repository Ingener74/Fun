cmake_minimum_required(VERSION 3.0)

find_package(BISON)
find_package(FLEX)

include_directories(
        ${CMAKE_CURRENT_BINARY_DIR}
        .
        AstParts
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
        
        AstParts/FuncType.cpp
        AstParts/FuncType.h
        
        AstParts/DefineType.cpp
        AstParts/DefineType.h
        
        AstParts/ArgType.cpp
        AstParts/ArgType.h
        
        AstParts/Import.cpp
        AstParts/Import.h
        
        AstParts/Print.cpp
        AstParts/Print.h
        
        AstParts/Plus.cpp
        AstParts/Plus.h
        
        AstParts/Minus.cpp
        AstParts/Minus.h
        
        AstParts/Mul.cpp
        AstParts/Mul.h
        
        AstParts/Div.cpp
        AstParts/Div.h
        
        ${BISON_MyParser_OUTPUTS}
        ${FLEX_MyScanner_OUTPUTS}
)
