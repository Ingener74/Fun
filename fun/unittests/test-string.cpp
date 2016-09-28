#include "test.h"

using namespace std;
using namespace fun;

PARSE_TERM(String, 0, R"(
"Test string"
)", "Test string");

//PARSE(String, 1, {
//    ParseResult r;
//    EXPECT_NO_THROW(r = parseAst(R"(
//"Test
//string"
//)"););
//    ASSERT_EQ(r.ast->root()->loc, location(position(nullptr, 2, 1), position(nullptr, 3, 6)));
//});

