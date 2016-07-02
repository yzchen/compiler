%{
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <vector>
#define DEBUG
#include "node.hh"
#include "util.hh"
#include "global.hh"
extern int yylex ();
extern void yyerror (const char *msg);
CompUnitNode     *root;
vector<Node *>    nodelist;
extern bool haserror;

void realse_nodelist(){
    for (int i = 0; i < nodelist.size(); ++i){
        nodelist.pop_back();
    }
}

%}

%union
{
    int  num;
    float floatnum;
    std::string *ident;
    Node *node;
}

%locations

%token eq_tok neq_tok lt_tok le_tok gt_tok ge_tok space_tok
%token while_tok if_tok main_tok void_tok int_tok float_tok const_tok else_tok return_tok
%token intnum_tok floatnum_tok ident_tok eol_tok err_tok extern_tok break_tok continue_tok struct_tok

%left '-' '+'
%left '*' '/' '%'

%type <num> intnum_tok eq_tok neq_tok lt_tok le_tok gt_tok ge_tok space_tok
%type <floatnum> floatnum_tok
%type <ident> ident_tok
%type <node> compUnit Decl ConstDecl ConstDef VarDecl FuncDef
%type <node> Block Cond Exp Expp VarList Ident BlockItemList BlockItem Stmt
%type <node> Prototype Args SimpleDecl IdentList ExternDecl InnerStructDecl StructDecl

%%
compUnit :
            {
                // debug("compUnit ::= empty \n");
                $$ = new CompUnitNode();
                root = (CompUnitNode *)$$;
                // nodelist.push_back((Node *)$$);
            }
            |compUnit ExternDecl ';'
            {
                // debug("compUnit ::= compUnit , ExternDecl \n");
                $$ = (CompUnitNode *)$1;
                ((CompUnitNode *)$$)->append((Node *)$2);
                root = (CompUnitNode *)$$;
                // nodelist.push_back((Node *)$$);
            }
            |compUnit  Decl
            {
                // debug("compUnit ::= compUnit , Decl \n");
                $$ = (CompUnitNode *)$1;
                ((CompUnitNode *)$$)->append((Node *)$2);
                root = (CompUnitNode *)$$;
                // nodelist.push_back((Node *)$$);
            }
            | compUnit struct_tok ident_tok '{' InnerStructDecl '}' ';'
            {
                $$ = (CompUnitNode *)$1;
                ((CompUnitNode *)$$)->append(new StructNode(new VarNode((std::string *)$3), (InnerStructDeclNode *)$5));
                root = (CompUnitNode *)$$;
            }
            |compUnit  FuncDef
            {
                // debug("compUnit ::= compUnit , FuncDef \n");
                $$ = (CompUnitNode *)$1;
                ((CompUnitNode *)$$)->append((Node *)$2);
                root = (CompUnitNode *)$$;
                // nodelist.push_back((Node *)$$);
            }
            ;

Decl    :  ConstDecl
            {
                // debug("Decl ::= ConstDecl \n");
                $$ = $1;
             }
            |  VarDecl
             {
                // debug("Decl ::= VarDecl \n");
                $$ = $1;
             }
            | StructDecl
            {
                $$ = $1;
            }
            ;

// only decl
StructDecl :
            struct_tok ident_tok ident_tok ';'
            {
                    $$ = new StructAssignNode(new VarNode((std::string *)$2), new VarNode((std::string *)$3), 0,DECLASSIGN);
            }
           |struct_tok ident_tok ident_tok '=' '{' Expp '}' ';'
           {
                    $$ = new StructAssignNode(new VarNode((std::string *)$2), new VarNode((std::string *)$3), (ExppNode *)$6,DECLASSIGN);
           }
           |struct_tok ident_tok ident_tok '[' Exp ']' ';'
           {
                    $$ = new StructArrayNode(new VarNode((std::string *)$2), new VarNode((std::string *)$3), (ExpNode *)$5);
           }
           |struct_tok ident_tok '*' ident_tok ';'
            {
                    // printf("this one\n");
                     $$ = new PointerAssignNode(new VarNode((std::string *)$2), new VarNode((std::string *)$4), 0, 0, DECLASSIGN);
                     dynamic_cast<PointerAssignNode *>($$)->VarType = 7;
            }
           |struct_tok ident_tok '*' ident_tok '=' ident_tok ';'
            {
                     $$ = new PointerAssignNode(new VarNode((std::string *)$2), new VarNode((std::string *)$4), new VarNode((std::string *)$4), 0, DECLASSIGN);
                     dynamic_cast<PointerAssignNode *>($$)->VarType = 7;
            }
           |struct_tok ident_tok '*' ident_tok '=' ident_tok '[' Exp ']' ';'
            {
                     $$ = new PointerAssignNode(new VarNode((std::string *)$2), new VarNode((std::string *)$4), new VarNode((std::string *)$4), (ExpNode *)$8, DECLASSIGN);
                     dynamic_cast<PointerAssignNode *>($$)->VarType = 7;
            }
           ;

