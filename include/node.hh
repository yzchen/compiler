#ifndef _NODE_HH_
#define _NODE_HH_

#pragma clang diagnostic ignored "-Wdeprecated-register"
#define __STDC_LIMIT_MACROS
#define __STDC_CONSTANT_MACROS

// #include "dumpdot.hh"
#include <cctype>
#include <cstdio>
#include <map>
#include <string>
#include <vector>

#include "llvm/IR/Verifier.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/DataLayout.h"
#include "llvm/Analysis/Passes.h"
#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/ExecutionEngine/MCJIT.h"
#include "llvm/ExecutionEngine/SectionMemoryManager.h"
#include "llvm/PassManager.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Transforms/Scalar.h"

using namespace llvm;
using namespace std;

extern Module *TheModule;

extern bool haserror;
extern bool globalflag;
Value *ErrorV(const char *Str);

typedef enum{
	INTNUM,
	FLOATNUM,
	VAR,
	EXP,
	EXPP,
	ARRAY,
	DECLASSIGN,
	STMTASSIGN,
	STRUCTASSIGN,
	POINTEEASSI,
	ARRAYASSIGNEXP,
	ARRAYASSIGNEXPP,
	LVALASSIGN,
	POINTERASSIGN,
	SETOVAR,
	VARTOSE,
	SETOAE,
	AETOSE,
	STRUCTELEMENTASSIGN,
	BINARYEXP,
	UNARYEXP,
	COMPUNIT,
	ARGS,
	SIMPKEDECL,
	PTOP,
	PROTOTYPE,
	FUNCDEF,
	RETURN,
	BREAK,
	CONTINUE,
	EXTERN,
	IDENTLIST,
	DECL,
	POINT,
	CONSTDECL,
	VARDECL,
	VARLIST,
	IDENT,
	BLOCK,
	CONSTDEF,
	BLOCKITEM,
	BLOCKITEMLIST,
	STMT,
	FUNCCALL,
	ASSIGNRET,
	ARRAYRETASSIGN,
	STRUCTARRAY,
	IF,
	IFELSE,
	WHILE,
	CONDSIMPLEEXP,
	CONDNOTEXP,
	CONDINFIXEXP,
	PARENEXP,
	INNERSTRUCTDECL,
	STRUCT
} NodeType;

typedef struct {
    int first_line;
    int first_column;
    int last_line;
    int last_column;
} Loc;

class Node {
public:
	NodeType type;
	Loc *loc;
	double value;
	Node() { loc = (Loc*)malloc(sizeof(Loc)); };
	// virtual ~Node() = 0;
	// virtual // int dumpdot(DumpDOT *dumper) = 0;
	virtual Value *Codegen( std::vector<AllocaInst *> &OldBindings , bool isConst=false) = 0;
	// virtual void setLoc(Loc *loc);
	// virtual void printast(FILE *fp, int indent);
	virtual void append(Node *node) = 0;
};

class ExpNode : public Node {
public:
	int VarType;
	// virtual // int dumpdot(DumpDOT *dumper) = 0;
	virtual Value *Codegen(std::vector<AllocaInst *> &OldBindings, bool isConst=false) = 0;
	// virtual ~ExpNode() = 0;
	// void printast(FILE *fp, int indent);
	// void setLoc(Loc *loc);
	virtual void append(Node *node) = 0;
};

class BlockItemNode : public Node{
public:
	BlockItemNode() { type = BLOCKITEM; }
	// virtual // int dumpdot(DumpDOT *dumper) = 0;
	virtual Value *Codegen(std::vector<AllocaInst *> &OldBindings, bool isConst=false) = 0;
	// void printast(FILE *fp, int indent);
	// void setLoc(Loc *loc);
	virtual void append(Node *node) = 0;
};

class StmtNode : public BlockItemNode{
public:
	// std::vector<Node *> v;
	StmtNode() { type = STMT; }
	// virtual // int dumpdot(DumpDOT *dumper) = 0;
	virtual void append(Node *node) = 0;
	virtual Value *Codegen(std::vector<AllocaInst *> &OldBindings, bool isConst=false) = 0;
	// void printast(FILE *fp, int indent);
	// void setLoc(Loc *loc);
};

class ANode : public ExpNode{
public:
	// virtual ~ANode() = 0;
	// virtual // int dumpdot(DumpDOT *dumper) = 0;
	// void printast(FILE *fp, int indent);
	// void setLoc(Loc *loc);
	virtual void append(Node *node) = 0;
	virtual Value *Codegen(std::vector<AllocaInst *> &OldBindings, bool isConst=false) = 0;
};

