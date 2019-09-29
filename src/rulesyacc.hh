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
     TOKEN_FOREACH = 290,
     TOKEN_IN = 291,
     TOKEN_SORT = 292,
     TOKEN_WITH = 293,
     TOKEN_REVERSE = 294,
     TOKEN_COMBINATION = 295,
     TOKEN_RAND = 296,
     TOKEN_UNION = 297,
     TOKEN_SUBSUME = 298,
     TOKEN_INSET = 299,
     TOKEN_AFF = 300,
     TOKEN_PIPE = 301,
     TOKEN_NOT = 302,
     TOKEN_OR = 303,
     TOKEN_AND = 304,
     TOKEN_IMPLICATION = 305,
     TOKEN_EQUIV = 306,
     TOKEN_PLUS = 307,
     TOKEN_MINUS = 308,
     TOKEN_TIMES = 309,
     TOKEN_DIVIDE = 310,
     TOKEN_MODULO = 311,
     TOKEN_EQUAL = 312,
     TOKEN_DIFF = 313,
     TOKEN_LT = 314,
     TOKEN_LE = 315,
     TOKEN_GT = 316,
     TOKEN_GE = 317,
     TOKEN_IDENTIFIER = 318,
     TOKEN_STRING = 319,
     TOKEN_INTEGER = 320,
     TOKEN_DOUBLE = 321,
     TOKEN_VARIABLE = 322,
     TOKEN_ANONYMOUS = 323,
     TOKEN_MINUS_U = 324,
     TOKEN_NOELSE = 325
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
#define TOKEN_FOREACH 290
#define TOKEN_IN 291
#define TOKEN_SORT 292
#define TOKEN_WITH 293
#define TOKEN_REVERSE 294
#define TOKEN_COMBINATION 295
#define TOKEN_RAND 296
#define TOKEN_UNION 297
#define TOKEN_SUBSUME 298
#define TOKEN_INSET 299
#define TOKEN_AFF 300
#define TOKEN_PIPE 301
#define TOKEN_NOT 302
#define TOKEN_OR 303
#define TOKEN_AND 304
#define TOKEN_IMPLICATION 305
#define TOKEN_EQUIV 306
#define TOKEN_PLUS 307
#define TOKEN_MINUS 308
#define TOKEN_TIMES 309
#define TOKEN_DIVIDE 310
#define TOKEN_MODULO 311
#define TOKEN_EQUAL 312
#define TOKEN_DIFF 313
#define TOKEN_LT 314
#define TOKEN_LE 315
#define TOKEN_GT 316
#define TOKEN_GE 317
#define TOKEN_IDENTIFIER 318
#define TOKEN_STRING 319
#define TOKEN_INTEGER 320
#define TOKEN_DOUBLE 321
#define TOKEN_VARIABLE 322
#define TOKEN_ANONYMOUS 323
#define TOKEN_MINUS_U 324
#define TOKEN_NOELSE 325




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
/* Line 1529 of yacc.c.  */
#line 208 "rulesyacc.hh"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE ruleslval;

