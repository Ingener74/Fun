#include "test.h"

using namespace std;
using namespace fun;

PARSE(Dict, 0, R"({})");

PARSE(Dict, 1, R"({a=1})");

PARSE(Dict, 2, R"({a=1 b=nil})");

PARSE(Dict, 3, R"({a=1 b=nil f="test"})");

PARSE(Dict, 4, R"({a=1 b=nil f="test" c=false})");

PARSE(Dict, 5, R"({a=1 b=nil f="test" c=false d=true})");

PARSE(Dict, 6, R"({a=1 b=nil f="test" c=false d=true e=2.72})");

PARSE(Dict, 7, R"(
{
  a=1
  b=nil
  f="test"
  c=false
  d=true
  e=2.72
  g=fun()end
})");

