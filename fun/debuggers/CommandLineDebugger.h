#pragma once

#include <Debugger.h>

namespace fun {

class CommandLineDebugger: public Debugger {
public:
    CommandLineDebugger();
    virtual ~CommandLineDebugger();
};

}
