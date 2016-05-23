#pragma once

#include <memory>
#include <stdexcept>

namespace fun {

template<typename T, typename ... Args>
std::unique_ptr<T> make_unique_(Args&& ... args) {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

#define fassert(condition, message) if(!condition) throw std::runtime_error(message);

class Utils {
public:
    Utils();
    virtual ~Utils();
};

}
