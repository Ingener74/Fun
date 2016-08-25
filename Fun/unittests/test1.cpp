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

struct ParseResult{
    Statement* root;
    bool result;
};

ParseResult parse(const std::string& source) {
    Statement* root = nullptr;
    stringstream ss;
    ss << source;
    FunLexer lexer("", &ss);
    FunParser parser(lexer, &root);
    parser.set_debug_level(0);
    int result = parser.parse();
    Statement::clear();
    return {root, result == 0};
}

TEST(Parse, Test1) {
    {
        auto result = parse(R"()");
        ASSERT_EQ(result.root, nullptr);
        ASSERT_EQ(result.result, true);
    }
    ASSERT_EQ(Statement::counter(), 0);
}

TEST(Parse, Test2) {
    {
        auto result = parse(R"(
print 42
print 3.14
print "foo"
print nil
print false
print true
)");
        ASSERT_NE(result.root, nullptr);
        ASSERT_EQ(result.result, true);
        result.root->release();
    }
    ASSERT_EQ(Statement::counter(), 0);
}

TEST(Parse, Test3) {
    {
        auto result = parse(R"(
foo = 
)");
        ASSERT_EQ(result.root, nullptr);
        ASSERT_EQ(result.result, false);
    }
    ASSERT_EQ(Statement::counter(), 0);
}

TEST(Parse, Test4) {
    {
        auto result = parse(R"(
foo = 42)");
        ASSERT_NE(result.root, nullptr);
        ASSERT_EQ(result.result, true);
        result.root->release();
    }
    ASSERT_EQ(Statement::counter(), 0);
}

TEST(Parse, Test5) {
    {
        auto result = parse(R"(
foo = 42)");
        ASSERT_NE(result.root, nullptr);
        ASSERT_EQ(result.result, true);
        result.root->release();
    }
    ASSERT_EQ(Statement::counter(), 0);
}

struct Result {
    std::unique_ptr<Interpreter> v;
    std::unique_ptr<Debugger> d;
    Statement* root;
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
    Statement* root = nullptr;
    stringstream ss;
    ss << source;
    FunLexer lexer("", &ss);
    FunParser parser(lexer, &root);
    parser.set_debug_level(0);
    bool result = parser.parse();
    Statement::clear();
    interpreter->iterateStatements(root);
    return {move(interpreter), move(debugger), root};
}

TEST(Fun, leakTest1) {
    {
        auto result = interpret(R"(foo = 42)");

        ASSERT_EQ(Statement::counter(), 3);
        result.root->release();
        ASSERT_EQ(Statement::counter(), 1);

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
        result.root->release();
        ASSERT_EQ(Statement::counter(), 4);
    }
    ASSERT_EQ(Statement::counter(), 0);
}
