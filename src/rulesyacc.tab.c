/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "rulesyacc.y"


/* **************************************************
 *
 * ELVEX
 *
 * Copyright 2014-2022 LABRI,
 * CNRS (UMR 5800), the University of Bordeaux,
 * and the Bordeaux INP
 *
 * Author:
 * Lionel Clément
 * LaBRI -- Université Bordeaux
 * 351, cours de la Libération
 * 33405 Talence Cedex - France
 * lionel.clement@u-bordeaux.fr
 *
 * This file is part of ELVEX.
 *
 ************************************************** */

#include <sstream>
#include "vartable.hpp"
#include "terms.hpp"
#include "entry.hpp"
#include "entries.hpp"
#include "parser.hpp"
#include "bitset.hpp"
#include "value.hpp"
#include "feature.hpp"
#include "features.hpp"
#include "pairp.hpp"
#include "statements.hpp"
#include "statement.hpp"
#include "terms.hpp"
#include "messages.hpp"
#include "rule.hpp"
#include "shared_ptr.hpp"
#include "parser_exception.hpp"

#ifndef DEBUGYACC
#define DEBUGYACC(x)
#else
#define DEBUGYACC(x) x
#endif

#define DBUGPRT(x) DEBUGYACC({std::cerr << "*** " << x << std::endl;})
#define DBUGPRTARG(x, s) DEBUGYACC({std::cerr << "*** " << x << ' ' << s << std::endl});
  
 extern unsigned int ruleslineno;
 extern unsigned int ruleslex();
 extern Parser parser;
 unsigned int headLineno;
 bool headTrace;

  void ruleserror(const char* str) {
      std::ostringstream oss;
      oss << str << " in " << parser.getTopBufferName() << " (line " << ruleslineno << ")";
      throw parser_exception(oss);
  }

  void yywarning(const char* str){
      std::ostringstream oss;
      oss << "warning: " << str << " " << parser.getTopBufferName() << " (" << ruleslineno << ")" << std::endl;
      std::cerr << oss.str() << std::endl;
  }

  

#line 141 "rulesyacc.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif


/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
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
    TOKEN_WAIT = 287,              /* TOKEN_WAIT  */
    TOKEN_NIL = 288,               /* TOKEN_NIL  */
    TOKEN_TRUE = 289,              /* TOKEN_TRUE  */
    TOKEN_FALSE = 290,             /* TOKEN_FALSE  */
    TOKEN_FOREACH = 291,           /* TOKEN_FOREACH  */
    TOKEN_IN = 292,                /* TOKEN_IN  */
    TOKEN_SEARCH = 293,            /* TOKEN_SEARCH  */
    TOKEN_ON = 294,                /* TOKEN_ON  */
    TOKEN_RAND = 295,              /* TOKEN_RAND  */
    TOKEN_TRACE = 296,             /* TOKEN_TRACE  */
    TOKEN_UNION = 297,             /* TOKEN_UNION  */
    TOKEN_SUBSUME = 298,           /* TOKEN_SUBSUME  */
    TOKEN_AFF = 299,               /* TOKEN_AFF  */
    TOKEN_PIPE = 300,              /* TOKEN_PIPE  */
    TOKEN_NOT = 301,               /* TOKEN_NOT  */
    TOKEN_OR = 302,                /* TOKEN_OR  */
    TOKEN_AND = 303,               /* TOKEN_AND  */
    TOKEN_IMPLICATION = 304,       /* TOKEN_IMPLICATION  */
    TOKEN_EQUIV = 305,             /* TOKEN_EQUIV  */
    TOKEN_PLUS = 306,              /* TOKEN_PLUS  */
    TOKEN_MINUS = 307,             /* TOKEN_MINUS  */
    TOKEN_TIMES = 308,             /* TOKEN_TIMES  */
    TOKEN_DIVIDE = 309,            /* TOKEN_DIVIDE  */
    TOKEN_MODULO = 310,            /* TOKEN_MODULO  */
    TOKEN_EQUAL = 311,             /* TOKEN_EQUAL  */
    TOKEN_DIFF = 312,              /* TOKEN_DIFF  */
    TOKEN_LT = 313,                /* TOKEN_LT  */
    TOKEN_LE = 314,                /* TOKEN_LE  */
    TOKEN_GT = 315,                /* TOKEN_GT  */
    TOKEN_GE = 316,                /* TOKEN_GE  */
    TOKEN_IDENTIFIER = 317,        /* TOKEN_IDENTIFIER  */
    TOKEN_STRING = 318,            /* TOKEN_STRING  */
    TOKEN_INTEGER = 319,           /* TOKEN_INTEGER  */
    TOKEN_DOUBLE = 320,            /* TOKEN_DOUBLE  */
    TOKEN_VARIABLE = 321,          /* TOKEN_VARIABLE  */
    TOKEN_ANONYMOUS = 322,         /* TOKEN_ANONYMOUS  */
    TOKEN_MINUS_U = 323,           /* TOKEN_MINUS_U  */
    TOKEN_NOELSE = 324             /* TOKEN_NOELSE  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 70 "rulesyacc.y"

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
  pairpPtr* pairp_slot;
  statementPtr* statement_slot;
  statementsPtr* statements_slot;

  std::list<  bitsetPtr >* list_args;
 

#line 277 "rulesyacc.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);



/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_TOKEN_RIGHTARROW = 3,           /* TOKEN_RIGHTARROW  */
  YYSYMBOL_TOKEN_UPARROW = 4,              /* TOKEN_UPARROW  */
  YYSYMBOL_TOKEN_UP2ARROW = 5,             /* TOKEN_UP2ARROW  */
  YYSYMBOL_TOKEN_DOWNARROW = 6,            /* TOKEN_DOWNARROW  */
  YYSYMBOL_TOKEN_DOWN2ARROW = 7,           /* TOKEN_DOWN2ARROW  */
  YYSYMBOL_TOKEN_LPAR = 8,                 /* TOKEN_LPAR  */
  YYSYMBOL_TOKEN_RPAR = 9,                 /* TOKEN_RPAR  */
  YYSYMBOL_TOKEN_LBRACE = 10,              /* TOKEN_LBRACE  */
  YYSYMBOL_TOKEN_RBRACE = 11,              /* TOKEN_RBRACE  */
  YYSYMBOL_TOKEN_LBRACKET = 12,            /* TOKEN_LBRACKET  */
  YYSYMBOL_TOKEN_RBRACKET = 13,            /* TOKEN_RBRACKET  */
  YYSYMBOL_TOKEN_DASH = 14,                /* TOKEN_DASH  */
  YYSYMBOL_TOKEN_AROBASE = 15,             /* TOKEN_AROBASE  */
  YYSYMBOL_TOKEN_SEMI = 16,                /* TOKEN_SEMI  */
  YYSYMBOL_TOKEN_DOT = 17,                 /* TOKEN_DOT  */
  YYSYMBOL_TOKEN_COLON = 18,               /* TOKEN_COLON  */
  YYSYMBOL_TOKEN_DOUBLECOLON = 19,         /* TOKEN_DOUBLECOLON  */
  YYSYMBOL_TOKEN_COMMA = 20,               /* TOKEN_COMMA  */
  YYSYMBOL_TOKEN_RULES = 21,               /* TOKEN_RULES  */
  YYSYMBOL_TOKEN_INPUT = 22,               /* TOKEN_INPUT  */
  YYSYMBOL_TOKEN_LEXICON = 23,             /* TOKEN_LEXICON  */
  YYSYMBOL_TOKEN_LEMMA = 24,               /* TOKEN_LEMMA  */
  YYSYMBOL_TOKEN_PRED = 25,                /* TOKEN_PRED  */
  YYSYMBOL_TOKEN_FORM = 26,                /* TOKEN_FORM  */
  YYSYMBOL_TOKEN_ATTEST = 27,              /* TOKEN_ATTEST  */
  YYSYMBOL_TOKEN_PRINT = 28,               /* TOKEN_PRINT  */
  YYSYMBOL_TOKEN_PRINTLN = 29,             /* TOKEN_PRINTLN  */
  YYSYMBOL_TOKEN_IF = 30,                  /* TOKEN_IF  */
  YYSYMBOL_TOKEN_ELSE = 31,                /* TOKEN_ELSE  */
  YYSYMBOL_TOKEN_WAIT = 32,                /* TOKEN_WAIT  */
  YYSYMBOL_TOKEN_NIL = 33,                 /* TOKEN_NIL  */
  YYSYMBOL_TOKEN_TRUE = 34,                /* TOKEN_TRUE  */
  YYSYMBOL_TOKEN_FALSE = 35,               /* TOKEN_FALSE  */
  YYSYMBOL_TOKEN_FOREACH = 36,             /* TOKEN_FOREACH  */
  YYSYMBOL_TOKEN_IN = 37,                  /* TOKEN_IN  */
  YYSYMBOL_TOKEN_SEARCH = 38,              /* TOKEN_SEARCH  */
  YYSYMBOL_TOKEN_ON = 39,                  /* TOKEN_ON  */
  YYSYMBOL_TOKEN_RAND = 40,                /* TOKEN_RAND  */
  YYSYMBOL_TOKEN_TRACE = 41,               /* TOKEN_TRACE  */
  YYSYMBOL_TOKEN_UNION = 42,               /* TOKEN_UNION  */
  YYSYMBOL_TOKEN_SUBSUME = 43,             /* TOKEN_SUBSUME  */
  YYSYMBOL_TOKEN_AFF = 44,                 /* TOKEN_AFF  */
  YYSYMBOL_TOKEN_PIPE = 45,                /* TOKEN_PIPE  */
  YYSYMBOL_TOKEN_NOT = 46,                 /* TOKEN_NOT  */
  YYSYMBOL_TOKEN_OR = 47,                  /* TOKEN_OR  */
  YYSYMBOL_TOKEN_AND = 48,                 /* TOKEN_AND  */
  YYSYMBOL_TOKEN_IMPLICATION = 49,         /* TOKEN_IMPLICATION  */
  YYSYMBOL_TOKEN_EQUIV = 50,               /* TOKEN_EQUIV  */
  YYSYMBOL_TOKEN_PLUS = 51,                /* TOKEN_PLUS  */
  YYSYMBOL_TOKEN_MINUS = 52,               /* TOKEN_MINUS  */
  YYSYMBOL_TOKEN_TIMES = 53,               /* TOKEN_TIMES  */
  YYSYMBOL_TOKEN_DIVIDE = 54,              /* TOKEN_DIVIDE  */
  YYSYMBOL_TOKEN_MODULO = 55,              /* TOKEN_MODULO  */
  YYSYMBOL_TOKEN_EQUAL = 56,               /* TOKEN_EQUAL  */
  YYSYMBOL_TOKEN_DIFF = 57,                /* TOKEN_DIFF  */
  YYSYMBOL_TOKEN_LT = 58,                  /* TOKEN_LT  */
  YYSYMBOL_TOKEN_LE = 59,                  /* TOKEN_LE  */
  YYSYMBOL_TOKEN_GT = 60,                  /* TOKEN_GT  */
  YYSYMBOL_TOKEN_GE = 61,                  /* TOKEN_GE  */
  YYSYMBOL_TOKEN_IDENTIFIER = 62,          /* TOKEN_IDENTIFIER  */
  YYSYMBOL_TOKEN_STRING = 63,              /* TOKEN_STRING  */
  YYSYMBOL_TOKEN_INTEGER = 64,             /* TOKEN_INTEGER  */
  YYSYMBOL_TOKEN_DOUBLE = 65,              /* TOKEN_DOUBLE  */
  YYSYMBOL_TOKEN_VARIABLE = 66,            /* TOKEN_VARIABLE  */
  YYSYMBOL_TOKEN_ANONYMOUS = 67,           /* TOKEN_ANONYMOUS  */
  YYSYMBOL_TOKEN_MINUS_U = 68,             /* TOKEN_MINUS_U  */
  YYSYMBOL_TOKEN_NOELSE = 69,              /* TOKEN_NOELSE  */
  YYSYMBOL_YYACCEPT = 70,                  /* $accept  */
  YYSYMBOL_axiom = 71,                     /* axiom  */
  YYSYMBOL_begin = 72,                     /* begin  */
  YYSYMBOL_dictionary = 73,                /* dictionary  */
  YYSYMBOL_dictionary_line = 74,           /* dictionary_line  */
  YYSYMBOL_stringOrIdentifier = 75,        /* stringOrIdentifier  */
  YYSYMBOL_lexical_entries = 76,           /* lexical_entries  */
  YYSYMBOL_lexical_entry = 77,             /* lexical_entry  */
  YYSYMBOL_rules = 78,                     /* rules  */
  YYSYMBOL_79_1 = 79,                      /* $@1  */
  YYSYMBOL_80_2 = 80,                      /* $@2  */
  YYSYMBOL_pref_rule = 81,                 /* pref_rule  */
  YYSYMBOL_rule = 82,                      /* rule  */
  YYSYMBOL_terms_vector = 83,              /* terms_vector  */
  YYSYMBOL_terms = 84,                     /* terms  */
  YYSYMBOL_terms_disj = 85,                /* terms_disj  */
  YYSYMBOL_term = 86,                      /* term  */
  YYSYMBOL_structure_statement = 87,       /* structure_statement  */
  YYSYMBOL_list_statement = 88,            /* list_statement  */
  YYSYMBOL_statements = 89,                /* statements  */
  YYSYMBOL_statement = 90,                 /* statement  */
  YYSYMBOL_left_hand_side_subset_statement = 91, /* left_hand_side_subset_statement  */
  YYSYMBOL_right_hand_side_subset_statement = 92, /* right_hand_side_subset_statement  */
  YYSYMBOL_left_hand_side_aff_statement = 93, /* left_hand_side_aff_statement  */
  YYSYMBOL_right_hand_side_aff_statement = 94, /* right_hand_side_aff_statement  */
  YYSYMBOL_expression_statement = 95,      /* expression_statement  */
  YYSYMBOL_expression_statement_composite = 96, /* expression_statement_composite  */
  YYSYMBOL_up = 97,                        /* up  */
  YYSYMBOL_up2 = 98,                       /* up2  */
  YYSYMBOL_down = 99,                      /* down  */
  YYSYMBOL_down2 = 100,                    /* down2  */
  YYSYMBOL_dash_statement = 101,           /* dash_statement  */
  YYSYMBOL_features = 102,                 /* features  */
  YYSYMBOL_features_composite_tail = 103,  /* features_composite_tail  */
  YYSYMBOL_features_composite = 104,       /* features_composite  */
  YYSYMBOL_feature = 105,                  /* feature  */
  YYSYMBOL_feature_value = 106,            /* feature_value  */
  YYSYMBOL_constant = 107,                 /* constant  */
  YYSYMBOL_identifier = 108,               /* identifier  */
  YYSYMBOL_variable = 109,                 /* variable  */
  YYSYMBOL_pairp = 110,                    /* pairp  */
  YYSYMBOL_pairp_elements = 111,           /* pairp_elements  */
  YYSYMBOL_pairp_element = 112             /* pairp_element  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  11
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   668

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  70
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  43
/* YYNRULES -- Number of rules.  */
#define YYNRULES  150
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  273

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   324


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   164,   164,   170,   174,   182,   188,   194,   202,   206,
     212,   237,   264,   292,   300,   306,   311,   316,   323,   331,
     339,   348,   359,   359,   364,   364,   370,   376,   382,   397,
     412,   418,   425,   430,   437,   444,   451,   458,   465,   474,
     480,   485,   491,   499,   507,   514,   521,   526,   532,   538,
     549,   560,   623,   640,   652,   665,   677,   691,   698,   704,
     709,   714,   722,   727,   732,   738,   749,   758,   765,   772,
     779,   792,   798,   805,   812,   819,   826,   833,   843,   851,
     859,   867,   875,   883,   890,   896,   902,   908,   917,   924,
     929,   934,   939,   944,   953,   959,   968,   974,   980,   988,
     996,  1005,  1019,  1027,  1037,  1043,  1049,  1056,  1063,  1069,
    1079,  1089,  1097,  1101,  1107,  1115,  1124,  1139,  1155,  1162,
    1169,  1176,  1184,  1191,  1197,  1205,  1212,  1222,  1229,  1236,
    1242,  1248,  1255,  1262,  1268,  1275,  1281,  1289,  1297,  1308,
    1314,  1320,  1331,  1344,  1352,  1360,  1367,  1373,  1379,  1386,
    1393
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "TOKEN_RIGHTARROW",
  "TOKEN_UPARROW", "TOKEN_UP2ARROW", "TOKEN_DOWNARROW", "TOKEN_DOWN2ARROW",
  "TOKEN_LPAR", "TOKEN_RPAR", "TOKEN_LBRACE", "TOKEN_RBRACE",
  "TOKEN_LBRACKET", "TOKEN_RBRACKET", "TOKEN_DASH", "TOKEN_AROBASE",
  "TOKEN_SEMI", "TOKEN_DOT", "TOKEN_COLON", "TOKEN_DOUBLECOLON",
  "TOKEN_COMMA", "TOKEN_RULES", "TOKEN_INPUT", "TOKEN_LEXICON",
  "TOKEN_LEMMA", "TOKEN_PRED", "TOKEN_FORM", "TOKEN_ATTEST", "TOKEN_PRINT",
  "TOKEN_PRINTLN", "TOKEN_IF", "TOKEN_ELSE", "TOKEN_WAIT", "TOKEN_NIL",
  "TOKEN_TRUE", "TOKEN_FALSE", "TOKEN_FOREACH", "TOKEN_IN", "TOKEN_SEARCH",
  "TOKEN_ON", "TOKEN_RAND", "TOKEN_TRACE", "TOKEN_UNION", "TOKEN_SUBSUME",
  "TOKEN_AFF", "TOKEN_PIPE", "TOKEN_NOT", "TOKEN_OR", "TOKEN_AND",
  "TOKEN_IMPLICATION", "TOKEN_EQUIV", "TOKEN_PLUS", "TOKEN_MINUS",
  "TOKEN_TIMES", "TOKEN_DIVIDE", "TOKEN_MODULO", "TOKEN_EQUAL",
  "TOKEN_DIFF", "TOKEN_LT", "TOKEN_LE", "TOKEN_GT", "TOKEN_GE",
  "TOKEN_IDENTIFIER", "TOKEN_STRING", "TOKEN_INTEGER", "TOKEN_DOUBLE",
  "TOKEN_VARIABLE", "TOKEN_ANONYMOUS", "TOKEN_MINUS_U", "TOKEN_NOELSE",
  "$accept", "axiom", "begin", "dictionary", "dictionary_line",
  "stringOrIdentifier", "lexical_entries", "lexical_entry", "rules", "$@1",
  "$@2", "pref_rule", "rule", "terms_vector", "terms", "terms_disj",
  "term", "structure_statement", "list_statement", "statements",
  "statement", "left_hand_side_subset_statement",
  "right_hand_side_subset_statement", "left_hand_side_aff_statement",
  "right_hand_side_aff_statement", "expression_statement",
  "expression_statement_composite", "up", "up2", "down", "down2",
  "dash_statement", "features", "features_composite_tail",
  "features_composite", "feature", "feature_value", "constant",
  "identifier", "variable", "pairp", "pairp_elements", "pairp_element", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-135)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-25)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       8,     4,    26,    35,    50,    14,  -135,    12,    51,     3,
      46,  -135,   384,    55,    59,    53,  -135,  -135,  -135,  -135,
      61,    40,  -135,    49,  -135,  -135,    67,    46,   -44,  -135,
      56,    96,    99,   108,  -135,  -135,   113,  -135,   116,   117,
    -135,  -135,  -135,     3,    51,  -135,   128,   120,    28,  -135,
    -135,    76,    12,   124,    97,  -135,    34,    34,    34,   273,
     132,   373,   172,   144,  -135,  -135,    12,  -135,   134,  -135,
    -135,  -135,   103,   118,  -135,   118,  -135,   118,  -135,   110,
    -135,   117,  -135,  -135,   313,  -135,  -135,  -135,  -135,  -135,
    -135,  -135,   129,  -135,  -135,  -135,     5,   160,  -135,  -135,
    -135,  -135,  -135,  -135,  -135,  -135,  -135,  -135,     6,   162,
     121,   280,     3,  -135,     5,  -135,   140,  -135,  -135,  -135,
     383,  -135,   115,  -135,  -135,   125,   290,  -135,   154,   180,
     182,   183,   185,   130,   130,   322,  -135,  -135,   152,   155,
    -135,  -135,   186,  -135,    -3,  -135,  -135,     3,   138,   141,
    -135,  -135,  -135,   354,  -135,   139,   154,   146,  -135,   154,
     196,   154,   154,  -135,  -135,  -135,  -135,   482,  -135,  -135,
    -135,  -135,  -135,  -135,  -135,  -135,  -135,   154,   154,   154,
     154,   171,   192,  -135,  -135,    91,   154,  -135,  -135,  -135,
    -135,  -135,  -135,  -135,   409,   197,   505,   206,   585,  -135,
    -135,   154,   154,   154,   154,   154,   154,   154,   154,   154,
     154,   154,   154,   154,   154,   154,   154,   525,     0,     7,
     433,   462,   154,   130,   207,  -135,  -135,  -135,  -135,   209,
     525,  -135,   163,   164,  -135,   596,   565,   585,   545,   545,
      52,    52,   176,   176,  -135,   607,   607,   607,   607,   607,
     607,   216,   154,   224,   364,   364,   223,   181,  -135,  -135,
    -135,  -135,  -135,   525,  -135,   211,  -135,   154,  -135,  -135,
     364,   192,  -135
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     2,     0,    22,     0,
       0,     1,     0,     0,     0,    27,    25,    38,    36,    37,
       0,     0,    14,     0,    15,    16,     0,     9,     0,   111,
       0,     0,     0,     0,   137,   138,   112,   115,     0,     0,
       7,     3,    26,     0,    22,     5,     0,     0,     0,     6,
       8,     0,    21,     0,    19,   117,     0,     0,     0,     0,
       0,     0,     0,     0,    23,     4,     0,    10,     0,    17,
      20,    12,     0,   118,   119,   120,   121,   123,   122,     0,
     114,   113,   110,   133,     0,   125,   130,   129,   134,   132,
     124,   128,   135,   127,   131,   126,     0,     0,    11,    18,
     116,   140,   147,   146,   149,   148,   145,   150,     0,   144,
       0,     0,     0,    41,     0,    31,    32,    35,    29,    13,
       0,   139,     0,   136,   105,     0,     0,    40,     0,     0,
       0,     0,     0,     0,     0,     0,    46,    42,     0,     0,
      62,    63,    57,    64,     0,    30,    28,     0,     0,     0,
     143,   106,    45,     0,   104,     0,     0,     0,    94,     0,
       0,     0,     0,    87,    86,    85,    96,     0,    89,    90,
      91,    92,    99,    93,    95,    97,   100,     0,     0,     0,
       0,     0,     0,    39,    43,     0,     0,    47,    33,    34,
     142,   141,    44,   107,     0,   109,     0,     0,    71,    83,
      48,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   103,     0,     0,
       0,     0,     0,     0,     0,    59,    60,    61,    58,     0,
      66,    98,     0,     0,    84,    88,    67,    68,    69,    70,
      78,    79,    80,    81,    82,    72,    73,    74,    75,    76,
      77,     0,     0,     0,     0,     0,     0,     0,    52,    51,
     108,   101,    49,   102,    50,    53,    55,     0,    56,    65,
       0,    97,    54
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -135,  -135,  -135,   227,  -135,    74,   184,  -135,   199,  -135,
    -135,  -135,  -135,  -135,   147,   150,    -6,   153,   142,  -135,
    -134,  -135,  -135,  -135,  -135,  -123,    80,    79,  -103,  -100,
      81,  -135,    -7,  -135,  -135,   210,   225,    87,    16,   -10,
     102,   189,   173
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     5,     6,    26,    27,    28,    53,    54,    14,    15,
      16,    43,    44,   114,   115,   116,   117,   118,   135,   136,
     137,   138,   224,   139,   229,   217,   218,   168,   169,   170,
     171,   172,   173,    60,    36,    37,    90,   174,    92,   175,
     176,   108,   109
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      13,   184,    39,    20,    17,   167,    17,    51,   140,   251,
     188,   141,     7,    46,    11,   111,   253,   112,    52,   184,
     252,   113,     1,   140,    12,   120,   141,   252,    38,     2,
       3,     4,   140,   194,     8,   141,   196,    63,   198,   199,
      12,    68,   147,     9,    67,    70,    74,    76,    78,    81,
     140,    93,    93,   141,    89,    89,   220,   221,    10,    97,
     -24,    21,    22,   230,    40,    18,   121,    18,    41,    19,
      45,    19,    23,    12,   106,    38,    49,   104,   235,   236,
     237,   238,   239,   240,   241,   242,   243,   244,   245,   246,
     247,   248,   249,   250,    42,   154,    24,    25,   155,   256,
      35,   143,    47,    12,   142,   208,   209,   210,    24,    25,
     106,    48,   106,   104,    56,   104,   143,    57,    55,   142,
     265,   266,   268,   181,   182,   143,    58,    12,   142,   263,
      73,    75,    77,    59,    61,    62,   272,    65,    66,    69,
      71,   189,    72,   143,   247,    82,   142,    96,    91,    91,
      98,   140,   140,   140,   141,   141,   141,    35,   154,   124,
     125,   155,   156,    94,    94,    52,    12,   140,   157,    51,
     141,   105,   100,    84,   110,   228,   119,    34,   227,   102,
     103,    35,   122,    34,    12,   147,   107,   158,   177,   151,
     178,   179,   159,   180,   160,   185,    35,   123,   190,   186,
     161,   191,   187,   193,   197,    83,   162,   105,   222,   105,
     195,   223,    84,   257,   232,   234,    34,   163,   164,   165,
      35,   166,   107,   258,   107,   259,   261,   260,   124,   125,
      84,   210,   262,   126,    34,    12,    86,    87,    35,    88,
     264,   269,   270,    64,   143,   143,   143,   142,   142,   142,
     128,   129,   130,   131,    50,   132,    99,   271,   219,   133,
     143,   145,   144,   142,   225,   201,   226,   146,   153,    80,
     202,   203,   204,   205,   206,   207,   208,   209,   210,   211,
     212,   267,   214,   215,   216,   124,   125,    95,    79,    35,
     126,   127,    12,   149,     0,   124,   125,    31,    32,    33,
     126,   152,    12,     0,     0,     0,     0,   128,   129,   130,
     131,   150,   132,     0,     0,     0,   133,   128,   129,   130,
     131,     0,   132,     0,     0,    12,   133,   124,   125,     0,
       0,     0,   126,   183,    12,    34,     0,     0,   134,    35,
       0,     0,     0,     0,     0,     0,    35,     0,   134,   128,
     129,   130,   131,     0,   132,     0,    35,     0,   133,   124,
     125,     0,     0,     0,   126,   192,    12,     0,     0,   124,
     125,    84,     0,   101,   126,    34,    12,   102,   103,    35,
     134,   128,   129,   130,   131,    12,   132,     0,    35,     0,
     133,   128,   129,   130,   131,    12,   132,    29,     0,    30,
     133,     0,     0,     0,     0,     0,    83,     0,    31,    32,
      33,     0,   134,     0,     0,     0,   148,     0,   231,     0,
      35,     0,   134,     0,     0,     0,     0,     0,     0,     0,
      35,    84,     0,     0,     0,    34,    85,    86,    87,    35,
      88,    84,   254,     0,     0,    34,    34,   102,   103,    35,
      35,   201,     0,     0,     0,     0,   202,   203,   204,   205,
     206,   207,   208,   209,   210,   211,   212,   213,   214,   215,
     216,   255,     0,     0,     0,   201,     0,     0,     0,     0,
     202,   203,   204,   205,   206,   207,   208,   209,   210,   211,
     212,   213,   214,   215,   216,     0,     0,     0,   200,     0,
       0,     0,     0,     0,   201,     0,     0,     0,     0,   202,
     203,   204,   205,   206,   207,   208,   209,   210,   211,   212,
     213,   214,   215,   216,   201,     0,     0,     0,     0,   202,
     203,   204,   205,   206,   207,   208,   209,   210,   211,   212,
     213,   214,   215,   216,   233,     0,     0,   201,     0,     0,
       0,     0,   202,   203,   204,   205,   206,   207,   208,   209,
     210,   211,   212,   213,   214,   215,   216,   201,     0,     0,
       0,     0,   202,   203,   204,   205,   206,   207,   208,   209,
     210,   211,   212,   213,   214,   215,   216,   201,     0,     0,
       0,     0,   202,   203,   -25,   -25,   206,   207,   208,   209,
     210,   211,   212,   213,   214,   215,   216,   201,     0,     0,
       0,     0,     0,   203,     0,     0,   206,   207,   208,   209,
     210,   211,   212,   213,   214,   215,   216,   201,     0,     0,
       0,     0,     0,     0,     0,     0,   206,   207,   208,   209,
     210,   211,   212,   213,   214,   215,   216,   206,   207,   208,
     209,   210,   211,   212,   213,   214,   215,   216,   206,   207,
     208,   209,   210,   -25,   -25,   -25,   -25,   -25,   -25
};

