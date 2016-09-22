#include "test.h"

using namespace std;
using namespace Poco;
using namespace fun;
using namespace testing;

#define PARSE_ASSIGN_VALID(n, str) PARSE_VALID2(Assign, n, str)
#define PARSE_ASSIGN_INVALID(n, str, errCls) PARSE_INVALID(Assign, n, str, errCls)

#define INTERPRET_ASSIGN(n, body) TEST_INTERPRET(Assign, n, body)

#define CHECK_INTEGER(name, val) \
    auto name = dynamic_cast<Integer*>(r.v->getMemory()[0][#name]); \
    ASSERT_NE(name, nullptr); \
    ASSERT_EQ(name->value, val);


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

    CHECK_INTEGER(foo, 42)
})

INTERPRET_ASSIGN(4, {
    auto r = interpret(R"(foo, bar = 42, 24)");

    ASSERT_EQ(Statement::counter(), 5);

    ASSERT_EQ(r.v->getOperands().size(), 0);
    ASSERT_EQ(r.v->getMemory()[0].size(), 2);

    CHECK_INTEGER(foo, 42)
    CHECK_INTEGER(bar, 24)
})

INTERPRET_ASSIGN(5, {
    auto r = interpret(R"(a, b, c = 1, 2)");

    ASSERT_EQ(Statement::counter(), 6);

    ASSERT_EQ(r.v->getOperands().size(), 0);
    ASSERT_EQ(r.v->getMemory()[0].size(), 3);

    CHECK_INTEGER(a, 1);
    CHECK_INTEGER(b, 2);

    auto c = dynamic_cast<Nil*>(r.v->getMemory()[0]["c"]);
})

INTERPRET_ASSIGN(6, {
    auto r = interpret(R"(a, b = 1, 2, 3)");

    ASSERT_EQ(Statement::counter(), 6);

    ASSERT_EQ(r.v->getOperands().size(), 0);
    ASSERT_EQ(r.v->getMemory()[0].size(), 2);

    CHECK_INTEGER(a, 1);
    CHECK_INTEGER(b, 2);
})

#define DEBUG_INTERACTIVE(body)                 \
    bool stop = false;                          \
    function<void()> f;                         \
    Mutex mtx;                                  \
    Condition cond;                             \
    body                                        \
    EXPECT_CALL(*r.d.get(), onProgramEnded()).  \
        WillOnce(InvokeWithoutArgs([&]{         \
           ScopedLock<Mutex> lock(mtx);         \
           f = [&]{                             \
               stop = true;                     \
               r.d->resume();                   \
           };                                   \
           cond.signal();                       \
        }));                                    \
    Thread th;                                  \
    th.startFunc([&r]{                          \
        r.ast->accept(r.v.get());               \
    });                                         \
    while(true){                                \
        ScopedLock<Mutex> lock(mtx);            \
        while (!f) cond.wait(mtx);              \
        f();                                    \
        f = {};                                 \
        if (stop) break;                        \
    }                                           \
    if(th.isRunning())                          \
        th.join();

#define BREAKPOINT(line, body)                                \
r.d->setBreakpoint({"", line});                                \
EXPECT_CALL(*r.d.get(), onCatchBreakpoint(Breakpoint{"", line})). \
        WillOnce(InvokeWithoutArgs([&]{                           \
            ScopedLock<Mutex> lock(mtx);                          \
            body                                                  \
            f = [&]{                                              \
                r.d->resume();                                    \
            };                                                    \
            cond.signal();                                        \
        }));


INTERPRET_ASSIGN(7, {
    auto r = interpretInteractive(R"(
a = 1

b = a

c = 0
)");

    DEBUG_INTERACTIVE({
        BREAKPOINT(4, {
            ASSERT_EQ(r.v->getOperands().size(), 0);
            ASSERT_EQ(r.v->getMemory()[0].size(), 1);

            CHECK_INTEGER(a, 1);
        })
        BREAKPOINT(6, {
           ASSERT_EQ(r.v->getOperands().size(), 0);
           ASSERT_EQ(r.v->getMemory()[0].size(), 2);

           CHECK_INTEGER(a, 1);
           CHECK_INTEGER(b, 1);
        })
    })

//    bool stop = false;
//    function<void()> f;
//    Mutex mtx;
//    Condition cond;
//
//    r.d->setBreakpoint({"", 4});
//    EXPECT_CALL(*r.d.get(), onCatchBreakpoint(Breakpoint{"", 4})).
//            WillOnce(InvokeWithoutArgs([&]{
//                ScopedLock<Mutex> lock(mtx);
//
//                ASSERT_EQ(r.v->getOperands().size(), 0);
//                ASSERT_EQ(r.v->getMemory()[0].size(), 1);
//
//                CHECK_INTEGER(a, 1);
//
//                f = [&]{
//                    r.d->resume();
//                };
//                cond.signal();
//            }));
//
//    r.d->setBreakpoint({"", 6});
//    EXPECT_CALL(*r.d.get(), onCatchBreakpoint(Breakpoint{"", 6})).
//            WillOnce(InvokeWithoutArgs([&]{
//               ScopedLock<Mutex> lock(mtx);
//
//               ASSERT_EQ(r.v->getOperands().size(), 0);
//               ASSERT_EQ(r.v->getMemory()[0].size(), 2);
//
//               CHECK_INTEGER(a, 1);
//               CHECK_INTEGER(b, 1);
//
//               f = [&]{
//                   r.d->resume();
//               };
//               cond.signal();
//            }));
//
//    EXPECT_CALL(*r.d.get(), onProgramEnded()).
//            WillOnce(InvokeWithoutArgs([&]{
//               ScopedLock<Mutex> lock(mtx);
//               f = [&]{
//                   stop = true;
//                   r.d->resume();
//               };
//               cond.signal();
//            }));
//
//    Thread th;
//    th.startFunc([&r]{
//        r.ast->accept(r.v.get());
//    });
//
//    while(true){
//        ScopedLock<Mutex> lock(mtx);
//        while (!f) {
//            cond.wait(mtx);
//        }
//        f();
//        f = {};
//        if (stop){
//            break;
//        }
//    }
//    if(th.isRunning())
//        th.join();
})



