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
 * Copyright 2014-2023 LABRI,
 * CNRS (UMR 5800), the University of Bordeaux,
 * and the Bordeaux INP
 *
 * Author:
 * Lionel Clément
 * LaBRI - Université Bordeaux 
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
  
 extern uint32_t ruleslineno;
 extern unsigned int ruleslex();
 extern Parser parser;
 uint32_t headLineno;
 bool headTrace;
 bool withSpaces;
 bool bidirectional;
 bool permutable;

  void ruleserror(const char* str) {
      std::ostringstream oss;
      oss << str << " in " << parser.getTopBufferName() << " (" << ruleslineno << ")";
      throw parser_exception(oss);
  }

  void yywarning(const char* str){
      std::ostringstream oss;
      oss << "warning: " << str << " " << parser.getTopBufferName() << " (" << ruleslineno << ")" << std::endl;
      std::cerr << oss.str() << std::endl;
  }

  

#line 151 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"

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
  YYSYMBOL_TOKEN_CONS = 19,                /* TOKEN_CONS  */
  YYSYMBOL_TOKEN_COMMA = 20,               /* TOKEN_COMMA  */
  YYSYMBOL_TOKEN_RULES = 21,               /* TOKEN_RULES  */
  YYSYMBOL_TOKEN_INPUT = 22,               /* TOKEN_INPUT  */
  YYSYMBOL_TOKEN_LEXICON = 23,             /* TOKEN_LEXICON  */
  YYSYMBOL_TOKEN_LEMMA = 24,               /* TOKEN_LEMMA  */
  YYSYMBOL_TOKEN_HEAD = 25,                /* TOKEN_HEAD  */
  YYSYMBOL_TOKEN_FORM = 26,                /* TOKEN_FORM  */
  YYSYMBOL_TOKEN_ATTEST = 27,              /* TOKEN_ATTEST  */
  YYSYMBOL_TOKEN_PRINT = 28,               /* TOKEN_PRINT  */
  YYSYMBOL_TOKEN_PRINTLN = 29,             /* TOKEN_PRINTLN  */
  YYSYMBOL_TOKEN_PRINTSTDERR = 30,         /* TOKEN_PRINTSTDERR  */
  YYSYMBOL_TOKEN_PRINTLNSTDERR = 31,       /* TOKEN_PRINTLNSTDERR  */
  YYSYMBOL_TOKEN_IF = 32,                  /* TOKEN_IF  */
  YYSYMBOL_TOKEN_ELSE = 33,                /* TOKEN_ELSE  */
  YYSYMBOL_TOKEN_DEFERRED = 34,            /* TOKEN_DEFERRED  */
  YYSYMBOL_TOKEN_NIL = 35,                 /* TOKEN_NIL  */
  YYSYMBOL_TOKEN_TRUE = 36,                /* TOKEN_TRUE  */
  YYSYMBOL_TOKEN_FALSE = 37,               /* TOKEN_FALSE  */
  YYSYMBOL_TOKEN_FOREACH = 38,             /* TOKEN_FOREACH  */
  YYSYMBOL_TOKEN_IN = 39,                  /* TOKEN_IN  */
  YYSYMBOL_TOKEN_SEARCH = 40,              /* TOKEN_SEARCH  */
  YYSYMBOL_TOKEN_ON = 41,                  /* TOKEN_ON  */
  YYSYMBOL_TOKEN_RAND = 42,                /* TOKEN_RAND  */
  YYSYMBOL_TOKEN_TRACE = 43,               /* TOKEN_TRACE  */
  YYSYMBOL_TOKEN_WITH_SPACES = 44,         /* TOKEN_WITH_SPACES  */
  YYSYMBOL_TOKEN_BIDIRECTIONAL = 45,       /* TOKEN_BIDIRECTIONAL  */
  YYSYMBOL_TOKEN_PERMUTABLE = 46,          /* TOKEN_PERMUTABLE  */
  YYSYMBOL_TOKEN_UNIFY = 47,               /* TOKEN_UNIFY  */
  YYSYMBOL_TOKEN_SUBSUME = 48,             /* TOKEN_SUBSUME  */
  YYSYMBOL_TOKEN_ASSIGNMENT = 49,          /* TOKEN_ASSIGNMENT  */
  YYSYMBOL_TOKEN_PIPE = 50,                /* TOKEN_PIPE  */
  YYSYMBOL_TOKEN_NOT = 51,                 /* TOKEN_NOT  */
  YYSYMBOL_TOKEN_OR = 52,                  /* TOKEN_OR  */
  YYSYMBOL_TOKEN_AND = 53,                 /* TOKEN_AND  */
  YYSYMBOL_TOKEN_IMPLICATION = 54,         /* TOKEN_IMPLICATION  */
  YYSYMBOL_TOKEN_EQUIV = 55,               /* TOKEN_EQUIV  */
  YYSYMBOL_TOKEN_PLUS = 56,                /* TOKEN_PLUS  */
  YYSYMBOL_TOKEN_MINUS = 57,               /* TOKEN_MINUS  */
  YYSYMBOL_TOKEN_TIMES = 58,               /* TOKEN_TIMES  */
  YYSYMBOL_TOKEN_DIVIDE = 59,              /* TOKEN_DIVIDE  */
  YYSYMBOL_TOKEN_MODULO = 60,              /* TOKEN_MODULO  */
  YYSYMBOL_TOKEN_EQUAL = 61,               /* TOKEN_EQUAL  */
  YYSYMBOL_TOKEN_DIFF = 62,                /* TOKEN_DIFF  */
  YYSYMBOL_TOKEN_LT = 63,                  /* TOKEN_LT  */
  YYSYMBOL_TOKEN_LE = 64,                  /* TOKEN_LE  */
  YYSYMBOL_TOKEN_GT = 65,                  /* TOKEN_GT  */
  YYSYMBOL_TOKEN_GE = 66,                  /* TOKEN_GE  */
  YYSYMBOL_TOKEN_IDENTIFIER = 67,          /* TOKEN_IDENTIFIER  */
  YYSYMBOL_TOKEN_STRING = 68,              /* TOKEN_STRING  */
  YYSYMBOL_TOKEN_INTEGER = 69,             /* TOKEN_INTEGER  */
  YYSYMBOL_TOKEN_DOUBLE = 70,              /* TOKEN_DOUBLE  */
  YYSYMBOL_TOKEN_VARIABLE = 71,            /* TOKEN_VARIABLE  */
  YYSYMBOL_TOKEN_ANONYMOUS = 72,           /* TOKEN_ANONYMOUS  */
  YYSYMBOL_TOKEN_MINUS_U = 73,             /* TOKEN_MINUS_U  */
  YYSYMBOL_TOKEN_NOELSE = 74,              /* TOKEN_NOELSE  */
  YYSYMBOL_YYACCEPT = 75,                  /* $accept  */
  YYSYMBOL_axiom = 76,                     /* axiom  */
  YYSYMBOL_begin = 77,                     /* begin  */
  YYSYMBOL_dictionary = 78,                /* dictionary  */
  YYSYMBOL_dictionary_line = 79,           /* dictionary_line  */
  YYSYMBOL_stringOrIdentifier = 80,        /* stringOrIdentifier  */
  YYSYMBOL_lexical_entries = 81,           /* lexical_entries  */
  YYSYMBOL_lexical_entry = 82,             /* lexical_entry  */
  YYSYMBOL_rules = 83,                     /* rules  */
  YYSYMBOL_84_1 = 84,                      /* $@1  */
  YYSYMBOL_85_2 = 85,                      /* $@2  */
  YYSYMBOL_pref_rule = 86,                 /* pref_rule  */
  YYSYMBOL_rule = 87,                      /* rule  */
  YYSYMBOL_terms_vector = 88,              /* terms_vector  */
  YYSYMBOL_terms = 89,                     /* terms  */
  YYSYMBOL_terms_disj = 90,                /* terms_disj  */
  YYSYMBOL_term = 91,                      /* term  */
  YYSYMBOL_structure_statement = 92,       /* structure_statement  */
  YYSYMBOL_list_statement = 93,            /* list_statement  */
  YYSYMBOL_statements = 94,                /* statements  */
  YYSYMBOL_statement = 95,                 /* statement  */
  YYSYMBOL_left_hand_side_subset_statement = 96, /* left_hand_side_subset_statement  */
  YYSYMBOL_right_hand_side_subset_statement = 97, /* right_hand_side_subset_statement  */
  YYSYMBOL_left_hand_side_assignment_statement = 98, /* left_hand_side_assignment_statement  */
  YYSYMBOL_right_hand_side_assignment_statement = 99, /* right_hand_side_assignment_statement  */
  YYSYMBOL_expression_statement = 100,     /* expression_statement  */
  YYSYMBOL_expression_statement_composite = 101, /* expression_statement_composite  */
  YYSYMBOL_up = 102,                       /* up  */
  YYSYMBOL_up2 = 103,                      /* up2  */
  YYSYMBOL_down = 104,                     /* down  */
  YYSYMBOL_down2 = 105,                    /* down2  */
  YYSYMBOL_dash_statement = 106,           /* dash_statement  */
  YYSYMBOL_features = 107,                 /* features  */
  YYSYMBOL_features_composite_tail = 108,  /* features_composite_tail  */
  YYSYMBOL_features_composite = 109,       /* features_composite  */
  YYSYMBOL_feature = 110,                  /* feature  */
  YYSYMBOL_feature_value = 111,            /* feature_value  */
  YYSYMBOL_constant = 112,                 /* constant  */
  YYSYMBOL_identifier = 113,               /* identifier  */
  YYSYMBOL_variable = 114,                 /* variable  */
  YYSYMBOL_pairp = 115,                    /* pairp  */
  YYSYMBOL_pairp_elements = 116,           /* pairp_elements  */
  YYSYMBOL_pairp_element = 117             /* pairp_element  */
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
#define YYLAST   698

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  75
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  43
/* YYNRULES -- Number of rules.  */
#define YYNRULES  156
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  279

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   329


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
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   170,   170,   176,   180,   188,   194,   200,   208,   212,
     218,   243,   270,   306,   314,   320,   325,   330,   337,   346,
     355,   364,   375,   375,   380,   380,   386,   392,   398,   404,
     410,   419,   441,   455,   461,   468,   473,   480,   487,   494,
     501,   508,   517,   523,   528,   534,   542,   550,   557,   564,
     569,   575,   581,   592,   603,   614,   625,   688,   705,   717,
     730,   742,   756,   763,   769,   774,   779,   787,   792,   797,
     803,   814,   823,   830,   837,   844,   857,   863,   870,   877,
     884,   891,   898,   908,   916,   924,   932,   940,   948,   955,
     961,   967,   973,   982,   989,   994,   999,  1004,  1009,  1018,
    1024,  1033,  1039,  1045,  1053,  1061,  1070,  1084,  1092,  1102,
    1108,  1114,  1121,  1128,  1134,  1144,  1154,  1162,  1166,  1172,
    1180,  1189,  1204,  1220,  1227,  1234,  1241,  1249,  1256,  1263,
    1269,  1277,  1284,  1294,  1301,  1308,  1314,  1320,  1327,  1334,
    1340,  1347,  1353,  1361,  1369,  1380,  1386,  1392,  1403,  1416,
    1424,  1432,  1439,  1445,  1451,  1458,  1465
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
  "TOKEN_SEMI", "TOKEN_DOT", "TOKEN_COLON", "TOKEN_CONS", "TOKEN_COMMA",
  "TOKEN_RULES", "TOKEN_INPUT", "TOKEN_LEXICON", "TOKEN_LEMMA",
  "TOKEN_HEAD", "TOKEN_FORM", "TOKEN_ATTEST", "TOKEN_PRINT",
  "TOKEN_PRINTLN", "TOKEN_PRINTSTDERR", "TOKEN_PRINTLNSTDERR", "TOKEN_IF",
  "TOKEN_ELSE", "TOKEN_DEFERRED", "TOKEN_NIL", "TOKEN_TRUE", "TOKEN_FALSE",
  "TOKEN_FOREACH", "TOKEN_IN", "TOKEN_SEARCH", "TOKEN_ON", "TOKEN_RAND",
  "TOKEN_TRACE", "TOKEN_WITH_SPACES", "TOKEN_BIDIRECTIONAL",
  "TOKEN_PERMUTABLE", "TOKEN_UNIFY", "TOKEN_SUBSUME", "TOKEN_ASSIGNMENT",
  "TOKEN_PIPE", "TOKEN_NOT", "TOKEN_OR", "TOKEN_AND", "TOKEN_IMPLICATION",
  "TOKEN_EQUIV", "TOKEN_PLUS", "TOKEN_MINUS", "TOKEN_TIMES",
  "TOKEN_DIVIDE", "TOKEN_MODULO", "TOKEN_EQUAL", "TOKEN_DIFF", "TOKEN_LT",
  "TOKEN_LE", "TOKEN_GT", "TOKEN_GE", "TOKEN_IDENTIFIER", "TOKEN_STRING",
  "TOKEN_INTEGER", "TOKEN_DOUBLE", "TOKEN_VARIABLE", "TOKEN_ANONYMOUS",
  "TOKEN_MINUS_U", "TOKEN_NOELSE", "$accept", "axiom", "begin",
  "dictionary", "dictionary_line", "stringOrIdentifier", "lexical_entries",
  "lexical_entry", "rules", "$@1", "$@2", "pref_rule", "rule",
  "terms_vector", "terms", "terms_disj", "term", "structure_statement",
  "list_statement", "statements", "statement",
  "left_hand_side_subset_statement", "right_hand_side_subset_statement",
  "left_hand_side_assignment_statement",
  "right_hand_side_assignment_statement", "expression_statement",
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

