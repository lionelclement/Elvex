%{

/* **************************************************
 *
 * ELVEX
 *
 * Copyright 2014-2026 LABRI,
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
  
 extern uint32_t ruleslineno;
 extern unsigned int ruleslex();
 extern Parser parser;
uint32_t headLineno;
uint32_t currentRhsSize;
bool pref_trace;
bool pref_withSpaces;
bool pref_unordered;

  void ruleserror(const char* str) {
      std::ostringstream oss;
      oss << str << " in " << parser.getTopBufferName() << " (" << ruleslineno << ")";
      throw parser_exception(oss);
  }

  void yywarning(const char* str){
      std::ostringstream oss;
      oss << "warning: " << str << " " << parser.getTopBufferName() << " (" << ruleslineno << ")" << std::endl;
      std::cerr << oss.str() << std::endl;
  }

  %}

%union{
  int64_t integer_slot;
  double double_slot;
  termsPtr* terms_slot; //(A|B)
  std::vector<termsPtr>* vector_terms_slot; // X Y
  std::vector<uint32_t>* order_chain_slot;
  std::vector<statementPtr>* vector_statement_slot;
  std::string* string_slot;
  std::pair<uint32_t, featuresPtr >* entry_slot;
  std::vector<std::pair<uint32_t, featuresPtr> >* entries_slot;
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
%token TOKEN_RIGHT_ARROW TOKEN_UP_ARROW TOKEN_DOUBLE_UP_ARROW TOKEN_DOWN_ARROW TOKEN_DOUBLE_DOWN_ARROW

// PAR
%token TOKEN_LPAR TOKEN_RPAR
%token TOKEN_LBRACE TOKEN_RBRACE TOKEN_LBRACKET TOKEN_RBRACKET

// PONCT
%token TOKEN_HASH
%token TOKEN_AT_SIGN
%token TOKEN_SEMI TOKEN_DOT TOKEN_COLON TOKEN_LIST_CONS TOKEN_COMMA

// KEYWORDS
%token TOKEN_MACROS TOKEN_RULES TOKEN_INPUT TOKEN_LEXICON
%token TOKEN_LEMMA TOKEN_HEAD TOKEN_FORM
%token TOKEN_ATTEST TOKEN_PRINT TOKEN_PRINTLN TOKEN_EPRINT TOKEN_EPRINTLN
%token TOKEN_IF TOKEN_ELSE
%token TOKEN_DEFERRED
%token TOKEN_NIL TOKEN_TRUE TOKEN_FALSE
%token TOKEN_RAND
%token TOKEN_TRACE TOKEN_WITH_SPACES TOKEN_WITHOUT_SPACES 
%token TOKEN_UNORDERED
%token TOKEN_ORDER TOKEN_BY
%token TOKEN_MIN
%token TOKEN_MAX

// OPERATORS
%token TOKEN_UNIFY TOKEN_SUBSUME TOKEN_ASSIGNMENT TOKEN_PIPE TOKEN_NOT
%token TOKEN_OR TOKEN_AND TOKEN_IMPLICATION TOKEN_EQUIV
%token TOKEN_PLUS TOKEN_MINUS TOKEN_TIMES TOKEN_DIVIDE TOKEN_MODULO
%token TOKEN_FLOOR
%token TOKEN_EQUAL TOKEN_DIFF TOKEN_LT TOKEN_LE TOKEN_GT TOKEN_GE
%token TOKEN_DOUBLE_LT TOKEN_DOUBLE_GT

 // LITERALS
%token<string_slot> TOKEN_IDENTIFIER TOKEN_STRING 

%token<integer_slot> TOKEN_INTEGER

%token<double_slot> TOKEN_DOUBLE

 // VARIABLES
%token<string_slot> TOKEN_VARIABLE
%token TOKEN_ANONYMOUS_VARIABLE

%type<string_slot> identifier identifier_or_string strings
%type<integer_slot> term variable
%type<terms_slot> terms terms_disj
%type<vector_terms_slot> terms_vector
%type<entries_slot> lexical_entries
%type<entry_slot> lexical_entry

%type<features_slot> features features_composite
%type<feature_slot> feature features_composite_tail
%type<bits_slot> constant constants field_access_attribute

%type<value_slot> feature_value
%type<pairp_slot> pairp pairp_elements pairp_element

%type<statements_slot> structure_statement list_statement compound_expression_statement


%type<statement_slot> statement statements
%type<statement_slot> order_statement
%type<statement_slot> expression_statement
%type<statement_slot> left_hand_side_subset_statement right_hand_side_subset_statement
%type<statement_slot> left_hand_side_assignment_statement right_hand_side_assignment_statement
%type<statement_slot> up_statement down_statement double_up_statement double_down_statement
%type<statement_slot> hash_statement
%type<statement_slot> field_access_root field_access_statement feature_statement_value
%type<statement_slot> order_relative_root order_relative_path

%type<order_chain_slot> order_chain order_index_list

%nonassoc TOKEN_IMPLICATION TOKEN_EQUIV
%left TOKEN_OR
%left TOKEN_AND
%right TOKEN_NOT
%left TOKEN_UNIFY
%nonassoc TOKEN_LT TOKEN_LE TOKEN_GT TOKEN_GE TOKEN_EQUAL TOKEN_DIFF TOKEN_SUBSUME
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
	}
	;

begin:
	TOKEN_MACROS TOKEN_LPAR macros TOKEN_RPAR{
	  DBUGPRT("begin grammar");
	}

	|TOKEN_RULES TOKEN_LPAR rules TOKEN_RPAR{
	  DBUGPRT("begin grammar");
	}

	|TOKEN_INPUT TOKEN_LPAR term features TOKEN_RPAR {
	  DBUGPRT("begin input");
	  parser.setStartTerm($3);
	  parser.setStartFeatures(*$4);
	  delete($4);
	}

	|TOKEN_INPUT TOKEN_LPAR term TOKEN_RPAR {
	  DBUGPRT("begin input");
	  parser.setStartTerm($3);
	  parser.setStartFeatures(Features::create());
	 }

	|TOKEN_LEXICON TOKEN_LPAR dictionary TOKEN_RPAR{
	  DBUGPRT("begin lexicon");
	  //COUT_LINE;
	  //parser.printCacheLexicon(std::cout);
	}

	|TOKEN_HASH TOKEN_LPAR features TOKEN_RPAR
	{
	  DBUGPRT("begin features");
	  parser.setLocalFeatures(*$3);
	  delete($3);
	}
	;

macros:
	macro_line macros {
	  DBUGPRT("macros");
	}

	|macro_line {
	  DBUGPRT("macros");
	}
	;

macro_line:
	//
	TOKEN_AT_SIGN TOKEN_IDENTIFIER TOKEN_ASSIGNMENT features TOKEN_SEMI
	{
	  DBUGPRT("dictionary_line");
	  parser.addMacros(*$2, *$4);
	  delete($2);
	  delete($4);
	}
	;

dictionary:
	dictionary_line dictionary {
	  DBUGPRT("dictionary");
	}

	|dictionary_line {
	  DBUGPRT("dictionary");
	}
	;

dictionary_line:
	// FORM constantNoun ;
	TOKEN_FORM TOKEN_IDENTIFIER TOKEN_SEMI
	{
	  DBUGPRT("dictionary_line");
	  uint32_t code = Vartable::nameToCode(*$2);
	  delete($2);
	  // constantNoun => (0 => args)
	  auto foundCode = parser.findCacheLexicon(code);
	  Parser::entries_map* formToEntries;
	  if (foundCode != parser.cendCacheLexicon()){
	    formToEntries = foundCode->second;
	  } else {
	    formToEntries = new Parser::entries_map();
	    parser.insertCacheLexicon(std::make_pair(code, formToEntries));
	  }
	  auto foundHead = formToEntries->find(Vartable::code_for_IS_A_FORM);
	  entriesPtr entries;
	  if (foundHead != formToEntries->cend()){
	    entries = foundHead->second;
	  } else {
	    entries = Entries::create();
	    formToEntries->insert(std::make_pair(Vartable::code_for_IS_A_FORM, entries));
	  }
	  entries->add(Entry::create(Features::create()));
	}

	|TOKEN_FORM TOKEN_IDENTIFIER features TOKEN_SEMI
	{
	  DBUGPRT("dictionary_line");
	  uint32_t code = Vartable::nameToCode(*$2);
	  delete($2);
	  // constantNoun => (0 => args)
	  auto foundCode = parser.findCacheLexicon(code);
	  Parser::entries_map* formToEntries;
	  if (foundCode != parser.cendCacheLexicon()) {
	    formToEntries = foundCode->second;
	  } else {
	    formToEntries = new Parser::entries_map;
	    parser.insertCacheLexicon(std::make_pair(code, formToEntries));
	  }
	  auto foundHead = formToEntries->find(Vartable::code_for_IS_A_FORM);
	  entriesPtr entries;
	  if (foundHead != formToEntries->cend()){
	    entries = foundHead->second;
	  } else {
	    entries = Entries::create();
	    formToEntries->insert(std::make_pair(Vartable::code_for_IS_A_FORM, entries));
	  }
	  entries->add(Entry::create(*$3));
	  delete($3);
	}

	//
	|identifier_or_string lexical_entries TOKEN_SEMI
	{
	  DBUGPRT("dictionary_line");
	  for (auto entries_map = (*$2).cbegin() ; entries_map != (*$2).cend() ; ++entries_map) {
		uint32_t pos = entries_map->first;
		featuresPtr features = entries_map->second;
		uint32_t head = features->assignHead();
		
		//std::cerr << Vartable::codeToName(pos) << std::endl;
		//features->flatPrint(std::cerr);
		//std::cerr << Vartable::codeToName(head) << std::endl;
		
	    //(*entry)->setForm(*$1);
	    entriesPtr entries;
	    Parser::entries_map* headToEntries;
		auto foundCode = parser.findCacheLexicon(pos);
	    if (foundCode != parser.cendCacheLexicon()){
	      headToEntries = foundCode->second;
	    } else {
	      headToEntries = new Parser::entries_map;
	      parser.insertCacheLexicon(std::make_pair(pos, headToEntries));
	    }
	    Parser::entries_map::iterator foundHead = headToEntries->find(head);
	    if (foundHead != headToEntries->cend()){
	      entries = foundHead->second;
	    } else {
	      entries = Entries::create();
	      headToEntries->insert(std::make_pair(head, entries));
	    }
	    entries->add(Entry::create(*$1, features));
	  }
	  delete($2);
	}

	|TOKEN_SEMI
	{
	  DBUGPRT("dictionary_line");
	}
	;

lexical_entries:
	lexical_entry TOKEN_PIPE lexical_entries
	{
	  DBUGPRT("lexical_entries");
	  $$ = $3;
	  $$->push_back(*$1);
	  delete($1);
	}

	|lexical_entry {
	  DBUGPRT("lexical_entries");
	  $$ = new std::vector<std::pair<uint32_t, featuresPtr> >;
	  $$->push_back(*$1);
	  delete($1);
	}
	;

lexical_entry:
	// pos [...]
	TOKEN_IDENTIFIER features
	{
	  DBUGPRT("lexical_entry");
	  $$ = new std::pair<uint32_t, featuresPtr>(std::make_pair(Vartable::nameToCode(*$1), *$2));
	  delete($1);
	  delete($2);
	}

	// pos
	|TOKEN_IDENTIFIER
	{
	  DBUGPRT("lexical_entry");
	  $$ = new std::pair<uint32_t, featuresPtr>(std::make_pair(Vartable::nameToCode(*$1), Features::create()));
	  delete($1);
	}
	;

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
	}
	;

pref_rule:
	 pref_rule TOKEN_TRACE
	{
	  DBUGPRT("pref_rule");
	  if (pref_trace)
		yyerror((char*)"@trace already done");
	  pref_trace = true;
	}

	|pref_rule TOKEN_WITH_SPACES 
	{
	  DBUGPRT("pref_rule");
	  if (pref_withSpaces)
		yyerror((char*)"@withSpaces already done");
	  pref_withSpaces = true;
	}

	|pref_rule TOKEN_WITHOUT_SPACES 
	{
	  DBUGPRT("pref_rule");
	  if (pref_withSpaces)
		pref_withSpaces = false;
	}

	|pref_rule TOKEN_UNORDERED 
	{
	  DBUGPRT("pref_rule");
	  pref_unordered = true;
	}

	| /* empty */ {
	  DBUGPRT("pref_rule");
	  // initialization
	  pref_trace = false;
	  pref_withSpaces = true;
	  pref_unordered = false;
	}
	;

rule:
    pref_rule term TOKEN_RIGHT_ARROW terms_vector
    {
      currentRhsSize = static_cast<uint32_t>($4->size());
    }
    structure_statement
    {
      DBUGPRT("rule");

      if (pref_unordered && $4->size() <= 1) {
        yyerror((char*)"This rule with fewer than 2 terms must not be unordered");
      }

      rulePtr rule = Rule::create(
        headLineno,
        parser.getTopBufferName(),
        pref_withSpaces,
        pref_unordered,
        $2,
        *$4,
        $6 ? *$6 : statementsPtr()
      );

      rule->setTrace(pref_trace);
      parser.getRules().addRule(rule);

      if (!parser.getRules().getStartTerm()) {
        parser.getRules().setStartTerm($2);
      }

      delete($4);

      if ($6) {
        delete($6);
      }
    }

    |pref_rule term TOKEN_RIGHT_ARROW
    {
      currentRhsSize = 0;
    }
    structure_statement
    {
      DBUGPRT("Rule");

      rulePtr rule = Rule::create(
        headLineno,
        parser.getTopBufferName(),
        pref_withSpaces,
        pref_unordered,
        $2,
        $5 ? *$5 : statementsPtr()
      );

      rule->setTrace(pref_trace);
      parser.getRules().addRule(rule);

      if (!parser.getRules().getStartTerm()) {
        parser.getRules().setStartTerm($2);
      }

      if ($5) {
        delete($5);
      }
    }
    ;
	
terms_vector:
	terms_vector terms {
	  DBUGPRT("term_vector");
	  $$=$1;
	  $$->push_back(*$2);
	  delete($2);
	}

	|terms {
	  DBUGPRT("term_vector");
	  $$ = new std::vector< termsPtr >;
	  $$->push_back(*$1);
	  delete($1);
	}
	;

terms:
	terms_disj {
	  DBUGPRT("term");
	  $$=$1;
	}

	|TOKEN_LPAR terms_disj TOKEN_RPAR {
	  DBUGPRT("term");
	  $$ = $2;
	  (*$$)->setOptional();
	}
	;

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
	}
	;

