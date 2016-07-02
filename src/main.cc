#include <stdio.h>
#include <string>
#include "node.hh"
#include "tok.hh"
// comment the next line to hide debug info
#define DEBUG
#include "util.hh"
#include "global.hh"
#include <iostream>
#include <fstream>

extern FILE *yyin;      // flex uses yyin as input file's pointer
extern int yylex();     // lexer.cc provides yylex()
extern int yyparse();   // parser.cc provides yyparse()
extern CompUnitNode *root; // AST's root, shared with yyparse()

extern Module *TheModule;

int main(int argc, char** argv)
{
    if (handle_opt(argc, argv) == false)
        return 0;
    yyin = infp;        // infp is initialized in handle_opt()
    TheModule = new Module("my cool jit", getGlobalContext());

    yyparse();
    debug("psrse done\n");
    // if (dumpfp != NULL) {
    //     DumpDOT *dumper = new DumpDOT(dumpfp);
    //     root->dumpdot(dumper);
    //     delete dumper;
    //     fclose(dumpfp);
    // }

    std::vector<AllocaInst *> OldBindings;
    Value  * retV = root->Codegen(OldBindings);
    // printf("before dump\n");

    TheModule->dump();

    /* root->printast(stdout, 0); */
    return 0;
}