#define YYPACT_NINF (-138)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-25)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      78,     1,     9,    17,    22,    63,  -138,    70,    79,     5,
      95,  -138,   448,    80,    86,  -138,  -138,  -138,  -138,  -138,
      65,    30,  -138,    39,  -138,  -138,    98,    95,   -32,  -138,
      42,    94,    97,   100,  -138,  -138,   102,  -138,   106,   107,
    -138,  -138,    13,    79,  -138,   123,    34,    -5,  -138,  -138,
      67,    70,   117,    87,  -138,     2,   -30,     2,   325,   128,
     214,   101,  -138,  -138,  -138,  -138,   140,  -138,  -138,    70,
    -138,   132,  -138,  -138,  -138,    84,   109,  -138,  -138,   109,
    -138,   109,  -138,   110,  -138,   107,  -138,  -138,    75,  -138,
    -138,  -138,  -138,  -138,  -138,  -138,   129,  -138,  -138,  -138,
       0,   151,  -138,  -138,  -138,  -138,  -138,  -138,  -138,  -138,
    -138,  -138,    -4,   158,   114,   189,     5,  -138,     0,  -138,
     138,  -138,  -138,  -138,   293,  -138,   379,  -138,  -138,   113,
     284,  -138,   266,   266,   266,   266,   266,   181,   182,   120,
     120,   376,  -138,  -138,   144,   147,  -138,  -138,   177,  -138,
      16,  -138,  -138,     5,   133,   137,  -138,  -138,  -138,   388,
    -138,   134,   266,   135,  -138,   266,   197,   266,   266,  -138,
    -138,  -138,  -138,   541,  -138,  -138,  -138,  -138,  -138,  -138,
    -138,  -138,  -138,   561,    23,    48,    59,    74,   266,   266,
     169,   178,  -138,  -138,    14,   266,  -138,  -138,  -138,  -138,
    -138,  -138,  -138,   469,   192,   447,   201,   621,  -138,  -138,
     266,   266,   266,   266,   266,   266,   266,   266,   266,   266,
     266,   266,   266,   266,   266,   266,  -138,   266,  -138,  -138,
    -138,   489,   509,   266,   120,   195,  -138,  -138,  -138,  -138,
     196,   561,  -138,   145,   148,  -138,   520,   601,   621,   581,
     581,    44,    44,   162,   162,  -138,   632,   632,   632,   632,
     632,   632,   561,   426,   426,   314,   160,  -138,  -138,  -138,
    -138,   211,  -138,   266,  -138,  -138,   426,   178,  -138
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     2,     0,    22,     0,
       0,     1,     0,     0,     0,    30,    25,    41,    39,    40,
       0,     0,    14,     0,    15,    16,     0,     9,     0,   116,
       0,     0,     0,     0,   143,   144,   117,   120,     0,     0,
       7,     3,     0,    22,     5,     0,     0,     0,     6,     8,
       0,    21,     0,    19,   122,     0,     0,     0,     0,     0,
       0,     0,    26,    27,    28,    29,     0,    23,     4,     0,
      10,     0,    17,    20,    12,     0,   123,   124,   127,   125,
     126,   129,   128,     0,   119,   118,   115,   139,     0,   131,
     136,   135,   140,   138,   130,   134,   141,   133,   137,   132,
       0,     0,    11,    18,   121,   146,   153,   152,   155,   154,
     151,   156,     0,   150,     0,     0,     0,    44,     0,    34,
      35,    38,    32,    13,     0,   145,     0,   142,   110,     0,
       0,    43,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    49,    45,     0,     0,    67,    68,    62,    69,
       0,    33,    31,     0,     0,     0,   149,   111,    48,     0,
     109,     0,     0,     0,    99,     0,     0,     0,     0,    92,
      91,    90,   101,     0,    94,    95,    96,    97,   104,    98,
     100,   102,   105,   108,     0,     0,     0,     0,     0,     0,
       0,     0,    42,    46,     0,     0,    50,    36,    37,   148,
     147,    47,   112,     0,   114,     0,     0,    76,    88,    51,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    52,     0,    53,    54,
      55,     0,     0,     0,     0,     0,    64,    65,    66,    63,
       0,    71,   103,     0,     0,    89,    93,    72,    73,    74,
      75,    83,    84,    85,    86,    87,    77,    78,    79,    80,
      81,    82,   107,     0,     0,     0,     0,    57,    56,   113,
     106,    58,    60,     0,    61,    70,     0,   102,    59
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -138,  -138,  -138,   219,  -138,   104,   172,  -138,   205,  -138,
    -138,  -138,  -138,  -138,   141,   146,    -6,   143,   149,  -138,
    -137,  -138,  -138,  -138,  -138,    18,    40,    56,  -110,  -107,
      71,  -138,    -7,  -138,  -138,   206,   207,   -28,     7,   -10,
     -33,   150,   163
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     5,     6,    26,    27,    28,    52,    53,    14,    15,
      16,    42,    43,   118,   119,   120,   121,   122,   141,   142,
     143,   144,   235,   145,   240,   183,   184,   174,   175,   176,
     177,   178,   179,    59,    36,    37,    94,   180,    96,   181,
     182,   112,   113
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      13,    17,    39,    20,   193,   146,    17,    12,   147,     7,
     115,    70,   116,    45,    17,   124,   117,     8,   160,    38,
     146,   161,   193,   147,    50,     9,    12,    98,    98,   197,
      10,   146,    95,    95,   147,    51,    66,    24,    25,   226,
      71,    35,    78,   227,    73,    77,    80,    82,    85,   146,
      97,    97,   147,    93,    93,   111,    62,    63,    64,    65,
     109,   125,   101,    11,   228,    38,   153,    18,   227,    24,
      25,    19,    18,    35,    44,   229,    19,    12,   110,   227,
      18,   108,    12,    69,    19,    35,   127,    12,   -24,    40,
     230,   111,     1,   111,   227,    41,   109,    46,   109,     2,
       3,     4,   217,   218,   219,   149,    47,    48,   148,    54,
      21,    22,    55,    12,   110,    56,   110,   108,    57,   108,
     149,    23,    58,   148,    60,    61,   271,   272,   274,   190,
     191,   149,    68,    74,   148,    72,    87,    75,    88,   278,
     105,    86,    34,   100,   106,   107,    35,   198,   102,   149,
     173,    51,   148,   146,   146,   146,   147,   147,   147,    76,
      79,    81,    24,    25,    88,    50,   146,   123,    34,   147,
      90,    91,    35,    92,   185,   186,   187,   104,   126,   114,
     203,    34,   157,   205,   239,   207,   208,   238,   153,   188,
     189,    35,   194,   196,   128,   129,   195,   234,   199,   130,
     131,    12,   200,   202,   204,   206,   231,   232,   233,   243,
     245,   267,   268,   241,   269,   270,   132,   133,   134,   135,
     136,   137,   219,   138,   266,   275,    12,   139,   246,   247,
     248,   249,   250,   251,   252,   253,   254,   255,   256,   257,
     258,   259,   260,   261,   276,   262,    49,   103,    67,    87,
     236,   265,   140,   149,   149,   149,   148,   148,   148,   151,
      35,   152,   150,   277,    84,   237,   149,     0,    99,   148,
     160,   128,   129,   161,   162,     0,   156,    88,    12,   159,
     163,    34,    89,    90,    91,    35,    92,   155,     0,   128,
     129,   258,     0,     0,   130,   158,    12,     0,     0,     0,
       0,   164,     0,     0,     0,    12,   165,     0,   166,     0,
       0,   132,   133,   134,   135,   136,   137,   167,   138,   128,
     129,     0,   139,   168,   130,     0,    12,     0,   154,    88,
       0,     0,     0,    34,   169,   170,   171,    35,   172,     0,
      83,   132,   133,   134,   135,   136,   137,   140,   138,    31,
      32,    33,   139,     0,     0,    35,    88,     0,     0,     0,
      34,   210,   106,   107,    35,     0,   211,   212,   213,   214,
     215,   216,   217,   218,   219,   220,   221,   273,   223,   224,
     225,   128,   129,     0,     0,    35,   130,   192,    12,     0,
       0,    12,    34,   128,   129,     0,    35,     0,   130,   201,
      12,     0,     0,   132,   133,   134,   135,   136,   137,     0,
     138,     0,     0,     0,   139,   132,   133,   134,   135,   136,
     137,     0,   138,     0,     0,     0,   139,     0,     0,     0,
       0,   128,   129,     0,     0,     0,   130,     0,    12,   140,
       0,     0,    88,     0,     0,     0,    34,    35,   106,   107,
      35,   140,     0,   132,   133,   134,   135,   136,   137,    35,
     138,    29,     0,    30,   139,     0,     0,     0,     0,     0,
       0,     0,    31,    32,    33,     0,     0,     0,   242,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   244,   140,
       0,     0,     0,     0,   210,     0,     0,    35,   263,   211,
     212,   213,   214,   215,   216,   217,   218,   219,   220,   221,
     222,   223,   224,   225,     0,    34,   210,     0,   264,    35,
       0,   211,   212,   213,   214,   215,   216,   217,   218,   219,
     220,   221,   222,   223,   224,   225,   210,     0,     0,     0,
       0,   211,   212,   213,   214,   215,   216,   217,   218,   219,
     220,   221,   222,   223,   224,   225,   210,   209,     0,     0,
       0,   211,   212,   213,   214,   215,   216,   217,   218,   219,
     220,   221,   222,   223,   224,   225,   215,   216,   217,   218,
     219,   220,   221,   222,   223,   224,   225,     0,   210,     0,
       0,     0,     0,   211,   212,   213,   214,   215,   216,   217,
     218,   219,   220,   221,   222,   223,   224,   225,   210,     0,
       0,     0,     0,   211,   212,   213,   214,   215,   216,   217,
     218,   219,   220,   221,   222,   223,   224,   225,   210,     0,
       0,     0,     0,   211,   212,   -25,   -25,   215,   216,   217,
     218,   219,   220,   221,   222,   223,   224,   225,   210,     0,
       0,     0,     0,     0,   212,     0,     0,   215,   216,   217,
     218,   219,   220,   221,   222,   223,   224,   225,   210,     0,
       0,     0,     0,     0,     0,     0,     0,   215,   216,   217,
     218,   219,   220,   221,   222,   223,   224,   225,   215,   216,
     217,   218,   219,   -25,   -25,   -25,   -25,   -25,   -25
};