term:
	TOKEN_IDENTIFIER
	{
	  DBUGPRT("term_id");
	  $$ = Vartable::nameToCode(*$1);
	  delete($1);
	}

	|TOKEN_VARIABLE
	{
	  DBUGPRT("term_id");
	  $$ = Vartable::nameToCode(*$1);
	  delete($1);
	}

	|error
	{
	  YYABORT;
	}
	;

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
	}
	;

list_statement:
	statement
	{
	  DBUGPRT("list_statement");
	  $$ = new statementsPtr(Statements::create());
	  (*$$)->addStatement(*$1);
	  delete($1);
	}

	|list_statement statement {
	  DBUGPRT("list_statement");
	  $$ = $1;
	  (*$$)->addStatement(*$2);
	  delete($2);
	}
	;

statements:
	TOKEN_LBRACE list_statement TOKEN_RBRACE
	{
	  DBUGPRT("statement");
	  $$ = new statementPtr(Statement::createStatements(ruleslineno, parser.getTopBufferName(), Statement::STMS_STATEMENT, false, *$2));
	  delete($2);
	}

	|TOKEN_LBRACE TOKEN_RBRACE
	{
	  DBUGPRT("statement");
	  $$ = new statementPtr(Statement::createStatements(ruleslineno, parser.getTopBufferName(), Statement::STMS_STATEMENT, false, Statements::create()));
	}
	;

