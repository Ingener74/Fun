#include "test.h"

using namespace std;
using namespace fun;

TEST(Parse, Integer_0) {
    {
        ASSERT_TRUE(parse(R"(
42
)"));
    }
    ASSERT_EQ(Statement::counter(), 0);
}

TEST(Parse, Integer_1) {
    {
        ASSERT_TRUE(parse(R"(
1000000000
)"));
    }
    ASSERT_EQ(Statement::counter(), 0);
}

TEST(Parse, Integer_2) {
    {
        ASSERT_TRUE(parse(R"(
0
)"));
    }
    ASSERT_EQ(Statement::counter(), 0);
}

TEST(Parse, Integer_3) {
    {
        ASSERT_TRUE(parse(R"(
100
)"));
    }
    ASSERT_EQ(Statement::counter(), 0);
}
