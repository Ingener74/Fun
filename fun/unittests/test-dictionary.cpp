#include "test.h"

using namespace std;
using namespace fun;

#define TEST_PARSE(n, body) TEST(Parse, Dict_##n) { body ASSERT_EQ(Statement::counter(), 0); }

TEST_PARSE(0, { EXPECT_NO_THROW(parse(R"({})")); })

TEST_PARSE(1, { EXPECT_NO_THROW(parse(R"({a=1})")); })

TEST_PARSE(2, { EXPECT_NO_THROW(parse(R"({a=1 b=nil})")); })

TEST_PARSE(3, { EXPECT_NO_THROW(parse(R"({a=1 b=nil f="test"})")); })

TEST_PARSE(4, { EXPECT_NO_THROW(parse(R"({a=1 b=nil f="test" c=false})")); })

TEST_PARSE(5, { EXPECT_NO_THROW(parse(R"({a=1 b=nil f="test" c=false d=true})")); })

TEST_PARSE(6, { EXPECT_NO_THROW(parse(R"({a=1 b=nil f="test" c=false d=true e=2.72})")); })

TEST_PARSE(7, { EXPECT_NO_THROW(parse(R"(
{
  a=1
  b=nil
  f="test"
  c=false
  d=true
  e=2.72
  g=fun()end
})")); })

