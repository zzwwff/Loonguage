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
  #include <memory>
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
                                                LoonScanner::location& loc,
                                                Loonguage::SymbolTable<std::string>& idenTable, 
                                                Loonguage::SymbolTable<std::string>& strTable,
                                                std::shared_ptr<Loonguage::NodeProgram>& program,
                                                Loonguage::Errors& errs){
    return scanner.nextToken(loc, idenTable, strTable, program, errs);
  }
  using namespace LoonScanner;
}

/*arguments from parser to scanner*/
%lex-param { LoonScanner::Scanner& scanner }
%lex-param { LoonScanner::location& loc }
%lex-param { Loonguage::SymbolTable<std::string>& idenTable }
%lex-param { Loonguage::SymbolTable<std::string>& strTable }
%lex-param { std::shared_ptr<Loonguage::NodeProgram>& program }
%lex-param { Loonguage::Errors& errs }


/*arguments from driver to parser */
%parse-param { LoonScanner::Scanner& scanner }
%parse-param { LoonScanner::location& loc }
%parse-param { Loonguage::SymbolTable<std::string>& idenTable }
%parse-param { Loonguage::SymbolTable<std::string>& strTable }
%parse-param { std::shared_ptr<Loonguage::NodeProgram>& program }
%parse-param { Loonguage::Errors& errs }

%locations
//%define parse-trace

/*show error messages*/
%define parse.error verbose

/*add prefiex to LoonScanner::Parser::make_XXX(loc)*/
%define api.token.prefix {TOKEN_}

%token <Loonguage::TokenKeyWord> IF WHILE CONTINUE BREAK RETURN
%token <Loonguage::TokenInt> INT
%token <Loonguage::TokenString> STR
%token <Loonguage::TokenIden> IDEN
%token <Loonguage::TokenSymbol> PLUS MINUS TIME DIVISION AND OR XOR REV LBRACKET RBRACKET LBRACE RBRACE SEMICOLON COMMA ASSIGN EQUAL LESS AT
%token <std::string> ERROR
%token END 0

%right ASSIGN
%nonassoc EQUAL LESS
%left OR
%left AND XOR
%left PLUS MINUS
%left TIME DIVISION
%right REV

%type <std::shared_ptr<Loonguage::NodeProgram>> program
%type <std::shared_ptr<Loonguage::NodeFunctions>> functions
%type <std::shared_ptr<Loonguage::NodeFunction>> function
%type <std::shared_ptr<Loonguage::NodeFormal>> formal
%type <std::shared_ptr<Loonguage::NodeFormals>> formals
%type <std::shared_ptr<Loonguage::NodeSentence>> sentence
%type <std::shared_ptr<Loonguage::NodeSentences>> sentences
%type <std::shared_ptr<Loonguage::NodeExpr>> expr
%type <std::shared_ptr<Loonguage::NodeActual>> actual
%type <std::shared_ptr<Loonguage::NodeActuals>> actuals


%start program


%%
 program:
functions
{ $$ = std::make_shared<Loonguage::NodeProgram>($1); 
  program = $$;
  }

functions:
function { $$ = std::make_shared<Loonguage::NodeFunctions>($1); }
| functions function {$$ = $1;
                      $$->push_back($2);}
| functions error {
                //$$ = std::make_shared<Loonguage::NodeFunctions>($1);
                $$ = $1;
}

formal:
IDEN IDEN { $$ = std::make_shared<Loonguage::NodeFormal>($1, $2); }

formals:
formals COMMA formal { $$ = $1;
                      $$->push_back($3);  }
| formal { $$ = std::make_shared<Loonguage::NodeFormals>($1); }
| error COMMA formal {
    $$ = std::make_shared<Loonguage::NodeFormals>($3);
}

function:
IDEN IDEN LBRACKET RBRACKET sentence { $$ = std::make_shared<Loonguage::NodeFunction>($1, $2, std::make_shared<Loonguage::NodeFormals>($1.line), $5); }
| IDEN IDEN LBRACKET formals RBRACKET sentence {
    $$ = std::make_shared<Loonguage::NodeFunction>($1, $2, $4, $6); }
| IDEN IDEN LBRACKET error RBRACKET sentence {$$ = std::make_shared<Loonguage::NodeFunction>($1, $2, std::make_shared<Loonguage::NodeFormals>($1.line), $6);
    }
| IDEN IDEN LBRACKET formals RBRACKET AT{
    $$ = std::make_shared<Loonguage::NodeNativeFunction>($1, $2, $4); 
    }
