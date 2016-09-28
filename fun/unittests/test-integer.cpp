#include "test.h"

using namespace std;
using namespace fun;

PARSE_TERM(Integer, 0, R"(42)", 42);

PARSE_TERM(Integer, 1, R"(1000000000)", 1000000000);

PARSE_TERM(Integer, 2, R"(0)", 0);

PARSE_TERM(Integer, 3, R"(100)", 100);
