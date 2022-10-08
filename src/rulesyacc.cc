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
 * Copyright 2014-2020 LABRI, 
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
#include "shared_ptr.hpp"
#include "vartable.hpp"
#include "terms.hpp"
#include "entry.hpp"
#include "entries.hpp"
#include "application.hpp"
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
#include "rules.hpp"
#include "shared_ptr.hpp"

#if false
#define DBUG(x)x
#else
#define DBUG(x)
#endif
#define DBUGPRT(x) DBUG(std::cerr << "*** " << x << std::endl)
#define DBUGPRTARG(x,s) DBUG(std::cerr << "*** " << x << " " << s << std::endl)
  
 extern unsigned int ruleslineno;
 extern unsigned int ruleslex();
 extern Application application;
 unsigned int headLineno;
 bool headTrace;

  void ruleserror(const char *str) {
      std::ostringstream oss;
      oss << str << " " << application.generator.getTopBufferName() << " (" << ruleslineno << ")" << std::endl;
      throw fatal_exception(oss.str());
  }
  
  void yywarning(const char *str){
    try {
      std::ostringstream oss;
      oss << "warning: " << str << " " << application.generator.getTopBufferName() << " (" << ruleslineno << ")" << std::endl;
      throw oss.str();	     
    }
    catch (std::string msg) {
      std::cerr << msg << std::endl;
    }
  }
  
  

