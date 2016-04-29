cmake_minimum_required(VERSION 3.0)

find_package(BISON)
find_package(FLEX)

include_directories(
        ${CMAKE_CURRENT_BINARY_DIR}
        .
        AstParts
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
        
        AstParts/Expr.cpp
        AstParts/Expr.h
        
        AstParts/IdExpr.cpp
        AstParts/IdExpr.h
        
        AstParts/NumExpr.cpp
        AstParts/NumExpr.h
        
        AstParts/AssignExpr.cpp
        AstParts/AssignExpr.h
        
        AstParts/Function.cpp
        AstParts/Function.h
        
        AstParts/DefineType.cpp
        AstParts/DefineType.h
        
        AstParts/Args.cpp
        AstParts/Args.h
        
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
        
        AstParts/FunctionStatements.cpp
        AstParts/FunctionStatements.h
        
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
