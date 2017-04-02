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

class VirtualMachine;

class MockDebugger: public Debugger, public Poco::Runnable {
public:
    MockDebugger();
    virtual ~MockDebugger();

    // Override
    MOCK_METHOD1(onCatchBreakpoint, void(const fun::Breakpoint &));
    MOCK_METHOD1(onOperandsChanged, void(const std::vector<fun::Terminal*> &));
    MOCK_METHOD1(onMemoryChanged, void(const std::unordered_map<std::string, fun::Terminal*>&));
    virtual void listen(Poco::AutoPtr<Pot>, Poco::AutoPtr<Compiler>, VirtualMachine*);
    virtual void onEndProgram() override;

    using Handler = std::function<void(IOperands*, IMemory*)>;

    MockDebugger* handleBreakpoint(Handler);
    MockDebugger* handleEnd(Handler);
    MockDebugger* handleError(Handler);

private:
    virtual void run() override;

    class Finalizer {
    public:
        Finalizer(const std::function<void()> finally): _f(finally) {}
        virtual ~Finalizer() {
            final();
        }

        void final() {
            if(_f)
                _f();
            _f = {};
        }

    private:
        std::function<void()> _f;
    };

    Poco::AutoPtr<Pot> _pot;
    Poco::AutoPtr<Compiler> _compiler;
    VirtualMachine* _virtualMachine;

    Handler _breakpointHandler;
    Handler _endHandler;
    Handler _errorHandler;

    bool _wait = true;
    bool _stop = false;
    Poco::Mutex _mutex;
    Poco::Condition _condition;

    std::exception_ptr _exceptionPtr;
};

}
