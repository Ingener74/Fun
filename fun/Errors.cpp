#include <sstream>
#include "Errors.h"

namespace fun {

using namespace std;

LexerError::LexerError(const string& message) :
        runtime_error(message) {
}

LexerError::~LexerError() {
}

ParserError::ParserError(const location& location, const string& message) :
        runtime_error([&location, &message] {
            stringstream ss;
            ss << location << ": " << message;
            return ss.str();
        }()) {
}

ParserError::~ParserError() {
}

InterpretError::InterpretError(const string& message) :
        runtime_error(message) {
}

InterpretError::~InterpretError() {
}

FunError::FunError(const string& message) :
        runtime_error(message) {
}

FunError::~FunError() {
}

}
