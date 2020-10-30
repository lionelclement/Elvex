%{
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

//
// Morphological transformation for French Language
//

#include <iostream>
#define YY_NO_INPUT

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
  . {yyless(0); BEGIN(BEGINLINE);}
}

<BEGINLINE>. {yyless(0); unput(' '); BEGIN(NEXT);}
	
<NEXT>{	
  \./[^0-9+-] {ECHO; BEGIN(INITIAL);}
  [[:space:]][nNdDjJlL][ea][[:space:]]+/[hH]?([aAeEiIoOuUyY]|â|Â|à|À|é|É|è|È|ê|Ê|ë|Ë|î|Î|ï|Ï|ö|Ö|ô|Ô|ü|Ü|û|Û) {std::cout << yytext[0] << yytext[1] << '\'';}
  [[:space:]][mMtTsS][e][[:space:]]+/[hH]?([aAeEiIoOuUyY]|â|Â|à|À|é|É|è|È|ê|Ê|ë|Ë|î|Î|ï|Ï|ö|Ö|ô|Ô|ü|Ü|û|Û) {std::cout << yytext[0] << yytext[1] << '\'';}
  [[:space:]][mMtTsS][a][[:space:]]+/[hH]?([aAeEiIoOuUyY]|â|Â|à|À|é|É|è|È|ê|Ê|ë|Ë|î|Î|ï|Ï|ö|Ö|ô|Ô|ü|Ü|û|Û) {std::cout << yytext[0] << yytext[1] << "on ";}
  [[:space:]][qQ]ue[[:space:]]+/[hH]?([aAeEiIoOuUyY]|â|Â|à|À|é|É|è|È|ê|Ê|ë|Ë|î|Î|ï|Ï|ö|Ö|ô|Ô|ü|Ü|û|Û) {std::cout << yytext[0] << "qu'";}
  [[:space:]][bB]eau[[:space:]]+[aeiouy] {std::cout << yytext[0] << yytext[1] << yytext[2] << "l " << yytext[yyleng-1];}
  [[:space:]][cC]e[[:space:]]+[aeiouy] {std::cout << yytext[0] << yytext[1] << "et " << yytext[yyleng-1];}
  [[:space:]][cC]e[[:space:]]+(é|è|ê|ë|î|ï|ô|ö|ù) {std::cout << yytext[0] << yytext[1] << "et " << yytext[yyleng-2] << yytext[yyleng-1];}
  [[:space:]][cC]e[[:space:]]+[hH][aeiouy] {std::cout << yytext[0] << yytext[1] << "et " << yytext[yyleng-2] << yytext[yyleng-1];}
  [[:space:]][cC]e[[:space:]]+[hH](é|è|ê|ë|î|ï|ô|ö|ù) {std::cout << yytext[0] << yytext[1] << "et " << yytext[yyleng-3] << yytext[yyleng-2] << yytext[yyleng-1];}
  [[:space:]][dD]e[[:space:]]+les/([[:space:]]|quel) {std::cout << yytext[0] << yytext[1] << "es";}
  [[:space:]](à|À)[[:space:]]+les/([[:space:]]|quel) {std::cout << yytext[0] << "aux";}
  [[:space:]][dD]e[[:space:]]+le/([[:space:]]|quel) {std::cout << yytext[0] << yytext[1] << 'u';}
  [[:space:]](à|À)[[:space:]]+le/[[:space:]] {std::cout << yytext[0] << "au";}
  [[:space:]](à|À)[[:space:]]+le/quel {std::cout << yytext[0] << "au";}
  [[:space:]](à|À)[[:space:]]+l[ea][[:space:]]+[hH]?/([aAeEiIoOuUyY]|â|Â|à|À|é|É|è|È|ê|Ê|ë|Ë|î|Î|ï|Ï|ö|Ö|ô|Ô|ü|Ü|û|Û) {std::cout << yytext[0] << "à l'";}
  [[:space:]][sS]i[[:space:]]+[i] {std::cout << yytext[0] << yytext[1] << '\'' << yytext[yyleng-1];}
  [[:space:]][dD]e[[:space:]]+des/[[:space:]] {std::cout << yytext[0] << yytext[1] << 'e';}
  [[:space:]][dD]e[[:space:]]+l[ea][[:space:]]+[hH]?/([aAeEiIoOuUyY]|â|Â|à|À|é|É|è|È|ê|Ê|ë|Ë|î|Î|ï|Ï|ö|Ö|ô|Ô|ü|Ü|û|Û) {std::cout << yytext[0] << "de l'";}
  [[:digit:]]+[[:space:]]/{mesure}[[:space:]] {yytext[yyleng-1]=0; ECHO;}
  [-][[:space:]]+ {yytext[yyleng-1]=0; ECHO;}
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
