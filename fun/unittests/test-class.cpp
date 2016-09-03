#include "test.h"

using namespace std;
using namespace fun;

#define PARSE_CLASS_VALID(n, str) PARSE_VALID2(Class, n, str)
#define PARSE_CLASS_INVALID(n, str) PARSE_INVALID(Class, n, str)

PARSE_CLASS_VALID(0, R"(class Foo() end)");

