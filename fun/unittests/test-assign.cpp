#include "test.h"

using namespace std;
using namespace Poco;
using namespace fun;
using namespace testing;

#define CHECK_INTEGER(name, val) \
    auto name = dynamic_cast<Integer*>(r.v->getMemory()[0][#name]); \
    ASSERT_NE(name, nullptr); \
    ASSERT_EQ(name->value, val);

#define CHECK_NIL(name) \
    auto name = dynamic_cast<Nil*>(r.v->getMemory()[0][#name]); \
    ASSERT_NE(name, nullptr);


PARSE_ERR(Assign, 1, R"(
foo = 
)", ParserError);

PARSE(Assign, 2, R"(
foo = 42)");

PARSE(Assign, 3, R"(
foo = 42)");

EVAL(Assign, 4, R"(foo = 42)",,
    ASSERT_EQ(Statement::counter(), 3);

    ASSERT_EQ(r.v->getOperands().size(), 0);
    ASSERT_EQ(r.v->getMemory()[0].size(), 1);

    CHECK_INTEGER(foo, 42)
)

EVAL(Assign, 5, R"(foo, bar = 42, 24)",,
    ASSERT_EQ(Statement::counter(), 5);

    ASSERT_EQ(r.v->getOperands().size(), 0);
    ASSERT_EQ(r.v->getMemory()[0].size(), 2);

    CHECK_INTEGER(foo, 42)
    CHECK_INTEGER(bar, 24)
)

EVAL(Assign, 6, R"(a, b, c = 1, 2)",,
    ASSERT_EQ(Statement::counter(), 7);

    ASSERT_EQ(r.v->getOperands().size(), 0);
    ASSERT_EQ(r.v->getMemory()[0].size(), 3);

    CHECK_INTEGER(a, 1);
    CHECK_INTEGER(b, 2);

    CHECK_NIL(c);
)


EVAL(Assign, 7, R"(a, b = 1, 2, 3)",,
    ASSERT_EQ(Statement::counter(), 6);

    ASSERT_EQ(r.v->getOperands().size(), 0);
    ASSERT_EQ(r.v->getMemory()[0].size(), 2);

    CHECK_INTEGER(a, 1);
    CHECK_INTEGER(b, 2);
)

EVAL(Assign, 8, R"(
a = 1

b = a
)",
    BREAKPOINT_LINE(4,
        ASSERT_EQ(r.v->getOperands().size(), 0);
        ASSERT_EQ(r.v->getMemory()[0].size(), 1);

        CHECK_INTEGER(a, 1);
    )
    ,
    ASSERT_EQ(r.v->getOperands().size(), 0);
    ASSERT_EQ(r.v->getMemory()[0].size(), 2);

    CHECK_INTEGER(a, 1);
    CHECK_INTEGER(b, 1);
)

PARSE(Assign, 9, R"(
foo = 0
foo += 42)");

PARSE(Assign, 10, R"(
bar = 0
foo += bar)");

PARSE(Assign, 11, R"(
foo = 0
bar = 0
foo, bar += 42, 32)");

PARSE(Assign, 12, R"(
bar = 0
foo = 10
quz = 30
foo, bar += quz, quz)");

PARSE(Assign, 13, R"(
foo = 0
bar = 0
C = 0
foo, bar, C += 42, 32)");

PARSE(Assign, 14, R"(
bar = 0
foo = 10
quz = 30
foo, bar += quz, quz, quz)");

PARSE(Assign, 15, R"(
foo = 0
foo -= 42)");

PARSE(Assign, 16, R"(
bar = 0
foo -= bar)");

PARSE(Assign, 17, R"(
a = 0
b = 0
a, b -= 42, 10)");

PARSE(Assign, 18, R"(
a = 100
b = 100
c = 24
a, b -= c, c)");

PARSE(Assign, 19, R"(
a = 50
b = 50
n = 3
a, b -= 42, 234, 23)");

PARSE(Assign, 20, R"(
_a = 340
_b = 230
_c = 235
_d = 35
_a, _b, _c -= _d, _d)");

PARSE(Assign, 21, R"(
foo = 0
foo *= 100)");

PARSE(Assign, 22, R"(
bar = 3
foo *= bar)");

PARSE(Assign, 23, R"(
a = 2
b = 3
a, b *= 3, 4)");

PARSE(Assign, 24, R"(
a = 3
b = 4
c = 5
a, b *= c, c)");

PARSE(Assign, 25, R"(
a = 2
b = 3
a, b, c *= 3, 4)");

PARSE(Assign, 26, R"(
a = 3
b = 4
c = 5
a, b, d *= c, c)");

PARSE(Assign, 27, R"(
a = 2
b = 3
a, b, c *= 3, 4)");

PARSE(Assign, 28, R"(
a = 3
b = 4
c = 5
a, b *= c, c, c)");

PARSE(Assign, 29, R"(
foo = 2
foo /= 4)");

PARSE(Assign, 30, R"(
bar = 2
foo /= bar)");

PARSE(Assign, 31, R"(
foo = 2
foo %= bar)");

PARSE(Assign, 32, R"(
bar = 2
foo %= bar)");

PARSE(Assign, 33, R"(
foo = 123
foo <<= 4)");

PARSE(Assign, 34, R"(
bar = 2
foo <<= bar)");

PARSE(Assign, 35, R"(
foo = 2
foo >>= 1)");

PARSE(Assign, 36, R"(
bar = 2
foo >>= bar)");

PARSE(Assign, 37, R"(
foo = 234
foo &= 423)");

PARSE(Assign, 38, R"(
bar = 6345
foo &= 5234)");

PARSE(Assign, 39, R"(
foo = 6345
foo |= 7456)");

PARSE(Assign, 40, R"(
bar = bar
foo |= 3645)");

PARSE(Assign, 41, R"(
foo = 95689
foo ^= 8567)");

PARSE(Assign, 42, R"(
bar = 746
foo ^= bar)");

PARSE(Assign, 43, R"(
bar = 36573 + 234
foo ^= bar)");

PARSE_ERR(Assign, 44, R"(
foo += 
)", ParserError);

PARSE_ERR(Assign, 45, R"(
foo ++= 
)", ParserError);

PARSE_ERR(Assign, 46, R"(
foo +== 
)", ParserError);

PARSE_ERR(Assign, 47, R"(
foo ++= 4234
)", ParserError);

PARSE_ERR(Assign, 48, R"(
foo +== 235 
)", ParserError);

PARSE_ERR(Assign, 49, R"(
foo --= 
)", ParserError);

PARSE_ERR(Assign, 50, R"(
foo -== 
)", ParserError);

PARSE_ERR(Assign, 51, R"(
foo --= 243
)", ParserError);

PARSE_ERR(Assign, 52, R"(
foo -== asd 
)", ParserError);

PARSE_ERR(Assign, 53, R"(
foo *= 
)", ParserError);

PARSE_ERR(Assign, 54, R"(
foo **= 
)", ParserError);

PARSE_ERR(Assign, 55, R"(
foo *== 
)", ParserError);

PARSE_ERR(Assign, 56, R"(
foo **= adsf
)", ParserError);

PARSE_ERR(Assign, 57, R"(
foo *== 234
)", ParserError);

PARSE_ERR(Assign, 58, R"(
foo /= 
)", ParserError);

PARSE_ERR(Assign, 59, R"(
foo /== 
)", ParserError);

PARSE_ERR(Assign, 60, R"(
foo //= 
)", ParserError);

PARSE_ERR(Assign, 61, R"(
foo //= 345
)", ParserError);

PARSE_ERR(Assign, 62, R"(
foo /== 2354
)", ParserError);

PARSE_ERR(Assign, 63, R"(
foo %= 
)", ParserError);

PARSE_ERR(Assign, 64, R"(
foo %%= 
)", ParserError);

PARSE_ERR(Assign, 65, R"(
foo %== 
)", ParserError);

PARSE_ERR(Assign, 66, R"(
foo %%= 34
)", ParserError);

PARSE_ERR(Assign, 67, R"(
foo %== 345 
)", ParserError);

PARSE_ERR(Assign, 68, R"(
foo &= 
)", ParserError);

PARSE_ERR(Assign, 69, R"(
foo &&= 
)", ParserError);

PARSE_ERR(Assign, 70, R"(
foo &== 
)", ParserError);

PARSE_ERR(Assign, 71, R"(
foo &&= a345
)", ParserError);

PARSE_ERR(Assign, 72, R"(
foo &== adsf
)", ParserError);

PARSE_ERR(Assign, 73, R"(
foo |= 
)", ParserError);

PARSE_ERR(Assign, 74, R"(
foo ||= 
)", ParserError);

PARSE_ERR(Assign, 75, R"(
foo |== 
)", ParserError);

PARSE_ERR(Assign, 76, R"(
foo ||= asdf
)", ParserError);

PARSE_ERR(Assign, 77, R"(
foo |== asdf
)", ParserError);

EVAL(Assign, 78, R"(
foo = 42
foo += 10
)",
    BREAKPOINT_LINE(3,
        ASSERT_EQ(r.v->getOperands().size(), 0);
        ASSERT_EQ(r.v->getMemory()[0].size(), 1);

        CHECK_INTEGER(foo, 42);
    )
    ,
    ASSERT_EQ(r.v->getOperands().size(), 0);
    ASSERT_EQ(r.v->getMemory()[0].size(), 1);

    CHECK_INTEGER(foo, 52);
)

EVAL(Assign, 79, R"(
foo = 42
bar = 100
foo += bar
)",
    BREAKPOINT_LINE(4,
        ASSERT_EQ(r.v->getOperands().size(), 0);
        ASSERT_EQ(r.v->getMemory()[0].size(), 2);

        CHECK_INTEGER(bar, 100);
        CHECK_INTEGER(foo, 42);
    )
    ,
    ASSERT_EQ(r.v->getOperands().size(), 0);
    ASSERT_EQ(r.v->getMemory()[0].size(), 2);

    CHECK_INTEGER(bar, 100);
    CHECK_INTEGER(foo, 142);
)

EVAL(Assign, 80, R"(
foo = 42
bar = 100
foo, bar += 12, 13
)",
    BREAKPOINT_LINE(4,
        ASSERT_EQ(r.v->getOperands().size(), 0);
        ASSERT_EQ(r.v->getMemory()[0].size(), 2);

        CHECK_INTEGER(foo, 42);
        CHECK_INTEGER(bar, 100);
    )
    ,
    ASSERT_EQ(r.v->getOperands().size(), 0);
    ASSERT_EQ(r.v->getMemory()[0].size(), 2);

    CHECK_INTEGER(foo, 42 + 12);
    CHECK_INTEGER(bar, 100 + 13);
)

