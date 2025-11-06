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
#line 37 "LoonParser.y"

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

#line 56 "LoonParser.cpp"




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
#line 156 "LoonParser.cpp"

  /// Build a parser object.
   Parser :: Parser  (LoonScanner::Scanner& scanner_yyarg, Loonguage::SymbolTable<std::string>& idenTable_yyarg, Loonguage::SymbolTable<std::string>& strTable_yyarg, Loonguage::NodeProgram** program_yyarg, Loonguage::Errors& errs_yyarg)
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      scanner (scanner_yyarg),
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
      case symbol_kind::S_actual: // actual
        value.YY_MOVE_OR_COPY< Loonguage::NodeActual* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_actuals: // actuals
        value.YY_MOVE_OR_COPY< Loonguage::NodeActuals* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr: // expr
        value.YY_MOVE_OR_COPY< Loonguage::NodeExpr* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_formal: // formal
        value.YY_MOVE_OR_COPY< Loonguage::NodeFormal* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_formals: // formals
        value.YY_MOVE_OR_COPY< Loonguage::NodeFormals* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_function: // function
        value.YY_MOVE_OR_COPY< Loonguage::NodeFunction* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_functions: // functions
        value.YY_MOVE_OR_COPY< Loonguage::NodeFunctions* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_program: // program
        value.YY_MOVE_OR_COPY< Loonguage::NodeProgram* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_sentence: // sentence
        value.YY_MOVE_OR_COPY< Loonguage::NodeSentence* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_sentences: // sentences
        value.YY_MOVE_OR_COPY< Loonguage::NodeSentences* > (YY_MOVE (that.value));
        break;

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
      case symbol_kind::S_SEMICOLON: // SEMICOLON
      case symbol_kind::S_COMMA: // COMMA
      case symbol_kind::S_ASSIGN: // ASSIGN
      case symbol_kind::S_EQUAL: // EQUAL
      case symbol_kind::S_LESS: // LESS
        value.YY_MOVE_OR_COPY< Loonguage::TokenSymbol > (YY_MOVE (that.value));
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
      case symbol_kind::S_actual: // actual
        value.move< Loonguage::NodeActual* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_actuals: // actuals
        value.move< Loonguage::NodeActuals* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr: // expr
        value.move< Loonguage::NodeExpr* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_formal: // formal
        value.move< Loonguage::NodeFormal* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_formals: // formals
        value.move< Loonguage::NodeFormals* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_function: // function
        value.move< Loonguage::NodeFunction* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_functions: // functions
        value.move< Loonguage::NodeFunctions* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_program: // program
        value.move< Loonguage::NodeProgram* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_sentence: // sentence
        value.move< Loonguage::NodeSentence* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_sentences: // sentences
        value.move< Loonguage::NodeSentences* > (YY_MOVE (that.value));
        break;

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
      case symbol_kind::S_SEMICOLON: // SEMICOLON
      case symbol_kind::S_COMMA: // COMMA
      case symbol_kind::S_ASSIGN: // ASSIGN
      case symbol_kind::S_EQUAL: // EQUAL
      case symbol_kind::S_LESS: // LESS
        value.move< Loonguage::TokenSymbol > (YY_MOVE (that.value));
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
      case symbol_kind::S_actual: // actual
        value.copy< Loonguage::NodeActual* > (that.value);
        break;

      case symbol_kind::S_actuals: // actuals
        value.copy< Loonguage::NodeActuals* > (that.value);
        break;

      case symbol_kind::S_expr: // expr
        value.copy< Loonguage::NodeExpr* > (that.value);
        break;

      case symbol_kind::S_formal: // formal
        value.copy< Loonguage::NodeFormal* > (that.value);
        break;

      case symbol_kind::S_formals: // formals
        value.copy< Loonguage::NodeFormals* > (that.value);
        break;

      case symbol_kind::S_function: // function
        value.copy< Loonguage::NodeFunction* > (that.value);
        break;

      case symbol_kind::S_functions: // functions
        value.copy< Loonguage::NodeFunctions* > (that.value);
        break;

      case symbol_kind::S_program: // program
        value.copy< Loonguage::NodeProgram* > (that.value);
        break;

      case symbol_kind::S_sentence: // sentence
        value.copy< Loonguage::NodeSentence* > (that.value);
        break;

      case symbol_kind::S_sentences: // sentences
        value.copy< Loonguage::NodeSentences* > (that.value);
        break;

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
      case symbol_kind::S_SEMICOLON: // SEMICOLON
      case symbol_kind::S_COMMA: // COMMA
      case symbol_kind::S_ASSIGN: // ASSIGN
      case symbol_kind::S_EQUAL: // EQUAL
      case symbol_kind::S_LESS: // LESS
        value.copy< Loonguage::TokenSymbol > (that.value);
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
      case symbol_kind::S_actual: // actual
        value.move< Loonguage::NodeActual* > (that.value);
        break;

      case symbol_kind::S_actuals: // actuals
        value.move< Loonguage::NodeActuals* > (that.value);
        break;

      case symbol_kind::S_expr: // expr
        value.move< Loonguage::NodeExpr* > (that.value);
        break;

      case symbol_kind::S_formal: // formal
        value.move< Loonguage::NodeFormal* > (that.value);
        break;

      case symbol_kind::S_formals: // formals
        value.move< Loonguage::NodeFormals* > (that.value);
        break;

      case symbol_kind::S_function: // function
        value.move< Loonguage::NodeFunction* > (that.value);
        break;

      case symbol_kind::S_functions: // functions
        value.move< Loonguage::NodeFunctions* > (that.value);
        break;

      case symbol_kind::S_program: // program
        value.move< Loonguage::NodeProgram* > (that.value);
        break;

      case symbol_kind::S_sentence: // sentence
        value.move< Loonguage::NodeSentence* > (that.value);
        break;

      case symbol_kind::S_sentences: // sentences
        value.move< Loonguage::NodeSentences* > (that.value);
        break;

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
      case symbol_kind::S_SEMICOLON: // SEMICOLON
      case symbol_kind::S_COMMA: // COMMA
      case symbol_kind::S_ASSIGN: // ASSIGN
      case symbol_kind::S_EQUAL: // EQUAL
      case symbol_kind::S_LESS: // LESS
        value.move< Loonguage::TokenSymbol > (that.value);
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
            symbol_type yylookahead (yylex (scanner, idenTable, strTable, program, errs));
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
      case symbol_kind::S_actual: // actual
        yylhs.value.emplace< Loonguage::NodeActual* > ();
        break;

      case symbol_kind::S_actuals: // actuals
        yylhs.value.emplace< Loonguage::NodeActuals* > ();
        break;

      case symbol_kind::S_expr: // expr
        yylhs.value.emplace< Loonguage::NodeExpr* > ();
        break;

      case symbol_kind::S_formal: // formal
        yylhs.value.emplace< Loonguage::NodeFormal* > ();
        break;

      case symbol_kind::S_formals: // formals
        yylhs.value.emplace< Loonguage::NodeFormals* > ();
        break;

      case symbol_kind::S_function: // function
        yylhs.value.emplace< Loonguage::NodeFunction* > ();
        break;

      case symbol_kind::S_functions: // functions
        yylhs.value.emplace< Loonguage::NodeFunctions* > ();
        break;

      case symbol_kind::S_program: // program
        yylhs.value.emplace< Loonguage::NodeProgram* > ();
        break;

      case symbol_kind::S_sentence: // sentence
        yylhs.value.emplace< Loonguage::NodeSentence* > ();
        break;

      case symbol_kind::S_sentences: // sentences
        yylhs.value.emplace< Loonguage::NodeSentences* > ();
        break;

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
      case symbol_kind::S_SEMICOLON: // SEMICOLON
      case symbol_kind::S_COMMA: // COMMA
      case symbol_kind::S_ASSIGN: // ASSIGN
      case symbol_kind::S_EQUAL: // EQUAL
      case symbol_kind::S_LESS: // LESS
        yylhs.value.emplace< Loonguage::TokenSymbol > ();
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
#line 112 "LoonParser.y"
{ yylhs.value.as < Loonguage::NodeProgram* > () = new Loonguage::NodeProgram(yystack_[0].value.as < Loonguage::NodeFunctions* > ()); 
  *program = yylhs.value.as < Loonguage::NodeProgram* > ();
  }