static const yytype_int16 yycheck[] =
{
       7,     1,    12,     9,   141,   115,     1,    12,   115,     8,
      10,    16,    12,    20,     1,    19,    16,     8,     4,    12,
     130,     7,   159,   130,    56,     8,    12,    60,    61,    13,
       8,   141,    60,    61,   141,    67,    42,    67,    68,    16,
      47,    71,    72,    20,    51,    55,    56,    57,    58,   159,
      60,    61,   159,    60,    61,    88,    43,    44,    45,    46,
      88,    65,    69,     0,    16,    58,    50,    67,    20,    67,
      68,    71,    67,    71,     9,    16,    71,    12,    88,    20,
      67,    88,    12,    49,    71,    71,   114,    12,     9,     9,
      16,   124,    14,   126,    20,     9,   124,    67,   126,    21,
      22,    23,    58,    59,    60,   115,    67,     9,   115,    67,
      15,    16,    18,    12,   124,    18,   126,   124,    18,   126,
     130,    26,    20,   130,    18,    18,   263,   264,   265,   139,
     140,   141,     9,    16,   141,    68,    35,    50,    63,   276,
      65,    13,    67,     3,    69,    70,    71,   153,    16,   159,
     132,    67,   159,   263,   264,   265,   263,   264,   265,    55,
      56,    57,    67,    68,    63,    56,   276,    16,    67,   276,
      69,    70,    71,    72,   134,   135,   136,    67,    20,    50,
     162,    67,    69,   165,   194,   167,   168,   194,    50,     8,
       8,    71,    48,    16,     5,     6,    49,    19,    65,    10,
      11,    12,    65,    69,    69,     8,   188,   189,    39,    17,
       9,    16,    16,   195,    69,    67,    27,    28,    29,    30,
      31,    32,    60,    34,   234,    65,    12,    38,   210,   211,
     212,   213,   214,   215,   216,   217,   218,   219,   220,   221,
     222,   223,   224,   225,    33,   227,    27,    75,    43,    35,
     194,   233,    63,   263,   264,   265,   263,   264,   265,   118,
      71,   118,   116,   273,    58,   194,   276,    -1,    61,   276,
       4,     5,     6,     7,     8,    -1,   126,    63,    12,   130,
      14,    67,    68,    69,    70,    71,    72,   124,    -1,     5,
       6,   273,    -1,    -1,    10,    11,    12,    -1,    -1,    -1,
      -1,    35,    -1,    -1,    -1,    12,    40,    -1,    42,    -1,
      -1,    27,    28,    29,    30,    31,    32,    51,    34,     5,
       6,    -1,    38,    57,    10,    -1,    12,    -1,    35,    63,
      -1,    -1,    -1,    67,    68,    69,    70,    71,    72,    -1,
      15,    27,    28,    29,    30,    31,    32,    63,    34,    24,
      25,    26,    38,    -1,    -1,    71,    63,    -1,    -1,    -1,
      67,    47,    69,    70,    71,    -1,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,     5,     6,    -1,    -1,    71,    10,    11,    12,    -1,
      -1,    12,    67,     5,     6,    -1,    71,    -1,    10,    11,
      12,    -1,    -1,    27,    28,    29,    30,    31,    32,    -1,
      34,    -1,    -1,    -1,    38,    27,    28,    29,    30,    31,
      32,    -1,    34,    -1,    -1,    -1,    38,    -1,    -1,    -1,
      -1,     5,     6,    -1,    -1,    -1,    10,    -1,    12,    63,
      -1,    -1,    63,    -1,    -1,    -1,    67,    71,    69,    70,
      71,    63,    -1,    27,    28,    29,    30,    31,    32,    71,
      34,    13,    -1,    15,    38,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    24,    25,    26,    -1,    -1,    -1,     9,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    41,    63,
      -1,    -1,    -1,    -1,    47,    -1,    -1,    71,     9,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    -1,    67,    47,    -1,     9,    71,
      -1,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    47,    -1,    -1,    -1,
      -1,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    47,    16,    -1,    -1,
      -1,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    -1,    47,    -1,
      -1,    -1,    -1,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    47,    -1,
      -1,    -1,    -1,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    47,    -1,
      -1,    -1,    -1,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    47,    -1,
      -1,    -1,    -1,    -1,    53,    -1,    -1,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    47,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    14,    21,    22,    23,    76,    77,     8,     8,     8,
       8,     0,    12,   107,    83,    84,    85,     1,    67,    71,
      91,    15,    16,    26,    67,    68,    78,    79,    80,    13,
      15,    24,    25,    26,    67,    71,   109,   110,   113,   114,
       9,     9,    86,    87,     9,   107,    67,    67,     9,    78,
      56,    67,    81,    82,    67,    18,    18,    18,    20,   108,
      18,    18,    43,    44,    45,    46,    91,    83,     9,    49,
      16,   107,    68,   107,    16,    50,    80,   114,    72,    80,
     114,    80,   114,    15,   110,   114,    13,    35,    63,    68,
      69,    70,    72,   107,   111,   112,   113,   114,   115,   111,
       3,   107,    16,    81,    67,    65,    69,    70,   107,   112,
     114,   115,   116,   117,    50,    10,    12,    16,    88,    89,
      90,    91,    92,    16,    19,    65,    20,   112,     5,     6,
      10,    11,    27,    28,    29,    30,    31,    32,    34,    38,
      63,    93,    94,    95,    96,    98,   103,   104,   107,   114,
      90,    89,    92,    50,    35,   117,   116,    69,    11,    93,
       4,     7,     8,    14,    35,    40,    42,    51,    57,    68,
      69,    70,    72,   100,   102,   103,   104,   105,   106,   107,
     112,   114,   115,   100,   101,   101,   101,   101,     8,     8,
     114,   114,    11,    95,    48,    49,    16,    13,    91,    65,
      65,    11,    69,   100,    69,   100,     8,   100,   100,    16,
      47,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    16,    20,    16,    16,
      16,   100,   100,    39,    19,    97,   102,   105,   107,   114,
      99,   100,     9,    17,    41,     9,   100,   100,   100,   100,
     100,   100,   100,   100,   100,   100,   100,   100,   100,   100,
     100,   100,   100,     9,     9,   100,   114,    16,    16,    69,
      67,    95,    95,    63,    95,    65,    33,   114,    95
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    75,    76,    77,    77,    77,    77,    77,    78,    78,
      79,    79,    79,    79,    79,    80,    80,    80,    81,    81,
      82,    82,    84,    83,    85,    83,    86,    86,    86,    86,
      86,    87,    87,    88,    88,    89,    89,    90,    90,    91,
      91,    91,    92,    92,    92,    93,    93,    94,    94,    95,
      95,    95,    95,    95,    95,    95,    95,    95,    95,    95,
      95,    95,    96,    97,    97,    97,    97,    98,    98,    98,
      98,    99,   100,   100,   100,   100,   100,   100,   100,   100,
     100,   100,   100,   100,   100,   100,   100,   100,   100,   100,
     100,   100,   100,   100,   100,   100,   100,   100,   100,   100,
     100,   100,   100,   100,   100,   100,   100,   101,   101,   102,
     103,   104,   105,   106,   106,   107,   107,   108,   108,   109,
     109,   109,   109,   110,   110,   110,   110,   110,   110,   110,
     110,   110,   110,   111,   111,   111,   111,   111,   111,   111,
     111,   112,   112,   113,   114,   115,   115,   115,   115,   116,
     116,   117,   117,   117,   117,   117,   117
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     4,     5,     4,     4,     4,     2,     1,
       3,     4,     3,     5,     1,     1,     1,     3,     3,     1,
       2,     1,     0,     3,     0,     1,     2,     2,     2,     2,
       0,     5,     4,     2,     1,     1,     3,     3,     1,     1,
       1,     1,     3,     2,     1,     1,     2,     3,     2,     1,
       2,     3,     3,     3,     3,     3,     4,     4,     5,     7,
       5,     5,     1,     1,     1,     1,     1,     1,     1,     1,
       5,     1,     3,     3,     3,     3,     2,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     2,     3,
       1,     1,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     1,     1,     4,     3,     1,     1,
       1,     2,     2,     4,     2,     4,     2,     0,     2,     3,
       1,     4,     2,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     1,     1,     3,     2,     5,     5,     3,
       1,     1,     1,     1,     1,     1,     1
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
#line 170 "src/rulesyacc.y"
              {
	  DBUGPRT("axiom done...");
	  YYACCEPT;
	}
#line 1550 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 3: /* begin: TOKEN_RULES TOKEN_LPAR rules TOKEN_RPAR  */
#line 176 "src/rulesyacc.y"
                                               {
	  DBUGPRT("begin grammar");
	}
#line 1558 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 4: /* begin: TOKEN_INPUT TOKEN_LPAR term features TOKEN_RPAR  */
#line 180 "src/rulesyacc.y"
                                                         {
	  DBUGPRT("begin input");
	  parser.setStartTerm((yyvsp[-2].integer_slot));
	  (*(yyvsp[-1].features_slot))->renameVariables((*(yyvsp[-1].features_slot))->getId());
	  parser.setStartFeatures(*(yyvsp[-1].features_slot));
	  free((yyvsp[-1].features_slot));
	}
#line 1570 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 5: /* begin: TOKEN_INPUT TOKEN_LPAR term TOKEN_RPAR  */
#line 188 "src/rulesyacc.y"
                                                {
	  DBUGPRT("begin input");
	  parser.setStartTerm((yyvsp[-1].integer_slot));
	  parser.setStartFeatures(Features::create());
	 }
#line 1580 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 6: /* begin: TOKEN_LEXICON TOKEN_LPAR dictionary TOKEN_RPAR  */
#line 194 "src/rulesyacc.y"
                                                       {
	  DBUGPRT("begin lexicon");
	  //COUT_LINE;
	  //parser.printCacheLexicon(std::cout);
	}
#line 1590 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 7: /* begin: TOKEN_DASH TOKEN_LPAR features TOKEN_RPAR  */
#line 201 "src/rulesyacc.y"
        {
	  DBUGPRT("begin features");
	  parser.setLocalFeatures(*(yyvsp[-1].features_slot));
	  free((yyvsp[-1].features_slot));
	}
#line 1600 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 8: /* dictionary: dictionary_line dictionary  */
#line 208 "src/rulesyacc.y"
                                   {
	  DBUGPRT("dictionary");
	}
#line 1608 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 9: /* dictionary: dictionary_line  */
#line 212 "src/rulesyacc.y"
                         {
	  DBUGPRT("dictionary");
	 }
#line 1616 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 10: /* dictionary_line: TOKEN_FORM TOKEN_IDENTIFIER TOKEN_SEMI  */
#line 219 "src/rulesyacc.y"
        {
	  DBUGPRT("dictionary_line");
	  uint16_t code = Vartable::nameToCode(*(yyvsp[-1].string_slot));
	  free((yyvsp[-1].string_slot));
	  // constantNoun => (0 => args)
	  auto foundCode = parser.findCacheLexicon(code);
	  Parser::entries_map* formToEntries;
	  if (foundCode != parser.cendCacheLexicon()){
	    formToEntries = foundCode->second;
	  } else {
	    formToEntries = new Parser::entries_map();
	    parser._insertCacheLexicon(std::make_pair(code, formToEntries));
	  }
	  auto foundHead = formToEntries->find(Vartable::IS_A_FORM);
	  entriesPtr entries;
	  if (foundHead != formToEntries->cend()){
	    entries = foundHead->second;
	  } else {
	    entries = Entries::create();
	    formToEntries->insert(std::make_pair(Vartable::IS_A_FORM, entries));
	  }
	  entries->add(Entry::create(/*code, */Features::create()));
	}
#line 1644 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 11: /* dictionary_line: TOKEN_FORM TOKEN_IDENTIFIER features TOKEN_SEMI  */
#line 244 "src/rulesyacc.y"
        {
	  DBUGPRT("dictionary_line");
	  uint16_t code = Vartable::nameToCode(*(yyvsp[-2].string_slot));
	  free((yyvsp[-2].string_slot));
	  // constantNoun => (0 => args)
	  auto foundCode = parser.findCacheLexicon(code);
	  Parser::entries_map* formToEntries;
	  if (foundCode != parser.cendCacheLexicon()) {
	    formToEntries = foundCode->second;
	  } else {
	    formToEntries = new Parser::entries_map;
	    parser._insertCacheLexicon(std::make_pair(code, formToEntries));
	  }
	  auto foundHead = formToEntries->find(Vartable::IS_A_FORM);
	  entriesPtr entries;
	  if (foundHead != formToEntries->cend()){
	    entries = foundHead->second;
	  } else {
	    entries = Entries::create();
	    formToEntries->insert(std::make_pair(Vartable::IS_A_FORM, entries));
	  }
	  entries->add(Entry::create(/*code, */*(yyvsp[-1].features_slot)));
	  free((yyvsp[-1].features_slot));
	}
#line 1673 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 12: /* dictionary_line: stringOrIdentifier lexical_entries TOKEN_SEMI  */
#line 271 "src/rulesyacc.y"
        {
	  DBUGPRT("dictionary_line");
	  for (auto entries_map = (*(yyvsp[-1].entries_slot)).cbegin() ; entries_map != (*(yyvsp[-1].entries_slot)).cend() ; ++entries_map) {
		uint16_t pos = entries_map->first;
		featuresPtr features = entries_map->second;
		uint16_t head = features->assignHead();
		
		//std::cerr << Vartable::codeToName(pos) << std::endl;
		//features->flatPrint(std::cerr);
		//std::cerr << Vartable::codeToName(head) << std::endl;
		
	    //(*entry)->setForm(*$1);
	    entriesPtr entries;
	    Parser::entries_map* headToEntries;
		auto foundCode = parser.findCacheLexicon(pos);
	    if (foundCode != parser.cendCacheLexicon()){
	      headToEntries = foundCode->second;
	    } else {
	      headToEntries = new Parser::entries_map;
	      parser._insertCacheLexicon(std::make_pair(pos, headToEntries));
	    }
	    Parser::entries_map_iterator foundHead = headToEntries->find(head);
	    if (foundHead != headToEntries->cend()){
	      entries = foundHead->second;
	    } else {
	      entries = Entries::create();
	      headToEntries->insert(std::make_pair(head, entries));
	    }
	    entries->add(Entry::create(*(yyvsp[-2].string_slot), features));
	  }
	  free((yyvsp[-2].string_slot));
	  free((yyvsp[-1].entries_slot));
	}
#line 1711 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 13: /* dictionary_line: TOKEN_AROBASE TOKEN_IDENTIFIER TOKEN_ASSIGNMENT features TOKEN_SEMI  */
#line 307 "src/rulesyacc.y"
        {
	  DBUGPRT("dictionary_line");
	  parser.addMacros(*(yyvsp[-3].string_slot), *(yyvsp[-1].features_slot));
	  free((yyvsp[-3].string_slot));
	  free((yyvsp[-1].features_slot));
	}
#line 1722 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 14: /* dictionary_line: TOKEN_SEMI  */
#line 315 "src/rulesyacc.y"
        {
	  DBUGPRT("dictionary_line");
	}
#line 1730 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 15: /* stringOrIdentifier: TOKEN_IDENTIFIER  */
#line 320 "src/rulesyacc.y"
                         {
	  DBUGPRT("stringOrIdentifier");
	  (yyval.string_slot) = (yyvsp[0].string_slot);
	}
#line 1739 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 16: /* stringOrIdentifier: TOKEN_STRING  */
#line 325 "src/rulesyacc.y"
                      {
	  DBUGPRT("stringOrIdentifier");
	  (yyval.string_slot) = (yyvsp[0].string_slot);
	 }
#line 1748 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 17: /* stringOrIdentifier: stringOrIdentifier TOKEN_PLUS TOKEN_STRING  */
#line 330 "src/rulesyacc.y"
                                                    {
	  DBUGPRT("string");
	  (yyval.string_slot) = (yyvsp[-2].string_slot);
	  *(yyval.string_slot) += *(yyvsp[0].string_slot);
	 }
#line 1758 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 18: /* lexical_entries: lexical_entry TOKEN_PIPE lexical_entries  */
#line 338 "src/rulesyacc.y"
        {
	  DBUGPRT("lexical_entries");
	  (yyval.entries_slot) = (yyvsp[0].entries_slot);
	  (yyval.entries_slot)->push_back(*(yyvsp[-2].entry_slot));
	  free((yyvsp[-2].entry_slot));
	}
#line 1769 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 19: /* lexical_entries: lexical_entry  */
#line 346 "src/rulesyacc.y"
                       {
	  DBUGPRT("lexical_entries");
	  (yyval.entries_slot) = new std::vector<std::pair<uint16_t, featuresPtr> >;
	  (yyval.entries_slot)->push_back(*(yyvsp[0].entry_slot));
	  free((yyvsp[0].entry_slot));
	 }
#line 1780 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 20: /* lexical_entry: TOKEN_IDENTIFIER features  */
#line 356 "src/rulesyacc.y"
        {
	  DBUGPRT("lexical_entry");
	  (yyval.entry_slot) = new std::pair<uint16_t, featuresPtr>(std::make_pair(Vartable::nameToCode(*(yyvsp[-1].string_slot)), *(yyvsp[0].features_slot)));
	  free((yyvsp[-1].string_slot));
	  free((yyvsp[0].features_slot));
	}
#line 1791 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 21: /* lexical_entry: TOKEN_IDENTIFIER  */
#line 365 "src/rulesyacc.y"
        {
	  DBUGPRT("lexical_entry");
	  (yyval.entry_slot) = new std::pair<uint16_t, featuresPtr>(std::make_pair(Vartable::nameToCode(*(yyvsp[0].string_slot)), Features::create()));
	  free((yyvsp[0].string_slot));
	}
#line 1801 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 22: /* $@1: %empty  */
#line 375 "src/rulesyacc.y"
        {headLineno = ruleslineno;}
#line 1807 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 23: /* rules: $@1 rule rules  */
#line 376 "src/rulesyacc.y"
        {
	  DBUGPRT("rules");
	}
#line 1815 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 24: /* $@2: %empty  */
#line 380 "src/rulesyacc.y"
         {headLineno = ruleslineno;}
#line 1821 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 25: /* rules: $@2  */
#line 381 "src/rulesyacc.y"
        {
	  DBUGPRT("rules");
	}
#line 1829 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 26: /* pref_rule: pref_rule TOKEN_TRACE  */
#line 387 "src/rulesyacc.y"
        {
	  DBUGPRT("pref_rule");
	  headTrace = true;
	}
#line 1838 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 27: /* pref_rule: pref_rule TOKEN_WITH_SPACES  */
#line 393 "src/rulesyacc.y"
        {
	  DBUGPRT("pref_rule");
	  withSpaces = true;
	}
#line 1847 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 28: /* pref_rule: pref_rule TOKEN_BIDIRECTIONAL  */
#line 399 "src/rulesyacc.y"
        {
	  DBUGPRT("pref_rule");
	  bidirectional = true;
	}
#line 1856 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 29: /* pref_rule: pref_rule TOKEN_PERMUTABLE  */
#line 405 "src/rulesyacc.y"
        {
	  DBUGPRT("pref_rule");
	  permutable = true;
	}
#line 1865 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 30: /* pref_rule: %empty  */
#line 410 "src/rulesyacc.y"
                      {
	  DBUGPRT("pref_rule");
	  headTrace = false;
	  withSpaces = false;
	  bidirectional = false;
	  permutable = false;
	}
#line 1877 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 31: /* rule: pref_rule term TOKEN_RIGHTARROW terms_vector structure_statement  */
#line 420 "src/rulesyacc.y"
        {
	  DBUGPRT("rule");
	  if (bidirectional && permutable){
		yyerror((char*)"This rule is both permutable and bidirectional");

	  }
	  if (permutable && (yyvsp[-1].vector_terms_slot)->size() <= 2){
		yyerror((char*)"This rule with fewer than 3 terms must be bidirectional, not permutable");

	  }
	  rulePtr rule = Rule::create(headLineno, parser.getTopBufferName(), withSpaces, bidirectional, permutable, (yyvsp[-3].integer_slot), *(yyvsp[-1].vector_terms_slot), (yyvsp[0].statements_slot) ? *(yyvsp[0].statements_slot) : statementsPtr());
	  rule->setTrace(headTrace);
	  parser.getRules().addRule(rule);
	  if (!parser.getRules().getStartTerm()){
	    parser.getRules().setStartTerm((yyvsp[-3].integer_slot));
	  }
	  free((yyvsp[-1].vector_terms_slot));
	  if ((yyvsp[0].statements_slot))
	     free((yyvsp[0].statements_slot));
	}
#line 1902 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 32: /* rule: pref_rule term TOKEN_RIGHTARROW structure_statement  */
#line 442 "src/rulesyacc.y"
        {
	  DBUGPRT("Rule");
	  rulePtr rule = Rule::create(headLineno, parser.getTopBufferName(), withSpaces, bidirectional, permutable, (yyvsp[-2].integer_slot), (yyvsp[0].statements_slot) ? *(yyvsp[0].statements_slot) : statementsPtr());
	  rule->setTrace(headTrace);
	  parser.getRules().addRule(rule);
	  if (!parser.getRules().getStartTerm()){
	    parser.getRules().setStartTerm((yyvsp[-2].integer_slot));
	  }
	  if ((yyvsp[0].statements_slot))
	    free((yyvsp[0].statements_slot));
	}
#line 1918 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 33: /* terms_vector: terms_vector terms  */
#line 455 "src/rulesyacc.y"
                           {
	  DBUGPRT("term_vector");
	  (yyval.vector_terms_slot)=(yyvsp[-1].vector_terms_slot);
	  (yyval.vector_terms_slot)->push_back(*(yyvsp[0].terms_slot));
	}
#line 1928 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 34: /* terms_vector: terms  */
#line 461 "src/rulesyacc.y"
               {
	  DBUGPRT("term_vector");
	  (yyval.vector_terms_slot) = new std::vector< termsPtr >;
	  (yyval.vector_terms_slot)->push_back(*(yyvsp[0].terms_slot));
	}
#line 1938 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 35: /* terms: terms_disj  */
#line 468 "src/rulesyacc.y"
                   {
	  DBUGPRT("term");
	  (yyval.terms_slot)=(yyvsp[0].terms_slot);
	}
#line 1947 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 36: /* terms: TOKEN_LBRACKET terms_disj TOKEN_RBRACKET  */
#line 473 "src/rulesyacc.y"
                                                  {
	  DBUGPRT("term");
	  (yyval.terms_slot) = (yyvsp[-1].terms_slot);
	  (*(yyval.terms_slot))->setOptional();
	}
#line 1957 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 37: /* terms_disj: terms_disj TOKEN_PIPE term  */
#line 481 "src/rulesyacc.y"
        {
	  DBUGPRT("term_disj");
	  (yyval.terms_slot) = (yyvsp[-2].terms_slot);
	  (*(yyval.terms_slot))->push_back((yyvsp[0].integer_slot));
	}
#line 1967 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 38: /* terms_disj: term  */
#line 488 "src/rulesyacc.y"
        {
	  DBUGPRT("term_disj");
	  (yyval.terms_slot) = new termsPtr(Terms::create((yyvsp[0].integer_slot)));
	}
#line 1976 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 39: /* term: TOKEN_IDENTIFIER  */
#line 495 "src/rulesyacc.y"
        {
	  DBUGPRT("term_id");
	  (yyval.integer_slot) = Vartable::nameToCode(*(yyvsp[0].string_slot));
	  free((yyvsp[0].string_slot));
	}
#line 1986 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 40: /* term: TOKEN_VARIABLE  */
#line 502 "src/rulesyacc.y"
        {
	  DBUGPRT("term_id");
	  (yyval.integer_slot) = Vartable::nameToCode(*(yyvsp[0].string_slot));
	  free((yyvsp[0].string_slot));
	}
#line 1996 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 41: /* term: error  */
#line 509 "src/rulesyacc.y"
        {
	  YYABORT;
	}
#line 2004 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 42: /* structure_statement: TOKEN_LBRACE list_statement TOKEN_RBRACE  */
#line 518 "src/rulesyacc.y"
        {
	  DBUGPRT("structure_statement");
	  (yyval.statements_slot)=(yyvsp[-1].statements_slot);
	}
#line 2013 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 43: /* structure_statement: TOKEN_LBRACE TOKEN_RBRACE  */
#line 524 "src/rulesyacc.y"
        {
	  (yyval.statements_slot)=NULL;
	}
#line 2021 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 44: /* structure_statement: TOKEN_SEMI  */
#line 529 "src/rulesyacc.y"
        {
	  (yyval.statements_slot)=NULL;
	}
#line 2029 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 45: /* list_statement: statement  */
#line 535 "src/rulesyacc.y"
        {
	  DBUGPRT("list_statement");
	  (yyval.statements_slot) = new statementsPtr(Statements::create());
	  (*(yyval.statements_slot))->addStatement(*(yyvsp[0].statement_slot));
	  free((yyvsp[0].statement_slot));
	}
#line 2040 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 46: /* list_statement: list_statement statement  */
#line 542 "src/rulesyacc.y"
                                  {
	  DBUGPRT("list_statement");
	  (yyval.statements_slot) = (yyvsp[-1].statements_slot);
	  (*(yyval.statements_slot))->addStatement(*(yyvsp[0].statement_slot));
	  free((yyvsp[0].statement_slot));
	}
#line 2051 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 47: /* statements: TOKEN_LBRACE list_statement TOKEN_RBRACE  */
#line 551 "src/rulesyacc.y"
        {
	  DBUGPRT("statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::STMS_STATEMENT, false, *(yyvsp[-1].statements_slot)));
	  free((yyvsp[-1].statements_slot));
	}
#line 2061 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 48: /* statements: TOKEN_LBRACE TOKEN_RBRACE  */
#line 558 "src/rulesyacc.y"
        {
	  DBUGPRT("statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::STMS_STATEMENT, false, Statements::create()));
	}
#line 2070 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 49: /* statement: statements  */
#line 564 "src/rulesyacc.y"
                   {
	  DBUGPRT("statement");
	  (yyval.statement_slot)=(yyvsp[0].statement_slot);
	 }
#line 2079 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 50: /* statement: features TOKEN_SEMI  */
#line 569 "src/rulesyacc.y"
                             {
	  DBUGPRT("statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::GUARD_STATEMENT, true, *(yyvsp[-1].features_slot)));
	  free((yyvsp[-1].features_slot));
	}
#line 2089 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 51: /* statement: TOKEN_ATTEST expression_statement TOKEN_SEMI  */
#line 575 "src/rulesyacc.y"
                                                      {
	  DBUGPRT("statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::ATTEST_STATEMENT, true, *(yyvsp[-1].statement_slot)));
	  free((yyvsp[-1].statement_slot));
	}
#line 2099 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 52: /* statement: TOKEN_PRINT expression_statement_composite TOKEN_SEMI  */
#line 581 "src/rulesyacc.y"
                                                               {
	  DBUGPRT("statement");
		(yyval.statement_slot) = new statementPtr(Statement::create(
			ruleslineno, 
			parser.getTopBufferName(), 
			Statement::PRINT_STATEMENT, 
			true, 
			*(yyvsp[-1].statements_slot)));
	  free((yyvsp[-1].statements_slot));
	}
#line 2114 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 53: /* statement: TOKEN_PRINTLN expression_statement_composite TOKEN_SEMI  */
#line 592 "src/rulesyacc.y"
                                                                 {
	  	DBUGPRT("statement");
		(yyval.statement_slot) = new statementPtr(Statement::create(
			ruleslineno, 
			parser.getTopBufferName(), 
			Statement::PRINTLN_STATEMENT, 
			true, 
			*(yyvsp[-1].statements_slot)));
	  free((yyvsp[-1].statements_slot));
	}
#line 2129 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 54: /* statement: TOKEN_PRINTSTDERR expression_statement_composite TOKEN_SEMI  */
#line 603 "src/rulesyacc.y"
                                                                     {
	  DBUGPRT("statement");
		(yyval.statement_slot) = new statementPtr(Statement::create(
			ruleslineno, 
			parser.getTopBufferName(), 
			Statement::PRINTSTDERR_STATEMENT, 
			true, 
			*(yyvsp[-1].statements_slot)));
	  free((yyvsp[-1].statements_slot));
	}
#line 2144 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 55: /* statement: TOKEN_PRINTLNSTDERR expression_statement_composite TOKEN_SEMI  */
#line 614 "src/rulesyacc.y"
                                                                       {
	  	DBUGPRT("statement");
		(yyval.statement_slot) = new statementPtr(Statement::create(
			ruleslineno, 
			parser.getTopBufferName(), 
			Statement::PRINTLNSTDERR_STATEMENT, 
			true, 
			*(yyvsp[-1].statements_slot)));
	  free((yyvsp[-1].statements_slot));
	}
#line 2159 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 56: /* statement: left_hand_side_assignment_statement TOKEN_ASSIGNMENT right_hand_side_assignment_statement TOKEN_SEMI  */
#line 625 "src/rulesyacc.y"
                                                                                                              {
	  DBUGPRT("statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::ASSIGNMENT_STATEMENT, true, *(yyvsp[-3].statement_slot), *(yyvsp[-1].statement_slot)));
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
	    yyerror((char*)"bad assignment expression");
	  }
	  free((yyvsp[-3].statement_slot));
	  free((yyvsp[-1].statement_slot));
	}
#line 2226 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 57: /* statement: left_hand_side_subset_statement TOKEN_SUBSUME right_hand_side_subset_statement TOKEN_SEMI  */
#line 688 "src/rulesyacc.y"
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
	    yyerror((char* )"bad subsumption expression");
	  free((yyvsp[-3].statement_slot));
	  free((yyvsp[-1].statement_slot));
	}
#line 2247 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 58: /* statement: TOKEN_IF TOKEN_LPAR expression_statement TOKEN_RPAR statement  */
#line 705 "src/rulesyacc.y"
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
#line 2263 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 59: /* statement: TOKEN_IF TOKEN_LPAR expression_statement TOKEN_RPAR statement TOKEN_ELSE statement  */
#line 717 "src/rulesyacc.y"
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
#line 2280 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 60: /* statement: TOKEN_DEFERRED TOKEN_LPAR expression_statement TOKEN_RPAR statement  */
#line 730 "src/rulesyacc.y"
                                                                             {
	  DBUGPRT("statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno,
						parser.getTopBufferName(), 
						Statement::DEFERRED_STATEMENT,
						true, 
						*(yyvsp[-2].statement_slot),
						*(yyvsp[0].statement_slot)));
	  free((yyvsp[-2].statement_slot));
	  free((yyvsp[0].statement_slot));
	}
#line 2296 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 61: /* statement: TOKEN_FOREACH variable TOKEN_IN expression_statement statement  */
#line 742 "src/rulesyacc.y"
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
#line 2313 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 62: /* left_hand_side_subset_statement: features  */
#line 756 "src/rulesyacc.y"
                 {
	  DBUGPRT("left_hand_side_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::FEATURES_STATEMENT, false, *(yyvsp[0].features_slot)));
	  free((yyvsp[0].features_slot));
	}
#line 2323 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 63: /* right_hand_side_subset_statement: variable  */
#line 763 "src/rulesyacc.y"
                 {
	  DBUGPRT("right_hand_side_subset_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::VARIABLE_STATEMENT, false, *(yyvsp[0].bits_slot)));
	  free((yyvsp[0].bits_slot));
	}
#line 2333 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 64: /* right_hand_side_subset_statement: up  */
#line 769 "src/rulesyacc.y"
            {
	  DBUGPRT("right_hand_side_subset_statement");
	  (yyval.statement_slot)=(yyvsp[0].statement_slot);
	}
#line 2342 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 65: /* right_hand_side_subset_statement: down2  */
#line 774 "src/rulesyacc.y"
               {
	  DBUGPRT("right_hand_side_subset_statement");
	  (yyval.statement_slot)=(yyvsp[0].statement_slot);
	}
#line 2351 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 66: /* right_hand_side_subset_statement: features  */
#line 779 "src/rulesyacc.y"
                  {
	  DBUGPRT("right_hand_side_subset_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::FEATURES_STATEMENT, false, *(yyvsp[0].features_slot)));
	  free((yyvsp[0].features_slot));
	}
#line 2361 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 67: /* left_hand_side_assignment_statement: up2  */
#line 787 "src/rulesyacc.y"
            {
	  DBUGPRT("left_hand_side_statement");
	  (yyval.statement_slot)=(yyvsp[0].statement_slot);
	}
#line 2370 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 68: /* left_hand_side_assignment_statement: down  */
#line 792 "src/rulesyacc.y"
              {
	  DBUGPRT("left_hand_side_statement");
	  (yyval.statement_slot)=(yyvsp[0].statement_slot);
	}
#line 2379 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 69: /* left_hand_side_assignment_statement: variable  */
#line 797 "src/rulesyacc.y"
                  {
	  DBUGPRT("left_hand_side_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::VARIABLE_STATEMENT, false, *(yyvsp[0].bits_slot)));
	  free((yyvsp[0].bits_slot));
	 }
#line 2389 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 70: /* left_hand_side_assignment_statement: TOKEN_LT variable TOKEN_CONS variable TOKEN_GT  */
#line 804 "src/rulesyacc.y"
        {
	  DBUGPRT("left_hand_side_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::PAIRP_STATEMENT, false, 
						Pairp::create(Pairp::create(Value::create(Value::VARIABLE_VALUE, *(yyvsp[-3].bits_slot))),
							     Pairp::create(Value::create(Value::VARIABLE_VALUE, *(yyvsp[-1].bits_slot))))));
	  free((yyvsp[-3].bits_slot));
	  free((yyvsp[-1].bits_slot));
	}
#line 2402 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 71: /* right_hand_side_assignment_statement: expression_statement  */
#line 814 "src/rulesyacc.y"
                             {
	  DBUGPRT("right_hand_side_statement");
	  (yyval.statement_slot)=(yyvsp[0].statement_slot);
	}
#line 2411 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 72: /* expression_statement: expression_statement TOKEN_OR expression_statement  */
#line 823 "src/rulesyacc.y"
                                                           {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::FUNCTION_STATEMENT, false, Statement::OR, (*(yyvsp[-2].statement_slot)), (*(yyvsp[0].statement_slot))));
	  free((yyvsp[-2].statement_slot));
	  free((yyvsp[0].statement_slot));
	}
#line 2422 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 73: /* expression_statement: expression_statement TOKEN_AND expression_statement  */
#line 830 "src/rulesyacc.y"
                                                             {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::FUNCTION_STATEMENT, false, Statement::AND, (*(yyvsp[-2].statement_slot)), (*(yyvsp[0].statement_slot))));
	  free((yyvsp[-2].statement_slot));
	  free((yyvsp[0].statement_slot));
	}
#line 2433 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 74: /* expression_statement: expression_statement TOKEN_IMPLICATION expression_statement  */
#line 837 "src/rulesyacc.y"
                                                                     {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::FUNCTION_STATEMENT, false, Statement::OR, Statement::create(ruleslineno, parser.getTopBufferName(), Statement::FUNCTION_STATEMENT, false, Statement::NOT, (*(yyvsp[-2].statement_slot))), (*(yyvsp[0].statement_slot))));
	  free((yyvsp[-2].statement_slot));
	  free((yyvsp[0].statement_slot));
	}
