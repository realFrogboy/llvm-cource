#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/InstIterator.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"

using namespace llvm;

static bool isFuncLogger(StringRef name) {
  return name == "binOptLogger" || name == "callLogger" ||
         name == "funcStartLogger" || name == "funcEndLogger" ||
         name == "cmpLogger" || name == "brLogger" || name == "unaryLogger";
}

static FunctionCallee getFuncStartLoggerCallee(Module &M) {
  LLVMContext &Ctx = M.getContext();
  IRBuilder<> builder(Ctx);

  Type *retType = Type::getVoidTy(Ctx);
  ArrayRef<Type *> funcStartParamTypes = {builder.getInt8Ty()->getPointerTo()};
  FunctionType *funcStartLogFuncType =
      FunctionType::get(retType, funcStartParamTypes, false);

  return M.getOrInsertFunction("funcStartLogger", funcStartLogFuncType);
}

static FunctionCallee getCallLoggerCallee(Module &M) {
  LLVMContext &Ctx = M.getContext();
  IRBuilder<> builder(Ctx);

  Type *retType = Type::getVoidTy(Ctx);
  ArrayRef<Type *> callParamTypes = {builder.getInt8Ty()->getPointerTo(),
                                     builder.getInt8Ty()->getPointerTo(),
                                     Type::getInt64Ty(Ctx)};
  FunctionType *callLogFuncType =
      FunctionType::get(retType, callParamTypes, false);

  return M.getOrInsertFunction("callLogger", callLogFuncType);
}

static FunctionCallee getFuncEndLoggerCallee(Module &M) {
  LLVMContext &Ctx = M.getContext();
  IRBuilder<> builder(Ctx);

  Type *retType = Type::getVoidTy(Ctx);
  ArrayRef<Type *> funcEndParamTypes = {builder.getInt8Ty()->getPointerTo(),
                                        Type::getInt64Ty(Ctx)};
  FunctionType *funcEndLogFuncType =
      FunctionType::get(retType, funcEndParamTypes, false);
  return M.getOrInsertFunction("funcEndLogger", funcEndLogFuncType);
}

static FunctionCallee getBinOptLoggerCallee(Module &M) {
  LLVMContext &Ctx = M.getContext();
  IRBuilder<> builder(Ctx);

  Type *retType = Type::getVoidTy(Ctx);
  ArrayRef<Type *> binOptParamTypes = {Type::getInt32Ty(Ctx),
                                       Type::getInt32Ty(Ctx),
                                       Type::getInt32Ty(Ctx),
                                       builder.getInt8Ty()->getPointerTo(),
                                       builder.getInt8Ty()->getPointerTo(),
                                       Type::getInt64Ty(Ctx)};
  FunctionType *binOptLogFuncType =
      FunctionType::get(retType, binOptParamTypes, false);

  return M.getOrInsertFunction("binOptLogger", binOptLogFuncType);
}

static FunctionCallee getCmpLoggerCallee(Module &M) {
  LLVMContext &Ctx = M.getContext();
  IRBuilder<> builder(Ctx);

  Type *retType = Type::getVoidTy(Ctx);
  ArrayRef<Type *> cmpParamTypes = {Type::getInt32Ty(Ctx),
                                    Type::getInt32Ty(Ctx),
                                    Type::getInt32Ty(Ctx),
                                    builder.getInt8Ty()->getPointerTo(),
                                    builder.getInt8Ty()->getPointerTo(),
                                    Type::getInt64Ty(Ctx)};
  FunctionType *cmpLogFuncType =
      FunctionType::get(retType, cmpParamTypes, false);

  return M.getOrInsertFunction("cmpLogger", cmpLogFuncType);
}

static FunctionCallee getBrLoggerCallee(Module &M) {
  LLVMContext &Ctx = M.getContext();
  IRBuilder<> builder(Ctx);

  Type *retType = Type::getVoidTy(Ctx);
  ArrayRef<Type *> brParamTypes = {
      builder.getInt8Ty()->getPointerTo(), builder.getInt8Ty()->getPointerTo(),
      Type::getInt32Ty(Ctx), Type::getInt64Ty(Ctx)};
  FunctionType *brLogFuncType = FunctionType::get(retType, brParamTypes, false);

  return M.getOrInsertFunction("brLogger", brLogFuncType);
}

