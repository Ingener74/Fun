#pragma once


#include <Debugger.h>

namespace fun {



class CommandLineDebugger: public Debugger {
public:
    CommandLineDebugger();
    virtual ~CommandLineDebugger();

    virtual void onCatchBreakpoint(const Breakpoint &) override;
    virtual void onOperandsChanged(const std::vector<Terminal*> &) override;
    virtual void onMemoryChanged(const std::unordered_map<std::string, Terminal*>&) override;

    virtual void listen();
};

}