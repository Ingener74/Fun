#include "test.h"

using namespace std;
using namespace fun;

PARSE_TERM(Real, 0, R"(0.0)", 0.0);

PARSE_TERM(Real, 1, R"(1.0)", 1.0);

PARSE_TERM(Real, 2, R"(.0)", .0);

PARSE_TERM(Real, 3, R"(10.)", 10.);

PARSE_TERM(Real, 4, R"(1.0e1)", 1.0e1);

PARSE_TERM(Real, 5, R"(1.0E1)", 1.0E1);

PARSE_TERM(Real, 6, R"(.1e-3)", .1e-3);

PARSE_TERM(Real, 7, R"(.13145E-12)", .13145E-12);

PARSE_TERM(Real, 8, R"(12.3E+12)", 12.3E+12);

PARSE_TERM(Real, 9, R"(1.e+3)", 1.e+3);

PARSE_ERR(Real, 10, R"(..13145E-12)", ParserError)

PARSE_ERR(Real, 11, R"(00.13145E-)", ParserError)

PARSE_ERR(Real, 12, R"(0.001e-)", ParserError)

PARSE_ERR(Real, 13, R"(0,1)", ParserError)

PARSE_ERR(Real, 14, R"(3,1415)", ParserError)

PARSE_TERM(Real, 15, R"(1.e+3)", 1.e+3)
