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

PARSE_ASSIGN_VALID(8, R"(
foo = 0
foo += 42)");

PARSE_ASSIGN_VALID(9, R"(
bar = 0
foo += bar)");

PARSE_ASSIGN_VALID(10, R"(
foo = 0
foo -= 42)");

PARSE_ASSIGN_VALID(11, R"(
bar = 0
foo -= bar)");

PARSE_ASSIGN_VALID(12, R"(
foo = 0
foo *= 100)");

PARSE_ASSIGN_VALID(13, R"(
bar = 3
foo *= bar)");

PARSE_ASSIGN_VALID(14, R"(
foo = 2
foo /= 4)");

PARSE_ASSIGN_VALID(15, R"(
bar = 2
foo /= bar)");

PARSE_ASSIGN_VALID(16, R"(
foo = 2
foo %= bar)");

PARSE_ASSIGN_VALID(17, R"(
bar = 2
foo %= bar)");

PARSE_ASSIGN_VALID(18, R"(
foo = 123
foo <<= 4)");

PARSE_ASSIGN_VALID(19, R"(
bar = 2
foo <<= bar)");

PARSE_ASSIGN_VALID(20, R"(
foo = 2
foo >>= 1)");

PARSE_ASSIGN_VALID(21, R"(
bar = 2
foo >>= bar)");

PARSE_ASSIGN_VALID(22, R"(
foo = 234
foo &= 423)");

PARSE_ASSIGN_VALID(23, R"(
bar = 6345
foo &= 5234)");

PARSE_ASSIGN_VALID(24, R"(
foo = 6345
foo |= 7456)");

PARSE_ASSIGN_VALID(25, R"(
bar = bar
foo |= 3645)");

PARSE_ASSIGN_VALID(26, R"(
foo = 95689
foo ^= 8567)");

PARSE_ASSIGN_VALID(27, R"(
bar = 746
foo ^= bar)");

PARSE_ASSIGN_VALID(28, R"(
bar = 36573 + 234
foo ^= bar)");

PARSE_ASSIGN_INVALID(29, R"(
foo += 
)", ParserError);

PARSE_ASSIGN_INVALID(30, R"(
foo ++= 
)", ParserError);

PARSE_ASSIGN_INVALID(31, R"(
foo +== 
)", ParserError);

PARSE_ASSIGN_INVALID(32, R"(
foo ++= 4234
)", ParserError);

PARSE_ASSIGN_INVALID(33, R"(
foo +== 235 
)", ParserError);

PARSE_ASSIGN_INVALID(34, R"(
foo --= 
)", ParserError);

PARSE_ASSIGN_INVALID(35, R"(
foo -== 
)", ParserError);

PARSE_ASSIGN_INVALID(36, R"(
foo --= 243
)", ParserError);

PARSE_ASSIGN_INVALID(37, R"(
foo -== asd 
)", ParserError);

PARSE_ASSIGN_INVALID(38, R"(
foo *= 
)", ParserError);

PARSE_ASSIGN_INVALID(39, R"(
foo **= 
)", ParserError);

PARSE_ASSIGN_INVALID(40, R"(
foo *== 
)", ParserError);

PARSE_ASSIGN_INVALID(41, R"(
foo **= adsf
)", ParserError);

PARSE_ASSIGN_INVALID(42, R"(
foo *== 234
)", ParserError);

PARSE_ASSIGN_INVALID(43, R"(
foo /= 
)", ParserError);

PARSE_ASSIGN_INVALID(44, R"(
foo /== 
)", ParserError);

PARSE_ASSIGN_INVALID(45, R"(
foo //= 
)", ParserError);

PARSE_ASSIGN_INVALID(46, R"(
foo //= 345
)", ParserError);

PARSE_ASSIGN_INVALID(47, R"(
foo /== 2354
)", ParserError);

PARSE_ASSIGN_INVALID(48, R"(
foo %= 
)", ParserError);

PARSE_ASSIGN_INVALID(49, R"(
foo %%= 
)", ParserError);

PARSE_ASSIGN_INVALID(50, R"(
foo %== 
)", ParserError);

PARSE_ASSIGN_INVALID(51, R"(
foo %%= 34
)", ParserError);

PARSE_ASSIGN_INVALID(52, R"(
foo %== 345 
)", ParserError);

PARSE_ASSIGN_INVALID(53, R"(
foo &= 
)", ParserError);

PARSE_ASSIGN_INVALID(54, R"(
foo &&= 
)", ParserError);

PARSE_ASSIGN_INVALID(55, R"(
foo &== 
)", ParserError);

PARSE_ASSIGN_INVALID(56, R"(
foo &&= a345
)", ParserError);

PARSE_ASSIGN_INVALID(57, R"(
foo &== adsf
)", ParserError);

PARSE_ASSIGN_INVALID(58, R"(
foo |= 
)", ParserError);

PARSE_ASSIGN_INVALID(59, R"(
foo ||= 
)", ParserError);

PARSE_ASSIGN_INVALID(60, R"(
foo |== 
)", ParserError);

PARSE_ASSIGN_INVALID(61, R"(
foo ||= asdf
)", ParserError);

PARSE_ASSIGN_INVALID(62, R"(
foo |== asdf
)", ParserError);