#line 153 "/Users/clement/workspace/elvex/src/rulesyacc.cc"

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
  YYSYMBOL_TOKEN_INSET = 42,               /* TOKEN_INSET  */
  YYSYMBOL_TOKEN_AFF = 43,                 /* TOKEN_AFF  */
  YYSYMBOL_TOKEN_PIPE = 44,                /* TOKEN_PIPE  */
  YYSYMBOL_TOKEN_NOT = 45,                 /* TOKEN_NOT  */
  YYSYMBOL_TOKEN_OR = 46,                  /* TOKEN_OR  */
  YYSYMBOL_TOKEN_AND = 47,                 /* TOKEN_AND  */
  YYSYMBOL_TOKEN_IMPLICATION = 48,         /* TOKEN_IMPLICATION  */
  YYSYMBOL_TOKEN_EQUIV = 49,               /* TOKEN_EQUIV  */
  YYSYMBOL_TOKEN_PLUS = 50,                /* TOKEN_PLUS  */
  YYSYMBOL_TOKEN_MINUS = 51,               /* TOKEN_MINUS  */
  YYSYMBOL_TOKEN_TIMES = 52,               /* TOKEN_TIMES  */
  YYSYMBOL_TOKEN_DIVIDE = 53,              /* TOKEN_DIVIDE  */
  YYSYMBOL_TOKEN_MODULO = 54,              /* TOKEN_MODULO  */
  YYSYMBOL_TOKEN_EQUAL = 55,               /* TOKEN_EQUAL  */
  YYSYMBOL_TOKEN_DIFF = 56,                /* TOKEN_DIFF  */
  YYSYMBOL_TOKEN_LT = 57,                  /* TOKEN_LT  */
  YYSYMBOL_TOKEN_LE = 58,                  /* TOKEN_LE  */
  YYSYMBOL_TOKEN_GT = 59,                  /* TOKEN_GT  */
  YYSYMBOL_TOKEN_GE = 60,                  /* TOKEN_GE  */
  YYSYMBOL_TOKEN_IDENTIFIER = 61,          /* TOKEN_IDENTIFIER  */
  YYSYMBOL_TOKEN_STRING = 62,              /* TOKEN_STRING  */
  YYSYMBOL_TOKEN_INTEGER = 63,             /* TOKEN_INTEGER  */
  YYSYMBOL_TOKEN_DOUBLE = 64,              /* TOKEN_DOUBLE  */
  YYSYMBOL_TOKEN_VARIABLE = 65,            /* TOKEN_VARIABLE  */
  YYSYMBOL_TOKEN_ANONYMOUS = 66,           /* TOKEN_ANONYMOUS  */
  YYSYMBOL_TOKEN_MINUS_U = 67,             /* TOKEN_MINUS_U  */
  YYSYMBOL_TOKEN_NOELSE = 68,              /* TOKEN_NOELSE  */
  YYSYMBOL_YYACCEPT = 69,                  /* $accept  */
  YYSYMBOL_axiom = 70,                     /* axiom  */
  YYSYMBOL_begin = 71,                     /* begin  */
  YYSYMBOL_dictionary = 72,                /* dictionary  */
  YYSYMBOL_stringOrIdentifier = 73,        /* stringOrIdentifier  */
  YYSYMBOL_dictionary_line = 74,           /* dictionary_line  */
  YYSYMBOL_lexical_entries = 75,           /* lexical_entries  */
  YYSYMBOL_lexical_entry = 76,             /* lexical_entry  */
  YYSYMBOL_rules = 77,                     /* rules  */
  YYSYMBOL_78_1 = 78,                      /* $@1  */
  YYSYMBOL_79_2 = 79,                      /* $@2  */
  YYSYMBOL_pref_rule = 80,                 /* pref_rule  */
  YYSYMBOL_rule = 81,                      /* rule  */
  YYSYMBOL_terms_vector = 82,              /* terms_vector  */
  YYSYMBOL_terms = 83,                     /* terms  */
  YYSYMBOL_terms_disj = 84,                /* terms_disj  */
  YYSYMBOL_term = 85,                      /* term  */
  YYSYMBOL_structure_statement = 86,       /* structure_statement  */
  YYSYMBOL_list_statement = 87,            /* list_statement  */
  YYSYMBOL_statements = 88,                /* statements  */
  YYSYMBOL_statement = 89,                 /* statement  */
  YYSYMBOL_left_hand_side_subset_statement = 90, /* left_hand_side_subset_statement  */
  YYSYMBOL_right_hand_side_subset_statement = 91, /* right_hand_side_subset_statement  */
  YYSYMBOL_left_hand_side_inset_statement = 92, /* left_hand_side_inset_statement  */
  YYSYMBOL_right_hand_side_inset_statement = 93, /* right_hand_side_inset_statement  */
  YYSYMBOL_left_hand_side_aff_statement = 94, /* left_hand_side_aff_statement  */
  YYSYMBOL_right_hand_side_aff_statement = 95, /* right_hand_side_aff_statement  */
  YYSYMBOL_expression_statement = 96,      /* expression_statement  */
  YYSYMBOL_up = 97,                        /* up  */
  YYSYMBOL_updouble = 98,                  /* updouble  */
  YYSYMBOL_down = 99,                      /* down  */
  YYSYMBOL_dash_statement = 100,           /* dash_statement  */
  YYSYMBOL_downdouble = 101,               /* downdouble  */
  YYSYMBOL_features = 102,                 /* features  */
  YYSYMBOL_features_components_head = 103, /* features_components_head  */
  YYSYMBOL_features_components_tail = 104, /* features_components_tail  */
  YYSYMBOL_feature = 105,                  /* feature  */
  YYSYMBOL_feature_value = 106,            /* feature_value  */
  YYSYMBOL_constant = 107,                 /* constant  */
  YYSYMBOL_identifier = 108,               /* identifier  */
  YYSYMBOL_variable = 109,                 /* variable  */
  YYSYMBOL_list = 110,                     /* list  */
  YYSYMBOL_list_elements = 111,            /* list_elements  */
  YYSYMBOL_list_element = 112              /* list_element  */
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
#define YYLAST   744

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  69
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  44
/* YYNRULES -- Number of rules.  */
#define YYNRULES  153
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  268

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   323


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
      65,    66,    67,    68
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   166,   166,   172,   176,   184,   190,   194,   202,   206,
     211,   216,   221,   229,   254,   281,   310,   319,   325,   333,
     341,   350,   361,   361,   366,   366,   372,   378,   384,   399,
     414,   420,   427,   432,   439,   446,   453,   460,   467,   476,
     482,   487,   493,   501,   509,   516,   523,   528,   534,   540,
     546,   552,   605,   621,   634,   652,   679,   699,   706,   712,
     717,   722,   728,   736,   747,   753,   759,   764,   769,   775,
     786,   795,   802,   809,   816,   829,   835,   842,   849,   856,
     863,   870,   880,   888,   896,   904,   912,   920,   927,   933,
     939,   945,   954,   961,   966,   971,   976,   981,   987,   993,
     999,  1005,  1011,  1016,  1022,  1027,  1036,  1042,  1048,  1055,
    1061,  1068,  1073,  1083,  1093,  1104,  1112,  1121,  1136,  1153,
    1159,  1168,  1175,  1182,  1189,  1197,  1205,  1212,  1221,  1229,
    1246,  1253,  1260,  1266,  1272,  1279,  1286,  1292,  1299,  1305,
    1313,  1321,  1332,  1338,  1344,  1355,  1366,  1374,  1382,  1389,
    1395,  1401,  1408,  1415
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
  "TOKEN_TRACE", "TOKEN_UNION", "TOKEN_SUBSUME", "TOKEN_INSET",
  "TOKEN_AFF", "TOKEN_PIPE", "TOKEN_NOT", "TOKEN_OR", "TOKEN_AND",
  "TOKEN_IMPLICATION", "TOKEN_EQUIV", "TOKEN_PLUS", "TOKEN_MINUS",
  "TOKEN_TIMES", "TOKEN_DIVIDE", "TOKEN_MODULO", "TOKEN_EQUAL",
  "TOKEN_DIFF", "TOKEN_LT", "TOKEN_LE", "TOKEN_GT", "TOKEN_GE",
  "TOKEN_IDENTIFIER", "TOKEN_STRING", "TOKEN_INTEGER", "TOKEN_DOUBLE",
  "TOKEN_VARIABLE", "TOKEN_ANONYMOUS", "TOKEN_MINUS_U", "TOKEN_NOELSE",
  "$accept", "axiom", "begin", "dictionary", "stringOrIdentifier",
  "dictionary_line", "lexical_entries", "lexical_entry", "rules", "$@1",
  "$@2", "pref_rule", "rule", "terms_vector", "terms", "terms_disj",
  "term", "structure_statement", "list_statement", "statements",
  "statement", "left_hand_side_subset_statement",
  "right_hand_side_subset_statement", "left_hand_side_inset_statement",
  "right_hand_side_inset_statement", "left_hand_side_aff_statement",
  "right_hand_side_aff_statement", "expression_statement", "up",
  "updouble", "down", "dash_statement", "downdouble", "features",
  "features_components_head", "features_components_tail", "feature",
  "feature_value", "constant", "identifier", "variable", "list",
  "list_elements", "list_element", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-117)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-68)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      70,     4,    13,     2,   141,    18,  -117,   357,  -117,  -117,
     -16,  -117,  -117,  -117,  -117,     4,   -35,  -117,   -24,  -117,
    -117,  -117,   -42,   141,  -117,   -21,   -23,    35,    57,    58,
    -117,  -117,    61,    69,  -117,    72,    82,  -117,     2,    13,
    -117,    89,    22,    49,     4,    96,    73,  -117,  -117,  -117,
      44,    44,    44,   516,   105,  -117,   239,   373,   123,  -117,
       4,  -117,   113,  -117,  -117,  -117,    83,    93,  -117,    93,
    -117,    93,  -117,    86,  -117,    82,  -117,  -117,   128,  -117,
    -117,  -117,  -117,  -117,  -117,  -117,   106,  -117,  -117,  -117,
       5,   142,  -117,  -117,  -117,  -117,  -117,  -117,  -117,  -117,
    -117,  -117,     9,   140,   103,    68,     2,  -117,     5,  -117,
     118,  -117,  -117,  -117,    -3,  -117,    71,  -117,  -117,   110,
     169,  -117,   261,   261,   261,   160,   -23,   -23,   359,  -117,
    -117,   135,   127,   143,  -117,   147,   162,  -117,    -8,  -117,
    -117,     2,   148,   149,  -117,  -117,  -117,   368,  -117,   137,
     261,   138,  -117,   198,   214,   261,   261,  -117,  -117,  -117,
    -117,   544,  -117,  -117,  -117,  -117,  -117,  -117,  -117,  -117,
    -117,   566,   589,   261,   191,   209,  -117,  -117,    20,   261,
     261,  -117,  -117,  -117,  -117,  -117,  -117,  -117,   395,   215,
     261,   224,   673,  -117,  -117,   261,   261,   261,   261,   261,
     261,   261,   261,   261,   261,   261,   261,   261,   261,   261,
     261,  -117,  -117,   417,   261,   -23,   227,   220,  -117,  -117,
    -117,  -117,   221,   610,   222,   610,  -117,   176,   447,  -117,
     511,   652,   673,   631,   631,   101,   101,   188,   188,  -117,
     684,   684,   684,   684,   684,   684,    59,   303,   184,   261,
    -117,  -117,  -117,  -117,  -117,   216,   261,  -117,  -117,   469,
      -9,    59,   209,  -117,   261,  -117,   499,  -117
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,    22,     0,     0,     0,     2,   119,     7,     3,
      27,    25,    38,    36,    37,     5,     0,    17,     0,    10,
      11,     6,     0,     9,     1,     0,     0,     0,     0,     0,
     140,   141,   119,     0,   116,     0,     0,    26,     0,    22,
       4,     0,     0,     0,    21,     0,    19,     8,   118,   120,
       0,     0,     0,     0,     0,   114,     0,     0,     0,    23,
       0,    13,     0,    12,    20,    15,     0,   121,   122,   123,
     124,   126,   125,     0,   115,   120,   113,   136,     0,   128,
     133,   132,   137,   135,   127,   131,   138,   130,   134,   129,
       0,     0,    14,    18,   117,   143,   150,   149,   152,   151,
     148,   153,     0,   147,     0,     0,     0,    41,     0,    31,
      32,    35,    29,    16,     0,   142,     0,   139,   107,     0,
       0,    40,     0,     0,     0,     0,     0,     0,     0,    46,
      42,     0,     0,     0,    66,    64,    57,    68,     0,    30,
      28,     0,     0,     0,   146,   108,    45,     0,   106,   111,
       0,     0,    98,     0,     0,     0,     0,    91,    90,    89,
     100,     0,    93,    94,    95,   104,    96,    97,    99,   101,
     103,     0,     0,     0,     0,     0,    39,    43,     0,     0,
       0,    50,    33,    34,   145,   144,    44,   112,     0,   110,
       0,     0,    75,    87,    47,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    48,    49,     0,     0,     0,     0,     0,    59,    60,
      61,    58,     0,    65,     0,    70,   102,     0,     0,    88,
      92,    71,    72,    73,    74,    82,    83,    84,    85,    86,
      76,    77,    78,    79,    80,    81,     0,     0,     0,     0,
      52,    53,    51,   109,   105,    54,     0,    56,    69,     0,
     138,     0,   101,    62,     0,    55,     0,    63
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -117,  -117,  -117,   225,   132,  -117,   183,  -117,   217,  -117,
    -117,  -117,  -117,  -117,   145,   151,     1,   146,   139,  -117,
    -116,  -117,  -117,  -117,  -117,  -117,  -117,    15,    80,   -98,
     -95,  -117,    84,    -1,  -117,   229,   210,   213,   174,    -5,
      -6,    45,   156,   163
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     5,     6,    21,    22,    23,    45,    46,     9,    10,
      11,    38,    39,   108,   109,   110,   111,   112,   128,   129,
     130,   131,   217,   132,   222,   133,   224,   242,   162,   163,
     164,   165,   166,   167,    32,    33,    34,    84,   168,    86,
     169,   170,   102,   103
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
       8,    36,    35,    12,    15,   182,    12,   134,    43,     7,
     135,   264,   177,   -24,    40,   105,     7,   106,    24,    44,
      49,   107,   134,    37,   148,   135,    41,   149,   114,   142,
     134,   177,     7,   135,     7,   104,   141,    42,    61,    58,
      48,    62,    31,    64,    68,    70,    72,    75,    35,   134,
      87,    87,   135,    50,    78,    83,    83,   216,    30,    91,
      96,    97,    31,    13,   118,   119,    13,    14,   115,   120,
      14,     7,   100,   118,   119,    51,    52,    98,   120,   121,
       7,    53,    55,     7,     1,    31,   122,   123,   124,   125,
      56,     2,     3,     4,   126,   122,   123,   124,   125,   137,
      57,    88,    88,   126,   136,    19,    20,    60,   100,    31,
     100,    63,    65,    98,   137,    98,   127,    66,    76,   136,
     174,   175,   137,   101,    31,   127,    90,   136,    78,    92,
     255,   257,    30,    31,    96,    97,    31,   161,   171,   172,
       7,   137,   183,    43,    44,   265,   136,    94,   134,   134,
     104,   135,   135,   202,   203,   204,    16,    17,   113,   101,
     116,   101,   141,   134,    30,   188,   135,    18,   173,   179,
     192,   193,   221,   145,   118,   119,   178,   220,   181,   120,
     146,     7,    67,    69,    71,    78,   180,    95,   213,    30,
     -67,    96,    97,    31,   223,   225,   122,   123,   124,   125,
     187,   189,    19,    20,   126,   228,   190,   184,   185,   248,
     230,   231,   232,   233,   234,   235,   236,   237,   238,   239,
     240,   241,   191,   243,   244,   245,   127,   214,   215,   247,
      85,    85,   227,   229,    31,   249,   250,   251,   252,   253,
     137,   137,   204,   258,   260,   136,   136,   261,    47,    93,
     262,     7,    99,   139,   140,   137,    59,   138,   218,   147,
     136,    54,   219,    74,   259,   148,   118,   119,   149,   150,
      89,    77,   144,     7,     0,   151,     0,   143,   117,   266,
       0,     0,     0,     0,     0,     0,     0,     0,    99,     0,
      99,     0,     0,   152,     0,     0,    78,     0,   153,   154,
      30,    79,    80,    81,    31,    82,   155,     0,   118,   119,
       0,     0,   156,   120,     0,     7,     0,     0,    78,     0,
       0,     0,    30,   157,   158,   159,    31,   160,     0,     0,
     122,   123,   124,   125,     0,     0,     0,     0,   126,     0,
       0,     0,     0,   195,     0,     0,     0,     0,     0,   196,
     197,   198,   199,   200,   201,   202,   203,   204,   205,   206,
     256,   208,   209,   210,   118,   119,     0,     0,    31,   120,
     176,     7,    25,   118,   119,     0,     0,    26,   120,   186,
       7,    27,    28,    29,     0,     7,   122,   123,   124,   125,
       0,     0,     0,     0,   126,   122,   123,   124,   125,     0,
       0,     0,     0,   126,   226,    77,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   127,     0,    30,     0,
       0,     0,    31,     0,    31,   127,   246,     0,     0,     0,
      78,     0,     0,    31,    30,   195,    80,    81,    31,    82,
       0,   196,   197,   198,   199,   200,   201,   202,   203,   204,
     205,   206,   207,   208,   209,   210,   254,   195,     0,     0,
       0,     0,     0,   196,   197,   198,   199,   200,   201,   202,
     203,   204,   205,   206,   207,   208,   209,   210,   263,     0,
       0,     0,     0,     0,     0,     0,     0,   195,     0,     0,
       0,     0,     0,   196,   197,   198,   199,   200,   201,   202,
     203,   204,   205,   206,   207,   208,   209,   210,   267,   195,
       0,     0,     0,     0,     0,   196,   197,   198,   199,   200,
     201,   202,   203,   204,   205,   206,   207,   208,   209,   210,
       0,    73,     0,     0,     0,     0,     0,     0,     0,   195,
      27,    28,    29,     0,     0,   196,   197,   198,   199,   200,
     201,   202,   203,   204,   205,   206,   207,   208,   209,   210,
     194,   200,   201,   202,   203,   204,   205,   206,   207,   208,
     209,   210,     0,     0,     0,     0,     0,    30,     0,     0,
       0,    31,   211,     0,   195,     0,     0,     0,     0,     0,
     196,   197,   198,   199,   200,   201,   202,   203,   204,   205,
     206,   207,   208,   209,   210,   212,   195,     0,     0,     0,
       0,     0,   196,   197,   198,   199,   200,   201,   202,   203,
     204,   205,   206,   207,   208,   209,   210,     0,     0,   195,
       0,     0,     0,     0,     0,   196,   197,   198,   199,   200,
     201,   202,   203,   204,   205,   206,   207,   208,   209,   210,
     195,     0,     0,     0,     0,     0,   196,   197,   198,   199,
     200,   201,   202,   203,   204,   205,   206,   207,   208,   209,
     210,   195,     0,     0,     0,     0,     0,   196,   197,   -68,
     -68,   200,   201,   202,   203,   204,   205,   206,   207,   208,
     209,   210,   195,     0,     0,     0,     0,     0,     0,   197,
       0,     0,   200,   201,   202,   203,   204,   205,   206,   207,
     208,   209,   210,   195,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   200,   201,   202,   203,   204,   205,   206,
     207,   208,   209,   210,   200,   201,   202,   203,   204,   -68,
     -68,   -68,   -68,   -68,   -68
};

