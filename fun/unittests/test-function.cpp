#include "test.h"

using namespace std;
using namespace fun;

#define TEST_PARSE(n, body) TEST(Parse, Function_##n) { body ASSERT_EQ(Statement::counter(), 0); }

TEST_PARSE(0, { EXPECT_THROW(parse(R"(fun)"), ParserError); })

TEST_PARSE(1, { EXPECT_THROW(parse(R"(fun end)"), ParserError); })

TEST_PARSE(2, { EXPECT_THROW(parse(R"(
fun
end
)"), ParserError); })

TEST_PARSE(3, { EXPECT_THROW(parse(R"(fun end)"), ParserError); })

TEST_PARSE(4, { EXPECT_NO_THROW(parse(R"(fun()end)")); })

TEST_PARSE(5, { EXPECT_NO_THROW(parse(R"(fun()
end)")); })

TEST_PARSE(6, { EXPECT_NO_THROW(parse(R"(fun(a)
end)")); })

TEST_PARSE(7, { EXPECT_THROW(parse(R"(fun(42)
end)"), ParserError); })

TEST_PARSE(8, { EXPECT_THROW(parse(R"(fun(nil)
end)"), ParserError); })

