#pragma once

#include <memory>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <fun.h>

void parse(const std::string& source, bool parser_debug = false);

struct ParseResult {
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

#define TEST_PARSE(klass, n, body) TEST(Parse,     klass##_##n) { body ASSERT_EQ(Statement::counter(), 0); }
#define TEST_INTERPRET(klass, n, body) TEST(Interpret, klass##_##n) { body ASSERT_EQ(Statement::counter(), 0); }

#define PARSE_VALID(klass, n, str, v) TEST_PARSE(klass, n, { \
    ParseResult r; \
    EXPECT_NO_THROW(r = parseAst(str);); \
    auto instance = dynamic_cast<klass*>(r.ast->root()); \
    ASSERT_NE(instance, nullptr); \
    ASSERT_EQ(instance->value, v); \
})

#define PARSE_VALID2(klass, n, str) TEST_PARSE(klass, n, { EXPECT_NO_THROW(parse(str)); })
#define PARSE_INVALID(klass, n, str, errorClass) TEST_PARSE(klass, n, { EXPECT_THROW(parse(str), errorClass); })

