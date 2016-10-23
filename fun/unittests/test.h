#pragma once

#include <memory>
#include <list>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <gmock/gmock-actions.h>

#include <Poco/Thread.h>

#include <Fun.h>
#include "MockDebugger.h"

#define PARSE(CLASS, N, SCRIPT)                                        \
    TEST(Parse, CLASS##_##N)                                           \
    {                                                                  \
        {                                                              \
            Poco::AutoPtr<Pot> pot;                                    \
            EXPECT_NO_THROW(pot = Fun::parseString(SCRIPT););          \
        }                                                              \
        ASSERT_EQ(Statement::counter(), 0);                            \
    }

#define PARSE_ERR(CLASS, N, SCRIPT, ERROR_CLASS)                       \
    TEST(Parse, CLASS##_##N)                                           \
    {                                                                  \
        {                                                              \
            Poco::AutoPtr<Pot> pot;                                    \
            EXPECT_THROW(pot = Fun::parseString(SCRIPT), ERROR_CLASS); \
        }                                                              \
        ASSERT_EQ(Statement::counter(), 0);                            \
    }

#define PARSE_TERM(CLASS, N, SCRIPT, VALUE)                            \
    TEST(Parse, CLASS##_##N)                                           \
    {                                                                  \
        {                                                              \
            Poco::AutoPtr<Pot> pot;                                    \
            EXPECT_NO_THROW(pot = Fun::parseString(SCRIPT););          \
            auto instance = dynamic_cast<CLASS*>(pot->root());         \
            ASSERT_NE(instance, nullptr);                              \
            ASSERT_EQ(instance->value, VALUE);                         \
        }                                                              \
        ASSERT_EQ(Statement::counter(), 0);                            \
    }


#define EVAL(CLASS, N, SCRIPT, BODY, END) TEST(Interpret, CLASS##_##N) \
    {                                                                  \
        {                                                              \
            Fun f;                                                     \
            auto dbg = new MockDebugger;                               \
            f.setDebugger(dbg);                                        \
            BODY                                                       \
            dbg->handleEnd([](IOperands* operands, IMemory* memory) {  \
                END                                                    \
            });                                                        \
            ASSERT_NO_THROW(f.evalString(SCRIPT); );                   \
        }                                                              \
        ASSERT_EQ(Statement::counter(), 0);                            \
    }

#define EVAL_ERR(CLASS, N, SCRIPT, BODY) TEST(Interpret, CLASS##_##N)  \
    {                                                                  \
        {                                                              \
            Fun f;                                                     \
            auto dbg = new MockDebugger;                               \
            f.setDebugger(dbg);                                        \
            BODY                                                       \
            EXPECT_THROW(f.evalString(SCRIPT);, InterpretError);       \
        }                                                              \
        ASSERT_EQ(Statement::counter(), 0);                            \
    }

#define BREAKPOINT_EXPR(line, scol, ecol, body)                        \
    dbg->setBreakpoint(Breakpoint(line, scol, ecol));                      \
    EXPECT_CALL(*dbg, onCatchBreakpoint(Breakpoint(line, scol, ecol))).    \
        WillOnce(testing::InvokeWithoutArgs([dbg] {                        \
            dbg->handleBreakpoint([](IOperands* operands, IMemory* memory) { \
                body                                                       \
            });                                                            \
        })                                                                 \
    );

#define BREAKPOINT_LINE(line, body)                                    \
    dbg->setBreakpoint(Breakpoint(line));                                  \
    EXPECT_CALL(*dbg, onCatchBreakpoint(Breakpoint(line))).                \
        WillOnce(testing::InvokeWithoutArgs([dbg] {                        \
            dbg->handleBreakpoint([](IOperands* operands, IMemory* memory) { \
                body                                                       \
            });                                                            \
        })                                                                 \
    );