static const yytype_int16 yycheck[] =
{
       7,   135,    12,     9,     1,   128,     1,    51,   111,     9,
      13,   111,     8,    20,     0,    10,     9,    12,    62,   153,
      20,    16,    14,   126,    12,    19,   126,    20,    12,    21,
      22,    23,   135,   156,     8,   135,   159,    43,   161,   162,
      12,    48,    45,     8,    16,    52,    56,    57,    58,    59,
     153,    61,    62,   153,    61,    62,   179,   180,     8,    66,
       9,    15,    16,   186,     9,    62,    60,    62,     9,    66,
       9,    66,    26,    12,    84,    59,     9,    84,   201,   202,
     203,   204,   205,   206,   207,   208,   209,   210,   211,   212,
     213,   214,   215,   216,    41,     4,    62,    63,     7,   222,
      66,   111,    62,    12,   111,    53,    54,    55,    62,    63,
     120,    62,   122,   120,    18,   122,   126,    18,    62,   126,
     254,   255,   256,   133,   134,   135,    18,    12,   135,   252,
      56,    57,    58,    20,    18,    18,   270,     9,    18,    63,
      16,   147,    45,   153,   267,    13,   153,     3,    61,    62,
      16,   254,   255,   256,   254,   255,   256,    66,     4,     5,
       6,     7,     8,    61,    62,    62,    12,   270,    14,    51,
     270,    84,    62,    58,    45,   185,    16,    62,   185,    64,
      65,    66,    20,    62,    12,    45,    84,    33,     8,    64,
       8,     8,    38,     8,    40,    43,    66,   110,    60,    44,
      46,    60,    16,    64,     8,    33,    52,   120,    37,   122,
      64,    19,    58,   223,    17,     9,    62,    63,    64,    65,
      66,    67,   120,    16,   122,    16,    62,    64,     5,     6,
      58,    55,    16,    10,    62,    12,    64,    65,    66,    67,
      16,    60,    31,    44,   254,   255,   256,   254,   255,   256,
      27,    28,    29,    30,    27,    32,    72,   267,   178,    36,
     270,   114,   112,   270,   185,    42,   185,   114,   126,    59,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,     5,     6,    62,    15,    66,
      10,    11,    12,   120,    -1,     5,     6,    24,    25,    26,
      10,    11,    12,    -1,    -1,    -1,    -1,    27,    28,    29,
      30,   122,    32,    -1,    -1,    -1,    36,    27,    28,    29,
      30,    -1,    32,    -1,    -1,    12,    36,     5,     6,    -1,
      -1,    -1,    10,    11,    12,    62,    -1,    -1,    58,    66,
      -1,    -1,    -1,    -1,    -1,    -1,    66,    -1,    58,    27,
      28,    29,    30,    -1,    32,    -1,    66,    -1,    36,     5,
       6,    -1,    -1,    -1,    10,    11,    12,    -1,    -1,     5,
       6,    58,    -1,    60,    10,    62,    12,    64,    65,    66,
      58,    27,    28,    29,    30,    12,    32,    -1,    66,    -1,
      36,    27,    28,    29,    30,    12,    32,    13,    -1,    15,
      36,    -1,    -1,    -1,    -1,    -1,    33,    -1,    24,    25,
      26,    -1,    58,    -1,    -1,    -1,    33,    -1,     9,    -1,
      66,    -1,    58,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      66,    58,    -1,    -1,    -1,    62,    63,    64,    65,    66,
      67,    58,     9,    -1,    -1,    62,    62,    64,    65,    66,
      66,    42,    -1,    -1,    -1,    -1,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,     9,    -1,    -1,    -1,    42,    -1,    -1,    -1,    -1,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    -1,    -1,    -1,    16,    -1,
      -1,    -1,    -1,    -1,    42,    -1,    -1,    -1,    -1,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    42,    -1,    -1,    -1,    -1,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    39,    -1,    -1,    42,    -1,    -1,
      -1,    -1,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    42,    -1,    -1,
      -1,    -1,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    42,    -1,    -1,
      -1,    -1,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    42,    -1,    -1,
      -1,    -1,    -1,    48,    -1,    -1,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    42,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    14,    21,    22,    23,    71,    72,     8,     8,     8,
       8,     0,    12,   102,    78,    79,    80,     1,    62,    66,
      86,    15,    16,    26,    62,    63,    73,    74,    75,    13,
      15,    24,    25,    26,    62,    66,   104,   105,   108,   109,
       9,     9,    41,    81,    82,     9,   102,    62,    62,     9,
      73,    51,    62,    76,    77,    62,    18,    18,    18,    20,
     103,    18,    18,    86,    78,     9,    18,    16,   102,    63,
     102,    16,    45,    75,   109,    75,   109,    75,   109,    15,
     105,   109,    13,    33,    58,    63,    64,    65,    67,   102,
     106,   107,   108,   109,   110,   106,     3,   102,    16,    76,
      62,    60,    64,    65,   102,   107,   109,   110,   111,   112,
      45,    10,    12,    16,    83,    84,    85,    86,    87,    16,
      19,    60,    20,   107,     5,     6,    10,    11,    27,    28,
      29,    30,    32,    36,    58,    88,    89,    90,    91,    93,
      98,    99,   102,   109,    85,    84,    87,    45,    33,   112,
     111,    64,    11,    88,     4,     7,     8,    14,    33,    38,
      40,    46,    52,    63,    64,    65,    67,    95,    97,    98,
      99,   100,   101,   102,   107,   109,   110,     8,     8,     8,
       8,   109,   109,    11,    90,    43,    44,    16,    13,    86,
      60,    60,    11,    64,    95,    64,    95,     8,    95,    95,
      16,    42,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    95,    96,    96,
      95,    95,    37,    19,    92,    97,   100,   102,   109,    94,
      95,     9,    17,    39,     9,    95,    95,    95,    95,    95,
      95,    95,    95,    95,    95,    95,    95,    95,    95,    95,
      95,     9,    20,     9,     9,     9,    95,   109,    16,    16,
      64,    62,    16,    95,    16,    90,    90,    58,    90,    60,
      31,   109,    90
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    70,    71,    72,    72,    72,    72,    72,    73,    73,
      74,    74,    74,    74,    74,    75,    75,    75,    76,    76,
      77,    77,    79,    78,    80,    78,    81,    81,    82,    82,
      83,    83,    84,    84,    85,    85,    86,    86,    86,    87,
      87,    87,    88,    88,    89,    89,    90,    90,    90,    90,
      90,    90,    90,    90,    90,    90,    90,    91,    92,    92,
      92,    92,    93,    93,    93,    93,    94,    95,    95,    95,
      95,    95,    95,    95,    95,    95,    95,    95,    95,    95,
      95,    95,    95,    95,    95,    95,    95,    95,    95,    95,
      95,    95,    95,    95,    95,    95,    95,    95,    95,    95,
      95,    95,    96,    96,    97,    98,    99,   100,   101,   101,
     102,   102,   103,   103,   104,   104,   104,   104,   105,   105,
     105,   105,   105,   105,   105,   105,   105,   106,   106,   106,
     106,   106,   106,   106,   106,   107,   107,   108,   109,   110,
     110,   110,   110,   111,   111,   112,   112,   112,   112,   112,
     112
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     4,     5,     4,     4,     4,     2,     1,
       3,     4,     3,     5,     1,     1,     1,     3,     3,     1,
       2,     1,     0,     3,     0,     1,     1,     0,     5,     4,
       2,     1,     1,     3,     3,     1,     1,     1,     1,     3,
       2,     1,     1,     2,     3,     2,     1,     2,     3,     5,
       5,     4,     4,     5,     7,     5,     5,     1,     1,     1,
       1,     1,     1,     1,     1,     5,     1,     3,     3,     3,
       3,     2,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     2,     3,     1,     1,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     1,
       1,     4,     3,     1,     1,     1,     2,     2,     4,     2,
       4,     2,     0,     2,     3,     1,     4,     2,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     1,     1,     3,
       2,     5,     5,     3,     1,     1,     1,     1,     1,     1,
       1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* axiom: begin  */
#line 164 "rulesyacc.y"
              {
	  DBUGPRT("axiom done...");
	  YYACCEPT;
	}
#line 1655 "rulesyacc.tab.c"
    break;

  case 3: /* begin: TOKEN_RULES TOKEN_LPAR rules TOKEN_RPAR  */
#line 170 "rulesyacc.y"
                                               {
	  DBUGPRT("begin grammar");
	}
#line 1663 "rulesyacc.tab.c"
    break;

  case 4: /* begin: TOKEN_INPUT TOKEN_LPAR term features TOKEN_RPAR  */
#line 174 "rulesyacc.y"
                                                         {
	  DBUGPRT("begin input");
	  parser.setStartTerm((yyvsp[-2].integer_slot));
	  (*(yyvsp[-1].features_slot))->renameVariables((*(yyvsp[-1].features_slot))->getId());
	  parser.setStartFeatures(*(yyvsp[-1].features_slot));
	  free((yyvsp[-1].features_slot));
	}
#line 1675 "rulesyacc.tab.c"
    break;

  case 5: /* begin: TOKEN_INPUT TOKEN_LPAR term TOKEN_RPAR  */
#line 182 "rulesyacc.y"
                                                {
	  DBUGPRT("begin input");
	  parser.setStartTerm((yyvsp[-1].integer_slot));
	  parser.setStartFeatures(Features::create());
	 }
#line 1685 "rulesyacc.tab.c"
    break;

  case 6: /* begin: TOKEN_LEXICON TOKEN_LPAR dictionary TOKEN_RPAR  */
#line 188 "rulesyacc.y"
                                                       {
	  DBUGPRT("begin lexicon");
	  //CERR_LINE;
	  //parser.printCacheLexicon(std::cout);
	}
#line 1695 "rulesyacc.tab.c"
    break;

  case 7: /* begin: TOKEN_DASH TOKEN_LPAR features TOKEN_RPAR  */
#line 195 "rulesyacc.y"
        {
	  DBUGPRT("begin features");
	  parser.setLocalFeatures(*(yyvsp[-1].features_slot));
	  free((yyvsp[-1].features_slot));
	}
#line 1705 "rulesyacc.tab.c"
    break;

  case 8: /* dictionary: dictionary_line dictionary  */
#line 202 "rulesyacc.y"
                                   {
	  DBUGPRT("dictionary");
	}
#line 1713 "rulesyacc.tab.c"
    break;

  case 9: /* dictionary: dictionary_line  */
#line 206 "rulesyacc.y"
                         {
	  DBUGPRT("dictionary");
	 }
#line 1721 "rulesyacc.tab.c"
    break;

  case 10: /* dictionary_line: TOKEN_FORM TOKEN_IDENTIFIER TOKEN_SEMI  */
#line 213 "rulesyacc.y"
        {
	  DBUGPRT("dictionary_line");
	  unsigned int code = Vartable::stringToCode(*(yyvsp[-1].string_slot));
	  free((yyvsp[-1].string_slot));
	  // constantNoun => (0 => args)
	  auto foundCode = parser.findCacheLexicon(code);
	  Parser::entries_map* zeroToEntries;
	  if (foundCode != parser.cendCacheLexicon()){
	    zeroToEntries = foundCode->second;
	  } else {
	    zeroToEntries = new Parser::entries_map();
	    parser.insertCacheLexicon(std::make_pair(code, zeroToEntries));
	  }
	  auto foundPred = zeroToEntries->find(0);
	  entriesPtr entries;
	  if (foundPred != zeroToEntries->cend()){
	    entries = foundPred->second;
	  } else {
	    entries = Entries::create();
	    zeroToEntries->insert(std::make_pair(0, entries));
	  }
	  entries->add(Entry::create(code, UINT_MAX, std::string(), Features::create()));
	}
#line 1749 "rulesyacc.tab.c"
    break;

  case 11: /* dictionary_line: TOKEN_FORM TOKEN_IDENTIFIER features TOKEN_SEMI  */
#line 238 "rulesyacc.y"
        {
	  DBUGPRT("dictionary_line");
	  unsigned int code = Vartable::stringToCode(*(yyvsp[-2].string_slot));
	  free((yyvsp[-2].string_slot));
	  // constantNoun => (0 => args)
	  auto foundCode = parser.findCacheLexicon(code);
	  Parser::entries_map* zeroToEntries;
	  if (foundCode != parser.cendCacheLexicon()) {
	    zeroToEntries = foundCode->second;
	  } else {
	    zeroToEntries = new Parser::entries_map;
	    parser.insertCacheLexicon(std::make_pair(code, zeroToEntries));
	  }
	  auto foundPred = zeroToEntries->find(0);
	  entriesPtr entries;
	  if (foundPred != zeroToEntries->cend()){
	    entries = foundPred->second;
	  } else {
	    entries = Entries::create();
	    zeroToEntries->insert(std::make_pair(0, entries));
	  }
	  entries->add(Entry::create(code, UINT_MAX, std::string(), *(yyvsp[-1].features_slot)));
	  free((yyvsp[-1].features_slot));
	}
#line 1778 "rulesyacc.tab.c"
    break;

  case 12: /* dictionary_line: stringOrIdentifier lexical_entries TOKEN_SEMI  */
#line 265 "rulesyacc.y"
        {
	  DBUGPRT("dictionary_line");
	  for (auto entry = (*(yyvsp[-1].entries_slot))->begin() ; entry != (*(yyvsp[-1].entries_slot))->end() ; ++entry) {
	    (*entry)->setForm(*(yyvsp[-2].string_slot));
	    entriesPtr lp;
	    Parser::entries_map* predToEntries;
		auto foundCode = parser.findCacheLexicon((*entry)->getPos());
	    if (foundCode != parser.cendCacheLexicon()){
	      predToEntries = foundCode->second;
	    } else {
	      predToEntries = new Parser::entries_map;
	      parser.insertCacheLexicon(std::make_pair((*entry)->getPos(), predToEntries));
	    }
	    Parser::entries_map_iterator foundPred = predToEntries->find((*entry)->getPred());
	    if (foundPred != predToEntries->cend()){
	      lp = foundPred->second;
	    } else {
	      lp = Entries::create();
	      predToEntries->insert(std::make_pair((*entry)->getPred(), lp));
	    }
	    lp->add(*entry);
	  }
	  free((yyvsp[-2].string_slot));
	  free((yyvsp[-1].entries_slot));
	}
#line 1808 "rulesyacc.tab.c"
    break;

  case 13: /* dictionary_line: TOKEN_AROBASE TOKEN_IDENTIFIER TOKEN_COLON features TOKEN_SEMI  */
#line 293 "rulesyacc.y"
        {
	  DBUGPRT("dictionary_line");
	  parser.addMacros(*(yyvsp[-3].string_slot), *(yyvsp[-1].features_slot));
	  free((yyvsp[-3].string_slot));
	  free((yyvsp[-1].features_slot));
	}
#line 1819 "rulesyacc.tab.c"
    break;

  case 14: /* dictionary_line: TOKEN_SEMI  */
#line 301 "rulesyacc.y"
        {
	  DBUGPRT("dictionary_line");
	}
#line 1827 "rulesyacc.tab.c"
    break;

  case 15: /* stringOrIdentifier: TOKEN_IDENTIFIER  */
#line 306 "rulesyacc.y"
                         {
	  DBUGPRT("stringOrIdentifier");
	  (yyval.string_slot) = (yyvsp[0].string_slot);
	}
#line 1836 "rulesyacc.tab.c"
    break;

  case 16: /* stringOrIdentifier: TOKEN_STRING  */
#line 311 "rulesyacc.y"
                      {
	  DBUGPRT("stringOrIdentifier");
	  (yyval.string_slot) = (yyvsp[0].string_slot);
	 }
#line 1845 "rulesyacc.tab.c"
    break;

  case 17: /* stringOrIdentifier: stringOrIdentifier TOKEN_PLUS TOKEN_STRING  */
#line 316 "rulesyacc.y"
                                                    {
	  DBUGPRT("string");
	  (yyval.string_slot) = (yyvsp[-2].string_slot);
	  *(yyval.string_slot) += *(yyvsp[0].string_slot);
	 }
#line 1855 "rulesyacc.tab.c"
    break;

  case 18: /* lexical_entries: lexical_entry TOKEN_PIPE lexical_entries  */
#line 324 "rulesyacc.y"
        {
	  DBUGPRT("lexical_entries");
	  (yyval.entries_slot) = (yyvsp[0].entries_slot);
	  (*(yyval.entries_slot))->add(*(yyvsp[-2].entry_slot));
	  free((yyvsp[-2].entry_slot));
	}
#line 1866 "rulesyacc.tab.c"
    break;

  case 19: /* lexical_entries: lexical_entry  */
#line 331 "rulesyacc.y"
                       {
	  DBUGPRT("lexical_entries");
	  (yyval.entries_slot) = new entriesPtr(Entries::create(*(yyvsp[0].entry_slot)));
	  free((yyvsp[0].entry_slot));
	 }
#line 1876 "rulesyacc.tab.c"
    break;

  case 20: /* lexical_entry: TOKEN_IDENTIFIER features  */
#line 340 "rulesyacc.y"
        {
	  DBUGPRT("lexical_entry");
	  unsigned int pred = (*(yyvsp[0].features_slot))->assignPred();
	  (yyval.entry_slot) = new entryPtr(Entry::create(Vartable::stringToCode(*(yyvsp[-1].string_slot)), pred, std::string(), *(yyvsp[0].features_slot)));
	  free((yyvsp[-1].string_slot));
	  free((yyvsp[0].features_slot));
	}
#line 1888 "rulesyacc.tab.c"
    break;

  case 21: /* lexical_entry: TOKEN_IDENTIFIER  */
#line 349 "rulesyacc.y"
        {
	  DBUGPRT("lexical_entry");
	  (yyval.entry_slot) = new entryPtr(Entry::create(Vartable::stringToCode(*(yyvsp[0].string_slot)), UINT_MAX, std::string(), Features::create()));
	  free((yyvsp[0].string_slot));
	}
#line 1898 "rulesyacc.tab.c"
    break;

  case 22: /* $@1: %empty  */
#line 359 "rulesyacc.y"
        {headLineno = ruleslineno;}
#line 1904 "rulesyacc.tab.c"
    break;

  case 23: /* rules: $@1 rule rules  */
#line 360 "rulesyacc.y"
        {
	  DBUGPRT("rules");
	}
#line 1912 "rulesyacc.tab.c"
    break;

  case 24: /* $@2: %empty  */
#line 364 "rulesyacc.y"
         {headLineno = ruleslineno;}
#line 1918 "rulesyacc.tab.c"
    break;

  case 25: /* rules: $@2  */
#line 365 "rulesyacc.y"
        {
	  DBUGPRT("rules");
	}
#line 1926 "rulesyacc.tab.c"
    break;

  case 26: /* pref_rule: TOKEN_TRACE  */
#line 371 "rulesyacc.y"
        {
	  DBUGPRT("pref_rule");
	  headTrace = true;
	}
#line 1935 "rulesyacc.tab.c"
    break;

  case 27: /* pref_rule: %empty  */
#line 376 "rulesyacc.y"
                      {
	  DBUGPRT("pref_rule");
	  headTrace = false;
	}
#line 1944 "rulesyacc.tab.c"
    break;

  case 28: /* rule: pref_rule term TOKEN_RIGHTARROW terms_vector structure_statement  */
#line 383 "rulesyacc.y"
        {
	  DBUGPRT("rule");
	  rulePtr rule = Rule::create(headLineno, parser.getTopBufferName(), (yyvsp[-3].integer_slot), *(yyvsp[-1].vector_terms_slot), (yyvsp[0].statements_slot) ? *(yyvsp[0].statements_slot) : statementsPtr());
	  rule->addDefaults();
	  rule->setTrace(headTrace);
	  parser.getRules().addRule(rule);
	  if (!parser.getRules().getStartTerm()){
	    parser.getRules().setStartTerm((yyvsp[-3].integer_slot));
	  }
	  free((yyvsp[-1].vector_terms_slot));
	  if ((yyvsp[0].statements_slot))
	     free((yyvsp[0].statements_slot));
	}
#line 1962 "rulesyacc.tab.c"
    break;

  case 29: /* rule: pref_rule term TOKEN_RIGHTARROW structure_statement  */
#line 398 "rulesyacc.y"
        {
	  DBUGPRT("Rule");
	  rulePtr rule = Rule::create(headLineno, parser.getTopBufferName(), (yyvsp[-2].integer_slot), (yyvsp[0].statements_slot) ? *(yyvsp[0].statements_slot) : statementsPtr());
	  rule->addDefaults();
	  rule->setTrace(headTrace);
	  parser.getRules().addRule(rule);
	  if (!parser.getRules().getStartTerm()){
	    parser.getRules().setStartTerm((yyvsp[-2].integer_slot));
	  }
	  if ((yyvsp[0].statements_slot))
	    free((yyvsp[0].statements_slot));
	}
#line 1979 "rulesyacc.tab.c"
    break;

  case 30: /* terms_vector: terms_vector terms  */
#line 412 "rulesyacc.y"
                           {
	  DBUGPRT("term_vector");
	  (yyval.vector_terms_slot)=(yyvsp[-1].vector_terms_slot);
	  (yyval.vector_terms_slot)->push_back(*(yyvsp[0].terms_slot));
	}
#line 1989 "rulesyacc.tab.c"
    break;

  case 31: /* terms_vector: terms  */
#line 418 "rulesyacc.y"
               {
	  DBUGPRT("term_vector");
	  (yyval.vector_terms_slot) = new std::vector< termsPtr >;
	  (yyval.vector_terms_slot)->push_back(*(yyvsp[0].terms_slot));
	}
#line 1999 "rulesyacc.tab.c"
    break;

  case 32: /* terms: terms_disj  */
#line 425 "rulesyacc.y"
                   {
	  DBUGPRT("term");
	  (yyval.terms_slot)=(yyvsp[0].terms_slot);
	}
#line 2008 "rulesyacc.tab.c"
    break;

  case 33: /* terms: TOKEN_LBRACKET terms_disj TOKEN_RBRACKET  */
#line 430 "rulesyacc.y"
                                                  {
	  DBUGPRT("term");
	  (yyval.terms_slot) = (yyvsp[-1].terms_slot);
	  (*(yyval.terms_slot))->setOptional();
	}
#line 2018 "rulesyacc.tab.c"
    break;

  case 34: /* terms_disj: terms_disj TOKEN_PIPE term  */
#line 438 "rulesyacc.y"
        {
	  DBUGPRT("term_disj");
	  (yyval.terms_slot) = (yyvsp[-2].terms_slot);
	  (*(yyval.terms_slot))->push_back((yyvsp[0].integer_slot));
	}
#line 2028 "rulesyacc.tab.c"
    break;

  case 35: /* terms_disj: term  */
#line 445 "rulesyacc.y"
        {
	  DBUGPRT("term_disj");
	  (yyval.terms_slot) = new termsPtr(Terms::create((yyvsp[0].integer_slot)));
	}
#line 2037 "rulesyacc.tab.c"
    break;

  case 36: /* term: TOKEN_IDENTIFIER  */
#line 452 "rulesyacc.y"
        {
	  DBUGPRT("term_id");
	  (yyval.integer_slot) = Vartable::stringToCode(*(yyvsp[0].string_slot));
	  free((yyvsp[0].string_slot));
	}
#line 2047 "rulesyacc.tab.c"
    break;

  case 37: /* term: TOKEN_VARIABLE  */
#line 459 "rulesyacc.y"
        {
	  DBUGPRT("term_id");
	  (yyval.integer_slot) = Vartable::stringToCode(*(yyvsp[0].string_slot));
	  free((yyvsp[0].string_slot));
	}
#line 2057 "rulesyacc.tab.c"
    break;

  case 38: /* term: error  */
#line 466 "rulesyacc.y"
        {
	  YYABORT;
	}
#line 2065 "rulesyacc.tab.c"
    break;

  case 39: /* structure_statement: TOKEN_LBRACE list_statement TOKEN_RBRACE  */
#line 475 "rulesyacc.y"
        {
	  DBUGPRT("structure_statement");
	  (yyval.statements_slot)=(yyvsp[-1].statements_slot);
	}
#line 2074 "rulesyacc.tab.c"
    break;

  case 40: /* structure_statement: TOKEN_LBRACE TOKEN_RBRACE  */
#line 481 "rulesyacc.y"
        {
	  (yyval.statements_slot)=NULL;
	}
#line 2082 "rulesyacc.tab.c"
    break;

  case 41: /* structure_statement: TOKEN_SEMI  */
#line 486 "rulesyacc.y"
        {
	  (yyval.statements_slot)=NULL;
	}
#line 2090 "rulesyacc.tab.c"
    break;

  case 42: /* list_statement: statement  */
#line 492 "rulesyacc.y"
        {
	  DBUGPRT("list_statement");
	  (yyval.statements_slot) = new statementsPtr(Statements::create());
	  (*(yyval.statements_slot))->addStatement(*(yyvsp[0].statement_slot));
	  free((yyvsp[0].statement_slot));
	}
#line 2101 "rulesyacc.tab.c"
    break;

  case 43: /* list_statement: list_statement statement  */
#line 499 "rulesyacc.y"
                                  {
	  DBUGPRT("list_statement");
	  (yyval.statements_slot) = (yyvsp[-1].statements_slot);
	  (*(yyval.statements_slot))->addStatement(*(yyvsp[0].statement_slot));
	  free((yyvsp[0].statement_slot));
	}
#line 2112 "rulesyacc.tab.c"
    break;

  case 44: /* statements: TOKEN_LBRACE list_statement TOKEN_RBRACE  */
#line 508 "rulesyacc.y"
        {
	  DBUGPRT("statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::STMS_STATEMENT, false, *(yyvsp[-1].statements_slot)));
	  free((yyvsp[-1].statements_slot));
	}
#line 2122 "rulesyacc.tab.c"
    break;

  case 45: /* statements: TOKEN_LBRACE TOKEN_RBRACE  */
#line 515 "rulesyacc.y"
        {
	  DBUGPRT("statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::STMS_STATEMENT, false, Statements::create()));
	}
#line 2131 "rulesyacc.tab.c"
    break;

  case 46: /* statement: statements  */
#line 521 "rulesyacc.y"
                   {
	  DBUGPRT("statement");
	  (yyval.statement_slot)=(yyvsp[0].statement_slot);
	 }
#line 2140 "rulesyacc.tab.c"
    break;

  case 47: /* statement: features TOKEN_SEMI  */
#line 526 "rulesyacc.y"
                             {
	  DBUGPRT("statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::GUARD_STATEMENT, true, *(yyvsp[-1].features_slot)));
	  free((yyvsp[-1].features_slot));
	}
#line 2150 "rulesyacc.tab.c"
    break;

  case 48: /* statement: TOKEN_ATTEST expression_statement TOKEN_SEMI  */
#line 532 "rulesyacc.y"
                                                      {
	  DBUGPRT("statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::ATTEST_STATEMENT, true, *(yyvsp[-1].statement_slot)));
	  free((yyvsp[-1].statement_slot));
	}
#line 2160 "rulesyacc.tab.c"
    break;

  case 49: /* statement: TOKEN_PRINT TOKEN_LPAR expression_statement_composite TOKEN_RPAR TOKEN_SEMI  */
#line 538 "rulesyacc.y"
                                                                                     {
	  DBUGPRT("statement");
		(yyval.statement_slot) = new statementPtr(Statement::create(
			ruleslineno, 
			parser.getTopBufferName(), 
			Statement::PRINT_STATEMENT, 
			true, 
			*(yyvsp[-2].statements_slot)));
	  free((yyvsp[-2].statements_slot));
	}
#line 2175 "rulesyacc.tab.c"
    break;

  case 50: /* statement: TOKEN_PRINTLN TOKEN_LPAR expression_statement_composite TOKEN_RPAR TOKEN_SEMI  */
#line 549 "rulesyacc.y"
                                                                                       {
	  	DBUGPRT("statement");
		(yyval.statement_slot) = new statementPtr(Statement::create(
			ruleslineno, 
			parser.getTopBufferName(), 
			Statement::PRINTLN_STATEMENT, 
			true, 
			*(yyvsp[-2].statements_slot)));
	  free((yyvsp[-2].statements_slot));
	}
#line 2190 "rulesyacc.tab.c"
    break;

  case 51: /* statement: left_hand_side_aff_statement TOKEN_AFF right_hand_side_aff_statement TOKEN_SEMI  */
#line 560 "rulesyacc.y"
                                                                                         {
	  DBUGPRT("statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::AFF_STATEMENT, true, *(yyvsp[-3].statement_slot), *(yyvsp[-1].statement_slot)));
	  // <X, …> = <…>
	  // <X, …> = $X
	  // <X, …> = search 
	  if (((*(yyvsp[-3].statement_slot))->isPairp()) 
	  		&& (((*(yyvsp[-1].statement_slot))->isPairp())
				||((*(yyvsp[-1].statement_slot))->isVariable()) 
				||((*(yyvsp[-1].statement_slot))->isSearch()))) {
	    }
	  // ↓i = $X
	  // ↓i = […]
	  // ↓i = ↑
	  // ↓i = … ∪ …
	  // ↓i = ⇓j
	  else if (((*(yyvsp[-3].statement_slot))->isDown()) 
	  		&& (((*(yyvsp[-1].statement_slot))->isVariable())
					||((*(yyvsp[-1].statement_slot))->isFeatures())
					||((*(yyvsp[-1].statement_slot))->isUp())
					||((*(yyvsp[-1].statement_slot))->isUnif())
					||((*(yyvsp[-1].statement_slot))->isDown2())))
	    ;
	  // ⇑ = $X
	  // ⇑ = […]
	  // ⇑ = ↑
	  // ⇑ = … ∪ …
	  // ⇑ = ⇓j
	  else if (((*(yyvsp[-3].statement_slot))->isUp2()) 
	  		&& (((*(yyvsp[-1].statement_slot))->isVariable())
					||((*(yyvsp[-1].statement_slot))->isFeatures())
					||((*(yyvsp[-1].statement_slot))->isUp())
					||((*(yyvsp[-1].statement_slot))->isUnif())
					||((*(yyvsp[-1].statement_slot))->isDown2())))
	    ;
	  // $X = $Y
	  // $X = a
	  // $X = <…>
	  // $X = […]
	  // $X = ↑
	  // $X = … ∪ …
	  // $X = ⇓j
	  // $X = <expr>
	  // $X = search
	  else if (((*(yyvsp[-3].statement_slot))->isVariable())
		   &&(((*(yyvsp[-1].statement_slot))->isVariable())
		      ||((*(yyvsp[-1].statement_slot))->isConstant())
		      ||((*(yyvsp[-1].statement_slot))->isPairp())
		      ||((*(yyvsp[-1].statement_slot))->isFeatures())
		      ||((*(yyvsp[-1].statement_slot))->isUp())
		      ||((*(yyvsp[-1].statement_slot))->isUnif())
		      ||((*(yyvsp[-1].statement_slot))->isDown2())
		      ||((*(yyvsp[-1].statement_slot))->isString())
		      ||((*(yyvsp[-1].statement_slot))->isNumber())
		      ||((*(yyvsp[-1].statement_slot))->isFct())
		      ||((*(yyvsp[-1].statement_slot))->isSearch())));
	  else {
	    yyerror((char*)"syntax error");
	  }
	  free((yyvsp[-3].statement_slot));
	  free((yyvsp[-1].statement_slot));
	}
#line 2257 "rulesyacc.tab.c"
    break;

  case 52: /* statement: left_hand_side_subset_statement TOKEN_SUBSUME right_hand_side_subset_statement TOKEN_SEMI  */
#line 623 "rulesyacc.y"
                                                                                                   {
	  DBUGPRT("statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::SUBSUME_STATEMENT, true, (*(yyvsp[-3].statement_slot)), (*(yyvsp[-1].statement_slot))));
	  // […] ⊂ ↑
	  // […] ⊂ ⇓j
	  // […] ⊂ $X
	  if (((*(yyvsp[-3].statement_slot))->isFeatures()) 
	  		&& (((*(yyvsp[-1].statement_slot))->isUp())
					||((*(yyvsp[-1].statement_slot))->isDown2())
					||((*(yyvsp[-1].statement_slot))->isVariable())))
	    ;
	  else
	    yyerror((char* )"syntax error");
	  free((yyvsp[-3].statement_slot));
	  free((yyvsp[-1].statement_slot));
	}
#line 2278 "rulesyacc.tab.c"
    break;

  case 53: /* statement: TOKEN_IF TOKEN_LPAR expression_statement TOKEN_RPAR statement  */
#line 640 "rulesyacc.y"
                                                                                          {
	  DBUGPRT("statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno,
						parser.getTopBufferName(), 
						Statement::IF_STATEMENT,
						  true, 
						  *(yyvsp[-2].statement_slot),
						  Statement::create(ruleslineno, parser.getTopBufferName(), Statement::IF_CON_T_STATEMENT, false, *(yyvsp[0].statement_slot), statementPtr())));
	  free((yyvsp[-2].statement_slot));
	  free((yyvsp[0].statement_slot));
	}
#line 2294 "rulesyacc.tab.c"
    break;

  case 54: /* statement: TOKEN_IF TOKEN_LPAR expression_statement TOKEN_RPAR statement TOKEN_ELSE statement  */
#line 652 "rulesyacc.y"
                                                                                            {
	  DBUGPRT("statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno,
						  parser.getTopBufferName(),
						  Statement::IF_STATEMENT,
						  true, 
						  (*(yyvsp[-4].statement_slot)),
						  Statement::create(ruleslineno, parser.getTopBufferName(), Statement::IF_CON_T_STATEMENT, false, *(yyvsp[-2].statement_slot), *(yyvsp[0].statement_slot))));
	  free((yyvsp[-4].statement_slot));
	  free((yyvsp[-2].statement_slot));
	  free((yyvsp[0].statement_slot));
	}
#line 2311 "rulesyacc.tab.c"
    break;

  case 55: /* statement: TOKEN_WAIT TOKEN_LPAR expression_statement TOKEN_RPAR statement  */
#line 665 "rulesyacc.y"
                                                                         {
	  DBUGPRT("statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno,
						parser.getTopBufferName(), 
						Statement::WAIT_STATEMENT,
						true, 
						*(yyvsp[-2].statement_slot),
						*(yyvsp[0].statement_slot)));
	  free((yyvsp[-2].statement_slot));
	  free((yyvsp[0].statement_slot));
	}
#line 2327 "rulesyacc.tab.c"
    break;

  case 56: /* statement: TOKEN_FOREACH variable TOKEN_IN expression_statement statement  */
#line 677 "rulesyacc.y"
                                                                        {
	  DBUGPRT("statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno,
						  parser.getTopBufferName(),
						  Statement::FOREACH_STATEMENT,
						  true, 
						  Statement::create(ruleslineno, parser.getTopBufferName(), Statement::VARIABLE_STATEMENT, false, (*(yyvsp[-3].bits_slot))),
						  Statement::create(ruleslineno, parser.getTopBufferName(), Statement::FOREACH_CON_T_STATEMENT, false, (*(yyvsp[-1].statement_slot)), *(yyvsp[0].statement_slot))));
	  free((yyvsp[-3].bits_slot));
	  free((yyvsp[-1].statement_slot));
	  free((yyvsp[0].statement_slot));
	}
#line 2344 "rulesyacc.tab.c"
    break;

  case 57: /* left_hand_side_subset_statement: features  */
#line 691 "rulesyacc.y"
                 {
	  DBUGPRT("left_hand_side_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::FEATURES_STATEMENT, false, *(yyvsp[0].features_slot)));
	  free((yyvsp[0].features_slot));
	}
#line 2354 "rulesyacc.tab.c"
    break;

  case 58: /* right_hand_side_subset_statement: variable  */
#line 698 "rulesyacc.y"
                 {
	  DBUGPRT("right_hand_side_subset_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::VARIABLE_STATEMENT, false, *(yyvsp[0].bits_slot)));
	  free((yyvsp[0].bits_slot));
	}
#line 2364 "rulesyacc.tab.c"
    break;

  case 59: /* right_hand_side_subset_statement: up  */
#line 704 "rulesyacc.y"
            {
	  DBUGPRT("right_hand_side_subset_statement");
	  (yyval.statement_slot)=(yyvsp[0].statement_slot);
	}
#line 2373 "rulesyacc.tab.c"
    break;

  case 60: /* right_hand_side_subset_statement: down2  */
#line 709 "rulesyacc.y"
               {
	  DBUGPRT("right_hand_side_subset_statement");
	  (yyval.statement_slot)=(yyvsp[0].statement_slot);
	}
#line 2382 "rulesyacc.tab.c"
    break;

  case 61: /* right_hand_side_subset_statement: features  */
#line 714 "rulesyacc.y"
                  {
	  DBUGPRT("right_hand_side_subset_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::FEATURES_STATEMENT, false, *(yyvsp[0].features_slot)));
	  free((yyvsp[0].features_slot));
	}
#line 2392 "rulesyacc.tab.c"
    break;

  case 62: /* left_hand_side_aff_statement: up2  */
#line 722 "rulesyacc.y"
            {
	  DBUGPRT("left_hand_side_statement");
	  (yyval.statement_slot)=(yyvsp[0].statement_slot);
	}
#line 2401 "rulesyacc.tab.c"
    break;

  case 63: /* left_hand_side_aff_statement: down  */
#line 727 "rulesyacc.y"
              {
	  DBUGPRT("left_hand_side_statement");
	  (yyval.statement_slot)=(yyvsp[0].statement_slot);
	}
#line 2410 "rulesyacc.tab.c"
    break;

  case 64: /* left_hand_side_aff_statement: variable  */
#line 732 "rulesyacc.y"
                  {
	  DBUGPRT("left_hand_side_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::VARIABLE_STATEMENT, false, *(yyvsp[0].bits_slot)));
	  free((yyvsp[0].bits_slot));
	 }
#line 2420 "rulesyacc.tab.c"
    break;

  case 65: /* left_hand_side_aff_statement: TOKEN_LT variable TOKEN_DOUBLECOLON variable TOKEN_GT  */
#line 739 "rulesyacc.y"
        {
	  DBUGPRT("left_hand_side_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::PAIRP_STATEMENT, false, 
						Pairp::create(Pairp::create(Value::create(Value::VARIABLE_VALUE, *(yyvsp[-3].bits_slot))),
							     Pairp::create(Value::create(Value::VARIABLE_VALUE, *(yyvsp[-1].bits_slot))))));
	  free((yyvsp[-3].bits_slot));
	  free((yyvsp[-1].bits_slot));
	}
#line 2433 "rulesyacc.tab.c"
    break;

  case 66: /* right_hand_side_aff_statement: expression_statement  */
#line 749 "rulesyacc.y"
                             {
	  DBUGPRT("right_hand_side_statement");
	  (yyval.statement_slot)=(yyvsp[0].statement_slot);
	}
#line 2442 "rulesyacc.tab.c"
    break;

  case 67: /* expression_statement: expression_statement TOKEN_OR expression_statement  */
#line 758 "rulesyacc.y"
                                                           {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::FUNCTION_STATEMENT, false, Statement::OR, (*(yyvsp[-2].statement_slot)), (*(yyvsp[0].statement_slot))));
	  free((yyvsp[-2].statement_slot));
	  free((yyvsp[0].statement_slot));
	}
#line 2453 "rulesyacc.tab.c"
    break;

  case 68: /* expression_statement: expression_statement TOKEN_AND expression_statement  */
#line 765 "rulesyacc.y"
                                                             {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::FUNCTION_STATEMENT, false, Statement::AND, (*(yyvsp[-2].statement_slot)), (*(yyvsp[0].statement_slot))));
	  free((yyvsp[-2].statement_slot));
	  free((yyvsp[0].statement_slot));
	}
#line 2464 "rulesyacc.tab.c"
    break;

  case 69: /* expression_statement: expression_statement TOKEN_IMPLICATION expression_statement  */
#line 772 "rulesyacc.y"
                                                                     {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::FUNCTION_STATEMENT, false, Statement::OR, Statement::create(ruleslineno, parser.getTopBufferName(), Statement::FUNCTION_STATEMENT, false, Statement::NOT, (*(yyvsp[-2].statement_slot))), (*(yyvsp[0].statement_slot))));
	  free((yyvsp[-2].statement_slot));
	  free((yyvsp[0].statement_slot));
	}
