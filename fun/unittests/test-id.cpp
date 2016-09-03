#include "test.h"

using namespace std;
using namespace fun;

#define PARSE_ID_VALID(n, str, v) PARSE_VALID(Id, n, str, v)
#define PARSE_ID_INVALID(n, str, errCls) PARSE_INVALID(Id, n, str, errCls)

PARSE_ID_VALID(0, R"(_)", "_");

PARSE_ID_VALID(1, R"(__)", "__");

PARSE_ID_VALID(2, R"(___)", "___");

PARSE_ID_VALID(3, R"(_1)", "_1");

PARSE_ID_VALID(4, R"(_Test)", "_Test");

PARSE_ID_VALID(5, R"(_123abc)", "_123abc");

PARSE_ID_VALID(6, R"(Test)", "Test");

PARSE_ID_VALID(7, R"(ABC)", "ABC");

PARSE_ID_VALID(8, R"(
aBC_TEst_very_long_id123
)", "aBC_TEst_very_long_id123");

PARSE_ID_INVALID(9, R"(
1aBc
)", LexerError);

PARSE_ID_INVALID(10, R"(
123aBc
)", LexerError);

