/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

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




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 80 "src/rulesyacc.y"
{
  unsigned int integer_slot;
  double double_slot;
  termPtr *term_slot;
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
/* Line 1529 of yacc.c.  */
#line 202 "/Users/clement/workspace/elvex/src/rulesyacc.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE ruleslval;

