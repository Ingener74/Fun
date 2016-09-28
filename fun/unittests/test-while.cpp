#include "test.h"

using namespace std;
using namespace fun;

PARSE_ERR(While, 1, R"(
while
)", ParserError);

PARSE_ERR(While, 2, R"(
while
end
)", ParserError);

PARSE_ERR(While, 3, R"(
while nil
end
)", ParserError);

PARSE_ERR(While, 4, R"(
while:
end
)", ParserError);

PARSE_ERR(While, 5, R"(
while:end
)", ParserError);

PARSE(While, 6, R"(
while nil:
end
)");

PARSE_ERR(While, 7, R"(
whilenil:end
)", ParserError);

PARSE_ERR(While, 8, R"(
while0:
end
)", ParserError);