#line 2444 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 75: /* expression_statement: expression_statement TOKEN_EQUIV expression_statement  */
#line 844 "src/rulesyacc.y"
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
#line 2461 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 76: /* expression_statement: TOKEN_NOT expression_statement  */
#line 857 "src/rulesyacc.y"
                                        {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::FUNCTION_STATEMENT, false, Statement::NOT, (*(yyvsp[0].statement_slot))));
	  free((yyvsp[0].statement_slot));
	}
#line 2471 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 77: /* expression_statement: expression_statement TOKEN_EQUAL expression_statement  */
#line 863 "src/rulesyacc.y"
                                                               {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::FUNCTION_STATEMENT, false, Statement::EQ, (*(yyvsp[-2].statement_slot)), (*(yyvsp[0].statement_slot))));
	  free((yyvsp[-2].statement_slot));
	  free((yyvsp[0].statement_slot));
	}
#line 2482 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 78: /* expression_statement: expression_statement TOKEN_DIFF expression_statement  */
#line 870 "src/rulesyacc.y"
                                                              {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::FUNCTION_STATEMENT, false, Statement::DIFF, (*(yyvsp[-2].statement_slot)), (*(yyvsp[0].statement_slot))));
	  free((yyvsp[-2].statement_slot));
	  free((yyvsp[0].statement_slot));
	}
