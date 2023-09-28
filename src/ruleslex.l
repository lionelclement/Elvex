%{
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

#include <iostream>
#include <bitset>
#include <string>
#include <sstream>
#include "parser.hpp"
#include "rulesyacc.hpp"
#include "messages.hpp"
#include "parser_exception.hpp"

#define YY_NO_INPUT

#ifndef DEBUGLEX
#define DEBUGLEX(x)
#else
#define DEBUGLEX(x)x
#endif

#define DBUGPRT(x) DEBUGLEX({std::cerr << "*** " << x << std::endl;})
#define DBUGPRTARG(x,s) DEBUGLEX({std::cerr << "*** " << x << ' ' << s << std::endl;})
  
  extern char *lexString;
  extern bool stringInput;
  extern Parser parser;
  
  int comments;
  std::stringstream strbuf;

  void init_buffer(){
    ruleslineno = 1;
  }
  
  void push_buffer() {
    yypush_buffer_state(yy_create_buffer( yyin, YY_BUF_SIZE ));
 }

  void delete_buffer() {
    yy_delete_buffer(YY_CURRENT_BUFFER);
  }
  
  void scan_string(std::string str) {
    yy_scan_string(str.c_str());
  }

%}

alphaMin [a-z]|à|á|â|ã|ä|å|æ|ç|è|é|ë|ê|ì|í|î|ï|ð|ñ|ò|ó|ô|õ|ö|ø|ù|ú|û|ü|ý|ÿ|ß
alphaCap [A-Z]|À|Á|Â|Ã|Ä|Å|Æ|Ç|È|É|Ë|Ê|Ì|Í|Î|Ï|Ð|Ñ|Ò|Ó|Ô|Õ|Ö|Ø|Ù|Ú|Û|Ü|Ý|Ÿ
alpha {alphaMin}|{alphaCap}
alphaNum [[:digit:]]|{alpha}|_
identifier {alpha}{alphaNum}*|[_]{alphaNum}+
variable "$"{identifier}
anonymous "_"
integer ([1-9][0-9]*)|0
double [+-]?{integer}(\.{integer})?([Ee][+-]?{integer})?
string \"([^\n\"]|\\\")*\"
blanks [[:blank:]\15]+
rightArrow "→"|"->"
upArrow "↑"
downArrow "↓"
upDoubleArrow "⇑"
downDoubleArrow "⇓"

%option nounput
%option yylineno
%option noyywrap

%x INCLUDE COMMENT STRING
 
%%

^.+$ {
	DBUGPRTARG("••••••••••••••• ", yytext);
	REJECT;
}

"//".*\n {
}

"/*" {comments=0; BEGIN COMMENT;}
<COMMENT>{
  \/\* {comments++;}
  \n {}
  \*\/ {if (!(comments--)) BEGIN INITIAL;} 
  . {}
}

^\#include {BEGIN INCLUDE;}
<INCLUDE>{
	[ \t]* {}
	[^ \t\n]+ {
	  DBUGPRT("TOKEN #INCLUDE");
	  parser.pushBufferName(yytext);
	  parser.pushLineno(ruleslineno);
	  ruleslineno = 1;
	  if (parser.getVerbose()) {
	    std::cerr << "open " << yytext << std::endl;
	  }
	  yyin = fopen( yytext, "r" );
	  if ( ! yyin ){
	    throw fatal_exception("can't open " + std::string(yytext));
	  }
	  push_buffer();
	  BEGIN INITIAL;
	}
	\n {}
}

\" {
  BEGIN STRING; 
  strbuf.str( std::string() );
  strbuf.clear(); 
  }
  
