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
        
        FunAst.cpp
        FunAst.h
        
        FunLexer.cpp
        FunLexer.h
        
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
        
        AstNodes/AstNode.cpp
        AstNodes/AstNode.h
        
        AstNodes/Scope.cpp
        AstNodes/Scope.h
        
        AstNodes/StatementNode.cpp
        AstNodes/StatementNode.h
        
        AstVisitors/AstVisitor.cpp
        AstVisitors/AstVisitor.h
        
        AstVisitors/CompileVisitor.cpp
        AstVisitors/CompileVisitor.h
        
        AstVisitors/ExecutionVisitor.cpp
        AstVisitors/ExecutionVisitor.h
        
        AstVisitors/PrintVisitor.cpp
        AstVisitors/PrintVisitor.h
        
        ${BISON_FunParser_OUTPUTS}
        ${FLEX_FunScanner_OUTPUTS}
)
