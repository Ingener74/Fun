#pragma once

#include <stdexcept>
#include <location.hh>

namespace fun {

class LexerError: public std::runtime_error {
public:
    LexerError(const std::string& message);
    virtual ~LexerError();
};

class ParserError: public std::runtime_error {
public:
    ParserError(const location& location, const std::string& message);
    virtual ~ParserError();
};

}