statement:
	statements {
	  DBUGPRT("statement");
	  $$=$1;
	 }

	|features TOKEN_SEMI {
	  DBUGPRT("statement");
	  $$ = new statementPtr(Statement::createFeatures(ruleslineno, parser.getTopBufferName(), Statement::GUARD_STATEMENT, true, *$1));
	  delete($1);
	}

    |order_statement
    {
      DBUGPRT("statement");
      $$ = $1;
    }
	
	|TOKEN_ATTEST expression_statement TOKEN_SEMI {
	  DBUGPRT("statement");
	  $$ = new statementPtr(Statement::createFirst(ruleslineno, parser.getTopBufferName(), Statement::ATTEST_STATEMENT, true, *$2));
	  delete($2);
	}

	|TOKEN_PRINT compound_expression_statement TOKEN_SEMI {
	  DBUGPRT("statement");
		$$ = new statementPtr(Statement::createStatements(
			ruleslineno, 
			parser.getTopBufferName(), 
			Statement::PRINT_STATEMENT, 
			true, 
			*$2));
	  delete($2);
	}

	|TOKEN_PRINTLN compound_expression_statement TOKEN_SEMI {
	  	DBUGPRT("statement");
		$$ = new statementPtr(Statement::createStatements(
			ruleslineno, 
			parser.getTopBufferName(), 
			Statement::PRINTLN_STATEMENT, 
			true, 
			*$2));
	  delete($2);
	}

	|TOKEN_EPRINT compound_expression_statement TOKEN_SEMI {
	  DBUGPRT("statement");
		$$ = new statementPtr(Statement::createStatements(
			ruleslineno, 
			parser.getTopBufferName(), 
			Statement::EPRINT_STATEMENT, 
			true, 
			*$2));
	  delete($2);
	}

	|TOKEN_EPRINTLN compound_expression_statement TOKEN_SEMI {
	  	DBUGPRT("statement");
		$$ = new statementPtr(Statement::createStatements(
			ruleslineno, 
			parser.getTopBufferName(), 
			Statement::EPRINTLN_STATEMENT, 
			true, 
			*$2));
	  delete($2);
	}

	|left_hand_side_assignment_statement TOKEN_ASSIGNMENT right_hand_side_assignment_statement TOKEN_SEMI {
	  DBUGPRT("statement");
	  $$ = new statementPtr(Statement::createFirstSecond(ruleslineno, parser.getTopBufferName(), Statement::ASSIGNMENT_STATEMENT, true, *$1, *$3));
	  // <X, …> = <…>
	  // <X, …> = $X
	  if (((*$1)->isPairp()) 
	  		&& (((*$3)->isPairp())
				||((*$3)->isVariable()) 
				||((*$3)->isFieldAccess()))) {
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
					||((*$3)->isDown2())
					||((*$3)->isFieldAccess())))
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
					||((*$3)->isDown2())
					||((*$3)->isFieldAccess())))
	    ;
	  // $X = $Y
	  // $X = a
	  // $X = <…>
	  // $X = […]
	  // $X = ↑
	  // $X = … ∪ …
	  // $X = ⇓j
	  // $X = <expr>
	  //
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
			  ||((*$3)->isFieldAccess())));
	  else {
	    yyerror((char*)"bad assignment expression");
	  }
	  delete($1);
	  delete($3);
	}

	|left_hand_side_subset_statement TOKEN_SUBSUME right_hand_side_subset_statement TOKEN_SEMI {
	  DBUGPRT("statement");
	  $$ = new statementPtr(Statement::createFirstSecond(ruleslineno, parser.getTopBufferName(), Statement::SUBSUME_STATEMENT, true, (*$1), (*$3)));
	  // […] ⊂ ↑
	  // […] ⊂ ⇓j
	  // […] ⊂ $X
	  if (((*$1)->isFeatures()) 
	  		&& (((*$3)->isUp())
					||((*$3)->isDown2())
	   				  ||((*$3)->isFieldAccess())
					||((*$3)->isVariable())))
	    ;
	  else
	    yyerror((char* )"bad subsumption expression");
	  delete($1);
	  delete($3);
	}

	|TOKEN_IF TOKEN_LPAR expression_statement TOKEN_RPAR statement %prec TOKEN_NOELSE {
	  DBUGPRT("statement");
	  $$ = new statementPtr(Statement::createFirstSecond(ruleslineno,
						parser.getTopBufferName(), 
						Statement::IF_STATEMENT,
						  true, 
						  *$3,
						  Statement::createFirst(ruleslineno, parser.getTopBufferName(), Statement::THEN_STATEMENT, false, *$5)));
	  delete($3);
	  delete($5);
	}

	|TOKEN_IF TOKEN_LPAR expression_statement TOKEN_RPAR statement TOKEN_ELSE statement {
	  DBUGPRT("statement");
	  $$ = new statementPtr(Statement::createFirstSecond(ruleslineno,
						  parser.getTopBufferName(),
						  Statement::IF_STATEMENT,
						  true, 
						  (*$3),
						  Statement::createFirstSecond(ruleslineno, parser.getTopBufferName(), Statement::THEN_ELSE_STATEMENT, false, *$5, *$7)));
	  delete($3);
	  delete($5);
	  delete($7);
	}

	|TOKEN_DEFERRED TOKEN_LPAR expression_statement TOKEN_RPAR statement {
	  DBUGPRT("statement");
	  $$ = new statementPtr(Statement::createFirstSecond(ruleslineno,
						parser.getTopBufferName(), 
						Statement::DEFERRED_STATEMENT,
						true, 
						*$3,
						*$5));
	  delete($3);
	  delete($5);
	}
	;