ExternDecl:
            extern_tok Prototype
           {
                // debug("ExternDecl ::= extern Prototype \n");
                $$ = new ExternNode((ProtoNode *)$2);
                // nodelist.push_back((Node *)$$);
           }
           | extern_tok SimpleDecl
           {
                // debug("ExternDecl ::= extern SimpleDecl \n");
                $$ = new ExternNode((SimpleDeclNode *)$2);
                // nodelist.push_back((Node *)$$);
           }
           ;

SimpleDecl:
            int_tok ident_tok
            {
                // debug("SimpleDecl ::= int ident \n");
                $$ = new SimpleDeclNode(new VarNode((std::string *)$2), 0);
                // nodelist.push_back((Node *)$$);
            }
           | float_tok ident_tok
            {
                $$ = new SimpleDeclNode(new VarNode((std::string *)$2), 1);
            }
            | int_tok '*' ident_tok
            {
                $$ = new SimpleDeclNode(new VarNode((std::string *)$3), 3);
            }
            | float_tok '*' ident_tok
            {
                $$ = new SimpleDeclNode(new VarNode((std::string *)$3), 4);
            }
            | int_tok ident_tok '[' Exp ']'
            {
                // debug("SimpleDecl ::= int ident [ Exp ] \n");
                $$ = new SimpleDeclNode(new VarNode((std::string *)$2), (ExpNode *)$4, 3);
            }
            |float_tok ident_tok '[' Exp ']'
            {
                $$ = new SimpleDeclNode(new VarNode((std::string *)$2), (ExpNode *)$4, 4);
            }
            | int_tok ident_tok '['  ']'
            {
                $$ = new SimpleDeclNode(new VarNode((std::string *)$2), (ExpNode *)0, 3);
            }
            |float_tok ident_tok '['  ']'
            {
                $$ = new SimpleDeclNode(new VarNode((std::string *)$2), (ExpNode *)0, 4);
            }
            |struct_tok ident_tok '*' ident_tok
            {
                $$ = new SimpleDeclNode(new VarNode((std::string *)$2), new VarNode((std::string *)$4), 5);
            }
            ;

InnerStructDecl :
            {
                    $$ = new InnerStructDeclNode();
            }
            | SimpleDecl ';'
            {
                    // debug("InnerStructDecl ::= Args \n");
                    $$ = new InnerStructDeclNode();
                    $$->append((SimpleDeclNode *)$1);
            }
            | InnerStructDecl  SimpleDecl ';'
            {
                    // debug("InnerStructDecl ::= InnerStructDecl Args ; \n");
                    $$ = (InnerStructDeclNode *)$1;
                    $$->append((SimpleDeclNode *)$2);
            }
            ;

Args :
            {
                // debug("Args ::= empty \n");
                $$ = new ArgsNode();
                // nodelist.push_back((Node *)$$);
            }
            | SimpleDecl
            {
                // debug("Args ::= SimpleDecl \n");
                $$ = new ArgsNode();
                $$->append((SimpleDeclNode *)$1);
                // nodelist.push_back((Node *)$$);
            }
            | Args ',' SimpleDecl
            {
                // debug("Args ::= Args , SimpleDecl \n");
                $$ = (ArgsNode *)$1 ;
                $$->append((SimpleDeclNode *)$3);
                // nodelist.push_back((Node *)$$);
            }
            ;

Prototype :
             void_tok ident_tok '(' Args ')'
            {
                    // debug("Prototype := void ident( Args ) \n ");
                    $$ = new ProtoNode("void" , new VarNode((std::string *)$2), (ArgsNode *)$4);
                    // nodelist.push_back((Node *)$$);
            }
            | int_tok ident_tok '(' Args ')'
            {
                    // debug("Prototype := int ident( Args ) \n ");
                    $$ = new ProtoNode("int", new VarNode((std::string *)$2), (ArgsNode *)$4);
                    // nodelist.push_back((Node *)$$);
            }
            | float_tok ident_tok '(' Args ')'
            {
                    // debug("Prototype := int ident( Args ) \n ");
                    $$ = new ProtoNode("float", new VarNode((std::string *)$2), (ArgsNode *)$4);
                    // nodelist.push_back((Node *)$$);
            }
            | int_tok '*' ident_tok '(' Args ')'
            {
                    // debug("Prototype := int ident( Args ) \n ");
                    $$ = new ProtoNode("int *", new VarNode((std::string *)$3), (ArgsNode *)$5);
                    // nodelist.push_back((Node *)$$);
            }
            | float_tok '*' ident_tok '(' Args ')'
            {
                    // debug("Prototype := int ident( Args ) \n ");
                    $$ = new ProtoNode("float *", new VarNode((std::string *)$3), (ArgsNode *)$5);
                    // nodelist.push_back((Node *)$$);
            }
            ;

