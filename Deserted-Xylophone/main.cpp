//
// Created by pavel on 12.04.16.
//

#include <iostream>
#include <stdexcept>

#include <llvm/IR/Module.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Verifier.h>
#include <llvm/IR/PassManager.h>
#include <llvm/Support/raw_ostream.h>

using namespace std;
using namespace llvm;

Module * makeModule();

int main(int argc, char *argv[]) {
    try {

        Module* module = makeModule();

        verifyModule(*module/*, */);

        ModulePassManager mpm;
//         mpm.addPass();
        mpm.run(module);

    } catch (const exception &e) {
        cerr << e.what() << endl;
    }
}

Module * makeModule() {
    LLVMContext &context = getGlobalContext();
    Module* module = new Module("MainModule", context);

    Constant* function = module->getOrInsertFunction("mul_add",
                                IntegerType::get(context, 32),
                                IntegerType::get(context, 32),
                                IntegerType::get(context, 32),
                                IntegerType::get(context, 32));

    Function* mul_add = cast<Function>(function);
    mul_add->setCallingConv(CallingConv::C);

    Function::arg_iterator args = mul_add->arg_begin();

    Value* x = args++;
    x->setName("x");

    Value* y = args++;
    y->setName("y");

    Value* z = args++;
    z->setName("z");

    BasicBlock* block = BasicBlock::Create(context, "block", mul_add);

    IRBuilder<> builder(block);

    Value* tmp = builder.CreateBinOp(BinaryOperator::Mul, x, y, "tmp");
    Value* tmp2 = builder.CreateBinOp(BinaryOperator::Add, tmp, z, "tmp2");

    builder.CreateRet(tmp2);

    return module;
}