#include "test.h"

using namespace std;
using namespace fun;

TEST(Parse, Assign_0) {
    {
        EXPECT_THROW(parse(R"(
foo = 
)"), ParserError);
    }
    ASSERT_EQ(Statement::counter(), 0);
}

TEST(Parse, Assign_1) {
    {
        ASSERT_EQ(parse(R"(
foo = 42)"), true);
    }
    ASSERT_EQ(Statement::counter(), 0);
}

TEST(Parse, Assign_2) {
    {
        ASSERT_EQ(parse(R"(
foo = 42)"), true);
    }
    ASSERT_EQ(Statement::counter(), 0);
}

TEST(Interpret, Assign_3) {
    {
        auto r = interpret(R"(foo = 42)");

        ASSERT_EQ(Statement::counter(), 3);

        ASSERT_EQ(r.v->getOperands().size(), 0);
        ASSERT_EQ(r.v->getMemory()[0].size(), 1);

        auto var = r.v->getMemory()[0]["foo"];

        auto integer = dynamic_cast<Integer*>(var);

        ASSERT_NE(integer, nullptr);
        ASSERT_EQ(integer->value, 42);
    }
    ASSERT_EQ(Statement::counter(), 0);
}