EVAL(Assign, 81, R"(
foo = 42
bar = 100
c = 123
d = 321
foo, bar += c, d
)",
    BREAKPOINT_LINE(6,
        ASSERT_EQ(r.v->getOperands().size(), 0);
        ASSERT_EQ(r.v->getMemory()[0].size(), 4);

        CHECK_INTEGER(foo, 42);
        CHECK_INTEGER(bar, 100);
        CHECK_INTEGER(c, 123);
        CHECK_INTEGER(d, 321);
    )
    ,
    ASSERT_EQ(r.v->getOperands().size(), 0);
    ASSERT_EQ(r.v->getMemory()[0].size(), 4);

    CHECK_INTEGER(foo, 42 + 123);
    CHECK_INTEGER(bar, 100 + 321);
    CHECK_INTEGER(c, 123);
    CHECK_INTEGER(d, 321);
)

EVAL(Assign, 82, R"(
foo = 42
bar = 100
c = 123
d = 321
foo, bar += c, d, 100
)",
    BREAKPOINT_LINE(6,
        ASSERT_EQ(r.v->getOperands().size(), 0);
        ASSERT_EQ(r.v->getMemory()[0].size(), 4);

        CHECK_INTEGER(foo, 42);
        CHECK_INTEGER(bar, 100);
        CHECK_INTEGER(c, 123);
        CHECK_INTEGER(d, 321);
    )
    ,
    ASSERT_EQ(r.v->getOperands().size(), 0);
    ASSERT_EQ(r.v->getMemory()[0].size(), 4);

    CHECK_INTEGER(foo, 42 + 123);
    CHECK_INTEGER(bar, 100 + 321);
    CHECK_INTEGER(c, 123);
    CHECK_INTEGER(d, 321);
)

