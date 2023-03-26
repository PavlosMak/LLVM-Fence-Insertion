#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

namespace {
    struct FenceInsertion : public FunctionPass {
        static char ID;
        FenceInsertion() : FunctionPass(ID) {}

        bool runOnFunction(Function &F) override {
            errs() << "Fence Insertion: ";
            errs().write_escaped(F.getName()) << "\n";
            return false; //We do not modify the code
        }
    };
}

char FenceInsertion::ID = 0; //Actual value does not matter; LLVM uses the pointer to it as identifier
static RegisterPass<FenceInsertion> X("FenceInsertion", "A fence insetion pass", 
false, // Does it only look at the CFG?
false  // Is it an analysis pass?
);