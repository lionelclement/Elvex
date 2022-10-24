%{
/* **************************************************
 *
 * ELVEX
 *
 * Copyright 2017 LABRI, 
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
using namespace std;
%}

%option noyywrap
%state KALABA GLOSS FRENCH

blank [ \t]

%%

<INITIAL>{
  #KALABA{blank}*	BEGIN KALABA;
  #GLOSS{blank}*	BEGIN GLOSS;
  #FRENCH{blank}*	BEGIN FRENCH;
  .|\n		;
}

<KALABA>{
  #GLOSS{blank}*	BEGIN GLOSS;
  \+{blank}+ ;
  {blank}+\+ ;
  \.\+{blank}+ ;
  {blank}+\+\. ;
  ((\.\+)|(\+\.))?{blank}*\{[^}]+\}{blank}* ;//std::cout << '[' << yytext << ']';
  \+ ;
  \. ;
  \\n{blank}*		    printf("\n");
}

<GLOSS>{
  #FRENCH{blank}*	BEGIN FRENCH;
  \+{blank}+ ;
  {blank}+\+ ;
  \.\+{blank}+(\{[^}]+\})?{blank}+ ;
  {blank}+\+\.(\{[^}]+\})? ;
  {blank}*\< printf("<");
  \\n{blank}*		    printf("\n");
}

<FRENCH>{
  \\n{blank}*		    printf("\n");
}

%%

int main(int argn, char **argv){
	yylex();
	return 0;
}