EVAL(Assign, 83, R"(
foo = 42
bar = 100
c = 123
d = 321
E = 0
foo, bar, E += c, d
)",
    BREAKPOINT_LINE(6,
        ASSERT_EQ(r.v->getOperands().size(), 0);
        ASSERT_EQ(r.v->getMemory()[0].size(), 4);

        CHECK_INTEGER(foo, 42);
        CHECK_INTEGER(bar, 100);
        CHECK_INTEGER(c, 123);
        CHECK_INTEGER(d, 321);
    )
    ,
    ASSERT_EQ(r.v->getOperands().size(), 0);
    ASSERT_EQ(r.v->getMemory()[0].size(), 5);

    CHECK_INTEGER(foo, 42 + 123);
    CHECK_INTEGER(bar, 100 + 321);
    CHECK_INTEGER(c, 123);
    CHECK_INTEGER(d, 321);
    CHECK_INTEGER(E, 0);
)

EVAL(Assign, 84, R"(
foo = 42
foo -= 10
)",
    BREAKPOINT_LINE(3,
        ASSERT_EQ(r.v->getOperands().size(), 0);
        ASSERT_EQ(r.v->getMemory()[0].size(), 1);

        CHECK_INTEGER(foo, 42);
    )
    ,
    ASSERT_EQ(r.v->getOperands().size(), 0);
    ASSERT_EQ(r.v->getMemory()[0].size(), 1);

    CHECK_INTEGER(foo, 32);
)

