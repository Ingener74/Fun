#pragma once

#include "Declarations.h"
#include "Visitor.h"

namespace fun {

class Compiler: public Visitor {
public:
    Compiler();
    virtual ~Compiler();

    virtual void iterateStatements(Statement*);

    virtual void visit(Statement*);
    virtual void visit(Break*);
    virtual void visit(Continue*);
    virtual void visit(Class*);
    virtual void visit(For*);
    virtual void visit(Function*);
    virtual void visit(Ifs*);
    virtual void visit(If*);
    virtual void visit(Import*);
    virtual void visit(Print*);
    virtual void visit(Return*);
    virtual void visit(While*);
    virtual void visit(Exception*);
    virtual void visit(Throw*);

    virtual void visit(Expression*);
    virtual void visit(Assign*);
    virtual void visit(BinaryOp*);
    virtual void visit(Dot*);
    virtual void visit(Call*);
    virtual void visit(Dictionary*);
    virtual void visit(Id*);
    virtual void visit(Index*);
    virtual void visit(RoundBrackets*);

    virtual void visit(Terminal*);
    virtual void visit(Boolean*);
    virtual void visit(Integer*);
    virtual void visit(Nil*);
    virtual void visit(Real*);
    virtual void visit(String*);

    const ByteCodeProgram& getProgram() const;

    bool hasDebugInfo() const {
        return _debugInfo;
    }

    void setDebugInfo(bool debugInfo = false) {
        _debugInfo = debugInfo;
    }

private:
    static const int PROGRAM_SIZE_INCREMENT = 4096;

    void checkOffsetAndResizeProgram(ptrdiff_t offset, size_t size);
    void checkPointerAndResizeProgram(void* ptr, size_t size);

    void write(void* to, void* data, size_t size);
    void write(void* data, size_t size);
    template<typename T>
    void write(const T& data);
    void write(const std::string& str);
    void write(OpCode, Statement*);

    bool _debugInfo = false;

    ByteCodeProgram _program;
    uint8_t* _programPtr = nullptr;
};

template<typename T>
inline void Compiler::write(const T& data) {
    write(const_cast<void*>(static_cast<const void*>(&data)), sizeof(data));
}

}
