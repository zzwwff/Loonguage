/* file: lexer.h*/

%{
  #include <iostream>
  #include <cerrno>
  #include <climits>
  #include <cstdlib>
  #include <string>

  #include "LoonParser.hpp"  
  #include "LoonScanner.h"  
  #include "location.hh" 
  #include "Tokens.h"
  #include "Error.h"

  
  #define YY_USER_ACTION  loc.columns (yyleng); /* 定义了YY_USER_ACTION，该宏在每个记号的语义动作之前被调用，来根据记号的长度设置位置的信息 */

  #undef yywrap
  #define yywrap() 1

  using namespace LoonScanner;
  #define yyterminate() Parser::make_END(loc);

  std::string strBuffer;


%}
%option c++

%option noyywrap debug

%option yyclass="Scanner"

%option prefix="Loon_"


%x COMMENT
%x STRING
%x STRING_ERROR
%x SINGLE_COMMENT

UNSIGNEDDIGIT [0-9]
DIGIT {UNSIGNEDDIGIT}+
IDEN [a-zA-Z][a-zA-Z0-9]*

NEW_LINE \n
BLANK [ \f\r\t\v]+

CHAR '.'
ESCT '\\t'
ESCN '\\n'



%%
%{
  // C++ 兼容的词法分析器的规则，step函数把位置的起始值设置为与结束值相等，这样位置就指向了上一个极少的结束位置。
  loc.step();
%}


<INITIAL>@EOF { return Parser::make_END(loc); }

<INITIAL>"/*" BEGIN(COMMENT);
<INITIAL>"//" BEGIN(SINGLE_COMMENT);

<COMMENT>{NEW_LINE} {            loc.lines(yyleng); 
            loc.step();  }
<COMMENT>[^*\n]* { }       /* eat anything that's not a '*' */
<COMMENT>"*"+[^*/\n]* { }  /* eat up '*'s not followed by '/'s */
<COMMENT>"*/" BEGIN(INITIAL);

<SINGLE_COMMENT>[^\n]
<SINGLE_COMMENT>\n {
    loc.lines(yyleng); 
    loc.step();
    BEGIN(INITIAL);
}

<INITIAL>\" {
    strBuffer.clear();
    BEGIN(STRING);
}


<STRING>\" {
    BEGIN(INITIAL);
    return Parser::make_STR(Loonguage::TokenString(loc.begin.line, strBuffer, strTable), loc); 
}

<STRING>\\[tn] {
    if (yytext[1] == 'n')
    	strBuffer.push_back('\n');
    else if (yytext[1] == 't')
    	strBuffer.push_back('\t');
}

<STRING>\\[^tn] {
    strBuffer.push_back(yytext[1]);
}

<STRING>[^\"\n] {
    strBuffer.push_back(yytext[0]);
  }

<STRING>\n {
    loc.lines(yyleng); 
    loc.step();
}



<INITIAL>{NEW_LINE}  {     loc.lines(yyleng); 
    loc.step(); }

<INITIAL>{BLANK} { }


<INITIAL>{DIGIT}    {
            return Parser::make_INT(Loonguage::TokenInt(loc.begin.line, std::stoi(yytext)), loc); 
          }

<INITIAL>if        {
            return Parser::make_IF(Loonguage::TokenKeyWord(loc.begin.line, Loonguage::TokenKeyWord::KeyWordType::KeyWordIf), loc); 
            }

<INITIAL>while        {
            return Parser::make_WHILE(Loonguage::TokenKeyWord(loc.begin.line, Loonguage::TokenKeyWord::KeyWordType::KeyWordIf), loc); 
            }

<INITIAL>continue        {
return Parser::make_CONTINUE(Loonguage::TokenKeyWord(loc.begin.line, Loonguage::TokenKeyWord::KeyWordType::KeyWordContinue), loc); 
}

<INITIAL>break        {
return Parser::make_BREAK(Loonguage::TokenKeyWord(loc.begin.line, Loonguage::TokenKeyWord::KeyWordType::KeyWordBreak), loc); 
}

<INITIAL>return        {
return Parser::make_RETURN(Loonguage::TokenKeyWord(loc.begin.line, Loonguage::TokenKeyWord::KeyWordType::KeyWordReturn), loc); 
}