#line 2475 "rulesyacc.tab.c"
    break;

  case 70: /* expression_statement: expression_statement TOKEN_EQUIV expression_statement  */
#line 779 "rulesyacc.y"
                                                               {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::FUNCTION_STATEMENT, false, Statement::AND,
						                    Statement::create(ruleslineno, parser.getTopBufferName(), Statement::FUNCTION_STATEMENT, false, Statement::OR,
								                Statement::create(ruleslineno, parser.getTopBufferName(), Statement::FUNCTION_STATEMENT, false, Statement::NOT, (*(yyvsp[-2].statement_slot))),
								                (*(yyvsp[0].statement_slot))),
						                    Statement::create(ruleslineno, parser.getTopBufferName(), Statement::FUNCTION_STATEMENT, false, Statement::OR,
								                (*(yyvsp[-2].statement_slot)),
								                Statement::create(ruleslineno, parser.getTopBufferName(), Statement::FUNCTION_STATEMENT, false, Statement::NOT, (*(yyvsp[0].statement_slot))))));
	  free((yyvsp[-2].statement_slot));
	  free((yyvsp[0].statement_slot));
	}
#line 2492 "rulesyacc.tab.c"
    break;

  case 71: /* expression_statement: TOKEN_NOT expression_statement  */
#line 792 "rulesyacc.y"
                                        {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::FUNCTION_STATEMENT, false, Statement::NOT, (*(yyvsp[0].statement_slot))));
	  free((yyvsp[0].statement_slot));
	}
