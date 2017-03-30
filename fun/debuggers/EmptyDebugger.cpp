#include "AST.h"
#include "Compiler.h"
#include "VirtualMachine.h"
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

void EmptyDebugger::listen(Poco::AutoPtr<Pot> pot, Poco::AutoPtr<Compiler> compiler, VirtualMachine* vm) {
    pot->accept(compiler);
    vm->run(compiler->getProgram(), pot, this);
}

void EmptyDebugger::onEndProgram() {
}

}
