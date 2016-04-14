#include <iostream>
#include <memory>
#include <vector>

#include <llvm/Support/raw_ostream.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>
#include "llvm/ExecutionEngine/Interpreter.h"
#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/ExecutionEngine/GenericValue.h>

using namespace std;
using namespace llvm;

Function * createAdd1(Module*, LLVMContext&);
Function * createFoo(Module*, LLVMContext&, Function*);

int main(int argc, char *argv[]) {
    try {
        InitializeNativeTarget();

        LLVMContext context;

        Module *module = new Module("test", context);

        Function *add1 = createAdd1(module, context);

        Function *foo = createFoo(module, context, add1);

        module->dump();

        std::string errorStr;
        ExecutionEngine *ee = EngineBuilder(std::unique_ptr<Module>(module))
                .setErrorStr(&errorStr)
                .create();

        if (!errorStr.empty())
            cout << errorStr << endl;
        if (ee) {
            std::vector<GenericValue> noargs;
            GenericValue ret = ee->runFunction(foo, noargs);

            outs() << ret.IntVal;
            outs().flush();
        }

        delete ee;

    } catch (const exception &e) {
        cerr << e.what() << endl;
    }
}

Function * createAdd1(Module *module, LLVMContext &context) {
    Function *add1 = cast<Function>(module->getOrInsertFunction("add1",
                                                                Type::getInt32Ty(context),
                                                                Type::getInt32Ty(context),
                                                                nullptr));

    BasicBlock *add1block = BasicBlock::Create(context, "add1block", add1);

    IRBuilder<> builder(add1block);

    Value *one = builder.getInt32(1);

    Argument *x = &*add1->arg_begin();
    x->setName("x");

    Value *res = builder.CreateAdd(one, x);

    builder.CreateRet(res);
    return add1;
}

Function * createFoo(Module* module, LLVMContext& context, Function* add1) {
    Function *foo = cast<Function>(module->getOrInsertFunction("foo",
                                                               Type::getInt32Ty(context),
                                                               nullptr));

    BasicBlock *fooblock = BasicBlock::Create(context, "fooBlock", foo);

    IRBuilder<> builder(fooblock);

    Value *ten = builder.getInt32(10);

    CallInst *add1CallRes = builder.CreateCall(add1, ten);
    add1CallRes->setTailCall(true);

    builder.CreateRet(add1CallRes);
    return foo;
}

