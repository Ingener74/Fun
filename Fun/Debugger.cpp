
#include <sstream>
#include <algorithm>

#include "Interpreter.h"
#include "Printer.h"
#include "Debugger.h"

namespace fun {

using namespace std;
using namespace Poco;

Debugger::Debugger(Printer *printer) : _printer(printer), _state(new Normal) {
}

void Debugger::setBreakpoint(const Breakpoint &breakpoint) {
    vb.push_back(breakpoint);

    stringstream ss;
    ss.seekg(0);
}

void Debugger::enableBreakpoint(const Breakpoint &breakpoint) {
}

void Debugger::disableBreakpoint(const Breakpoint &breakpoint) {
}

void Debugger::removeBreakpoint(const Breakpoint &breakpoint) {
    auto it = find(begin(vb), end(vb), breakpoint);
    if (it == vb.end())
        return;
    vb.erase(it);
}

const Breakpoints &Debugger::getBreakpoints() const {
    return vb;
}

void Debugger::list() {
    if (_currentStatement)
        _currentStatement->accept(_printer);
}

void Debugger::Normal::onEnter(Debugger *debugger) {
}

void Debugger::Normal::onExit(Debugger *debugger) {
}

void Debugger::Normal::pause(Debugger *d) {
}

void Debugger::Normal::resume(Debugger *d) {
    Mutex::ScopedLock lock(d->_mutex);
    d->_run = true;
    d->_cond.signal();
}

void Debugger::Normal::stepOver(Debugger *d) {
    Mutex::ScopedLock lock(d->_mutex);
    d->switchState<StepOver>(true);
}

void Debugger::Normal::stepIn(Debugger *d) {
}

void Debugger::Normal::stepOut(Debugger *d) {
}

void Debugger::Normal::onBeforeStep(Debugger *d, Statement *statement) {
    Mutex::ScopedLock lock(d->_mutex);
    d->_currentStatement = statement;
    for (auto &b: d->vb) {
        if (b.line == statement->loc.begin.line) {
            while (!d->_run)
                d->_cond.wait(d->_mutex);
            d->_run = false;
        }
    }
}

void Debugger::StepOver::onEnter(Debugger *d) {
    if (_resume)
        resume(d);
}

void Debugger::StepOver::onExit(Debugger *debugger) {
}

void Debugger::StepOver::pause(Debugger *d) {
}

void Debugger::StepOver::resume(Debugger *d) {
    Mutex::ScopedLock lock(d->_mutex);
    d->switchState<Normal>();
    d->_run = true;
    d->_cond.signal();
}

void Debugger::StepOver::stepOver(Debugger *d) {
    Mutex::ScopedLock lock(d->_mutex);
    d->_run = true;
    d->_cond.signal();
}

void Debugger::StepOver::stepIn(Debugger *d) {
}

void Debugger::StepOver::stepOut(Debugger *d) {
}

void Debugger::StepOver::onBeforeStep(Debugger *d, Statement *statement) {
    Mutex::ScopedLock lock(d->_mutex);
    d->_currentStatement = statement;
    while (!d->_run)
        d->_cond.wait(d->_mutex);
    d->_run = false;
}
}
