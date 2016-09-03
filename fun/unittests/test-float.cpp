#include "test.h"

using namespace std;
using namespace fun;

#define PARSE_FLOAT_VALID(n, str, v) PARSE_VALID(Real, n, str, v)
#define PARSE_FLOAT_INVALID(n, str, errCls) PARSE_INVALID(Real, n, str, errCls)

PARSE_FLOAT_VALID(0, R"(0.0)", 0.0);

PARSE_FLOAT_VALID(1, R"(1.0)", 1.0);

PARSE_FLOAT_VALID(2, R"(.0)", .0);

PARSE_FLOAT_VALID(3, R"(10.)", 10.);

PARSE_FLOAT_VALID(4, R"(1.0e1)", 1.0e1);

PARSE_FLOAT_VALID(5, R"(1.0E1)", 1.0E1);

PARSE_FLOAT_VALID(6, R"(.1e-3)", .1e-3);

PARSE_FLOAT_VALID(7, R"(.13145E-12)", .13145E-12);

PARSE_FLOAT_VALID(8, R"(12.3E+12)", 12.3E+12);

PARSE_FLOAT_VALID(9, R"(1.e+3)", 1.e+3);

PARSE_FLOAT_INVALID(10, R"(..13145E-12)", ParserError)

PARSE_FLOAT_INVALID(11, R"(00.13145E-)", ParserError)

PARSE_FLOAT_INVALID(12, R"(0.001e-)", ParserError)

PARSE_FLOAT_INVALID(13, R"(0,1)", ParserError)

PARSE_FLOAT_INVALID(14, R"(3,1415)", ParserError)
