#include "VirtualMachine.h"

namespace fun {

VirtualMachine::VirtualMachine() {
}

VirtualMachine::~VirtualMachine() {
}

void VirtualMachine::run(ByteCodeProgram& program) {
    _instructionPointer = program.data();
    fetch();
}

void VirtualMachine::fetch() {
}

void VirtualMachine::push() {
}

void VirtualMachine::pop() {
}

void VirtualMachine::load() {
}

void VirtualMachine::save() {
}

void VirtualMachine::jump() {
}

void VirtualMachine::test() {
}

void VirtualMachine::jumpIfTrue() {
}

void VirtualMachine::jumpIfNotTrue() {
}

void VirtualMachine::print() {
}

void VirtualMachine::binaryOperation() {
}

void VirtualMachine::unaryOperation() {
}

}
