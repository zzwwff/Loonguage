/* file: parser.y */

/* 使用指令％skeleton "lalr1.cc"选择C++解析器的骨架 */
%skeleton "lalr1.cc"

/* 指定bison的版本 */
%require "3.0.4"

%define api.namespace {LoonScanner} 
%define api.parser.class { Parser }
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
  #include "NodeActual.h"
  #include "NodeExpr.h"
  #include "NodeFormal.h"
  #include "NodeFunction.h"
  #include "NodeProgram.h"
  #include "NodeSentence.h"
  #include "Error.h"

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
  #include "NodeProgram.h"
  class NodeProgram;
  static LoonScanner::Parser::symbol_type yylex(LoonScanner::Scanner& scanner, 
                                                Loonguage::SymbolTable<std::string>& idenTable, 
                                                Loonguage::SymbolTable<std::string>& strTable,
                                                Loonguage::NodeProgram** program,
                                                Loonguage::Errors& errs){
    return scanner.nextToken(idenTable, strTable, program, errs);
  }
  using namespace LoonScanner;
}

/*定义parser传给scanner的参数*/
%lex-param { LoonScanner::Scanner& scanner }
%lex-param { Loonguage::SymbolTable<std::string>& idenTable }
%lex-param { Loonguage::SymbolTable<std::string>& strTable }
%lex-param { Loonguage::NodeProgram** program }
%lex-param { Loonguage::Errors& errs }


/*定义driver传给parser的参数*/
%parse-param { LoonScanner::Scanner& scanner }
%parse-param { Loonguage::SymbolTable<std::string>& idenTable }
%parse-param { Loonguage::SymbolTable<std::string>& strTable }
%parse-param { Loonguage::NodeProgram** program }
%parse-param { Loonguage::Errors& errs }

%locations
//%define parse-trace

/*详细显示错误信息*/
%define parse.error verbose

/*通过LoonScanner::Parser::make_XXX(loc)给token添加前缀*/
%define api.token.prefix {TOKEN_}

%token <Loonguage::TokenKeyWord> IF WHILE CONTINUE BREAK RETURN
%token <Loonguage::TokenInt> INT
%token <Loonguage::TokenString> STR
%token <Loonguage::TokenIden> IDEN
%token <Loonguage::TokenSymbol> PLUS MINUS TIME DIVISION AND OR XOR REV LBRACKET RBRACKET LBRACE RBRACE SEMICOLON COMMA ASSIGN EQUAL LESS 
%token <std::string> ERROR
%token END 0

%right ASSIGN
%nonassoc EQUAL LESS
%left OR
%left AND XOR
%left PLUS MINUS
%left TIME DIVISION
%right REV

%type <Loonguage::NodeProgram*> program
%type <Loonguage::NodeFunctions*> functions
%type <Loonguage::NodeFunction*> function
%type <Loonguage::NodeFormal*> formal
%type <Loonguage::NodeFormals*> formals
%type <Loonguage::NodeSentence*> sentence
%type <Loonguage::NodeSentences*> sentences
%type <Loonguage::NodeExpr*> expr
%type <Loonguage::NodeActual*> actual
%type <Loonguage::NodeActuals*> actuals


%start program


%%
 program:
functions
{ $$ = new Loonguage::NodeProgram($1); 
  *program = $$;
  }

functions:
function { $$ = new Loonguage::NodeFunctions($1); }
| functions function {$$ = $1;
                      $$->push_back($2);}
| functions error {
                //$$ = new Loonguage::NodeFunctions($1);
                $$ = $1;
}

formal:
IDEN IDEN { $$ = new Loonguage::NodeFormal($1, $2); }

formals:
formals COMMA formal { $$ = $1;
                      $$->push_back($3);  }
| formal { $$ = new Loonguage::NodeFormals($1); }
| error COMMA formal {
    $$ = new Loonguage::NodeFormals($3);
}

