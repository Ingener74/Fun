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
    ScopedLock<Mutex> lock(_mutex);
    th.start(*this);
    while (true) {
        while (!f){
            _condition.wait(_mutex);
            cout << "after wait" << endl;
        }
        f();
        f = {};
        if (_stop) {
            break;
        }
    }
    if (th.isRunning())
        th.join();

    if (_exceptionPtr)
        rethrow_exception(_exceptionPtr);
}

void MockDebugger::run() {
    try {
        ScopedLock<Mutex> lock(_mutex);
        f = [&] {
            _stop = true;
            resume();
        };
        ConditionUnlocker unlocker(_condition);

        _pot->accept(_visitor);
        if (_endHandler)
            _endHandler(_visitor.cast<Interpreter>(), _visitor.cast<Interpreter>());
    } catch (exception const& e) {
        _exceptionPtr = current_exception();
    }
}

MockDebugger* MockDebugger::handleBreakpoint(Handler function) {
    Poco::ScopedLock<Poco::Mutex> lock(_mutex);
    f = [&] {
        resume();
    };
    ConditionUnlocker unlocker(_condition);
    if (function)
        function(_visitor.cast<Interpreter>(), _visitor.cast<Interpreter>());
    cout << static_cast<bool>(f) << endl;
    return this;
}

MockDebugger* MockDebugger::handleEnd(Handler function) {
    _endHandler = function;
    return this;
}

MockDebugger::ConditionUnlocker::ConditionUnlocker(Condition &cond) :
    _condition(cond) {
}

MockDebugger::ConditionUnlocker::~ConditionUnlocker() {
    cout << "signal" << endl;
    _condition.signal();
}

}
