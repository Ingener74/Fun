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

#define PARSE(CLASS, N, SCRIPT)                                        \
    TEST(Parse, CLASS##_##N)                                           \
    {                                                                  \
        {                                                              \
            EXPECT_NO_THROW(parse(SCRIPT));                            \
        }                                                              \
        ASSERT_EQ(Statement::counter(), 0);                            \
    }

#define PARSE_ERR(CLASS, N, SCRIPT, ERROR_CLASS)                       \
    TEST(Parse, CLASS##_##N)                                           \
    {                                                                  \
        {                                                              \
            EXPECT_THROW(parse(SCRIPT), ERROR_CLASS);                  \
        }                                                              \
        ASSERT_EQ(Statement::counter(), 0);                            \
    }

#define PARSE_TERM(CLASS, N, SCRIPT, VALUE)                            \
    TEST(Parse, CLASS##_##N)                                           \
    {                                                                  \
        {                                                              \
            ParseResult r;                                             \
            EXPECT_NO_THROW(r = parseAst(SCRIPT););                    \
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
            auto r = interpretInteractive(SCRIPT);                     \
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
            th.startFunc([&r]{                                         \
                r.ast->accept(r.v.get());                              \
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

#define BREAKPOINT(line, body)                                         \
r.d->setBreakpoint({"", line});                                        \
EXPECT_CALL(*r.d.get(), onCatchBreakpoint(Breakpoint{"", line})).      \
    WillOnce(InvokeWithoutArgs([&]{                                    \
        ScopedLock<Mutex> lock(mtx);                                   \
        f = [&]{ r.d->resume(); };                                     \
        ConditionUnlocker unlocker(cond);                              \
        body                                                           \
    }));

