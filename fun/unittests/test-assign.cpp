#include "test.h"

using namespace std;
using namespace Poco;
using namespace fun;
using namespace testing;

#define PARSE_ASSIGN_VALID(n, str) PARSE_VALID2(Assign, n, str)
#define PARSE_ASSIGN_INVALID(n, str, errCls) PARSE_INVALID(Assign, n, str, errCls)

#define INTERPRET_ASSIGN(n, body) TEST_INTERPRET(Assign, n, body)

#define CHECK_INTEGER(name, val) \
    auto name = dynamic_cast<Integer*>(r.v->getMemory()[0][#name]); \
    ASSERT_NE(name, nullptr); \
    ASSERT_EQ(name->value, val);

PARSE_ASSIGN_INVALID(0, R"(
foo = 
)", ParserError);

PARSE_ASSIGN_VALID(1, R"(
foo = 42)");

PARSE_ASSIGN_VALID(2, R"(
foo = 42)");

INTERPRET_ASSIGN(3, {
    EVALUATE(R"(foo = 42)", {
        ASSERT_EQ(Statement::counter(), 3);

        ASSERT_EQ(r.v->getOperands().size(), 0);
        ASSERT_EQ(r.v->getMemory()[0].size(), 1);

        CHECK_INTEGER(foo, 42)
    })
})

INTERPRET_ASSIGN(4, {
    EVALUATE(R"(foo, bar = 42, 24)", {
        ASSERT_EQ(Statement::counter(), 5);

        ASSERT_EQ(r.v->getOperands().size(), 0);
        ASSERT_EQ(r.v->getMemory()[0].size(), 2);

        CHECK_INTEGER(foo, 42)
        CHECK_INTEGER(bar, 24)
    })
})

INTERPRET_ASSIGN(5, {
    EVALUATE(R"(a, b, c = 1, 2)", {
        ASSERT_EQ(Statement::counter(), 6);

        ASSERT_EQ(r.v->getOperands().size(), 0);
        ASSERT_EQ(r.v->getMemory()[0].size(), 3);

        CHECK_INTEGER(a, 1);
        CHECK_INTEGER(b, 2);

        auto c = dynamic_cast<Nil*>(r.v->getMemory()[0]["c"]);
    })
})


INTERPRET_ASSIGN(6, {
    EVALUATE(R"(a, b = 1, 2, 3)",
    {
        ASSERT_EQ(Statement::counter(), 6);

        ASSERT_EQ(r.v->getOperands().size(), 0);
        ASSERT_EQ(r.v->getMemory()[0].size(), 2);

        CHECK_INTEGER(a, 1);
        CHECK_INTEGER(b, 2);
    })
})

INTERPRET_ASSIGN(7, {
    DEBUGGING(R"(
a = 1

b = a

c = 0
)", {
        BREAKPOINT(4, {
            ASSERT_EQ(r.v->getOperands().size(), 0);
            ASSERT_EQ(r.v->getMemory()[0].size(), 1);

            CHECK_INTEGER(a, 1);
        })
        BREAKPOINT(6, {
           ASSERT_EQ(r.v->getOperands().size(), 0);
           ASSERT_EQ(r.v->getMemory()[0].size(), 2);

           CHECK_INTEGER(a, 1);
           CHECK_INTEGER(b, 1);
        })
    }, )
})



