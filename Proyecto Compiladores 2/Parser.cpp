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



// First part of user prologue.
#line 12 "gramatica.y"

    #include "Lexer.hpp"
    #define yylex(v) lexer.getNextToken(v)
    
    void proyecto::Parser::error(const std::string& msg) {
        throw std::runtime_error("Error Sintáctico: " + msg + "\n");
    }

#line 50 "Parser.cpp"


#include "Parser.hpp"




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

#line 24 "gramatica.y"
namespace proyecto {
#line 129 "Parser.cpp"

  /// Build a parser object.
  Parser::Parser (Lexer &lexer_yyarg, AstNode*& astN_yyarg)
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      lexer (lexer_yyarg),
      astN (astN_yyarg)
  {}

  Parser::~Parser ()
  {}

  Parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------.
  | symbol.  |
  `---------*/

  // basic_symbol.
  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (const basic_symbol& that)
    : Base (that)
    , value (that.value)
  {}


  /// Constructor for valueless symbols.
  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t)
    : Base (t)
    , value ()
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (value_type) v)
    : Base (t)
    , value (YY_MOVE (v))
  {}


  template <typename Base>
  Parser::symbol_kind_type
  Parser::basic_symbol<Base>::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }


  template <typename Base>
  bool
  Parser::basic_symbol<Base>::empty () const YY_NOEXCEPT
  {
    return this->kind () == symbol_kind::S_YYEMPTY;
  }

  template <typename Base>
  void
  Parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move (s);
    value = YY_MOVE (s.value);
  }

  // by_kind.
  Parser::by_kind::by_kind () YY_NOEXCEPT
    : kind_ (symbol_kind::S_YYEMPTY)
  {}

#if 201103L <= YY_CPLUSPLUS
  Parser::by_kind::by_kind (by_kind&& that) YY_NOEXCEPT
    : kind_ (that.kind_)
  {
    that.clear ();
  }
#endif

  Parser::by_kind::by_kind (const by_kind& that) YY_NOEXCEPT
    : kind_ (that.kind_)
  {}

  Parser::by_kind::by_kind (token_kind_type t) YY_NOEXCEPT
    : kind_ (yytranslate_ (t))
  {}



  void
  Parser::by_kind::clear () YY_NOEXCEPT
  {
    kind_ = symbol_kind::S_YYEMPTY;
  }

  void
  Parser::by_kind::move (by_kind& that)
  {
    kind_ = that.kind_;
    that.clear ();
  }

  Parser::symbol_kind_type
  Parser::by_kind::kind () const YY_NOEXCEPT
  {
    return kind_;
  }


  Parser::symbol_kind_type
  Parser::by_kind::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }



  // by_state.
  Parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  Parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  Parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  Parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  Parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  Parser::symbol_kind_type
  Parser::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

  Parser::stack_symbol_type::stack_symbol_type ()
  {}

  Parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.value))
  {
#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  Parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.value))
  {
    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
  Parser::stack_symbol_type&
  Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    return *this;
  }

  Parser::stack_symbol_type&
  Parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  Parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);

    // User destructor.
    YY_USE (yysym.kind ());
  }

#if YYDEBUG
  template <typename Base>
  void
  Parser::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YY_USE (yyoutput);
    if (yysym.empty ())
      yyo << "empty symbol";
    else
      {
        symbol_kind_type yykind = yysym.kind ();
        yyo << (yykind < YYNTOKENS ? "token" : "nterm")
            << ' ' << yysym.name () << " (";
        YY_USE (yykind);
        yyo << ')';
      }
  }
#endif

  void
  Parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  Parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  Parser::yypop_ (int n) YY_NOEXCEPT
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  Parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  Parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  Parser::debug_level_type
  Parser::debug_level () const
  {
    return yydebug_;
  }

  void
  Parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  Parser::state_type
  Parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
  Parser::yy_pact_value_is_default_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  Parser::yy_table_value_is_error_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yytable_ninf_;
  }

  int
  Parser::operator() ()
  {
    return parse ();
  }

  int
  Parser::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

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
            yyla.kind_ = yytranslate_ (yylex (&yyla.value));
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
      /* If YYLEN is nonzero, implement the default value of the
         action: '$$ = $1'.  Otherwise, use the top of the stack.

         Otherwise, the following line sets YYLHS.VALUE to garbage.
         This behavior is undocumented and Bison users should not rely
         upon it.  */
      if (yylen)
        yylhs.value = yystack_[yylen - 1].value;
      else
        yylhs.value = yystack_[0].value;


      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2: // program: opt_statement_list
#line 42 "gramatica.y"
                            { astN = new Program(yystack_[0].value); }
#line 587 "Parser.cpp"
    break;

  case 3: // opt_statement_list: statement_list
#line 45 "gramatica.y"
                                   { yylhs.value= yystack_[0].value; }
#line 593 "Parser.cpp"
    break;

  case 4: // opt_statement_list: %empty
#line 46 "gramatica.y"
                           { yylhs.value= new StatementList({}); }
#line 599 "Parser.cpp"
    break;

  case 5: // statement_list: statement_list statement
#line 49 "gramatica.y"
                                         { 
                    yylhs.value= yystack_[1].value; 
                    reinterpret_cast<StatementList*>(yylhs.value)->stmts.push_back(yystack_[0].value);
                }
#line 608 "Parser.cpp"
    break;

  case 6: // statement_list: statement
#line 53 "gramatica.y"
                          { 
                    yylhs.value= new StatementList({});
                    reinterpret_cast<StatementList*>(yylhs.value)->stmts.push_back(yystack_[0].value);
                }
#line 617 "Parser.cpp"
    break;

  case 7: // statement: var_decl
#line 59 "gramatica.y"
                    { yylhs.value= yystack_[0].value; }
#line 623 "Parser.cpp"
    break;

  case 8: // statement: assignment
#line 60 "gramatica.y"
                      { yylhs.value= yystack_[0].value; }
#line 629 "Parser.cpp"
    break;

  case 9: // statement: if_stmt
#line 61 "gramatica.y"
                   { yylhs.value= yystack_[0].value; }
#line 635 "Parser.cpp"
    break;

  case 10: // statement: while_stmt
#line 62 "gramatica.y"
                      { yylhs.value= yystack_[0].value; }
#line 641 "Parser.cpp"
    break;

  case 11: // statement: print_stmt
#line 63 "gramatica.y"
                      { yylhs.value= yystack_[0].value; }
#line 647 "Parser.cpp"
    break;

  case 12: // statement: block
#line 64 "gramatica.y"
                 { yylhs.value= yystack_[0].value; }
#line 653 "Parser.cpp"
    break;

  case 13: // statement: array_decl
#line 65 "gramatica.y"
                      { yylhs.value= yystack_[0].value; }
#line 659 "Parser.cpp"
    break;

  case 14: // var_decl: KW_INT ident_decl opt_ident_list SEMICOLON
#line 68 "gramatica.y"
                                                     {
            yylhs.value= new VarDeclStmt(yystack_[2].value, yystack_[1].value);
        }
#line 667 "Parser.cpp"
    break;

  case 15: // opt_ident_list: opt_ident_list COMMA ident_decl
#line 73 "gramatica.y"
                                                {
                    yylhs.value= yystack_[2].value;
                    reinterpret_cast<IdentList*>(yylhs.value)->idents.push_back(yystack_[0].value);
                }
#line 676 "Parser.cpp"
    break;

  case 16: // opt_ident_list: %empty
#line 77 "gramatica.y"
                       {
                    yylhs.value= new IdentList({});
                }
#line 684 "Parser.cpp"
    break;

  case 17: // ident_decl: IDENTIFIER opt_assign_expr
#line 82 "gramatica.y"
                                       {
                yylhs.value= new IdentDecl(yystack_[1].value, yystack_[0].value);
            }
#line 692 "Parser.cpp"
    break;

  case 18: // opt_assign_expr: ASSIGN expression
#line 87 "gramatica.y"
                                   { yylhs.value= yystack_[0].value; }
#line 698 "Parser.cpp"
    break;

  case 19: // opt_assign_expr: %empty
#line 88 "gramatica.y"
                        { yylhs.value= nullptr; }
#line 704 "Parser.cpp"
    break;

  case 20: // assignment: IDENTIFIER ASSIGN expression SEMICOLON
#line 91 "gramatica.y"
                                                   {
                yylhs.value= new AssignmentStmt(yystack_[3].value, yystack_[1].value);
            }
#line 712 "Parser.cpp"
    break;

  case 21: // if_stmt: KW_IF OP_PAR expression CLOSE_PAR statement
#line 96 "gramatica.y"
                                                                {
            yylhs.value= new IfStmt(yystack_[2].value, yystack_[0].value, nullptr);
         }
#line 720 "Parser.cpp"
    break;

  case 22: // if_stmt: KW_IF OP_PAR expression CLOSE_PAR statement KW_ELSE statement
#line 99 "gramatica.y"
                                                                       {
            yylhs.value= new IfStmt(yystack_[4].value, yystack_[2].value, yystack_[0].value);
         }
#line 728 "Parser.cpp"
    break;

  case 23: // while_stmt: KW_WHILE OP_PAR expression CLOSE_PAR statement
#line 104 "gramatica.y"
                                                           {
                yylhs.value= new WhileStmt(yystack_[2].value, yystack_[0].value);
            }
#line 736 "Parser.cpp"
    break;

  case 24: // print_stmt: KW_PRINT OP_PAR expression CLOSE_PAR SEMICOLON
#line 109 "gramatica.y"
                                                           {
                yylhs.value= new PrintStmt(yystack_[2].value);
            }
#line 744 "Parser.cpp"
    break;

  case 25: // input_stmt: KW_INPUT OP_PAR CLOSE_PAR
#line 114 "gramatica.y"
                                      {
                yylhs.value= new InputStmt();
            }
#line 752 "Parser.cpp"
    break;

  case 26: // block: OP_BRACE opt_statement_list CLOSE_BRACE
#line 119 "gramatica.y"
                                               {
            yylhs.value= new BlockStmt(yystack_[1].value);
       }
#line 760 "Parser.cpp"
    break;

  case 27: // expression: logical_or
#line 124 "gramatica.y"
                       { yylhs.value= yystack_[0].value; }
#line 766 "Parser.cpp"
    break;

  case 28: // logical_or: logical_or OR logical_and
#line 127 "gramatica.y"
                                      {
                yylhs.value= new BinaryExpr(yystack_[2].value, BinaryOperator::OR, yystack_[0].value);
            }
#line 774 "Parser.cpp"
    break;

  case 29: // logical_or: logical_and
#line 130 "gramatica.y"
                        { yylhs.value= yystack_[0].value; }
#line 780 "Parser.cpp"
    break;

  case 30: // logical_and: logical_and AND equality
#line 133 "gramatica.y"
                                      {
                yylhs.value= new BinaryExpr(yystack_[2].value, BinaryOperator::AND, yystack_[0].value);
             }
#line 788 "Parser.cpp"
    break;

  case 31: // logical_and: equality
#line 136 "gramatica.y"
                      { yylhs.value= yystack_[0].value; }
#line 794 "Parser.cpp"
    break;

  case 32: // equality: equality EQUAL comparison
#line 139 "gramatica.y"
                                    {
            yylhs.value= new BinaryExpr(yystack_[2].value, BinaryOperator::EQUAL, yystack_[0].value);
          }
#line 802 "Parser.cpp"
    break;

  case 33: // equality: equality DISTINCT comparison
#line 142 "gramatica.y"
                                       {
            yylhs.value= new BinaryExpr(yystack_[2].value, BinaryOperator::DISTINCT, yystack_[0].value);
          }
#line 810 "Parser.cpp"
    break;

  case 34: // equality: comparison
#line 145 "gramatica.y"
                     { yylhs.value= yystack_[0].value; }
#line 816 "Parser.cpp"
    break;

  case 35: // comparison: comparison LESS_THAN term
#line 148 "gramatica.y"
                                      {
                yylhs.value= new BinaryExpr(yystack_[2].value, BinaryOperator::LESS_THAN, yystack_[0].value);
            }
#line 824 "Parser.cpp"
    break;

  case 36: // comparison: comparison GREATER_THAN term
#line 151 "gramatica.y"
                                         {
                yylhs.value= new BinaryExpr(yystack_[2].value, BinaryOperator::GREATER_THAN, yystack_[0].value);
            }
#line 832 "Parser.cpp"
    break;

  case 37: // comparison: comparison LESS_EQUAL term
#line 154 "gramatica.y"
                                       {
                yylhs.value= new BinaryExpr(yystack_[2].value, BinaryOperator::LESS_EQUAL, yystack_[0].value);
            }
#line 840 "Parser.cpp"
    break;

  case 38: // comparison: comparison GREATER_EQUAL term
#line 157 "gramatica.y"
                                          {
                yylhs.value= new BinaryExpr(yystack_[2].value, BinaryOperator::GREATER_EQUAL, yystack_[0].value);
            }
#line 848 "Parser.cpp"
    break;

  case 39: // comparison: term
#line 160 "gramatica.y"
                 { yylhs.value= yystack_[0].value; }
#line 854 "Parser.cpp"
    break;

  case 40: // term: term PLUS factor
#line 163 "gramatica.y"
                       {
        yylhs.value= new BinaryExpr(yystack_[2].value, BinaryOperator::PLUS, yystack_[0].value);
      }
#line 862 "Parser.cpp"
    break;

  case 41: // term: term MINUS factor
#line 166 "gramatica.y"
                        {
        yylhs.value= new BinaryExpr(yystack_[2].value, BinaryOperator::MINUS, yystack_[0].value);
      }
#line 870 "Parser.cpp"
    break;

  case 42: // term: factor
#line 169 "gramatica.y"
             { yylhs.value= yystack_[0].value; }
#line 876 "Parser.cpp"
    break;

  case 43: // factor: factor MULT unary
#line 172 "gramatica.y"
                          {
            yylhs.value= new BinaryExpr(yystack_[2].value, BinaryOperator::MULT, yystack_[0].value);
        }
#line 884 "Parser.cpp"
    break;

  case 44: // factor: factor DIV unary
#line 175 "gramatica.y"
                         {
            yylhs.value= new BinaryExpr(yystack_[2].value, BinaryOperator::DIV, yystack_[0].value);
        }
#line 892 "Parser.cpp"
    break;

  case 45: // factor: factor MOD unary
#line 178 "gramatica.y"
                         {
            yylhs.value= new BinaryExpr(yystack_[2].value, BinaryOperator::MOD, yystack_[0].value);
        }
#line 900 "Parser.cpp"
    break;

  case 46: // factor: unary
#line 181 "gramatica.y"
              { yylhs.value= yystack_[0].value; }
#line 906 "Parser.cpp"
    break;

  case 47: // unary: NOT unary
#line 184 "gramatica.y"
                 {
            yylhs.value= new UnaryExpr(UnaryOperator::NOT, yystack_[0].value);
       }
#line 914 "Parser.cpp"
    break;

  case 48: // unary: MINUS unary
#line 187 "gramatica.y"
                   {
            yylhs.value= new UnaryExpr(UnaryOperator::NEGATE, yystack_[0].value);
       }
#line 922 "Parser.cpp"
    break;

  case 49: // unary: primary
#line 190 "gramatica.y"
               { yylhs.value= yystack_[0].value; }
#line 928 "Parser.cpp"
    break;

  case 50: // primary: INTEGER
#line 193 "gramatica.y"
                 { yylhs.value= yystack_[0].value; }
#line 934 "Parser.cpp"
    break;

  case 51: // primary: FLOAT
#line 194 "gramatica.y"
               { yylhs.value= yystack_[0].value; }
#line 940 "Parser.cpp"
    break;

  case 52: // primary: IDENTIFIER
#line 195 "gramatica.y"
                    { yylhs.value= yystack_[0].value; }
#line 946 "Parser.cpp"
    break;

  case 53: // primary: input_stmt
#line 196 "gramatica.y"
                    { yylhs.value= yystack_[0].value; }
#line 952 "Parser.cpp"
    break;

  case 54: // primary: OP_PAR expression CLOSE_PAR
#line 197 "gramatica.y"
                                     { yylhs.value= new ParExpr(yystack_[1].value);  }
#line 958 "Parser.cpp"
    break;

  case 55: // array: OP_BRACKET expression CLOSE_BRACKET
#line 200 "gramatica.y"
                                           {
            yylhs.value= new ArrayAccess(yystack_[1].value);
       }
#line 966 "Parser.cpp"
    break;

  case 56: // array_decl: KW_INT IDENTIFIER array SEMICOLON
#line 205 "gramatica.y"
                                              {
                yylhs.value= new ArrayDeclStmt(yystack_[2].value, yystack_[1].value);
            }
#line 974 "Parser.cpp"
    break;

  case 57: // array_decl: array
#line 208 "gramatica.y"
                  { yylhs.value= yystack_[0].value; }
#line 980 "Parser.cpp"
    break;


#line 984 "Parser.cpp"

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
        std::string msg = YY_("syntax error");
        error (YY_MOVE (msg));
      }


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

        yy_destroy_ ("Error: popping", yystack_[0]);
        yypop_ ();
        YY_STACK_PRINT ();
      }
    {
      stack_symbol_type error_token;


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
  Parser::error (const syntax_error& yyexc)
  {
    error (yyexc.what ());
  }

#if YYDEBUG || 0
  const char *
  Parser::symbol_name (symbol_kind_type yysymbol)
  {
    return yytname_[yysymbol];
  }
#endif // #if YYDEBUG || 0









  const signed char Parser::yypact_ninf_ = -32;

  const signed char Parser::yytable_ninf_ = -1;

  const signed char
  Parser::yypact_[] =
  {
      18,     4,    20,    11,    23,    37,    18,     0,    33,   -32,
      18,   -32,   -32,   -32,   -32,   -32,   -32,   -32,   -32,   -32,
       0,    -2,   -32,     0,     0,     0,    38,   -32,   -32,   -32,
      40,     0,     0,     0,   -32,    39,    24,    26,   -12,     3,
      25,   -17,   -32,   -32,   -32,   -32,    47,     0,   -32,    48,
      35,    46,    49,    50,   -32,    51,    54,   -32,   -32,   -32,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   -32,   -32,   -32,   -32,    60,    18,    18,
      58,   -32,   -32,    26,   -12,     3,     3,    25,    25,    25,
      25,   -17,   -17,   -32,   -32,   -32,    52,   -32,    64,   -32,
     -32,    18,   -32
  };

  const signed char
  Parser::yydefact_[] =
  {
       4,     0,     0,     0,     0,     0,     4,     0,     0,     2,
       3,     6,     7,     8,     9,    10,    11,    12,    57,    13,
       0,    19,    16,     0,     0,     0,     0,    52,    50,    51,
       0,     0,     0,     0,    53,     0,    27,    29,    31,    34,
      39,    42,    46,    49,     1,     5,     0,     0,    17,     0,
       0,     0,     0,     0,    26,     0,     0,    48,    47,    55,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    20,    18,    56,    14,     0,     0,     0,
       0,    25,    54,    28,    30,    32,    33,    35,    36,    37,
      38,    40,    41,    43,    44,    45,    19,    15,    21,    23,
      24,     0,    22
  };

  const signed char
  Parser::yypgoto_[] =
  {
     -32,   -32,    67,   -32,   -10,   -32,   -32,    -3,   -32,   -32,
     -32,   -32,   -32,   -32,   -32,   -11,   -32,    15,    16,    -9,
     -22,   -18,   -31,   -32,    55,   -32
  };

  const signed char
  Parser::yydefgoto_[] =
  {
       0,     8,     9,    10,    11,    12,    50,    22,    48,    13,
      14,    15,    16,    34,    17,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    18,    19
  };

  const signed char
  Parser::yytable_[] =
  {
      45,    57,    58,    27,    28,    29,    70,    71,    72,    46,
      47,    30,    51,    52,    53,    31,    20,     7,    62,    63,
      56,     1,    32,    21,     2,     3,    23,     4,     5,    64,
      65,    66,    67,    44,    33,     6,    74,     7,    24,    93,
      94,    95,    87,    88,    89,    90,    68,    69,    76,    77,
      91,    92,    25,    85,    86,    55,    54,    60,    61,    59,
      73,    75,    78,    96,    47,    79,    80,    81,    98,    99,
      82,   100,   101,    26,    97,    83,    49,    84,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   102
  };

  const signed char
  Parser::yycheck_[] =
  {
      10,    32,    33,     3,     4,     5,    23,    24,    25,    20,
      12,    11,    23,    24,    25,    15,    12,    19,    30,    31,
      31,     3,    22,     3,     6,     7,    15,     9,    10,    26,
      27,    28,    29,     0,    34,    17,    47,    19,    15,    70,
      71,    72,    64,    65,    66,    67,    21,    22,    13,    14,
      68,    69,    15,    62,    63,    15,    18,    33,    32,    20,
      13,    13,    16,     3,    12,    16,    16,    16,    78,    79,
      16,    13,     8,     6,    77,    60,    21,    61,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   101
  };

  const signed char
  Parser::yystos_[] =
  {
       0,     3,     6,     7,     9,    10,    17,    19,    38,    39,
      40,    41,    42,    46,    47,    48,    49,    51,    61,    62,
      12,     3,    44,    15,    15,    15,    39,     3,     4,     5,
      11,    15,    22,    34,    50,    52,    53,    54,    55,    56,
      57,    58,    59,    60,     0,    41,    52,    12,    45,    61,
      43,    52,    52,    52,    18,    15,    52,    59,    59,    20,
      33,    32,    30,    31,    26,    27,    28,    29,    21,    22,
      23,    24,    25,    13,    52,    13,    13,    14,    16,    16,
      16,    16,    16,    54,    55,    56,    56,    57,    57,    57,
      57,    58,    58,    59,    59,    59,     3,    44,    41,    41,
      13,     8,    41
  };

  const signed char
  Parser::yyr1_[] =
  {
       0,    37,    38,    39,    39,    40,    40,    41,    41,    41,
      41,    41,    41,    41,    42,    43,    43,    44,    45,    45,
      46,    47,    47,    48,    49,    50,    51,    52,    53,    53,
      54,    54,    55,    55,    55,    56,    56,    56,    56,    56,
      57,    57,    57,    58,    58,    58,    58,    59,    59,    59,
      60,    60,    60,    60,    60,    61,    62,    62
  };

  const signed char
  Parser::yyr2_[] =
  {
       0,     2,     1,     1,     0,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     4,     3,     0,     2,     2,     0,
       4,     5,     7,     5,     5,     3,     3,     1,     3,     1,
       3,     1,     3,     3,     1,     3,     3,     3,     3,     1,
       3,     3,     1,     3,     3,     3,     1,     2,     2,     1,
       1,     1,     1,     1,     3,     3,     4,     1
  };


#if YYDEBUG
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const Parser::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "IDENTIFIER",
  "INTEGER", "FLOAT", "KW_INT", "KW_IF", "KW_ELSE", "KW_WHILE", "KW_PRINT",
  "KW_INPUT", "ASSIGN", "SEMICOLON", "COMMA", "OP_PAR", "CLOSE_PAR",
  "OP_BRACE", "CLOSE_BRACE", "OP_BRACKET", "CLOSE_BRACKET", "PLUS",
  "MINUS", "MULT", "DIV", "MOD", "LESS_THAN", "GREATER_THAN", "LESS_EQUAL",
  "GREATER_EQUAL", "EQUAL", "DISTINCT", "AND", "OR", "NOT", "DOT", "THEN",
  "$accept", "program", "opt_statement_list", "statement_list",
  "statement", "var_decl", "opt_ident_list", "ident_decl",
  "opt_assign_expr", "assignment", "if_stmt", "while_stmt", "print_stmt",
  "input_stmt", "block", "expression", "logical_or", "logical_and",
  "equality", "comparison", "term", "factor", "unary", "primary", "array",
  "array_decl", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const unsigned char
  Parser::yyrline_[] =
  {
       0,    42,    42,    45,    46,    49,    53,    59,    60,    61,
      62,    63,    64,    65,    68,    73,    77,    82,    87,    88,
      91,    96,    99,   104,   109,   114,   119,   124,   127,   130,
     133,   136,   139,   142,   145,   148,   151,   154,   157,   160,
     163,   166,   169,   172,   175,   178,   181,   184,   187,   190,
     193,   194,   195,   196,   197,   200,   205,   208
  };

  void
  Parser::yy_stack_print_ () const
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
  Parser::yy_reduce_print_ (int yyrule) const
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

  Parser::symbol_kind_type
  Parser::yytranslate_ (int t) YY_NOEXCEPT
  {
    // YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to
    // TOKEN-NUM as returned by yylex.
    static
    const signed char
    translate_table[] =
    {
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36
    };
    // Last valid token kind.
    const int code_max = 291;

    if (t <= 0)
      return symbol_kind::S_YYEOF;
    else if (t <= code_max)
      return static_cast <symbol_kind_type> (translate_table[t]);
    else
      return symbol_kind::S_YYUNDEF;
  }

#line 24 "gramatica.y"
} // proyecto
#line 1408 "Parser.cpp"

#line 211 "gramatica.y"
