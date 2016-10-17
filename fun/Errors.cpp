
#include <sstream>
#include "Errors.h"

namespace fun {

using namespace std;

LexerError::LexerError(const std::string& message) :
        std::runtime_error(message) {
}

LexerError::~LexerError() {
}

ParserError::ParserError(const location& location, const std::string& message) :
        runtime_error([&location, &message] {
            stringstream ss;
            ss << location << ": " << message;
            return ss.str();
        }()) {
}

ParserError::~ParserError() {
}

InterpretError::InterpretError(const std::string& message) :
        runtime_error(message) {
}

InterpretError::~InterpretError() {
}

}
