/* file: lexer.h*/

%{
  #include <iostream>
  #include <cerrno>
  #include <climits>
  #include <cstdlib>
  #include <string>

  #include "LoonParser.hpp"  //包含由parser.y生成的头文件
  #include "LoonScanner.h"   //包含yyFlexLexer子类的头文件
  #include "location.hh" //包含位置调试信息头文件

  static LoonScanner::location loc;//声明位置实例
  #define YY_USER_ACTION  loc.columns (yyleng); /* 定义了YY_USER_ACTION，该宏在每个记号的语义动作之前被调用，来根据记号的长度设置位置的信息 */

  #undef yywrap
  #define yywrap() 1

  using namespace LoonScanner;
  #define yyterminate() Parser::make_END(loc);
%}
%option c++

%option noyywrap debug

%option yyclass="Scanner"

%option prefix="Loon_"


%x COMMENT
%x SINGLE_COMMENT

UNSIGNEDDIGIT [0-9]
DIGIT {UNSIGNEDDIGIT}+
IDEN [a-zA-Z][a-zA-Z0-9]*

NEW_LINE \n
BLANK [" "\f\r\t\v]+



%%
%{
  // C++ 兼容的词法分析器的规则，step函数把位置的起始值设置为与结束值相等，这样位置就指向了上一个极少的结束位置。
  loc.step();
%}


EOF { yyterminate(); }

<INITIAL>"/*" BEGIN(COMMENT);
<INITIAL>"//" BEGIN(SINGLE_COMMENT);

<COMMENT>{NEW_LINE} { }
<COMMENT>[^*\n]* { }       /* eat anything that's not a '*' */
<COMMENT>"*"+[^*/\n]* { }  /* eat up '*'s not followed by '/'s */
<COMMENT>"*/" BEGIN(INITIAL);

<SINGLE_COMMENT>[^\n]
<SINGLE_COMMENT>\n {
    BEGIN(INITIAL);
}

<INITIAL>{NEW_LINE}  {  }

<INITIAL>{BLANK} { }


<INITIAL>{DIGIT}    {
            return Parser::make_INT(yytext, loc); 
          }

<INITIAL>if        {
                return Parser::make_IF(yytext, loc); 
            }

<INITIAL>while        {
                return Parser::make_WHILE(yytext, loc); 
            }

<INITIAL>{IDEN}  {
                return Parser::make_IDEN(yytext, loc); 
            }

<INITIAL>==  {
                return Parser::make_SYMBOL('#', loc); 
            }

<INITIAL>"+"|"-"|"*"|"/"|"{"|"}"|"("|")"|";"|"="|"&"|"|"|"^"|"<"|"~"|"," {
                return Parser::make_SYMBOL(yytext[0], loc); 
            }

<<EOF>>   { return yyterminate(); }
.         {
             printf("Mystery character %c\n", *yytext);
             loc.step();
          }
%%
//这里可以放一些C或者C++代码
