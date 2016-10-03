#pragma once

#include <memory>
#include <list>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <gmock/gmock-actions.h>

#include <Poco/Thread.h>

#include <fun.h>

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

Result parse(const std::string& source);

#define PARSE(CLASS, N, SCRIPT)                                        \
    TEST(Parse, CLASS##_##N)                                           \
    {                                                                  \
        {                                                              \
            Result r;                                                  \
            EXPECT_NO_THROW(r = parse(SCRIPT););                       \
        }                                                              \
        ASSERT_EQ(Statement::counter(), 0);                            \
    }

#define PARSE_ERR(CLASS, N, SCRIPT, ERROR_CLASS)                       \
    TEST(Parse, CLASS##_##N)                                           \
    {                                                                  \
        {                                                              \
            Result r;                                                  \
            EXPECT_THROW(r = parse(SCRIPT), ERROR_CLASS);              \
        }                                                              \
        ASSERT_EQ(Statement::counter(), 0);                            \
    }

#define PARSE_TERM(CLASS, N, SCRIPT, VALUE)                            \
    TEST(Parse, CLASS##_##N)                                           \
    {                                                                  \
        {                                                              \
            Result r;                                                  \
            EXPECT_NO_THROW(r = parse(SCRIPT););                       \
            auto instance = dynamic_cast<CLASS*>(r.ast->root());       \
            ASSERT_NE(instance, nullptr);                              \
            ASSERT_EQ(instance->value, VALUE);                         \
        }                                                              \
        ASSERT_EQ(Statement::counter(), 0);                            \
    }

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

#define EVAL(CLASS, N, SCRIPT, BODY, END) TEST(Interpret, CLASS##_##N) \
    {                                                                  \
        {                                                              \
            auto r = parse(SCRIPT);                                    \
            bool stop = false;                                         \
            function<void()> f;                                        \
            Mutex mtx;                                                 \
            Condition cond;                                            \
            BODY                                                       \
            EXPECT_CALL(*r.d.get(), onProgramEnded()).                 \
                WillOnce(InvokeWithoutArgs([&]{                        \
                   ScopedLock<Mutex> lock(mtx);                        \
                   f = [&]{ stop = true; r.d->resume(); };             \
                   ConditionUnlocker unlocker(cond);                   \
                   END                                                 \
                }));                                                   \
            Thread th;                                                 \
            th.startFunc([&]{                                          \
                EXPECT_NO_THROW(r.ast->accept(r.v.get()));             \
            });                                                        \
            while(true){                                               \
                ScopedLock<Mutex> lock(mtx);                           \
                while (!f) cond.wait(mtx);                             \
                f();                                                   \
                f = {};                                                \
                if (stop) { break; }                                   \
            }                                                          \
            if(th.isRunning())                                         \
                th.join();                                             \
        }                                                              \
        ASSERT_EQ(Statement::counter(), 0);                            \
    }

#define EVAL_ERR(CLASS, N, SCRIPT, BODY) TEST(Interpret, CLASS##_##N)  \
    {                                                                  \
        {                                                              \
            auto r = parse(SCRIPT);                                    \
            bool stop = false;                                         \
            function<void()> f;                                        \
            Mutex mtx;                                                 \
            Condition cond;                                            \
            BODY                                                       \
            EXPECT_CALL(*r.d.get(), onProgramEnded()).                 \
                Times(0);                                              \
            Thread th;                                                 \
            th.startFunc([&]{                                          \
                EXPECT_THROW(r.ast->accept(r.v.get()), InterpretError); \
                ScopedLock<Mutex> lock(mtx);                           \
                f = [&]{ stop = true; r.d->resume(); };                \
                ConditionUnlocker unlocker(cond);                      \
            });                                                        \
            while(true){                                               \
                ScopedLock<Mutex> lock(mtx);                           \
                while (!f) cond.wait(mtx);                             \
                f();                                                   \
                f = {};                                                \
                if (stop) { break; }                                   \
            }                                                          \
            if(th.isRunning())                                         \
                th.join();                                             \
        }                                                              \
        ASSERT_EQ(Statement::counter(), 0);                            \
    }

#define BREAKPOINT_EXPR(line, scol, ecol, body)                        \
r.d->setBreakpoint({line, scol, ecol});                                \
EXPECT_CALL(*r.d.get(), onCatchBreakpoint(Breakpoint(line, scol, ecol))). \
    WillOnce(InvokeWithoutArgs([&]{                                    \
        ScopedLock<Mutex> lock(mtx);                                   \
        f = [&]{ r.d->resume(); };                                     \
        ConditionUnlocker unlocker(cond);                              \
        body                                                           \
    }));

#define BREAKPOINT_LINE(line, body)                                    \
r.d->setBreakpoint({line});                                            \
EXPECT_CALL(*r.d.get(), onCatchBreakpoint(Breakpoint(line))).          \
    WillOnce(InvokeWithoutArgs([&]{                                    \
        ScopedLock<Mutex> lock(mtx);                                   \
        f = [&]{ r.d->resume(); };                                     \
        ConditionUnlocker unlocker(cond);                              \
        body                                                           \
    }));


