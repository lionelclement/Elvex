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
/* Line 1529 of yacc.c.  */
#line 218 "/Users/clement/Elvex/src/rulesyacc.hpp"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE ruleslval;

