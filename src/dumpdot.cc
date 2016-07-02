#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstdarg>
#include <map>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include "node.hh"
#include "dumpdot.hh"

extern bool haserror;

//===----------------------------------------------------------------------===//
// Utilities in Dump DOT
//===----------------------------------------------------------------------===//

// There are two ways to create a dot node:
// 1. newNode(num, str1, str2, ...)
//    num corresponds to the number of strings
//    Each string will appear in the generated image as a port
//    All strings are char*
// 2. newNode(1, strs.str().c_str())
//    All elements of the 1, strs.str().c_str()tor are std::string
// newNode returns an integer, which is the number of the corresponding
// node in DOT file.

int DumpDOT::newNode(int num, ...) {
    va_list list;
    va_start(list, num);
    fprintf(fp, "    %d [label = \"", count);
    bool first = true;
    for (int i=0; i<num; i++) {
        char* st = va_arg(list, char*);
        if (!first)
            fprintf(fp, "|");
        first = false;
        if (st[0]=='<')
            fprintf(fp, "<%d> \\<", i);
        else
            fprintf(fp, "<%d> %s", i, st);
    }
    va_end(list);
    fprintf(fp, "\"];\n");
    return count++;
}

int DumpDOT::newNode(std::vector<std::string> list) {
    fprintf(fp, "    %d [label = \"", count);
    bool first = true;
    for (int i=0; i<list.size(); i++) {
        std::string st = list[i];
        if (!first)
            fprintf(fp, "|");
        first = false;
        fprintf(fp, "<%d> %s", i, st.c_str());
    }
    fprintf(fp, "\"];\n");
    return count++;
}

// Draw a line from nSrc node's pSrc port to nDst node.
// If you want it start from the whole node, let pSrc = -1

void DumpDOT::drawLine(int nSrc, int pSrc, int nDst) {
    fprintf(fp, "    %d", nSrc);
    if (pSrc>=0)
        fprintf(fp, ":%d", pSrc);
    fprintf(fp, " -> %d;\n", nDst);
}

//===----------------------------------------------------------------------===//
// Dump AST to DOT
//===----------------------------------------------------------------------===//

// The following functions convert AST to DOT using DumpDOT.
// Each dumpdot returns an integer, which is corresponding number in DOT file.
// 53+29*71 will become:
// digraph {
// node [shape = record];
//     0 [label = "<0> |<1> +|<2> "];
//     1 [label = "<0> 53"];
//     2 [label = "<0> |<1> *|<2> "];
//     3 [label = "<0> 29"];
//     4 [label = "<0> 71"];
//     0:0 -> 1;
//     0:2 -> 2;
//     2:0 -> 3;
//     2:2 -> 4;
// }

// int BlockItemNode::dumpdot(DumpDOT *dumper){
//     int nThis = dumper->newNode(1, "blockitem");
//     return nThis;
// }

int BlockNode::dumpdot(DumpDOT *dumper){
    // if(!haserror){
    //     int nThis = dumper->newNode(1, "block");
    //     return nThis;
    // }
    // else return 0;
}

int BlockItemListNode::dumpdot(DumpDOT *dumper){
    // if(!haserror){
    // std::ostringstream strs;
    // strs << v.size() << " blockitems";

    // int nThis = dumper->newNode(1, strs.str().c_str());
    // for (int i = 0; i < v.size(); ++i){
    //     int nlocal = v[i]->dumpdot(dumper);
    //         dumper->drawLine(nThis, 0, nlocal);
    // }
    // return nThis;
    // }
    // else return 0;
}

int CompUnitNode::dumpdot(DumpDOT *dumper){
    // if(!haserror){
    // std::ostringstream strs;
    // strs << v.size() << " compunits";

    // int nThis = dumper->newNode(1, strs.str().c_str());
    // for (int i = 0; i < v.size(); ++i){
    //     int nlocal = v[i]->dumpdot(dumper);
    //         dumper->drawLine(nThis, 0, nlocal);
    // }
    // return nThis;
    // }
    // else return 0;
}

// int ReturnNode::dumpdot(DumpDOT *dumper){   
//     if(!haserror){
//         int nThis = dumper->newNode(1, rettype.c_str());
//         return nThis;
//     }
//     else
//         return 0;
// }

