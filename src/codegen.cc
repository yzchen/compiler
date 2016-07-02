#include "node.hh"
#include "tok.hh"
#include <iostream>
#include <cstring>
#include <vector>

// using namespace std;

Module *TheModule;      // top level structure
IRBuilder<> Builder(getGlobalContext());
std::vector<std::string> conflictName ;               // record the local name conflicted with global one

// isPointer : 0 -- no pointer        1 -- left pointer         2 -- right pointer

// VarType :  means var's type
//                      0 -- int       1 -- float       2 -- array         3 -- int *        4 -- float *        5 -- struct          6 -- struct *         7 -- struct arrauy
typedef struct attributes{
      double value;
      bool isConst;
      int isPointer;
      Value *VaV;
      int VarType;
}attributes ;

typedef struct ElementsAttr{
      std::string name;
      int VarType;
}ElementsAttr;

std::map<std::string, attributes> NamedValues;      // current local symbol table
std::map<std::string, attributes> ConstantList;         // store constant values

std::map<std::string, std::string> StructGList;              // map a global struct variable to a struct type
std::map<std::string, std::string> StructLList;              // map a local struct variable to a struct type
std::map<std::string, int> SizeStruct;                          // map a struct type to it's size
std::map<std::string, std::vector<ElementsAttr>> StructElements;               // store struct's elements

std::vector<BasicBlock *> breakOutBB;
std::vector<BasicBlock *> continueOutBB;

// FunctionPassManager *TheFPM;
static std::unique_ptr<legacy::FunctionPassManager> TheFPM;
// static std::unique_ptr<KaleidoscopeJIT> TheJIT;
static std::map<std::string, std::unique_ptr<ProtoNode>> FunctionProtos;

static AllocaInst *CreateEntryBlockAlloca(Function *TheFunction, const std::string &VarName) {
  // cout<<"done"<<endl;
  IRBuilder<> TmpB(&TheFunction->getEntryBlock(), TheFunction->getEntryBlock().begin());
  return TmpB.CreateAlloca(Type::getInt32Ty(getGlobalContext()), 0, VarName.c_str());
}

// Function *getFunction(std::string Name, std::vector<AllocaInst *> &OldBindings){
//   // First, see if the function has already been added to the current module.
//   if (auto *F = TheModule->getFunction(Name))
//     return F;

//   // If not, check whether we can codegen the declaration from some existing
//   // prototype.
//   auto FI = FunctionProtos.find(Name);
//   if (FI != FunctionProtos.end())
//     return FI->second->Codegen(OldBindings);

//   // If no existing prototype exists, return null.
//   return 0;
// }

// isConst = true : need a global constant value
// isConst = false : unconstant value is ok
double getGlobalValue(ExpNode *exp, bool isConst){
        if(exp->type == INTNUM || exp->type == FLOATNUM)
              return exp->value;
        else if(exp->type == VAR){
              if(ConstantList.count(*(dynamic_cast<VarNode *>(exp)->name)) > 0){
                      if( !ConstantList[*(dynamic_cast<VarNode *>(exp)->name)].isConst and isConst ){
                               ErrorV("can't assign a const with a variable in getGlobalValue");
                               exit(-1);
                      }
                      else{
                              return (double)ConstantList[*(dynamic_cast<VarNode *>(exp)->name)].value;
                      }
              }
              else{
                       Value *glov = ConstantList[ *(dynamic_cast<VarNode *>(exp)->name) ].VaV;
                        if(!glov){
                                ErrorV("no variable specified given");
                                exit(-1);
                        }
                        return ConstantList[ *(dynamic_cast<VarNode *>(exp)->name) ].value;
              }
        }
        else if(exp->type == BINARYEXP){
              switch (dynamic_cast<BinaryExpNode *>(exp)->op){
                      case '+' :    return getGlobalValue(dynamic_cast<BinaryExpNode *>(exp)->lhs, isConst) + getGlobalValue(dynamic_cast<BinaryExpNode *>(exp)->rhs, isConst);
                      case '-' :     return getGlobalValue(dynamic_cast<BinaryExpNode *>(exp)->lhs, isConst) - getGlobalValue(dynamic_cast<BinaryExpNode *>(exp)->rhs, isConst);
                      case '*' :    return getGlobalValue(dynamic_cast<BinaryExpNode *>(exp)->lhs, isConst) * getGlobalValue(dynamic_cast<BinaryExpNode *>(exp)->rhs, isConst);
                      case '/' :     return getGlobalValue(dynamic_cast<BinaryExpNode *>(exp)->lhs, isConst) / getGlobalValue(dynamic_cast<BinaryExpNode *>(exp)->rhs, isConst);
                      case '%' :   return (int)getGlobalValue(dynamic_cast<BinaryExpNode *>(exp)->lhs, isConst) % (int)getGlobalValue(dynamic_cast<BinaryExpNode *>(exp)->rhs, isConst);
        }
      }
      else if(exp->type == UNARYEXP){
            if((dynamic_cast<BinaryExpNode *>(exp))->op == '-')
                    return 0 - getGlobalValue(dynamic_cast<UnaryExpNode *>(exp)->operand, isConst);
            return getGlobalValue(dynamic_cast<UnaryExpNode *>(exp)->operand, isConst);
      }
      return 0;
}

// isConst = true : need a local constant value
// isConst = false : unconstant value is ok
// local means variable call this is local
double getLocalValue(ExpNode *exp, bool isConst){
        if(exp->type == INTNUM )
              return exp->value;
        else if(exp->type == VAR){
              if(NamedValues.count(*(dynamic_cast<VarNode *>(exp)->name)) > 0){
                      if( !NamedValues[*(dynamic_cast<VarNode *>(exp)->name)].isConst and isConst ){
                               ErrorV("can't assign a const with a variable in getLocalValue");
                               exit(-1);
                      }
                      else{
                              return (double)NamedValues[*(dynamic_cast<VarNode *>(exp)->name)].value;
                      }
              }
              else{
                      if(ConstantList.count(*(dynamic_cast<VarNode *>(exp)->name)) > 0){
                               if( !ConstantList[*(dynamic_cast<VarNode *>(exp)->name)].isConst and isConst ){
                                         ErrorV("can't assign a const with a variable in getLocalValue");
                                         exit(-1);
                                }
                                else{
                                        // printf("%d\n", ConstantList[*(dynamic_cast<VarNode *>(exp)->name)].value);
                                        return (double)ConstantList[*(dynamic_cast<VarNode *>(exp)->name)].value;
                                }
                              }
                              else{
                                         Value *glov = ConstantList[ *(dynamic_cast<VarNode *>(exp)->name) ].VaV;
                                          if(!glov){
                                                  ErrorV("no variable specified given");
                                                  exit(-1);
                                          }
                                          return ConstantList[ *(dynamic_cast<VarNode *>(exp)->name) ].value;
                        }
              }
        }
        else if(exp->type == BINARYEXP){
              switch (dynamic_cast<BinaryExpNode *>(exp)->op){
                      case '+' :    return getLocalValue(dynamic_cast<BinaryExpNode *>(exp)->lhs, isConst) + getLocalValue(dynamic_cast<BinaryExpNode *>(exp)->rhs, isConst);
                      case '-' :     return getLocalValue(dynamic_cast<BinaryExpNode *>(exp)->lhs, isConst) - getLocalValue(dynamic_cast<BinaryExpNode *>(exp)->rhs, isConst);
                      case '*' :    return getLocalValue(dynamic_cast<BinaryExpNode *>(exp)->lhs, isConst) * getLocalValue(dynamic_cast<BinaryExpNode *>(exp)->rhs, isConst);
                      case '/' :     return getLocalValue(dynamic_cast<BinaryExpNode *>(exp)->lhs, isConst) / getLocalValue(dynamic_cast<BinaryExpNode *>(exp)->rhs, isConst);
                      case '%' :   return (int)getLocalValue(dynamic_cast<BinaryExpNode *>(exp)->lhs, isConst) % (int)getLocalValue(dynamic_cast<BinaryExpNode *>(exp)->rhs, isConst);
        }
      }
      else if(exp->type == UNARYEXP){
            if((dynamic_cast<BinaryExpNode *>(exp))->op == '-')
                    return 0 - getLocalValue(dynamic_cast<UnaryExpNode *>(exp)->operand, isConst);
            return getLocalValue(dynamic_cast<UnaryExpNode *>(exp)->operand, isConst);
      }
      return 0;
}

// generate this function for memory copying in struct assign
Function *getMemCpyFunc(){
               PointerType* PointerTy_4 = Type::getInt8PtrTy(getGlobalContext());

               std::vector<Type *>FuncTy_6_args;
               FuncTy_6_args.push_back(PointerTy_4);
               FuncTy_6_args.push_back(PointerTy_4);
               FuncTy_6_args.push_back(Type::getInt64Ty(getGlobalContext()));
               FuncTy_6_args.push_back(Type::getInt32Ty(getGlobalContext()));
               FuncTy_6_args.push_back(Type::getInt1Ty(getGlobalContext()));
               FunctionType* FuncTy_6 = FunctionType::get(Type::getVoidTy(getGlobalContext()), FuncTy_6_args, false);

               Function* func_llvm_memcpy_p0i8_p0i8_i64 = TheModule->getFunction("llvmmemcpy");
               if (!func_llvm_memcpy_p0i8_p0i8_i64) {
                             func_llvm_memcpy_p0i8_p0i8_i64 = Function::Create(FuncTy_6, GlobalValue::ExternalLinkage, "llvmmemcpy");            // (external, no body)
                             func_llvm_memcpy_p0i8_p0i8_i64->setCallingConv(CallingConv::C);
               }

               AttributeSet func_llvm_memcpy_p0i8_p0i8_i64_PAL;
               SmallVector<AttributeSet, 4> Attrs;
               AttributeSet PAS;
               AttrBuilder PAS_B1;
               PAS_B1.addAttribute(Attribute::NoCapture);
               PAS = AttributeSet::get(getGlobalContext(), 1U, PAS_B1);

                Attrs.push_back(PAS);
                 AttrBuilder PAS_B2;
                 PAS_B2.addAttribute(Attribute::ReadOnly);
                 PAS_B2.addAttribute(Attribute::NoCapture);
                 PAS = AttributeSet::get(getGlobalContext(), 2U, PAS_B2);

               Attrs.push_back(PAS);
                AttrBuilder PAS_B3;
                PAS_B3.addAttribute(Attribute::NoUnwind);
                PAS = AttributeSet::get(getGlobalContext(), ~0U, PAS_B3);

              Attrs.push_back(PAS);
              func_llvm_memcpy_p0i8_p0i8_i64_PAL = AttributeSet::get(getGlobalContext(), Attrs);
              func_llvm_memcpy_p0i8_p0i8_i64->setAttributes(func_llvm_memcpy_p0i8_p0i8_i64_PAL);
              return func_llvm_memcpy_p0i8_p0i8_i64;
}