static FunctionCallee getUnaryLoggerCallee(Module &M) {
  LLVMContext &Ctx = M.getContext();
  IRBuilder<> builder(Ctx);

  Type *retType = Type::getVoidTy(Ctx);
  ArrayRef<Type *> unaryParamTypes = {builder.getInt8Ty()->getPointerTo(),
                                      builder.getInt8Ty()->getPointerTo(),
                                      Type::getInt64Ty(Ctx)};
  FunctionType *unaryLogFuncType =
      FunctionType::get(retType, unaryParamTypes, false);

  return M.getOrInsertFunction("unaryLogger", unaryLogFuncType);
}

static void insertFuncStartLoggerCall(Module &M, Function &F) {
  LLVMContext &Ctx = F.getContext();
  IRBuilder<> builder(Ctx);

  BasicBlock &entryBB = F.getEntryBlock();
  builder.SetInsertPoint(&entryBB.front());

  FunctionCallee funcStartLogFunc = getFuncStartLoggerCallee(M);
  Value *funcName = builder.CreateGlobalStringPtr(F.getName());
  Value *args[] = {funcName};
  builder.CreateCall(funcStartLogFunc, args);
}

static void insertCallLoggerCall(Module &M, Function &F, CallInst *CI) {
  assert(CI);

  Function *callee = CI->getCalledFunction();
  if (!callee || isFuncLogger(callee->getName()))
    return;

  LLVMContext &Ctx = F.getContext();
  IRBuilder<> builder(Ctx);

  builder.SetInsertPoint(CI);

  FunctionCallee callLogFunc = getCallLoggerCallee(M);
  Value *valueAddr =
      ConstantInt::get(builder.getInt64Ty(), reinterpret_cast<uint64_t>(CI));
  Value *calleeName = builder.CreateGlobalStringPtr(callee->getName());
  Value *funcName = builder.CreateGlobalStringPtr(F.getName());
  Value *args[] = {funcName, calleeName, valueAddr};
  builder.CreateCall(callLogFunc, args);
}

static void insertFuncEndLoggerCall(Module &M, Function &F, Instruction *I) {
  assert(I);

  LLVMContext &Ctx = F.getContext();
  IRBuilder<> builder(Ctx);

  builder.SetInsertPoint(I);

  FunctionCallee funcEndLogFunc = getFuncEndLoggerCallee(M);
  Value *valueAddr =
      ConstantInt::get(builder.getInt64Ty(), reinterpret_cast<uint64_t>(I));
  Value *funcName = builder.CreateGlobalStringPtr(F.getName());
  Value *args[] = {funcName, valueAddr};
  builder.CreateCall(funcEndLogFunc, args);
}

static void insertBinOptLoggerCall(Module &M, Function &F, BinaryOperator *Op) {
  assert(Op);

  LLVMContext &Ctx = F.getContext();
  IRBuilder<> builder(Ctx);

  builder.SetInsertPoint(Op->getNextNode());

  FunctionCallee binOptLogFunc = getBinOptLoggerCallee(M);
  Value *valueAddr =
      ConstantInt::get(builder.getInt64Ty(), reinterpret_cast<uint64_t>(Op));
  Value *lhs = Op->getOperand(0);
  Value *rhs = Op->getOperand(1);
  Value *funcName = builder.CreateGlobalStringPtr(F.getName());
  Value *opName = builder.CreateGlobalStringPtr(Op->getOpcodeName());
  Value *args[] = {Op, lhs, rhs, opName, funcName, valueAddr};
  builder.CreateCall(binOptLogFunc, args);
}

static void insertCmpLoggerCall(Module &M, Function &F, CmpInst *Cmp) {
  assert(Cmp);

  LLVMContext &Ctx = F.getContext();
  IRBuilder<> builder(Ctx);

  builder.SetInsertPoint(Cmp->getNextNode());

  FunctionCallee cmpLogFunc = getCmpLoggerCallee(M);
  Value *valueAddr =
      ConstantInt::get(builder.getInt64Ty(), reinterpret_cast<uint64_t>(Cmp));
  Value *lhs = Cmp->getOperand(0);
  Value *rhs = Cmp->getOperand(1);
  Value *pred = ConstantInt::get(builder.getInt32Ty(), Cmp->getPredicate());
  Value *funcName = builder.CreateGlobalStringPtr(F.getName());
  Value *opName = builder.CreateGlobalStringPtr(Cmp->getOpcodeName());
  Value *args[] = {pred, lhs, rhs, opName, funcName, valueAddr};
  builder.CreateCall(cmpLogFunc, args);
}

