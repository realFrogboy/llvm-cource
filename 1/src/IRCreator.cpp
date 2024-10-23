#include "sim.h"

// #include "llvm/lib/ExecutionEngine/Interpreter/Interpreter.h"
#include "llvm/ADT/StringSwitch.h"
#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/ExecutionEngine/GenericValue.h"
#include "llvm/ExecutionEngine/Interpreter.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

static Constant *createCircleInstance(Module &M, StructType *CircleTy, int X,
                                      int Y, int XVelocity, int YVelocity,
                                      int Radius, int Color) {
  auto &C = M.getContext();
  IRBuilder<> Builder(C);

  auto *XConstInt = Builder.getInt32(static_cast<uint32_t>(X));
  auto *YConstInt = Builder.getInt32(static_cast<uint32_t>(Y));
  auto *XVConstInt = Builder.getInt32(static_cast<uint32_t>(XVelocity));
  auto *YVConstInt = Builder.getInt32(static_cast<uint32_t>(YVelocity));
  auto *RadiusConstInt = Builder.getInt32(static_cast<uint32_t>(Radius));
  auto *ColorConstInt = Builder.getInt32(static_cast<uint32_t>(Color));

  auto *Circle = ConstantStruct::get(CircleTy, {XConstInt, YConstInt,
                                                XVConstInt, YVConstInt,
                                                RadiusConstInt, ColorConstInt});
  return Circle;
}

static GlobalVariable *createCirclesArray(Module &M) {
  auto &C = M.getContext();
  IRBuilder<> Builder(C);

  auto *Int32Ty = Builder.getInt32Ty();
  auto *CircleTy = StructType::create(
      C, {Int32Ty, Int32Ty, Int32Ty, Int32Ty, Int32Ty, Int32Ty}, "Circle");

  auto *Circle0 =
      createCircleInstance(M, CircleTy, 480, 360, 1, 1, 100, -12799119);
  auto *Circle1 = createCircleInstance(M, CircleTy, 480, 360, 2, 3, 50, -23296);
  auto *Circle2 =
      createCircleInstance(M, CircleTy, 480, 360, -4, -1, 75, -9807155);
  auto *Circle3 =
      createCircleInstance(M, CircleTy, 480, 360, -3, 4, 25, -1146130);
  auto *Circle4 =
      createCircleInstance(M, CircleTy, 480, 360, -1, 3, 40, -47975);
  auto *Circle5 = createCircleInstance(M, CircleTy, 480, 360, 4, 5, 65, -9063);
  auto *Circle6 =
      createCircleInstance(M, CircleTy, 480, 360, -5, 3, 98, -16727297);
  auto *Circle7 =
      createCircleInstance(M, CircleTy, 480, 360, -4, -6, 32, -7673200);
  auto *Circle8 =
      createCircleInstance(M, CircleTy, 480, 360, -3, 2, 55, -1401718);
  auto *Circle9 =
      createCircleInstance(M, CircleTy, 480, 360, -2, 3, 77, -1172966);

  auto *CirclesTy = ArrayType::get(CircleTy, 10);
  auto *CirclesArray = ConstantArray::get(
      CirclesTy, {Circle0, Circle1, Circle2, Circle3, Circle4, Circle5, Circle6,
                  Circle7, Circle8, Circle9});
  auto *Circles = new GlobalVariable(
      M, CirclesTy, true, llvm::GlobalValue::LinkageTypes::PrivateLinkage,
      CirclesArray, "circles");
  Circles->setAlignment(llvm::Align(16));
  return Circles;
}

