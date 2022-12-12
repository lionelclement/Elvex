%{

/* **************************************************
 *
 * ELVEX
 *
 * Copyright 2014-2022 LABRI,
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

#include <sstream>
#include "vartable.hpp"
#include "terms.hpp"
#include "entry.hpp"
#include "entries.hpp"
#include "parser.hpp"
#include "bitset.hpp"
#include "value.hpp"
#include "feature.hpp"
#include "features.hpp"
#include "pairp.hpp"
#include "statements.hpp"
#include "statement.hpp"
#include "terms.hpp"
#include "messages.hpp"
#include "rule.hpp"
#include "shared_ptr.hpp"
#include "parser_exception.hpp"

#ifndef DEBUGYACC
#define DEBUGYACC(x)
#else
#define DEBUGYACC(x) x
#endif

#define DBUGPRT(x) DEBUGYACC({std::cerr << "*** " << x << std::endl;})
#define DBUGPRTARG(x, s) DEBUGYACC({std::cerr << "*** " << x << ' ' << s << std::endl});
  
 extern unsigned int ruleslineno;
 extern unsigned int ruleslex();
 extern Parser parser;
 unsigned int headLineno;
 bool headTrace;

  void ruleserror(const char* str) {
      std::ostringstream oss;
      oss << str << " in " << parser.getTopBufferName() << " (line " << ruleslineno << ")";
      throw parser_exception(oss);
  }

  void yywarning(const char* str){
      std::ostringstream oss;
      oss << "warning: " << str << " " << parser.getTopBufferName() << " (" << ruleslineno << ")" << std::endl;
      std::cerr << oss.str() << std::endl;
  }

  %}

%union{
  unsigned int integer_slot;
  double double_slot;
  termsPtr* terms_slot; //(A|B)
  std::vector< termsPtr  >* vector_terms_slot; // X Y
  std::string* string_slot;
  entryPtr* entry_slot;
  entriesPtr* entries_slot;
  bitsetPtr* bits_slot;
  valuePtr* value_slot;
  featurePtr* feature_slot;
  featuresPtr* features_slot;
  pairpPtr* pairp_slot;
  statementPtr* statement_slot;
  statementsPtr* statements_slot;

  std::list<  bitsetPtr >* list_args;
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
%token TOKEN_RULES TOKEN_INPUT TOKEN_LEXICON
%token TOKEN_LEMMA TOKEN_PRED TOKEN_FORM
%token TOKEN_ATTEST TOKEN_PRINT TOKEN_PRINTLN
%token TOKEN_IF TOKEN_ELSE
%token TOKEN_WAIT
%token TOKEN_NIL TOKEN_TRUE TOKEN_FALSE
%token TOKEN_FOREACH TOKEN_IN
%token TOKEN_SEARCH TOKEN_ON
%token TOKEN_RAND
%token TOKEN_TRACE

// OPERATORS
%token TOKEN_UNION TOKEN_SUBSUME TOKEN_AFF TOKEN_PIPE TOKEN_NOT 
TOKEN_OR TOKEN_AND TOKEN_IMPLICATION TOKEN_EQUIV
TOKEN_PLUS TOKEN_MINUS TOKEN_TIMES TOKEN_DIVIDE TOKEN_MODULO
TOKEN_EQUAL TOKEN_DIFF TOKEN_LT TOKEN_LE TOKEN_GT TOKEN_GE
//TOKEN_INSET 

 // LITERALS
%token<string_slot> TOKEN_IDENTIFIER TOKEN_STRING

%token<integer_slot> TOKEN_INTEGER

%token<double_slot> TOKEN_DOUBLE

 // VARIABLES
%token<string_slot> TOKEN_VARIABLE
%token TOKEN_ANONYMOUS

%type<string_slot> stringOrIdentifier
%type<integer_slot> term
%type<terms_slot> terms terms_disj
%type<vector_terms_slot> terms_vector
%type<entries_slot> lexical_entries
%type<entry_slot> lexical_entry

%type<features_slot> features features_composite
%type<feature_slot> feature features_composite_tail
%type<bits_slot> variable identifier constant
%type<value_slot> feature_value
%type<pairp_slot> pairp pairp_elements pairp_element

%type<statements_slot> structure_statement list_statement expression_statement_composite
%type<statement_slot> statement statements left_hand_side_subset_statement right_hand_side_subset_statement left_hand_side_aff_statement right_hand_side_aff_statement up down up2 down2 dash_statement
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
	TOKEN_RULES TOKEN_LPAR rules TOKEN_RPAR{
	  DBUGPRT("begin grammar");
	}

	|TOKEN_INPUT TOKEN_LPAR term features TOKEN_RPAR {
	  DBUGPRT("begin input");
	  parser.setStartTerm($3);
	  (*$4)->renameVariables((*$4)->getId());
	  parser.setStartFeatures(*$4);
	  free($4);
	}

	|TOKEN_INPUT TOKEN_LPAR term TOKEN_RPAR {
	  DBUGPRT("begin input");
	  parser.setStartTerm($3);
	  parser.setStartFeatures(Features::create());
	 }

	|TOKEN_LEXICON TOKEN_LPAR dictionary TOKEN_RPAR{
	  DBUGPRT("begin lexicon");
	  //CERR_LINE;
	  //parser.printCacheLexicon(std::cout);
	}

	|TOKEN_DASH TOKEN_LPAR features TOKEN_RPAR
	{
	  DBUGPRT("begin features");
	  parser.setLocalFeatures(*$3);
	  free($3);
	};

dictionary:
	dictionary_line dictionary {
	  DBUGPRT("dictionary");
	}

	|dictionary_line {
	  DBUGPRT("dictionary");
	 };

dictionary_line:
	// FORM constantNoun ;
	TOKEN_FORM TOKEN_IDENTIFIER TOKEN_SEMI
	{
	  DBUGPRT("dictionary_line");
	  unsigned int code = Vartable::stringToCode(*$2);
	  free($2);
	  // constantNoun => (0 => args)
	  auto foundCode = parser.findCacheLexicon(code);
	  Parser::entries_map* zeroToEntries;
	  if (foundCode != parser.cendCacheLexicon()){
	    zeroToEntries = foundCode->second;
	  } else {
	    zeroToEntries = new Parser::entries_map();
	    parser.insertCacheLexicon(std::make_pair(code, zeroToEntries));
	  }
	  auto foundPred = zeroToEntries->find(0);
	  entriesPtr entries;
	  if (foundPred != zeroToEntries->cend()){
	    entries = foundPred->second;
	  } else {
	    entries = Entries::create();
	    zeroToEntries->insert(std::make_pair(0, entries));
	  }
	  entries->add(Entry::create(code, UINT_MAX, std::string(), Features::create()));
	}

	|TOKEN_FORM TOKEN_IDENTIFIER features TOKEN_SEMI
	{
	  DBUGPRT("dictionary_line");
	  unsigned int code = Vartable::stringToCode(*$2);
	  free($2);
	  // constantNoun => (0 => args)
	  auto foundCode = parser.findCacheLexicon(code);
	  Parser::entries_map* zeroToEntries;
	  if (foundCode != parser.cendCacheLexicon()) {
	    zeroToEntries = foundCode->second;
	  } else {
	    zeroToEntries = new Parser::entries_map;
	    parser.insertCacheLexicon(std::make_pair(code, zeroToEntries));
	  }
	  auto foundPred = zeroToEntries->find(0);
	  entriesPtr entries;
	  if (foundPred != zeroToEntries->cend()){
	    entries = foundPred->second;
	  } else {
	    entries = Entries::create();
	    zeroToEntries->insert(std::make_pair(0, entries));
	  }
	  entries->add(Entry::create(code, UINT_MAX, std::string(), *$3));
	  free($3);
	}

	//
	|stringOrIdentifier lexical_entries TOKEN_SEMI
	{
	  DBUGPRT("dictionary_line");
	  for (auto entry = (*$2)->begin() ; entry != (*$2)->end() ; ++entry) {
	    (*entry)->setForm(*$1);
	    entriesPtr lp;
	    Parser::entries_map* predToEntries;
		auto foundCode = parser.findCacheLexicon((*entry)->getPos());
	    if (foundCode != parser.cendCacheLexicon()){
	      predToEntries = foundCode->second;
	    } else {
	      predToEntries = new Parser::entries_map;
	      parser.insertCacheLexicon(std::make_pair((*entry)->getPos(), predToEntries));
	    }
	    Parser::entries_map_iterator foundPred = predToEntries->find((*entry)->getPred());
	    if (foundPred != predToEntries->cend()){
	      lp = foundPred->second;
	    } else {
	      lp = Entries::create();
	      predToEntries->insert(std::make_pair((*entry)->getPred(), lp));
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

stringOrIdentifier:
	TOKEN_IDENTIFIER {
	  DBUGPRT("stringOrIdentifier");
	  $$ = $1;
	}

	|TOKEN_STRING {
	  DBUGPRT("stringOrIdentifier");
	  $$ = $1;
	 }

	|stringOrIdentifier TOKEN_PLUS TOKEN_STRING {
	  DBUGPRT("string");
	  $$ = $1;
	  *$$ += *$3;
	 };

lexical_entries:
	lexical_entry TOKEN_PIPE lexical_entries
	{
	  DBUGPRT("lexical_entries");
	  $$ = $3;
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
	  $$ = new entryPtr(Entry::create(Vartable::stringToCode(*$1), pred, std::string(), *$2));
	  free($1);
	  free($2);
	}

	|TOKEN_IDENTIFIER
	{
	  DBUGPRT("lexical_entry");
	  $$ = new entryPtr(Entry::create(Vartable::stringToCode(*$1), UINT_MAX, std::string(), Features::create()));
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
	  rulePtr rule = Rule::create(headLineno, parser.getTopBufferName(), $2, *$4, $5 ? *$5 : statementsPtr());
	  rule->addDefaults();
	  rule->setTrace(headTrace);
	  parser.getRules().addRule(rule);
	  if (!parser.getRules().getStartTerm()){
	    parser.getRules().setStartTerm($2);
	  }
	  free($4);
	  if ($5)
	     free($5);
	}

	|pref_rule term TOKEN_RIGHTARROW structure_statement
	{
	  DBUGPRT("Rule");
	  rulePtr rule = Rule::create(headLineno, parser.getTopBufferName(), $2, $4 ? *$4 : statementsPtr());
	  rule->addDefaults();
	  rule->setTrace(headTrace);
	  parser.getRules().addRule(rule);
	  if (!parser.getRules().getStartTerm()){
	    parser.getRules().setStartTerm($2);
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
	  (*$$)->push_back($3);
	}

	|term
	{
	  DBUGPRT("term_disj");
	  $$ = new termsPtr(Terms::create($1));
	};

term:
	TOKEN_IDENTIFIER
	{
	  DBUGPRT("term_id");
	  $$ = Vartable::stringToCode(*$1);
	  free($1);
	}

	|TOKEN_VARIABLE
	{
	  DBUGPRT("term_id");
	  $$ = Vartable::stringToCode(*$1);
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
	  $$ = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::STMS_STATEMENT, false, *$2));
	  free($2);
	}

	|TOKEN_LBRACE TOKEN_RBRACE
	{
	  DBUGPRT("statement");
	  $$ = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::STMS_STATEMENT, false, Statements::create()));
	};

statement:
	statements {
	  DBUGPRT("statement");
	  $$=$1;
	 }

	|features TOKEN_SEMI {
	  DBUGPRT("statement");
	  $$ = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::GUARD_STATEMENT, true, *$1));
	  free($1);
	}

	|TOKEN_ATTEST expression_statement TOKEN_SEMI {
	  DBUGPRT("statement");
	  $$ = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::ATTEST_STATEMENT, true, *$2));
	  free($2);
	}

	|TOKEN_PRINT TOKEN_LPAR expression_statement_composite TOKEN_RPAR TOKEN_SEMI {
	  DBUGPRT("statement");
		$$ = new statementPtr(Statement::create(
			ruleslineno, 
			parser.getTopBufferName(), 
			Statement::PRINT_STATEMENT, 
			true, 
			*$3));
	  free($3);
	}

	|TOKEN_PRINTLN TOKEN_LPAR expression_statement_composite TOKEN_RPAR TOKEN_SEMI {
	  	DBUGPRT("statement");
		$$ = new statementPtr(Statement::create(
			ruleslineno, 
			parser.getTopBufferName(), 
			Statement::PRINTLN_STATEMENT, 
			true, 
			*$3));
	  free($3);
	}

	|left_hand_side_aff_statement TOKEN_AFF right_hand_side_aff_statement TOKEN_SEMI {
	  DBUGPRT("statement");
	  $$ = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::AFF_STATEMENT, true, *$1, *$3));
	  // <X, …> = <…>
	  // <X, …> = $X
	  // <X, …> = search 
	  if (((*$1)->isPairp()) 
	  		&& (((*$3)->isPairp())
				||((*$3)->isVariable()) 
				||((*$3)->isSearch()))) {
	    }
	  // ↓i = $X
	  // ↓i = […]
	  // ↓i = ↑
	  // ↓i = … ∪ …
	  // ↓i = ⇓j
	  else if (((*$1)->isDown()) 
	  		&& (((*$3)->isVariable())
					||((*$3)->isFeatures())
					||((*$3)->isUp())
					||((*$3)->isUnif())
					||((*$3)->isDown2())))
	    ;
	  // ⇑ = $X
	  // ⇑ = […]
	  // ⇑ = ↑
	  // ⇑ = … ∪ …
	  // ⇑ = ⇓j
	  else if (((*$1)->isUp2()) 
	  		&& (((*$3)->isVariable())
					||((*$3)->isFeatures())
					||((*$3)->isUp())
					||((*$3)->isUnif())
					||((*$3)->isDown2())))
	    ;
	  // $X = $Y
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
		      ||((*$3)->isPairp())
		      ||((*$3)->isFeatures())
		      ||((*$3)->isUp())
		      ||((*$3)->isUnif())
		      ||((*$3)->isDown2())
		      ||((*$3)->isString())
		      ||((*$3)->isNumber())
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
	  $$ = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::SUBSUME_STATEMENT, true, (*$1), (*$3)));
	  // […] ⊂ ↑
	  // […] ⊂ ⇓j
	  // […] ⊂ $X
	  if (((*$1)->isFeatures()) 
	  		&& (((*$3)->isUp())
					||((*$3)->isDown2())
					||((*$3)->isVariable())))
	    ;
	  else
	    yyerror((char* )"syntax error");
	  free($1);
	  free($3);
	}

	|TOKEN_IF TOKEN_LPAR expression_statement TOKEN_RPAR statement %prec TOKEN_NOELSE {
	  DBUGPRT("statement");
	  $$ = new statementPtr(Statement::create(ruleslineno,
						parser.getTopBufferName(), 
						Statement::IF_STATEMENT,
						  true, 
						  *$3,
						  Statement::create(ruleslineno, parser.getTopBufferName(), Statement::IF_CON_T_STATEMENT, false, *$5, statementPtr())));
	  free($3);
	  free($5);
	}

	|TOKEN_IF TOKEN_LPAR expression_statement TOKEN_RPAR statement TOKEN_ELSE statement {
	  DBUGPRT("statement");
	  $$ = new statementPtr(Statement::create(ruleslineno,
						  parser.getTopBufferName(),
						  Statement::IF_STATEMENT,
						  true, 
						  (*$3),
						  Statement::create(ruleslineno, parser.getTopBufferName(), Statement::IF_CON_T_STATEMENT, false, *$5, *$7)));
	  free($3);
	  free($5);
	  free($7);
	}

	|TOKEN_WAIT TOKEN_LPAR expression_statement TOKEN_RPAR statement {
	  DBUGPRT("statement");
	  $$ = new statementPtr(Statement::create(ruleslineno,
						parser.getTopBufferName(), 
						Statement::WAIT_STATEMENT,
						true, 
						*$3,
						*$5));
	  free($3);
	  free($5);
	}

	|TOKEN_FOREACH variable TOKEN_IN expression_statement statement {
	  DBUGPRT("statement");
	  $$ = new statementPtr(Statement::create(ruleslineno,
						  parser.getTopBufferName(),
						  Statement::FOREACH_STATEMENT,
						  true, 
						  Statement::create(ruleslineno, parser.getTopBufferName(), Statement::VARIABLE_STATEMENT, false, (*$2)),
						  Statement::create(ruleslineno, parser.getTopBufferName(), Statement::FOREACH_CON_T_STATEMENT, false, (*$4), *$5)));
	  free($2);
	  free($4);
	  free($5);
	};

left_hand_side_subset_statement:
	features {
	  DBUGPRT("left_hand_side_statement");
	  $$ = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::FEATURES_STATEMENT, false, *$1));
	  free($1);
	};

right_hand_side_subset_statement:
	variable {
	  DBUGPRT("right_hand_side_subset_statement");
	  $$ = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::VARIABLE_STATEMENT, false, *$1));
	  free($1);
	}

	|up {
	  DBUGPRT("right_hand_side_subset_statement");
	  $$=$1;
	}

	|down2 {
	  DBUGPRT("right_hand_side_subset_statement");
	  $$=$1;
	}

	|features {
	  DBUGPRT("right_hand_side_subset_statement");
	  $$ = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::FEATURES_STATEMENT, false, *$1));
	  free($1);
	}
	;

left_hand_side_aff_statement:
	up2 {
	  DBUGPRT("left_hand_side_statement");
	  $$=$1;
	}

	|down {
	  DBUGPRT("left_hand_side_statement");
	  $$=$1;
	}

	|variable {
	  DBUGPRT("left_hand_side_statement");
	  $$ = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::VARIABLE_STATEMENT, false, *$1));
	  free($1);
	 }

	|TOKEN_LT variable TOKEN_DOUBLECOLON variable TOKEN_GT
	{
	  DBUGPRT("left_hand_side_statement");
	  $$ = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::PAIRP_STATEMENT, false, 
						Pairp::create(Pairp::create(Value::create(Value::VARIABLE_VALUE, *$2)),
							     Pairp::create(Value::create(Value::VARIABLE_VALUE, *$4)))));
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
	  $$ = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::FUNCTION_STATEMENT, false, Statement::OR, (*$1), (*$3)));
	  free($1);
	  free($3);
	}

	|expression_statement TOKEN_AND expression_statement {
	  DBUGPRT("expression_statement");
	  $$ = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::FUNCTION_STATEMENT, false, Statement::AND, (*$1), (*$3)));
	  free($1);
	  free($3);
	}

	|expression_statement TOKEN_IMPLICATION expression_statement {
	  DBUGPRT("expression_statement");
	  $$ = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::FUNCTION_STATEMENT, false, Statement::OR, Statement::create(ruleslineno, parser.getTopBufferName(), Statement::FUNCTION_STATEMENT, false, Statement::NOT, (*$1)), (*$3)));
	  free($1);
	  free($3);
	}

	|expression_statement TOKEN_EQUIV expression_statement {
	  DBUGPRT("expression_statement");
	  $$ = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::FUNCTION_STATEMENT, false, Statement::AND,
						                    Statement::create(ruleslineno, parser.getTopBufferName(), Statement::FUNCTION_STATEMENT, false, Statement::OR,
								                Statement::create(ruleslineno, parser.getTopBufferName(), Statement::FUNCTION_STATEMENT, false, Statement::NOT, (*$1)),
								                (*$3)),
						                    Statement::create(ruleslineno, parser.getTopBufferName(), Statement::FUNCTION_STATEMENT, false, Statement::OR,
								                (*$1),
								                Statement::create(ruleslineno, parser.getTopBufferName(), Statement::FUNCTION_STATEMENT, false, Statement::NOT, (*$3)))));
	  free($1);
	  free($3);
	}

	|TOKEN_NOT expression_statement {
	  DBUGPRT("expression_statement");
	  $$ = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::FUNCTION_STATEMENT, false, Statement::NOT, (*$2)));
	  free($2);
	}

	|expression_statement TOKEN_EQUAL expression_statement {
	  DBUGPRT("expression_statement");
	  $$ = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::FUNCTION_STATEMENT, false, Statement::EQ, (*$1), (*$3)));
	  free($1);
	  free($3);
	}

	|expression_statement TOKEN_DIFF expression_statement {
	  DBUGPRT("expression_statement");
	  $$ = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::FUNCTION_STATEMENT, false, Statement::DIFF, (*$1), (*$3)));
	  free($1);
	  free($3);
	}

	|expression_statement TOKEN_LT expression_statement {
	  DBUGPRT("expression_statement");
	  $$ = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::FUNCTION_STATEMENT, false, Statement::LT, (*$1), (*$3)));
	  free($1);
	  free($3);
	}

	|expression_statement TOKEN_LE expression_statement {
	  DBUGPRT("expression_statement");
	  $$ = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::FUNCTION_STATEMENT, false, Statement::LE, (*$1), (*$3)));
	  free($1);
	  free($3);
	}

	|expression_statement TOKEN_GT expression_statement {
	  DBUGPRT("expression_statement");
	  $$ = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::FUNCTION_STATEMENT, false, Statement::GT, (*$1), (*$3)));
	  free($1);
	  free($3);
	}

	|expression_statement TOKEN_GE expression_statement {
	  DBUGPRT("expression_statement");
	  $$ = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::FUNCTION_STATEMENT, false, Statement::GE, (*$1), (*$3)));
	  free($1);
	  free($3);
	}

	//////////////////////////////////////////////////
	// arithmetic, string, lists
	//////////////////////////////////////////////////
	|expression_statement TOKEN_PLUS expression_statement
	{
	  DBUGPRT("expression_statement");
	  $$ = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::FUNCTION_STATEMENT, false, Statement::PLUS, (*$1), (*$3)));
	  free($1);
	  free($3);
	}

	|expression_statement TOKEN_MINUS expression_statement
	{
	  DBUGPRT("expression_statement");
	  $$ = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::FUNCTION_STATEMENT, false, Statement::MINUS, (*$1), (*$3)));
	  free($1);
	  free($3);
	}

	|expression_statement TOKEN_TIMES expression_statement
	{
	  DBUGPRT("expression_statement");
	  $$ = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::FUNCTION_STATEMENT, false, Statement::TIMES, (*$1), (*$3)));
	  free($1);
	  free($3);
	}

	|expression_statement TOKEN_DIVIDE expression_statement
	{
	  DBUGPRT("expression_statement");
	  $$ = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::FUNCTION_STATEMENT, false, Statement::DIVIDE, (*$1), (*$3)));
	  free($1);
	  free($3);
	}

	|expression_statement TOKEN_MODULO expression_statement
	{
	  DBUGPRT("expression_statement");
	  $$ = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::FUNCTION_STATEMENT, false, Statement::MODULO, (*$1), (*$3)));
	  free($1);
	  free($3);
	}

	|TOKEN_MINUS expression_statement %prec TOKEN_MINUS_U
	{
	  DBUGPRT("expression_statement");
	  $$ = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::FUNCTION_STATEMENT, false, Statement::MINUS_U, (*$2), statementPtr()));
	  free($2);
	}

	|TOKEN_RAND TOKEN_LPAR TOKEN_RPAR
	{
	  DBUGPRT("expression_statement");
	  $$ = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::FUNCTION_STATEMENT, false, Statement::RAND));
	}

	|TOKEN_DOUBLE
	{
	  DBUGPRT("expression_statement");
	  $$ = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::NUMBER_STATEMENT, false, $1));
	}

	|TOKEN_INTEGER
	{
	  DBUGPRT("expression_statement");
 	  $$ = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::NUMBER_STATEMENT, false, (double)$1));
	}

	|TOKEN_STRING
	{
	  DBUGPRT("expression_statement");
 	  $$ = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::STRING_STATEMENT, false, *$1));
	}

	//////////////////////////////////////////////////
	// features
	//////////////////////////////////////////////////
	|expression_statement TOKEN_UNION expression_statement {
	  DBUGPRT("expression_statement");
	  $$ = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::UNIF_STATEMENT, false, (*$1), (*$3)));
	  free($1);
	  free($3);
	}

	|up {
	  DBUGPRT("expression_statement");
	  $$=$1;
	}

	|up2 {
	  DBUGPRT("expression_statement");
	  $$=$1;
	}

	|down {
	  DBUGPRT("expression_statement");
	  $$=$1;
	}

	|down2 {
	  DBUGPRT("expression_statement");
	  $$=$1;
	}

	|features {
	  DBUGPRT("expression_statement");
	  $$ = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::FEATURES_STATEMENT, false, *$1));
	  free($1);
	}

	//////////////////////////////////////////////////
	// constants
	//////////////////////////////////////////////////
	|TOKEN_NIL
	{
	  DBUGPRT("expression_statement");
	  $$ = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::NIL_STATEMENT, false));
	}

	|constant {
	  DBUGPRT("expression_statement");
	  $$ = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::CONSTANT_STATEMENT, false, *$1));
	  free($1);
	}

	//////////////////////////////////////////////////
	// variables
	//////////////////////////////////////////////////
	|TOKEN_ANONYMOUS
	{
	  DBUGPRT("expression_statement");
	  $$ = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::ANONYMOUS_STATEMENT, false, Value::STATIC_ANONYMOUS));
	}

	|variable {
	  DBUGPRT("expression_statement");
	  $$ = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::VARIABLE_STATEMENT, false, *$1));
	  free($1);
	}

	|TOKEN_LPAR expression_statement TOKEN_RPAR {
	  DBUGPRT("expression_statement");
	  $$=$2;
	}

	//////////////////////////////////////////////////
	// position
	//////////////////////////////////////////////////
	|dash_statement {
	  DBUGPRT("expression_statement");
	  $$=$1;
	}

	//////////////////////////////////////////////////
	// pairp
	//////////////////////////////////////////////////
	|pairp {
	  DBUGPRT("expression_statement");
	  $$ = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::PAIRP_STATEMENT, false, *$1));
	  free($1);
	}

	//////////////////////////////////////////////////
	// search
	//////////////////////////////////////////////////
	|TOKEN_SEARCH expression_statement TOKEN_ON TOKEN_IDENTIFIER {
	  	DBUGPRT("expression_statement");
	  	$$ = new statementPtr(Statement::create(ruleslineno,
						  parser.getTopBufferName(),
						  Statement::SEARCH_STATEMENT,
						  true,
						  *$2,
						  Vartable::stringToCode(*$4)));
		free($2);
	  	free($4);
	 }
	 ;

expression_statement_composite:
	expression_statement_composite TOKEN_COMMA expression_statement
	{
	  DBUGPRT("expression_statement_composite");
	  $$ = $1;
	  (*$$)->addStatement(*$3);
	  free($3);
	}

	|expression_statement
	{
	  DBUGPRT("expression_statement_composite");
	  $$ = new statementsPtr(Statements::create());
	  (*$$)->addStatement(*$1);
	  free($1);
	}
	;

up:
	TOKEN_UPARROW {
	  DBUGPRT("up");
	  $$ = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::INHERITED_FEATURES_STATEMENT, false));
	};

up2:
	TOKEN_UP2ARROW {
	  DBUGPRT("up2");
	  $$ = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::SYNTHESIZED_FEATURES_STATEMENT, false));
	};

down:
	TOKEN_DOWNARROW TOKEN_INTEGER
	{
	  DBUGPRT("down");
	  $$ = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::INHERITED_CHILDREN_FEATURES_STATEMENT, false, (unsigned int)$2-1));
	};

down2:
	TOKEN_DOWN2ARROW TOKEN_INTEGER
	{
	  DBUGPRT("down2");
	  $$ = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::SYNTHESIZED_CHILDREN_FEATURES_STATEMENT, false, (unsigned int)($2-1)));
	};

dash_statement:
	TOKEN_DASH TOKEN_INTEGER TOKEN_DOT TOKEN_INTEGER
	{
	  DBUGPRT("dash_statement");
	  $$ = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::DASH_STATEMENT, false, (unsigned int)($2-1), (unsigned int)($4-1)));
	}

	|TOKEN_DASH TOKEN_INTEGER
	{
	  DBUGPRT("dash_statement");
	  $$ = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::DASH_STATEMENT, false, (unsigned int)($2-1), (unsigned int)UINT_MAX));
	};

//////////////////////////
// Features
//////////////////////////
features:
	TOKEN_LBRACKET features_composite features_composite_tail TOKEN_RBRACKET
	{
	  DBUGPRT("features");
 	  $$ = $2;
	  if ($3) {
	    (*$$)->add(*$3);
	    free($3);
	  }
	}

	|TOKEN_LBRACKET TOKEN_RBRACKET
	{
	  DBUGPRT("features");
	  $$ = new featuresPtr(Features::create());
	};

features_composite_tail:
	/* empty */
	{
	    $$ = NULL;
	}

	|TOKEN_COMMA variable
	{
        $$ = new featurePtr(Feature::create(Feature::_VARIABLE_, *$2, valuePtr()));
    };

features_composite:
	features_composite TOKEN_COMMA feature
	{
	  DBUGPRT("feature_components");
	  $$ = $1;
	  (*$$)->add(*$3);
	  free($3);
	}

	|feature
	{
	  DBUGPRT("features_composite");
	  $$ = new featuresPtr(Features::create());
	  (*$$)->add(*$1);
	  free($1);
	}

	//…, @identifier
	|features_composite TOKEN_COMMA TOKEN_AROBASE TOKEN_IDENTIFIER
	{
	  DBUGPRT("features_composite");
	  featuresPtr found = parser.findMacros(*$4);
	  $$ = $1;
	  if (!(found)){
	     std::ostringstream oss; oss << "unknown macro: @" << *$4;
	     yyerror((char*)oss.str().c_str());
	  } else {
	    (*$$)->add(found->clone());
	  }
	  free($4);
	}

	//@identifier
	|TOKEN_AROBASE TOKEN_IDENTIFIER
	{
	  DBUGPRT("features_composite");
	  featuresPtr found = parser.findMacros(*$2);
	  $$ = new featuresPtr(Features::create());
	  if (!(found)){
	    std::ostringstream oss; oss << "***unknown macro: @" << *$2;
	    yyerror((char*)oss.str().c_str());
	  } else {
	    (*$$)->add(found->clone());
	  }
	  free($2);
	  };

feature:
	// LEMMA: lemma
	TOKEN_LEMMA TOKEN_COLON stringOrIdentifier
	{
	  DBUGPRT("feature");
	  $$ = new featurePtr(Feature::create(Feature::_LEMMA_, bitsetPtr(), Value::create(Value::IDENTIFIER_VALUE, *$3)));
	}

	// LEMMA: $X
	|TOKEN_LEMMA TOKEN_COLON variable
	{
	  DBUGPRT("feature");
	  $$ = new featurePtr(Feature::create(Feature::_LEMMA_, bitsetPtr(), Value::create(Value::VARIABLE_VALUE, *$3)));
	}

	// PRED: predicate
	|TOKEN_PRED TOKEN_COLON stringOrIdentifier
	{
	  DBUGPRT("feature");
	  $$ = new featurePtr(Feature::create(Feature::_PRED_, bitsetPtr(), Value::create(Value::IDENTIFIER_VALUE, *$3)));
	}

	// PRED: $X
	|TOKEN_PRED TOKEN_COLON variable
	{
	  DBUGPRT("feature");
	  $$ = new featurePtr(Feature::create(Feature::_PRED_, bitsetPtr(), Value::create(Value::VARIABLE_VALUE, *$3)));
	  free($3);
	}

	// FORM: $X
	|TOKEN_FORM TOKEN_COLON variable
	{
	  DBUGPRT("feature");
	  $$ = new featurePtr(Feature::create(Feature::_FORM_, bitsetPtr(), Value::create(Value::VARIABLE_VALUE, *$3)));
	  free($3);
	}

	|TOKEN_FORM TOKEN_COLON stringOrIdentifier
	{
	  DBUGPRT("feature");
	  $$ = new featurePtr(Feature::create(Feature::_FORM_, bitsetPtr(), Value::create(Value::FORM_VALUE, *$3)));
	}

	|identifier TOKEN_COLON feature_value
	{
	  DBUGPRT("feature");
	  $$ = new featurePtr(Feature::create(Feature::_CONSTANT_, *$1, *$3));
	  free($1);
	  free($3);
	}

	|identifier TOKEN_COLON TOKEN_STRING
	{
	  DBUGPRT("feature");
	  $$ = new featurePtr(Feature::create(Feature::_CONSTANT_, *$1, Value::create(Value::FORM_VALUE, *$3)));
	  free($1);
	}

	|variable TOKEN_COLON feature_value
	{
	  DBUGPRT("feature");
	  $$ = new featurePtr(Feature::create(Feature::_VARIABLE_, *$1, *$3));
	  free($1);
	  free($3);
	}
	;

feature_value:
	variable
	{
	  DBUGPRT("feature_value");
	  $$ = new valuePtr(Value::create(Value::VARIABLE_VALUE, *$1));
	  free($1);
	}

	|constant
	{
	  DBUGPRT("feature_value");
	  $$ = new valuePtr(Value::create(Value::CONSTANT_VALUE, *$1));
	  free($1);
	}

	|TOKEN_DOUBLE
	{
	  DBUGPRT("expression_statement");
	  $$ = new valuePtr(Value::create(Value::NUMBER_VALUE, $1));
	}

	|TOKEN_INTEGER
	{
	  DBUGPRT("expression_statement");
	  $$ = new valuePtr(Value::create(Value::NUMBER_VALUE, (double)$1));
	}

	|pairp
	{
	  DBUGPRT("feature_value");
	  $$ = new valuePtr(Value::create(*$1));
	  free($1);
	}

	|features
	{
	  DBUGPRT("feature_value");
	  $$ = new valuePtr(Value::create(*$1));
	  free($1);
	}

	|TOKEN_NIL
	{
	  DBUGPRT("feature_value");
	  $$ = new valuePtr(Value::STATIC_NIL);
	}

	|TOKEN_ANONYMOUS
	{
	  DBUGPRT("feature_value");
	  $$ = new valuePtr(Value::STATIC_ANONYMOUS);
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
 	  $$ = new bitsetPtr(Bitset::create(Vartable::createVariable(*$1)));
 	  free($1);
	};

variable:
	TOKEN_VARIABLE
	{
	  DBUGPRT("variable");
	  std::ostringstream oss;
	  oss << *$1;
  	  std::string str = oss.str();
	  $$ = new bitsetPtr(Bitset::create(Vartable::createVariable(str)));
	  free($1);
	};

pairp:
	TOKEN_LT pairp_elements TOKEN_GT
	{
	  DBUGPRT("list");
	  $$ = $2;
	}

	|TOKEN_LT TOKEN_GT
	{
	  DBUGPRT("list");
	  $$ = new pairpPtr(Pairp::NIL);
	}

	|TOKEN_LT pairp_elements TOKEN_DOUBLECOLON pairp_element TOKEN_GT
	{
	  DBUGPRT("list");
	  if ((*$2)->isPairp() && (*$2)->getCdr()->isNil())
	    $$ = new pairpPtr(Pairp::create((*$2)->getCar(), *$4));
	  else
	    $$ = new pairpPtr(Pairp::create(*$2, *$4));
	  free($2);
	  free($4);
	}

	|TOKEN_LT pairp_elements TOKEN_DOUBLECOLON TOKEN_NIL TOKEN_GT
	{
	  DBUGPRT("list");
	  if ((*$2)->isPairp() && (*$2)->getCdr()->isNil())
	    $$ = new pairpPtr(Pairp::create((*$2)->getCar(), Pairp::NIL));
	  else
	    $$ = new pairpPtr(Pairp::create(*$2, Pairp::NIL));
	  free($2);
	}
	
	 ;

pairp_elements:
	pairp_element TOKEN_COMMA pairp_elements
	{
	  DBUGPRT("pairp_elements");
	  $$ = new pairpPtr(Pairp::create(*$1, *$3));
	  free($1);
	  free($3);
	}

	|pairp_element
	{
	  DBUGPRT("pairp_elements");
	  $$ = new pairpPtr(Pairp::create(*$1, Pairp::NIL));
	  free($1);
	};

pairp_element:
	variable
	{
	  DBUGPRT("pairp_element");
	  $$ = new pairpPtr(Pairp::create(Value::create(Value::VARIABLE_VALUE, *$1)));
	  free($1);
	}

	|TOKEN_DOUBLE
	{
	  DBUGPRT("expression_statement");
	  $$ = new pairpPtr(Pairp::create(Value::create(Value::NUMBER_VALUE, $1)));
	}

 	|TOKEN_INTEGER
	{
	  DBUGPRT("expression_statement");
	  $$ = new pairpPtr(Pairp::create(Value::create(Value::NUMBER_VALUE, (double)$1)));
	}

	|constant
	{
	  DBUGPRT("pairp_element");
	  $$ = new pairpPtr(Pairp::create(Value::create(Value::CONSTANT_VALUE, *$1)));
	  free($1);
	}

	|features
	{
	  DBUGPRT("pairp_element");
	  $$ = new pairpPtr(Pairp::create(Value::create(*$1)));
	  free($1);
	}

	|pairp
	{
	  DBUGPRT("pairp_element");
	  $$=$1;
	};

%%