#line 976 "LoonParser.cpp"
    break;

  case 3: // functions: function
#line 117 "LoonParser.y"
         { yylhs.value.as < Loonguage::NodeFunctions* > () = new Loonguage::NodeFunctions(yystack_[0].value.as < Loonguage::NodeFunction* > ()); }
#line 982 "LoonParser.cpp"
    break;

  case 4: // functions: functions function
#line 118 "LoonParser.y"
                     {yylhs.value.as < Loonguage::NodeFunctions* > () = yystack_[1].value.as < Loonguage::NodeFunctions* > ();
                      yylhs.value.as < Loonguage::NodeFunctions* > ()->push_back(yystack_[0].value.as < Loonguage::NodeFunction* > ());}
#line 989 "LoonParser.cpp"
    break;

  case 5: // functions: functions error
#line 120 "LoonParser.y"
                  {
                //$$ = new Loonguage::NodeFunctions($1);
                yylhs.value.as < Loonguage::NodeFunctions* > () = yystack_[1].value.as < Loonguage::NodeFunctions* > ();
}
#line 998 "LoonParser.cpp"
    break;

  case 6: // formal: IDEN IDEN
#line 126 "LoonParser.y"
          { yylhs.value.as < Loonguage::NodeFormal* > () = new Loonguage::NodeFormal(yystack_[1].value.as < Loonguage::TokenIden > (), yystack_[0].value.as < Loonguage::TokenIden > ()); }
