/* A Bison parser, made by GNU Bison 3.7.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
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
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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
#define YYBISON 30704

/* Bison version string.  */
#define YYBISON_VERSION "3.7.4"

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
   
  void ruleserror(const char *str) {
    try {
      std::ostringstream oss;
      oss << "error: " << str << " " << parser.getTopBufferName() << " (" << ruleslineno << ")" << std::endl;
      throw oss.str();
    }
    catch (std::string msg) {
      std::cerr << msg << std::endl;
    }
  }
  
  void yywarning(const char *str){
    try {
      std::ostringstream oss;
      oss << "warning: " << str << " " << parser.getTopBufferName() << " (" << ruleslineno << ")" << std::endl;
      throw oss.str();	     
    }
    catch (std::string msg) {
      std::cerr << msg << std::endl;
    }
  }
  
  

#line 157 "/Users/clement/workspace/elvex/src/rulesyacc.cc"

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
  YYSYMBOL_TOKEN_GRAMMAR = 21,             /* TOKEN_GRAMMAR  */
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
  YYSYMBOL_features_components = 103,      /* features_components  */
  YYSYMBOL_feature = 104,                  /* feature  */
  YYSYMBOL_feature_value = 105,            /* feature_value  */
  YYSYMBOL_constant = 106,                 /* constant  */
  YYSYMBOL_identifier = 107,               /* identifier  */
  YYSYMBOL_variable = 108,                 /* variable  */
  YYSYMBOL_list = 109,                     /* list  */
  YYSYMBOL_list_elements = 110,            /* list_elements  */
  YYSYMBOL_list_element = 111              /* list_element  */
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
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
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
#define YYLAST   698

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  69
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  43
/* YYNRULES -- Number of rules.  */
#define YYNRULES  151
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  261

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
       0,   169,   169,   175,   179,   187,   193,   197,   205,   209,
     214,   219,   224,   232,   257,   284,   313,   322,   328,   336,
     344,   353,   364,   364,   369,   369,   375,   381,   387,   402,
     417,   423,   430,   435,   442,   449,   456,   463,   470,   479,
     485,   490,   496,   504,   512,   519,   526,   531,   537,   543,
     549,   555,   603,   618,   631,   649,   676,   696,   703,   709,
     714,   719,   725,   736,   742,   748,   753,   758,   764,   775,
     784,   791,   798,   805,   818,   824,   831,   838,   845,   852,
     859,   869,   877,   885,   893,   901,   909,   916,   922,   928,
     934,   943,   950,   955,   960,   965,   970,   976,   982,   988,
     994,  1000,  1005,  1011,  1016,  1025,  1031,  1037,  1044,  1050,
    1057,  1062,  1072,  1078,  1085,  1093,  1102,  1117,  1133,  1140,
    1147,  1154,  1162,  1169,  1175,  1183,  1190,  1198,  1206,  1213,
    1220,  1226,  1232,  1239,  1246,  1252,  1259,  1265,  1273,  1281,
    1292,  1298,  1304,  1315,  1326,  1334,  1342,  1349,  1355,  1361,
    1368,  1375
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
  "TOKEN_COMMA", "TOKEN_GRAMMAR", "TOKEN_INPUT", "TOKEN_LEXICON",
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
  "features_components", "feature", "feature_value", "constant",
  "identifier", "variable", "list", "list_elements", "list_element", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323
};
#endif

#define YYPACT_NINF (-117)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-67)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     175,     6,    13,    10,    42,    23,  -117,   371,  -117,  -117,
     -31,  -117,  -117,  -117,  -117,     6,   -33,  -117,   -27,  -117,
    -117,  -117,   -30,    42,  -117,  -117,   -10,    45,    46,    58,
    -117,  -117,    19,  -117,    61,    63,  -117,    10,    13,  -117,
      80,    25,    38,     6,    85,    65,  -117,  -117,    12,    12,
      12,  -117,   470,   217,   151,    99,  -117,     6,  -117,    96,
    -117,  -117,  -117,    52,    66,  -117,    66,  -117,    66,  -117,
      62,  -117,  -117,    21,  -117,  -117,  -117,  -117,  -117,  -117,
    -117,    86,  -117,  -117,  -117,     5,   108,  -117,  -117,  -117,
    -117,  -117,  -117,  -117,  -117,  -117,  -117,     0,   107,    70,
     165,    10,  -117,     5,  -117,    91,  -117,  -117,  -117,   170,
    -117,    94,  -117,  -117,    73,   289,  -117,    83,    83,    83,
     121,    95,    95,   337,  -117,  -117,   109,   119,   122,  -117,
     123,   146,  -117,    -8,  -117,  -117,    10,   105,   114,  -117,
    -117,  -117,   346,  -117,   111,    83,   116,  -117,   160,   172,
      83,    83,  -117,  -117,  -117,  -117,   498,  -117,  -117,  -117,
    -117,  -117,  -117,  -117,  -117,  -117,   520,   543,    83,   145,
     180,  -117,  -117,    18,    83,    83,  -117,  -117,  -117,  -117,
    -117,  -117,  -117,   368,   167,    83,   182,   627,  -117,  -117,
      83,    83,    83,    83,    83,    83,    83,    83,    83,    83,
      83,    83,    83,    83,    83,    83,  -117,  -117,   400,    83,
      95,   193,   187,  -117,  -117,  -117,  -117,   188,   564,   189,
     564,  -117,   144,   421,  -117,   465,   606,   627,   585,   585,
       8,     8,   155,   155,  -117,   638,   638,   638,   638,   638,
     638,   377,   280,   152,    70,  -117,  -117,  -117,  -117,  -117,
     179,    83,  -117,  -117,   200,   377,   180,    83,  -117,   453,
    -117
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,    22,     0,     0,     0,     2,     0,     7,     3,
      27,    25,    38,    36,    37,     5,     0,    17,     0,    10,
      11,     6,     0,     9,     1,   113,     0,     0,     0,     0,
     138,   139,     0,   115,     0,   127,    26,     0,    22,     4,
       0,     0,     0,    21,     0,    19,     8,   117,     0,     0,
       0,   112,     0,     0,     0,     0,    23,     0,    13,     0,
      12,    20,    15,     0,   118,   119,   120,   121,   123,   122,
       0,   114,   134,     0,   125,   131,   130,   135,   133,   124,
     129,   136,   128,   132,   126,     0,     0,    14,    18,   116,
     141,   148,   147,   150,   149,   146,   151,     0,   145,     0,
       0,     0,    41,     0,    31,    32,    35,    29,    16,     0,
     140,     0,   137,   106,     0,     0,    40,     0,     0,     0,
       0,     0,     0,     0,    46,    42,     0,     0,     0,    65,
      63,    57,    67,     0,    30,    28,     0,     0,     0,   144,
     107,    45,     0,   105,   110,     0,     0,    97,     0,     0,
       0,     0,    90,    89,    88,    99,     0,    92,    93,    94,
     103,    95,    96,    98,   100,   102,     0,     0,     0,     0,
       0,    39,    43,     0,     0,     0,    50,    33,    34,   143,
     142,    44,   111,     0,   109,     0,     0,    74,    86,    47,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    48,    49,     0,     0,
       0,     0,     0,    59,    60,    61,    58,     0,    64,     0,
      69,   101,     0,     0,    87,    91,    70,    71,    72,    73,
      81,    82,    83,    84,    85,    75,    76,    77,    78,    79,
      80,     0,     0,     0,     0,    52,    53,    51,   108,   104,
      54,     0,    56,    68,     0,     0,   100,     0,    55,     0,
      62
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -117,  -117,  -117,   198,    44,  -117,   161,  -117,   185,  -117,
    -117,  -117,  -117,  -117,   125,   124,     1,   129,   130,  -117,
    -116,  -117,  -117,  -117,  -117,  -117,  -117,    68,    53,   -99,
     -88,  -117,    71,    -1,  -117,   194,   196,    79,    -5,    -4,
     -44,   137,   143
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     5,     6,    21,    22,    23,    44,    45,     9,    10,
      11,    37,    38,   103,   104,   105,   106,   107,   123,   124,
     125,   126,   212,   127,   217,   128,   219,   237,   157,   158,
     159,   160,   161,   162,    32,    33,    79,   163,    81,   164,
     165,    97,    98
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
       8,   129,    34,    35,    15,   177,    12,   172,    36,    83,
      83,    12,   130,   -24,    39,   100,   129,   101,     7,   109,
      42,   102,   143,    24,   129,   144,   172,   130,    40,    96,
       7,    43,    51,     7,    41,   130,   136,     7,    55,    52,
      59,    58,    61,   129,    65,    67,    69,    34,    35,    82,
      82,    47,    78,    78,   130,   211,    86,    16,    17,   110,
     197,   198,   199,    48,    49,    96,    13,    96,    18,    95,
      14,    13,    93,    19,    20,    14,    50,    31,    73,    53,
      90,    54,    30,    31,    91,    92,    31,   143,   113,   114,
     144,   145,    64,    66,    68,     7,   132,   146,    57,   131,
      60,    62,    85,    19,    20,    95,     7,    95,    93,    63,
      93,   132,    87,    43,   131,   147,    42,   169,   170,   132,
     148,   149,   131,    89,   108,   250,   252,   111,   150,   168,
      99,    30,    80,    80,   151,   136,   140,   178,   132,   258,
      73,   131,   129,   129,    30,   152,   153,   154,    31,   155,
     173,    73,    94,   130,   130,    30,   129,    91,    92,    31,
      31,   174,   176,     7,   179,   175,   -66,   130,   185,   216,
     113,   114,   215,   180,   182,   115,   116,     7,   112,   184,
     186,   209,     7,    72,   222,   156,   166,   167,    94,     1,
      94,   224,   117,   118,   119,   120,     2,     3,     4,   210,
     121,   244,   137,   245,   246,   247,   243,   248,    73,   199,
     255,   253,    30,   183,    75,    76,    31,    77,   187,   188,
     257,    46,   122,    56,    88,   133,   213,    73,   134,     7,
      31,    30,   135,    91,    92,    31,   208,   132,   132,   254,
     131,   131,   218,   220,   214,   142,    71,   256,   139,    72,
      84,   132,   138,   223,   131,     0,     0,     0,   225,   226,
     227,   228,   229,   230,   231,   232,   233,   234,   235,   236,
       0,   238,   239,   240,    73,     0,     0,   242,    30,    74,
      75,    76,    31,    77,     0,   113,   114,     0,     0,     0,
     115,     0,     7,     0,   113,   114,     0,     0,     0,   115,
     141,     7,     0,     0,     0,     0,     0,   117,   118,   119,
     120,     0,     0,     0,     0,   121,   117,   118,   119,   120,
     190,     0,     0,     0,   121,   259,   191,   192,   193,   194,
     195,   196,   197,   198,   199,   200,   201,   251,   203,   204,
     205,     0,   113,   114,     0,    31,   122,   115,   171,     7,
       0,   113,   114,     0,    31,     0,   115,   181,     7,     0,
       0,     0,     0,     0,   117,   118,   119,   120,     0,     0,
       0,     0,   121,   117,   118,   119,   120,   221,     0,     0,
       0,   121,   113,   114,    25,     0,    26,   115,     0,     7,
       0,     0,     0,     0,   122,    27,    28,    29,     0,     0,
       0,     0,    31,   122,   117,   118,   119,   120,   190,   241,
       0,    31,   121,     0,   191,   192,   193,   194,   195,   196,
     197,   198,   199,   200,   201,   202,   203,   204,   205,     0,
     249,     0,    30,     0,   122,     0,    31,     0,     0,     0,
     190,     0,    31,     0,     0,     0,   191,   192,   193,   194,
     195,   196,   197,   198,   199,   200,   201,   202,   203,   204,
     205,   190,   260,     0,     0,     0,     0,   191,   192,   193,
     194,   195,   196,   197,   198,   199,   200,   201,   202,   203,
     204,   205,     0,     0,     0,    70,     0,     0,     0,     0,
       0,     0,     0,   190,    27,    28,    29,     0,     0,   191,
     192,   193,   194,   195,   196,   197,   198,   199,   200,   201,
     202,   203,   204,   205,   189,   195,   196,   197,   198,   199,
     200,   201,   202,   203,   204,   205,     0,     0,     0,     0,
       0,    30,     0,     0,     0,    31,   206,     0,   190,     0,
       0,     0,     0,     0,   191,   192,   193,   194,   195,   196,
     197,   198,   199,   200,   201,   202,   203,   204,   205,   207,
     190,     0,     0,     0,     0,     0,   191,   192,   193,   194,
     195,   196,   197,   198,   199,   200,   201,   202,   203,   204,
     205,     0,     0,   190,     0,     0,     0,     0,     0,   191,
     192,   193,   194,   195,   196,   197,   198,   199,   200,   201,
     202,   203,   204,   205,   190,     0,     0,     0,     0,     0,
     191,   192,   193,   194,   195,   196,   197,   198,   199,   200,
     201,   202,   203,   204,   205,   190,     0,     0,     0,     0,
       0,   191,   192,   -67,   -67,   195,   196,   197,   198,   199,
     200,   201,   202,   203,   204,   205,   190,     0,     0,     0,
       0,     0,     0,   192,     0,     0,   195,   196,   197,   198,
     199,   200,   201,   202,   203,   204,   205,   190,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   195,   196,   197,
     198,   199,   200,   201,   202,   203,   204,   205,   195,   196,
     197,   198,   199,   -67,   -67,   -67,   -67,   -67,   -67
};

