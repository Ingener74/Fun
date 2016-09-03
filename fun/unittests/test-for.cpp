#include "test.h"

using namespace std;
using namespace fun;

#define PARSE_FOR_VALID(n, str) PARSE_VALID2(For, n, str)
#define PARSE_FOR_INVALID(n, str, errCls) PARSE_INVALID(For, n, str, errCls)

PARSE_FOR_INVALID(1, R"(
for
)", ParserError);

PARSE_FOR_INVALID(2, R"(
for
end
)", ParserError);

PARSE_FOR_INVALID(3, R"(
for ;;:
end
)", ParserError);

PARSE_FOR_INVALID(4, R"(
for end
)", ParserError);

PARSE_FOR_VALID(5, R"(
for 0; 1; 2: end
)");
