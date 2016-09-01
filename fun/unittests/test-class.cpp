#include "test.h"

using namespace std;
using namespace fun;

#define TEST_PARSE(n, body) TEST(Parse, Class_##n) { body ASSERT_EQ(Statement::counter(), 0); }

TEST_PARSE(0, { ASSERT_TRUE(parse(R"(class Foo() end)")); })

