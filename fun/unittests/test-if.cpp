#include "MockDebugger.h"
#include "test.h"

using namespace std;
using namespace fun;

TEST(Interpret, If_999)
    {
        {
            Fun f;
            auto dbg = new MockDebugger;
            f.setDebugger(dbg);

            dbg->setBreakpoint(Breakpoint(4));
            EXPECT_CALL(*dbg, onCatchBreakpoint(Breakpoint(4))).
                WillOnce(testing::InvokeWithoutArgs([dbg]{
                    dbg->handleBreakpoint([](IOperands* operands, IMemory* memory) {
                        EXPECT_EQ(operands->getOperands().size(), 0);
                        EXPECT_EQ(memory->getMemory().at(0).size(), 1);
                    });
                }));

            dbg->setBreakpoint(Breakpoint(6));
            EXPECT_CALL(*dbg, onCatchBreakpoint(Breakpoint(6))).
                WillOnce(testing::InvokeWithoutArgs([dbg]{
                    dbg->handleBreakpoint([](IOperands* operands, IMemory* memory) {
                        EXPECT_EQ(operands->getOperands().size(), 0);
                        EXPECT_EQ(memory->getMemory().at(0).size(), 2);
                    });
                }));

            dbg->handleEnd([](IOperands* operands, IMemory* memory) {
                EXPECT_EQ(operands->getOperands().size(), 0);
                EXPECT_EQ(memory->getMemory().at(0).size(), 3);
            });

            ASSERT_NO_THROW(
                f.evalString(R"(
a = 1

b = 2

c = 3
)");
            );

        }
        ASSERT_EQ(Statement::counter(), 0);
    }

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