#line 2493 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 79: /* expression_statement: expression_statement TOKEN_LT expression_statement  */
#line 877 "src/rulesyacc.y"
                                                            {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::FUNCTION_STATEMENT, false, Statement::LT, (*(yyvsp[-2].statement_slot)), (*(yyvsp[0].statement_slot))));
	  free((yyvsp[-2].statement_slot));
	  free((yyvsp[0].statement_slot));
	}
#line 2504 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 80: /* expression_statement: expression_statement TOKEN_LE expression_statement  */
#line 884 "src/rulesyacc.y"
                                                            {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::FUNCTION_STATEMENT, false, Statement::LE, (*(yyvsp[-2].statement_slot)), (*(yyvsp[0].statement_slot))));
	  free((yyvsp[-2].statement_slot));
	  free((yyvsp[0].statement_slot));
	}
#line 2515 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 81: /* expression_statement: expression_statement TOKEN_GT expression_statement  */
#line 891 "src/rulesyacc.y"
                                                            {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::FUNCTION_STATEMENT, false, Statement::GT, (*(yyvsp[-2].statement_slot)), (*(yyvsp[0].statement_slot))));
	  free((yyvsp[-2].statement_slot));
	  free((yyvsp[0].statement_slot));
	}
#line 2526 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 82: /* expression_statement: expression_statement TOKEN_GE expression_statement  */
#line 898 "src/rulesyacc.y"
                                                            {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::FUNCTION_STATEMENT, false, Statement::GE, (*(yyvsp[-2].statement_slot)), (*(yyvsp[0].statement_slot))));
	  free((yyvsp[-2].statement_slot));
	  free((yyvsp[0].statement_slot));
	}
