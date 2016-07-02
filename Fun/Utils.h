#pragma once

#include <memory>
#include <stdexcept>
#include <sstream>

namespace fun {

template<typename T, typename ... Args>
std::unique_ptr<T> make_unique_(Args&& ... args) {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

template<typename Res, typename Arg>
Res to_(Arg&& arg) {
    std::stringstream _;
    _ << arg;
    Res res;
    _ >> res;
    return res;
}

#define fassert(condition, message) \
    if(!condition) \
        throw std::runtime_error( \
                std::string("Error: ") + std::string(message) + std::string("\n") + \
                std::string("At: ") + std::string(__FILE__) + std::string(": ") + to_<std::string>(__LINE__));

class Utils {
public:
    Utils() = default;
    virtual ~Utils() = default;
};

}
