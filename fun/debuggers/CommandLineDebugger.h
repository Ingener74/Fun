#pragma once

#include <Poco/Runnable.h>

#include "Debugger.h"

namespace fun {

class CommandLineDebugger: public Debugger, public Poco::Runnable {
public:
    CommandLineDebugger();
    virtual ~CommandLineDebugger();

    virtual void onCatchBreakpoint(const Breakpoint &) override;
    virtual void onOperandsChanged(const std::vector<Terminal*> &) override;
    virtual void onMemoryChanged(const std::unordered_map<std::string, Terminal*>&) override;

    virtual void listen(Poco::AutoPtr<Visitor>, Poco::AutoPtr<Pot>);

    virtual void run() override;

private:
    int resumeCmd();
    int stepIntoCmd();
    int stepOverCmd();
    int operandsCmd();
    int memoryCmd();
    int quitCmd();
    int listCmd();
    int breakpointCmd(const std::vector<std::string>&);

private:
    Poco::AutoPtr<Visitor> _visitor;
    Poco::AutoPtr<Pot> _pot;
};

}
