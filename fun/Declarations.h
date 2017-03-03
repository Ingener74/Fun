#pragma once

#include <vector>

class Statement;

using Program = std::vector<Statement*>;
using InstructionPointer = Program::iterator;

using ByteCodeProgram = std::vector<unsigned char>;
using ByteCodeInstructionPointer = ByteCodeProgram::iterator;


