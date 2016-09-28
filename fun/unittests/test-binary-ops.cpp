#include "test.h"

using namespace std;
using namespace fun;

PARSE_ERR(BinaryOp, 0, R"(42 + )", ParserError);

