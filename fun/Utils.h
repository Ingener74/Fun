#pragma once

#include <memory>
#include <stdexcept>
#include <sstream>
#include <Errors.h>

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
    if(!(condition)) \
        throw InterpretError( \
                std::string("Error: ") + std::string((message)) + std::string("\n") + \
                std::string("At: ") + std::string(__FILE__) + std::string(": ") + to_<std::string>(__LINE__));

#define fassertl(condition, loc, message) \
    if(!(condition)) \
        throw InterpretError( \
                std::string("Error: ") + to_<string>(loc) + ": " + std::string((message)) + std::string("\n") + \
                std::string("At: ") + std::string(__FILE__) + std::string(": ") + to_<std::string>(__LINE__));

#define fasserts(condition, stmt, message) \
    if(!(condition)) \
        if (stmt) \
            throw InterpretError( \
                    std::string("Error: ") + to_<string>(stmt->loc) + ": " + std::string((message)) + std::string("\n") + \
                    std::string("At: ") + std::string(__FILE__) + std::string(": ") + to_<std::string>(__LINE__)); \
        else \
            throw InterpretError( \
                    std::string("Error: ") + std::string((message)) + std::string("\n") + \
                    std::string("At: ") + std::string(__FILE__) + std::string(": ") + to_<std::string>(__LINE__));

class Utils {
public:
    Utils() = default;
    virtual ~Utils() = default;
};

template<typename T>
class VectorView {
public:
    VectorView() :
            _data(nullptr), _size(0) {
    }
    VectorView(const std::vector<T>& v) :
            _data(v.data()), _size(v.size()) {
    }

    bool checkInside(T* t) {
        return !_data && _data <= t && t < (_data + _size);
    }

private:
    const T* _data = nullptr;
    size_t _size = 0;
};

template<typename T>
VectorView<T> make_vector_view(const std::vector<T>& v) {
    return VectorView<T>(v);
}

}
