#include "test.h"

using namespace std;
using namespace Poco;
using namespace fun;
using namespace testing;

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

INTERPRET_ASSIGN(4, {
    auto r = interpret(R"(foo, bar = 42, 24)");

    ASSERT_EQ(Statement::counter(), 5);

    ASSERT_EQ(r.v->getOperands().size(), 0);
    ASSERT_EQ(r.v->getMemory()[0].size(), 2);

    auto foo_term = r.v->getMemory()[0]["foo"];
    auto bar_term = r.v->getMemory()[0]["bar"];

    auto foo = dynamic_cast<Integer*>(foo_term);
    auto bar = dynamic_cast<Integer*>(bar_term);

    ASSERT_NE(foo, nullptr);
    ASSERT_EQ(foo->value, 42);

    ASSERT_NE(bar, nullptr);
    ASSERT_EQ(bar->value, 24);
})

INTERPRET_ASSIGN(5, {
    auto r = interpret(R"(a, b, c = 1, 2)");

    ASSERT_EQ(Statement::counter(), 6);

    ASSERT_EQ(r.v->getOperands().size(), 0);
    ASSERT_EQ(r.v->getMemory()[0].size(), 3);

    auto a = dynamic_cast<Integer*>(r.v->getMemory()[0]["a"]);
    auto b = dynamic_cast<Integer*>(r.v->getMemory()[0]["b"]);
    auto c = dynamic_cast<Nil*>(r.v->getMemory()[0]["c"]);

    ASSERT_NE(a, nullptr);
    ASSERT_EQ(a->value, 1);

    ASSERT_NE(b, nullptr);
    ASSERT_EQ(b->value, 2);
})

INTERPRET_ASSIGN(6, {
    auto r = interpret(R"(a, b = 1, 2, 3)");

    ASSERT_EQ(Statement::counter(), 6);

    ASSERT_EQ(r.v->getOperands().size(), 0);
    ASSERT_EQ(r.v->getMemory()[0].size(), 2);

    auto a = dynamic_cast<Integer*>(r.v->getMemory()[0]["a"]);
    auto b = dynamic_cast<Integer*>(r.v->getMemory()[0]["b"]);

    ASSERT_NE(a, nullptr);
    ASSERT_EQ(a->value, 1);

    ASSERT_NE(b, nullptr);
    ASSERT_EQ(b->value, 2);
})

INTERPRET_ASSIGN(7, {
    auto r = interpretInteractive(R"(
a = 1

b = a

c = 0
)");

    r.d->setBreakpoint({"", 2});
    r.d->setBreakpoint({"", 4});

    bool stop = false;
    function<void()> f;
    Mutex mtx;
    Condition cond;

    EXPECT_CALL(*r.d.get(), onCatchBreakpoint(Breakpoint{"", 2})).
            WillOnce(InvokeWithoutArgs([&]{
                ScopedLock<Mutex> lock(mtx);
                f = [&]{
                    r.d->resume();
                };
                cond.signal();
            }));

    EXPECT_CALL(*r.d.get(), onCatchBreakpoint(Breakpoint{"", 4})).
            WillOnce(InvokeWithoutArgs([&]{
               ScopedLock<Mutex> lock(mtx);
               f = [&]{
                   stop = true;
                   r.d->resume();
               };
               cond.signal();
            }));

    Thread th;
    th.startFunc([&r]{
        r.ast->accept(r.v.get());
    });

    while(true){
        ScopedLock<Mutex> lock(mtx);
        while (!f) {
            cond.wait(mtx);
        }
        f();
        f = {};
        if (stop){
            break;
        }
    }

    th.join();

//    ASSERT_EQ(r.v->getOperands().size(), 0);
//    ASSERT_EQ(r.v->getMemory()[0].size(), 2);
//
//    auto a = dynamic_cast<Integer*>(r.v->getMemory()[0]["a"]);
//    auto b = dynamic_cast<Integer*>(r.v->getMemory()[0]["b"]);
//
//    ASSERT_NE(a, nullptr);
//    ASSERT_EQ(a->value, 1);
//
//    ASSERT_NE(b, nullptr);
//    ASSERT_EQ(b->value, 2);
})



