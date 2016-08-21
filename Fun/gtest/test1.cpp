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
    Statement* root;
};

Result interpret(const std::string& source) {
    std::unique_ptr<Interpreter> visitor(new Interpreter(nullptr));
    Statement* root = nullptr;
    stringstream ss;
    ss << source;
    FunLexer lexer("", &ss);
    FunParser parser(lexer, &root);
    parser.set_debug_level(0);
    bool result = parser.parse();
    visitor->iterateStatements(root);
    return {move(visitor), root};
}

TEST(Fun, leakTest1) {
    auto result = interpret(R"(

foo = 42

)");

    ASSERT_EQ(Statement::statementCounter(), 3);
    result.root->release();
    ASSERT_EQ(Statement::statementCounter(), 0);

    ASSERT_EQ(result.v->getMemory()[0].size(), 1);
}

TEST(Fun, test2) {
    ASSERT_EQ(1, 1);
}
