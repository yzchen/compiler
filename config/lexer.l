%{
#include <string>
#include "node.hh"
#include "tok.hh"

int yycolumn = 1;

#define YY_USER_ACTION yylloc.first_line = yylloc.last_line = yylineno; \
    yylloc.first_column = yycolumn; yylloc.last_column = yycolumn+yyleng-1; \
    yycolumn += yyleng;
%}

%option yylineno

%x COMMENTML
%x COMMENTOL

D       [0-9]
L       [a-zA-Z_]

%option noyywrap

%%

"#".*               		// comment
{D}+      		{   yylval.num = atoi (yytext);
                        			return intnum_tok;
             		}

{D}+\.{D}+	{   yylval.floatnum = atof (yytext);
				return floatnum_tok;
		}


"const" 	   		return const_tok;
"int"         		return int_tok;
"float"			return float_tok;
"void"       		return void_tok;
"while"     		return while_tok;
"if"       			return if_tok;
"else"			return else_tok;
"return"		return return_tok;
"extern"		return extern_tok;
"break"			return break_tok;
"continue"		return continue_tok;
"struct"			return struct_tok;

{L}({L}|{D})*     	 	{   yylval.ident = new std::string (yytext);
                        			return ident_tok;
                    		}

"+"        	         		return '+';
"-"         	        		return '-';
"*"        	        		return '*';
"/"        		         	return '/';
"%"			return '%';
"&"			return '&';

"="	                 	return '=';
"!="			return neq_tok;
"=="			return eq_tok;
"<="			return le_tok;
"<"			return lt_tok;
">="			return ge_tok;
">"			return gt_tok;

"("                 		return '(';
")"                 		return ')';
"["			return '[';
"]"			return ']';
"{"			return '{';
"}"			return '}';
"."			return '.';
";"                 		return ';';

","			return ',';
\n                 		yycolumn = 1;


"/*"			{
				BEGIN 	COMMENTML;
			}
<COMMENTML>\n 		{
				yycolumn = 1;
			}
<COMMENTML>"*/"	{
				BEGIN INITIAL;
			}
<COMMENTML>.             	{ }


"//"			{
				BEGIN 	 COMMENTOL;
			}
<COMMENTOL>\n 	{
				BEGIN    INITIAL;
			}
<COMMENTOL>. 	{

			}


[\t ]*			;
.                   		return err_tok;

%%
