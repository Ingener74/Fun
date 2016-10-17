#pragma once

#include <Debugger.h>

namespace fun {

class TcpSocketDebugger: public Debugger {
public:
    TcpSocketDebugger();
    virtual ~TcpSocketDebugger();
};

}

