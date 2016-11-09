#include "test.h"

using namespace std;
using namespace fun;

#define CHECK_INTEGER(level, name, val)                           \
    { auto name = memory->variable(level, #name).cast<Integer>(); \
    ASSERT_FALSE(name.isNull());                                  \
    EXPECT_EQ(name->value, val); }

PARSE_ERR(If, 0, R"(
if
)", ParserError)

PARSE_ERR(If, 1, R"(
if
end
)", ParserError)

PARSE_ERR(If, 2, R"(
if nil
end
)", ParserError);

PARSE_ERR(If, 3, R"(
if:
end
)", ParserError);

PARSE(If, 4, R"(
if nil:
end
)");

PARSE_ERR(If, 5, R"(
if 0:
if 1:
end
)", ParserError);

PARSE(If, 6, R"(
if 0:
elif 1:
end
)");

PARSE(If, 7, R"(
if 0:
elif 1:
else
end
)");

PARSE_ERR(If, 8, R"(
if 0:
    ""
elif 1:
    5
else
    4
else
    2
end
)", ParserError);

EVAL(If, 9, R"(
a = 1
if true:
	a = 2
	nil
end
)",
	BREAKPOINT_LINE(5,
        EXPECT_EQ(memory->levelCount(), 2);
		EXPECT_EQ(memory->count(0), 1);
		EXPECT_EQ(memory->count(1), 1);

		CHECK_INTEGER(0, a, 1)
		CHECK_INTEGER(1, a, 2)
	)
	,
	EXPECT_EQ(memory->levelCount(), 1);
	EXPECT_EQ(memory->count(0), 1);
	CHECK_INTEGER(0, a, 1)
)

EVAL(If, 10, R"(
a = 1
if false:
	a = 2
	nil
else
	a = 3
	nil
end
)",
	BREAKPOINT_LINE(7,
        EXPECT_EQ(memory->levelCount(), 2);
		EXPECT_EQ(memory->count(0), 1);
		EXPECT_EQ(memory->count(1), 1);
		
		CHECK_INTEGER(0, a, 1)
		CHECK_INTEGER(1, a, 3)
	)
	,
	EXPECT_EQ(memory->levelCount(), 1);
	EXPECT_EQ(memory->count(0), 1);
	CHECK_INTEGER(0, a, 1)
)

