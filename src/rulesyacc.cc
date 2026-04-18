/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0

/* Substitute the variable and function names.  */
#define yyparse rulesparse
#define yylex   ruleslex
#define yyerror ruleserror
#define yylval  ruleslval
#define yychar  ruleschar
#define yydebug rulesdebug
#define yynerrs rulesnerrs


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     TOKEN_RIGHTARROW = 258,
     TOKEN_UPARROW = 259,
     TOKEN_UP2ARROW = 260,
     TOKEN_DOWNARROW = 261,
     TOKEN_DOWN2ARROW = 262,
     TOKEN_LPAR = 263,
     TOKEN_RPAR = 264,
     TOKEN_LBRACE = 265,
     TOKEN_RBRACE = 266,
     TOKEN_LBRACKET = 267,
     TOKEN_RBRACKET = 268,
     TOKEN_DASH = 269,
     TOKEN_AROBASE = 270,
     TOKEN_SEMI = 271,
     TOKEN_DOT = 272,
     TOKEN_COLON = 273,
     TOKEN_CONS = 274,
     TOKEN_COMMA = 275,
     TOKEN_MACROS = 276,
     TOKEN_RULES = 277,
     TOKEN_INPUT = 278,
     TOKEN_LEXICON = 279,
     TOKEN_LEMMA = 280,
     TOKEN_HEAD = 281,
     TOKEN_FORM = 282,
     TOKEN_ATTEST = 283,
     TOKEN_PRINT = 284,
     TOKEN_PRINTLN = 285,
     TOKEN_EPRINT = 286,
     TOKEN_EPRINTLN = 287,
     TOKEN_IF = 288,
     TOKEN_ELSE = 289,
     TOKEN_DEFERRED = 290,
     TOKEN_NIL = 291,
     TOKEN_TRUE = 292,
     TOKEN_FALSE = 293,
     TOKEN_FOREACH = 294,
     TOKEN_IN = 295,
     TOKEN_SEARCH = 296,
     TOKEN_ON = 297,
     TOKEN_RAND = 298,
     TOKEN_TRACE = 299,
     TOKEN_WITH_SPACES = 300,
     TOKEN_WITHOUT_SPACES = 301,
     TOKEN_UNORDERED = 302,
     TOKEN_UNIFY = 303,
     TOKEN_SUBSUME = 304,
     TOKEN_ASSIGNMENT = 305,
     TOKEN_PIPE = 306,
     TOKEN_NOT = 307,
     TOKEN_OR = 308,
     TOKEN_AND = 309,
     TOKEN_IMPLICATION = 310,
     TOKEN_EQUIV = 311,
     TOKEN_PLUS = 312,
     TOKEN_MINUS = 313,
     TOKEN_TIMES = 314,
     TOKEN_DIVIDE = 315,
     TOKEN_MODULO = 316,
     TOKEN_EQUAL = 317,
     TOKEN_DIFF = 318,
     TOKEN_LT = 319,
     TOKEN_LE = 320,
     TOKEN_GT = 321,
     TOKEN_GE = 322,
     TOKEN_IDENTIFIER = 323,
     TOKEN_STRING = 324,
     TOKEN_INTEGER = 325,
     TOKEN_DOUBLE = 326,
     TOKEN_VARIABLE = 327,
     TOKEN_ANONYMOUS = 328,
     TOKEN_MINUS_U = 329,
     TOKEN_NOELSE = 330
   };
#endif
/* Tokens.  */
#define TOKEN_RIGHTARROW 258
#define TOKEN_UPARROW 259
#define TOKEN_UP2ARROW 260
#define TOKEN_DOWNARROW 261
#define TOKEN_DOWN2ARROW 262
#define TOKEN_LPAR 263
#define TOKEN_RPAR 264
#define TOKEN_LBRACE 265
#define TOKEN_RBRACE 266
#define TOKEN_LBRACKET 267
#define TOKEN_RBRACKET 268
#define TOKEN_DASH 269
#define TOKEN_AROBASE 270
#define TOKEN_SEMI 271
#define TOKEN_DOT 272
#define TOKEN_COLON 273
#define TOKEN_CONS 274
#define TOKEN_COMMA 275
#define TOKEN_MACROS 276
#define TOKEN_RULES 277
#define TOKEN_INPUT 278
#define TOKEN_LEXICON 279
#define TOKEN_LEMMA 280
#define TOKEN_HEAD 281
#define TOKEN_FORM 282
#define TOKEN_ATTEST 283
#define TOKEN_PRINT 284
#define TOKEN_PRINTLN 285
#define TOKEN_EPRINT 286
#define TOKEN_EPRINTLN 287
#define TOKEN_IF 288
#define TOKEN_ELSE 289
#define TOKEN_DEFERRED 290
#define TOKEN_NIL 291
#define TOKEN_TRUE 292
#define TOKEN_FALSE 293
#define TOKEN_FOREACH 294
#define TOKEN_IN 295
#define TOKEN_SEARCH 296
#define TOKEN_ON 297
#define TOKEN_RAND 298
#define TOKEN_TRACE 299
#define TOKEN_WITH_SPACES 300
#define TOKEN_WITHOUT_SPACES 301
#define TOKEN_UNORDERED 302
#define TOKEN_UNIFY 303
#define TOKEN_SUBSUME 304
#define TOKEN_ASSIGNMENT 305
#define TOKEN_PIPE 306
#define TOKEN_NOT 307
#define TOKEN_OR 308
#define TOKEN_AND 309
#define TOKEN_IMPLICATION 310
#define TOKEN_EQUIV 311
#define TOKEN_PLUS 312
#define TOKEN_MINUS 313
#define TOKEN_TIMES 314
#define TOKEN_DIVIDE 315
#define TOKEN_MODULO 316
#define TOKEN_EQUAL 317
#define TOKEN_DIFF 318
#define TOKEN_LT 319
#define TOKEN_LE 320
#define TOKEN_GT 321
#define TOKEN_GE 322
#define TOKEN_IDENTIFIER 323
#define TOKEN_STRING 324
#define TOKEN_INTEGER 325
#define TOKEN_DOUBLE 326
#define TOKEN_VARIABLE 327
#define TOKEN_ANONYMOUS 328
#define TOKEN_MINUS_U 329
#define TOKEN_NOELSE 330




/* Copy the first part of user declarations.  */
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
 bool pref_trace;
 bool pref_withSpaces;
 bool pref_unordered;

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

  

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 72 "src/rulesyacc.y"
{
  uint32_t integer_slot;
  double double_slot;
  termsPtr* terms_slot; //(A|B)
  std::vector< termsPtr >* vector_terms_slot; // X Y
  std::string* string_slot;
  std::pair<uint32_t, featuresPtr >* entry_slot;
  std::vector<std::pair<uint32_t, featuresPtr> >* entries_slot;
  bitsetPtr* bits_slot;
  valuePtr* value_slot;
  featurePtr* feature_slot;
  featuresPtr* features_slot;
  pairpPtr* pairp_slot;
  statementPtr* statement_slot;
  statementsPtr* statements_slot;

  std::list<  bitsetPtr >* list_args;
 }
