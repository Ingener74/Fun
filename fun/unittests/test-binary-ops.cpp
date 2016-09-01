#include "test.h"

using namespace std;
using namespace fun;

#define TEST_PARSE(n, body) TEST(Parse, BinaryOps_##n) { body ASSERT_EQ(Statement::counter(), 0); }

TEST_PARSE(0, { EXPECT_THROW(parse(R"(42 + )"), ParserError); })