static const yytype_int16 yycheck[] =
{
       1,     7,     7,     1,     3,    13,     1,   105,    50,    12,
     105,    20,   128,     0,    15,    10,    12,    12,     0,    61,
      26,    16,   120,    39,     4,   120,    61,     7,    19,    32,
     128,   147,    12,   128,    12,    44,    44,    61,    16,    38,
      61,    42,    65,    44,    50,    51,    52,    53,    53,   147,
      56,    57,   147,    18,    57,    56,    57,    37,    61,    60,
      63,    64,    65,    61,     5,     6,    61,    65,    59,    10,
      65,    12,    78,     5,     6,    18,    18,    78,    10,    11,
      12,    20,    13,    12,    14,    65,    27,    28,    29,    30,
      18,    21,    22,    23,    35,    27,    28,    29,    30,   105,
      18,    56,    57,    35,   105,    61,    62,    18,   114,    65,
     116,    62,    16,   114,   120,   116,    57,    44,    13,   120,
     126,   127,   128,    78,    65,    57,     3,   128,    57,    16,
     246,   247,    61,    65,    63,    64,    65,   122,   123,   124,
      12,   147,   141,    50,    61,   261,   147,    61,   246,   247,
      44,   246,   247,    52,    53,    54,    15,    16,    16,   114,
      20,   116,    44,   261,    61,   150,   261,    26,     8,    42,
     155,   156,   178,    63,     5,     6,    41,   178,    16,    10,
      11,    12,    50,    51,    52,    57,    43,    59,   173,    61,
      43,    63,    64,    65,   179,   180,    27,    28,    29,    30,
      63,    63,    61,    62,    35,   190,     8,    59,    59,   215,
     195,   196,   197,   198,   199,   200,   201,   202,   203,   204,
     205,   206,     8,   208,   209,   210,    57,    36,    19,   214,
      56,    57,    17,     9,    65,     8,    16,    16,    16,    63,
     246,   247,    54,    59,   249,   246,   247,    31,    23,    66,
     256,    12,    78,   108,   108,   261,    39,   106,   178,   120,
     261,    32,   178,    53,   249,     4,     5,     6,     7,     8,
      57,    32,   116,    12,    -1,    14,    -1,   114,   104,   264,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   114,    -1,
     116,    -1,    -1,    32,    -1,    -1,    57,    -1,    37,    38,
      61,    62,    63,    64,    65,    66,    45,    -1,     5,     6,
      -1,    -1,    51,    10,    -1,    12,    -1,    -1,    57,    -1,
      -1,    -1,    61,    62,    63,    64,    65,    66,    -1,    -1,
      27,    28,    29,    30,    -1,    -1,    -1,    -1,    35,    -1,
      -1,    -1,    -1,    40,    -1,    -1,    -1,    -1,    -1,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,     5,     6,    -1,    -1,    65,    10,
      11,    12,    15,     5,     6,    -1,    -1,    20,    10,    11,
      12,    24,    25,    26,    -1,    12,    27,    28,    29,    30,
      -1,    -1,    -1,    -1,    35,    27,    28,    29,    30,    -1,
      -1,    -1,    -1,    35,     9,    32,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    57,    -1,    61,    -1,
      -1,    -1,    65,    -1,    65,    57,     9,    -1,    -1,    -1,
      57,    -1,    -1,    65,    61,    40,    63,    64,    65,    66,
      -1,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,     9,    40,    -1,    -1,
      -1,    -1,    -1,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,     9,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    40,    -1,    -1,
      -1,    -1,    -1,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,     9,    40,
      -1,    -1,    -1,    -1,    -1,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      -1,    15,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    40,
      24,    25,    26,    -1,    -1,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      16,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    -1,    -1,    -1,    -1,    -1,    61,    -1,    -1,
      -1,    65,    16,    -1,    40,    -1,    -1,    -1,    -1,    -1,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    16,    40,    -1,    -1,    -1,
      -1,    -1,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    -1,    -1,    40,
      -1,    -1,    -1,    -1,    -1,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      40,    -1,    -1,    -1,    -1,    -1,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    40,    -1,    -1,    -1,    -1,    -1,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    40,    -1,    -1,    -1,    -1,    -1,    -1,    47,
      -1,    -1,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    40,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    14,    21,    22,    23,    70,    71,    12,   102,    77,
      78,    79,     1,    61,    65,    85,    15,    16,    26,    61,
      62,    72,    73,    74,     0,    15,    20,    24,    25,    26,
      61,    65,   103,   104,   105,   108,   109,    39,    80,    81,
     102,    61,    61,    50,    61,    75,    76,    72,    61,   109,
      18,    18,    18,    20,   104,    13,    18,    18,    85,    77,
      18,    16,   102,    62,   102,    16,    44,    73,   109,    73,
     109,    73,   109,    15,   105,   109,    13,    32,    57,    62,
      63,    64,    66,   102,   106,   107,   108,   109,   110,   106,
       3,   102,    16,    75,    61,    59,    63,    64,   102,   107,
     109,   110,   111,   112,    44,    10,    12,    16,    82,    83,
      84,    85,    86,    16,    19,    59,    20,   107,     5,     6,
      10,    11,    27,    28,    29,    30,    35,    57,    87,    88,
      89,    90,    92,    94,    98,    99,   102,   109,    84,    83,
      86,    44,    32,   112,   111,    63,    11,    87,     4,     7,
       8,    14,    32,    37,    38,    45,    51,    62,    63,    64,
      66,    96,    97,    98,    99,   100,   101,   102,   107,   109,
     110,    96,    96,     8,   109,   109,    11,    89,    41,    42,
      43,    16,    13,    85,    59,    59,    11,    63,    96,    63,
       8,     8,    96,    96,    16,    40,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    16,    16,    96,    36,    19,    37,    91,    97,   101,
     102,   109,    93,    96,    95,    96,     9,    17,    96,     9,
      96,    96,    96,    96,    96,    96,    96,    96,    96,    96,
      96,    96,    96,    96,    96,    96,     9,    96,   109,     8,
      16,    16,    16,    63,     9,    89,    57,    89,    59,    96,
     108,    31,   109,     9,    20,    89,    96,     9
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    69,    70,    71,    71,    71,    71,    71,    72,    72,
      73,    73,    73,    74,    74,    74,    74,    74,    75,    75,
      76,    76,    78,    77,    79,    77,    80,    80,    81,    81,
      82,    82,    83,    83,    84,    84,    85,    85,    85,    86,
      86,    86,    87,    87,    88,    88,    89,    89,    89,    89,
      89,    89,    89,    89,    89,    89,    89,    90,    91,    91,
      91,    91,    91,    91,    92,    93,    94,    94,    94,    94,
      95,    96,    96,    96,    96,    96,    96,    96,    96,    96,
      96,    96,    96,    96,    96,    96,    96,    96,    96,    96,
      96,    96,    96,    96,    96,    96,    96,    96,    96,    96,
      96,    96,    96,    96,    96,    96,    97,    98,    99,   100,
     100,   101,   101,   102,   102,   103,   103,   103,   103,   104,
     104,   105,   105,   105,   105,   105,   105,   105,   105,   105,
     106,   106,   106,   106,   106,   106,   106,   106,   107,   107,
     108,   109,   110,   110,   110,   110,   111,   111,   112,   112,
     112,   112,   112,   112
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     3,     2,     2,     2,     2,     1,
       1,     1,     3,     3,     4,     3,     5,     1,     3,     1,
       2,     1,     0,     3,     0,     1,     1,     0,     5,     4,
       2,     1,     1,     3,     3,     1,     1,     1,     1,     3,
       2,     1,     1,     2,     3,     2,     1,     3,     3,     3,
       2,     4,     4,     4,     5,     7,     5,     1,     1,     1,
       1,     1,     4,     6,     1,     1,     1,     1,     1,     5,
       1,     3,     3,     3,     3,     2,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     2,     3,     1,
       1,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     1,     1,     4,     1,     1,     2,     4,
       2,     1,     2,     4,     3,     3,     1,     4,     2,     0,
       2,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       1,     1,     3,     2,     5,     5,     3,     1,     1,     1,
       1,     1,     1,     1
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
#line 166 "src/rulesyacc.y"
              {
	  DBUGPRT("axiom done...");
	  YYACCEPT;
	}
#line 1553 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 3: /* begin: TOKEN_RULES rules  */
#line 172 "src/rulesyacc.y"
                          {
	  DBUGPRT("begin rules");
	}
#line 1561 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 4: /* begin: TOKEN_INPUT term features  */
#line 176 "src/rulesyacc.y"
                                   {
	  DBUGPRT("begin input");
	  application.generator.setStartTerm((yyvsp[-1].integer_slot));
	  (*(yyvsp[0].features_slot))->renameVariables((*(yyvsp[0].features_slot))->getId());
	  application.generator.setStartFeatures(*(yyvsp[0].features_slot));
	  free((yyvsp[0].features_slot));
	}
#line 1573 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 5: /* begin: TOKEN_INPUT term  */
#line 184 "src/rulesyacc.y"
                          {
	  DBUGPRT("begin input");
	  application.generator.setStartTerm((yyvsp[0].integer_slot));
	  application.generator.setStartFeatures(Features::create());
	 }
#line 1583 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 6: /* begin: TOKEN_LEXICON dictionary  */
#line 190 "src/rulesyacc.y"
                                  {      
	  DBUGPRT("begin lexicon");
	}
#line 1591 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 7: /* begin: TOKEN_DASH features  */
#line 195 "src/rulesyacc.y"
        {
	  DBUGPRT("begin features");
	  application.generator.setLocalFeatures(*(yyvsp[0].features_slot));
	  free((yyvsp[0].features_slot));
	}
#line 1601 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 8: /* dictionary: dictionary_line dictionary  */
#line 202 "src/rulesyacc.y"
                                   {
	  DBUGPRT("dictionary");
	}
#line 1609 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 9: /* dictionary: dictionary_line  */
#line 206 "src/rulesyacc.y"
                         {
	  DBUGPRT("dictionary");
	 }
#line 1617 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 10: /* stringOrIdentifier: TOKEN_IDENTIFIER  */
#line 211 "src/rulesyacc.y"
                         {
	  DBUGPRT("stringOrIdentifier");
	  (yyval.string_slot) = (yyvsp[0].string_slot);
	}
#line 1626 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 11: /* stringOrIdentifier: TOKEN_STRING  */
#line 216 "src/rulesyacc.y"
                      {
	  DBUGPRT("stringOrIdentifier");
	  (yyval.string_slot) = (yyvsp[0].string_slot);
	 }
#line 1635 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 12: /* stringOrIdentifier: stringOrIdentifier TOKEN_PLUS TOKEN_STRING  */
#line 221 "src/rulesyacc.y"
                                                    {
	  DBUGPRT("string");
	  (yyval.string_slot) = (yyvsp[-2].string_slot);
	  *(yyval.string_slot) += *(yyvsp[0].string_slot);
	 }
#line 1645 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 13: /* dictionary_line: TOKEN_FORM TOKEN_IDENTIFIER TOKEN_SEMI  */
#line 230 "src/rulesyacc.y"
        {
	  DBUGPRT("dictionary_line");
	  unsigned int code = Vartable::identifierToCode(*(yyvsp[-1].string_slot));
	  free((yyvsp[-1].string_slot));
	  // constantNoun => (0 => args)
	  auto foundCode = application.generator.getLexicon().find(code);
	  Generator::entries_map *zeroToEntries;
	  if (foundCode != application.generator.getLexicon().end()){
	    zeroToEntries = foundCode->second;
	  } else {
	    zeroToEntries = new Generator::entries_map();
	    application.generator.getLexicon().insert(std::make_pair(code, zeroToEntries));
	  }
	  auto foundPred = zeroToEntries->find(0);
	  entriesPtr lp;
	  if (foundPred != zeroToEntries->end()){
	    lp = foundPred->second;
	  } else {
	    lp = Entries::create();
	    zeroToEntries->insert(std::make_pair(0, lp));
	  }
	  lp->add(Entry::create(code, UINT_MAX, std::string(), Features::create()));
	}
#line 1673 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 14: /* dictionary_line: TOKEN_FORM TOKEN_IDENTIFIER features TOKEN_SEMI  */
#line 255 "src/rulesyacc.y"
        {
	  DBUGPRT("dictionary_line");
	  unsigned int code=Vartable::identifierToCode(*(yyvsp[-2].string_slot));
	  free((yyvsp[-2].string_slot));
	  // constantNoun => (0 => args)
	  auto foundCode = application.generator.getLexicon().find(code);
	  Generator::entries_map *zeroToEntries;
	  if (foundCode != application.generator.getLexicon().end()) {
	    zeroToEntries=foundCode->second;
	  } else {
	    zeroToEntries = new Generator::entries_map;
	    application.generator.getLexicon().insert(std::make_pair(code, zeroToEntries));
	  }
	  auto foundPred = zeroToEntries->find(0);
	  entriesPtr lp;
	  if (foundPred!=zeroToEntries->end()){
	    lp = foundPred->second;
	  } else {
	    lp = Entries::create();
	    zeroToEntries->insert(std::make_pair(0, lp));
	  }
	  lp->add(Entry::create(code, UINT_MAX, std::string(), *(yyvsp[-1].features_slot)));
	  free((yyvsp[-1].features_slot));
	}
#line 1702 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 15: /* dictionary_line: stringOrIdentifier lexical_entries TOKEN_SEMI  */
#line 282 "src/rulesyacc.y"
        {
	  DBUGPRT("dictionary_line");
	  for (auto entry = (*(yyvsp[-1].entries_slot))->begin() ; entry != (*(yyvsp[-1].entries_slot))->end() ; ++entry) {
	    (*entry)->setForm(*(yyvsp[-2].string_slot));
	    entriesPtr lp;
	    Generator::entries_map *predToEntries;
	    //std::cerr << entry->getCode() << std::endl;
	    Generator::entries_map_map::iterator foundCode = application.generator.getLexicon().find((*entry)->getPos());
	    if (foundCode != application.generator.getLexicon().end()){
	      predToEntries = foundCode->second;
	    } else {
	      predToEntries = new Generator::entries_map;
	      application.generator.getLexicon().insert(std::make_pair((*entry)->getPos(), predToEntries));
	    }
	    Generator::entries_map::iterator foundPred = predToEntries->find((*entry)->getPred());
	    if (foundPred != predToEntries->end()){
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
#line 1733 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 16: /* dictionary_line: TOKEN_AROBASE TOKEN_IDENTIFIER TOKEN_COLON features TOKEN_SEMI  */
#line 311 "src/rulesyacc.y"
        {
	  DBUGPRT("dictionary_line");
	  application.generator.addMacros(*(yyvsp[-3].string_slot), *(yyvsp[-1].features_slot));
	  free((yyvsp[-3].string_slot));
	  free((yyvsp[-1].features_slot));
	  
	}
#line 1745 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 17: /* dictionary_line: TOKEN_SEMI  */
#line 320 "src/rulesyacc.y"
        {
	  DBUGPRT("dictionary_line");
	}
#line 1753 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 18: /* lexical_entries: lexical_entry TOKEN_PIPE lexical_entries  */
#line 326 "src/rulesyacc.y"
        {	  
	  DBUGPRT("lexical_entries");
	  (yyval.entries_slot) = (yyvsp[0].entries_slot);
	  (*(yyval.entries_slot))->add(*(yyvsp[-2].entry_slot));
	  free((yyvsp[-2].entry_slot));
	}
#line 1764 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 19: /* lexical_entries: lexical_entry  */
#line 333 "src/rulesyacc.y"
                       {
	  DBUGPRT("lexical_entries");
	  (yyval.entries_slot) = new entriesPtr(Entries::create(*(yyvsp[0].entry_slot)));
	  free((yyvsp[0].entry_slot));
	 }
#line 1774 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 20: /* lexical_entry: TOKEN_IDENTIFIER features  */
#line 342 "src/rulesyacc.y"
        {
	  DBUGPRT("lexical_entry");
	  unsigned int pred = (*(yyvsp[0].features_slot))->assignPred();
	  (yyval.entry_slot) = new entryPtr(Entry::create(Vartable::identifierToCode(*(yyvsp[-1].string_slot)), pred, std::string(), *(yyvsp[0].features_slot)));
	  free((yyvsp[-1].string_slot));
	  free((yyvsp[0].features_slot));
	}
#line 1786 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 21: /* lexical_entry: TOKEN_IDENTIFIER  */
#line 351 "src/rulesyacc.y"
        {
	  DBUGPRT("lexical_entry");
	  (yyval.entry_slot) = new entryPtr(Entry::create(Vartable::identifierToCode(*(yyvsp[0].string_slot)), UINT_MAX, std::string(), Features::create()));
	  free((yyvsp[0].string_slot));
	}
#line 1796 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 22: /* $@1: %empty  */
#line 361 "src/rulesyacc.y"
        {headLineno = ruleslineno;}
#line 1802 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 23: /* rules: $@1 rule rules  */
#line 362 "src/rulesyacc.y"
        {
	  DBUGPRT("rules"); 
	}
#line 1810 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 24: /* $@2: %empty  */
#line 366 "src/rulesyacc.y"
         {headLineno = ruleslineno;}
#line 1816 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 25: /* rules: $@2  */
#line 367 "src/rulesyacc.y"
        {
	  DBUGPRT("rules"); 
	}
#line 1824 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 26: /* pref_rule: TOKEN_TRACE  */
#line 373 "src/rulesyacc.y"
        {
	  DBUGPRT("pref_rule");
	  headTrace = true;
	}
#line 1833 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 27: /* pref_rule: %empty  */
#line 378 "src/rulesyacc.y"
                      {
	  DBUGPRT("pref_rule");
	  headTrace = false;
	}
#line 1842 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 28: /* rule: pref_rule term TOKEN_RIGHTARROW terms_vector structure_statement  */
#line 385 "src/rulesyacc.y"
        {
	  DBUGPRT("rule");
	  rulePtr rule = Rule::create(headLineno, application.generator.getTopBufferName(), (yyvsp[-3].integer_slot), *(yyvsp[-1].vector_terms_slot), (yyvsp[0].statements_slot) ? *(yyvsp[0].statements_slot) : statementsPtr());
	  rule->addDefaults();
	  rule->setTrace(headTrace);
	  application.generator.rules.addRule(rule);
      if (!application.generator.rules.getStartTerm()){
      	    application.generator.rules.setStartTerm((yyvsp[-3].integer_slot));
      }
      free((yyvsp[-1].vector_terms_slot));
	  if ((yyvsp[0].statements_slot))
	     free((yyvsp[0].statements_slot));
	}
#line 1860 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 29: /* rule: pref_rule term TOKEN_RIGHTARROW structure_statement  */
#line 400 "src/rulesyacc.y"
        {
	  DBUGPRT("Rule");
	  rulePtr rule = Rule::create(headLineno, application.generator.getTopBufferName(), (yyvsp[-2].integer_slot), (yyvsp[0].statements_slot) ? *(yyvsp[0].statements_slot) : statementsPtr());
	  rule->addDefaults();
	  rule->setTrace(headTrace);
	  application.generator.rules.addRule(rule);
	  if (!application.generator.rules.getStartTerm()){
	    application.generator.rules.setStartTerm((yyvsp[-2].integer_slot));
	  }
	  if ((yyvsp[0].statements_slot))
	    free((yyvsp[0].statements_slot));
	}
#line 1877 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 30: /* terms_vector: terms_vector terms  */
#line 414 "src/rulesyacc.y"
                           { 
	  DBUGPRT("term_vector");
	  (yyval.vector_terms_slot)=(yyvsp[-1].vector_terms_slot);
	  (yyval.vector_terms_slot)->push_back(*(yyvsp[0].terms_slot));
	}
#line 1887 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 31: /* terms_vector: terms  */
#line 420 "src/rulesyacc.y"
               { 
	  DBUGPRT("term_vector"); 
	  (yyval.vector_terms_slot) = new std::vector< termsPtr >;
	  (yyval.vector_terms_slot)->push_back(*(yyvsp[0].terms_slot));
	}
#line 1897 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 32: /* terms: terms_disj  */
#line 427 "src/rulesyacc.y"
                   { 
	  DBUGPRT("term");
	  (yyval.terms_slot)=(yyvsp[0].terms_slot);
	}
#line 1906 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 33: /* terms: TOKEN_LBRACKET terms_disj TOKEN_RBRACKET  */
#line 432 "src/rulesyacc.y"
                                                  { 
	  DBUGPRT("term");
	  (yyval.terms_slot) = (yyvsp[-1].terms_slot);
	  (*(yyval.terms_slot))->setOptional();
	}
#line 1916 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 34: /* terms_disj: terms_disj TOKEN_PIPE term  */
#line 440 "src/rulesyacc.y"
        { 
	  DBUGPRT("term_disj");
	  (yyval.terms_slot) = (yyvsp[-2].terms_slot);
	  (*(yyval.terms_slot))->push_back((yyvsp[0].integer_slot));
	}
#line 1926 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 35: /* terms_disj: term  */
#line 447 "src/rulesyacc.y"
        { 
	  DBUGPRT("term_disj"); 
	  (yyval.terms_slot) = new termsPtr(Terms::create((yyvsp[0].integer_slot)));
	}
#line 1935 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 36: /* term: TOKEN_IDENTIFIER  */
#line 454 "src/rulesyacc.y"
        { 
	  DBUGPRT("term_id");
	  (yyval.integer_slot) = Vartable::identifierToCode(*(yyvsp[0].string_slot));
	  free((yyvsp[0].string_slot));
	}
#line 1945 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 37: /* term: TOKEN_VARIABLE  */
#line 461 "src/rulesyacc.y"
        { 
	  DBUGPRT("term_id");
	  (yyval.integer_slot) = Vartable::identifierToCode(*(yyvsp[0].string_slot));
	  free((yyvsp[0].string_slot));
	}
#line 1955 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 38: /* term: error  */
#line 468 "src/rulesyacc.y"
        {
	  YYABORT;
	}
#line 1963 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 39: /* structure_statement: TOKEN_LBRACE list_statement TOKEN_RBRACE  */
#line 477 "src/rulesyacc.y"
        {
	  DBUGPRT("structure_statement");
	  (yyval.statements_slot)=(yyvsp[-1].statements_slot);
	}
#line 1972 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 40: /* structure_statement: TOKEN_LBRACE TOKEN_RBRACE  */
#line 483 "src/rulesyacc.y"
        {
	  (yyval.statements_slot)=NULL;
	}
#line 1980 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 41: /* structure_statement: TOKEN_SEMI  */
#line 488 "src/rulesyacc.y"
        {
	  (yyval.statements_slot)=NULL;
	}
#line 1988 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 42: /* list_statement: statement  */
#line 494 "src/rulesyacc.y"
        {
	  DBUGPRT("list_statement");
	  (yyval.statements_slot) = new statementsPtr(Statements::create());
	  (*(yyval.statements_slot))->addStatement(*(yyvsp[0].statement_slot));
	  free((yyvsp[0].statement_slot));
	}
#line 1999 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 43: /* list_statement: list_statement statement  */
#line 501 "src/rulesyacc.y"
                                  {
	  DBUGPRT("list_statement");
	  (yyval.statements_slot) = (yyvsp[-1].statements_slot);
	  (*(yyval.statements_slot))->addStatement(*(yyvsp[0].statement_slot));
	  free((yyvsp[0].statement_slot));
	}
#line 2010 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 44: /* statements: TOKEN_LBRACE list_statement TOKEN_RBRACE  */
#line 510 "src/rulesyacc.y"
        {
	  DBUGPRT("statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::STMS, *(yyvsp[-1].statements_slot)));
	  free((yyvsp[-1].statements_slot));
	}
#line 2020 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 45: /* statements: TOKEN_LBRACE TOKEN_RBRACE  */
#line 517 "src/rulesyacc.y"
        {
	  DBUGPRT("statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::STMS, Statements::create()));
	}
#line 2029 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 46: /* statement: statements  */
#line 523 "src/rulesyacc.y"
                   {
	  DBUGPRT("statement");
	  (yyval.statement_slot)=(yyvsp[0].statement_slot);
	 }
#line 2038 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 47: /* statement: TOKEN_ATTEST expression_statement TOKEN_SEMI  */
#line 528 "src/rulesyacc.y"
                                                      {
	  DBUGPRT("statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::ATTEST, *(yyvsp[-1].statement_slot)));
	  free((yyvsp[-1].statement_slot));
	}
#line 2048 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 48: /* statement: TOKEN_PRINT expression_statement TOKEN_SEMI  */
#line 534 "src/rulesyacc.y"
                                                     {
	  DBUGPRT("statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::PRINT, *(yyvsp[-1].statement_slot)));
	  free((yyvsp[-1].statement_slot));
	}
#line 2058 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 49: /* statement: TOKEN_PRINTLN expression_statement TOKEN_SEMI  */
#line 540 "src/rulesyacc.y"
                                                       {
	  DBUGPRT("statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::PRINTLN, *(yyvsp[-1].statement_slot)));
	  free((yyvsp[-1].statement_slot));
	}
#line 2068 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 50: /* statement: features TOKEN_SEMI  */
#line 546 "src/rulesyacc.y"
                             {
	  DBUGPRT("statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::GUARD, *(yyvsp[-1].features_slot)));
	  free((yyvsp[-1].features_slot));
	}
#line 2078 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 51: /* statement: left_hand_side_aff_statement TOKEN_AFF right_hand_side_aff_statement TOKEN_SEMI  */
#line 552 "src/rulesyacc.y"
                                                                                         {
	  DBUGPRT("statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::AFF, *(yyvsp[-3].statement_slot), *(yyvsp[-1].statement_slot)));
	  // <X, …> = <…>
	  // <X, …> = $X
	  if (((*(yyvsp[-3].statement_slot))->isList()) && (((*(yyvsp[-1].statement_slot))->isList())||((*(yyvsp[-1].statement_slot))->isVariable()))) {
    	  //OK
	  }
	  // ↓i = $X
	  // ↓i = […]
	  // ↓i = ↑
	  // ↓i = … ∪ …
	  // ↓i = ⇓j
	  else if (((*(yyvsp[-3].statement_slot))->isDown()) && (((*(yyvsp[-1].statement_slot))->isVariable())||((*(yyvsp[-1].statement_slot))->isFeatures())||((*(yyvsp[-1].statement_slot))->isUp())||((*(yyvsp[-1].statement_slot))->isUnif())||((*(yyvsp[-1].statement_slot))->isDown2()))){
	      // OK
	  }
	  // ⇑ = $X
	  // ⇑ = […]
	  // ⇑ = ↑
	  // ⇑ = … ∪ …
	  // ⇑ = ⇓j
	  else if (((*(yyvsp[-3].statement_slot))->isUp2()) && (((*(yyvsp[-1].statement_slot))->isVariable())||((*(yyvsp[-1].statement_slot))->isFeatures())||((*(yyvsp[-1].statement_slot))->isUp())||((*(yyvsp[-1].statement_slot))->isUnif())||((*(yyvsp[-1].statement_slot))->isDown2()))){
	    // OK
	  }
	  // $X = Y
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
		      ||((*(yyvsp[-1].statement_slot))->isSearch()))){
	    // OK
	  }
	  else {
	    yyerror((char*)"syntax error");
	  }
	  free((yyvsp[-3].statement_slot));
	  free((yyvsp[-1].statement_slot));
	}
#line 2135 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 52: /* statement: left_hand_side_subset_statement TOKEN_SUBSUME right_hand_side_subset_statement TOKEN_SEMI  */
#line 605 "src/rulesyacc.y"
                                                                                                   {
	  DBUGPRT("statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::SUBSUME, (*(yyvsp[-3].statement_slot)), (*(yyvsp[-1].statement_slot))));
	  // […] ⊂ ↑ 
	  // […] ⊂ ⇓j 
	  // […] ⊂ $X 
	  // […] ⊂ search  
	  if (((*(yyvsp[-3].statement_slot))->isFeatures()) && (((*(yyvsp[-1].statement_slot))->isUp())||((*(yyvsp[-1].statement_slot))->isDown2())||((*(yyvsp[-1].statement_slot))->isVariable())||((*(yyvsp[-1].statement_slot))->isSearch()))) {
        }
	  else {
	    yyerror((char *)"syntax error");
	  }
	  free((yyvsp[-3].statement_slot));
	  free((yyvsp[-1].statement_slot));
	}
#line 2155 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 53: /* statement: left_hand_side_inset_statement TOKEN_INSET right_hand_side_inset_statement TOKEN_SEMI  */
#line 621 "src/rulesyacc.y"
                                                                                               {
	  DBUGPRT("statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::INSET, (*(yyvsp[-3].statement_slot)), (*(yyvsp[-1].statement_slot))));
	  // ↓i ∈ <...>
	  if (((*(yyvsp[-3].statement_slot))->isDown())
	       && (((*(yyvsp[-1].statement_slot))->isList())))
	    ;
	    else 
	  yyerror((char *)"syntax error");
	  free((yyvsp[-3].statement_slot));
	  free((yyvsp[-1].statement_slot));
	}
#line 2172 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 54: /* statement: TOKEN_IF TOKEN_LPAR expression_statement TOKEN_RPAR statement  */
#line 634 "src/rulesyacc.y"
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
#line 2194 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 55: /* statement: TOKEN_IF TOKEN_LPAR expression_statement TOKEN_RPAR statement TOKEN_ELSE statement  */
#line 652 "src/rulesyacc.y"
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
#line 2225 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 56: /* statement: TOKEN_FOREACH variable TOKEN_IN expression_statement statement  */
#line 679 "src/rulesyacc.y"
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
#line 2248 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 57: /* left_hand_side_subset_statement: features  */
#line 699 "src/rulesyacc.y"
                 {
	  DBUGPRT("left_hand_side_subset_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::FEATURES, *(yyvsp[0].features_slot)));
	  free((yyvsp[0].features_slot));
	}
#line 2258 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 58: /* right_hand_side_subset_statement: variable  */
#line 706 "src/rulesyacc.y"
                 {
	  DBUGPRT("right_hand_side_subset_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::VARIABLE, *(yyvsp[0].bits_slot)));
	  free((yyvsp[0].bits_slot));
	}
#line 2268 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 59: /* right_hand_side_subset_statement: up  */
#line 712 "src/rulesyacc.y"
            {
	  DBUGPRT("right_hand_side_subset_statement");
	  (yyval.statement_slot)=(yyvsp[0].statement_slot);
	}
#line 2277 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 60: /* right_hand_side_subset_statement: downdouble  */
#line 717 "src/rulesyacc.y"
                    {
	  DBUGPRT("right_hand_side_subset_statement");
	  (yyval.statement_slot)=(yyvsp[0].statement_slot);
	}
#line 2286 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 61: /* right_hand_side_subset_statement: features  */
#line 722 "src/rulesyacc.y"
                  {
	  DBUGPRT("right_hand_side_subset_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::FEATURES, *(yyvsp[0].features_slot)));
	  free((yyvsp[0].features_slot));
	}
#line 2296 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 62: /* right_hand_side_subset_statement: TOKEN_SEARCH TOKEN_LPAR expression_statement TOKEN_RPAR  */
#line 728 "src/rulesyacc.y"
                                                                  {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno,
						  Statement::SEARCH,
						  *(yyvsp[-1].statement_slot)));
	  free((yyvsp[-1].statement_slot));
	 }
#line 2308 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 63: /* right_hand_side_subset_statement: TOKEN_SEARCH TOKEN_LPAR identifier TOKEN_COMMA expression_statement TOKEN_RPAR  */
#line 736 "src/rulesyacc.y"
                                                                                         {
	  DBUGPRT("right_hand_side_subset_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno,
						  Statement::SEARCH,
						  *(yyvsp[-3].bits_slot),
						  *(yyvsp[-1].statement_slot)));
	  free((yyvsp[-3].bits_slot));
	  free((yyvsp[-1].statement_slot));
	 }
#line 2322 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 64: /* left_hand_side_inset_statement: down  */
#line 747 "src/rulesyacc.y"
             {
	  DBUGPRT("left_hand_side_statement");
	  (yyval.statement_slot)=(yyvsp[0].statement_slot);
	}
#line 2331 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 65: /* right_hand_side_inset_statement: expression_statement  */
#line 753 "src/rulesyacc.y"
                             {
	  DBUGPRT("right_hand_side_statement");
	  (yyval.statement_slot)=(yyvsp[0].statement_slot);
	}
#line 2340 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 66: /* left_hand_side_aff_statement: updouble  */
#line 759 "src/rulesyacc.y"
                 {
	  DBUGPRT("left_hand_side_statement");
	  (yyval.statement_slot)=(yyvsp[0].statement_slot);
	}
#line 2349 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 67: /* left_hand_side_aff_statement: down  */
#line 764 "src/rulesyacc.y"
              {
	  DBUGPRT("left_hand_side_statement");
	  (yyval.statement_slot)=(yyvsp[0].statement_slot);
	}
#line 2358 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 68: /* left_hand_side_aff_statement: variable  */
#line 769 "src/rulesyacc.y"
                  {
	  DBUGPRT("left_hand_side_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::VARIABLE, *(yyvsp[0].bits_slot)));
	  free((yyvsp[0].bits_slot));
	 }
#line 2368 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 69: /* left_hand_side_aff_statement: TOKEN_LT variable TOKEN_DOUBLECOLON variable TOKEN_GT  */
#line 776 "src/rulesyacc.y"
        {
	  DBUGPRT("left_hand_side_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::LIST,
						List::create(List::create(Value::create(Value::_VARIABLE, *(yyvsp[-3].bits_slot))),
							     List::create(Value::create(Value::_VARIABLE, *(yyvsp[-1].bits_slot))))));
	  free((yyvsp[-3].bits_slot));
	  free((yyvsp[-1].bits_slot));
	}
#line 2381 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 70: /* right_hand_side_aff_statement: expression_statement  */
#line 786 "src/rulesyacc.y"
                             {
	  DBUGPRT("right_hand_side_statement");
	  (yyval.statement_slot)=(yyvsp[0].statement_slot);
	}
#line 2390 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 71: /* expression_statement: expression_statement TOKEN_OR expression_statement  */
#line 795 "src/rulesyacc.y"
                                                           {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::FCT, Statement::OR, (*(yyvsp[-2].statement_slot)), (*(yyvsp[0].statement_slot))));
	  free((yyvsp[-2].statement_slot));
	  free((yyvsp[0].statement_slot));
	}
#line 2401 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 72: /* expression_statement: expression_statement TOKEN_AND expression_statement  */
#line 802 "src/rulesyacc.y"
                                                             {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::FCT, Statement::AND, (*(yyvsp[-2].statement_slot)), (*(yyvsp[0].statement_slot))));
	  free((yyvsp[-2].statement_slot));
	  free((yyvsp[0].statement_slot));
	}
#line 2412 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 73: /* expression_statement: expression_statement TOKEN_IMPLICATION expression_statement  */
#line 809 "src/rulesyacc.y"
                                                                     {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::FCT, Statement::OR, Statement::create(ruleslineno, Statement::FCT, Statement::NOT, (*(yyvsp[-2].statement_slot))), (*(yyvsp[0].statement_slot))));
	  free((yyvsp[-2].statement_slot));
	  free((yyvsp[0].statement_slot));
	}
#line 2423 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 74: /* expression_statement: expression_statement TOKEN_EQUIV expression_statement  */
#line 816 "src/rulesyacc.y"
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
#line 2440 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 75: /* expression_statement: TOKEN_NOT expression_statement  */
#line 829 "src/rulesyacc.y"
                                        {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::FCT, Statement::NOT, (*(yyvsp[0].statement_slot))));
	  free((yyvsp[0].statement_slot));
	}
#line 2450 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 76: /* expression_statement: expression_statement TOKEN_EQUAL expression_statement  */
#line 835 "src/rulesyacc.y"
                                                               {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::FCT, Statement::EQ, (*(yyvsp[-2].statement_slot)), (*(yyvsp[0].statement_slot))));
	  free((yyvsp[-2].statement_slot));
	  free((yyvsp[0].statement_slot));
	}
#line 2461 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 77: /* expression_statement: expression_statement TOKEN_DIFF expression_statement  */
#line 842 "src/rulesyacc.y"
                                                              { 
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::FCT, Statement::DIFF, (*(yyvsp[-2].statement_slot)), (*(yyvsp[0].statement_slot)))); 
	  free((yyvsp[-2].statement_slot));
	  free((yyvsp[0].statement_slot));
	}
