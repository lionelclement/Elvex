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


/* Substitute the variable and function names.  */
#define yyparse         rulesparse
#define yylex           ruleslex
#define yyerror         ruleserror
#define yydebug         rulesdebug
#define yynerrs         rulesnerrs
#define yylval          ruleslval
#define yychar          ruleschar

/* First part of user prologue.  */
#line 1 "src/rulesyacc.y"


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
 * lionel.clement@labri.fr
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
#include "list.hpp"
#include "statements.hpp"
#include "statement.hpp"
#include "terms.hpp"
#include "messages.hpp"
#include "rule.hpp"
#include "shared_ptr.hpp"
#include "parser_exception.hpp"

#if false
#define DBUG(x)x
#else
#define DBUG(x)
#endif
#define DBUGPRT(x) DBUG(std::cerr << "*** " << x << std::endl)
#define DBUGPRTARG(x,s) DBUG(std::cerr << "*** " << x << " " << s << std::endl)

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

  

#line 147 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"

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

#include "rulesyacc.hpp"
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
  YYSYMBOL_TOKEN_NIL = 32,                 /* TOKEN_NIL  */
  YYSYMBOL_TOKEN_TRUE = 33,                /* TOKEN_TRUE  */
  YYSYMBOL_TOKEN_FALSE = 34,               /* TOKEN_FALSE  */
  YYSYMBOL_TOKEN_FOREACH = 35,             /* TOKEN_FOREACH  */
  YYSYMBOL_TOKEN_IN = 36,                  /* TOKEN_IN  */
  YYSYMBOL_TOKEN_SEARCH = 37,              /* TOKEN_SEARCH  */
  YYSYMBOL_TOKEN_RAND = 38,                /* TOKEN_RAND  */
  YYSYMBOL_TOKEN_TRACE = 39,               /* TOKEN_TRACE  */
  YYSYMBOL_TOKEN_UNION = 40,               /* TOKEN_UNION  */
  YYSYMBOL_TOKEN_SUBSUME = 41,             /* TOKEN_SUBSUME  */
  YYSYMBOL_TOKEN_AFF = 42,                 /* TOKEN_AFF  */
  YYSYMBOL_TOKEN_PIPE = 43,                /* TOKEN_PIPE  */
  YYSYMBOL_TOKEN_NOT = 44,                 /* TOKEN_NOT  */
  YYSYMBOL_TOKEN_OR = 45,                  /* TOKEN_OR  */
  YYSYMBOL_TOKEN_AND = 46,                 /* TOKEN_AND  */
  YYSYMBOL_TOKEN_IMPLICATION = 47,         /* TOKEN_IMPLICATION  */
  YYSYMBOL_TOKEN_EQUIV = 48,               /* TOKEN_EQUIV  */
  YYSYMBOL_TOKEN_PLUS = 49,                /* TOKEN_PLUS  */
  YYSYMBOL_TOKEN_MINUS = 50,               /* TOKEN_MINUS  */
  YYSYMBOL_TOKEN_TIMES = 51,               /* TOKEN_TIMES  */
  YYSYMBOL_TOKEN_DIVIDE = 52,              /* TOKEN_DIVIDE  */
  YYSYMBOL_TOKEN_MODULO = 53,              /* TOKEN_MODULO  */
  YYSYMBOL_TOKEN_EQUAL = 54,               /* TOKEN_EQUAL  */
  YYSYMBOL_TOKEN_DIFF = 55,                /* TOKEN_DIFF  */
  YYSYMBOL_TOKEN_LT = 56,                  /* TOKEN_LT  */
  YYSYMBOL_TOKEN_LE = 57,                  /* TOKEN_LE  */
  YYSYMBOL_TOKEN_GT = 58,                  /* TOKEN_GT  */
  YYSYMBOL_TOKEN_GE = 59,                  /* TOKEN_GE  */
  YYSYMBOL_TOKEN_IDENTIFIER = 60,          /* TOKEN_IDENTIFIER  */
  YYSYMBOL_TOKEN_STRING = 61,              /* TOKEN_STRING  */
  YYSYMBOL_TOKEN_INTEGER = 62,             /* TOKEN_INTEGER  */
  YYSYMBOL_TOKEN_DOUBLE = 63,              /* TOKEN_DOUBLE  */
  YYSYMBOL_TOKEN_VARIABLE = 64,            /* TOKEN_VARIABLE  */
  YYSYMBOL_TOKEN_ANONYMOUS = 65,           /* TOKEN_ANONYMOUS  */
  YYSYMBOL_TOKEN_MINUS_U = 66,             /* TOKEN_MINUS_U  */
  YYSYMBOL_TOKEN_NOELSE = 67,              /* TOKEN_NOELSE  */
  YYSYMBOL_YYACCEPT = 68,                  /* $accept  */
  YYSYMBOL_axiom = 69,                     /* axiom  */
  YYSYMBOL_begin = 70,                     /* begin  */
  YYSYMBOL_dictionary = 71,                /* dictionary  */
  YYSYMBOL_dictionary_line = 72,           /* dictionary_line  */
  YYSYMBOL_stringOrIdentifier = 73,        /* stringOrIdentifier  */
  YYSYMBOL_lexical_entries = 74,           /* lexical_entries  */
  YYSYMBOL_lexical_entry = 75,             /* lexical_entry  */
  YYSYMBOL_rules = 76,                     /* rules  */
  YYSYMBOL_77_1 = 77,                      /* $@1  */
  YYSYMBOL_78_2 = 78,                      /* $@2  */
  YYSYMBOL_pref_rule = 79,                 /* pref_rule  */
  YYSYMBOL_rule = 80,                      /* rule  */
  YYSYMBOL_terms_vector = 81,              /* terms_vector  */
  YYSYMBOL_terms = 82,                     /* terms  */
  YYSYMBOL_terms_disj = 83,                /* terms_disj  */
  YYSYMBOL_term = 84,                      /* term  */
  YYSYMBOL_structure_statement = 85,       /* structure_statement  */
  YYSYMBOL_list_statement = 86,            /* list_statement  */
  YYSYMBOL_statements = 87,                /* statements  */
  YYSYMBOL_statement = 88,                 /* statement  */
  YYSYMBOL_left_hand_side_subset_statement = 89, /* left_hand_side_subset_statement  */
  YYSYMBOL_right_hand_side_subset_statement = 90, /* right_hand_side_subset_statement  */
  YYSYMBOL_left_hand_side_aff_statement = 91, /* left_hand_side_aff_statement  */
  YYSYMBOL_right_hand_side_aff_statement = 92, /* right_hand_side_aff_statement  */
  YYSYMBOL_expression_statement = 93,      /* expression_statement  */
  YYSYMBOL_up = 94,                        /* up  */
  YYSYMBOL_updouble = 95,                  /* updouble  */
  YYSYMBOL_down = 96,                      /* down  */
  YYSYMBOL_dash_statement = 97,            /* dash_statement  */
  YYSYMBOL_downdouble = 98,                /* downdouble  */
  YYSYMBOL_features = 99,                  /* features  */
  YYSYMBOL_features_components_tail = 100, /* features_components_tail  */
  YYSYMBOL_features_components = 101,      /* features_components  */
  YYSYMBOL_feature = 102,                  /* feature  */
  YYSYMBOL_feature_value = 103,            /* feature_value  */
  YYSYMBOL_constant = 104,                 /* constant  */
  YYSYMBOL_identifier = 105,               /* identifier  */
  YYSYMBOL_variable = 106,                 /* variable  */
  YYSYMBOL_list = 107,                     /* list  */
  YYSYMBOL_list_elements = 108,            /* list_elements  */
  YYSYMBOL_list_element = 109              /* list_element  */
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
#define YYFINAL  24
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   735

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  68
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  42
/* YYNRULES -- Number of rules.  */
#define YYNRULES  150
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  260

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   322


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
      65,    66,    67
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   162,   162,   168,   172,   180,   186,   192,   200,   204,
     210,   235,   262,   291,   299,   305,   310,   315,   322,   330,
     338,   347,   358,   358,   363,   363,   369,   375,   381,   396,
     411,   417,   424,   429,   436,   443,   450,   457,   464,   473,
     479,   484,   490,   498,   506,   513,   520,   525,   531,   537,
     543,   549,   609,   628,   646,   673,   693,   700,   706,   711,
     716,   722,   732,   741,   746,   751,   757,   768,   777,   784,
     791,   798,   811,   817,   824,   831,   838,   845,   852,   862,
     870,   878,   886,   894,   902,   909,   915,   921,   927,   936,
     943,   948,   953,   958,   963,   969,   975,   981,   987,   993,
     998,  1004,  1009,  1018,  1024,  1030,  1037,  1043,  1050,  1055,
    1065,  1075,  1083,  1087,  1093,  1101,  1110,  1125,  1141,  1148,
    1155,  1162,  1170,  1177,  1183,  1191,  1198,  1208,  1215,  1222,
    1228,  1234,  1241,  1248,  1254,  1261,  1267,  1275,  1283,  1294,
    1300,  1306,  1317,  1328,  1336,  1344,  1351,  1357,  1363,  1370,
    1377
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
  "TOKEN_PRINTLN", "TOKEN_IF", "TOKEN_ELSE", "TOKEN_NIL", "TOKEN_TRUE",
  "TOKEN_FALSE", "TOKEN_FOREACH", "TOKEN_IN", "TOKEN_SEARCH", "TOKEN_RAND",
  "TOKEN_TRACE", "TOKEN_UNION", "TOKEN_SUBSUME", "TOKEN_AFF", "TOKEN_PIPE",
  "TOKEN_NOT", "TOKEN_OR", "TOKEN_AND", "TOKEN_IMPLICATION", "TOKEN_EQUIV",
  "TOKEN_PLUS", "TOKEN_MINUS", "TOKEN_TIMES", "TOKEN_DIVIDE",
  "TOKEN_MODULO", "TOKEN_EQUAL", "TOKEN_DIFF", "TOKEN_LT", "TOKEN_LE",
  "TOKEN_GT", "TOKEN_GE", "TOKEN_IDENTIFIER", "TOKEN_STRING",
  "TOKEN_INTEGER", "TOKEN_DOUBLE", "TOKEN_VARIABLE", "TOKEN_ANONYMOUS",
  "TOKEN_MINUS_U", "TOKEN_NOELSE", "$accept", "axiom", "begin",
  "dictionary", "dictionary_line", "stringOrIdentifier", "lexical_entries",
  "lexical_entry", "rules", "$@1", "$@2", "pref_rule", "rule",
  "terms_vector", "terms", "terms_disj", "term", "structure_statement",
  "list_statement", "statements", "statement",
  "left_hand_side_subset_statement", "right_hand_side_subset_statement",
  "left_hand_side_aff_statement", "right_hand_side_aff_statement",
  "expression_statement", "up", "updouble", "down", "dash_statement",
  "downdouble", "features", "features_components_tail",
  "features_components", "feature", "feature_value", "constant",
  "identifier", "variable", "list", "list_elements", "list_element", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-114)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-25)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      82,    -7,    18,     3,   268,    42,  -114,    69,  -114,  -114,
      16,  -114,  -114,  -114,  -114,    -7,     1,  -114,     2,  -114,
    -114,  -114,   268,   -27,  -114,  -114,     6,    54,    55,    57,
    -114,  -114,    56,  -114,    60,    62,  -114,     3,    18,  -114,
      81,    48,  -114,    41,    -7,    84,    63,  -114,   -37,   -37,
     -37,   204,    98,    96,   215,   111,  -114,    -7,  -114,    99,
    -114,  -114,  -114,    58,    73,  -114,    73,  -114,    73,  -114,
      65,  -114,    62,  -114,  -114,    25,  -114,  -114,  -114,  -114,
    -114,  -114,  -114,    80,  -114,  -114,  -114,     5,   114,  -114,
    -114,  -114,  -114,  -114,  -114,  -114,  -114,  -114,  -114,   -10,
     112,    71,   169,     3,  -114,     5,  -114,    91,  -114,  -114,
    -114,    85,  -114,   131,  -114,  -114,    93,   345,  -114,   249,
     249,   249,   136,   101,   101,   354,  -114,  -114,   105,   120,
    -114,  -114,   150,  -114,    -5,  -114,  -114,     3,   113,   124,
    -114,  -114,  -114,   385,  -114,   110,   249,   121,  -114,   176,
     177,   249,   249,  -114,  -114,  -114,  -114,   540,  -114,  -114,
    -114,  -114,  -114,  -114,  -114,  -114,  -114,   565,   585,   249,
     152,   170,  -114,  -114,    22,   249,  -114,  -114,  -114,  -114,
    -114,  -114,  -114,   416,   173,   249,   191,   665,  -114,  -114,
     249,   249,   249,   249,   249,   249,   249,   249,   249,   249,
     249,   249,   249,   249,   249,   249,  -114,  -114,   436,   249,
     101,   193,   187,  -114,  -114,  -114,  -114,   189,   605,  -114,
     161,   468,  -114,   381,   645,   665,   625,   625,    39,    39,
     171,   171,  -114,   676,   676,   676,   676,   676,   676,   394,
     290,   174,   249,  -114,  -114,  -114,  -114,   200,   249,  -114,
    -114,   488,   -18,   394,   170,  -114,   249,  -114,   520,  -114
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,    22,     0,     0,     0,     2,     0,     7,     3,
      27,    25,    38,    36,    37,     5,     0,    14,     0,    15,
      16,     6,     9,     0,     1,   111,     0,     0,     0,     0,
     137,   138,   112,   115,     0,     0,    26,     0,    22,     4,
       0,     0,     8,     0,    21,     0,    19,   117,     0,     0,
       0,     0,     0,     0,     0,     0,    23,     0,    10,     0,
      17,    20,    12,     0,   118,   119,   120,   121,   123,   122,
       0,   114,   113,   110,   133,     0,   125,   130,   129,   134,
     132,   124,   128,   135,   127,   131,   126,     0,     0,    11,
      18,   116,   140,   147,   146,   149,   148,   145,   150,     0,
     144,     0,     0,     0,    41,     0,    31,    32,    35,    29,
      13,     0,   139,     0,   136,   104,     0,     0,    40,     0,
       0,     0,     0,     0,     0,     0,    46,    42,     0,     0,
      63,    64,    56,    65,     0,    30,    28,     0,     0,     0,
     143,   105,    45,     0,   103,   108,     0,     0,    95,     0,
       0,     0,     0,    88,    87,    86,    97,     0,    90,    91,
      92,   101,    93,    94,    96,    98,   100,     0,     0,     0,
       0,     0,    39,    43,     0,     0,    50,    33,    34,   142,
     141,    44,   109,     0,   107,     0,     0,    72,    84,    47,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    48,    49,     0,     0,
       0,     0,     0,    58,    59,    60,    57,     0,    67,    99,
       0,     0,    85,    89,    68,    69,    70,    71,    79,    80,
      81,    82,    83,    73,    74,    75,    76,    77,    78,     0,
       0,     0,     0,    52,    51,   106,   102,    53,     0,    55,
      66,     0,   135,     0,    98,    62,     0,    54,     0,    61
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -114,  -114,  -114,   212,  -114,   128,   178,  -114,   199,  -114,
    -114,  -114,  -114,  -114,   135,   140,    -2,   141,   133,  -114,
    -113,  -114,  -114,  -114,  -114,    17,    74,   -89,   -86,  -114,
      77,    -1,  -114,  -114,   194,   206,   -43,     0,    -4,   -34,
     145,   151
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     5,     6,    21,    22,    23,    45,    46,     9,    10,
      11,    37,    38,   105,   106,   107,   108,   109,   125,   126,
     127,   128,   212,   129,   217,   235,   158,   159,   160,   161,
     162,   163,    52,    32,    33,    81,   164,    83,   165,   166,
      99,   100
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
       8,    15,   256,    35,    12,     7,    12,    34,   177,   111,
      82,    82,   173,   130,    39,   102,   131,   103,   -24,    85,
      85,   104,    43,    19,    20,   101,   144,    31,   130,   145,
     173,   131,    96,    44,     7,    55,   130,     7,   137,   131,
      59,    98,    24,    61,    65,    67,    69,    72,   112,    84,
      84,    34,    80,    80,   130,    36,    88,   131,   114,   211,
       7,    40,    41,    13,    58,    13,    47,    14,    96,    14,
      96,    97,    48,    49,    95,    50,    51,    98,    53,    98,
      54,    75,    25,    92,    26,    30,    31,    93,    94,    31,
     197,   198,   199,    27,    28,    29,     1,     7,   133,    57,
      62,   132,    60,     2,     3,     4,    63,    97,     7,    97,
      95,    73,    95,   133,    87,    89,   132,   138,    44,   170,
     171,   133,    43,   101,   132,    91,   247,   249,    74,    30,
     110,    30,   113,    31,   137,   178,   157,   167,   168,   133,
     257,    75,   132,     7,   169,    30,   174,    93,    94,    31,
     130,   130,    75,   131,   131,   141,    30,    76,    77,    78,
      31,    79,   175,   183,   130,    31,   176,   131,   187,   188,
     216,   179,   182,   215,   115,   116,    64,    66,    68,   117,
     118,     7,   180,   184,   185,   186,   208,    75,   209,   210,
     220,    30,   218,    93,    94,    31,   119,   120,   121,   122,
     222,   242,   221,   243,   123,   244,   241,   223,   224,   225,
     226,   227,   228,   229,   230,   231,   232,   233,   234,    70,
     236,   237,   238,   245,   199,   124,   240,     7,    27,    28,
      29,   253,   250,    31,    42,   133,   133,    56,   132,   132,
     135,    90,   252,   134,   254,    71,   136,    74,   213,   133,
     143,   214,   132,   144,   115,   116,   145,   146,   140,   251,
      86,     7,   139,   147,    30,     0,     0,     0,    31,     0,
       0,    75,     0,   258,     0,    30,     0,    77,    78,    31,
      79,   148,     0,    16,    17,     0,   149,   150,     0,     0,
       0,     0,     0,   151,    18,   115,   116,     0,     0,   152,
     117,     0,     7,     0,     0,    75,     0,     0,     0,    30,
     153,   154,   155,    31,   156,     0,     0,   119,   120,   121,
     122,     0,     0,     0,     0,   123,     0,     0,    19,    20,
     190,     0,     0,     0,     0,   191,   192,   193,   194,   195,
     196,   197,   198,   199,   200,   201,   248,   203,   204,   205,
     115,   116,     0,     0,    31,   117,   142,     7,     0,   115,
     116,     0,     0,     0,   117,   172,     7,     0,     0,     0,
       0,     0,   119,   120,   121,   122,     0,     0,     0,     0,
     123,   119,   120,   121,   122,     0,     0,     0,     0,   123,
     115,   116,     0,     0,     0,   117,   181,     7,     0,   115,
     116,   124,     0,     0,   117,     0,     7,     0,     0,    31,
     124,     0,   119,   120,   121,   122,     0,     0,    31,     0,
     123,   119,   120,   121,   122,   219,     0,     0,     0,   123,
     195,   196,   197,   198,   199,   200,   201,   202,   203,   204,
     205,   124,     0,     0,     0,   239,     0,     0,     0,    31,
     124,     0,     0,     0,     0,     0,   190,     0,    31,     0,
       0,   191,   192,   193,   194,   195,   196,   197,   198,   199,
     200,   201,   202,   203,   204,   205,   190,   246,     0,     0,
       0,   191,   192,   193,   194,   195,   196,   197,   198,   199,
     200,   201,   202,   203,   204,   205,     0,   255,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   190,     0,
       0,     0,     0,   191,   192,   193,   194,   195,   196,   197,
     198,   199,   200,   201,   202,   203,   204,   205,   190,   259,
       0,     0,     0,   191,   192,   193,   194,   195,   196,   197,
     198,   199,   200,   201,   202,   203,   204,   205,     0,     0,
       0,     0,     0,     0,     0,     0,   189,     0,     0,     0,
     190,     0,     0,     0,     0,   191,   192,   193,   194,   195,
     196,   197,   198,   199,   200,   201,   202,   203,   204,   205,
     190,   206,     0,     0,     0,   191,   192,   193,   194,   195,
     196,   197,   198,   199,   200,   201,   202,   203,   204,   205,
       0,   207,     0,     0,     0,   190,     0,     0,     0,     0,
     191,   192,   193,   194,   195,   196,   197,   198,   199,   200,
     201,   202,   203,   204,   205,   190,     0,     0,     0,     0,
     191,   192,   193,   194,   195,   196,   197,   198,   199,   200,
     201,   202,   203,   204,   205,   190,     0,     0,     0,     0,
     191,   192,   193,   194,   195,   196,   197,   198,   199,   200,
     201,   202,   203,   204,   205,   190,     0,     0,     0,     0,
     191,   192,   -25,   -25,   195,   196,   197,   198,   199,   200,
     201,   202,   203,   204,   205,   190,     0,     0,     0,     0,
       0,   192,     0,     0,   195,   196,   197,   198,   199,   200,
     201,   202,   203,   204,   205,   190,     0,     0,     0,     0,
       0,     0,     0,     0,   195,   196,   197,   198,   199,   200,
     201,   202,   203,   204,   205,   195,   196,   197,   198,   199,
     -25,   -25,   -25,   -25,   -25,   -25
};

