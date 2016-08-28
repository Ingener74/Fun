#include "Compiler.h"

namespace fun {

Compiler::Compiler() {
}

Compiler::~Compiler() {
}

const Program& fun::Compiler::getProgram() const {
    return _program;
}

}
