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
     TOKEN_DASH = 263,
     TOKEN_LPAR = 264,
     TOKEN_RPAR = 265,
     TOKEN_LBRACE = 266,
     TOKEN_RBRACE = 267,
     TOKEN_LBRACKET = 268,
     TOKEN_RBRACKET = 269,
     TOKEN_LEFT_DOUBLE_ANGLE_QUOTATION_MARK = 270,
     TOKEN_RIGHT_DOUBLE_ANGLE_QUOTATION_MARK = 271,
     TOKEN_SEMI = 272,
     TOKEN_COLON = 273,
     TOKEN_COLON2 = 274,
     TOKEN_COMMA = 275,
     TOKEN_DOT = 276,
     TOKEN_GRAMMAR = 277,
     TOKEN_INPUT = 278,
     TOKEN_LEXICON = 279,
     TOKEN_INPUTVALENCY = 280,
     TOKEN_PRED = 281,
     TOKEN_FORM = 282,
     TOKEN_ATTEST = 283,
     TOKEN_PRINT = 284,
     TOKEN_PRINTLN = 285,
     TOKEN_IF = 286,
     TOKEN_ELSE = 287,
     TOKEN_NIL = 288,
     TOKEN_TRUE = 289,
     TOKEN_SORT = 290,
     TOKEN_WITH = 291,
     TOKEN_REVERSE = 292,
     TOKEN_COMBINATION = 293,
     TOKEN_RAND = 294,
     TOKEN_UNION = 295,
     TOKEN_SUBSUME = 296,
     TOKEN_INSET = 297,
     TOKEN_AFF = 298,
     TOKEN_PIPE = 299,
     TOKEN_NOT = 300,
     TOKEN_OR = 301,
     TOKEN_AND = 302,
     TOKEN_IMPLICATION = 303,
     TOKEN_EQUIV = 304,
     TOKEN_PLUS = 305,
     TOKEN_MINUS = 306,
     TOKEN_TIMES = 307,
     TOKEN_DIVIDE = 308,
     TOKEN_MODULO = 309,
     TOKEN_EQUAL = 310,
     TOKEN_DIFF = 311,
     TOKEN_LT = 312,
     TOKEN_LE = 313,
     TOKEN_GT = 314,
     TOKEN_GE = 315,
     TOKEN_IDENTIFIER = 316,
     TOKEN_STRING = 317,
     TOKEN_INTEGER = 318,
     TOKEN_DOUBLE = 319,
     TOKEN_VARIABLE = 320,
     TOKEN_ANONYMOUS = 321,
     TOKEN_MINUS_U = 322,
     TOKEN_NOELSE = 323
   };
#endif
/* Tokens.  */
#define TOKEN_RIGHTARROW 258
#define TOKEN_UPARROW 259
#define TOKEN_UP2ARROW 260
#define TOKEN_DOWNARROW 261
#define TOKEN_DOWN2ARROW 262
#define TOKEN_DASH 263
#define TOKEN_LPAR 264
#define TOKEN_RPAR 265
#define TOKEN_LBRACE 266
#define TOKEN_RBRACE 267
#define TOKEN_LBRACKET 268
#define TOKEN_RBRACKET 269
#define TOKEN_LEFT_DOUBLE_ANGLE_QUOTATION_MARK 270
#define TOKEN_RIGHT_DOUBLE_ANGLE_QUOTATION_MARK 271
#define TOKEN_SEMI 272
#define TOKEN_COLON 273
#define TOKEN_COLON2 274
#define TOKEN_COMMA 275
#define TOKEN_DOT 276
#define TOKEN_GRAMMAR 277
#define TOKEN_INPUT 278
#define TOKEN_LEXICON 279
#define TOKEN_INPUTVALENCY 280
#define TOKEN_PRED 281
#define TOKEN_FORM 282
#define TOKEN_ATTEST 283
#define TOKEN_PRINT 284
#define TOKEN_PRINTLN 285
#define TOKEN_IF 286
#define TOKEN_ELSE 287
#define TOKEN_NIL 288
#define TOKEN_TRUE 289
#define TOKEN_SORT 290
#define TOKEN_WITH 291
#define TOKEN_REVERSE 292
#define TOKEN_COMBINATION 293
#define TOKEN_RAND 294
#define TOKEN_UNION 295
#define TOKEN_SUBSUME 296
#define TOKEN_INSET 297
#define TOKEN_AFF 298
#define TOKEN_PIPE 299
#define TOKEN_NOT 300
#define TOKEN_OR 301
#define TOKEN_AND 302
#define TOKEN_IMPLICATION 303
#define TOKEN_EQUIV 304
#define TOKEN_PLUS 305
#define TOKEN_MINUS 306
#define TOKEN_TIMES 307
#define TOKEN_DIVIDE 308
#define TOKEN_MODULO 309
#define TOKEN_EQUAL 310
#define TOKEN_DIFF 311
#define TOKEN_LT 312
#define TOKEN_LE 313
#define TOKEN_GT 314
#define TOKEN_GE 315
#define TOKEN_IDENTIFIER 316
#define TOKEN_STRING 317
#define TOKEN_INTEGER 318
#define TOKEN_DOUBLE 319
#define TOKEN_VARIABLE 320
#define TOKEN_ANONYMOUS 321
#define TOKEN_MINUS_U 322
#define TOKEN_NOELSE 323




/* Copy the first part of user declarations.  */
#line 1 "rulesyacc.yy"

