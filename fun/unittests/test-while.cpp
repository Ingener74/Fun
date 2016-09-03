#include "test.h"

using namespace std;
using namespace fun;

#define PARSE_WHILE_VALID(n, str) PARSE_VALID2(While, n, str)
#define PARSE_WHILE_INVALID(n, str, errCls) PARSE_INVALID(While, n, str, errCls)

PARSE_WHILE_INVALID(1, R"(
while
)", ParserError);

PARSE_WHILE_INVALID(2, R"(
while
end
)", ParserError);

PARSE_WHILE_INVALID(3, R"(
while nil
end
)", ParserError);

PARSE_WHILE_INVALID(4, R"(
while:
end
)", ParserError);

PARSE_WHILE_INVALID(5, R"(
while:end
)", ParserError);

PARSE_WHILE_VALID(6, R"(
while nil:
end
)");

PARSE_WHILE_INVALID(7, R"(
whilenil:end
)", ParserError);

PARSE_WHILE_INVALID(8, R"(
while0:
end
)", ParserError);
