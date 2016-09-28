#include "test.h"

using namespace std;
using namespace fun;

PARSE_ERR(If, 0, R"(
if
)", ParserError);

PARSE_ERR(If, 1, R"(
if
end
)", ParserError);

PARSE_ERR(If, 2, R"(
if nil
end
)", ParserError);

PARSE_ERR(If, 3, R"(
if:
end
)", ParserError);

PARSE(If, 4, R"(
if nil:
end
)");

PARSE_ERR(If, 5, R"(
if 0:
if 1:
end
)", ParserError);

PARSE(If, 6, R"(
if 0:
elif 1:
end
)");

PARSE(If, 7, R"(
if 0:
elif 1:
else
end
)");

PARSE_ERR(If, 8, R"(
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