order_statement:
	// order 1 < 2 < 3;
    TOKEN_ORDER order_chain TOKEN_SEMI
	{
	DBUGPRT("order_statement");

	if ($2->size() < 2) {
		yyerror((char*)"order chain must contain at least two indexes");
	}

	$$ = new statementPtr(
		Statement::createOrder(
		ruleslineno,
		parser.getTopBufferName(),
		Statement::ORDER_CHAIN_STATEMENT,
		true,
		*$2
		)
	);

	delete($2);
	}

	// order << 2;
    |TOKEN_ORDER TOKEN_DOUBLE_LT TOKEN_INTEGER TOKEN_SEMI
    {
      DBUGPRT("order_statement");

      if ($3 < 1 || static_cast<uint32_t>($3) > currentRhsSize) {
        yyerror((char*)"bad order index");
      }

      $$ = new statementPtr(
        Statement::createOrder(
          ruleslineno,
          parser.getTopBufferName(),
          Statement::ORDER_FIRST_STATEMENT,
          true,
          static_cast<uint32_t>($3 - 1)
        )
      );
    }

	// order >> 2;
    |TOKEN_ORDER TOKEN_DOUBLE_GT TOKEN_INTEGER TOKEN_SEMI
    {
      DBUGPRT("order_statement");

      if ($3 < 1 || static_cast<uint32_t>($3) > currentRhsSize) {
        yyerror((char*)"bad order index");
      }

      $$ = new statementPtr(
        Statement::createOrder(
          ruleslineno,
          parser.getTopBufferName(),
          Statement::ORDER_LAST_STATEMENT,
          true,
          static_cast<uint32_t>($3 - 1)
        )
      );
    }
	
	// order 2, 3 by ⇓.prosody.weight;
	| TOKEN_ORDER order_index_list TOKEN_BY order_relative_path TOKEN_SEMI
    {
		DBUGPRT("order_statement");
		$$ = new statementPtr(
			Statement::createOrder(
				ruleslineno,
				parser.getTopBufferName(),
				Statement::ORDER_FIELD_ACCESS_STATEMENT,
				true,
				*$2, *$4
			)
		);
		delete($2);
		delete($4);
    }
	;
	
order_index_list:
    TOKEN_INTEGER
	{
      DBUGPRT("order_index_list");
      if ($1 < 1 || static_cast<uint32_t>($1) > currentRhsSize) {
        yyerror((char*)"bad order index");
      }

      $$ = new std::vector<uint32_t>();
      $$->push_back(static_cast<uint32_t>($1 - 1));
	}
  
	| order_index_list TOKEN_COMMA TOKEN_INTEGER
	{
		DBUGPRT("order_index_list");
		if ($3 < 1 || static_cast<uint32_t>($3) > currentRhsSize) {
		yyerror((char*)"bad order index");
		}

		uint32_t index = static_cast<uint32_t>($3 - 1);

		for (auto previous : *$1) {
			if (previous == index) {
			yyerror((char*)"duplicate index in order chain");
			}
		}

		$$ = $1;
		$$->push_back(index);
	}
	;
  
order_relative_path:
    order_relative_root TOKEN_DOT field_access_attribute
	{
	  DBUGPRT("order_relative_path");
	  $$ = new statementPtr(
		Statement::createFieldAccess(
		  ruleslineno,
		  parser.getTopBufferName(),
		  false,
		  *$1,
		  *$3
		)
	  );
	  delete($1);
	  delete($3);
	}

  | order_relative_path TOKEN_DOT field_access_attribute 
  {
	  DBUGPRT("order_relative_path");
	  $$ = new statementPtr(
		Statement::createFieldAccess(
		  ruleslineno,
		  parser.getTopBufferName(),
		  false,
		  *$1,
		  *$3
		)
	  );
	  delete($1);
	  delete($3);
  }
  ;
  
order_relative_root:
	TOKEN_DOWN_ARROW {
	  DBUGPRT("order_relative_root inherited child");
	  $$ = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::INHERITED_CHILDREN_FEATURES_STATEMENT, false, UINT8_MAX));
	}

	|TOKEN_DOUBLE_DOWN_ARROW {
	  DBUGPRT("order_relative_root synthesized child");
	  $$ = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::SYNTHESIZED_CHILDREN_FEATURES_STATEMENT, false, UINT8_MAX));
	}
	;


order_chain:
    TOKEN_INTEGER TOKEN_LT TOKEN_INTEGER
    {
      DBUGPRT("order_chain");

      if ($1 < 1 || static_cast<uint32_t>($1) > currentRhsSize) {
        yyerror((char*)"bad order index");
      }
      if ($3 < 1 || static_cast<uint32_t>($3) > currentRhsSize) {
        yyerror((char*)"bad order index");
      }

      uint32_t index1 = static_cast<uint32_t>($1 - 1);
      uint32_t index2 = static_cast<uint32_t>($3 - 1);

      if (index1 == index2) {
        yyerror((char*)"duplicate index in order chain");
      }

      $$ = new std::vector<uint32_t>();
      $$->push_back(index1);
      $$->push_back(index2);
    }

  | order_chain TOKEN_LT TOKEN_INTEGER
    {
      DBUGPRT("order_chain");

      if ($3 < 1 || static_cast<uint32_t>($3) > currentRhsSize) {
        yyerror((char*)"bad order index");
      }

      uint32_t index = static_cast<uint32_t>($3 - 1);

      for (auto previous : *$1) {
        if (previous == index) {
          yyerror((char*)"duplicate index in order chain");
        }
      }

      $$ = $1;
      $$->push_back(index);
    }
  ;
  
