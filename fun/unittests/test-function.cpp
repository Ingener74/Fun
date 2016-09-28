#include "test.h"

using namespace std;
using namespace fun;

PARSE_ERR(Function, 0, R"(fun)", ParserError);

PARSE_ERR(Function, 1, R"(fun end)", ParserError);

PARSE_ERR(Function, 2, R"(
fun
end
)", ParserError);

PARSE_ERR(Function, 3, R"(fun end)", ParserError);

PARSE(Function, 4, R"(fun()end)");

PARSE(Function, 5, R"(fun()
end)");

PARSE(Function, 6, R"(fun(a)
end)");

PARSE_ERR(Function, 7, R"(fun(42)
end)", ParserError);

PARSE_ERR(Function, 8, R"(fun(nil)
end)", ParserError);