class DeclNode : public StmtNode{
public:
	DeclNode() { type = DECL; }
	// virtual // int dumpdot(DumpDOT *dumper) = 0;
	// void printast(FILE *fp, int indent);
	// void setLoc(Loc *loc);
	virtual void append(Node *node) = 0;
	virtual Value *Codegen(std::vector<AllocaInst *> &OldBindings, bool isConst=false) = 0;
};

class IdentNode : public Node{
public:
	IdentNode() { type = IDENT; };
	// virtual // int dumpdot(DumpDOT *dumper) = 0;
	// void printast(FILE *fp, int indent);
	// void setLoc(Loc *loc);
	virtual Value *Codegen(std::vector<AllocaInst *> &OldBindings, bool isConst=false) = 0;
	virtual void append(Node *node) = 0;
};

class BlockItemListNode : public Node{
public:
	std::vector<BlockItemNode *> v;
	BlockItemListNode() { type = BLOCKITEMLIST; }
	// int dumpdot(DumpDOT *dumper);
	void append(Node *node);
	virtual Value *Codegen(std::vector<AllocaInst *> &OldBindings, bool isConst=false);
	// void printast(FILE *fp, int indent);
	// void setLoc(Loc *loc);
};

class BlockNode : public Node{
	BlockItemListNode *blockitemlist;
public:
	BlockNode(BlockItemListNode *blockitemlist) : blockitemlist(blockitemlist) { type = BLOCK;};
	// int dumpdot(DumpDOT *dumper);
              //void printast(FILE *fp, int indent);
	// void setLoc(Loc *loc);
	virtual Value *Codegen(std::vector<AllocaInst *> &OldBindings, bool isConst=false);
	void append(Node *node) { }
};

class VarNode : public ExpNode {
public:
	std::string *name;
	VarNode(std::string* name) : name(name) { type = VAR; }
	// int dumpdot(DumpDOT *dumper);
	// void printast(FILE *fp, int indent);
	// void setLoc(Loc *loc);
	virtual Value *Codegen(std::vector<AllocaInst *> &OldBindings, bool isConst=false);
	const std::string &getName() const { return *name; }
	void append(Node *node) { }
};

// point : &a
class PointNode : public ExpNode{
public:
	VarNode *var;
	PointNode(VarNode *var) : var(var) { type = POINT; };
	virtual Value *Codegen(std::vector<AllocaInst *> &OldBindings, bool isConst=false);
	void append(Node *node) { }
};

class CompUnitNode : public Node{
public:
	std::vector<Node *> v;
	CompUnitNode() { type = COMPUNIT; }
	// int dumpdot(DumpDOT *dumper);
	void append(Node *node);
	virtual Value *Codegen(std::vector<AllocaInst *> &OldBindings, bool isConst=false);
	// void printast(FILE *fp, int indent);
	// void setLoc(Loc *loc);
};

class SimpleDeclNode : public DeclNode{
public:
	VarNode *structvar;
	VarNode *var;
	ExpNode *exp;
	int VarType;
	// int dumpdot(DumpDOT *dumper){ return 0; };
	void append(Node *node){};
	SimpleDeclNode(VarNode *var, int VarType): var(var), VarType(VarType) { type =SIMPKEDECL; };
	SimpleDeclNode(VarNode *structvar, VarNode *var, int VarType): structvar(structvar), var(var), VarType(VarType) { type =SIMPKEDECL;  };
	SimpleDeclNode(VarNode *var, ExpNode *exp ,int VarType): var(var), exp(exp), VarType(VarType) { type =SIMPKEDECL; };
	virtual Value *Codegen(std::vector<AllocaInst *> &OldBindings, bool isConst=false);
};

class ArgsNode : public Node{
public:
	std::vector<SimpleDeclNode *> v;
	ArgsNode(){ type = ARGS; };
	// int dumpdot(DumpDOT *dumper){ return 0; };
	void append(Node *node);
	virtual Value *Codegen(std::vector<AllocaInst *> &OldBindings, bool isConst=false);
};

class InnerStructDeclNode : public Node{
public:
	std::vector<SimpleDeclNode *> v;
	InnerStructDeclNode(){ type = INNERSTRUCTDECL; };
	void append(Node *node);
	virtual Value *Codegen(std::vector<AllocaInst *> &OldBindings, bool isConst=false);
};

