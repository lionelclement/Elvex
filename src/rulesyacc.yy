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

#include <sstream>
#include "vartable.hh"
#include "term.hh"
#include "terms.hh"
#include "entry.hh"
#include "entries.hh"
#include "parser.hh"
#include "bitset.hh"
#include "value.hh"
#include "feature.hh"
#include "features.hh"
#include "list.hh"
#include "statements.hh"

#include "statement.hh"
#include "terms.hh"
#include "messages.hh"
#include "rule.hh"
#include "ipointer.hh"

#if false
#define DBUG(x)x
#else
#define DBUG(x)
#endif
#define DBUGPRT(x) DBUG(std::cerr << "*** " << x << std::endl)
#define DBUGPRTARG(x,s) DBUG(std::cerr << "*** " << x << " " << s << std::endl)
  
 extern unsigned int ruleslineno;
 extern unsigned int ruleslex();
 extern Parser parser;
 unsigned int headLineno;
 bool headTrace;
   
  void ruleserror(const char *str) {
    try {
      std::ostringstream oss;
      oss << "error: " << str << " " << parser.getTopBufferName() << " (" << ruleslineno << ")" << std::endl;
      throw oss.str();
    }
    catch (std::string msg) {
      std::cerr << msg << std::endl;
    }
  }
  
  void yywarning(const char *str){
    try {
      std::ostringstream oss;
      oss << "warning: " << str << " " << parser.getTopBufferName() << " (" << ruleslineno << ")" << std::endl;
      throw oss.str();	     
    }
    catch (std::string msg) {
      std::cerr << msg << std::endl;
    }
  }
  
  %}

