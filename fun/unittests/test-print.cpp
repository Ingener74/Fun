#include "test.h"

using namespace std;
using namespace fun;

PARSE(Print, 0, R"(
print 42
print 3.14
print "foo"
print nil
print false
print true
)")

PARSE_ERR(Print, 1, R"(
print 
)", ParserError)

//Parse, Print_2) {
//    {
//        ParseResult r;
//        EXPECT_NO_THROW(r = parseAst(R"(
//print 42
//)"););
//
//        auto print = dynamic_cast<Print*>(r.ast->root());
//
//        ASSERT_NE(print, nullptr);
//
//        ASSERT_EQ(print->loc, location(position(nullptr, 2, 0), position(nullptr, 2, 8)));
//    }
//    ASSERT_EQ(Statement::counter(), 0);
//}
//
