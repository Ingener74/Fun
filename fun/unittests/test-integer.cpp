#include "test.h"

using namespace std;
using namespace fun;

#define PARSE_INTEGER_VALID(n, str, v) PARSE_VALID(Integer, n, str, v)
#define PARSE_INTEGER_INVALID(n, str, errCls) PARSE_INVALID(Integer, n, str, errCls)

#define INTERPRET_INTEGER(n, body) TEST_INTERPRET(Integer, n, body)

PARSE_INTEGER_VALID(0, R"(42)", 42);

PARSE_INTEGER_VALID(1, R"(1000000000)", 1000000000);

PARSE_INTEGER_VALID(2, R"(0)", 0);

PARSE_INTEGER_VALID(3, R"(100)", 100);
