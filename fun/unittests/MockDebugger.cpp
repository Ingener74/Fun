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
        while (_wait)
            _condition.wait(_mutex);
        resume();
        _wait = true;
        if (_stop)
            break;
    }
    if (th.isRunning())
        th.join();

    if (_exceptionPtr)
        rethrow_exception(_exceptionPtr);
}

void MockDebugger::run() {
    Finalizer f([this] {
        ScopedLock<Mutex> lock(_mutex);
        _stop = true;
        _wait = false;
        _condition.signal();
    });
    try {
        _pot->accept(_visitor);
        if (_endHandler)
            _endHandler(_visitor.cast<Interpreter>(), _visitor.cast<Interpreter>());
    } catch (exception const& e) {
        if (_errorHandler)
            _errorHandler(_visitor.cast<Interpreter>(), _visitor.cast<Interpreter>());
        _exceptionPtr = current_exception();
    }
}

MockDebugger* MockDebugger::handleBreakpoint(Handler function) {
    Finalizer f([this] {
        Poco::ScopedLock<Poco::Mutex> lock(_mutex);
        _wait = false;
        _condition.signal();
    });
    if (function)
        function(_visitor.cast<Interpreter>(), _visitor.cast<Interpreter>());
    return this;
}

MockDebugger* MockDebugger::handleEnd(Handler function) {
    _endHandler = function;
    return this;
}

MockDebugger *MockDebugger::handleError(Handler handler) {
    _errorHandler = handler;
    return this;
}

}