#line 2472 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 78: /* expression_statement: expression_statement TOKEN_LT expression_statement  */
#line 849 "src/rulesyacc.y"
                                                            { 
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::FCT, Statement::LT, (*(yyvsp[-2].statement_slot)), (*(yyvsp[0].statement_slot)))); 
	  free((yyvsp[-2].statement_slot));
	  free((yyvsp[0].statement_slot));
	}
#line 2483 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 79: /* expression_statement: expression_statement TOKEN_LE expression_statement  */
#line 856 "src/rulesyacc.y"
                                                            { 
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::FCT, Statement::LE, (*(yyvsp[-2].statement_slot)), (*(yyvsp[0].statement_slot)))); 
	  free((yyvsp[-2].statement_slot));
	  free((yyvsp[0].statement_slot));
	}
#line 2494 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 80: /* expression_statement: expression_statement TOKEN_GT expression_statement  */
#line 863 "src/rulesyacc.y"
                                                            { 
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::FCT, Statement::GT, (*(yyvsp[-2].statement_slot)), (*(yyvsp[0].statement_slot)))); 
	  free((yyvsp[-2].statement_slot));
	  free((yyvsp[0].statement_slot));
	}
#line 2505 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 81: /* expression_statement: expression_statement TOKEN_GE expression_statement  */
#line 870 "src/rulesyacc.y"
                                                            { 
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::FCT, Statement::GE, (*(yyvsp[-2].statement_slot)), (*(yyvsp[0].statement_slot)))); 
	  free((yyvsp[-2].statement_slot));
	  free((yyvsp[0].statement_slot));
	}