FuncDef :
             Prototype Block
            {
                    // debug("FuncDef ::= Prototype Block \n");
                    $$ = new FuncDefNode((ProtoNode *)$1, (BlockNode *)$2);
                    // nodelist.push_back((Node *)$$);
             }
            // |void_tok ident_tok ')' Block               //error
            // {
            //         error("FuncDef ::= void ident ) Block \n");
            //         haserror = true;
            //         realse_nodelist();
            //         sprintf(tmpcmd, "sed -n %dp %s | sed 's/\t/ /g' ", @3.first_line, infile_name);
            //         system(tmpcmd);
            //         offset = @3.first_column-2;
            //         for (int i = 0; i < offset; ++i)
            //             fprintf(stderr, " ");
            //         fprintf(stderr, "^\n");
            //  }
            // |void_tok ident_tok '(' Block               //error
            // {
            //         error("FuncDef ::= void ident ( Block \n");
            //         haserror = true;
            //         realse_nodelist();
            //         sprintf(tmpcmd, "sed -n %dp %s | sed 's/\t/ /g' ", @3.first_line, infile_name);
            //         system(tmpcmd);
            //         offset = @3.first_column;
            //         for (int i = 0; i < offset; ++i)
            //             fprintf(stderr, " ");
            //         fprintf(stderr, "^\n");
            //  }
           // | void_tok main_tok '(' ')' Block
           //  {
           //          debug("FuncDef ::= void main() Block \n");
           //          $$ = new MainNode((BlockNode *)$5);
           //          // nodelist.push_back((Node *)$$);
           //  }
            // | void_tok main_tok ')' Block           //error
            // {
            //         error("FuncDef ::= void main ) Block \n");
            //         haserror = true;
            //         realse_nodelist();
            //         sprintf(tmpcmd, "sed -n %dp %s | sed 's/\t/ /g' ", @3.first_line, infile_name);
            //         system(tmpcmd);
            //         offset = @3.first_column-2;
            //         for (int i = 0; i < offset; ++i)
            //             fprintf(stderr, " ");
            //         fprintf(stderr, "^\n");
            // }
            // |void_tok main_tok '(' Block               //error
            // {
            //         error("FuncDef ::= void main ( Block \n");
            //         haserror = true;
            //         realse_nodelist();
            //         sprintf(tmpcmd, "sed -n %dp %s | sed 's/\t/ /g' ", @3.first_line, infile_name);
            //         system(tmpcmd);
            //         offset = @3.first_column;
            //         for (int i = 0; i < offset; ++i)
            //             fprintf(stderr, " ");
            //         fprintf(stderr, "^\n");
            //  }
            ;

ConstDecl :
             const_tok int_tok ConstDef ';'
            {
                    // debug("ConstDecl ::= const int ConstDef ;\n");
                    $$ = new ConstDeclNode((ConstDefNode *)$3, 0);
                    // nodelist.push_back((Node *)$$);
            }
            |const_tok float_tok ConstDef ';'
            {
                   $$ = new ConstDeclNode((ConstDefNode *)$3, 1);
            }
            // | const_tok ConstDef ';'                                //warning
            // {
            //         warning("ConstDecl ::= const ConstDef \n");
            //         $$ = new ConstDeclNode((ConstDefNode *)$2);
            //         // nodelist.push_back((Node *)$$);
            //         sprintf(tmpcmd, "sed -n %dp %s | sed 's/\t/ /g' ", @2.first_line, infile_name);
            //         system(tmpcmd);
            //         offset = @2.first_column-1;
            //         for (int i = 0; i < offset-1; ++i)
            //             fprintf(stderr, " ");
            //         fprintf(stderr, "^\n");
            //  }
             ;