static const yytype_int16 yycheck[] =
{
       1,   100,     7,     7,     3,    13,     1,   123,    39,    53,
      54,     1,   100,     0,    15,    10,   115,    12,    12,    19,
      50,    16,     4,     0,   123,     7,   142,   115,    61,    73,
      12,    61,    13,    12,    61,   123,    44,    12,    37,    20,
      41,    16,    43,   142,    48,    49,    50,    52,    52,    53,
      54,    61,    53,    54,   142,    37,    57,    15,    16,    59,
      52,    53,    54,    18,    18,   109,    61,   111,    26,    73,
      65,    61,    73,    61,    62,    65,    18,    65,    57,    18,
      59,    18,    61,    65,    63,    64,    65,     4,     5,     6,
       7,     8,    48,    49,    50,    12,   100,    14,    18,   100,
      62,    16,     3,    61,    62,   109,    12,   111,   109,    44,
     111,   115,    16,    61,   115,    32,    50,   121,   122,   123,
      37,    38,   123,    61,    16,   241,   242,    20,    45,     8,
      44,    61,    53,    54,    51,    44,    63,   136,   142,   255,
      57,   142,   241,   242,    61,    62,    63,    64,    65,    66,
      41,    57,    73,   241,   242,    61,   255,    63,    64,    65,
      65,    42,    16,    12,    59,    43,    43,   255,     8,   173,
       5,     6,   173,    59,    63,    10,    11,    12,    99,    63,
       8,    36,    12,    32,    17,   117,   118,   119,   109,    14,
     111,     9,    27,    28,    29,    30,    21,    22,    23,    19,
      35,     8,    32,    16,    16,    16,   210,    63,    57,    54,
      31,    59,    61,   145,    63,    64,    65,    66,   150,   151,
      20,    23,    57,    38,    63,   101,   173,    57,   103,    12,
      65,    61,   103,    63,    64,    65,   168,   241,   242,   244,
     241,   242,   174,   175,   173,   115,    52,   251,   111,    32,
      54,   255,   109,   185,   255,    -1,    -1,    -1,   190,   191,
     192,   193,   194,   195,   196,   197,   198,   199,   200,   201,
      -1,   203,   204,   205,    57,    -1,    -1,   209,    61,    62,
      63,    64,    65,    66,    -1,     5,     6,    -1,    -1,    -1,
      10,    -1,    12,    -1,     5,     6,    -1,    -1,    -1,    10,
      11,    12,    -1,    -1,    -1,    -1,    -1,    27,    28,    29,
      30,    -1,    -1,    -1,    -1,    35,    27,    28,    29,    30,
      40,    -1,    -1,    -1,    35,   257,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    -1,     5,     6,    -1,    65,    57,    10,    11,    12,
      -1,     5,     6,    -1,    65,    -1,    10,    11,    12,    -1,
      -1,    -1,    -1,    -1,    27,    28,    29,    30,    -1,    -1,
      -1,    -1,    35,    27,    28,    29,    30,     9,    -1,    -1,
      -1,    35,     5,     6,    13,    -1,    15,    10,    -1,    12,
      -1,    -1,    -1,    -1,    57,    24,    25,    26,    -1,    -1,
      -1,    -1,    65,    57,    27,    28,    29,    30,    40,     9,
      -1,    65,    35,    -1,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    -1,
       9,    -1,    61,    -1,    57,    -1,    65,    -1,    -1,    -1,
      40,    -1,    65,    -1,    -1,    -1,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    40,     9,    -1,    -1,    -1,    -1,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    -1,    -1,    -1,    15,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    40,    24,    25,    26,    -1,    -1,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    16,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    -1,    -1,    -1,    -1,
      -1,    61,    -1,    -1,    -1,    65,    16,    -1,    40,    -1,
      -1,    -1,    -1,    -1,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    16,
      40,    -1,    -1,    -1,    -1,    -1,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    -1,    -1,    40,    -1,    -1,    -1,    -1,    -1,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    40,    -1,    -1,    -1,    -1,    -1,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    40,    -1,    -1,    -1,    -1,
      -1,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    40,    -1,    -1,    -1,
      -1,    -1,    -1,    47,    -1,    -1,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    40,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    14,    21,    22,    23,    70,    71,    12,   102,    77,
      78,    79,     1,    61,    65,    85,    15,    16,    26,    61,
      62,    72,    73,    74,     0,    13,    15,    24,    25,    26,
      61,    65,   103,   104,   107,   108,    39,    80,    81,   102,
      61,    61,    50,    61,    75,    76,    72,    61,    18,    18,
      18,    13,    20,    18,    18,    85,    77,    18,    16,   102,
      62,   102,    16,    44,    73,   108,    73,   108,    73,   108,
      15,   104,    32,    57,    62,    63,    64,    66,   102,   105,
     106,   107,   108,   109,   105,     3,   102,    16,    75,    61,
      59,    63,    64,   102,   106,   108,   109,   110,   111,    44,
      10,    12,    16,    82,    83,    84,    85,    86,    16,    19,
      59,    20,   106,     5,     6,    10,    11,    27,    28,    29,
      30,    35,    57,    87,    88,    89,    90,    92,    94,    98,
      99,   102,   108,    84,    83,    86,    44,    32,   111,   110,
      63,    11,    87,     4,     7,     8,    14,    32,    37,    38,
      45,    51,    62,    63,    64,    66,    96,    97,    98,    99,
     100,   101,   102,   106,   108,   109,    96,    96,     8,   108,
     108,    11,    89,    41,    42,    43,    16,    13,    85,    59,
      59,    11,    63,    96,    63,     8,     8,    96,    96,    16,
      40,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    16,    16,    96,    36,
      19,    37,    91,    97,   101,   102,   108,    93,    96,    95,
      96,     9,    17,    96,     9,    96,    96,    96,    96,    96,
      96,    96,    96,    96,    96,    96,    96,    96,    96,    96,
      96,     9,    96,   108,     8,    16,    16,    16,    63,     9,
      89,    57,    89,    59,   107,    31,   108,    20,    89,    96,
       9
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    69,    70,    71,    71,    71,    71,    71,    72,    72,
      73,    73,    73,    74,    74,    74,    74,    74,    75,    75,
      76,    76,    78,    77,    79,    77,    80,    80,    81,    81,
      82,    82,    83,    83,    84,    84,    85,    85,    85,    86,
      86,    86,    87,    87,    88,    88,    89,    89,    89,    89,
      89,    89,    89,    89,    89,    89,    89,    90,    91,    91,
      91,    91,    91,    92,    93,    94,    94,    94,    94,    95,
      96,    96,    96,    96,    96,    96,    96,    96,    96,    96,
      96,    96,    96,    96,    96,    96,    96,    96,    96,    96,
      96,    96,    96,    96,    96,    96,    96,    96,    96,    96,
      96,    96,    96,    96,    96,    97,    98,    99,   100,   100,
     101,   101,   102,   102,   103,   103,   103,   103,   104,   104,
     104,   104,   104,   104,   104,   104,   104,   104,   105,   105,
     105,   105,   105,   105,   105,   105,   106,   106,   107,   108,
     109,   109,   109,   109,   110,   110,   111,   111,   111,   111,
     111,   111
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     3,     2,     2,     2,     2,     1,
       1,     1,     3,     3,     4,     3,     5,     1,     3,     1,
       2,     1,     0,     3,     0,     1,     1,     0,     5,     4,
       2,     1,     1,     3,     3,     1,     1,     1,     1,     3,
       2,     1,     1,     2,     3,     2,     1,     3,     3,     3,
       2,     4,     4,     4,     5,     7,     5,     1,     1,     1,
       1,     1,     6,     1,     1,     1,     1,     1,     5,     1,
       3,     3,     3,     3,     2,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     2,     3,     1,     1,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     1,     1,     4,     1,     1,     2,     4,     2,
       1,     2,     3,     2,     3,     1,     4,     2,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     1,     1,
       3,     2,     5,     5,     3,     1,     1,     1,     1,     1,
       1,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


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

/* This macro is provided for backward compatibility. */
# ifndef YY_LOCATION_PRINT
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif


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
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yykind < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yykind], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yykind);
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
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yykind);
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
    goto yyexhaustedlab;
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
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
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
#line 169 "src/rulesyacc.y"
              {
	  DBUGPRT("axiom done...");
	  YYACCEPT;
	}
