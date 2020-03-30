%{
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

//
// Morphological transformation for English
//

#include <iostream>
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
  {space}+/[,?!.;:-] {}
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

int main(int argn, char **argv){
    yylex();
    return 0;
}
