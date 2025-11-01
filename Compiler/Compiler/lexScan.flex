/* scanner for a toy Pascal-like language */
%option noyywrap

%{
#include "unistd.h"
#include <string.h>

int curLine = 1;

char output[1024 * 16];
char buffer[1024];
int len = 0;

void addString()
{
    int newLen = len + strlen(buffer);
    strcat_s(output + len, 1024 * 16, buffer);
    len = newLen;
}
%}

%x COMMENT
%x SINGLE_COMMENT


UNSIGNEDDIGIT [0-9]
DIGIT {UNSIGNEDDIGIT}+
IDEN [a-z][a-zA-Z0-9]*



NEW_LINE \n
BLANK [" "\f\r\t\v]+

%%

EOF { yyterminate(); }

<INITIAL>"/*" BEGIN(COMMENT);
<INITIAL>"//" BEGIN(SINGLE_COMMENT);

<COMMENT>{NEW_LINE} { curLine++; }
<COMMENT>[^*\n]* { }       /* eat anything that's not a '*' */
<COMMENT>"*"+[^*/\n]* { }  /* eat up '*'s not followed by '/'s */
<COMMENT>"*/" BEGIN(INITIAL);

<SINGLE_COMMENT>[^\n]
<SINGLE_COMMENT>\n {
    curLine++;
    BEGIN(INITIAL);
}

<INITIAL>{NEW_LINE}  { curLine++; }

<INITIAL>{BLANK} { }


<INITIAL>{DIGIT}    {
                snprintf(buffer, sizeof(buffer), " TokenInt %d %s", curLine, yytext);
                addString();
            }

<INITIAL>if        {
                snprintf(buffer, sizeof(buffer), " TokenKeyWord %d KeyWordIf", curLine);
                addString();
            }

<INITIAL>while        {
                snprintf(buffer, sizeof(buffer), " TokenKeyWord %d KeyWordWhile", curLine);
                addString();
            }

<INITIAL>{IDEN}  {
                snprintf(buffer, sizeof(buffer), " TokenIden %d %s", curLine, yytext);
                addString();
            }

<INITIAL>==  {
                snprintf(buffer, sizeof(buffer), " TokenSymbol %d #", curLine);
                addString();
            }

<INITIAL>"+"|"-"|"*"|"/"|"{"|"}"|"("|")"|";"|"="|"&"|"|"|"^"|"<"|"~"|"," {
                snprintf(buffer, sizeof(buffer), " TokenSymbol %d %c", curLine, yytext[0]);
                addString();
            }



%%



char* lexical(  )
    {
    yylex();
    return output;
    }
