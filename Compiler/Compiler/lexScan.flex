/* scanner for a toy Pascal-like language */
%option noyywrap

%{
#include "unistd.h"
int curLine = 1;
%}

UNSIGNEDDIGIT [0-9]
DIGIT [-]*{UNSIGNEDDIGIT}+
IDEN [a-z][a-z0-9]*

NEW_LINE \n
BLANK_CHAR [ \f\r\t\v]
BLANK_STRING {BLANK_CHAR}+

%%

{NEW_LINE}  { curLine++; }

BLANK_STRING { }

{DIGIT}    {
                printf("#%d:digit %s\n", curLine, yytext);
            }

if        {
                printf("#%d:if\n", curLine);
            }

while        {
                printf("#%d:while\n", curLine);
            }

{IDEN}  {
                printf("#%d:iden %s\n", curLine, yytext);
            }

"+"|"-"|"*"|"/"   printf( "#%d: An operator: %s\n", curLine, yytext );


.           printf( "Unrecognized character: %s\n", yytext );

%%

void lexical(  )
    {
    yylex();
    }