<STRING>{
  [^\\"\n]*   { strbuf << yytext; }
  \n         { strbuf << '\n'; }
  \\n         { strbuf << '\n'; }
  \\t         { strbuf << '\t'; }
  \\[0-7]*    { strbuf << strtol(yytext+1, 0, 8); }
  \\[\\"]     { strbuf << yytext[1]; }
  \"          { 
    ruleslval.string_slot = new std::string(strbuf.str());
    BEGIN INITIAL; 
    DBUGPRTARG("TOKEN_STRING ", strbuf.str());
    strbuf.clear(); 
    return TOKEN_STRING;}
  \\.         { throw parser_exception("*** error: bogus escape '" + std::string(yytext) + "' in string"); }
  \n          { throw parser_exception("*** error: newline in string"); }
}

<<EOF>> {
  yypop_buffer_state();
  if ( !YY_CURRENT_BUFFER ) {
    throw parser_exception("can't close current buffer");
    yyterminate();
  }
  else {
    if (parser.getVerbose()) {
      std::cerr << "close " << parser.getTopBufferName() << std::endl;
    }
    parser.popBufferName();
    ruleslineno = parser.popLineno();
  }
}

<INITIAL>{
  {rightArrow} {
    DBUGPRT("TOKEN_RIGHTARROW");
    return TOKEN_RIGHTARROW;
  }
  
  {upArrow} {
    DBUGPRT("TOKEN_UPARROW");
    return TOKEN_UPARROW;
  }
  
  {upDoubleArrow} {
    DBUGPRT("TOKEN_UP2ARROW");
    return TOKEN_UP2ARROW;
  }
  
  {downArrow} {
    DBUGPRT("TOKEN_DOWNARROW");
    ruleslval.integer_slot = 1;
    return TOKEN_DOWNARROW;
  }
  
  {downDoubleArrow} {
    DBUGPRT("TOKEN_DOWN2ARROW");
    return TOKEN_DOWN2ARROW;
  }
  
  "<" {
    DBUGPRT("TOKEN_LT");
    return TOKEN_LT;
  }
  
  ">" {
    DBUGPRT("TOKEN_GT");
    return TOKEN_GT;
  }
  
  "≤"|"<=" {
    DBUGPRT("TOKEN_LE");
    return TOKEN_LT;
  }
  
  "≥"|">=" {
    DBUGPRT("TOKEN_GE");
    return TOKEN_GE;
  }
  
  "(" {
    DBUGPRT("TOKEN_LPAR");
    return TOKEN_LPAR;
  }
  
  ")" {
    DBUGPRT("TOKEN_RPAR");
    return TOKEN_RPAR;
  }
  
  "[" {
    DBUGPRT("TOKEN_LBRACKET");
    return TOKEN_LBRACKET;
  }
  
  "]" {
    DBUGPRT("TOKEN_RBRACKET");
    return TOKEN_RBRACKET;
  }
  
  "{" {
    DBUGPRT("TOKEN_LBRACE");
    return TOKEN_LBRACE;
  }
  
  "}" {
    DBUGPRT("TOKEN_RBRACE");
    return TOKEN_RBRACE;
  }
  
  ";" {
    DBUGPRT("TOKEN_SEMI");
    return TOKEN_SEMI;
  }
  
  "::" {
    DBUGPRT("TOKEN_CONS");
    return TOKEN_CONS;
  }
  
  ":" {
    DBUGPRT("TOKEN_COLON");
    return TOKEN_COLON;
  }
  
  \. {
    DBUGPRT("TOKEN_DOT");
    return TOKEN_DOT;
  }
  
  \# {
    DBUGPRT("TOKEN_DASH");
    return TOKEN_DASH;
  }
  
  "∪"|[Uu] {
    DBUGPRT("TOKEN_UNIFY");
    return TOKEN_UNIFY;
  }
  
  "⊂"|"<<" {
    DBUGPRT("TOKEN_SUBSUME");
    return TOKEN_SUBSUME;
  }
  
  "==" {
    DBUGPRT("TOKEN_EQUAL");
    return TOKEN_EQUAL;
  }
  
  "=" {
    DBUGPRT("TOKEN_ASSIGNMENT");
    return TOKEN_ASSIGNMENT;
  }
  
  "≠"|"!=" {
    DBUGPRT("TOKEN_DIFF");
    return TOKEN_DIFF;
  }
  
  "+" {
    DBUGPRT("TOKEN_PLUS");
    return TOKEN_PLUS;
  }
  
  "-" {
    DBUGPRT("TOKEN_MINUS");
    return TOKEN_MINUS;
  }
  
  "*" {
    DBUGPRT("TOKEN_TIMES");
    return TOKEN_TIMES;
  }
  
  "/" {
    DBUGPRT("TOKEN_DIVIDE");
    return TOKEN_DIVIDE;
  }
  
  "@" {
    DBUGPRT("TOKEN_AROBASE");
    return TOKEN_AROBASE;
  }
  
  "@input" {
    DBUGPRT("TOKEN_INPUT");
    return TOKEN_INPUT;
  }
  
  "@rules" {
    DBUGPRT("TOKEN_RULES");
    return TOKEN_RULES;
  }
  
  "@lexicon" {
    DBUGPRT("TOKEN_LEXICON");
    return TOKEN_LEXICON;
  }
  
  "@trace" {
    DBUGPRT("TOKEN_TRACE");
    return TOKEN_TRACE;
  }
  
  "@withspaces" {
    DBUGPRT("TOKEN_WITH_SPACES");
    return TOKEN_WITH_SPACES;
  }
  
  "@bidirectional" {
    DBUGPRT("TOKEN_BIDIRECTIONAL");
    return TOKEN_BIDIRECTIONAL;
  }
  
  "@permutable" {
    DBUGPRT("TOKEN_PERMUTABLE");
    return TOKEN_PERMUTABLE;
  }
  
  "attest" {
    DBUGPRT("TOKEN_ATTEST");
    return TOKEN_ATTEST;
  }
  
  "if" {
    DBUGPRT("TOKEN_IF");
    return TOKEN_IF;
  }
  
  "else" {
    DBUGPRT("TOKEN_ELSE");
    return TOKEN_ELSE;
  }
  
  "deferred" {
    DBUGPRT("TOKEN_DEFERRED");
    return TOKEN_DEFERRED;
  }
  
  "print" {
    DBUGPRT("TOKEN_PRINT");
    return TOKEN_PRINT;
  }
  
  "println" {
    DBUGPRT("TOKEN_PRINTLN");
    return TOKEN_PRINTLN;
  }
  
  "printstderr" {
    DBUGPRT("TOKEN_STDERR_PRINT");
    return TOKEN_STDERR_PRINT;
  }
  
  "printlnstderr" {
    DBUGPRT("TOKEN_STDERR_PRINTLN");
    return TOKEN_STDERR_PRINTLN;
  }
  
  "search" {
    DBUGPRT("TOKEN_SEARCH");
    return TOKEN_SEARCH;
  }
  
  "rand" {
    DBUGPRT("TOKEN_RAND");
    return TOKEN_RAND;
  }
  
  "foreach" {
    DBUGPRT("TOKEN_FOREACH");
    return TOKEN_FOREACH;
  }
  
  "in" {
    DBUGPRT("TOKEN_IN");
    return TOKEN_IN;
  }
  
  "on" {
    DBUGPRT("TOKEN_ON");
    return TOKEN_ON;
  }
  
  "|" {
    DBUGPRT("TOKEN_PIPE");
    return TOKEN_PIPE;
  }
  
  "∨"|"||" {
    DBUGPRT("TOKEN_OR");
    return TOKEN_OR;
  }
  
  "∧"|"&&" {
    DBUGPRT("TOKEN_AND");
    return TOKEN_AND;
  }
  
  "⇒"|"=>" {
    DBUGPRT("TOKEN_IMPLICATION");
    return TOKEN_IMPLICATION;
  }
  
  "⇔"|"<=>" {
    DBUGPRT("TOKEN_EQUIV");
    return TOKEN_EQUIV;
  }
  
  "¬"|"!" {
    DBUGPRT("TOKEN_NOT");
    return TOKEN_NOT;
  }
  
  "," {
    DBUGPRT("TOKEN_COMMA");
    return TOKEN_COMMA;
  }
  
  "#" {
    DBUGPRT("TOKEN_DASH");
    return TOKEN_DASH;
  }
  
  "+" {
    DBUGPRT("TOKEN_PLUS");
    return TOKEN_PLUS;
  }
  
  "-" {
    DBUGPRT("TOKEN_MINUS");
    return TOKEN_MINUS;
  }
  
  "%" {
    DBUGPRT("TOKEN_MODULO");
    return TOKEN_MODULO;
  }
  
  "HEAD" {
    DBUGPRT("TOKEN_HEAD");
    return TOKEN_HEAD;
  }
  
  "LEMMA" {
    DBUGPRT("TOKEN_LEMMA");
    return TOKEN_LEMMA;
  }

  "FORM" {
    DBUGPRT("TOKEN_FORM");
    return TOKEN_FORM;
  }
  
  "TRUE" {
    DBUGPRT("TOKEN_TRUE");
    return TOKEN_TRUE;
  }
  
  "FALSE" {
    DBUGPRT("TOKEN_FALSE");
    return TOKEN_FALSE;
  }
  
  "NIL" {
    DBUGPRT("TOKEN_NILL");
    return TOKEN_NIL;
  }
  
  "__LINE__" {
    DBUGPRTARG("TOKEN_STRING ", yytext);
    //ruleslval.integer_slot = yylineno;
    ruleslval.string_slot = new std::string(std::to_string(yylineno));
    return TOKEN_STRING;
  }
  
  "__FILE__" {
    DBUGPRTARG("TOKEN_STRING ", yytext);
    ruleslval.string_slot = new std::string(parser.getTopBufferName());
    return TOKEN_STRING;
  }
  
  {identifier} {
    DBUGPRTARG("TOKEN_IDENTIFIER ", yytext);
    ruleslval.string_slot = new std::string(yytext);
    return TOKEN_IDENTIFIER;
  }
  
  {variable} {
    DBUGPRTARG("TOKEN_VARIABLE ", yytext);
    ruleslval.string_slot = new std::string(yytext);
    return TOKEN_VARIABLE;
  }
  
  {anonymous} {
    DBUGPRTARG("TOKEN_ANONYMOUS ", yytext);
    return TOKEN_ANONYMOUS;
  }
  
  {integer} {
    DBUGPRTARG("TOKEN_INTEGER ", yytext);
    sscanf(yytext, "%d", &ruleslval.integer_slot);
    return TOKEN_INTEGER;
  }
  
  d{double} {
    DBUGPRTARG("TOKEN_DOUBLE ", yytext);
    sscanf(yytext+1, "%lf", &ruleslval.double_slot);
    return TOKEN_DOUBLE;
  }
  
  {blanks} {}
  
  \n {}
  
  . {
    DBUGPRTARG("OTHER TOKEN ", yytext);
    return (*yytext);
  }
}

%%