// getConstantV(typeindex, tmpExp, totalsize) , only used in StructassignNode::Codegen, fetch a Constant Value for an element of a struct
Constant *getConstantV(int typeindex, ExpNode *tmpExp, int &totalsize){
        Constant *expV;
        if(tmpExp->VarType < 3 ){         // assign for unpointer(judged by tmpExp)
                  double Val = getLocalValue(tmpExp, false);
                  if(tmpExp->VarType == 0){
                            expV = ConstantInt::get(Type::getInt32Ty(getGlobalContext()), (int)Val, true);
                            if(typeindex == 3){
                                      expV = (Constant *)Builder.CreateUIToFP(expV, Type::getDoubleTy(getGlobalContext()), "tmp");
                                      totalsize += 8;
                           }
                           else if(typeindex == 14 && Val == 0){                  // this is a pointer but initialize it as a 0(null)
                                      totalsize += 8;
                                      return 0;
                           }
                           else if(typeindex != 10){
                                      ErrorV("invalid type in struct.");
                                      exit(-1);
                           }
                            // printf("This is a int.\n");
                            totalsize += 4;
                  }
                  else if(tmpExp->VarType == 1){
                            if(typeindex != 3){
                                      ErrorV("invalid type in struct.");
                                      exit(-1);
                            }
                            expV = ConstantFP::get(Type::getDoubleTy(getGlobalContext()), Val);
                            // printf("This is a float.\n");
                            totalsize += 8;
                  }
        }
        else{                   // assign for pointer element
                  if(tmpExp->type != VAR){
                             ErrorV("not correctly RVlaue.");
                             exit(-1);
                  }
                  VarNode *tmpVar = dynamic_cast<VarNode *>(tmpExp);
                  if(tmpExp->VarType == 3){                       // pointer int
                              if(typeindex != 14){
                                       ErrorV("invalid type in struct.");
                                       exit(-1);
                              }
                              if(NamedValues.count(tmpVar->name->c_str()) > 0){
                                         if(NamedValues[ tmpVar->name->c_str() ].VarType != 3){
                                                  ErrorV("left and right anr not same type.");
                                                  exit(-1);
                                         }
                                         expV = (Constant *)NamedValues[ tmpVar->name->c_str() ].VaV;
                              }
                              else if(ConstantList.count(tmpVar->name->c_str()) > 0){
                                         if(NamedValues[ tmpVar->name->c_str() ].VarType != 3){
                                                  ErrorV("left and right anr not same type.");
                                                  exit(-1);
                                         }
                                          expV = (Constant *)ConstantList[ tmpVar->name->c_str() ].VaV;
                                          totalsize += 8;
                              }
                              else{
                                          ErrorV("no such variable.");
                                          exit(-1);
                              }
                  }
                  else if(tmpExp->VarType == 4){            // pointer double
                              if(typeindex != 14){
                                       ErrorV("invalid type in struct.");
                                       exit(-1);
                              }
                              if(NamedValues.count(tmpVar->name->c_str()) > 0){
                                         if(NamedValues[ tmpVar->name->c_str() ].VarType != 4){
                                                  ErrorV("left and right anr not same type.");
                                                  exit(-1);
                                         }
                                         expV = (Constant *)NamedValues[ tmpVar->name->c_str() ].VaV;
                              }
                              else if(ConstantList.count(tmpVar->name->c_str()) > 0){
                                         if(NamedValues[ tmpVar->name->c_str() ].VarType != 4){
                                                  ErrorV("left and right anr not same type.");
                                                  exit(-1);
                                         }
                                          expV = (Constant *)ConstantList[ tmpVar->name->c_str() ].VaV;
                                          totalsize += 8;
                              }
                              else{
                                          ErrorV("no such variable.");
                                          exit(-1);
                              }
                  }
                // else if(tmpExp->VarType == 5)
        }
        return expV;
}

// given a name, find a allocaints for it
Value *LookupTable(std::string *name, int &isGlobal){
      Value *ValueV;
      // printf("%s\n",name->c_str());
      if(NamedValues.count(*(name)) > 0){
               ValueV = (AllocaInst *)NamedValues[*(name)].VaV;
               isGlobal = 0;
      }
      else if(ConstantList.count(*(name)) > 0){
               ValueV = (AllocaInst *)ConstantList[*(name)].VaV;
               isGlobal = 1;
      }
      else {
              ValueV = TheModule->getNamedValue(name->c_str());
              if(!ValueV){
                      ErrorV("no such variable in Symbal Table.");
                      exit(-1);
              }
      }
      return ValueV;
}


Value *BlockItemListNode::Codegen(std::vector<AllocaInst *> &OldBindings, bool isConst){
      // printf("blockitemlist begin\n");
      // printf("%d\n", v.size());
      for (int i = 0; i < v.size(); i++){
          // printf("item\n");
          // cout<<(*itv)->type<<endl;
          if( v[i] ){
                  v[i]->Codegen(OldBindings);
                  // TheModule->dump();
                  // printf("%d\n", v[i]->type);
                  // printf("done\n");
          }
          // last->dump();
      }

      // int e = conflictName.size();
      // for(int i = 0; i < e; i++){
      //         std::string name = conflictName.back() ;
      //         // printf("%s\n", name.c_str());
      //         conflictName.pop_back();
      //         NamedValues[ name ].VaV = OldBindings.back() ;
      //         OldBindings.pop_back();
      // }
      // OldBindings.clear();

      return 0;
}

Value *BlockNode::Codegen(std::vector<AllocaInst *> &OldBindings , bool isConst){
      // printf("block begin\n");
      return blockitemlist->Codegen(OldBindings);
}


Value *VarNode::Codegen(std::vector<AllocaInst *> &OldBindings , bool isConst) {
    // Look this variable up in the function.
    Value *V;
    if(NamedValues.count(name->c_str()) > 0){
             V = NamedValues[*name].VaV;
             return Builder.CreateLoad(V, name->c_str());
    }
    else {
        GlobalValue *GV = TheModule->getNamedValue(name->c_str());
        if( !GV )
            return ErrorV("Unknown variable name");
        else{
            return Builder.CreateLoad(GV , name->c_str());
        }
     }
}


Value *CompUnitNode::Codegen(std::vector<AllocaInst *> &OldBindings , bool isConst){
        for (std::vector<Node *>::iterator itv = v.begin(); itv !=v.end();++itv){
                  if( *(itv) ){
                              // printf("%d\n", (*itv)->type);
                              (*itv)->Codegen(OldBindings);
                              // printf("done with a node \n");
                              // last->dump();
                              // TheModule->dump();
                  }
        }
        return 0 ;
}

// this is only for extern, the other simpledecl is in args
Value *SimpleDeclNode::Codegen(std::vector<AllocaInst *> &OldBindings , bool isConst){
        var->VarType = VarType;
        // printf("%d\n", var->VarType);
        Type *Assigntype;
        if(VarType == 0)
                    Assigntype =  Type::getInt32Ty(getGlobalContext());
        else if(VarType == 1)
                    Assigntype =  Type::getDoubleTy(getGlobalContext());
        else if(VarType == 3)
                    Assigntype =  Type::getInt32PtrTy(getGlobalContext());
        else if(VarType == 4)
                    Assigntype =  Type::getDoublePtrTy(getGlobalContext());
        // else if(VarType == 5){
        //             StructType *StructTyA = TheModule->getTypeByName(structvar->name->c_str());
        //             Assigntype = PointerType::get(StructTyA, 0);
        // }

        return new GlobalVariable(*TheModule, Assigntype, false, GlobalValue::ExternalLinkage, 0, var->name->c_str());
}

// has generated in ProtoNode
Value *ArgsNode::Codegen(std::vector<AllocaInst *> &OldBindings , bool isConst){
        return 0;
}

Value *ExternNode::Codegen(std::vector<AllocaInst *> &OldBindings , bool isConst){
     return exte->Codegen(OldBindings, isConst);
}

void ProtoNode::CreateArgumentAllocas(Function *F) {
        Function::arg_iterator AI = F->arg_begin();
        for (unsigned Idx = 0, e = Args->v.size(); Idx != e; ++Idx, ++AI) {
                // Create an alloca for this variable.
                // AllocaInst *Alloca = CreateEntryBlockAlloca(F, *(Args->v[Idx]->var->name));
                int argType = Args->v[Idx]->VarType;
                Type *ArgType;
                // printf("%d\n",argType );
                switch(argType){
                          case 0 : ArgType = Type::getInt32Ty(getGlobalContext()); ;break;
                          case 1 : ArgType = Type::getDoubleTy(getGlobalContext()); ;break;
                          case 3 : ArgType = Type::getInt32PtrTy(getGlobalContext());  ;break;
                          case 4 : ArgType = Type::getDoublePtrTy(getGlobalContext());  ;break;
                          case 5 : {
                                        // printf("reached\n");
                                        StructType *StructTyA = TheModule->getTypeByName(Args->v[Idx]->structvar->name->c_str());
                                        ArgType = PointerType::get(StructTyA, 0);
                                        break;
                                      }
                          default : ErrorV("type is not correct for struct element.");break;
                }

                AllocaInst *Alloca = Builder.CreateAlloca(ArgType, 0, Args->v[Idx]->var->name->c_str());
                // Store the initial value into the alloca.
                Builder.CreateStore(AI, Alloca);

                // Add arguments to variable symbol table.
                NamedValues[*(Args->v[Idx]->var->name)].VaV = Alloca;
                NamedValues[*(Args->v[Idx]->var->name)].VarType = argType;
                NamedValues[*(Args->v[Idx]->var->name)].isConst = false;
        }
        return 0;
}


