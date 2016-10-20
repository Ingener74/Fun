#include "test.h"

using namespace std;
using namespace fun;

TEST(Interpret, If_999)
    {
        {
            Fun f;
            f.setDebugger(Fun::DebuggerType::TestingMockDebugger);

            // BODY

            auto mockDbg = f.getConcreteDebugger<MockDebugger>();

            mockDbg->setBreakpoint(Breakpoint(4));

            EXPECT_CALL(mockDbg.get(), onCatchBreakpoint(Breakpoint(4))).
                WillOnce(testing::InvokeWithoutArgs([&]{
                    Poco::ScopedLock<Poco::Mutex> lock(mtx);
                    f = [&]{ r.d->resume(); };
                    ConditionUnlocker unlocker(cond);
                    // body

                    mockDbg->onBreakpoint([&]{

                    });

                }));

            f.evalString(R"(
a = 1

b = 2

c = 3
)");

//            Poco::Thread th;
//            th.startFunc([&]{
//                EXPECT_NO_THROW(r.pot->accept(r.v.get()));
//                Poco::ScopedLock<Poco::Mutex> lock(mtx);
//                f = [&]{ stop = true; r.d->resume(); };
//                ConditionUnlocker unlocker(cond);
//
////                END
//
//            });
//            while(true){
//                Poco::ScopedLock<Poco::Mutex> lock(mtx);
//                while (!f) cond.wait(mtx);
//                f();
//                f = {};
//                if (stop) { break; }
//            }
//            if(th.isRunning())
//                th.join();
        }
        ASSERT_EQ(Statement::counter(), 0);
    }

PARSE_ERR(If, 0, R"(
if
)", ParserError);

PARSE_ERR(If, 1, R"(
if
end
)", ParserError);

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