<INITIAL>{IDEN}  {
                return Parser::make_IDEN(Loonguage::TokenIden(loc.begin.line, yytext, idenTable), loc); 
            }

<INITIAL>==  {
                return Parser::make_EQUAL(Loonguage::TokenSymbol(loc.begin.line, '#'), loc); 
            }

<INITIAL>"+" {
                return Parser::make_PLUS(Loonguage::TokenSymbol(loc.begin.line, yytext[0]), loc); 
            }

<INITIAL>"-" {
                return Parser::make_MINUS(Loonguage::TokenSymbol(loc.begin.line, yytext[0]), loc); 
            }
<INITIAL>"*" {
                return Parser::make_TIME(Loonguage::TokenSymbol(loc.begin.line, yytext[0]), loc); 
            }
<INITIAL>"/" {
                return Parser::make_DIVISION(Loonguage::TokenSymbol(loc.begin.line, yytext[0]), loc); 
            }
<INITIAL>"{" {
                return Parser::make_LBRACE(Loonguage::TokenSymbol(loc.begin.line, yytext[0]), loc); 
            }
<INITIAL>"}" {
                return Parser::make_RBRACE(Loonguage::TokenSymbol(loc.begin.line, yytext[0]), loc); 
            }
<INITIAL>"(" {
                return Parser::make_LBRACKET(Loonguage::TokenSymbol(loc.begin.line, yytext[0]), loc); 
            }
<INITIAL>")" {
                return Parser::make_RBRACKET(Loonguage::TokenSymbol(loc.begin.line, yytext[0]), loc); 
            }
<INITIAL>"," {
                return Parser::make_COMMA(Loonguage::TokenSymbol(loc.begin.line, yytext[0]), loc); 
            }
<INITIAL>"=" {
                return Parser::make_ASSIGN(Loonguage::TokenSymbol(loc.begin.line, yytext[0]), loc); 
            }
<INITIAL>";" {
                return Parser::make_SEMICOLON(Loonguage::TokenSymbol(loc.begin.line, yytext[0]), loc); 
            }
<INITIAL>"&" {
                return Parser::make_AND(Loonguage::TokenSymbol(loc.begin.line, yytext[0]), loc); 
            }
<INITIAL>"|" {
                return Parser::make_OR(Loonguage::TokenSymbol(loc.begin.line, yytext[0]), loc); 
            }
<INITIAL>"~" {
                return Parser::make_REV(Loonguage::TokenSymbol(loc.begin.line, yytext[0]), loc); 
            }
<INITIAL>"^" {
                return Parser::make_XOR(Loonguage::TokenSymbol(loc.begin.line, yytext[0]), loc); 
            }

<INITIAL>"<" {
                return Parser::make_LESS(Loonguage::TokenSymbol(loc.begin.line, yytext[0]), loc); 
            }

<INITIAL>"@" {
    return Parser::make_AT(Loonguage::TokenSymbol(loc.begin.line, yytext[0]), loc); 
}

<INITIAL>"[" {
    return Parser::make_LSQUARE(Loonguage::TokenSymbol(loc.begin.line, yytext[0]), loc); 
}

<INITIAL>"]" {
    return Parser::make_RSQUARE(Loonguage::TokenSymbol(loc.begin.line, yytext[0]), loc); 
}

<INITIAL>{CHAR} {
            return Parser::make_INT(Loonguage::TokenInt(loc.begin.line, (int)yytext[1]), loc); 
          }

<INITIAL>{ESCT} {
            return Parser::make_INT(Loonguage::TokenInt(loc.begin.line, '\t'), loc); 
          }
          
<INITIAL>{ESCN} {
            return Parser::make_INT(Loonguage::TokenInt(loc.begin.line, '\n'), loc); 
          }

<<EOF>>   { return yyterminate(); }

.         {
             errs.push_back(Loonguage::Error( std::string("Lexical Analysis"), (int)loc.begin.line, std::string("Unknown character \'") + yytext[0] + '\'' ));
             loc.step();
          }
%%
//这里可以放一些C或者C++代码
