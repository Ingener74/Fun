#include "AST.h"
#include "Visitor.h"
#include "debuggers/EmptyDebugger.h"

namespace fun {

using namespace std;
using namespace Poco;

EmptyDebugger::EmptyDebugger() {
}

EmptyDebugger::~EmptyDebugger() {
}

void EmptyDebugger::onCatchBreakpoint(const Breakpoint&) {
}

void EmptyDebugger::onOperandsChanged(const std::vector<Terminal*>&) {
}

void EmptyDebugger::onMemoryChanged(const std::unordered_map<std::string, Terminal*>&) {
}

void EmptyDebugger::listen(AutoPtr<Visitor> v, AutoPtr<Pot> p) {
    p->accept(v);
}

}