static void insertBrLoggerCall(Module &M, Function &F, BranchInst *Br) {
  assert(Br);

  LLVMContext &Ctx = F.getContext();
  IRBuilder<> builder(Ctx);

  builder.SetInsertPoint(Br);

  FunctionCallee brLogFunc = getBrLoggerCallee(M);
  Value *valueAddr =
      ConstantInt::get(builder.getInt64Ty(), reinterpret_cast<uint64_t>(Br));
  Value *cond = Br->isConditional()
                    ? Br->getCondition()
                    : ConstantInt::get(builder.getInt32Ty(), -1);
  Value *funcName = builder.CreateGlobalStringPtr(F.getName());
  Value *opName = builder.CreateGlobalStringPtr(Br->getOpcodeName());
  Value *args[] = {funcName, opName, cond, valueAddr};
  builder.CreateCall(brLogFunc, args);
}

static void insertUnaryLoggerCall(Module &M, Function &F, Instruction *UI) {
  assert(UI);

  LLVMContext &Ctx = F.getContext();
  IRBuilder<> builder(Ctx);

  builder.SetInsertPoint(UI->getNextNode());

  FunctionCallee unaryLogFunc = getUnaryLoggerCallee(M);
  Value *valueAddr =
      ConstantInt::get(builder.getInt64Ty(), reinterpret_cast<uint64_t>(UI));
  Value *funcName = builder.CreateGlobalStringPtr(F.getName());
  Value *opName = builder.CreateGlobalStringPtr(UI->getOpcodeName());
  Value *args[] = {funcName, opName, valueAddr};
  builder.CreateCall(unaryLogFunc, args);
}

struct TracePass : public PassInfoMixin<TracePass> {
  PreservedAnalyses run(Module &M, ModuleAnalysisManager &AM) {
    for (auto &F : M) {
      if (isFuncLogger(F.getName()) || F.isDeclaration()) {
        continue;
      }

      insertFuncStartLoggerCall(M, F);

      for (auto &I : instructions(F)) {
        if (auto *Select = dyn_cast<SelectInst>(&I))
          insertUnaryLoggerCall(M, F, Select);

        if (auto *GetElemPtr = dyn_cast<GetElementPtrInst>(&I))
          insertUnaryLoggerCall(M, F, GetElemPtr);

        if (auto *UnOp = dyn_cast<UnaryInstruction>(&I))
          insertUnaryLoggerCall(M, F, UnOp);

        if (auto *Br = dyn_cast<BranchInst>(&I))
          insertBrLoggerCall(M, F, Br);

        if (auto *Cmp = dyn_cast<CmpInst>(&I))
          insertCmpLoggerCall(M, F, Cmp);

        if (auto *CI = dyn_cast<CallInst>(&I))
          insertCallLoggerCall(M, F, CI);

        if (auto *Ret = dyn_cast<ReturnInst>(&I))
          insertFuncEndLoggerCall(M, F, Ret);

        if (auto *Op = dyn_cast<BinaryOperator>(&I))
          insertBinOptLoggerCall(M, F, Op);
      }
    }
    return PreservedAnalyses::none();
  };
};

PassPluginLibraryInfo getPassPluginInfo() {
  const auto callback = [](PassBuilder &PB) {
    PB.registerPipelineStartEPCallback([&](ModulePassManager &MPM, auto) {
      MPM.addPass(TracePass{});
      return true;
    });
  };

  return {LLVM_PLUGIN_API_VERSION, "TracerPlugin", "0.0.1", callback};
};

/* When a plugin is loaded by the driver, it will call this entry point to
obtain information about this plugin and about how to register its passes.
*/
extern "C" LLVM_ATTRIBUTE_WEAK PassPluginLibraryInfo llvmGetPassPluginInfo() {
  return getPassPluginInfo();
}