EVAL(Assign, 85, R"(
foo = 42
foo, E -= 10
)",
    BREAKPOINT_LINE(3,
        ASSERT_EQ(r.v->getOperands().size(), 0);
        ASSERT_EQ(r.v->getMemory()[0].size(), 1);

        CHECK_INTEGER(foo, 42);

        // http://stackoverflow.com/questions/8648243/google-mock-how-can-i-expect-that-no-method-will-be-called-on-a-mock
    )
    ,
    ASSERT_EQ(r.v->getOperands().size(), 0);
    ASSERT_EQ(r.v->getMemory()[0].size(), 1);

    CHECK_INTEGER(foo, 32);
)

EVAL(Assign, 86, R"(
foo = 42
a = 12
foo -= a
)",
    BREAKPOINT_LINE(4,
        ASSERT_EQ(r.v->getOperands().size(), 0);
        ASSERT_EQ(r.v->getMemory()[0].size(), 2);

        CHECK_INTEGER(foo, 42);
        CHECK_INTEGER(a, 12);
    )
    ,
    ASSERT_EQ(r.v->getOperands().size(), 0);
    ASSERT_EQ(r.v->getMemory()[0].size(), 2);

    CHECK_INTEGER(foo, 30);
    CHECK_INTEGER(a, 12);
)

EVAL(Assign, 87, R"(
foo = 42
b = 10
foo, b -= 10, 3
)",
    BREAKPOINT_LINE(4,
        ASSERT_EQ(r.v->getOperands().size(), 0);
        ASSERT_EQ(r.v->getMemory()[0].size(), 2);

        CHECK_INTEGER(foo, 42);
        CHECK_INTEGER(b, 10);
    )
    ,
    ASSERT_EQ(r.v->getOperands().size(), 0);
    ASSERT_EQ(r.v->getMemory()[0].size(), 2);

    CHECK_INTEGER(foo, 42 - 10);
    CHECK_INTEGER(b, 10 - 3);
)

