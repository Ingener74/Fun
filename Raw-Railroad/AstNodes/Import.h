#pragma once

#include <string>

using namespace std;

class Import {
public:
    Import(const std::string& library);
    virtual ~Import();

    const std::string& getImport() const {
        return m_import;
    }

private:
    std::string m_import;
};
