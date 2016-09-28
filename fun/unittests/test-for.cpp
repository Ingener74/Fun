#include "test.h"

using namespace std;
using namespace fun;

PARSE_ERR(For, 1, R"(
for
)", ParserError);

PARSE_ERR(For, 2, R"(
for
end
)", ParserError);

PARSE_ERR(For, 3, R"(
for ;;:
end
)", ParserError);

PARSE_ERR(For, 4, R"(
for end
)", ParserError);

PARSE(For, 5, R"(
for 0; 1; 2: end
)");