#line 1004 "LoonParser.cpp"
    break;

  case 7: // formals: formals COMMA formal
#line 129 "LoonParser.y"
                     { yylhs.value.as < Loonguage::NodeFormals* > () = yystack_[2].value.as < Loonguage::NodeFormals* > ();
                      yylhs.value.as < Loonguage::NodeFormals* > ()->push_back(yystack_[0].value.as < Loonguage::NodeFormal* > ());  }
#line 1011 "LoonParser.cpp"
    break;

  case 8: // formals: formal
#line 131 "LoonParser.y"
         { yylhs.value.as < Loonguage::NodeFormals* > () = new Loonguage::NodeFormals(yystack_[0].value.as < Loonguage::NodeFormal* > ()); }
#line 1017 "LoonParser.cpp"
    break;

  case 9: // formals: error COMMA formal
#line 132 "LoonParser.y"
                     {
    yylhs.value.as < Loonguage::NodeFormals* > () = new Loonguage::NodeFormals(yystack_[0].value.as < Loonguage::NodeFormal* > ());
}
#line 1025 "LoonParser.cpp"
    break;

  case 10: // function: IDEN IDEN LBRACKET RBRACKET sentence
#line 137 "LoonParser.y"
                                     { yylhs.value.as < Loonguage::NodeFunction* > () = new Loonguage::NodeFunction(yystack_[4].value.as < Loonguage::TokenIden > (), yystack_[3].value.as < Loonguage::TokenIden > (), new Loonguage::NodeFormals(yystack_[4].value.as < Loonguage::TokenIden > ().line), yystack_[0].value.as < Loonguage::NodeSentence* > ()); }
#line 1031 "LoonParser.cpp"
    break;

  case 11: // function: IDEN IDEN LBRACKET formals RBRACKET sentence
#line 138 "LoonParser.y"
                                               {
    yylhs.value.as < Loonguage::NodeFunction* > () = new Loonguage::NodeFunction(yystack_[5].value.as < Loonguage::TokenIden > (), yystack_[4].value.as < Loonguage::TokenIden > (), yystack_[2].value.as < Loonguage::NodeFormals* > (), yystack_[0].value.as < Loonguage::NodeSentence* > ()); }
#line 1038 "LoonParser.cpp"
    break;

  case 12: // function: IDEN IDEN LBRACKET error RBRACKET sentence
#line 140 "LoonParser.y"
                                             {yylhs.value.as < Loonguage::NodeFunction* > () = new Loonguage::NodeFunction(yystack_[5].value.as < Loonguage::TokenIden > (), yystack_[4].value.as < Loonguage::TokenIden > (), new Loonguage::NodeFormals(yystack_[5].value.as < Loonguage::TokenIden > ().line), yystack_[0].value.as < Loonguage::NodeSentence* > ());
    }