#line 1546 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 3: /* begin: TOKEN_GRAMMAR rules  */
#line 175 "src/rulesyacc.y"
                            {
	  DBUGPRT("begin grammar");
	}
#line 1554 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 4: /* begin: TOKEN_INPUT term features  */
#line 179 "src/rulesyacc.y"
                                   {
	  DBUGPRT("begin input");
	  parser.setStartTerm((yyvsp[-1].integer_slot));
	  (*(yyvsp[0].features_slot))->renameVariables((*(yyvsp[0].features_slot))->getId());
	  parser.setStartFeatures(*(yyvsp[0].features_slot));
	  free((yyvsp[0].features_slot));
	}
#line 1566 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 5: /* begin: TOKEN_INPUT term  */
#line 187 "src/rulesyacc.y"
                          {
	  DBUGPRT("begin input");
	  parser.setStartTerm((yyvsp[0].integer_slot));
	  parser.setStartFeatures(Features::create());
	 }
#line 1576 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 6: /* begin: TOKEN_LEXICON dictionary  */
#line 193 "src/rulesyacc.y"
                                  {      
	  DBUGPRT("begin lexicon");
	}
#line 1584 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 7: /* begin: TOKEN_DASH features  */
#line 198 "src/rulesyacc.y"
        {
	  DBUGPRT("begin features");
	  parser.setLocalFeatures(*(yyvsp[0].features_slot));
	  free((yyvsp[0].features_slot));
	}
#line 1594 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 8: /* dictionary: dictionary_line dictionary  */
#line 205 "src/rulesyacc.y"
                                   {
	  DBUGPRT("dictionary");
	}
#line 1602 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 9: /* dictionary: dictionary_line  */
#line 209 "src/rulesyacc.y"
                         {
	  DBUGPRT("dictionary");
	 }
#line 1610 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 10: /* stringOrIdentifier: TOKEN_IDENTIFIER  */
#line 214 "src/rulesyacc.y"
                         {
	  DBUGPRT("stringOrIdentifier");
	  (yyval.string_slot) = (yyvsp[0].string_slot);
	}
#line 1619 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 11: /* stringOrIdentifier: TOKEN_STRING  */
#line 219 "src/rulesyacc.y"
                      {
	  DBUGPRT("stringOrIdentifier");
	  (yyval.string_slot) = (yyvsp[0].string_slot);
	 }
#line 1628 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 12: /* stringOrIdentifier: stringOrIdentifier TOKEN_PLUS TOKEN_STRING  */
#line 224 "src/rulesyacc.y"
                                                    {
	  DBUGPRT("string");
	  (yyval.string_slot) = (yyvsp[-2].string_slot);
	  *(yyval.string_slot) += *(yyvsp[0].string_slot);
	 }
