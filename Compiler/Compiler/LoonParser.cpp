// A Bison parser, made by GNU Bison 3.8.2.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2021 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.

// "%code top" blocks.
#line 38 "LoonParser.y"

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

#line 57 "LoonParser.cpp"




#include "LoonParser.hpp"




#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif


// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (false)
# endif


// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yy_stack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YY_USE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 9 "LoonParser.y"
namespace LoonScanner {
#line 157 "LoonParser.cpp"

  /// Build a parser object.
   Parser :: Parser  (LoonScanner::Scanner& scanner_yyarg, LoonScanner::location& loc_yyarg, Loonguage::SymbolTable<std::string>& idenTable_yyarg, Loonguage::SymbolTable<std::string>& strTable_yyarg, std::shared_ptr<Loonguage::NodeProgram>& program_yyarg, Loonguage::Errors& errs_yyarg)
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      scanner (scanner_yyarg),
      loc (loc_yyarg),
      idenTable (idenTable_yyarg),
      strTable (strTable_yyarg),
      program (program_yyarg),
      errs (errs_yyarg)
  {}

   Parser ::~ Parser  ()
  {}

   Parser ::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------.
  | symbol.  |
  `---------*/



  // by_state.
   Parser ::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

   Parser ::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
   Parser ::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
   Parser ::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

   Parser ::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

   Parser ::symbol_kind_type
   Parser ::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

   Parser ::stack_symbol_type::stack_symbol_type ()
  {}

   Parser ::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_IDEN: // IDEN
        value.YY_MOVE_OR_COPY< Loonguage::TokenIden > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_INT: // INT
        value.YY_MOVE_OR_COPY< Loonguage::TokenInt > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_IF: // IF
      case symbol_kind::S_WHILE: // WHILE
      case symbol_kind::S_CONTINUE: // CONTINUE
      case symbol_kind::S_BREAK: // BREAK
      case symbol_kind::S_RETURN: // RETURN
        value.YY_MOVE_OR_COPY< Loonguage::TokenKeyWord > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_STR: // STR
        value.YY_MOVE_OR_COPY< Loonguage::TokenString > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_PLUS: // PLUS
      case symbol_kind::S_MINUS: // MINUS
      case symbol_kind::S_TIME: // TIME
      case symbol_kind::S_DIVISION: // DIVISION
      case symbol_kind::S_AND: // AND
      case symbol_kind::S_OR: // OR
      case symbol_kind::S_XOR: // XOR
      case symbol_kind::S_REV: // REV
      case symbol_kind::S_LBRACKET: // LBRACKET
      case symbol_kind::S_RBRACKET: // RBRACKET
      case symbol_kind::S_LBRACE: // LBRACE
      case symbol_kind::S_RBRACE: // RBRACE
      case symbol_kind::S_LSQUARE: // LSQUARE
      case symbol_kind::S_RSQUARE: // RSQUARE
      case symbol_kind::S_SEMICOLON: // SEMICOLON
      case symbol_kind::S_COMMA: // COMMA
      case symbol_kind::S_ASSIGN: // ASSIGN
      case symbol_kind::S_EQUAL: // EQUAL
      case symbol_kind::S_LESS: // LESS
      case symbol_kind::S_AT: // AT
      case symbol_kind::S_MOD: // MOD
        value.YY_MOVE_OR_COPY< Loonguage::TokenSymbol > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_actual: // actual
        value.YY_MOVE_OR_COPY< std::shared_ptr<Loonguage::NodeActual> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_actuals: // actuals
        value.YY_MOVE_OR_COPY< std::shared_ptr<Loonguage::NodeActuals> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr: // expr
        value.YY_MOVE_OR_COPY< std::shared_ptr<Loonguage::NodeExpr> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_formal: // formal
        value.YY_MOVE_OR_COPY< std::shared_ptr<Loonguage::NodeFormal> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_formals: // formals
        value.YY_MOVE_OR_COPY< std::shared_ptr<Loonguage::NodeFormals> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_function: // function
        value.YY_MOVE_OR_COPY< std::shared_ptr<Loonguage::NodeFunction> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_functions: // functions
        value.YY_MOVE_OR_COPY< std::shared_ptr<Loonguage::NodeFunctions> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_program: // program
        value.YY_MOVE_OR_COPY< std::shared_ptr<Loonguage::NodeProgram> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_sentence: // sentence
        value.YY_MOVE_OR_COPY< std::shared_ptr<Loonguage::NodeSentence> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_sentences: // sentences
        value.YY_MOVE_OR_COPY< std::shared_ptr<Loonguage::NodeSentences> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ERROR: // ERROR
        value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

   Parser ::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_IDEN: // IDEN
        value.move< Loonguage::TokenIden > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_INT: // INT
        value.move< Loonguage::TokenInt > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_IF: // IF
      case symbol_kind::S_WHILE: // WHILE
      case symbol_kind::S_CONTINUE: // CONTINUE
      case symbol_kind::S_BREAK: // BREAK
      case symbol_kind::S_RETURN: // RETURN
        value.move< Loonguage::TokenKeyWord > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_STR: // STR
        value.move< Loonguage::TokenString > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_PLUS: // PLUS
      case symbol_kind::S_MINUS: // MINUS
      case symbol_kind::S_TIME: // TIME
      case symbol_kind::S_DIVISION: // DIVISION
      case symbol_kind::S_AND: // AND
      case symbol_kind::S_OR: // OR
      case symbol_kind::S_XOR: // XOR
      case symbol_kind::S_REV: // REV
      case symbol_kind::S_LBRACKET: // LBRACKET
      case symbol_kind::S_RBRACKET: // RBRACKET
      case symbol_kind::S_LBRACE: // LBRACE
      case symbol_kind::S_RBRACE: // RBRACE
      case symbol_kind::S_LSQUARE: // LSQUARE
      case symbol_kind::S_RSQUARE: // RSQUARE
      case symbol_kind::S_SEMICOLON: // SEMICOLON
      case symbol_kind::S_COMMA: // COMMA
      case symbol_kind::S_ASSIGN: // ASSIGN
      case symbol_kind::S_EQUAL: // EQUAL
      case symbol_kind::S_LESS: // LESS
      case symbol_kind::S_AT: // AT
      case symbol_kind::S_MOD: // MOD
        value.move< Loonguage::TokenSymbol > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_actual: // actual
        value.move< std::shared_ptr<Loonguage::NodeActual> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_actuals: // actuals
        value.move< std::shared_ptr<Loonguage::NodeActuals> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr: // expr
        value.move< std::shared_ptr<Loonguage::NodeExpr> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_formal: // formal
        value.move< std::shared_ptr<Loonguage::NodeFormal> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_formals: // formals
        value.move< std::shared_ptr<Loonguage::NodeFormals> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_function: // function
        value.move< std::shared_ptr<Loonguage::NodeFunction> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_functions: // functions
        value.move< std::shared_ptr<Loonguage::NodeFunctions> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_program: // program
        value.move< std::shared_ptr<Loonguage::NodeProgram> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_sentence: // sentence
        value.move< std::shared_ptr<Loonguage::NodeSentence> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_sentences: // sentences
        value.move< std::shared_ptr<Loonguage::NodeSentences> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ERROR: // ERROR
        value.move< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
   Parser ::stack_symbol_type&
   Parser ::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_IDEN: // IDEN
        value.copy< Loonguage::TokenIden > (that.value);
        break;

      case symbol_kind::S_INT: // INT
        value.copy< Loonguage::TokenInt > (that.value);
        break;

      case symbol_kind::S_IF: // IF
      case symbol_kind::S_WHILE: // WHILE
      case symbol_kind::S_CONTINUE: // CONTINUE
      case symbol_kind::S_BREAK: // BREAK
      case symbol_kind::S_RETURN: // RETURN
        value.copy< Loonguage::TokenKeyWord > (that.value);
        break;

      case symbol_kind::S_STR: // STR
        value.copy< Loonguage::TokenString > (that.value);
        break;

      case symbol_kind::S_PLUS: // PLUS
      case symbol_kind::S_MINUS: // MINUS
      case symbol_kind::S_TIME: // TIME
      case symbol_kind::S_DIVISION: // DIVISION
      case symbol_kind::S_AND: // AND
      case symbol_kind::S_OR: // OR
      case symbol_kind::S_XOR: // XOR
      case symbol_kind::S_REV: // REV
      case symbol_kind::S_LBRACKET: // LBRACKET
      case symbol_kind::S_RBRACKET: // RBRACKET
      case symbol_kind::S_LBRACE: // LBRACE
      case symbol_kind::S_RBRACE: // RBRACE
      case symbol_kind::S_LSQUARE: // LSQUARE
      case symbol_kind::S_RSQUARE: // RSQUARE
      case symbol_kind::S_SEMICOLON: // SEMICOLON
      case symbol_kind::S_COMMA: // COMMA
      case symbol_kind::S_ASSIGN: // ASSIGN
      case symbol_kind::S_EQUAL: // EQUAL
      case symbol_kind::S_LESS: // LESS
      case symbol_kind::S_AT: // AT
      case symbol_kind::S_MOD: // MOD
        value.copy< Loonguage::TokenSymbol > (that.value);
        break;

      case symbol_kind::S_actual: // actual
        value.copy< std::shared_ptr<Loonguage::NodeActual> > (that.value);
        break;

      case symbol_kind::S_actuals: // actuals
        value.copy< std::shared_ptr<Loonguage::NodeActuals> > (that.value);
        break;

      case symbol_kind::S_expr: // expr
        value.copy< std::shared_ptr<Loonguage::NodeExpr> > (that.value);
        break;

      case symbol_kind::S_formal: // formal
        value.copy< std::shared_ptr<Loonguage::NodeFormal> > (that.value);
        break;

      case symbol_kind::S_formals: // formals
        value.copy< std::shared_ptr<Loonguage::NodeFormals> > (that.value);
        break;

      case symbol_kind::S_function: // function
        value.copy< std::shared_ptr<Loonguage::NodeFunction> > (that.value);
        break;

      case symbol_kind::S_functions: // functions
        value.copy< std::shared_ptr<Loonguage::NodeFunctions> > (that.value);
        break;

      case symbol_kind::S_program: // program
        value.copy< std::shared_ptr<Loonguage::NodeProgram> > (that.value);
        break;

      case symbol_kind::S_sentence: // sentence
        value.copy< std::shared_ptr<Loonguage::NodeSentence> > (that.value);
        break;

      case symbol_kind::S_sentences: // sentences
        value.copy< std::shared_ptr<Loonguage::NodeSentences> > (that.value);
        break;

      case symbol_kind::S_ERROR: // ERROR
        value.copy< std::string > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }

   Parser ::stack_symbol_type&
   Parser ::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_IDEN: // IDEN
        value.move< Loonguage::TokenIden > (that.value);
        break;

      case symbol_kind::S_INT: // INT
        value.move< Loonguage::TokenInt > (that.value);
        break;

      case symbol_kind::S_IF: // IF
      case symbol_kind::S_WHILE: // WHILE
      case symbol_kind::S_CONTINUE: // CONTINUE
      case symbol_kind::S_BREAK: // BREAK
      case symbol_kind::S_RETURN: // RETURN
        value.move< Loonguage::TokenKeyWord > (that.value);
        break;

      case symbol_kind::S_STR: // STR
        value.move< Loonguage::TokenString > (that.value);
        break;

      case symbol_kind::S_PLUS: // PLUS
      case symbol_kind::S_MINUS: // MINUS
      case symbol_kind::S_TIME: // TIME
      case symbol_kind::S_DIVISION: // DIVISION
      case symbol_kind::S_AND: // AND
      case symbol_kind::S_OR: // OR
      case symbol_kind::S_XOR: // XOR
      case symbol_kind::S_REV: // REV
      case symbol_kind::S_LBRACKET: // LBRACKET
      case symbol_kind::S_RBRACKET: // RBRACKET
      case symbol_kind::S_LBRACE: // LBRACE
      case symbol_kind::S_RBRACE: // RBRACE
      case symbol_kind::S_LSQUARE: // LSQUARE
      case symbol_kind::S_RSQUARE: // RSQUARE
      case symbol_kind::S_SEMICOLON: // SEMICOLON
      case symbol_kind::S_COMMA: // COMMA
      case symbol_kind::S_ASSIGN: // ASSIGN
      case symbol_kind::S_EQUAL: // EQUAL
      case symbol_kind::S_LESS: // LESS
      case symbol_kind::S_AT: // AT
      case symbol_kind::S_MOD: // MOD
        value.move< Loonguage::TokenSymbol > (that.value);
        break;

      case symbol_kind::S_actual: // actual
        value.move< std::shared_ptr<Loonguage::NodeActual> > (that.value);
        break;

      case symbol_kind::S_actuals: // actuals
        value.move< std::shared_ptr<Loonguage::NodeActuals> > (that.value);
        break;

      case symbol_kind::S_expr: // expr
        value.move< std::shared_ptr<Loonguage::NodeExpr> > (that.value);
        break;

      case symbol_kind::S_formal: // formal
        value.move< std::shared_ptr<Loonguage::NodeFormal> > (that.value);
        break;

      case symbol_kind::S_formals: // formals
        value.move< std::shared_ptr<Loonguage::NodeFormals> > (that.value);
        break;

      case symbol_kind::S_function: // function
        value.move< std::shared_ptr<Loonguage::NodeFunction> > (that.value);
        break;

      case symbol_kind::S_functions: // functions
        value.move< std::shared_ptr<Loonguage::NodeFunctions> > (that.value);
        break;

      case symbol_kind::S_program: // program
        value.move< std::shared_ptr<Loonguage::NodeProgram> > (that.value);
        break;

      case symbol_kind::S_sentence: // sentence
        value.move< std::shared_ptr<Loonguage::NodeSentence> > (that.value);
        break;

      case symbol_kind::S_sentences: // sentences
        value.move< std::shared_ptr<Loonguage::NodeSentences> > (that.value);
        break;

      case symbol_kind::S_ERROR: // ERROR
        value.move< std::string > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
   Parser ::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
   Parser ::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YY_USE (yyoutput);
    if (yysym.empty ())
      yyo << "empty symbol";
    else
      {
        symbol_kind_type yykind = yysym.kind ();
        yyo << (yykind < YYNTOKENS ? "token" : "nterm")
            << ' ' << yysym.name () << " ("
            << yysym.location << ": ";
        YY_USE (yykind);
        yyo << ')';
      }
  }
#endif

  void
   Parser ::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
   Parser ::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
   Parser ::yypop_ (int n) YY_NOEXCEPT
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
   Parser ::debug_stream () const
  {
    return *yycdebug_;
  }

  void
   Parser ::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


   Parser ::debug_level_type
   Parser ::debug_level () const
  {
    return yydebug_;
  }

  void
   Parser ::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

   Parser ::state_type
   Parser ::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
   Parser ::yy_pact_value_is_default_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yypact_ninf_;
  }

  bool
   Parser ::yy_table_value_is_error_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yytable_ninf_;
  }

  int
   Parser ::operator() ()
  {
    return parse ();
  }

  int
   Parser ::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';
    YY_STACK_PRINT ();

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token\n";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            symbol_type yylookahead (yylex (scanner, loc, idenTable, strTable, program, errs));
            yyla.move (yylookahead);
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    if (yyla.kind () == symbol_kind::S_YYerror)
    {
      // The scanner already issued an error message, process directly
      // to error recovery.  But do not keep the error token as
      // lookahead, it is too special and may lead us to an endless
      // loop in error recovery. */
      yyla.kind_ = symbol_kind::S_YYUNDEF;
      goto yyerrlab1;
    }

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.kind ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.kind ())
      {
        goto yydefault;
      }

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
      switch (yyr1_[yyn])
    {
      case symbol_kind::S_IDEN: // IDEN
        yylhs.value.emplace< Loonguage::TokenIden > ();
        break;

      case symbol_kind::S_INT: // INT
        yylhs.value.emplace< Loonguage::TokenInt > ();
        break;

      case symbol_kind::S_IF: // IF
      case symbol_kind::S_WHILE: // WHILE
      case symbol_kind::S_CONTINUE: // CONTINUE
      case symbol_kind::S_BREAK: // BREAK
      case symbol_kind::S_RETURN: // RETURN
        yylhs.value.emplace< Loonguage::TokenKeyWord > ();
        break;

      case symbol_kind::S_STR: // STR
        yylhs.value.emplace< Loonguage::TokenString > ();
        break;

      case symbol_kind::S_PLUS: // PLUS
      case symbol_kind::S_MINUS: // MINUS
      case symbol_kind::S_TIME: // TIME
      case symbol_kind::S_DIVISION: // DIVISION
      case symbol_kind::S_AND: // AND
      case symbol_kind::S_OR: // OR
      case symbol_kind::S_XOR: // XOR
      case symbol_kind::S_REV: // REV
      case symbol_kind::S_LBRACKET: // LBRACKET
      case symbol_kind::S_RBRACKET: // RBRACKET
      case symbol_kind::S_LBRACE: // LBRACE
      case symbol_kind::S_RBRACE: // RBRACE
      case symbol_kind::S_LSQUARE: // LSQUARE
      case symbol_kind::S_RSQUARE: // RSQUARE
      case symbol_kind::S_SEMICOLON: // SEMICOLON
      case symbol_kind::S_COMMA: // COMMA
      case symbol_kind::S_ASSIGN: // ASSIGN
      case symbol_kind::S_EQUAL: // EQUAL
      case symbol_kind::S_LESS: // LESS
      case symbol_kind::S_AT: // AT
      case symbol_kind::S_MOD: // MOD
        yylhs.value.emplace< Loonguage::TokenSymbol > ();
        break;

      case symbol_kind::S_actual: // actual
        yylhs.value.emplace< std::shared_ptr<Loonguage::NodeActual> > ();
        break;

      case symbol_kind::S_actuals: // actuals
        yylhs.value.emplace< std::shared_ptr<Loonguage::NodeActuals> > ();
        break;

      case symbol_kind::S_expr: // expr
        yylhs.value.emplace< std::shared_ptr<Loonguage::NodeExpr> > ();
        break;

      case symbol_kind::S_formal: // formal
        yylhs.value.emplace< std::shared_ptr<Loonguage::NodeFormal> > ();
        break;

      case symbol_kind::S_formals: // formals
        yylhs.value.emplace< std::shared_ptr<Loonguage::NodeFormals> > ();
        break;

      case symbol_kind::S_function: // function
        yylhs.value.emplace< std::shared_ptr<Loonguage::NodeFunction> > ();
        break;

      case symbol_kind::S_functions: // functions
        yylhs.value.emplace< std::shared_ptr<Loonguage::NodeFunctions> > ();
        break;

      case symbol_kind::S_program: // program
        yylhs.value.emplace< std::shared_ptr<Loonguage::NodeProgram> > ();
        break;

      case symbol_kind::S_sentence: // sentence
        yylhs.value.emplace< std::shared_ptr<Loonguage::NodeSentence> > ();
        break;

      case symbol_kind::S_sentences: // sentences
        yylhs.value.emplace< std::shared_ptr<Loonguage::NodeSentences> > ();
        break;

      case symbol_kind::S_ERROR: // ERROR
        yylhs.value.emplace< std::string > ();
        break;

      default:
        break;
    }


      // Default location.
      {
        stack_type::slice range (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, range, yylen);
        yyerror_range[1].location = yylhs.location;
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2: // program: functions
#line 116 "LoonParser.y"
{ yylhs.value.as < std::shared_ptr<Loonguage::NodeProgram> > () = std::make_shared<Loonguage::NodeProgram>(yystack_[0].value.as < std::shared_ptr<Loonguage::NodeFunctions> > ()); 
  program = yylhs.value.as < std::shared_ptr<Loonguage::NodeProgram> > ();
  }
#line 998 "LoonParser.cpp"
    break;

  case 3: // functions: function
#line 121 "LoonParser.y"
         { yylhs.value.as < std::shared_ptr<Loonguage::NodeFunctions> > () = std::make_shared<Loonguage::NodeFunctions>(yystack_[0].value.as < std::shared_ptr<Loonguage::NodeFunction> > ()); }
#line 1004 "LoonParser.cpp"
    break;

  case 4: // functions: functions function
#line 122 "LoonParser.y"
                     {yylhs.value.as < std::shared_ptr<Loonguage::NodeFunctions> > () = yystack_[1].value.as < std::shared_ptr<Loonguage::NodeFunctions> > ();
                      yylhs.value.as < std::shared_ptr<Loonguage::NodeFunctions> > ()->push_back(yystack_[0].value.as < std::shared_ptr<Loonguage::NodeFunction> > ());}
#line 1011 "LoonParser.cpp"
    break;

  case 5: // functions: functions error
#line 124 "LoonParser.y"
                  {
                //$$ = std::make_shared<Loonguage::NodeFunctions>($1);
                yylhs.value.as < std::shared_ptr<Loonguage::NodeFunctions> > () = yystack_[1].value.as < std::shared_ptr<Loonguage::NodeFunctions> > ();
}
#line 1020 "LoonParser.cpp"
    break;

  case 6: // formal: IDEN IDEN
#line 130 "LoonParser.y"
          { yylhs.value.as < std::shared_ptr<Loonguage::NodeFormal> > () = std::make_shared<Loonguage::NodeFormal>(yystack_[1].value.as < Loonguage::TokenIden > (), yystack_[0].value.as < Loonguage::TokenIden > ()); }
#line 1026 "LoonParser.cpp"
    break;

  case 7: // formals: formals COMMA formal
#line 133 "LoonParser.y"
                     { yylhs.value.as < std::shared_ptr<Loonguage::NodeFormals> > () = yystack_[2].value.as < std::shared_ptr<Loonguage::NodeFormals> > ();
                      yylhs.value.as < std::shared_ptr<Loonguage::NodeFormals> > ()->push_back(yystack_[0].value.as < std::shared_ptr<Loonguage::NodeFormal> > ());  }
#line 1033 "LoonParser.cpp"
    break;

  case 8: // formals: formal
#line 135 "LoonParser.y"
         { yylhs.value.as < std::shared_ptr<Loonguage::NodeFormals> > () = std::make_shared<Loonguage::NodeFormals>(yystack_[0].value.as < std::shared_ptr<Loonguage::NodeFormal> > ()); }
#line 1039 "LoonParser.cpp"
    break;

  case 9: // formals: error COMMA formal
#line 136 "LoonParser.y"
                     {
    yylhs.value.as < std::shared_ptr<Loonguage::NodeFormals> > () = std::make_shared<Loonguage::NodeFormals>(yystack_[0].value.as < std::shared_ptr<Loonguage::NodeFormal> > ());
}
#line 1047 "LoonParser.cpp"
    break;

  case 10: // function: IDEN IDEN LBRACKET RBRACKET sentence
#line 141 "LoonParser.y"
                                     { yylhs.value.as < std::shared_ptr<Loonguage::NodeFunction> > () = std::make_shared<Loonguage::NodeFunction>(yystack_[4].value.as < Loonguage::TokenIden > (), yystack_[3].value.as < Loonguage::TokenIden > (), std::make_shared<Loonguage::NodeFormals>(yystack_[4].value.as < Loonguage::TokenIden > ().line), yystack_[0].value.as < std::shared_ptr<Loonguage::NodeSentence> > ()); }
#line 1053 "LoonParser.cpp"
    break;

  case 11: // function: IDEN IDEN LBRACKET formals RBRACKET sentence
#line 142 "LoonParser.y"
                                               {
    yylhs.value.as < std::shared_ptr<Loonguage::NodeFunction> > () = std::make_shared<Loonguage::NodeFunction>(yystack_[5].value.as < Loonguage::TokenIden > (), yystack_[4].value.as < Loonguage::TokenIden > (), yystack_[2].value.as < std::shared_ptr<Loonguage::NodeFormals> > (), yystack_[0].value.as < std::shared_ptr<Loonguage::NodeSentence> > ()); }
#line 1060 "LoonParser.cpp"
    break;

  case 12: // function: IDEN IDEN LBRACKET error RBRACKET sentence
#line 144 "LoonParser.y"
                                             {yylhs.value.as < std::shared_ptr<Loonguage::NodeFunction> > () = std::make_shared<Loonguage::NodeFunction>(yystack_[5].value.as < Loonguage::TokenIden > (), yystack_[4].value.as < Loonguage::TokenIden > (), std::make_shared<Loonguage::NodeFormals>(yystack_[5].value.as < Loonguage::TokenIden > ().line), yystack_[0].value.as < std::shared_ptr<Loonguage::NodeSentence> > ());
    }
#line 1067 "LoonParser.cpp"
    break;

  case 13: // function: IDEN IDEN LBRACKET formals RBRACKET AT
#line 146 "LoonParser.y"
                                        {
    yylhs.value.as < std::shared_ptr<Loonguage::NodeFunction> > () = std::make_shared<Loonguage::NodeNativeFunction>(yystack_[5].value.as < Loonguage::TokenIden > (), yystack_[4].value.as < Loonguage::TokenIden > (), yystack_[2].value.as < std::shared_ptr<Loonguage::NodeFormals> > ()); 
    }
#line 1075 "LoonParser.cpp"
    break;

  case 14: // function: IDEN IDEN LBRACKET RBRACKET AT
#line 149 "LoonParser.y"
                                 { 
    yylhs.value.as < std::shared_ptr<Loonguage::NodeFunction> > () = std::make_shared<Loonguage::NodeNativeFunction>(yystack_[4].value.as < Loonguage::TokenIden > (), yystack_[3].value.as < Loonguage::TokenIden > (), std::make_shared<Loonguage::NodeFormals>(yystack_[4].value.as < Loonguage::TokenIden > ().line));
    }
#line 1083 "LoonParser.cpp"
    break;

  case 15: // sentence: expr SEMICOLON
#line 154 "LoonParser.y"
               { yylhs.value.as < std::shared_ptr<Loonguage::NodeSentence> > () = std::make_shared<Loonguage::NodeSExpr>(yystack_[1].value.as < std::shared_ptr<Loonguage::NodeExpr> > ()); }
#line 1089 "LoonParser.cpp"
    break;

  case 16: // sentence: IF LBRACKET expr RBRACKET sentence
#line 155 "LoonParser.y"
                                     { yylhs.value.as < std::shared_ptr<Loonguage::NodeSentence> > () = std::make_shared<Loonguage::NodeSIf>(yystack_[2].value.as < std::shared_ptr<Loonguage::NodeExpr> > (), yystack_[0].value.as < std::shared_ptr<Loonguage::NodeSentence> > ()); }
#line 1095 "LoonParser.cpp"
    break;

  case 17: // sentence: WHILE LBRACKET expr RBRACKET sentence
#line 156 "LoonParser.y"
                                        { yylhs.value.as < std::shared_ptr<Loonguage::NodeSentence> > () = std::make_shared<Loonguage::NodeSWhile>(yystack_[2].value.as < std::shared_ptr<Loonguage::NodeExpr> > (), yystack_[0].value.as < std::shared_ptr<Loonguage::NodeSentence> > ()); }
#line 1101 "LoonParser.cpp"
    break;

  case 18: // sentence: LBRACE sentences RBRACE
#line 157 "LoonParser.y"
                          { yylhs.value.as < std::shared_ptr<Loonguage::NodeSentence> > () = std::make_shared<Loonguage::NodeSBlock>(yystack_[1].value.as < std::shared_ptr<Loonguage::NodeSentences> > ()); }
#line 1107 "LoonParser.cpp"
    break;

  case 19: // sentence: LBRACE RBRACE
#line 158 "LoonParser.y"
                { yylhs.value.as < std::shared_ptr<Loonguage::NodeSentence> > () = std::make_shared<Loonguage::NodeSBlock>(std::make_shared<Loonguage::NodeSentences>(yystack_[1].value.as < Loonguage::TokenSymbol > ().line)); }
#line 1113 "LoonParser.cpp"
    break;

  case 20: // sentence: IDEN IDEN SEMICOLON
#line 159 "LoonParser.y"
                        { yylhs.value.as < std::shared_ptr<Loonguage::NodeSentence> > () = std::make_shared<Loonguage::NodeSDecl>(yystack_[2].value.as < Loonguage::TokenIden > (), yystack_[1].value.as < Loonguage::TokenIden > (), nullptr);}
#line 1119 "LoonParser.cpp"
    break;

  case 21: // sentence: IDEN IDEN ASSIGN expr SEMICOLON
#line 160 "LoonParser.y"
                                  { yylhs.value.as < std::shared_ptr<Loonguage::NodeSentence> > () = std::make_shared<Loonguage::NodeSDecl>(yystack_[4].value.as < Loonguage::TokenIden > (), yystack_[3].value.as < Loonguage::TokenIden > (), yystack_[1].value.as < std::shared_ptr<Loonguage::NodeExpr> > ());}
#line 1125 "LoonParser.cpp"
    break;

  case 22: // sentence: IDEN IDEN LSQUARE INT RSQUARE SEMICOLON
#line 161 "LoonParser.y"
                                          { yylhs.value.as < std::shared_ptr<Loonguage::NodeSentence> > () = std::make_shared<Loonguage::NodeSDeclArray>(yystack_[5].value.as < Loonguage::TokenIden > (), yystack_[4].value.as < Loonguage::TokenIden > (), yystack_[2].value.as < Loonguage::TokenInt > ()); }
#line 1131 "LoonParser.cpp"
    break;

  case 23: // sentence: BREAK SEMICOLON
#line 162 "LoonParser.y"
                  { yylhs.value.as < std::shared_ptr<Loonguage::NodeSentence> > () = std::make_shared<Loonguage::NodeSBreak>(yystack_[0].value.as < Loonguage::TokenSymbol > ().line);}
#line 1137 "LoonParser.cpp"
    break;

  case 24: // sentence: CONTINUE SEMICOLON
#line 163 "LoonParser.y"
                     { yylhs.value.as < std::shared_ptr<Loonguage::NodeSentence> > () = std::make_shared<Loonguage::NodeSContinue>(yystack_[0].value.as < Loonguage::TokenSymbol > ().line);}
#line 1143 "LoonParser.cpp"
    break;

  case 25: // sentence: RETURN expr SEMICOLON
#line 164 "LoonParser.y"
                        { yylhs.value.as < std::shared_ptr<Loonguage::NodeSentence> > () = std::make_shared<Loonguage::NodeSReturn>(yystack_[1].value.as < std::shared_ptr<Loonguage::NodeExpr> > ());}
#line 1149 "LoonParser.cpp"
    break;

  case 26: // sentence: RETURN SEMICOLON
#line 165 "LoonParser.y"
                   { yylhs.value.as < std::shared_ptr<Loonguage::NodeSentence> > () = std::make_shared<Loonguage::NodeSReturn>(nullptr);}
#line 1155 "LoonParser.cpp"
    break;

  case 27: // sentence: error SEMICOLON
#line 166 "LoonParser.y"
                  { yylhs.value.as < std::shared_ptr<Loonguage::NodeSentence> > () = std::make_shared<Loonguage::NodeSentence>(yystack_[0].value.as < Loonguage::TokenSymbol > ().line);}
#line 1161 "LoonParser.cpp"
    break;

  case 28: // sentence: LBRACE error RBRACE
#line 167 "LoonParser.y"
                      { yylhs.value.as < std::shared_ptr<Loonguage::NodeSentence> > () = std::make_shared<Loonguage::NodeSentence>(yystack_[2].value.as < Loonguage::TokenSymbol > ().line); }
#line 1167 "LoonParser.cpp"
    break;

  case 29: // sentences: sentence
#line 170 "LoonParser.y"
         { yylhs.value.as < std::shared_ptr<Loonguage::NodeSentences> > () = std::make_shared<Loonguage::NodeSentences>(yystack_[0].value.as < std::shared_ptr<Loonguage::NodeSentence> > ()); }
#line 1173 "LoonParser.cpp"
    break;

  case 30: // sentences: sentences sentence
#line 171 "LoonParser.y"
                     { yylhs.value.as < std::shared_ptr<Loonguage::NodeSentences> > () = yystack_[1].value.as < std::shared_ptr<Loonguage::NodeSentences> > ();
                      yylhs.value.as < std::shared_ptr<Loonguage::NodeSentences> > ()->push_back(yystack_[0].value.as < std::shared_ptr<Loonguage::NodeSentence> > ()); }
#line 1180 "LoonParser.cpp"
    break;

  case 31: // expr: IDEN
#line 175 "LoonParser.y"
     { yylhs.value.as < std::shared_ptr<Loonguage::NodeExpr> > () = std::make_shared<Loonguage::NodeEIden>(yystack_[0].value.as < Loonguage::TokenIden > ()); }
#line 1186 "LoonParser.cpp"
    break;

  case 32: // expr: IDEN LSQUARE expr RSQUARE
#line 176 "LoonParser.y"
                            { yylhs.value.as < std::shared_ptr<Loonguage::NodeExpr> > () = std::make_shared<Loonguage::NodeEIdenArray>(yystack_[3].value.as < Loonguage::TokenIden > (), yystack_[1].value.as < std::shared_ptr<Loonguage::NodeExpr> > ()); }
#line 1192 "LoonParser.cpp"
    break;

  case 33: // expr: LBRACKET expr RBRACKET
#line 177 "LoonParser.y"
                         {  yylhs.value.as < std::shared_ptr<Loonguage::NodeExpr> > () = std::make_shared<Loonguage::NodeEBracket>(yystack_[1].value.as < std::shared_ptr<Loonguage::NodeExpr> > ()); }
#line 1198 "LoonParser.cpp"
    break;

  case 34: // expr: IDEN LBRACKET actuals RBRACKET
#line 178 "LoonParser.y"
                                 {  yylhs.value.as < std::shared_ptr<Loonguage::NodeExpr> > () = std::make_shared<Loonguage::NodeEDispatch>(yystack_[3].value.as < Loonguage::TokenIden > (), yystack_[1].value.as < std::shared_ptr<Loonguage::NodeActuals> > ()); }
#line 1204 "LoonParser.cpp"
    break;

  case 35: // expr: IDEN LBRACKET RBRACKET
#line 179 "LoonParser.y"
                         {  yylhs.value.as < std::shared_ptr<Loonguage::NodeExpr> > () = std::make_shared<Loonguage::NodeEDispatch>(yystack_[2].value.as < Loonguage::TokenIden > (), std::make_shared<Loonguage::NodeActuals>(yystack_[2].value.as < Loonguage::TokenIden > ().line)); }
#line 1210 "LoonParser.cpp"
    break;

  case 36: // expr: expr PLUS expr
#line 180 "LoonParser.y"
                 {  yylhs.value.as < std::shared_ptr<Loonguage::NodeExpr> > () = std::make_shared<Loonguage::NodeECalc>(yystack_[2].value.as < std::shared_ptr<Loonguage::NodeExpr> > (), '+', yystack_[0].value.as < std::shared_ptr<Loonguage::NodeExpr> > ()); }
#line 1216 "LoonParser.cpp"
    break;

  case 37: // expr: expr MINUS expr
#line 181 "LoonParser.y"
                  {  yylhs.value.as < std::shared_ptr<Loonguage::NodeExpr> > () = std::make_shared<Loonguage::NodeECalc>(yystack_[2].value.as < std::shared_ptr<Loonguage::NodeExpr> > (), '-', yystack_[0].value.as < std::shared_ptr<Loonguage::NodeExpr> > ()); }
#line 1222 "LoonParser.cpp"
    break;

  case 38: // expr: expr TIME expr
#line 182 "LoonParser.y"
                 {  yylhs.value.as < std::shared_ptr<Loonguage::NodeExpr> > () = std::make_shared<Loonguage::NodeECalc>(yystack_[2].value.as < std::shared_ptr<Loonguage::NodeExpr> > (), '*', yystack_[0].value.as < std::shared_ptr<Loonguage::NodeExpr> > ()); }
#line 1228 "LoonParser.cpp"
    break;

  case 39: // expr: expr DIVISION expr
#line 183 "LoonParser.y"
                     {  yylhs.value.as < std::shared_ptr<Loonguage::NodeExpr> > () = std::make_shared<Loonguage::NodeECalc>(yystack_[2].value.as < std::shared_ptr<Loonguage::NodeExpr> > (), '/', yystack_[0].value.as < std::shared_ptr<Loonguage::NodeExpr> > ()); }
#line 1234 "LoonParser.cpp"
    break;

  case 40: // expr: expr AND expr
#line 184 "LoonParser.y"
                {  yylhs.value.as < std::shared_ptr<Loonguage::NodeExpr> > () = std::make_shared<Loonguage::NodeECalc>(yystack_[2].value.as < std::shared_ptr<Loonguage::NodeExpr> > (), '&', yystack_[0].value.as < std::shared_ptr<Loonguage::NodeExpr> > ()); }
#line 1240 "LoonParser.cpp"
    break;

  case 41: // expr: expr OR expr
#line 185 "LoonParser.y"
               {  yylhs.value.as < std::shared_ptr<Loonguage::NodeExpr> > () = std::make_shared<Loonguage::NodeECalc>(yystack_[2].value.as < std::shared_ptr<Loonguage::NodeExpr> > (), '|', yystack_[0].value.as < std::shared_ptr<Loonguage::NodeExpr> > ()); }
#line 1246 "LoonParser.cpp"
    break;

  case 42: // expr: expr XOR expr
#line 186 "LoonParser.y"
                {  yylhs.value.as < std::shared_ptr<Loonguage::NodeExpr> > () = std::make_shared<Loonguage::NodeECalc>(yystack_[2].value.as < std::shared_ptr<Loonguage::NodeExpr> > (), '^', yystack_[0].value.as < std::shared_ptr<Loonguage::NodeExpr> > ()); }
#line 1252 "LoonParser.cpp"
    break;

  case 43: // expr: expr MOD expr
#line 187 "LoonParser.y"
                {  yylhs.value.as < std::shared_ptr<Loonguage::NodeExpr> > () = std::make_shared<Loonguage::NodeECalc>(yystack_[2].value.as < std::shared_ptr<Loonguage::NodeExpr> > (), '%', yystack_[0].value.as < std::shared_ptr<Loonguage::NodeExpr> > ()); }
#line 1258 "LoonParser.cpp"
    break;

  case 44: // expr: expr EQUAL expr
#line 188 "LoonParser.y"
                  {  yylhs.value.as < std::shared_ptr<Loonguage::NodeExpr> > () = std::make_shared<Loonguage::NodeEEqua>(yystack_[2].value.as < std::shared_ptr<Loonguage::NodeExpr> > (), yystack_[0].value.as < std::shared_ptr<Loonguage::NodeExpr> > ()); }
#line 1264 "LoonParser.cpp"
    break;

  case 45: // expr: expr LESS expr
#line 189 "LoonParser.y"
                 {  yylhs.value.as < std::shared_ptr<Loonguage::NodeExpr> > () = std::make_shared<Loonguage::NodeELess>(yystack_[2].value.as < std::shared_ptr<Loonguage::NodeExpr> > (), yystack_[0].value.as < std::shared_ptr<Loonguage::NodeExpr> > ()); }
#line 1270 "LoonParser.cpp"
    break;

  case 46: // expr: REV expr
#line 190 "LoonParser.y"
           {  yylhs.value.as < std::shared_ptr<Loonguage::NodeExpr> > () = std::make_shared<Loonguage::NodeERev>(yystack_[0].value.as < std::shared_ptr<Loonguage::NodeExpr> > ()); }
#line 1276 "LoonParser.cpp"
    break;

  case 47: // expr: IDEN ASSIGN expr
#line 191 "LoonParser.y"
                   {  yylhs.value.as < std::shared_ptr<Loonguage::NodeExpr> > () = std::make_shared<Loonguage::NodeEAssign>(yystack_[2].value.as < Loonguage::TokenIden > (), yystack_[0].value.as < std::shared_ptr<Loonguage::NodeExpr> > ()); }
#line 1282 "LoonParser.cpp"
    break;

  case 48: // expr: IDEN LSQUARE expr RSQUARE ASSIGN expr
#line 192 "LoonParser.y"
                                        {  yylhs.value.as < std::shared_ptr<Loonguage::NodeExpr> > () = std::make_shared<Loonguage::NodeEAssignArray>(yystack_[5].value.as < Loonguage::TokenIden > (), yystack_[3].value.as < std::shared_ptr<Loonguage::NodeExpr> > (), yystack_[0].value.as < std::shared_ptr<Loonguage::NodeExpr> > ()); }
#line 1288 "LoonParser.cpp"
    break;

  case 49: // expr: INT
#line 193 "LoonParser.y"
      {  yylhs.value.as < std::shared_ptr<Loonguage::NodeExpr> > () = std::make_shared<Loonguage::NodeEInt>(yystack_[0].value.as < Loonguage::TokenInt > ()); }
#line 1294 "LoonParser.cpp"
    break;

  case 50: // expr: STR
#line 194 "LoonParser.y"
      {  yylhs.value.as < std::shared_ptr<Loonguage::NodeExpr> > () = std::make_shared<Loonguage::NodeEStr>(yystack_[0].value.as < Loonguage::TokenString > ()); }
#line 1300 "LoonParser.cpp"
    break;

  case 51: // actual: expr
#line 197 "LoonParser.y"
     { yylhs.value.as < std::shared_ptr<Loonguage::NodeActual> > () = std::make_shared<Loonguage::NodeActual>(yystack_[0].value.as < std::shared_ptr<Loonguage::NodeExpr> > ()); }
#line 1306 "LoonParser.cpp"
    break;

  case 52: // actuals: actual
#line 200 "LoonParser.y"
       { yylhs.value.as < std::shared_ptr<Loonguage::NodeActuals> > () = std::make_shared<Loonguage::NodeActuals>(yystack_[0].value.as < std::shared_ptr<Loonguage::NodeActual> > ()); }
#line 1312 "LoonParser.cpp"
    break;

  case 53: // actuals: actuals COMMA actual
#line 201 "LoonParser.y"
                       {  yylhs.value.as < std::shared_ptr<Loonguage::NodeActuals> > () = yystack_[2].value.as < std::shared_ptr<Loonguage::NodeActuals> > ();
                      yylhs.value.as < std::shared_ptr<Loonguage::NodeActuals> > ()->push_back(yystack_[0].value.as < std::shared_ptr<Loonguage::NodeActual> > ()); }
#line 1319 "LoonParser.cpp"
    break;

  case 54: // actuals: error COMMA actual
#line 203 "LoonParser.y"
                    {
    yylhs.value.as < std::shared_ptr<Loonguage::NodeActuals> > () = std::make_shared<Loonguage::NodeActuals>(yystack_[0].value.as < std::shared_ptr<Loonguage::NodeActual> > ());
}
#line 1327 "LoonParser.cpp"
    break;


#line 1331 "LoonParser.cpp"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
    }
    goto yynewstate;


  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        context yyctx (*this, yyla);
        std::string msg = yysyntax_error_ (yyctx);
        error (yyla.location, YY_MOVE (msg));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.kind () == symbol_kind::S_YYEOF)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    // Pop stack until we find a state that shifts the error token.
    for (;;)
      {
        yyn = yypact_[+yystack_[0].state];
        if (!yy_pact_value_is_default_ (yyn))
          {
            yyn += symbol_kind::S_YYerror;
            if (0 <= yyn && yyn <= yylast_
                && yycheck_[yyn] == symbol_kind::S_YYerror)
              {
                yyn = yytable_[yyn];
                if (0 < yyn)
                  break;
              }
          }

        // Pop the current state because it cannot handle the error token.
        if (yystack_.size () == 1)
          YYABORT;

        yyerror_range[1].location = yystack_[0].location;
        yy_destroy_ ("Error: popping", yystack_[0]);
        yypop_ ();
        YY_STACK_PRINT ();
      }
    {
      stack_symbol_type error_token;

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    YY_STACK_PRINT ();
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
   Parser ::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
   Parser ::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr;
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              else
                goto append;

            append:
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }

  std::string
   Parser ::symbol_name (symbol_kind_type yysymbol)
  {
    return yytnamerr_ (yytname_[yysymbol]);
  }



  //  Parser ::context.
   Parser ::context::context (const  Parser & yyparser, const symbol_type& yyla)
    : yyparser_ (yyparser)
    , yyla_ (yyla)
  {}

  int
   Parser ::context::expected_tokens (symbol_kind_type yyarg[], int yyargn) const
  {
    // Actual number of expected tokens
    int yycount = 0;

    const int yyn = yypact_[+yyparser_.yystack_[0].state];
    if (!yy_pact_value_is_default_ (yyn))
      {
        /* Start YYX at -YYN if negative to avoid negative indexes in
           YYCHECK.  In other words, skip the first -YYN actions for
           this state because they are default actions.  */
        const int yyxbegin = yyn < 0 ? -yyn : 0;
        // Stay within bounds of both yycheck and yytname.
        const int yychecklim = yylast_ - yyn + 1;
        const int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
        for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
          if (yycheck_[yyx + yyn] == yyx && yyx != symbol_kind::S_YYerror
              && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
            {
              if (!yyarg)
                ++yycount;
              else if (yycount == yyargn)
                return 0;
              else
                yyarg[yycount++] = YY_CAST (symbol_kind_type, yyx);
            }
      }

    if (yyarg && yycount == 0 && 0 < yyargn)
      yyarg[0] = symbol_kind::S_YYEMPTY;
    return yycount;
  }






  int
   Parser ::yy_syntax_error_arguments_ (const context& yyctx,
                                                 symbol_kind_type yyarg[], int yyargn) const
  {
    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state merging
         (from LALR or IELR) and default reductions corrupt the expected
         token list.  However, the list is correct for canonical LR with
         one exception: it will still contain any token that will not be
         accepted due to an error action in a later state.
    */

    if (!yyctx.lookahead ().empty ())
      {
        if (yyarg)
          yyarg[0] = yyctx.token ();
        int yyn = yyctx.expected_tokens (yyarg ? yyarg + 1 : yyarg, yyargn - 1);
        return yyn + 1;
      }
    return 0;
  }

  // Generate an error message.
  std::string
   Parser ::yysyntax_error_ (const context& yyctx) const
  {
    // Its maximum.
    enum { YYARGS_MAX = 5 };
    // Arguments of yyformat.
    symbol_kind_type yyarg[YYARGS_MAX];
    int yycount = yy_syntax_error_arguments_ (yyctx, yyarg, YYARGS_MAX);

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
      default: // Avoid compiler warnings.
        YYCASE_ (0, YY_("syntax error"));
        YYCASE_ (1, YY_("syntax error, unexpected %s"));
        YYCASE_ (2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_ (3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_ (4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_ (5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    std::ptrdiff_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += symbol_name (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char  Parser ::yypact_ninf_ = -58;

  const signed char  Parser ::yytable_ninf_ = -3;

  const short
   Parser ::yypact_[] =
  {
      -4,    -3,    13,    17,   -58,    27,   -58,   -58,   -58,    29,
      -6,    38,    51,   -58,    24,   153,    43,   -58,    41,    57,
      59,    67,    79,    55,   -58,   -58,   293,   296,   296,   109,
     -58,   -58,   164,    90,    43,   -58,   -58,   -58,   296,   296,
     -58,   -58,    48,   -58,   171,    78,   299,   296,   296,   -58,
     192,     6,   -58,   -58,   131,   296,   296,   296,   296,   296,
     296,   296,   -58,   296,   296,   296,   -58,   -58,   -58,   202,
     223,   -58,    98,   -58,   296,    81,   -58,   261,   -58,    42,
     233,   261,   -58,   -58,   -58,   -58,   -12,   -12,   -58,   -58,
      -2,    71,    -2,   282,   282,   -58,   153,   153,    97,   254,
     296,   -58,   296,    95,   -58,   -58,    99,   -58,   -58,   -58,
     296,   -58,   261
  };

  const signed char
   Parser ::yydefact_[] =
  {
       0,     0,     0,     0,     3,     0,     1,     5,     4,     0,
       0,     0,     0,     8,     0,     0,     0,     6,     0,     0,
       0,     0,     0,     0,    49,    50,    31,     0,     0,     0,
      14,    10,     0,     0,     0,    12,     9,    27,     0,     0,
      24,    23,    31,    26,     0,     0,     0,     0,     0,    46,
       0,     0,    19,    29,     0,     0,     0,     0,     0,     0,
       0,     0,    15,     0,     0,     0,    13,    11,     7,     0,
       0,    25,     0,    20,     0,     0,    35,    51,    52,     0,
       0,    47,    33,    28,    18,    30,    36,    37,    38,    39,
      40,    41,    42,    44,    45,    43,     0,     0,     0,     0,
       0,    34,     0,    32,    16,    17,     0,    21,    54,    53,
       0,    22,    48
  };

  const signed char
   Parser ::yypgoto_[] =
  {
     -58,   -58,   -58,   -13,   -58,   120,    -7,   -58,   -23,   -57,
     -58
  };

  const signed char
   Parser ::yydefgoto_[] =
  {
       0,     2,     3,    13,    14,     4,    31,    54,    32,    78,
      79
  };

  const signed char
   Parser ::yytable_[] =
  {
      44,    57,    58,    36,    49,    50,     1,     5,    35,    55,
      56,    57,    58,     6,    15,    69,    70,    -2,     7,    65,
      16,    68,    53,    77,    80,    81,    67,     1,    83,    65,
      10,    37,    86,    87,    88,    89,    90,    91,    92,    11,
      93,    94,    95,   108,    33,   109,     9,    85,    17,    12,
      34,    99,    18,    11,    19,    20,    21,    22,    23,    24,
      25,    26,   101,    24,    25,    42,    37,    46,   102,    27,
      28,    47,    29,    27,    28,    48,    38,    77,    39,    77,
      43,    30,    55,    56,    57,    58,    59,   112,    61,   104,
     105,    18,    40,    19,    20,    21,    22,    23,    24,    25,
      26,    72,    65,    73,    41,    74,    98,   100,    27,    28,
      51,    29,    19,    20,    21,    22,    23,    24,    25,    26,
      66,   106,   110,     8,   111,     0,     0,    27,    28,     0,
      29,    52,    18,     0,    19,    20,    21,    22,    23,    24,
      25,    26,     0,     0,     0,     0,     0,     0,     0,    27,
      28,     0,    29,    84,    18,     0,    19,    20,    21,    22,
      23,    24,    25,    26,     0,     0,     0,     0,     0,     0,
       0,    27,    28,     0,    29,    55,    56,    57,    58,    59,
      60,    61,    55,    56,    57,    58,    59,    60,    61,    62,
       0,     0,    63,    64,     0,    65,    71,     0,     0,    63,
      64,     0,    65,    55,    56,    57,    58,    59,    60,    61,
       0,     0,    82,    55,    56,    57,    58,    59,    60,    61,
      63,    64,    96,    65,     0,     0,     0,     0,     0,     0,
      63,    64,     0,    65,    55,    56,    57,    58,    59,    60,
      61,     0,     0,    97,    55,    56,    57,    58,    59,    60,
      61,    63,    64,     0,    65,     0,     0,   103,     0,     0,
       0,    63,    64,     0,    65,    55,    56,    57,    58,    59,
      60,    61,    55,    56,    57,    58,    59,    60,    61,   107,
       0,     0,    63,    64,     0,    65,     0,     0,     0,    63,
      64,     0,    65,    55,    56,    57,    58,    59,    60,    61,
      75,     0,     0,    45,    24,    25,    42,    24,    25,    42,
      -3,    -3,    46,    65,    27,    28,    47,    27,    28,    76,
      48
  };

  const signed char
   Parser ::yycheck_[] =
  {
      23,    13,    14,    16,    27,    28,    10,    10,    15,    11,
      12,    13,    14,     0,    20,    38,    39,     0,     1,    31,
      26,    34,    29,    46,    47,    48,    33,    10,    22,    31,
       1,    25,    55,    56,    57,    58,    59,    60,    61,    10,
      63,    64,    65,   100,    20,   102,    19,    54,    10,    20,
      26,    74,     1,    10,     3,     4,     5,     6,     7,     8,
       9,    10,    20,     8,     9,    10,    25,    19,    26,    18,
      19,    23,    21,    18,    19,    27,    19,   100,    19,   102,
      25,    30,    11,    12,    13,    14,    15,   110,    17,    96,
      97,     1,    25,     3,     4,     5,     6,     7,     8,     9,
      10,    23,    31,    25,    25,    27,     8,    26,    18,    19,
       1,    21,     3,     4,     5,     6,     7,     8,     9,    10,
      30,    24,    27,     3,    25,    -1,    -1,    18,    19,    -1,
      21,    22,     1,    -1,     3,     4,     5,     6,     7,     8,
       9,    10,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    18,
      19,    -1,    21,    22,     1,    -1,     3,     4,     5,     6,
       7,     8,     9,    10,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    18,    19,    -1,    21,    11,    12,    13,    14,    15,
      16,    17,    11,    12,    13,    14,    15,    16,    17,    25,
      -1,    -1,    28,    29,    -1,    31,    25,    -1,    -1,    28,
      29,    -1,    31,    11,    12,    13,    14,    15,    16,    17,
      -1,    -1,    20,    11,    12,    13,    14,    15,    16,    17,
      28,    29,    20,    31,    -1,    -1,    -1,    -1,    -1,    -1,
      28,    29,    -1,    31,    11,    12,    13,    14,    15,    16,
      17,    -1,    -1,    20,    11,    12,    13,    14,    15,    16,
      17,    28,    29,    -1,    31,    -1,    -1,    24,    -1,    -1,
      -1,    28,    29,    -1,    31,    11,    12,    13,    14,    15,
      16,    17,    11,    12,    13,    14,    15,    16,    17,    25,
      -1,    -1,    28,    29,    -1,    31,    -1,    -1,    -1,    28,
      29,    -1,    31,    11,    12,    13,    14,    15,    16,    17,
       1,    -1,    -1,    10,     8,     9,    10,     8,     9,    10,
      28,    29,    19,    31,    18,    19,    23,    18,    19,    20,
      27
  };

  const signed char
   Parser ::yystos_[] =
  {
       0,    10,    34,    35,    38,    10,     0,     1,    38,    19,
       1,    10,    20,    36,    37,    20,    26,    10,     1,     3,
       4,     5,     6,     7,     8,     9,    10,    18,    19,    21,
      30,    39,    41,    20,    26,    39,    36,    25,    19,    19,
      25,    25,    10,    25,    41,    10,    19,    23,    27,    41,
      41,     1,    22,    39,    40,    11,    12,    13,    14,    15,
      16,    17,    25,    28,    29,    31,    30,    39,    36,    41,
      41,    25,    23,    25,    27,     1,    20,    41,    42,    43,
      41,    41,    20,    22,    22,    39,    41,    41,    41,    41,
      41,    41,    41,    41,    41,    41,    20,    20,     8,    41,
      26,    20,    26,    24,    39,    39,    24,    25,    42,    42,
      27,    25,    41
  };

  const signed char
   Parser ::yyr1_[] =
  {
       0,    33,    34,    35,    35,    35,    36,    37,    37,    37,
      38,    38,    38,    38,    38,    39,    39,    39,    39,    39,
      39,    39,    39,    39,    39,    39,    39,    39,    39,    40,
      40,    41,    41,    41,    41,    41,    41,    41,    41,    41,
      41,    41,    41,    41,    41,    41,    41,    41,    41,    41,
      41,    42,    43,    43,    43
  };

  const signed char
   Parser ::yyr2_[] =
  {
       0,     2,     1,     1,     2,     2,     2,     3,     1,     3,
       5,     6,     6,     6,     5,     2,     5,     5,     3,     2,
       3,     5,     6,     2,     2,     3,     2,     2,     3,     1,
       2,     1,     4,     3,     4,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     2,     3,     6,     1,
       1,     1,     1,     3,     3
  };


#if YYDEBUG || 1
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const  Parser ::yytname_[] =
  {
  "END", "error", "\"invalid token\"", "IF", "WHILE", "CONTINUE", "BREAK",
  "RETURN", "INT", "STR", "IDEN", "PLUS", "MINUS", "TIME", "DIVISION",
  "AND", "OR", "XOR", "REV", "LBRACKET", "RBRACKET", "LBRACE", "RBRACE",
  "LSQUARE", "RSQUARE", "SEMICOLON", "COMMA", "ASSIGN", "EQUAL", "LESS",
  "AT", "MOD", "ERROR", "$accept", "program", "functions", "formal",
  "formals", "function", "sentence", "sentences", "expr", "actual",
  "actuals", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const unsigned char
   Parser ::yyrline_[] =
  {
       0,   115,   115,   121,   122,   124,   130,   133,   135,   136,
     141,   142,   144,   146,   149,   154,   155,   156,   157,   158,
     159,   160,   161,   162,   163,   164,   165,   166,   167,   170,
     171,   175,   176,   177,   178,   179,   180,   181,   182,   183,
     184,   185,   186,   187,   188,   189,   190,   191,   192,   193,
     194,   197,   200,   201,   203
  };

  void
   Parser ::yy_stack_print_ () const
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  void
   Parser ::yy_reduce_print_ (int yyrule) const
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG


#line 9 "LoonParser.y"
} // LoonScanner
#line 1910 "LoonParser.cpp"

#line 207 "LoonParser.y"

/*Parser实现错误处理接口*/
void LoonScanner::Parser::error(const LoonScanner::location& location,const std::string& message){
    errs.push_back(Loonguage::Error( std::string("Syntax Analysis"), location.begin.line, message ));
}