#line 1045 "LoonParser.cpp"
    break;

  case 13: // sentence: expr SEMICOLON
#line 144 "LoonParser.y"
               { yylhs.value.as < Loonguage::NodeSentence* > () = new Loonguage::NodeSExpr(yystack_[1].value.as < Loonguage::NodeExpr* > ()); }
#line 1051 "LoonParser.cpp"
    break;

  case 14: // sentence: IF LBRACKET expr RBRACKET sentence
#line 145 "LoonParser.y"
                                     { yylhs.value.as < Loonguage::NodeSentence* > () = new Loonguage::NodeSIf(yystack_[2].value.as < Loonguage::NodeExpr* > (), yystack_[0].value.as < Loonguage::NodeSentence* > ()); }
#line 1057 "LoonParser.cpp"
    break;

  case 15: // sentence: WHILE LBRACKET expr RBRACKET sentence
#line 146 "LoonParser.y"
                                        { yylhs.value.as < Loonguage::NodeSentence* > () = new Loonguage::NodeSWhile(yystack_[2].value.as < Loonguage::NodeExpr* > (), yystack_[0].value.as < Loonguage::NodeSentence* > ()); }
#line 1063 "LoonParser.cpp"
    break;

  case 16: // sentence: LBRACE sentences RBRACE
#line 147 "LoonParser.y"
                          { yylhs.value.as < Loonguage::NodeSentence* > () = new Loonguage::NodeSBlock(yystack_[1].value.as < Loonguage::NodeSentences* > ()); }
#line 1069 "LoonParser.cpp"
    break;

  case 17: // sentence: LBRACE RBRACE
#line 148 "LoonParser.y"
                { yylhs.value.as < Loonguage::NodeSentence* > () = new Loonguage::NodeSBlock(new Loonguage::NodeSentences(yystack_[1].value.as < Loonguage::TokenSymbol > ().line)); }
#line 1075 "LoonParser.cpp"
    break;

  case 18: // sentence: IDEN IDEN SEMICOLON
#line 149 "LoonParser.y"
                      { yylhs.value.as < Loonguage::NodeSentence* > () = new Loonguage::NodeSDecl(yystack_[2].value.as < Loonguage::TokenIden > (), yystack_[1].value.as < Loonguage::TokenIden > ());}
#line 1081 "LoonParser.cpp"
    break;

  case 19: // sentence: BREAK SEMICOLON
#line 150 "LoonParser.y"
                  { yylhs.value.as < Loonguage::NodeSentence* > () = new Loonguage::NodeSBreak(yystack_[0].value.as < Loonguage::TokenSymbol > ().line);}
#line 1087 "LoonParser.cpp"
    break;

  case 20: // sentence: CONTINUE SEMICOLON
#line 151 "LoonParser.y"
                     { yylhs.value.as < Loonguage::NodeSentence* > () = new Loonguage::NodeSContinue(yystack_[0].value.as < Loonguage::TokenSymbol > ().line);}
#line 1093 "LoonParser.cpp"
    break;

  case 21: // sentence: RETURN expr SEMICOLON
#line 152 "LoonParser.y"
                        { yylhs.value.as < Loonguage::NodeSentence* > () = new Loonguage::NodeSReturn(yystack_[1].value.as < Loonguage::NodeExpr* > ());}
#line 1099 "LoonParser.cpp"
    break;

  case 22: // sentence: error SEMICOLON
#line 153 "LoonParser.y"
                  { yylhs.value.as < Loonguage::NodeSentence* > () = new Loonguage::NodeSentence(yystack_[0].value.as < Loonguage::TokenSymbol > ().line);}
#line 1105 "LoonParser.cpp"
    break;

  case 23: // sentence: LBRACE error RBRACE
#line 154 "LoonParser.y"
                      { yylhs.value.as < Loonguage::NodeSentence* > () = new Loonguage::NodeSentence(yystack_[2].value.as < Loonguage::TokenSymbol > ().line); }
#line 1111 "LoonParser.cpp"
    break;

  case 24: // sentences: sentence