#line 2502 "rulesyacc.tab.c"
    break;

  case 72: /* expression_statement: expression_statement TOKEN_EQUAL expression_statement  */
#line 798 "rulesyacc.y"
                                                               {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::FUNCTION_STATEMENT, false, Statement::EQ, (*(yyvsp[-2].statement_slot)), (*(yyvsp[0].statement_slot))));
	  free((yyvsp[-2].statement_slot));
	  free((yyvsp[0].statement_slot));
	}
#line 2513 "rulesyacc.tab.c"
    break;

  case 73: /* expression_statement: expression_statement TOKEN_DIFF expression_statement  */
#line 805 "rulesyacc.y"
                                                              {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::FUNCTION_STATEMENT, false, Statement::DIFF, (*(yyvsp[-2].statement_slot)), (*(yyvsp[0].statement_slot))));
	  free((yyvsp[-2].statement_slot));
	  free((yyvsp[0].statement_slot));
	}
#line 2524 "rulesyacc.tab.c"
    break;

  case 74: /* expression_statement: expression_statement TOKEN_LT expression_statement  */
#line 812 "rulesyacc.y"
                                                            {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::FUNCTION_STATEMENT, false, Statement::LT, (*(yyvsp[-2].statement_slot)), (*(yyvsp[0].statement_slot))));
	  free((yyvsp[-2].statement_slot));
	  free((yyvsp[0].statement_slot));
	}