Function *ProtoNode::Codegen(std::vector<AllocaInst *> &OldBindings , bool isConst) {
     // Make the function type:  int(int, int) etc.
     std::vector<Type*> Ints;
     // printf("%lu\n", Args->v.size());
     // printf("%lu\n", Ints.size());
     for (int i = 0; i < Args->v.size(); ++i){
            int argType = Args->v[i]->VarType;
            Type *ArgType;
            // printf("%d\n",argType );
            switch(argType){
                      case 0 : ArgType = Type::getInt32Ty(getGlobalContext());  ;break;
                      case 1 : ArgType = Type::getDoubleTy(getGlobalContext()); ;break;
                      case 3 : ArgType = Type::getInt32PtrTy(getGlobalContext());  ;break;
                      case 4 : ArgType = Type::getDoublePtrTy(getGlobalContext());  ;break;
                      case 5 : {
                                    // printf("reached\n");
                                    StructType *StructTyA = TheModule->getTypeByName(Args->v[i]->structvar->name->c_str());
                                    ArgType = PointerType::get(StructTyA, 0);
                                    break;
                                  }
                      default : ErrorV("type is not correct for struct element.");break;
            }
            // printf("%s\n", Args->v[i]->var->name->c_str());
            Ints.push_back(ArgType);
     }
     // printf("%lu\n", Ints.size());

     Type *Ret_Type;
     if (ret == "void")
        Ret_Type = Type::getVoidTy(getGlobalContext());
     else if(ret == "int")
        Ret_Type = Type::getInt32Ty(getGlobalContext());
     else if(ret == "float")
        Ret_Type = Type::getDoubleTy(getGlobalContext());
     else if(ret == "int *")
        Ret_Type = Type::getInt32PtrTy(getGlobalContext());
     else if(ret == "float *")
        Ret_Type = Type::getDoublePtrTy(getGlobalContext());


    // printf("before FunctionType\n");
    FunctionType *FT = FunctionType::get(Ret_Type , Ints , false);
    // printf("FunctionType\n");

    Function *F = Function::Create(FT, Function::ExternalLinkage, var->name->c_str(), TheModule);
    // TheModule->dump();
    // If F conflicted, there was already something named 'Name'.  If it has a
    // body, don't allow redefinition or reextern.
    if (F->getName() != *(var->name)) {
          // Delete the one we just made and get the existing one.
          F->eraseFromParent();
          F = TheModule->getFunction(*(var->name));
          // If F already has a body, reject this.
          if (!F->empty()) {
            ErrorV("redefinition of function");
            exit(-1);
          }

          // If F took a different number of args, reject.
          if ( F->arg_size() != Args->v.size()) {
            ErrorV("redefinition of function with different # args");
            exit(-1);
          }
    }

    // Set names for all arguments.
    unsigned Idx = 0;
    // printf("%d\n", Args->v.size());
    // for (int i = 0; i < Args->v.size(); ++i){
    //     printf("%s\n", Args->v[i]->name->c_str());
    // }
    for (Function::arg_iterator AI = F->arg_begin(); Idx != Args->v.size();++AI, ++Idx){
        // printf("args in Args : %s\n", Args->v[Idx]->var->name->c_str());
        AI->setName(Args->v[Idx]->var->name->c_str());
        // printf("args in F : %s\n", AI->getName());
        // printf("after setname proto\n");
    }
    // printf("done with proto\n");
    return F;
    // return 0;
}


Function *FuncDefNode::Codegen(std::vector<AllocaInst *> &OldBindings , bool isConst) {
      globalflag = false;

      NamedValues.clear();
      StructLList.clear();

      Function *TheFunction = proto->Codegen(OldBindings);

      // TheModule->dump();
      BasicBlock *BB = BasicBlock::Create(getGlobalContext(), "entry", TheFunction);
      // BasicBlock *EndBB = BasicBlock::Create(getGlobalContext(), "end");
      Builder.SetInsertPoint(BB);
      // printf("here\n");
      proto->CreateArgumentAllocas(TheFunction);
      // TheModule->dump();
      // AllocaInst *retVal = CreateEntryBlockAlloca(TheFunction, "retVal");
      // NamedValues["retVal"].VaV = retVal;
      // NamedValues["retVal"].isConst = false;
      // Builder.CreateStore(ConstantInt::get(Type::getInt32Ty(getGlobalContext()) , 0 , true), retVal);
      block->Codegen(OldBindings);
      // Finish off the function.
      // TheFunction->getBasicBlockList().push_back(EndBB);
      if(proto->ret == "void")
              Builder.CreateRetVoid();
      // else{
      //         // TheModule->dump();
      //         AllocaInst *RetV = NamedValues["retVal"].VaV;
      //         Value *Ret = Builder.CreateLoad(RetV);
      //        // ConstantInt *retVal = ConstantInt::get(Type::getInt32Ty(getGlobalContext()), 0, true);
      //         Builder.CreateRet(Ret);
      //         // TheModule->dump();
      // }
      // printf("Finish\n");

      // Validate the generated code, checking for consistency.
      verifyFunction(*TheFunction);
      // printf("done with function\n");
      globalflag = true;
      return TheFunction;
}


Value *RetNode::Codegen(std::vector<AllocaInst *> &OldBindings , bool isConst){
      Function *TheFunction = Builder.GetInsertBlock()->getParent();
      if(TheFunction->getReturnType() == Type::getVoidTy(getGlobalContext())){
            ErrorV("void function has no return value");
            exit(-1);
      }
      Value *retValueV = exp->Codegen(OldBindings);
       // AllocaInst *RetV = NamedValues["retVal"].VaV;
       // Value *Ret = Builder.CreateLoad(RetV);
      // Builder.CreateStore(retValueV, RetV);
      // printf("done\n");
      // TheModule->dump();
      Builder.CreateRet(retValueV);
      // TheModule->dump();
      return retValueV;
}


Value *BreakNode::Codegen(std::vector<AllocaInst *> &OldBindings, bool isConst){
      Function *TheFunction = Builder.GetInsertBlock()->getParent();
      BasicBlock *BB = breakOutBB.back();
      if(BB){
              Builder.CreateBr(BB);
      }
      else{
        ErrorV("no right block");
        exit(-1);
      }
     BasicBlock *anonyBB = BasicBlock::Create(getGlobalContext(), "after_break", TheFunction);
     Builder.SetInsertPoint(anonyBB);
      return 0;
}


Value *ContinueNode::Codegen(std::vector<AllocaInst *> &OldBindings, bool isConst){
      Function *TheFunction = Builder.GetInsertBlock()->getParent();
      BasicBlock *BB = continueOutBB.back();
      if(BB){
              Builder.CreateBr(BB);
      }
      else{
        ErrorV("no right block");
        exit(-1);
      }
     BasicBlock *anonyBB = BasicBlock::Create(getGlobalContext(), "after_break", TheFunction);
     Builder.SetInsertPoint(anonyBB);
      return 0;
}


Value *ConstDefNode::Codegen(std::vector<AllocaInst *> &OldBindings , bool isConst){
      Value *last;
      for (std::vector<ANode *>::iterator itv = v.begin(); itv != v.end(); itv++){
              (*itv)->VarType = VarType;
              last = (*itv)->Codegen(OldBindings, true);
              if( !last )
                     return 0;
      }
      return last;
}


Value *ConstDeclNode::Codegen(std::vector<AllocaInst *> &OldBindings , bool isConst){
      constdef->VarType = VarType;
      Value *ConstV = constdef->Codegen(OldBindings, true);
      return ConstV;
}


Value *ExppNode::Codegen(std::vector<AllocaInst *> &OldBindings , bool isConst){
    for (std::vector<ExpNode *>::iterator itv = v.begin(); itv != v.end(); itv++){
        (*itv)->Codegen(OldBindings);
    }
}

//  only varlist and const declare will generate new variables
Value *VarListNode::Codegen(std::vector<AllocaInst *> &OldBindings , bool isConst){
      for (std::vector<ExpNode *>::iterator itv = v.begin(); itv != v.end(); itv++ ){
              (*itv)->VarType = VarType;
              (*itv)->Codegen(OldBindings);
        }
      return 0;
}


Value *VarDeclNode::Codegen(std::vector<AllocaInst *> &OldBindings , bool isConst){
        varlist->VarType = VarType;
        Value *VarDefV = varlist->Codegen(OldBindings);
        return VarDefV;
}

Value *IdentListNode::Codegen(std::vector<AllocaInst *> &OldBindings , bool isConst){
  return 0;
}

Value *InnerStructDeclNode::Codegen(std::vector<AllocaInst *> &OldBindings, bool isConst){
  return 0;
}

// create a struct type
Value *StructNode::Codegen(std::vector<AllocaInst *> &OldBindings, bool isConst){
            StructType *StructTyA = TheModule->getTypeByName(var->name->c_str());
            if (!StructTyA) {
                        StructTyA = StructType::create(getGlobalContext(), var->name->c_str());
            }
            std::vector<Type *>StructTyA_fields;
            // printf("over\n");
            Type *StructVType;
            // printf("%lu\n",innerstructdecl->v.size() );
            SizeStruct[*(var->name)] = innerstructdecl->v.size();                           // store the number of elements in SizeStruct
            for (int i = 0; i < innerstructdecl->v.size(); ++i){
                      // printf("%s\n", var->name->c_str());
                      // printf("%d\n", innerstructdecl->v[i]->VarType);
                      // if(innerstructdecl->v[i]->VarType != 5)
                             StructElements[*(var->name)].push_back( {*(innerstructdecl->v[i]->var->name), innerstructdecl->v[i]->VarType} );
                      // else
                      //        StructElements[*(var->name)].push_back(*(innerstructdecl->v[i]->var->name));

                      // printf("%s\n", innerstructdecl->v[i]->var->name->c_str());
                      switch(innerstructdecl->v[i]->VarType){
                                case 0 : StructVType = Type::getInt32Ty(getGlobalContext());break;
                                case 1 : StructVType = Type::getDoubleTy(getGlobalContext());break;
                                case 3 : StructVType = Type::getInt32PtrTy(getGlobalContext());break;
                                case 4 : StructVType = Type::getDoublePtrTy(getGlobalContext());break;
                                case 5 : {
                                              // printf("reached\n");
                                              StructType *StructTyA = TheModule->getTypeByName(innerstructdecl->v[i]->structvar->name->c_str());
                                              StructVType = PointerType::get(StructTyA, 0);
                                              break;
                                            }
                                default : ErrorV("type is not correct for struct element.");break;
                      }
                      // printf("push back\n");
                      StructTyA_fields.push_back(StructVType);
            }
            // printf("%lu\n", StructElements[*(var->name)].size());
             if (StructTyA->isOpaque()) {
                      // printf("is Opaque\n");
                      // GlobalVariable *Alloca = new GlobalVariable(*TheModule, StructTyA, false, GlobalValue::ExternalLinkage,0, var->name->c_str());
                      StructTyA->setBody(StructTyA_fields);
                      // TheModule->dump();
                      // return Alloca;
                      return 0;
              }
              return 0;
}

