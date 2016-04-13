#include <iostream>
#include <memory>
#include <vector>

#include <llvm/Support/raw_ostream.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/ExecutionEngine/GenericValue.h>

using namespace std;
using namespace llvm;

int main(int argc, char *argv[]) {
    try {
        InitializeNativeTarget();

        LLVMContext context;

        Module* module = new Module("test", context);

        Function* add1 = nullptr;

        {
            add1 = cast<Function>(module->getOrInsertFunction("add1",
                                                              Type::getInt32Ty(context),
                                                              Type::getInt32Ty(context),
                                                              nullptr));

            BasicBlock* add1block = BasicBlock::Create(context, "add1block", add1);

            IRBuilder<> builder(add1block);

            Value* one = builder.getInt32(1);

            Argument* x = &*add1->arg_begin();
            x->setName("x");

            Value* res = builder.CreateAdd(one, x);

            builder.CreateRet(res);
        }

        Function* foo = nullptr;
        {
            foo = cast<Function>(module->getOrInsertFunction("foo",
                                                             Type::getInt32Ty(context),
                                                             Type::getInt32Ty(context),
                                                             nullptr));

            BasicBlock* fooblock = BasicBlock::Create(context, "fooBlock", foo);

            IRBuilder<> builder(fooblock);

            Value* ten = builder.getInt32(10);

            CallInst* add1CallRes = builder.CreateCall(add1, ten);
            add1CallRes->setTailCall(true);

            builder.CreateRet(add1CallRes);
        }

        ExecutionEngine* ee = EngineBuilder(std::unique_ptr<Module>(module)).create();

        std::vector<GenericValue> noargs;
        GenericValue ret = ee->runFunction(foo, noargs);

        outs() << ret.IntVal;
        outs().flush();
//        cout << ret.IntVal << endl;

        delete ee;

//        module->dump();

    } catch (const exception &e) {
        cerr << e.what() << endl;
    }
}