left_hand_side_subset_statement:
	features 
	{
	  DBUGPRT("left_hand_side_statement");
	  $$ = new statementPtr(Statement::createFeatures(ruleslineno, parser.getTopBufferName(), Statement::FEATURES_STATEMENT, false, *$1));
	  delete($1);
	}
	;

right_hand_side_subset_statement:
	variable 
	{
	  DBUGPRT("right_hand_side_subset_statement");
	  $$ = new statementPtr(Statement::createVariable(ruleslineno, parser.getTopBufferName(), false, $1));
	}

	|up_statement 
	{
	  DBUGPRT("right_hand_side_subset_statement");
	  $$=$1;
	}

	|double_down_statement 
	{
	  DBUGPRT("right_hand_side_subset_statement");
	  $$=$1;
	}

	|field_access_statement 
	{
	  DBUGPRT("right_hand_side_subset_statement");
	  $$=$1;
	}

	|features 
	{
	  DBUGPRT("right_hand_side_subset_statement");
	  $$ = new statementPtr(Statement::createFeatures(ruleslineno, parser.getTopBufferName(), Statement::FEATURES_STATEMENT, false, *$1));
	  delete($1);
	}
	;

left_hand_side_assignment_statement:
	double_up_statement 
	{
	  DBUGPRT("left_hand_side_statement");
	  $$=$1;
	}

	|down_statement 
	{
	  DBUGPRT("left_hand_side_statement");
	  $$=$1;
	}

	|variable {
	  DBUGPRT("left_hand_side_statement");
	  $$ = new statementPtr(Statement::createVariable(ruleslineno, parser.getTopBufferName(), false, $1));
	}

	|TOKEN_LT variable TOKEN_LIST_CONS variable TOKEN_GT
	{
	  DBUGPRT("left_hand_side_statement");
	  $$ = new statementPtr(Statement::createPairp(ruleslineno, parser.getTopBufferName(), false, 
						Pairp::create(Pairp::create(Value::createVariable($2)),
							     Pairp::create(Value::createVariable($4)))));
	}
	;

right_hand_side_assignment_statement:
	expression_statement {
	  DBUGPRT("right_hand_side_statement");
	  $$=$1;
	}
	;

