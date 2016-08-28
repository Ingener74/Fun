#include "test.h"

using namespace std;
using namespace fun;

TEST(Parse, Id_0) {
    {
        auto r = parseAst(R"(
_
)");
        ASSERT_TRUE(r.successful);
        auto bool_ = dynamic_cast<Id*>(r.ast->root());
        ASSERT_NE(bool_, nullptr);
        ASSERT_EQ(bool_->value, "_");
    }
    ASSERT_EQ(Statement::counter(), 0);
}

TEST(Parse, Id_1) {
    {
        auto r = parseAst(R"(
__
)");
        ASSERT_TRUE(r.successful);
        auto bool_ = dynamic_cast<Id*>(r.ast->root());
        ASSERT_NE(bool_, nullptr);
        ASSERT_EQ(bool_->value, "__");
    }
    ASSERT_EQ(Statement::counter(), 0);
}

TEST(Parse, Id_2) {
    {
        auto r = parseAst(R"(
___
)");
        ASSERT_TRUE(r.successful);
        auto bool_ = dynamic_cast<Id*>(r.ast->root());
        ASSERT_NE(bool_, nullptr);
        ASSERT_EQ(bool_->value, "___");
    }
    ASSERT_EQ(Statement::counter(), 0);
}

TEST(Parse, Id_3) {
    {
        auto r = parseAst(R"(
_1
)");
        ASSERT_TRUE(r.successful);
        auto bool_ = dynamic_cast<Id*>(r.ast->root());
        ASSERT_NE(bool_, nullptr);
        ASSERT_EQ(bool_->value, "_1");
    }
    ASSERT_EQ(Statement::counter(), 0);
}

TEST(Parse, Id_4) {
    {
        auto r = parseAst(R"(
_Test
)");
        ASSERT_TRUE(r.successful);
        auto bool_ = dynamic_cast<Id*>(r.ast->root());
        ASSERT_NE(bool_, nullptr);
        ASSERT_EQ(bool_->value, "_Test");
    }
    ASSERT_EQ(Statement::counter(), 0);
}

TEST(Parse, Id_5) {
    {
        auto r = parseAst(R"(
_123abc
)");
        ASSERT_TRUE(r.successful);
        auto bool_ = dynamic_cast<Id*>(r.ast->root());
        ASSERT_NE(bool_, nullptr);
        ASSERT_EQ(bool_->value, "_123abc");
    }
    ASSERT_EQ(Statement::counter(), 0);
}

TEST(Parse, Id_6) {
    {
        auto r = parseAst(R"(
Test
)");
        ASSERT_TRUE(r.successful);
        auto bool_ = dynamic_cast<Id*>(r.ast->root());
        ASSERT_NE(bool_, nullptr);
        ASSERT_EQ(bool_->value, "Test");
    }
    ASSERT_EQ(Statement::counter(), 0);
}

TEST(Parse, Id_7) {
    {
        auto r = parseAst(R"(
ABC
)");
        ASSERT_TRUE(r.successful);
        auto bool_ = dynamic_cast<Id*>(r.ast->root());
        ASSERT_NE(bool_, nullptr);
        ASSERT_EQ(bool_->value, "ABC");
    }
    ASSERT_EQ(Statement::counter(), 0);
}

TEST(Parse, Id_8) {
    {
        auto r = parseAst(R"(
aBC_TEst_very_long_id123
)");
        ASSERT_TRUE(r.successful);
        auto bool_ = dynamic_cast<Id*>(r.ast->root());
        ASSERT_NE(bool_, nullptr);
        ASSERT_EQ(bool_->value, "aBC_TEst_very_long_id123");
    }
    ASSERT_EQ(Statement::counter(), 0);
}

TEST(Parse, Id_9) {
    {
        EXPECT_THROW(parse(R"(
1aBc
)", true), ParserError);
    }
    ASSERT_EQ(Statement::counter(), 0);
}

TEST(Parse, Id_10) {
    {
        EXPECT_THROW(parse(R"(
123aBc
)", true), ParserError);
    }
    ASSERT_EQ(Statement::counter(), 0);
}

