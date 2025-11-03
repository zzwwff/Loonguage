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

  static LoonScanner::Parser::symbol_type yylex(LoonScanner::Scanner& scanner){
    return scanner.nextToken();
  }
  using namespace LoonScanner;
}

/*定义parser传给scanner的参数*/
%lex-param { LoonScanner::Scanner& scanner }

/*定义driver传给parser的参数*/
%parse-param { LoonScanner::Scanner& scanner }

%locations
//%define parse-trace

/*详细显示错误信息*/
%define parse.error verbose

/*通过LoonScanner::Parser::make_XXX(loc)给token添加前缀*/
%define api.token.prefix {TOKEN_}

%token <std::string> IDEN IF WHILE INT
%token <std::string> ERROR
%token <char>   SYMBOL
%token END 0


%type <int> program

%start program


%%
 program:
IDEN IDEN SYMBOL INT SYMBOL
{ std::cout << "hello  world = " << $4 << std::endl;  $$ = 1; }


%%
/*Parser实现错误处理接口*/
void LoonScanner::Parser::error(const LoonScanner::location& location,const std::string& message){
  std::cout<<"msg:"<<message
           <<", error happened at: "<<location<<std::endl;
}