#line 1638 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 13: /* dictionary_line: TOKEN_FORM TOKEN_IDENTIFIER TOKEN_SEMI  */
#line 233 "src/rulesyacc.y"
        {
	  DBUGPRT("dictionary_line");
	  unsigned int code = Vartable::identifierToCode(*(yyvsp[-1].string_slot));
	  free((yyvsp[-1].string_slot));
	  // constantNoun => (0 => args)
	  auto foundCode = parser.getLexicon().find(code);
	  Parser::entries_map *zeroToEntries;
	  if (foundCode != parser.getLexicon().end()){
	    zeroToEntries = foundCode->second;
	  } else {
	    zeroToEntries = new Parser::entries_map();
	    parser.getLexicon().insert(std::make_pair(code, zeroToEntries));
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
#line 1666 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 14: /* dictionary_line: TOKEN_FORM TOKEN_IDENTIFIER features TOKEN_SEMI  */
#line 258 "src/rulesyacc.y"
        {
	  DBUGPRT("dictionary_line");
	  unsigned int code=Vartable::identifierToCode(*(yyvsp[-2].string_slot));
	  free((yyvsp[-2].string_slot));
	  // constantNoun => (0 => args)
	  auto foundCode = parser.getLexicon().find(code);
	  Parser::entries_map *zeroToEntries;
	  if (foundCode!=parser.getLexicon().end()) {
	    zeroToEntries=foundCode->second;
	  } else {
	    zeroToEntries = new Parser::entries_map;
	    parser.getLexicon().insert(std::make_pair(code, zeroToEntries));
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
#line 1695 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 15: /* dictionary_line: stringOrIdentifier lexical_entries TOKEN_SEMI  */
#line 285 "src/rulesyacc.y"
        {
	  DBUGPRT("dictionary_line");
	  for (auto entry = (*(yyvsp[-1].entries_slot))->begin() ; entry != (*(yyvsp[-1].entries_slot))->end() ; ++entry) {
	    (*entry)->setForm(*(yyvsp[-2].string_slot));
	    entriesPtr lp;
	    Parser::entries_map *predToEntries;
	    //std::cerr << entry->getCode() << std::endl;
	    Parser::entries_map_map::iterator foundCode = parser.getLexicon().find((*entry)->getPos());
	    if (foundCode != parser.getLexicon().end()){
	      predToEntries = foundCode->second;
	    } else {
	      predToEntries = new Parser::entries_map;
	      parser.getLexicon().insert(std::make_pair((*entry)->getPos(), predToEntries));
	    }
	    Parser::entries_map::iterator foundPred = predToEntries->find((*entry)->getPred());
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
#line 1726 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 16: /* dictionary_line: TOKEN_AROBASE TOKEN_IDENTIFIER TOKEN_COLON features TOKEN_SEMI  */
#line 314 "src/rulesyacc.y"
        {
	  DBUGPRT("dictionary_line");
	  parser.addMacros(*(yyvsp[-3].string_slot), *(yyvsp[-1].features_slot));
	  free((yyvsp[-3].string_slot));
	  free((yyvsp[-1].features_slot));
	  
	}
#line 1738 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 17: /* dictionary_line: TOKEN_SEMI  */
#line 323 "src/rulesyacc.y"
        {
	  DBUGPRT("dictionary_line");
	}
#line 1746 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 18: /* lexical_entries: lexical_entry TOKEN_PIPE lexical_entries  */
#line 329 "src/rulesyacc.y"
        {	  
	  DBUGPRT("lexical_entries");
	  (yyval.entries_slot) = (yyvsp[0].entries_slot);
	  (*(yyval.entries_slot))->add(*(yyvsp[-2].entry_slot));
	  free((yyvsp[-2].entry_slot));
	}
#line 1757 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 19: /* lexical_entries: lexical_entry  */
#line 336 "src/rulesyacc.y"
                       {
	  DBUGPRT("lexical_entries");
	  (yyval.entries_slot) = new entriesPtr(Entries::create(*(yyvsp[0].entry_slot)));
	  free((yyvsp[0].entry_slot));
	 }
#line 1767 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 20: /* lexical_entry: TOKEN_IDENTIFIER features  */
#line 345 "src/rulesyacc.y"
        {
	  DBUGPRT("lexical_entry");
	  unsigned int pred = (*(yyvsp[0].features_slot))->assignPred();
	  (yyval.entry_slot) = new entryPtr(Entry::create(Vartable::identifierToCode(*(yyvsp[-1].string_slot)), pred, std::string(), *(yyvsp[0].features_slot)));
	  free((yyvsp[-1].string_slot));
	  free((yyvsp[0].features_slot));
	}
#line 1779 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 21: /* lexical_entry: TOKEN_IDENTIFIER  */
#line 354 "src/rulesyacc.y"
        {
	  DBUGPRT("lexical_entry");
	  (yyval.entry_slot) = new entryPtr(Entry::create(Vartable::identifierToCode(*(yyvsp[0].string_slot)), UINT_MAX, std::string(), Features::create()));
	  free((yyvsp[0].string_slot));
	}
#line 1789 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 22: /* $@1: %empty  */
#line 364 "src/rulesyacc.y"
        {headLineno = ruleslineno;}
#line 1795 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 23: /* rules: $@1 rule rules  */
#line 365 "src/rulesyacc.y"
        {
	  DBUGPRT("rules"); 
	}
#line 1803 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 24: /* $@2: %empty  */
#line 369 "src/rulesyacc.y"
         {headLineno = ruleslineno;}
#line 1809 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 25: /* rules: $@2  */
#line 370 "src/rulesyacc.y"
        {
	  DBUGPRT("rules"); 
	}
#line 1817 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 26: /* pref_rule: TOKEN_TRACE  */
#line 376 "src/rulesyacc.y"
        {
	  DBUGPRT("pref_rule");
	  headTrace = true;
	}
#line 1826 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 27: /* pref_rule: %empty  */
#line 381 "src/rulesyacc.y"
                      {
	  DBUGPRT("pref_rule");
	  headTrace = false;
	}
#line 1835 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 28: /* rule: pref_rule term TOKEN_RIGHTARROW terms_vector structure_statement  */
#line 388 "src/rulesyacc.y"
        {
	  DBUGPRT("rule");
	  rulePtr rule = Rule::create(headLineno, parser.getTopBufferName(), (yyvsp[-3].integer_slot), *(yyvsp[-1].vector_terms_slot), (yyvsp[0].statements_slot) ? *(yyvsp[0].statements_slot) : statementsPtr());
	  rule->addDefaults();
	  rule->setTrace(headTrace);
	  parser.getGrammar().addRule(rule);
	  if (!parser.getGrammar().getStartTerm()){
	    parser.getGrammar().setStartTerm((yyvsp[-3].integer_slot));
	  }
	  free((yyvsp[-1].vector_terms_slot));
	  if ((yyvsp[0].statements_slot))
	     free((yyvsp[0].statements_slot));
	}
#line 1853 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 29: /* rule: pref_rule term TOKEN_RIGHTARROW structure_statement  */
#line 403 "src/rulesyacc.y"
        {
	  DBUGPRT("Rule");
	  rulePtr rule = Rule::create(headLineno, parser.getTopBufferName(), (yyvsp[-2].integer_slot), (yyvsp[0].statements_slot) ? *(yyvsp[0].statements_slot) : statementsPtr());
	  rule->addDefaults();
	  rule->setTrace(headTrace);
	  parser.getGrammar().addRule(rule);
	  if (!parser.getGrammar().getStartTerm()){
	    parser.getGrammar().setStartTerm((yyvsp[-2].integer_slot));
	  }
	  if ((yyvsp[0].statements_slot))
	    free((yyvsp[0].statements_slot));
	}
#line 1870 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 30: /* terms_vector: terms_vector terms  */
#line 417 "src/rulesyacc.y"
                           { 
	  DBUGPRT("term_vector");
	  (yyval.vector_terms_slot)=(yyvsp[-1].vector_terms_slot);
	  (yyval.vector_terms_slot)->push_back(*(yyvsp[0].terms_slot));
	}
#line 1880 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 31: /* terms_vector: terms  */
#line 423 "src/rulesyacc.y"
               { 
	  DBUGPRT("term_vector"); 
	  (yyval.vector_terms_slot) = new std::vector< termsPtr >;
	  (yyval.vector_terms_slot)->push_back(*(yyvsp[0].terms_slot));
	}
#line 1890 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 32: /* terms: terms_disj  */
#line 430 "src/rulesyacc.y"
                   { 
	  DBUGPRT("term");
	  (yyval.terms_slot)=(yyvsp[0].terms_slot);
	}
#line 1899 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 33: /* terms: TOKEN_LBRACKET terms_disj TOKEN_RBRACKET  */
#line 435 "src/rulesyacc.y"
                                                  { 
	  DBUGPRT("term");
	  (yyval.terms_slot) = (yyvsp[-1].terms_slot);
	  (*(yyval.terms_slot))->setOptional();
	}
#line 1909 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 34: /* terms_disj: terms_disj TOKEN_PIPE term  */
#line 443 "src/rulesyacc.y"
        { 
	  DBUGPRT("term_disj");
	  (yyval.terms_slot) = (yyvsp[-2].terms_slot);
	  (*(yyval.terms_slot))->push_back((yyvsp[0].integer_slot));
	}
#line 1919 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 35: /* terms_disj: term  */
#line 450 "src/rulesyacc.y"
        { 
	  DBUGPRT("term_disj"); 
	  (yyval.terms_slot) = new termsPtr(Terms::create((yyvsp[0].integer_slot)));
	}
#line 1928 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 36: /* term: TOKEN_IDENTIFIER  */
#line 457 "src/rulesyacc.y"
        { 
	  DBUGPRT("term_id");
	  (yyval.integer_slot) = Vartable::identifierToCode(*(yyvsp[0].string_slot));
	  free((yyvsp[0].string_slot));
	}
#line 1938 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 37: /* term: TOKEN_VARIABLE  */
#line 464 "src/rulesyacc.y"
        { 
	  DBUGPRT("term_id");
	  (yyval.integer_slot) = Vartable::identifierToCode(*(yyvsp[0].string_slot));
	  free((yyvsp[0].string_slot));
	}
#line 1948 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 38: /* term: error  */
#line 471 "src/rulesyacc.y"
        {
	  YYABORT;
	}
#line 1956 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 39: /* structure_statement: TOKEN_LBRACE list_statement TOKEN_RBRACE  */
#line 480 "src/rulesyacc.y"
        {
	  DBUGPRT("structure_statement");
	  (yyval.statements_slot)=(yyvsp[-1].statements_slot);
	}
#line 1965 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 40: /* structure_statement: TOKEN_LBRACE TOKEN_RBRACE  */
#line 486 "src/rulesyacc.y"
        {
	  (yyval.statements_slot)=NULL;
	}
#line 1973 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 41: /* structure_statement: TOKEN_SEMI  */
#line 491 "src/rulesyacc.y"
        {
	  (yyval.statements_slot)=NULL;
	}
#line 1981 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 42: /* list_statement: statement  */
#line 497 "src/rulesyacc.y"
        {
	  DBUGPRT("list_statement");
	  (yyval.statements_slot) = new statementsPtr(Statements::create());
	  (*(yyval.statements_slot))->addStatement(*(yyvsp[0].statement_slot));
	  free((yyvsp[0].statement_slot));
	}
#line 1992 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 43: /* list_statement: list_statement statement  */
#line 504 "src/rulesyacc.y"
                                  {
	  DBUGPRT("list_statement");
	  (yyval.statements_slot) = (yyvsp[-1].statements_slot);
	  (*(yyval.statements_slot))->addStatement(*(yyvsp[0].statement_slot));
	  free((yyvsp[0].statement_slot));
	}
#line 2003 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 44: /* statements: TOKEN_LBRACE list_statement TOKEN_RBRACE  */
#line 513 "src/rulesyacc.y"
        {
	  DBUGPRT("statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::STMS, *(yyvsp[-1].statements_slot)));
	  free((yyvsp[-1].statements_slot));
	}
#line 2013 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 45: /* statements: TOKEN_LBRACE TOKEN_RBRACE  */
#line 520 "src/rulesyacc.y"
        {
	  DBUGPRT("statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::STMS, Statements::create()));
	}
#line 2022 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 46: /* statement: statements  */
#line 526 "src/rulesyacc.y"
                   {
	  DBUGPRT("statement");
	  (yyval.statement_slot)=(yyvsp[0].statement_slot);
	 }
#line 2031 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 47: /* statement: TOKEN_ATTEST expression_statement TOKEN_SEMI  */
#line 531 "src/rulesyacc.y"
                                                      {
	  DBUGPRT("statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::ATTEST, *(yyvsp[-1].statement_slot)));
	  free((yyvsp[-1].statement_slot));
	}
#line 2041 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 48: /* statement: TOKEN_PRINT expression_statement TOKEN_SEMI  */
#line 537 "src/rulesyacc.y"
                                                     {
	  DBUGPRT("statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::PRINT, *(yyvsp[-1].statement_slot)));
	  free((yyvsp[-1].statement_slot));
	}
#line 2051 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 49: /* statement: TOKEN_PRINTLN expression_statement TOKEN_SEMI  */
#line 543 "src/rulesyacc.y"
                                                       {
	  DBUGPRT("statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::PRINTLN, *(yyvsp[-1].statement_slot)));
	  free((yyvsp[-1].statement_slot));
	}
#line 2061 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 50: /* statement: features TOKEN_SEMI  */
#line 549 "src/rulesyacc.y"
                             {
	  DBUGPRT("statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::GUARD, *(yyvsp[-1].features_slot)));
	  free((yyvsp[-1].features_slot));
	}
#line 2071 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 51: /* statement: left_hand_side_aff_statement TOKEN_AFF right_hand_side_aff_statement TOKEN_SEMI  */
#line 555 "src/rulesyacc.y"
                                                                                         {
	  DBUGPRT("statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::AFF, *(yyvsp[-3].statement_slot), *(yyvsp[-1].statement_slot)));
	  // <X, …> = <…>
	  // <X, …> = Z
	  if (((*(yyvsp[-3].statement_slot))->isList()) && (((*(yyvsp[-1].statement_slot))->isList())||((*(yyvsp[-1].statement_slot))->isVariable()))) {
	    }
	  // ↓i = $X
	  // ↓i = […]
	  // ↓i = ↑
	  // ↓i = … ∪ …
	  // ↓i = ⇓j
	  else if (((*(yyvsp[-3].statement_slot))->isDown()) && (((*(yyvsp[-1].statement_slot))->isVariable())||((*(yyvsp[-1].statement_slot))->isFeatures())||((*(yyvsp[-1].statement_slot))->isUp())||((*(yyvsp[-1].statement_slot))->isUnif())||((*(yyvsp[-1].statement_slot))->isDown2())))
	    ;
	  // ⇑ = $X
	  // ⇑ = […]
	  // ⇑ = ↑
	  // ⇑ = … ∪ …
	  // ⇑ = ⇓j
	  else if (((*(yyvsp[-3].statement_slot))->isUp2()) && (((*(yyvsp[-1].statement_slot))->isVariable())||((*(yyvsp[-1].statement_slot))->isFeatures())||((*(yyvsp[-1].statement_slot))->isUp())||((*(yyvsp[-1].statement_slot))->isUnif())||((*(yyvsp[-1].statement_slot))->isDown2())))
	    ;
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
		      ||((*(yyvsp[-1].statement_slot))->isSearch())));
	  else {
	    yyerror((char*)"syntax error");
	  }
	  free((yyvsp[-3].statement_slot));
	  free((yyvsp[-1].statement_slot));
	}
#line 2123 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 52: /* statement: left_hand_side_subset_statement TOKEN_SUBSUME right_hand_side_subset_statement TOKEN_SEMI  */
#line 603 "src/rulesyacc.y"
                                                                                                   {
	  DBUGPRT("statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::SUBSUME, (*(yyvsp[-3].statement_slot)), (*(yyvsp[-1].statement_slot))));
	  // […] ⊂ ↑ 
	  // […] ⊂ ⇓j 
	  // […] ⊂ $X 
	  // […] ⊂ search  
	  if (((*(yyvsp[-3].statement_slot))->isFeatures()) && (((*(yyvsp[-1].statement_slot))->isUp())||((*(yyvsp[-1].statement_slot))->isDown2())||((*(yyvsp[-1].statement_slot))->isVariable())||((*(yyvsp[-1].statement_slot))->isSearch())))
	    ;
	  else 
	    yyerror((char *)"syntax error");
	  free((yyvsp[-3].statement_slot));
	  free((yyvsp[-1].statement_slot));
	}
#line 2142 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 53: /* statement: left_hand_side_inset_statement TOKEN_INSET right_hand_side_inset_statement TOKEN_SEMI  */
#line 618 "src/rulesyacc.y"
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
#line 2159 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 54: /* statement: TOKEN_IF TOKEN_LPAR expression_statement TOKEN_RPAR statement  */
#line 631 "src/rulesyacc.y"
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
#line 2181 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 55: /* statement: TOKEN_IF TOKEN_LPAR expression_statement TOKEN_RPAR statement TOKEN_ELSE statement  */
#line 649 "src/rulesyacc.y"
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
#line 2212 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 56: /* statement: TOKEN_FOREACH variable TOKEN_IN expression_statement statement  */
#line 676 "src/rulesyacc.y"
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
#line 2235 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 57: /* left_hand_side_subset_statement: features  */
#line 696 "src/rulesyacc.y"
                 {
	  DBUGPRT("left_hand_side_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::FEATURES, *(yyvsp[0].features_slot)));
	  free((yyvsp[0].features_slot));
	}
#line 2245 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 58: /* right_hand_side_subset_statement: variable  */
#line 703 "src/rulesyacc.y"
                 {
	  DBUGPRT("right_hand_side_subset_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::VARIABLE, *(yyvsp[0].bits_slot)));
	  free((yyvsp[0].bits_slot));
	}
#line 2255 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 59: /* right_hand_side_subset_statement: up  */
#line 709 "src/rulesyacc.y"
            {
	  DBUGPRT("right_hand_side_subset_statement");
	  (yyval.statement_slot)=(yyvsp[0].statement_slot);
	}
#line 2264 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 60: /* right_hand_side_subset_statement: downdouble  */
#line 714 "src/rulesyacc.y"
                    {
	  DBUGPRT("right_hand_side_subset_statement");
	  (yyval.statement_slot)=(yyvsp[0].statement_slot);
	}
#line 2273 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 61: /* right_hand_side_subset_statement: features  */
#line 719 "src/rulesyacc.y"
                  {
	  DBUGPRT("right_hand_side_subset_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::FEATURES, *(yyvsp[0].features_slot)));
	  free((yyvsp[0].features_slot));
	}
#line 2283 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 62: /* right_hand_side_subset_statement: TOKEN_SEARCH TOKEN_LPAR identifier TOKEN_COMMA expression_statement TOKEN_RPAR  */
#line 725 "src/rulesyacc.y"
                                                                                         {
	  DBUGPRT("right_hand_side_subset_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, 
						  Statement::SEARCH, 
						  *(yyvsp[-3].bits_slot),
						  *(yyvsp[-1].statement_slot)));
	  free((yyvsp[-3].bits_slot));
	  free((yyvsp[-1].statement_slot));
	 }
#line 2297 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 63: /* left_hand_side_inset_statement: down  */
#line 736 "src/rulesyacc.y"
             {
	  DBUGPRT("left_hand_side_statement");
	  (yyval.statement_slot)=(yyvsp[0].statement_slot);
	}
#line 2306 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 64: /* right_hand_side_inset_statement: expression_statement  */
#line 742 "src/rulesyacc.y"
                             {
	  DBUGPRT("right_hand_side_statement");
	  (yyval.statement_slot)=(yyvsp[0].statement_slot);
	}
#line 2315 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 65: /* left_hand_side_aff_statement: updouble  */
#line 748 "src/rulesyacc.y"
                 {
	  DBUGPRT("left_hand_side_statement");
	  (yyval.statement_slot)=(yyvsp[0].statement_slot);
	}
#line 2324 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 66: /* left_hand_side_aff_statement: down  */
#line 753 "src/rulesyacc.y"
              {
	  DBUGPRT("left_hand_side_statement");
	  (yyval.statement_slot)=(yyvsp[0].statement_slot);
	}
#line 2333 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 67: /* left_hand_side_aff_statement: variable  */
#line 758 "src/rulesyacc.y"
                  {
	  DBUGPRT("left_hand_side_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::VARIABLE, *(yyvsp[0].bits_slot)));
	  free((yyvsp[0].bits_slot));
	 }
#line 2343 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 68: /* left_hand_side_aff_statement: TOKEN_LT variable TOKEN_DOUBLECOLON variable TOKEN_GT  */
#line 765 "src/rulesyacc.y"
        {
	  DBUGPRT("left_hand_side_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::LIST,
						List::create(List::create(Value::create(Value::_VARIABLE, *(yyvsp[-3].bits_slot))),
							     List::create(Value::create(Value::_VARIABLE, *(yyvsp[-1].bits_slot))))));
	  free((yyvsp[-3].bits_slot));
	  free((yyvsp[-1].bits_slot));
	}
#line 2356 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 69: /* right_hand_side_aff_statement: expression_statement  */
#line 775 "src/rulesyacc.y"
                             {
	  DBUGPRT("right_hand_side_statement");
	  (yyval.statement_slot)=(yyvsp[0].statement_slot);
	}
#line 2365 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 70: /* expression_statement: expression_statement TOKEN_OR expression_statement  */
#line 784 "src/rulesyacc.y"
                                                           {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::FCT, Statement::OR, (*(yyvsp[-2].statement_slot)), (*(yyvsp[0].statement_slot))));
	  free((yyvsp[-2].statement_slot));
	  free((yyvsp[0].statement_slot));
	}
#line 2376 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 71: /* expression_statement: expression_statement TOKEN_AND expression_statement  */
#line 791 "src/rulesyacc.y"
                                                             {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::FCT, Statement::AND, (*(yyvsp[-2].statement_slot)), (*(yyvsp[0].statement_slot))));
	  free((yyvsp[-2].statement_slot));
	  free((yyvsp[0].statement_slot));
	}
#line 2387 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 72: /* expression_statement: expression_statement TOKEN_IMPLICATION expression_statement  */
#line 798 "src/rulesyacc.y"
                                                                     {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::FCT, Statement::OR, Statement::create(ruleslineno, Statement::FCT, Statement::NOT, (*(yyvsp[-2].statement_slot))), (*(yyvsp[0].statement_slot))));
	  free((yyvsp[-2].statement_slot));
	  free((yyvsp[0].statement_slot));
	}
#line 2398 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 73: /* expression_statement: expression_statement TOKEN_EQUIV expression_statement  */
#line 805 "src/rulesyacc.y"
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
#line 2415 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 74: /* expression_statement: TOKEN_NOT expression_statement  */
#line 818 "src/rulesyacc.y"
                                        {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::FCT, Statement::NOT, (*(yyvsp[0].statement_slot))));
	  free((yyvsp[0].statement_slot));
	}
#line 2425 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 75: /* expression_statement: expression_statement TOKEN_EQUAL expression_statement  */
#line 824 "src/rulesyacc.y"
                                                               {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::FCT, Statement::EQ, (*(yyvsp[-2].statement_slot)), (*(yyvsp[0].statement_slot))));
	  free((yyvsp[-2].statement_slot));
	  free((yyvsp[0].statement_slot));
	}
#line 2436 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 76: /* expression_statement: expression_statement TOKEN_DIFF expression_statement  */
#line 831 "src/rulesyacc.y"
                                                              { 
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::FCT, Statement::DIFF, (*(yyvsp[-2].statement_slot)), (*(yyvsp[0].statement_slot)))); 
	  free((yyvsp[-2].statement_slot));
	  free((yyvsp[0].statement_slot));
	}
#line 2447 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 77: /* expression_statement: expression_statement TOKEN_LT expression_statement  */
#line 838 "src/rulesyacc.y"
                                                            { 
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::FCT, Statement::LT, (*(yyvsp[-2].statement_slot)), (*(yyvsp[0].statement_slot)))); 
	  free((yyvsp[-2].statement_slot));
	  free((yyvsp[0].statement_slot));
	}