/* Line 193 of yacc.c.  */
#line 344 "/Users/clement/Elvex/src/rulesyacc.cc"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 357 "/Users/clement/Elvex/src/rulesyacc.cc"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  13
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   691

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  76
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  47
/* YYNRULES -- Number of rules.  */
#define YYNRULES  162
/* YYNRULES -- Number of states.  */
#define YYNSTATES  289

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   330

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
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
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,    10,    15,    21,    26,    31,    36,
      39,    41,    47,    50,    52,    56,    61,    65,    67,    71,
      73,    76,    78,    79,    83,    84,    86,    89,    92,    95,
      98,    99,   105,   110,   113,   115,   117,   121,   125,   127,
     129,   131,   133,   137,   140,   142,   144,   147,   151,   154,
     156,   159,   163,   167,   171,   175,   179,   184,   189,   195,
     203,   209,   215,   217,   219,   221,   223,   225,   227,   229,
     231,   237,   239,   243,   247,   251,   255,   258,   262,   266,
     270,   274,   278,   282,   286,   290,   294,   298,   302,   305,
     309,   311,   313,   315,   319,   321,   323,   325,   327,   329,
     331,   333,   335,   337,   341,   343,   345,   350,   354,   356,
     358,   360,   363,   366,   371,   374,   379,   382,   383,   386,
     390,   392,   397,   400,   404,   408,   412,   416,   420,   424,
     428,   432,   436,   440,   442,   444,   446,   448,   450,   452,
     454,   456,   459,   461,   465,   467,   469,   471,   473,   475,
     477,   481,   485,   488,   494,   500,   504,   506,   508,   510,
     512,   514,   516
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      77,     0,    -1,    78,    -1,    21,     8,    79,     9,    -1,
      22,     8,    85,     9,    -1,    23,     8,    93,   109,     9,
      -1,    23,     8,    93,     9,    -1,    24,     8,    81,     9,
      -1,    14,     8,   109,     9,    -1,    80,    79,    -1,    80,
      -1,    15,    68,    50,   109,    16,    -1,    82,    81,    -1,
      82,    -1,    27,    68,    16,    -1,    27,    68,   109,    16,
      -1,   118,    83,    16,    -1,    16,    -1,    84,    51,    83,
      -1,    84,    -1,    68,   109,    -1,    68,    -1,    -1,    86,
      89,    85,    -1,    -1,    87,    -1,    88,    44,    -1,    88,
      45,    -1,    88,    46,    -1,    88,    47,    -1,    -1,    88,
      93,     3,    90,    94,    -1,    88,    93,     3,    94,    -1,
      90,    91,    -1,    91,    -1,    92,    -1,     8,    92,     9,
      -1,    92,    51,    93,    -1,    93,    -1,    68,    -1,    72,
      -1,     1,    -1,    10,    95,    11,    -1,    10,    11,    -1,
      16,    -1,    97,    -1,    95,    97,    -1,    10,    95,    11,
      -1,    10,    11,    -1,    96,    -1,   109,    16,    -1,    28,
     102,    16,    -1,    29,   103,    16,    -1,    30,   103,    16,
      -1,    31,   103,    16,    -1,    32,   103,    16,    -1,   100,
      50,   101,    16,    -1,    98,    49,    99,    16,    -1,    33,
       8,   102,     9,    97,    -1,    33,     8,   102,     9,    97,
      34,    97,    -1,    35,     8,   102,     9,    97,    -1,    39,
     116,    40,   102,    97,    -1,   109,    -1,   116,    -1,   104,
      -1,   107,    -1,   109,    -1,   105,    -1,   106,    -1,   116,
      -1,    64,   116,    19,   116,    66,    -1,   102,    -1,   102,
      53,   102,    -1,   102,    54,   102,    -1,   102,    55,   102,
      -1,   102,    56,   102,    -1,    52,   102,    -1,   102,    62,
     102,    -1,   102,    63,   102,    -1,   102,    64,   102,    -1,
     102,    65,   102,    -1,   102,    66,   102,    -1,   102,    67,
     102,    -1,   102,    57,   102,    -1,   102,    58,   102,    -1,
     102,    59,   102,    -1,   102,    60,   102,    -1,   102,    61,
     102,    -1,    58,   102,    -1,    43,     8,     9,    -1,    71,
      -1,    70,    -1,    69,    -1,   102,    48,   102,    -1,   104,
      -1,   105,    -1,   106,    -1,   107,    -1,   109,    -1,    36,
      -1,   114,    -1,    73,    -1,   116,    -1,     8,   102,     9,
      -1,   108,    -1,   120,    -1,    41,   102,    42,    68,    -1,
     103,    20,   102,    -1,   102,    -1,     4,    -1,     5,    -1,
       6,    70,    -1,     7,    70,    -1,    14,    70,    17,    70,
      -1,    14,    70,    -1,    12,   111,   110,    13,    -1,    12,
      13,    -1,    -1,    20,   116,    -1,   111,    20,   112,    -1,
     112,    -1,   111,    20,    15,    68,    -1,    15,    68,    -1,
      25,    18,   117,    -1,    25,    18,   116,    -1,    26,    18,
     117,    -1,    26,    18,   116,    -1,    26,    18,    73,    -1,
      27,    18,   116,    -1,    27,    18,   119,    -1,   115,    18,
     113,    -1,   115,    18,   119,    -1,   116,    18,   113,    -1,
     116,    -1,   114,    -1,    71,    -1,    70,    -1,   120,    -1,
     109,    -1,    36,    -1,    73,    -1,     7,    70,    -1,   115,
      -1,   115,    51,   114,    -1,    68,    -1,    72,    -1,    68,
      -1,    68,    -1,    69,    -1,    69,    -1,   119,    57,    69,
      -1,    64,   121,    66,    -1,    64,    66,    -1,    64,   121,
      19,   122,    66,    -1,    64,   121,    19,    36,    66,    -1,
     122,    20,   121,    -1,   122,    -1,   116,    -1,    71,    -1,
      70,    -1,   114,    -1,   109,    -1,   120,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   167,   167,   173,   177,   181,   188,   194,   200,   208,
     212,   218,   227,   231,   237,   262,   289,   323,   329,   338,
     347,   356,   367,   367,   372,   372,   378,   386,   394,   401,
     407,   416,   434,   448,   454,   461,   466,   473,   480,   487,
     494,   501,   510,   516,   521,   527,   535,   543,   550,   557,
     562,   568,   574,   585,   596,   607,   618,   681,   698,   710,
     723,   735,   747,   754,   759,   764,   769,   777,   782,   787,
     792,   801,   810,   817,   824,   831,   844,   850,   857,   864,
     871,   878,   885,   895,   903,   911,   919,   927,   935,   942,
     948,   954,   960,   969,   976,   981,   986,   991,   996,  1005,
    1011,  1020,  1026,  1031,  1039,  1047,  1056,  1069,  1077,  1087,
    1093,  1099,  1106,  1113,  1119,  1129,  1139,  1147,  1151,  1157,
    1165,  1174,  1189,  1205,  1212,  1219,  1226,  1233,  1240,  1246,
    1252,  1260,  1267,  1276,  1282,  1289,  1295,  1301,  1308,  1315,
    1321,  1327,  1334,  1340,  1348,  1356,  1363,  1369,  1374,  1380,
    1385,  1392,  1398,  1404,  1415,  1428,  1436,  1444,  1450,  1456,
    1462,  1469,  1476
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TOKEN_RIGHTARROW", "TOKEN_UPARROW",
  "TOKEN_UP2ARROW", "TOKEN_DOWNARROW", "TOKEN_DOWN2ARROW", "TOKEN_LPAR",
  "TOKEN_RPAR", "TOKEN_LBRACE", "TOKEN_RBRACE", "TOKEN_LBRACKET",
  "TOKEN_RBRACKET", "TOKEN_DASH", "TOKEN_AROBASE", "TOKEN_SEMI",
  "TOKEN_DOT", "TOKEN_COLON", "TOKEN_CONS", "TOKEN_COMMA", "TOKEN_MACROS",
  "TOKEN_RULES", "TOKEN_INPUT", "TOKEN_LEXICON", "TOKEN_LEMMA",
  "TOKEN_HEAD", "TOKEN_FORM", "TOKEN_ATTEST", "TOKEN_PRINT",
  "TOKEN_PRINTLN", "TOKEN_EPRINT", "TOKEN_EPRINTLN", "TOKEN_IF",
  "TOKEN_ELSE", "TOKEN_DEFERRED", "TOKEN_NIL", "TOKEN_TRUE", "TOKEN_FALSE",
  "TOKEN_FOREACH", "TOKEN_IN", "TOKEN_SEARCH", "TOKEN_ON", "TOKEN_RAND",
  "TOKEN_TRACE", "TOKEN_WITH_SPACES", "TOKEN_WITHOUT_SPACES",
  "TOKEN_UNORDERED", "TOKEN_UNIFY", "TOKEN_SUBSUME", "TOKEN_ASSIGNMENT",
  "TOKEN_PIPE", "TOKEN_NOT", "TOKEN_OR", "TOKEN_AND", "TOKEN_IMPLICATION",
  "TOKEN_EQUIV", "TOKEN_PLUS", "TOKEN_MINUS", "TOKEN_TIMES",
  "TOKEN_DIVIDE", "TOKEN_MODULO", "TOKEN_EQUAL", "TOKEN_DIFF", "TOKEN_LT",
  "TOKEN_LE", "TOKEN_GT", "TOKEN_GE", "TOKEN_IDENTIFIER", "TOKEN_STRING",
  "TOKEN_INTEGER", "TOKEN_DOUBLE", "TOKEN_VARIABLE", "TOKEN_ANONYMOUS",
  "TOKEN_MINUS_U", "TOKEN_NOELSE", "$accept", "axiom", "begin", "macros",
  "macro_line", "dictionary", "dictionary_line", "lexical_entries",
  "lexical_entry", "rules", "@1", "@2", "pref_rule", "rule",
  "terms_vector", "terms", "terms_disj", "term", "structure_statement",
  "list_statement", "statements", "statement",
  "left_hand_side_subset_statement", "right_hand_side_subset_statement",
  "left_hand_side_assignment_statement",
  "right_hand_side_assignment_statement", "expression_statement",
  "expression_statement_composite", "up_statement", "up2_statement",
  "down_statement", "down2_statement", "dash_statement", "features",
  "features_composite_tail", "features_composite", "feature",
  "feature_value", "constants", "constant", "variable", "identifier",
  "identifierOrString", "strings", "pairp", "pairp_elements",
  "pairp_element", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    76,    77,    78,    78,    78,    78,    78,    78,    79,
      79,    80,    81,    81,    82,    82,    82,    82,    83,    83,
      84,    84,    86,    85,    87,    85,    88,    88,    88,    88,
      88,    89,    89,    90,    90,    91,    91,    92,    92,    93,
      93,    93,    94,    94,    94,    95,    95,    96,    96,    97,
      97,    97,    97,    97,    97,    97,    97,    97,    97,    97,
      97,    97,    98,    99,    99,    99,    99,   100,   100,   100,
     100,   101,   102,   102,   102,   102,   102,   102,   102,   102,
     102,   102,   102,   102,   102,   102,   102,   102,   102,   102,
     102,   102,   102,   102,   102,   102,   102,   102,   102,   102,
     102,   102,   102,   102,   102,   102,   102,   103,   103,   104,
     105,   106,   107,   108,   108,   109,   109,   110,   110,   111,
     111,   111,   111,   112,   112,   112,   112,   112,   112,   112,
     112,   112,   112,   113,   113,   113,   113,   113,   113,   113,
     113,   113,   114,   114,   115,   116,   117,   118,   118,   119,
     119,   120,   120,   120,   120,   121,   121,   122,   122,   122,
     122,   122,   122
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     4,     4,     5,     4,     4,     4,     2,
       1,     5,     2,     1,     3,     4,     3,     1,     3,     1,
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
       1,     2,     1,     3,     1,     1,     1,     1,     1,     1,
       3,     3,     2,     5,     5,     3,     1,     1,     1,     1,
       1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     2,     0,     0,
      22,     0,     0,     1,     0,     0,     0,     0,    10,     0,
      30,    25,    41,    39,    40,     0,    17,     0,   147,   148,
       0,    13,     0,   116,     0,     0,     0,     0,   144,   145,
     117,   120,     0,     0,     8,     0,     3,     9,     4,     0,
      22,     6,     0,     0,     7,    12,    21,     0,    19,   122,
       0,     0,     0,     0,     0,     0,     0,     0,    26,    27,
      28,    29,     0,    23,     5,    14,     0,    20,    16,     0,
     146,   124,   123,   127,   126,   125,   149,   128,   129,     0,
     119,   118,   115,     0,   139,     0,   136,   135,   140,   138,
     130,   134,   142,   133,   131,   137,   132,     0,     0,    15,
      18,     0,   121,   141,   152,   159,   158,   161,   160,   157,
     162,     0,   156,     0,    11,     0,     0,    44,     0,    34,
      35,    38,    32,   150,     0,   151,     0,   143,     0,   110,
       0,     0,    43,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    49,    45,     0,     0,    67,    68,    62,
      69,    33,    31,     0,     0,     0,   155,    36,   111,    48,
       0,   109,     0,     0,     0,    99,     0,     0,     0,     0,
      92,    91,    90,   101,     0,    94,    95,    96,    97,   104,
      98,   100,   102,   105,   108,     0,     0,     0,     0,     0,
       0,     0,     0,    42,    46,     0,     0,    50,    37,   154,
     153,    47,   112,     0,   114,     0,     0,    76,    88,    51,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    52,     0,    53,    54,
      55,     0,     0,     0,     0,     0,    64,    65,    66,    63,
       0,    71,   103,     0,     0,    89,    93,    72,    73,    74,
      75,    83,    84,    85,    86,    87,    77,    78,    79,    80,
      81,    82,   107,     0,     0,     0,     0,    57,    56,   113,
     106,    58,    60,     0,    61,    70,     0,   102,    59
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     6,     7,    17,    18,    30,    31,    57,    58,    19,
      20,    21,    49,    50,   128,   129,   130,   131,   132,   152,
     153,   154,   155,   245,   156,   250,   194,   195,   185,   186,
     187,   188,   189,   190,    64,    40,    41,   100,   191,   102,
     192,    82,    32,    88,   193,   121,   122
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -139
static const yytype_int16 yypact[] =
{
     194,    -1,     4,    19,    25,    35,    56,  -139,    57,    48,
      69,     3,   105,  -139,   413,    70,    17,    98,    48,   100,
    -139,  -139,  -139,  -139,  -139,    16,  -139,    18,  -139,  -139,
     118,   105,    61,  -139,    63,    96,   116,   120,  -139,  -139,
     123,  -139,   129,   134,  -139,   110,  -139,  -139,  -139,    36,
      69,  -139,   145,    14,  -139,  -139,    57,   139,   124,  -139,
     -34,    77,    50,    -7,   148,   383,   406,    57,  -139,  -139,
    -139,  -139,   168,  -139,  -139,  -139,   161,  -139,  -139,    61,
    -139,  -139,  -139,  -139,  -139,  -139,  -139,  -139,   121,   114,
    -139,   134,  -139,   125,  -139,   160,  -139,  -139,  -139,  -139,
    -139,  -139,   142,  -139,   121,  -139,  -139,   195,     5,  -139,
    -139,   141,  -139,  -139,  -139,  -139,  -139,  -139,  -139,  -139,
    -139,    10,   192,   146,  -139,     3,   276,  -139,     5,  -139,
     170,  -139,  -139,  -139,   361,  -139,   330,  -139,    13,  -139,
     149,   327,  -139,   184,   184,   184,   184,   184,   214,   215,
     157,   157,   339,  -139,  -139,   185,   187,  -139,  -139,   219,
    -139,  -139,  -139,     3,   173,   175,  -139,  -139,  -139,  -139,
     377,  -139,   177,   184,   179,  -139,   184,   232,   184,   184,
    -139,  -139,  -139,  -139,   507,  -139,  -139,  -139,  -139,  -139,
    -139,  -139,  -139,  -139,   553,    20,    46,    90,   104,   184,
     184,   203,   225,  -139,  -139,    -2,   184,  -139,  -139,  -139,
    -139,  -139,  -139,   434,   228,   533,   241,   613,  -139,  -139,
     184,   184,   184,   184,   184,   184,   184,   184,   184,   184,
     184,   184,   184,   184,   184,   184,  -139,   184,  -139,  -139,
    -139,   454,   474,   184,   157,   235,  -139,  -139,  -139,  -139,
     242,   553,  -139,   189,   193,  -139,   485,   593,   613,   573,
     573,   107,   107,   199,   199,  -139,   624,   624,   624,   624,
     624,   624,   553,   174,   174,   264,   202,  -139,  -139,  -139,
    -139,   237,  -139,   184,  -139,  -139,   174,   225,  -139
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -139,  -139,  -139,   255,  -139,   246,  -139,   200,  -139,   230,
    -139,  -139,  -139,  -139,  -139,   155,   159,   -10,   162,   144,
    -139,  -138,  -139,  -139,  -139,  -139,  -132,    54,    84,  -117,
    -110,    86,  -139,    -8,  -139,  -139,   238,   234,    47,     9,
     -11,   249,  -139,   233,    51,   166,   180
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -25
static const yytype_int16 yytable[] =
{
      15,    25,   171,    43,    22,   172,    22,     8,    89,   157,
      14,   184,     9,   125,   204,   126,   158,    52,    35,    36,
      37,   127,   167,    42,   157,    51,    14,    10,    14,   134,
      75,   158,   204,    11,    80,   157,   236,    22,    39,    72,
     237,   213,   158,    12,   215,    76,   217,   218,    77,    81,
      84,    87,    91,   157,   103,   103,    13,    99,    99,   107,
     158,    38,   238,    16,   163,    39,   237,   241,   242,    14,
      39,    23,    42,    23,   251,    24,   135,    24,   -24,    44,
      68,    69,    70,    71,   119,    45,    53,   117,   256,   257,
     258,   259,   260,   261,   262,   263,   264,   265,   266,   267,
     268,   269,   270,   271,    23,   272,   239,    46,    24,    48,
     237,   275,   101,   101,    60,   160,   105,   105,   159,    86,
     240,    26,    39,   119,   237,   119,   117,    54,   117,    56,
     160,    59,    27,   159,    61,   281,   282,   284,    62,   201,
     202,   160,   118,    63,   159,    80,   120,    65,   288,    39,
      83,   268,    66,   208,    74,    78,   157,   157,   157,   160,
      67,    92,   159,   158,   158,   158,   227,   228,   229,   157,
     137,   108,    14,    28,    29,    79,   158,   109,   111,   139,
     140,   118,   112,   118,   141,   120,    14,   120,   171,   139,
     140,   172,   173,   123,   249,   113,    14,   248,   174,   196,
     197,   198,   143,   144,   145,   146,   147,   148,     1,   149,
     133,   124,   136,   150,    38,     2,     3,     4,     5,   168,
     175,   163,   199,   200,    95,   176,   114,   177,    38,    39,
     115,   116,    39,   276,   205,   207,   178,   206,   151,   209,
     216,   210,   179,   243,   244,   253,    39,   212,    95,   214,
     255,   277,    38,   180,   181,   182,    39,   183,   278,   279,
     229,   280,   160,   160,   160,   159,   159,   159,   285,   139,
     140,   286,   287,    47,   141,   160,    14,    55,   159,   110,
      73,   139,   140,   161,   138,   170,   141,   142,    14,   246,
     162,   247,   143,   144,   145,   146,   147,   148,   104,   149,
     106,    90,   166,   150,   143,   144,   145,   146,   147,   148,
      85,   149,   220,     0,   165,   150,     0,   221,   222,   223,
     224,   225,   226,   227,   228,   229,   230,   231,   283,   233,
     234,   235,   139,   140,     0,     0,    39,   141,   169,    14,
     151,     0,    14,     0,   139,   140,     0,     0,    39,   141,
     203,    14,     0,     0,     0,   143,   144,   145,   146,   147,
     148,     0,   149,     0,     0,     0,   150,   143,   144,   145,
     146,   147,   148,    14,   149,     0,     0,     0,   150,     0,
       0,     0,   139,   140,     0,     0,     0,   141,   211,    14,
      93,   151,     0,     0,    95,    14,     0,   164,    38,    39,
     115,   116,    39,   151,     0,   143,   144,   145,   146,   147,
     148,    39,   149,    93,     0,     0,   150,     0,    14,    94,
       0,     0,     0,     0,     0,    95,    33,     0,    34,    38,
       0,   115,   116,    39,     0,     0,     0,     0,    35,    36,
      37,   151,    94,   252,     0,     0,     0,    95,     0,    39,
       0,    38,    86,    96,    97,    39,    98,     0,     0,     0,
       0,     0,     0,   273,     0,     0,     0,     0,     0,     0,
      95,     0,     0,     0,    38,     0,    96,    97,    39,    98,
       0,    38,   220,   274,     0,    39,     0,   221,   222,   223,
     224,   225,   226,   227,   228,   229,   230,   231,   232,   233,
     234,   235,   220,     0,     0,     0,     0,   221,   222,   223,
     224,   225,   226,   227,   228,   229,   230,   231,   232,   233,
     234,   235,   220,   219,     0,     0,     0,   221,   222,   223,
     224,   225,   226,   227,   228,   229,   230,   231,   232,   233,
     234,   235,   225,   226,   227,   228,   229,   230,   231,   232,
     233,   234,   235,     0,     0,   220,     0,     0,     0,     0,
     221,   222,   223,   224,   225,   226,   227,   228,   229,   230,
     231,   232,   233,   234,   235,   254,     0,     0,     0,     0,
       0,   220,     0,     0,     0,     0,   221,   222,   223,   224,
     225,   226,   227,   228,   229,   230,   231,   232,   233,   234,
     235,   220,     0,     0,     0,     0,   221,   222,   223,   224,
     225,   226,   227,   228,   229,   230,   231,   232,   233,   234,
     235,   220,     0,     0,     0,     0,   221,   222,   -25,   -25,
     225,   226,   227,   228,   229,   230,   231,   232,   233,   234,
     235,   220,     0,     0,     0,     0,     0,   222,     0,     0,
     225,   226,   227,   228,   229,   230,   231,   232,   233,   234,
     235,   220,     0,     0,     0,     0,     0,     0,     0,     0,
     225,   226,   227,   228,   229,   230,   231,   232,   233,   234,
     235,   225,   226,   227,   228,   229,   -25,   -25,   -25,   -25,
     -25,   -25
};

static const yytype_int16 yycheck[] =
{
       8,    11,     4,    14,     1,     7,     1,     8,    15,   126,
      12,   143,     8,     8,   152,    10,   126,    25,    25,    26,
      27,    16,     9,    14,   141,     9,    12,     8,    12,    19,
      16,   141,   170,     8,    68,   152,    16,     1,    72,    49,
      20,   173,   152,     8,   176,    53,   178,   179,    56,    60,
      61,    62,    63,   170,    65,    66,     0,    65,    66,    67,
     170,    68,    16,    15,    51,    72,    20,   199,   200,    12,
      72,    68,    63,    68,   206,    72,    66,    72,     9,     9,
      44,    45,    46,    47,    95,    68,    68,    95,   220,   221,
     222,   223,   224,   225,   226,   227,   228,   229,   230,   231,
     232,   233,   234,   235,    68,   237,    16,     9,    72,     9,
      20,   243,    65,    66,    18,   126,    65,    66,   126,    69,
      16,    16,    72,   134,    20,   136,   134,     9,   136,    68,
     141,    68,    27,   141,    18,   273,   274,   275,    18,   150,
     151,   152,    95,    20,   152,    68,    95,    18,   286,    72,
      73,   283,    18,   163,     9,    16,   273,   274,   275,   170,
      50,    13,   170,   273,   274,   275,    59,    60,    61,   286,
     123,     3,    12,    68,    69,    51,   286,    16,    57,     5,
       6,   134,    68,   136,    10,   134,    12,   136,     4,     5,
       6,     7,     8,    51,   205,    70,    12,   205,    14,   145,
     146,   147,    28,    29,    30,    31,    32,    33,    14,    35,
      69,    16,    20,    39,    68,    21,    22,    23,    24,    70,
      36,    51,     8,     8,    64,    41,    66,    43,    68,    72,
      70,    71,    72,   244,    49,    16,    52,    50,    64,    66,
       8,    66,    58,    40,    19,    17,    72,    70,    64,    70,
       9,    16,    68,    69,    70,    71,    72,    73,    16,    70,
      61,    68,   273,   274,   275,   273,   274,   275,    66,     5,
       6,    34,   283,    18,    10,   286,    12,    31,   286,    79,
      50,     5,     6,   128,   125,   141,    10,    11,    12,   205,
     128,   205,    28,    29,    30,    31,    32,    33,    65,    35,
      66,    63,   136,    39,    28,    29,    30,    31,    32,    33,
      61,    35,    48,    -1,   134,    39,    -1,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,     5,     6,    -1,    -1,    72,    10,    11,    12,
      64,    -1,    12,    -1,     5,     6,    -1,    -1,    72,    10,
      11,    12,    -1,    -1,    -1,    28,    29,    30,    31,    32,
      33,    -1,    35,    -1,    -1,    -1,    39,    28,    29,    30,
      31,    32,    33,    12,    35,    -1,    -1,    -1,    39,    -1,
      -1,    -1,     5,     6,    -1,    -1,    -1,    10,    11,    12,
       7,    64,    -1,    -1,    64,    12,    -1,    36,    68,    72,
      70,    71,    72,    64,    -1,    28,    29,    30,    31,    32,
      33,    72,    35,     7,    -1,    -1,    39,    -1,    12,    36,
      -1,    -1,    -1,    -1,    -1,    64,    13,    -1,    15,    68,
      -1,    70,    71,    72,    -1,    -1,    -1,    -1,    25,    26,
      27,    64,    36,     9,    -1,    -1,    -1,    64,    -1,    72,
      -1,    68,    69,    70,    71,    72,    73,    -1,    -1,    -1,
      -1,    -1,    -1,     9,    -1,    -1,    -1,    -1,    -1,    -1,
      64,    -1,    -1,    -1,    68,    -1,    70,    71,    72,    73,
      -1,    68,    48,     9,    -1,    72,    -1,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    48,    -1,    -1,    -1,    -1,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    48,    16,    -1,    -1,    -1,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    -1,    -1,    48,    -1,    -1,    -1,    -1,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    42,    -1,    -1,    -1,    -1,
      -1,    48,    -1,    -1,    -1,    -1,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    48,    -1,    -1,    -1,    -1,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    48,    -1,    -1,    -1,    -1,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    48,    -1,    -1,    -1,    -1,    -1,    54,    -1,    -1,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    48,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    14,    21,    22,    23,    24,    77,    78,     8,     8,
       8,     8,     8,     0,    12,   109,    15,    79,    80,    85,
      86,    87,     1,    68,    72,    93,    16,    27,    68,    69,
      81,    82,   118,    13,    15,    25,    26,    27,    68,    72,
     111,   112,   115,   116,     9,    68,     9,    79,     9,    88,
      89,     9,   109,    68,     9,    81,    68,    83,    84,    68,
      18,    18,    18,    20,   110,    18,    18,    50,    44,    45,
      46,    47,    93,    85,     9,    16,   109,   109,    16,    51,
      68,   116,   117,    73,   116,   117,    69,   116,   119,    15,
     112,   116,    13,     7,    36,    64,    70,    71,    73,   109,
     113,   114,   115,   116,   119,   120,   113,   109,     3,    16,
      83,    57,    68,    70,    66,    70,    71,   109,   114,   116,
     120,   121,   122,    51,    16,     8,    10,    16,    90,    91,
      92,    93,    94,    69,    19,    66,    20,   114,    92,     5,
       6,    10,    11,    28,    29,    30,    31,    32,    33,    35,
      39,    64,    95,    96,    97,    98,   100,   105,   106,   109,
     116,    91,    94,    51,    36,   122,   121,     9,    70,    11,
      95,     4,     7,     8,    14,    36,    41,    43,    52,    58,
      69,    70,    71,    73,   102,   104,   105,   106,   107,   108,
     109,   114,   116,   120,   102,   103,   103,   103,   103,     8,
       8,   116,   116,    11,    97,    49,    50,    16,    93,    66,
      66,    11,    70,   102,    70,   102,     8,   102,   102,    16,
      48,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    16,    20,    16,    16,
      16,   102,   102,    40,    19,    99,   104,   107,   109,   116,
     101,   102,     9,    17,    42,     9,   102,   102,   102,   102,
     102,   102,   102,   102,   102,   102,   102,   102,   102,   102,
     102,   102,   102,     9,     9,   102,   116,    16,    16,    70,
      68,    97,    97,    64,    97,    66,    34,   116,    97
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
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



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
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
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

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
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 167 "src/rulesyacc.y"
    {
	  DBUGPRT("axiom done...");
	  YYACCEPT;
	;}
    break;

  case 3:
#line 173 "src/rulesyacc.y"
    {
	  DBUGPRT("begin grammar");
	;}
    break;

  case 4:
#line 177 "src/rulesyacc.y"
    {
	  DBUGPRT("begin grammar");
	;}
    break;

  case 5:
#line 181 "src/rulesyacc.y"
    {
	  DBUGPRT("begin input");
	  parser.setStartTerm((yyvsp[(3) - (5)].integer_slot));
	  parser.setStartFeatures(*(yyvsp[(4) - (5)].features_slot));
	  free((yyvsp[(4) - (5)].features_slot));
	;}
    break;

  case 6:
#line 188 "src/rulesyacc.y"
    {
	  DBUGPRT("begin input");
	  parser.setStartTerm((yyvsp[(3) - (4)].integer_slot));
	  parser.setStartFeatures(Features::create());
	 ;}
    break;

  case 7:
#line 194 "src/rulesyacc.y"
    {
	  DBUGPRT("begin lexicon");
	  //COUT_LINE;
	  //parser.printCacheLexicon(std::cout);
	;}
    break;

  case 8:
#line 201 "src/rulesyacc.y"
    {
	  DBUGPRT("begin features");
	  parser.setLocalFeatures(*(yyvsp[(3) - (4)].features_slot));
	  free((yyvsp[(3) - (4)].features_slot));
	;}
    break;

  case 9:
#line 208 "src/rulesyacc.y"
    {
	  DBUGPRT("macros");
	;}
    break;

  case 10:
#line 212 "src/rulesyacc.y"
    {
	  DBUGPRT("macros");
	 ;}
    break;

  case 11:
#line 219 "src/rulesyacc.y"
    {
	  DBUGPRT("dictionary_line");
	  parser.addMacros(*(yyvsp[(2) - (5)].string_slot), *(yyvsp[(4) - (5)].features_slot));
	  free((yyvsp[(2) - (5)].string_slot));
	  free((yyvsp[(4) - (5)].features_slot));
	;}
    break;

  case 12:
#line 227 "src/rulesyacc.y"
    {
	  DBUGPRT("dictionary");
	;}
    break;

  case 13:
#line 231 "src/rulesyacc.y"
    {
	  DBUGPRT("dictionary");
	 ;}
    break;

  case 14:
#line 238 "src/rulesyacc.y"
    {
	  DBUGPRT("dictionary_line");
	  uint32_t code = Vartable::nameToCode(*(yyvsp[(2) - (3)].string_slot));
	  free((yyvsp[(2) - (3)].string_slot));
	  // constantNoun => (0 => args)
	  auto foundCode = parser.findCacheLexicon(code);
	  Parser::entries_map* formToEntries;
	  if (foundCode != parser.cendCacheLexicon()){
	    formToEntries = foundCode->second;
	  } else {
	    formToEntries = new Parser::entries_map();
	    parser.insertCacheLexicon(std::make_pair(code, formToEntries));
	  }
	  auto foundHead = formToEntries->find(Vartable::code_for_IS_A_FORM);
	  entriesPtr entries;
	  if (foundHead != formToEntries->cend()){
	    entries = foundHead->second;
	  } else {
	    entries = Entries::create();
	    formToEntries->insert(std::make_pair(Vartable::code_for_IS_A_FORM, entries));
	  }
	  entries->add(Entry::create(Features::create()));
	;}
    break;

  case 15:
#line 263 "src/rulesyacc.y"
    {
	  DBUGPRT("dictionary_line");
	  uint32_t code = Vartable::nameToCode(*(yyvsp[(2) - (4)].string_slot));
	  free((yyvsp[(2) - (4)].string_slot));
	  // constantNoun => (0 => args)
	  auto foundCode = parser.findCacheLexicon(code);
	  Parser::entries_map* formToEntries;
	  if (foundCode != parser.cendCacheLexicon()) {
	    formToEntries = foundCode->second;
	  } else {
	    formToEntries = new Parser::entries_map;
	    parser.insertCacheLexicon(std::make_pair(code, formToEntries));
	  }
	  auto foundHead = formToEntries->find(Vartable::code_for_IS_A_FORM);
	  entriesPtr entries;
	  if (foundHead != formToEntries->cend()){
	    entries = foundHead->second;
	  } else {
	    entries = Entries::create();
	    formToEntries->insert(std::make_pair(Vartable::code_for_IS_A_FORM, entries));
	  }
	  entries->add(Entry::create(/*code, */*(yyvsp[(3) - (4)].features_slot)));
	  free((yyvsp[(3) - (4)].features_slot));
	;}
    break;

  case 16:
#line 290 "src/rulesyacc.y"
    {
	  DBUGPRT("dictionary_line");
	  for (auto entries_map = (*(yyvsp[(2) - (3)].entries_slot)).cbegin() ; entries_map != (*(yyvsp[(2) - (3)].entries_slot)).cend() ; ++entries_map) {
		uint32_t pos = entries_map->first;
		featuresPtr features = entries_map->second;
		uint32_t head = features->assignHead();
		
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
	      parser.insertCacheLexicon(std::make_pair(pos, headToEntries));
	    }
	    Parser::entries_map::iterator foundHead = headToEntries->find(head);
	    if (foundHead != headToEntries->cend()){
	      entries = foundHead->second;
	    } else {
	      entries = Entries::create();
	      headToEntries->insert(std::make_pair(head, entries));
	    }
	    entries->add(Entry::create(*(yyvsp[(1) - (3)].string_slot), features));
	  }
	  free((yyvsp[(2) - (3)].entries_slot));
	;}
    break;

  case 17:
#line 324 "src/rulesyacc.y"
    {
	  DBUGPRT("dictionary_line");
	;}
    break;

  case 18:
#line 330 "src/rulesyacc.y"
    {
	  DBUGPRT("lexical_entries");
	  (yyval.entries_slot) = (yyvsp[(3) - (3)].entries_slot);
	  (yyval.entries_slot)->push_back(*(yyvsp[(1) - (3)].entry_slot));
	  free((yyvsp[(1) - (3)].entry_slot));
	;}
    break;

  case 19:
#line 338 "src/rulesyacc.y"
    {
	  DBUGPRT("lexical_entries");
	  (yyval.entries_slot) = new std::vector<std::pair<uint32_t, featuresPtr> >;
	  (yyval.entries_slot)->push_back(*(yyvsp[(1) - (1)].entry_slot));
	  free((yyvsp[(1) - (1)].entry_slot));
	 ;}
    break;

  case 20:
#line 348 "src/rulesyacc.y"
    {
	  DBUGPRT("lexical_entry");
	  (yyval.entry_slot) = new std::pair<uint32_t, featuresPtr>(std::make_pair(Vartable::nameToCode(*(yyvsp[(1) - (2)].string_slot)), *(yyvsp[(2) - (2)].features_slot)));
	  free((yyvsp[(1) - (2)].string_slot));
	  free((yyvsp[(2) - (2)].features_slot));
	;}
    break;

  case 21:
#line 357 "src/rulesyacc.y"
    {
	  DBUGPRT("lexical_entry");
	  (yyval.entry_slot) = new std::pair<uint32_t, featuresPtr>(std::make_pair(Vartable::nameToCode(*(yyvsp[(1) - (1)].string_slot)), Features::create()));
	  free((yyvsp[(1) - (1)].string_slot));
	;}
    break;

  case 22:
#line 367 "src/rulesyacc.y"
    {headLineno = ruleslineno;;}
    break;

  case 23:
#line 368 "src/rulesyacc.y"
    {
	  DBUGPRT("rules");
	;}
    break;

  case 24:
#line 372 "src/rulesyacc.y"
    {headLineno = ruleslineno;;}
    break;

  case 25:
#line 373 "src/rulesyacc.y"
    {
	  DBUGPRT("rules");
	;}
    break;

  case 26:
#line 379 "src/rulesyacc.y"
    {
	  DBUGPRT("pref_rule");
	  if (pref_trace)
		yyerror((char*)"@trace already done");
	  pref_trace = true;
	;}
    break;

  case 27:
#line 387 "src/rulesyacc.y"
    {
	  DBUGPRT("pref_rule");
	  if (pref_withSpaces)
		yyerror((char*)"@withSpaces already done");
	  pref_withSpaces = true;
	;}
    break;

  case 28:
#line 395 "src/rulesyacc.y"
    {
	  DBUGPRT("pref_rule");
	  if (pref_withSpaces)
		pref_withSpaces = false;
	;}
    break;

  case 29:
#line 402 "src/rulesyacc.y"
    {
	  DBUGPRT("pref_rule");
	  pref_unordered = true;
	;}
    break;

  case 30:
#line 407 "src/rulesyacc.y"
    {
	  DBUGPRT("pref_rule");
	  // initialization
	  pref_trace = false;
	  pref_withSpaces = true;
	  pref_unordered = false;
	;}
    break;

  case 31:
#line 417 "src/rulesyacc.y"
    {
	  DBUGPRT("rule");
	  if (pref_unordered && (yyvsp[(4) - (5)].vector_terms_slot)->size() <= 1){
		yyerror((char*)"This rule with fewer than 2 terms must not be unordered");

	  }
	  rulePtr rule = Rule::create(headLineno, parser.getTopBufferName(), pref_withSpaces, pref_unordered, (yyvsp[(2) - (5)].integer_slot), *(yyvsp[(4) - (5)].vector_terms_slot), (yyvsp[(5) - (5)].statements_slot) ? *(yyvsp[(5) - (5)].statements_slot) : statementsPtr());
	  rule->setTrace(pref_trace);
	  parser.getRules().addRule(rule);
	  if (!parser.getRules().getStartTerm()){
	    parser.getRules().setStartTerm((yyvsp[(2) - (5)].integer_slot));
	  }
	  free((yyvsp[(4) - (5)].vector_terms_slot));
	  if ((yyvsp[(5) - (5)].statements_slot))
	     free((yyvsp[(5) - (5)].statements_slot));
	;}
    break;

  case 32:
#line 435 "src/rulesyacc.y"
    {
	  DBUGPRT("Rule");
	  rulePtr rule = Rule::create(headLineno, parser.getTopBufferName(), pref_withSpaces, pref_unordered, (yyvsp[(2) - (4)].integer_slot), (yyvsp[(4) - (4)].statements_slot) ? *(yyvsp[(4) - (4)].statements_slot) : statementsPtr());
	  rule->setTrace(pref_trace);
	  parser.getRules().addRule(rule);
	  if (!parser.getRules().getStartTerm()){
	    parser.getRules().setStartTerm((yyvsp[(2) - (4)].integer_slot));
	  }
	  if ((yyvsp[(4) - (4)].statements_slot))
	    free((yyvsp[(4) - (4)].statements_slot));
	;}
    break;

  case 33:
#line 448 "src/rulesyacc.y"
    {
	  DBUGPRT("term_vector");
	  (yyval.vector_terms_slot)=(yyvsp[(1) - (2)].vector_terms_slot);
	  (yyval.vector_terms_slot)->push_back(*(yyvsp[(2) - (2)].terms_slot));
	;}
    break;

  case 34:
#line 454 "src/rulesyacc.y"
    {
	  DBUGPRT("term_vector");
	  (yyval.vector_terms_slot) = new std::vector< termsPtr >;
	  (yyval.vector_terms_slot)->push_back(*(yyvsp[(1) - (1)].terms_slot));
	;}
    break;

  case 35:
#line 461 "src/rulesyacc.y"
    {
	  DBUGPRT("term");
	  (yyval.terms_slot)=(yyvsp[(1) - (1)].terms_slot);
	;}
    break;

  case 36:
#line 466 "src/rulesyacc.y"
    {
	  DBUGPRT("term");
	  (yyval.terms_slot) = (yyvsp[(2) - (3)].terms_slot);
	  (*(yyval.terms_slot))->setOptional();
	;}
    break;

  case 37:
#line 474 "src/rulesyacc.y"
    {
	  DBUGPRT("term_disj");
	  (yyval.terms_slot) = (yyvsp[(1) - (3)].terms_slot);
	  (*(yyval.terms_slot))->push_back((yyvsp[(3) - (3)].integer_slot));
	;}
    break;

  case 38:
#line 481 "src/rulesyacc.y"
    {
	  DBUGPRT("term_disj");
	  (yyval.terms_slot) = new termsPtr(Terms::create((yyvsp[(1) - (1)].integer_slot)));
	;}
    break;

  case 39:
#line 488 "src/rulesyacc.y"
    {
	  DBUGPRT("term_id");
	  (yyval.integer_slot) = Vartable::nameToCode(*(yyvsp[(1) - (1)].string_slot));
	  free((yyvsp[(1) - (1)].string_slot));
	;}
    break;

  case 40:
#line 495 "src/rulesyacc.y"
    {
	  DBUGPRT("term_id");
	  (yyval.integer_slot) = Vartable::nameToCode(*(yyvsp[(1) - (1)].string_slot));
	  free((yyvsp[(1) - (1)].string_slot));
	;}
    break;

  case 41:
#line 502 "src/rulesyacc.y"
    {
	  YYABORT;
	;}
    break;

  case 42:
#line 511 "src/rulesyacc.y"
    {
	  DBUGPRT("structure_statement");
	  (yyval.statements_slot)=(yyvsp[(2) - (3)].statements_slot);
	;}
    break;

  case 43:
#line 517 "src/rulesyacc.y"
    {
	  (yyval.statements_slot)=NULL;
	;}
    break;

  case 44:
#line 522 "src/rulesyacc.y"
    {
	  (yyval.statements_slot)=NULL;
	;}
    break;

  case 45:
#line 528 "src/rulesyacc.y"
    {
	  DBUGPRT("list_statement");
	  (yyval.statements_slot) = new statementsPtr(Statements::create());
	  (*(yyval.statements_slot))->addStatement(*(yyvsp[(1) - (1)].statement_slot));
	  free((yyvsp[(1) - (1)].statement_slot));
	;}
    break;

  case 46:
#line 535 "src/rulesyacc.y"
    {
	  DBUGPRT("list_statement");
	  (yyval.statements_slot) = (yyvsp[(1) - (2)].statements_slot);
	  (*(yyval.statements_slot))->addStatement(*(yyvsp[(2) - (2)].statement_slot));
	  free((yyvsp[(2) - (2)].statement_slot));
	;}
    break;

  case 47:
#line 544 "src/rulesyacc.y"
    {
	  DBUGPRT("statement");
	  (yyval.statement_slot) = new statementPtr(Statement::createStatements(ruleslineno, parser.getTopBufferName(), Statement::STMS_STATEMENT, false, *(yyvsp[(2) - (3)].statements_slot)));
	  free((yyvsp[(2) - (3)].statements_slot));
	;}
    break;

  case 48:
#line 551 "src/rulesyacc.y"
    {
	  DBUGPRT("statement");
	  (yyval.statement_slot) = new statementPtr(Statement::createStatements(ruleslineno, parser.getTopBufferName(), Statement::STMS_STATEMENT, false, Statements::create()));
	;}
    break;

  case 49:
#line 557 "src/rulesyacc.y"
    {
	  DBUGPRT("statement");
	  (yyval.statement_slot)=(yyvsp[(1) - (1)].statement_slot);
	 ;}
    break;

  case 50:
#line 562 "src/rulesyacc.y"
    {
	  DBUGPRT("statement");
	  (yyval.statement_slot) = new statementPtr(Statement::createFeatures(ruleslineno, parser.getTopBufferName(), Statement::GUARD_STATEMENT, true, *(yyvsp[(1) - (2)].features_slot)));
	  free((yyvsp[(1) - (2)].features_slot));
	;}
    break;

  case 51:
#line 568 "src/rulesyacc.y"
    {
	  DBUGPRT("statement");
	  (yyval.statement_slot) = new statementPtr(Statement::createFirst(ruleslineno, parser.getTopBufferName(), Statement::ATTEST_STATEMENT, true, *(yyvsp[(2) - (3)].statement_slot)));
	  free((yyvsp[(2) - (3)].statement_slot));
	;}
    break;

  case 52:
#line 574 "src/rulesyacc.y"
    {
	  DBUGPRT("statement");
		(yyval.statement_slot) = new statementPtr(Statement::createStatements(
			ruleslineno, 
			parser.getTopBufferName(), 
			Statement::PRINT_STATEMENT, 
			true, 
			*(yyvsp[(2) - (3)].statements_slot)));
	  free((yyvsp[(2) - (3)].statements_slot));
	;}
    break;

  case 53:
#line 585 "src/rulesyacc.y"
    {
	  	DBUGPRT("statement");
		(yyval.statement_slot) = new statementPtr(Statement::createStatements(
			ruleslineno, 
			parser.getTopBufferName(), 
			Statement::PRINTLN_STATEMENT, 
			true, 
			*(yyvsp[(2) - (3)].statements_slot)));
	  free((yyvsp[(2) - (3)].statements_slot));
	;}
    break;

  case 54:
#line 596 "src/rulesyacc.y"
    {
	  DBUGPRT("statement");
		(yyval.statement_slot) = new statementPtr(Statement::createStatements(
			ruleslineno, 
			parser.getTopBufferName(), 
			Statement::EPRINT_STATEMENT, 
			true, 
			*(yyvsp[(2) - (3)].statements_slot)));
	  free((yyvsp[(2) - (3)].statements_slot));
	;}
    break;

  case 55:
#line 607 "src/rulesyacc.y"
    {
	  	DBUGPRT("statement");
		(yyval.statement_slot) = new statementPtr(Statement::createStatements(
			ruleslineno, 
			parser.getTopBufferName(), 
			Statement::EPRINTLN_STATEMENT, 
			true, 
			*(yyvsp[(2) - (3)].statements_slot)));
	  free((yyvsp[(2) - (3)].statements_slot));
	;}
    break;

  case 56:
#line 618 "src/rulesyacc.y"
    {
	  DBUGPRT("statement");
	  (yyval.statement_slot) = new statementPtr(Statement::createFirstSecond(ruleslineno, parser.getTopBufferName(), Statement::ASSIGNMENT_STATEMENT, true, *(yyvsp[(1) - (4)].statement_slot), *(yyvsp[(3) - (4)].statement_slot)));
	  // <X, …> = <…>
	  // <X, …> = $X
	  // <X, …> = search 
	  if (((*(yyvsp[(1) - (4)].statement_slot))->isPairp()) 
	  		&& (((*(yyvsp[(3) - (4)].statement_slot))->isPairp())
				||((*(yyvsp[(3) - (4)].statement_slot))->isVariable()) 
				||((*(yyvsp[(3) - (4)].statement_slot))->isSearch()))) {
	    }
	  // ↓i = $X
	  // ↓i = […]
	  // ↓i = ↑
	  // ↓i = … ∪ …
	  // ↓i = ⇓j
	  else if (((*(yyvsp[(1) - (4)].statement_slot))->isDown()) 
	  		&& (((*(yyvsp[(3) - (4)].statement_slot))->isVariable())
					||((*(yyvsp[(3) - (4)].statement_slot))->isFeatures())
					||((*(yyvsp[(3) - (4)].statement_slot))->isUp())
					||((*(yyvsp[(3) - (4)].statement_slot))->isUnif())
					||((*(yyvsp[(3) - (4)].statement_slot))->isDown2())))
	    ;
	  // ⇑ = $X
	  // ⇑ = […]
	  // ⇑ = ↑
	  // ⇑ = … ∪ …
	  // ⇑ = ⇓j
	  else if (((*(yyvsp[(1) - (4)].statement_slot))->isUp2()) 
	  		&& (((*(yyvsp[(3) - (4)].statement_slot))->isVariable())
					||((*(yyvsp[(3) - (4)].statement_slot))->isFeatures())
					||((*(yyvsp[(3) - (4)].statement_slot))->isUp())
					||((*(yyvsp[(3) - (4)].statement_slot))->isUnif())
					||((*(yyvsp[(3) - (4)].statement_slot))->isDown2())))
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
	  else if (((*(yyvsp[(1) - (4)].statement_slot))->isVariable())
		   &&(((*(yyvsp[(3) - (4)].statement_slot))->isVariable())
		      ||((*(yyvsp[(3) - (4)].statement_slot))->isConstant())
		      ||((*(yyvsp[(3) - (4)].statement_slot))->isPairp())
		      ||((*(yyvsp[(3) - (4)].statement_slot))->isFeatures())
		      ||((*(yyvsp[(3) - (4)].statement_slot))->isUp())
		      ||((*(yyvsp[(3) - (4)].statement_slot))->isUnif())
		      ||((*(yyvsp[(3) - (4)].statement_slot))->isDown2())
		      ||((*(yyvsp[(3) - (4)].statement_slot))->isString())
		      ||((*(yyvsp[(3) - (4)].statement_slot))->isNumber())
		      ||((*(yyvsp[(3) - (4)].statement_slot))->isFct())
		      ||((*(yyvsp[(3) - (4)].statement_slot))->isSearch())));
	  else {
	    yyerror((char*)"bad assignment expression");
	  }
	  free((yyvsp[(1) - (4)].statement_slot));
	  free((yyvsp[(3) - (4)].statement_slot));
	;}
    break;

  case 57:
#line 681 "src/rulesyacc.y"
    {
	  DBUGPRT("statement");
	  (yyval.statement_slot) = new statementPtr(Statement::createFirstSecond(ruleslineno, parser.getTopBufferName(), Statement::SUBSUME_STATEMENT, true, (*(yyvsp[(1) - (4)].statement_slot)), (*(yyvsp[(3) - (4)].statement_slot))));
	  // […] ⊂ ↑
	  // […] ⊂ ⇓j
	  // […] ⊂ $X
	  if (((*(yyvsp[(1) - (4)].statement_slot))->isFeatures()) 
	  		&& (((*(yyvsp[(3) - (4)].statement_slot))->isUp())
					||((*(yyvsp[(3) - (4)].statement_slot))->isDown2())
					||((*(yyvsp[(3) - (4)].statement_slot))->isVariable())))
	    ;
	  else
	    yyerror((char* )"bad subsumption expression");
	  free((yyvsp[(1) - (4)].statement_slot));
	  free((yyvsp[(3) - (4)].statement_slot));
	;}
    break;

  case 58:
#line 698 "src/rulesyacc.y"
    {
	  DBUGPRT("statement");
	  (yyval.statement_slot) = new statementPtr(Statement::createFirstSecond(ruleslineno,
						parser.getTopBufferName(), 
						Statement::IF_STATEMENT,
						  true, 
						  *(yyvsp[(3) - (5)].statement_slot),
						  Statement::createFirst(ruleslineno, parser.getTopBufferName(), Statement::THEN_STATEMENT, false, *(yyvsp[(5) - (5)].statement_slot))));
	  free((yyvsp[(3) - (5)].statement_slot));
	  free((yyvsp[(5) - (5)].statement_slot));
	;}
    break;

  case 59:
#line 710 "src/rulesyacc.y"
    {
	  DBUGPRT("statement");
	  (yyval.statement_slot) = new statementPtr(Statement::createFirstSecond(ruleslineno,
						  parser.getTopBufferName(),
						  Statement::IF_STATEMENT,
						  true, 
						  (*(yyvsp[(3) - (7)].statement_slot)),
						  Statement::createFirstSecond(ruleslineno, parser.getTopBufferName(), Statement::THEN_ELSE_STATEMENT, false, *(yyvsp[(5) - (7)].statement_slot), *(yyvsp[(7) - (7)].statement_slot))));
	  free((yyvsp[(3) - (7)].statement_slot));
	  free((yyvsp[(5) - (7)].statement_slot));
	  free((yyvsp[(7) - (7)].statement_slot));
	;}
    break;

  case 60:
#line 723 "src/rulesyacc.y"
    {
	  DBUGPRT("statement");
	  (yyval.statement_slot) = new statementPtr(Statement::createFirstSecond(ruleslineno,
						parser.getTopBufferName(), 
						Statement::DEFERRED_STATEMENT,
						true, 
						*(yyvsp[(3) - (5)].statement_slot),
						*(yyvsp[(5) - (5)].statement_slot)));
	  free((yyvsp[(3) - (5)].statement_slot));
	  free((yyvsp[(5) - (5)].statement_slot));
	;}
    break;

  case 61:
#line 735 "src/rulesyacc.y"
    {
	  DBUGPRT("statement");
	  (yyval.statement_slot) = new statementPtr(Statement::createForeach(ruleslineno,
						  parser.getTopBufferName(),
						  true, 
						  (yyvsp[(2) - (5)].integer_slot),
						  Statement::createFirstSecond(ruleslineno, parser.getTopBufferName(), Statement::FOREACH_CON_T_STATEMENT, false, (*(yyvsp[(4) - (5)].statement_slot)), *(yyvsp[(5) - (5)].statement_slot))));
	  free((yyvsp[(4) - (5)].statement_slot));
	  free((yyvsp[(5) - (5)].statement_slot));
	;}
    break;

  case 62:
#line 747 "src/rulesyacc.y"
    {
	  DBUGPRT("left_hand_side_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::createFeatures(ruleslineno, parser.getTopBufferName(), Statement::FEATURES_STATEMENT, false, *(yyvsp[(1) - (1)].features_slot)));
	  free((yyvsp[(1) - (1)].features_slot));
	;}
    break;

  case 63:
#line 754 "src/rulesyacc.y"
    {
	  DBUGPRT("right_hand_side_subset_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::createVariable(ruleslineno, parser.getTopBufferName(), false, (yyvsp[(1) - (1)].integer_slot)));
	;}
    break;

  case 64:
#line 759 "src/rulesyacc.y"
    {
	  DBUGPRT("right_hand_side_subset_statement");
	  (yyval.statement_slot)=(yyvsp[(1) - (1)].statement_slot);
	;}
    break;

  case 65:
#line 764 "src/rulesyacc.y"
    {
	  DBUGPRT("right_hand_side_subset_statement");
	  (yyval.statement_slot)=(yyvsp[(1) - (1)].statement_slot);
	;}
    break;

  case 66:
#line 769 "src/rulesyacc.y"
    {
	  DBUGPRT("right_hand_side_subset_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::createFeatures(ruleslineno, parser.getTopBufferName(), Statement::FEATURES_STATEMENT, false, *(yyvsp[(1) - (1)].features_slot)));
	  free((yyvsp[(1) - (1)].features_slot));
	;}
    break;

  case 67:
#line 777 "src/rulesyacc.y"
    {
	  DBUGPRT("left_hand_side_statement");
	  (yyval.statement_slot)=(yyvsp[(1) - (1)].statement_slot);
	;}
    break;

  case 68:
#line 782 "src/rulesyacc.y"
    {
	  DBUGPRT("left_hand_side_statement");
	  (yyval.statement_slot)=(yyvsp[(1) - (1)].statement_slot);
	;}
    break;

  case 69:
#line 787 "src/rulesyacc.y"
    {
	  DBUGPRT("left_hand_side_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::createVariable(ruleslineno, parser.getTopBufferName(), false, (yyvsp[(1) - (1)].integer_slot)));
	 ;}
    break;

  case 70:
#line 793 "src/rulesyacc.y"
    {
	  DBUGPRT("left_hand_side_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::createPairp(ruleslineno, parser.getTopBufferName(), false, 
						Pairp::create(Pairp::create(Value::createVariable((yyvsp[(2) - (5)].integer_slot))),
							     Pairp::create(Value::createVariable((yyvsp[(4) - (5)].integer_slot))))));
	;}
    break;

  case 71:
#line 801 "src/rulesyacc.y"
    {
	  DBUGPRT("right_hand_side_statement");
	  (yyval.statement_slot)=(yyvsp[(1) - (1)].statement_slot);
	;}
    break;

  case 72:
#line 810 "src/rulesyacc.y"
    {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::createFunction(ruleslineno, parser.getTopBufferName(), false, Statement::OR, (*(yyvsp[(1) - (3)].statement_slot)), (*(yyvsp[(3) - (3)].statement_slot))));
	  free((yyvsp[(1) - (3)].statement_slot));
	  free((yyvsp[(3) - (3)].statement_slot));
	;}
    break;

  case 73:
#line 817 "src/rulesyacc.y"
    {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::createFunction(ruleslineno, parser.getTopBufferName(), false, Statement::AND, (*(yyvsp[(1) - (3)].statement_slot)), (*(yyvsp[(3) - (3)].statement_slot))));
	  free((yyvsp[(1) - (3)].statement_slot));
	  free((yyvsp[(3) - (3)].statement_slot));
	;}
    break;

  case 74:
#line 824 "src/rulesyacc.y"
    {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::createFunction(ruleslineno, parser.getTopBufferName(), false, Statement::OR, Statement::createFunction(ruleslineno, parser.getTopBufferName(), false, Statement::NOT, (*(yyvsp[(1) - (3)].statement_slot))), (*(yyvsp[(3) - (3)].statement_slot))));
	  free((yyvsp[(1) - (3)].statement_slot));
	  free((yyvsp[(3) - (3)].statement_slot));
	;}
    break;

  case 75:
#line 831 "src/rulesyacc.y"
    {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::createFunction(ruleslineno, parser.getTopBufferName(), false, Statement::AND,
						                    Statement::createFunction(ruleslineno, parser.getTopBufferName(), false, Statement::OR,
								                Statement::createFunction(ruleslineno, parser.getTopBufferName(), false, Statement::NOT, (*(yyvsp[(1) - (3)].statement_slot))),
								                (*(yyvsp[(3) - (3)].statement_slot))),
						                    Statement::createFunction(ruleslineno, parser.getTopBufferName(), false, Statement::OR,
								                (*(yyvsp[(1) - (3)].statement_slot)),
								                Statement::createFunction(ruleslineno, parser.getTopBufferName(), false, Statement::NOT, (*(yyvsp[(3) - (3)].statement_slot))))));
	  free((yyvsp[(1) - (3)].statement_slot));
	  free((yyvsp[(3) - (3)].statement_slot));
	;}
    break;

  case 76:
#line 844 "src/rulesyacc.y"
    {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::createFunction(ruleslineno, parser.getTopBufferName(), false, Statement::NOT, (*(yyvsp[(2) - (2)].statement_slot))));
	  free((yyvsp[(2) - (2)].statement_slot));
	;}
    break;

  case 77:
#line 850 "src/rulesyacc.y"
    {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::createFunction(ruleslineno, parser.getTopBufferName(), false, Statement::EQUAL, (*(yyvsp[(1) - (3)].statement_slot)), (*(yyvsp[(3) - (3)].statement_slot))));
	  free((yyvsp[(1) - (3)].statement_slot));
	  free((yyvsp[(3) - (3)].statement_slot));
	;}
    break;

  case 78:
#line 857 "src/rulesyacc.y"
    {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::createFunction(ruleslineno, parser.getTopBufferName(), false, Statement::DIFF, (*(yyvsp[(1) - (3)].statement_slot)), (*(yyvsp[(3) - (3)].statement_slot))));
	  free((yyvsp[(1) - (3)].statement_slot));
	  free((yyvsp[(3) - (3)].statement_slot));
	;}
    break;

  case 79:
#line 864 "src/rulesyacc.y"
    {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::createFunction(ruleslineno, parser.getTopBufferName(), false, Statement::LT, (*(yyvsp[(1) - (3)].statement_slot)), (*(yyvsp[(3) - (3)].statement_slot))));
	  free((yyvsp[(1) - (3)].statement_slot));
	  free((yyvsp[(3) - (3)].statement_slot));
	;}
    break;

  case 80:
#line 871 "src/rulesyacc.y"
    {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::createFunction(ruleslineno, parser.getTopBufferName(), false, Statement::LE, (*(yyvsp[(1) - (3)].statement_slot)), (*(yyvsp[(3) - (3)].statement_slot))));
	  free((yyvsp[(1) - (3)].statement_slot));
	  free((yyvsp[(3) - (3)].statement_slot));
	;}
    break;

  case 81:
#line 878 "src/rulesyacc.y"
    {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::createFunction(ruleslineno, parser.getTopBufferName(), false, Statement::GT, (*(yyvsp[(1) - (3)].statement_slot)), (*(yyvsp[(3) - (3)].statement_slot))));
	  free((yyvsp[(1) - (3)].statement_slot));
	  free((yyvsp[(3) - (3)].statement_slot));
	;}
    break;

  case 82:
#line 885 "src/rulesyacc.y"
    {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::createFunction(ruleslineno, parser.getTopBufferName(), false, Statement::GE, (*(yyvsp[(1) - (3)].statement_slot)), (*(yyvsp[(3) - (3)].statement_slot))));
	  free((yyvsp[(1) - (3)].statement_slot));
	  free((yyvsp[(3) - (3)].statement_slot));
	;}
    break;

  case 83:
#line 896 "src/rulesyacc.y"
    {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::createFunction(ruleslineno, parser.getTopBufferName(), false, Statement::PLUS, (*(yyvsp[(1) - (3)].statement_slot)), (*(yyvsp[(3) - (3)].statement_slot))));
	  free((yyvsp[(1) - (3)].statement_slot));
	  free((yyvsp[(3) - (3)].statement_slot));
	;}
    break;

  case 84:
#line 904 "src/rulesyacc.y"
    {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::createFunction(ruleslineno, parser.getTopBufferName(), false, Statement::MINUS, (*(yyvsp[(1) - (3)].statement_slot)), (*(yyvsp[(3) - (3)].statement_slot))));
	  free((yyvsp[(1) - (3)].statement_slot));
	  free((yyvsp[(3) - (3)].statement_slot));
	;}
    break;

  case 85:
#line 912 "src/rulesyacc.y"
    {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::createFunction(ruleslineno, parser.getTopBufferName(), false, Statement::TIMES, (*(yyvsp[(1) - (3)].statement_slot)), (*(yyvsp[(3) - (3)].statement_slot))));
	  free((yyvsp[(1) - (3)].statement_slot));
	  free((yyvsp[(3) - (3)].statement_slot));
	;}
    break;

  case 86:
#line 920 "src/rulesyacc.y"
    {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::createFunction(ruleslineno, parser.getTopBufferName(), false, Statement::DIVIDE, (*(yyvsp[(1) - (3)].statement_slot)), (*(yyvsp[(3) - (3)].statement_slot))));
	  free((yyvsp[(1) - (3)].statement_slot));
	  free((yyvsp[(3) - (3)].statement_slot));
	;}
    break;

  case 87:
#line 928 "src/rulesyacc.y"
    {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::createFunction(ruleslineno, parser.getTopBufferName(), false, Statement::MODULO, (*(yyvsp[(1) - (3)].statement_slot)), (*(yyvsp[(3) - (3)].statement_slot))));
	  free((yyvsp[(1) - (3)].statement_slot));
	  free((yyvsp[(3) - (3)].statement_slot));
	;}
    break;

  case 88:
#line 936 "src/rulesyacc.y"
    {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::createFunction(ruleslineno, parser.getTopBufferName(), false, Statement::MINUS_U, (*(yyvsp[(2) - (2)].statement_slot)), statementPtr()));
	  free((yyvsp[(2) - (2)].statement_slot));
	;}
    break;

  case 89:
#line 943 "src/rulesyacc.y"
    {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::createFunction(ruleslineno, parser.getTopBufferName(), false, Statement::RANDOM));
	;}
    break;

  case 90:
#line 949 "src/rulesyacc.y"
    {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::createNumber(ruleslineno, parser.getTopBufferName(), false, (yyvsp[(1) - (1)].double_slot)));
	;}
    break;

  case 91:
#line 955 "src/rulesyacc.y"
    {
	  DBUGPRT("expression_statement");
 	  (yyval.statement_slot) = new statementPtr(Statement::createNumber(ruleslineno, parser.getTopBufferName(), false, (double)(yyvsp[(1) - (1)].integer_slot)));
	;}
    break;

  case 92:
#line 961 "src/rulesyacc.y"
    {
	  DBUGPRT("expression_statement");
 	  (yyval.statement_slot) = new statementPtr(Statement::createString(ruleslineno, parser.getTopBufferName(), false, *(yyvsp[(1) - (1)].string_slot)));
	;}
    break;

  case 93:
#line 969 "src/rulesyacc.y"
    {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::createFirstSecond(ruleslineno, parser.getTopBufferName(), Statement::UNIF_STATEMENT, false, (*(yyvsp[(1) - (3)].statement_slot)), (*(yyvsp[(3) - (3)].statement_slot))));
	  free((yyvsp[(1) - (3)].statement_slot));
	  free((yyvsp[(3) - (3)].statement_slot));
	;}
    break;

  case 94:
#line 976 "src/rulesyacc.y"
    {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot)=(yyvsp[(1) - (1)].statement_slot);
	;}
    break;

  case 95:
#line 981 "src/rulesyacc.y"
    {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot)=(yyvsp[(1) - (1)].statement_slot);
	;}
    break;

  case 96:
#line 986 "src/rulesyacc.y"
    {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot)=(yyvsp[(1) - (1)].statement_slot);
	;}
    break;

  case 97:
#line 991 "src/rulesyacc.y"
    {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot)=(yyvsp[(1) - (1)].statement_slot);
	;}
    break;

  case 98:
#line 996 "src/rulesyacc.y"
    {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::createFeatures(ruleslineno, parser.getTopBufferName(), Statement::FEATURES_STATEMENT, false, *(yyvsp[(1) - (1)].features_slot)));
	  free((yyvsp[(1) - (1)].features_slot));
	;}
    break;

  case 99:
#line 1006 "src/rulesyacc.y"
    {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::createEmpty(ruleslineno, parser.getTopBufferName(), Statement::NIL_STATEMENT, false));
	;}
    break;

  case 100:
#line 1011 "src/rulesyacc.y"
    {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::createConstant(ruleslineno, parser.getTopBufferName(), false, *(yyvsp[(1) - (1)].bits_slot)));
	  free((yyvsp[(1) - (1)].bits_slot));
	;}
    break;

  case 101:
#line 1021 "src/rulesyacc.y"
    {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::createAnonymous(ruleslineno, parser.getTopBufferName(), false));
	;}
    break;

  case 102:
#line 1026 "src/rulesyacc.y"
    {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::createVariable(ruleslineno, parser.getTopBufferName(), false, (yyvsp[(1) - (1)].integer_slot)));
	;}
    break;

  case 103:
#line 1031 "src/rulesyacc.y"
    {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot)=(yyvsp[(2) - (3)].statement_slot);
	;}
    break;

  case 104:
#line 1039 "src/rulesyacc.y"
    {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot)=(yyvsp[(1) - (1)].statement_slot);
	;}
    break;

  case 105:
#line 1047 "src/rulesyacc.y"
    {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::createPairp(ruleslineno, parser.getTopBufferName(), false, *(yyvsp[(1) - (1)].pairp_slot)));
	  free((yyvsp[(1) - (1)].pairp_slot));
	;}
    break;

  case 106:
#line 1056 "src/rulesyacc.y"
    {
	  	DBUGPRT("expression_statement");
	  	(yyval.statement_slot) = new statementPtr(Statement::createSearch(ruleslineno,
						  parser.getTopBufferName(),
						  true,
						  Vartable ::nameToCode(*(yyvsp[(4) - (4)].string_slot)),
						  *(yyvsp[(2) - (4)].statement_slot)));
		free((yyvsp[(2) - (4)].statement_slot));
	  	free((yyvsp[(4) - (4)].string_slot));
	 ;}
    break;

  case 107:
#line 1070 "src/rulesyacc.y"
    {
	  DBUGPRT("expression_statement_composite");
	  (yyval.statements_slot) = (yyvsp[(1) - (3)].statements_slot);
	  (*(yyval.statements_slot))->addStatement(*(yyvsp[(3) - (3)].statement_slot));
	  free((yyvsp[(3) - (3)].statement_slot));
	;}
    break;

  case 108:
#line 1078 "src/rulesyacc.y"
    {
	  DBUGPRT("expression_statement_composite");
	  (yyval.statements_slot) = new statementsPtr(Statements::create());
	  (*(yyval.statements_slot))->addStatement(*(yyvsp[(1) - (1)].statement_slot));
	  free((yyvsp[(1) - (1)].statement_slot));
	;}
    break;

  case 109:
#line 1087 "src/rulesyacc.y"
    {
	  DBUGPRT("up");
	  (yyval.statement_slot) = new statementPtr(Statement::createEmpty(ruleslineno, parser.getTopBufferName(), Statement::INHERITED_FEATURES_STATEMENT, false));
	;}
    break;

  case 110:
#line 1093 "src/rulesyacc.y"
    {
	  DBUGPRT("up2_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::createEmpty(ruleslineno, parser.getTopBufferName(), Statement::SYNTHESIZED_FEATURES_STATEMENT, false));
	;}
    break;

  case 111:
#line 1100 "src/rulesyacc.y"
    {
	  DBUGPRT("down_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::INHERITED_CHILDREN_FEATURES_STATEMENT, false, static_cast<uint8_t>((yyvsp[(2) - (2)].integer_slot)-1)));
	;}
    break;

  case 112:
#line 1107 "src/rulesyacc.y"
    {
	  DBUGPRT("down2");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::SYNTHESIZED_CHILDREN_FEATURES_STATEMENT, false, static_cast<uint8_t>((yyvsp[(2) - (2)].integer_slot)-1)));
	;}
    break;

  case 113:
#line 1114 "src/rulesyacc.y"
    {
	  DBUGPRT("dash_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::DASH_STATEMENT, false, static_cast<uint8_t>((yyvsp[(2) - (4)].integer_slot)-1), static_cast<uint8_t>((yyvsp[(4) - (4)].integer_slot)-1)));
	;}
    break;

  case 114:
#line 1120 "src/rulesyacc.y"
    {
	  DBUGPRT("dash_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::DASH_STATEMENT, false, static_cast<uint8_t>((yyvsp[(2) - (2)].integer_slot)-1), UINT8_MAX));
	;}
    break;

  case 115:
#line 1130 "src/rulesyacc.y"
    {
	  DBUGPRT("features");
 	  (yyval.features_slot) = (yyvsp[(2) - (4)].features_slot);
	  if ((yyvsp[(3) - (4)].feature_slot)) {
	    (*(yyval.features_slot))->add(*(yyvsp[(3) - (4)].feature_slot));
	    free((yyvsp[(3) - (4)].feature_slot));
	  }
	;}
    break;

  case 116:
#line 1140 "src/rulesyacc.y"
    {
	  DBUGPRT("features");
	  (yyval.features_slot) = new featuresPtr(Features::create());
	;}
    break;

  case 117:
#line 1147 "src/rulesyacc.y"
    {
	    (yyval.feature_slot) = NULL;
	;}
    break;

  case 118:
#line 1152 "src/rulesyacc.y"
    {
        (yyval.feature_slot) = new featurePtr(Feature::createVariable((yyvsp[(2) - (2)].integer_slot), valuePtr()));
    ;}
    break;

  case 119:
#line 1158 "src/rulesyacc.y"
    {
	  DBUGPRT("feature_components");
	  (yyval.features_slot) = (yyvsp[(1) - (3)].features_slot);
	  (*(yyval.features_slot))->add(*(yyvsp[(3) - (3)].feature_slot));
	  free((yyvsp[(3) - (3)].feature_slot));
	;}
    break;

  case 120:
#line 1166 "src/rulesyacc.y"
    {
	  DBUGPRT("features_composite");
	  (yyval.features_slot) = new featuresPtr(Features::create());
	  (*(yyval.features_slot))->add(*(yyvsp[(1) - (1)].feature_slot));
	  free((yyvsp[(1) - (1)].feature_slot));
	;}
    break;

  case 121:
#line 1175 "src/rulesyacc.y"
    {
	  DBUGPRT("features_composite");
	  featuresPtr found = parser.findMacros(*(yyvsp[(4) - (4)].string_slot));
	  (yyval.features_slot) = (yyvsp[(1) - (4)].features_slot);
	  if (!(found)){
	     std::ostringstream oss; oss << "unknown macro: @" << *(yyvsp[(4) - (4)].string_slot);
	     yyerror((char*)oss.str().c_str());
	  } else {
	    (*(yyval.features_slot))->add(found->clone());
	  }
	  free((yyvsp[(4) - (4)].string_slot));
	;}
    break;

  case 122:
#line 1190 "src/rulesyacc.y"
    {
	  DBUGPRT("features_composite");
	  featuresPtr found = parser.findMacros(*(yyvsp[(2) - (2)].string_slot));
	  (yyval.features_slot) = new featuresPtr(Features::create());
	  if (!(found)){
	    std::ostringstream oss; oss << "***unknown macro: @" << *(yyvsp[(2) - (2)].string_slot);
	    yyerror((char*)oss.str().c_str());
	  } else {
	    (*(yyval.features_slot))->add(found->clone());
	  }
	  free((yyvsp[(2) - (2)].string_slot));
	  ;}
    break;

  case 123:
#line 1206 "src/rulesyacc.y"
    {
	  DBUGPRT("feature");
	  (yyval.feature_slot) = new featurePtr(Feature::createLemma(Value::createIdentifier(*(yyvsp[(3) - (3)].string_slot))));
	;}
    break;

  case 124:
#line 1213 "src/rulesyacc.y"
    {
	  DBUGPRT("feature");
	  (yyval.feature_slot) = new featurePtr(Feature::createLemma(Value::createVariable((yyvsp[(3) - (3)].integer_slot))));
	;}
    break;

  case 125:
#line 1220 "src/rulesyacc.y"
    {
	  DBUGPRT("feature");
	  (yyval.feature_slot) = new featurePtr(Feature::createHead(Value::createIdentifier(*(yyvsp[(3) - (3)].string_slot))));
	;}
    break;

  case 126:
#line 1227 "src/rulesyacc.y"
    {
	  DBUGPRT("feature");
	  (yyval.feature_slot) = new featurePtr(Feature::createHead(Value::createVariable((yyvsp[(3) - (3)].integer_slot))));
	;}
    break;

  case 127:
#line 1234 "src/rulesyacc.y"
    {
	  DBUGPRT("feature");
	  (yyval.feature_slot) = new featurePtr(Feature::createHead(Value::createEmpty(Value::ANONYMOUS_VALUE)));
	;}
    break;

  case 128:
#line 1241 "src/rulesyacc.y"
    {
	  DBUGPRT("feature");
	  (yyval.feature_slot) = new featurePtr(Feature::createForm(Value::createVariable((yyvsp[(3) - (3)].integer_slot))));
	;}
    break;

  case 129:
#line 1247 "src/rulesyacc.y"
    {
	  DBUGPRT("feature");
	  (yyval.feature_slot) = new featurePtr(Feature::createForm(Value::createForm(*(yyvsp[(3) - (3)].string_slot))));
	;}
    break;

  case 130:
#line 1253 "src/rulesyacc.y"
    {
	  DBUGPRT("feature");
	  (yyval.feature_slot) = new featurePtr(Feature::createConstant(*(yyvsp[(1) - (3)].bits_slot), *(yyvsp[(3) - (3)].value_slot)));
	  free((yyvsp[(1) - (3)].bits_slot));
	  free((yyvsp[(3) - (3)].value_slot));
	;}
    break;

  case 131:
#line 1261 "src/rulesyacc.y"
    {
	  DBUGPRT("feature");
	  (yyval.feature_slot) = new featurePtr(Feature::createConstant(*(yyvsp[(1) - (3)].bits_slot), Value::createForm(*(yyvsp[(3) - (3)].string_slot))));
	  free((yyvsp[(1) - (3)].bits_slot));
	;}
    break;

  case 132:
#line 1268 "src/rulesyacc.y"
    {
	  DBUGPRT("feature");
	  (yyval.feature_slot) = new featurePtr(Feature::createVariable((yyvsp[(1) - (3)].integer_slot), *(yyvsp[(3) - (3)].value_slot)));
	  free((yyvsp[(3) - (3)].value_slot));
	;}
    break;

  case 133:
#line 1277 "src/rulesyacc.y"
    {
	  DBUGPRT("feature_value");
	  (yyval.value_slot) = new valuePtr(Value::createVariable((yyvsp[(1) - (1)].integer_slot)));
	;}
    break;

  case 134:
#line 1283 "src/rulesyacc.y"
    {
	  DBUGPRT("feature_value");
	  (yyval.value_slot) = new valuePtr(Value::createConstant(*(yyvsp[(1) - (1)].bits_slot)));
	  free((yyvsp[(1) - (1)].bits_slot));
	;}
    break;

  case 135:
#line 1290 "src/rulesyacc.y"
    {
	  DBUGPRT("expression_statement");
	  (yyval.value_slot) = new valuePtr(Value::createNumber((yyvsp[(1) - (1)].double_slot)));
	;}
    break;

  case 136:
#line 1296 "src/rulesyacc.y"
    {
	  DBUGPRT("expression_statement");
	  (yyval.value_slot) = new valuePtr(Value::createNumber((double)(yyvsp[(1) - (1)].integer_slot)));
	;}
    break;

  case 137:
#line 1302 "src/rulesyacc.y"
    {
	  DBUGPRT("feature_value");
	  (yyval.value_slot) = new valuePtr(Value::createPairp(*(yyvsp[(1) - (1)].pairp_slot)));
	  free((yyvsp[(1) - (1)].pairp_slot));
	;}
    break;

  case 138:
#line 1309 "src/rulesyacc.y"
    {
	  DBUGPRT("feature_value");
	  (yyval.value_slot) = new valuePtr(Value::createFeatures(*(yyvsp[(1) - (1)].features_slot)));
	  free((yyvsp[(1) - (1)].features_slot));
	;}
    break;

  case 139:
#line 1316 "src/rulesyacc.y"
    {
	  DBUGPRT("feature_value");
	  (yyval.value_slot) = new valuePtr(Value::STATIC_NIL);
	;}
    break;

  case 140:
#line 1322 "src/rulesyacc.y"
    {
	  DBUGPRT("feature_value");
	  (yyval.value_slot) = new valuePtr(Value::STATIC_ANONYMOUS);
	;}
    break;

  case 141:
#line 1327 "src/rulesyacc.y"
    {
	  DBUGPRT("down2_value");
	  (yyval.value_slot) = new valuePtr(Value::createDown2(static_cast<uint8_t>((yyvsp[(2) - (2)].integer_slot)-1)));
	;}
    break;

  case 142:
#line 1335 "src/rulesyacc.y"
    {
	  DBUGPRT("constants");
	  (yyval.bits_slot)=(yyvsp[(1) - (1)].bits_slot);
	;}
    break;

  case 143:
#line 1341 "src/rulesyacc.y"
    {
	  DBUGPRT("constants");
	  (yyval.bits_slot)=(yyvsp[(1) - (3)].bits_slot);
	  (**(yyval.bits_slot)) |= (**(yyvsp[(3) - (3)].bits_slot));
	;}
    break;

  case 144:
#line 1349 "src/rulesyacc.y"
    {
	  DBUGPRT("constant");
 	  (yyval.bits_slot) = new bitsetPtr(Bitset::create(Vartable::createSymbol(*(yyvsp[(1) - (1)].string_slot))));
 	  free((yyvsp[(1) - (1)].string_slot));
	;}
    break;

  case 145:
#line 1357 "src/rulesyacc.y"
    {
	  DBUGPRT("variable");
	  (yyval.integer_slot) = Vartable::nameToCode(*(yyvsp[(1) - (1)].string_slot));
	;}
    break;

  case 146:
#line 1363 "src/rulesyacc.y"
    {
	  DBUGPRT("identifier");
	  (yyval.string_slot) = (yyvsp[(1) - (1)].string_slot);
	;}
    break;

  case 147:
#line 1369 "src/rulesyacc.y"
    {
	  DBUGPRT("identifierOrString");
	  (yyval.string_slot) = (yyvsp[(1) - (1)].string_slot);
	;}
    break;

  case 148:
#line 1374 "src/rulesyacc.y"
    {
		DBUGPRT("identifierOrString");
	  	(yyval.string_slot) = (yyvsp[(1) - (1)].string_slot);
	;}
    break;

  case 149:
#line 1380 "src/rulesyacc.y"
    {
		DBUGPRT("identifierOrString");
	  	(yyval.string_slot) = (yyvsp[(1) - (1)].string_slot);
	;}
    break;

  case 150:
#line 1385 "src/rulesyacc.y"
    {
	  DBUGPRT("string");
	  (yyval.string_slot) = (yyvsp[(1) - (3)].string_slot);
	  *(yyval.string_slot) += *(yyvsp[(3) - (3)].string_slot);
	 ;}
    break;

  case 151:
#line 1393 "src/rulesyacc.y"
    {
	  DBUGPRT("list");
	  (yyval.pairp_slot) = (yyvsp[(2) - (3)].pairp_slot);
	;}
    break;

  case 152:
#line 1399 "src/rulesyacc.y"
    {
	  DBUGPRT("list");
	  (yyval.pairp_slot) = new pairpPtr(Pairp::NIL);
	;}
    break;

  case 153:
#line 1405 "src/rulesyacc.y"
    {
	  DBUGPRT("list");
	  if ((*(yyvsp[(2) - (5)].pairp_slot))->isPairp() && (*(yyvsp[(2) - (5)].pairp_slot))->getCdr()->isNil())
	    (yyval.pairp_slot) = new pairpPtr(Pairp::create((*(yyvsp[(2) - (5)].pairp_slot))->getCar(), *(yyvsp[(4) - (5)].pairp_slot)));
	  else
	    (yyval.pairp_slot) = new pairpPtr(Pairp::create(*(yyvsp[(2) - (5)].pairp_slot), *(yyvsp[(4) - (5)].pairp_slot)));
	  free((yyvsp[(2) - (5)].pairp_slot));
	  free((yyvsp[(4) - (5)].pairp_slot));
	;}
    break;

  case 154:
#line 1416 "src/rulesyacc.y"
    {
	  DBUGPRT("list");
	  if ((*(yyvsp[(2) - (5)].pairp_slot))->isPairp() && (*(yyvsp[(2) - (5)].pairp_slot))->getCdr()->isNil())
	    (yyval.pairp_slot) = new pairpPtr(Pairp::create((*(yyvsp[(2) - (5)].pairp_slot))->getCar(), Pairp::NIL));
	  else
	    (yyval.pairp_slot) = new pairpPtr(Pairp::create(*(yyvsp[(2) - (5)].pairp_slot), Pairp::NIL));
	  free((yyvsp[(2) - (5)].pairp_slot));
	;}
    break;

  case 155:
#line 1429 "src/rulesyacc.y"
    {
	  DBUGPRT("pairp_elements");
	  (yyval.pairp_slot) = new pairpPtr(Pairp::create(*(yyvsp[(1) - (3)].pairp_slot), *(yyvsp[(3) - (3)].pairp_slot)));
	  free((yyvsp[(1) - (3)].pairp_slot));
	  free((yyvsp[(3) - (3)].pairp_slot));
	;}
    break;

  case 156:
#line 1437 "src/rulesyacc.y"
    {
	  DBUGPRT("pairp_elements");
	  (yyval.pairp_slot) = new pairpPtr(Pairp::create(*(yyvsp[(1) - (1)].pairp_slot), Pairp::NIL));
	  free((yyvsp[(1) - (1)].pairp_slot));
	;}
    break;

  case 157:
#line 1445 "src/rulesyacc.y"
    {
	  DBUGPRT("pairp_element");
	  (yyval.pairp_slot) = new pairpPtr(Pairp::create(Value::createVariable((yyvsp[(1) - (1)].integer_slot))));
	;}
    break;

  case 158:
#line 1451 "src/rulesyacc.y"
    {
	  DBUGPRT("expression_statement");
	  (yyval.pairp_slot) = new pairpPtr(Pairp::create(Value::createNumber((yyvsp[(1) - (1)].double_slot))));
	;}
    break;

  case 159:
#line 1457 "src/rulesyacc.y"
    {
	  DBUGPRT("expression_statement");
	  (yyval.pairp_slot) = new pairpPtr(Pairp::create(Value::createNumber((double)(yyvsp[(1) - (1)].integer_slot))));
	;}
    break;

  case 160:
#line 1463 "src/rulesyacc.y"
    {
	  DBUGPRT("pairp_element");
	  (yyval.pairp_slot) = new pairpPtr(Pairp::create(Value::createConstant(*(yyvsp[(1) - (1)].bits_slot))));
	  free((yyvsp[(1) - (1)].bits_slot));
	;}
    break;

  case 161:
#line 1470 "src/rulesyacc.y"
    {
	  DBUGPRT("pairp_element");
	  (yyval.pairp_slot) = new pairpPtr(Pairp::create(Value::createFeatures(*(yyvsp[(1) - (1)].features_slot))));
	  free((yyvsp[(1) - (1)].features_slot));
	;}
    break;

  case 162:
#line 1477 "src/rulesyacc.y"
    {
	  DBUGPRT("pairp_element");
	  (yyval.pairp_slot)=(yyvsp[(1) - (1)].pairp_slot);
	;}
    break;


/* Line 1267 of yacc.c.  */
#line 3541 "/Users/clement/Elvex/src/rulesyacc.cc"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
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

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

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

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 1482 "src/rulesyacc.y"