#line 2535 "rulesyacc.tab.c"
    break;

  case 75: /* expression_statement: expression_statement TOKEN_LE expression_statement  */
#line 819 "rulesyacc.y"
                                                            {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::FUNCTION_STATEMENT, false, Statement::LE, (*(yyvsp[-2].statement_slot)), (*(yyvsp[0].statement_slot))));
	  free((yyvsp[-2].statement_slot));
	  free((yyvsp[0].statement_slot));
	}
#line 2546 "rulesyacc.tab.c"
    break;

  case 76: /* expression_statement: expression_statement TOKEN_GT expression_statement  */
#line 826 "rulesyacc.y"
                                                            {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::FUNCTION_STATEMENT, false, Statement::GT, (*(yyvsp[-2].statement_slot)), (*(yyvsp[0].statement_slot))));
	  free((yyvsp[-2].statement_slot));
	  free((yyvsp[0].statement_slot));
	}
#line 2557 "rulesyacc.tab.c"
    break;

  case 77: /* expression_statement: expression_statement TOKEN_GE expression_statement  */
#line 833 "rulesyacc.y"
                                                            {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::FUNCTION_STATEMENT, false, Statement::GE, (*(yyvsp[-2].statement_slot)), (*(yyvsp[0].statement_slot))));
	  free((yyvsp[-2].statement_slot));
	  free((yyvsp[0].statement_slot));
	}
#line 2568 "rulesyacc.tab.c"
    break;

  case 78: /* expression_statement: expression_statement TOKEN_PLUS expression_statement  */
#line 844 "rulesyacc.y"
        {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::FUNCTION_STATEMENT, false, Statement::PLUS, (*(yyvsp[-2].statement_slot)), (*(yyvsp[0].statement_slot))));
	  free((yyvsp[-2].statement_slot));
	  free((yyvsp[0].statement_slot));
	}
#line 2579 "rulesyacc.tab.c"
    break;

  case 79: /* expression_statement: expression_statement TOKEN_MINUS expression_statement  */
#line 852 "rulesyacc.y"
        {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::FUNCTION_STATEMENT, false, Statement::MINUS, (*(yyvsp[-2].statement_slot)), (*(yyvsp[0].statement_slot))));
	  free((yyvsp[-2].statement_slot));
	  free((yyvsp[0].statement_slot));
	}
#line 2590 "rulesyacc.tab.c"
    break;

  case 80: /* expression_statement: expression_statement TOKEN_TIMES expression_statement  */
#line 860 "rulesyacc.y"
        {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::FUNCTION_STATEMENT, false, Statement::TIMES, (*(yyvsp[-2].statement_slot)), (*(yyvsp[0].statement_slot))));
	  free((yyvsp[-2].statement_slot));
	  free((yyvsp[0].statement_slot));
	}
#line 2601 "rulesyacc.tab.c"
    break;

  case 81: /* expression_statement: expression_statement TOKEN_DIVIDE expression_statement  */
#line 868 "rulesyacc.y"
        {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::FUNCTION_STATEMENT, false, Statement::DIVIDE, (*(yyvsp[-2].statement_slot)), (*(yyvsp[0].statement_slot))));
	  free((yyvsp[-2].statement_slot));
	  free((yyvsp[0].statement_slot));
	}
#line 2612 "rulesyacc.tab.c"
    break;

  case 82: /* expression_statement: expression_statement TOKEN_MODULO expression_statement  */
#line 876 "rulesyacc.y"
        {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::FUNCTION_STATEMENT, false, Statement::MODULO, (*(yyvsp[-2].statement_slot)), (*(yyvsp[0].statement_slot))));
	  free((yyvsp[-2].statement_slot));
	  free((yyvsp[0].statement_slot));
	}
#line 2623 "rulesyacc.tab.c"
    break;

  case 83: /* expression_statement: TOKEN_MINUS expression_statement  */
#line 884 "rulesyacc.y"
        {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::FUNCTION_STATEMENT, false, Statement::MINUS_U, (*(yyvsp[0].statement_slot)), statementPtr()));
	  free((yyvsp[0].statement_slot));
	}
#line 2633 "rulesyacc.tab.c"
    break;

  case 84: /* expression_statement: TOKEN_RAND TOKEN_LPAR TOKEN_RPAR  */
#line 891 "rulesyacc.y"
        {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::FUNCTION_STATEMENT, false, Statement::RAND));
	}
#line 2642 "rulesyacc.tab.c"
    break;

  case 85: /* expression_statement: TOKEN_DOUBLE  */