static const yytype_int16 yycheck[] =
{
       1,     3,    20,     7,     1,    12,     1,     7,    13,    19,
      53,    54,   125,   102,    15,    10,   102,    12,     0,    53,
      54,    16,    49,    60,    61,    43,     4,    64,   117,     7,
     143,   117,    75,    60,    12,    37,   125,    12,    43,   125,
      41,    75,     0,    44,    48,    49,    50,    51,    58,    53,
      54,    51,    53,    54,   143,    39,    57,   143,   101,    37,
      12,    60,    60,    60,    16,    60,    60,    64,   111,    64,
     113,    75,    18,    18,    75,    18,    20,   111,    18,   113,
      18,    56,    13,    58,    15,    60,    64,    62,    63,    64,
      51,    52,    53,    24,    25,    26,    14,    12,   102,    18,
      16,   102,    61,    21,    22,    23,    43,   111,    12,   113,
     111,    13,   113,   117,     3,    16,   117,    32,    60,   123,
     124,   125,    49,    43,   125,    60,   239,   240,    32,    60,
      16,    60,    20,    64,    43,   137,   119,   120,   121,   143,
     253,    56,   143,    12,     8,    60,    41,    62,    63,    64,
     239,   240,    56,   239,   240,    62,    60,    61,    62,    63,
      64,    65,    42,   146,   253,    64,    16,   253,   151,   152,
     174,    58,    62,   174,     5,     6,    48,    49,    50,    10,
      11,    12,    58,    62,     8,     8,   169,    56,    36,    19,
      17,    60,   175,    62,    63,    64,    27,    28,    29,    30,
       9,     8,   185,    16,    35,    16,   210,   190,   191,   192,
     193,   194,   195,   196,   197,   198,   199,   200,   201,    15,
     203,   204,   205,    62,    53,    56,   209,    12,    24,    25,
      26,    31,    58,    64,    22,   239,   240,    38,   239,   240,
     105,    63,   242,   103,   248,    51,   105,    32,   174,   253,
     117,   174,   253,     4,     5,     6,     7,     8,   113,   242,
      54,    12,   111,    14,    60,    -1,    -1,    -1,    64,    -1,
      -1,    56,    -1,   256,    -1,    60,    -1,    62,    63,    64,
      65,    32,    -1,    15,    16,    -1,    37,    38,    -1,    -1,
      -1,    -1,    -1,    44,    26,     5,     6,    -1,    -1,    50,
      10,    -1,    12,    -1,    -1,    56,    -1,    -1,    -1,    60,
      61,    62,    63,    64,    65,    -1,    -1,    27,    28,    29,
      30,    -1,    -1,    -1,    -1,    35,    -1,    -1,    60,    61,
      40,    -1,    -1,    -1,    -1,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
       5,     6,    -1,    -1,    64,    10,    11,    12,    -1,     5,
       6,    -1,    -1,    -1,    10,    11,    12,    -1,    -1,    -1,
      -1,    -1,    27,    28,    29,    30,    -1,    -1,    -1,    -1,
      35,    27,    28,    29,    30,    -1,    -1,    -1,    -1,    35,
       5,     6,    -1,    -1,    -1,    10,    11,    12,    -1,     5,
       6,    56,    -1,    -1,    10,    -1,    12,    -1,    -1,    64,
      56,    -1,    27,    28,    29,    30,    -1,    -1,    64,    -1,
      35,    27,    28,    29,    30,     9,    -1,    -1,    -1,    35,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    56,    -1,    -1,    -1,     9,    -1,    -1,    -1,    64,
      56,    -1,    -1,    -1,    -1,    -1,    40,    -1,    64,    -1,
      -1,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    40,     9,    -1,    -1,
      -1,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    -1,     9,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    40,    -1,
      -1,    -1,    -1,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    40,     9,
      -1,    -1,    -1,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    16,    -1,    -1,    -1,
      40,    -1,    -1,    -1,    -1,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      40,    16,    -1,    -1,    -1,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      -1,    16,    -1,    -1,    -1,    40,    -1,    -1,    -1,    -1,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    40,    -1,    -1,    -1,    -1,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    40,    -1,    -1,    -1,    -1,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    40,    -1,    -1,    -1,    -1,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    40,    -1,    -1,    -1,    -1,
      -1,    46,    -1,    -1,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    40,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    14,    21,    22,    23,    69,    70,    12,    99,    76,
      77,    78,     1,    60,    64,    84,    15,    16,    26,    60,
      61,    71,    72,    73,     0,    13,    15,    24,    25,    26,
      60,    64,   101,   102,   105,   106,    39,    79,    80,    99,
      60,    60,    71,    49,    60,    74,    75,    60,    18,    18,
      18,    20,   100,    18,    18,    84,    76,    18,    16,    99,
      61,    99,    16,    43,    73,   106,    73,   106,    73,   106,
      15,   102,   106,    13,    32,    56,    61,    62,    63,    65,
      99,   103,   104,   105,   106,   107,   103,     3,    99,    16,
      74,    60,    58,    62,    63,    99,   104,   106,   107,   108,
     109,    43,    10,    12,    16,    81,    82,    83,    84,    85,
      16,    19,    58,    20,   104,     5,     6,    10,    11,    27,
      28,    29,    30,    35,    56,    86,    87,    88,    89,    91,
      95,    96,    99,   106,    83,    82,    85,    43,    32,   109,
     108,    62,    11,    86,     4,     7,     8,    14,    32,    37,
      38,    44,    50,    61,    62,    63,    65,    93,    94,    95,
      96,    97,    98,    99,   104,   106,   107,    93,    93,     8,
     106,   106,    11,    88,    41,    42,    16,    13,    84,    58,
      58,    11,    62,    93,    62,     8,     8,    93,    93,    16,
      40,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    16,    16,    93,    36,
      19,    37,    90,    94,    98,    99,   106,    92,    93,     9,
      17,    93,     9,    93,    93,    93,    93,    93,    93,    93,
      93,    93,    93,    93,    93,    93,    93,    93,    93,     9,
      93,   106,     8,    16,    16,    62,     9,    88,    56,    88,
      58,    93,   105,    31,   106,     9,    20,    88,    93,     9
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    68,    69,    70,    70,    70,    70,    70,    71,    71,
      72,    72,    72,    72,    72,    73,    73,    73,    74,    74,
      75,    75,    77,    76,    78,    76,    79,    79,    80,    80,
      81,    81,    82,    82,    83,    83,    84,    84,    84,    85,
      85,    85,    86,    86,    87,    87,    88,    88,    88,    88,
      88,    88,    88,    88,    88,    88,    89,    90,    90,    90,
      90,    90,    90,    91,    91,    91,    91,    92,    93,    93,
      93,    93,    93,    93,    93,    93,    93,    93,    93,    93,
      93,    93,    93,    93,    93,    93,    93,    93,    93,    93,
      93,    93,    93,    93,    93,    93,    93,    93,    93,    93,
      93,    93,    93,    94,    95,    96,    97,    97,    98,    98,
      99,    99,   100,   100,   101,   101,   101,   101,   102,   102,
     102,   102,   102,   102,   102,   102,   102,   103,   103,   103,
     103,   103,   103,   103,   103,   104,   104,   105,   106,   107,
     107,   107,   107,   108,   108,   109,   109,   109,   109,   109,
     109
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     3,     2,     2,     2,     2,     1,
       3,     4,     3,     5,     1,     1,     1,     3,     3,     1,
       2,     1,     0,     3,     0,     1,     1,     0,     5,     4,
       2,     1,     1,     3,     3,     1,     1,     1,     1,     3,
       2,     1,     1,     2,     3,     2,     1,     3,     3,     3,
       2,     4,     4,     5,     7,     5,     1,     1,     1,     1,
       1,     6,     4,     1,     1,     1,     5,     1,     3,     3,
       3,     3,     2,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     2,     3,     1,     1,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       1,     1,     4,     1,     1,     2,     4,     2,     1,     2,
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
#line 162 "src/rulesyacc.y"
              {
	  DBUGPRT("axiom done...");
	  YYACCEPT;
	}
#line 1537 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 3: /* begin: TOKEN_RULES rules  */
#line 168 "src/rulesyacc.y"
                          {
	  DBUGPRT("begin grammar");
	}
#line 1545 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 4: /* begin: TOKEN_INPUT term features  */
#line 172 "src/rulesyacc.y"
                                   {
	  DBUGPRT("begin input");
	  parser.setStartTerm((yyvsp[-1].integer_slot));
	  (*(yyvsp[0].features_slot))->renameVariables((*(yyvsp[0].features_slot))->getId());
	  parser.setStartFeatures(*(yyvsp[0].features_slot));
	  free((yyvsp[0].features_slot));
	}
#line 1557 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 5: /* begin: TOKEN_INPUT term  */
#line 180 "src/rulesyacc.y"
                          {
	  DBUGPRT("begin input");
	  parser.setStartTerm((yyvsp[0].integer_slot));
	  parser.setStartFeatures(Features::create());
	 }
#line 1567 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 6: /* begin: TOKEN_LEXICON dictionary  */
#line 186 "src/rulesyacc.y"
                                  {
	  DBUGPRT("begin lexicon");
	  //CERR_LINE;
	  //parser.printCacheLexicon(std::cerr);
	}
#line 1577 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 7: /* begin: TOKEN_DASH features  */
#line 193 "src/rulesyacc.y"
        {
	  DBUGPRT("begin features");
	  parser.setLocalFeatures(*(yyvsp[0].features_slot));
	  free((yyvsp[0].features_slot));
	}
#line 1587 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 8: /* dictionary: dictionary_line dictionary  */
#line 200 "src/rulesyacc.y"
                                   {
	  DBUGPRT("dictionary");
	}
#line 1595 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 9: /* dictionary: dictionary_line  */
#line 204 "src/rulesyacc.y"
                         {
	  DBUGPRT("dictionary");
	 }
#line 1603 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 10: /* dictionary_line: TOKEN_FORM TOKEN_IDENTIFIER TOKEN_SEMI  */
#line 211 "src/rulesyacc.y"
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
#line 1631 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 11: /* dictionary_line: TOKEN_FORM TOKEN_IDENTIFIER features TOKEN_SEMI  */
#line 236 "src/rulesyacc.y"
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
#line 1660 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 12: /* dictionary_line: stringOrIdentifier lexical_entries TOKEN_SEMI  */
#line 263 "src/rulesyacc.y"
        {
	  DBUGPRT("dictionary_line");
	  for (auto entry = (*(yyvsp[-1].entries_slot))->begin() ; entry != (*(yyvsp[-1].entries_slot))->end() ; ++entry) {
	    (*entry)->setForm(*(yyvsp[-2].string_slot));
	    entriesPtr lp;
	    Parser::entries_map* predToEntries;
	    //std::cerr << entry->getCode() << std::endl;
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
#line 1691 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 13: /* dictionary_line: TOKEN_AROBASE TOKEN_IDENTIFIER TOKEN_COLON features TOKEN_SEMI  */
#line 292 "src/rulesyacc.y"
        {
	  DBUGPRT("dictionary_line");
	  parser.addMacros(*(yyvsp[-3].string_slot), *(yyvsp[-1].features_slot));
	  free((yyvsp[-3].string_slot));
	  free((yyvsp[-1].features_slot));
	}
#line 1702 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 14: /* dictionary_line: TOKEN_SEMI  */
#line 300 "src/rulesyacc.y"
        {
	  DBUGPRT("dictionary_line");
	}
#line 1710 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 15: /* stringOrIdentifier: TOKEN_IDENTIFIER  */
#line 305 "src/rulesyacc.y"
                         {
	  DBUGPRT("stringOrIdentifier");
	  (yyval.string_slot) = (yyvsp[0].string_slot);
	}
#line 1719 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 16: /* stringOrIdentifier: TOKEN_STRING  */
#line 310 "src/rulesyacc.y"
                      {
	  DBUGPRT("stringOrIdentifier");
	  (yyval.string_slot) = (yyvsp[0].string_slot);
	 }
#line 1728 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 17: /* stringOrIdentifier: stringOrIdentifier TOKEN_PLUS TOKEN_STRING  */
#line 315 "src/rulesyacc.y"
                                                    {
	  DBUGPRT("string");
	  (yyval.string_slot) = (yyvsp[-2].string_slot);
	  *(yyval.string_slot) += *(yyvsp[0].string_slot);
	 }
#line 1738 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 18: /* lexical_entries: lexical_entry TOKEN_PIPE lexical_entries  */
#line 323 "src/rulesyacc.y"
        {
	  DBUGPRT("lexical_entries");
	  (yyval.entries_slot) = (yyvsp[0].entries_slot);
	  (*(yyval.entries_slot))->add(*(yyvsp[-2].entry_slot));
	  free((yyvsp[-2].entry_slot));
	}
#line 1749 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 19: /* lexical_entries: lexical_entry  */
#line 330 "src/rulesyacc.y"
                       {
	  DBUGPRT("lexical_entries");
	  (yyval.entries_slot) = new entriesPtr(Entries::create(*(yyvsp[0].entry_slot)));
	  free((yyvsp[0].entry_slot));
	 }
#line 1759 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 20: /* lexical_entry: TOKEN_IDENTIFIER features  */
#line 339 "src/rulesyacc.y"
        {
	  DBUGPRT("lexical_entry");
	  unsigned int pred = (*(yyvsp[0].features_slot))->assignPred();
	  (yyval.entry_slot) = new entryPtr(Entry::create(Vartable::stringToCode(*(yyvsp[-1].string_slot)), pred, std::string(), *(yyvsp[0].features_slot)));
	  free((yyvsp[-1].string_slot));
	  free((yyvsp[0].features_slot));
	}
#line 1771 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 21: /* lexical_entry: TOKEN_IDENTIFIER  */
#line 348 "src/rulesyacc.y"
        {
	  DBUGPRT("lexical_entry");
	  (yyval.entry_slot) = new entryPtr(Entry::create(Vartable::stringToCode(*(yyvsp[0].string_slot)), UINT_MAX, std::string(), Features::create()));
	  free((yyvsp[0].string_slot));
	}
#line 1781 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 22: /* $@1: %empty  */
#line 358 "src/rulesyacc.y"
        {headLineno = ruleslineno;}
#line 1787 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 23: /* rules: $@1 rule rules  */
#line 359 "src/rulesyacc.y"
        {
	  DBUGPRT("rules");
	}
#line 1795 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 24: /* $@2: %empty  */
#line 363 "src/rulesyacc.y"
         {headLineno = ruleslineno;}
#line 1801 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 25: /* rules: $@2  */
#line 364 "src/rulesyacc.y"
        {
	  DBUGPRT("rules");
	}
#line 1809 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 26: /* pref_rule: TOKEN_TRACE  */
#line 370 "src/rulesyacc.y"
        {
	  DBUGPRT("pref_rule");
	  headTrace = true;
	}
#line 1818 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 27: /* pref_rule: %empty  */
#line 375 "src/rulesyacc.y"
                      {
	  DBUGPRT("pref_rule");
	  headTrace = false;
	}
#line 1827 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 28: /* rule: pref_rule term TOKEN_RIGHTARROW terms_vector structure_statement  */
#line 382 "src/rulesyacc.y"
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
#line 1845 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 29: /* rule: pref_rule term TOKEN_RIGHTARROW structure_statement  */
#line 397 "src/rulesyacc.y"
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
#line 1862 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 30: /* terms_vector: terms_vector terms  */
#line 411 "src/rulesyacc.y"
                           {
	  DBUGPRT("term_vector");
	  (yyval.vector_terms_slot)=(yyvsp[-1].vector_terms_slot);
	  (yyval.vector_terms_slot)->push_back(*(yyvsp[0].terms_slot));
	}
#line 1872 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 31: /* terms_vector: terms  */
#line 417 "src/rulesyacc.y"
               {
	  DBUGPRT("term_vector");
	  (yyval.vector_terms_slot) = new std::vector< termsPtr >;
	  (yyval.vector_terms_slot)->push_back(*(yyvsp[0].terms_slot));
	}
#line 1882 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 32: /* terms: terms_disj  */
#line 424 "src/rulesyacc.y"
                   {
	  DBUGPRT("term");
	  (yyval.terms_slot)=(yyvsp[0].terms_slot);
	}
#line 1891 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 33: /* terms: TOKEN_LBRACKET terms_disj TOKEN_RBRACKET  */
#line 429 "src/rulesyacc.y"
                                                  {
	  DBUGPRT("term");
	  (yyval.terms_slot) = (yyvsp[-1].terms_slot);
	  (*(yyval.terms_slot))->setOptional();
	}
#line 1901 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 34: /* terms_disj: terms_disj TOKEN_PIPE term  */
#line 437 "src/rulesyacc.y"
        {
	  DBUGPRT("term_disj");
	  (yyval.terms_slot) = (yyvsp[-2].terms_slot);
	  (*(yyval.terms_slot))->push_back((yyvsp[0].integer_slot));
	}
#line 1911 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 35: /* terms_disj: term  */
#line 444 "src/rulesyacc.y"
        {
	  DBUGPRT("term_disj");
	  (yyval.terms_slot) = new termsPtr(Terms::create((yyvsp[0].integer_slot)));
	}
#line 1920 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 36: /* term: TOKEN_IDENTIFIER  */
#line 451 "src/rulesyacc.y"
        {
	  DBUGPRT("term_id");
	  (yyval.integer_slot) = Vartable::stringToCode(*(yyvsp[0].string_slot));
	  free((yyvsp[0].string_slot));
	}
#line 1930 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 37: /* term: TOKEN_VARIABLE  */
#line 458 "src/rulesyacc.y"
        {
	  DBUGPRT("term_id");
	  (yyval.integer_slot) = Vartable::stringToCode(*(yyvsp[0].string_slot));
	  free((yyvsp[0].string_slot));
	}
#line 1940 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 38: /* term: error  */
#line 465 "src/rulesyacc.y"
        {
	  YYABORT;
	}
#line 1948 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 39: /* structure_statement: TOKEN_LBRACE list_statement TOKEN_RBRACE  */
#line 474 "src/rulesyacc.y"
        {
	  DBUGPRT("structure_statement");
	  (yyval.statements_slot)=(yyvsp[-1].statements_slot);
	}
#line 1957 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 40: /* structure_statement: TOKEN_LBRACE TOKEN_RBRACE  */
#line 480 "src/rulesyacc.y"
        {
	  (yyval.statements_slot)=NULL;
	}
#line 1965 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 41: /* structure_statement: TOKEN_SEMI  */
#line 485 "src/rulesyacc.y"
        {
	  (yyval.statements_slot)=NULL;
	}
#line 1973 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 42: /* list_statement: statement  */
#line 491 "src/rulesyacc.y"
        {
	  DBUGPRT("list_statement");
	  (yyval.statements_slot) = new statementsPtr(Statements::create());
	  (*(yyval.statements_slot))->addStatement(*(yyvsp[0].statement_slot));
	  free((yyvsp[0].statement_slot));
	}
#line 1984 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 43: /* list_statement: list_statement statement  */
#line 498 "src/rulesyacc.y"
                                  {
	  DBUGPRT("list_statement");
	  (yyval.statements_slot) = (yyvsp[-1].statements_slot);
	  (*(yyval.statements_slot))->addStatement(*(yyvsp[0].statement_slot));
	  free((yyvsp[0].statement_slot));
	}
#line 1995 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 44: /* statements: TOKEN_LBRACE list_statement TOKEN_RBRACE  */
#line 507 "src/rulesyacc.y"
        {
	  DBUGPRT("statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::STMS, *(yyvsp[-1].statements_slot)));
	  free((yyvsp[-1].statements_slot));
	}
#line 2005 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 45: /* statements: TOKEN_LBRACE TOKEN_RBRACE  */
#line 514 "src/rulesyacc.y"
        {
	  DBUGPRT("statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::STMS, Statements::create()));
	}
#line 2014 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 46: /* statement: statements  */
#line 520 "src/rulesyacc.y"
                   {
	  DBUGPRT("statement");
	  (yyval.statement_slot)=(yyvsp[0].statement_slot);
	 }
#line 2023 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 47: /* statement: TOKEN_ATTEST expression_statement TOKEN_SEMI  */
#line 525 "src/rulesyacc.y"
                                                      {
	  DBUGPRT("statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::ATTEST, *(yyvsp[-1].statement_slot)));
	  free((yyvsp[-1].statement_slot));
	}
#line 2033 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 48: /* statement: TOKEN_PRINT expression_statement TOKEN_SEMI  */
#line 531 "src/rulesyacc.y"
                                                     {
	  DBUGPRT("statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::PRINT, *(yyvsp[-1].statement_slot)));
	  free((yyvsp[-1].statement_slot));
	}
#line 2043 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 49: /* statement: TOKEN_PRINTLN expression_statement TOKEN_SEMI  */
#line 537 "src/rulesyacc.y"
                                                       {
	  DBUGPRT("statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::PRINTLN, *(yyvsp[-1].statement_slot)));
	  free((yyvsp[-1].statement_slot));
	}
#line 2053 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 50: /* statement: features TOKEN_SEMI  */
#line 543 "src/rulesyacc.y"
                             {
	  DBUGPRT("statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::GUARD, *(yyvsp[-1].features_slot)));
	  free((yyvsp[-1].features_slot));
	}
#line 2063 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 51: /* statement: left_hand_side_aff_statement TOKEN_AFF right_hand_side_aff_statement TOKEN_SEMI  */
#line 549 "src/rulesyacc.y"
                                                                                         {
	  DBUGPRT("statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::AFF, *(yyvsp[-3].statement_slot), *(yyvsp[-1].statement_slot)));
	  // <X, …> = <…>
	  // <X, …> = $X
	  if (((*(yyvsp[-3].statement_slot))->isList()) 
	  		&& (((*(yyvsp[-1].statement_slot))->isList())
					||((*(yyvsp[-1].statement_slot))->isVariable()))) {
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
		      ||((*(yyvsp[-1].statement_slot))->isList())
		      ||((*(yyvsp[-1].statement_slot))->isFeatures())
		      ||((*(yyvsp[-1].statement_slot))->isUp())
		      ||((*(yyvsp[-1].statement_slot))->isUnif())
		      ||((*(yyvsp[-1].statement_slot))->isDown2())
		      ||((*(yyvsp[-1].statement_slot))->isNumber())
		      ||((*(yyvsp[-1].statement_slot))->isFct())
		      ||((*(yyvsp[-1].statement_slot))->isSearch())));
	  else {
	    yyerror((char*)"syntax error");
	  }
	  free((yyvsp[-3].statement_slot));
	  free((yyvsp[-1].statement_slot));
	}
#line 2127 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 52: /* statement: left_hand_side_subset_statement TOKEN_SUBSUME right_hand_side_subset_statement TOKEN_SEMI  */
#line 609 "src/rulesyacc.y"
                                                                                                   {
	  DBUGPRT("statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::SUBSUME, (*(yyvsp[-3].statement_slot)), (*(yyvsp[-1].statement_slot))));
	  // […] ⊂ ↑
	  // […] ⊂ ⇓j
	  // […] ⊂ $X
	  // […] ⊂ search
	  if (((*(yyvsp[-3].statement_slot))->isFeatures()) 
	  		&& (((*(yyvsp[-1].statement_slot))->isUp())
					||((*(yyvsp[-1].statement_slot))->isDown2())
					||((*(yyvsp[-1].statement_slot))->isVariable())
					||((*(yyvsp[-1].statement_slot))->isSearch())))
	    ;
	  else
	    yyerror((char* )"syntax error");
	  free((yyvsp[-3].statement_slot));
	  free((yyvsp[-1].statement_slot));
	}
#line 2150 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 53: /* statement: TOKEN_IF TOKEN_LPAR expression_statement TOKEN_RPAR statement  */
#line 628 "src/rulesyacc.y"
                                                                                          {
	  DBUGPRT("statement");
	  statementPtr stm;
	  if (!(*(yyvsp[0].statement_slot))->isStms()) {
	    statementsPtr stms = Statements::create();
	    stms->addStatement(*(yyvsp[0].statement_slot));
	    stm = Statement::create(ruleslineno, Statement::STMS, stms);
	  }
	  else
	    stm = *(yyvsp[0].statement_slot);
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno,
						Statement::IF,
						  *(yyvsp[-2].statement_slot),
						  Statement::create(ruleslineno, Statement::THENELSE, stm, statementPtr())));
	  free((yyvsp[-2].statement_slot));
	  free((yyvsp[0].statement_slot));
	}
#line 2172 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 54: /* statement: TOKEN_IF TOKEN_LPAR expression_statement TOKEN_RPAR statement TOKEN_ELSE statement  */
#line 646 "src/rulesyacc.y"
                                                                                            {
	  DBUGPRT("statement");
	  statementPtr stm1;
	  statementPtr stm2;
	  if (!(*(yyvsp[-2].statement_slot))->isStms()) {
	    statementsPtr stms = Statements::create();
	    stms->addStatement(*(yyvsp[-2].statement_slot));
	    stm1 = Statement::create(ruleslineno, Statement::STMS, stms);
	  }
	  else
	    stm1 = *(yyvsp[-2].statement_slot);
	  if (!(*(yyvsp[0].statement_slot))->isStms()) {
	    statementsPtr stms = Statements::create();
	    stms->addStatement(*(yyvsp[0].statement_slot));
	    stm2 = Statement::create(ruleslineno, Statement::STMS, stms);
	  }
	  else
	    stm2 = *(yyvsp[0].statement_slot);
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno,
						  Statement::IF,
						  (*(yyvsp[-4].statement_slot)),
						  Statement::create(ruleslineno, Statement::THENELSE, stm1, stm2)));
	  free((yyvsp[-4].statement_slot));
	  free((yyvsp[-2].statement_slot));
	  free((yyvsp[0].statement_slot));
	}
#line 2203 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 55: /* statement: TOKEN_FOREACH variable TOKEN_IN expression_statement statement  */
#line 673 "src/rulesyacc.y"
                                                                        {
	  DBUGPRT("statement");
	  statementPtr stm;
	  if (!(*(yyvsp[0].statement_slot))->isStms()) {
	    statementsPtr stms = Statements::create();
	    stms->addStatement(*(yyvsp[0].statement_slot));
	    stm = Statement::create(ruleslineno, Statement::STMS, stms);
	  }
	  else
	    stm = *(yyvsp[0].statement_slot);
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno,
						  Statement::FOREACH,
						  Statement::create(ruleslineno, Statement::VARIABLE, (*(yyvsp[-3].bits_slot))),
						  Statement::create(ruleslineno, Statement::IN, (*(yyvsp[-1].statement_slot)), stm)));
	  free((yyvsp[-3].bits_slot));
	  free((yyvsp[-1].statement_slot));
	  free((yyvsp[0].statement_slot));
	}
#line 2226 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 56: /* left_hand_side_subset_statement: features  */
#line 693 "src/rulesyacc.y"
                 {
	  DBUGPRT("left_hand_side_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::FEATURES, *(yyvsp[0].features_slot)));
	  free((yyvsp[0].features_slot));
	}
#line 2236 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 57: /* right_hand_side_subset_statement: variable  */
#line 700 "src/rulesyacc.y"
                 {
	  DBUGPRT("right_hand_side_subset_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::VARIABLE, *(yyvsp[0].bits_slot)));
	  free((yyvsp[0].bits_slot));
	}
#line 2246 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 58: /* right_hand_side_subset_statement: up  */
#line 706 "src/rulesyacc.y"
            {
	  DBUGPRT("right_hand_side_subset_statement");
	  (yyval.statement_slot)=(yyvsp[0].statement_slot);
	}
#line 2255 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 59: /* right_hand_side_subset_statement: downdouble  */
#line 711 "src/rulesyacc.y"
                    {
	  DBUGPRT("right_hand_side_subset_statement");
	  (yyval.statement_slot)=(yyvsp[0].statement_slot);
	}
#line 2264 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 60: /* right_hand_side_subset_statement: features  */
#line 716 "src/rulesyacc.y"
                  {
	  DBUGPRT("right_hand_side_subset_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::FEATURES, *(yyvsp[0].features_slot)));
	  free((yyvsp[0].features_slot));
	}
#line 2274 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 61: /* right_hand_side_subset_statement: TOKEN_SEARCH TOKEN_LPAR identifier TOKEN_COMMA expression_statement TOKEN_RPAR  */
#line 722 "src/rulesyacc.y"
                                                                                         {
	  DBUGPRT("right_hand_side_subset_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno,
						  Statement::SEARCH,
						  *(yyvsp[-3].bits_slot),
						  *(yyvsp[-1].statement_slot)));
	  free((yyvsp[-3].bits_slot));
	  free((yyvsp[-1].statement_slot));
	 }
#line 2288 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 62: /* right_hand_side_subset_statement: TOKEN_SEARCH TOKEN_LPAR expression_statement TOKEN_RPAR  */
#line 732 "src/rulesyacc.y"
                                                             {
 	  DBUGPRT("expression_statement");
 	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno,
 						  Statement::SEARCH,
 						  *(yyvsp[-1].statement_slot)));
 	  free((yyvsp[-1].statement_slot));
 	 }
#line 2300 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 63: /* left_hand_side_aff_statement: updouble  */
#line 741 "src/rulesyacc.y"
                 {
	  DBUGPRT("left_hand_side_statement");
	  (yyval.statement_slot)=(yyvsp[0].statement_slot);
	}
#line 2309 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 64: /* left_hand_side_aff_statement: down  */
#line 746 "src/rulesyacc.y"
              {
	  DBUGPRT("left_hand_side_statement");
	  (yyval.statement_slot)=(yyvsp[0].statement_slot);
	}
#line 2318 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 65: /* left_hand_side_aff_statement: variable  */
#line 751 "src/rulesyacc.y"
                  {
	  DBUGPRT("left_hand_side_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::VARIABLE, *(yyvsp[0].bits_slot)));
	  free((yyvsp[0].bits_slot));
	 }
#line 2328 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 66: /* left_hand_side_aff_statement: TOKEN_LT variable TOKEN_DOUBLECOLON variable TOKEN_GT  */
#line 758 "src/rulesyacc.y"
        {
	  DBUGPRT("left_hand_side_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::LIST,
						List::create(List::create(Value::create(Value::_VARIABLE, *(yyvsp[-3].bits_slot))),
							     List::create(Value::create(Value::_VARIABLE, *(yyvsp[-1].bits_slot))))));
	  free((yyvsp[-3].bits_slot));
	  free((yyvsp[-1].bits_slot));
	}
#line 2341 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 67: /* right_hand_side_aff_statement: expression_statement  */
#line 768 "src/rulesyacc.y"
                             {
	  DBUGPRT("right_hand_side_statement");
	  (yyval.statement_slot)=(yyvsp[0].statement_slot);
	}
#line 2350 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 68: /* expression_statement: expression_statement TOKEN_OR expression_statement  */
#line 777 "src/rulesyacc.y"
                                                           {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::FCT, Statement::OR, (*(yyvsp[-2].statement_slot)), (*(yyvsp[0].statement_slot))));
	  free((yyvsp[-2].statement_slot));
	  free((yyvsp[0].statement_slot));
	}
#line 2361 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 69: /* expression_statement: expression_statement TOKEN_AND expression_statement  */
#line 784 "src/rulesyacc.y"
                                                             {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::FCT, Statement::AND, (*(yyvsp[-2].statement_slot)), (*(yyvsp[0].statement_slot))));
	  free((yyvsp[-2].statement_slot));
	  free((yyvsp[0].statement_slot));
	}