#line 2516 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 82: /* expression_statement: expression_statement TOKEN_PLUS expression_statement  */
#line 881 "src/rulesyacc.y"
        {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::FCT, Statement::PLUS, (*(yyvsp[-2].statement_slot)), (*(yyvsp[0].statement_slot))));
	  free((yyvsp[-2].statement_slot));
	  free((yyvsp[0].statement_slot));
	}
#line 2527 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 83: /* expression_statement: expression_statement TOKEN_MINUS expression_statement  */
#line 889 "src/rulesyacc.y"
        {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::FCT, Statement::MINUS, (*(yyvsp[-2].statement_slot)), (*(yyvsp[0].statement_slot))));
	  free((yyvsp[-2].statement_slot));
	  free((yyvsp[0].statement_slot));
	}
#line 2538 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 84: /* expression_statement: expression_statement TOKEN_TIMES expression_statement  */
#line 897 "src/rulesyacc.y"
        {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::FCT, Statement::TIMES, (*(yyvsp[-2].statement_slot)), (*(yyvsp[0].statement_slot))));
	  free((yyvsp[-2].statement_slot));
	  free((yyvsp[0].statement_slot));
	}
#line 2549 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 85: /* expression_statement: expression_statement TOKEN_DIVIDE expression_statement  */
#line 905 "src/rulesyacc.y"
        {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::FCT, Statement::DIVIDE, (*(yyvsp[-2].statement_slot)), (*(yyvsp[0].statement_slot))));
	  free((yyvsp[-2].statement_slot));
	  free((yyvsp[0].statement_slot));
	}