class StructNode : public Node{
public:
	VarNode *var;
	InnerStructDeclNode *innerstructdecl;
	// std::vector<char> v;
	StructNode(VarNode *var, InnerStructDeclNode *innerstructdecl) : var(var), innerstructdecl(innerstructdecl) { type = STRUCT; };
	void append(Node *node){};
	virtual Value *Codegen(std::vector<AllocaInst *> &OldBindings, bool isConst = false);
};

class ProtoNode : public Node{
public:
	std::string ret;
	VarNode *var;
	ArgsNode *Args;
	ProtoNode(std::string ret, VarNode *var, ArgsNode *Args): ret(ret) , var(var) , Args(Args) { type = PROTOTYPE; };
	// int dumpdot(DumpDOT *dumper);
	// void printast(FILE *fp, int indent);
	// void setLoc(Loc *loc);
	virtual Function *Codegen(std::vector<AllocaInst *> &OldBindings, bool isConst=false);
	void CreateArgumentAllocas(Function *F);
	void append(Node *node) { }
};

class ExternNode : public Node{
public:
	Node *exte;
	ExternNode(Node *exte) : exte(exte) { type = EXTERN; }
	// int dumpdot(DumpDOT *dumper){ return 0; }
	void append(Node *node){};
	virtual Value *Codegen(std::vector<AllocaInst *> &OldBindings, bool isConst=false);
};

class FuncDefNode : public Node{
	ProtoNode *proto;
	BlockNode *block;
public:
	FuncDefNode(ProtoNode *proto, BlockNode *block) : proto(proto), block(block) { type = FUNCDEF; };
	// int dumpdot(DumpDOT *dumper);
	// void printast(FILE *fp, int indent);
	// void setLoc(Loc *loc);
	virtual Function *Codegen(std::vector<AllocaInst *> &OldBindings, bool isConst=false);
	void append(Node *node) { }
};

class RetNode : public StmtNode{
public:
	ExpNode *exp;
	RetNode(ExpNode *exp) : exp(exp){ type = RETURN; value = exp->value; }
	// int dumpdot(DumpDOT *dumper){ return 0; } ;
	// void printast(FILE *fp, int indent);
	// void setLoc(Loc *loc);
	virtual Value *Codegen(std::vector<AllocaInst *> &OldBindings, bool isConst=false);
	void append(Node *node) { }
	~RetNode();
};

class ConstDefNode : public Node{
public:
	std::vector<ANode *> v;
	int VarType;
	ConstDefNode() { type = CONSTDEF; }
	// int dumpdot(DumpDOT *dumper);
	void append(Node *node);
	virtual Value *Codegen(std::vector<AllocaInst *> &OldBindings, bool isConst=false);
	// void printast(FILE *fp, int indent);
	// void setLoc(Loc *loc);
};

class BreakNode : public Node{
public:
	BreakNode(){type = BREAK;};
	// int dumpdot(DumpDOT *dumper){ return 0; };
	void append(Node *node){};
	virtual Value *Codegen(std::vector<AllocaInst *> &OldBindings, bool isConst=false);
};

class ContinueNode : public Node{
public:
	ContinueNode(){type=CONTINUE;};
	// int dumpdot(DumpDOT *dumper){ return 0; };
	void append(Node *node){};
	virtual Value *Codegen(std::vector<AllocaInst *> &OldBindings, bool isConst=false);
};

class ConstDeclNode : public DeclNode{
	ConstDefNode *constdef;
	int VarType;
public:
	ConstDeclNode(ConstDefNode *constdef, int VarType) : constdef(constdef), VarType(VarType) { type = CONSTDECL; }
	// int dumpdot(DumpDOT *dumper);
	// void printast(FILE *fp, int indent);
	// void setLoc(Loc *loc);
	virtual Value *Codegen(std::vector<AllocaInst *> &OldBindings, bool isConst=false);
	void append(Node *node) { }
};

class ExppNode : public Node{
public:
	std::vector<ExpNode *> v;
	ExppNode() { type = EXPP; }
	// int dumpdot(DumpDOT *dumper);
	void append(Node *node);
	virtual Value *Codegen(std::vector<AllocaInst *> &OldBindings, bool isConst=false);
	// void printast(FILE *fp, int indent);
	// void setLoc(Loc *loc);
};