int main() {
  LLVMContext C;
  Module *M = new Module("app.c", C);

  auto *Circles = createCirclesArray(*M);

  IRBuilder<> Builder(C);

  FunctionType *simHandleEventsTy =
      FunctionType::get(Builder.getInt32Ty(), false);
  FunctionCallee simHandleEventsFunc =
      M->getOrInsertFunction("simHandleEvents", simHandleEventsTy);

  FunctionType *simFlushTy = FunctionType::get(Builder.getVoidTy(), false);
  FunctionCallee simFlushFunc = M->getOrInsertFunction("simFlush", simFlushTy);

  FunctionType *simFillScreenTy =
      FunctionType::get(Builder.getVoidTy(), {Builder.getInt32Ty()}, false);
  FunctionCallee simFillScreenFunc =
      M->getOrInsertFunction("simFillScreen", simFillScreenTy);

  FunctionType *simDrawCircleTy =
      FunctionType::get(Builder.getInt32Ty(), {Builder.getPtrTy()}, false);
  FunctionCallee simDrawCircleFunc =
      M->getOrInsertFunction("simDrawCircle", simDrawCircleTy);

  // define dso_local void @app() local_unnamed_addr #0 {
  auto *appFuncTy = FunctionType::get(Builder.getVoidTy(), false);
  auto *appFunc =
      Function::Create(appFuncTy, Function::ExternalLinkage, "app", M);

  // BasicBlocks:
  BasicBlock *BB0 = BasicBlock::Create(C, "", appFunc);
  BasicBlock *BB4 = BasicBlock::Create(C, "", appFunc);
  BasicBlock *BB7 = BasicBlock::Create(C, "", appFunc);
  BasicBlock *BB8 = BasicBlock::Create(C, "", appFunc);
  BasicBlock *BB11 = BasicBlock::Create(C, "", appFunc);
  BasicBlock *BB24 = BasicBlock::Create(C, "", appFunc);
  BasicBlock *BB26 = BasicBlock::Create(C, "", appFunc);
  BasicBlock *BB27 = BasicBlock::Create(C, "", appFunc);
  BasicBlock *BB37 = BasicBlock::Create(C, "", appFunc);
  BasicBlock *BB39 = BasicBlock::Create(C, "", appFunc);
  BasicBlock *BB40 = BasicBlock::Create(C, "", appFunc);
  BasicBlock *BB43 = BasicBlock::Create(C, "", appFunc);

  Builder.SetInsertPoint(BB0);

  auto *val1 = Builder.CreateAlloca(Circles->getValueType());
  val1->setAlignment(llvm::Align(16));

  Builder.CreateIntrinsic(Intrinsic::lifetime_start, {Builder.getPtrTy()},
                          {Builder.getInt64(240), val1});
  Builder.CreateIntrinsic(
      Intrinsic::memcpy,
      {Builder.getPtrTy(), Builder.getPtrTy(), Builder.getInt64Ty(),
       Builder.getInt1Ty()},
      {val1, Circles, Builder.getInt64(240), Builder.getFalse()});

  //  auto *val2IndirectCall =
  //  Builder.CreateIntToPtr(Builder.getInt64(reinterpret_cast<uint64_t>(&simHandleEvents)),
  //  Builder.getPtrTy()); auto *val2 = Builder.CreateCall(simHandleEventsTy,
  //  val2IndirectCall);
  auto *val2 = Builder.CreateCall(simHandleEventsFunc);

  auto *val3 = Builder.CreateICmpEQ(val2, Builder.getInt32(0));

  Builder.CreateCondBr(val3, BB7, BB43);

  Builder.SetInsertPoint(BB4);

  // auto *simFlushIndirectCall =
  // Builder.CreateIntToPtr(Builder.getInt64(reinterpret_cast<uint64_t>(&simFlush)),
  // Builder.getPtrTy()); Builder.CreateCall(simFlushTy, simFlushIndirectCall);
  Builder.CreateCall(simFlushFunc);

  //  auto *val5IndirectCall =
  //  Builder.CreateIntToPtr(Builder.getInt64(reinterpret_cast<uint64_t>(&simHandleEvents)),
  //  Builder.getPtrTy()); auto *val5 = Builder.CreateCall(simHandleEventsTy,
  //  val5IndirectCall);
  auto *val5 = Builder.CreateCall(simHandleEventsFunc);

  auto *val6 = Builder.CreateICmpEQ(val5, Builder.getInt32(0));

  Builder.CreateCondBr(val6, BB7, BB43);

  Builder.SetInsertPoint(BB7);

  //  auto *simFillScreenIndirectCall =
  //  Builder.CreateIntToPtr(Builder.getInt64(reinterpret_cast<uint64_t>(&simFillScreen)),
  //  Builder.getPtrTy()); Builder.CreateCall(simFillScreenTy,
  //  simFillScreenIndirectCall, {Builder.getInt32(-15198184)});
  Builder.CreateCall(simFillScreenFunc, {Builder.getInt32(-15198184)});

  Builder.CreateBr(BB11);

  /// START PHI NODE FORWARDING
  Builder.SetInsertPoint(BB11);

  auto *val12 = Builder.CreatePHI(Builder.getInt64Ty(), 2);
  /// END PHI NODE FORWARDING

  Builder.SetInsertPoint(BB8);

  auto *val9 = Builder.CreateAdd(val12, Builder.getInt64(1));

  val12->addIncoming(Builder.getInt64(0), BB7);
  val12->addIncoming(val9, BB8);

  auto *val10 = Builder.CreateICmpEQ(val9, Builder.getInt64(10));

  Builder.CreateCondBr(val10, BB4, BB11);

  Builder.SetInsertPoint(BB11);

  auto *val13 = Builder.CreateGEP(Circles->getValueType(), val1,
                                  {Builder.getInt64(0), val12});

  auto *val14 = Builder.CreateLoad(Builder.getInt32Ty(), val13);

  auto *val15 =
      Builder.CreateGEP(Circles->getValueType(), val1,
                        {Builder.getInt64(0), val12, Builder.getInt32(2)});

  auto *val16 = Builder.CreateLoad(Builder.getInt32Ty(), val15);

  auto *val17 = Builder.CreateAdd(val16, val14);

  auto *val18 =
      Builder.CreateGEP(Circles->getValueType(), val1,
                        {Builder.getInt64(0), val12, Builder.getInt32(4)});

  auto *val19 = Builder.CreateLoad(Builder.getInt32Ty(), val18);

  auto *val20 = Builder.CreateICmpSLT(val17, val19);

  auto *val21 = Builder.CreateAdd(val17, val19);

  auto *val22 = Builder.CreateICmpUGT(val21, Builder.getInt32(959));

  auto *val23 = Builder.CreateSelect(val20, Builder.getTrue(), val22);

  Builder.CreateCondBr(val23, BB24, BB26);

  Builder.SetInsertPoint(BB24);

  auto *val25 = Builder.CreateSub(Builder.getInt32(0), val16);

  Builder.CreateStore(val25, val15);

  Builder.CreateBr(BB27);

  Builder.SetInsertPoint(BB26);

  Builder.CreateStore(val17, val13);

  Builder.CreateBr(BB27);

  Builder.SetInsertPoint(BB27);

  auto *val28 =
      Builder.CreateGEP(Circles->getValueType(), val1,
                        {Builder.getInt64(0), val12, Builder.getInt32(1)});

  auto *val29 = Builder.CreateLoad(Builder.getInt32Ty(), val28);

  auto *val30 =
      Builder.CreateGEP(Circles->getValueType(), val1,
                        {Builder.getInt64(0), val12, Builder.getInt32(3)});

  auto *val31 = Builder.CreateLoad(Builder.getInt32Ty(), val30);

  auto *val32 = Builder.CreateAdd(val31, val29);

  auto *val33 = Builder.CreateICmpSLT(val32, val19);

  auto *val34 = Builder.CreateAdd(val32, val19);

  auto *val35 = Builder.CreateICmpUGT(val34, Builder.getInt32(719));

  auto *val36 = Builder.CreateSelect(val33, Builder.getTrue(), val35);

  Builder.CreateCondBr(val36, BB37, BB39);

  Builder.SetInsertPoint(BB37);

  auto *val38 = Builder.CreateSub(Builder.getInt32(0), val31);

  Builder.CreateStore(val38, val30);

  Builder.CreateBr(BB40);

  Builder.SetInsertPoint(BB39);

  Builder.CreateStore(val32, val28);

  Builder.CreateBr(BB40);

  Builder.SetInsertPoint(BB40);

  //  auto *simDrawCircleIndirectCall =
  //  Builder.CreateIntToPtr(Builder.getInt64(reinterpret_cast<uint64_t>(&simDrawCircle)),
  //  Builder.getPtrTy()); auto *val41 = Builder.CreateCall(simDrawCircleTy,
  //  simDrawCircleIndirectCall,  {val13});
  auto *val41 = Builder.CreateCall(simDrawCircleFunc, {val13});

  auto *val42 = Builder.CreateICmpEQ(val41, Builder.getInt32(0));

  Builder.CreateCondBr(val42, BB8, BB43);

  Builder.SetInsertPoint(BB43);

  Builder.CreateIntrinsic(Intrinsic::lifetime_end, {Builder.getPtrTy()},
                          {Builder.getInt64(240), val1});

  Builder.CreateRetVoid();

  M->print(outs(), nullptr);

  // LLVM IR Interpreter
  outs() << "[EE] Run\n";
  InitializeNativeTarget();
  InitializeNativeTargetAsmPrinter();
  InitializeNativeTargetAsmParser();
  LLVMLinkInInterpreter();

  if (Error Err = M->materializeAll()) {
    std::string Msg;
    handleAllErrors(std::move(Err),
                    [&](ErrorInfoBase &EIB) { Msg = EIB.message(); });
    printf("MSG:: %s\n", Msg.c_str());
  }

  std::string bla;
  ExecutionEngine *EE =
      EngineBuilder(std::unique_ptr<Module>(M)).setErrorStr(&bla).create();
  assert(EE);
  EE->InstallLazyFunctionCreator([&](const std::string &fnName) -> void * {
    void *FuncAddr =
        llvm::StringSwitch<void *>(fnName)
            .Case("simHandleEvents", reinterpret_cast<void *>(simHandleEvents))
            .Case("simFlush", reinterpret_cast<void *>(simFlush))
            .Case("simFillScreen", reinterpret_cast<void *>(simFillScreen))
            .Case("simDrawCircle", reinterpret_cast<void *>(simDrawCircle))
            .Default(nullptr);
    return FuncAddr;
  });
  EE->finalizeObject();

  simInit();

  ArrayRef<GenericValue> NoArgs;
  GenericValue V = EE->runFunction(appFunc, NoArgs);
  outs() << "[EE] Result: " << V.IntVal << "\n";

  simKill();
  return 0;
}