/* **************************************************
 *
 * ELVEX
 *
 * Copyright 2019 LABRI, 
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

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <bitset>
#include "id.hh"
#include "vartable.hh"
#include "bitset.hh"
#include "grammar.hh"
#include "term.hh"
#include "entry.hh"
#include "entries.hh"
#include "synthesizer.hh"
#include "value.hh"
#include "feature.hh"
#include "features.hh"
#include "list.hh"
#include "statements.hh"
#include "statement.hh"
#include "terms.hh"
#include "messages.hh"
#include "ipointer.hh"

#if false
#define DBUG(x)x
#else
#define DBUG(x)
#endif
#define DBUGPRT(x) DBUG(cerr << "*** " << x << endl)
#define DBUGPRTARG(x,s) DBUG(cerr << "*** " << x << " " << s << endl)
  
 extern unsigned int ruleslineno;
 extern unsigned int ruleslex();
 extern Synthesizer synthesizer;
   
  void ruleserror(const char* str){
    try {
      std::ostringstream oss;
      oss << "error: " << str << " " << synthesizer.getTopBufferName() << " (" << ruleslineno << ")" << std::endl;
      throw oss.str();
    }
    catch (std::string msg) {
      std::cerr << msg << std::endl;
    }
  }
  
  void yywarning(const char* str){
    try {
      std::ostringstream oss;
      oss << "warning: " << str << " " << synthesizer.getTopBufferName() << " (" << ruleslineno << ")" << std::endl;
      throw oss.str();	     
    }
    catch (std::string msg) {
      std::cerr << msg << std::endl;
    }
  }
  
  std::list< std::string> argsCat;
  std::list< std::string> argsPred;
  unsigned int codeString; 
  
  unsigned int globalLineno;
  std::string globalBufferName;
  

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
#line 87 "rulesyacc.yy"
{
  int integer_slot;
  double double_slot;
  class Term *term_slot;
  class Terms *terms_slot; //(A|B)
  std::vector< class Terms * > *vector_terms_slot; // X Y
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
#line 345 "rulesyacc.cc"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 358 "rulesyacc.cc"

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
#define YYFINAL  22
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   560

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  69
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  42
/* YYNRULES -- Number of rules.  */
#define YYNRULES  143
/* YYNRULES -- Number of states.  */
#define YYNSTATES  233

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   323

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
      65,    66,    67,    68
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     8,    12,    15,    18,    21,    24,
      26,    28,    30,    34,    39,    43,    45,    49,    51,    54,
      56,    57,    61,    62,    64,    69,    73,    76,    78,    80,
      84,    88,    90,    92,    94,    98,   101,   103,   105,   108,
     112,   115,   117,   121,   125,   129,   132,   137,   142,   147,
     153,   161,   163,   165,   167,   169,   171,   173,   175,   177,
     179,   181,   187,   189,   193,   197,   201,   205,   208,   212,
     216,   220,   224,   228,   232,   236,   240,   244,   248,   252,
     255,   259,   261,   263,   265,   269,   271,   273,   275,   277,
     279,   281,   283,   285,   289,   294,   297,   302,   305,   308,
     310,   312,   314,   316,   319,   324,   327,   329,   332,   336,
     339,   343,   345,   349,   353,   357,   361,   365,   369,   373,
     375,   377,   379,   381,   383,   385,   387,   389,   391,   393,
     395,   399,   401,   403,   407,   410,   416,   420,   422,   424,
     426,   428,   430,   432
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      70,     0,    -1,    71,    -1,    22,    77,    -1,    23,    84,
     101,    -1,    23,    84,    -1,    24,    72,    -1,     8,   101,
      -1,    74,    72,    -1,    74,    -1,    61,    -1,    62,    -1,
      27,    61,    17,    -1,    27,    61,   101,    17,    -1,    73,
      75,    17,    -1,    17,    -1,    76,    44,    75,    -1,    76,
      -1,    61,   101,    -1,    61,    -1,    -1,    78,    80,    77,
      -1,    -1,    79,    -1,    84,     3,    81,    85,    -1,    84,
       3,    85,    -1,    81,    82,    -1,    82,    -1,    83,    -1,
      13,    83,    14,    -1,    83,    44,    84,    -1,    84,    -1,
      61,    -1,    65,    -1,    11,    86,    12,    -1,    11,    12,
      -1,    17,    -1,    88,    -1,    86,    88,    -1,    11,    86,
      12,    -1,    11,    12,    -1,    87,    -1,    28,    95,    17,
      -1,    29,    95,    17,    -1,    30,    95,    17,    -1,   101,
      17,    -1,    93,    43,    94,    17,    -1,    89,    41,    90,
      17,    -1,    91,    42,    92,    17,    -1,    31,     9,    95,
      10,    88,    -1,    31,     9,    95,    10,    88,    32,    88,
      -1,   101,    -1,   107,    -1,    96,    -1,   100,    -1,   101,
      -1,    98,    -1,    95,    -1,    97,    -1,    98,    -1,   107,
      -1,    57,   107,    19,   107,    59,    -1,    95,    -1,    95,
      46,    95,    -1,    95,    47,    95,    -1,    95,    48,    95,
      -1,    95,    49,    95,    -1,    45,    95,    -1,    95,    55,
      95,    -1,    95,    56,    95,    -1,    95,    57,    95,    -1,
      95,    58,    95,    -1,    95,    59,    95,    -1,    95,    60,
      95,    -1,    95,    50,    95,    -1,    95,    51,    95,    -1,
      95,    52,    95,    -1,    95,    53,    95,    -1,    95,    54,
      95,    -1,    51,    95,    -1,    39,     9,    10,    -1,    64,
      -1,    63,    -1,    62,    -1,    95,    40,    95,    -1,    96,
      -1,    97,    -1,    98,    -1,   100,    -1,   101,    -1,    33,
      -1,   105,    -1,   107,    -1,     9,    95,    10,    -1,    35,
     107,    36,   106,    -1,    35,   107,    -1,    35,   108,    36,
     106,    -1,    35,   108,    -1,    37,   107,    -1,   108,    -1,
      99,    -1,     4,    -1,     5,    -1,     6,    63,    -1,     8,
      63,    18,    63,    -1,     8,    63,    -1,     7,    -1,     7,
      63,    -1,    13,   102,    14,    -1,    13,    14,    -1,   102,
      20,   103,    -1,   103,    -1,    26,    18,    61,    -1,    26,
      18,   107,    -1,    27,    18,   107,    -1,    27,    18,    62,
      -1,   106,    18,   104,    -1,   106,    18,    62,    -1,   107,
      18,   104,    -1,   107,    -1,   107,    -1,   105,    -1,    64,
      -1,    63,    -1,   108,    -1,   101,    -1,    33,    -1,    34,
      -1,    66,    -1,   106,    -1,   106,    44,   105,    -1,    61,
      -1,    65,    -1,    57,   109,    59,    -1,    57,    59,    -1,
      57,   109,    19,   110,    59,    -1,   110,    20,   109,    -1,
     110,    -1,   107,    -1,    64,    -1,    63,    -1,   105,    -1,
     101,    -1,   108,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   179,   179,   185,   190,   198,   204,   208,   217,   221,
     226,   231,   238,   263,   290,   324,   330,   338,   347,   356,
     368,   368,   373,   373,   379,   393,   407,   413,   420,   425,
     433,   441,   448,   456,   468,   474,   479,   486,   494,   502,
     509,   516,   521,   527,   533,   539,   545,   597,   611,   624,
     634,   647,   655,   661,   666,   671,   679,   686,   693,   698,
     703,   709,   721,   731,   738,   745,   752,   765,   771,   778,
     785,   792,   799,   806,   816,   824,   832,   840,   848,   856,
     863,   869,   875,   881,   890,   897,   902,   907,   912,   917,
     923,   929,   935,   941,   946,   955,   963,   972,   980,   988,
     994,  1001,  1007,  1013,  1020,  1026,  1033,  1038,  1048,  1054,
    1062,  1070,  1081,  1088,  1096,  1103,  1109,  1117,  1124,  1133,
    1142,  1149,  1156,  1162,  1168,  1175,  1182,  1188,  1194,  1202,
    1208,  1216,  1224,  1236,  1242,  1248,  1261,  1269,  1278,  1285,
    1291,  1297,  1304,  1311
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TOKEN_RIGHTARROW", "TOKEN_UPARROW",
  "TOKEN_UP2ARROW", "TOKEN_DOWNARROW", "TOKEN_DOWN2ARROW", "TOKEN_DASH",
  "TOKEN_LPAR", "TOKEN_RPAR", "TOKEN_LBRACE", "TOKEN_RBRACE",
  "TOKEN_LBRACKET", "TOKEN_RBRACKET",
  "TOKEN_LEFT_DOUBLE_ANGLE_QUOTATION_MARK",
  "TOKEN_RIGHT_DOUBLE_ANGLE_QUOTATION_MARK", "TOKEN_SEMI", "TOKEN_COLON",
  "TOKEN_COLON2", "TOKEN_COMMA", "TOKEN_DOT", "TOKEN_GRAMMAR",
  "TOKEN_INPUT", "TOKEN_LEXICON", "TOKEN_INPUTVALENCY", "TOKEN_PRED",
  "TOKEN_FORM", "TOKEN_ATTEST", "TOKEN_PRINT", "TOKEN_PRINTLN", "TOKEN_IF",
  "TOKEN_ELSE", "TOKEN_NIL", "TOKEN_TRUE", "TOKEN_SORT", "TOKEN_WITH",
  "TOKEN_REVERSE", "TOKEN_COMBINATION", "TOKEN_RAND", "TOKEN_UNION",
  "TOKEN_SUBSUME", "TOKEN_INSET", "TOKEN_AFF", "TOKEN_PIPE", "TOKEN_NOT",
  "TOKEN_OR", "TOKEN_AND", "TOKEN_IMPLICATION", "TOKEN_EQUIV",
  "TOKEN_PLUS", "TOKEN_MINUS", "TOKEN_TIMES", "TOKEN_DIVIDE",
  "TOKEN_MODULO", "TOKEN_EQUAL", "TOKEN_DIFF", "TOKEN_LT", "TOKEN_LE",
  "TOKEN_GT", "TOKEN_GE", "TOKEN_IDENTIFIER", "TOKEN_STRING",
  "TOKEN_INTEGER", "TOKEN_DOUBLE", "TOKEN_VARIABLE", "TOKEN_ANONYMOUS",
  "TOKEN_MINUS_U", "TOKEN_NOELSE", "$accept", "axiom", "declaration",
  "dictionary", "stringOrIdentifier", "word", "lexical_entries",
  "lexical_entry", "rules", "@1", "@2", "rule", "terms_vector", "terms",
  "terms_disj", "term", "structure_statement", "list_statement",
  "statements", "statement", "left_hand_side_subset_statement",
  "right_hand_side_subset_statement", "left_hand_side_inset_statement",
  "right_hand_side_inset_statement", "left_hand_side_aff_statement",
  "right_hand_side_aff_statement", "expression_statement", "up",
  "updouble", "down", "dash_statement", "downdouble", "features",
  "features_components", "feature", "feature_value", "constant",
  "identifier", "variable", "list", "list_elements", "list_element", 0
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
     315,   316,   317,   318,   319,   320,   321,   322,   323
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    69,    70,    71,    71,    71,    71,    71,    72,    72,
      73,    73,    74,    74,    74,    74,    75,    75,    76,    76,
      78,    77,    79,    77,    80,    80,    81,    81,    82,    82,
      83,    83,    84,    84,    85,    85,    85,    86,    86,    87,
      87,    88,    88,    88,    88,    88,    88,    88,    88,    88,
      88,    89,    90,    90,    90,    90,    91,    92,    93,    93,
      93,    93,    94,    95,    95,    95,    95,    95,    95,    95,
      95,    95,    95,    95,    95,    95,    95,    95,    95,    95,
      95,    95,    95,    95,    95,    95,    95,    95,    95,    95,
      95,    95,    95,    95,    95,    95,    95,    95,    95,    95,
      95,    96,    97,    98,    99,    99,   100,   100,   101,   101,
     102,   102,   103,   103,   103,   103,   103,   103,   103,   103,
     104,   104,   104,   104,   104,   104,   104,   104,   104,   105,
     105,   106,   107,   108,   108,   108,   109,   109,   110,   110,
     110,   110,   110,   110
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     3,     2,     2,     2,     2,     1,
       1,     1,     3,     4,     3,     1,     3,     1,     2,     1,
       0,     3,     0,     1,     4,     3,     2,     1,     1,     3,
       3,     1,     1,     1,     3,     2,     1,     1,     2,     3,
       2,     1,     3,     3,     3,     2,     4,     4,     4,     5,
       7,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     5,     1,     3,     3,     3,     3,     2,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     2,
       3,     1,     1,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     4,     2,     4,     2,     2,     1,
       1,     1,     1,     2,     4,     2,     1,     2,     3,     2,
       3,     1,     3,     3,     3,     3,     3,     3,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     1,     1,     3,     2,     5,     3,     1,     1,     1,
       1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,    20,     0,     0,     0,     2,     0,     7,     3,
       0,    23,    32,    33,     5,    15,     0,    10,    11,     6,
       0,     9,     1,   109,     0,     0,   131,   132,     0,   111,
       0,   119,    20,     0,     4,     0,    19,     0,    17,     8,
       0,     0,   108,     0,     0,     0,    21,     0,    12,     0,
      18,    14,     0,   112,   113,   115,   114,   110,   126,   127,
       0,   117,   123,   122,   128,   125,   116,   121,   129,   120,
     124,   118,     0,     0,    36,     0,    27,    28,    31,    25,
      13,    16,   134,   140,   139,   142,   141,   138,   143,     0,
     137,     0,   102,     0,     0,    35,     0,     0,     0,     0,
       0,     0,    41,    37,     0,     0,     0,    58,    56,    51,
      60,     0,    26,    24,     0,     0,   133,     0,   130,   103,
      40,     0,   101,   106,     0,     0,    90,     0,     0,     0,
       0,     0,    83,    82,    81,     0,    85,    86,    87,   100,
      88,    89,    91,    92,    99,     0,     0,     0,     0,    34,
      38,     0,     0,     0,    45,    29,    30,     0,   136,    39,
     107,   105,     0,    95,    97,    98,     0,    67,    79,    42,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    43,    44,     0,     0,
       0,    53,    54,    55,    52,     0,    57,     0,    62,   135,
       0,    93,     0,     0,    80,    84,    63,    64,    65,    66,
      74,    75,    76,    77,    78,    68,    69,    70,    71,    72,
      73,     0,     0,    47,    48,    46,   104,    94,    96,    49,
      61,     0,    50
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     5,     6,    19,    20,    21,    37,    38,     9,    10,
      11,    32,    75,    76,    77,    78,    79,   101,   102,   103,
     104,   190,   105,   195,   106,   197,   135,   136,   137,   138,
     139,   140,   141,    28,    29,    66,   142,    68,   143,   144,
      89,    90
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -101
static const yytype_int16 yypact[] =
{
      64,    -8,    10,    15,     1,    17,  -101,   276,  -101,  -101,
      15,  -101,  -101,  -101,    -8,  -101,   -32,  -101,  -101,  -101,
     -31,     1,  -101,  -101,    30,    32,  -101,  -101,    47,  -101,
      37,    39,    10,    57,  -101,    72,    -8,    48,    20,  -101,
      54,    60,  -101,     5,    41,   261,  -101,    34,  -101,    61,
    -101,  -101,   -31,  -101,  -101,  -101,  -101,  -101,  -101,  -101,
     251,  -101,  -101,  -101,  -101,  -101,  -101,  -101,    50,  -101,
    -101,  -101,   210,    15,  -101,    34,  -101,    68,  -101,  -101,
    -101,  -101,  -101,  -101,  -101,  -101,  -101,  -101,  -101,   -13,
      53,    22,  -101,    38,   220,  -101,   129,   129,   129,    83,
      63,   231,  -101,  -101,    88,    90,    87,  -101,    96,   123,
    -101,     8,  -101,  -101,    15,   271,  -101,   271,  -101,  -101,
    -101,   241,  -101,    78,    80,   129,  -101,   -42,    63,   135,
     129,   129,  -101,  -101,  -101,   349,  -101,  -101,  -101,  -101,
    -101,  -101,  -101,  -101,  -101,   373,   394,   129,   126,  -101,
    -101,    12,   129,   129,  -101,  -101,  -101,    89,  -101,  -101,
    -101,   128,   303,   113,   115,  -101,   142,   478,  -101,  -101,
     129,   129,   129,   129,   129,   129,   129,   129,   129,   129,
     129,   129,   129,   129,   129,   129,  -101,  -101,   328,    63,
     138,  -101,  -101,  -101,  -101,   139,   415,   140,   415,  -101,
      95,  -101,    22,    22,  -101,   489,   457,   478,   436,   436,
      56,    56,   107,   107,  -101,   500,   500,   500,   500,   500,
     500,   252,   106,  -101,  -101,  -101,  -101,  -101,  -101,   141,
    -101,   252,  -101
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -101,  -101,  -101,   146,  -101,  -101,   118,  -101,   143,  -101,
    -101,  -101,  -101,    97,    98,     4,   102,    84,  -101,  -100,
    -101,  -101,  -101,  -101,  -101,  -101,    29,    33,   -68,   -52,
    -101,    36,    -1,  -101,   145,   144,   -33,    -5,    -4,   -36,
      66,    81
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -60
static const yytype_int16 yytable[] =
{
       8,   150,    30,    31,   107,     7,   115,    14,    70,    70,
     -22,    67,    67,    34,    33,    60,   122,    22,    15,   123,
     108,   150,   155,    27,    88,     7,   107,    86,    16,    35,
      36,    24,    25,   107,    49,    50,    54,    56,    30,    31,
      69,    69,   108,    65,    65,    72,   116,    73,    40,   108,
      41,    74,   114,   107,     7,    44,    87,    45,   118,    85,
      47,    42,    17,    18,    52,    51,    26,    43,   110,   108,
      27,   109,     1,   117,    58,    59,    12,    27,    80,    88,
      13,    88,    86,    26,    86,     7,     2,     3,     4,    48,
     110,   164,   147,   109,    91,    12,   148,   110,    60,    13,
     109,   119,    26,    61,    62,    63,    27,    64,   177,   178,
     179,    87,   114,    87,    85,    53,    85,   110,   156,    27,
     109,   229,    55,   163,   165,    27,   145,   146,    27,   151,
     153,   232,   152,   122,    92,    93,   123,   124,   125,   -59,
     154,   160,     7,   161,   166,   189,   200,   194,   199,   202,
     193,   203,   204,   107,   162,   223,   224,   225,   226,   167,
     168,   179,   126,   107,   127,   230,   128,    39,   129,   108,
      81,   111,   112,   231,   130,    46,   188,   113,   121,   108,
     131,   196,   198,   158,   191,   222,    60,   192,    57,    71,
      26,   132,   133,   134,    27,     0,   157,   227,   228,   205,
     206,   207,   208,   209,   210,   211,   212,   213,   214,   215,
     216,   217,   218,   219,   220,    92,    93,   110,     0,     0,
     109,    94,    95,     7,     0,    92,    93,   110,     0,     0,
     109,    94,   120,     7,     0,     0,    92,    93,    96,    97,
      98,    99,    94,   149,     7,     0,    92,    93,    96,    97,
      98,    99,    94,   159,     7,     0,     0,    92,    93,    96,
      97,    98,    99,    94,     7,     7,     0,   100,     0,    96,
      97,    98,    99,     0,     7,    27,     0,   100,     0,     0,
      96,    97,    98,    99,     7,    27,     0,     0,   100,     0,
      23,     0,     0,     0,    58,    59,    27,     0,   100,     0,
       0,     0,    24,    25,     0,     0,    27,     0,    60,   100,
      82,     0,    26,   201,    83,    84,    27,    27,    60,     0,
       0,     0,    26,     0,    62,    63,    27,    64,    60,     0,
       0,     0,    26,     0,    83,    84,    27,    26,   221,     0,
       0,    27,     0,   170,     0,     0,     0,     0,     0,   171,
     172,   173,   174,   175,   176,   177,   178,   179,   180,   181,
     182,   183,   184,   185,     0,     0,   169,     0,   170,     0,
       0,     0,     0,     0,   171,   172,   173,   174,   175,   176,
     177,   178,   179,   180,   181,   182,   183,   184,   185,   170,
     186,     0,     0,     0,     0,   171,   172,   173,   174,   175,
     176,   177,   178,   179,   180,   181,   182,   183,   184,   185,
       0,   187,     0,   170,     0,     0,     0,     0,     0,   171,
     172,   173,   174,   175,   176,   177,   178,   179,   180,   181,
     182,   183,   184,   185,   170,     0,     0,     0,     0,     0,
     171,   172,   173,   174,   175,   176,   177,   178,   179,   180,
     181,   182,   183,   184,   185,   170,     0,     0,     0,     0,
       0,   171,   172,   173,   174,   175,   176,   177,   178,   179,
     180,   181,   182,   183,   184,   185,   170,     0,     0,     0,
       0,     0,   171,   172,   -60,   -60,   175,   176,   177,   178,
     179,   180,   181,   182,   183,   184,   185,   170,     0,     0,
       0,     0,     0,     0,   172,     0,     0,   175,   176,   177,
     178,   179,   180,   181,   182,   183,   184,   185,   170,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   175,   176,
     177,   178,   179,   180,   181,   182,   183,   184,   185,   175,
     176,   177,   178,   179,   180,   181,   182,   183,   184,   185,
     175,   176,   177,   178,   179,   -60,   -60,   -60,   -60,   -60,
     -60
};

static const yytype_int16 yycheck[] =
{
       1,   101,     7,     7,    72,    13,    19,     3,    44,    45,
       0,    44,    45,    14,    10,    57,     4,     0,    17,     7,
      72,   121,    14,    65,    60,    13,    94,    60,    27,    61,
      61,    26,    27,   101,    35,    36,    40,    41,    43,    43,
      44,    45,    94,    44,    45,    11,    59,    13,    18,   101,
      18,    17,    44,   121,    13,    18,    60,    18,    91,    60,
       3,    14,    61,    62,    44,    17,    61,    20,    72,   121,
      65,    72,     8,    20,    33,    34,    61,    65,    17,   115,
      65,   117,   115,    61,   117,    13,    22,    23,    24,    17,
      94,   127,     9,    94,    44,    61,   100,   101,    57,    65,
     101,    63,    61,    62,    63,    64,    65,    66,    52,    53,
      54,   115,    44,   117,   115,    61,   117,   121,   114,    65,
     121,   221,    62,   127,   128,    65,    97,    98,    65,    41,
      43,   231,    42,     4,     5,     6,     7,     8,     9,    43,
      17,    63,    13,    63,     9,    19,    18,   151,    59,    36,
     151,    36,    10,   221,   125,    17,    17,    17,    63,   130,
     131,    54,    33,   231,    35,    59,    37,    21,    39,   221,
      52,    73,    75,    32,    45,    32,   147,    75,    94,   231,
      51,   152,   153,   117,   151,   189,    57,   151,    43,    45,
      61,    62,    63,    64,    65,    -1,   115,   202,   203,   170,
     171,   172,   173,   174,   175,   176,   177,   178,   179,   180,
     181,   182,   183,   184,   185,     5,     6,   221,    -1,    -1,
     221,    11,    12,    13,    -1,     5,     6,   231,    -1,    -1,
     231,    11,    12,    13,    -1,    -1,     5,     6,    28,    29,
      30,    31,    11,    12,    13,    -1,     5,     6,    28,    29,
      30,    31,    11,    12,    13,    -1,    -1,     5,     6,    28,
      29,    30,    31,    11,    13,    13,    -1,    57,    -1,    28,
      29,    30,    31,    -1,    13,    65,    -1,    57,    -1,    -1,
      28,    29,    30,    31,    13,    65,    -1,    -1,    57,    -1,
      14,    -1,    -1,    -1,    33,    34,    65,    -1,    57,    -1,
      -1,    -1,    26,    27,    -1,    -1,    65,    -1,    57,    57,
      59,    -1,    61,    10,    63,    64,    65,    65,    57,    -1,
      -1,    -1,    61,    -1,    63,    64,    65,    66,    57,    -1,
      -1,    -1,    61,    -1,    63,    64,    65,    61,    10,    -1,
      -1,    65,    -1,    40,    -1,    -1,    -1,    -1,    -1,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    -1,    -1,    17,    -1,    40,    -1,
      -1,    -1,    -1,    -1,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    40,
      17,    -1,    -1,    -1,    -1,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      -1,    17,    -1,    40,    -1,    -1,    -1,    -1,    -1,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    40,    -1,    -1,    -1,    -1,    -1,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    40,    -1,    -1,    -1,    -1,
      -1,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    40,    -1,    -1,    -1,
      -1,    -1,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    40,    -1,    -1,
      -1,    -1,    -1,    -1,    47,    -1,    -1,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    40,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     8,    22,    23,    24,    70,    71,    13,   101,    77,
      78,    79,    61,    65,    84,    17,    27,    61,    62,    72,
      73,    74,     0,    14,    26,    27,    61,    65,   102,   103,
     106,   107,    80,    84,   101,    61,    61,    75,    76,    72,
      18,    18,    14,    20,    18,    18,    77,     3,    17,   101,
     101,    17,    44,    61,   107,    62,   107,   103,    33,    34,
      57,    62,    63,    64,    66,   101,   104,   105,   106,   107,
     108,   104,    11,    13,    17,    81,    82,    83,    84,    85,
      17,    75,    59,    63,    64,   101,   105,   107,   108,   109,
     110,    44,     5,     6,    11,    12,    28,    29,    30,    31,
      57,    86,    87,    88,    89,    91,    93,    97,    98,   101,
     107,    83,    82,    85,    44,    19,    59,    20,   105,    63,
      12,    86,     4,     7,     8,     9,    33,    35,    37,    39,
      45,    51,    62,    63,    64,    95,    96,    97,    98,    99,
     100,   101,   105,   107,   108,    95,    95,     9,   107,    12,
      88,    41,    42,    43,    17,    14,    84,   110,   109,    12,
      63,    63,    95,   107,   108,   107,     9,    95,    95,    17,
      40,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    17,    17,    95,    19,
      90,    96,   100,   101,   107,    92,    95,    94,    95,    59,
      18,    10,    36,    36,    10,    95,    95,    95,    95,    95,
      95,    95,    95,    95,    95,    95,    95,    95,    95,    95,
      95,    10,   107,    17,    17,    17,    63,   106,   106,    88,
      59,    32,    88
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
#line 179 "rulesyacc.yy"
    {
	  DBUGPRT("axiom done...");
	  YYACCEPT;
	}
    break;

  case 3:
#line 185 "rulesyacc.yy"
    {
	  DBUGPRT("declaration grammar");
	  synthesizer.getGrammar().analyseTerms(synthesizer);
	}
    break;

  case 4:
#line 190 "rulesyacc.yy"
    {
	  DBUGPRT("declaration input");
	  synthesizer.setStartTerm((yyvsp[(2) - (3)].term_slot));
	  (*(yyvsp[(3) - (3)].features_slot))->renameVariables((*(yyvsp[(3) - (3)].features_slot))->getId());
	  synthesizer.setStartFeatures(*(yyvsp[(3) - (3)].features_slot));
	  free((yyvsp[(3) - (3)].features_slot));
	}
    break;

  case 5:
#line 198 "rulesyacc.yy"
    {
	  DBUGPRT("declaration input");
	  synthesizer.setStartTerm((yyvsp[(2) - (2)].term_slot));
	  synthesizer.setStartFeatures(Features::create());
	 }
    break;

  case 6:
#line 204 "rulesyacc.yy"
    {      
	  DBUGPRT("declaration lexicon");
	}
    break;

  case 7:
#line 209 "rulesyacc.yy"
    {
	  DBUGPRT("declaration features");
	  unsigned int pred = (*(yyvsp[(2) - (2)].features_slot))->assignPred();
	  synthesizer.setLocalEntry(Entry::create(0, pred, std::string(), *(yyvsp[(2) - (2)].features_slot)));
	  free((yyvsp[(2) - (2)].features_slot));
	}
    break;

  case 8:
#line 217 "rulesyacc.yy"
    {
	  DBUGPRT("dictionary");
	}
    break;

  case 9:
#line 221 "rulesyacc.yy"
    {
	  DBUGPRT("dictionary");
	 }
    break;

  case 10:
#line 226 "rulesyacc.yy"
    {
	  DBUGPRT("stringOrIdentifier");
	  (yyval.string_slot)=(yyvsp[(1) - (1)].string_slot);
	}
    break;

  case 11:
#line 231 "rulesyacc.yy"
    {
	  DBUGPRT("stringOrIdentifier");
	  (yyval.string_slot)=(yyvsp[(1) - (1)].string_slot);
	 }
    break;

  case 12:
#line 239 "rulesyacc.yy"
    {
	  DBUGPRT("word");
	  unsigned int code=Vartable::strToInt(*(yyvsp[(2) - (3)].string_slot));
	  free((yyvsp[(2) - (3)].string_slot));
	  // constantNoun => (0 => args)
	  std::map< unsigned int, std::map< unsigned int, entriesPtr > *>::iterator foundCode=synthesizer.getLexicon().find(code);
	  std::map< unsigned int, entriesPtr > *zeroToEntries;
	  if (foundCode!=synthesizer.getLexicon().end()){
	    zeroToEntries=foundCode->second;
	  } else {
	    zeroToEntries=new std::map< unsigned int, entriesPtr >;
	    synthesizer.getLexicon().insert(std::make_pair(code, zeroToEntries));
	  }
	  std::map< unsigned int, entriesPtr >::iterator foundPred=zeroToEntries->find(0);
	  entriesPtr lp;
	  if (foundPred!=zeroToEntries->end()){
	    lp=foundPred->second;
	  } else {
	    lp = Entries::create();
	    zeroToEntries->insert(std::make_pair(0, lp));
	  }
	  lp->add(Entry::create(code, UINT_MAX, std::string(), Features::create()));
	}
    break;

  case 13:
#line 264 "rulesyacc.yy"
    {
	  DBUGPRT("word");
	  unsigned int code=Vartable::strToInt(*(yyvsp[(2) - (4)].string_slot));
	  free((yyvsp[(2) - (4)].string_slot));
	  // constantNoun => (0 => args)
	  std::map< unsigned int, std::map< unsigned int, entriesPtr > *>::iterator foundCode=synthesizer.getLexicon().find(code);
	  std::map< unsigned int, entriesPtr > *zeroToEntries;
	  if (foundCode!=synthesizer.getLexicon().end()){
	    zeroToEntries=foundCode->second;
	  } else {
	    zeroToEntries=new std::map< unsigned int, entriesPtr >;
	    synthesizer.getLexicon().insert(std::make_pair(code, zeroToEntries));
	  }
	  std::map< unsigned int, entriesPtr >::iterator foundPred=zeroToEntries->find(0);
	  entriesPtr lp;
	  if (foundPred!=zeroToEntries->end()){
	    lp=foundPred->second;
	  } else {
	    lp=Entries::create();
	    zeroToEntries->insert(std::make_pair(0, lp));
	  }
	  lp->add(Entry::create(code, UINT_MAX, std::string(), *(yyvsp[(3) - (4)].features_slot)));
	  free((yyvsp[(3) - (4)].features_slot));
	}
    break;

  case 14:
#line 291 "rulesyacc.yy"
    {
	  DBUGPRT("word");
	  for (std::vector< entryPtr >::const_iterator entry = (*(yyvsp[(2) - (3)].entries_slot))->begin();
	       entry != (*(yyvsp[(2) - (3)].entries_slot))->end();
	       ++entry){
	    (*entry)->setForm(*(yyvsp[(1) - (3)].string_slot));
	    //}
	    //for (std::vector< entryPtr >::const_iterator entry = (*$2)->begin();
	    //    entry != (*$2)->end();
	    //   ++entry){
	    entriesPtr lp;
	    std::map< unsigned int, entriesPtr > *predToEntries;
	    //std::cerr << (*entry)->getCode() << std::endl;
	    std::map< unsigned int, std::map< unsigned int, entriesPtr > *>::iterator foundCode = synthesizer.getLexicon().find((*entry)->getCode());
	    if (foundCode != synthesizer.getLexicon().end()){
	      predToEntries = foundCode->second;
	    } else {
	      predToEntries = new std::map< unsigned int, entriesPtr >;
	      synthesizer.getLexicon().insert(std::make_pair((*entry)->getCode(), predToEntries));
	    }
	    std::map< unsigned int, entriesPtr >::iterator foundPred = predToEntries->find((*entry)->getCodePred());
	    if (foundPred != predToEntries->end()){
	      lp = foundPred->second;
	    } else {
	      lp = Entries::create();
	      predToEntries->insert(std::make_pair((*entry)->getCodePred(), lp));
	    }
	    lp->add(*entry);
	  }
	  free((yyvsp[(1) - (3)].string_slot));
	  free((yyvsp[(2) - (3)].entries_slot));
	}
    break;

  case 15:
#line 325 "rulesyacc.yy"
    {
	  DBUGPRT("word");
	}
    break;

  case 16:
#line 331 "rulesyacc.yy"
    {	  
	  DBUGPRT("lexical_entries");
	  (yyval.entries_slot)=(yyvsp[(3) - (3)].entries_slot); 
	  (*(yyval.entries_slot))->add(*(yyvsp[(1) - (3)].entry_slot));
	  free((yyvsp[(1) - (3)].entry_slot));
	}
    break;

  case 17:
#line 338 "rulesyacc.yy"
    {
	  DBUGPRT("lexical_entries");
	  (yyval.entries_slot)=new entriesPtr(Entries::create(*(yyvsp[(1) - (1)].entry_slot)));
	  free((yyvsp[(1) - (1)].entry_slot));
	 }
    break;

  case 18:
#line 348 "rulesyacc.yy"
    {
	  DBUGPRT("lexical_entry");
	  unsigned int pred = (*(yyvsp[(2) - (2)].features_slot))->assignPred();
	  (yyval.entry_slot)=new entryPtr(Entry::create(Vartable::strToInt(*(yyvsp[(1) - (2)].string_slot)), pred, std::string(), *(yyvsp[(2) - (2)].features_slot)));
	  free((yyvsp[(1) - (2)].string_slot));
	  free((yyvsp[(2) - (2)].features_slot));
	}
    break;

  case 19:
#line 357 "rulesyacc.yy"
    {
	  DBUGPRT("lexical_entry");
	  (yyval.entry_slot)=new entryPtr(Entry::create(Vartable::strToInt(*(yyvsp[(1) - (1)].string_slot)), UINT_MAX, std::string(), Features::create()));
	  free((yyvsp[(1) - (1)].string_slot));
	}
    break;

  case 20:
#line 368 "rulesyacc.yy"
    {globalLineno = ruleslineno; globalBufferName=synthesizer.getTopBufferName();}
    break;

  case 21:
#line 369 "rulesyacc.yy"
    {
	  DBUGPRT("rules"); 
	}
    break;

  case 22:
#line 373 "rulesyacc.yy"
    {globalLineno = ruleslineno; globalBufferName=synthesizer.getTopBufferName();}
    break;

  case 23:
#line 374 "rulesyacc.yy"
    {
	  DBUGPRT("rules"); 
	}
    break;

  case 24:
#line 380 "rulesyacc.yy"
    {
	  DBUGPRT("rule");
	  class Rule *rule = new Rule(globalLineno, globalBufferName, (yyvsp[(1) - (4)].term_slot), *(yyvsp[(3) - (4)].vector_terms_slot), (yyvsp[(4) - (4)].statements_slot) ? *(yyvsp[(4) - (4)].statements_slot) : statementsPtr());
	  rule->addDefaults();
	  synthesizer.getGrammar().addRule(rule);
	  if (!synthesizer.getGrammar().getStartTerm()){
	    synthesizer.getGrammar().setStartTerm((yyvsp[(1) - (4)].term_slot));
	  }
	  free((yyvsp[(3) - (4)].vector_terms_slot));
	  if ((yyvsp[(4) - (4)].statements_slot))
	     free((yyvsp[(4) - (4)].statements_slot));
	}
    break;

  case 25:
#line 394 "rulesyacc.yy"
    {
	  DBUGPRT("Rule");
	  class Rule *rule=new Rule(globalLineno, globalBufferName, (yyvsp[(1) - (3)].term_slot), (yyvsp[(3) - (3)].statements_slot) ? *(yyvsp[(3) - (3)].statements_slot) : statementsPtr());
	  rule->addDefaults();
	  synthesizer.getGrammar().addRule(rule);
	  if (!synthesizer.getGrammar().getStartTerm()){
	    synthesizer.getGrammar().setStartTerm((yyvsp[(1) - (3)].term_slot));
	  }
	  if ((yyvsp[(3) - (3)].statements_slot))
	    free((yyvsp[(3) - (3)].statements_slot));
	}
    break;

  case 26:
#line 407 "rulesyacc.yy"
    { 
	  DBUGPRT("term_vector");
	  (yyval.vector_terms_slot)=(yyvsp[(1) - (2)].vector_terms_slot);
	  (yyval.vector_terms_slot)->push_back((yyvsp[(2) - (2)].terms_slot));
	}
    break;

  case 27:
#line 413 "rulesyacc.yy"
    { 
	  DBUGPRT("term_vector"); 
	  (yyval.vector_terms_slot)=new std::vector< class Terms*>;
	  (yyval.vector_terms_slot)->push_back((yyvsp[(1) - (1)].terms_slot));
	}
    break;

  case 28:
#line 420 "rulesyacc.yy"
    { 
	  DBUGPRT("term");
	  (yyval.terms_slot)=(yyvsp[(1) - (1)].terms_slot);
	}
    break;

  case 29:
#line 425 "rulesyacc.yy"
    { 
	  DBUGPRT("term");
	  (yyval.terms_slot)=(yyvsp[(2) - (3)].terms_slot);
	  (yyval.terms_slot)->setOptional();
	  //$$->setFolded();
	}
    break;

  case 30:
#line 434 "rulesyacc.yy"
    { 
	  DBUGPRT("term_disj");
	  (yyval.terms_slot)=(yyvsp[(1) - (3)].terms_slot);
	  (yyval.terms_slot)->push_back((yyvsp[(3) - (3)].term_slot));
	  //$$->setFolded();
	}
    break;

  case 31:
#line 442 "rulesyacc.yy"
    { 
	  DBUGPRT("term_disj"); 
	  (yyval.terms_slot)=new Terms((yyvsp[(1) - (1)].term_slot));
	}
    break;

  case 32:
#line 449 "rulesyacc.yy"
    { 
	  DBUGPRT("term_id");
	  unsigned int code=Vartable::strToInt(*(yyvsp[(1) - (1)].string_slot));
	  (yyval.term_slot) = new Term(code);
	  free((yyvsp[(1) - (1)].string_slot));
	}
    break;

  case 33:
#line 457 "rulesyacc.yy"
    { 
	  DBUGPRT("term_id");
	  unsigned int code=Vartable::strToInt(*(yyvsp[(1) - (1)].string_slot));
	  (yyval.term_slot) = new Term(code);
	  free((yyvsp[(1) - (1)].string_slot));
	}
    break;

  case 34:
#line 469 "rulesyacc.yy"
    {
	  DBUGPRT("structure_statement");
	  (yyval.statements_slot)=(yyvsp[(2) - (3)].statements_slot);
	}
    break;

  case 35:
#line 475 "rulesyacc.yy"
    {
	  (yyval.statements_slot)=NULL;
	}
    break;

  case 36:
#line 480 "rulesyacc.yy"
    {
	  (yyval.statements_slot)=NULL;
	}
    break;

  case 37:
#line 487 "rulesyacc.yy"
    {
	  DBUGPRT("list_statement");
	  (yyval.statements_slot)=new statementsPtr(Statements::create());
	  (*(yyval.statements_slot))->addStatement(*(yyvsp[(1) - (1)].statement_slot));
	  free((yyvsp[(1) - (1)].statement_slot));
	}
    break;

  case 38:
#line 494 "rulesyacc.yy"
    {
	  DBUGPRT("list_statement");
	  (yyval.statements_slot)=(yyvsp[(1) - (2)].statements_slot);
	  (*(yyval.statements_slot))->addStatement(*(yyvsp[(2) - (2)].statement_slot));
	  free((yyvsp[(2) - (2)].statement_slot));
	}
    break;

  case 39:
#line 503 "rulesyacc.yy"
    {
	  DBUGPRT("statement");
	  (yyval.statement_slot)=new statementPtr(Statement::create(ruleslineno, Statement::STMS, *(yyvsp[(2) - (3)].statements_slot)));
	  free((yyvsp[(2) - (3)].statements_slot));
	}
    break;

  case 40:
#line 510 "rulesyacc.yy"
    {
	  DBUGPRT("statement");
	  (yyval.statement_slot)=new statementPtr(Statement::create(ruleslineno, Statement::STMS, Statements::create()));
	}
    break;

  case 41:
#line 516 "rulesyacc.yy"
    {
	  DBUGPRT("statement");
	  (yyval.statement_slot)=(yyvsp[(1) - (1)].statement_slot);
	 }
    break;

  case 42:
#line 521 "rulesyacc.yy"
    {
	  DBUGPRT("statement");
	  (yyval.statement_slot)=new statementPtr(Statement::create(ruleslineno, Statement::ATTEST, *(yyvsp[(2) - (3)].statement_slot)));
	  free((yyvsp[(2) - (3)].statement_slot));
	}
    break;

  case 43:
#line 527 "rulesyacc.yy"
    {
	  DBUGPRT("statement");
	  (yyval.statement_slot)=new statementPtr(Statement::create(ruleslineno, Statement::PRINT, *(yyvsp[(2) - (3)].statement_slot)));
	  free((yyvsp[(2) - (3)].statement_slot));
	}
    break;

  case 44:
#line 533 "rulesyacc.yy"
    {
	  DBUGPRT("statement");
	  (yyval.statement_slot)=new statementPtr(Statement::create(ruleslineno, Statement::PRINTLN, *(yyvsp[(2) - (3)].statement_slot)));
	  free((yyvsp[(2) - (3)].statement_slot));
	}
    break;

  case 45:
#line 539 "rulesyacc.yy"
    {
	  DBUGPRT("statement");
	  (yyval.statement_slot)=new statementPtr(Statement::create(ruleslineno, Statement::GUARD, *(yyvsp[(1) - (2)].features_slot)));
	  free((yyvsp[(1) - (2)].features_slot));
	}
    break;

  case 46:
#line 545 "rulesyacc.yy"
    {
	  DBUGPRT("statement");
	  (yyval.statement_slot)=new statementPtr(Statement::create(ruleslineno, Statement::AFF, *(yyvsp[(1) - (4)].statement_slot), *(yyvsp[(3) - (4)].statement_slot)));
	  // <X, …> = <…>
	  // <X, …> = sort …
	  // <X, …> = reverse …
	  // <X, …> = Z
	  if (((*(yyvsp[(1) - (4)].statement_slot))->getOp()==Statement::LIST) && (((*(yyvsp[(3) - (4)].statement_slot))->getOp()==Statement::LIST)||((*(yyvsp[(3) - (4)].statement_slot))->getOp()==Statement::SORT)||((*(yyvsp[(3) - (4)].statement_slot))->getOp()==Statement::REVERSE)||((*(yyvsp[(3) - (4)].statement_slot))->getOp()==Statement::VARIABLE)))
	    ;	  
	  // ↓i = X
	  // ↓i = […]
	  // ↓i = ↑
	  // ↓i = … ∪ …
	  // ↓i = ⇓j
	  else if (((*(yyvsp[(1) - (4)].statement_slot))->getOp()==Statement::DOWN) && (((*(yyvsp[(3) - (4)].statement_slot))->getOp()==Statement::VARIABLE)||((*(yyvsp[(3) - (4)].statement_slot))->getOp()==Statement::FEATURES)||((*(yyvsp[(3) - (4)].statement_slot))->getOp()==Statement::UP)||((*(yyvsp[(3) - (4)].statement_slot))->getOp()==Statement::UNIF)||((*(yyvsp[(3) - (4)].statement_slot))->getOp()==Statement::DOWN2)))
	    ;
	  // ⇑ = X
	  // ⇑ = […]
	  // ⇑ = ↑
	  // ⇑ = … ∪ …
	  // ⇑ = ⇓j
	  else if (((*(yyvsp[(1) - (4)].statement_slot))->getOp()==Statement::UP2) && (((*(yyvsp[(3) - (4)].statement_slot))->getOp()==Statement::VARIABLE)||((*(yyvsp[(3) - (4)].statement_slot))->getOp()==Statement::FEATURES)||((*(yyvsp[(3) - (4)].statement_slot))->getOp()==Statement::UP)||((*(yyvsp[(3) - (4)].statement_slot))->getOp()==Statement::UNIF)||((*(yyvsp[(3) - (4)].statement_slot))->getOp()==Statement::DOWN2)))
	    ;
	  // X = Y
	  // X = a
	  // X = <…>
	  // X = sort …
	  // X = reverse …
	  // X = […]
	  // X = ↑
	  // X = … ∪ …
	  // X = ⇓j
	  // X = <expr>
	  else if (((*(yyvsp[(1) - (4)].statement_slot))->getOp()==Statement::VARIABLE) 
		   &&(((*(yyvsp[(3) - (4)].statement_slot))->getOp()==Statement::VARIABLE)
		      ||((*(yyvsp[(3) - (4)].statement_slot))->getOp()==Statement::CONSTANT)
		      ||((*(yyvsp[(3) - (4)].statement_slot))->getOp()==Statement::LIST)
		      ||((*(yyvsp[(3) - (4)].statement_slot))->getOp()==Statement::SORT)
		      ||((*(yyvsp[(3) - (4)].statement_slot))->getOp()==Statement::REVERSE)
		      ||((*(yyvsp[(3) - (4)].statement_slot))->getOp()==Statement::FEATURES)
		      ||((*(yyvsp[(3) - (4)].statement_slot))->getOp()==Statement::UP)
		      ||((*(yyvsp[(3) - (4)].statement_slot))->getOp()==Statement::UNIF)
		      ||((*(yyvsp[(3) - (4)].statement_slot))->getOp()==Statement::DOWN2)
		      ||((*(yyvsp[(3) - (4)].statement_slot))->getOp()==Statement::DOUBLE)
		      ||((*(yyvsp[(3) - (4)].statement_slot))->getOp()==Statement::FCT)));
	  else {
	    yyerror((char*)"syntax error");
	  }
	  free((yyvsp[(1) - (4)].statement_slot));
	  free((yyvsp[(3) - (4)].statement_slot));
	}
    break;

  case 47:
#line 597 "rulesyacc.yy"
    {
	  DBUGPRT("statement");
	  (yyval.statement_slot)=new statementPtr(Statement::create(ruleslineno, Statement::SUBSUME, (*(yyvsp[(1) - (4)].statement_slot)), (*(yyvsp[(3) - (4)].statement_slot))));
	  // […] ⊂ ↑ 
	  // […] ⊂ ⇓j 
	  // […] ⊂ X 
	  if (((*(yyvsp[(1) - (4)].statement_slot))->getOp()==Statement::FEATURES) && (((*(yyvsp[(3) - (4)].statement_slot))->getOp()==Statement::UP)||((*(yyvsp[(3) - (4)].statement_slot))->getOp()==Statement::DOWN2)||((*(yyvsp[(3) - (4)].statement_slot))->getOp()==Statement::VARIABLE)))
	    ;
	  else 
	    yyerror((char *)"syntax error");
	  free((yyvsp[(1) - (4)].statement_slot));
	  free((yyvsp[(3) - (4)].statement_slot));
	}
    break;

  case 48:
#line 611 "rulesyacc.yy"
    {
	  DBUGPRT("statement");
	  (yyval.statement_slot)=new statementPtr(Statement::create(ruleslineno, Statement::INSET, (*(yyvsp[(1) - (4)].statement_slot)), (*(yyvsp[(3) - (4)].statement_slot))));
	  // ↓i ∈ <...>
	  if (((*(yyvsp[(1) - (4)].statement_slot))->getOp()==Statement::DOWN)
	       && (((*(yyvsp[(3) - (4)].statement_slot))->getOp()==Statement::LIST)))
	    ;
	    else 
	  yyerror((char *)"syntax error");
	  free((yyvsp[(1) - (4)].statement_slot));
	  free((yyvsp[(3) - (4)].statement_slot));
	}
    break;

  case 49:
#line 624 "rulesyacc.yy"
    {
	  DBUGPRT("statement");
	  (yyval.statement_slot)=new statementPtr(Statement::create(ruleslineno, 
						Statement::IF,
						(*(yyvsp[(3) - (5)].statement_slot)), 
						Statement::create(ruleslineno, Statement::THENELSE, (*(yyvsp[(5) - (5)].statement_slot)), statementPtr())));
	  free((yyvsp[(3) - (5)].statement_slot));
	  free((yyvsp[(5) - (5)].statement_slot));
	}
    break;

  case 50:
#line 634 "rulesyacc.yy"
    {
	  DBUGPRT("statement");
	  (yyval.statement_slot)=new statementPtr(Statement::create(ruleslineno, 
						Statement::IF, 
						(*(yyvsp[(3) - (7)].statement_slot)), 
						Statement::create(ruleslineno, Statement::THENELSE, (*(yyvsp[(5) - (7)].statement_slot)), (*(yyvsp[(7) - (7)].statement_slot)))));
	  free((yyvsp[(3) - (7)].statement_slot));
	  free((yyvsp[(5) - (7)].statement_slot));
	  free((yyvsp[(7) - (7)].statement_slot));
	}
    break;

  case 51:
#line 647 "rulesyacc.yy"
    {
	  DBUGPRT("left_hand_side_statement");
	  (yyval.statement_slot)=new statementPtr(Statement::create(ruleslineno, Statement::FEATURES, *(yyvsp[(1) - (1)].features_slot)));
	  free((yyvsp[(1) - (1)].features_slot));
	}
    break;

  case 52:
#line 655 "rulesyacc.yy"
    {
	  DBUGPRT("right_hand_side_subset_statement");
	  (yyval.statement_slot)=new statementPtr(Statement::create(ruleslineno, Statement::VARIABLE, *(yyvsp[(1) - (1)].bits_slot)));
	  free((yyvsp[(1) - (1)].bits_slot));
	}
    break;

  case 53:
#line 661 "rulesyacc.yy"
    {
	  DBUGPRT("right_hand_side_subset_statement");
	  (yyval.statement_slot)=(yyvsp[(1) - (1)].statement_slot);
	}
    break;

  case 54:
#line 666 "rulesyacc.yy"
    {
	  DBUGPRT("right_hand_side_subset_statement");
	  (yyval.statement_slot)=(yyvsp[(1) - (1)].statement_slot);
	}
    break;

  case 55:
#line 671 "rulesyacc.yy"
    {
	  DBUGPRT("right_hand_side_subset_statement");
	  (yyval.statement_slot)=new statementPtr(Statement::create(ruleslineno, Statement::FEATURES, *(yyvsp[(1) - (1)].features_slot)));
	  free((yyvsp[(1) - (1)].features_slot));
	}
    break;

  case 56:
#line 679 "rulesyacc.yy"
    {
	  DBUGPRT("left_hand_side_statement");
	  (yyval.statement_slot)=(yyvsp[(1) - (1)].statement_slot);
	}
    break;

  case 57:
#line 686 "rulesyacc.yy"
    {
	  DBUGPRT("right_hand_side_statement");
	  (yyval.statement_slot)=(yyvsp[(1) - (1)].statement_slot);
	}
    break;

  case 58:
#line 693 "rulesyacc.yy"
    {
	  DBUGPRT("left_hand_side_statement");
	  (yyval.statement_slot)=(yyvsp[(1) - (1)].statement_slot);
	}
    break;

  case 59:
#line 698 "rulesyacc.yy"
    {
	  DBUGPRT("left_hand_side_statement");
	  (yyval.statement_slot)=(yyvsp[(1) - (1)].statement_slot);
	}
    break;

  case 60:
#line 703 "rulesyacc.yy"
    {
	  DBUGPRT("left_hand_side_statement");
	  (yyval.statement_slot)=new statementPtr(Statement::create(ruleslineno, Statement::VARIABLE, *(yyvsp[(1) - (1)].bits_slot)));
	  free((yyvsp[(1) - (1)].bits_slot));
	 }
    break;

  case 61:
#line 710 "rulesyacc.yy"
    {
	  DBUGPRT("left_hand_side_statement");
	  (yyval.statement_slot)=new statementPtr(Statement::create(ruleslineno, Statement::LIST,
						List::create(List::create(Value::create(Value::VARIABLE, *(yyvsp[(2) - (5)].bits_slot))),
							     List::create(Value::create(Value::VARIABLE, *(yyvsp[(4) - (5)].bits_slot))))));
	  free((yyvsp[(2) - (5)].bits_slot));
	  free((yyvsp[(4) - (5)].bits_slot));
	}
    break;

  case 62:
#line 721 "rulesyacc.yy"
    {
	  DBUGPRT("right_hand_side_statement");
	  (yyval.statement_slot)=(yyvsp[(1) - (1)].statement_slot);
	}
    break;

  case 63:
#line 731 "rulesyacc.yy"
    {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot)=new statementPtr(Statement::create(ruleslineno, Statement::FCT, Statement::OR, (*(yyvsp[(1) - (3)].statement_slot)), (*(yyvsp[(3) - (3)].statement_slot))));
	  free((yyvsp[(1) - (3)].statement_slot));
	  free((yyvsp[(3) - (3)].statement_slot));
	}
    break;

  case 64:
#line 738 "rulesyacc.yy"
    {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot)=new statementPtr(Statement::create(ruleslineno, Statement::FCT, Statement::AND, (*(yyvsp[(1) - (3)].statement_slot)), (*(yyvsp[(3) - (3)].statement_slot))));
	  free((yyvsp[(1) - (3)].statement_slot));
	  free((yyvsp[(3) - (3)].statement_slot));
	}
    break;

  case 65:
#line 745 "rulesyacc.yy"
    {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot)=new statementPtr(Statement::create(ruleslineno, Statement::FCT, Statement::OR, Statement::create(ruleslineno, Statement::FCT, Statement::NOT, (*(yyvsp[(1) - (3)].statement_slot))), (*(yyvsp[(3) - (3)].statement_slot))));
	  free((yyvsp[(1) - (3)].statement_slot));
	  free((yyvsp[(3) - (3)].statement_slot));
	}
    break;

  case 66:
#line 752 "rulesyacc.yy"
    {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot)=new statementPtr(Statement::create(ruleslineno, Statement::FCT, Statement::AND,
						Statement::create(ruleslineno, Statement::FCT, Statement::OR,
								  Statement::create(ruleslineno, Statement::FCT, Statement::NOT, (*(yyvsp[(1) - (3)].statement_slot))),
								  (*(yyvsp[(3) - (3)].statement_slot))),
						Statement::create(ruleslineno, Statement::FCT, Statement::OR,
								  (*(yyvsp[(1) - (3)].statement_slot)),
								  Statement::create(ruleslineno, Statement::FCT, Statement::NOT, (*(yyvsp[(3) - (3)].statement_slot))))));
	  free((yyvsp[(1) - (3)].statement_slot));
	  free((yyvsp[(3) - (3)].statement_slot));
	}
    break;

  case 67:
#line 765 "rulesyacc.yy"
    {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot)=new statementPtr(Statement::create(ruleslineno, Statement::FCT, Statement::NOT, (*(yyvsp[(2) - (2)].statement_slot))));
	  free((yyvsp[(2) - (2)].statement_slot));
	}
    break;

  case 68:
#line 771 "rulesyacc.yy"
    {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot)=new statementPtr(Statement::create(ruleslineno, Statement::FCT, Statement::EQ, (*(yyvsp[(1) - (3)].statement_slot)), (*(yyvsp[(3) - (3)].statement_slot))));
	  free((yyvsp[(1) - (3)].statement_slot));
	  free((yyvsp[(3) - (3)].statement_slot));
	}
    break;

  case 69:
#line 778 "rulesyacc.yy"
    { 
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot)=new statementPtr(Statement::create(ruleslineno, Statement::FCT, Statement::DIFF, (*(yyvsp[(1) - (3)].statement_slot)), (*(yyvsp[(3) - (3)].statement_slot)))); 
	  free((yyvsp[(1) - (3)].statement_slot));
	  free((yyvsp[(3) - (3)].statement_slot));
	}
    break;

  case 70:
#line 785 "rulesyacc.yy"
    { 
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot)=new statementPtr(Statement::create(ruleslineno, Statement::FCT, Statement::LT, (*(yyvsp[(1) - (3)].statement_slot)), (*(yyvsp[(3) - (3)].statement_slot)))); 
	  free((yyvsp[(1) - (3)].statement_slot));
	  free((yyvsp[(3) - (3)].statement_slot));
	}
    break;

  case 71:
#line 792 "rulesyacc.yy"
    { 
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot)=new statementPtr(Statement::create(ruleslineno, Statement::FCT, Statement::LE, (*(yyvsp[(1) - (3)].statement_slot)), (*(yyvsp[(3) - (3)].statement_slot)))); 
	  free((yyvsp[(1) - (3)].statement_slot));
	  free((yyvsp[(3) - (3)].statement_slot));
	}
    break;

  case 72:
#line 799 "rulesyacc.yy"
    { 
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot)=new statementPtr(Statement::create(ruleslineno, Statement::FCT, Statement::GT, (*(yyvsp[(1) - (3)].statement_slot)), (*(yyvsp[(3) - (3)].statement_slot)))); 
	  free((yyvsp[(1) - (3)].statement_slot));
	  free((yyvsp[(3) - (3)].statement_slot));
	}
    break;

  case 73:
#line 806 "rulesyacc.yy"
    { 
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot)=new statementPtr(Statement::create(ruleslineno, Statement::FCT, Statement::GE, (*(yyvsp[(1) - (3)].statement_slot)), (*(yyvsp[(3) - (3)].statement_slot)))); 
	  free((yyvsp[(1) - (3)].statement_slot));
	  free((yyvsp[(3) - (3)].statement_slot));
	}
    break;

  case 74:
#line 817 "rulesyacc.yy"
    {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot)=new statementPtr(Statement::create(ruleslineno, Statement::FCT, Statement::PLUS, (*(yyvsp[(1) - (3)].statement_slot)), (*(yyvsp[(3) - (3)].statement_slot))));
	  free((yyvsp[(1) - (3)].statement_slot));
	  free((yyvsp[(3) - (3)].statement_slot));
	}
    break;

  case 75:
#line 825 "rulesyacc.yy"
    {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot)=new statementPtr(Statement::create(ruleslineno, Statement::FCT, Statement::MINUS, (*(yyvsp[(1) - (3)].statement_slot)), (*(yyvsp[(3) - (3)].statement_slot))));
	  free((yyvsp[(1) - (3)].statement_slot));
	  free((yyvsp[(3) - (3)].statement_slot));
	}
    break;

  case 76:
#line 833 "rulesyacc.yy"
    {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot)=new statementPtr(Statement::create(ruleslineno, Statement::FCT, Statement::TIMES, (*(yyvsp[(1) - (3)].statement_slot)), (*(yyvsp[(3) - (3)].statement_slot))));
	  free((yyvsp[(1) - (3)].statement_slot));
	  free((yyvsp[(3) - (3)].statement_slot));
	}
    break;

  case 77:
#line 841 "rulesyacc.yy"
    {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot)=new statementPtr(Statement::create(ruleslineno, Statement::FCT, Statement::DIVIDE, (*(yyvsp[(1) - (3)].statement_slot)), (*(yyvsp[(3) - (3)].statement_slot))));
	  free((yyvsp[(1) - (3)].statement_slot));
	  free((yyvsp[(3) - (3)].statement_slot));
	}
    break;

  case 78:
#line 849 "rulesyacc.yy"
    {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot)=new statementPtr(Statement::create(ruleslineno, Statement::FCT, Statement::MODULO, (*(yyvsp[(1) - (3)].statement_slot)), (*(yyvsp[(3) - (3)].statement_slot))));
	  free((yyvsp[(1) - (3)].statement_slot));
	  free((yyvsp[(3) - (3)].statement_slot));
	}
    break;

  case 79:
#line 857 "rulesyacc.yy"
    {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot)=new statementPtr(Statement::create(ruleslineno, Statement::FCT, Statement::MINUS_U, (*(yyvsp[(2) - (2)].statement_slot)), statementPtr()));
	  free((yyvsp[(2) - (2)].statement_slot));
	}
    break;

  case 80:
#line 864 "rulesyacc.yy"
    {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot)=new statementPtr(Statement::create(ruleslineno, Statement::FCT, Statement::RAND));
	}
    break;

  case 81:
#line 870 "rulesyacc.yy"
    {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot)=new statementPtr(Statement::create(ruleslineno, Statement::DOUBLE, (yyvsp[(1) - (1)].double_slot)));
	}
    break;

  case 82:
#line 876 "rulesyacc.yy"
    {
	  DBUGPRT("expression_statement");
 	  (yyval.statement_slot)=new statementPtr(Statement::create(ruleslineno, Statement::DOUBLE, (double)(yyvsp[(1) - (1)].integer_slot)));
	}
    break;

  case 83:
#line 882 "rulesyacc.yy"
    {
	  DBUGPRT("expression_statement");
 	  (yyval.statement_slot)=new statementPtr(Statement::create(ruleslineno, Statement::STR, *(yyvsp[(1) - (1)].string_slot)));
	}
    break;

  case 84:
#line 890 "rulesyacc.yy"
    {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot)=new statementPtr(Statement::create(ruleslineno, Statement::UNIF, (*(yyvsp[(1) - (3)].statement_slot)), (*(yyvsp[(3) - (3)].statement_slot))));
	  free((yyvsp[(1) - (3)].statement_slot));
	  free((yyvsp[(3) - (3)].statement_slot));
	}
    break;

  case 85:
#line 897 "rulesyacc.yy"
    {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot)=(yyvsp[(1) - (1)].statement_slot);
	}
    break;

  case 86:
#line 902 "rulesyacc.yy"
    {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot)=(yyvsp[(1) - (1)].statement_slot);
	}
    break;

  case 87:
#line 907 "rulesyacc.yy"
    {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot)=(yyvsp[(1) - (1)].statement_slot);
	}
    break;

  case 88:
#line 912 "rulesyacc.yy"
    {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot)=(yyvsp[(1) - (1)].statement_slot);
	}
    break;

  case 89:
#line 917 "rulesyacc.yy"
    {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot)=new statementPtr(Statement::create(ruleslineno, Statement::FEATURES, *(yyvsp[(1) - (1)].features_slot)));
	  free((yyvsp[(1) - (1)].features_slot));
	}
    break;

  case 90:
#line 924 "rulesyacc.yy"
    {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot)=new statementPtr(Statement::create(ruleslineno, Statement::NIL));
	}
    break;

  case 91:
#line 929 "rulesyacc.yy"
    {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot)=new statementPtr(Statement::create(ruleslineno, Statement::CONSTANT, *(yyvsp[(1) - (1)].bits_slot)));
	  free((yyvsp[(1) - (1)].bits_slot));
	}
    break;

  case 92:
#line 935 "rulesyacc.yy"
    {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot)=new statementPtr(Statement::create(ruleslineno, Statement::VARIABLE, *(yyvsp[(1) - (1)].bits_slot)));
	  free((yyvsp[(1) - (1)].bits_slot));
	}
    break;

  case 93:
#line 941 "rulesyacc.yy"
    {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot)=(yyvsp[(2) - (3)].statement_slot);
	}
    break;

  case 94:
#line 946 "rulesyacc.yy"
    {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot)=new statementPtr(Statement::create(ruleslineno, Statement::SORT,
						Statement::create(ruleslineno, Statement::VARIABLE, *(yyvsp[(2) - (4)].bits_slot)),
						Statement::create(ruleslineno, Statement::CONSTANT, *(yyvsp[(4) - (4)].bits_slot))));
	  free((yyvsp[(2) - (4)].bits_slot));
	  free((yyvsp[(4) - (4)].bits_slot));
	}
    break;

  case 95:
#line 955 "rulesyacc.yy"
    {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot)=new statementPtr(Statement::create(ruleslineno, Statement::SORT,
						Statement::create(ruleslineno, Statement::VARIABLE, *(yyvsp[(2) - (2)].bits_slot)),
						statementPtr()));
	  free((yyvsp[(2) - (2)].bits_slot));
	}
    break;

  case 96:
#line 963 "rulesyacc.yy"
    {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot)=new statementPtr(Statement::create(ruleslineno, Statement::SORT,
						Statement::create(ruleslineno, Statement::LIST, *(yyvsp[(2) - (4)].list_slot)), 
						Statement::create(ruleslineno, Statement::CONSTANT, *(yyvsp[(4) - (4)].bits_slot))));
	  free((yyvsp[(2) - (4)].list_slot));
	  free((yyvsp[(4) - (4)].bits_slot));
	}
    break;

  case 97:
#line 972 "rulesyacc.yy"
    {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot)=new statementPtr(Statement::create(ruleslineno, Statement::SORT,
						Statement::create(ruleslineno, Statement::LIST, *(yyvsp[(2) - (2)].list_slot)), 
						statementPtr()));
	  free((yyvsp[(2) - (2)].list_slot));
	}
    break;

  case 98:
#line 980 "rulesyacc.yy"
    {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot)=new statementPtr(Statement::create(ruleslineno, Statement::REVERSE,
						Statement::create(ruleslineno, Statement::VARIABLE, *(yyvsp[(2) - (2)].bits_slot)),
						statementPtr()));
	  free((yyvsp[(2) - (2)].bits_slot));
	}
    break;

  case 99:
#line 988 "rulesyacc.yy"
    {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot)=new statementPtr(Statement::create(ruleslineno, Statement::LIST, *(yyvsp[(1) - (1)].list_slot)));
	  free((yyvsp[(1) - (1)].list_slot));
	}
    break;

  case 100:
#line 994 "rulesyacc.yy"
    {
	  DBUGPRT("expression_statement");
	  (yyval.statement_slot)=(yyvsp[(1) - (1)].statement_slot);
	 }
    break;

  case 101:
#line 1001 "rulesyacc.yy"
    {  
	  DBUGPRT("up");
	  (yyval.statement_slot)=new statementPtr(Statement::create(ruleslineno, Statement::UP));
	}
    break;

  case 102:
#line 1007 "rulesyacc.yy"
    {  
	  DBUGPRT("updouble");
	  (yyval.statement_slot)=new statementPtr(Statement::create(ruleslineno, Statement::UP2));
	}
    break;

  case 103:
#line 1014 "rulesyacc.yy"
    { 
	  DBUGPRT("downSimple");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::DOWN, (unsigned int)(yyvsp[(2) - (2)].integer_slot)-1)); 
	}
    break;

  case 104:
#line 1021 "rulesyacc.yy"
    { 
	  DBUGPRT("dash_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::DASH, (unsigned int)((yyvsp[(2) - (4)].integer_slot)-1), (unsigned int)((yyvsp[(4) - (4)].integer_slot)-1))); 
	}
    break;

  case 105:
#line 1027 "rulesyacc.yy"
    { 
	  DBUGPRT("dash_statement");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::DASH, (unsigned int)((yyvsp[(2) - (2)].integer_slot)-1))); 
	}
    break;

  case 106:
#line 1033 "rulesyacc.yy"
    {  
	  DBUGPRT("downdouble");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::DOWN2, (unsigned int)0)); 
	}
    break;

  case 107:
#line 1039 "rulesyacc.yy"
    { 
	  DBUGPRT("downdouble");
	  (yyval.statement_slot) = new statementPtr(Statement::create(ruleslineno, Statement::DOWN2, (unsigned int)((yyvsp[(2) - (2)].integer_slot)-1))); 
	}
    break;

  case 108:
#line 1049 "rulesyacc.yy"
    {
	  DBUGPRT("features");
 	  (yyval.features_slot)=(yyvsp[(2) - (3)].features_slot);
	}
    break;

  case 109:
#line 1055 "rulesyacc.yy"
    {
	  DBUGPRT("features");
	  (yyval.features_slot)=new featuresPtr(Features::create());
	}
    break;

  case 110:
#line 1063 "rulesyacc.yy"
    {
	  DBUGPRT("feature_components");
	  (yyval.features_slot)=(yyvsp[(1) - (3)].features_slot); 
	  (*(yyval.features_slot))->addFeature(*(yyvsp[(3) - (3)].feature_slot));
	  free((yyvsp[(3) - (3)].feature_slot));
	}
    break;

  case 111:
#line 1071 "rulesyacc.yy"
    {
	  DBUGPRT("features_components");
	  (yyval.features_slot)=new featuresPtr(Features::create());
	  (*(yyval.features_slot))->addFeature(*(yyvsp[(1) - (1)].feature_slot));
	  free((yyvsp[(1) - (1)].feature_slot));
	}
    break;

  case 112:
#line 1082 "rulesyacc.yy"
    {
	  DBUGPRT("feature");
	  (yyval.feature_slot) = new featurePtr(Feature::create(Feature::PRED, bitsetPtr(), Value::create(Value::IDENTIFIER, *(yyvsp[(3) - (3)].string_slot))));
	}
    break;

  case 113:
#line 1089 "rulesyacc.yy"
    {
	  DBUGPRT("feature");
	  (yyval.feature_slot) = new featurePtr(Feature::create(Feature::PRED, bitsetPtr(), Value::create(Value::VARIABLE, *(yyvsp[(3) - (3)].bits_slot))));
	  free((yyvsp[(3) - (3)].bits_slot));
	}
    break;

  case 114:
#line 1097 "rulesyacc.yy"
    {
	  DBUGPRT("feature");
	  (yyval.feature_slot) = new featurePtr(Feature::create(Feature::FORM, bitsetPtr(), Value::create(Value::VARIABLE, *(yyvsp[(3) - (3)].bits_slot))));
	  free((yyvsp[(3) - (3)].bits_slot));
	}
    break;

  case 115:
#line 1104 "rulesyacc.yy"
    {
	  DBUGPRT("feature");
	  (yyval.feature_slot) = new featurePtr(Feature::create(Feature::FORM, bitsetPtr(), Value::create(Value::STR, *(yyvsp[(3) - (3)].string_slot))));
	}
    break;

  case 116:
#line 1110 "rulesyacc.yy"
    {
	  DBUGPRT("feature");
	  (yyval.feature_slot) = new featurePtr(Feature::create(Feature::CONSTANT, *(yyvsp[(1) - (3)].bits_slot), *(yyvsp[(3) - (3)].value_slot)));
	  free((yyvsp[(1) - (3)].bits_slot));
	  free((yyvsp[(3) - (3)].value_slot));
	}
    break;

  case 117:
#line 1118 "rulesyacc.yy"
    {
	  DBUGPRT("feature");
	  (yyval.feature_slot) = new featurePtr(Feature::create(Feature::CONSTANT, *(yyvsp[(1) - (3)].bits_slot), Value::create(Value::STR, *(yyvsp[(3) - (3)].string_slot))));
	  free((yyvsp[(1) - (3)].bits_slot));
	}
    break;

  case 118:
#line 1125 "rulesyacc.yy"
    {
	  DBUGPRT("feature");
	  //FATAL_ERROR;
	  (yyval.feature_slot) = new featurePtr(Feature::create(Feature::VARIABLE, *(yyvsp[(1) - (3)].bits_slot), *(yyvsp[(3) - (3)].value_slot)));
	  free((yyvsp[(1) - (3)].bits_slot));
	  free((yyvsp[(3) - (3)].value_slot));
	}
    break;

  case 119:
#line 1134 "rulesyacc.yy"
    {
	  DBUGPRT("feature");
	  (yyval.feature_slot) = new featurePtr(Feature::create(Feature::VARIABLE, *(yyvsp[(1) - (1)].bits_slot), valuePtr()));
	  free((yyvsp[(1) - (1)].bits_slot));
	}
    break;

  case 120:
#line 1143 "rulesyacc.yy"
    {
	  DBUGPRT("feature_value");
	  (yyval.value_slot)=new valuePtr(Value::create(Value::VARIABLE, *(yyvsp[(1) - (1)].bits_slot)));
	  free((yyvsp[(1) - (1)].bits_slot));
	}
    break;

  case 121:
#line 1150 "rulesyacc.yy"
    {
	  DBUGPRT("feature_value");
	  (yyval.value_slot)=new valuePtr(Value::create(Value::CONSTANT, *(yyvsp[(1) - (1)].bits_slot)));
	  free((yyvsp[(1) - (1)].bits_slot));
	}
    break;

  case 122:
#line 1157 "rulesyacc.yy"
    {
	  DBUGPRT("expression_statement");
	  (yyval.value_slot)=new valuePtr(Value::create(Value::DOUBLE, (yyvsp[(1) - (1)].double_slot)));
	}
    break;

  case 123:
#line 1163 "rulesyacc.yy"
    {
	  DBUGPRT("expression_statement");
	  (yyval.value_slot)=new valuePtr(Value::create(Value::DOUBLE, (double)(yyvsp[(1) - (1)].integer_slot)));
	}
    break;

  case 124:
#line 1169 "rulesyacc.yy"
    {
	  DBUGPRT("feature_value");
	  (yyval.value_slot)=new valuePtr(Value::create(Value::LIST, *(yyvsp[(1) - (1)].list_slot)));
	  free((yyvsp[(1) - (1)].list_slot));
	}
    break;

  case 125:
#line 1176 "rulesyacc.yy"
    {
	  DBUGPRT("feature_value");
	  (yyval.value_slot)=new valuePtr(Value::create(Value::FEATURES, *(yyvsp[(1) - (1)].features_slot)));
	  free((yyvsp[(1) - (1)].features_slot));
	}
    break;

  case 126:
#line 1183 "rulesyacc.yy"
    {
	  DBUGPRT("feature_value");
	  (yyval.value_slot)=new valuePtr(Value::_nil);
	}
    break;

  case 127:
#line 1189 "rulesyacc.yy"
    {
	  DBUGPRT("feature_value");
	  (yyval.value_slot)=new valuePtr(Value::_true);
	}
    break;

  case 128:
#line 1195 "rulesyacc.yy"
    {
	  DBUGPRT("variable");
	  (yyval.value_slot)=new valuePtr(Value::_anonymous);
	}
    break;

  case 129:
#line 1203 "rulesyacc.yy"
    {
	  DBUGPRT("constants");
	  (yyval.bits_slot)=(yyvsp[(1) - (1)].bits_slot);
	}
    break;

  case 130:
#line 1209 "rulesyacc.yy"
    {
	  DBUGPRT("constants");
	  (yyval.bits_slot)=(yyvsp[(1) - (3)].bits_slot);
	  (**(yyval.bits_slot)) |= (**(yyvsp[(3) - (3)].bits_slot));
	}
    break;

  case 131:
#line 1217 "rulesyacc.yy"
    {
	  DBUGPRT("identifier");
 	  (yyval.bits_slot)=new bitsetPtr(Bitset::create(Vartable::varTableAdd(*(yyvsp[(1) - (1)].string_slot))));
	  free((yyvsp[(1) - (1)].string_slot));
	}
    break;

  case 132:
#line 1225 "rulesyacc.yy"
    {
	  DBUGPRT("variable");
	  std::ostringstream oss;
	  oss << *(yyvsp[(1) - (1)].string_slot);
  	  std::string str = oss.str();
	  (yyval.bits_slot)=new bitsetPtr(Bitset::create(Vartable::varTableAdd(str)));
	  free((yyvsp[(1) - (1)].string_slot));
	}
    break;

  case 133:
#line 1237 "rulesyacc.yy"
    {
	  DBUGPRT("list");
	  (yyval.list_slot)=(yyvsp[(2) - (3)].list_slot);
	}
    break;

  case 134:
#line 1243 "rulesyacc.yy"
    {
	  DBUGPRT("list");
	  (yyval.list_slot)=new listPtr(List::nil);
	}
    break;

  case 135:
#line 1249 "rulesyacc.yy"
    {
	  DBUGPRT("list");
	  if ((*(yyvsp[(2) - (5)].list_slot))->isPairp() && (*(yyvsp[(2) - (5)].list_slot))->cdr()->isNil())
	    (yyval.list_slot)=new listPtr(List::create((*(yyvsp[(2) - (5)].list_slot))->car(), *(yyvsp[(4) - (5)].list_slot)));
	  else
	    (yyval.list_slot)=new listPtr(List::create(*(yyvsp[(2) - (5)].list_slot), *(yyvsp[(4) - (5)].list_slot)));
	  free((yyvsp[(2) - (5)].list_slot));
	  free((yyvsp[(4) - (5)].list_slot));
	}
    break;

  case 136:
#line 1262 "rulesyacc.yy"
    {
	  DBUGPRT("list_elements");
	  (yyval.list_slot)=new listPtr(List::create(*(yyvsp[(1) - (3)].list_slot), *(yyvsp[(3) - (3)].list_slot)));
	  free((yyvsp[(1) - (3)].list_slot));
	  free((yyvsp[(3) - (3)].list_slot));
	}
    break;

  case 137:
#line 1270 "rulesyacc.yy"
    {
	  DBUGPRT("list_elements");
	  (yyval.list_slot)=new listPtr(List::create(*(yyvsp[(1) - (1)].list_slot), List::nil));
	  free((yyvsp[(1) - (1)].list_slot));
	}
    break;

  case 138:
#line 1279 "rulesyacc.yy"
    {
	  DBUGPRT("list_element");
	  (yyval.list_slot)=new listPtr(List::create(Value::create(Value::VARIABLE, *(yyvsp[(1) - (1)].bits_slot))));
	  free((yyvsp[(1) - (1)].bits_slot));
	}
    break;

  case 139:
#line 1286 "rulesyacc.yy"
    {
	  DBUGPRT("expression_statement");
	  (yyval.list_slot)=new listPtr(List::create(Value::create(Value::DOUBLE, (yyvsp[(1) - (1)].double_slot))));
	}
    break;

  case 140:
#line 1292 "rulesyacc.yy"
    {
	  DBUGPRT("expression_statement");
	  (yyval.list_slot)=new listPtr(List::create(Value::create(Value::DOUBLE, (double)(yyvsp[(1) - (1)].integer_slot))));
	}
    break;

  case 141:
#line 1298 "rulesyacc.yy"
    {
	  DBUGPRT("list_element");
	  (yyval.list_slot)=new listPtr(List::create(Value::create(Value::CONSTANT, *(yyvsp[(1) - (1)].bits_slot))));
	  free((yyvsp[(1) - (1)].bits_slot));
	}
    break;

  case 142:
#line 1305 "rulesyacc.yy"
    {
	  DBUGPRT("list_element");
	  (yyval.list_slot)=new listPtr(List::create(Value::create(Value::FEATURES, *(yyvsp[(1) - (1)].features_slot))));
	  free((yyvsp[(1) - (1)].features_slot));
	}
    break;

  case 143:
#line 1312 "rulesyacc.yy"
    {
	  DBUGPRT("list_element");
	  (yyval.list_slot)=(yyvsp[(1) - (1)].list_slot);
	}
    break;


/* Line 1267 of yacc.c.  */
#line 3278 "rulesyacc.cc"
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


#line 1318 "rulesyacc.yy"


