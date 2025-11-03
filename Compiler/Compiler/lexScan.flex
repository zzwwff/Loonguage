
%{
#include "synScan.tab.h"
#include <string.h>
#include <stdlib.h>
#include "lexicalConfig.h"
 
int curLine = 1;

char last[4096];
char output[4096];
char buffer[1024];
int len = 0;

void addString()
{
    int newLen = len + strlen(buffer);
    strcat_s(output + len, sizeof(output) - len, buffer);
    strcpy_s(last, sizeof(last), output);
    len = newLen;
}
%}

%x COMMENT
%x SINGLE_COMMENT


UNSIGNEDDIGIT [0-9]
DIGIT {UNSIGNEDDIGIT}+
IDEN [a-zA-Z][a-zA-Z0-9]*



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
                strcpy(yylval.text, yytext);
                return INT;
            }

<INITIAL>if        {
                snprintf(buffer, sizeof(buffer), " TokenKeyWord %d KeyWordIf", curLine);
                addString();
                strcpy(yylval.text, yytext);
                return IF;
            }

<INITIAL>while        {
                snprintf(buffer, sizeof(buffer), " TokenKeyWord %d KeyWordWhile", curLine);
                addString();
                strcpy(yylval.text, yytext);
                return WHILE;
            }

<INITIAL>{IDEN}  {
                snprintf(buffer, sizeof(buffer), " TokenIden %d %s", curLine, yytext);
                addString();
                strcpy(yylval.text, yytext);
                return IDEN;
            }

<INITIAL>==  {
                snprintf(buffer, sizeof(buffer), " TokenSymbol %d #", curLine);
                addString();
                return '#';
            }

<INITIAL>"+"|"-"|"*"|"/"|"{"|"}"|"("|")"|";"|"="|"&"|"|"|"^"|"<"|"~"|"," {
                snprintf(buffer, sizeof(buffer), " TokenSymbol %d %c", curLine, yytext[0]);
                addString();
                return yytext[0];
            }

. {
    if (strlen(last) < 10)
        snprintf(yylval.errorMsg, sizeof(yylval.errorMsg), "An error occurs at lexical analysis at line %d after %s.", curLine, last);
    else{
        last[10] = 0;
        snprintf(yylval.errorMsg, sizeof(yylval.errorMsg), "An error occurs at lexical analysis at line %d after %s...", curLine, last);
    }
    return ERROR;
}

%%
 
int yywrap()
{
    return 1;
}

int lexical(const char* input)
{
    return 0;
}