/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_RULES_USERS_CLEMENT_WORKSPACE_ELVEX_SRC_RULESYACC_HPP_INCLUDED
# define YY_RULES_USERS_CLEMENT_WORKSPACE_ELVEX_SRC_RULESYACC_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int rulesdebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    TOKEN_RIGHTARROW = 258,        /* TOKEN_RIGHTARROW  */
    TOKEN_UPARROW = 259,           /* TOKEN_UPARROW  */
    TOKEN_UP2ARROW = 260,          /* TOKEN_UP2ARROW  */
    TOKEN_DOWNARROW = 261,         /* TOKEN_DOWNARROW  */
    TOKEN_DOWN2ARROW = 262,        /* TOKEN_DOWN2ARROW  */
    TOKEN_LPAR = 263,              /* TOKEN_LPAR  */
    TOKEN_RPAR = 264,              /* TOKEN_RPAR  */
    TOKEN_LBRACE = 265,            /* TOKEN_LBRACE  */
    TOKEN_RBRACE = 266,            /* TOKEN_RBRACE  */
    TOKEN_LBRACKET = 267,          /* TOKEN_LBRACKET  */
    TOKEN_RBRACKET = 268,          /* TOKEN_RBRACKET  */
    TOKEN_DASH = 269,              /* TOKEN_DASH  */
    TOKEN_AROBASE = 270,           /* TOKEN_AROBASE  */
    TOKEN_SEMI = 271,              /* TOKEN_SEMI  */
    TOKEN_DOT = 272,               /* TOKEN_DOT  */
    TOKEN_COLON = 273,             /* TOKEN_COLON  */
    TOKEN_DOUBLECOLON = 274,       /* TOKEN_DOUBLECOLON  */
    TOKEN_COMMA = 275,             /* TOKEN_COMMA  */
    TOKEN_RULES = 276,             /* TOKEN_RULES  */
    TOKEN_INPUT = 277,             /* TOKEN_INPUT  */
    TOKEN_LEXICON = 278,           /* TOKEN_LEXICON  */
    TOKEN_LEMMA = 279,             /* TOKEN_LEMMA  */
    TOKEN_PRED = 280,              /* TOKEN_PRED  */
    TOKEN_FORM = 281,              /* TOKEN_FORM  */
    TOKEN_ATTEST = 282,            /* TOKEN_ATTEST  */
    TOKEN_PRINT = 283,             /* TOKEN_PRINT  */
    TOKEN_PRINTLN = 284,           /* TOKEN_PRINTLN  */
    TOKEN_IF = 285,                /* TOKEN_IF  */
    TOKEN_ELSE = 286,              /* TOKEN_ELSE  */
    TOKEN_NIL = 287,               /* TOKEN_NIL  */
    TOKEN_TRUE = 288,              /* TOKEN_TRUE  */
    TOKEN_FALSE = 289,             /* TOKEN_FALSE  */
    TOKEN_FOREACH = 290,           /* TOKEN_FOREACH  */
    TOKEN_IN = 291,                /* TOKEN_IN  */
    TOKEN_SEARCH = 292,            /* TOKEN_SEARCH  */
    TOKEN_RAND = 293,              /* TOKEN_RAND  */
    TOKEN_TRACE = 294,             /* TOKEN_TRACE  */
    TOKEN_UNION = 295,             /* TOKEN_UNION  */
    TOKEN_SUBSUME = 296,           /* TOKEN_SUBSUME  */
    TOKEN_AFF = 297,               /* TOKEN_AFF  */
    TOKEN_PIPE = 298,              /* TOKEN_PIPE  */
    TOKEN_NOT = 299,               /* TOKEN_NOT  */
    TOKEN_OR = 300,                /* TOKEN_OR  */
    TOKEN_AND = 301,               /* TOKEN_AND  */
    TOKEN_IMPLICATION = 302,       /* TOKEN_IMPLICATION  */
    TOKEN_EQUIV = 303,             /* TOKEN_EQUIV  */
    TOKEN_PLUS = 304,              /* TOKEN_PLUS  */
    TOKEN_MINUS = 305,             /* TOKEN_MINUS  */
    TOKEN_TIMES = 306,             /* TOKEN_TIMES  */
    TOKEN_DIVIDE = 307,            /* TOKEN_DIVIDE  */
    TOKEN_MODULO = 308,            /* TOKEN_MODULO  */
    TOKEN_EQUAL = 309,             /* TOKEN_EQUAL  */
    TOKEN_DIFF = 310,              /* TOKEN_DIFF  */
    TOKEN_LT = 311,                /* TOKEN_LT  */
    TOKEN_LE = 312,                /* TOKEN_LE  */
    TOKEN_GT = 313,                /* TOKEN_GT  */
    TOKEN_GE = 314,                /* TOKEN_GE  */
    TOKEN_IDENTIFIER = 315,        /* TOKEN_IDENTIFIER  */
    TOKEN_STRING = 316,            /* TOKEN_STRING  */
    TOKEN_INTEGER = 317,           /* TOKEN_INTEGER  */
    TOKEN_DOUBLE = 318,            /* TOKEN_DOUBLE  */
    TOKEN_VARIABLE = 319,          /* TOKEN_VARIABLE  */
    TOKEN_ANONYMOUS = 320,         /* TOKEN_ANONYMOUS  */
    TOKEN_MINUS_U = 321,           /* TOKEN_MINUS_U  */
    TOKEN_NOELSE = 322             /* TOKEN_NOELSE  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 69 "src/rulesyacc.y"

  unsigned int integer_slot;
  double double_slot;
  termsPtr* terms_slot; //(A|B)
  std::vector< termsPtr  >* vector_terms_slot; // X Y
  std::string* string_slot;
  entryPtr* entry_slot;
  entriesPtr* entries_slot;
  bitsetPtr* bits_slot;
  valuePtr* value_slot;
  featurePtr* feature_slot;
  featuresPtr* features_slot;
  listPtr* list_slot;
  statementPtr* statement_slot;
  statementsPtr* statements_slot;
  std::list<  bitsetPtr >* list_args;
 

#line 150 "/Users/clement/workspace/Elvex/src/rulesyacc.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE ruleslval;


int rulesparse (void);


#endif /* !YY_RULES_USERS_CLEMENT_WORKSPACE_ELVEX_SRC_RULESYACC_HPP_INCLUDED  */
