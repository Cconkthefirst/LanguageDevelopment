%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbols.h"
#include "evalexpr.h"
#include "prog.h"
#include "compilecpp.h"
#define YYDEBUG 1

int yylex (void); 
int yyerror(char* s);
%}

%union semrec { /*SEMANTIC RECORD */ 
	char *val;
    char* id;
}

%start program
%token ASSIGNOP 
%token <id> ID
%token <val> WEBOBJECT 
%token <val> FUNC1GETHTML 
%token <val> FUNC2FINDWEBIMAGES 
%token <val> FUNC3ORGANIZEWEBINFO 

%%

program : script_instructions;
script_instructions : instruction | instruction script_instructions;
instruction : ID ASSIGNOP WEBOBJECT {assignSymbol($1, $3)} 
    | ID FUNC1GETHTML   { genCode(func1gethtml, $1); } 
    | ID FUNC2FINDWEBIMAGES   { genCode(func2findwebimages, $1); } 
    | ID FUNC3ORGANIZEWEBINFO     { genCode(func3organizewebinfo, $1); } 
;
%%

int yyerror(char* s) {
    printf("error: %s\n", s);
}

int main(int argc, char**argv) { 
    extern FILE* yyin;

    if (argc == 2) {
        yyin = fopen(argv[1], "r");
        if (yyin == NULL) {
            printf("%s doesn't exist\n", argv[1]);
            return -1;
        }
    }
    yyparse();

    printf("compiling...\n");
    compilePerl();
    cleanupSymbols();
}