#line 2560 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 86: /* expression_statement: expression_statement TOKEN_MODULO expression_statement  */
#line 913 "src/rulesyacc.y"
        {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::FCT, Statement::MODULO, (*(yyvsp[-2].statement_slot)), (*(yyvsp[0].statement_slot))));
	  free((yyvsp[-2].statement_slot));
	  free((yyvsp[0].statement_slot));
	}
#line 2571 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 87: /* expression_statement: TOKEN_MINUS expression_statement  */
#line 921 "src/rulesyacc.y"
        {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::FCT, Statement::MINUS_U, (*(yyvsp[0].statement_slot)), statementPtr()));
	  free((yyvsp[0].statement_slot));
	}
#line 2581 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 88: /* expression_statement: TOKEN_RAND TOKEN_LPAR TOKEN_RPAR  */
#line 928 "src/rulesyacc.y"
        {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::FCT, Statement::RAND));
	}
#line 2590 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 89: /* expression_statement: TOKEN_DOUBLE  */
#line 934 "src/rulesyacc.y"
        {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::NUMBER, (yyvsp[0].double_slot)));
	}
#line 2599 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 90: /* expression_statement: TOKEN_INTEGER  */
#line 940 "src/rulesyacc.y"
        {
	  DBUGPRT("expression_statement");
 	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::NUMBER, (double)(yyvsp[0].integer_slot)));
	}
#line 2608 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 91: /* expression_statement: TOKEN_STRING  */
#line 946 "src/rulesyacc.y"
        {
	  DBUGPRT("expression_statement");
 	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::STR, *(yyvsp[0].string_slot)));
	}
