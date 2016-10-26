#pragma once

#include <unordered_map>

namespace fun {

class Terminal;

class IMemory {
public:
    virtual ~IMemory() = default;

    virtual const std::vector<std::unordered_map<std::string, Poco::AutoPtr<Terminal>>>& getMemory() const = 0;
    virtual std::vector<std::unordered_map<std::string, Poco::AutoPtr<Terminal>>>& getMemory() = 0;
};

}
