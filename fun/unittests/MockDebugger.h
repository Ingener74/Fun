#pragma once

#include <functional>
#include <exception>

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <gmock/gmock-actions.h>

#include <Poco/Runnable.h>
#include <Poco/Mutex.h>
#include <Poco/Condition.h>

#include "Debugger.h"

namespace fun {

class MockDebugger: public Debugger, public Poco::Runnable {
public:
    MockDebugger();
    virtual ~MockDebugger();

    // Override
    MOCK_METHOD1(onCatchBreakpoint, void(const fun::Breakpoint &));
    MOCK_METHOD1(onOperandsChanged, void(const std::vector<fun::Terminal*> &));
    MOCK_METHOD1(onMemoryChanged, void(const std::unordered_map<std::string, fun::Terminal*>&));
    virtual void listen(Poco::AutoPtr<Visitor>, Poco::AutoPtr<Pot>);

    using Handler = std::function<void(IOperands*, IMemory*)>;

    MockDebugger* handleBreakpoint(Handler);
    MockDebugger* handleEnd(Handler);

private:
    virtual void run() override;

    class ConditionUnlocker {
    public:
        ConditionUnlocker(Poco::Condition& _condition);
        virtual ~ConditionUnlocker();
    private:
        ConditionUnlocker(const ConditionUnlocker&) = delete;
        ConditionUnlocker& operator=(const ConditionUnlocker&) = delete;
        Poco::Condition& _condition;
    };

    Poco::AutoPtr<Visitor> _visitor;
    Poco::AutoPtr<Pot> _pot;

    std::function<void(IOperands*, IMemory*)> _breakpointHandler;
    std::function<void(IOperands*, IMemory*)> _endHandler;

    bool _stop = false;
    std::function<void()> f;
    Poco::Mutex _mutex;
    Poco::Condition _condition;

    std::exception_ptr _exceptionPtr;
};

}
