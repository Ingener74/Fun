#pragma once

#include <Poco/AutoPtr.h>
#include <Lexer.h>
#include <AST.h>
#include <Printer.h>
#include <Interpreter.h>
#include <Compiler.h>
#include <Utils.h>
#include <Debugger.h>

namespace fun {

class Fun {
public:
    Fun();
    virtual ~Fun();

    enum class DebuggerType {
        NoDebugger, NetDebugger, CommandLineDebugger, TestingMockDebugger
    };

    static Poco::AutoPtr<Pot> parseString(const std::string& source);
    static Poco::AutoPtr<Pot> parseStream(const std::istream& source);
    static Poco::AutoPtr<Pot> parseFile(const std::string& filename);

    void evalString(const std::string& script);
    void evalStream(const std::istream& script);
    void evalFile(const std::string& filename);
    void evalAst(Poco::AutoPtr<Pot> pot);

    Fun& setDebugger(DebuggerType);
    Poco::AutoPtr<Debugger> getDebugger();

    template<typename T>
    Poco::AutoPtr<T> getConcreteDebugger() {
        return _debugger.cast<T>();
    }

private:
    Poco::AutoPtr<Debugger> _debugger;
    Poco::AutoPtr<Visitor> _visitor;
};

}