int ProtoNode::dumpdot(DumpDOT *dumper){
    // if(!haserror){
    //     // need change to 3 if need args
    //     int nThis = dumper->newNode(2, ret.c_str(), "varname");
    //     int rthis = var->dumpdot(dumper);
    //     dumper->drawLine(nThis, 1, rthis);
    //     return nThis;
    // }
    // else
    //     return 0;
}

int FuncDefNode::dumpdot(DumpDOT *dumper){
    // if(!haserror){
    //     int nThis = dumper->newNode(2, "proto", "funcbody");
    //     int lthis  = proto->dumpdot(dumper);
    //     int rthis = block->dumpdot(dumper);
    //     dumper->drawLine(nThis, 0, lthis);
    //     dumper->drawLine(nThis, 1, rthis);
    //     return nThis;
    // }
    // else return 0;
}

int ConstDefNode::dumpdot(DumpDOT *dumper){
    // if(!haserror){
    // std::ostringstream strs;
    // strs << v.size() << " constdefs";

    // int nThis = dumper->newNode(1, strs.str().c_str());
    // for (int i = 0; i < v.size(); ++i){
    //     int nlocal = v[i]->dumpdot(dumper);
    //         dumper->drawLine(nThis, 0, nlocal);
    // }   
    // return nThis;
    // }
    // else return 0;
}

int ConstDeclNode::dumpdot(DumpDOT *dumper){
    // if(!haserror){
    // int nThis = dumper->newNode(2, "const", "decl");
    // int nDef = constdef->dumpdot(dumper);
    //     dumper->drawLine(nThis, 1, nDef);
    // return nThis;
    // }
    // else return 0;
}

int ExppNode::dumpdot(DumpDOT *dumper){
    // if(!haserror){
    // std::ostringstream strs;
    // strs << v.size() << " exps";

    // int nThis = dumper->newNode(1, strs.str().c_str());
    // for (int i = 0; i < v.size(); ++i){
    //     int nlocal = v[i]->dumpdot(dumper);
    //         dumper->drawLine(nThis, 0, nlocal);
    // }   
    // return nThis;
    // }
    // else return 0;
}

int VarListNode::dumpdot(DumpDOT *dumper){
    // if(!haserror){
    // std::ostringstream strs;
    // strs << v.size() << " vars";

    // int nThis = dumper->newNode(1, strs.str().c_str());
    // for (int i = 0; i < v.size(); ++i){
    //     int nlocal = v[i]->dumpdot(dumper);
    //         dumper->drawLine(nThis, 0, nlocal);
    // }   
    // return nThis;
    // }
    // else return 0;
}

int VarDeclNode::dumpdot(DumpDOT *dumper){
    // if(!haserror){
    // int nThis = dumper->newNode(2, "int", "varlist");
    // int nVar = varlist->dumpdot(dumper);
    //     dumper->drawLine(nThis, 1, nVar);
    // return nThis;
    // }
    // else return 0;
}

int FuncCallNode::dumpdot(DumpDOT *dumper){
    // if(!haserror){
    // int nThis = dumper->newNode(1, "funcname");
    // int nName = var->dumpdot(dumper);
    //     dumper->drawLine(nThis, 0, nName);
    // return nThis;
    // }
    // else return 0;
}

int MainNode::dumpdot(DumpDOT *dumper){
    // if(!haserror){
    // int nThis = dumper->newNode(3, "void", "main", "mainbody");
    // int nBody = block->dumpdot(dumper);
    //     dumper->drawLine(nThis, 2, nBody);
    // return nThis;
    // }
    // else return 0;
}

int ArrayNode::dumpdot(DumpDOT *dumper){
    // if(!haserror){
    // int nThis = dumper->newNode(2, "arrname", "exp");
    // int lthis = var->dumpdot(dumper);
    // int rthis = 0;
    // if(exp != NULL)
    //      rthis = exp->dumpdot(dumper);
    //     dumper->drawLine(nThis, 0, lthis);
    // if(rthis != 0)
    //     dumper->drawLine(nThis, 1, rthis);
    // return nThis;
    // }
    // else return 0;
}

int ArrayAssignExpNode::dumpdot(DumpDOT *dumper){
    // if(!haserror){
    // int nThis = dumper->newNode(3, "array",  "=", "exp");
    // int lthis = array->dumpdot(dumper);
    // int rthis = exp->dumpdot(dumper);
    //     dumper->drawLine(nThis, 0, lthis);
    //     dumper->drawLine(nThis, 2, rthis);
    // return nThis;
    // }
    // else return 0;
}

