#include <Poco/Thread.h>
#include "AST.h"
#include "Visitor.h"
#include "Interpreter.h"
#include "MockDebugger.h"

namespace fun {

using namespace std;
using namespace Poco;

MockDebugger::MockDebugger() {
}

MockDebugger::~MockDebugger() {
}

void MockDebugger::listen(AutoPtr<Visitor> visitor, AutoPtr<Pot> pot) {
    _visitor = visitor;
    _pot = pot;
    Thread th;
    th.start(*this);
    while (true) {
        ScopedLock<Mutex> lock(mtx);
        while (!f)
            cond.wait(mtx);
        f();
        f = {};
        if (stop) {
            break;
        }
    }
    if (th.isRunning())
        th.join();

    if (_exceptionPtr)
        rethrow_exception(_exceptionPtr);
}

void MockDebugger::run() {
    // EXPECT_NO_THROW(pot->accept(visitor));
    try {
        _pot->accept(_visitor);
        ScopedLock<Mutex> lock(mtx);
        f = [&] {
            stop = true;
            resume();
        };
        ConditionUnlocker unlocker(cond);
        if (_endHandler)
            _endHandler(_visitor.cast<Interpreter>(), _visitor.cast<Interpreter>());
    } catch (exception const& e) {
        _exceptionPtr = current_exception();
    }
}

MockDebugger* MockDebugger::breakpointHandler(const std::function<void(IOperands*, IMemory*)>& function) {
    Poco::ScopedLock<Poco::Mutex> lock(mtx);
    f = [&] {
        resume();
    };
    ConditionUnlocker unlocker(cond);
    if (function)
        function(_visitor.cast<Interpreter>(), _visitor.cast<Interpreter>());
    return this;
}

MockDebugger* MockDebugger::endHandler(const std::function<void(IOperands*, IMemory*)>& function) {
    _endHandler = function;
    return this;
}

}