#line 2537 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 83: /* expression_statement: expression_statement TOKEN_PLUS expression_statement  */
#line 909 "src/rulesyacc.y"
        {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::FUNCTION_STATEMENT, false, Statement::PLUS, (*(yyvsp[-2].statement_slot)), (*(yyvsp[0].statement_slot))));
	  free((yyvsp[-2].statement_slot));
	  free((yyvsp[0].statement_slot));
	}
#line 2548 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 84: /* expression_statement: expression_statement TOKEN_MINUS expression_statement  */
#line 917 "src/rulesyacc.y"
        {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::FUNCTION_STATEMENT, false, Statement::MINUS, (*(yyvsp[-2].statement_slot)), (*(yyvsp[0].statement_slot))));
	  free((yyvsp[-2].statement_slot));
	  free((yyvsp[0].statement_slot));
	}
#line 2559 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 85: /* expression_statement: expression_statement TOKEN_TIMES expression_statement  */
#line 925 "src/rulesyacc.y"
        {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::FUNCTION_STATEMENT, false, Statement::TIMES, (*(yyvsp[-2].statement_slot)), (*(yyvsp[0].statement_slot))));
	  free((yyvsp[-2].statement_slot));
	  free((yyvsp[0].statement_slot));
	}
#line 2570 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 86: /* expression_statement: expression_statement TOKEN_DIVIDE expression_statement  */
#line 933 "src/rulesyacc.y"
        {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::FUNCTION_STATEMENT, false, Statement::DIVIDE, (*(yyvsp[-2].statement_slot)), (*(yyvsp[0].statement_slot))));
	  free((yyvsp[-2].statement_slot));
	  free((yyvsp[0].statement_slot));
	}
#line 2581 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 87: /* expression_statement: expression_statement TOKEN_MODULO expression_statement  */
#line 941 "src/rulesyacc.y"
        {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::FUNCTION_STATEMENT, false, Statement::MODULO, (*(yyvsp[-2].statement_slot)), (*(yyvsp[0].statement_slot))));
	  free((yyvsp[-2].statement_slot));
	  free((yyvsp[0].statement_slot));
	}
#line 2592 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 88: /* expression_statement: TOKEN_MINUS expression_statement  */
#line 949 "src/rulesyacc.y"
        {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::FUNCTION_STATEMENT, false, Statement::MINUS_U, (*(yyvsp[0].statement_slot)), statementPtr()));
	  free((yyvsp[0].statement_slot));
	}
#line 2602 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 89: /* expression_statement: TOKEN_RAND TOKEN_LPAR TOKEN_RPAR  */
#line 956 "src/rulesyacc.y"
        {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::FUNCTION_STATEMENT, false, Statement::RANDOM));
	}
#line 2611 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 90: /* expression_statement: TOKEN_DOUBLE  */
#line 962 "src/rulesyacc.y"
        {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::NUMBER_STATEMENT, false, (yyvsp[0].double_slot)));
	}
#line 2620 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 91: /* expression_statement: TOKEN_INTEGER  */
#line 968 "src/rulesyacc.y"
        {
	  DBUGPRT("expression_statement");
 	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::NUMBER_STATEMENT, false, (double)(yyvsp[0].integer_slot)));
	}
#line 2629 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 92: /* expression_statement: TOKEN_STRING  */
#line 974 "src/rulesyacc.y"
        {
	  DBUGPRT("expression_statement");
 	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::STRING_STATEMENT, false, *(yyvsp[0].string_slot)));
	}