Value *FuncCallNode::Codegen(std::vector<AllocaInst *> &OldBindings , bool isConst) {
    // Look up the name in the global module table.
    Function *CalleeF = TheModule->getFunction(*(var->name));
    if (CalleeF == 0){
        ErrorV("Unknown function referenced");
        exit(-1);
    }
    // TheModule->dump();
    // If argument mismatch error.
    // printf("%d\n", identlist->v.size());
    if (CalleeF->arg_size() != identlist->v.size()){
        ErrorV("Incorrect # arguments passed");
        exit(-1);
    }

    std::vector<Value *> ArgsV;
    // printf("%d\n", identlist->v.size());
    // for (int i = 0; i < identlist->v.size(); ++i){
    //   printf("%s\n", identlist->v[i]->name->c_str());
    // }
    for (unsigned i = 0, e = identlist->v.size(); i != e; ++i) {
          // printf("%s\n", identlist->v[i]->name->c_str());
          if(identlist->v[i]->type == VAR){
                    Value *VarV = NamedValues[ (dynamic_cast<VarNode *>(identlist->v[i]))->name->c_str() ].VaV;
                    ArgsV.push_back(new LoadInst( VarV, (dynamic_cast<VarNode *>(identlist->v[i]))->name->c_str(), false, Builder.GetInsertBlock()));
          }
          else{
                    ConstantInt *constnum = ConstantInt::get(Type::getInt32Ty(getGlobalContext()), (dynamic_cast<IntNumNode *>(identlist->v[i]))->val, true);
                    ArgsV.push_back((Value *)constnum);
          }
          if (ArgsV.back() == 0)
              return 0;
    }
    // printf("%d\n", ArgsV.size());
    // for (int i = 0; i < ArgsV.size(); ++i){
    //       printf("%s\n", ArgsV[i]->getName());
    // }
    ArrayRef<Value *> args(ArgsV);
    // TheModule->dump();
    if(CalleeF->getReturnType() == Type::getVoidTy(getGlobalContext())){
             return Builder.CreateCall(CalleeF, args);
    }
    else
            return  Builder.CreateCall(CalleeF, args, "call");
}

// whole assign to a struct variable not assign a single element of a struct
Value *StructAssignNode::Codegen(std::vector<AllocaInst *> &OldBindings , bool isConst){
      // printf("done\n");
      StructType *StructTyA;
      bool hasinitflag = false;
      if(expp)
              hasinitflag = true;

      if(!globalflag){                // local struct variable
               AllocaInst *ptrVvar;
               if(Ty == DECLASSIGN){            // decl struct assign
                        StructTyA = TheModule->getTypeByName(structvar->name->c_str());           // if decl a struct variable, first look up global table for a struct type
                        if(!StructTyA){
                                 ErrorV("no such struct type.");
                                 exit(-1);
                        }
                        ptrVvar = Builder.CreateAlloca(StructTyA, 0, var->name->c_str());
                        // printf("%s\n",var->name->c_str() );
                        NamedValues[ *(var->name) ].VaV = ptrVvar;
                        // NamedValues[ *(var->name) ].isPointer = isPointer;
                        NamedValues[ *(var->name) ].VarType = 5;

                        StructLList[*(var->name)] = *(structvar->name);                // map a struct variable to a struct type
                        if(!hasinitflag)              // no initializer , done
                                return 0;
                        else{                             // has initializer, do nothing, initialization is below
                        }
               }
               else if(Ty == STMTASSIGN){             // assign all once
                        if(!hasinitflag){
                                    ErrorV("no RValue for struct but need it.");
                                    exit(-1);
                        }

                        // printf("this is in local stmt assign.\n");
                        //  LValue
                        if(NamedValues.count(var->name->c_str()) > 0){
                                    if(NamedValues[var->name->c_str()].VarType != 5){
                                                ErrorV("LValue is not struct.");
                                                exit(-1);
                                    }
                                    ptrVvar = (AllocaInst *)NamedValues[ var->name->c_str() ].VaV;
                        }
                        else if(ConstantList.count(var->name->c_str()) > 0){
                                   if(ConstantList[var->name->c_str()].VarType != 5){
                                                ErrorV("LValue is not struct.");
                                                exit(-1);
                                    }
                                    ptrVvar = (AllocaInst *)ConstantList[ var->name->c_str() ].VaV;
                        }
                        else{
                                    ErrorV("no such struct variable.");
                                    exit(-1);
                        }
                        // RValue
                        StructTyA = TheModule->getTypeByName(StructLList[*(var->name)].c_str());
                        // if(!StructTyA)
                        //        StructTyA = TheModule->getTypeByName(StructGList[*(var->name)].c_str());
               }

               // this segment can be achived by DECLASSIGN(hasinitflag) and STMTASSIGN
              int vsize = SizeStruct[StructLList[*(var->name)]];                 // get size of struct type
              // if(!vsize)
              //           vsize = SizeStruct[StructGList[*(var->name)]];
              // printf("%d\n", vsize);
              if(expp->v.size() > vsize){
                            ErrorV("too many initializers for struct.");
                            exit(-1);
              }
              else if(expp->v.size() < vsize){
                            ErrorV("too llittle initializers for struct.");
                            exit(-1);
              }

              // printf("%lu\n", expp->v.size());
              std::vector<Constant *> ListExppV;
              int totalsize = 0;                              // record the number of bytes the struct used
              for (int i = 0; i < expp->v.size(); ++i){
                            // printf("go on\n");
                            ExpNode *tmpExp = expp->v[i];
                            int typeindex = StructTyA->getTypeAtIndex(i)->getTypeID();
                            Constant *expV = getConstantV(typeindex, tmpExp, totalsize);
                            if(!expV){
                                    // printf("%d\n", i);
                                    int localType = StructElements[StructLList[*(var->name)]][i].VarType;
                                    PointerType *pTy;
                                    if(localType == 3){
                                            // printf("int null\n");
                                            pTy = Type::getInt32PtrTy(getGlobalContext());
                                    }
                                    else if(localType == 4)
                                            pTy = Type::getDoublePtrTy(getGlobalContext());
                                     else{
                                            pTy = PointerType::get(StructTyA, 0);
                                     }
                                     // printf("null\n");
                                     expV = ConstantPointerNull::get(pTy);
                            }
                            // printf("null or \n");
                            ListExppV.push_back(expV);
                            // printf("null and \n");
              }
              // printf("%d\n", totalsize);
              Constant *constListExppV = ConstantStruct::get(StructTyA, ListExppV);
              // printf("constListExppV\n");
              GlobalVariable *glStruct = new GlobalVariable(*TheModule, StructTyA, true, GlobalValue::PrivateLinkage, 0, "");
               // printf("glStruct\n");
              // TheModule->dump();
              glStruct->setInitializer(constListExppV);
              // printf("constListExppV\n");

              PointerType *PointerTy4 = Type::getInt8PtrTy(getGlobalContext());

              std::vector<Value *> StructParams;;
              // CastInst *bitCastType = new BitCastInst(ptrVvar, PointerTy4);
              Value *bitCastType = Builder.CreateBitCast(ptrVvar, PointerTy4, "cast");
              StructParams.push_back(bitCastType);
              Constant *constglStruct = ConstantExpr::getCast(Instruction::BitCast, glStruct, PointerTy4);
              StructParams.push_back(constglStruct);
              ConstantInt *constSize = ConstantInt::get(Type::getInt64Ty(getGlobalContext()), totalsize, true);
              StructParams.push_back(constSize);
              ConstantInt *constbyte = ConstantInt::get(Type::getInt32Ty(getGlobalContext()), 8, true);
              StructParams.push_back(constbyte);
              ConstantInt *const0 = ConstantInt::get(Type::getInt1Ty(getGlobalContext()), 0, true);
              StructParams.push_back(const0);

              // printf("befor get function\n");
              Function *llvmMemCpy = getMemCpyFunc();
              // printf("before call llvmMemCpy\n");
              // TheModule->dump();
              // printf("dump\n");

              Builder.CreateCall(llvmMemCpy, StructParams, "");
              // TheModule->dump();
              // printf("after call llvmMemCpy\n");
               return 0;
      }
      else {                                  // global struct variable, is can be initilized or not
                StructTyA = TheModule->getTypeByName(structvar->name->c_str());           // if decl a struct variable, first look up global table for a struct type
                if( !StructTyA ){
                         ErrorV("no such struct type.");
                         exit(-1);
                }
                GlobalVariable *Alloca = new GlobalVariable(*TheModule, StructTyA, false, GlobalValue::ExternalLinkage, 0, "");
                ConstantList[ *(var->name) ].VaV = Alloca;
                // ConstantList[ *(var->name) ].isPointer = isPointer;
                ConstantList[ *(var->name) ].VarType = 5;

                Constant *constint0 = ConstantInt::get(Type::getInt32Ty(getGlobalContext()), 0, true);
                Constant *constfloat0 = ConstantFP::get(Type::getDoubleTy(getGlobalContext()), 0.0);

                StructGList[*(var->name)] = *(structvar->name);                // map a struct variable to a struct type
                // printf("%s\n", var->name->c_str());
                // printf("%s\n", StructList[*(var->name)].c_str());

                int vsize = SizeStruct[*(structvar->name)];                          // get size of struct type
                // printf("%d\n", vsize);
                std::vector<Constant *> ListExppV;

                if(!hasinitflag) {             // no initializer , make it 0
                        for (int i = 0; i < vsize; ++i){
                               int typeindex = StructTyA->getTypeAtIndex(i)->getTypeID();
                               switch(typeindex){
                                        case 3 : ListExppV.push_back(constfloat0); break;
                                        case 10 : ListExppV.push_back(constint0); break;
                                        case 14 : ListExppV.push_back(0); break;
                                        default : ListExppV.push_back(0); break;
                               }
                        }
                        Constant *constListExppV = ConstantStruct::get(StructTyA, ListExppV);
                        Alloca->setInitializer(constListExppV);
                        return 0;
                }
                else{               // has initializer
                      if(expp->v.size() > vsize){
                                  ErrorV("too many initializers for struct.");
                                  exit(-1);
                      }
                      else if(expp->v.size() > vsize){
                                  ErrorV("too little initializers for struct.");
                                  exit(-1);
                      }
                      else{
                              for (int i = 0; i < vsize; ++i){
                                            int totalsize;
                                            ExpNode *tmpExp = expp->v[i];
                                            int typeindex = StructTyA->getTypeAtIndex(i)->getTypeID();
                                            Constant *expV = getConstantV(typeindex, tmpExp, totalsize);
                                            ListExppV.push_back(expV);
                              }
                              Constant *constListExppV = ConstantStruct::get(StructTyA, ListExppV);
                              Alloca->setInitializer(constListExppV);
                              return 0;
                      }
                }
      }
      // TheModule->dump();
      return 0;
}

