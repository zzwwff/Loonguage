

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexicalConfig.h"

 
void yyerror(const char *s) {
    fprintf(stderr, "error: %s\n", s);
}
 
int yylex(void);  // ÉùÃ÷Cº¯Êý
 

%}
 
%union {
    char text[100];
    char errorMsg[100];
    int res;
}
 
%token <text> IDEN IF WHILE INT
%token <errorMsg> ERROR
%type<res> program
 
 
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