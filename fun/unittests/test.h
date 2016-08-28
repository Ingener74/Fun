#pragma once

#include <memory>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <fun.h>

bool parse(const std::string& source, bool parser_debug = false);

struct ParseResult {
    bool successful;
    std::unique_ptr<fun::Ast> ast;
};

ParseResult parseAst(const std::string& source);

struct Result {
    std::unique_ptr<fun::Interpreter> v;
    std::unique_ptr<fun::Debugger> d;
    std::unique_ptr<fun::Ast> ast;
};

class DebuggerMock: public fun::Debugger {
public:
    MOCK_METHOD1(onCatchBreakpoint, void(const fun::Breakpoint &));
    MOCK_METHOD1(onOperandsChanged, void(const std::vector<fun::Terminal*> &));
    MOCK_METHOD1(onMemoryChanged, void(const std::unordered_map<std::string, fun::Terminal*>&));
};

Result interpret(const std::string& source);
