#pragma once

#include <string>
#include <memory>
#include <vector>
#include <unordered_map>
#include <Poco/Mutex.h>
#include <Poco/Condition.h>

namespace fun {

class Printer;

class Breakpoint {
public:
    enum Type {
        LINE, LOCATION,
    };

    Breakpoint(const location& location);
    Breakpoint(unsigned int line, unsigned int startColumn, unsigned int endColumn);
    Breakpoint(unsigned int line);

    virtual ~Breakpoint();

    bool operator ==(const Breakpoint& rhs) const;
    bool operator !=(const Breakpoint& rhs) const;

    friend std::ostream& operator<<(std::ostream&, const Breakpoint&);

    const location& getLocation() const {
        return _location;
    }

    void setLocation(const location& location) {
        _location = location;
    }

    Type getType() const {
        return _type;
    }

private:
    location _location;
    Type _type;
};

using Breakpoints = std::vector<Breakpoint>;

class Debugger {
public:
    Debugger(Printer *printer = nullptr);
    virtual ~Debugger() = default;

    virtual void setBreakpoint(const Breakpoint &breakpoint);
    virtual void enableBreakpoint(const Breakpoint &breakpoint);
    virtual void disableBreakpoint(const Breakpoint &breakpoint);
    virtual void removeBreakpoint(const Breakpoint &breakpoint);
    virtual const Breakpoints &getBreakpoints() const;

    virtual void onCatchBreakpoint(const Breakpoint &) = 0;
    virtual void onOperandsChanged(const std::vector<Terminal*> &) = 0;
    virtual void onMemoryChanged(const std::unordered_map<std::string, Terminal*>&) = 0;

    virtual void list();

    virtual void pause() { _state->pause(this); }
    virtual void resume() { _state->resume(this); }
    virtual void stepOver() { _state->stepOver(this); }
    virtual void stepIn() { _state->stepIn(this); }
    virtual void stepOut() { _state->stepOut(this); }
    virtual void onBeforeStep(Statement *stmt) { _state->onBeforeStep(this, stmt); }

protected:
    Breakpoints _breakpoints;
    bool _run = false;
    Poco::Mutex _mutex;
    Poco::Condition _cond;

    unsigned int _lastBreakpointLine = 1;

    Printer *_printer = nullptr;
    Statement *_currentStatement = nullptr;

private:
    template<typename T, typename ... Args>
    void switchState(Args&& ... args){
        _state.reset(new T(std::forward<Args>(args)...));
    }

    class State{
    public:
        State(){}
        virtual ~State(){}

        virtual void onEnter(Debugger*){}
        virtual void onExit(Debugger*){}

        virtual void pause(Debugger*){}
        virtual void resume(Debugger*){}
        virtual void stepOver(Debugger*){}
        virtual void stepIn(Debugger*){}
        virtual void stepOut(Debugger*){}
        virtual void onBeforeStep(Debugger*, Statement *){}
    };

    class Normal: public State{
    public:
        virtual void onEnter(Debugger *debugger) override;
        virtual void onExit(Debugger *debugger) override;
        virtual void pause(Debugger *debugger) override;
        virtual void resume(Debugger *debugger) override;
        virtual void stepOver(Debugger *debugger) override;
        virtual void stepIn(Debugger *debugger) override;
        virtual void stepOut(Debugger *debugger) override;
        virtual void onBeforeStep(Debugger *debugger, Statement *statement) override;
    };

    class StepOver: public State{
    public:
        StepOver(bool resume = false): _resume(resume){}
        virtual void onEnter(Debugger *debugger) override;
        virtual void onExit(Debugger *debugger) override;
        virtual void pause(Debugger *debugger) override;
        virtual void resume(Debugger *debugger) override;
        virtual void stepOver(Debugger *debugger) override;
        virtual void stepIn(Debugger *debugger) override;
        virtual void stepOut(Debugger *debugger) override;
        virtual void onBeforeStep(Debugger *debugger, Statement *statement) override;
        bool _resume = false;
    };
    std::unique_ptr<State> _state;
};

}


