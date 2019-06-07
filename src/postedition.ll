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

//
// Morphological transformation for French Language
//

#include <iostream>
%}

%option noyywrap

%s NEXT BEGINLINE

weakPonct	[,;:()'-]
strongPonct	[.!?/]
mesure		mm|cm|m|dm|km|m2|m3|A|[oO]hm|V|VA|gr|[kK]g

%%

<INITIAL>{
  [ \t] ;
  [[:lower:]] {
    char cpy = *yytext;
    unput(toupper(cpy));
    BEGIN(BEGINLINE);
  }
  à {std::string s = "À"; unput(s.c_str()[1]); unput(s.c_str()[0]); BEGIN(BEGINLINE);}
  â {std::string s = "Â"; unput(s.c_str()[1]); unput(s.c_str()[0]); BEGIN(BEGINLINE);}
  ä {std::string s = "Ä"; unput(s.c_str()[1]); unput(s.c_str()[0]); BEGIN(BEGINLINE);}
  é {std::string s = "É"; unput(s.c_str()[1]); unput(s.c_str()[0]); BEGIN(BEGINLINE);}
  è {std::string s = "È"; unput(s.c_str()[1]); unput(s.c_str()[0]); BEGIN(BEGINLINE);}
  ê {std::string s = "Ê"; unput(s.c_str()[1]); unput(s.c_str()[0]); BEGIN(BEGINLINE);}
  ë {std::string s = "Ë"; unput(s.c_str()[1]); unput(s.c_str()[0]); BEGIN(BEGINLINE);}
  î {std::string s = "Î"; unput(s.c_str()[1]); unput(s.c_str()[0]); BEGIN(BEGINLINE);}
  ï {std::string s = "Ï"; unput(s.c_str()[1]); unput(s.c_str()[0]); BEGIN(BEGINLINE);}
  ô {std::string s = "Ô"; unput(s.c_str()[1]); unput(s.c_str()[0]); BEGIN(BEGINLINE);}
  ô {std::string s = "Ö"; unput(s.c_str()[1]); unput(s.c_str()[0]); BEGIN(BEGINLINE);}
  û {std::string s = "Û"; unput(s.c_str()[1]); unput(s.c_str()[0]); BEGIN(BEGINLINE);}
  ü {std::string s = "Ü"; unput(s.c_str()[1]); unput(s.c_str()[0]); BEGIN(BEGINLINE);}
  . {yyless(0); BEGIN(BEGINLINE);}
}

<BEGINLINE>. {yyless(0); unput(' '); BEGIN(NEXT);}
	
<NEXT>{	
  \./[^0-9+-] {ECHO; BEGIN(INITIAL);}
  [^[:alpha:]][nNdDjJlL][ea][[:space:]]+/[hH]?([aAeEiIoOuUyY]|â|Â|à|À|é|É|è|È|ê|Ê|ë|Ë|î|Î|ï|Ï|ö|Ö|ô|Ô|ü|Ü|û|Û) {std::cout << yytext[0] << yytext[1] << '\'';}
  [^[:alpha:]][mMtTsS][e][[:space:]]+/[hH]?([aAeEiIoOuUyY]|â|Â|à|À|é|É|è|È|ê|Ê|ë|Ë|î|Î|ï|Ï|ö|Ö|ô|Ô|ü|Ü|û|Û) {std::cout << yytext[0] << yytext[1] << '\'';}
  [^[:alpha:]][mMtTsS][a][[:space:]]+/[hH]?([aAeEiIoOuUyY]|â|Â|à|À|é|É|è|È|ê|Ê|ë|Ë|î|Î|ï|Ï|ö|Ö|ô|Ô|ü|Ü|û|Û) {std::cout << yytext[0] << yytext[1] << "on ";}
  [^[:alpha:]][qQ]ue[[:space:]]+/[hH]?([aAeEiIoOuUyY]|â|Â|à|À|é|É|è|È|ê|Ê|ë|Ë|î|Î|ï|Ï|ö|Ö|ô|Ô|ü|Ü|û|Û) {std::cout << yytext[0] << "qu'";}
  [^[:alpha:]][bB]eau[[:space:]]+[aeiouy] {std::cout << yytext[0] << yytext[1] << yytext[2] << "l " << yytext[yyleng-1];}
  [^[:alpha:]][cC]e[[:space:]]+[aeiouy] {std::cout << yytext[0] << yytext[1] << "et " << yytext[yyleng-1];}
  [^[:alpha:]][cC]e[[:space:]]+(é|è|ê|ë|î|ï|ô|ö|ù) {std::cout << yytext[0] << yytext[1] << "et " << yytext[yyleng-2] << yytext[yyleng-1];}
  [^[:alpha:]][cC]e[[:space:]]+[hH][aeiouy] {std::cout << yytext[0] << yytext[1] << "et " << yytext[yyleng-2] << yytext[yyleng-1];}
  [^[:alpha:]][cC]e[[:space:]]+[hH](é|è|ê|ë|î|ï|ô|ö|ù) {std::cout << yytext[0] << yytext[1] << "et " << yytext[yyleng-3] << yytext[yyleng-2] << yytext[yyleng-1];}
  [^[:alpha:]][dD]e[[:space:]]+les/([[:space:]]|quel) {std::cout << yytext[0] << yytext[1] << "es";}
  [^[:alpha:]](à|À)[[:space:]]+les/([[:space:]]|quel) {std::cout << yytext[0] << "aux";}
  [^[:alpha:]][dD]e[[:space:]]+le/([[:space:]]|quel) {std::cout << yytext[0] << yytext[1] << 'u';}
  [^[:alpha:]](à|À)[[:space:]]+le/([[:space:]]|quel) {std::cout << yytext[0] << "au";}
  [^[:alpha:]](à|À)[[:space:]]+l[ea][[:space:]]+/[hH]?([aAeEiIoOuUyY]|â|Â|à|À|é|É|è|È|ê|Ê|ë|Ë|î|Î|ï|Ï|ö|Ö|ô|Ô|ü|Ü|û|Û) {std::cout << yytext[0] << "à l'";}
  [^[:alpha:]][sS]i[[:space:]]+[i] {std::cout << yytext[0] << yytext[1] << '\'' << yytext[yyleng-1];}
  [^[:alpha:]][dD]e[[:space:]]+des/[[:space:]] {std::cout << yytext[0] << yytext[1] << 'e';}
  [[:digit:]]+[[:space:]]/{mesure}[[:space:]] {yytext[yyleng-1]=0; ECHO;}
  [ \t]+/[,.;:-] {}
  [ \t]+ {std::cout << ' ';}
  \n {ECHO; BEGIN(INITIAL);}
  . {ECHO;}
}

%%

int main(int argn, char **argv){
    yylex();
    return 0;
}
