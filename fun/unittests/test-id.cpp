#include "test.h"

using namespace std;
using namespace fun;

PARSE_TERM(Id, 0, R"(_)", "_");

PARSE_TERM(Id, 1, R"(__)", "__");

PARSE_TERM(Id, 2, R"(___)", "___");

PARSE_TERM(Id, 3, R"(_1)", "_1");

PARSE_TERM(Id, 4, R"(_Test)", "_Test");

PARSE_TERM(Id, 5, R"(_123abc)", "_123abc");

PARSE_TERM(Id, 6, R"(Test)", "Test");

PARSE_TERM(Id, 7, R"(ABC)", "ABC");

PARSE_TERM(Id, 8, R"(aBC_TEst_very_long_id123)", "aBC_TEst_very_long_id123");

PARSE_ERR(Id, 9, R"(1aBc)", LexerError);

PARSE_ERR(Id, 10, R"(123aBc)", LexerError);

PARSE_ERR(Id, 11, R"(123aBc)", LexerError);

