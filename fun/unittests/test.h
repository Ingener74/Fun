#pragma once

#include <memory>
#include <list>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <gmock/gmock-actions.h>

#include <Poco/Thread.h>

#include <fun.h>

void parse(const std::string& source, bool parser_debug = false);

struct ParseResult {
    std::unique_ptr<fun::Ast> ast;
};

ParseResult parseAst(const std::string& source);

class DebuggerMock: public fun::Debugger {
public:
    MOCK_METHOD1(onCatchBreakpoint, void(const fun::Breakpoint &));
    MOCK_METHOD1(onOperandsChanged, void(const std::vector<fun::Terminal*> &));
    MOCK_METHOD1(onMemoryChanged, void(const std::unordered_map<std::string, fun::Terminal*>&));
    MOCK_METHOD0(onProgramEnded, void());
};

struct Result {
    std::unique_ptr<fun::Interpreter> v;
    std::unique_ptr<DebuggerMock> d;
    std::unique_ptr<fun::Ast> ast;
};

Result interpret(const std::string& source);
Result interpretInteractive(const std::string& source);

#define TEST_PARSE(klass, n, body) TEST(Parse,     klass##_##n) { body ASSERT_EQ(Statement::counter(), 0); }
#define TEST_INTERPRET(klass, n, body) TEST(Interpret, klass##_##n) { body ASSERT_EQ(Statement::counter(), 0); }

#define PARSE_VALID(klass, n, str, v) TEST_PARSE(klass, n, { \
    ParseResult r; \
    EXPECT_NO_THROW(r = parseAst(str);); \
    auto instance = dynamic_cast<klass*>(r.ast->root()); \
    ASSERT_NE(instance, nullptr); \
    ASSERT_EQ(instance->value, v); \
})

#define PARSE_VALID2(klass, n, str) TEST_PARSE(klass, n, { EXPECT_NO_THROW(parse(str)); })
#define PARSE_INVALID(klass, n, str, errorClass) TEST_PARSE(klass, n, { EXPECT_THROW(parse(str), errorClass); })

class ConditionUnlocker {
public:
    ConditionUnlocker(Poco::Condition& cond) :
            cond(cond) {
    }
    virtual ~ConditionUnlocker() {
        cond.signal();
    }
private:
    ConditionUnlocker(const ConditionUnlocker&) = delete;
    ConditionUnlocker& operator=(const ConditionUnlocker&) = delete;
    Poco::Condition& cond;
};

#define DEBUGGING(script, body, end)                              \
    auto r = interpretInteractive(script);                        \
    bool stop = false;                                            \
    function<void()> f;                                           \
    Mutex mtx;                                                    \
    Condition cond;                                               \
    body                                                          \
    EXPECT_CALL(*r.d.get(), onProgramEnded()).                    \
        WillOnce(InvokeWithoutArgs([&]{                           \
           ScopedLock<Mutex> lock(mtx);                           \
           f = [&]{ stop = true; r.d->resume(); };                \
           ConditionUnlocker unlocker(cond);                      \
           end                                                    \
        }));                                                      \
    Thread th;                                                    \
    th.startFunc([&r]{                                            \
        r.ast->accept(r.v.get());                                 \
    });                                                           \
    while(true){                                                  \
        ScopedLock<Mutex> lock(mtx);                              \
        while (!f) cond.wait(mtx);                                \
        f();                                                      \
        f = {};                                                   \
        if (stop) { break; }                                      \
    }                                                             \
    if(th.isRunning())                                            \
        th.join();

#define EVALUATE(script, end) DEBUGGING(script,,end)

#define BREAKPOINT(line, body)                                    \
r.d->setBreakpoint({"", line});                                   \
EXPECT_CALL(*r.d.get(), onCatchBreakpoint(Breakpoint{"", line})). \
    WillOnce(InvokeWithoutArgs([&]{                               \
        ScopedLock<Mutex> lock(mtx);                              \
        f = [&]{ r.d->resume(); };                                \
        ConditionUnlocker unlocker(cond);                         \
        body                                                      \
    }));

