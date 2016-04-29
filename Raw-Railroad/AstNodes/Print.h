#pragma once

#include <string>

class Print {
public:
    Print(const std::string& id);
    virtual ~Print();

    const std::string& getId() const {
        return m_id;
    }

private:
    std::string m_id;
};
