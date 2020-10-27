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
     TOKEN_DOUBLECOLON = 274,
     TOKEN_COMMA = 275,
     TOKEN_GRAMMAR = 276,
     TOKEN_INPUT = 277,
     TOKEN_LEXICON = 278,
     TOKEN_PRED = 279,
     TOKEN_FORM = 280,
     TOKEN_ATTEST = 281,
     TOKEN_PRINT = 282,
     TOKEN_PRINTLN = 283,
     TOKEN_IF = 284,
     TOKEN_ELSE = 285,
     TOKEN_NIL = 286,
     TOKEN_TRUE = 287,
     TOKEN_FALSE = 288,
     TOKEN_FOREACH = 289,
     TOKEN_IN = 290,
     TOKEN_SEARCH = 291,
     TOKEN_RAND = 292,
     TOKEN_TRACE = 293,
     TOKEN_UNION = 294,
     TOKEN_SUBSUME = 295,
     TOKEN_INSET = 296,
     TOKEN_AFF = 297,
     TOKEN_PIPE = 298,
     TOKEN_NOT = 299,
     TOKEN_OR = 300,
     TOKEN_AND = 301,
     TOKEN_IMPLICATION = 302,
     TOKEN_EQUIV = 303,
     TOKEN_PLUS = 304,
     TOKEN_MINUS = 305,
     TOKEN_TIMES = 306,
     TOKEN_DIVIDE = 307,
     TOKEN_MODULO = 308,
     TOKEN_EQUAL = 309,
     TOKEN_DIFF = 310,
     TOKEN_LT = 311,
     TOKEN_LE = 312,
     TOKEN_GT = 313,
     TOKEN_GE = 314,
     TOKEN_IDENTIFIER = 315,
     TOKEN_STRING = 316,
     TOKEN_INTEGER = 317,
     TOKEN_DOUBLE = 318,
     TOKEN_VARIABLE = 319,
     TOKEN_ANONYMOUS = 320,
     TOKEN_MINUS_U = 321,
     TOKEN_NOELSE = 322
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
#define TOKEN_DOUBLECOLON 274
#define TOKEN_COMMA 275
#define TOKEN_GRAMMAR 276
#define TOKEN_INPUT 277
#define TOKEN_LEXICON 278
#define TOKEN_PRED 279
#define TOKEN_FORM 280
#define TOKEN_ATTEST 281
#define TOKEN_PRINT 282
#define TOKEN_PRINTLN 283
#define TOKEN_IF 284
#define TOKEN_ELSE 285
#define TOKEN_NIL 286
#define TOKEN_TRUE 287
#define TOKEN_FALSE 288
#define TOKEN_FOREACH 289
#define TOKEN_IN 290
#define TOKEN_SEARCH 291
#define TOKEN_RAND 292
#define TOKEN_TRACE 293
#define TOKEN_UNION 294
#define TOKEN_SUBSUME 295
#define TOKEN_INSET 296
#define TOKEN_AFF 297
#define TOKEN_PIPE 298
#define TOKEN_NOT 299
#define TOKEN_OR 300
#define TOKEN_AND 301
#define TOKEN_IMPLICATION 302
#define TOKEN_EQUIV 303
#define TOKEN_PLUS 304
#define TOKEN_MINUS 305
#define TOKEN_TIMES 306
#define TOKEN_DIVIDE 307
#define TOKEN_MODULO 308
#define TOKEN_EQUAL 309
#define TOKEN_DIFF 310
#define TOKEN_LT 311
#define TOKEN_LE 312
#define TOKEN_GT 313
#define TOKEN_GE 314
#define TOKEN_IDENTIFIER 315
#define TOKEN_STRING 316
#define TOKEN_INTEGER 317
#define TOKEN_DOUBLE 318
#define TOKEN_VARIABLE 319
#define TOKEN_ANONYMOUS 320
#define TOKEN_MINUS_U 321
#define TOKEN_NOELSE 322




/* Copy the first part of user declarations.  */
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
#line 79 "src/rulesyacc.y"
{
  unsigned int integer_slot;
  double double_slot;
  termsPtr *terms_slot; //(A|B)
  std::vector< termsPtr  > *vector_terms_slot; // X Y
  std::string *string_slot;
  entryPtr *entry_slot;
  entriesPtr *entries_slot;
  bitsetPtr *bits_slot;
  valuePtr *value_slot;
  featurePtr *feature_slot;
  featuresPtr *features_slot;
  listPtr *list_slot;
  statementPtr *statement_slot;
  statementsPtr *statements_slot;
  std::list<  bitsetPtr > *list_args;
 }
