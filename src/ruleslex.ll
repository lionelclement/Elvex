%{
/* **************************************************
 *
 * ELVEX
 *
 * Copyright 2019 LABRI, 
 * CNRS (UMR 5800), the University of Bordeaux,
 * and the Bordeaux INP
 *
 * Author: Lionel Clément,
 * Labri -- 351, cours de la Libération
 * 33405 Talence Cedex - France
 * lionel.clement@labri.fr
 * 
 * This file is part of ELVEX.
 *
 ************************************************** */

#include <iostream>
#include <sstream>
#include <string>
#include <bitset>
#include <vector>
#include <list>
#include "ipointer.hh"
#include "vartable.hh"
#include "synthesizer.hh"
#include "rulesyacc.hh"
#include "messages.hh"

#if false
#define DBUG(x)x
#else
#define DBUG(x)
#endif

#define DBUGPRT(x) DBUG(cerr << "*** " << x << "<BR>" << std::endl;);
#define DBUGPRTARG(x,s) DBUG(cerr << "*** " << x << "&nbsp;" << s << "<BR>" << std::endl);
  
  extern char *lexString;
  extern bool stringInput;
  extern Synthesizer synthesizer;
  
  std::string *str;
  int comments;

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

alphaMin [a-z]|à|á|â|ã|ä|å|æ|ç|è|é|ê|ë|ì|í|î|ï|ð|ñ|ò|ó|ô|õ|ö|ø|ù|ú|û|ü|ý|ÿ
alphaCap [A-Z]|À|Á|Â|Ã|Ä|Å|Æ|Ç|È|É|Ë|Ì|Í|Î|Ï|Ð|Ñ|Ò|Ó|Ô|Õ|Ö|Ø|Ù|Ú|Û|Ü|Ý|Ÿ|ß
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

%x INCLUDE COMMENT
 
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
  . ;
}

^\#include {BEGIN INCLUDE;}
<INCLUDE>{
	[ \t]* {}
	[^ \t\n]+ {
	  DBUGPRT("TOKEN_#INCLUDE\n");
	  synthesizer.pushBufferName(yytext);
	  synthesizer.pushLineno(ruleslineno);
	  ruleslineno=1;
	  yyin = fopen( yytext, "r" );
	  if ( ! yyin ){
	    std::cerr << "*** error -" << yytext << "- not found" << std::endl;
	    exit(1);
	  }
	  push_buffer();
	  BEGIN(INITIAL);
	}
	\n {}
}

<<EOF>> {
    yypop_buffer_state();
    if ( !YY_CURRENT_BUFFER ) {
      yyterminate();
    }
    else {
      synthesizer.popBufferName();
      ruleslineno = synthesizer.popLineno();
    }
}