#line 2458 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 78: /* expression_statement: expression_statement TOKEN_LE expression_statement  */
#line 845 "src/rulesyacc.y"
                                                            { 
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::FCT, Statement::LE, (*(yyvsp[-2].statement_slot)), (*(yyvsp[0].statement_slot)))); 
	  free((yyvsp[-2].statement_slot));
	  free((yyvsp[0].statement_slot));
	}
#line 2469 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 79: /* expression_statement: expression_statement TOKEN_GT expression_statement  */
#line 852 "src/rulesyacc.y"
                                                            { 
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::FCT, Statement::GT, (*(yyvsp[-2].statement_slot)), (*(yyvsp[0].statement_slot)))); 
	  free((yyvsp[-2].statement_slot));
	  free((yyvsp[0].statement_slot));
	}
#line 2480 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 80: /* expression_statement: expression_statement TOKEN_GE expression_statement  */
#line 859 "src/rulesyacc.y"
                                                            { 
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::FCT, Statement::GE, (*(yyvsp[-2].statement_slot)), (*(yyvsp[0].statement_slot)))); 
	  free((yyvsp[-2].statement_slot));
	  free((yyvsp[0].statement_slot));
	}
#line 2491 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 81: /* expression_statement: expression_statement TOKEN_PLUS expression_statement  */
#line 870 "src/rulesyacc.y"
        {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::FCT, Statement::PLUS, (*(yyvsp[-2].statement_slot)), (*(yyvsp[0].statement_slot))));
	  free((yyvsp[-2].statement_slot));
	  free((yyvsp[0].statement_slot));
	}