EVAL(Assign, 88, R"(
foo = 42
b = 34
a = 12
foo, b -= a, a
)",
    BREAKPOINT_LINE(5,
        ASSERT_EQ(r.v->getOperands().size(), 0);
        ASSERT_EQ(r.v->getMemory()[0].size(), 3);

        CHECK_INTEGER(foo, 42);
        CHECK_INTEGER(b, 34);
        CHECK_INTEGER(a, 12);
    )
    ,
    ASSERT_EQ(r.v->getOperands().size(), 0);
    ASSERT_EQ(r.v->getMemory()[0].size(), 3);

    CHECK_INTEGER(foo, 42 - 12);
    CHECK_INTEGER(b, 34 - 12);
    CHECK_INTEGER(a, 12);
)

EVAL(Assign, 89, R"(
foo = 42
b = 34
a = 12
foo, b -= a, a, a
)",
    BREAKPOINT_LINE(5,
        ASSERT_EQ(r.v->getOperands().size(), 0);
        ASSERT_EQ(r.v->getMemory()[0].size(), 3);

        CHECK_INTEGER(foo, 42);
        CHECK_INTEGER(b, 34);
        CHECK_INTEGER(a, 12);
    )
    ,
    ASSERT_EQ(r.v->getOperands().size(), 0);
    ASSERT_EQ(r.v->getMemory()[0].size(), 3);

    CHECK_INTEGER(foo, 42 - 12);
    CHECK_INTEGER(b, 34 - 12);
    CHECK_INTEGER(a, 12);
)

EVAL(Assign, 90, R"(
foo = 42
b = 34
a = 12
c = 23
foo, b, c -= a, a
)",
    BREAKPOINT_LINE(6,
        ASSERT_EQ(r.v->getOperands().size(), 0);
        ASSERT_EQ(r.v->getMemory()[0].size(), 4);

        CHECK_INTEGER(foo, 42);
        CHECK_INTEGER(b, 34);
        CHECK_INTEGER(a, 12);
        CHECK_INTEGER(c, 23);
    )
    ,
    ASSERT_EQ(r.v->getOperands().size(), 0);
    ASSERT_EQ(r.v->getMemory()[0].size(), 4);

    CHECK_INTEGER(foo, 42 - 12);
    CHECK_INTEGER(b, 34 - 12);
    CHECK_INTEGER(a, 12);
    CHECK_INTEGER(c, 23);
)

EVAL(Assign, 91, R"(
foo = 42
foo *= 10
)",
    BREAKPOINT_LINE(3,
        ASSERT_EQ(r.v->getOperands().size(), 0);
        ASSERT_EQ(r.v->getMemory()[0].size(), 1);

        CHECK_INTEGER(foo, 42);
    )
    ,
    ASSERT_EQ(r.v->getOperands().size(), 0);
    ASSERT_EQ(r.v->getMemory()[0].size(), 1);

    CHECK_INTEGER(foo, 420);
)

EVAL(Assign, 92, R"(
foo = 42
bar = 23
foo *= bar
)",
    BREAKPOINT_LINE(4,
        ASSERT_EQ(r.v->getOperands().size(), 0);
        ASSERT_EQ(r.v->getMemory()[0].size(), 2);

        CHECK_INTEGER(foo, 42);
        CHECK_INTEGER(bar, 23);
    )
    ,
    ASSERT_EQ(r.v->getOperands().size(), 0);
    ASSERT_EQ(r.v->getMemory()[0].size(), 2);

    CHECK_INTEGER(foo, 42*23);
    CHECK_INTEGER(bar, 23);
)