expression_statement:
	//////////////////////////////////////////////////
	// logic
	//////////////////////////////////////////////////
	expression_statement TOKEN_OR expression_statement {
	  DBUGPRT("expression_statement");
	  $$ = new statementPtr(Statement::createFunction(ruleslineno, parser.getTopBufferName(), false, Statement::OR, (*$1), (*$3)));
	  delete($1);
	  delete($3);
	}

	|expression_statement TOKEN_AND expression_statement {
	  DBUGPRT("expression_statement");
	  $$ = new statementPtr(Statement::createFunction(ruleslineno, parser.getTopBufferName(), false, Statement::AND, (*$1), (*$3)));
	  delete($1);
	  delete($3);
	}

	|expression_statement TOKEN_IMPLICATION expression_statement {
	  DBUGPRT("expression_statement");
	  $$ = new statementPtr(Statement::createFunction(ruleslineno, parser.getTopBufferName(), false, Statement::OR, Statement::createFunction(ruleslineno, parser.getTopBufferName(), false, Statement::NOT, (*$1)), (*$3)));
	  delete($1);
	  delete($3);
	}

	|expression_statement TOKEN_EQUIV expression_statement {
	  DBUGPRT("expression_statement");
	  $$ = new statementPtr(Statement::createFunction(ruleslineno, parser.getTopBufferName(), false, Statement::AND,
						                    Statement::createFunction(ruleslineno, parser.getTopBufferName(), false, Statement::OR,
								                Statement::createFunction(ruleslineno, parser.getTopBufferName(), false, Statement::NOT, (*$1)),
								                (*$3)),
						                    Statement::createFunction(ruleslineno, parser.getTopBufferName(), false, Statement::OR,
								                (*$1),
								                Statement::createFunction(ruleslineno, parser.getTopBufferName(), false, Statement::NOT, (*$3)))));
	  delete($1);
	  delete($3);
	}

	|TOKEN_NOT expression_statement {
	  DBUGPRT("expression_statement");
	  $$ = new statementPtr(Statement::createFunction(ruleslineno, parser.getTopBufferName(), false, Statement::NOT, (*$2)));
	  delete($2);
	}

	|expression_statement TOKEN_EQUAL expression_statement {
	  DBUGPRT("expression_statement");
	  $$ = new statementPtr(Statement::createFunction(ruleslineno, parser.getTopBufferName(), false, Statement::EQUAL, (*$1), (*$3)));
	  delete($1);
	  delete($3);
	}

	|expression_statement TOKEN_DIFF expression_statement {
	  DBUGPRT("expression_statement");
	  $$ = new statementPtr(Statement::createFunction(ruleslineno, parser.getTopBufferName(), false, Statement::DIFF, (*$1), (*$3)));
	  delete($1);
	  delete($3);
	}

	|expression_statement TOKEN_LT expression_statement {
	  DBUGPRT("expression_statement");
	  $$ = new statementPtr(Statement::createFunction(ruleslineno, parser.getTopBufferName(), false, Statement::LT, (*$1), (*$3)));
	  delete($1);
	  delete($3);
	}

	|expression_statement TOKEN_LE expression_statement {
	  DBUGPRT("expression_statement");
	  $$ = new statementPtr(Statement::createFunction(ruleslineno, parser.getTopBufferName(), false, Statement::LE, (*$1), (*$3)));
	  delete($1);
	  delete($3);
	}

	|expression_statement TOKEN_GT expression_statement {
	  DBUGPRT("expression_statement");
	  $$ = new statementPtr(Statement::createFunction(ruleslineno, parser.getTopBufferName(), false, Statement::GT, (*$1), (*$3)));
	  delete($1);
	  delete($3);
	}

	|expression_statement TOKEN_GE expression_statement {
	  DBUGPRT("expression_statement");
	  $$ = new statementPtr(Statement::createFunction(ruleslineno, parser.getTopBufferName(), false, Statement::GE, (*$1), (*$3)));
	  delete($1);
	  delete($3);
	}

    |left_hand_side_subset_statement TOKEN_SUBSUME right_hand_side_subset_statement
    {
      DBUGPRT("expression_statement");

      $$ = new statementPtr(
        Statement::createFirstSecond(
          ruleslineno,
          parser.getTopBufferName(),
          Statement::SUBSUME_STATEMENT,
          false,
          (*$1),
          (*$3)
        )
      );

      // […] ⊂ ↑
      // […] ⊂ ⇓j
      // […] ⊂ $X
      if (((*$1)->isFeatures())
          && (((*$3)->isUp())
              || ((*$3)->isDown2())
              || ((*$3)->isFieldAccess())
              || ((*$3)->isVariable())))
        ;
      else
        yyerror((char*)"bad subsumption expression");

      delete($1);
      delete($3);
    }
	
	//////////////////////////////////////////////////
	// arithmetic, string, lists
	//////////////////////////////////////////////////
	|expression_statement TOKEN_PLUS expression_statement
	{
	  DBUGPRT("expression_statement");
	  $$ = new statementPtr(Statement::createFunction(ruleslineno, parser.getTopBufferName(), false, Statement::PLUS, (*$1), (*$3)));
	  delete($1);
	  delete($3);
	}

	|expression_statement TOKEN_MINUS expression_statement
	{
	  DBUGPRT("expression_statement");
	  $$ = new statementPtr(Statement::createFunction(ruleslineno, parser.getTopBufferName(), false, Statement::MINUS, (*$1), (*$3)));
	  delete($1);
	  delete($3);
	}

	|expression_statement TOKEN_TIMES expression_statement
	{
	  DBUGPRT("expression_statement");
	  $$ = new statementPtr(Statement::createFunction(ruleslineno, parser.getTopBufferName(), false, Statement::TIMES, (*$1), (*$3)));
	  delete($1);
	  delete($3);
	}

	|expression_statement TOKEN_DIVIDE expression_statement
	{
	  DBUGPRT("expression_statement");
	  $$ = new statementPtr(Statement::createFunction(ruleslineno, parser.getTopBufferName(), false, Statement::DIVIDE, (*$1), (*$3)));
	  delete($1);
	  delete($3);
	}

	|expression_statement TOKEN_MODULO expression_statement
	{
	  DBUGPRT("expression_statement");
	  $$ = new statementPtr(Statement::createFunction(ruleslineno, parser.getTopBufferName(), false, Statement::MODULO, (*$1), (*$3)));
	  delete($1);
	  delete($3);
	}

	|TOKEN_MINUS expression_statement %prec TOKEN_MINUS_U
	{
	  DBUGPRT("expression_statement");
	  $$ = new statementPtr(Statement::createFunction(ruleslineno, parser.getTopBufferName(), false, Statement::MINUS_U, (*$2), statementPtr()));
	  delete($2);
	}

	|TOKEN_FLOOR TOKEN_LPAR expression_statement TOKEN_RPAR
	{
	  DBUGPRT("expression_statement");
	  $$ = new statementPtr(Statement::createFunction(ruleslineno, parser.getTopBufferName(), false, Statement::FLOOR, (*$3), statementPtr()));
	  delete($3);
	}

	|TOKEN_MIN TOKEN_LT expression_statement TOKEN_COMMA expression_statement TOKEN_GT
	{
	  DBUGPRT("expression_statement");
	  $$ = new statementPtr(Statement::createFunction(ruleslineno, parser.getTopBufferName(), false, Statement::MIN, (*$3), (*$5)));
	  delete($3);
	  delete($5);
	}

	|TOKEN_MAX TOKEN_LT expression_statement TOKEN_COMMA expression_statement TOKEN_GT
	{
	  DBUGPRT("expression_statement");
	  $$ = new statementPtr(Statement::createFunction(ruleslineno, parser.getTopBufferName(), false, Statement::MAX, (*$3), (*$5)));
	  delete($3);
	  delete($5);
	}
	
	|TOKEN_RAND TOKEN_LPAR TOKEN_RPAR
	{
	  DBUGPRT("expression_statement");
	  $$ = new statementPtr(Statement::createFunction(ruleslineno, parser.getTopBufferName(), false, Statement::RANDOM));
	}

	|TOKEN_DOUBLE
	{
	  DBUGPRT("expression_statement");
	  $$ = new statementPtr(Statement::createNumber(ruleslineno, parser.getTopBufferName(), false, $1));
	}

	|TOKEN_INTEGER
	{
	  DBUGPRT("expression_statement");
 	  $$ = new statementPtr(Statement::createNumber(ruleslineno, parser.getTopBufferName(), false, (double)$1));
	}

	|TOKEN_STRING
	{
	  DBUGPRT("expression_statement");
 	  $$ = new statementPtr(Statement::createString(ruleslineno, parser.getTopBufferName(), false, *$1));
	  delete($1);
	}

	//////////////////////////////////////////////////
	// features
	//////////////////////////////////////////////////
	|expression_statement TOKEN_UNIFY expression_statement {
	  DBUGPRT("expression_statement");
	  $$ = new statementPtr(Statement::createFirstSecond(ruleslineno, parser.getTopBufferName(), Statement::UNIF_STATEMENT, false, (*$1), (*$3)));
	  delete($1);
	  delete($3);
	}

	|up_statement {
	  DBUGPRT("expression_statement");
	  $$=$1;
	}

	|double_up_statement {
	  DBUGPRT("expression_statement");
	  $$=$1;
	}

	|down_statement {
	  DBUGPRT("expression_statement");
	  $$=$1;
	}

	|double_down_statement {
	  DBUGPRT("expression_statement");
	  $$=$1;
	}

	|field_access_statement {
  	  DBUGPRT("expression_statement");
	  $$=$1;
	}

	|features {
	  DBUGPRT("expression_statement");
	  $$ = new statementPtr(Statement::createFeatures(ruleslineno, parser.getTopBufferName(), Statement::FEATURES_STATEMENT, false, *$1));
	  delete($1);
	}

	//////////////////////////////////////////////////
	// constants
	//////////////////////////////////////////////////
	|TOKEN_NIL
	{
	  DBUGPRT("expression_statement");
	  $$ = new statementPtr(Statement::createEmpty(ruleslineno, parser.getTopBufferName(), Statement::NIL_STATEMENT, false));
	}

	|constants {
	  DBUGPRT("expression_statement");
	  $$ = new statementPtr(Statement::createConstant(ruleslineno, parser.getTopBufferName(), false, *$1));
	  delete($1);
	}

	|variable {
	  DBUGPRT("expression_statement");
	  $$ = new statementPtr(Statement::createVariable(ruleslineno, parser.getTopBufferName(), false, $1));
	}

	|TOKEN_LPAR expression_statement TOKEN_RPAR {
	  DBUGPRT("expression_statement");
	  $$=$2;
	}

	//////////////////////////////////////////////////
	// position
	//////////////////////////////////////////////////
	|hash_statement {
	  DBUGPRT("expression_statement");
	  $$=$1;
	}

	//////////////////////////////////////////////////
	// pairp
	//////////////////////////////////////////////////
	|pairp {
	  DBUGPRT("expression_statement");
	  $$ = new statementPtr(Statement::createPairp(ruleslineno, parser.getTopBufferName(), false, *$1));
	  delete($1);
	}
	;