#line 2638 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 93: /* expression_statement: expression_statement TOKEN_UNIFY expression_statement  */
#line 982 "src/rulesyacc.y"
                                                               {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::UNIF_STATEMENT, false, (*(yyvsp[-2].statement_slot)), (*(yyvsp[0].statement_slot))));
	  free((yyvsp[-2].statement_slot));
	  free((yyvsp[0].statement_slot));
	}
#line 2649 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 94: /* expression_statement: up  */
#line 989 "src/rulesyacc.y"
            {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot)=(yyvsp[0].statement_slot);
	}
#line 2658 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 95: /* expression_statement: up2  */
#line 994 "src/rulesyacc.y"
             {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot)=(yyvsp[0].statement_slot);
	}
#line 2667 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 96: /* expression_statement: down  */
#line 999 "src/rulesyacc.y"
              {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot)=(yyvsp[0].statement_slot);
	}
#line 2676 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 97: /* expression_statement: down2  */
#line 1004 "src/rulesyacc.y"
               {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot)=(yyvsp[0].statement_slot);
	}
#line 2685 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 98: /* expression_statement: features  */
#line 1009 "src/rulesyacc.y"
                  {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::FEATURES_STATEMENT, false, *(yyvsp[0].features_slot)));
	  free((yyvsp[0].features_slot));
	}
#line 2695 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 99: /* expression_statement: TOKEN_NIL  */
#line 1019 "src/rulesyacc.y"
        {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::NIL_STATEMENT, false));
	}
#line 2704 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 100: /* expression_statement: constant  */
#line 1024 "src/rulesyacc.y"
                  {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::CONSTANT_STATEMENT, false, *(yyvsp[0].bits_slot)));
	  free((yyvsp[0].bits_slot));
	}
#line 2714 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 101: /* expression_statement: TOKEN_ANONYMOUS  */
#line 1034 "src/rulesyacc.y"
        {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::ANONYMOUS_STATEMENT, false, Value::STATIC_ANONYMOUS));
	}
#line 2723 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 102: /* expression_statement: variable  */
#line 1039 "src/rulesyacc.y"
                  {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::VARIABLE_STATEMENT, false, *(yyvsp[0].bits_slot)));
	  free((yyvsp[0].bits_slot));
	}
#line 2733 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 103: /* expression_statement: TOKEN_LPAR expression_statement TOKEN_RPAR  */
#line 1045 "src/rulesyacc.y"
                                                    {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot)=(yyvsp[-1].statement_slot);
	}
#line 2742 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 104: /* expression_statement: dash_statement  */
#line 1053 "src/rulesyacc.y"
                        {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot)=(yyvsp[0].statement_slot);
	}
#line 2751 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 105: /* expression_statement: pairp  */
#line 1061 "src/rulesyacc.y"
               {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::PAIRP_STATEMENT, false, *(yyvsp[0].pairp_slot)));
	  free((yyvsp[0].pairp_slot));
	}
#line 2761 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 106: /* expression_statement: TOKEN_SEARCH expression_statement TOKEN_ON TOKEN_IDENTIFIER  */
#line 1070 "src/rulesyacc.y"
                                                                     {
	  	DBUGPRT("expression_statement");
	  	(yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno,
						  parser.getTopBufferName(),
						  Statement::SEARCH_STATEMENT,
						  true,
						  *(yyvsp[-2].statement_slot),
						  Vartable::nameToCode(*(yyvsp[0].string_slot))));
		free((yyvsp[-2].statement_slot));
	  	free((yyvsp[0].string_slot));
	 }
#line 2777 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 107: /* expression_statement_composite: expression_statement_composite TOKEN_COMMA expression_statement  */
#line 1085 "src/rulesyacc.y"
        {
	  DBUGPRT("expression_statement_composite");
	  (yyval.statements_slot) = (yyvsp[-2].statements_slot);
	  (*(yyval.statements_slot))->addStatement(*(yyvsp[0].statement_slot));
	  free((yyvsp[0].statement_slot));
	}
#line 2788 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 108: /* expression_statement_composite: expression_statement  */
#line 1093 "src/rulesyacc.y"
        {
	  DBUGPRT("expression_statement_composite");
	  (yyval.statements_slot) = new statementsPtr(Statements::create());
	  (*(yyval.statements_slot))->addStatement(*(yyvsp[0].statement_slot));
	  free((yyvsp[0].statement_slot));
	}
#line 2799 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 109: /* up: TOKEN_UPARROW  */
#line 1102 "src/rulesyacc.y"
                      {
	  DBUGPRT("up");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::INHERITED_FEATURES_STATEMENT, false));
	}
#line 2808 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 110: /* up2: TOKEN_UP2ARROW  */
#line 1108 "src/rulesyacc.y"
                       {
	  DBUGPRT("up2");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::SYNTHESIZED_FEATURES_STATEMENT, false));
	}
#line 2817 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 111: /* down: TOKEN_DOWNARROW TOKEN_INTEGER  */
#line 1115 "src/rulesyacc.y"
        {
	  DBUGPRT("down");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::INHERITED_CHILDREN_FEATURES_STATEMENT, false, static_cast<uint8_t>((yyvsp[0].integer_slot)-1)));
	}
#line 2826 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 112: /* down2: TOKEN_DOWN2ARROW TOKEN_INTEGER  */
#line 1122 "src/rulesyacc.y"
        {
	  DBUGPRT("down2");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::SYNTHESIZED_CHILDREN_FEATURES_STATEMENT, false, static_cast<uint8_t>((yyvsp[0].integer_slot)-1)));
	}