#line 2372 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 70: /* expression_statement: expression_statement TOKEN_IMPLICATION expression_statement  */
#line 791 "src/rulesyacc.y"
                                                                     {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::FCT, Statement::OR, Statement::create(ruleslineno, Statement::FCT, Statement::NOT, (*(yyvsp[-2].statement_slot))), (*(yyvsp[0].statement_slot))));
	  free((yyvsp[-2].statement_slot));
	  free((yyvsp[0].statement_slot));
	}
#line 2383 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 71: /* expression_statement: expression_statement TOKEN_EQUIV expression_statement  */
#line 798 "src/rulesyacc.y"
                                                               {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::FCT, Statement::AND,
						                    Statement::create(ruleslineno, Statement::FCT, Statement::OR,
								                Statement::create(ruleslineno, Statement::FCT, Statement::NOT, (*(yyvsp[-2].statement_slot))),
								                (*(yyvsp[0].statement_slot))),
						                    Statement::create(ruleslineno, Statement::FCT, Statement::OR,
								                (*(yyvsp[-2].statement_slot)),
								                Statement::create(ruleslineno, Statement::FCT, Statement::NOT, (*(yyvsp[0].statement_slot))))));
	  free((yyvsp[-2].statement_slot));
	  free((yyvsp[0].statement_slot));
	}
