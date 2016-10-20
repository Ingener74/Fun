#include "debuggers/MockDebugger.h"

namespace fun {

using namespace std;
using namespace Poco;

MockDebugger::MockDebugger() {
}

MockDebugger::~MockDebugger() {
}

void MockDebugger::listen(AutoPtr<Visitor> visitor, AutoPtr<Pot> pot) {
    Thread th;
    th.startFunc([visitor, pot] {
        // EXPECT_NO_THROW(pot->accept(visitor));
            pot->accept(visitor);
            ScopedLock<Mutex> lock(mtx);
            f = [&] {
                stop = true;
                resume();
            };
            ConditionUnlocker unlocker(cond);
            // END
        });
    while (true) {
        ScopedLock<Mutex> lock(mtx);
        while (!f)
            cond.wait(mtx);
        f();
        f = {};
        if (stop) {
            break;
        }
    }
    if (th.isRunning())
        th.join();
}

}
