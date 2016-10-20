#pragma once

#include <functional>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <gmock/gmock-actions.h>
#include <Poco/Mutex.h>
#include <Poco/Condition.h>

#include "Debugger.h"

namespace fun {

class MockDebugger: public Debugger {
public:
    MockDebugger();
    virtual ~MockDebugger();

    // Override
    MOCK_METHOD1(onCatchBreakpoint, void(const fun::Breakpoint &));
    MOCK_METHOD1(onOperandsChanged, void(const std::vector<fun::Terminal*> &));
    MOCK_METHOD1(onMemoryChanged, void(const std::unordered_map<std::string, fun::Terminal*>&));
    virtual void listen(Poco::AutoPtr<Visitor>, Poco::AutoPtr<Pot>);

    void onBreakpoint(const std::function<void()>&);

private:
    bool stop = false;
    std::function<void()> f;
    Poco::Mutex mtx;
    Poco::Condition cond;
};

}