/* Line 193 of yacc.c.  */
#line 334 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 347 "/Users/clement/workspace/elvex/src/rulesyacc.cc"

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
#define YYFINAL  24
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   671

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  68
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  43
/* YYNRULES -- Number of rules.  */
#define YYNRULES  151
/* YYNRULES -- Number of states.  */
#define YYNSTATES  259

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   322

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
      65,    66,    67
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     8,    12,    15,    18,    21,    24,
      26,    28,    30,    34,    38,    43,    47,    53,    55,    59,
      61,    64,    66,    67,    71,    72,    74,    76,    77,    83,
      88,    91,    93,    95,    99,   103,   105,   107,   109,   111,
     115,   118,   120,   122,   125,   129,   132,   134,   138,   142,
     146,   149,   154,   159,   164,   170,   178,   184,   186,   188,
     190,   192,   194,   201,   203,   205,   207,   209,   211,   217,
     219,   223,   227,   231,   235,   238,   242,   246,   250,   254,
     258,   262,   266,   270,   274,   278,   282,   285,   289,   291,
     293,   295,   299,   301,   303,   305,   307,   309,   311,   313,
     315,   317,   321,   323,   325,   330,   332,   334,   337,   342,
     345,   347,   350,   354,   357,   361,   363,   368,   371,   375,
     379,   383,   387,   391,   395,   399,   401,   403,   405,   407,
     409,   411,   413,   415,   417,   419,   421,   423,   427,   429,
     431,   435,   438,   444,   450,   454,   456,   458,   460,   462,
     464,   466
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      69,     0,    -1,    70,    -1,    21,    76,    -1,    22,    84,
     101,    -1,    22,    84,    -1,    23,    71,    -1,    14,   101,
      -1,    73,    71,    -1,    73,    -1,    60,    -1,    61,    -1,
      72,    49,    61,    -1,    25,    60,    16,    -1,    25,    60,
     101,    16,    -1,    72,    74,    16,    -1,    15,    60,    18,
     101,    16,    -1,    16,    -1,    75,    43,    74,    -1,    75,
      -1,    60,   101,    -1,    60,    -1,    -1,    77,    80,    76,
      -1,    -1,    78,    -1,    38,    -1,    -1,    79,    84,     3,
      81,    85,    -1,    79,    84,     3,    85,    -1,    81,    82,
      -1,    82,    -1,    83,    -1,    12,    83,    13,    -1,    83,
      43,    84,    -1,    84,    -1,    60,    -1,    64,    -1,     1,
      -1,    10,    86,    11,    -1,    10,    11,    -1,    16,    -1,
      88,    -1,    86,    88,    -1,    10,    86,    11,    -1,    10,
      11,    -1,    87,    -1,    26,    95,    16,    -1,    27,    95,
      16,    -1,    28,    95,    16,    -1,   101,    16,    -1,    93,
      42,    94,    16,    -1,    89,    40,    90,    16,    -1,    91,
      41,    92,    16,    -1,    29,     8,    95,     9,    88,    -1,
      29,     8,    95,     9,    88,    30,    88,    -1,    34,   107,
      35,    95,    88,    -1,   101,    -1,   107,    -1,    96,    -1,
     100,    -1,   101,    -1,    36,     8,   106,    20,    95,     9,
      -1,    98,    -1,    95,    -1,    97,    -1,    98,    -1,   107,
      -1,    56,   107,    19,   107,    58,    -1,    95,    -1,    95,
      45,    95,    -1,    95,    46,    95,    -1,    95,    47,    95,
      -1,    95,    48,    95,    -1,    44,    95,    -1,    95,    54,
      95,    -1,    95,    55,    95,    -1,    95,    56,    95,    -1,
      95,    57,    95,    -1,    95,    58,    95,    -1,    95,    59,
      95,    -1,    95,    49,    95,    -1,    95,    50,    95,    -1,
      95,    51,    95,    -1,    95,    52,    95,    -1,    95,    53,
      95,    -1,    50,    95,    -1,    37,     8,     9,    -1,    63,
      -1,    62,    -1,    61,    -1,    95,    39,    95,    -1,    96,
      -1,    97,    -1,    98,    -1,   100,    -1,   101,    -1,    31,
      -1,   105,    -1,    65,    -1,   107,    -1,     8,    95,     9,
      -1,   108,    -1,    99,    -1,    36,     8,    95,     9,    -1,
       4,    -1,     5,    -1,     6,    62,    -1,    14,    62,    17,
      62,    -1,    14,    62,    -1,     7,    -1,     7,    62,    -1,
      12,   102,    13,    -1,    12,    13,    -1,   102,    20,   103,
      -1,   103,    -1,   102,    20,    15,    60,    -1,    15,    60,
      -1,    24,    18,    60,    -1,    24,    18,   107,    -1,    25,
      18,   107,    -1,    25,    18,    72,    -1,   106,    18,   104,
      -1,   106,    18,    61,    -1,   107,    18,   104,    -1,   107,
      -1,   107,    -1,   105,    -1,    63,    -1,    62,    -1,   108,
      -1,   101,    -1,    31,    -1,    32,    -1,    33,    -1,    65,
      -1,   106,    -1,   106,    43,   105,    -1,    60,    -1,    64,
      -1,    56,   109,    58,    -1,    56,    58,    -1,    56,   109,
      19,   110,    58,    -1,    56,   109,    19,    31,    58,    -1,
     110,    20,   109,    -1,   110,    -1,   107,    -1,    63,    -1,
      62,    -1,   105,    -1,   101,    -1,   108,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
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
    1148,  1155,  1161,  1169,  1176,  1184,  1192,  1199,  1206,  1212,
    1218,  1225,  1232,  1238,  1244,  1250,  1257,  1263,  1271,  1279,
    1290,  1296,  1302,  1313,  1324,  1332,  1340,  1347,  1353,  1359,
    1366,  1373
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
  "TOKEN_DOT", "TOKEN_COLON", "TOKEN_DOUBLECOLON", "TOKEN_COMMA",
  "TOKEN_GRAMMAR", "TOKEN_INPUT", "TOKEN_LEXICON", "TOKEN_PRED",
  "TOKEN_FORM", "TOKEN_ATTEST", "TOKEN_PRINT", "TOKEN_PRINTLN", "TOKEN_IF",
  "TOKEN_ELSE", "TOKEN_NIL", "TOKEN_TRUE", "TOKEN_FALSE", "TOKEN_FOREACH",
  "TOKEN_IN", "TOKEN_SEARCH", "TOKEN_RAND", "TOKEN_TRACE", "TOKEN_UNION",
  "TOKEN_SUBSUME", "TOKEN_INSET", "TOKEN_AFF", "TOKEN_PIPE", "TOKEN_NOT",
  "TOKEN_OR", "TOKEN_AND", "TOKEN_IMPLICATION", "TOKEN_EQUIV",
  "TOKEN_PLUS", "TOKEN_MINUS", "TOKEN_TIMES", "TOKEN_DIVIDE",
  "TOKEN_MODULO", "TOKEN_EQUAL", "TOKEN_DIFF", "TOKEN_LT", "TOKEN_LE",
  "TOKEN_GT", "TOKEN_GE", "TOKEN_IDENTIFIER", "TOKEN_STRING",
  "TOKEN_INTEGER", "TOKEN_DOUBLE", "TOKEN_VARIABLE", "TOKEN_ANONYMOUS",
  "TOKEN_MINUS_U", "TOKEN_NOELSE", "$accept", "axiom", "begin",
  "dictionary", "stringOrIdentifier", "dictionary_line", "lexical_entries",
  "lexical_entry", "rules", "@1", "@2", "pref_rule", "rule",
  "terms_vector", "terms", "terms_disj", "term", "structure_statement",
  "list_statement", "statements", "statement",
  "left_hand_side_subset_statement", "right_hand_side_subset_statement",
  "left_hand_side_inset_statement", "right_hand_side_inset_statement",
  "left_hand_side_aff_statement", "right_hand_side_aff_statement",
  "expression_statement", "up", "updouble", "down", "dash_statement",
  "downdouble", "features", "features_components", "feature",
  "feature_value", "constant", "identifier", "variable", "list",
  "list_elements", "list_element", 0
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
     315,   316,   317,   318,   319,   320,   321,   322
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    68,    69,    70,    70,    70,    70,    70,    71,    71,
      72,    72,    72,    73,    73,    73,    73,    73,    74,    74,
      75,    75,    77,    76,    78,    76,    79,    79,    80,    80,
      81,    81,    82,    82,    83,    83,    84,    84,    84,    85,
      85,    85,    86,    86,    87,    87,    88,    88,    88,    88,
      88,    88,    88,    88,    88,    88,    88,    89,    90,    90,
      90,    90,    90,    91,    92,    93,    93,    93,    93,    94,
      95,    95,    95,    95,    95,    95,    95,    95,    95,    95,
      95,    95,    95,    95,    95,    95,    95,    95,    95,    95,
      95,    95,    95,    95,    95,    95,    95,    95,    95,    95,
      95,    95,    95,    95,    95,    96,    97,    98,    99,    99,
     100,   100,   101,   101,   102,   102,   102,   102,   103,   103,
     103,   103,   103,   103,   103,   103,   104,   104,   104,   104,
     104,   104,   104,   104,   104,   104,   105,   105,   106,   107,
     108,   108,   108,   108,   109,   109,   110,   110,   110,   110,
     110,   110
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
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
       3,     3,     3,     3,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     1,     1,
       3,     2,     5,     5,     3,     1,     1,     1,     1,     1,
       1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,    22,     0,     0,     0,     2,     0,     7,     3,
      27,    25,    38,    36,    37,     5,     0,    17,     0,    10,
      11,     6,     0,     9,     1,   113,     0,     0,     0,   138,
     139,     0,   115,     0,   125,    26,     0,    22,     4,     0,
       0,     0,    21,     0,    19,     8,   117,     0,     0,   112,
       0,     0,     0,     0,    23,     0,    13,     0,    12,    20,
      15,     0,   118,   119,   121,   120,     0,   114,   132,   133,
     134,     0,   123,   129,   128,   135,   131,   122,   127,   136,
     126,   130,   124,     0,     0,    14,    18,   116,   141,   148,
     147,   150,   149,   146,   151,     0,   145,     0,     0,     0,
      41,     0,    31,    32,    35,    29,    16,     0,   140,     0,
     137,   106,     0,     0,    40,     0,     0,     0,     0,     0,
       0,     0,    46,    42,     0,     0,     0,    65,    63,    57,
      67,     0,    30,    28,     0,     0,     0,   144,   107,    45,
       0,   105,   110,     0,     0,    97,     0,     0,     0,     0,
      90,    89,    88,    99,     0,    92,    93,    94,   103,    95,
      96,    98,   100,   102,     0,     0,     0,     0,     0,    39,
      43,     0,     0,     0,    50,    33,    34,   143,   142,    44,
     111,     0,   109,     0,     0,    74,    86,    47,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    48,    49,     0,     0,     0,     0,
       0,    59,    60,    61,    58,     0,    64,     0,    69,   101,
       0,     0,    87,    91,    70,    71,    72,    73,    81,    82,
      83,    84,    85,    75,    76,    77,    78,    79,    80,     0,
       0,     0,     0,    52,    53,    51,   108,   104,    54,     0,
      56,    68,     0,     0,   100,     0,    55,     0,    62
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     5,     6,    21,    22,    23,    43,    44,     9,    10,
      11,    36,    37,   101,   102,   103,   104,   105,   121,   122,
     123,   124,   210,   125,   215,   126,   217,   235,   155,   156,
     157,   158,   159,   160,    31,    32,    77,   161,    79,   162,
     163,    95,    96
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -114
static const yytype_int16 yypact[] =
{
     207,    -3,    16,    35,   157,    18,  -114,     4,  -114,  -114,
     -17,  -114,  -114,  -114,  -114,    -3,   -34,  -114,   -20,  -114,
    -114,  -114,   -36,   157,  -114,  -114,   -18,    39,    40,  -114,
    -114,    43,  -114,    47,    48,  -114,    35,    16,  -114,    58,
      19,    28,    -3,    84,    61,  -114,  -114,    38,   -49,  -114,
      86,   288,   323,   104,  -114,    -3,  -114,   102,  -114,  -114,
    -114,    64,  -114,  -114,    72,  -114,    65,  -114,  -114,  -114,
    -114,   333,  -114,  -114,  -114,  -114,  -114,  -114,  -114,    79,
    -114,  -114,  -114,    59,   112,  -114,  -114,  -114,  -114,  -114,
    -114,  -114,  -114,  -114,  -114,     1,   110,    75,   269,    35,
    -114,    59,  -114,    95,  -114,  -114,  -114,   346,  -114,   194,
    -114,  -114,    81,   278,  -114,   149,   149,   149,   133,    83,
      83,   303,  -114,  -114,   105,   117,   118,  -114,   122,   152,
    -114,    10,  -114,  -114,    35,   126,   129,  -114,  -114,  -114,
     312,  -114,   121,   149,   127,  -114,   180,   182,   149,   149,
    -114,  -114,  -114,  -114,   461,  -114,  -114,  -114,  -114,  -114,
    -114,  -114,  -114,  -114,   485,   506,   149,   156,   173,  -114,
    -114,   130,   149,   149,  -114,  -114,  -114,  -114,  -114,  -114,
    -114,   366,   183,   149,   192,   590,  -114,  -114,   149,   149,
     149,   149,   149,   149,   149,   149,   149,   149,   149,   149,
     149,   149,   149,   149,  -114,  -114,   389,   149,    83,   199,
     186,  -114,  -114,  -114,  -114,   200,   527,   206,   527,  -114,
     146,   417,  -114,   601,   569,   590,   548,   548,   125,   125,
     162,   162,  -114,   612,   612,   612,   612,   612,   612,   169,
     214,   165,    75,  -114,  -114,  -114,  -114,  -114,   197,   149,
    -114,  -114,   211,   169,   173,   149,  -114,   440,  -114
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -114,  -114,  -114,   209,   196,  -114,   185,  -114,   210,  -114,
    -114,  -114,  -114,  -114,   150,   135,    -2,   154,   163,  -114,
    -113,  -114,  -114,  -114,  -114,  -114,  -114,  -111,   106,   -91,
     -88,  -114,   111,    -1,  -114,   235,   234,    62,    -5,    -4,
      22,   178,   184
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -67
static const yytype_int16 yytable[] =
{
       8,    15,    33,    34,   154,   164,   165,   127,   170,     7,
     128,    19,    20,    41,    38,    30,   -24,    25,    24,    26,
     107,    35,   127,   175,    42,   128,    39,   170,    27,    28,
     127,     7,   181,   128,    53,    56,    12,   185,   186,    57,
      40,    59,    46,    63,    65,    33,    34,    80,    80,   127,
      76,    76,   128,   134,    84,   206,    49,    47,    48,   108,
      12,   216,   218,    50,    29,    51,    52,    93,    30,    98,
      91,    99,   221,    81,    81,   100,    55,   223,   224,   225,
     226,   227,   228,   229,   230,   231,   232,   233,   234,    58,
     236,   237,   238,    94,   130,    13,   240,   129,    62,    14,
      60,    66,    30,    93,    61,    93,    91,    83,    91,   130,
      27,    28,   129,    78,    78,   167,   168,   130,    85,    13,
     129,    41,    97,    14,    42,    87,   248,   250,   106,    94,
     109,    94,   176,    92,   141,    29,   130,   142,   134,   129,
     256,   166,     7,   138,   257,   171,    29,    30,   127,   127,
      30,   128,   128,   141,   111,   112,   142,   143,   172,   110,
     173,     7,   127,   144,   -66,   128,   209,   214,   174,    92,
     213,    92,    16,    17,   111,   112,   195,   196,   197,   113,
     145,     7,    18,   180,   177,   146,   147,   178,   183,   182,
     184,   207,   208,   148,    30,   115,   116,   117,   118,   149,
     220,   222,   243,   119,   241,    71,     7,   242,   246,    29,
     150,   151,   152,    30,   153,   197,   244,    19,    20,   111,
     112,     1,   245,   251,   113,   120,     7,   253,     2,     3,
       4,   255,    45,    30,   131,   130,   130,   252,   129,   129,
     115,   116,   117,   118,    64,   254,    86,    54,   119,   130,
      71,   132,   129,   188,    29,   133,    89,    90,    30,   189,
     190,   191,   192,   193,   194,   195,   196,   197,   198,   199,
     249,   201,   202,   203,   111,   112,   140,   211,    30,   113,
     114,     7,   212,   111,   112,    67,    82,   137,   113,   139,
       7,   136,     0,     0,     0,   115,   116,   117,   118,     0,
       7,     0,     0,   119,   115,   116,   117,   118,   111,   112,
       0,     0,   119,   113,   169,     7,     0,   111,   112,    68,
      69,    70,   113,   179,     7,   120,     0,     0,     0,   115,
     116,   117,   118,    30,   120,     7,     0,   119,   115,   116,
     117,   118,    30,     0,    71,     7,   119,     0,    29,    72,
      73,    74,    30,    75,    68,    69,    70,     0,     7,   120,
       0,     0,     0,     0,     0,     0,     0,    30,   120,     0,
       0,     0,     0,     0,     0,   219,    30,   135,     0,    71,
       0,     0,     0,    29,     0,    73,    74,    30,    75,    71,
       0,    88,     0,    29,     0,    89,    90,    30,   239,     0,
       0,     0,    71,     0,     0,   188,    29,     0,    89,    90,
      30,   189,   190,   191,   192,   193,   194,   195,   196,   197,
     198,   199,   200,   201,   202,   203,   247,     0,   188,     0,
       0,     0,     0,     0,   189,   190,   191,   192,   193,   194,
     195,   196,   197,   198,   199,   200,   201,   202,   203,   258,
       0,     0,     0,     0,     0,     0,   188,     0,     0,     0,
       0,     0,   189,   190,   191,   192,   193,   194,   195,   196,
     197,   198,   199,   200,   201,   202,   203,   187,     0,   188,
       0,     0,     0,     0,     0,   189,   190,   191,   192,   193,
     194,   195,   196,   197,   198,   199,   200,   201,   202,   203,
     188,   204,     0,     0,     0,     0,   189,   190,   191,   192,
     193,   194,   195,   196,   197,   198,   199,   200,   201,   202,
     203,     0,   205,     0,   188,     0,     0,     0,     0,     0,
     189,   190,   191,   192,   193,   194,   195,   196,   197,   198,
     199,   200,   201,   202,   203,   188,     0,     0,     0,     0,
       0,   189,   190,   191,   192,   193,   194,   195,   196,   197,
     198,   199,   200,   201,   202,   203,   188,     0,     0,     0,
       0,     0,   189,   190,   191,   192,   193,   194,   195,   196,
     197,   198,   199,   200,   201,   202,   203,   188,     0,     0,
       0,     0,     0,   189,   190,   -67,   -67,   193,   194,   195,
     196,   197,   198,   199,   200,   201,   202,   203,   188,     0,
       0,     0,     0,     0,     0,   190,     0,     0,   193,   194,
     195,   196,   197,   198,   199,   200,   201,   202,   203,   188,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   193,
     194,   195,   196,   197,   198,   199,   200,   201,   202,   203,
     193,   194,   195,   196,   197,   198,   199,   200,   201,   202,
     203,   193,   194,   195,   196,   197,   -67,   -67,   -67,   -67,
     -67,   -67
};

static const yytype_int16 yycheck[] =
{
       1,     3,     7,     7,   115,   116,   117,    98,   121,    12,
      98,    60,    61,    49,    15,    64,     0,    13,     0,    15,
      19,    38,   113,    13,    60,   113,    60,   140,    24,    25,
     121,    12,   143,   121,    36,    16,     1,   148,   149,    40,
      60,    42,    60,    47,    48,    50,    50,    51,    52,   140,
      51,    52,   140,    43,    55,   166,    13,    18,    18,    58,
       1,   172,   173,    20,    60,    18,    18,    71,    64,    10,
      71,    12,   183,    51,    52,    16,    18,   188,   189,   190,
     191,   192,   193,   194,   195,   196,   197,   198,   199,    61,
     201,   202,   203,    71,    98,    60,   207,    98,    60,    64,
      16,    15,    64,   107,    43,   109,   107,     3,   109,   113,
      24,    25,   113,    51,    52,   119,   120,   121,    16,    60,
     121,    49,    43,    64,    60,    60,   239,   240,    16,   107,
      20,   109,   134,    71,     4,    60,   140,     7,    43,   140,
     253,     8,    12,    62,   255,    40,    60,    64,   239,   240,
      64,   239,   240,     4,     5,     6,     7,     8,    41,    97,
      42,    12,   253,    14,    42,   253,    36,   171,    16,   107,
     171,   109,    15,    16,     5,     6,    51,    52,    53,    10,
      31,    12,    25,    62,    58,    36,    37,    58,     8,    62,
       8,    35,    19,    44,    64,    26,    27,    28,    29,    50,
      17,     9,    16,    34,   208,    56,    12,     8,    62,    60,
      61,    62,    63,    64,    65,    53,    16,    60,    61,     5,
       6,    14,    16,    58,    10,    56,    12,    30,    21,    22,
      23,    20,    23,    64,    99,   239,   240,   242,   239,   240,
      26,    27,    28,    29,    48,   249,    61,    37,    34,   253,
      56,   101,   253,    39,    60,   101,    62,    63,    64,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,     5,     6,   113,   171,    64,    10,
      11,    12,   171,     5,     6,    50,    52,   109,    10,    11,
      12,   107,    -1,    -1,    -1,    26,    27,    28,    29,    -1,
      12,    -1,    -1,    34,    26,    27,    28,    29,     5,     6,
      -1,    -1,    34,    10,    11,    12,    -1,     5,     6,    31,
      32,    33,    10,    11,    12,    56,    -1,    -1,    -1,    26,
      27,    28,    29,    64,    56,    12,    -1,    34,    26,    27,
      28,    29,    64,    -1,    56,    12,    34,    -1,    60,    61,
      62,    63,    64,    65,    31,    32,    33,    -1,    12,    56,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    64,    56,    -1,
      -1,    -1,    -1,    -1,    -1,     9,    64,    31,    -1,    56,
      -1,    -1,    -1,    60,    -1,    62,    63,    64,    65,    56,
      -1,    58,    -1,    60,    -1,    62,    63,    64,     9,    -1,
      -1,    -1,    56,    -1,    -1,    39,    60,    -1,    62,    63,
      64,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,     9,    -1,    39,    -1,
      -1,    -1,    -1,    -1,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,     9,
      -1,    -1,    -1,    -1,    -1,    -1,    39,    -1,    -1,    -1,
      -1,    -1,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    16,    -1,    39,
      -1,    -1,    -1,    -1,    -1,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      39,    16,    -1,    -1,    -1,    -1,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    -1,    16,    -1,    39,    -1,    -1,    -1,    -1,    -1,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    39,    -1,    -1,    -1,    -1,
      -1,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    39,    -1,    -1,    -1,
      -1,    -1,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    39,    -1,    -1,
      -1,    -1,    -1,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    39,    -1,
      -1,    -1,    -1,    -1,    -1,    46,    -1,    -1,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    39,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    14,    21,    22,    23,    69,    70,    12,   101,    76,
      77,    78,     1,    60,    64,    84,    15,    16,    25,    60,
      61,    71,    72,    73,     0,    13,    15,    24,    25,    60,
      64,   102,   103,   106,   107,    38,    79,    80,   101,    60,
      60,    49,    60,    74,    75,    71,    60,    18,    18,    13,
      20,    18,    18,    84,    76,    18,    16,   101,    61,   101,
      16,    43,    60,   107,    72,   107,    15,   103,    31,    32,
      33,    56,    61,    62,    63,    65,   101,   104,   105,   106,
     107,   108,   104,     3,   101,    16,    74,    60,    58,    62,
      63,   101,   105,   107,   108,   109,   110,    43,    10,    12,
      16,    81,    82,    83,    84,    85,    16,    19,    58,    20,
     105,     5,     6,    10,    11,    26,    27,    28,    29,    34,
      56,    86,    87,    88,    89,    91,    93,    97,    98,   101,
     107,    83,    82,    85,    43,    31,   110,   109,    62,    11,
      86,     4,     7,     8,    14,    31,    36,    37,    44,    50,
      61,    62,    63,    65,    95,    96,    97,    98,    99,   100,
     101,   105,   107,   108,    95,    95,     8,   107,   107,    11,
      88,    40,    41,    42,    16,    13,    84,    58,    58,    11,
      62,    95,    62,     8,     8,    95,    95,    16,    39,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    16,    16,    95,    35,    19,    36,
      90,    96,   100,   101,   107,    92,    95,    94,    95,     9,
      17,    95,     9,    95,    95,    95,    95,    95,    95,    95,
      95,    95,    95,    95,    95,    95,    95,    95,    95,     9,
      95,   107,     8,    16,    16,    16,    62,     9,    88,    56,
      88,    58,   106,    30,   107,    20,    88,    95,     9
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
#line 169 "src/rulesyacc.y"
    {
	  DBUGPRT("axiom done...");
	  YYACCEPT;
	;}
    break;

  case 3:
#line 175 "src/rulesyacc.y"
    {
	  DBUGPRT("begin grammar");
	;}
    break;

  case 4:
#line 179 "src/rulesyacc.y"
    {
	  DBUGPRT("begin input");
	  parser.setStartTerm((yyvsp[(2) - (3)].integer_slot));
	  (*(yyvsp[(3) - (3)].features_slot))->renameVariables((*(yyvsp[(3) - (3)].features_slot))->getId());
	  parser.setStartFeatures(*(yyvsp[(3) - (3)].features_slot));
	  free((yyvsp[(3) - (3)].features_slot));
	;}
    break;

  case 5:
#line 187 "src/rulesyacc.y"
    {
	  DBUGPRT("begin input");
	  parser.setStartTerm((yyvsp[(2) - (2)].integer_slot));
	  parser.setStartFeatures(Features::create());
	 ;}
    break;

  case 6:
#line 193 "src/rulesyacc.y"
    {      
	  DBUGPRT("begin lexicon");
	;}
    break;

  case 7:
#line 198 "src/rulesyacc.y"
    {
	  DBUGPRT("begin features");
	  parser.setLocalFeatures(*(yyvsp[(2) - (2)].features_slot));
	  free((yyvsp[(2) - (2)].features_slot));
	;}
    break;

  case 8:
#line 205 "src/rulesyacc.y"
    {
	  DBUGPRT("dictionary");
	;}
    break;

  case 9:
#line 209 "src/rulesyacc.y"
    {
	  DBUGPRT("dictionary");
	 ;}
    break;

  case 10:
#line 214 "src/rulesyacc.y"
    {
	  DBUGPRT("stringOrIdentifier");
	  (yyval.string_slot) = (yyvsp[(1) - (1)].string_slot);
	;}
    break;

  case 11:
#line 219 "src/rulesyacc.y"
    {
	  DBUGPRT("stringOrIdentifier");
	  (yyval.string_slot) = (yyvsp[(1) - (1)].string_slot);
	 ;}
    break;

  case 12:
#line 224 "src/rulesyacc.y"
    {
	  DBUGPRT("string");
	  (yyval.string_slot) = (yyvsp[(1) - (3)].string_slot);
	  *(yyval.string_slot) += *(yyvsp[(3) - (3)].string_slot);
	 ;}
    break;

  case 13:
#line 233 "src/rulesyacc.y"
    {
	  DBUGPRT("dictionary_line");
	  unsigned int code=Vartable::identifierToCode(*(yyvsp[(2) - (3)].string_slot));
	  free((yyvsp[(2) - (3)].string_slot));
	  // constantNoun => (0 => args)
	  Parser::entries_map_map::iterator foundCode = parser.getLexicon().find(code);
	  Parser::entries_map *zeroToEntries;
	  if (foundCode != parser.getLexicon().end()){
	    zeroToEntries = foundCode->second;
	  } else {
	    zeroToEntries = new Parser::entries_map();
	    parser.getLexicon().insert(std::make_pair(code, zeroToEntries));
	  }
	  Parser::entries_map::iterator foundPred=zeroToEntries->find(0);
	  entriesPtr lp;
	  if (foundPred!=zeroToEntries->end()){
	    lp=foundPred->second;
	  } else {
	    lp = Entries::create();
	    zeroToEntries->insert(std::make_pair(0, lp));
	  }
	  lp->add(Entry::create(code, UINT_MAX, std::string(), Features::create()));
	;}
    break;

  case 14:
#line 258 "src/rulesyacc.y"
    {
	  DBUGPRT("dictionary_line");
	  unsigned int code=Vartable::identifierToCode(*(yyvsp[(2) - (4)].string_slot));
	  free((yyvsp[(2) - (4)].string_slot));
	  // constantNoun => (0 => args)
	  Parser::entries_map_map::iterator foundCode=parser.getLexicon().find(code);
	  Parser::entries_map *zeroToEntries;
	  if (foundCode!=parser.getLexicon().end()) {
	    zeroToEntries=foundCode->second;
	  } else {
	    zeroToEntries = new Parser::entries_map;
	    parser.getLexicon().insert(std::make_pair(code, zeroToEntries));
	  }
	  Parser::entries_map::iterator foundPred=zeroToEntries->find(0);
	  entriesPtr lp;
	  if (foundPred!=zeroToEntries->end()){
	    lp=foundPred->second;
	  } else {
	    lp=Entries::create();
	    zeroToEntries->insert(std::make_pair(0, lp));
	  }
	  lp->add(Entry::create(code, UINT_MAX, std::string(), *(yyvsp[(3) - (4)].features_slot)));
	  free((yyvsp[(3) - (4)].features_slot));
	;}
    break;

  case 15:
#line 285 "src/rulesyacc.y"
    {
	  DBUGPRT("dictionary_line");
	  for (auto entry = (*(yyvsp[(2) - (3)].entries_slot))->begin() ; entry != (*(yyvsp[(2) - (3)].entries_slot))->end() ; ++entry) {
	    (*entry)->setForm(*(yyvsp[(1) - (3)].string_slot));
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
	  free((yyvsp[(1) - (3)].string_slot));
	  free((yyvsp[(2) - (3)].entries_slot));
	;}
    break;

  case 16:
#line 314 "src/rulesyacc.y"
    {
	  DBUGPRT("dictionary_line");
	  parser.addMacros(*(yyvsp[(2) - (5)].string_slot), *(yyvsp[(4) - (5)].features_slot));
	  free((yyvsp[(2) - (5)].string_slot));
	  free((yyvsp[(4) - (5)].features_slot));
	  
	;}
    break;

  case 17:
#line 323 "src/rulesyacc.y"
    {
	  DBUGPRT("dictionary_line");
	;}
    break;

  case 18:
#line 329 "src/rulesyacc.y"
    {	  
	  DBUGPRT("lexical_entries");
	  (yyval.entries_slot) = (yyvsp[(3) - (3)].entries_slot);
	  (*(yyval.entries_slot))->add(*(yyvsp[(1) - (3)].entry_slot));
	  free((yyvsp[(1) - (3)].entry_slot));
	;}
    break;

  case 19:
#line 336 "src/rulesyacc.y"
    {
	  DBUGPRT("lexical_entries");
	  (yyval.entries_slot) = new entriesPtr(Entries::create(*(yyvsp[(1) - (1)].entry_slot)));
	  free((yyvsp[(1) - (1)].entry_slot));
	 ;}
    break;

  case 20:
#line 345 "src/rulesyacc.y"
    {
	  DBUGPRT("lexical_entry");
	  unsigned int pred = (*(yyvsp[(2) - (2)].features_slot))->assignPred();
	  (yyval.entry_slot) = new entryPtr(Entry::create(Vartable::identifierToCode(*(yyvsp[(1) - (2)].string_slot)), pred, std::string(), *(yyvsp[(2) - (2)].features_slot)));
	  free((yyvsp[(1) - (2)].string_slot));
	  free((yyvsp[(2) - (2)].features_slot));
	;}
    break;

  case 21:
#line 354 "src/rulesyacc.y"
    {
	  DBUGPRT("lexical_entry");
	  (yyval.entry_slot) = new entryPtr(Entry::create(Vartable::identifierToCode(*(yyvsp[(1) - (1)].string_slot)), UINT_MAX, std::string(), Features::create()));
	  free((yyvsp[(1) - (1)].string_slot));
	;}
    break;

  case 22:
#line 364 "src/rulesyacc.y"
    {headLineno = ruleslineno;;}
    break;

  case 23:
#line 365 "src/rulesyacc.y"
    {
	  DBUGPRT("rules"); 
	;}
    break;

  case 24:
#line 369 "src/rulesyacc.y"
    {headLineno = ruleslineno;;}
    break;

  case 25:
#line 370 "src/rulesyacc.y"
    {
	  DBUGPRT("rules"); 
	;}
    break;

  case 26:
#line 376 "src/rulesyacc.y"
    {
	  DBUGPRT("pref_rule");
	  headTrace = true;
	;}
    break;

  case 27:
#line 381 "src/rulesyacc.y"
    {
	  DBUGPRT("pref_rule");
	  headTrace = false;
	;}
    break;

  case 28:
#line 388 "src/rulesyacc.y"
    {
	  DBUGPRT("rule");
	  rulePtr rule = Rule::create(headLineno, parser.getTopBufferName(), (yyvsp[(2) - (5)].integer_slot), *(yyvsp[(4) - (5)].vector_terms_slot), (yyvsp[(5) - (5)].statements_slot) ? *(yyvsp[(5) - (5)].statements_slot) : statementsPtr());
	  rule->addDefaults();
	  rule->setTrace(headTrace);
	  parser.getGrammar().addRule(rule);
	  if (!parser.getGrammar().getStartTerm()){
	    parser.getGrammar().setStartTerm((yyvsp[(2) - (5)].integer_slot));
	  }
	  free((yyvsp[(4) - (5)].vector_terms_slot));
	  if ((yyvsp[(5) - (5)].statements_slot))
	     free((yyvsp[(5) - (5)].statements_slot));
	;}
    break;

  case 29:
#line 403 "src/rulesyacc.y"
    {
	  DBUGPRT("Rule");
	  rulePtr rule = Rule::create(headLineno, parser.getTopBufferName(), (yyvsp[(2) - (4)].integer_slot), (yyvsp[(4) - (4)].statements_slot) ? *(yyvsp[(4) - (4)].statements_slot) : statementsPtr());
	  rule->addDefaults();
	  rule->setTrace(headTrace);
	  parser.getGrammar().addRule(rule);
	  if (!parser.getGrammar().getStartTerm()){
	    parser.getGrammar().setStartTerm((yyvsp[(2) - (4)].integer_slot));
	  }
	  if ((yyvsp[(4) - (4)].statements_slot))
	    free((yyvsp[(4) - (4)].statements_slot));
	;}
    break;

  case 30:
#line 417 "src/rulesyacc.y"
    { 
	  DBUGPRT("term_vector");
	  (yyval.vector_terms_slot)=(yyvsp[(1) - (2)].vector_terms_slot);
	  (yyval.vector_terms_slot)->push_back(*(yyvsp[(2) - (2)].terms_slot));
	;}
    break;

  case 31:
#line 423 "src/rulesyacc.y"
    { 
	  DBUGPRT("term_vector"); 
	  (yyval.vector_terms_slot) = new std::vector< termsPtr >;
	  (yyval.vector_terms_slot)->push_back(*(yyvsp[(1) - (1)].terms_slot));
	;}
    break;

  case 32:
#line 430 "src/rulesyacc.y"
    { 
	  DBUGPRT("term");
	  (yyval.terms_slot)=(yyvsp[(1) - (1)].terms_slot);
	;}
    break;

  case 33:
#line 435 "src/rulesyacc.y"
    { 
	  DBUGPRT("term");
	  (yyval.terms_slot) = (yyvsp[(2) - (3)].terms_slot);
	  (*(yyval.terms_slot))->setOptional();
	;}
    break;

  case 34:
#line 443 "src/rulesyacc.y"
    { 
	  DBUGPRT("term_disj");
	  (yyval.terms_slot) = (yyvsp[(1) - (3)].terms_slot);
	  (*(yyval.terms_slot))->push_back((yyvsp[(3) - (3)].integer_slot));
	;}
    break;

  case 35:
#line 450 "src/rulesyacc.y"
    { 
	  DBUGPRT("term_disj"); 
	  (yyval.terms_slot) = new termsPtr(Terms::create((yyvsp[(1) - (1)].integer_slot)));
	;}
    break;

  case 36:
#line 457 "src/rulesyacc.y"
    { 
	  DBUGPRT("term_id");
	  (yyval.integer_slot) = Vartable::identifierToCode(*(yyvsp[(1) - (1)].string_slot));
	  free((yyvsp[(1) - (1)].string_slot));
	;}
    break;

  case 37:
#line 464 "src/rulesyacc.y"
    { 
	  DBUGPRT("term_id");
	  (yyval.integer_slot) = Vartable::identifierToCode(*(yyvsp[(1) - (1)].string_slot));
	  free((yyvsp[(1) - (1)].string_slot));
	;}
    break;

  case 38:
#line 471 "src/rulesyacc.y"
    {
	  YYABORT;
	;}
    break;

  case 39:
#line 480 "src/rulesyacc.y"
    {
	  DBUGPRT("structure_statement");
	  (yyval.statements_slot)=(yyvsp[(2) - (3)].statements_slot);
	;}
    break;

  case 40:
#line 486 "src/rulesyacc.y"
    {
	  (yyval.statements_slot)=NULL;
	;}
    break;

  case 41:
#line 491 "src/rulesyacc.y"
    {
	  (yyval.statements_slot)=NULL;
	;}
    break;

  case 42:
#line 497 "src/rulesyacc.y"
    {
	  DBUGPRT("list_statement");
	  (yyval.statements_slot) = new statementsPtr(Statements::create());
	  (*(yyval.statements_slot))->addStatement(*(yyvsp[(1) - (1)].statement_slot));
	  free((yyvsp[(1) - (1)].statement_slot));
	;}
    break;

  case 43:
#line 504 "src/rulesyacc.y"
    {
	  DBUGPRT("list_statement");
	  (yyval.statements_slot) = (yyvsp[(1) - (2)].statements_slot);
	  (*(yyval.statements_slot))->addStatement(*(yyvsp[(2) - (2)].statement_slot));
	  free((yyvsp[(2) - (2)].statement_slot));
	;}
    break;

  case 44:
#line 513 "src/rulesyacc.y"
    {
	  DBUGPRT("statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::STMS, *(yyvsp[(2) - (3)].statements_slot)));
	  free((yyvsp[(2) - (3)].statements_slot));
	;}
    break;

  case 45:
#line 520 "src/rulesyacc.y"
    {
	  DBUGPRT("statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::STMS, Statements::create()));
	;}
    break;

  case 46:
#line 526 "src/rulesyacc.y"
    {
	  DBUGPRT("statement");
	  (yyval.statement_slot)=(yyvsp[(1) - (1)].statement_slot);
	 ;}
    break;

  case 47:
#line 531 "src/rulesyacc.y"
    {
	  DBUGPRT("statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::ATTEST, *(yyvsp[(2) - (3)].statement_slot)));
	  free((yyvsp[(2) - (3)].statement_slot));
	;}
    break;

  case 48:
#line 537 "src/rulesyacc.y"
    {
	  DBUGPRT("statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::PRINT, *(yyvsp[(2) - (3)].statement_slot)));
	  free((yyvsp[(2) - (3)].statement_slot));
	;}
    break;

  case 49:
#line 543 "src/rulesyacc.y"
    {
	  DBUGPRT("statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::PRINTLN, *(yyvsp[(2) - (3)].statement_slot)));
	  free((yyvsp[(2) - (3)].statement_slot));
	;}
    break;

  case 50:
#line 549 "src/rulesyacc.y"
    {
	  DBUGPRT("statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::GUARD, *(yyvsp[(1) - (2)].features_slot)));
	  free((yyvsp[(1) - (2)].features_slot));
	;}
    break;

  case 51:
#line 555 "src/rulesyacc.y"
    {
	  DBUGPRT("statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::AFF, *(yyvsp[(1) - (4)].statement_slot), *(yyvsp[(3) - (4)].statement_slot)));
	  // <X, …> = <…>
	  // <X, …> = Z
	  if (((*(yyvsp[(1) - (4)].statement_slot))->isList()) && (((*(yyvsp[(3) - (4)].statement_slot))->isList())||((*(yyvsp[(3) - (4)].statement_slot))->isVariable()))) {
	    }
	  // ↓i = $X
	  // ↓i = […]
	  // ↓i = ↑
	  // ↓i = … ∪ …
	  // ↓i = ⇓j
	  else if (((*(yyvsp[(1) - (4)].statement_slot))->isDown()) && (((*(yyvsp[(3) - (4)].statement_slot))->isVariable())||((*(yyvsp[(3) - (4)].statement_slot))->isFeatures())||((*(yyvsp[(3) - (4)].statement_slot))->isUp())||((*(yyvsp[(3) - (4)].statement_slot))->isUnif())||((*(yyvsp[(3) - (4)].statement_slot))->isDown2())))
	    ;
	  // ⇑ = $X
	  // ⇑ = […]
	  // ⇑ = ↑
	  // ⇑ = … ∪ …
	  // ⇑ = ⇓j
	  else if (((*(yyvsp[(1) - (4)].statement_slot))->isUp2()) && (((*(yyvsp[(3) - (4)].statement_slot))->isVariable())||((*(yyvsp[(3) - (4)].statement_slot))->isFeatures())||((*(yyvsp[(3) - (4)].statement_slot))->isUp())||((*(yyvsp[(3) - (4)].statement_slot))->isUnif())||((*(yyvsp[(3) - (4)].statement_slot))->isDown2())))
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
	  else if (((*(yyvsp[(1) - (4)].statement_slot))->isVariable()) 
		   &&(((*(yyvsp[(3) - (4)].statement_slot))->isVariable())
		      ||((*(yyvsp[(3) - (4)].statement_slot))->isConstant())
		      ||((*(yyvsp[(3) - (4)].statement_slot))->isList())
		      ||((*(yyvsp[(3) - (4)].statement_slot))->isFeatures())
		      ||((*(yyvsp[(3) - (4)].statement_slot))->isUp())
		      ||((*(yyvsp[(3) - (4)].statement_slot))->isUnif())
		      ||((*(yyvsp[(3) - (4)].statement_slot))->isDown2())
		      ||((*(yyvsp[(3) - (4)].statement_slot))->isNumber())
		      ||((*(yyvsp[(3) - (4)].statement_slot))->isFct())
		      ||((*(yyvsp[(3) - (4)].statement_slot))->isSearch())));
	  else {
	    yyerror((char*)"syntax error");
	  }
	  free((yyvsp[(1) - (4)].statement_slot));
	  free((yyvsp[(3) - (4)].statement_slot));
	;}
    break;

  case 52:
#line 603 "src/rulesyacc.y"
    {
	  DBUGPRT("statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::SUBSUME, (*(yyvsp[(1) - (4)].statement_slot)), (*(yyvsp[(3) - (4)].statement_slot))));
	  // […] ⊂ ↑ 
	  // […] ⊂ ⇓j 
	  // […] ⊂ $X 
	  // […] ⊂ search  
	  if (((*(yyvsp[(1) - (4)].statement_slot))->isFeatures()) && (((*(yyvsp[(3) - (4)].statement_slot))->isUp())||((*(yyvsp[(3) - (4)].statement_slot))->isDown2())||((*(yyvsp[(3) - (4)].statement_slot))->isVariable())||((*(yyvsp[(3) - (4)].statement_slot))->isSearch())))
	    ;
	  else 
	    yyerror((char *)"syntax error");
	  free((yyvsp[(1) - (4)].statement_slot));
	  free((yyvsp[(3) - (4)].statement_slot));
	;}
    break;

  case 53:
#line 618 "src/rulesyacc.y"
    {
	  DBUGPRT("statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::INSET, (*(yyvsp[(1) - (4)].statement_slot)), (*(yyvsp[(3) - (4)].statement_slot))));
	  // ↓i ∈ <...>
	  if (((*(yyvsp[(1) - (4)].statement_slot))->isDown())
	       && (((*(yyvsp[(3) - (4)].statement_slot))->isList())))
	    ;
	    else 
	  yyerror((char *)"syntax error");
	  free((yyvsp[(1) - (4)].statement_slot));
	  free((yyvsp[(3) - (4)].statement_slot));
	;}
    break;

  case 54:
#line 631 "src/rulesyacc.y"
    {
	  DBUGPRT("statement");
	  statementPtr stm;
	  if (!(*(yyvsp[(5) - (5)].statement_slot))->isStms()) {
	    statementsPtr stms = Statements::create();
	    stms->addStatement(*(yyvsp[(5) - (5)].statement_slot));
	    stm = Statement::create(ruleslineno, Statement::STMS, stms);
	  }
	  else
	    stm = *(yyvsp[(5) - (5)].statement_slot);
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, 
						Statement::IF,
						  *(yyvsp[(3) - (5)].statement_slot), 
						  Statement::create(ruleslineno, Statement::THENELSE, stm, statementPtr())));
	  free((yyvsp[(3) - (5)].statement_slot));
	  free((yyvsp[(5) - (5)].statement_slot));
	;}
    break;

  case 55:
#line 649 "src/rulesyacc.y"
    {
	  DBUGPRT("statement");
	  statementPtr stm1;
	  statementPtr stm2;
	  if (!(*(yyvsp[(5) - (7)].statement_slot))->isStms()) {
	    statementsPtr stms = Statements::create();
	    stms->addStatement(*(yyvsp[(5) - (7)].statement_slot));
	    stm1 = Statement::create(ruleslineno, Statement::STMS, stms);
	  }
	  else
	    stm1 = *(yyvsp[(5) - (7)].statement_slot);
	  if (!(*(yyvsp[(7) - (7)].statement_slot))->isStms()) {
	    statementsPtr stms = Statements::create();
	    stms->addStatement(*(yyvsp[(7) - (7)].statement_slot));
	    stm2 = Statement::create(ruleslineno, Statement::STMS, stms);
	  }
	  else
	    stm2 = *(yyvsp[(7) - (7)].statement_slot);
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, 
						  Statement::IF, 
						  (*(yyvsp[(3) - (7)].statement_slot)), 
						  Statement::create(ruleslineno, Statement::THENELSE, stm1, stm2)));
	  free((yyvsp[(3) - (7)].statement_slot));
	  free((yyvsp[(5) - (7)].statement_slot));
	  free((yyvsp[(7) - (7)].statement_slot));
	;}
    break;

  case 56:
#line 676 "src/rulesyacc.y"
    {
	  DBUGPRT("statement");
	  statementPtr stm;
	  if (!(*(yyvsp[(5) - (5)].statement_slot))->isStms()) {
	    statementsPtr stms = Statements::create();
	    stms->addStatement(*(yyvsp[(5) - (5)].statement_slot));
	    stm = Statement::create(ruleslineno, Statement::STMS, stms);
	  }
	  else
	    stm = *(yyvsp[(5) - (5)].statement_slot);
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, 
						  Statement::FOREACH,
						  Statement::create(ruleslineno, Statement::VARIABLE, (*(yyvsp[(2) - (5)].bits_slot))),
						  Statement::create(ruleslineno, Statement::IN, (*(yyvsp[(4) - (5)].statement_slot)), stm)));
	  free((yyvsp[(2) - (5)].bits_slot));
	  free((yyvsp[(4) - (5)].statement_slot));
	  free((yyvsp[(5) - (5)].statement_slot));
	;}
    break;

  case 57:
#line 696 "src/rulesyacc.y"
    {
	  DBUGPRT("left_hand_side_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::FEATURES, *(yyvsp[(1) - (1)].features_slot)));
	  free((yyvsp[(1) - (1)].features_slot));
	;}
    break;

  case 58:
#line 703 "src/rulesyacc.y"
    {
	  DBUGPRT("right_hand_side_subset_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::VARIABLE, *(yyvsp[(1) - (1)].bits_slot)));
	  free((yyvsp[(1) - (1)].bits_slot));
	;}
    break;

  case 59:
#line 709 "src/rulesyacc.y"
    {
	  DBUGPRT("right_hand_side_subset_statement");
	  (yyval.statement_slot)=(yyvsp[(1) - (1)].statement_slot);
	;}
    break;

  case 60:
#line 714 "src/rulesyacc.y"
    {
	  DBUGPRT("right_hand_side_subset_statement");
	  (yyval.statement_slot)=(yyvsp[(1) - (1)].statement_slot);
	;}
    break;

  case 61:
#line 719 "src/rulesyacc.y"
    {
	  DBUGPRT("right_hand_side_subset_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::FEATURES, *(yyvsp[(1) - (1)].features_slot)));
	  free((yyvsp[(1) - (1)].features_slot));
	;}
    break;

  case 62:
#line 725 "src/rulesyacc.y"
    {
	  DBUGPRT("right_hand_side_subset_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, 
						  Statement::SEARCH, 
						  *(yyvsp[(3) - (6)].bits_slot),
						  *(yyvsp[(5) - (6)].statement_slot)));
	  free((yyvsp[(3) - (6)].bits_slot));
	  free((yyvsp[(5) - (6)].statement_slot));
	 ;}
    break;

  case 63:
#line 736 "src/rulesyacc.y"
    {
	  DBUGPRT("left_hand_side_statement");
	  (yyval.statement_slot)=(yyvsp[(1) - (1)].statement_slot);
	;}
    break;

  case 64:
#line 742 "src/rulesyacc.y"
    {
	  DBUGPRT("right_hand_side_statement");
	  (yyval.statement_slot)=(yyvsp[(1) - (1)].statement_slot);
	;}
    break;

  case 65:
#line 748 "src/rulesyacc.y"
    {
	  DBUGPRT("left_hand_side_statement");
	  (yyval.statement_slot)=(yyvsp[(1) - (1)].statement_slot);
	;}
    break;

  case 66:
#line 753 "src/rulesyacc.y"
    {
	  DBUGPRT("left_hand_side_statement");
	  (yyval.statement_slot)=(yyvsp[(1) - (1)].statement_slot);
	;}
    break;

  case 67:
#line 758 "src/rulesyacc.y"
    {
	  DBUGPRT("left_hand_side_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::VARIABLE, *(yyvsp[(1) - (1)].bits_slot)));
	  free((yyvsp[(1) - (1)].bits_slot));
	 ;}
    break;

  case 68:
#line 765 "src/rulesyacc.y"
    {
	  DBUGPRT("left_hand_side_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::LIST,
						List::create(List::create(Value::create(Value::VARIABLE, *(yyvsp[(2) - (5)].bits_slot))),
							     List::create(Value::create(Value::VARIABLE, *(yyvsp[(4) - (5)].bits_slot))))));
	  free((yyvsp[(2) - (5)].bits_slot));
	  free((yyvsp[(4) - (5)].bits_slot));
	;}
    break;

  case 69:
#line 775 "src/rulesyacc.y"
    {
	  DBUGPRT("right_hand_side_statement");
	  (yyval.statement_slot)=(yyvsp[(1) - (1)].statement_slot);
	;}
    break;

  case 70:
#line 784 "src/rulesyacc.y"
    {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::FCT, Statement::OR, (*(yyvsp[(1) - (3)].statement_slot)), (*(yyvsp[(3) - (3)].statement_slot))));
	  free((yyvsp[(1) - (3)].statement_slot));
	  free((yyvsp[(3) - (3)].statement_slot));
	;}
    break;

  case 71:
#line 791 "src/rulesyacc.y"
    {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::FCT, Statement::AND, (*(yyvsp[(1) - (3)].statement_slot)), (*(yyvsp[(3) - (3)].statement_slot))));
	  free((yyvsp[(1) - (3)].statement_slot));
	  free((yyvsp[(3) - (3)].statement_slot));
	;}
    break;

  case 72:
#line 798 "src/rulesyacc.y"
    {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::FCT, Statement::OR, Statement::create(ruleslineno, Statement::FCT, Statement::NOT, (*(yyvsp[(1) - (3)].statement_slot))), (*(yyvsp[(3) - (3)].statement_slot))));
	  free((yyvsp[(1) - (3)].statement_slot));
	  free((yyvsp[(3) - (3)].statement_slot));
	;}
    break;

  case 73:
#line 805 "src/rulesyacc.y"
    {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::FCT, Statement::AND,
						Statement::create(ruleslineno, Statement::FCT, Statement::OR,
								  Statement::create(ruleslineno, Statement::FCT, Statement::NOT, (*(yyvsp[(1) - (3)].statement_slot))),
								  (*(yyvsp[(3) - (3)].statement_slot))),
						Statement::create(ruleslineno, Statement::FCT, Statement::OR,
								  (*(yyvsp[(1) - (3)].statement_slot)),
								  Statement::create(ruleslineno, Statement::FCT, Statement::NOT, (*(yyvsp[(3) - (3)].statement_slot))))));
	  free((yyvsp[(1) - (3)].statement_slot));
	  free((yyvsp[(3) - (3)].statement_slot));
	;}
    break;

  case 74:
#line 818 "src/rulesyacc.y"
    {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::FCT, Statement::NOT, (*(yyvsp[(2) - (2)].statement_slot))));
	  free((yyvsp[(2) - (2)].statement_slot));
	;}
    break;

  case 75:
#line 824 "src/rulesyacc.y"
    {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::FCT, Statement::EQ, (*(yyvsp[(1) - (3)].statement_slot)), (*(yyvsp[(3) - (3)].statement_slot))));
	  free((yyvsp[(1) - (3)].statement_slot));
	  free((yyvsp[(3) - (3)].statement_slot));
	;}
    break;

  case 76:
#line 831 "src/rulesyacc.y"
    { 
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::FCT, Statement::DIFF, (*(yyvsp[(1) - (3)].statement_slot)), (*(yyvsp[(3) - (3)].statement_slot)))); 
	  free((yyvsp[(1) - (3)].statement_slot));
	  free((yyvsp[(3) - (3)].statement_slot));
	;}
    break;

  case 77:
#line 838 "src/rulesyacc.y"
    { 
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::FCT, Statement::LT, (*(yyvsp[(1) - (3)].statement_slot)), (*(yyvsp[(3) - (3)].statement_slot)))); 
	  free((yyvsp[(1) - (3)].statement_slot));
	  free((yyvsp[(3) - (3)].statement_slot));
	;}
    break;

  case 78:
#line 845 "src/rulesyacc.y"
    { 
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::FCT, Statement::LE, (*(yyvsp[(1) - (3)].statement_slot)), (*(yyvsp[(3) - (3)].statement_slot)))); 
	  free((yyvsp[(1) - (3)].statement_slot));
	  free((yyvsp[(3) - (3)].statement_slot));
	;}
    break;

  case 79:
#line 852 "src/rulesyacc.y"
    { 
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::FCT, Statement::GT, (*(yyvsp[(1) - (3)].statement_slot)), (*(yyvsp[(3) - (3)].statement_slot)))); 
	  free((yyvsp[(1) - (3)].statement_slot));
	  free((yyvsp[(3) - (3)].statement_slot));
	;}
    break;

  case 80:
#line 859 "src/rulesyacc.y"
    { 
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::FCT, Statement::GE, (*(yyvsp[(1) - (3)].statement_slot)), (*(yyvsp[(3) - (3)].statement_slot)))); 
	  free((yyvsp[(1) - (3)].statement_slot));
	  free((yyvsp[(3) - (3)].statement_slot));
	;}
    break;

  case 81:
#line 870 "src/rulesyacc.y"
    {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::FCT, Statement::PLUS, (*(yyvsp[(1) - (3)].statement_slot)), (*(yyvsp[(3) - (3)].statement_slot))));
	  free((yyvsp[(1) - (3)].statement_slot));
	  free((yyvsp[(3) - (3)].statement_slot));
	;}
    break;

  case 82:
#line 878 "src/rulesyacc.y"
    {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::FCT, Statement::MINUS, (*(yyvsp[(1) - (3)].statement_slot)), (*(yyvsp[(3) - (3)].statement_slot))));
	  free((yyvsp[(1) - (3)].statement_slot));
	  free((yyvsp[(3) - (3)].statement_slot));
	;}
    break;

  case 83:
#line 886 "src/rulesyacc.y"
    {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::FCT, Statement::TIMES, (*(yyvsp[(1) - (3)].statement_slot)), (*(yyvsp[(3) - (3)].statement_slot))));
	  free((yyvsp[(1) - (3)].statement_slot));
	  free((yyvsp[(3) - (3)].statement_slot));
	;}
    break;

  case 84:
#line 894 "src/rulesyacc.y"
    {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::FCT, Statement::DIVIDE, (*(yyvsp[(1) - (3)].statement_slot)), (*(yyvsp[(3) - (3)].statement_slot))));
	  free((yyvsp[(1) - (3)].statement_slot));
	  free((yyvsp[(3) - (3)].statement_slot));
	;}
    break;

  case 85:
#line 902 "src/rulesyacc.y"
    {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::FCT, Statement::MODULO, (*(yyvsp[(1) - (3)].statement_slot)), (*(yyvsp[(3) - (3)].statement_slot))));
	  free((yyvsp[(1) - (3)].statement_slot));
	  free((yyvsp[(3) - (3)].statement_slot));
	;}
    break;

  case 86:
#line 910 "src/rulesyacc.y"
    {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::FCT, Statement::MINUS_U, (*(yyvsp[(2) - (2)].statement_slot)), statementPtr()));
	  free((yyvsp[(2) - (2)].statement_slot));
	;}
    break;

  case 87:
#line 917 "src/rulesyacc.y"
    {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::FCT, Statement::RAND));
	;}
    break;

  case 88:
#line 923 "src/rulesyacc.y"
    {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::NUMBER, (yyvsp[(1) - (1)].double_slot)));
	;}
    break;

  case 89:
#line 929 "src/rulesyacc.y"
    {
	  DBUGPRT("expression_statement");
 	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::NUMBER, (double)(yyvsp[(1) - (1)].integer_slot)));
	;}
    break;

  case 90:
#line 935 "src/rulesyacc.y"
    {
	  DBUGPRT("expression_statement");
 	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::STR, *(yyvsp[(1) - (1)].string_slot)));
	;}
    break;

  case 91:
#line 943 "src/rulesyacc.y"
    {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::UNIF, (*(yyvsp[(1) - (3)].statement_slot)), (*(yyvsp[(3) - (3)].statement_slot))));
	  free((yyvsp[(1) - (3)].statement_slot));
	  free((yyvsp[(3) - (3)].statement_slot));
	;}
    break;

  case 92:
#line 950 "src/rulesyacc.y"
    {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot)=(yyvsp[(1) - (1)].statement_slot);
	;}
    break;

  case 93:
#line 955 "src/rulesyacc.y"
    {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot)=(yyvsp[(1) - (1)].statement_slot);
	;}
    break;

  case 94:
#line 960 "src/rulesyacc.y"
    {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot)=(yyvsp[(1) - (1)].statement_slot);
	;}
    break;

  case 95:
#line 965 "src/rulesyacc.y"
    {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot)=(yyvsp[(1) - (1)].statement_slot);
	;}
    break;

  case 96:
#line 970 "src/rulesyacc.y"
    {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::FEATURES, *(yyvsp[(1) - (1)].features_slot)));
	  free((yyvsp[(1) - (1)].features_slot));
	;}
    break;

  case 97:
#line 977 "src/rulesyacc.y"
    {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::NIL));
	;}
    break;

  case 98:
#line 982 "src/rulesyacc.y"
    {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::CONSTANT, *(yyvsp[(1) - (1)].bits_slot)));
	  free((yyvsp[(1) - (1)].bits_slot));
	;}
    break;

  case 99:
#line 989 "src/rulesyacc.y"
    {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::ANONYMOUS, Value::ANONYMOUS_VALUE));
	;}
    break;

  case 100:
#line 994 "src/rulesyacc.y"
    {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::VARIABLE, *(yyvsp[(1) - (1)].bits_slot)));
	  free((yyvsp[(1) - (1)].bits_slot));
	;}
    break;

  case 101:
#line 1000 "src/rulesyacc.y"
    {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot)=(yyvsp[(2) - (3)].statement_slot);
	;}
    break;

  case 102:
#line 1005 "src/rulesyacc.y"
    {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::LIST, *(yyvsp[(1) - (1)].list_slot)));
	  free((yyvsp[(1) - (1)].list_slot));
	;}
    break;

  case 103:
#line 1011 "src/rulesyacc.y"
    {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot)=(yyvsp[(1) - (1)].statement_slot);
	;}
    break;

  case 104:
#line 1016 "src/rulesyacc.y"
    {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, 
						  Statement::SEARCH, 
						  *(yyvsp[(3) - (4)].statement_slot)));
	  free((yyvsp[(3) - (4)].statement_slot));
	 ;}
    break;

  case 105:
#line 1025 "src/rulesyacc.y"
    {  
	  DBUGPRT("up");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::UP));
	;}
    break;

  case 106:
#line 1031 "src/rulesyacc.y"
    {  
	  DBUGPRT("updouble");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::UP2));
	;}
    break;

  case 107:
#line 1038 "src/rulesyacc.y"
    { 
	  DBUGPRT("down");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::DOWN, (unsigned int)(yyvsp[(2) - (2)].integer_slot)-1)); 
	;}
    break;

  case 108:
#line 1045 "src/rulesyacc.y"
    { 
	  DBUGPRT("dash_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::DASH, (unsigned int)((yyvsp[(2) - (4)].integer_slot)-1), (unsigned int)((yyvsp[(4) - (4)].integer_slot)-1))); 
	;}
    break;

  case 109:
#line 1051 "src/rulesyacc.y"
    { 
	  DBUGPRT("dash_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::DASH, (unsigned int)((yyvsp[(2) - (2)].integer_slot)-1))); 
	;}
    break;

  case 110:
#line 1057 "src/rulesyacc.y"
    {  
	  DBUGPRT("downdouble");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::DOWN2, (unsigned int)0)); 
	;}
    break;

  case 111:
#line 1063 "src/rulesyacc.y"
    { 
	  DBUGPRT("downdouble");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::DOWN2, (unsigned int)((yyvsp[(2) - (2)].integer_slot)-1))); 
	;}
    break;

  case 112:
#line 1073 "src/rulesyacc.y"
    {
	  DBUGPRT("features");
 	  (yyval.features_slot)=(yyvsp[(2) - (3)].features_slot);
	;}
    break;

  case 113:
#line 1079 "src/rulesyacc.y"
    {
	  DBUGPRT("features");
	  (yyval.features_slot) = new featuresPtr(Features::create());
	;}
    break;

  case 114:
#line 1086 "src/rulesyacc.y"
    {
	  DBUGPRT("feature_components");
	  (yyval.features_slot)=(yyvsp[(1) - (3)].features_slot); 
	  (*(yyval.features_slot))->add(*(yyvsp[(3) - (3)].feature_slot));
	  free((yyvsp[(3) - (3)].feature_slot));
	;}
    break;

  case 115:
#line 1094 "src/rulesyacc.y"
    {
	  DBUGPRT("features_components");
	  (yyval.features_slot) = new featuresPtr(Features::create());
	  (*(yyval.features_slot))->add(*(yyvsp[(1) - (1)].feature_slot));
	  free((yyvsp[(1) - (1)].feature_slot));
	;}
    break;

  case 116:
#line 1103 "src/rulesyacc.y"
    {
	  DBUGPRT("features_components");
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

  case 117:
#line 1118 "src/rulesyacc.y"
    {
	  DBUGPRT("features_components");
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

  case 118:
#line 1134 "src/rulesyacc.y"
    {
	  DBUGPRT("feature");
	  (yyval.feature_slot) = new featurePtr(Feature::create(Feature::PRED, bitsetPtr(), Value::create(Value::CODE, *(yyvsp[(3) - (3)].string_slot))));
	;}
    break;

  case 119:
#line 1141 "src/rulesyacc.y"
    {
	  DBUGPRT("feature");
	  (yyval.feature_slot) = new featurePtr(Feature::create(Feature::PRED, bitsetPtr(), Value::create(Value::VARIABLE, *(yyvsp[(3) - (3)].bits_slot))));
	  free((yyvsp[(3) - (3)].bits_slot));
	;}
    break;

  case 120:
#line 1149 "src/rulesyacc.y"
    {
	  DBUGPRT("feature");
	  (yyval.feature_slot) = new featurePtr(Feature::create(Feature::FORM, bitsetPtr(), Value::create(Value::VARIABLE, *(yyvsp[(3) - (3)].bits_slot))));
	  free((yyvsp[(3) - (3)].bits_slot));
	;}
    break;

  case 121:
#line 1156 "src/rulesyacc.y"
    {
	  DBUGPRT("feature");
	  (yyval.feature_slot) = new featurePtr(Feature::create(Feature::FORM, bitsetPtr(), Value::create(Value::STR, *(yyvsp[(3) - (3)].string_slot))));
	;}
    break;

  case 122:
#line 1162 "src/rulesyacc.y"
    {
	  DBUGPRT("feature");
	  (yyval.feature_slot) = new featurePtr(Feature::create(Feature::CONSTANT, *(yyvsp[(1) - (3)].bits_slot), *(yyvsp[(3) - (3)].value_slot)));
	  free((yyvsp[(1) - (3)].bits_slot));
	  free((yyvsp[(3) - (3)].value_slot));
	;}
    break;

  case 123:
#line 1170 "src/rulesyacc.y"
    {
	  DBUGPRT("feature");
	  (yyval.feature_slot) = new featurePtr(Feature::create(Feature::CONSTANT, *(yyvsp[(1) - (3)].bits_slot), Value::create(Value::STR, *(yyvsp[(3) - (3)].string_slot))));
	  free((yyvsp[(1) - (3)].bits_slot));
	;}
    break;

  case 124:
#line 1177 "src/rulesyacc.y"
    {
	  DBUGPRT("feature");
	  (yyval.feature_slot) = new featurePtr(Feature::create(Feature::VARIABLE, *(yyvsp[(1) - (3)].bits_slot), *(yyvsp[(3) - (3)].value_slot)));
	  free((yyvsp[(1) - (3)].bits_slot));
	  free((yyvsp[(3) - (3)].value_slot));
	;}
    break;

  case 125:
#line 1185 "src/rulesyacc.y"
    {
	  DBUGPRT("feature");
	  (yyval.feature_slot) = new featurePtr(Feature::create(Feature::VARIABLE, *(yyvsp[(1) - (1)].bits_slot), valuePtr()));
	  free((yyvsp[(1) - (1)].bits_slot));
	;}
    break;

  case 126:
#line 1193 "src/rulesyacc.y"
    {
	  DBUGPRT("feature_value");
	  (yyval.value_slot) = new valuePtr(Value::create(Value::VARIABLE, *(yyvsp[(1) - (1)].bits_slot)));
	  free((yyvsp[(1) - (1)].bits_slot));
	;}
    break;

  case 127:
#line 1200 "src/rulesyacc.y"
    {
	  DBUGPRT("feature_value");
	  (yyval.value_slot) = new valuePtr(Value::create(Value::CONSTANT, *(yyvsp[(1) - (1)].bits_slot)));
	  free((yyvsp[(1) - (1)].bits_slot));
	;}
    break;

  case 128:
#line 1207 "src/rulesyacc.y"
    {
	  DBUGPRT("expression_statement");
	  (yyval.value_slot) = new valuePtr(Value::create(Value::NUMBER, (yyvsp[(1) - (1)].double_slot)));
	;}
    break;

  case 129:
#line 1213 "src/rulesyacc.y"
    {
	  DBUGPRT("expression_statement");
	  (yyval.value_slot) = new valuePtr(Value::create(Value::NUMBER, (double)(yyvsp[(1) - (1)].integer_slot)));
	;}
    break;

  case 130:
#line 1219 "src/rulesyacc.y"
    {
	  DBUGPRT("feature_value");
	  (yyval.value_slot) = new valuePtr(Value::create(Value::LIST, *(yyvsp[(1) - (1)].list_slot)));
	  free((yyvsp[(1) - (1)].list_slot));
	;}
    break;

  case 131:
#line 1226 "src/rulesyacc.y"
    {
	  DBUGPRT("feature_value");
	  (yyval.value_slot) = new valuePtr(Value::create(Value::FEATURES, *(yyvsp[(1) - (1)].features_slot)));
	  free((yyvsp[(1) - (1)].features_slot));
	;}
    break;

  case 132:
#line 1233 "src/rulesyacc.y"
    {
	  DBUGPRT("feature_value");
	  (yyval.value_slot) = new valuePtr(Value::NIL_VALUE);
	;}
    break;

  case 133:
#line 1239 "src/rulesyacc.y"
    {
	  DBUGPRT("feature_value");
	  (yyval.value_slot) = new valuePtr(Value::TRUE_VALUE);
	;}
    break;

  case 134:
#line 1245 "src/rulesyacc.y"
    {
	  DBUGPRT("feature_value");
	  (yyval.value_slot) = new valuePtr(Value::FALSE_VALUE);
	;}
    break;

  case 135:
#line 1251 "src/rulesyacc.y"
    {
	  DBUGPRT("feature_value");
	  (yyval.value_slot) = new valuePtr(Value::ANONYMOUS_VALUE);
	;}
    break;

  case 136:
#line 1258 "src/rulesyacc.y"
    {
	  DBUGPRT("constants");
	  (yyval.bits_slot)=(yyvsp[(1) - (1)].bits_slot);
	;}
    break;

  case 137:
#line 1264 "src/rulesyacc.y"
    {
	  DBUGPRT("constants");
	  (yyval.bits_slot)=(yyvsp[(1) - (3)].bits_slot);
	  (**(yyval.bits_slot)) |= (**(yyvsp[(3) - (3)].bits_slot));
	;}
    break;

  case 138:
#line 1272 "src/rulesyacc.y"
    {
	  DBUGPRT("identifier");
 	  (yyval.bits_slot) = new bitsetPtr(Bitset::create(Vartable::createVariable(*(yyvsp[(1) - (1)].string_slot))));
 	  free((yyvsp[(1) - (1)].string_slot));
	;}
    break;

  case 139:
#line 1280 "src/rulesyacc.y"
    {
	  DBUGPRT("variable");
	  std::ostringstream oss;
	  oss << *(yyvsp[(1) - (1)].string_slot);
  	  std::string str = oss.str();
	  (yyval.bits_slot) = new bitsetPtr(Bitset::create(Vartable::createVariable(str)));
	  free((yyvsp[(1) - (1)].string_slot));
	;}
    break;

  case 140:
#line 1291 "src/rulesyacc.y"
    {
	  DBUGPRT("list");
	  (yyval.list_slot) = (yyvsp[(2) - (3)].list_slot);
	;}
    break;

  case 141:
#line 1297 "src/rulesyacc.y"
    {
	  DBUGPRT("list");
	  (yyval.list_slot) = new listPtr(List::NIL_LIST);
	;}
    break;

  case 142:
#line 1303 "src/rulesyacc.y"
    {
	  DBUGPRT("list");
	  if ((*(yyvsp[(2) - (5)].list_slot))->isPairp() && (*(yyvsp[(2) - (5)].list_slot))->getCdr()->isNil())
	    (yyval.list_slot) = new listPtr(List::create((*(yyvsp[(2) - (5)].list_slot))->getCar(), *(yyvsp[(4) - (5)].list_slot)));
	  else
	    (yyval.list_slot) = new listPtr(List::create(*(yyvsp[(2) - (5)].list_slot), *(yyvsp[(4) - (5)].list_slot)));
	  free((yyvsp[(2) - (5)].list_slot));
	  free((yyvsp[(4) - (5)].list_slot));
	;}
    break;

  case 143:
#line 1314 "src/rulesyacc.y"
    {
	  DBUGPRT("list");
	  if ((*(yyvsp[(2) - (5)].list_slot))->isPairp() && (*(yyvsp[(2) - (5)].list_slot))->getCdr()->isNil())
	    (yyval.list_slot) = new listPtr(List::create((*(yyvsp[(2) - (5)].list_slot))->getCar(), List::NIL_LIST));
	  else
	    (yyval.list_slot) = new listPtr(List::create(*(yyvsp[(2) - (5)].list_slot), List::NIL_LIST));
	  free((yyvsp[(2) - (5)].list_slot));
	;}
    break;

  case 144:
#line 1325 "src/rulesyacc.y"
    {
	  DBUGPRT("list_elements");
	  (yyval.list_slot) = new listPtr(List::create(*(yyvsp[(1) - (3)].list_slot), *(yyvsp[(3) - (3)].list_slot)));
	  free((yyvsp[(1) - (3)].list_slot));
	  free((yyvsp[(3) - (3)].list_slot));
	;}
    break;

  case 145:
#line 1333 "src/rulesyacc.y"
    {
	  DBUGPRT("list_elements");
	  (yyval.list_slot) = new listPtr(List::create(*(yyvsp[(1) - (1)].list_slot), List::NIL_LIST));
	  free((yyvsp[(1) - (1)].list_slot));
	;}
    break;

  case 146:
#line 1341 "src/rulesyacc.y"
    {
	  DBUGPRT("list_element");
	  (yyval.list_slot) = new listPtr(List::create(Value::create(Value::VARIABLE, *(yyvsp[(1) - (1)].bits_slot))));
	  free((yyvsp[(1) - (1)].bits_slot));
	;}
    break;

  case 147:
#line 1348 "src/rulesyacc.y"
    {
	  DBUGPRT("expression_statement");
	  (yyval.list_slot) = new listPtr(List::create(Value::create(Value::NUMBER, (yyvsp[(1) - (1)].double_slot))));
	;}
    break;

  case 148:
#line 1354 "src/rulesyacc.y"
    {
	  DBUGPRT("expression_statement");
	  (yyval.list_slot) = new listPtr(List::create(Value::create(Value::NUMBER, (double)(yyvsp[(1) - (1)].integer_slot))));
	;}
    break;

  case 149:
#line 1360 "src/rulesyacc.y"
    {
	  DBUGPRT("list_element");
	  (yyval.list_slot) = new listPtr(List::create(Value::create(Value::CONSTANT, *(yyvsp[(1) - (1)].bits_slot))));
	  free((yyvsp[(1) - (1)].bits_slot));
	;}
    break;

  case 150:
#line 1367 "src/rulesyacc.y"
    {
	  DBUGPRT("list_element");
	  (yyval.list_slot) = new listPtr(List::create(Value::create(Value::FEATURES, *(yyvsp[(1) - (1)].features_slot))));
	  free((yyvsp[(1) - (1)].features_slot));
	;}
    break;

  case 151:
#line 1374 "src/rulesyacc.y"
    {
	  DBUGPRT("list_element");
	  (yyval.list_slot)=(yyvsp[(1) - (1)].list_slot);
	;}
    break;


/* Line 1267 of yacc.c.  */
#line 3403 "/Users/clement/workspace/elvex/src/rulesyacc.cc"
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


#line 1379 "src/rulesyacc.y"