int ArrayAssignExppNode::dumpdot(DumpDOT *dumper){
    // if(!haserror){
    // int nThis = dumper->newNode(3, "array", "=", "expp");
    // int lthis = array->dumpdot(dumper);
    // int rthis = expp->dumpdot(dumper);
    //     dumper->drawLine(nThis, 0, lthis);
    //     dumper->drawLine(nThis, 2, rthis);
    // return nThis;
    // }
    // else return 0;
}

int NumNode::dumpdot(DumpDOT *dumper) {
    // if(!haserror){
    // std::ostringstream strs;
    // strs << val;
    // int nThis = dumper->newNode(1, strs.str().c_str());
    // return nThis;
    // }
    // else return 0;
}

int VarNode::dumpdot(DumpDOT *dumper) {
    // if(!haserror){
    // int nThis = dumper->newNode(1, name->c_str());
    // return nThis;
    // }
    // else return 0;
}

int BinaryExpNode::dumpdot(DumpDOT *dumper) {
    // if(!haserror){
    // char st[2] = " ";
    // st[0] = op;
    // int nThis = dumper->newNode(3, " ", st, " ");
    // int nlhs = lhs->dumpdot(dumper);
    // int nrhs = rhs->dumpdot(dumper);
    //     dumper->drawLine(nThis, 0, nlhs);
    //     dumper->drawLine(nThis, 2, nrhs);
    // return nThis;
    // }
    // else return 0;
}

int UnaryExpNode::dumpdot(DumpDOT *dumper) {
    // if(!haserror){
    // char st[2] = " ";
    // st[0] = op;
    // int nThis = dumper->newNode(2, st, " ");
    // int nOperand = operand->dumpdot(dumper);
    //     dumper->drawLine(nThis, 0, nOperand);
    // return nThis;
    // }
    // else return 0;
}

int AssignNode::dumpdot(DumpDOT *dumper) {
    // if(!haserror){
    // int nThis = dumper->newNode(3, "var", "=", "exp");
    // int nVar = var->dumpdot(dumper);
    // int nExp = exp->dumpdot(dumper);
    //     dumper->drawLine(nThis, 0, nVar);
    //     dumper->drawLine(nThis, 2, nExp);
    // return nThis;
    // }
    // else return 0;
}

int CondNode::dumpdot(DumpDOT *dumper){
    // if(!haserror){
    // int nThis = dumper->newNode(3, "var", "relop", "expp");
    // int lthis = lexp->dumpdot(dumper);
    // int rthis = rexp->dumpdot(dumper);
    //     dumper->drawLine(nThis, 0, lthis);
    //     dumper->drawLine(nThis,1, rthis);
    // return nThis;
    // }
    // else return 0;
}

// int IfNode::dumpdot(DumpDOT *dumper){
    // if(!haserror){
    // int nThis = dumper->newNode(2, "cond", "stmt");
    // int lthis = cond->dumpdot(dumper);
    // int rthis = block->dumpdot(dumper);
    //     dumper->drawLine(nThis, 0, lthis);
    //     dumper->drawLine(nThis, 1, rthis);
    // return nThis;
    // }
    // else return 0;
// }

int IfElseNode::dumpdot(DumpDOT *dumper){
    // if(!haserror){
    // int nThis = dumper->newNode(3, "cond", "stmt1", "stmt2");
    // int lthis = cond->dumpdot(dumper);
    // int mthis = block1->dumpdot(dumper);
    // int rthis = block2->dumpdot(dumper);
    //     dumper->drawLine(nThis, 0, lthis);
    //     dumper->drawLine(nThis, 1, mthis);
    //     dumper->drawLine(nThis, 2, rthis);
    // return nThis;
    // }
    // else return 0;
}

int WhileNode::dumpdot(DumpDOT *dumper){
    // if(!haserror){
    // int nThis = dumper->newNode(2, "cond", "stmt");
    // int lthis = cond->dumpdot(dumper);
    // int rthis = block->dumpdot(dumper);
    //     dumper->drawLine(nThis, 0, lthis);
    //     dumper->drawLine(nThis, 1, rthis);
    // return nThis;
    // }
    // else return 0;
}
