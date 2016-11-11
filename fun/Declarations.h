#pragma once

#include <vector>

class Statement;

using Program = std::vector<Statement*>;
using InstructionPointer = Program::iterator;

using ByteCode = std::vector<unsigned char>;
using ByteCodeInstructionPointer = ByteCode::iterator;