function:
IDEN IDEN LBRACKET RBRACKET sentence { $$ = new Loonguage::NodeFunction($1, $2, new Loonguage::NodeFormals($1.line), $5); }
| IDEN IDEN LBRACKET formals RBRACKET sentence {
    $$ = new Loonguage::NodeFunction($1, $2, $4, $6); }
| IDEN IDEN LBRACKET error RBRACKET sentence {$$ = new Loonguage::NodeFunction($1, $2, new Loonguage::NodeFormals($1.line), $6);
    }

sentence:
expr SEMICOLON { $$ = new Loonguage::NodeSExpr($1); }
| IF LBRACKET expr RBRACKET sentence { $$ = new Loonguage::NodeSIf($3, $5); }
| WHILE LBRACKET expr RBRACKET sentence { $$ = new Loonguage::NodeSWhile($3, $5); }
| LBRACE sentences RBRACE { $$ = new Loonguage::NodeSBlock($2); }
| LBRACE RBRACE { $$ = new Loonguage::NodeSBlock(new Loonguage::NodeSentences($1.line)); }
| IDEN IDEN SEMICOLON { $$ = new Loonguage::NodeSDecl($1, $2);}
| BREAK SEMICOLON { $$ = new Loonguage::NodeSBreak($2.line);}
| CONTINUE SEMICOLON { $$ = new Loonguage::NodeSContinue($2.line);}
| RETURN expr SEMICOLON { $$ = new Loonguage::NodeSReturn($2);}
| error SEMICOLON { $$ = new Loonguage::NodeSentence($2.line);}
| LBRACE error RBRACE { $$ = new Loonguage::NodeSentence($1.line); }

sentences:
sentence { $$ = new Loonguage::NodeSentences($1); }
| sentences sentence { $$ = $1;
                      $$->push_back($2); }

expr:
IDEN { $$ = new Loonguage::NodeEIden($1); }
| LBRACKET expr RBRACKET {  $$ = new Loonguage::NodeEBracket($2); }
| IDEN LBRACKET actuals RBRACKET {  $$ = new Loonguage::NodeEDispatch($1, $3); }
| IDEN LBRACKET RBRACKET {  $$ = new Loonguage::NodeEDispatch($1, new Loonguage::NodeActuals($1.line)); }
| expr PLUS expr {  $$ = new Loonguage::NodeECalc($1, '+', $3); }
| expr MINUS expr {  $$ = new Loonguage::NodeECalc($1, '-', $3); }
| expr TIME expr {  $$ = new Loonguage::NodeECalc($1, '*', $3); }
| expr DIVISION expr {  $$ = new Loonguage::NodeECalc($1, '/', $3); }
| expr AND expr {  $$ = new Loonguage::NodeECalc($1, '&', $3); }
| expr OR expr {  $$ = new Loonguage::NodeECalc($1, '|', $3); }
| expr XOR expr {  $$ = new Loonguage::NodeECalc($1, '^', $3); }
| expr EQUAL expr {  $$ = new Loonguage::NodeEEqua($1, $3); }
| expr LESS expr {  $$ = new Loonguage::NodeELess($1, $3); }
| REV expr {  $$ = new Loonguage::NodeERev($2); }
| IDEN ASSIGN expr {  $$ = new Loonguage::NodeEAssign($1, $3); }
| INT {  $$ = new Loonguage::NodeEInt($1); }
| STR {  $$ = new Loonguage::NodeEStr($1); }

actual:
expr { $$ = new Loonguage::NodeActual($1); }

actuals:
actual { $$ = new Loonguage::NodeActuals($1); }
| actuals COMMA actual {  $$ = $1;
                      $$->push_back($3); }
| error COMMA actual{
    $$ = new Loonguage::NodeActuals($3);
}

%%
/*Parser实现错误处理接口*/
void LoonScanner::Parser::error(const LoonScanner::location& location,const std::string& message){
    errs.push_back(Loonguage::Error( std::string("Syntax Analysis"), location.begin.line, message ));
}