ConstDef  :
             ident_tok '=' Exp
            {
                    // debug("ConstDef ::= id assign exp \n");
                    $$ = new ConstDefNode();
                    $$->append((Node *)new AssignNode(new VarNode((std::string *)$1), (ExpNode *)$3, DECLASSIGN, 0));
                    // nodelist.push_back((Node *)$$);
            }
            | '*' ident_tok '=' '&' ident_tok
            {
                    $$ = new ConstDefNode();
                    $$->append((Node *)(new AssignNode(new VarNode((std::string *)$2),  (ExpNode *)(new VarNode((std::string *)$5)), DECLASSIGN, 1)));
            }
            |ident_tok '[' ']' '=' '{' Expp '}'
            {
                    // debug("ConstDef ::= id [] assign { Exp {, Exp} } \n");
                    $$ = new ConstDefNode();
                    $$->append((Node *)new ArrayAssignExppNode(new VarNode((std::string *)$1), new IntNumNode(-1), (ExppNode *)$6));
                    // nodelist.push_back((Node *)$$);
             }
            |ident_tok '[' intnum_tok ']' '=' '{' Expp '}'
            {
                    // debug("ConstDef ::= id [num] assign { Exp {, Exp} } \n");
                    $$ = new ConstDefNode();
                    $$->append((Node *)new ArrayAssignExppNode(new VarNode((std::string *)$1), new IntNumNode((int)$3), (ExppNode *)$7));
                    // nodelist.push_back((Node *)$$);
             }
            |ConstDef  ',' ident_tok '=' Exp
            {
                    // debug("ConstDef ::= ConstDef , id assign exp \n");
                    $$ = (ConstDefNode *)$1;
                    $$->append((Node *)new AssignNode(new VarNode((std::string *)$3), (ExpNode *)$5, DECLASSIGN, 0));
                    // nodelist.push_back((Node *)$$);
             }
            | ConstDef ',' '*' ident_tok '=' '&' ident_tok
            {
                    $$ = (ConstDefNode *)$1;
                    $$->append((Node *)(new AssignNode(new VarNode((std::string *)$4),  (ExpNode *)(new VarNode((std::string *)$7)), DECLASSIGN, 1)));
            }
            | ConstDef ',' ident_tok '[' ']' '=' '{' Expp '}'
            {
                    // debug("ConstDef ::= id [] assign { Exp {, Exp} } \n");
                    $$ = (ConstDefNode *)$1;
                    $$->append((Node *)new ArrayAssignExppNode(new VarNode((std::string *)$3), new IntNumNode(-1), (ExppNode *)$8));
                    // nodelist.push_back((Node *)$$);
             }
            | ConstDef  ',' ident_tok '[' intnum_tok ']' '=' '{' Expp '}'
            {
                    // debug("ConstDef ::= ConstDef , id [Exp] assign { Expp } \n");
                    $$ = (ConstDefNode *)$1;
                    $$->append((Node *)new ArrayAssignExppNode(new VarNode((std::string *)$3), new IntNumNode((int)$5), (ExppNode *)$9));
                    // nodelist.push_back((Node *)$$);
             }
             ;

Expp :  Exp
            {
                    // debug("Expp ::= Exp \n");
                    $$ = new ExppNode();
                    $$->append((Node *)$1);
                    // nodelist.push_back((Node *)$$);
            }
            |Expp ',' Exp
            {
                     // debug("Expp ::= Expp, Exp \n");
                     $$ = (ExppNode *)$1;
                     $$->append((Node *)$3);
                     // nodelist.push_back((Node *)$$);
            }
            ;

VarDecl :
            int_tok VarList ';'
            {
                    // debug("IdentDecl ::= int VarList ; \n");
                    $$ = new VarDeclNode((VarListNode *)$2, 0);
                    // nodelist.push_back((Node *)$$);
             }
             | float_tok VarList ';'
             {
                    $$ = new VarDeclNode((VarListNode *)$2, 1);
             }
            ;

VarList :
            VarList ',' Ident
            {
                    // debug("VarList ::= VarList, Ident \n");
                    $$ = (VarListNode *)$1;
                    $$->append((Node *)$3);
                    // nodelist.push_back((Node *)$$);
            }
            |Ident
            {
                    // debug("VarList ::= Ident \n");
                    // printf("identlist\n");
                    $$ = new VarListNode();
                    $$->append((Node *)$1);
                    // nodelist.push_back((Node *)$$);
            }
            ;