Value *PointNode::Codegen(std::vector<AllocaInst *> &OldBindings , bool isConst){
      int isGlobal;
      return LookupTable(var->name, isGlobal);
}

// a = b.c
Value *SEToVarNode::Codegen(std::vector<AllocaInst *> &OldBindings , bool isConst){
      // printf("%s\n", mvar->name->c_str());
      // printf("%s\n", StructList["gcc"].c_str());
      bool isGlobal = false;          // isGlobal : struct varible
      if(StructLList.count(*(mvar->name)) == 0){
                isGlobal = true;
                if(StructGList.count(*(mvar->name)) == 0){
                        ErrorV("no such struct variable in StructList.");
                        exit(-1);
                }
      }

      std::string structT;
      if(!isGlobal)
                structT = StructLList[*(mvar->name)];                  // struct type
      else
                structT = StructGList[*(mvar->name)];

      StructType *StructTyA = TheModule->getTypeByName(structT);
      if(!StructTyA){
               ErrorV("no such struct type.");
               exit(-1);
      }

      // get RValue
      AllocaInst *StructV;          // for struct variable
      int isGGlobal;
      StructV = (AllocaInst *)LookupTable(mvar->name, isGGlobal);

      std::vector<Value *> ptr_indices;
      ConstantInt* const0 = ConstantInt::get(Type::getInt32Ty(getGlobalContext()), 0, true);
      ptr_indices.push_back(const0);
      int index2;
      int vsize = SizeStruct[structT];
      // printf("%d\n", vsize);
      // printf("%ld\n", StructElements[structT].size());
      // printf("%s\n", rvar->name->c_str());

      for (index2 = 0; index2 < vsize; ++index2){
              // printf("%s\n", StructElements[structT][index2].c_str());
              if(rvar->name->compare(StructElements[structT][index2].name) == 0)
                          break;
      }
      if(index2 == vsize){
              ErrorV("no such variable in struct type.");
              exit(-1);
      }
      // printf("%d\n", index2);
      ConstantInt *indexV = ConstantInt::get(Type::getInt32Ty(getGlobalContext()), index2, true);
      ptr_indices.push_back(indexV);
      Value *ptrindex = Builder.CreateGEP(StructV, ptr_indices, "");
      Value *RValue = Builder.CreateLoad(ptrindex, "");
      // if(isPointer){
      //           // printf("pointer\n");
      //           RValue = Builder.CreateLoad(RValue, "");
      //  }

      // get LValue
      AllocaInst *LValueV;
      if(Ty == STMTASSIGN){               // stmt assign
              LValueV = (AllocaInst *)LookupTable(lvar->name, isGGlobal);
              return Builder.CreateStore(RValue, LValueV);
      }
      else{                                         // decl assign
              Type *Assigntype;
              if(!isPointer){
                      if(VarType == 0)
                              Assigntype = Type::getInt32Ty(getGlobalContext());
                      else if(VarType == 1)
                              Assigntype = Type::getDoubleTy(getGlobalContext());
              }
              // else if(VarType == 2)
              //         Assigntype = Type::getArrayTy(getGlobalContext());
              else if(VarType == 0)
                      Assigntype = Type::getInt32PtrTy(getGlobalContext());
              else if(VarType == 1)
                      Assigntype = Type::getDoublePtrTy(getGlobalContext());
              // else if(VarType == 5)
              //         Assigntype = Type::getStructTy(getGlobalContext());

              if( !globalflag ){
                      // printf("is local\n");
                      LValueV = Builder.CreateAlloca(Assigntype, 0, lvar->name->c_str());              //Lvalue
                      // printf("CreateAlloca\n");
                      OldBindings.push_back((AllocaInst *)NamedValues[ *(lvar->name) ].VaV);
                      conflictName.push_back( *(lvar->name) );
                      // TheModule->dump();
                      return Builder.CreateStore(RValue, LValueV);
              }
              else{
                      ErrorV("can't assign a variable with a struct element in global.");
                      exit(-1);
              }
      }
}

// b.c = a
Value *VarToSENode::Codegen(std::vector<AllocaInst *> &OldBindings , bool isConst){
        Value *RValue ;
        if(rightPointer){
                // printf("is a pointer\n");
                VarNode *tmpVar;
                if(exp->type == VAR)
                          tmpVar = dynamic_cast<VarNode *>(exp);
                else{
                          ErrorV("not correct type for element in struct.");
                          exit(-1);
                }
                int isGlobal;
                RValue = (AllocaInst *)LookupTable(tmpVar->name, isGlobal);
        }
        else
                RValue = exp->Codegen(OldBindings);              // RValue

        // TheModule->dump();
        bool isGlobal = false;          // isGlobal : struct varible
        if(StructLList.count(*(lvar->name)) == 0){
                  isGlobal = true;
                  if(StructGList.count(*(lvar->name)) == 0){
                          ErrorV("no such struct variable in StructList.");
                          exit(-1);
                  }
        }

        std::string structT;
        if(!isGlobal)
                  structT = StructLList[*(lvar->name)];                  // struct type
        else
                  structT = StructGList[*(lvar->name)];

        StructType *StructTyA = TheModule->getTypeByName(structT);
        if(!StructTyA){
                 ErrorV("no such struct type.");
                 exit(-1);
        }
      AllocaInst *StructV;          // for struct variable
      if(NamedValues.count(*(lvar->name)) > 0){
               StructV = (AllocaInst *)NamedValues[*(lvar->name)].VaV;
      }
      else if(ConstantList.count(*(lvar->name)) > 0){
               StructV = (AllocaInst *)ConstantList[*(lvar->name)].VaV;
      }
      else{
              ErrorV("no such struct variable in Symbal Table.");
              exit(-1);
      }
      std::vector<Value *> ptr_indices;
      ConstantInt* const0 = ConstantInt::get(Type::getInt32Ty(getGlobalContext()), 0, true);
      ptr_indices.push_back(const0);
      int index2;
      int vsize = SizeStruct[structT];
      // printf("%d\n", vsize);
      // printf("%ld\n", StructElements[structT].size());
      // printf("%s\n", StructElements[structT][0].c_str());
      for (index2 = 0; index2 < vsize; ++index2){
              // printf("%s\n", StructElements[structT][index2].c_str());
              if(mvar->name->compare(StructElements[structT][index2].name) == 0)
                          break;
      }
      if(index2 == vsize){
              ErrorV("no such variable in struct type.");
              exit(-1);
      }
      // printf("%d\n", index2);
      ConstantInt *indexV = ConstantInt::get(Type::getInt32Ty(getGlobalContext()), index2, true);
      ptr_indices.push_back(indexV);
      Value *ptrindex = Builder.CreateGEP(StructV, ptr_indices, "");
      Builder.CreateStore(RValue, ptrindex);
      // TheModule->dump();
      // printf("generate store over for b.c\n");
      return 0;
}

  Value *RetAssignNode::Codegen(std::vector<AllocaInst *> &OldBindings , bool isConst){
        Value *call = funccall->Codegen(OldBindings);
        if(Ty == STMTASSIGN){
                AllocaInst *VarV = (AllocaInst *)NamedValues[ var-> name->c_str() ].VaV;         // first fetch it in local
                if( !VarV ){
                       GlobalValue *GloV = TheModule->getNamedValue(var->name->c_str());     // then fetch it in global
                       // Builder.CreateLoad( GloV, name->c_str() );
                       Builder.CreateStore(call, GloV);
                       return call;
                }
                if( !VarV )
                       return 0;
                if( NamedValues[ var->name->c_str() ].isConst == false ){
                       return Builder.CreateStore(call, VarV);
                }
                else{
                       ErrorV("can't assign a read only value");
                       exit(-1);
                 }
         }
         else if(Ty == DECLASSIGN){
                 Type *Assigntype;
                 // printf("%d\n", VarType);
                 if(!isPointer){
                       switch(VarType){
                              case 0 : Assigntype = Type::getInt32Ty(getGlobalContext());break;
                              case 1 : Assigntype = Type::getDoubleTy(getGlobalContext());break;
                       }
               }
               else{
                       switch(VarType){
                              case 0 : Assigntype = Type::getInt32PtrTy(getGlobalContext());break;
                              case 1 : Assigntype = Type::getDoublePtrTy(getGlobalContext());break;
                       }
               }

                 AllocaInst *LValue = Builder.CreateAlloca(Assigntype, 0, var->name->c_str());
                 NamedValues[*(var->name)].VaV = LValue;
                 NamedValues[*(var->name)].isConst = false;

                 return Builder.CreateStore(call, LValue);
         }
        return 0;
}

Value *ArrayRetAssignNode::Codegen(std::vector<AllocaInst *> &OldBindings , bool isConst){
      if( NamedValues[ var->name->c_str() ].isConst == true ){
            ErrorV("can't assign a read only array's element in ArrayRetAssign");
            exit(-1);
      }
      // Value *ValueV = exp2->Codegen(OldBindings);               // get answer first
      Value *call = funccall->Codegen(OldBindings);
      std::vector<Value *> ptr_indices;
      Value *ptrindex;

      Value *indexV = exp->Codegen(OldBindings);
      ConstantInt* const0 = ConstantInt::get(getGlobalContext(), APInt(64, StringRef("0"), 10));
      ptr_indices.push_back(const0);
      ptr_indices.push_back(indexV);

      Value *ArrayV = NamedValues[ *(var->name) ].VaV;
      if( !ArrayV ){
               GlobalValue *GloV = TheModule->getNamedValue(var->name->c_str());
               ptrindex = Builder.CreateGEP(GloV, ptr_indices,"");
      }
      else{
            ptrindex = Builder.CreateGEP(ArrayV, ptr_indices,"");
      }

      return Builder.CreateStore(call, ptrindex);
}

Value *IntNumNode::Codegen(std::vector<AllocaInst *> &OldBindings , bool isConst) {

      return ConstantInt::get(Type::getInt32Ty(getGlobalContext()), val, true);
}

Value *FloatNumNode::Codegen(std::vector<AllocaInst *> &OldBindings , bool isConst) {
      // printf("%f\n", val);
      return ConstantFP::get(Type::getDoubleTy(getGlobalContext()), val);
}