#line 2502 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 82: /* expression_statement: expression_statement TOKEN_MINUS expression_statement  */
#line 878 "src/rulesyacc.y"
        {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::FCT, Statement::MINUS, (*(yyvsp[-2].statement_slot)), (*(yyvsp[0].statement_slot))));
	  free((yyvsp[-2].statement_slot));
	  free((yyvsp[0].statement_slot));
	}
#line 2513 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 83: /* expression_statement: expression_statement TOKEN_TIMES expression_statement  */
#line 886 "src/rulesyacc.y"
        {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::FCT, Statement::TIMES, (*(yyvsp[-2].statement_slot)), (*(yyvsp[0].statement_slot))));
	  free((yyvsp[-2].statement_slot));
	  free((yyvsp[0].statement_slot));
	}
#line 2524 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 84: /* expression_statement: expression_statement TOKEN_DIVIDE expression_statement  */
#line 894 "src/rulesyacc.y"
        {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::FCT, Statement::DIVIDE, (*(yyvsp[-2].statement_slot)), (*(yyvsp[0].statement_slot))));
	  free((yyvsp[-2].statement_slot));
	  free((yyvsp[0].statement_slot));
	}
#line 2535 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 85: /* expression_statement: expression_statement TOKEN_MODULO expression_statement  */
#line 902 "src/rulesyacc.y"
        {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::FCT, Statement::MODULO, (*(yyvsp[-2].statement_slot)), (*(yyvsp[0].statement_slot))));
	  free((yyvsp[-2].statement_slot));
	  free((yyvsp[0].statement_slot));
	}
#line 2546 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 86: /* expression_statement: TOKEN_MINUS expression_statement  */
#line 910 "src/rulesyacc.y"
        {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::FCT, Statement::MINUS_U, (*(yyvsp[0].statement_slot)), statementPtr()));
	  free((yyvsp[0].statement_slot));
	}
#line 2556 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 87: /* expression_statement: TOKEN_RAND TOKEN_LPAR TOKEN_RPAR  */
#line 917 "src/rulesyacc.y"
        {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::FCT, Statement::RAND));
	}
#line 2565 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 88: /* expression_statement: TOKEN_DOUBLE  */
#line 923 "src/rulesyacc.y"
        {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::NUMBER, (yyvsp[0].double_slot)));
	}
#line 2574 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 89: /* expression_statement: TOKEN_INTEGER  */
#line 929 "src/rulesyacc.y"
        {
	  DBUGPRT("expression_statement");
 	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::NUMBER, (double)(yyvsp[0].integer_slot)));
	}
#line 2583 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 90: /* expression_statement: TOKEN_STRING  */
#line 935 "src/rulesyacc.y"
        {
	  DBUGPRT("expression_statement");
 	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::STR, *(yyvsp[0].string_slot)));
	}
#line 2592 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 91: /* expression_statement: expression_statement TOKEN_UNION expression_statement  */
#line 943 "src/rulesyacc.y"
                                                               {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::UNIF, (*(yyvsp[-2].statement_slot)), (*(yyvsp[0].statement_slot))));
	  free((yyvsp[-2].statement_slot));
	  free((yyvsp[0].statement_slot));
	}
#line 2603 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 92: /* expression_statement: up  */
#line 950 "src/rulesyacc.y"
            {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot)=(yyvsp[0].statement_slot);
	}
#line 2612 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 93: /* expression_statement: updouble  */
#line 955 "src/rulesyacc.y"
                  {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot)=(yyvsp[0].statement_slot);
	}
#line 2621 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 94: /* expression_statement: down  */
#line 960 "src/rulesyacc.y"
              {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot)=(yyvsp[0].statement_slot);
	}
#line 2630 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 95: /* expression_statement: downdouble  */
#line 965 "src/rulesyacc.y"
                    {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot)=(yyvsp[0].statement_slot);
	}
#line 2639 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 96: /* expression_statement: features  */
#line 970 "src/rulesyacc.y"
                  {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::FEATURES, *(yyvsp[0].features_slot)));
	  free((yyvsp[0].features_slot));
	}