#line 157 "LoonParser.y"
         { yylhs.value.as < Loonguage::NodeSentences* > () = new Loonguage::NodeSentences(yystack_[0].value.as < Loonguage::NodeSentence* > ()); }
#line 1117 "LoonParser.cpp"
    break;

  case 25: // sentences: sentences sentence
#line 158 "LoonParser.y"
                     { yylhs.value.as < Loonguage::NodeSentences* > () = yystack_[1].value.as < Loonguage::NodeSentences* > ();
                      yylhs.value.as < Loonguage::NodeSentences* > ()->push_back(yystack_[0].value.as < Loonguage::NodeSentence* > ()); }
#line 1124 "LoonParser.cpp"
    break;

  case 26: // expr: IDEN
#line 162 "LoonParser.y"
     { yylhs.value.as < Loonguage::NodeExpr* > () = new Loonguage::NodeEIden(yystack_[0].value.as < Loonguage::TokenIden > ()); }
#line 1130 "LoonParser.cpp"
    break;

  case 27: // expr: LBRACKET expr RBRACKET
#line 163 "LoonParser.y"
                         {  yylhs.value.as < Loonguage::NodeExpr* > () = new Loonguage::NodeEBracket(yystack_[1].value.as < Loonguage::NodeExpr* > ()); }
#line 1136 "LoonParser.cpp"
    break;

  case 28: // expr: IDEN LBRACKET actuals RBRACKET
#line 164 "LoonParser.y"
                                 {  yylhs.value.as < Loonguage::NodeExpr* > () = new Loonguage::NodeEDispatch(yystack_[3].value.as < Loonguage::TokenIden > (), yystack_[1].value.as < Loonguage::NodeActuals* > ()); }
#line 1142 "LoonParser.cpp"
    break;

  case 29: // expr: IDEN LBRACKET RBRACKET
#line 165 "LoonParser.y"
                         {  yylhs.value.as < Loonguage::NodeExpr* > () = new Loonguage::NodeEDispatch(yystack_[2].value.as < Loonguage::TokenIden > (), new Loonguage::NodeActuals(yystack_[2].value.as < Loonguage::TokenIden > ().line)); }
#line 1148 "LoonParser.cpp"
    break;

  case 30: // expr: expr PLUS expr
#line 166 "LoonParser.y"
                 {  yylhs.value.as < Loonguage::NodeExpr* > () = new Loonguage::NodeECalc(yystack_[2].value.as < Loonguage::NodeExpr* > (), '+', yystack_[0].value.as < Loonguage::NodeExpr* > ()); }
#line 1154 "LoonParser.cpp"
    break;

  case 31: // expr: expr MINUS expr
#line 167 "LoonParser.y"
                  {  yylhs.value.as < Loonguage::NodeExpr* > () = new Loonguage::NodeECalc(yystack_[2].value.as < Loonguage::NodeExpr* > (), '-', yystack_[0].value.as < Loonguage::NodeExpr* > ()); }
#line 1160 "LoonParser.cpp"
    break;

  case 32: // expr: expr TIME expr
#line 168 "LoonParser.y"
                 {  yylhs.value.as < Loonguage::NodeExpr* > () = new Loonguage::NodeECalc(yystack_[2].value.as < Loonguage::NodeExpr* > (), '*', yystack_[0].value.as < Loonguage::NodeExpr* > ()); }
#line 1166 "LoonParser.cpp"
    break;

  case 33: // expr: expr DIVISION expr
#line 169 "LoonParser.y"
                     {  yylhs.value.as < Loonguage::NodeExpr* > () = new Loonguage::NodeECalc(yystack_[2].value.as < Loonguage::NodeExpr* > (), '/', yystack_[0].value.as < Loonguage::NodeExpr* > ()); }
#line 1172 "LoonParser.cpp"
    break;

  case 34: // expr: expr AND expr
#line 170 "LoonParser.y"
                {  yylhs.value.as < Loonguage::NodeExpr* > () = new Loonguage::NodeECalc(yystack_[2].value.as < Loonguage::NodeExpr* > (), '&', yystack_[0].value.as < Loonguage::NodeExpr* > ()); }
#line 1178 "LoonParser.cpp"
    break;

  case 35: // expr: expr OR expr
