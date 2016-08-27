/*
 * test1.cpp
 *
 *  Created on: Aug 21, 2016
 *      Author: pavel
 */

#include <memory>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <fun.h>

using namespace std;
using namespace fun;

bool parse(const std::string& source) {
    stringstream ss;
    ss << source;
    FunLexer lexer("", &ss);
    Ast ast;
    FunParser parser(lexer, &ast);
    parser.set_debug_level(0);
    int result = parser.parse();
    return result == 0;
}

TEST(Parse, Test1) {
    {
        ASSERT_EQ(parse(R"()"), true);
    }
    ASSERT_EQ(Statement::counter(), 0);
}

TEST(Parse, Test2) {
    {
        ASSERT_EQ(parse(R"(
print 42
print 3.14
print "foo"
print nil
print false
print true
)"), true);
    }
    ASSERT_EQ(Statement::counter(), 0);
}

TEST(Parse, Test3) {
    {
        ASSERT_EQ(parse(R"(
foo = 
)"), false);
    }
    ASSERT_EQ(Statement::counter(), 0);
}

TEST(Parse, Test4) {
    {
        ASSERT_EQ(parse(R"(
foo = 42)"), true);
    }
    ASSERT_EQ(Statement::counter(), 0);
}

TEST(Parse, Test5) {
    {
        ASSERT_EQ(parse(R"(
foo = 42)"), true);
    }
    ASSERT_EQ(Statement::counter(), 0);
}

struct Result {
    std::unique_ptr<Interpreter> v;
    std::unique_ptr<Debugger> d;
    std::unique_ptr<Ast> ast;
};

class DebuggerMock: public Debugger {
public:
    MOCK_METHOD1(onCatchBreakpoint, void(const Breakpoint &));
    MOCK_METHOD1(onOperandsChanged, void(const std::vector<Terminal*> &));
    MOCK_METHOD1(onMemoryChanged, void(const std::unordered_map<std::string, Terminal*>&));
};

Result interpret(const std::string& source) {
    std::unique_ptr<Debugger> debugger(new DebuggerMock);
    std::unique_ptr<Interpreter> interpreter(new Interpreter(debugger.get()));
    std::unique_ptr<Ast> ast(new Ast);
    stringstream ss;
    ss << source;
    FunLexer lexer("", &ss);
    FunParser parser(lexer, ast.get());
    parser.set_debug_level(0);
    bool result = parser.parse();
    ast->accept(interpreter.get());
    return {move(interpreter), move(debugger), move(ast)};
}

TEST(Fun, leakTest1) {
    {
        auto result = interpret(R"(foo = 42)");

        ASSERT_EQ(Statement::counter(), 3);

        ASSERT_EQ(result.v->getOperands().size(), 0);
        ASSERT_EQ(result.v->getMemory()[0].size(), 1);
    }
    ASSERT_EQ(Statement::counter(), 0);
}

TEST(Fun, test2) {
    {
        auto result = interpret(R"(
foo = 42
print foo
)");
        ASSERT_EQ(Statement::counter(), 5);
    }
    ASSERT_EQ(Statement::counter(), 0);
}
