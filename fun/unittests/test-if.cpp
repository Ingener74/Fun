#include "test.h"

using namespace std;
using namespace fun;

TEST(Parse, If_0) {
    {
        EXPECT_THROW(parse(R"(
if
)"), ParserError);
    }
    ASSERT_EQ(Statement::counter(), 0);
}

TEST(Parse, If_1) {
    {
        EXPECT_THROW(parse(R"(
if
end
)"), ParserError);
    }
    ASSERT_EQ(Statement::counter(), 0);
}

TEST(Parse, If_2) {
    {
        EXPECT_THROW(parse(R"(
if nil
end
)"), ParserError);
    }
    ASSERT_EQ(Statement::counter(), 0);
}

TEST(Parse, If_3) {
    {
        EXPECT_THROW(parse(R"(
if:
end
)"), ParserError);
    }
    ASSERT_EQ(Statement::counter(), 0);
}

TEST(Parse, If_4) {
    {
        ASSERT_EQ(parse(R"(
if nil:
end
)"), true);
    }
    ASSERT_EQ(Statement::counter(), 0);
}

TEST(Parse, If_5) {
    {
        EXPECT_THROW(parse(R"(
if 0:
if 1:
end
)"), ParserError);
    }
    ASSERT_EQ(Statement::counter(), 0);
}

TEST(Parse, If_6) {
    {
        ASSERT_EQ(parse(R"(
if 0:
elif 1:
end
)"), true);
    }
    ASSERT_EQ(Statement::counter(), 0);
}

TEST(Parse, If_7) {
    {
        ASSERT_EQ(parse(R"(
if 0:
elif 1:
else
end
)"), true);
    }
    ASSERT_EQ(Statement::counter(), 0);
}

TEST(Parse, If_8) {
    {
        EXPECT_THROW(parse(R"(
if 0:
    ""
elif 1:
    5
else
    4
else
    2
end
)"), ParserError);
    }
    ASSERT_EQ(Statement::counter(), 0);
}