EVAL(Assign, 93, R"(
foo = 42
foo /= 2
)",
    BREAKPOINT_LINE(3,
        ASSERT_EQ(r.v->getOperands().size(), 0);
        ASSERT_EQ(r.v->getMemory()[0].size(), 1);

        CHECK_INTEGER(foo, 42);
    )
    ,
    ASSERT_EQ(r.v->getOperands().size(), 0);
    ASSERT_EQ(r.v->getMemory()[0].size(), 1);

    CHECK_INTEGER(foo, 42/2);
)

EVAL(Assign, 94, R"(
foo = 42
bb = 3
foo /= bb
)",
    BREAKPOINT_LINE(4,
        ASSERT_EQ(r.v->getOperands().size(), 0);
        ASSERT_EQ(r.v->getMemory()[0].size(), 2);

        CHECK_INTEGER(foo, 42);
        CHECK_INTEGER(bb, 3);
    )
    ,
    ASSERT_EQ(r.v->getOperands().size(), 0);
    ASSERT_EQ(r.v->getMemory()[0].size(), 2);

    CHECK_INTEGER(foo, 42/3);
    CHECK_INTEGER(bb, 3);
)

EVAL(Assign, 95, R"(
foo = 42
foo %= 4
nil
)",
    BREAKPOINT_EXPR(4, 0, 3,
        ASSERT_EQ(r.v->getOperands().size(), 0);
        ASSERT_EQ(r.v->getMemory()[0].size(), 1);

        CHECK_INTEGER(foo, 42%4);
    )
    ,
)

EVAL(Assign, 96, R"(
foo = 42
q = 5
foo %= q
)",
    BREAKPOINT_LINE(4,
        ASSERT_EQ(r.v->getOperands().size(), 0);
        ASSERT_EQ(r.v->getMemory()[0].size(), 2);

        CHECK_INTEGER(foo, 42);
        CHECK_INTEGER(q, 5);
    )
    ,
    ASSERT_EQ(r.v->getOperands().size(), 0);
    ASSERT_EQ(r.v->getMemory()[0].size(), 2);

    CHECK_INTEGER(foo, 42%5);
    CHECK_INTEGER(q, 5);
)

EVAL(Assign, 97, R"(
foo = 42
foo <<= 3
)",
    BREAKPOINT_LINE(3,
        ASSERT_EQ(r.v->getOperands().size(), 0);
        ASSERT_EQ(r.v->getMemory()[0].size(), 1);

        CHECK_INTEGER(foo, 42);
    )
    ,
    ASSERT_EQ(r.v->getOperands().size(), 0);
    ASSERT_EQ(r.v->getMemory()[0].size(), 1);

    CHECK_INTEGER(foo, 42<<3);
)

EVAL(Assign, 98, R"(
foo = 42
test = 4
foo <<= test
)",
    BREAKPOINT_LINE(4,
        ASSERT_EQ(r.v->getOperands().size(), 0);
        ASSERT_EQ(r.v->getMemory()[0].size(), 2);

        CHECK_INTEGER(foo, 42);
        CHECK_INTEGER(test, 4);
    )
    ,
    ASSERT_EQ(r.v->getOperands().size(), 0);
    ASSERT_EQ(r.v->getMemory()[0].size(), 2);

    CHECK_INTEGER(foo, 42<<4);
    CHECK_INTEGER(test, 4);
)


EVAL(Assign, 99, R"(
foo = 42
foo >>= 2
)",
    BREAKPOINT_LINE(3,
        ASSERT_EQ(r.v->getOperands().size(), 0);
        ASSERT_EQ(r.v->getMemory()[0].size(), 1);

        CHECK_INTEGER(foo, 42);
    )
    ,
    ASSERT_EQ(r.v->getOperands().size(), 0);
    ASSERT_EQ(r.v->getMemory()[0].size(), 1);

    CHECK_INTEGER(foo, 42>>2);
)