#line 2400 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 72: /* expression_statement: TOKEN_NOT expression_statement  */
#line 811 "src/rulesyacc.y"
                                        {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::FCT, Statement::NOT, (*(yyvsp[0].statement_slot))));
	  free((yyvsp[0].statement_slot));
	}
#line 2410 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 73: /* expression_statement: expression_statement TOKEN_EQUAL expression_statement  */
#line 817 "src/rulesyacc.y"
                                                               {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::FCT, Statement::EQ, (*(yyvsp[-2].statement_slot)), (*(yyvsp[0].statement_slot))));
	  free((yyvsp[-2].statement_slot));
	  free((yyvsp[0].statement_slot));
	}
#line 2421 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 74: /* expression_statement: expression_statement TOKEN_DIFF expression_statement  */
#line 824 "src/rulesyacc.y"
                                                              {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::FCT, Statement::DIFF, (*(yyvsp[-2].statement_slot)), (*(yyvsp[0].statement_slot))));
	  free((yyvsp[-2].statement_slot));
	  free((yyvsp[0].statement_slot));
	}
#line 2432 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 75: /* expression_statement: expression_statement TOKEN_LT expression_statement  */
#line 831 "src/rulesyacc.y"
                                                            {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::FCT, Statement::LT, (*(yyvsp[-2].statement_slot)), (*(yyvsp[0].statement_slot))));
	  free((yyvsp[-2].statement_slot));
	  free((yyvsp[0].statement_slot));
	}
