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
    int resumeCmd(const std::vector<std::string>& tokens);
    int stepIntoCmd(const std::vector<std::string>& tokens);
    int stepOverCmd(const std::vector<std::string>& tokens);
    int operandsCmd(const std::vector<std::string>& tokens);
    int memoryCmd(const std::vector<std::string>& tokens);
    int quitCmd(const std::vector<std::string>& tokens);
    int listCmd(const std::vector<std::string>& tokens);
    int breakpointCmd(const std::vector<std::string>&);

private:
    Poco::AutoPtr<Visitor> _visitor;
    Poco::AutoPtr<Pot> _pot;

    using Command = int (CommandLineDebugger::*)(const std::vector<std::string>&);
    using Commands = std::unordered_map<std::string, Command>;

    Commands _commands;
};

}
