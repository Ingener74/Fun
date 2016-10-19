#include "debuggers/EmptyDebugger.h"

namespace fun {

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

void EmptyDebugger::listen() {
}

}
