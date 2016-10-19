#pragma once

#include <unordered_map>

namespace fun {

class Terminal;

class IMemory {
public:
    virtual ~IMemory() = default;

    const std::vector<std::unordered_map<std::string, Terminal*>>& getMemory() const;
    std::vector<std::unordered_map<std::string, Terminal*>>& getMemory();
};

}
