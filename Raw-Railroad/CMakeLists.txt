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
        MyParser
        MyParser.y
        ${CMAKE_CURRENT_BINARY_DIR}/MyParser.cpp
)

FLEX_TARGET(
        MyScanner
        MyScanner.l
        ${CMAKE_CURRENT_BINARY_DIR}/MyScanner.cpp)

ADD_FLEX_BISON_DEPENDENCY(MyScanner MyParser)

add_library(
        Raw-Railroad
        
        Fun1Ast.cpp
        Fun1Ast.h
        
        MyLexer.cpp
        MyLexer.h
        
        Utils.cpp
        Utils.h
        
        AstNodes/Expr.cpp
        AstNodes/Expr.h
        
        AstNodes/IdExpr.cpp
        AstNodes/IdExpr.h
        
        AstNodes/NumExpr.cpp
        AstNodes/NumExpr.h
        
        AstNodes/AssignExpr.cpp
        AstNodes/AssignExpr.h
        
        AstNodes/Function.cpp
        AstNodes/Function.h
        
        AstNodes/DefineType.cpp
        AstNodes/DefineType.h
        
        AstNodes/Args.cpp
        AstNodes/Args.h
        
        AstNodes/Import.cpp
        AstNodes/Import.h
        
        AstNodes/Print.cpp
        AstNodes/Print.h
        
        AstNodes/Plus.cpp
        AstNodes/Plus.h
        
        AstNodes/Minus.cpp
        AstNodes/Minus.h
        
        AstNodes/Mul.cpp
        AstNodes/Mul.h
        
        AstNodes/Div.cpp
        AstNodes/Div.h
        
        AstNodes/FunctionStatements.cpp
        AstNodes/FunctionStatements.h
        
        AstVisitors/AstVisitor.cpp
        AstVisitors/AstVisitor.h
        AstVisitors/CompileVisitor.cpp
        AstVisitors/CompileVisitor.h
        AstVisitors/ExecutionVisitor.cpp
        AstVisitors/ExecutionVisitor.h
        AstVisitors/PrintVisitor.cpp
        AstVisitors/PrintVisitor.h
        
        ${BISON_MyParser_OUTPUTS}
        ${FLEX_MyScanner_OUTPUTS}
)