class VarListNode : public Node{
public:
	std::vector<ExpNode *> v;
	int VarType;
	VarListNode() { type = VARLIST; }
	// int dumpdot(DumpDOT *dumper);
	void append(Node *node);
	virtual Value *Codegen(std::vector<AllocaInst *> &OldBindings, bool isConst=false);
	// void printast(FILE *fp, int indent);
	// void setLoc(Loc *loc);
};

class VarDeclNode : public DeclNode{
	VarListNode *varlist;
	int VarType;
public:
	//std::vector<VarListNode *> v;
	VarDeclNode(VarListNode *varlist, int VarType) :varlist(varlist), VarType(VarType) { type = VARDECL; }
	// int dumpdot(DumpDOT *dumper);
	//void append(VarListNode *node);
	// void printast(FILE *fp, int indent);
	// void setLoc(Loc *loc);
	virtual Value *Codegen(std::vector<AllocaInst *> &OldBindings, bool isConst=false);
	void append(Node *node) { }
};

class StructAssignNode : public ANode{
public:
	VarNode *structvar;
	VarNode *var;
	ExppNode *expp;
	NodeType Ty;
	StructAssignNode(VarNode *structvar, VarNode *var, ExppNode *expp, NodeType Ty):structvar(structvar), var(var), expp(expp), Ty(Ty) { type = STRUCTASSIGN; };
	virtual Value *Codegen(std::vector<AllocaInst *> &OldBindings, bool isConst=false);
	void append(Node *node){};
};

// a = b.c
class SEToVarNode : public ANode{
public:
	VarNode *lvar;
	VarNode *mvar;
	VarNode *rvar;
	NodeType Ty;
	int isPointer;
	SEToVarNode(VarNode *lvar, VarNode *mvar, VarNode *rvar, NodeType Ty) : lvar(lvar), mvar(mvar), rvar(rvar), Ty(Ty) { type = SETOVAR; };
	virtual Value *Codegen(std::vector<AllocaInst *> &OldBindings, bool isConst=false);
	void append(Node *node){};
};

//b.c = a, only in stmt
class VarToSENode : public ANode{
public:
	VarNode *lvar;
	VarNode *mvar;
	ExpNode *exp;
	int rightPointer;
	VarToSENode(VarNode *lvar, VarNode *mvar, ExpNode *exp):lvar(lvar), mvar(mvar), exp(exp) { type = VARTOSE; };
	virtual Value *Codegen(std::vector<AllocaInst *> &OldBindings, bool isConst=false);
	void append(Node *node){};
};

class PointeeAssignNode : public ANode{
public:
	VarNode *lvar;
	VarNode *rvar;
	NodeType Ty;
	PointeeAssignNode(VarNode *lvar, VarNode *rvar, NodeType Ty): lvar(lvar), rvar(rvar), Ty(Ty) { type = POINTEEASSI ; } ;
	virtual Value *Codegen(std::vector<AllocaInst *> &OldBindings, bool isConst=false);
	void append(Node *node){};
};

class PointerAssignNode : public ANode{
public:
	VarNode *structvar;
	VarNode *lvar;
	VarNode *rvar;
	ExpNode *exp;
	NodeType Ty;
	PointerAssignNode(VarNode *lvar, VarNode *rvar, NodeType Ty):lvar(lvar), rvar(rvar), Ty(Ty){ type = POINTERASSIGN; };
	PointerAssignNode(VarNode *structvar, VarNode *lvar, VarNode *rvar, ExpNode *exp, NodeType Ty): structvar(structvar),lvar(lvar), rvar(rvar), exp(exp),Ty(Ty){ type = POINTERASSIGN; };
	PointerAssignNode(VarNode *lvar, VarNode *rvar, ExpNode *exp, NodeType Ty):lvar(lvar) , rvar(rvar), exp(exp), Ty(Ty){ type = POINTERASSIGN; };
	virtual Value *Codegen(std::vector<AllocaInst *> &OldBindings, bool isConst=false);
	void append(Node *node){};
};

class IdentListNode : public Node{
public:
	std::vector<Node *> v;
	IdentListNode(){ type = IDENTLIST; };
	// int dumpdot(DumpDOT *dumper){ return 0; };
	// void printast(FILE *fp, int indent);
	// void setLoc(Loc *loc);
	virtual Value *Codegen(std::vector<AllocaInst *> &OldBindings, bool isConst=false);
	void append(Node *node);
};

