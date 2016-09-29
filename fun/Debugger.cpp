
#include <sstream>
#include <algorithm>

#include "Interpreter.h"
#include "Printer.h"
#include "Debugger.h"

namespace fun {

using namespace std;
using namespace Poco;


Breakpoint::Breakpoint(const location& location) :
        _location(location), _type(LOCATION) {
}

Breakpoint::Breakpoint(unsigned int line, unsigned int startColumn, unsigned int endColumn):
    Breakpoint(location(position(nullptr, line, startColumn), position(nullptr, line, endColumn))) {
}

Breakpoint::Breakpoint(unsigned int line):
    _location(position{nullptr, line, 0}), _type(LINE) {
}

Breakpoint::~Breakpoint() {
}

bool Breakpoint::operator ==(const Breakpoint& rhs) const {
    return _location == rhs._location;
}

bool Breakpoint::operator !=(const Breakpoint& rhs) const {
    return !(rhs == *this);
}

ostream& operator<<(ostream& out, const Breakpoint& rhs){
    return out << "Breakpoint(" << rhs._location << ")";
}

Debugger::Debugger(Printer *printer) : _printer(printer), _state(new Normal) {
}

void Debugger::setBreakpoint(const Breakpoint &breakpoint) {
    _breakpoints.push_back(breakpoint);

    stringstream ss;
    ss.seekg(0);
}

void Debugger::enableBreakpoint(const Breakpoint &breakpoint) {
}

void Debugger::disableBreakpoint(const Breakpoint &breakpoint) {
}

void Debugger::removeBreakpoint(const Breakpoint &breakpoint) {
    auto it = find(begin(_breakpoints), end(_breakpoints), breakpoint);
    if (it == _breakpoints.end())
        return;
    _breakpoints.erase(it);
}

const Breakpoints &Debugger::getBreakpoints() const {
    return _breakpoints;
}

void Debugger::list() {
    if (_currentStatement && _printer)
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

    auto line = statement->loc.begin.line;

    d->_currentStatement = statement;
    for (auto &breakpoint : d->_breakpoints) {
        if (breakpoint.getType() == Breakpoint::LOCATION ?
                (breakpoint.getLocation() == statement->loc):
                (breakpoint.getLocation().begin.line == line && d->_lastBreakpointLine != line)) {
            while (!d->_run) {
                d->onCatchBreakpoint(breakpoint);
                d->_cond.wait(d->_mutex);
            }
            d->_run = false;
        }
    }
    d->_lastBreakpointLine = line;
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
    d->onCatchBreakpoint(Breakpoint{statement->loc});
    d->_run = false;
}
}