Value *ArrayNode::getPtrIndex(std::vector<AllocaInst *> &OldBindings, bool isConst){
      std::vector<Value *> ptr_indices;
      Value *ValueV = exp->Codegen(OldBindings);
      int expnum = getLocalValue(exp, isConst);
      ConstantInt* const0 = ConstantInt::get(Type::getInt32Ty(getGlobalContext()), 0, true);
      // ConstantInt* indexV = ConstantInt::get(Type::getInt32Ty(getGlobalContext()), valuei, true);
      ptr_indices.push_back(const0);
      ptr_indices.push_back(ValueV);

      // printf("get value\n");
      Value *ArrayV = NamedValues[ *(var->name) ].VaV;
      if(NamedValues[*(var->name)].VarType == 3 ||NamedValues[*(var->name)].VarType == 4){
                // printf("is pointer\n");
                Value *ptrindex = ArrayV + expnum;
                return Builder.CreateLoad(ptrindex, "");
      }
      if( !ArrayV ){
            GlobalValue *GloV = TheModule->getNamedValue(var->name->c_str());
            if(!GloV){
                  ErrorV("no specified value");
                  exit(-1);
            }
            Value *ptrindex = Builder.CreateGEP(GloV, ptr_indices, "");
            return Builder.CreateLoad(ptrindex, "");
      }
      return Builder.CreateGEP(ArrayV, ptr_indices, "");
}

// use it as a right value
Value *ArrayNode::Codegen(std::vector<AllocaInst *> &OldBindings , bool isConst){
      // return ptrindex;
      std::vector<Value *> ptr_indices;
      Value *ValueV = exp->Codegen(OldBindings);
      int expnum = getLocalValue(exp, isConst);
      ConstantInt* const0 = ConstantInt::get(Type::getInt32Ty(getGlobalContext()), 0, true);
      // ConstantInt* indexV = ConstantInt::get(Type::getInt32Ty(getGlobalContext()), valuei, true);
      ptr_indices.push_back(const0);
      ptr_indices.push_back(ValueV);

      // printf("get value\n");
      Value *ArrayV = NamedValues[ *(var->name) ].VaV;
      // if(NamedValues[*(var->name)].VarType == 3 ||NamedValues[*(var->name)].VarType == 4){
      //           // printf("is pointer\n");
      //           Value *ptrindex = ArrayV + expnum;
      //           Builder.CreateLoad(ptrindex, "");
      //           // TheModule->dump();
      //           return Builder.CreateLoad(ptrindex, "");
      // }
      if( !ArrayV ){
            GlobalValue *GloV = TheModule->getNamedValue(var->name->c_str());
            if(!GloV){
                  ErrorV("no specified value");
                  exit(-1);
            }
            Value *ptrindex = Builder.CreateGEP(GloV, ptr_indices, "");
            return Builder.CreateLoad(ptrindex, "");
      }
      int arrType = NamedValues[ *(var->name) ].VarType;
      Value *ptrindex = Builder.CreateGEP(ArrayV, ptr_indices, "");
      return Builder.CreateLoad(ptrindex, "");
}

// when a variable is created, call this , variable allows has no init
Value *AssignNode::Codegen(std::vector<AllocaInst *> &OldBindings , bool isConst){
       const std::string &VarName = *(var->name);
       bool hasinitflag = true;
       exp->VarType = VarType;
       ExpNode *Init = exp;
       // printf("%d\n", exp->type);
       if(exp->type == INTNUM || exp->type == FLOATNUM){
            if((int)getLocalValue(exp, isConst) == 65535)
                  hasinitflag = false;
       }

       Value *InitVal;
       Type *Assigntype;                  // Assigntype means left var's type

       // get Assigntype
       if(!isPointer){
                InitVal = Init->Codegen(OldBindings);                            // get answer first
                 // TheModule->dump();
                 Builder.GetInsertBlock();
                 if(VarType == 0)
                         Assigntype = Type::getInt32Ty(getGlobalContext());
                 else if(VarType == 1){
                          // printf("%d\n", InitVal->getType()->getTypeID());
                          if(InitVal->getType()->getTypeID() == 10 )         // init value is int
                                  InitVal =  Builder.CreateUIToFP(InitVal, Type::getDoubleTy(getGlobalContext()), "tmp");
                          if(InitVal->getType()->getTypeID() == 2)
                                  InitVal =  Builder.CreateFPExt(InitVal, Type::getDoubleTy(getGlobalContext()), "tmp");
                         Assigntype = Type::getDoubleTy(getGlobalContext());
                        // printf("done\n");
                  }
        }

        // local or global
       if(globalflag == false){                                // assign to local variable
            Function *TheFunction = Builder.GetInsertBlock()->getParent();
            if(type == DECLASSIGN){           // need change symbol table
                  // printf("begin alloca assign\n");
                  AllocaInst *Alloca = Builder.CreateAlloca(Assigntype, 0, VarName.c_str());              //Lvalue
                  // Alloca->dump();
                  // printf("allca done assign\n");
                  OldBindings.push_back((AllocaInst *)NamedValues[ VarName ].VaV);
                  conflictName.push_back( VarName );

                  if( hasinitflag ){
                        // printf("has init\n");
                        Builder.CreateStore(InitVal, Alloca);
                        // TheModule->dump();

                        if(isConst){
                                NamedValues[ VarName ].isConst = true;
                        }
                        else
                                NamedValues[ VarName ].isConst = false;
                  }
                  else{
                        // printf("no init\n");
                        NamedValues[ VarName ].isConst = false;
                  }
                  NamedValues[ VarName ].VaV = Alloca;
                  if(!isPointer)
                              NamedValues[ VarName ].value = getLocalValue(exp, isConst);
                  else if(isPointer == 1)
                              NamedValues[ VarName ].value = -1;
                  else if(isPointer == 2){
                              NamedValues[ VarName ].value = -2;
                  }
                  NamedValues[ VarName ].VarType = VarType;
                  NamedValues[ VarName ].isPointer = isPointer;
                  // printf("%s\n", VarName.c_str());
                  // TheModule->dump();
                  return 0;
          }
          else if(type == STMTASSIGN){                    // stmt assign need generate Lvalue itself
              AllocaInst *VarV = (AllocaInst *)NamedValues[ VarName ].VaV;         // first fetch it in local
              int preTy = VarType;
              VarType = NamedValues[ VarName ].VarType;
              if( !VarV ){
                        GlobalValue *GloV = TheModule->getNamedValue(VarName.c_str());     // then fetch it in global
                        // Builder.CreateLoad( GloV, name->c_str() );
                        if(!isPointer)
                                  Builder.CreateStore(InitVal, GloV);
                        else if(isPointer == 2){
                                  InitVal = Builder.CreateLoad(InitVal, "");
                                  Builder.CreateStore(InitVal, GloV);
                        }
                        return InitVal;
              }
              if( !VarV ){
                        ErrorV("no such variable.");
                        exit(-1);
              }
              Builder.CreateStore(InitVal, VarV);
        }
        return InitVal;
      }
      else{                                                            // global variable
            GlobalVariable *Alloca ;
            // printf("%s  :  %d\n", var->name->c_str(), VarType);
            if( isConst ){        // global constant
                    ConstantList[*(var->name)].isConst = true;
                    ConstantList[*(var->name)].VarType = VarType;
                    ConstantList[*(var->name)].isPointer = isPointer;
                    if(!isPointer){
                              double  tempConstV = getGlobalValue(exp, true);
                              ConstantList[*(var->name)].value = tempConstV;      // store this const value
                              if(VarType == 0){
                                        Constant *constInit;
                                        if(hasinitflag && tempConstV != 65535)
                                                      constInit =  ConstantInt::get(Type::getInt32Ty(getGlobalContext()), (int)tempConstV, true);
                                        else
                                                      constInit =  ConstantInt::get(Type::getInt32Ty(getGlobalContext()), 0, true);
                                        Alloca = new GlobalVariable(*TheModule, Type::getInt32Ty(getGlobalContext()) ,true ,GlobalValue::ExternalLinkage, constInit, VarName.c_str());
                              }
                              else if(VarType == 1){
                                        Constant *constInit;
                                        if(hasinitflag && tempConstV != 65535)
                                                      constInit =  ConstantFP::get(Type::getDoubleTy(getGlobalContext()), (double)tempConstV);
                                        else
                                                      constInit =  ConstantFP::get(Type::getDoubleTy(getGlobalContext()), 0.0);
                                        Alloca = new GlobalVariable(*TheModule, Type::getDoubleTy(getGlobalContext()) ,true ,GlobalValue::ExternalLinkage, constInit, VarName.c_str());
                                }
                    }
                  ConstantList[*(var->name)].VaV = Alloca;
            }
            else{               // global unconstant
                    // ConstantList[*(var->name)].value = tempUnConstV;      // store this value
                    // ConstantList[*(var->name)].isConst = false;
                    if(!isPointer){
                              double  tempUnConstV = getGlobalValue(exp, false);
                              if(VarType == 0){
                                        Constant *constInit;
                                        if(hasinitflag && tempUnConstV != 65535)
                                                      constInit =  ConstantInt::get(Type::getDoubleTy(getGlobalContext()), (int)tempUnConstV, true);
                                        else
                                                      constInit =  ConstantInt::get(Type::getDoubleTy(getGlobalContext()), 0.0, true);
                                        Alloca = new GlobalVariable(*TheModule, Type::getInt32Ty(getGlobalContext()) ,false ,GlobalValue::ExternalLinkage, constInit, VarName.c_str());
                              }
                              else if(VarType == 1){
                                        Constant *constInit;
                                        if(hasinitflag && tempUnConstV != 65535)
                                                      constInit =  ConstantFP::get(Type::getDoubleTy(getGlobalContext()), (double)tempUnConstV);
                                        else
                                                      constInit =  ConstantFP::get(Type::getDoubleTy(getGlobalContext()), 0.0);
                                        Alloca = new GlobalVariable(*TheModule, Type::getDoubleTy(getGlobalContext()) ,false ,GlobalValue::ExternalLinkage, constInit, VarName.c_str());
                              }
                              ConstantList[*(var->name)].VaV = Alloca;
                              ConstantList[*(var->name)].isConst = false;
                              ConstantList[*(var->name)].VarType = VarType;
                              // printf("%s : %d \n", var->name->c_str(), ConstantList[*(var->name)].VarType);
                              ConstantList[*(var->name)].isPointer = isPointer;
                              ConstantList[*(var->name)].value = tempUnConstV;      // store this const value
                              // TheModule->dump();
                   }
            }
            // TheModule->dump();
            return InitVal;
      }
}

