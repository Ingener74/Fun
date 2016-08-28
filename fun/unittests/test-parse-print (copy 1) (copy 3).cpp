#include "test.h"

using namespace std;
using namespace fun;

TEST(Parse, Empty_0) {
    {
        ASSERT_TRUE(parse(R"()"));
    }
    ASSERT_EQ(Statement::counter(), 0);
}

TEST(Parse, Bool_0) {
    {
        ASSERT_TRUE(parse(R"(
true
)"));
    }
    ASSERT_EQ(Statement::counter(), 0);
}

TEST(Parse, Bool_1) {
    {
        ASSERT_TRUE(parse(R"(
false
)"));
    }
    ASSERT_EQ(Statement::counter(), 0);
}

TEST(Parse, Bool_2) {
    {
        auto r = parseAst(R"(
True
)");
        ASSERT_TRUE(r.successful);

        auto id = dynamic_cast<Id*>(r.ast->root());

        ASSERT_NE(id, nullptr);

        ASSERT_EQ(id->value, "True");
    }
    ASSERT_EQ(Statement::counter(), 0);
}

TEST(Parse, Bool_3) {
    {
        ASSERT_FALSE(parse(R"(
False
)"));
    }
    ASSERT_EQ(Statement::counter(), 0);
}

TEST(Parse, Bool_4) {
    {
        ASSERT_FALSE(parse(R"(
TRUE
)"));
    }
    ASSERT_EQ(Statement::counter(), 0);
}

TEST(Parse, Bool_5) {
    {
        ASSERT_FALSE(parse(R"(
FALSE
)"));
    }
    ASSERT_EQ(Statement::counter(), 0);
}

TEST(Parse, Float_0) {
    {
        ASSERT_TRUE(parse(R"(
0.0
)"));
    }
    ASSERT_EQ(Statement::counter(), 0);
}

TEST(Parse, Float_1) {
    {
        ASSERT_TRUE(parse(R"(
1.0
)"));
    }
    ASSERT_EQ(Statement::counter(), 0);
}

TEST(Parse, Float_2) {
    {
        ASSERT_TRUE(parse(R"(
.0
)"));
    }
    ASSERT_EQ(Statement::counter(), 0);
}

TEST(Parse, Float_3) {
    {
        ASSERT_TRUE(parse(R"(
10.
)"));
    }
    ASSERT_EQ(Statement::counter(), 0);
}

TEST(Parse, Float_4) {
    {
        ASSERT_TRUE(parse(R"(
1.0e1
)"));
    }
    ASSERT_EQ(Statement::counter(), 0);
}

TEST(Parse, Float_5) {
    {
        ASSERT_TRUE(parse(R"(
1.0E1
)"));
    }
    ASSERT_EQ(Statement::counter(), 0);
}

TEST(Parse, Float_6) {
    {
        ASSERT_TRUE(parse(R"(
.1e-3
)"));
    }
    ASSERT_EQ(Statement::counter(), 0);
}

TEST(Parse, Float_7) {
    {
        ASSERT_TRUE(parse(R"(
.13145E-12
)"));
    }
    ASSERT_EQ(Statement::counter(), 0);
}

TEST(Parse, Float_8) {
    {
        auto r = parseAst(R"(
1.0
)");
        ASSERT_TRUE(r.successful);

        Real* real = dynamic_cast<Real*>(r.ast->root());

        ASSERT_NE(real, nullptr);

        ASSERT_FLOAT_EQ(real->value, 1.0);
    }
    ASSERT_EQ(Statement::counter(), 0);
}

TEST(Parse, Float_9) {
    {
        auto r = parseAst(R"(
1.0
)");
        ASSERT_TRUE(r.successful);

        Real* real = dynamic_cast<Real*>(r.ast->root());

        ASSERT_NE(real, nullptr);

        ASSERT_FLOAT_EQ(real->value, 1.0);
    }
    ASSERT_EQ(Statement::counter(), 0);
}

TEST(Parse, String_0) {
    {
        ASSERT_TRUE(parse(R"(
"Test string"
)"));
    }
    ASSERT_EQ(Statement::counter(), 0);
}

TEST(Parse, String_1) {
    {
        auto result = parseAst(R"(
"Test
string"
)");
        ASSERT_TRUE(result.successful);
        ASSERT_EQ(result.ast->root()->loc, location(position(nullptr, 2, 1), position(nullptr, 3, 6)));
    }
    ASSERT_EQ(Statement::counter(), 0);
}

TEST(Parse, Test2) {
    {
        ASSERT_EQ(parse(R"(
print 42
print 3.14
print "foo"
print nil
print false
print true
)"), true);
    }
    ASSERT_EQ(Statement::counter(), 0);
}

TEST(Parse, Test3) {
    {
        ASSERT_EQ(parse(R"(
foo = 
)"), false);
    }
    ASSERT_EQ(Statement::counter(), 0);
}

TEST(Parse, Test4) {
    {
        ASSERT_EQ(parse(R"(
foo = 42)"), true);
    }
    ASSERT_EQ(Statement::counter(), 0);
}

TEST(Parse, Test5) {
    {
        ASSERT_EQ(parse(R"(
foo = 42)"), true);
    }
    ASSERT_EQ(Statement::counter(), 0);
}

TEST(Parse, If_1) {
    {
        ASSERT_EQ(parse(R"(
if
)"), false);
    }
    ASSERT_EQ(Statement::counter(), 0);
}

TEST(Parse, If_2) {
    {
        ASSERT_EQ(parse(R"(
if
end
)"), false);
    }
    ASSERT_EQ(Statement::counter(), 0);
}

TEST(Parse, If_3) {
    {
        ASSERT_EQ(parse(R"(
if nil
end
)"), false);
    }
    ASSERT_EQ(Statement::counter(), 0);
}

TEST(Parse, If_4) {
    {
        ASSERT_EQ(parse(R"(
if:
end
)"), false);
    }
    ASSERT_EQ(Statement::counter(), 0);
}

TEST(Parse, If_5) {
    {
        ASSERT_EQ(parse(R"(
if nil:
end
)"), true);
    }
    ASSERT_EQ(Statement::counter(), 0);
}

TEST(Parse, If_6) {
    {
        ASSERT_EQ(parse(R"(
if 0:
if 1:
end
)"), false);
    }
    ASSERT_EQ(Statement::counter(), 0);
}

TEST(Parse, If_7) {
    {
        ASSERT_EQ(parse(R"(
if 0:
elif 1:
end
)"), true);
    }
    ASSERT_EQ(Statement::counter(), 0);
}

TEST(Parse, If_8) {
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

TEST(Parse, If_9) {
    {
        ASSERT_EQ(parse(R"(
if 0:
    ""
elif 1:
    5
else
    4
else
    2
end
)"), false);
    }
    ASSERT_EQ(Statement::counter(), 0);
}

TEST(Fun, leakTest1) {
    {
        auto result = interpret(R"(foo = 42)");

        ASSERT_EQ(Statement::counter(), 3);

        ASSERT_EQ(result.v->getOperands().size(), 0);
        ASSERT_EQ(result.v->getMemory()[0].size(), 1);
    }
    ASSERT_EQ(Statement::counter(), 0);
}

TEST(Fun, test2) {
    {
        auto result = interpret(R"(
foo = 42
print foo
)");
        ASSERT_EQ(Statement::counter(), 5);
    }
    ASSERT_EQ(Statement::counter(), 0);
}