%union{
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

// ARROWS
%token TOKEN_RIGHTARROW TOKEN_UPARROW TOKEN_UP2ARROW TOKEN_DOWNARROW TOKEN_DOWN2ARROW 

// PAR
%token TOKEN_LPAR TOKEN_RPAR 
%token TOKEN_LBRACE TOKEN_RBRACE TOKEN_LBRACKET TOKEN_RBRACKET

// PONCT
%token TOKEN_DASH
%token TOKEN_AROBASE
%token TOKEN_SEMI TOKEN_DOT TOKEN_COLON TOKEN_DOUBLECOLON TOKEN_COMMA

// KEYWORDS
%token TOKEN_GRAMMAR TOKEN_INPUT TOKEN_LEXICON
%token TOKEN_PRED TOKEN_FORM
%token TOKEN_ATTEST TOKEN_PRINT TOKEN_PRINTLN
%token TOKEN_IF TOKEN_ELSE
%token TOKEN_NIL TOKEN_TRUE
%token TOKEN_FOREACH TOKEN_IN
%token TOKEN_SEARCH
%token TOKEN_RAND
%token TOKEN_TRACE

// OPERATORS
%token TOKEN_UNION TOKEN_SUBSUME TOKEN_INSET TOKEN_AFF TOKEN_PIPE TOKEN_NOT TOKEN_OR TOKEN_AND TOKEN_IMPLICATION TOKEN_EQUIV
TOKEN_PLUS TOKEN_MINUS TOKEN_TIMES TOKEN_DIVIDE TOKEN_MODULO
TOKEN_EQUAL TOKEN_DIFF TOKEN_LT TOKEN_LE TOKEN_GT TOKEN_GE

 // LITERALS
%token<string_slot> TOKEN_IDENTIFIER TOKEN_STRING

%token<integer_slot> TOKEN_INTEGER

%token<double_slot> TOKEN_DOUBLE 

 // VARIABLES
%token<string_slot> TOKEN_VARIABLE
%token TOKEN_ANONYMOUS

%type<string_slot> stringOrIdentifier
%type<term_slot> term
%type<terms_slot> terms terms_disj
%type<vector_terms_slot> terms_vector
%type<entries_slot> lexical_entries  
%type<entry_slot> lexical_entry

%type<features_slot> features features_components
%type<feature_slot> feature
%type<bits_slot> variable identifier constant
%type<value_slot> feature_value 
%type<list_slot> list list_elements list_element

%type<statements_slot> structure_statement list_statement
%type<statement_slot> statement statements left_hand_side_subset_statement right_hand_side_subset_statement left_hand_side_inset_statement right_hand_side_inset_statement left_hand_side_aff_statement right_hand_side_aff_statement up down updouble downdouble dash_statement
%type<statement_slot> expression_statement

%nonassoc TOKEN_IMPLICATION TOKEN_EQUIV
%left TOKEN_OR
%left TOKEN_AND
%right TOKEN_NOT
%left TOKEN_UNION
%nonassoc TOKEN_LT TOKEN_LE TOKEN_GT TOKEN_GE TOKEN_EQUAL TOKEN_DIFF
%left TOKEN_PLUS TOKEN_MINUS
%left TOKEN_TIMES TOKEN_DIVIDE
%left TOKEN_MODULO
%right TOKEN_MINUS_U
%nonassoc TOKEN_NOELSE 
%nonassoc TOKEN_ELSE 

%%

axiom:
	begin {
	  DBUGPRT("axiom done...");
	  YYACCEPT;
	};

begin:
	TOKEN_GRAMMAR rules {
	  DBUGPRT("begin grammar");
	}

	|TOKEN_INPUT term features {
	  DBUGPRT("begin input");
	  parser.setStartTerm(*$2);
	  (*$3)->_renameVariables((*$3)->getId());
	  parser.setStartFeatures(*$3);
	  free($3);
	}

	|TOKEN_INPUT term {
	  DBUGPRT("begin input");
	  parser.setStartTerm(*$2);
	  parser.setStartFeatures(Features::create());
	 }

	|TOKEN_LEXICON dictionary {      
	  DBUGPRT("begin lexicon");
	}

	|TOKEN_DASH features
	{
	  DBUGPRT("begin features");
	  parser.setLocalFeatures(*$2);
	  free($2);
	};

dictionary:
	dictionary_line dictionary {
	  DBUGPRT("dictionary");
	}

	|dictionary_line {
	  DBUGPRT("dictionary");
	 };

stringOrIdentifier:
	TOKEN_IDENTIFIER {
	  DBUGPRT("stringOrIdentifier");
	  $$=$1;
	}

	|TOKEN_STRING {
	  DBUGPRT("stringOrIdentifier");
	  $$=$1;
	 };

dictionary_line:
	// FORM constantNoun ;
	TOKEN_FORM TOKEN_IDENTIFIER TOKEN_SEMI
	{
	  DBUGPRT("dictionary_line");
	  unsigned int code=Vartable::strToInt(*$2);
	  free($2);
	  // constantNoun => (0 => args)
	  Parser::entries_map_map::iterator foundCode = parser.getLexicon().find(code);
	  Parser::entries_map *zeroToEntries;
	  if (foundCode != parser.getLexicon().end()){
	    zeroToEntries = foundCode->second;
	  } else {
	    zeroToEntries = new Parser::entries_map();
	    parser.getLexicon().insert(std::make_pair(code, zeroToEntries));
	  }
	  Parser::entries_map::iterator foundPred=zeroToEntries->find(0);
	  entriesPtr lp;
	  if (foundPred!=zeroToEntries->end()){
	    lp=foundPred->second;
	  } else {
	    lp = Entries::create();
	    zeroToEntries->insert(std::make_pair(0, lp));
	  }
	  lp->add(Entry::create(code, UINT_MAX, std::string(), Features::create()));
	}

	|TOKEN_FORM TOKEN_IDENTIFIER features TOKEN_SEMI
	{
	  DBUGPRT("dictionary_line");
	  unsigned int code=Vartable::strToInt(*$2);
	  free($2);
	  // constantNoun => (0 => args)
	  Parser::entries_map_map::iterator foundCode=parser.getLexicon().find(code);
	  Parser::entries_map *zeroToEntries;
	  if (foundCode!=parser.getLexicon().end()) {
	    zeroToEntries=foundCode->second;
	  } else {
	    zeroToEntries = new Parser::entries_map;
	    parser.getLexicon().insert(std::make_pair(code, zeroToEntries));
	  }
	  Parser::entries_map::iterator foundPred=zeroToEntries->find(0);
	  entriesPtr lp;
	  if (foundPred!=zeroToEntries->end()){
	    lp=foundPred->second;
	  } else {
	    lp=Entries::create();
	    zeroToEntries->insert(std::make_pair(0, lp));
	  }
	  lp->add(Entry::create(code, UINT_MAX, std::string(), *$3));
	  free($3);
	}

	//
	|stringOrIdentifier lexical_entries TOKEN_SEMI
	{
	  DBUGPRT("dictionary_line");
	  for (Entries::list::const_iterator entry = (*$2)->begin();
	       entry != (*$2)->end();
	       ++entry){
	    (*entry)->setForm(*$1);
	    //}
	    //for (std::vector< entryPtr >::const_iterator entry = (*$2)->begin();
	    //    entry != (*$2)->end();
	    //   ++entry){
	    entriesPtr lp;
	    Parser::entries_map *predToEntries;
	    //std::cerr << (*entry)->getCode() << std::endl;
	    Parser::entries_map_map::iterator foundCode = parser.getLexicon().find((*entry)->getCode());
	    if (foundCode != parser.getLexicon().end()){
	      predToEntries = foundCode->second;
	    } else {
	      predToEntries = new Parser::entries_map;
	      parser.getLexicon().insert(std::make_pair((*entry)->getCode(), predToEntries));
	    }
	    Parser::entries_map::iterator foundPred = predToEntries->find((*entry)->getCodePred());
	    if (foundPred != predToEntries->end()){
	      lp = foundPred->second;
	    } else {
	      lp = Entries::create();
	      predToEntries->insert(std::make_pair((*entry)->getCodePred(), lp));
	    }
	    lp->add(*entry);
	  }
	  free($1);
	  free($2);
	}

	//
	|TOKEN_AROBASE TOKEN_IDENTIFIER TOKEN_COLON features TOKEN_SEMI
	{
	  DBUGPRT("dictionary_line");
	  parser.addMacros(*$2, *$4);
	  free($2);
	  free($4);
	  
	}

	|TOKEN_SEMI
	{
	  DBUGPRT("dictionary_line");
	};

lexical_entries:
	lexical_entry TOKEN_PIPE lexical_entries
	{	  
	  DBUGPRT("lexical_entries");
	  $$=$3; 
	  (*$$)->add(*$1);
	  free($1);
	}
	
	|lexical_entry {
	  DBUGPRT("lexical_entries");
	  $$ = new entriesPtr(Entries::create(*$1));
	  free($1);
	 };

lexical_entry:
	// pos
	TOKEN_IDENTIFIER features
	{
	  DBUGPRT("lexical_entry");
	  unsigned int pred = (*$2)->assignPred();
	  $$ = new entryPtr(Entry::create(Vartable::strToInt(*$1), pred, std::string(), *$2));
	  free($1);
	  free($2);
	}

	|TOKEN_IDENTIFIER 
	{
	  DBUGPRT("lexical_entry");
	  $$ = new entryPtr(Entry::create(Vartable::strToInt(*$1), UINT_MAX, std::string(), Features::create()));
	  free($1);
	};

///////////////////////////
// RULES
//////////////////////////
rules:
	{headLineno = ruleslineno;} rule rules
	{
	  DBUGPRT("rules"); 
	}
	
	|{headLineno = ruleslineno;} /*empty*/
	{
	  DBUGPRT("rules"); 
	};

pref_rule:
	TOKEN_TRACE
	{
	  DBUGPRT("pref_rule");
	  headTrace = true;
	}

	| /* empty */ {
	  DBUGPRT("pref_rule");
	  headTrace = false;
	};

rule:
	pref_rule term TOKEN_RIGHTARROW terms_vector structure_statement
	{
	  DBUGPRT("rule");
	  rulePtr rule = Rule::create(headLineno, parser.getTopBufferName(), *$2, *$4, $5 ? *$5 : statementsPtr());
	  rule->addDefaults();
	  rule->setTrace(headTrace);
	  parser.getGrammar().addRule(rule);
	  if (!parser.getGrammar().getStartTerm()){
	    parser.getGrammar().setStartTerm(*$2);
	  }
	  free($4);
	  if ($5)
	     free($5);
	}

	|pref_rule term TOKEN_RIGHTARROW structure_statement
	{
	  DBUGPRT("Rule");
	  rulePtr rule = Rule::create(headLineno, parser.getTopBufferName(), *$2, $4 ? *$4 : statementsPtr());
	  rule->addDefaults();
	  rule->setTrace(headTrace);
	  parser.getGrammar().addRule(rule);
	  if (!parser.getGrammar().getStartTerm()){
	    parser.getGrammar().setStartTerm(*$2);
	  }
	  if ($4)
	    free($4);
	};

terms_vector:
	terms_vector terms { 
	  DBUGPRT("term_vector");
	  $$=$1;
	  $$->push_back(*$2);
	}

	|terms { 
	  DBUGPRT("term_vector"); 
	  $$ = new std::vector< termsPtr >;
	  $$->push_back(*$1);
	};
	
terms:
	terms_disj { 
	  DBUGPRT("term");
	  $$=$1;
	}

	|TOKEN_LBRACKET terms_disj TOKEN_RBRACKET { 
	  DBUGPRT("term");
	  $$ = $2;
	  (*$$)->setOptional();
	};

terms_disj:
	terms_disj TOKEN_PIPE term
	{ 
	  DBUGPRT("term_disj");
	  $$ = $1;
	  (*$$)->push_back(*$3);
	}

	|term
	{ 
	  DBUGPRT("term_disj"); 
	  $$ = new termsPtr(Terms::create(*$1));
	};
	
term:
	TOKEN_IDENTIFIER
	{ 
	  DBUGPRT("term_id");
	  unsigned int code = Vartable::strToInt(*$1);
	  $$ = new termPtr(Term::create(code));
	  free($1);
	}

	|TOKEN_VARIABLE
	{ 
	  DBUGPRT("term_id");
	  unsigned int code = Vartable::strToInt(*$1);
	  $$ = new termPtr(Term::create(code));
	  free($1);
	}

	|error 
	{
	  YYABORT;
	};

///////////////////////////////////////////////
// SEMANTIC FOR RULES
///////////////////////////////////////////////
structure_statement:
	TOKEN_LBRACE list_statement TOKEN_RBRACE
	{
	  DBUGPRT("structure_statement");
	  $$=$2;
	}

	|TOKEN_LBRACE TOKEN_RBRACE
	{
	  $$=NULL;
	}

	|TOKEN_SEMI
	{
	  $$=NULL;
	};

list_statement:
	statement
	{
	  DBUGPRT("list_statement");
	  $$ = new statementsPtr(Statements::create());
	  (*$$)->addStatement(*$1);
	  free($1);
	}

	|list_statement statement {
	  DBUGPRT("list_statement");
	  $$ = $1;
	  (*$$)->addStatement(*$2);
	  free($2);
	};

statements:
	TOKEN_LBRACE list_statement TOKEN_RBRACE
	{
	  DBUGPRT("statement");
	  $$ = new statementPtr(Statement::create(ruleslineno, Statement::STMS, *$2));
	  free($2);
	}
	
	|TOKEN_LBRACE TOKEN_RBRACE
	{
	  DBUGPRT("statement");
	  $$ = new statementPtr(Statement::create(ruleslineno, Statement::STMS, Statements::create()));
	};
	
statement:
	statements {
	  DBUGPRT("statement");
	  $$=$1;
	 }

	|TOKEN_ATTEST expression_statement TOKEN_SEMI {
	  DBUGPRT("statement");
	  $$ = new statementPtr(Statement::create(ruleslineno, Statement::ATTEST, *$2));
	  free($2);
	}

	|TOKEN_PRINT expression_statement TOKEN_SEMI {
	  DBUGPRT("statement");
	  $$ = new statementPtr(Statement::create(ruleslineno, Statement::PRINT, *$2));
	  free($2);
	}

	|TOKEN_PRINTLN expression_statement TOKEN_SEMI {
	  DBUGPRT("statement");
	  $$ = new statementPtr(Statement::create(ruleslineno, Statement::PRINTLN, *$2));
	  free($2);
	}

	|features TOKEN_SEMI {
	  DBUGPRT("statement");
	  $$ = new statementPtr(Statement::create(ruleslineno, Statement::GUARD, *$1));
	  free($1);
	}

	|left_hand_side_aff_statement TOKEN_AFF right_hand_side_aff_statement TOKEN_SEMI {
	  DBUGPRT("statement");
	  $$ = new statementPtr(Statement::create(ruleslineno, Statement::AFF, *$1, *$3));
	  // <X, …> = <…>
	  // <X, …> = Z
	  if (((*$1)->isList()) && (((*$3)->isList())||((*$3)->isVariable()))) {
	    }
	  // ↓i = $X
	  // ↓i = […]
	  // ↓i = ↑
	  // ↓i = … ∪ …
	  // ↓i = ⇓j
	  else if (((*$1)->isDown()) && (((*$3)->isVariable())||((*$3)->isFeatures())||((*$3)->isUp())||((*$3)->isUnif())||((*$3)->isDown2())))
	    ;
	  // ⇑ = $X
	  // ⇑ = […]
	  // ⇑ = ↑
	  // ⇑ = … ∪ …
	  // ⇑ = ⇓j
	  else if (((*$1)->isUp2()) && (((*$3)->isVariable())||((*$3)->isFeatures())||((*$3)->isUp())||((*$3)->isUnif())||((*$3)->isDown2())))
	    ;
	  // $X = Y
	  // $X = a
	  // $X = <…>
	  // $X = […]
	  // $X = ↑
	  // $X = … ∪ …
	  // $X = ⇓j
	  // $X = <expr>
	  // $X = search
	  else if (((*$1)->isVariable()) 
		   &&(((*$3)->isVariable())
		      ||((*$3)->isConstant())
		      ||((*$3)->isList())
		      ||((*$3)->isFeatures())
		      ||((*$3)->isUp())
		      ||((*$3)->isUnif())
		      ||((*$3)->isDown2())
		      ||((*$3)->isDouble())
		      ||((*$3)->isFct())
		      ||((*$3)->isSearch())));
	  else {
	    yyerror((char*)"syntax error");
	  }
	  free($1);
	  free($3);
	}

	|left_hand_side_subset_statement TOKEN_SUBSUME right_hand_side_subset_statement TOKEN_SEMI {
	  DBUGPRT("statement");
	  $$ = new statementPtr(Statement::create(ruleslineno, Statement::SUBSUME, (*$1), (*$3)));
	  // […] ⊂ ↑ 
	  // […] ⊂ ⇓j 
	  // […] ⊂ $X 
	  // […] ⊂ search  
	  if (((*$1)->isFeatures()) && (((*$3)->isUp())||((*$3)->isDown2())||((*$3)->isVariable())||((*$3)->isSearch())))
	    ;
	  else 
	    yyerror((char *)"syntax error");
	  free($1);
	  free($3);
	}

	|left_hand_side_inset_statement TOKEN_INSET right_hand_side_inset_statement TOKEN_SEMI {
	  DBUGPRT("statement");
	  $$ = new statementPtr(Statement::create(ruleslineno, Statement::INSET, (*$1), (*$3)));
	  // ↓i ∈ <...>
	  if (((*$1)->isDown())
	       && (((*$3)->isList())))
	    ;
	    else 
	  yyerror((char *)"syntax error");
	  free($1);
	  free($3);
	}

	|TOKEN_IF TOKEN_LPAR expression_statement TOKEN_RPAR statement %prec TOKEN_NOELSE {
	  DBUGPRT("statement");
	  statementPtr stm;
	  if (!(*$5)->isStms()) {
	    statementsPtr stms = Statements::create();
	    stms->addStatement(*$5);
	    stm = Statement::create(ruleslineno, Statement::STMS, stms);
	  }
	  else
	    stm = *$5;
	  $$ = new statementPtr(Statement::create(ruleslineno, 
						Statement::IF,
						  *$3, 
						  Statement::create(ruleslineno, Statement::THENELSE, stm, statementPtr())));
	  free($3);
	  free($5);
	}

	|TOKEN_IF TOKEN_LPAR expression_statement TOKEN_RPAR statement TOKEN_ELSE statement {
	  DBUGPRT("statement");
	  statementPtr stm1;
	  statementPtr stm2;
	  if (!(*$5)->isStms()) {
	    statementsPtr stms = Statements::create();
	    stms->addStatement(*$5);
	    stm1 = Statement::create(ruleslineno, Statement::STMS, stms);
	  }
	  else
	    stm1 = *$5;
	  if (!(*$7)->isStms()) {
	    statementsPtr stms = Statements::create();
	    stms->addStatement(*$7);
	    stm2 = Statement::create(ruleslineno, Statement::STMS, stms);
	  }
	  else
	    stm2 = *$7;
	  $$ = new statementPtr(Statement::create(ruleslineno, 
						  Statement::IF, 
						  (*$3), 
						  Statement::create(ruleslineno, Statement::THENELSE, stm1, stm2)));
	  free($3);
	  free($5);
	  free($7);
	}

	|TOKEN_FOREACH variable TOKEN_IN expression_statement statement {
	  DBUGPRT("statement");
	  statementPtr stm;
	  if (!(*$5)->isStms()) {
	    statementsPtr stms = Statements::create();
	    stms->addStatement(*$5);
	    stm = Statement::create(ruleslineno, Statement::STMS, stms);
	  }
	  else
	    stm = *$5;
	  $$ = new statementPtr(Statement::create(ruleslineno, 
						  Statement::FOREACH,
						  Statement::create(ruleslineno, Statement::VARIABLE, (*$2)),
						  Statement::create(ruleslineno, Statement::IN, (*$4), stm)));
	  free($2);
	  free($4);
	  free($5);
	};

left_hand_side_subset_statement:
	features {
	  DBUGPRT("left_hand_side_statement");
	  $$ = new statementPtr(Statement::create(ruleslineno, Statement::FEATURES, *$1));
	  free($1);
	};
	
right_hand_side_subset_statement:
	variable {
	  DBUGPRT("right_hand_side_subset_statement");
	  $$ = new statementPtr(Statement::create(ruleslineno, Statement::VARIABLE, *$1));
	  free($1);
	}

	|up {
	  DBUGPRT("right_hand_side_subset_statement");
	  $$=$1;
	}

	|downdouble {
	  DBUGPRT("right_hand_side_subset_statement");
	  $$=$1;
	}

	|features {
	  DBUGPRT("right_hand_side_subset_statement");
	  $$ = new statementPtr(Statement::create(ruleslineno, Statement::FEATURES, *$1));
	  free($1);
	}

	|TOKEN_SEARCH TOKEN_LPAR expression_statement TOKEN_RPAR  {
	  DBUGPRT("right_hand_side_subset_statement");
	  $$ = new statementPtr(Statement::create(ruleslineno, 
						  Statement::SEARCH, 
						  *$3));
	  free($3);
	 };
	
left_hand_side_inset_statement:
	down {
	  DBUGPRT("left_hand_side_statement");
	  $$=$1;
	};
	
right_hand_side_inset_statement:
	expression_statement {
	  DBUGPRT("right_hand_side_statement");
	  $$=$1;
	};	

left_hand_side_aff_statement:
	updouble {
	  DBUGPRT("left_hand_side_statement");
	  $$=$1;
	}

	|down {
	  DBUGPRT("left_hand_side_statement");
	  $$=$1;
	}

	|variable {
	  DBUGPRT("left_hand_side_statement");
	  $$ = new statementPtr(Statement::create(ruleslineno, Statement::VARIABLE, *$1));
	  free($1);
	 }

	|TOKEN_LT variable TOKEN_DOUBLECOLON variable TOKEN_GT
	{
	  DBUGPRT("left_hand_side_statement");
	  $$ = new statementPtr(Statement::create(ruleslineno, Statement::LIST,
						List::create(List::create(Value::create(Value::VARIABLE, *$2)),
							     List::create(Value::create(Value::VARIABLE, *$4)))));
	  free($2);
	  free($4);
	};

right_hand_side_aff_statement:
	expression_statement {
	  DBUGPRT("right_hand_side_statement");
	  $$=$1;
	};	

expression_statement:
	//////////////////////////////////////////////////
	// logic
	//////////////////////////////////////////////////
	expression_statement TOKEN_OR expression_statement {
	  DBUGPRT("expression_statement");
	  $$ = new statementPtr(Statement::create(ruleslineno, Statement::FCT, Statement::OR, (*$1), (*$3)));
	  free($1);
	  free($3);
	}

	|expression_statement TOKEN_AND expression_statement {
	  DBUGPRT("expression_statement");
	  $$ = new statementPtr(Statement::create(ruleslineno, Statement::FCT, Statement::AND, (*$1), (*$3)));
	  free($1);
	  free($3);
	}

	|expression_statement TOKEN_IMPLICATION expression_statement {
	  DBUGPRT("expression_statement");
	  $$ = new statementPtr(Statement::create(ruleslineno, Statement::FCT, Statement::OR, Statement::create(ruleslineno, Statement::FCT, Statement::NOT, (*$1)), (*$3)));
	  free($1);
	  free($3);
	}

	|expression_statement TOKEN_EQUIV expression_statement {
	  DBUGPRT("expression_statement");
	  $$ = new statementPtr(Statement::create(ruleslineno, Statement::FCT, Statement::AND,
						Statement::create(ruleslineno, Statement::FCT, Statement::OR,
								  Statement::create(ruleslineno, Statement::FCT, Statement::NOT, (*$1)),
								  (*$3)),
						Statement::create(ruleslineno, Statement::FCT, Statement::OR,
								  (*$1),
								  Statement::create(ruleslineno, Statement::FCT, Statement::NOT, (*$3)))));
	  free($1);
	  free($3);
	}

	|TOKEN_NOT expression_statement {
	  DBUGPRT("expression_statement");
	  $$ = new statementPtr(Statement::create(ruleslineno, Statement::FCT, Statement::NOT, (*$2)));
	  free($2);
	}

	|expression_statement TOKEN_EQUAL expression_statement {
	  DBUGPRT("expression_statement");
	  $$ = new statementPtr(Statement::create(ruleslineno, Statement::FCT, Statement::EQ, (*$1), (*$3)));
	  free($1);
	  free($3);
	}
	
	|expression_statement TOKEN_DIFF expression_statement { 
	  DBUGPRT("expression_statement");
	  $$ = new statementPtr(Statement::create(ruleslineno, Statement::FCT, Statement::DIFF, (*$1), (*$3))); 
	  free($1);
	  free($3);
	}
	
	|expression_statement TOKEN_LT expression_statement { 
	  DBUGPRT("expression_statement");
	  $$ = new statementPtr(Statement::create(ruleslineno, Statement::FCT, Statement::LT, (*$1), (*$3))); 
	  free($1);
	  free($3);
	}

	|expression_statement TOKEN_LE expression_statement { 
	  DBUGPRT("expression_statement");
	  $$ = new statementPtr(Statement::create(ruleslineno, Statement::FCT, Statement::LE, (*$1), (*$3))); 
	  free($1);
	  free($3);
	}

	|expression_statement TOKEN_GT expression_statement { 
	  DBUGPRT("expression_statement");
	  $$ = new statementPtr(Statement::create(ruleslineno, Statement::FCT, Statement::GT, (*$1), (*$3))); 
	  free($1);
	  free($3);
	}

	|expression_statement TOKEN_GE expression_statement { 
	  DBUGPRT("expression_statement");
	  $$ = new statementPtr(Statement::create(ruleslineno, Statement::FCT, Statement::GE, (*$1), (*$3))); 
	  free($1);
	  free($3);
	}
	
	//////////////////////////////////////////////////
	// arithmetic, string, lists
	//////////////////////////////////////////////////
	|expression_statement TOKEN_PLUS expression_statement
	{
	  DBUGPRT("expression_statement");
	  $$ = new statementPtr(Statement::create(ruleslineno, Statement::FCT, Statement::PLUS, (*$1), (*$3)));
	  free($1);
	  free($3);
	}

	|expression_statement TOKEN_MINUS expression_statement
	{
	  DBUGPRT("expression_statement");
	  $$ = new statementPtr(Statement::create(ruleslineno, Statement::FCT, Statement::MINUS, (*$1), (*$3)));
	  free($1);
	  free($3);
	}

	|expression_statement TOKEN_TIMES expression_statement
	{
	  DBUGPRT("expression_statement");
	  $$ = new statementPtr(Statement::create(ruleslineno, Statement::FCT, Statement::TIMES, (*$1), (*$3)));
	  free($1);
	  free($3);
	}

	|expression_statement TOKEN_DIVIDE expression_statement
	{
	  DBUGPRT("expression_statement");
	  $$ = new statementPtr(Statement::create(ruleslineno, Statement::FCT, Statement::DIVIDE, (*$1), (*$3)));
	  free($1);
	  free($3);
	}

	|expression_statement TOKEN_MODULO expression_statement
	{
	  DBUGPRT("expression_statement");
	  $$ = new statementPtr(Statement::create(ruleslineno, Statement::FCT, Statement::MODULO, (*$1), (*$3)));
	  free($1);
	  free($3);
	}

	|TOKEN_MINUS expression_statement %prec TOKEN_MINUS_U
	{
	  DBUGPRT("expression_statement");
	  $$ = new statementPtr(Statement::create(ruleslineno, Statement::FCT, Statement::MINUS_U, (*$2), statementPtr()));
	  free($2);
	}

	|TOKEN_RAND TOKEN_LPAR TOKEN_RPAR
	{
	  DBUGPRT("expression_statement");
	  $$ = new statementPtr(Statement::create(ruleslineno, Statement::FCT, Statement::RAND));
	}

	|TOKEN_DOUBLE
	{
	  DBUGPRT("expression_statement");
	  $$ = new statementPtr(Statement::create(ruleslineno, Statement::DOUBLE, $1));
	}

	|TOKEN_INTEGER
	{
	  DBUGPRT("expression_statement");
 	  $$ = new statementPtr(Statement::create(ruleslineno, Statement::DOUBLE, (double)$1));
	}

	|TOKEN_STRING
	{
	  DBUGPRT("expression_statement");
 	  $$ = new statementPtr(Statement::create(ruleslineno, Statement::STR, *$1));
	}

	//////////////////////////////////////////////////
	// features
	//////////////////////////////////////////////////
	|expression_statement TOKEN_UNION expression_statement {
	  DBUGPRT("expression_statement");
	  $$ = new statementPtr(Statement::create(ruleslineno, Statement::UNIF, (*$1), (*$3)));
	  free($1);
	  free($3);
	}
 	
	|up {
	  DBUGPRT("expression_statement");
	  $$=$1;
	}

	|updouble {
	  DBUGPRT("expression_statement");
	  $$=$1;
	}

	|down {
	  DBUGPRT("expression_statement");
	  $$=$1;
	}

	|downdouble {
	  DBUGPRT("expression_statement");
	  $$=$1;
	}

	|features {
	  DBUGPRT("expression_statement");
	  $$ = new statementPtr(Statement::create(ruleslineno, Statement::FEATURES, *$1));
	  free($1);
	}

	|TOKEN_NIL
	{
	  DBUGPRT("expression_statement");
	  $$ = new statementPtr(Statement::create(ruleslineno, Statement::NIL));
	}

	|constant {
	  DBUGPRT("expression_statement");
	  $$ = new statementPtr(Statement::create(ruleslineno, Statement::CONSTANT, *$1));
	  free($1);
	}

	|TOKEN_ANONYMOUS
	{
	  DBUGPRT("expression_statement");
	  $$ = new statementPtr(Statement::create(ruleslineno, Statement::ANONYMOUS, Value::ANONYMOUS_VALUE));
	}

	|variable {
	  DBUGPRT("expression_statement");
	  $$ = new statementPtr(Statement::create(ruleslineno, Statement::VARIABLE, *$1));
	  free($1);
	}

	|TOKEN_LPAR expression_statement TOKEN_RPAR {
	  DBUGPRT("expression_statement");
	  $$=$2;
	}
	
	|list {
	  DBUGPRT("expression_statement");
	  $$ = new statementPtr(Statement::create(ruleslineno, Statement::LIST, *$1));
	  free($1);
	}

	|dash_statement {
	  DBUGPRT("expression_statement");
	  $$=$1;
	}

	|TOKEN_SEARCH TOKEN_LPAR expression_statement TOKEN_RPAR  {
	  DBUGPRT("expression_statement");
	  $$ = new statementPtr(Statement::create(ruleslineno, 
						  Statement::SEARCH, 
						  *$3));
	  free($3);
	 };

up:
	TOKEN_UPARROW {  
	  DBUGPRT("up");
	  $$ = new statementPtr(Statement::create(ruleslineno, Statement::UP));
	};

updouble:
	TOKEN_UP2ARROW {  
	  DBUGPRT("updouble");
	  $$ = new statementPtr(Statement::create(ruleslineno, Statement::UP2));
	};

down:
	TOKEN_DOWNARROW TOKEN_INTEGER
	{ 
	  DBUGPRT("down");
	  $$ = new statementPtr(Statement::create(ruleslineno, Statement::DOWN, (unsigned int)$2-1)); 
	};

dash_statement:
	TOKEN_DASH TOKEN_INTEGER TOKEN_DOT TOKEN_INTEGER
	{ 
	  DBUGPRT("dash_statement");
	  $$ = new statementPtr(Statement::create(ruleslineno, Statement::DASH, (unsigned int)($2-1), (unsigned int)($4-1))); 
	}

	|TOKEN_DASH TOKEN_INTEGER
	{ 
	  DBUGPRT("dash_statement");
	  $$ = new statementPtr(Statement::create(ruleslineno, Statement::DASH, (unsigned int)($2-1))); 
	};

downdouble:
	TOKEN_DOWN2ARROW {  
	  DBUGPRT("downdouble");
	  $$ = new statementPtr(Statement::create(ruleslineno, Statement::DOWN2, (unsigned int)0)); 
	}

	|TOKEN_DOWN2ARROW TOKEN_INTEGER
	{ 
	  DBUGPRT("downdouble");
	  $$ = new statementPtr(Statement::create(ruleslineno, Statement::DOWN2, (unsigned int)($2-1))); 
	};

//////////////////////////
// Features
//////////////////////////
features:
	TOKEN_LBRACKET features_components TOKEN_RBRACKET
	{
	  DBUGPRT("features");
 	  $$=$2;
	}

	|TOKEN_LBRACKET TOKEN_RBRACKET
	{
	  DBUGPRT("features");
	  $$ = new featuresPtr(Features::create());
	};

features_components:
	features_components TOKEN_COMMA feature
	{
	  DBUGPRT("feature_components");
	  $$=$1; 
	  (*$$)->add(*$3);
	  free($3);
	}

	|feature 
	{
	  DBUGPRT("features_components");
	  $$ = new featuresPtr(Features::create());
	  (*$$)->add(*$1);
	  free($1);
	}

	//…, @identifier
	|features_components TOKEN_COMMA TOKEN_AROBASE TOKEN_IDENTIFIER
	{
	  DBUGPRT("features_components");
	  featuresPtr found = parser.findMacros(*$4);
	  free($4);
	  if (!(found)){
	    yyerror((char*)"syntax error");
	  }
	  $$ = $1; 
	  (*$$)->add(found->clone());
	}

	//@identifier
	|TOKEN_AROBASE TOKEN_IDENTIFIER
	{
	  DBUGPRT("features_components");
	  featuresPtr found = parser.findMacros(*$2);
	  free($2);
	  if (!(found)){
	    yyerror((char*)"syntax error");
	  }
	  $$ = new featuresPtr(Features::create());
	  (*$$)->add(found->clone());
	};

feature:
	// PRED: predicate
	TOKEN_PRED TOKEN_COLON TOKEN_IDENTIFIER
	{
	  DBUGPRT("feature");
	  $$ = new featurePtr(Feature::create(Feature::PRED, bitsetPtr(), Value::create(Value::IDENTIFIER, *$3)));
	}

	// PRED: $X
	|TOKEN_PRED TOKEN_COLON variable
	{
	  DBUGPRT("feature");
	  $$ = new featurePtr(Feature::create(Feature::PRED, bitsetPtr(), Value::create(Value::VARIABLE, *$3)));
	  free($3);
	}

	// FORM: $X
	|TOKEN_FORM TOKEN_COLON variable
	{
	  DBUGPRT("feature");
	  $$ = new featurePtr(Feature::create(Feature::FORM, bitsetPtr(), Value::create(Value::VARIABLE, *$3)));
	  free($3);
	}

	|TOKEN_FORM TOKEN_COLON TOKEN_STRING
	{
	  DBUGPRT("feature");
	  $$ = new featurePtr(Feature::create(Feature::FORM, bitsetPtr(), Value::create(Value::STR, *$3)));
	}

	|identifier TOKEN_COLON feature_value
	{
	  DBUGPRT("feature");
	  $$ = new featurePtr(Feature::create(Feature::CONSTANT, *$1, *$3));
	  free($1);
	  free($3);
	}

	|identifier TOKEN_COLON TOKEN_STRING
	{
	  DBUGPRT("feature");
	  $$ = new featurePtr(Feature::create(Feature::CONSTANT, *$1, Value::create(Value::STR, *$3)));
	  free($1);
	}

	|variable TOKEN_COLON feature_value
	{
	  DBUGPRT("feature");
	  $$ = new featurePtr(Feature::create(Feature::VARIABLE, *$1, *$3));
	  free($1);
	  free($3);
	}

	|variable
	{
	  DBUGPRT("feature");
	  $$ = new featurePtr(Feature::create(Feature::VARIABLE, *$1, valuePtr()));
	  free($1);
	};

feature_value:
	variable
	{
	  DBUGPRT("feature_value");
	  $$ = new valuePtr(Value::create(Value::VARIABLE, *$1));
	  free($1);
	}

	|constant
	{
	  DBUGPRT("feature_value");
	  $$ = new valuePtr(Value::create(Value::CONSTANT, *$1));
	  free($1);
	}

	|TOKEN_DOUBLE
	{
	  DBUGPRT("expression_statement");
	  $$ = new valuePtr(Value::create(Value::DOUBLE, $1));
	}

	|TOKEN_INTEGER
	{
	  DBUGPRT("expression_statement");
	  $$ = new valuePtr(Value::create(Value::DOUBLE, (double)$1));
	}

	|list
	{
	  DBUGPRT("feature_value");
	  $$ = new valuePtr(Value::create(Value::LIST, *$1));
	  free($1);
	}

	|features
	{
	  DBUGPRT("feature_value");
	  $$ = new valuePtr(Value::create(Value::FEATURES, *$1));
	  free($1);
	}

	|TOKEN_NIL
	{
	  DBUGPRT("feature_value");
	  $$ = new valuePtr(Value::NIL_VALUE);
	}

	|TOKEN_TRUE
	{
	  DBUGPRT("feature_value");
	  $$ = new valuePtr(Value::TRUE_VALUE);
	}

	|TOKEN_ANONYMOUS
	{
	  DBUGPRT("feature_value");
	  $$ = new valuePtr(Value::ANONYMOUS_VALUE);
	};

constant:
	identifier
	{
	  DBUGPRT("constants");
	  $$=$1;
	}

	| identifier TOKEN_PIPE constant
	{
	  DBUGPRT("constants");
	  $$=$1;
	  (**$$) |= (**$3);
	};

identifier:
	TOKEN_IDENTIFIER
	{
	  DBUGPRT("identifier");
 	  $$ = new bitsetPtr(Bitset::create(Vartable::varTableAdd(*$1)));
 	  free($1);
	};

variable:
	TOKEN_VARIABLE
	{
	  DBUGPRT("variable");
	  std::ostringstream oss;
	  oss << *$1;
  	  std::string str = oss.str();
	  $$ = new bitsetPtr(Bitset::create(Vartable::varTableAdd(str)));
	  free($1);
	};
	
list:
	TOKEN_LT list_elements TOKEN_GT
	{
	  DBUGPRT("list");
	  $$ = $2;
	}

	|TOKEN_LT TOKEN_GT
	{
	  DBUGPRT("list");
	  $$ = new listPtr(List::NIL_LIST);
	}

	|TOKEN_LT list_elements TOKEN_DOUBLECOLON list_element TOKEN_GT
	{
	  DBUGPRT("list");
	  if ((*$2)->isPairp() && (*$2)->getCdr()->isNil())
	    $$ = new listPtr(List::create((*$2)->getCar(), *$4));
	  else
	    $$ = new listPtr(List::create(*$2, *$4));
	  free($2);
	  free($4);
	}

	|TOKEN_LT list_elements TOKEN_DOUBLECOLON TOKEN_NIL TOKEN_GT
	{
	  DBUGPRT("list");
	  if ((*$2)->isPairp() && (*$2)->getCdr()->isNil())
	    $$ = new listPtr(List::create((*$2)->getCar(), List::NIL_LIST));
	  else
	    $$ = new listPtr(List::create(*$2, List::NIL_LIST));
	  free($2);
	};

list_elements:
	list_element TOKEN_COMMA list_elements 
	{
	  DBUGPRT("list_elements");
	  $$ = new listPtr(List::create(*$1, *$3));
	  free($1);
	  free($3);
	}

	|list_element
	{
	  DBUGPRT("list_elements");
	  $$ = new listPtr(List::create(*$1, List::NIL_LIST));
	  free($1);
	};

list_element:
	variable
	{
	  DBUGPRT("list_element");
	  $$ = new listPtr(List::create(Value::create(Value::VARIABLE, *$1)));
	  free($1);
	}

	|TOKEN_DOUBLE
	{
	  DBUGPRT("expression_statement");
	  $$ = new listPtr(List::create(Value::create(Value::DOUBLE, $1)));
	}

 	|TOKEN_INTEGER
	{
	  DBUGPRT("expression_statement");
	  $$ = new listPtr(List::create(Value::create(Value::DOUBLE, (double)$1)));
	}

	|constant
	{
	  DBUGPRT("list_element");
	  $$ = new listPtr(List::create(Value::create(Value::CONSTANT, *$1)));
	  free($1);
	}

	|features
	{
	  DBUGPRT("list_element");
	  $$ = new listPtr(List::create(Value::create(Value::FEATURES, *$1)));
	  free($1);
	}

	|list
	{
	  DBUGPRT("list_element");
	  $$=$1;
	};

%%
