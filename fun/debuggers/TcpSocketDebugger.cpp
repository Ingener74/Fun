#include "debuggers/TcpSocketDebugger.h"

namespace fun {

using namespace std;
using namespace Poco;

TcpSocketDebugger::TcpSocketDebugger() {
}

TcpSocketDebugger::~TcpSocketDebugger() {
}

void TcpSocketDebugger::onCatchBreakpoint(const Breakpoint&) {
}

void TcpSocketDebugger::onOperandsChanged(const vector<Terminal*>&) {
}

void TcpSocketDebugger::onMemoryChanged(const unordered_map<string, Terminal*>&) {
}

void TcpSocketDebugger::listen(AutoPtr<Visitor>, AutoPtr<Pot>) {
}

}
