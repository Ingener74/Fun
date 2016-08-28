#include "test.h"

using namespace std;
using namespace fun;

TEST(Parse, Bool_0) {
    {
        auto r = parseAst(R"(
true
)");
        ASSERT_TRUE(r.successful);

        auto bool_ = dynamic_cast<Boolean*>(r.ast->root());

        ASSERT_NE(bool_, nullptr);

        ASSERT_EQ(bool_->value, true);
    }
    ASSERT_EQ(Statement::counter(), 0);
}

TEST(Parse, Bool_1) {
    {
        auto r = parseAst(R"(
false
)");
        ASSERT_TRUE(r.successful);

        auto bool_ = dynamic_cast<Boolean*>(r.ast->root());

        ASSERT_NE(bool_, nullptr);
        ASSERT_EQ(bool_->value, false);
    }
    ASSERT_EQ(Statement::counter(), 0);
}

TEST(Parse, Bool_2) {
    {
        auto r = parseAst(R"(
True
)");
        ASSERT_TRUE(r.successful);

        auto id = dynamic_cast<Boolean*>(r.ast->root());

        ASSERT_NE(id, nullptr);
        ASSERT_EQ(id->value, true);
    }
    ASSERT_EQ(Statement::counter(), 0);
}

TEST(Parse, Bool_3) {
    {
        auto r = parseAst(R"(
False
)");
        ASSERT_TRUE(r.successful);

        auto id = dynamic_cast<Boolean*>(r.ast->root());

        ASSERT_NE(id, nullptr);
        ASSERT_EQ(id->value, false);
    }
    ASSERT_EQ(Statement::counter(), 0);
}

TEST(Parse, Bool_4) {
    {
        auto r = parseAst(R"(
TRUE
)");
        ASSERT_TRUE(r.successful);

        auto id = dynamic_cast<Boolean*>(r.ast->root());

        ASSERT_NE(id, nullptr);
        ASSERT_EQ(id->value, true);
    }
    ASSERT_EQ(Statement::counter(), 0);
}

TEST(Parse, Bool_5) {
    {
        auto r = parseAst(R"(
FALSE
)");
        ASSERT_TRUE(r.successful);

        auto id = dynamic_cast<Boolean*>(r.ast->root());

        ASSERT_NE(id, nullptr);
        ASSERT_EQ(id->value, false);
    }
    ASSERT_EQ(Statement::counter(), 0);
}

TEST(Parse, Bool_6) {
    {
        auto r = parseAst(R"(
fAlSe
)");
        ASSERT_TRUE(r.successful);

        auto id = dynamic_cast<Boolean*>(r.ast->root());

        ASSERT_NE(id, nullptr);
        ASSERT_EQ(id->value, false);
    }
    ASSERT_EQ(Statement::counter(), 0);
}

TEST(Parse, Bool_7) {
    {
        auto r = parseAst(R"(
TrUe
)");
        ASSERT_TRUE(r.successful);

        auto id = dynamic_cast<Boolean*>(r.ast->root());

        ASSERT_NE(id, nullptr);
        ASSERT_EQ(id->value, true);
    }
    ASSERT_EQ(Statement::counter(), 0);
}