#line 897 "rulesyacc.y"
        {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::NUMBER_STATEMENT, false, (yyvsp[0].double_slot)));
	}
#line 2651 "rulesyacc.tab.c"
    break;

  case 86: /* expression_statement: TOKEN_INTEGER  */
#line 903 "rulesyacc.y"
        {
	  DBUGPRT("expression_statement");
 	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::NUMBER_STATEMENT, false, (double)(yyvsp[0].integer_slot)));
	}
#line 2660 "rulesyacc.tab.c"
    break;

  case 87: /* expression_statement: TOKEN_STRING  */
#line 909 "rulesyacc.y"
        {
	  DBUGPRT("expression_statement");
 	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::STRING_STATEMENT, false, *(yyvsp[0].string_slot)));
	}
#line 2669 "rulesyacc.tab.c"
    break;

  case 88: /* expression_statement: expression_statement TOKEN_UNION expression_statement  */
#line 917 "rulesyacc.y"
                                                               {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::UNIF_STATEMENT, false, (*(yyvsp[-2].statement_slot)), (*(yyvsp[0].statement_slot))));
	  free((yyvsp[-2].statement_slot));
	  free((yyvsp[0].statement_slot));
	}
#line 2680 "rulesyacc.tab.c"
    break;

  case 89: /* expression_statement: up  */
#line 924 "rulesyacc.y"
            {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot)=(yyvsp[0].statement_slot);
	}
#line 2689 "rulesyacc.tab.c"
    break;

  case 90: /* expression_statement: up2  */
#line 929 "rulesyacc.y"
             {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot)=(yyvsp[0].statement_slot);
	}
#line 2698 "rulesyacc.tab.c"
    break;

  case 91: /* expression_statement: down  */
#line 934 "rulesyacc.y"
              {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot)=(yyvsp[0].statement_slot);
	}
#line 2707 "rulesyacc.tab.c"
    break;

  case 92: /* expression_statement: down2  */
#line 939 "rulesyacc.y"
               {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot)=(yyvsp[0].statement_slot);
	}
#line 2716 "rulesyacc.tab.c"
    break;

  case 93: /* expression_statement: features  */
#line 944 "rulesyacc.y"
                  {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::FEATURES_STATEMENT, false, *(yyvsp[0].features_slot)));
	  free((yyvsp[0].features_slot));
	}
#line 2726 "rulesyacc.tab.c"
    break;

  case 94: /* expression_statement: TOKEN_NIL  */
#line 954 "rulesyacc.y"
        {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::NIL_STATEMENT, false));
	}
#line 2735 "rulesyacc.tab.c"
    break;

  case 95: /* expression_statement: constant  */
#line 959 "rulesyacc.y"
                  {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::CONSTANT_STATEMENT, false, *(yyvsp[0].bits_slot)));
	  free((yyvsp[0].bits_slot));
	}
#line 2745 "rulesyacc.tab.c"
    break;

  case 96: /* expression_statement: TOKEN_ANONYMOUS  */
#line 969 "rulesyacc.y"
        {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::ANONYMOUS_STATEMENT, false, Value::STATIC_ANONYMOUS));
	}
#line 2754 "rulesyacc.tab.c"
    break;

  case 97: /* expression_statement: variable  */
#line 974 "rulesyacc.y"
                  {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::VARIABLE_STATEMENT, false, *(yyvsp[0].bits_slot)));
	  free((yyvsp[0].bits_slot));
	}
#line 2764 "rulesyacc.tab.c"
    break;

  case 98: /* expression_statement: TOKEN_LPAR expression_statement TOKEN_RPAR  */
#line 980 "rulesyacc.y"
                                                    {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot)=(yyvsp[-1].statement_slot);
	}
#line 2773 "rulesyacc.tab.c"
    break;

  case 99: /* expression_statement: dash_statement  */
#line 988 "rulesyacc.y"
                        {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot)=(yyvsp[0].statement_slot);
	}
#line 2782 "rulesyacc.tab.c"
    break;

  case 100: /* expression_statement: pairp  */
#line 996 "rulesyacc.y"
               {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::PAIRP_STATEMENT, false, *(yyvsp[0].pairp_slot)));
	  free((yyvsp[0].pairp_slot));
	}
#line 2792 "rulesyacc.tab.c"
    break;

  case 101: /* expression_statement: TOKEN_SEARCH expression_statement TOKEN_ON TOKEN_IDENTIFIER  */
#line 1005 "rulesyacc.y"
                                                                     {
	  	DBUGPRT("expression_statement");
	  	(yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno,
						  parser.getTopBufferName(),
						  Statement::SEARCH_STATEMENT,
						  true,
						  *(yyvsp[-2].statement_slot),
						  Vartable::stringToCode(*(yyvsp[0].string_slot))));
		free((yyvsp[-2].statement_slot));
	  	free((yyvsp[0].string_slot));
	 }
#line 2808 "rulesyacc.tab.c"
    break;

  case 102: /* expression_statement_composite: expression_statement_composite TOKEN_COMMA expression_statement  */
#line 1020 "rulesyacc.y"
        {
	  DBUGPRT("expression_statement_composite");
	  (yyval.statements_slot) = (yyvsp[-2].statements_slot);
	  (*(yyval.statements_slot))->addStatement(*(yyvsp[0].statement_slot));
	  free((yyvsp[0].statement_slot));
	}
#line 2819 "rulesyacc.tab.c"
    break;

  case 103: /* expression_statement_composite: expression_statement  */
#line 1028 "rulesyacc.y"
        {
	  DBUGPRT("expression_statement_composite");
	  (yyval.statements_slot) = new statementsPtr(Statements::create());
	  (*(yyval.statements_slot))->addStatement(*(yyvsp[0].statement_slot));
	  free((yyvsp[0].statement_slot));
	}
#line 2830 "rulesyacc.tab.c"
    break;

  case 104: /* up: TOKEN_UPARROW  */
#line 1037 "rulesyacc.y"
                      {
	  DBUGPRT("up");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::INHERITED_FEATURES_STATEMENT, false));
	}
#line 2839 "rulesyacc.tab.c"
    break;

  case 105: /* up2: TOKEN_UP2ARROW  */
#line 1043 "rulesyacc.y"
                       {
	  DBUGPRT("up2");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::SYNTHESIZED_FEATURES_STATEMENT, false));
	}
#line 2848 "rulesyacc.tab.c"
    break;

  case 106: /* down: TOKEN_DOWNARROW TOKEN_INTEGER  */
#line 1050 "rulesyacc.y"
        {
	  DBUGPRT("down");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::INHERITED_CHILDREN_FEATURES_STATEMENT, false, (unsigned int)(yyvsp[0].integer_slot)-1));
	}
#line 2857 "rulesyacc.tab.c"
    break;

  case 107: /* down2: TOKEN_DOWN2ARROW TOKEN_INTEGER  */
#line 1057 "rulesyacc.y"
        {
	  DBUGPRT("down2");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::SYNTHESIZED_CHILDREN_FEATURES_STATEMENT, false, (unsigned int)((yyvsp[0].integer_slot)-1)));
	}
#line 2866 "rulesyacc.tab.c"
    break;

  case 108: /* dash_statement: TOKEN_DASH TOKEN_INTEGER TOKEN_DOT TOKEN_INTEGER  */
