#include "test.h"

using namespace std;
using namespace fun;

#define PARSE_INTEGER_VALID(n, str, v) PARSE_VALID(Print, n, str, v)
#define PARSE_INTEGER_INVALID(n, str, errCls) PARSE_INVALID(Print, n, str, errCls)

TEST(Parse, Print_0) {
    {
        EXPECT_NO_THROW(parse(R"(
print 42
print 3.14
print "foo"
print nil
print false
print true
)"));
    }
    ASSERT_EQ(Statement::counter(), 0);
}

TEST(Parse, Print_1) {
    {
        EXPECT_THROW(parse(R"(
print 
)"), ParserError);
    }
    ASSERT_EQ(Statement::counter(), 0);
}

TEST(Parse, Print_2) {
    {
        ParseResult r;
        EXPECT_NO_THROW(r = parseAst(R"(
print 42
)"););

        auto print = dynamic_cast<Print*>(r.ast->root());

        ASSERT_NE(print, nullptr);

        ASSERT_EQ(print->loc, location(position(nullptr, 2, 0), position(nullptr, 2, 8)));
    }
    ASSERT_EQ(Statement::counter(), 0);
}