compound_expression_statement:
	compound_expression_statement TOKEN_COMMA expression_statement
	{
	  DBUGPRT("compound_expression_statement");
	  $$ = $1;
	  (*$$)->addStatement(*$3);
	  delete($3);
	}

	|expression_statement
	{
	  DBUGPRT("compound_expression_statement");
	  $$ = new statementsPtr(Statements::create());
	  (*$$)->addStatement(*$1);
	  delete($1);
	}
	;

up_statement:
	TOKEN_UP_ARROW {
	  DBUGPRT("up");
	  $$ = new statementPtr(Statement::createEmpty(ruleslineno, parser.getTopBufferName(), Statement::INHERITED_FEATURES_STATEMENT, false));
	}
	;

double_up_statement:
	TOKEN_DOUBLE_UP_ARROW {
	  DBUGPRT("double_up_statement");
	  $$ = new statementPtr(Statement::createEmpty(ruleslineno, parser.getTopBufferName(), Statement::SYNTHESIZED_FEATURES_STATEMENT, false));
	}
	;

down_statement:
	TOKEN_DOWN_ARROW TOKEN_INTEGER
	{
	  DBUGPRT("down_statement");
	  $$ = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::INHERITED_CHILDREN_FEATURES_STATEMENT, false, static_cast<uint8_t>($2-1)));
	}
	;

double_down_statement:
	TOKEN_DOUBLE_DOWN_ARROW TOKEN_INTEGER
	{
	  DBUGPRT("down2");
	  $$ = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::SYNTHESIZED_CHILDREN_FEATURES_STATEMENT, false, static_cast<uint8_t>($2-1)));
	}
	;

field_access_attribute:
    TOKEN_IDENTIFIER
    {
      DBUGPRT("field_access_attribute");
      $$ = new bitsetPtr(Vartable::createSymbol(*$1));
      delete $1;
    }

    |TOKEN_HEAD
    {
      DBUGPRT("field_access_attribute");
      $$ = new bitsetPtr(Vartable::createSymbol("HEAD"));
    }

    |TOKEN_LEMMA
    {
      DBUGPRT("field_access_attribute");
      $$ = new bitsetPtr(Vartable::createSymbol("LEMMA"));
    }

    |TOKEN_FORM
    {
      DBUGPRT("field_access_attribute");
      $$ = new bitsetPtr(Vartable::createSymbol("FORM"));
    }
    ;
	
field_access_root:
    up_statement
    {
      DBUGPRT("field_access_root");
      $$ = $1;
    }

    |double_down_statement
    {
      DBUGPRT("field_access_root");
      $$ = $1;
    }
    ;

field_access_statement:
    field_access_root TOKEN_DOT field_access_attribute
	{
      DBUGPRT("field_access_statement");

      $$ = new statementPtr(
        Statement::createFieldAccess(
          ruleslineno,
          parser.getTopBufferName(),
          false,
          *$1,
          *$3
        )
      );

      delete $1;
      delete $3;
    }

	|field_access_statement TOKEN_DOT field_access_attribute
    {
      DBUGPRT("field_access_statement");

      $$ = new statementPtr(
        Statement::createFieldAccess(
          ruleslineno,
          parser.getTopBufferName(),
          false,
          *$1,
          *$3
        )
      );

      delete $1;
      delete $3;
    }
    ;
	
hash_statement:
	TOKEN_HASH TOKEN_INTEGER TOKEN_DOT TOKEN_INTEGER
	{
	  DBUGPRT("hash_statement");
	  $$ = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::HASH_STATEMENT, false, static_cast<uint8_t>($2-1), static_cast<uint8_t>($4-1)));
	}

	|TOKEN_HASH TOKEN_INTEGER
	{
	  DBUGPRT("hash_statement");
	  $$ = new statementPtr(Statement::create(ruleslineno, parser.getTopBufferName(), Statement::HASH_STATEMENT, false, static_cast<uint8_t>($2-1), UINT8_MAX));
	}
	;

feature_statement_value:
    up_statement
    {
      DBUGPRT("feature_statement_value");
      $$ = $1;
    }

    |double_down_statement
    {
      DBUGPRT("feature_statement_value");
      $$ = $1;
    }

    |field_access_statement
    {
      DBUGPRT("feature_statement_value");
      $$ = $1;
    }
    ;
	
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
	    delete($3);
	  }
	}

	|TOKEN_LBRACKET TOKEN_RBRACKET
	{
	  DBUGPRT("features");
	  $$ = new featuresPtr(Features::create());
	}
	;

features_composite_tail:
	/* empty */
	{
	    $$ = NULL;
	}

	|TOKEN_COMMA variable
	{
        $$ = new featurePtr(Feature::createVariable($2, valuePtr()));
    }
	;

features_composite:
	features_composite TOKEN_COMMA feature
	{
	  DBUGPRT("feature_components");
	  $$ = $1;
	  (*$$)->add(*$3);
	  delete($3);
	}

	|feature
	{
	  DBUGPRT("features_composite");
	  $$ = new featuresPtr(Features::create());
	  (*$$)->add(*$1);
	  delete($1);
	}

	//…, @constant
	|features_composite TOKEN_COMMA TOKEN_AT_SIGN TOKEN_IDENTIFIER
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
	  delete($4);
	}

	//@constant
	|TOKEN_AT_SIGN TOKEN_IDENTIFIER
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
	delete($2);
	}
	;