#line 2443 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 76: /* expression_statement: expression_statement TOKEN_LE expression_statement  */
#line 838 "src/rulesyacc.y"
                                                            {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::FCT, Statement::LE, (*(yyvsp[-2].statement_slot)), (*(yyvsp[0].statement_slot))));
	  free((yyvsp[-2].statement_slot));
	  free((yyvsp[0].statement_slot));
	}
#line 2454 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 77: /* expression_statement: expression_statement TOKEN_GT expression_statement  */
#line 845 "src/rulesyacc.y"
                                                            {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::FCT, Statement::GT, (*(yyvsp[-2].statement_slot)), (*(yyvsp[0].statement_slot))));
	  free((yyvsp[-2].statement_slot));
	  free((yyvsp[0].statement_slot));
	}
#line 2465 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 78: /* expression_statement: expression_statement TOKEN_GE expression_statement  */
#line 852 "src/rulesyacc.y"
                                                            {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::FCT, Statement::GE, (*(yyvsp[-2].statement_slot)), (*(yyvsp[0].statement_slot))));
	  free((yyvsp[-2].statement_slot));
	  free((yyvsp[0].statement_slot));
	}
#line 2476 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 79: /* expression_statement: expression_statement TOKEN_PLUS expression_statement  */
#line 863 "src/rulesyacc.y"
        {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::FCT, Statement::PLUS, (*(yyvsp[-2].statement_slot)), (*(yyvsp[0].statement_slot))));
	  free((yyvsp[-2].statement_slot));
	  free((yyvsp[0].statement_slot));
	}
