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
 * LaBRI -- Université Bordeaux 
 * 351, cours de la Libération
 * 33405 Talence Cedex - France
 * lionel.clement@u-bordeaux.fr
 * 
 * This file is part of ELVEX.
 *
 ************************************************** */

//
// Morphological transformation for English
//

#include <iostream>
#define YY_NO_INPUT

%}

%option noyywrap

%s NEXT BEGINLINE

space		[ ]
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
  {space}+/[,?!.;:-] {}
  {space}[dD]o{space}+not { std::cout << yytext[0] << yytext[1] << "on't" ; }
  {space}[dD]oes{space}+not { std::cout << yytext[0] << yytext[1] << "oesn't" ; }
  {space}[dD]id{space}+not { std::cout << yytext[0] << yytext[1] << "idn't" ; }
  {space}[iI]s{space}+not { std::cout << yytext[0] << yytext[1] << "sn't" ; }
  {space}[wW]as{space}+not { std::cout << yytext[0] << yytext[1] << "asn't" ; }
  {space}[wW]ere{space}+not { std::cout << yytext[0] << yytext[1] << "eren't" ; }
  {space}[aA]re{space}+not { std::cout << yytext[0] << yytext[1] << "ren't" ; }
  {space}[hH]ave{space}+not { std::cout << yytext[0] << yytext[1] << "aven't" ; }
  {space}[hH]as{space}+not { std::cout << yytext[0] << yytext[1] << "asn't" ; }
  {space}[hH]ad{space}+not { std::cout << yytext[0] << yytext[1] << "adn't" ; }
  {space}[wW]ill{space}+not { std::cout << yytext[0] << yytext[1] << "on't" ; }
  \n {ECHO; BEGIN(INITIAL);}
}

%%

int main(){
    yylex();
    return 0;
}
