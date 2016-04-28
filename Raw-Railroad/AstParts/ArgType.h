#pragma once

#include <string>

class IdExpr;

class ArgType {
public:
    ArgType(const std::string& id);
    virtual ~ArgType();

    void addArg(IdExpr*);

    void setTest();

    const std::string& getId() const {
        return m_id;
    }

private:
    std::string m_id;
};
