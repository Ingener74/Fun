#include "test.h"

using namespace std;
using namespace fun;

#define PARSE_BOOL_VALID(n, str, v) PARSE_VALID(Boolean, n, str, v)
#define PARSE_BOOL_INVALID(n, str, errCls) PARSE_INVALID(Boolean, n, str, errCls)

PARSE_BOOL_VALID(0, R"(true)", true);

PARSE_BOOL_VALID(1, R"(false)", false);

PARSE_BOOL_VALID(2, R"(True)", true);

PARSE_BOOL_VALID(3, R"(False)", false);

PARSE_BOOL_VALID(4, R"(TRUE)", true);

PARSE_BOOL_VALID(5, R"(FALSE)", false);

PARSE_BOOL_VALID(6, R"(fAlSe)", false);

PARSE_BOOL_VALID(7, R"(TrUe)", true);