#line 2649 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 97: /* expression_statement: TOKEN_NIL  */
#line 977 "src/rulesyacc.y"
        {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::NIL));
	}
#line 2658 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 98: /* expression_statement: constant  */
#line 982 "src/rulesyacc.y"
                  {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::CONSTANT, *(yyvsp[0].bits_slot)));
	  free((yyvsp[0].bits_slot));
	}
#line 2668 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 99: /* expression_statement: TOKEN_ANONYMOUS  */
#line 989 "src/rulesyacc.y"
        {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::ANONYMOUS, Value::ANONYMOUS_VALUE));
	}
#line 2677 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 100: /* expression_statement: variable  */
#line 994 "src/rulesyacc.y"
                  {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::VARIABLE, *(yyvsp[0].bits_slot)));
	  free((yyvsp[0].bits_slot));
	}
#line 2687 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 101: /* expression_statement: TOKEN_LPAR expression_statement TOKEN_RPAR  */
#line 1000 "src/rulesyacc.y"
                                                    {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot)=(yyvsp[-1].statement_slot);
	}
#line 2696 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 102: /* expression_statement: list  */
#line 1005 "src/rulesyacc.y"
              {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::LIST, *(yyvsp[0].list_slot)));
	  free((yyvsp[0].list_slot));
	}
#line 2706 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 103: /* expression_statement: dash_statement  */
#line 1011 "src/rulesyacc.y"
                        {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot)=(yyvsp[0].statement_slot);
	}
#line 2715 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 104: /* expression_statement: TOKEN_SEARCH TOKEN_LPAR expression_statement TOKEN_RPAR  */
#line 1016 "src/rulesyacc.y"
                                                                  {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, 
						  Statement::SEARCH, 
						  *(yyvsp[-1].statement_slot)));
	  free((yyvsp[-1].statement_slot));
	 }
#line 2727 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 105: /* up: TOKEN_UPARROW  */
#line 1025 "src/rulesyacc.y"
                      {  
	  DBUGPRT("up");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::UP));
	}
#line 2736 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 106: /* updouble: TOKEN_UP2ARROW  */
#line 1031 "src/rulesyacc.y"
                       {  
	  DBUGPRT("updouble");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::UP2));
	}
#line 2745 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 107: /* down: TOKEN_DOWNARROW TOKEN_INTEGER  */
#line 1038 "src/rulesyacc.y"
        { 
	  DBUGPRT("down");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::DOWN, (unsigned int)(yyvsp[0].integer_slot)-1)); 
	}
#line 2754 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 108: /* dash_statement: TOKEN_DASH TOKEN_INTEGER TOKEN_DOT TOKEN_INTEGER  */
#line 1045 "src/rulesyacc.y"
        { 
	  DBUGPRT("dash_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::DASH, (unsigned int)((yyvsp[-2].integer_slot)-1), (unsigned int)((yyvsp[0].integer_slot)-1))); 
	}
#line 2763 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 109: /* dash_statement: TOKEN_DASH TOKEN_INTEGER  */
#line 1051 "src/rulesyacc.y"
        { 
	  DBUGPRT("dash_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::DASH, (unsigned int)((yyvsp[0].integer_slot)-1))); 
	}
#line 2772 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 110: /* downdouble: TOKEN_DOWN2ARROW  */
#line 1057 "src/rulesyacc.y"
                         {  
	  DBUGPRT("downdouble");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::DOWN2, (unsigned int)0)); 
	}
#line 2781 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 111: /* downdouble: TOKEN_DOWN2ARROW TOKEN_INTEGER  */
#line 1063 "src/rulesyacc.y"
        { 
	  DBUGPRT("downdouble");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::DOWN2, (unsigned int)((yyvsp[0].integer_slot)-1))); 
	}
#line 2790 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 112: /* features: TOKEN_LBRACKET features_components TOKEN_RBRACKET  */
#line 1073 "src/rulesyacc.y"
        {
	  DBUGPRT("features");
 	  (yyval.features_slot)=(yyvsp[-1].features_slot);
	}
#line 2799 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 113: /* features: TOKEN_LBRACKET TOKEN_RBRACKET  */
#line 1079 "src/rulesyacc.y"
        {
	  DBUGPRT("features");
	  (yyval.features_slot) = new featuresPtr(Features::create());
	}
#line 2808 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 114: /* features_components: features_components TOKEN_COMMA feature  */
#line 1086 "src/rulesyacc.y"
        {
	  DBUGPRT("feature_components");
	  (yyval.features_slot)=(yyvsp[-2].features_slot); 
	  (*(yyval.features_slot))->add(*(yyvsp[0].feature_slot));
	  free((yyvsp[0].feature_slot));
	}
#line 2819 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 115: /* features_components: feature  */
#line 1094 "src/rulesyacc.y"
        {
	  DBUGPRT("features_components");
	  (yyval.features_slot) = new featuresPtr(Features::create());
	  (*(yyval.features_slot))->add(*(yyvsp[0].feature_slot));
	  free((yyvsp[0].feature_slot));
	}
#line 2830 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 116: /* features_components: features_components TOKEN_COMMA TOKEN_AROBASE TOKEN_IDENTIFIER  */
#line 1103 "src/rulesyacc.y"
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
#line 2847 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 117: /* features_components: TOKEN_AROBASE TOKEN_IDENTIFIER  */
#line 1118 "src/rulesyacc.y"
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
#line 2864 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 118: /* feature: TOKEN_LEMMA TOKEN_COLON stringOrIdentifier  */
#line 1134 "src/rulesyacc.y"
        {
	  DBUGPRT("feature");
	  (yyval.feature_slot) = new featurePtr(Feature::create(Feature::LEMMA, bitsetPtr(), Value::create(Value::_CODE, *(yyvsp[0].string_slot))));
	}
#line 2873 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 119: /* feature: TOKEN_LEMMA TOKEN_COLON variable  */
#line 1141 "src/rulesyacc.y"
        {
	  DBUGPRT("feature");
	  (yyval.feature_slot) = new featurePtr(Feature::create(Feature::LEMMA, bitsetPtr(), Value::create(Value::_VARIABLE, *(yyvsp[0].bits_slot))));
	}
#line 2882 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 120: /* feature: TOKEN_PRED TOKEN_COLON stringOrIdentifier  */
#line 1148 "src/rulesyacc.y"
        {
	  DBUGPRT("feature");
	  (yyval.feature_slot) = new featurePtr(Feature::create(Feature::PRED, bitsetPtr(), Value::create(Value::_CODE, *(yyvsp[0].string_slot))));
	}
#line 2891 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 121: /* feature: TOKEN_PRED TOKEN_COLON variable  */
#line 1155 "src/rulesyacc.y"
        {
	  DBUGPRT("feature");
	  (yyval.feature_slot) = new featurePtr(Feature::create(Feature::PRED, bitsetPtr(), Value::create(Value::_VARIABLE, *(yyvsp[0].bits_slot))));
	  free((yyvsp[0].bits_slot));
	}
#line 2901 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 122: /* feature: TOKEN_FORM TOKEN_COLON variable  */
#line 1163 "src/rulesyacc.y"
        {
	  DBUGPRT("feature");
	  (yyval.feature_slot) = new featurePtr(Feature::create(Feature::FORM, bitsetPtr(), Value::create(Value::_VARIABLE, *(yyvsp[0].bits_slot))));
	  free((yyvsp[0].bits_slot));
	}
#line 2911 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 123: /* feature: TOKEN_FORM TOKEN_COLON stringOrIdentifier  */
#line 1170 "src/rulesyacc.y"
        {
	  DBUGPRT("feature");
	  (yyval.feature_slot) = new featurePtr(Feature::create(Feature::FORM, bitsetPtr(), Value::create(Value::_FORM, *(yyvsp[0].string_slot))));
	}
#line 2920 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 124: /* feature: identifier TOKEN_COLON feature_value  */
#line 1176 "src/rulesyacc.y"
        {
	  DBUGPRT("feature");
	  (yyval.feature_slot) = new featurePtr(Feature::create(Feature::CONSTANT, *(yyvsp[-2].bits_slot), *(yyvsp[0].value_slot)));
	  free((yyvsp[-2].bits_slot));
	  free((yyvsp[0].value_slot));
	}
#line 2931 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 125: /* feature: identifier TOKEN_COLON TOKEN_STRING  */
#line 1184 "src/rulesyacc.y"
        {
	  DBUGPRT("feature");
	  (yyval.feature_slot) = new featurePtr(Feature::create(Feature::CONSTANT, *(yyvsp[-2].bits_slot), Value::create(Value::_FORM, *(yyvsp[0].string_slot))));
	  free((yyvsp[-2].bits_slot));
	}
#line 2941 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 126: /* feature: variable TOKEN_COLON feature_value  */
#line 1191 "src/rulesyacc.y"
        {
	  DBUGPRT("feature");
	  (yyval.feature_slot) = new featurePtr(Feature::create(Feature::VARIABLE, *(yyvsp[-2].bits_slot), *(yyvsp[0].value_slot)));
	  free((yyvsp[-2].bits_slot));
	  free((yyvsp[0].value_slot));
	}