#line 2835 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 113: /* dash_statement: TOKEN_DASH TOKEN_INTEGER TOKEN_DOT TOKEN_INTEGER  */
#line 1129 "src/rulesyacc.y"
        {
	  DBUGPRT("dash_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::DASH_STATEMENT, false, static_cast<uint8_t>((yyvsp[-2].integer_slot)-1), static_cast<uint8_t>((yyvsp[0].integer_slot)-1)));
	}
#line 2844 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 114: /* dash_statement: TOKEN_DASH TOKEN_INTEGER  */
#line 1135 "src/rulesyacc.y"
        {
	  DBUGPRT("dash_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::DASH_STATEMENT, false, static_cast<uint8_t>((yyvsp[0].integer_slot)-1), UINT8_MAX));
	}
#line 2853 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 115: /* features: TOKEN_LBRACKET features_composite features_composite_tail TOKEN_RBRACKET  */
#line 1145 "src/rulesyacc.y"
        {
	  DBUGPRT("features");
 	  (yyval.features_slot) = (yyvsp[-2].features_slot);
	  if ((yyvsp[-1].feature_slot)) {
	    (*(yyval.features_slot))->add(*(yyvsp[-1].feature_slot));
	    free((yyvsp[-1].feature_slot));
	  }
	}
#line 2866 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 116: /* features: TOKEN_LBRACKET TOKEN_RBRACKET  */
#line 1155 "src/rulesyacc.y"
        {
	  DBUGPRT("features");
	  (yyval.features_slot) = new featuresPtr(Features::create());
	}
#line 2875 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 117: /* features_composite_tail: %empty  */
#line 1162 "src/rulesyacc.y"
        {
	    (yyval.feature_slot) = NULL;
	}
#line 2883 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 118: /* features_composite_tail: TOKEN_COMMA variable  */
#line 1167 "src/rulesyacc.y"
        {
        (yyval.feature_slot) = new featurePtr(Feature::create(Feature::_VARIABLE_, *(yyvsp[0].bits_slot), valuePtr()));
    }
#line 2891 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 119: /* features_composite: features_composite TOKEN_COMMA feature  */
#line 1173 "src/rulesyacc.y"
        {
	  DBUGPRT("feature_components");
	  (yyval.features_slot) = (yyvsp[-2].features_slot);
	  (*(yyval.features_slot))->add(*(yyvsp[0].feature_slot));
	  free((yyvsp[0].feature_slot));
	}
#line 2902 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 120: /* features_composite: feature  */
#line 1181 "src/rulesyacc.y"
        {
	  DBUGPRT("features_composite");
	  (yyval.features_slot) = new featuresPtr(Features::create());
	  (*(yyval.features_slot))->add(*(yyvsp[0].feature_slot));
	  free((yyvsp[0].feature_slot));
	}
#line 2913 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 121: /* features_composite: features_composite TOKEN_COMMA TOKEN_AROBASE TOKEN_IDENTIFIER  */
#line 1190 "src/rulesyacc.y"
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
#line 2930 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 122: /* features_composite: TOKEN_AROBASE TOKEN_IDENTIFIER  */
#line 1205 "src/rulesyacc.y"
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
#line 2947 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 123: /* feature: TOKEN_LEMMA TOKEN_COLON stringOrIdentifier  */
#line 1221 "src/rulesyacc.y"
        {
	  DBUGPRT("feature");
	  (yyval.feature_slot) = new featurePtr(Feature::create(Feature::_LEMMA_, bitsetPtr(), Value::create(Value::IDENTIFIER_VALUE, *(yyvsp[0].string_slot))));
	}
#line 2956 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 124: /* feature: TOKEN_LEMMA TOKEN_COLON variable  */
#line 1228 "src/rulesyacc.y"
        {
	  DBUGPRT("feature");
	  (yyval.feature_slot) = new featurePtr(Feature::create(Feature::_LEMMA_, bitsetPtr(), Value::create(Value::VARIABLE_VALUE, *(yyvsp[0].bits_slot))));
	}
#line 2965 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 125: /* feature: TOKEN_HEAD TOKEN_COLON stringOrIdentifier  */
#line 1235 "src/rulesyacc.y"
        {
	  DBUGPRT("feature");
	  (yyval.feature_slot) = new featurePtr(Feature::create(Feature::_HEAD_, bitsetPtr(), Value::create(Value::IDENTIFIER_VALUE, *(yyvsp[0].string_slot))));
	}
#line 2974 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 126: /* feature: TOKEN_HEAD TOKEN_COLON variable  */
#line 1242 "src/rulesyacc.y"
        {
	  DBUGPRT("feature");
	  (yyval.feature_slot) = new featurePtr(Feature::create(Feature::_HEAD_, bitsetPtr(), Value::create(Value::VARIABLE_VALUE, *(yyvsp[0].bits_slot))));
	  free((yyvsp[0].bits_slot));
	}
#line 2984 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 127: /* feature: TOKEN_HEAD TOKEN_COLON TOKEN_ANONYMOUS  */
#line 1250 "src/rulesyacc.y"
        {
	  DBUGPRT("feature");
	  (yyval.feature_slot) = new featurePtr(Feature::create(Feature::_HEAD_, bitsetPtr(), Value::create(Value::ANONYMOUS_VALUE)));
	}
#line 2993 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 128: /* feature: TOKEN_FORM TOKEN_COLON variable  */
#line 1257 "src/rulesyacc.y"
        {
	  DBUGPRT("feature");
	  (yyval.feature_slot) = new featurePtr(Feature::create(Feature::_FORM_, bitsetPtr(), Value::create(Value::VARIABLE_VALUE, *(yyvsp[0].bits_slot))));
	  free((yyvsp[0].bits_slot));
	}
#line 3003 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 129: /* feature: TOKEN_FORM TOKEN_COLON stringOrIdentifier  */
#line 1264 "src/rulesyacc.y"
        {
	  DBUGPRT("feature");
	  (yyval.feature_slot) = new featurePtr(Feature::create(Feature::_FORM_, bitsetPtr(), Value::create(Value::FORM_VALUE, *(yyvsp[0].string_slot))));
	}
#line 3012 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 130: /* feature: identifier TOKEN_COLON feature_value  */
#line 1270 "src/rulesyacc.y"
        {
	  DBUGPRT("feature");
	  (yyval.feature_slot) = new featurePtr(Feature::create(Feature::_CONSTANT_, *(yyvsp[-2].bits_slot), *(yyvsp[0].value_slot)));
	  free((yyvsp[-2].bits_slot));
	  free((yyvsp[0].value_slot));
	}
#line 3023 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 131: /* feature: identifier TOKEN_COLON TOKEN_STRING  */
#line 1278 "src/rulesyacc.y"
        {
	  DBUGPRT("feature");
	  (yyval.feature_slot) = new featurePtr(Feature::create(Feature::_CONSTANT_, *(yyvsp[-2].bits_slot), Value::create(Value::FORM_VALUE, *(yyvsp[0].string_slot))));
	  free((yyvsp[-2].bits_slot));
	}
#line 3033 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 132: /* feature: variable TOKEN_COLON feature_value  */
#line 1285 "src/rulesyacc.y"
        {
	  DBUGPRT("feature");
	  (yyval.feature_slot) = new featurePtr(Feature::create(Feature::_VARIABLE_, *(yyvsp[-2].bits_slot), *(yyvsp[0].value_slot)));
	  free((yyvsp[-2].bits_slot));
	  free((yyvsp[0].value_slot));
	}
#line 3044 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 133: /* feature_value: variable  */
#line 1295 "src/rulesyacc.y"
        {
	  DBUGPRT("feature_value");
	  (yyval.value_slot) = new valuePtr(Value::create(Value::VARIABLE_VALUE, *(yyvsp[0].bits_slot)));
	  free((yyvsp[0].bits_slot));
	}
#line 3054 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 134: /* feature_value: constant  */
#line 1302 "src/rulesyacc.y"
        {
	  DBUGPRT("feature_value");
	  (yyval.value_slot) = new valuePtr(Value::create(Value::CONSTANT_VALUE, *(yyvsp[0].bits_slot)));
	  free((yyvsp[0].bits_slot));
	}
#line 3064 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 135: /* feature_value: TOKEN_DOUBLE  */
#line 1309 "src/rulesyacc.y"
        {
	  DBUGPRT("expression_statement");
	  (yyval.value_slot) = new valuePtr(Value::create(Value::NUMBER_VALUE, (yyvsp[0].double_slot)));
	}
#line 3073 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 136: /* feature_value: TOKEN_INTEGER  */
#line 1315 "src/rulesyacc.y"
        {
	  DBUGPRT("expression_statement");
	  (yyval.value_slot) = new valuePtr(Value::create(Value::NUMBER_VALUE, (double)(yyvsp[0].integer_slot)));
	}
#line 3082 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 137: /* feature_value: pairp  */
#line 1321 "src/rulesyacc.y"
        {
	  DBUGPRT("feature_value");
	  (yyval.value_slot) = new valuePtr(Value::create(*(yyvsp[0].pairp_slot)));
	  free((yyvsp[0].pairp_slot));
	}
#line 3092 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 138: /* feature_value: features  */
#line 1328 "src/rulesyacc.y"
        {
	  DBUGPRT("feature_value");
	  (yyval.value_slot) = new valuePtr(Value::create(*(yyvsp[0].features_slot)));
	  free((yyvsp[0].features_slot));
	}
#line 3102 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 139: /* feature_value: TOKEN_NIL  */
#line 1335 "src/rulesyacc.y"
        {
	  DBUGPRT("feature_value");
	  (yyval.value_slot) = new valuePtr(Value::STATIC_NIL);
	}
#line 3111 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 140: /* feature_value: TOKEN_ANONYMOUS  */
#line 1341 "src/rulesyacc.y"
        {
	  DBUGPRT("feature_value");
	  (yyval.value_slot) = new valuePtr(Value::STATIC_ANONYMOUS);
	}
#line 3120 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 141: /* constant: identifier  */
#line 1348 "src/rulesyacc.y"
        {
	  DBUGPRT("constants");
	  (yyval.bits_slot)=(yyvsp[0].bits_slot);
	}
#line 3129 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 142: /* constant: identifier TOKEN_PIPE constant  */
#line 1354 "src/rulesyacc.y"
        {
	  DBUGPRT("constants");
	  (yyval.bits_slot)=(yyvsp[-2].bits_slot);
	  (**(yyval.bits_slot)) |= (**(yyvsp[0].bits_slot));
	}
#line 3139 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 143: /* identifier: TOKEN_IDENTIFIER  */
#line 1362 "src/rulesyacc.y"
        {
	  DBUGPRT("identifier");
 	  (yyval.bits_slot) = new bitsetPtr(Bitset::create(Vartable::createVariable(*(yyvsp[0].string_slot))));
 	  free((yyvsp[0].string_slot));
	}
#line 3149 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 144: /* variable: TOKEN_VARIABLE  */
#line 1370 "src/rulesyacc.y"
        {
	  DBUGPRT("variable");
	  std::ostringstream oss;
	  oss << *(yyvsp[0].string_slot);
  	  std::string str = oss.str();
	  (yyval.bits_slot) = new bitsetPtr(Bitset::create(Vartable::createVariable(str)));
	  free((yyvsp[0].string_slot));
	}
#line 3162 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 145: /* pairp: TOKEN_LT pairp_elements TOKEN_GT  */
#line 1381 "src/rulesyacc.y"
        {
	  DBUGPRT("list");
	  (yyval.pairp_slot) = (yyvsp[-1].pairp_slot);
	}
#line 3171 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 146: /* pairp: TOKEN_LT TOKEN_GT  */
#line 1387 "src/rulesyacc.y"
        {
	  DBUGPRT("list");
	  (yyval.pairp_slot) = new pairpPtr(Pairp::NIL);
	}
#line 3180 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 147: /* pairp: TOKEN_LT pairp_elements TOKEN_CONS pairp_element TOKEN_GT  */
#line 1393 "src/rulesyacc.y"
        {
	  DBUGPRT("list");
	  if ((*(yyvsp[-3].pairp_slot))->isPairp() && (*(yyvsp[-3].pairp_slot))->getCdr()->isNil())
	    (yyval.pairp_slot) = new pairpPtr(Pairp::create((*(yyvsp[-3].pairp_slot))->getCar(), *(yyvsp[-1].pairp_slot)));
	  else
	    (yyval.pairp_slot) = new pairpPtr(Pairp::create(*(yyvsp[-3].pairp_slot), *(yyvsp[-1].pairp_slot)));
	  free((yyvsp[-3].pairp_slot));
	  free((yyvsp[-1].pairp_slot));
	}
#line 3194 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 148: /* pairp: TOKEN_LT pairp_elements TOKEN_CONS TOKEN_NIL TOKEN_GT  */
#line 1404 "src/rulesyacc.y"
        {
	  DBUGPRT("list");
	  if ((*(yyvsp[-3].pairp_slot))->isPairp() && (*(yyvsp[-3].pairp_slot))->getCdr()->isNil())
	    (yyval.pairp_slot) = new pairpPtr(Pairp::create((*(yyvsp[-3].pairp_slot))->getCar(), Pairp::NIL));
	  else
	    (yyval.pairp_slot) = new pairpPtr(Pairp::create(*(yyvsp[-3].pairp_slot), Pairp::NIL));
	  free((yyvsp[-3].pairp_slot));
	}
#line 3207 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 149: /* pairp_elements: pairp_element TOKEN_COMMA pairp_elements  */
#line 1417 "src/rulesyacc.y"
        {
	  DBUGPRT("pairp_elements");
	  (yyval.pairp_slot) = new pairpPtr(Pairp::create(*(yyvsp[-2].pairp_slot), *(yyvsp[0].pairp_slot)));
	  free((yyvsp[-2].pairp_slot));
	  free((yyvsp[0].pairp_slot));
	}
#line 3218 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 150: /* pairp_elements: pairp_element  */
#line 1425 "src/rulesyacc.y"
        {
	  DBUGPRT("pairp_elements");
	  (yyval.pairp_slot) = new pairpPtr(Pairp::create(*(yyvsp[0].pairp_slot), Pairp::NIL));
	  free((yyvsp[0].pairp_slot));
	}
#line 3228 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 151: /* pairp_element: variable  */
#line 1433 "src/rulesyacc.y"
        {
	  DBUGPRT("pairp_element");
	  (yyval.pairp_slot) = new pairpPtr(Pairp::create(Value::create(Value::VARIABLE_VALUE, *(yyvsp[0].bits_slot))));
	  free((yyvsp[0].bits_slot));
	}
#line 3238 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 152: /* pairp_element: TOKEN_DOUBLE  */
#line 1440 "src/rulesyacc.y"
        {
	  DBUGPRT("expression_statement");
	  (yyval.pairp_slot) = new pairpPtr(Pairp::create(Value::create(Value::NUMBER_VALUE, (yyvsp[0].double_slot))));
	}
#line 3247 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 153: /* pairp_element: TOKEN_INTEGER  */
#line 1446 "src/rulesyacc.y"
        {
	  DBUGPRT("expression_statement");
	  (yyval.pairp_slot) = new pairpPtr(Pairp::create(Value::create(Value::NUMBER_VALUE, (double)(yyvsp[0].integer_slot))));
	}
#line 3256 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 154: /* pairp_element: constant  */
#line 1452 "src/rulesyacc.y"
        {
	  DBUGPRT("pairp_element");
	  (yyval.pairp_slot) = new pairpPtr(Pairp::create(Value::create(Value::CONSTANT_VALUE, *(yyvsp[0].bits_slot))));
	  free((yyvsp[0].bits_slot));
	}
#line 3266 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 155: /* pairp_element: features  */
#line 1459 "src/rulesyacc.y"
        {
	  DBUGPRT("pairp_element");
	  (yyval.pairp_slot) = new pairpPtr(Pairp::create(Value::create(*(yyvsp[0].features_slot))));
	  free((yyvsp[0].features_slot));
	}
#line 3276 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;

  case 156: /* pairp_element: pairp  */
#line 1466 "src/rulesyacc.y"
        {
	  DBUGPRT("pairp_element");
	  (yyval.pairp_slot)=(yyvsp[0].pairp_slot);
	}
#line 3285 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"
    break;


#line 3289 "/Users/clement/workspace/Elvex/src/rulesyacc.cc"

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

#line 1471 "src/rulesyacc.y"

