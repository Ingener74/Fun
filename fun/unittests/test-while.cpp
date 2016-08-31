#include "test.h"

using namespace std;
using namespace fun;

TEST(Parse, While_1) {
    {
        EXPECT_THROW(parse(R"(
while
)"), ParserError);
    }
    ASSERT_EQ(Statement::counter(), 0);
}

TEST(Parse, While_2) {
    {
        EXPECT_THROW(parse(R"(
while
end
)"), ParserError);
    }
    ASSERT_EQ(Statement::counter(), 0);
}

TEST(Parse, While_3) {
    {
        EXPECT_THROW(parse(R"(
while nil
end
)"), ParserError);
    }
    ASSERT_EQ(Statement::counter(), 0);
}

TEST(Parse, While_4) {
    {
        EXPECT_THROW(parse(R"(
while:
end
)"), ParserError);
    }
    ASSERT_EQ(Statement::counter(), 0);
}

TEST(Parse, While_5) {
    {
        EXPECT_THROW(parse(R"(
while:end
)"), ParserError);
    }
    ASSERT_EQ(Statement::counter(), 0);
}

TEST(Parse, While_6) {
    {
        EXPECT_NO_THROW(parse(R"(
while nil:
end
)"));
    }
    ASSERT_EQ(Statement::counter(), 0);
}

TEST(Parse, While_7) {
    {
        EXPECT_THROW(parse(R"(
whilenil:end
)"), ParserError);
    }
    ASSERT_EQ(Statement::counter(), 0);
}

TEST(Parse, While_8) {
    {
        EXPECT_THROW(parse(R"(
while0:
end
)"), ParserError);
    }
    ASSERT_EQ(Statement::counter(), 0);
}

//TEST(Parse, While_9) {
//    {
//        ASSERT_EQ(parse(R"(
//if 0:
//elif 1:
//else
//end
//)"), true);
//    }
//    ASSERT_EQ(Statement::counter(), 0);
//}
//
//TEST(Parse, While_10) {
//    {
//        ASSERT_EQ(parse(R"(
//if 0:
//    ""
//elif 1:
//    5
//else
//    4
//else
//    2
//end
//)"), false);
//    }
//    ASSERT_EQ(Statement::counter(), 0);
//}