#line 2487 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 80: /* expression_statement: expression_statement TOKEN_MINUS expression_statement  */
#line 871 "src/rulesyacc.y"
        {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::FCT, Statement::MINUS, (*(yyvsp[-2].statement_slot)), (*(yyvsp[0].statement_slot))));
	  free((yyvsp[-2].statement_slot));
	  free((yyvsp[0].statement_slot));
	}
#line 2498 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 81: /* expression_statement: expression_statement TOKEN_TIMES expression_statement  */
#line 879 "src/rulesyacc.y"
        {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::FCT, Statement::TIMES, (*(yyvsp[-2].statement_slot)), (*(yyvsp[0].statement_slot))));
	  free((yyvsp[-2].statement_slot));
	  free((yyvsp[0].statement_slot));
	}
#line 2509 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 82: /* expression_statement: expression_statement TOKEN_DIVIDE expression_statement  */
#line 887 "src/rulesyacc.y"
        {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::FCT, Statement::DIVIDE, (*(yyvsp[-2].statement_slot)), (*(yyvsp[0].statement_slot))));
	  free((yyvsp[-2].statement_slot));
	  free((yyvsp[0].statement_slot));
	}
#line 2520 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 83: /* expression_statement: expression_statement TOKEN_MODULO expression_statement  */
#line 895 "src/rulesyacc.y"
        {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::FCT, Statement::MODULO, (*(yyvsp[-2].statement_slot)), (*(yyvsp[0].statement_slot))));
	  free((yyvsp[-2].statement_slot));
	  free((yyvsp[0].statement_slot));
	}
#line 2531 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 84: /* expression_statement: TOKEN_MINUS expression_statement  */
#line 903 "src/rulesyacc.y"
        {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::FCT, Statement::MINUS_U, (*(yyvsp[0].statement_slot)), statementPtr()));
	  free((yyvsp[0].statement_slot));
	}
#line 2541 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 85: /* expression_statement: TOKEN_RAND TOKEN_LPAR TOKEN_RPAR  */
#line 910 "src/rulesyacc.y"
        {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::FCT, Statement::RAND));
	}
#line 2550 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 86: /* expression_statement: TOKEN_DOUBLE  */
#line 916 "src/rulesyacc.y"
        {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::NUMBER, (yyvsp[0].double_slot)));
	}
