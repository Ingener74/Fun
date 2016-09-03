#include "test.h"

using namespace std;
using namespace fun;

#define PARSE_BINARYOP_VALID(n, str) PARSE_VALID2(BinaryOp, n, str)
#define PARSE_BINARYOP_INVALID(n, str, errCls) PARSE_INVALID(BinaryOp, n, str, errCls)

PARSE_BINARYOP_INVALID(0, R"(42 + )", ParserError);

