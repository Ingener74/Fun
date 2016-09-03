#include "test.h"

using namespace std;
using namespace fun;

#define PARSE_DICT_VALID(n, str) PARSE_VALID2(Dict, n, str)
#define PARSE_DICT_INVALID(n, str) PARSE_INVALID(Dict, n, str)

PARSE_DICT_VALID(0, R"({})");

PARSE_DICT_VALID(1, R"({a=1})");

PARSE_DICT_VALID(2, R"({a=1 b=nil})");

PARSE_DICT_VALID(3, R"({a=1 b=nil f="test"})");

PARSE_DICT_VALID(4, R"({a=1 b=nil f="test" c=false})");

PARSE_DICT_VALID(5, R"({a=1 b=nil f="test" c=false d=true})");

PARSE_DICT_VALID(6, R"({a=1 b=nil f="test" c=false d=true e=2.72})");

PARSE_DICT_VALID(7, R"(
{
  a=1
  b=nil
  f="test"
  c=false
  d=true
  e=2.72
  g=fun()end
})");