#line 2559 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 87: /* expression_statement: TOKEN_INTEGER  */
#line 922 "src/rulesyacc.y"
        {
	  DBUGPRT("expression_statement");
 	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::NUMBER, (double)(yyvsp[0].integer_slot)));
	}
#line 2568 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 88: /* expression_statement: TOKEN_STRING  */
#line 928 "src/rulesyacc.y"
        {
	  DBUGPRT("expression_statement");
 	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::STR, *(yyvsp[0].string_slot)));
	}
#line 2577 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 89: /* expression_statement: expression_statement TOKEN_UNION expression_statement  */
#line 936 "src/rulesyacc.y"
                                                               {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::UNIF, (*(yyvsp[-2].statement_slot)), (*(yyvsp[0].statement_slot))));
	  free((yyvsp[-2].statement_slot));
	  free((yyvsp[0].statement_slot));
	}
#line 2588 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 90: /* expression_statement: up  */
#line 943 "src/rulesyacc.y"
            {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot)=(yyvsp[0].statement_slot);
	}
#line 2597 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 91: /* expression_statement: updouble  */
#line 948 "src/rulesyacc.y"
                  {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot)=(yyvsp[0].statement_slot);
	}
#line 2606 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 92: /* expression_statement: down  */
#line 953 "src/rulesyacc.y"
              {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot)=(yyvsp[0].statement_slot);
	}
#line 2615 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 93: /* expression_statement: downdouble  */
#line 958 "src/rulesyacc.y"
                    {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot)=(yyvsp[0].statement_slot);
	}
#line 2624 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 94: /* expression_statement: features  */
#line 963 "src/rulesyacc.y"
                  {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::FEATURES, *(yyvsp[0].features_slot)));
	  free((yyvsp[0].features_slot));
	}
#line 2634 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 95: /* expression_statement: TOKEN_NIL  */
#line 970 "src/rulesyacc.y"
        {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::NIL));
	}
#line 2643 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 96: /* expression_statement: constant  */
#line 975 "src/rulesyacc.y"
                  {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::CONSTANT, *(yyvsp[0].bits_slot)));
	  free((yyvsp[0].bits_slot));
	}
#line 2653 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 97: /* expression_statement: TOKEN_ANONYMOUS  */
#line 982 "src/rulesyacc.y"
        {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::ANONYMOUS, Value::ANONYMOUS_VALUE));
	}
#line 2662 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 98: /* expression_statement: variable  */
#line 987 "src/rulesyacc.y"
                  {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::VARIABLE, *(yyvsp[0].bits_slot)));
	  free((yyvsp[0].bits_slot));
	}
#line 2672 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 99: /* expression_statement: TOKEN_LPAR expression_statement TOKEN_RPAR  */
#line 993 "src/rulesyacc.y"
                                                    {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot)=(yyvsp[-1].statement_slot);
	}
#line 2681 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 100: /* expression_statement: list  */
#line 998 "src/rulesyacc.y"
              {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::LIST, *(yyvsp[0].list_slot)));
	  free((yyvsp[0].list_slot));
	}
#line 2691 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 101: /* expression_statement: dash_statement  */
#line 1004 "src/rulesyacc.y"
                        {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot)=(yyvsp[0].statement_slot);
	}
#line 2700 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 102: /* expression_statement: TOKEN_SEARCH TOKEN_LPAR expression_statement TOKEN_RPAR  */
#line 1009 "src/rulesyacc.y"
                                                                  {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno,
						  Statement::SEARCH,
						  *(yyvsp[-1].statement_slot)));
	  free((yyvsp[-1].statement_slot));
	 }
#line 2712 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 103: /* up: TOKEN_UPARROW  */
#line 1018 "src/rulesyacc.y"
                      {
	  DBUGPRT("up");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::UP));
	}
#line 2721 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 104: /* updouble: TOKEN_UP2ARROW  */
#line 1024 "src/rulesyacc.y"
                       {
	  DBUGPRT("updouble");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::UP2));
	}
#line 2730 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 105: /* down: TOKEN_DOWNARROW TOKEN_INTEGER  */
#line 1031 "src/rulesyacc.y"
        {
	  DBUGPRT("down");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::DOWN, (unsigned int)(yyvsp[0].integer_slot)-1));
	}
#line 2739 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 106: /* dash_statement: TOKEN_DASH TOKEN_INTEGER TOKEN_DOT TOKEN_INTEGER  */
#line 1038 "src/rulesyacc.y"
        {
	  DBUGPRT("dash_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::DASH, (unsigned int)((yyvsp[-2].integer_slot)-1), (unsigned int)((yyvsp[0].integer_slot)-1)));
	}
#line 2748 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 107: /* dash_statement: TOKEN_DASH TOKEN_INTEGER  */
#line 1044 "src/rulesyacc.y"
        {
	  DBUGPRT("dash_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::DASH, (unsigned int)((yyvsp[0].integer_slot)-1)));
	}
#line 2757 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 108: /* downdouble: TOKEN_DOWN2ARROW  */
#line 1050 "src/rulesyacc.y"
                         {
	  DBUGPRT("downdouble");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::DOWN2, (unsigned int)0));
	}
#line 2766 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 109: /* downdouble: TOKEN_DOWN2ARROW TOKEN_INTEGER  */
#line 1056 "src/rulesyacc.y"
        {
	  DBUGPRT("downdouble");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::DOWN2, (unsigned int)((yyvsp[0].integer_slot)-1)));
	}
#line 2775 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 110: /* features: TOKEN_LBRACKET features_components features_components_tail TOKEN_RBRACKET  */
#line 1066 "src/rulesyacc.y"
        {
	  DBUGPRT("features");
 	  (yyval.features_slot) = (yyvsp[-2].features_slot);
	  if ((yyvsp[-1].feature_slot)) {
	    (*(yyval.features_slot))->add(*(yyvsp[-1].feature_slot));
	    free((yyvsp[-1].feature_slot));
	  }
	}
#line 2788 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 111: /* features: TOKEN_LBRACKET TOKEN_RBRACKET  */
#line 1076 "src/rulesyacc.y"
        {
	  DBUGPRT("features");
	  (yyval.features_slot) = new featuresPtr(Features::create());
	}
#line 2797 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 112: /* features_components_tail: %empty  */
#line 1083 "src/rulesyacc.y"
        {
	    (yyval.feature_slot) = NULL;
	}
#line 2805 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 113: /* features_components_tail: TOKEN_COMMA variable  */
#line 1088 "src/rulesyacc.y"
        {
        (yyval.feature_slot) = new featurePtr(Feature::create(Feature::VARIABLE, *(yyvsp[0].bits_slot), valuePtr()));
    }
#line 2813 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 114: /* features_components: features_components TOKEN_COMMA feature  */
#line 1094 "src/rulesyacc.y"
        {
	  DBUGPRT("feature_components");
	  (yyval.features_slot) = (yyvsp[-2].features_slot);
	  (*(yyval.features_slot))->add(*(yyvsp[0].feature_slot));
	  free((yyvsp[0].feature_slot));
	}
#line 2824 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 115: /* features_components: feature  */
#line 1102 "src/rulesyacc.y"
        {
	  DBUGPRT("features_components");
	  (yyval.features_slot) = new featuresPtr(Features::create());
	  (*(yyval.features_slot))->add(*(yyvsp[0].feature_slot));
	  free((yyvsp[0].feature_slot));
	}
