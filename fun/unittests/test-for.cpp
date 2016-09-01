#include "test.h"

using namespace std;
using namespace fun;

TEST(Parse, For_1) {
    {
        EXPECT_THROW(parse(R"(
for
)"), ParserError);
    }
    ASSERT_EQ(Statement::counter(), 0);
}

TEST(Parse, For_2) {
    {
        EXPECT_THROW(parse(R"(
for
end
)"), ParserError);
    }
    ASSERT_EQ(Statement::counter(), 0);
}

TEST(Parse, For_3) {
    {
        EXPECT_THROW(parse(R"(
for ;;:
end
)"), ParserError);
    }
    ASSERT_EQ(Statement::counter(), 0);
}

TEST(Parse, For_4) {
    {
        EXPECT_THROW(parse(R"(
for end
)"), ParserError);
    }
    ASSERT_EQ(Statement::counter(), 0);
}

TEST(Parse, For_5) {
    {
        EXPECT_NO_THROW(parse(R"(
for 0; 1; 2: end
)"));
    }
    ASSERT_EQ(Statement::counter(), 0);
}