#line 1064 "rulesyacc.y"
        {
	  DBUGPRT("dash_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::DASH_STATEMENT, false, (unsigned int)((yyvsp[-2].integer_slot)-1), (unsigned int)((yyvsp[0].integer_slot)-1)));
	}
#line 2875 "rulesyacc.tab.c"
    break;

  case 109: /* dash_statement: TOKEN_DASH TOKEN_INTEGER  */
#line 1070 "rulesyacc.y"
        {
	  DBUGPRT("dash_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::DASH_STATEMENT, false, (unsigned int)((yyvsp[0].integer_slot)-1), (unsigned int)UINT_MAX));
	}
#line 2884 "rulesyacc.tab.c"
    break;

  case 110: /* features: TOKEN_LBRACKET features_composite features_composite_tail TOKEN_RBRACKET  */
#line 1080 "rulesyacc.y"
        {
	  DBUGPRT("features");
 	  (yyval.features_slot) = (yyvsp[-2].features_slot);
	  if ((yyvsp[-1].feature_slot)) {
	    (*(yyval.features_slot))->add(*(yyvsp[-1].feature_slot));
	    free((yyvsp[-1].feature_slot));
	  }
	}
#line 2897 "rulesyacc.tab.c"
    break;

  case 111: /* features: TOKEN_LBRACKET TOKEN_RBRACKET  */
#line 1090 "rulesyacc.y"
        {
	  DBUGPRT("features");
	  (yyval.features_slot) = new featuresPtr(Features::create());
	}
#line 2906 "rulesyacc.tab.c"
    break;

  case 112: /* features_composite_tail: %empty  */
#line 1097 "rulesyacc.y"
        {
	    (yyval.feature_slot) = NULL;
	}
#line 2914 "rulesyacc.tab.c"
    break;

  case 113: /* features_composite_tail: TOKEN_COMMA variable  */
#line 1102 "rulesyacc.y"
        {
        (yyval.feature_slot) = new featurePtr(Feature::create(Feature::_VARIABLE_, *(yyvsp[0].bits_slot), valuePtr()));
    }
#line 2922 "rulesyacc.tab.c"
    break;

  case 114: /* features_composite: features_composite TOKEN_COMMA feature  */
#line 1108 "rulesyacc.y"
        {
	  DBUGPRT("feature_components");
	  (yyval.features_slot) = (yyvsp[-2].features_slot);
	  (*(yyval.features_slot))->add(*(yyvsp[0].feature_slot));
	  free((yyvsp[0].feature_slot));
	}
#line 2933 "rulesyacc.tab.c"
    break;

  case 115: /* features_composite: feature  */
#line 1116 "rulesyacc.y"
        {
	  DBUGPRT("features_composite");
	  (yyval.features_slot) = new featuresPtr(Features::create());
	  (*(yyval.features_slot))->add(*(yyvsp[0].feature_slot));
	  free((yyvsp[0].feature_slot));
	}
#line 2944 "rulesyacc.tab.c"
    break;

  case 116: /* features_composite: features_composite TOKEN_COMMA TOKEN_AROBASE TOKEN_IDENTIFIER  */
#line 1125 "rulesyacc.y"
        {
	  DBUGPRT("features_composite");
	  featuresPtr found = parser.findMacros(*(yyvsp[0].string_slot));
	  (yyval.features_slot) = (yyvsp[-3].features_slot);
	  if (!(found)){
	     std::ostringstream oss; oss << "unknown macro: @" << *(yyvsp[0].string_slot);
	     yyerror((char*)oss.str().c_str());
	  } else {
	    (*(yyval.features_slot))->add(found->clone());
	  }
	  free((yyvsp[0].string_slot));
	}
#line 2961 "rulesyacc.tab.c"
    break;

  case 117: /* features_composite: TOKEN_AROBASE TOKEN_IDENTIFIER  */
#line 1140 "rulesyacc.y"
        {
	  DBUGPRT("features_composite");
	  featuresPtr found = parser.findMacros(*(yyvsp[0].string_slot));
	  (yyval.features_slot) = new featuresPtr(Features::create());
	  if (!(found)){
	    std::ostringstream oss; oss << "***unknown macro: @" << *(yyvsp[0].string_slot);
	    yyerror((char*)oss.str().c_str());
	  } else {
	    (*(yyval.features_slot))->add(found->clone());
	  }
	  free((yyvsp[0].string_slot));
	  }
#line 2978 "rulesyacc.tab.c"
    break;

  case 118: /* feature: TOKEN_LEMMA TOKEN_COLON stringOrIdentifier  */
#line 1156 "rulesyacc.y"
        {
	  DBUGPRT("feature");
	  (yyval.feature_slot) = new featurePtr(Feature::create(Feature::_LEMMA_, bitsetPtr(), Value::create(Value::IDENTIFIER_VALUE, *(yyvsp[0].string_slot))));
	}
#line 2987 "rulesyacc.tab.c"
    break;

  case 119: /* feature: TOKEN_LEMMA TOKEN_COLON variable  */
#line 1163 "rulesyacc.y"
        {
	  DBUGPRT("feature");
	  (yyval.feature_slot) = new featurePtr(Feature::create(Feature::_LEMMA_, bitsetPtr(), Value::create(Value::VARIABLE_VALUE, *(yyvsp[0].bits_slot))));
	}
#line 2996 "rulesyacc.tab.c"
    break;

  case 120: /* feature: TOKEN_PRED TOKEN_COLON stringOrIdentifier  */
#line 1170 "rulesyacc.y"
        {
	  DBUGPRT("feature");
	  (yyval.feature_slot) = new featurePtr(Feature::create(Feature::_PRED_, bitsetPtr(), Value::create(Value::IDENTIFIER_VALUE, *(yyvsp[0].string_slot))));
	}
#line 3005 "rulesyacc.tab.c"
    break;

  case 121: /* feature: TOKEN_PRED TOKEN_COLON variable  */
#line 1177 "rulesyacc.y"
        {
	  DBUGPRT("feature");
	  (yyval.feature_slot) = new featurePtr(Feature::create(Feature::_PRED_, bitsetPtr(), Value::create(Value::VARIABLE_VALUE, *(yyvsp[0].bits_slot))));
	  free((yyvsp[0].bits_slot));
	}
#line 3015 "rulesyacc.tab.c"
    break;

  case 122: /* feature: TOKEN_FORM TOKEN_COLON variable  */
#line 1185 "rulesyacc.y"
        {
	  DBUGPRT("feature");
	  (yyval.feature_slot) = new featurePtr(Feature::create(Feature::_FORM_, bitsetPtr(), Value::create(Value::VARIABLE_VALUE, *(yyvsp[0].bits_slot))));
	  free((yyvsp[0].bits_slot));
	}
#line 3025 "rulesyacc.tab.c"
    break;

  case 123: /* feature: TOKEN_FORM TOKEN_COLON stringOrIdentifier  */
#line 1192 "rulesyacc.y"
        {
	  DBUGPRT("feature");
	  (yyval.feature_slot) = new featurePtr(Feature::create(Feature::_FORM_, bitsetPtr(), Value::create(Value::FORM_VALUE, *(yyvsp[0].string_slot))));
	}
#line 3034 "rulesyacc.tab.c"
    break;

  case 124: /* feature: identifier TOKEN_COLON feature_value  */
#line 1198 "rulesyacc.y"
        {
	  DBUGPRT("feature");
	  (yyval.feature_slot) = new featurePtr(Feature::create(Feature::_CONSTANT_, *(yyvsp[-2].bits_slot), *(yyvsp[0].value_slot)));
	  free((yyvsp[-2].bits_slot));
	  free((yyvsp[0].value_slot));
	}
#line 3045 "rulesyacc.tab.c"
    break;

  case 125: /* feature: identifier TOKEN_COLON TOKEN_STRING  */
#line 1206 "rulesyacc.y"
        {
	  DBUGPRT("feature");
	  (yyval.feature_slot) = new featurePtr(Feature::create(Feature::_CONSTANT_, *(yyvsp[-2].bits_slot), Value::create(Value::FORM_VALUE, *(yyvsp[0].string_slot))));
	  free((yyvsp[-2].bits_slot));
	}
#line 3055 "rulesyacc.tab.c"
    break;

  case 126: /* feature: variable TOKEN_COLON feature_value  */
#line 1213 "rulesyacc.y"
        {
	  DBUGPRT("feature");
	  (yyval.feature_slot) = new featurePtr(Feature::create(Feature::_VARIABLE_, *(yyvsp[-2].bits_slot), *(yyvsp[0].value_slot)));
	  free((yyvsp[-2].bits_slot));
	  free((yyvsp[0].value_slot));
	}
#line 3066 "rulesyacc.tab.c"
    break;

  case 127: /* feature_value: variable  */
#line 1223 "rulesyacc.y"
        {
	  DBUGPRT("feature_value");
	  (yyval.value_slot) = new valuePtr(Value::create(Value::VARIABLE_VALUE, *(yyvsp[0].bits_slot)));
	  free((yyvsp[0].bits_slot));
	}
#line 3076 "rulesyacc.tab.c"
    break;

  case 128: /* feature_value: constant  */
#line 1230 "rulesyacc.y"
        {
	  DBUGPRT("feature_value");
	  (yyval.value_slot) = new valuePtr(Value::create(Value::CONSTANT_VALUE, *(yyvsp[0].bits_slot)));
	  free((yyvsp[0].bits_slot));
	}
#line 3086 "rulesyacc.tab.c"
    break;

  case 129: /* feature_value: TOKEN_DOUBLE  */
#line 1237 "rulesyacc.y"
        {
	  DBUGPRT("expression_statement");
	  (yyval.value_slot) = new valuePtr(Value::create(Value::NUMBER_VALUE, (yyvsp[0].double_slot)));
	}
#line 3095 "rulesyacc.tab.c"
    break;

  case 130: /* feature_value: TOKEN_INTEGER  */
#line 1243 "rulesyacc.y"
        {
	  DBUGPRT("expression_statement");
	  (yyval.value_slot) = new valuePtr(Value::create(Value::NUMBER_VALUE, (double)(yyvsp[0].integer_slot)));
	}
#line 3104 "rulesyacc.tab.c"
    break;

  case 131: /* feature_value: pairp  */
#line 1249 "rulesyacc.y"
        {
	  DBUGPRT("feature_value");
	  (yyval.value_slot) = new valuePtr(Value::create(*(yyvsp[0].pairp_slot)));
	  free((yyvsp[0].pairp_slot));
	}
#line 3114 "rulesyacc.tab.c"
    break;

  case 132: /* feature_value: features  */
#line 1256 "rulesyacc.y"
        {
	  DBUGPRT("feature_value");
	  (yyval.value_slot) = new valuePtr(Value::create(*(yyvsp[0].features_slot)));
	  free((yyvsp[0].features_slot));
	}
#line 3124 "rulesyacc.tab.c"
    break;

  case 133: /* feature_value: TOKEN_NIL  */
#line 1263 "rulesyacc.y"
        {
	  DBUGPRT("feature_value");
	  (yyval.value_slot) = new valuePtr(Value::STATIC_NIL);
	}
#line 3133 "rulesyacc.tab.c"
    break;

  case 134: /* feature_value: TOKEN_ANONYMOUS  */
#line 1269 "rulesyacc.y"
        {
	  DBUGPRT("feature_value");
	  (yyval.value_slot) = new valuePtr(Value::STATIC_ANONYMOUS);
	}
#line 3142 "rulesyacc.tab.c"
    break;

  case 135: /* constant: identifier  */
#line 1276 "rulesyacc.y"
        {
	  DBUGPRT("constants");
	  (yyval.bits_slot)=(yyvsp[0].bits_slot);
	}
#line 3151 "rulesyacc.tab.c"
    break;

  case 136: /* constant: identifier TOKEN_PIPE constant  */
#line 1282 "rulesyacc.y"
        {
	  DBUGPRT("constants");
	  (yyval.bits_slot)=(yyvsp[-2].bits_slot);
	  (**(yyval.bits_slot)) |= (**(yyvsp[0].bits_slot));
	}
#line 3161 "rulesyacc.tab.c"
    break;

  case 137: /* identifier: TOKEN_IDENTIFIER  */
#line 1290 "rulesyacc.y"
        {
	  DBUGPRT("identifier");
 	  (yyval.bits_slot) = new bitsetPtr(Bitset::create(Vartable::createVariable(*(yyvsp[0].string_slot))));
 	  free((yyvsp[0].string_slot));
	}
#line 3171 "rulesyacc.tab.c"
    break;

  case 138: /* variable: TOKEN_VARIABLE  */
#line 1298 "rulesyacc.y"
        {
	  DBUGPRT("variable");
	  std::ostringstream oss;
	  oss << *(yyvsp[0].string_slot);
  	  std::string str = oss.str();
	  (yyval.bits_slot) = new bitsetPtr(Bitset::create(Vartable::createVariable(str)));
	  free((yyvsp[0].string_slot));
	}
#line 3184 "rulesyacc.tab.c"
    break;

  case 139: /* pairp: TOKEN_LT pairp_elements TOKEN_GT  */
#line 1309 "rulesyacc.y"
        {
	  DBUGPRT("list");
	  (yyval.pairp_slot) = (yyvsp[-1].pairp_slot);
	}
#line 3193 "rulesyacc.tab.c"
    break;

  case 140: /* pairp: TOKEN_LT TOKEN_GT  */
#line 1315 "rulesyacc.y"
        {
	  DBUGPRT("list");
	  (yyval.pairp_slot) = new pairpPtr(Pairp::NIL);
	}
#line 3202 "rulesyacc.tab.c"
    break;

  case 141: /* pairp: TOKEN_LT pairp_elements TOKEN_DOUBLECOLON pairp_element TOKEN_GT  */
#line 1321 "rulesyacc.y"
        {
	  DBUGPRT("list");
	  if ((*(yyvsp[-3].pairp_slot))->isPairp() && (*(yyvsp[-3].pairp_slot))->getCdr()->isNil())
	    (yyval.pairp_slot) = new pairpPtr(Pairp::create((*(yyvsp[-3].pairp_slot))->getCar(), *(yyvsp[-1].pairp_slot)));
	  else
	    (yyval.pairp_slot) = new pairpPtr(Pairp::create(*(yyvsp[-3].pairp_slot), *(yyvsp[-1].pairp_slot)));
	  free((yyvsp[-3].pairp_slot));
	  free((yyvsp[-1].pairp_slot));
	}
#line 3216 "rulesyacc.tab.c"
    break;

  case 142: /* pairp: TOKEN_LT pairp_elements TOKEN_DOUBLECOLON TOKEN_NIL TOKEN_GT  */
#line 1332 "rulesyacc.y"
        {
	  DBUGPRT("list");
	  if ((*(yyvsp[-3].pairp_slot))->isPairp() && (*(yyvsp[-3].pairp_slot))->getCdr()->isNil())
	    (yyval.pairp_slot) = new pairpPtr(Pairp::create((*(yyvsp[-3].pairp_slot))->getCar(), Pairp::NIL));
	  else
	    (yyval.pairp_slot) = new pairpPtr(Pairp::create(*(yyvsp[-3].pairp_slot), Pairp::NIL));
	  free((yyvsp[-3].pairp_slot));
	}
#line 3229 "rulesyacc.tab.c"
    break;

  case 143: /* pairp_elements: pairp_element TOKEN_COMMA pairp_elements  */
#line 1345 "rulesyacc.y"
        {
	  DBUGPRT("pairp_elements");
	  (yyval.pairp_slot) = new pairpPtr(Pairp::create(*(yyvsp[-2].pairp_slot), *(yyvsp[0].pairp_slot)));
	  free((yyvsp[-2].pairp_slot));
	  free((yyvsp[0].pairp_slot));
	}
#line 3240 "rulesyacc.tab.c"
    break;

  case 144: /* pairp_elements: pairp_element  */
#line 1353 "rulesyacc.y"
        {
	  DBUGPRT("pairp_elements");
	  (yyval.pairp_slot) = new pairpPtr(Pairp::create(*(yyvsp[0].pairp_slot), Pairp::NIL));
	  free((yyvsp[0].pairp_slot));
	}
#line 3250 "rulesyacc.tab.c"
    break;

  case 145: /* pairp_element: variable  */
#line 1361 "rulesyacc.y"
        {
	  DBUGPRT("pairp_element");
	  (yyval.pairp_slot) = new pairpPtr(Pairp::create(Value::create(Value::VARIABLE_VALUE, *(yyvsp[0].bits_slot))));
	  free((yyvsp[0].bits_slot));
	}
#line 3260 "rulesyacc.tab.c"
    break;

  case 146: /* pairp_element: TOKEN_DOUBLE  */
#line 1368 "rulesyacc.y"
        {
	  DBUGPRT("expression_statement");
	  (yyval.pairp_slot) = new pairpPtr(Pairp::create(Value::create(Value::NUMBER_VALUE, (yyvsp[0].double_slot))));
	}
#line 3269 "rulesyacc.tab.c"
    break;

  case 147: /* pairp_element: TOKEN_INTEGER  */
#line 1374 "rulesyacc.y"
        {
	  DBUGPRT("expression_statement");
	  (yyval.pairp_slot) = new pairpPtr(Pairp::create(Value::create(Value::NUMBER_VALUE, (double)(yyvsp[0].integer_slot))));
	}
#line 3278 "rulesyacc.tab.c"
    break;

  case 148: /* pairp_element: constant  */
#line 1380 "rulesyacc.y"
        {
	  DBUGPRT("pairp_element");
	  (yyval.pairp_slot) = new pairpPtr(Pairp::create(Value::create(Value::CONSTANT_VALUE, *(yyvsp[0].bits_slot))));
	  free((yyvsp[0].bits_slot));
	}
#line 3288 "rulesyacc.tab.c"
    break;

  case 149: /* pairp_element: features  */
#line 1387 "rulesyacc.y"
        {
	  DBUGPRT("pairp_element");
	  (yyval.pairp_slot) = new pairpPtr(Pairp::create(Value::create(*(yyvsp[0].features_slot))));
	  free((yyvsp[0].features_slot));
	}
#line 3298 "rulesyacc.tab.c"
    break;

  case 150: /* pairp_element: pairp  */
#line 1394 "rulesyacc.y"
        {
	  DBUGPRT("pairp_element");
	  (yyval.pairp_slot)=(yyvsp[0].pairp_slot);
	}
#line 3307 "rulesyacc.tab.c"
    break;


#line 3311 "rulesyacc.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 1399 "rulesyacc.y"

