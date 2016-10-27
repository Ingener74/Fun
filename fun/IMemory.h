#pragma once

#include <unordered_map>

namespace fun {

class Terminal;

class IMemory {
public:
    virtual ~IMemory() = default;

    virtual size_t getMemoryLevelCount() const = 0;

    virtual bool has(const std::string& name) const = 0;
    virtual bool has(size_t memoryLevel, const std::string& name) const = 0;

    virtual Terminal::Type type(const std::string& name) const = 0;
    virtual Terminal::Type type(size_t memoryLevel, const std::string& name) const = 0;

    virtual bool boolean(const std::string& name) const = 0;
    virtual bool boolean(size_t memoryLevel, const std::string& name) const = 0;

    virtual long long int integer(const std::string& name) const = 0;
    virtual long long int integer(size_t memoryLevel, const std::string& name) const = 0;

    virtual double real(const std::string& name) const = 0;
    virtual double real(size_t memoryLevel, const std::string& name) const = 0;
};

}