#line 2617 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 92: /* expression_statement: expression_statement TOKEN_UNION expression_statement  */
#line 954 "src/rulesyacc.y"
                                                               {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::UNIF, (*(yyvsp[-2].statement_slot)), (*(yyvsp[0].statement_slot))));
	  free((yyvsp[-2].statement_slot));
	  free((yyvsp[0].statement_slot));
	}
#line 2628 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 93: /* expression_statement: up  */
#line 961 "src/rulesyacc.y"
            {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot)=(yyvsp[0].statement_slot);
	}
#line 2637 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 94: /* expression_statement: updouble  */
#line 966 "src/rulesyacc.y"
                  {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot)=(yyvsp[0].statement_slot);
	}
#line 2646 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 95: /* expression_statement: down  */
#line 971 "src/rulesyacc.y"
              {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot)=(yyvsp[0].statement_slot);
	}
#line 2655 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 96: /* expression_statement: downdouble  */
#line 976 "src/rulesyacc.y"
                    {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot)=(yyvsp[0].statement_slot);
	}
#line 2664 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 97: /* expression_statement: features  */
#line 981 "src/rulesyacc.y"
                  {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::FEATURES, *(yyvsp[0].features_slot)));
	  free((yyvsp[0].features_slot));
	}
#line 2674 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 98: /* expression_statement: TOKEN_NIL  */
#line 988 "src/rulesyacc.y"
        {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::NIL));
	}
#line 2683 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 99: /* expression_statement: constant  */
#line 993 "src/rulesyacc.y"
                  {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::CONSTANT, *(yyvsp[0].bits_slot)));
	  free((yyvsp[0].bits_slot));
	}
#line 2693 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 100: /* expression_statement: TOKEN_ANONYMOUS  */
#line 1000 "src/rulesyacc.y"
        {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::ANONYMOUS, Value::ANONYMOUS_VALUE));
	}
#line 2702 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 101: /* expression_statement: variable  */
#line 1005 "src/rulesyacc.y"
                  {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::VARIABLE, *(yyvsp[0].bits_slot)));
	  free((yyvsp[0].bits_slot));
	}
#line 2712 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 102: /* expression_statement: TOKEN_LPAR expression_statement TOKEN_RPAR  */
#line 1011 "src/rulesyacc.y"
                                                    {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot)=(yyvsp[-1].statement_slot);
	}
#line 2721 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 103: /* expression_statement: list  */
#line 1016 "src/rulesyacc.y"
              {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::LIST, *(yyvsp[0].list_slot)));
	  free((yyvsp[0].list_slot));
	}
#line 2731 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 104: /* expression_statement: dash_statement  */
#line 1022 "src/rulesyacc.y"
                        {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot)=(yyvsp[0].statement_slot);
	}
#line 2740 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 105: /* expression_statement: TOKEN_SEARCH TOKEN_LPAR expression_statement TOKEN_RPAR  */
#line 1027 "src/rulesyacc.y"
                                                                  {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno,
						  Statement::SEARCH,
						  *(yyvsp[-1].statement_slot)));
	  free((yyvsp[-1].statement_slot));
	 }
#line 2752 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 106: /* up: TOKEN_UPARROW  */
#line 1036 "src/rulesyacc.y"
                      {  
	  DBUGPRT("up");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::UP));
	}
#line 2761 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 107: /* updouble: TOKEN_UP2ARROW  */
#line 1042 "src/rulesyacc.y"
                       {  
	  DBUGPRT("updouble");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::UP2));
	}
#line 2770 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 108: /* down: TOKEN_DOWNARROW TOKEN_INTEGER  */
#line 1049 "src/rulesyacc.y"
        { 
	  DBUGPRT("down");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::DOWN, (unsigned int)(yyvsp[0].integer_slot)-1)); 
	}
#line 2779 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 109: /* dash_statement: TOKEN_DASH TOKEN_INTEGER TOKEN_DOT TOKEN_INTEGER  */
#line 1056 "src/rulesyacc.y"
        { 
	  DBUGPRT("dash_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::DASH, (unsigned int)((yyvsp[-2].integer_slot)-1), (unsigned int)((yyvsp[0].integer_slot)-1))); 
	}
#line 2788 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 110: /* dash_statement: TOKEN_DASH TOKEN_INTEGER  */
#line 1062 "src/rulesyacc.y"
        { 
	  DBUGPRT("dash_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::DASH, (unsigned int)((yyvsp[0].integer_slot)-1))); 
	}
#line 2797 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 111: /* downdouble: TOKEN_DOWN2ARROW  */
#line 1068 "src/rulesyacc.y"
                         {  
	  DBUGPRT("downdouble");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::DOWN2, (unsigned int)0)); 
	}
#line 2806 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 112: /* downdouble: TOKEN_DOWN2ARROW TOKEN_INTEGER  */
#line 1074 "src/rulesyacc.y"
        { 
	  DBUGPRT("downdouble");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::DOWN2, (unsigned int)((yyvsp[0].integer_slot)-1))); 
	}
#line 2815 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 113: /* features: TOKEN_LBRACKET features_components_head features_components_tail TOKEN_RBRACKET  */
#line 1084 "src/rulesyacc.y"
        {
	  DBUGPRT("features");
 	  (yyval.features_slot) = (yyvsp[-2].features_slot);
	  if ((yyvsp[-1].feature_slot)){
	    (*(yyval.features_slot))->add(*(yyvsp[-1].feature_slot));
	    free((yyvsp[-1].feature_slot));
	  }
	}
#line 2828 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 114: /* features: TOKEN_LBRACKET features_components_tail TOKEN_RBRACKET  */
#line 1094 "src/rulesyacc.y"
        {
	  DBUGPRT("features");
	  (yyval.features_slot) = new featuresPtr(Features::create());
	  if ((yyvsp[-1].feature_slot)){
	    (*(yyval.features_slot))->add(*(yyvsp[-1].feature_slot));
	    free((yyvsp[-1].feature_slot));
	  }
	}
#line 2841 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 115: /* features_components_head: features_components_head TOKEN_COMMA feature  */
#line 1105 "src/rulesyacc.y"
        {
	  DBUGPRT("features_components_head");
	  (yyval.features_slot) = (yyvsp[-2].features_slot);
	  (*(yyval.features_slot))->add(*(yyvsp[0].feature_slot));
	  free((yyvsp[0].feature_slot));
	}
#line 2852 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 116: /* features_components_head: feature  */
#line 1113 "src/rulesyacc.y"
        {
	  DBUGPRT("features_components_head");
	  (yyval.features_slot) = new featuresPtr(Features::create());
	  (*(yyval.features_slot))->add(*(yyvsp[0].feature_slot));
	  free((yyvsp[0].feature_slot));
	}
#line 2863 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 117: /* features_components_head: features_components_head TOKEN_COMMA TOKEN_AROBASE TOKEN_IDENTIFIER  */
#line 1122 "src/rulesyacc.y"
        {
	  DBUGPRT("features_components_head");
	  featuresPtr found = application.generator.findMacros(*(yyvsp[0].string_slot));
	  (yyval.features_slot) = (yyvsp[-3].features_slot);
	  if (!(found)){
	     std::ostringstream oss; oss << "unknown macro: @" << *(yyvsp[0].string_slot);
	     yyerror((char*)oss.str().c_str());
	  } else {
	    (*(yyval.features_slot))->add(found->clone());
	  }
	  free((yyvsp[0].string_slot));
    }
#line 2880 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 118: /* features_components_head: TOKEN_AROBASE TOKEN_IDENTIFIER  */
#line 1137 "src/rulesyacc.y"
        {
	  DBUGPRT("features_components_head");
	  featuresPtr found = application.generator.findMacros(*(yyvsp[0].string_slot));
	  (yyval.features_slot) = new featuresPtr(Features::create());
	  if (!(found)){
	    std::ostringstream oss; oss << "***unknown macro: @" << *(yyvsp[0].string_slot);
	    yyerror((char*)oss.str().c_str());
	  } else {
	    (*(yyval.features_slot))->add(found->clone());
	  }
	  free((yyvsp[0].string_slot));
      }
#line 2897 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 119: /* features_components_tail: %empty  */
#line 1153 "src/rulesyacc.y"
    {
	  DBUGPRT("features_components_tail");
      (yyval.feature_slot) = NULL;
    }
#line 2906 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 120: /* features_components_tail: TOKEN_COMMA variable  */
#line 1160 "src/rulesyacc.y"
        {
	  DBUGPRT("features_components_tail");
	  (yyval.feature_slot) = new featurePtr(Feature::create(Feature::VARIABLE, *(yyvsp[0].bits_slot), valuePtr()));
    }
#line 2915 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 121: /* feature: TOKEN_LEMMA TOKEN_COLON stringOrIdentifier  */
#line 1169 "src/rulesyacc.y"
        {
	  DBUGPRT("feature");
	  (yyval.feature_slot) = new featurePtr(Feature::create(Feature::LEMMA, bitsetPtr(), Value::create(Value::_CODE, *(yyvsp[0].string_slot))));
	}
#line 2924 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 122: /* feature: TOKEN_LEMMA TOKEN_COLON variable  */
#line 1176 "src/rulesyacc.y"
        {
	  DBUGPRT("feature");
	  (yyval.feature_slot) = new featurePtr(Feature::create(Feature::LEMMA, bitsetPtr(), Value::create(Value::_VARIABLE, *(yyvsp[0].bits_slot))));
	}
#line 2933 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 123: /* feature: TOKEN_PRED TOKEN_COLON stringOrIdentifier  */
#line 1183 "src/rulesyacc.y"
        {
	  DBUGPRT("feature");
	  (yyval.feature_slot) = new featurePtr(Feature::create(Feature::PRED, bitsetPtr(), Value::create(Value::_CODE, *(yyvsp[0].string_slot))));
	}
#line 2942 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 124: /* feature: TOKEN_PRED TOKEN_COLON variable  */
#line 1190 "src/rulesyacc.y"
        {
	  DBUGPRT("feature");
	  (yyval.feature_slot) = new featurePtr(Feature::create(Feature::PRED, bitsetPtr(), Value::create(Value::_VARIABLE, *(yyvsp[0].bits_slot))));
	  free((yyvsp[0].bits_slot));
	}
#line 2952 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 125: /* feature: TOKEN_FORM TOKEN_COLON variable  */
#line 1198 "src/rulesyacc.y"
        {
	  DBUGPRT("feature");
	  (yyval.feature_slot) = new featurePtr(Feature::create(Feature::FORM, bitsetPtr(), Value::create(Value::_VARIABLE, *(yyvsp[0].bits_slot))));
	  free((yyvsp[0].bits_slot));
	}
