#include "test.h"

using namespace std;
using namespace Poco;
using namespace fun;
using namespace testing;

#define CHECK_INTEGER(name, val) \
    auto name = dynamic_cast<Integer*>(r.v->getMemory()[0][#name]); \
    ASSERT_NE(name, nullptr); \
    ASSERT_EQ(name->value, val);

PARSE_ERR(Assign, 0, R"(
foo = 
)", ParserError);

PARSE(Assign, 1, R"(
foo = 42)");

PARSE(Assign, 2, R"(
foo = 42)");

EVAL(Assign, 3, R"(foo = 42)",,
    ASSERT_EQ(Statement::counter(), 3);

    ASSERT_EQ(r.v->getOperands().size(), 0);
    ASSERT_EQ(r.v->getMemory()[0].size(), 1);

    CHECK_INTEGER(foo, 42)
)

EVAL(Assign, 4, R"(foo, bar = 42, 24)",,
    ASSERT_EQ(Statement::counter(), 5);

    ASSERT_EQ(r.v->getOperands().size(), 0);
    ASSERT_EQ(r.v->getMemory()[0].size(), 2);

    CHECK_INTEGER(foo, 42)
    CHECK_INTEGER(bar, 24)
)

EVAL(Assign, 5, R"(a, b, c = 1, 2)",,
    ASSERT_EQ(Statement::counter(), 6);

    ASSERT_EQ(r.v->getOperands().size(), 0);
    ASSERT_EQ(r.v->getMemory()[0].size(), 3);

    CHECK_INTEGER(a, 1);
    CHECK_INTEGER(b, 2);

    auto c = dynamic_cast<Nil*>(r.v->getMemory()[0]["c"]);
)


EVAL(Assign, 6, R"(a, b = 1, 2, 3)",,
    ASSERT_EQ(Statement::counter(), 6);

    ASSERT_EQ(r.v->getOperands().size(), 0);
    ASSERT_EQ(r.v->getMemory()[0].size(), 2);

    CHECK_INTEGER(a, 1);
    CHECK_INTEGER(b, 2);
)

EVAL(Assign, 7, R"(
a = 1

b = a

c = 0
)",
    BREAKPOINT(4,
        ASSERT_EQ(r.v->getOperands().size(), 0);
        ASSERT_EQ(r.v->getMemory()[0].size(), 1);

        CHECK_INTEGER(a, 1);
    )
    BREAKPOINT(6,
       ASSERT_EQ(r.v->getOperands().size(), 0);
       ASSERT_EQ(r.v->getMemory()[0].size(), 2);

       CHECK_INTEGER(a, 1);
       CHECK_INTEGER(b, 1);
    )
    ,
)

PARSE(Assign, 8, R"(
foo = 0
foo += 42)");

PARSE(Assign, 9, R"(
bar = 0
foo += bar)");

PARSE(Assign, 10, R"(
foo = 0
foo -= 42)");

PARSE(Assign, 11, R"(
bar = 0
foo -= bar)");

PARSE(Assign, 12, R"(
foo = 0
foo *= 100)");

PARSE(Assign, 13, R"(
bar = 3
foo *= bar)");

PARSE(Assign, 14, R"(
foo = 2
foo /= 4)");

PARSE(Assign, 15, R"(
bar = 2
foo /= bar)");

PARSE(Assign, 16, R"(
foo = 2
foo %= bar)");

PARSE(Assign, 17, R"(
bar = 2
foo %= bar)");

PARSE(Assign, 18, R"(
foo = 123
foo <<= 4)");

PARSE(Assign, 19, R"(
bar = 2
foo <<= bar)");

PARSE(Assign, 20, R"(
foo = 2
foo >>= 1)");

PARSE(Assign, 21, R"(
bar = 2
foo >>= bar)");

PARSE(Assign, 22, R"(
foo = 234
foo &= 423)");

PARSE(Assign, 23, R"(
bar = 6345
foo &= 5234)");

PARSE(Assign, 24, R"(
foo = 6345
foo |= 7456)");

PARSE(Assign, 25, R"(
bar = bar
foo |= 3645)");

PARSE(Assign, 26, R"(
foo = 95689
foo ^= 8567)");

PARSE(Assign, 27, R"(
bar = 746
foo ^= bar)");

PARSE(Assign, 28, R"(
bar = 36573 + 234
foo ^= bar)");

PARSE_ERR(Assign, 29, R"(
foo += 
)", ParserError);

PARSE_ERR(Assign, 30, R"(
foo ++= 
)", ParserError);

PARSE_ERR(Assign, 31, R"(
foo +== 
)", ParserError);

PARSE_ERR(Assign, 32, R"(
foo ++= 4234
)", ParserError);

PARSE_ERR(Assign, 33, R"(
foo +== 235 
)", ParserError);

PARSE_ERR(Assign, 34, R"(
foo --= 
)", ParserError);

PARSE_ERR(Assign, 35, R"(
foo -== 
)", ParserError);

PARSE_ERR(Assign, 36, R"(
foo --= 243
)", ParserError);

PARSE_ERR(Assign, 37, R"(
foo -== asd 
)", ParserError);

PARSE_ERR(Assign, 38, R"(
foo *= 
)", ParserError);

PARSE_ERR(Assign, 39, R"(
foo **= 
)", ParserError);

PARSE_ERR(Assign, 40, R"(
foo *== 
)", ParserError);

PARSE_ERR(Assign, 41, R"(
foo **= adsf
)", ParserError);

PARSE_ERR(Assign, 42, R"(
foo *== 234
)", ParserError);

PARSE_ERR(Assign, 43, R"(
foo /= 
)", ParserError);

PARSE_ERR(Assign, 44, R"(
foo /== 
)", ParserError);

PARSE_ERR(Assign, 45, R"(
foo //= 
)", ParserError);

PARSE_ERR(Assign, 46, R"(
foo //= 345
)", ParserError);

PARSE_ERR(Assign, 47, R"(
foo /== 2354
)", ParserError);

PARSE_ERR(Assign, 48, R"(
foo %= 
)", ParserError);

PARSE_ERR(Assign, 49, R"(
foo %%= 
)", ParserError);

PARSE_ERR(Assign, 50, R"(
foo %== 
)", ParserError);

PARSE_ERR(Assign, 51, R"(
foo %%= 34
)", ParserError);

PARSE_ERR(Assign, 52, R"(
foo %== 345 
)", ParserError);

PARSE_ERR(Assign, 53, R"(
foo &= 
)", ParserError);

PARSE_ERR(Assign, 54, R"(
foo &&= 
)", ParserError);

PARSE_ERR(Assign, 55, R"(
foo &== 
)", ParserError);

PARSE_ERR(Assign, 56, R"(
foo &&= a345
)", ParserError);

PARSE_ERR(Assign, 57, R"(
foo &== adsf
)", ParserError);

PARSE_ERR(Assign, 58, R"(
foo |= 
)", ParserError);

PARSE_ERR(Assign, 59, R"(
foo ||= 
)", ParserError);

PARSE_ERR(Assign, 60, R"(
foo |== 
)", ParserError);

PARSE_ERR(Assign, 61, R"(
foo ||= asdf
)", ParserError);

PARSE_ERR(Assign, 62, R"(
foo |== asdf
)", ParserError);