// used in define var
Ident :  ident_tok
            {
                    // debug("Ident ::= id \n");
                    $$ = new AssignNode(new VarNode((std::string *)$1), new IntNumNode(65535), DECLASSIGN, 0);
                    // printf("ident got\n");
                    // nodelist.push_back((Node *)$$);
             }
            | '*' ident_tok
            {
                     $$ = new PointerAssignNode(new VarNode((std::string *)$2), 0, DECLASSIGN);
            }
            | '*' ident_tok '=' ident_tok               // only in decl
            {
                    $$ = new PointerAssignNode(new VarNode((std::string *)$2), new VarNode((std::string *)$4), PTOP);
            }
            | '*'  ident_tok '=' ident_tok '.' ident_tok
            {
                    $$ = new SEToVarNode(new VarNode((std::string *)$2), new VarNode((std::string *)$4), new VarNode((std::string *)$6), DECLASSIGN);
                    dynamic_cast<SEToVarNode *>($$)->isPointer = 1;
            }
            | '*' ident_tok '=' '&' ident_tok
            {
                     $$ = new PointerAssignNode(new VarNode((std::string *)$2), new VarNode((std::string *)$5), DECLASSIGN);
                     // printf("%d\n", ((ExpNode *)$5)->type);
            }
            | '*' ident_tok '=' '&' ident_tok '[' Exp ']'
            {
                     $$ = new PointerAssignNode(new VarNode((std::string *)$2), new VarNode((std::string *)$5), (ExpNode *)$7, DECLASSIGN);
            }
            | ident_tok '=' '*' ident_tok
            {
                     $$ = new PointeeAssignNode(new VarNode((std::string *)$1), new VarNode((std::string *)$4), DECLASSIGN);
            }
            | ident_tok '=' ident_tok '.' ident_tok
            {
                  // printf("done\n");
                  $$ = new SEToVarNode(new VarNode((std::string *)$1), new VarNode((std::string *)$3), new VarNode((std::string *)$5), DECLASSIGN);
                  dynamic_cast<SEToVarNode *>($$)->isPointer = 0;
            }
             |ident_tok '=' ident_tok '(' IdentList ')'
            {
                        // printf("a  = f()\n");
                        $$ = new RetAssignNode(new VarNode((std::string *)$1), new FuncCallNode(new VarNode((std::string *)$3), (IdentListNode *)$5));
                       dynamic_cast<RetAssignNode *>($$)->Ty= DECLASSIGN;
                       dynamic_cast<RetAssignNode *>($$)->isPointer= 0;
            }
             | '*' ident_tok '=' ident_tok '(' IdentList ')'
            {
                        // printf("a  = f()\n");
                        $$ = new RetAssignNode(new VarNode((std::string *)$2), new FuncCallNode(new VarNode((std::string *)$4), (IdentListNode *)$6));
                       dynamic_cast<RetAssignNode *>($$)->Ty= DECLASSIGN;
                       dynamic_cast<RetAssignNode *>($$)->isPointer= 1;
            }
            | ident_tok '[' Exp ']'
            {
                    // debug("Ident ::= id [ Exp ] \n");
                    $$ = new ArrayAssignExppNode(new VarNode((std::string *)$1), (ExpNode *)$3, new ExppNode());
                    // nodelist.push_back((Node *)$$);
             }
            | ident_tok '=' Exp
            {
                    // debug("Ident ::= id assign Exp \n");
                    $$ = new AssignNode(new VarNode((std::string *)$1), (ExpNode *)$3, DECLASSIGN, 0);
                    // nodelist.push_back((Node *)$$);
            }
            |ident_tok '[' ']' '=' '{' Expp '}'
            {
                    // debug("Ident ::= id [ ] assign { Expp } \n");
                    $$ = new ArrayAssignExppNode(new VarNode((std::string *)$1), 0, (ExppNode *)$6);
                    // nodelist.push_back((Node *)$$);
            }
            |ident_tok '[' Exp ']' '=' '{' Expp '}'
            {
                    // debug("Ident ::= id [ num ] assign { Expp } \n");
                    $$ = new ArrayAssignExppNode(new VarNode((std::string *)$1), (ExpNode *)$3, (ExppNode *)$7);
                    // nodelist.push_back((Node *)$$);
            }
            // |ident_tok '=' ident_tok '(' IdentList ')' ';'
            // {
            //         // printf("a = f()\n");
            //             $$ = new RetAssignNode(new VarNode((std::string *)$1), new FuncCallNode(new VarNode((std::string *)$3), (IdentListNode *)$5));
            // }
            ;

Block :   '{' BlockItemList '}'
            {
                // debug("Block ::= BlockItemList \n");
                $$ = new BlockNode((BlockItemListNode *)$2);
                // nodelist.push_back((Node *)$$);
                $$ = $2;
            }
            ;

BlockItemList :
            {
                 // debug("BlockItemList ::= empty \n ");
                 $$ = new BlockItemListNode();
                 // nodelist.push_back((Node *)$$);
            }
            |BlockItemList BlockItem
            {
                // debug("BlockItemList ::= BlockItemList , BlockItem \n");
                $$ = (BlockItemListNode *)$1;
                $$->append((Node *)$2);
                // nodelist.push_back((Node *)$$);
            }
            ;

BlockItem :
             Decl
            {
                // debug("BlockItem ::= Decl \n");
                $$ = $1;
            }
            | Stmt
            {
                // debug("BlockItem ::= Stmt \n");
                $$ = $1;
            }
            ;