#line 2962 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 126: /* feature: TOKEN_FORM TOKEN_COLON stringOrIdentifier  */
#line 1206 "src/rulesyacc.y"
        {
	  DBUGPRT("feature");
	  (yyval.feature_slot) = new featurePtr(Feature::create(Feature::FORM, bitsetPtr(), Value::create(Value::_FORM, *(yyvsp[0].string_slot))));
	}
#line 2971 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 127: /* feature: identifier TOKEN_COLON feature_value  */
#line 1213 "src/rulesyacc.y"
        {
	  DBUGPRT("feature");
	  (yyval.feature_slot) = new featurePtr(Feature::create(Feature::CONSTANT, *(yyvsp[-2].bits_slot), *(yyvsp[0].value_slot)));
	  free((yyvsp[-2].bits_slot));
	  free((yyvsp[0].value_slot));
	}
#line 2982 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 128: /* feature: identifier TOKEN_COLON TOKEN_STRING  */
#line 1222 "src/rulesyacc.y"
        {
	  DBUGPRT("feature");
	  (yyval.feature_slot) = new featurePtr(Feature::create(Feature::CONSTANT, *(yyvsp[-2].bits_slot), Value::create(Value::_FORM, *(yyvsp[0].string_slot))));
	  free((yyvsp[-2].bits_slot));
	}
#line 2992 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 129: /* feature: variable TOKEN_COLON feature_value  */
#line 1230 "src/rulesyacc.y"
        {
	  DBUGPRT("feature");
	  (yyval.feature_slot) = new featurePtr(Feature::create(Feature::VARIABLE, *(yyvsp[-2].bits_slot), *(yyvsp[0].value_slot)));
	  free((yyvsp[-2].bits_slot));
	  free((yyvsp[0].value_slot));
	}
#line 3003 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 130: /* feature_value: variable  */
#line 1247 "src/rulesyacc.y"
        {
	  DBUGPRT("feature_value");
	  (yyval.value_slot) = new valuePtr(Value::create(Value::_VARIABLE, *(yyvsp[0].bits_slot)));
	  free((yyvsp[0].bits_slot));
	}
#line 3013 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 131: /* feature_value: constant  */
#line 1254 "src/rulesyacc.y"
        {
	  DBUGPRT("feature_value");
	  (yyval.value_slot) = new valuePtr(Value::create(Value::_CONSTANT, *(yyvsp[0].bits_slot)));
	  free((yyvsp[0].bits_slot));
	}
#line 3023 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 132: /* feature_value: TOKEN_DOUBLE  */
#line 1261 "src/rulesyacc.y"
        {
	  DBUGPRT("expression_statement");
	  (yyval.value_slot) = new valuePtr(Value::create(Value::_NUMBER, (yyvsp[0].double_slot)));
	}
#line 3032 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 133: /* feature_value: TOKEN_INTEGER  */
#line 1267 "src/rulesyacc.y"
        {
	  DBUGPRT("expression_statement");
	  (yyval.value_slot) = new valuePtr(Value::create(Value::_NUMBER, (double)(yyvsp[0].integer_slot)));
	}
#line 3041 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 134: /* feature_value: list  */
#line 1273 "src/rulesyacc.y"
        {
	  DBUGPRT("feature_value");
	  (yyval.value_slot) = new valuePtr(Value::create(Value::_LIST, *(yyvsp[0].list_slot)));
	  free((yyvsp[0].list_slot));
	}
#line 3051 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 135: /* feature_value: features  */
#line 1280 "src/rulesyacc.y"
        {
	  DBUGPRT("feature_value");
	  (yyval.value_slot) = new valuePtr(Value::create(Value::_FEATURES, *(yyvsp[0].features_slot)));
	  free((yyvsp[0].features_slot));
	}
#line 3061 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 136: /* feature_value: TOKEN_NIL  */
#line 1287 "src/rulesyacc.y"
        {
	  DBUGPRT("feature_value");
	  (yyval.value_slot) = new valuePtr(Value::NIL_VALUE);
	}
#line 3070 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 137: /* feature_value: TOKEN_ANONYMOUS  */
#line 1293 "src/rulesyacc.y"
        {
	  DBUGPRT("feature_value");
	  (yyval.value_slot) = new valuePtr(Value::ANONYMOUS_VALUE);
	}
#line 3079 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 138: /* constant: identifier  */
#line 1300 "src/rulesyacc.y"
        {
	  DBUGPRT("constants");
	  (yyval.bits_slot)=(yyvsp[0].bits_slot);
	}
#line 3088 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 139: /* constant: identifier TOKEN_PIPE constant  */
#line 1306 "src/rulesyacc.y"
        {
	  DBUGPRT("constants");
	  (yyval.bits_slot)=(yyvsp[-2].bits_slot);
	  (**(yyval.bits_slot)) |= (**(yyvsp[0].bits_slot));
	}
#line 3098 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 140: /* identifier: TOKEN_IDENTIFIER  */
#line 1314 "src/rulesyacc.y"
        {
	  DBUGPRT("identifier");
 	  (yyval.bits_slot) = new bitsetPtr(Bitset::create(Vartable::createVariable(*(yyvsp[0].string_slot))));
 	  free((yyvsp[0].string_slot));
	}
#line 3108 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 141: /* variable: TOKEN_VARIABLE  */
#line 1322 "src/rulesyacc.y"
        {
	  DBUGPRT("variable");
	  std::ostringstream oss;
	  oss << *(yyvsp[0].string_slot);
  	  std::string str = oss.str();
	  (yyval.bits_slot) = new bitsetPtr(Bitset::create(Vartable::createVariable(str)));
	  free((yyvsp[0].string_slot));
	}
#line 3121 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 142: /* list: TOKEN_LT list_elements TOKEN_GT  */
#line 1333 "src/rulesyacc.y"
        {
	  DBUGPRT("list");
	  (yyval.list_slot) = (yyvsp[-1].list_slot);
	}
#line 3130 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 143: /* list: TOKEN_LT TOKEN_GT  */
#line 1339 "src/rulesyacc.y"
        {
	  DBUGPRT("list");
	  (yyval.list_slot) = new listPtr(List::NIL_LIST);
	}
#line 3139 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 144: /* list: TOKEN_LT list_elements TOKEN_DOUBLECOLON list_element TOKEN_GT  */
#line 1345 "src/rulesyacc.y"
        {
	  DBUGPRT("list");
	  if ((*(yyvsp[-3].list_slot))->isPairp() && (*(yyvsp[-3].list_slot))->getCdr()->isNil())
	    (yyval.list_slot) = new listPtr(List::create((*(yyvsp[-3].list_slot))->getCar(), *(yyvsp[-1].list_slot)));
	  else
	    (yyval.list_slot) = new listPtr(List::create(*(yyvsp[-3].list_slot), *(yyvsp[-1].list_slot)));
	  free((yyvsp[-3].list_slot));
	  free((yyvsp[-1].list_slot));
	}
#line 3153 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 145: /* list: TOKEN_LT list_elements TOKEN_DOUBLECOLON TOKEN_NIL TOKEN_GT  */
#line 1356 "src/rulesyacc.y"
        {
	  DBUGPRT("list");
	  if ((*(yyvsp[-3].list_slot))->isPairp() && (*(yyvsp[-3].list_slot))->getCdr()->isNil())
	    (yyval.list_slot) = new listPtr(List::create((*(yyvsp[-3].list_slot))->getCar(), List::NIL_LIST));
	  else
	    (yyval.list_slot) = new listPtr(List::create(*(yyvsp[-3].list_slot), List::NIL_LIST));
	  free((yyvsp[-3].list_slot));
	}
#line 3166 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 146: /* list_elements: list_element TOKEN_COMMA list_elements  */
#line 1367 "src/rulesyacc.y"
        {
	  DBUGPRT("list_elements");
	  (yyval.list_slot) = new listPtr(List::create(*(yyvsp[-2].list_slot), *(yyvsp[0].list_slot)));
	  free((yyvsp[-2].list_slot));
	  free((yyvsp[0].list_slot));
	}
#line 3177 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 147: /* list_elements: list_element  */
#line 1375 "src/rulesyacc.y"
        {
	  DBUGPRT("list_elements");
	  (yyval.list_slot) = new listPtr(List::create(*(yyvsp[0].list_slot), List::NIL_LIST));
	  free((yyvsp[0].list_slot));
	}
#line 3187 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 148: /* list_element: variable  */
#line 1383 "src/rulesyacc.y"
        {
	  DBUGPRT("list_element");
	  (yyval.list_slot) = new listPtr(List::create(Value::create(Value::_VARIABLE, *(yyvsp[0].bits_slot))));
	  free((yyvsp[0].bits_slot));
	}
#line 3197 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 149: /* list_element: TOKEN_DOUBLE  */
#line 1390 "src/rulesyacc.y"
        {
	  DBUGPRT("expression_statement");
	  (yyval.list_slot) = new listPtr(List::create(Value::create(Value::_NUMBER, (yyvsp[0].double_slot))));
	}
#line 3206 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 150: /* list_element: TOKEN_INTEGER  */
#line 1396 "src/rulesyacc.y"
        {
	  DBUGPRT("expression_statement");
	  (yyval.list_slot) = new listPtr(List::create(Value::create(Value::_NUMBER, (double)(yyvsp[0].integer_slot))));
	}
#line 3215 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 151: /* list_element: constant  */
#line 1402 "src/rulesyacc.y"
        {
	  DBUGPRT("list_element");
	  (yyval.list_slot) = new listPtr(List::create(Value::create(Value::_CONSTANT, *(yyvsp[0].bits_slot))));
	  free((yyvsp[0].bits_slot));
	}
#line 3225 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 152: /* list_element: features  */
#line 1409 "src/rulesyacc.y"
        {
	  DBUGPRT("list_element");
	  (yyval.list_slot) = new listPtr(List::create(Value::create(Value::_FEATURES, *(yyvsp[0].features_slot))));
	  free((yyvsp[0].features_slot));
	}
#line 3235 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 153: /* list_element: list  */
#line 1416 "src/rulesyacc.y"
        {
	  DBUGPRT("list_element");
	  (yyval.list_slot) = (yyvsp[0].list_slot);
	}
#line 3244 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;


#line 3248 "/Users/clement/workspace/elvex/src/rulesyacc.cc"

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

#line 1421 "src/rulesyacc.y"