class FuncCallNode : public Node{
	VarNode *var;
	// std::vector<int > Args;
	IdentListNode *identlist;
public:
	FuncCallNode(VarNode *var, IdentListNode *identlist) : var(var),identlist(identlist) { type = FUNCCALL; }
	// int dumpdot(DumpDOT *dumper);
	// void printast(FILE *fp, int indent);
	// void setLoc(Loc *loc);
	virtual Value *Codegen(std::vector<AllocaInst *> &OldBindings, bool isConst=false);
	void append(Node *node) { }
};

// decl struct array, but only need it to be local
class StructArrayNode : public ANode{
public:
	VarNode *structvar;
	VarNode *var;
	ExpNode *exp;
	// ExppNode *expp;
	StructArrayNode(VarNode *structvar, VarNode *var, ExpNode *exp): structvar(structvar), var(var), exp(exp) {type = STRUCTARRAY; };
	virtual Value *Codegen(std::vector<AllocaInst *> &OldBindings, bool isConst=false);
	void append(Node *node) {};
};

class StructElementAssignNode : public ANode{
public:
	VarNode *lvar;
	ExpNode *exp;
	VarNode *rvar;
	StructElementAssignNode(VarNode *lvar, ExpNode *exp, VarNode *rvar) : lvar(lvar), exp(exp), rvar(rvar) { type = STRUCTELEMENTASSIGN; };
	virtual Value *Codegen(std::vector<AllocaInst *> &OldBindings, bool isConst=false);
	void append(Node *node) {};
};

class RetAssignNode : public ANode{
public:
	VarNode *var;
	FuncCallNode *funccall;
	NodeType Ty;
	int isPointer;
	RetAssignNode( VarNode *var, FuncCallNode *funccall) : var(var), funccall(funccall){ type = ASSIGNRET; };
	// // int dumpdot(DumpDOT *dumper){};
	// void printast(FILE *fp, int indent);
	// void setLoc(Loc *loc);
	virtual Value *Codegen(std::vector<AllocaInst *> &OldBindings, bool isConst=false);
	void append(Node *node) { };
};

class ArrayRetAssignNode : public ANode{
public:
	VarNode *var;
	ExpNode *exp;
	FuncCallNode *funccall;
	ArrayRetAssignNode( VarNode *var, ExpNode *exp, FuncCallNode *funccall) : var(var), exp(exp), funccall(funccall){ type = ARRAYRETASSIGN; };
	// // int dumpdot(DumpDOT *dumper){};
	// void printast(FILE *fp, int indent);
	// void setLoc(Loc *loc);
	virtual Value *Codegen(std::vector<AllocaInst *> &OldBindings, bool isConst=false);
	void append(Node *node) { };
};

class IntNumNode : public ExpNode {
public:
	int val;
	IntNumNode(int val) : val(val) { type = INTNUM; value = val; }
	// int dumpdot(DumpDOT *dumper);
	// void printast(FILE *fp, int indent);
	// void setLoc(Loc *loc);
	virtual Value *Codegen(std::vector<AllocaInst *> &OldBindings, bool isConst=false);
	void append(Node *node) { }
};

class FloatNumNode : public ExpNode{
public:
	double val;
	FloatNumNode(float val): val(val){ type = FLOATNUM; value = val; };
	virtual Value *Codegen(std::vector<AllocaInst *> &OldBindings, bool isConst=false);
	void append(Node *node) { }
};

// only used to give value to others , such as : t = a[3]
class ArrayNode : public ExpNode{
	VarNode *var;
	ExpNode *exp;
public:
	ArrayNode(VarNode *var, ExpNode *exp) : var(var) , exp(exp) { type = ARRAY; }
	// int dumpdot(DumpDOT *dumper);
	// void printast(FILE *fp, int indent);
	// void setLoc(Loc *loc);
	Value *getPtrIndex(std::vector<AllocaInst *> &OldBindings,bool isConst=false);
	virtual Value *Codegen(std::vector<AllocaInst *> &OldBindings, bool isConst=false);
	void append(Node *node) { }
};

// isPointer : 	0 -- assign to normal     1 -- assign to pointer       2 -- use pointer to assign normal
class AssignNode : public ANode {
	VarNode *var;
	ExpNode *exp;
	int isPointer;
public:
	AssignNode(VarNode *var, ExpNode *exp, NodeType Ty, int isPointer) : var(var) , exp(exp), isPointer(isPointer){ type = Ty; var->value = exp->value;};
	// int dumpdot(DumpDOT *dumper);
	// void printast(FILE *fp, int indent);
	// void setLoc(Loc *loc);
	virtual Value *Codegen(std::vector<AllocaInst *> &OldBindings, bool isConst=false);
	void append(Node *node) { }
};

