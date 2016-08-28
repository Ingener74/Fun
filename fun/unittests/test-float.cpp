#include "test.h"

using namespace std;
using namespace fun;

TEST(Parse, Float_0) {
    {
        auto r = parseAst(R"(
0.0
)");
        ASSERT_TRUE(r.successful);
        Real* real = dynamic_cast<Real*>(r.ast->root());
        ASSERT_NE(real, nullptr);
        ASSERT_DOUBLE_EQ(real->value, 0.0);
    }
    ASSERT_EQ(Statement::counter(), 0);
}

TEST(Parse, Float_1) {
    {
        auto r = parseAst(R"(
1.0
)");
        ASSERT_TRUE(r.successful);
        Real* real = dynamic_cast<Real*>(r.ast->root());
        ASSERT_NE(real, nullptr);
        ASSERT_DOUBLE_EQ(real->value, 1.0);
    }
    ASSERT_EQ(Statement::counter(), 0);
}

TEST(Parse, Float_2) {
    {
        auto r = parseAst(R"(
.0
)");
        ASSERT_TRUE(r.successful);
        Real* real = dynamic_cast<Real*>(r.ast->root());
        ASSERT_NE(real, nullptr);
        ASSERT_DOUBLE_EQ(real->value, .0);
    }
    ASSERT_EQ(Statement::counter(), 0);
}

TEST(Parse, Float_3) {
    {
        auto r = parseAst(R"(
10.
)");
        ASSERT_TRUE(r.successful);
        Real* real = dynamic_cast<Real*>(r.ast->root());
        ASSERT_NE(real, nullptr);
        ASSERT_DOUBLE_EQ(real->value, 10.);
    }
    ASSERT_EQ(Statement::counter(), 0);
}

TEST(Parse, Float_4) {
    {
        auto r = parseAst(R"(
1.0e1
)");
        ASSERT_TRUE(r.successful);
        Real* real = dynamic_cast<Real*>(r.ast->root());
        ASSERT_NE(real, nullptr);
        ASSERT_DOUBLE_EQ(real->value, 1.0e1);
    }
    ASSERT_EQ(Statement::counter(), 0);
}

TEST(Parse, Float_5) {
    {
        auto r = parseAst(R"(
1.0E1
)");
        ASSERT_TRUE(r.successful);
        Real* real = dynamic_cast<Real*>(r.ast->root());
        ASSERT_NE(real, nullptr);
        ASSERT_DOUBLE_EQ(real->value, 1.0E1);
    }
    ASSERT_EQ(Statement::counter(), 0);
}

TEST(Parse, Float_6) {
    {
        auto r = parseAst(R"(
.1e-3
)");
        ASSERT_TRUE(r.successful);
        Real* real = dynamic_cast<Real*>(r.ast->root());
        ASSERT_NE(real, nullptr);
        ASSERT_DOUBLE_EQ(real->value, .1e-3);
    }
    ASSERT_EQ(Statement::counter(), 0);
}

TEST(Parse, Float_7) {
    {
        auto r = parseAst(R"(
.13145E-12
)");
        ASSERT_TRUE(r.successful);
        Real* real = dynamic_cast<Real*>(r.ast->root());
        ASSERT_NE(real, nullptr);
        ASSERT_DOUBLE_EQ(real->value, .13145E-12);
    }
    ASSERT_EQ(Statement::counter(), 0);
}

TEST(Parse, Float_8) {
    {
        auto r = parseAst(R"(
12.3E+12
)");
        ASSERT_TRUE(r.successful);
        Real* real = dynamic_cast<Real*>(r.ast->root());
        ASSERT_NE(real, nullptr);
        ASSERT_DOUBLE_EQ(real->value, 12.3E+12);
    }
    ASSERT_EQ(Statement::counter(), 0);
}

TEST(Parse, Float_9) {
    {
        auto r = parseAst(R"(
1.e+3
)");
        ASSERT_TRUE(r.successful);
        Real* real = dynamic_cast<Real*>(r.ast->root());
        ASSERT_NE(real, nullptr);
        ASSERT_DOUBLE_EQ(real->value, 1.e+3);
    }
    ASSERT_EQ(Statement::counter(), 0);
}

TEST(Parse, Float_10) {
    {
        EXPECT_THROW(parse(R"(
..13145E-12
)"), ParserError);
    }
    ASSERT_EQ(Statement::counter(), 0);
}

TEST(Parse, Float_11) {
    {
        EXPECT_THROW(parse(R"(
00.13145E-
)"), ParserError);
    }
    ASSERT_EQ(Statement::counter(), 0);
}

TEST(Parse, Float_12) {
    {
        EXPECT_THROW(parse(R"(
0.001e-
)"), ParserError);
    }
    ASSERT_EQ(Statement::counter(), 0);
}

TEST(Parse, Float_13) {
    {
        EXPECT_THROW(parse(R"(
0,1
)"), ParserError);
    }
    ASSERT_EQ(Statement::counter(), 0);
}

TEST(Parse, Float_14) {
    {
        EXPECT_THROW(parse(R"(
3,1415
)"), ParserError);
    }
    ASSERT_EQ(Statement::counter(), 0);
}