Value *PointeeAssignNode::Codegen(std::vector<AllocaInst *> &OldBindings , bool isConst){
        // printf("here is for a = *p codegen\n");
        // get RValue
        Value *RValue;
        if(NamedValues.count(*(rvar->name)) > 0){
                RValue = NamedValues[*(rvar->name)].VaV;
        }
        else if(ConstantList.count(*(rvar->name)) > 0){
                RValue = ConstantList[*(rvar->name)].VaV;
        }
        else{
                ErrorV("no such variable in PointerAssign.");
                exit(-1);
        }
        RValue = Builder.CreateLoad(RValue, "");
        RValue = Builder.CreateLoad(RValue, "");
        // TheModule->dump();

        // get LValue
        AllocaInst *LValue;
        if(Ty == STMTASSIGN){
              bool constor = false;
              int isGlobal;
              LValue = (AllocaInst *)LookupTable(lvar->name, isGlobal);
              if(isGlobal)
                      constor = ConstantList[*(lvar->name)].isConst;
              else
                      constor = NamedValues[*(lvar->name)].isConst;

              if(constor){
                      ErrorV("can't assign to a const.");
                      exit(-1);
              }
              // printf("%s\n", );
              return Builder.CreateStore(RValue, LValue);
        }
        else {            // decl assign
              Type *Assigntype;
              if(VarType == 0)
                      Assigntype = Type::getInt32Ty(getGlobalContext());
              else if(VarType == 1)
                      Assigntype = Type::getDoubleTy(getGlobalContext());
              LValue = Builder.CreateAlloca(Assigntype, 0, lvar->name->c_str());
              return Builder.CreateStore(RValue, LValue);
        }
        // TheModule->dump();
        // return 0;
}

// assign to pointer (decl a pointer and assign to a pointer are both here)
Value *PointerAssignNode::Codegen(std::vector<AllocaInst *> &OldBindings , bool isConst){
              // printf("here is for pointer assign\n");
            // generate RValue
            Value *RValue = 0;
            if(rvar){                  // rvar == 0 means no intializer
                    int isGlobal;
                    // printf("get rvalue\n");
                    RValue = LookupTable(rvar->name, isGlobal);
                    if(exp){
                              // printf("get rvalue\n");
                              ArrayNode *arrN = new ArrayNode(rvar, exp);
                              RValue = arrN->getPtrIndex(OldBindings);
                      }
                      else{
                              ErrorV("invalid type for right value.");
                              exit(-1);
                      }
                      if(Ty == PTOP)
                              RValue = Builder.CreateLoad(RValue, "");
                      // TheModule->dump();
            }

            // generate LValue
            // printf("get lvar\n");
            AllocaInst *LValue;
            if(Ty == STMTASSIGN){
                      // printf("in stmt\n");
                      bool constor = false;
                      int isGlobal;
                      // printf("%s\n", lvar->name->c_str());
                      LValue = (AllocaInst *)LookupTable(lvar->name, isGlobal);
                      if(isGlobal)
                              constor = ConstantList[*(lvar->name)].isConst;
                      else
                              constor = NamedValues[*(lvar->name)].isConst;
                      if(constor){
                              ErrorV("can't assign to a const variable.");
                              exit(-1);
                      }
                      if(RValue)
                             return Builder.CreateStore(RValue, LValue);
                             // printf("CreateStore\n");
            }
            else if(Ty == DECLASSIGN || Ty == PTOP){
                      // printf("in decl\n");
                      Type *Assigntype;
                      if(VarType == 0)
                              Assigntype = Type::getInt32PtrTy(getGlobalContext());
                      else if(VarType == 1)
                              Assigntype = Type::getDoublePtrTy(getGlobalContext());
                      else if(VarType == 7){
                              StructType *StructTyA = TheModule->getTypeByName(structvar->name->c_str());
                              // printf("%s\n",structvar->name->c_str() );
                              Assigntype = PointerType::get(StructTyA, 0);
                      }

                      if(!globalflag){
                              LValue = Builder.CreateAlloca(Assigntype, 0, lvar->name->c_str());
                              // printf("%s\n",lvar->name->c_str() );
                              NamedValues[*(lvar->name)].VaV = LValue;
                              NamedValues[*(lvar->name)].isConst = isConst;
                              NamedValues[*(lvar->name)].isPointer = true;
                              NamedValues[*(lvar->name)].VarType = VarType+2;
                              if(isConst){
                                      ConstantList[*(lvar->name)].VaV = LValue;
                                      ConstantList[*(lvar->name)].isConst = isConst;
                                      ConstantList[*(lvar->name)].VarType = VarType+2;
                              }

                             if(RValue)
                                    return Builder.CreateStore(RValue, LValue);
                              // printf("no rvalue\n");
                      }
                      else{
                              GlobalVariable *GloV = new GlobalVariable(*TheModule, Assigntype, true, GlobalValue::ExternalLinkage, (Constant *)RValue, lvar->name->c_str());
                              ConstantList[*(lvar->name)].VaV = LValue;
                              ConstantList[*(lvar->name)].isConst = isConst;
                              ConstantList[*(lvar->name)].VarType = VarType;
                              return GloV;
                      }
            }
            return 0;
}

// in stmt , a[x] = y ;
Value *ArrayAssignExpNode::Codegen(std::vector<AllocaInst *> &OldBindings , bool isConst){
      std::vector<Value *> ptr_indices;
      Value *ptrindex;

      Value *indexV = exp1->Codegen(OldBindings);
      ConstantInt* const0 = ConstantInt::get(getGlobalContext(), APInt(64, StringRef("0"), 10));
      ptr_indices.push_back(const0);
      ptr_indices.push_back(indexV);

      Value *RValue;
      int varType = NamedValues[ *(var->name) ].VarType;
      if(varType != 7){
               RValue = exp2->Codegen(OldBindings);               // get answer first
               // printf("done\n");
      }
      else if(varType == 7){            // struct array
            if(exp2->type != VAR){
                      ErrorV("no match type with struct array element assign.");
                      exit(-1);
            }
            VarNode *RNode = dynamic_cast<VarNode *>(exp2);
            RValue = RNode->Codegen(OldBindings);
      }

      Value *ArrayV = NamedValues[ *(var->name) ].VaV;
      if( !ArrayV ){
               GlobalValue *GloV = TheModule->getNamedValue(var->name->c_str());
               ptrindex = Builder.CreateGEP(GloV, ptr_indices,"");
      }
      else{
            ptrindex = Builder.CreateGEP(ArrayV, ptr_indices,"");
      }

      return Builder.CreateStore(RValue, ptrindex);
      // return 0;
}

// in decl , initialize, const array must have initilize, unconst mustn't
Value *ArrayAssignExppNode::Codegen(std::vector<AllocaInst *> &OldBindings , bool isConst){
      ArrayType *ArrayTy;         // type of array
      Type *Assigntype;             // type of element
      if(VarType == 0)
               Assigntype = Type::getInt32Ty(getGlobalContext());
      else if(VarType == 1)
               Assigntype = Type::getDoubleTy(getGlobalContext());

       int lenOfArr;                        // length of array
      if(exp->type == INTNUM)
              lenOfArr = dynamic_cast<IntNumNode *>(exp)->val;
      else{
              if(globalflag == false)
                      lenOfArr = (int)getLocalValue(exp, true);
              else
                      lenOfArr = (int)getGlobalValue(exp, true);
      }
      // printf("%d\n", lenOfArr);
      if(lenOfArr > 0)
             ArrayTy = ArrayType::get(Assigntype, lenOfArr);
      else
            ArrayTy = ArrayType::get(Assigntype, expp->v.size());

      ConstantInt *const0 = ConstantInt::get(Type::getInt32Ty(getGlobalContext()), 0, true);
      if(globalflag == false){              // local array
                AllocaInst *ptrArr = Builder.CreateAlloca(ArrayTy, 0 , var->name->c_str());
                if( !ptrArr ){
                      printf("no memory allca\n");
                      return 0;
                }

                // remember the old bindings
                OldBindings.push_back( (AllocaInst *)NamedValues[ *(var->name) ].VaV ) ;
                conflictName.push_back( *(var->name) );

                NamedValues[ *(var->name) ].VaV = ptrArr;           // add it into symbol table
                NamedValues[ *(var->name) ].VarType = VarType;
                NamedValues[ *(var->name) ].isConst = isConst;

                std::vector<Value *> ptr_indices;
                ConstantInt *const1 = ConstantInt::get(Type::getInt32Ty(getGlobalContext()), 1, true);
                ptr_indices.push_back(const0);
                ptr_indices.push_back(const0);

                if( expp->v.size() > 0 ){
                        // Instruction *ptrtostart = GetElementPtrInst::Create(ptrArr, ptr_indices, "");
                        Value *ptrCurrent = Builder.CreateGEP(ptrArr, ptr_indices,"");
                        Value *RValueV = expp->v[0]->Codegen(OldBindings);
                        if(VarType == 1){
                                  if(RValueV->getType()->getTypeID() == 10)
                                              RValueV = Builder.CreateUIToFP(RValueV, Assigntype, "tmp");
                                  if(RValueV->getType()->getTypeID() == 2)
                                              RValueV = Builder.CreateFPExt(RValueV, Assigntype, "tmp");
                        }
                        Builder.CreateStore(RValueV, ptrCurrent);

                        for (int i = 1; i < expp->v.size(); ++i){
                              // printf("%d \n", i );
                               ptrCurrent = Builder.CreateGEP(ptrCurrent, const1,"");
                               Value *RValueV = expp->v[i]->Codegen(OldBindings);
                               if(VarType == 1){
                                      if(RValueV->getType()->getTypeID() == 10)
                                                  RValueV = Builder.CreateUIToFP(RValueV, Assigntype, "tmp");
                                      if(RValueV->getType()->getTypeID() == 2)
                                                  RValueV = Builder.CreateFPExt(RValueV, Assigntype, "tmp");
                                }
                              // RValueV->dump();
                              // printf("store\n");
                              Builder.CreateStore(RValueV, ptrCurrent);
                              // TheModule->dump();
                              // StoreInst *varI = new StoreInst(RValueV, ptri, false);
                        }
                        if(expp->v.size() < lenOfArr){
                              for (int i = expp->v.size(); i < lenOfArr; ++i){
                                  ptrCurrent = Builder.CreateGEP(ptrCurrent, const1,"");
                                  Value *RValueV = expp->v[i]->Codegen(OldBindings);
                                  Builder.CreateStore(const0, ptrCurrent);
                                  // StoreInst *varI = new StoreInst(RValueV, ptri, false);
                              }
                        }
                }
                return ptrArr;
        }
        else{             // global array
            GlobalVariable *Alloca;
            Constant *constArrayValue;
            std::vector<Constant *> constArraygetV;
            if(VarType == 0){
                      for (int i = 0; i < expp->v.size(); ++i){
                             int valuei = (int)getGlobalValue(expp->v[i], isConst);
                             Constant *RValueV = ConstantInt::get(Type::getInt32Ty(getGlobalContext()) , valuei , true);
                             constArraygetV.push_back(RValueV);
                      }
                      for (int i = expp->v.size(); i < lenOfArr; ++i){
                              constArraygetV.push_back(const0);
                      }
            }
            else if(VarType == 1){
                      for (int i = 0; i < expp->v.size(); ++i){
                             double valuei = getGlobalValue(expp->v[i], isConst);
                             Constant *RValueV = ConstantFP::get(Type::getDoubleTy(getGlobalContext()) , valuei);
                             constArraygetV.push_back(RValueV);
                      }
                      Constant *constdouble0 = ConstantFP::get(Type::getDoubleTy(getGlobalContext()), 0.0);
                      for (int i = expp->v.size(); i < lenOfArr; ++i){
                              constArraygetV.push_back(constdouble0);
                      }
            }
            constArrayValue = ConstantArray::get(ArrayTy, constArraygetV);
            if( isConst ){
                    Alloca = new GlobalVariable(*TheModule, ArrayTy, true, GlobalValue::ExternalLinkage,0, var->name->c_str());
                    Alloca->setInitializer(constArrayValue);
                    ConstantList[*(var->name)].VarType = 2;
                    ConstantList[*(var->name)].VaV = Alloca;
                    ConstantList[*(var->name)].isConst = true;
            }
            else{
                    Alloca = new GlobalVariable(*TheModule, ArrayTy, false, GlobalValue::ExternalLinkage,0, var->name->c_str());
                    Alloca->setInitializer(constArrayValue);
                    ConstantList[*(var->name)].VarType = 2;
                    ConstantList[*(var->name)].VaV = Alloca;
                    ConstantList[*(var->name)].isConst = false;
              }
           return Alloca;
    }
}

