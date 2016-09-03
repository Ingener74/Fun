#include "test.h"

using namespace std;
using namespace fun;

#define PARSE_ASSIGN_VALID(n, str) PARSE_VALID2(Assign, n, str)
#define PARSE_ASSIGN_INVALID(n, str, errCls) PARSE_INVALID(Assign, n, str, errCls)

#define INTERPRET_ASSIGN(n, body) TEST_INTERPRET(Assign, n, body)

PARSE_ASSIGN_INVALID(0, R"(
foo = 
)", ParserError);

PARSE_ASSIGN_VALID(1, R"(
foo = 42)");

PARSE_ASSIGN_VALID(2, R"(
foo = 42)");

INTERPRET_ASSIGN(3, {
    auto r = interpret(R"(foo = 42)");

    ASSERT_EQ(Statement::counter(), 3);

    ASSERT_EQ(r.v->getOperands().size(), 0);
    ASSERT_EQ(r.v->getMemory()[0].size(), 1);

    auto var = r.v->getMemory()[0]["foo"];

    auto integer = dynamic_cast<Integer*>(var);

    ASSERT_NE(integer, nullptr);
    ASSERT_EQ(integer->value, 42);
})