IdentList:
            {
                // debug("Ident_List ::= empty \n");
                $$ = new IdentListNode();
                // nodelist.push_back((Node *)$$);
            }
            | ident_tok
            {
                // debug("Ident_List ::= ident \n");
                $$ = new IdentListNode();
                // printf("%s\n", (std::string *)$1->c_str());
                $$->append(new VarNode((std::string *)$1));
                // nodelist.push_back((Node *)$$);
            }
            | intnum_tok
            {
                $$ = new IdentListNode();
                // printf("%s\n", (std::string *)$1->c_str());
                $$->append(new IntNumNode((int)$1));
            }
            | IdentList ',' ident_tok
            {
                // debug("Ident_List ::= IdentList , ident \n");
                $$ = (IdentListNode *)$1 ;
                $$->append(new VarNode((std::string *)$3));
                // nodelist.push_back((Node *)$$);
            }
           | IdentList ',' intnum_tok
           {
                $$ = (IdentListNode *)$1 ;
                $$->append(new IntNumNode((int)$3));
           }
            ;

Stmt :
            ident_tok '=' Exp ';'
            {
                    // debug("Stmt ::= Ident = Exp \n");
                    $$ = new AssignNode(new VarNode((std::string *)$1), (ExpNode *)$3, STMTASSIGN, 0);
                    // nodelist.push_back((Node *)$$);
             }
            | ident_tok '=' '*' ident_tok ';'
            {
                    $$ = new PointeeAssignNode(new VarNode((std::string *)$1), new VarNode((std::string *)$4), STMTASSIGN);
            }
            | ident_tok '=' '{' Expp '}' ';'
            {
                   $$ = new StructAssignNode(0, new VarNode((std::string *)$1), (ExppNode *)$4, STMTASSIGN);
            }
            | ident_tok '=' ident_tok '.' ident_tok ';'
            {
                  // printf("done\n");
                  $$ = new SEToVarNode(new VarNode((std::string *)$1), new VarNode((std::string *)$3), new VarNode((std::string *)$5), STMTASSIGN);
            }
            | ident_tok '.' ident_tok '=' Exp ';'
            {
                  $$ = new VarToSENode(new VarNode((std::string *)$1), new VarNode((std::string *)$3), (ExpNode *)$5);
            }
            | ident_tok '.' ident_tok '=' '&' ident_tok ';'
            {
                  $$ = new VarToSENode(new VarNode((std::string *)$1), new VarNode((std::string *)$3), (ExpNode *)(new VarNode((std::string *)$6)));
                  dynamic_cast<VarToSENode *>($$)->rightPointer = 1;
            }
            | ident_tok '=' '&' ident_tok '[' Exp ']' ';'
            {
                     $$ = new PointerAssignNode(new VarNode((std::string *)$1), new VarNode((std::string *)$4), (ExpNode *)$6, STMTASSIGN);
            }
            |ident_tok '[' Exp ']' '=' Exp ';'
            {
                    // debug("Stmt ::= Ident[Exp] = Exp \n");
                    $$ = new ArrayAssignExpNode(new VarNode((std::string *)$1), (ExpNode *)$3, (ExpNode *)$6);
                    // nodelist.push_back((Node *)$$);
            }
            |ident_tok '(' IdentList ')' ';'
            {
            	     $$ = new FuncCallNode(new VarNode((std::string *)$1), (IdentListNode *)$3);
            }
            |ident_tok '=' ident_tok '(' IdentList ')' ';'
            {
            		// printf("a = f()\n");
            	    	$$ = new RetAssignNode(new VarNode((std::string *)$1), new FuncCallNode(new VarNode((std::string *)$3), (IdentListNode *)$5));
                            dynamic_cast<RetAssignNode *>($$)->Ty= STMTASSIGN;
            }
            |ident_tok '[' Exp ']' '=' ident_tok '(' IdentList ')' ';'
            {
            	    	$$ = new ArrayRetAssignNode(new VarNode((std::string *)$1), (ExpNode *)$3, new FuncCallNode(new VarNode((std::string *)$6), (IdentListNode *)$8));
            }
            |break_tok ';'
            {
                        // debug(" Stmt ::= break ");
                        $$ = new BreakNode();
                        // // nodelist.push_back((Node *)$$);
            }
            |continue_tok ';'
            {
                        // debug(" Stmt ::= break ");
                        $$ = new ContinueNode();
                        // // nodelist.push_back((Node *)$$);
            }
            | Block
             {
                    // debug("Stmt ::= Block \n");
                    $$ = $1;
             }
            |return_tok Exp ';'
            {
                // debug("FUNCRET := return Exp \n");
                $$ = new RetNode((ExpNode *)$2);
                // // nodelist.push_back((Node *)$$);
            }
            |if_tok '(' Cond ')' Stmt
            {
                    // debug("Stmt ::= if( Cond ) Stmt \n");
                    $$ = new IfElseNode((CondNode *)$3, (StmtNode * )$5,0);
                    // // nodelist.push_back((Node *)$$);
             }
            // |if_tok Cond ')' Stmt                       //error
            // {
            //         error("Stmt ::= if Cond ) Stmt \n");
            //         haserror = true;
            //         realse_nodelist();
            //         sprintf(tmpcmd, "sed -n %dp %s | sed 's/\t/ /g' ", @2.first_line, infile_name);
            //         system(tmpcmd);
            //         offset = @2.first_column-2;
            //         for (int i = 0; i < offset; ++i)
            //             fprintf(stderr, " ");
            //         fprintf(stderr, "^\n");
            //  }
            // |if_tok '(' Cond Stmt                       //error
            // {
            //         error("Stmt ::= if ( Cond Stmt \n");
            //         haserror = true;
            //         realse_nodelist();
            //         sprintf(tmpcmd, "sed -n %dp %s | sed 's/\t/ /g' ", @3.last_line, infile_name);
            //         system(tmpcmd);
            //         offset = @3.last_column;
            //         for (int i = 0; i < offset; ++i)
            //             fprintf(stderr, " ");
            //         fprintf(stderr, "^\n");
            //  }
            |if_tok '(' Cond ')' Stmt else_tok Stmt
            {
                    // debug("Stmt ::= if( Cond ) Stmt else Stmt \n");
                    $$ = new IfElseNode((CondNode *)$3, (StmtNode *)$5, (StmtNode *)$7);
                    // // nodelist.push_back((Node *)$$);
             }
            // |if_tok Cond ')' Stmt else_tok Stmt     //error
            // {
            //         error("Stmt ::= if Cond ) Stmt else Stmt \n");
            //         haserror = true;
            //         realse_nodelist();
            //         sprintf(tmpcmd, "sed -n %dp %s | sed 's/\t/ /g' ", @2.first_line, infile_name);
            //         system(tmpcmd);
            //         offset = @2.first_column-2;
            //         for (int i = 0; i < offset; ++i)
            //             fprintf(stderr, " ");
            //         fprintf(stderr, "^\n");
            //  }
            // |if_tok '(' Cond Stmt else_tok Stmt     //error
            // {
            //         error("Stmt ::= if ( Cond Stmt else Stmt \n");
            //         haserror = true;
            //         realse_nodelist();
            //         sprintf(tmpcmd, "sed -n %dp %s | sed 's/\t/ /g' ", @3.last_line, infile_name);
            //         system(tmpcmd);
            //         offset = @3.last_column;
            //         for (int i = 0; i < offset; ++i)
            //             fprintf(stderr, " ");
            //         fprintf(stderr, "^\n");
            //  }
            | while_tok '(' Cond ')' Stmt
            {
                    // debug("Stmt ::= while ( Cond ) Stmt \n");
                    $$ = new WhileNode((CondNode *)$3, (StmtNode *)$5);
                    // nodelist.push_back((Node *)$$);
            }
           //  | while_tok Cond ')' Stmt       //error
           //  {
           //          error("Stmt ::= while Cond ) Stmt \n");
           //          haserror = true;
           //          realse_nodelist();
           //          sprintf(tmpcmd, "sed -n %dp %s | sed 's/\t/ /g' ", @2.first_line, infile_name);
           //          system(tmpcmd);
           //          offset = @2.first_column-2;
           //          for (int i = 0; i < offset; ++i)
           //              fprintf(stderr, " ");
           //          fprintf(stderr, "^\n");
           //  }
           // | while_tok '(' Cond Stmt       //error
           //  {
           //          error("Stmt ::= while ( Cond Stmt \n");
           //          haserror = true;
           //          realse_nodelist();
           //          sprintf(tmpcmd, "sed -n %dp %s | sed 's/\t/ /g' ", @3.last_line, infile_name);
           //          system(tmpcmd);
           //          offset = @3.last_column;
           //          for (int i = 0; i < offset; ++i)
           //              fprintf(stderr, " ");
           //          fprintf(stderr, "^\n");
           //  }
            | ';'
            {
                    // debug("Stmt ::= ; \n");
            }
            ;