#line 171 "LoonParser.y"
               {  yylhs.value.as < Loonguage::NodeExpr* > () = new Loonguage::NodeECalc(yystack_[2].value.as < Loonguage::NodeExpr* > (), '|', yystack_[0].value.as < Loonguage::NodeExpr* > ()); }
#line 1184 "LoonParser.cpp"
    break;

  case 36: // expr: expr XOR expr
#line 172 "LoonParser.y"
                {  yylhs.value.as < Loonguage::NodeExpr* > () = new Loonguage::NodeECalc(yystack_[2].value.as < Loonguage::NodeExpr* > (), '^', yystack_[0].value.as < Loonguage::NodeExpr* > ()); }
#line 1190 "LoonParser.cpp"
    break;

  case 37: // expr: expr EQUAL expr
#line 173 "LoonParser.y"
                  {  yylhs.value.as < Loonguage::NodeExpr* > () = new Loonguage::NodeEEqua(yystack_[2].value.as < Loonguage::NodeExpr* > (), yystack_[0].value.as < Loonguage::NodeExpr* > ()); }
#line 1196 "LoonParser.cpp"
    break;

  case 38: // expr: expr LESS expr
#line 174 "LoonParser.y"
                 {  yylhs.value.as < Loonguage::NodeExpr* > () = new Loonguage::NodeELess(yystack_[2].value.as < Loonguage::NodeExpr* > (), yystack_[0].value.as < Loonguage::NodeExpr* > ()); }
#line 1202 "LoonParser.cpp"
    break;

  case 39: // expr: REV expr
#line 175 "LoonParser.y"
           {  yylhs.value.as < Loonguage::NodeExpr* > () = new Loonguage::NodeERev(yystack_[0].value.as < Loonguage::NodeExpr* > ()); }
#line 1208 "LoonParser.cpp"
    break;

  case 40: // expr: IDEN ASSIGN expr
#line 176 "LoonParser.y"
                   {  yylhs.value.as < Loonguage::NodeExpr* > () = new Loonguage::NodeEAssign(yystack_[2].value.as < Loonguage::TokenIden > (), yystack_[0].value.as < Loonguage::NodeExpr* > ()); }
#line 1214 "LoonParser.cpp"
    break;

  case 41: // expr: INT
#line 177 "LoonParser.y"
      {  yylhs.value.as < Loonguage::NodeExpr* > () = new Loonguage::NodeEInt(yystack_[0].value.as < Loonguage::TokenInt > ()); }
#line 1220 "LoonParser.cpp"
    break;

  case 42: // expr: STR
#line 178 "LoonParser.y"
      {  yylhs.value.as < Loonguage::NodeExpr* > () = new Loonguage::NodeEStr(yystack_[0].value.as < Loonguage::TokenString > ()); }
#line 1226 "LoonParser.cpp"
    break;

  case 43: // actual: expr
#line 181 "LoonParser.y"
     { yylhs.value.as < Loonguage::NodeActual* > () = new Loonguage::NodeActual(yystack_[0].value.as < Loonguage::NodeExpr* > ()); }
#line 1232 "LoonParser.cpp"
    break;

  case 44: // actuals: actual
#line 184 "LoonParser.y"
       { yylhs.value.as < Loonguage::NodeActuals* > () = new Loonguage::NodeActuals(yystack_[0].value.as < Loonguage::NodeActual* > ()); }
#line 1238 "LoonParser.cpp"
    break;

  case 45: // actuals: actuals COMMA actual
#line 185 "LoonParser.y"
                       {  yylhs.value.as < Loonguage::NodeActuals* > () = yystack_[2].value.as < Loonguage::NodeActuals* > ();
                      yylhs.value.as < Loonguage::NodeActuals* > ()->push_back(yystack_[0].value.as < Loonguage::NodeActual* > ()); }
#line 1245 "LoonParser.cpp"
    break;

  case 46: // actuals: error COMMA actual
#line 187 "LoonParser.y"
                    {
    yylhs.value.as < Loonguage::NodeActuals* > () = new Loonguage::NodeActuals(yystack_[0].value.as < Loonguage::NodeActual* > ());
}
#line 1253 "LoonParser.cpp"
    break;


