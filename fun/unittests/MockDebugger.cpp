#include <Poco/Thread.h>
#include "AST.h"
#include "Compiler.h"
#include "VirtualMachine.h"
#include "MockDebugger.h"

namespace fun {

using namespace std;
using namespace Poco;

MockDebugger::MockDebugger() {
}

MockDebugger::~MockDebugger() {
}

void MockDebugger::listen(Poco::AutoPtr<Pot> pot, Poco::AutoPtr<Compiler> compiler, VirtualMachine* vm) {
    _pot = pot;
    _compiler = compiler;
    _virtualMachine = vm;

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

void MockDebugger::onEndProgram() {
    if (_endHandler)
        _endHandler(_virtualMachine, _virtualMachine);
}

void MockDebugger::run() {
    Finalizer f([this] {
        ScopedLock<Mutex> lock(_mutex);
        _stop = true;
        _wait = false;
        _condition.signal();
    });
    try {
        _pot->accept(_compiler);
        _virtualMachine->run(_compiler->getProgram(), _pot, this);
//        if (_endHandler)
//            _endHandler(_virtualMachine, _virtualMachine);
    } catch (exception const& e) {
        if (_errorHandler)
            _errorHandler(_virtualMachine, _virtualMachine);
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
        function(_virtualMachine, _virtualMachine);
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
