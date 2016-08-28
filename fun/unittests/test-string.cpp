#include "test.h"

using namespace std;
using namespace fun;

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

