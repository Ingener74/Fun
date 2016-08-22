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
        ASSERT_EQ(Statement::counter(), 1);
    }

    ASSERT_EQ(Statement::counter(), 0);
}
