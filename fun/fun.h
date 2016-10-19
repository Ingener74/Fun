#pragma once

#include <Lexer.h>
#include <AST.h>
#include <Printer.h>
#include <Interpreter.h>
#include <Compiler.h>
#include <Utils.h>

class Fun {
public:
    Fun();
    virtual ~Fun();

    enum class Debugger {
        NoDebugger, NetDebugger, CommandLineDebugger,
        TestingMockDebugger
    };

    void eval(const std::string& script);
};