Exp :     intnum_tok
            {
                    // debug ("Exp ::= num \n");
                    $$ = new IntNumNode((int)$1);
                    // nodelist.push_back((Node *)$$);
             }
            | floatnum_tok
            {
                    // printf("%f\n", $1);
                    $$ = new FloatNumNode((float)$1);
                    // printf("%f\n",(float)$1);
            }
            | ident_tok
            {
                    // debug ("Exp ::= Ident \n");
                    $$ = new VarNode((std::string *)$1);
                    // nodelist.push_back((Node *)$$);
             }
            | '&' ident_tok
            {
                   $$ = new PointNode(new VarNode((std::string *)$2));
            }
            | ident_tok '[' Exp ']'                 // as a right value
            {
                    // debug("Exp ::= Ident [ Exp ] \n");
                    $$ = new ArrayNode(new VarNode((std::string *)$1), (ExpNode *)$3);
                    // nodelist.push_back((Node *)$$);
            }
            |Exp '+' Exp
            {
                    // debug("Exp ::= Exp add Exp \n");
                    $$ = new BinaryExpNode('+', (ExpNode *)$1, (ExpNode *)$3);
                    // nodelist.push_back((Node *)$$);
             }
            |Exp '-' Exp
            {
                    // debug("Exp ::= Exp minus Exp \n");
                    $$ = new BinaryExpNode('-', (ExpNode *)$1, (ExpNode *)$3);
                    // nodelist.push_back((Node *)$$);
            }
            |Exp '*' Exp
            {
                    // debug("Exp ::= Exp mul Exp \n");
                    $$ = new BinaryExpNode('*', (ExpNode *)$1, (ExpNode *)$3);
                    // nodelist.push_back((Node *)$$);
             }
            |Exp '/' Exp
            {
                    // debug("Exp ::= Exp div Exp \n");
                    $$ = new BinaryExpNode('/', (ExpNode *)$1, (ExpNode *)$3);
                    // nodelist.push_back((Node *)$$);
             }
            |Exp '%' Exp
            {
                    // debug("Exp ::= Exp mod Exp \n");
                    $$ = new BinaryExpNode('%', (ExpNode *)$1, (ExpNode *)$3);
                    // nodelist.push_back((Node *)$$);
             }
            | '-' Exp %prec '-'
            {
                    // debug("Exp ::= - Exp \n");
                    $$ = new UnaryExpNode('-', (ExpNode *)$2);
                    // nodelist.push_back((Node *)$$);
            }
            | '(' Exp ')'
            {
                    // debug ("Exp ::= ( Exp ) \n");
                    $$ = $2;
             }
            // | '(' Exp
            // {
            //         error("Exp ::=  '(' Exp \n");         //error
            //         haserror = true;
            //         realse_nodelist();
            //         sprintf(tmpcmd, "sed -n %dp %s | sed 's/\t/ /g' ", @2.last_line, infile_name);
            //         system(tmpcmd);
            //         offset = @2.last_column;
            //         for (int i = 0; i < offset; ++i)
            //             fprintf(stderr, " ");
            //         fprintf(stderr, "^\n");
            // }
            // | Exp error ')'                                            //error
            // {
            //         haserror = true;
            //         realse_nodelist();
            //         sprintf(tmpcmd, "sed -n %dp %s | sed 's/\t/ /g' ", @1.first_line, infile_name);
            //         system(tmpcmd);
            //         offset = @1.first_column-2;
            //         for (int i = 0; i < offset; ++i)
            //             fprintf(stderr, " ");
            //         fprintf(stderr, "^\n");
            // }
            // |Exp Exp                                                    //error
            // {
            //         error("Exp ::= Exp Exp\n");
            //         haserror = true;
            //         realse_nodelist();
            //         sprintf(tmpcmd, "sed -n %dp %s | sed 's/\t/ /g' ", @2.first_line, infile_name);
            //         system(tmpcmd);
            //         offset = @1.last_column;
            //         for (int i = 0; i < offset; ++i)
            //             fprintf(stderr, " ");
            //         fprintf(stderr, "^\n");
            // }
            ;