#line 2952 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 127: /* feature: variable  */
#line 1199 "src/rulesyacc.y"
        {
	  DBUGPRT("feature");
	  (yyval.feature_slot) = new featurePtr(Feature::create(Feature::VARIABLE, *(yyvsp[0].bits_slot), valuePtr()));
	  free((yyvsp[0].bits_slot));
	}
#line 2962 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 128: /* feature_value: variable  */
#line 1207 "src/rulesyacc.y"
        {
	  DBUGPRT("feature_value");
	  (yyval.value_slot) = new valuePtr(Value::create(Value::_VARIABLE, *(yyvsp[0].bits_slot)));
	  free((yyvsp[0].bits_slot));
	}
#line 2972 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 129: /* feature_value: constant  */
#line 1214 "src/rulesyacc.y"
        {
	  DBUGPRT("feature_value");
	  (yyval.value_slot) = new valuePtr(Value::create(Value::_CONSTANT, *(yyvsp[0].bits_slot)));
	  free((yyvsp[0].bits_slot));
	}
#line 2982 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 130: /* feature_value: TOKEN_DOUBLE  */
#line 1221 "src/rulesyacc.y"
        {
	  DBUGPRT("expression_statement");
	  (yyval.value_slot) = new valuePtr(Value::create(Value::_NUMBER, (yyvsp[0].double_slot)));
	}
#line 2991 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 131: /* feature_value: TOKEN_INTEGER  */
#line 1227 "src/rulesyacc.y"
        {
	  DBUGPRT("expression_statement");
	  (yyval.value_slot) = new valuePtr(Value::create(Value::_NUMBER, (double)(yyvsp[0].integer_slot)));
	}
#line 3000 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 132: /* feature_value: list  */
#line 1233 "src/rulesyacc.y"
        {
	  DBUGPRT("feature_value");
	  (yyval.value_slot) = new valuePtr(Value::create(Value::_LIST, *(yyvsp[0].list_slot)));
	  free((yyvsp[0].list_slot));
	}
#line 3010 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 133: /* feature_value: features  */
#line 1240 "src/rulesyacc.y"
        {
	  DBUGPRT("feature_value");
	  (yyval.value_slot) = new valuePtr(Value::create(Value::_FEATURES, *(yyvsp[0].features_slot)));
	  free((yyvsp[0].features_slot));
	}
#line 3020 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 134: /* feature_value: TOKEN_NIL  */
#line 1247 "src/rulesyacc.y"
        {
	  DBUGPRT("feature_value");
	  (yyval.value_slot) = new valuePtr(Value::NIL_VALUE);
	}
#line 3029 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 135: /* feature_value: TOKEN_ANONYMOUS  */
#line 1253 "src/rulesyacc.y"
        {
	  DBUGPRT("feature_value");
	  (yyval.value_slot) = new valuePtr(Value::ANONYMOUS_VALUE);
	}
#line 3038 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 136: /* constant: identifier  */
#line 1260 "src/rulesyacc.y"
        {
	  DBUGPRT("constants");
	  (yyval.bits_slot)=(yyvsp[0].bits_slot);
	}
#line 3047 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 137: /* constant: identifier TOKEN_PIPE constant  */
#line 1266 "src/rulesyacc.y"
        {
	  DBUGPRT("constants");
	  (yyval.bits_slot)=(yyvsp[-2].bits_slot);
	  (**(yyval.bits_slot)) |= (**(yyvsp[0].bits_slot));
	}
#line 3057 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 138: /* identifier: TOKEN_IDENTIFIER  */
#line 1274 "src/rulesyacc.y"
        {
	  DBUGPRT("identifier");
 	  (yyval.bits_slot) = new bitsetPtr(Bitset::create(Vartable::createVariable(*(yyvsp[0].string_slot))));
 	  free((yyvsp[0].string_slot));
	}
#line 3067 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 139: /* variable: TOKEN_VARIABLE  */
#line 1282 "src/rulesyacc.y"
        {
	  DBUGPRT("variable");
	  std::ostringstream oss;
	  oss << *(yyvsp[0].string_slot);
  	  std::string str = oss.str();
	  (yyval.bits_slot) = new bitsetPtr(Bitset::create(Vartable::createVariable(str)));
	  free((yyvsp[0].string_slot));
	}
#line 3080 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 140: /* list: TOKEN_LT list_elements TOKEN_GT  */
#line 1293 "src/rulesyacc.y"
        {
	  DBUGPRT("list");
	  (yyval.list_slot) = (yyvsp[-1].list_slot);
	}
#line 3089 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 141: /* list: TOKEN_LT TOKEN_GT  */
#line 1299 "src/rulesyacc.y"
        {
	  DBUGPRT("list");
	  (yyval.list_slot) = new listPtr(List::NIL_LIST);
	}
#line 3098 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 142: /* list: TOKEN_LT list_elements TOKEN_DOUBLECOLON list_element TOKEN_GT  */
#line 1305 "src/rulesyacc.y"
        {
	  DBUGPRT("list");
	  if ((*(yyvsp[-3].list_slot))->isPairp() && (*(yyvsp[-3].list_slot))->getCdr()->isNil())
	    (yyval.list_slot) = new listPtr(List::create((*(yyvsp[-3].list_slot))->getCar(), *(yyvsp[-1].list_slot)));
	  else
	    (yyval.list_slot) = new listPtr(List::create(*(yyvsp[-3].list_slot), *(yyvsp[-1].list_slot)));
	  free((yyvsp[-3].list_slot));
	  free((yyvsp[-1].list_slot));
	}
#line 3112 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 143: /* list: TOKEN_LT list_elements TOKEN_DOUBLECOLON TOKEN_NIL TOKEN_GT  */
#line 1316 "src/rulesyacc.y"
        {
	  DBUGPRT("list");
	  if ((*(yyvsp[-3].list_slot))->isPairp() && (*(yyvsp[-3].list_slot))->getCdr()->isNil())
	    (yyval.list_slot) = new listPtr(List::create((*(yyvsp[-3].list_slot))->getCar(), List::NIL_LIST));
	  else
	    (yyval.list_slot) = new listPtr(List::create(*(yyvsp[-3].list_slot), List::NIL_LIST));
	  free((yyvsp[-3].list_slot));
	}
#line 3125 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 144: /* list_elements: list_element TOKEN_COMMA list_elements  */
#line 1327 "src/rulesyacc.y"
        {
	  DBUGPRT("list_elements");
	  (yyval.list_slot) = new listPtr(List::create(*(yyvsp[-2].list_slot), *(yyvsp[0].list_slot)));
	  free((yyvsp[-2].list_slot));
	  free((yyvsp[0].list_slot));
	}
#line 3136 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 145: /* list_elements: list_element  */
#line 1335 "src/rulesyacc.y"
        {
	  DBUGPRT("list_elements");
	  (yyval.list_slot) = new listPtr(List::create(*(yyvsp[0].list_slot), List::NIL_LIST));
	  free((yyvsp[0].list_slot));
	}
#line 3146 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 146: /* list_element: variable  */
#line 1343 "src/rulesyacc.y"
        {
	  DBUGPRT("list_element");
	  (yyval.list_slot) = new listPtr(List::create(Value::create(Value::_VARIABLE, *(yyvsp[0].bits_slot))));
	  free((yyvsp[0].bits_slot));
	}
#line 3156 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 147: /* list_element: TOKEN_DOUBLE  */
#line 1350 "src/rulesyacc.y"
        {
	  DBUGPRT("expression_statement");
	  (yyval.list_slot) = new listPtr(List::create(Value::create(Value::_NUMBER, (yyvsp[0].double_slot))));
	}
#line 3165 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 148: /* list_element: TOKEN_INTEGER  */
#line 1356 "src/rulesyacc.y"
        {
	  DBUGPRT("expression_statement");
	  (yyval.list_slot) = new listPtr(List::create(Value::create(Value::_NUMBER, (double)(yyvsp[0].integer_slot))));
	}
#line 3174 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 149: /* list_element: constant  */
#line 1362 "src/rulesyacc.y"
        {
	  DBUGPRT("list_element");
	  (yyval.list_slot) = new listPtr(List::create(Value::create(Value::_CONSTANT, *(yyvsp[0].bits_slot))));
	  free((yyvsp[0].bits_slot));
	}
#line 3184 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 150: /* list_element: features  */
#line 1369 "src/rulesyacc.y"
        {
	  DBUGPRT("list_element");
	  (yyval.list_slot) = new listPtr(List::create(Value::create(Value::_FEATURES, *(yyvsp[0].features_slot))));
	  free((yyvsp[0].features_slot));
	}
#line 3194 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;

  case 151: /* list_element: list  */
#line 1376 "src/rulesyacc.y"
        {
	  DBUGPRT("list_element");
	  (yyval.list_slot)=(yyvsp[0].list_slot);
	}
#line 3203 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
    break;


#line 3207 "/Users/clement/workspace/elvex/src/rulesyacc.cc"

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
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturn;
#endif


/*-------------------------------------------------------.
| yyreturn -- parsing is finished, clean up and return.  |
`-------------------------------------------------------*/
yyreturn:
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

#line 1381 "src/rulesyacc.y"

