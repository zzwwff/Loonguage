/* file: parser.y */

/* 使用指令％skeleton "lalr1.cc"选择C++解析器的骨架 */
%skeleton "lalr1.cc"

/* 指定bison的版本 */
%require "3.0.4"

%define api.namespace {LoonScanner} 
%define parser_class_name { Parser }
%define api.token.constructor
%define api.value.type variant 
%define parse.assert  
%defines  //generate  location.hh position.hh  parser.hpp
%code requires
{
  #include <iostream>
  #include <string>
  #include <vector>
  #include <stdint.h>
  #include <cmath>
  #include "Tokens.h"

  namespace LoonScanner { 
    class Scanner;
  }
}

%code top
{
  #include <iostream>
  #include "LoonScanner.h"
  #include "LoonParser.hpp"
  #include "location.hh"

  static LoonScanner::Parser::symbol_type yylex(LoonScanner::Scanner& scanner, 
                                                Loonguage::SymbolTable<std::string>& idenTable, 
                                                Loonguage::SymbolTable<std::string>& strTable){
    return scanner.nextToken(idenTable, strTable);
  }
  using namespace LoonScanner;
}

/*定义parser传给scanner的参数*/
%lex-param { LoonScanner::Scanner& scanner }
%lex-param { Loonguage::SymbolTable<std::string>& idenTable }
%lex-param { Loonguage::SymbolTable<std::string>& strTable }

/*定义driver传给parser的参数*/
%parse-param { LoonScanner::Scanner& scanner }
%parse-param { Loonguage::SymbolTable<std::string>& idenTable }
%parse-param { Loonguage::SymbolTable<std::string>& strTable }

%locations
//%define parse-trace

/*详细显示错误信息*/
%define parse.error verbose

/*通过LoonScanner::Parser::make_XXX(loc)给token添加前缀*/
%define api.token.prefix {TOKEN_}

%token <Loonguage::TokenKeyWord> IF WHILE
%token <Loonguage::TokenInt> INT
%token <Loonguage::TokenString> STR
%token <Loonguage::TokenIden> IDEN
%token <Loonguage::TokenSymbol> PLUS MINUS TIME DIVISION AND OR XOR REV LBRACKET RBRACKET LBRACE RBRACE SEMICOLON COMMA ASSIGN EQUAL LESS 
%token <std::string> ERROR
%token END 0


%type <int> program
%type <int> functions
%type <int> function
%type <int> formal
%type <int> formals
%type <int> sentence
%type <int> sentences
%type <int> expr
%type <int> actual
%type <int> actuals


%start program


%%
 program:
functions
{ std::cout << "program" << std::endl;}

functions:
function { }
| function functions {std::cout << "function" << std::endl; }

formal:
IDEN IDEN {}

formals:
formal COMMA formals { }
| formal { }

function:
IDEN IDEN LBRACKET RBRACKET sentence { }
| IDEN IDEN LBRACKET formals RBRACKET sentence { }

sentence:
expr SEMICOLON { }
| IF LBRACKET expr RBRACKET sentence { }
| WHILE LBRACKET expr RBRACKET sentence { }
| LBRACE sentences RBRACE { }
| LBRACE RBRACE { }
| IDEN IDEN SEMICOLON { }

sentences:
sentence { }
| sentence sentences { }

expr:
| IDEN { }
| LBRACKET expr RBRACKET { }
| IDEN LBRACKET actuals RBRACKET { }
| IDEN LBRACKET RBRACKET { }
| IDEN { }
| expr PLUS expr { }
| expr MINUS expr { }
| expr TIME expr { }
| expr DIVISION expr { }
| expr AND expr { }
| expr OR expr { }
| expr XOR expr { }
| expr EQUAL expr { }
| expr LESS expr { }
| REV expr { }
| IDEN ASSIGN expr { }
| INT { }
| STR { }

actual:
expr { }

actuals:
actual { }
| actual actuals { }

%%
/*Parser实现错误处理接口*/
void LoonScanner::Parser::error(const LoonScanner::location& location,const std::string& message){
  std::cout<<"msg:"<<message
           <<", error happened at: "<<location<<std::endl;
}
