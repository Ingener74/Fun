#include "test.h"

using namespace std;
using namespace fun;

#define PARSE_FUN_VALID(n, str) PARSE_VALID2(Fun, n, str)
#define PARSE_FUN_INVALID(n, str, errCls) PARSE_INVALID(Fun, n, str, errCls)

PARSE_FUN_INVALID(0, R"(fun)", ParserError);

PARSE_FUN_INVALID(1, R"(fun end)", ParserError);

PARSE_FUN_INVALID(2, R"(
fun
end
)", ParserError);

PARSE_FUN_INVALID(3, R"(fun end)", ParserError);

PARSE_FUN_VALID(4, R"(fun()end)");

PARSE_FUN_VALID(5, R"(fun()
end)");

PARSE_FUN_VALID(6, R"(fun(a)
end)");

PARSE_FUN_INVALID(7, R"(fun(42)
end)", ParserError);

PARSE_FUN_INVALID(8, R"(fun(nil)
end)", ParserError);

