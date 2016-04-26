#pragma once

class IdExpr;

class ArgType {
public:
    ArgType();
    virtual ~ArgType();

    void addArg(IdExpr*);
};