Value *StructArrayNode::Codegen(std::vector<AllocaInst *> &OldBindings, bool isConst){
       // printf("struct array\n");
       int lenOfArr;                        // length of array
       StructType *StructTyA;
       if(exp->type == INTNUM)
              lenOfArr = dynamic_cast<IntNumNode *>(exp)->val;
       else{
              if(globalflag == false)
                      lenOfArr = (int)getLocalValue(exp, true);
              else
                      lenOfArr = (int)getGlobalValue(exp, true);
       }

       StructTyA = TheModule->getTypeByName(structvar->name->c_str());           // if decl a struct variable, first look up global table for a struct type
       if(!StructTyA){
               ErrorV("no such struct type.");
               exit(-1);
       }
       if(lenOfArr > 0){
               ArrayType *ArrayTy = ArrayType::get(StructTyA, lenOfArr);
               // printf("%d\n", lenOfArr);
               // printf("%s\n",var->name->c_str() );
               AllocaInst *LValue = Builder.CreateAlloca(ArrayTy, 0, var->name->c_str());
               NamedValues[*(var->name)].VaV = LValue;
               NamedValues[*(var->name)].isConst = false;
               NamedValues[*(var->name)].VarType = 7;
               return LValue;
       }
}

Value *BinaryExpNode::Codegen(std::vector<AllocaInst *> &OldBindings , bool isConst) {
      Value *L = lhs->Codegen(OldBindings);
      Value *R = rhs->Codegen(OldBindings);
      int isDouble = 0;
      if(lhs->type == INTNUM)
                lhs->VarType = 0;
      else if(lhs->type == VAR){
                VarNode *lhsNode = dynamic_cast<VarNode *>(lhs);
                // printf("%s : %d \n", lhsNode->name->c_str(), VarType);
                // printf("%lu\n", NamedValues.size());
                // printf("%f\n", NamedValues[lhsNode->name->c_str()].value);
                if(NamedValues.count(lhsNode->name->c_str()) > 0){
                           // printf("switch type in local \n");
                          if(NamedValues[lhsNode->name->c_str()].VarType > 0)
                                    lhs->VarType = 1;
                }
                else if(ConstantList.count(lhsNode->name->c_str()) > 0){
                          // printf("switch type in global \n");
                          if(ConstantList[lhsNode->name->c_str()].VarType > 0)
                                    lhs->VarType = 1;
               }
        }
        else
              lhs->VarType = 0;

      if(rhs->type == INTNUM)
                rhs->VarType = 0;
      else if(rhs->type == VAR){
                VarNode *rhsNode = dynamic_cast<VarNode *>(rhs);
                if(NamedValues.count(rhsNode->name->c_str()) > 0){
                          if(NamedValues[rhsNode->name->c_str()].VarType > 0)
                                    rhs->VarType = 1;
                }
                else if(ConstantList.count(rhsNode->name->c_str()) > 0){
                          if(ConstantList[rhsNode->name->c_str()].VarType > 0)
                                    rhs->VarType = 1;
                }
      }
      else
                rhs->VarType = 0;

       VarType = rhs->VarType > lhs->VarType ? rhs->VarType : lhs->VarType;
       // printf("%d\n", VarType);

      // printf("%d  %d\n", lhs->VarType, rhs->VarType);
      if(lhs->VarType < 2 && rhs->VarType < 2){
                if(lhs->VarType || rhs->VarType){
                           isDouble = 1;
                          // printf("isDouble\n");
                }
                if(lhs->VarType < rhs->VarType){
                          L = Builder.CreateUIToFP(L, Type::getDoubleTy(getGlobalContext()), "tmp");
                }
                if(lhs->VarType > rhs->VarType){
                          R = Builder.CreateUIToFP(R, Type::getDoubleTy(getGlobalContext()), "tmp");
                }
      }
      if (L == 0 || R == 0) {
              // printf("return 0\n");
              return 0;
      }
      if(!isDouble){
                switch (op) {
                      case '+': return Builder.CreateAdd(L, R, "addtem");
                      case '-': return Builder.CreateSub(L, R, "subtem");
                      case '*': return Builder.CreateMul(L, R, "multem");
                      case '/': return Builder.CreateSDiv(L, R, "divtem");
                      case '%': return Builder.CreateSRem(L, R, "remtem");
                      default: return ErrorV("invalid binary operator");
                }
      }
      else if(isDouble == 1){
                // printf("do\n");
                switch (op) {
                      case '+': return Builder.CreateFAdd(L, R, "addtem");
                      case '-': return Builder.CreateFSub(L, R, "subtem");
                      case '*': return Builder.CreateFMul(L, R, "multem");
                      case '/': return Builder.CreateFDiv(L, R, "divtem");
                      case '%': return ErrorV("invalid binary operator");
                      default: return ErrorV("invalid binary operator");
                }

      }
}

Value *UnaryExpNode::Codegen(std::vector<AllocaInst *> &OldBindings , bool isConst){
        // printf("before\n");
        Value *OperandV = operand->Codegen(OldBindings);
        // printf("done\n");
        if(op == '-')
                  return Builder.CreateSub( ConstantInt::get(Type::getInt32Ty(getGlobalContext()), 0, true), OperandV, "negtmp");
        else
                  return OperandV;
}

Value *CondNode::Codegen(std::vector<AllocaInst *> &OldBindings , bool isConst){
	Value *L = lexp->Codegen(OldBindings);
       // L->dump();
	Value *R = rexp->Codegen(OldBindings);
       // R->dump();
	if (L == 0 || R == 0)
		return 0;

  	switch(relop){
		case eq_tok:  return L = Builder.CreateICmpEQ(L, R, "eqtmp");
		case neq_tok:   return L = Builder.CreateICmpNE(L, R, "neqtmp");
		case lt_tok:  return L = Builder.CreateICmpSLT(L, R, "lttmp");
		case le_tok:  return L = Builder.CreateICmpSLE(L, R, "letmp");
		case gt_tok:  return L = Builder.CreateICmpSGT(L, R, "gttmp");
		case ge_tok:  return L = Builder.CreateICmpSGE(L, R, "getmp");
		default:  return ErrorV("invalid binary operator");
	}
  return 0;
}

Value *IfElseNode::Codegen(std::vector<AllocaInst *> &OldBindings , bool isConst) {
      Value *CondV = cond->Codegen(OldBindings);

      Function *TheFunction = Builder.GetInsertBlock()->getParent();
      // cout<<"done"<<endl;

      // Create blocks for the then and else cases.  Insert the 'then' block at the
      // end of the function.
      BasicBlock *ThenBB = BasicBlock::Create(getGlobalContext(), "then", TheFunction);
      BasicBlock *ElseBB = BasicBlock::Create(getGlobalContext(), "else");
      BasicBlock *MergeBB = BasicBlock::Create(getGlobalContext(), "ifcont");

      Builder.CreateCondBr(CondV, ThenBB, ElseBB);

      // Emit then value.
      Builder.SetInsertPoint(ThenBB);
      // printf("then 1\n");

      Value *ThenV = block1->Codegen(OldBindings);
      // printf("then 2\n");
      // ThenV->dump();
      Builder.CreateBr(MergeBB);
      // Codegen of 'Then' can change the current block, update ThenBB for the PHI.
      ThenBB = Builder.GetInsertBlock();
      // TheModule->dump();

      // Emit else block.
      TheFunction->getBasicBlockList().push_back(ElseBB);

      Builder.SetInsertPoint(ElseBB);
      // TheModule->dump();

      Value *ElseV = 0;
      if(block2){
            ElseV = block2->Codegen(OldBindings);
      }
      Builder.CreateBr(MergeBB);
      ElseBB = Builder.GetInsertBlock();

      // // TheModule->dump();
      TheFunction->getBasicBlockList().push_back(MergeBB);
      Builder.SetInsertPoint(MergeBB);
      return ThenV;
}

Value *WhileNode::Codegen(std::vector<AllocaInst *> &OldBindings , bool isConst){
    	Function *TheFunction = Builder.GetInsertBlock()->getParent();
    	BasicBlock *CondBB = BasicBlock::Create(getGlobalContext(), "whilecond", TheFunction);
       Builder.CreateBr(CondBB);
       Builder.SetInsertPoint(CondBB);
       Value *CondV = cond->Codegen(OldBindings);

    	BasicBlock *LoopBB = BasicBlock::Create(getGlobalContext(), "whileloop", TheFunction);
 	BasicBlock *MergeBB = BasicBlock::Create(getGlobalContext(), "whilet");
        breakOutBB.push_back(MergeBB);
        continueOutBB.push_back(CondBB);

      	Builder.CreateCondBr(CondV, LoopBB, MergeBB);
        // TheModule->dump();
      	Builder.SetInsertPoint(LoopBB);
        Value *LoopV = block->Codegen(OldBindings);

      	Builder.CreateBr(CondBB);
        // TheModule->dump();

      	TheFunction->getBasicBlockList().push_back(MergeBB);
      	Builder.SetInsertPoint(MergeBB);
        breakOutBB.pop_back();
        continueOutBB.pop_back();
        // TheModule->dump();

      return LoopV;
}
