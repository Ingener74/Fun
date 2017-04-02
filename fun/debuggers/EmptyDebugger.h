#pragma once

#include "Debugger.h"

namespace fun {

class EmptyDebugger: public Debugger {
public:
    EmptyDebugger();
    virtual ~EmptyDebugger();

    virtual void onCatchBreakpoint(const Breakpoint &) override;
    virtual void onOperandsChanged(const std::vector<Terminal*> &) override;
    virtual void onMemoryChanged(const std::unordered_map<std::string, Terminal*>&) override;
    virtual void listen(Poco::AutoPtr<Pot>, Poco::AutoPtr<Compiler>, VirtualMachine*) override;
    virtual void onEndProgram() override;
};

}