#line 1257 "LoonParser.cpp"

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


  const signed char  Parser ::yypact_ninf_ = -16;

  const signed char  Parser ::yytable_ninf_ = -3;

  const short
   Parser ::yypact_[] =
  {
      -8,     2,    34,    64,   -16,    28,   -16,   -16,   -16,    87,
      11,    65,    77,   -16,    69,    77,    66,   -16,    68,    73,
      90,    89,   107,   193,   -16,   -16,    41,   193,   193,     0,
     -16,    88,    77,    66,   -16,   -16,   -16,   193,   193,   -16,
     -16,    44,   105,   117,    19,   193,   -16,   122,     1,   -16,
     -16,    49,   193,   193,   193,   193,   193,   193,   193,   -16,
     193,   193,   -16,   -16,   139,   156,   -16,   -16,    86,   -16,
     173,   -16,    70,   173,   -16,   -16,   -16,   -16,    48,    48,
     -16,   -16,   132,   112,   132,   180,   180,    77,    77,   193,
     -16,   193,   -16,   -16,   -16,   -16
  };

  const signed char
   Parser ::yydefact_[] =
  {
       0,     0,     0,     0,     3,     0,     1,     5,     4,     0,
       0,     0,     0,     8,     0,     0,     0,     6,     0,     0,
       0,     0,     0,     0,    41,    42,    26,     0,     0,     0,
      10,     0,     0,     0,    12,     9,    22,     0,     0,    20,
      19,    26,     0,     0,     0,     0,    39,     0,     0,    17,
      24,     0,     0,     0,     0,     0,     0,     0,     0,    13,
       0,     0,    11,     7,     0,     0,    21,    18,     0,    29,
      43,    44,     0,    40,    27,    23,    16,    25,    30,    31,
      32,    33,    34,    35,    36,    37,    38,     0,     0,     0,
      28,     0,    14,    15,    46,    45
  };

  const signed char
   Parser ::yypgoto_[] =
  {
     -16,   -16,   -16,    -3,   -16,   110,   -15,   -16,   -12,    17,
     -16
  };

  const signed char
   Parser ::yydefgoto_[] =
  {
       0,     2,     3,    13,    14,     4,    30,    51,    31,    71,
      72
  };

  const signed char
   Parser ::yytable_[] =
  {
      34,    48,     1,    19,    20,    21,    22,    23,    24,    25,
      26,    42,     5,    35,    50,    46,    47,    62,    27,    28,
      68,    29,    49,    75,    36,    64,    65,    24,    25,    41,
      63,    15,    70,    73,     6,    16,    77,    27,    28,    69,
      78,    79,    80,    81,    82,    83,    84,     9,    85,    86,
      18,    43,    19,    20,    21,    22,    23,    24,    25,    26,
      44,    54,    55,    44,    -2,     7,    45,    27,    28,    45,
      29,    76,    92,    93,     1,    17,    11,    70,    18,    70,
      19,    20,    21,    22,    23,    24,    25,    26,    10,    32,
      90,    36,    37,    33,    91,    27,    28,    11,    29,    52,
      53,    54,    55,    56,    57,    58,    94,    12,    95,    38,
      89,    59,    39,     8,    60,    61,    52,    53,    54,    55,
      56,    57,    58,    52,    53,    54,    55,    56,    66,    58,
      40,    60,    61,    52,    53,    54,    55,    56,    57,    58,
      67,     0,    74,    52,    53,    54,    55,     0,    60,    61,
      52,    53,    54,    55,    56,    57,    58,     0,     0,    87,
       0,     0,     0,     0,     0,    60,    61,    52,    53,    54,
      55,    56,    57,    58,     0,     0,    88,     0,     0,     0,
       0,     0,    60,    61,    52,    53,    54,    55,    56,    57,
      58,    52,    53,    54,    55,    56,    57,    58,     0,    60,
      61,    24,    25,    41,     0,     0,    -3,    -3,     0,     0,
       0,    27,    28
  };

  const signed char
   Parser ::yycheck_[] =
  {
      15,     1,    10,     3,     4,     5,     6,     7,     8,     9,
      10,    23,    10,    16,    29,    27,    28,    32,    18,    19,
       1,    21,    22,    22,    23,    37,    38,     8,     9,    10,
      33,    20,    44,    45,     0,    24,    51,    18,    19,    20,
      52,    53,    54,    55,    56,    57,    58,    19,    60,    61,
       1,    10,     3,     4,     5,     6,     7,     8,     9,    10,
      19,    13,    14,    19,     0,     1,    25,    18,    19,    25,
      21,    22,    87,    88,    10,    10,    10,    89,     1,    91,
       3,     4,     5,     6,     7,     8,     9,    10,     1,    20,
      20,    23,    19,    24,    24,    18,    19,    10,    21,    11,
      12,    13,    14,    15,    16,    17,    89,    20,    91,    19,
      24,    23,    23,     3,    26,    27,    11,    12,    13,    14,
      15,    16,    17,    11,    12,    13,    14,    15,    23,    17,
      23,    26,    27,    11,    12,    13,    14,    15,    16,    17,
      23,    -1,    20,    11,    12,    13,    14,    -1,    26,    27,
      11,    12,    13,    14,    15,    16,    17,    -1,    -1,    20,
      -1,    -1,    -1,    -1,    -1,    26,    27,    11,    12,    13,
      14,    15,    16,    17,    -1,    -1,    20,    -1,    -1,    -1,
      -1,    -1,    26,    27,    11,    12,    13,    14,    15,    16,
      17,    11,    12,    13,    14,    15,    16,    17,    -1,    26,
      27,     8,     9,    10,    -1,    -1,    26,    27,    -1,    -1,
      -1,    18,    19
  };

  const signed char
   Parser ::yystos_[] =
  {
       0,    10,    30,    31,    34,    10,     0,     1,    34,    19,
       1,    10,    20,    32,    33,    20,    24,    10,     1,     3,
       4,     5,     6,     7,     8,     9,    10,    18,    19,    21,
      35,    37,    20,    24,    35,    32,    23,    19,    19,    23,
      23,    10,    37,    10,    19,    25,    37,    37,     1,    22,
      35,    36,    11,    12,    13,    14,    15,    16,    17,    23,
      26,    27,    35,    32,    37,    37,    23,    23,     1,    20,
      37,    38,    39,    37,    20,    22,    22,    35,    37,    37,
      37,    37,    37,    37,    37,    37,    37,    20,    20,    24,
      20,    24,    35,    35,    38,    38
  };

  const signed char
   Parser ::yyr1_[] =
  {
       0,    29,    30,    31,    31,    31,    32,    33,    33,    33,
      34,    34,    34,    35,    35,    35,    35,    35,    35,    35,
      35,    35,    35,    35,    36,    36,    37,    37,    37,    37,
      37,    37,    37,    37,    37,    37,    37,    37,    37,    37,
      37,    37,    37,    38,    39,    39,    39
  };

  const signed char
   Parser ::yyr2_[] =
  {
       0,     2,     1,     1,     2,     2,     2,     3,     1,     3,
       5,     6,     6,     2,     5,     5,     3,     2,     3,     2,
       2,     3,     2,     3,     1,     2,     1,     3,     4,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     2,
       3,     1,     1,     1,     1,     3,     3
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
  "SEMICOLON", "COMMA", "ASSIGN", "EQUAL", "LESS", "ERROR", "$accept",
  "program", "functions", "formal", "formals", "function", "sentence",
  "sentences", "expr", "actual", "actuals", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const unsigned char
   Parser ::yyrline_[] =
  {
       0,   111,   111,   117,   118,   120,   126,   129,   131,   132,
     137,   138,   140,   144,   145,   146,   147,   148,   149,   150,
     151,   152,   153,   154,   157,   158,   162,   163,   164,   165,
     166,   167,   168,   169,   170,   171,   172,   173,   174,   175,
     176,   177,   178,   181,   184,   185,   187
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
#line 1804 "LoonParser.cpp"

#line 191 "LoonParser.y"

/*Parser实现错误处理接口*/
void LoonScanner::Parser::error(const LoonScanner::location& location,const std::string& message){
    errs.push_back(Loonguage::Error( std::string("Syntax Analysis"), location.begin.line, message ));
}
