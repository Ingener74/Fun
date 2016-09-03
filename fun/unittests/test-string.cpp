#include "test.h"

using namespace std;
using namespace fun;

#define PARSE_INTEGER_VALID(n, str, v) PARSE_VALID(String, n, str, v)
#define PARSE_INTEGER_INVALID(n, str, errCls) PARSE_INVALID(String, n, str, errCls)

PARSE_INTEGER_VALID(0, R"(
"Test string"
)", "Test string");

TEST_PARSE(String, 1, {
    ParseResult r;
    EXPECT_NO_THROW(r = parseAst(R"(
"Test
string"
)"););
    ASSERT_EQ(r.ast->root()->loc, location(position(nullptr, 2, 1), position(nullptr, 3, 6)));
});

