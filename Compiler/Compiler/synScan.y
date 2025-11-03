%language "c++"
%define api.token.constructor

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cstring>
#include "lexicalConfig.h"

 
void yyerror(const char *s) {
    fprintf(stderr, "error: %s\n", s);
}
 
int yylex(void);  // ÉùÃ÷Cº¯Êý
 

%}
 
 
%token <std::string> IDEN IF WHILE INT
%token <std::string> ERROR
%nterm<int> program
 
 
%%
 program:
IDEN IDEN '=' INT ';'
{ printf("hello world\n"); $$ = 1; }

 
%%
 
int parses() {
    printf("Enter expression: \n");
    yyparse();
    return 0;
}