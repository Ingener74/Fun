#pragma once

#include <string>
#include <vector>

namespace fun {

class Args {
public:
    Args(const std::string& arg);
    virtual ~Args();

    void addArg(const std::string& arg);

    const std::string& getArg(size_t index) const;
    const std::vector<std::string>& getArgs() const;

private:
    std::vector<std::string> m_args;
};

}
