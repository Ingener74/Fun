#include "test.h"

using namespace std;
using namespace fun;

#define PARSE_IF_VALID(n, str) PARSE_VALID2(If, n, str)
#define PARSE_IF_INVALID(n, str, errCls) PARSE_INVALID(If, n, str, errCls)

PARSE_IF_INVALID(0, R"(
if
)", ParserError);

PARSE_IF_INVALID(1, R"(
if
end
)", ParserError);

PARSE_IF_INVALID(2, R"(
if nil
end
)", ParserError);

PARSE_IF_INVALID(3, R"(
if:
end
)", ParserError);

PARSE_IF_VALID(4, R"(
if nil:
end
)");

PARSE_IF_INVALID(5, R"(
if 0:
if 1:
end
)", ParserError);

PARSE_IF_VALID(6, R"(
if 0:
elif 1:
end
)");

PARSE_IF_VALID(7, R"(
if 0:
elif 1:
else
end
)");

PARSE_IF_INVALID(8, R"(
if 0:
    ""
elif 1:
    5
else
    4
else
    2
end
)", ParserError);