| IDEN IDEN LBRACKET RBRACKET AT { 
    $$ = std::make_shared<Loonguage::NodeNativeFunction>($1, $2, std::make_shared<Loonguage::NodeFormals>($1.line));
    }

sentence:
expr SEMICOLON { $$ = std::make_shared<Loonguage::NodeSExpr>($1); }
| IF LBRACKET expr RBRACKET sentence { $$ = std::make_shared<Loonguage::NodeSIf>($3, $5); }
| WHILE LBRACKET expr RBRACKET sentence { $$ = std::make_shared<Loonguage::NodeSWhile>($3, $5); }
| LBRACE sentences RBRACE { $$ = std::make_shared<Loonguage::NodeSBlock>($2); }
| LBRACE RBRACE { $$ = std::make_shared<Loonguage::NodeSBlock>(std::make_shared<Loonguage::NodeSentences>($1.line)); }
| IDEN IDEN SEMICOLON   { $$ = std::make_shared<Loonguage::NodeSDecl>($1, $2);}
| BREAK SEMICOLON { $$ = std::make_shared<Loonguage::NodeSBreak>($2.line);}
| CONTINUE SEMICOLON { $$ = std::make_shared<Loonguage::NodeSContinue>($2.line);}
| RETURN expr SEMICOLON { $$ = std::make_shared<Loonguage::NodeSReturn>($2);}
| RETURN SEMICOLON { $$ = std::make_shared<Loonguage::NodeSReturn>(nullptr);}
| error SEMICOLON { $$ = std::make_shared<Loonguage::NodeSentence>($2.line);}
| LBRACE error RBRACE { $$ = std::make_shared<Loonguage::NodeSentence>($1.line); }

sentences:
sentence { $$ = std::make_shared<Loonguage::NodeSentences>($1); }
| sentences sentence { $$ = $1;
                      $$->push_back($2); }

expr:
IDEN { $$ = std::make_shared<Loonguage::NodeEIden>($1); }
| LBRACKET expr RBRACKET {  $$ = std::make_shared<Loonguage::NodeEBracket>($2); }
| IDEN LBRACKET actuals RBRACKET {  $$ = std::make_shared<Loonguage::NodeEDispatch>($1, $3); }
| IDEN LBRACKET RBRACKET {  $$ = std::make_shared<Loonguage::NodeEDispatch>($1, std::make_shared<Loonguage::NodeActuals>($1.line)); }
| expr PLUS expr {  $$ = std::make_shared<Loonguage::NodeECalc>($1, '+', $3); }
| expr MINUS expr {  $$ = std::make_shared<Loonguage::NodeECalc>($1, '-', $3); }
| expr TIME expr {  $$ = std::make_shared<Loonguage::NodeECalc>($1, '*', $3); }
| expr DIVISION expr {  $$ = std::make_shared<Loonguage::NodeECalc>($1, '/', $3); }
| expr AND expr {  $$ = std::make_shared<Loonguage::NodeECalc>($1, '&', $3); }
| expr OR expr {  $$ = std::make_shared<Loonguage::NodeECalc>($1, '|', $3); }
| expr XOR expr {  $$ = std::make_shared<Loonguage::NodeECalc>($1, '^', $3); }
| expr EQUAL expr {  $$ = std::make_shared<Loonguage::NodeEEqua>($1, $3); }
| expr LESS expr {  $$ = std::make_shared<Loonguage::NodeELess>($1, $3); }
| REV expr {  $$ = std::make_shared<Loonguage::NodeERev>($2); }
| IDEN ASSIGN expr {  $$ = std::make_shared<Loonguage::NodeEAssign>($1, $3); }
| INT {  $$ = std::make_shared<Loonguage::NodeEInt>($1); }
| STR {  $$ = std::make_shared<Loonguage::NodeEStr>($1); }

actual:
expr { $$ = std::make_shared<Loonguage::NodeActual>($1); }

actuals:
actual { $$ = std::make_shared<Loonguage::NodeActuals>($1); }
| actuals COMMA actual {  $$ = $1;
                      $$->push_back($3); }
| error COMMA actual{
    $$ = std::make_shared<Loonguage::NodeActuals>($3);
}

%%
/*Parser实现错误处理接口*/
void LoonScanner::Parser::error(const LoonScanner::location& location,const std::string& message){
    errs.push_back(Loonguage::Error( std::string("Syntax Analysis"), location.begin.line, message ));
}
