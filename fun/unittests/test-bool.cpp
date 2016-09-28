#include "test.h"

using namespace std;
using namespace fun;

PARSE_TERM(Boolean, 0, R"(true)", true);

PARSE_TERM(Boolean, 1, R"(false)", false);

PARSE_TERM(Boolean, 2, R"(True)", true);

PARSE_TERM(Boolean, 3, R"(False)", false);

PARSE_TERM(Boolean, 4, R"(TRUE)", true);

PARSE_TERM(Boolean, 5, R"(FALSE)", false);

PARSE_TERM(Boolean, 6, R"(fAlSe)", false);

PARSE_TERM(Boolean, 7, R"(TrUe)", true);