#line 2835 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 116: /* features_components: features_components TOKEN_COMMA TOKEN_AROBASE TOKEN_IDENTIFIER  */
#line 1111 "src/rulesyacc.y"
        {
	  DBUGPRT("features_components");
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
#line 2852 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 117: /* features_components: TOKEN_AROBASE TOKEN_IDENTIFIER  */
#line 1126 "src/rulesyacc.y"
        {
	  DBUGPRT("features_components");
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
#line 2869 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 118: /* feature: TOKEN_LEMMA TOKEN_COLON stringOrIdentifier  */
#line 1142 "src/rulesyacc.y"
        {
	  DBUGPRT("feature");
	  (yyval.feature_slot) = new featurePtr(Feature::create(Feature::LEMMA, bitsetPtr(), Value::create(Value::_CODE, *(yyvsp[0].string_slot))));
	}
#line 2878 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 119: /* feature: TOKEN_LEMMA TOKEN_COLON variable  */
#line 1149 "src/rulesyacc.y"
        {
	  DBUGPRT("feature");
	  (yyval.feature_slot) = new featurePtr(Feature::create(Feature::LEMMA, bitsetPtr(), Value::create(Value::_VARIABLE, *(yyvsp[0].bits_slot))));
	}
#line 2887 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 120: /* feature: TOKEN_PRED TOKEN_COLON stringOrIdentifier  */
#line 1156 "src/rulesyacc.y"
        {
	  DBUGPRT("feature");
	  (yyval.feature_slot) = new featurePtr(Feature::create(Feature::PRED, bitsetPtr(), Value::create(Value::_CODE, *(yyvsp[0].string_slot))));
	}
#line 2896 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 121: /* feature: TOKEN_PRED TOKEN_COLON variable  */
#line 1163 "src/rulesyacc.y"
        {
	  DBUGPRT("feature");
	  (yyval.feature_slot) = new featurePtr(Feature::create(Feature::PRED, bitsetPtr(), Value::create(Value::_VARIABLE, *(yyvsp[0].bits_slot))));
	  free((yyvsp[0].bits_slot));
	}
#line 2906 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 122: /* feature: TOKEN_FORM TOKEN_COLON variable  */
#line 1171 "src/rulesyacc.y"
        {
	  DBUGPRT("feature");
	  (yyval.feature_slot) = new featurePtr(Feature::create(Feature::FORM, bitsetPtr(), Value::create(Value::_VARIABLE, *(yyvsp[0].bits_slot))));
	  free((yyvsp[0].bits_slot));
	}
#line 2916 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 123: /* feature: TOKEN_FORM TOKEN_COLON stringOrIdentifier  */
#line 1178 "src/rulesyacc.y"
        {
	  DBUGPRT("feature");
	  (yyval.feature_slot) = new featurePtr(Feature::create(Feature::FORM, bitsetPtr(), Value::create(Value::_FORM, *(yyvsp[0].string_slot))));
	}
#line 2925 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 124: /* feature: identifier TOKEN_COLON feature_value  */
#line 1184 "src/rulesyacc.y"
        {
	  DBUGPRT("feature");
	  (yyval.feature_slot) = new featurePtr(Feature::create(Feature::CONSTANT, *(yyvsp[-2].bits_slot), *(yyvsp[0].value_slot)));
	  free((yyvsp[-2].bits_slot));
	  free((yyvsp[0].value_slot));
	}
#line 2936 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 125: /* feature: identifier TOKEN_COLON TOKEN_STRING  */
#line 1192 "src/rulesyacc.y"
        {
	  DBUGPRT("feature");
	  (yyval.feature_slot) = new featurePtr(Feature::create(Feature::CONSTANT, *(yyvsp[-2].bits_slot), Value::create(Value::_FORM, *(yyvsp[0].string_slot))));
	  free((yyvsp[-2].bits_slot));
	}
#line 2946 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 126: /* feature: variable TOKEN_COLON feature_value  */
#line 1199 "src/rulesyacc.y"
        {
	  DBUGPRT("feature");
	  (yyval.feature_slot) = new featurePtr(Feature::create(Feature::VARIABLE, *(yyvsp[-2].bits_slot), *(yyvsp[0].value_slot)));
	  free((yyvsp[-2].bits_slot));
	  free((yyvsp[0].value_slot));
	}
#line 2957 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 127: /* feature_value: variable  */
#line 1209 "src/rulesyacc.y"
        {
	  DBUGPRT("feature_value");
	  (yyval.value_slot) = new valuePtr(Value::create(Value::_VARIABLE, *(yyvsp[0].bits_slot)));
	  free((yyvsp[0].bits_slot));
	}
#line 2967 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 128: /* feature_value: constant  */
#line 1216 "src/rulesyacc.y"
        {
	  DBUGPRT("feature_value");
	  (yyval.value_slot) = new valuePtr(Value::create(Value::_CONSTANT, *(yyvsp[0].bits_slot)));
	  free((yyvsp[0].bits_slot));
	}
#line 2977 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 129: /* feature_value: TOKEN_DOUBLE  */
#line 1223 "src/rulesyacc.y"
        {
	  DBUGPRT("expression_statement");
	  (yyval.value_slot) = new valuePtr(Value::create(Value::_NUMBER, (yyvsp[0].double_slot)));
	}
#line 2986 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 130: /* feature_value: TOKEN_INTEGER  */
#line 1229 "src/rulesyacc.y"
        {
	  DBUGPRT("expression_statement");
	  (yyval.value_slot) = new valuePtr(Value::create(Value::_NUMBER, (double)(yyvsp[0].integer_slot)));
	}
#line 2995 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 131: /* feature_value: list  */
#line 1235 "src/rulesyacc.y"
        {
	  DBUGPRT("feature_value");
	  (yyval.value_slot) = new valuePtr(Value::create(Value::_LIST, *(yyvsp[0].list_slot)));
	  free((yyvsp[0].list_slot));
	}
#line 3005 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 132: /* feature_value: features  */
#line 1242 "src/rulesyacc.y"
        {
	  DBUGPRT("feature_value");
	  (yyval.value_slot) = new valuePtr(Value::create(Value::_FEATURES, *(yyvsp[0].features_slot)));
	  free((yyvsp[0].features_slot));
	}
#line 3015 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 133: /* feature_value: TOKEN_NIL  */
#line 1249 "src/rulesyacc.y"
        {
	  DBUGPRT("feature_value");
	  (yyval.value_slot) = new valuePtr(Value::NIL_VALUE);
	}
#line 3024 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 134: /* feature_value: TOKEN_ANONYMOUS  */
#line 1255 "src/rulesyacc.y"
        {
	  DBUGPRT("feature_value");
	  (yyval.value_slot) = new valuePtr(Value::ANONYMOUS_VALUE);
	}
#line 3033 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 135: /* constant: identifier  */
#line 1262 "src/rulesyacc.y"
        {
	  DBUGPRT("constants");
	  (yyval.bits_slot)=(yyvsp[0].bits_slot);
	}
#line 3042 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 136: /* constant: identifier TOKEN_PIPE constant  */
#line 1268 "src/rulesyacc.y"
        {
	  DBUGPRT("constants");
	  (yyval.bits_slot)=(yyvsp[-2].bits_slot);
	  (**(yyval.bits_slot)) |= (**(yyvsp[0].bits_slot));
	}
#line 3052 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 137: /* identifier: TOKEN_IDENTIFIER  */
#line 1276 "src/rulesyacc.y"
        {
	  DBUGPRT("identifier");
 	  (yyval.bits_slot) = new bitsetPtr(Bitset::create(Vartable::createVariable(*(yyvsp[0].string_slot))));
 	  free((yyvsp[0].string_slot));
	}
#line 3062 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 138: /* variable: TOKEN_VARIABLE  */
#line 1284 "src/rulesyacc.y"
        {
	  DBUGPRT("variable");
	  std::ostringstream oss;
	  oss << *(yyvsp[0].string_slot);
  	  std::string str = oss.str();
	  (yyval.bits_slot) = new bitsetPtr(Bitset::create(Vartable::createVariable(str)));
	  free((yyvsp[0].string_slot));
	}
#line 3075 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 139: /* list: TOKEN_LT list_elements TOKEN_GT  */
#line 1295 "src/rulesyacc.y"
        {
	  DBUGPRT("list");
	  (yyval.list_slot) = (yyvsp[-1].list_slot);
	}
#line 3084 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 140: /* list: TOKEN_LT TOKEN_GT  */
#line 1301 "src/rulesyacc.y"
        {
	  DBUGPRT("list");
	  (yyval.list_slot) = new listPtr(List::NIL_LIST);
	}
#line 3093 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 141: /* list: TOKEN_LT list_elements TOKEN_DOUBLECOLON list_element TOKEN_GT  */
#line 1307 "src/rulesyacc.y"
        {
	  DBUGPRT("list");
	  if ((*(yyvsp[-3].list_slot))->isPairp() && (*(yyvsp[-3].list_slot))->getCdr()->isNil())
	    (yyval.list_slot) = new listPtr(List::create((*(yyvsp[-3].list_slot))->getCar(), *(yyvsp[-1].list_slot)));
	  else
	    (yyval.list_slot) = new listPtr(List::create(*(yyvsp[-3].list_slot), *(yyvsp[-1].list_slot)));
	  free((yyvsp[-3].list_slot));
	  free((yyvsp[-1].list_slot));
	}
#line 3107 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 142: /* list: TOKEN_LT list_elements TOKEN_DOUBLECOLON TOKEN_NIL TOKEN_GT  */
#line 1318 "src/rulesyacc.y"
        {
	  DBUGPRT("list");
	  if ((*(yyvsp[-3].list_slot))->isPairp() && (*(yyvsp[-3].list_slot))->getCdr()->isNil())
	    (yyval.list_slot) = new listPtr(List::create((*(yyvsp[-3].list_slot))->getCar(), List::NIL_LIST));
	  else
	    (yyval.list_slot) = new listPtr(List::create(*(yyvsp[-3].list_slot), List::NIL_LIST));
	  free((yyvsp[-3].list_slot));
	}
#line 3120 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 143: /* list_elements: list_element TOKEN_COMMA list_elements  */
#line 1329 "src/rulesyacc.y"
        {
	  DBUGPRT("list_elements");
	  (yyval.list_slot) = new listPtr(List::create(*(yyvsp[-2].list_slot), *(yyvsp[0].list_slot)));
	  free((yyvsp[-2].list_slot));
	  free((yyvsp[0].list_slot));
	}
#line 3131 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 144: /* list_elements: list_element  */
#line 1337 "src/rulesyacc.y"
        {
	  DBUGPRT("list_elements");
	  (yyval.list_slot) = new listPtr(List::create(*(yyvsp[0].list_slot), List::NIL_LIST));
	  free((yyvsp[0].list_slot));
	}
#line 3141 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 145: /* list_element: variable  */
#line 1345 "src/rulesyacc.y"
        {
	  DBUGPRT("list_element");
	  (yyval.list_slot) = new listPtr(List::create(Value::create(Value::_VARIABLE, *(yyvsp[0].bits_slot))));
	  free((yyvsp[0].bits_slot));
	}
#line 3151 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 146: /* list_element: TOKEN_DOUBLE  */
#line 1352 "src/rulesyacc.y"
        {
	  DBUGPRT("expression_statement");
	  (yyval.list_slot) = new listPtr(List::create(Value::create(Value::_NUMBER, (yyvsp[0].double_slot))));
	}
#line 3160 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 147: /* list_element: TOKEN_INTEGER  */
#line 1358 "src/rulesyacc.y"
        {
	  DBUGPRT("expression_statement");
	  (yyval.list_slot) = new listPtr(List::create(Value::create(Value::_NUMBER, (double)(yyvsp[0].integer_slot))));
	}
#line 3169 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 148: /* list_element: constant  */
#line 1364 "src/rulesyacc.y"
        {
	  DBUGPRT("list_element");
	  (yyval.list_slot) = new listPtr(List::create(Value::create(Value::_CONSTANT, *(yyvsp[0].bits_slot))));
	  free((yyvsp[0].bits_slot));
	}
#line 3179 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 149: /* list_element: features  */
#line 1371 "src/rulesyacc.y"
        {
	  DBUGPRT("list_element");
	  (yyval.list_slot) = new listPtr(List::create(Value::create(Value::_FEATURES, *(yyvsp[0].features_slot))));
	  free((yyvsp[0].features_slot));
	}
#line 3189 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 150: /* list_element: list  */
#line 1378 "src/rulesyacc.y"
        {
	  DBUGPRT("list_element");
	  (yyval.list_slot)=(yyvsp[0].list_slot);
	}
#line 3198 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;


#line 3202 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"

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

#line 1383 "src/rulesyacc.y"