<INITIAL>{
  {rightArrow} {
    DBUGPRT("TOKEN_RIGHTARROW\n");
    return TOKEN_RIGHTARROW;
  }
  
  {upArrow} {
    DBUGPRT("TOKEN_UPARROW\n");
    return TOKEN_UPARROW;
  }
  
  {upDoubleArrow} {
    DBUGPRT("TOKEN_UP2ARROW\n");
    return TOKEN_UP2ARROW;
  }
  
  {downArrow} {
    DBUGPRT("TOKEN_DOWNARROW\n");
    ruleslval.integer_slot = 1;
    return TOKEN_DOWNARROW;
  }
  
  {downDoubleArrow} {
    DBUGPRT("TOKEN_DOWN2ARROW\n");
    return TOKEN_DOWN2ARROW;
  }
  
  "<" {
    DBUGPRT("TOKEN_LT\n");
    return TOKEN_LT;
  }
  
  ">" {
    DBUGPRT("TOKEN_GT\n");
    return TOKEN_GT;
  }
  
  "≤"|"<=" {
    DBUGPRT("TOKEN_LE\n");
    return TOKEN_LT;
  }
  
  "≥"|">=" {
    DBUGPRT("TOKEN_GE\n");
    return TOKEN_GE;
  }
  
  "(" {
    DBUGPRT("TOKEN_LPAR\n");
    return TOKEN_LPAR;
  }
  
  ")" {
    DBUGPRT("TOKEN_RPAR\n");
    return TOKEN_RPAR;
  }
  
  "[" {
    DBUGPRT("TOKEN_LBRACKET\n");
    return TOKEN_LBRACKET;
  }
  
  "]" {
    DBUGPRT("TOKEN_RBRACKET\n");
    return TOKEN_RBRACKET;
  }
  
  "{" {
    DBUGPRT("TOKEN_LBRACE\n");
    return TOKEN_LBRACE;
  }
  
  "}" {
    DBUGPRT("TOKEN_RBRACE\n");
    return TOKEN_RBRACE;
  }
  
  ";" {
    DBUGPRT("TOKEN_SEMI\n");
    return TOKEN_SEMI;
  }
  
  "." {
    DBUGPRT("TOKEN_DOT\n");
    return TOKEN_DOT;
  }
  
  "::" {
    DBUGPRT("TOKEN_COLON2\n");
    return TOKEN_COLON2;
  }
  
  ":" {
    DBUGPRT("TOKEN_COLON\n");
    return TOKEN_COLON;
  }
  
  \# {
    DBUGPRT("TOKEN_DASH");
    return TOKEN_DASH;
  }
  
  "∪"|[Uu] {
    DBUGPRT("TOKEN_UNION\n");
    return TOKEN_UNION;
  }
  
  "⊂"|"<<" {
    DBUGPRT("TOKEN_SUBSUME\n");
    return TOKEN_SUBSUME;
  }
  
  "==" {
    DBUGPRT("TOKEN_EQUAL\n");
    return TOKEN_EQUAL;
  }
  
  "=" {
    DBUGPRT("TOKEN_AFF\n");
    return TOKEN_AFF;
  }
  
  "≠"|"!=" {
    DBUGPRT("TOKEN_DIFF\n");
    return TOKEN_DIFF;
  }
  
  "+" {
    DBUGPRT("TOKEN_PLUS\n");
    return TOKEN_PLUS;
  }
  
  "-" {
    DBUGPRT("TOKEN_MINUS\n");
    return TOKEN_MINUS;
  }
  
  "*" {
    DBUGPRT("TOKEN_TIMES\n");
    return TOKEN_TIMES;
  }
  
  "/" {
    DBUGPRT("TOKEN_DIVIDE\n");
    return TOKEN_DIVIDE;
  }
  
  "@input" {
    DBUGPRT("TOKEN_INPUT\n");
    return TOKEN_INPUT;
  }
  
  "@grammar" {
    DBUGPRT("TOKEN_GRAMMAR\n");
    return TOKEN_GRAMMAR;
  }
  
  "@lexicon" {
    DBUGPRT("TOKEN_LEXICON\n");
    return TOKEN_LEXICON;
  }
  
  "if" {
    DBUGPRT("TOKEN_IF\n");
    return TOKEN_IF;
  }
  
  "else" {
    DBUGPRT("TOKEN_ELSE\n");
    return TOKEN_ELSE;
  }
  
  "attest" {
    DBUGPRT("TOKEN_ATTEST\n");
    return TOKEN_ATTEST;
  }
  
  "print" {
    DBUGPRT("TOKEN_PRINT\n");
    return TOKEN_PRINT;
  }
  
  "println" {
    DBUGPRT("TOKEN_PRINTLN\n");
    return TOKEN_PRINTLN;
  }
  
  "sort" {
    DBUGPRT("TOKEN_SORT\n");
    return TOKEN_SORT;
  }
  
  "reverse" {
    DBUGPRT("TOKEN_REVERSE\n");
    return TOKEN_REVERSE;
  }
  
  "rand" {
    DBUGPRT("TOKEN_RAND\n");
    return TOKEN_RAND;
  }
  
  "with" {
    DBUGPRT("TOKEN_WITH\n");
    return TOKEN_WITH;
  }
  
  "combination" {
    DBUGPRT("TOKEN_COMBINATION\n");
    return TOKEN_COMBINATION;
  }
  
  "|" {
    DBUGPRT("TOKEN_PIPE\n");
    return TOKEN_PIPE;
  }
  
  "∨"|"||" {
    DBUGPRT("TOKEN_OR\n");
    return TOKEN_OR;
  }
  
  "∧"|"&&" {
    DBUGPRT("TOKEN_AND\n");
    return TOKEN_AND;
  }
  
  "⇒"|"=>" {
    DBUGPRT("TOKEN_IMPLICATION\n");
    return TOKEN_IMPLICATION;
  }
  
  "⇔"|"<=>" {
    DBUGPRT("TOKEN_EQUIV\n");
    return TOKEN_EQUIV;
  }
  
  "¬"|"!" {
    DBUGPRT("TOKEN_NOT\n");
    return TOKEN_NOT;
  }
  
  "∈" {
    DBUGPRT("TOKEN_INSET\n");
    return TOKEN_INSET;
  }
  


"," {
    DBUGPRT("TOKEN_COMMA\n");
    return TOKEN_COMMA;
  }
  
  "#" {
    DBUGPRT("TOKEN_DASH\n");
    return TOKEN_DASH;
  }
  
  "+" {
    DBUGPRT("TOKEN_PLUS\n");
    return TOKEN_PLUS;
  }
  
  "-" {
    DBUGPRT("TOKEN_MINUS\n");
    return TOKEN_MINUS;
  }
  
  "%" {
    DBUGPRT("TOKEN_MODULO\n");
    return TOKEN_MODULO;
  }
  
  "PRED" {
    DBUGPRT("TOKEN_PRED\n");
    return TOKEN_PRED;
  }
  
  "FORM" {
    DBUGPRT("TOKEN_FORM\n");
    return TOKEN_FORM;
  }
  
  "TRUE" {
    DBUGPRT("TOKEN_TRUE\n");
    return TOKEN_TRUE;
  }
  
  "NIL" {
    DBUGPRT("TOKEN_NILL\n");
    return TOKEN_NIL;
  }
  
  "__LINE__" {
    DBUGPRTARG("TOKEN_INTEGER ", yytext);
    ruleslval.integer_slot = yylineno;
    return TOKEN_INTEGER;
  }
  
  "__FILE__" {
    DBUGPRTARG("TOKEN_STRING ", yytext);
    ruleslval.string_slot = new std::string(synthesizer.getTopBufferName());
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
  
  {double} {
    DBUGPRTARG("TOKEN_DOUBLE ", yytext);
    sscanf(yytext, "%lf", &ruleslval.double_slot);
    return TOKEN_DOUBLE;
  }
  
  {string} {
    DBUGPRTARG("TOKEN_STRING ", yytext);
    std::string s = yytext;
    ruleslval.string_slot = new std::string(s.substr(1, s.length()-2));
    return TOKEN_STRING;
  }
  
  {blanks} {}
  
  \n {}
  
  . {
    DBUGPRTARG("OTHER TOKEN ", yytext);
    return (*yytext);
  }
}

%%