Cond :   Exp eq_tok Exp
            {
                    // debug("Cond ::= Exp eq Exp \n");
                    $$ = new CondNode(eq_tok, (ExpNode *)$1, (ExpNode *)$3);
                    // nodelist.push_back((Node *)$$);
            }
            | Exp neq_tok Exp
            {
                    // debug("Cond ::= Exp neq Exp \n");
                    $$ = new CondNode(neq_tok, (ExpNode *)$1, (ExpNode *)$3);
                    // nodelist.push_back((Node *)$$);
            }
            | Exp lt_tok Exp
            {
                    // debug("Cond ::= Exp lt Exp \n");
                    $$ = new CondNode(lt_tok, (ExpNode *)$1, (ExpNode *)$3);
                    // nodelist.push_back((Node *)$$);
            }
            | Exp le_tok Exp
            {
                    // debug("Cond ::= Exp le Exp \n");
                    $$ = new CondNode(le_tok, (ExpNode *)$1, (ExpNode *)$3);
                    // nodelist.push_back((Node *)$$);
            }
            | Exp gt_tok Exp
            {
                    // debug("Cond ::= Exp gt Exp \n");
                    $$ = new CondNode(gt_tok, (ExpNode *)$1, (ExpNode *)$3);
                    // nodelist.push_back((Node *)$$);
            }
            | Exp ge_tok Exp
            {
                    // debug("Cond ::= Exp ge Exp \n");
                    $$ = new CondNode(ge_tok, (ExpNode *)$1, (ExpNode *)$3);
                    // nodelist.push_back((Node *)$$);
            }
            ;

%%

void yyerror (const char *msg)
{
    error ("%s\n", msg);
}