feature:
	// LEMMA: lemma
	TOKEN_LEMMA TOKEN_COLON identifier
	{
	  DBUGPRT("feature");
	  $$ = new featurePtr(Feature::createLemma(Value::createIdentifier(*$3)));
	  delete($3);
	}

	// LEMMA: $X
	|TOKEN_LEMMA TOKEN_COLON variable
	{
	  DBUGPRT("feature");
	  $$ = new featurePtr(Feature::createLemma(Value::createVariable($3)));
	}

	// HEAD: headicate
	|TOKEN_HEAD TOKEN_COLON identifier
	{
	  DBUGPRT("feature");
	  $$ = new featurePtr(Feature::createHead(Value::createIdentifier(*$3)));
	  delete($3);
	}

	// HEAD: $X
	|TOKEN_HEAD TOKEN_COLON variable
	{
	  DBUGPRT("feature");
	  $$ = new featurePtr(Feature::createHead(Value::createVariable($3)));
	}

	// HEAD: _
	|TOKEN_HEAD TOKEN_COLON TOKEN_ANONYMOUS_VARIABLE
	{
	  DBUGPRT("feature");
	  $$ = new featurePtr(Feature::createHead(Value::STATIC_ANONYMOUS_VARIABLE));
	}

	// FORM: $X
	|TOKEN_FORM TOKEN_COLON variable
	{
	  DBUGPRT("feature");
	  $$ = new featurePtr(Feature::createForm(Value::createVariable($3)));
	}

	|TOKEN_FORM TOKEN_COLON strings
	{
	  DBUGPRT("feature");
	  $$ = new featurePtr(Feature::createForm(Value::createString(*$3)));
	  delete($3);
	}

	|TOKEN_FORM TOKEN_COLON TOKEN_ANONYMOUS_VARIABLE
	{
	  DBUGPRT("feature");
	  $$ = new featurePtr(Feature::createForm(Value::STATIC_ANONYMOUS_VARIABLE));
	}

	|constant TOKEN_COLON feature_value
	{
	  DBUGPRT("feature");
	  $$ = new featurePtr(Feature::createConstant(*$1, *$3));
	  delete($1);
	  delete($3);
	}

	|constant TOKEN_COLON strings
	{
	  DBUGPRT("feature");
	  $$ = new featurePtr(Feature::createConstant(*$1, Value::createString(*$3)));
	  delete($1);
	  delete($3);
	}
	;

feature_value:
	variable
	{
	  DBUGPRT("feature_value");
	  $$ = new valuePtr(Value::createVariable($1));
	}

	|constants
	{
	  DBUGPRT("feature_value");
	  $$ = new valuePtr(Value::createConstant(*$1));
	  delete($1);
	}

	|TOKEN_DOUBLE
	{
	  DBUGPRT("expression_statement");
	  $$ = new valuePtr(Value::createNumber($1));
	}

	|TOKEN_INTEGER
	{
	  DBUGPRT("expression_statement");
	  $$ = new valuePtr(Value::createNumber((double)$1));
	}

	|pairp
	{
	  DBUGPRT("feature_value");
	  $$ = new valuePtr(Value::createPairp(*$1));
	  delete($1);
	}

	|features
	{
	  DBUGPRT("feature_value");
	  $$ = new valuePtr(Value::createFeatures(*$1));
	  delete($1);
	}

    |feature_statement_value
    {
      DBUGPRT("feature_value");
      $$ = new valuePtr(Value::createStatement(*$1));
      delete($1);
    }	

	|TOKEN_NIL
	{
	  DBUGPRT("feature_value");
	  $$ = new valuePtr(Value::STATIC_NIL);
	}

	|TOKEN_ANONYMOUS_VARIABLE
	{
	  DBUGPRT("feature_value");
	  $$ = new valuePtr(Value::STATIC_ANONYMOUS_VARIABLE);
	}
	;

constants:
	constant
	{
	  DBUGPRT("constants");
	  $$=$1;
	}

	| constant TOKEN_PIPE constants
	{
	  DBUGPRT("constants");
	  $$=$1;
	  (**$$) |= (**$3);
	}
	;

constant:
	TOKEN_IDENTIFIER
	{
	  DBUGPRT("constant");
 	  $$ = new bitsetPtr(Bitset::create(Vartable::createSymbol(*$1)));
 	  delete($1);
	}
	;

variable:
	TOKEN_VARIABLE
	{
	  DBUGPRT("variable");
	  $$ = Vartable::nameToCode(*$1);
	  delete($1);
	}
	;

identifier:
	TOKEN_IDENTIFIER {
	  DBUGPRT("identifier");
	  $$ = $1;
	}
	;

identifier_or_string:
	TOKEN_IDENTIFIER {
	  DBUGPRT("identifier_or_string");
	  $$ = $1;
	}

	|TOKEN_STRING {
		DBUGPRT("identifier_or_string");
	  	$$ = $1;
	}
	;

strings:
	TOKEN_STRING {
		DBUGPRT("identifier_or_string");
	  	$$ = $1;
	}
	
	|strings TOKEN_PLUS TOKEN_STRING {
	  DBUGPRT("string");
	  $$ = $1;
	  *$$ += *$3;
	  delete($3);
	}
	;

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

	|TOKEN_LT pairp_elements TOKEN_LIST_CONS pairp_element TOKEN_GT
	{
	  DBUGPRT("list");
	  if ((*$2)->isPairp() && (*$2)->getCdr()->isNil())
	    $$ = new pairpPtr(Pairp::create((*$2)->getCar(), *$4));
	  else
	    $$ = new pairpPtr(Pairp::create(*$2, *$4));
	  delete($2);
	  delete($4);
	}

	|TOKEN_LT pairp_elements TOKEN_LIST_CONS TOKEN_NIL TOKEN_GT
	{
	  DBUGPRT("list");
	  if ((*$2)->isPairp() && (*$2)->getCdr()->isNil())
	    $$ = new pairpPtr(Pairp::create((*$2)->getCar(), Pairp::NIL));
	  else
	    $$ = new pairpPtr(Pairp::create(*$2, Pairp::NIL));
	  delete($2);
	}
	;

pairp_elements:
	pairp_element TOKEN_COMMA pairp_elements
	{
	  DBUGPRT("pairp_elements");
	  $$ = new pairpPtr(Pairp::create(*$1, *$3));
	  delete($1);
	  delete($3);
	}

	|pairp_element
	{
	  DBUGPRT("pairp_elements");
	  $$ = new pairpPtr(Pairp::create(*$1, Pairp::NIL));
	  delete($1);
	}
	;

pairp_element:
	variable
	{
	  DBUGPRT("pairp_element");
	  $$ = new pairpPtr(Pairp::create(Value::createVariable($1)));
	}

	|TOKEN_DOUBLE
	{
	  DBUGPRT("expression_statement");
	  $$ = new pairpPtr(Pairp::create(Value::createNumber($1)));
	}

 	|TOKEN_INTEGER
	{
	  DBUGPRT("expression_statement");
	  $$ = new pairpPtr(Pairp::create(Value::createNumber((double)$1)));
	}

	|constants
	{
	  DBUGPRT("pairp_element");
	  $$ = new pairpPtr(Pairp::create(Value::createConstant(*$1)));
	  delete($1);
	}

	|features
	{
	  DBUGPRT("pairp_element");
	  $$ = new pairpPtr(Pairp::create(Value::createFeatures(*$1)));
	  delete($1);
	}

    |feature_statement_value
    {
      DBUGPRT("pairp_element");
      $$ = new pairpPtr(Pairp::create(Value::createStatement(*$1)));
      delete($1);
    }
	
	|pairp
	{
	  DBUGPRT("pairp_element");
	  $$=$1;
	}
	;

%%