EVAL(Assign, 100, R"(
foo = 42
T = 3
foo >>= T
)",
    BREAKPOINT_LINE(4,
        ASSERT_EQ(r.v->getOperands().size(), 0);
        ASSERT_EQ(r.v->getMemory()[0].size(), 2);

        CHECK_INTEGER(foo, 42);
        CHECK_INTEGER(T, 3);
    )
    ,
    ASSERT_EQ(r.v->getOperands().size(), 0);
    ASSERT_EQ(r.v->getMemory()[0].size(), 2);

    CHECK_INTEGER(foo, 42>>3);
    CHECK_INTEGER(T, 3);
)


EVAL(Assign, 101, R"(
foo = 42
foo &= 12
)",
    BREAKPOINT_LINE(3,
        ASSERT_EQ(r.v->getOperands().size(), 0);
        ASSERT_EQ(r.v->getMemory()[0].size(), 1);

        CHECK_INTEGER(foo, 42);
    )
    ,
    ASSERT_EQ(r.v->getOperands().size(), 0);
    ASSERT_EQ(r.v->getMemory()[0].size(), 1);

    CHECK_INTEGER(foo, 42&12);
)

EVAL(Assign, 102, R"(
foo = 42
A = 34
foo &= A
)",
    BREAKPOINT_LINE(4,
        ASSERT_EQ(r.v->getOperands().size(), 0);
        ASSERT_EQ(r.v->getMemory()[0].size(), 2);

        CHECK_INTEGER(foo, 42);
        CHECK_INTEGER(A, 34);
    )
    ,
    ASSERT_EQ(r.v->getOperands().size(), 0);
    ASSERT_EQ(r.v->getMemory()[0].size(), 2);

    CHECK_INTEGER(foo, 42&34);
    CHECK_INTEGER(A, 34);
)


EVAL(Assign, 103, R"(
foo = 42
foo |= 54
)",
    BREAKPOINT_LINE(3,
        ASSERT_EQ(r.v->getOperands().size(), 0);
        ASSERT_EQ(r.v->getMemory()[0].size(), 1);

        CHECK_INTEGER(foo, 42);
    )
    ,
    ASSERT_EQ(r.v->getOperands().size(), 0);
    ASSERT_EQ(r.v->getMemory()[0].size(), 1);

    CHECK_INTEGER(foo, 42|54);
)

EVAL(Assign, 104, R"(
foo = 42
F = 45
foo |= F
)",
    BREAKPOINT_LINE(4,
        ASSERT_EQ(r.v->getOperands().size(), 0);
        ASSERT_EQ(r.v->getMemory()[0].size(), 2);

        CHECK_INTEGER(foo, 42);
        CHECK_INTEGER(F, 45);
    )
    ,
    ASSERT_EQ(r.v->getOperands().size(), 0);
    ASSERT_EQ(r.v->getMemory()[0].size(), 2);

    CHECK_INTEGER(foo, 42|45);
    CHECK_INTEGER(F, 45);
)


EVAL(Assign, 105, R"(
foo = 42
foo ^= 40
)",
    BREAKPOINT_LINE(3,
        ASSERT_EQ(r.v->getOperands().size(), 0);
        ASSERT_EQ(r.v->getMemory()[0].size(), 1);

        CHECK_INTEGER(foo, 42);
    )
    ,
    ASSERT_EQ(r.v->getOperands().size(), 0);
    ASSERT_EQ(r.v->getMemory()[0].size(), 1);

    CHECK_INTEGER(foo, 42^40);
)

EVAL(Assign, 106, R"(
foo = 42
G = 50
foo ^= G
)",
    BREAKPOINT_LINE(4,
        ASSERT_EQ(r.v->getOperands().size(), 0);
        ASSERT_EQ(r.v->getMemory()[0].size(), 2);

        CHECK_INTEGER(foo, 42);
        CHECK_INTEGER(G, 50);
    )
    ,
    ASSERT_EQ(r.v->getOperands().size(), 0);
    ASSERT_EQ(r.v->getMemory()[0].size(), 2);

    CHECK_INTEGER(foo, 42^50);
    CHECK_INTEGER(G, 50);
)
