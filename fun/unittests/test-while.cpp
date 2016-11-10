#include "test.h"

using namespace std;
using namespace fun;

#define CHECK_INTEGER(level, name, val)                           \
    { auto name = memory->variable(level, #name).cast<Integer>(); \
    ASSERT_FALSE(name.isNull());                                  \
    EXPECT_EQ(name->value, val); }

PARSE_ERR(While, 1, R"(
while
)", ParserError);

PARSE_ERR(While, 2, R"(
while
end
)", ParserError);

PARSE_ERR(While, 3, R"(
while nil
end
)", ParserError);

PARSE_ERR(While, 4, R"(
while:
end
)", ParserError);

PARSE_ERR(While, 5, R"(
while:end
)", ParserError);

PARSE(While, 6, R"(
while nil:
end
)");

PARSE_ERR(While, 7, R"(
whilenil:end
)", ParserError);

PARSE_ERR(While, 8, R"(
while0:
end
)", ParserError);

EVAL(While, 9, R"(
a = 0
while a < 3:
	a += 1
	nil
end
)", {
		int i = 0;

		BREAKPOINT_LINE_REPEAT(5, 3,
			if(i == 0){
				EXPECT_EQ(memory->levelCount(), 2);
				EXPECT_EQ(memory->count(0), 1);
				EXPECT_EQ(memory->count(1), 0);
				
				CHECK_INTEGER(0, a, 1)
				i++;
			}
			if(i == 1){
				EXPECT_EQ(memory->levelCount(), 2);
				EXPECT_EQ(memory->count(0), 1);
				EXPECT_EQ(memory->count(1), 0);
				
				CHECK_INTEGER(0, a, 2)
				i++;
			}
			if(i == 2){
				EXPECT_EQ(memory->levelCount(), 2);
				EXPECT_EQ(memory->count(0), 1);
				EXPECT_EQ(memory->count(1), 0);
				
				CHECK_INTEGER(0, a, 3)
				i++;
			}
		)
	}
	,
	EXPECT_EQ(memory->levelCount(), 1);
	EXPECT_EQ(memory->count(0), 1);
	
	CHECK_INTEGER(0, a, 3)
)