class ArrayAssignExpNode : public ANode{
	VarNode *var;
	ExpNode *exp1;
	ExpNode *exp2;
public:
	ArrayAssignExpNode(VarNode *var, ExpNode *exp1, ExpNode *exp2) :  var(var) , exp1(exp1) , exp2(exp2) { type = ARRAYASSIGNEXP; }
	// int dumpdot(DumpDOT *dumper);
	// void printast(FILE *fp, int indent);
	// void setLoc(Loc *loc);
	virtual Value *Codegen(std::vector<AllocaInst *> &OldBindings, bool isConst=false);
	void append(Node *node) { }
};

class ArrayAssignExppNode : public ANode {
	VarNode *var;
	ExpNode *exp;
	ExppNode *expp;
public:
	ArrayAssignExppNode(VarNode *var, ExpNode *exp, ExppNode *expp) :  var(var) , exp(exp) , expp(expp) { type = ARRAYASSIGNEXPP; }
	// int dumpdot(DumpDOT *dumper);
	// void printast(FILE *fp, int indent);
	// void setLoc(Loc *loc);
	virtual Value *Codegen(std::vector<AllocaInst *> &OldBindings, bool isConst=false);
	void append(Node *node) { }
};

class BinaryExpNode : public ExpNode {
public:
	int op;
	ExpNode *lhs, *rhs;
	BinaryExpNode(int op, ExpNode *lhs, ExpNode *rhs) : op(op), lhs(lhs), rhs(rhs) {
	 	type = BINARYEXP;
	 	switch(op){
	 		case '+': 	value = lhs->value + rhs->value; break;
	 		case '-': 		value = lhs->value - rhs->value; break;
	 		case '*': 	value = lhs->value * rhs->value; break;
	 		case '/':	 	value = lhs->value / rhs->value; break;
	 		case '%': 	value = (int)lhs->value % (int)rhs->value; break;
	 	};
	};
	// int dumpdot(DumpDOT *dumper);
	// void printast(FILE *fp, int indent);
	// void setLoc(Loc *loc);
	virtual Value *Codegen(std::vector<AllocaInst *> &OldBindings, bool isConst=false);
	void append(Node *node) { }
};

class UnaryExpNode : public ExpNode {
public:
	int op;
	ExpNode *operand;
	UnaryExpNode(int op, ExpNode *operand) : op(op), operand(operand) { type = UNARYEXP; };
	// int dumpdot(DumpDOT *dumper);
	// void printast(FILE *fp, int indent);
	// void setLoc(Loc *loc);
	virtual Value *Codegen(std::vector<AllocaInst *> &OldBindings, bool isConst=false);
	void append(Node *node) { }
};

class CondNode : public Node{
public:
	int relop;
	ExpNode *lexp, *rexp;
	CondNode(int relop, ExpNode *lexp, ExpNode *rexp) : relop(relop), lexp(lexp), rexp(rexp) {
		type = CONDINFIXEXP;

	};
	// int dumpdot(DumpDOT *dumper);
	// void printast(FILE *fp, int indent);
	// void setLoc(Loc *loc);
	virtual Value *Codegen(std::vector<AllocaInst *> &OldBindings, bool isConst=false);
	void append(Node *node) { }
};

class IfElseNode : public Node{
	CondNode *cond;
	StmtNode *block1;
	StmtNode *block2;
public:
	IfElseNode(CondNode *cond, StmtNode *block1, StmtNode *block2) : cond(cond), block1(block1), block2(block2) { type = IFELSE; }
	// int dumpdot(DumpDOT *dumper);
	// void printast(FILE *fp, int indent);
	// void setLoc(Loc *loc);
	virtual Value *Codegen(std::vector<AllocaInst *> &OldBindings, bool isConst=false);
	void append(Node *node) { }
};

class WhileNode : public Node{
	CondNode *cond;
	StmtNode *block;
public:
	WhileNode(CondNode *cond, StmtNode *block) : cond(cond), block(block) { type = WHILE; }
	// int dumpdot(DumpDOT *dumper);
	// void printast(FILE *fp, int indent);
	// void setLoc(Loc *loc);
	virtual Value *Codegen(std::vector<AllocaInst *> &OldBindings, bool isConst=false);
	void append(Node *node) { }
};

#endif
