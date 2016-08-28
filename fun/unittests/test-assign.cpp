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
        auto result = interpret(R"(foo = 42)");

        ASSERT_EQ(Statement::counter(), 3);

        ASSERT_EQ(result.v->getOperands().size(), 0);
        ASSERT_EQ(result.v->getMemory()[0].size(), 1);
    }
    ASSERT_EQ(Statement::counter(), 0);
}

