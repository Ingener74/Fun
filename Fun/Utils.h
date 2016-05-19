#pragma once

#include <memory>

namespace fun {

template<typename T, typename ... Args>
std::unique_ptr<T> make_unique_(Args&& ... args) {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

class Utils {
public:
    Utils();
    virtual ~Utils();
};

}
