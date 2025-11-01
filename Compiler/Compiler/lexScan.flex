/* scanner for a toy Pascal-like language */
%option noyywrap

%{
#include "unistd.h"
#include <string.h>
#include "lexicalConfig.h"
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
                return INT;
            }

<INITIAL>if        {
                snprintf(buffer, sizeof(buffer), " TokenKeyWord %d KeyWordIf", curLine);
                addString();
                return IF;
            }

<INITIAL>while        {
                snprintf(buffer, sizeof(buffer), " TokenKeyWord %d KeyWordWhile", curLine);
                addString();
                return WHILE;
            }

<INITIAL>{IDEN}  {
                snprintf(buffer, sizeof(buffer), " TokenIden %d %s", curLine, yytext);
                addString();
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



%%



int lexical(const char* input)
    {
    output[0] = len = 0;
    if (strcmp(input, "cin") != 0)
    {
           FILE *input_file = fopen(input, "r");
        if (input_file == NULL) {
            perror("Error opening file");
            return 0;
        }
        yyin = input_file;
    }
    int t = yylex();
    if (strcmp(input, "cin") != 0)
        fclose(yyin);

    return t;
    }
