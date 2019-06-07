/* **************************************************
 *
 * ELVEX
 *
 * Copyright 2018 LABRI, 
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

#include <cmath>
#include <map>
#include "statement.hh"
#include "environment.hh"
#include "statements.hh"
#include "feature.hh"
#include "features.hh"
#include "value.hh"
#include "terms.hh"
#include "list.hh"
#include "messages.hh"
#include "item.hh"
#include "ipointer.hh"
#include "listfeatures.hh"
#include "rule.hh"
#include "synthesizer.hh"

/* **************************************************
 *
 ************************************************** */
Statement::Statement (unsigned int lineno,
		      type op,
		      std::string str)
{
  NEW;
  this->lineno = lineno;
  this->op = op;
  this->lhs = statementPtr();
  this->rhs = statementPtr();
  this->pair.first=0;
  this->pair.second=0;
  this->features = featuresPtr();
  this->bits = bitsetPtr();
  this->str = str;
  this->fct = NOP;
  this->list = listPtr();
  this->statements = statementsPtr();
  this->number=0;
}

/* **************************************************
 *
 ************************************************** */
Statement::Statement (unsigned int lineno,
		      type op,
		      statementPtr lhs,
		      statementPtr rhs,
		      unsigned int first,
		      unsigned int second,
		      featuresPtr features,
		      bitsetPtr bits,
		      arithmetic_op fct,
		      listPtr list,
		      statementsPtr statements,
		      double number)
{
  NEW;
  this->lineno = lineno;
  this->op = op;
  this->lhs = lhs;
  this->rhs = rhs;
  this->pair.first = first;
  this->pair.second = second;
  this->features = features;
  this->bits = bits;
  this->str = std::string();
  this->fct = fct;
  this->list = list;
  this->statements = statements;
  this->number = number;
}

/* **************************************************
 *
 ************************************************** */
Statement::~Statement (void)
{
  //DELETE;
}

/* **************************************************
 *
 ************************************************** */
statementPtr Statement::create (unsigned int lineno, type op, statementPtr lhs, statementPtr rhs)
{
  return statementPtr( new Statement(lineno, op, lhs, rhs) );
}

/* **************************************************
 *
 ************************************************** */
statementPtr Statement::create (unsigned int lineno, type op, unsigned int first, unsigned int second)
{
  return statementPtr( new Statement(lineno, op, statementPtr(), statementPtr(), first, second) );
}

/* **************************************************
 *
 ************************************************** */
statementPtr Statement::create (unsigned int lineno, type op, featuresPtr features)
{
  return statementPtr( new Statement(lineno, op, statementPtr(), statementPtr(), UINT_MAX, UINT_MAX, features) );
}

/* **************************************************
 *
 ************************************************** */
statementPtr Statement::create (unsigned int lineno, type op, valuePtr value)
{
  return statementPtr( new Statement(lineno, op, statementPtr(), statementPtr(), UINT_MAX, UINT_MAX) );
}

/* **************************************************
 *
 ************************************************** */
statementPtr Statement::create (unsigned int lineno, type op, bitsetPtr bits)
{
  return statementPtr( new Statement(lineno, op, statementPtr(), statementPtr(), UINT_MAX, UINT_MAX, featuresPtr(), bits) );
}

/* **************************************************
 *
 ************************************************** */
statementPtr Statement::create (unsigned int lineno, type op, std::string str)
{
  return statementPtr( new Statement(lineno, op, str) );
}

/* **************************************************
 *
 ************************************************** */
statementPtr Statement::create (unsigned int lineno, type op, arithmetic_op fct, statementPtr lhs, statementPtr rhs)
{
  return statementPtr( new Statement(lineno, op, lhs, rhs, UINT_MAX, UINT_MAX, featuresPtr(), bitsetPtr(), fct) );
}

/* **************************************************
 *
 ************************************************** */
statementPtr Statement::create (unsigned int lineno, type op, listPtr list)
{
  return statementPtr( new Statement(lineno, op, statementPtr(), statementPtr(), UINT_MAX, UINT_MAX, featuresPtr(), bitsetPtr(), Statement::NOP, list) );
}

/* **************************************************
 *
 ************************************************** */
statementPtr Statement::create (unsigned int lineno, type op, statementsPtr statements)
{
  return statementPtr( new Statement(lineno, op, statementPtr(), statementPtr(), UINT_MAX, UINT_MAX, featuresPtr(), bitsetPtr(), Statement::NOP, listPtr(), statements) );
}

/* **************************************************
 *
 ************************************************** */
statementPtr Statement::create (unsigned int lineno, type op, double number)
{
  return statementPtr( new Statement(lineno, op, statementPtr(), statementPtr(), UINT_MAX, UINT_MAX, featuresPtr(), bitsetPtr(), Statement::NOP, listPtr(), statementsPtr(), number) );
}

/* **************************************************
 *
 ************************************************** */
statementPtr Statement::create (void)
{
  return statementPtr( new Statement(0, DASH, statementPtr(), statementPtr(), UINT_MAX, UINT_MAX, featuresPtr(), bitsetPtr(), Statement::NOP, listPtr(), statementsPtr()) );
}

/* **************************************************
 *
 ************************************************** */
Statement::type Statement::getOp(void) const 
{
  return this->op;
}

/* **************************************************
 *
 ************************************************** */
Statement::arithmetic_op Statement::getFct(void) const 
{
  return fct;
}

/* **************************************************
 *
 ************************************************** */
statementPtr Statement::getLhs(void) const 
{
  return lhs;
}

/* **************************************************
 *
 ************************************************** */
statementPtr Statement::getRhs(void) const 
{
  return rhs;
}

/* **************************************************
 *
 ************************************************** */
featuresPtr Statement::getFeatures(void) const 
{
  return features;
}

/* **************************************************
 *
 ************************************************** */
bitsetPtr Statement::getBits(void) const 
{
  return bits;
}

/* **************************************************
 *
 ************************************************** */
unsigned int Statement::getFirst(void) const 
{
  return pair.first;
}

/* **************************************************
 *
 ************************************************** */
unsigned int Statement::getSecond(void) const 
{
  return pair.second;
}

/* **************************************************
 *
 ************************************************** */
std::string Statement::getStr(void) const 
{
  return str;
}

/* **************************************************
 *
 ************************************************** */
listPtr Statement::getList(void) const 
{
  return list;
}

/* **************************************************
 *
 ************************************************** */
statementsPtr Statement::getStatements(void) const 
{
  return this->statements;
}

/* **************************************************
 *
 ************************************************** */
double Statement::getNumber(void) const 
{
  return this->number;
}

/* **************************************************
 *
 ************************************************** */
int Statement::getLineno(void) const 
{
  return lineno;
}

/* **************************************************
 *
 ************************************************** */
void
Statement::print(std::ostream &outStream, int left) const
{
  std::string red="", green="", blue="";
  switch (this->op) {
  case SORT:
  case REVERSE:
  case ATTEST:
  case AFF:
  case SUBSUME:
  case PRINT:
  case PRINTLN:
  case GUARD:
  case IF:
  case THENELSE:
    for (int j=1 ; j<=left ; j++)
      outStream << "&nbsp;";
    break;
  default:
    break;
  }
  if (isSetFlags(Flags::SEEN)) {
    red="00"; green="00"; blue="FF";
  }
  if (isSetFlags(Flags::DISABLED)) {
    red="C0"; green="C0"; blue="C0";
  }
  if (isSetFlags(Flags::BOTTOM)) {
    red="FF"; green="00"; blue="00";
  }
  std::string color="";
  if (red!="" || green!="" || blue!="")
    color="#"+red+green+blue;
  if (color!="")
    outStream << "<SPAN style=\"color:" << color << ";\">";
  if (isSetFlags(Flags::REJECTED)) {
    outStream << "<S>";
  }
  switch (this->op) {
  case SORT:
    outStream << "sort&nbsp;";
    lhs->print(outStream);
    if (rhs) {
      outStream << " with&nbsp;";
      rhs->print(outStream);
    }
    break;
  case REVERSE:
    outStream << "reverse&nbsp;";
    lhs->print(outStream);
    break;
    // case COMBINATION:
    //   outStream << "combination&nbsp;";
    //   lhs->print(outStream);
    //   break;
  case ATTEST:
    outStream << "attest&nbsp;";
    lhs->print(outStream);
    break;
  case NIL:
    outStream << "NIL";
    break;
  case NOT_NIL:
    outStream << "NOT_NIL";
    break;
  case FINISHED:
    outStream << "finished";
    break;
  case AFF:
    lhs->print(outStream);
    outStream << "&nbsp;=&nbsp;";
    rhs->print(outStream);
    break;
  case SUBSUME:
    lhs->print(outStream);
    outStream << "&nbsp;⊂&nbsp;";
    rhs->print(outStream);
    break;
  case INSET:
    lhs->print(outStream);
    outStream << "&nbsp;∈&nbsp;";
    rhs->print(outStream);
    break;
  case FCT:
    switch (this->getFct()) {
    case NOP:
      outStream << ";";
      break;
    case NOT:
      outStream << "¬";
      outStream << "&nbsp;(";
      lhs->print(outStream);
      outStream << ")&nbsp;";
      break;
    case AND:
      outStream << "&nbsp;(";
      lhs->print(outStream);
      outStream << "&nbsp;∧&nbsp;";
      rhs->print(outStream);
      outStream << ")&nbsp;";
      break;
    case OR:
      outStream << "&nbsp;(";
      lhs->print(outStream);
      outStream << "&nbsp;∨&nbsp;";
      rhs->print(outStream);
      outStream << ")&nbsp;";
      break;
    case EQ:
      outStream << "&nbsp;(";
      lhs->print(outStream);
      outStream << "&nbsp;==&nbsp;";
      rhs->print(outStream);
      outStream << ")&nbsp;";
      break;
    case DIFF:
      outStream << "&nbsp;(";
      lhs->print(outStream);
      outStream << "&nbsp;≠&nbsp;";
      rhs->print(outStream);
      outStream << ")&nbsp;";
      break;
    case PLUS:
      outStream << '(';
      lhs->print(outStream);
      outStream << "&nbsp;+&nbsp;";
      rhs->print(outStream);
      outStream << ')';
      break;
    case MINUS:
      outStream << '(';
      lhs->print(outStream);
      outStream << "&nbsp;-&nbsp;";
      rhs->print(outStream);
      outStream << ')';
      break;
    case TIMES:
      outStream << '(';
      lhs->print(outStream);
      outStream << "&nbsp;*&nbsp;";
      rhs->print(outStream);
      outStream << ')';
      break;
    case DIVIDE:
      outStream << '(';
      lhs->print(outStream);
      outStream << "&nbsp;/&nbsp;";
      rhs->print(outStream);
      outStream << ')';
      break;
    case MODULO:
      outStream << '(';
      lhs->print(outStream);
      outStream << "&nbsp;%&nbsp;";
      rhs->print(outStream);
      outStream << ')';
      break;
    case LT:
      outStream << '(';
      lhs->print(outStream);
      outStream << "&nbsp;<&nbsp;";
      rhs->print(outStream);
      outStream << ')';
      break;
    case LE:
      outStream << '(';
      lhs->print(outStream);
      outStream << "&nbsp;≤&nbsp;";
      rhs->print(outStream);
      outStream << ')';
      break;
    case GT:
      outStream << '(';
      lhs->print(outStream);
      outStream << "&nbsp;>&nbsp;";
      rhs->print(outStream);
      outStream << ')';
      break;
    case GE:
      outStream << '(';
      lhs->print(outStream);
      outStream << "&nbsp;≥&nbsp;";
      rhs->print(outStream);
      outStream << ')';
      break;
    case MINUS_U:
      outStream << "-&nbsp;";
      lhs->print(outStream);
      break;
    case RAND:
      outStream << "rand()";
      break;
    }
    break;
  case CONSTANT:
  case VARIABLE:
    outStream << getBits()->_toString();
    break;
  case PRINT:
    outStream << "print&nbsp;";
    lhs->print(outStream);
    break;
  case PRINTLN:
    outStream << "println&nbsp;";
    lhs->print(outStream);
    break;
  case FEATURES:
    getFeatures()->print(outStream, true, true);
    break;
  case LIST:
    getList()->print(outStream, true, true);
    break;
  case GUARD:
    getFeatures()->print(outStream, true, true);
    break;
  case UNIF:
    outStream << "&nbsp;(";
    lhs->print(outStream);
    outStream << "&nbsp;∪&nbsp;";
    rhs->print(outStream);
    outStream << ")&nbsp;";
    break;
  case UP:
    outStream << "↑";
    break;
  case UP2:
    outStream << "⇑";
    break;
  case DASH:
    outStream << '#';
    outStream << getFirst()+1;
    if (getSecond()!=UINT_MAX) {
      outStream << ":" << getSecond()+1;
    }
    break;
  case DOWN:
    outStream << "↓";
    outStream << getFirst()+1;
    if (getSecond()!=UINT_MAX) {
      outStream << "." << getSecond()+1;
    }
    break;
  case DOWN2:
    outStream << "⇓";
    outStream << getFirst()+1;
    break;
  case IF:
    outStream << "if (";
    lhs->print(outStream);
    outStream << ')';
    rhs->print(outStream, left);
    break;
  case THENELSE:
    outStream << "<DIV";
    if (color!="")
      outStream << " style=\"color:" << color << "\"";
    outStream << ">";
    lhs->print(outStream, left+3);
    outStream << "</DIV>";
    if (rhs) {
      for (int j=1 ; j<=left ; j++)
	outStream << "&nbsp;";
      outStream << "else ";
      outStream << "<DIV>";
      rhs->print(outStream, left+3);
      outStream << "</DIV>";
    }
    break;
  case STR:
    outStream << "&quot;" << getStr() << "&quot;";
    break;
  case STMS:
    getStatements()->print(outStream, left);
    break;
  case DOUBLE:
    outStream << getNumber();
    break;
  }
  switch (this->op) {
  case SORT:
  case REVERSE:
  case ATTEST:
  case AFF:
  case SUBSUME:
  case PRINT:
  case PRINTLN:
  case GUARD:
    outStream << ";<BR>";
    break;
  default:
    break;
  }
  if (isSetFlags(Flags::REJECTED)) {
    outStream << "</S>";
  }
  if (color!="")
    outStream << "</SPAN>";
}

/* **************************************************
 *
 ************************************************** */
const std::string
Statement::makeSerializationId() 
{
  switch (this->op) {
  case SORT:
    serialId = 'S' + lhs->serialize();
    if (rhs) {
      serialId += " W " + rhs->serialize();
    }
    break;
  case REVERSE:
    serialId = 'R' + lhs->serialize();
    break;
  case ATTEST:
    serialId = 'A' + lhs->serialize();
    break;
  case NIL:
    serialId = 'N';
    break;
  case NOT_NIL:
    serialId = '~';
    break;
  case FINISHED:
    serialId = 'F';
    break;
  case AFF:
    serialId = lhs->serialize() + '=' + rhs->serialize();
    break;
  case SUBSUME:
    serialId = lhs->serialize() + "⊂" + rhs->serialize();
    break;
  case INSET:
    serialId = lhs->serialize() + "∈" + rhs->serialize();
    break;
  case FCT:
    switch (this->getFct()) {
    case NOP:
      serialId = ';';
      break;
    case NOT:
      serialId = "¬("+lhs->serialize()+')';
      break;
    case AND:
      serialId = '('+lhs->serialize()+"∧"+rhs->serialize()+')';
      break;
    case OR:
      serialId = '('+lhs->serialize()+"∨"+rhs->serialize()+')';
      break;
    case DIFF:
      serialId = '('+lhs->serialize()+"≠"+rhs->serialize()+')';
      break;
    case EQ:
      serialId = '('+lhs->serialize()+"=="+rhs->serialize()+')';
      break;
    case PLUS:
      serialId = '('+lhs->serialize()+"+"+rhs->serialize()+')';
      break;
    case MINUS:
      serialId = '('+lhs->serialize()+'-'+rhs->serialize()+')';
      break;
    case TIMES:
      serialId = '('+lhs->serialize()+'*'+rhs->serialize()+')';
      break;
    case DIVIDE:
      serialId = '('+lhs->serialize()+'/'+rhs->serialize()+')';
      break;
    case MODULO:
      serialId = '('+lhs->serialize()+'%'+rhs->serialize()+')';
      break;
    case LT:
      serialId = '('+lhs->serialize()+'<'+rhs->serialize()+')';
      break;
    case LE:
      serialId = '('+lhs->serialize()+"≤"+rhs->serialize()+')';
      break;
    case GT:
      serialId = '('+lhs->serialize()+'>'+rhs->serialize()+')';
      break;
    case GE:
      serialId = '('+lhs->serialize()+"≥"+rhs->serialize()+')';
      break;
    case MINUS_U:
      serialId = '-'+lhs->serialize();
      break;
    case RAND:
      serialId = "r()";
      break;
    }
    break;
  case CONSTANT:
  case VARIABLE:
    serialId = getBits()->serialize();
    break;
  case PRINT:
    serialId = "P "+lhs->serialize();
    break;
  case PRINTLN:
    serialId = "PL "+lhs->serialize();
    break;
  case FEATURES:
    serialId = getFeatures()->serialize();
    break;
  case LIST:
    serialId = getList()->serialize();
    break;
  case GUARD:
    serialId = "G "+getFeatures()->serialize();
    break;
  case UNIF:
    serialId = '('+lhs->serialize()+"∪"+rhs->serialize()+')';
    break;
  case UP:
    serialId = "↑";
    break;
  case UP2:
    serialId = "⇑";
    break;
  case DASH:
    serialId = '#'+std::to_string(getFirst()+1);
    if (getSecond()!=UINT_MAX)
      serialId += ":" + std::to_string(getSecond()+1);
    break;
  case DOWN:
    serialId = "↓"+std::to_string(getFirst()+1);
    if (getSecond()!=UINT_MAX)
      serialId += '.' + std::to_string(getSecond()+1);
    break;
  case DOWN2:
    serialId = "⇓"+std::to_string(getFirst()+1);
    break;
  case IF:
    serialId = "if("+lhs->serialize()+')'+rhs->serialize();
    break;
  case THENELSE:
    serialId = "then("+lhs->serialize()+')';
    if (rhs) {
      serialId += "else("+rhs->serialize()+')';
    }
    break;
  case STR:
    serialId = '"' + getStr() + '"';
    break;
  case STMS:
    serialId = getStatements()->serialize();
    break;
  case DOUBLE:
    serialId = getNumber();
    break;
  }
  return serialId;
}

/* **************************************************
 *
 ************************************************** */
statementPtr 
Statement::clone(const std::bitset < NBRFLAGS>& savedFlags)
{
  statementPtr statement = shared_from_this();
  switch (this->op) {
  case UP:
  case UP2:
  case NIL:
  case NOT_NIL:
  case DASH:
  case DOWN:
  case DOWN2:
  case CONSTANT:
  case STR:
  case DOUBLE:
  case FINISHED:
    statement = shared_from_this();
    break;
  case FEATURES:
  case GUARD:
    statement = Statement::create(this->lineno, this->op, getFeatures()->clone());
    break;
  case LIST:
    statement = Statement::create(this->lineno, this->op, getList()->clone());
    break;
  case VARIABLE:
    statement = Statement::create(this->lineno, this->op, getBits());
    break;
  case ATTEST:
  case PRINT:
  case PRINTLN:
    statement = Statement::create(this->lineno, this->op, lhs?lhs->clone(savedFlags):statementPtr());
    break;
  case IF:
  case THENELSE:
  case UNIF:
  case SORT:
  case REVERSE:
  case AFF:
  case SUBSUME:
  case INSET:
    statement = Statement::create(this->lineno, this->op, lhs?lhs->clone(savedFlags):statementPtr(), rhs?rhs->clone(savedFlags):statementPtr());
    break;
  case FCT:
    statement = Statement::create(this->lineno, this->op, this->getFct(), lhs?lhs->clone(savedFlags):statementPtr(), rhs?rhs->clone(savedFlags):statementPtr());
    break;
  case STMS:
    statement = Statement::create(this->lineno, this->op, getStatements()->clone(savedFlags));
    break;
  }
  statement->addFlags(savedFlags &  this->getFlags());
  return statement;
}

/* **************************************************
 *
 ************************************************** */
featuresPtr  
Statement::evalFeatures(itemPtr item, bool replaceVariables)
{
#ifdef TRACE_EVAL
  std::cerr << "####################### EVAL FEATURES #######################" << std::endl;
  std::cerr << "<div>" << std::endl;
  this->print(std::cerr);
  std::cerr << std::endl;
  item->print(std::cerr);
  std::cerr << "</div>" << std::endl;
#endif
  
  featuresPtr resultFeatures = Features::_nil;
  switch (this->op) {
  case STR:
  case DASH:
  case PRINT:
  case PRINTLN:
  case ATTEST:
  case CONSTANT:
  case NIL:
  case NOT_NIL:
  case IF:
  case THENELSE:
  case AFF:
  case SUBSUME:
  case INSET:
  case DOWN:
  case UP2:
  case LIST:
  case SORT:
  case REVERSE:
  case STMS:
  case DOUBLE:
  case FCT:
  case FINISHED:
    FATAL_ERROR_STM;
    break;
  case FEATURES:
  case GUARD:
    resultFeatures = getFeatures()->clone();
    if (replaceVariables && item->getEnvironment() && item->getEnvironment()->size() > 0) {
      bool effect = false;
      item->getEnvironment()->replaceVariables(resultFeatures, effect);
    }
    break;
  case UP:
    resultFeatures = item->getInheritedFeatures()->clone();
    if (replaceVariables && item->getEnvironment() && item->getEnvironment()->size() > 0) {
      bool effect = false;
      item->getEnvironment()->replaceVariables(resultFeatures, effect);
    }
    break;
  case VARIABLE:
    if (item->getEnvironment()) {
      valuePtr value = item->getEnvironment()->find(getBits());
      if (!value)
	FATAL_ERROR_STM;
      if (value && value->getType()==Value::FEATURES)
	resultFeatures = value->getFeatures()->clone();
    }
    break;
  case DOWN2:
    resultFeatures=(*item->getSynthesizedSonFeatures())[getFirst()]->clone();
    if (replaceVariables && item->getEnvironment() && item->getEnvironment()->size() > 0) {
      bool effect = false;
      item->getEnvironment()->replaceVariables(resultFeatures, effect);
    }
    break;
  case UNIF:
    {
      featuresPtr fs1=lhs->evalFeatures(item, replaceVariables);
      featuresPtr fs2=rhs->evalFeatures(item, replaceVariables);
      if ((!fs1) || (!fs2)) {
	resultFeatures = featuresPtr();
      }
      else {
	fs1->subFlags(Flags::SEEN);
	fs2->subFlags(Flags::SEEN);
	resultFeatures = unif(fs1, fs2, item);
	if (replaceVariables && item->getEnvironment() && item->getEnvironment()->size() > 0) {
	  bool effect = false;
	  item->getEnvironment()->replaceVariables(resultFeatures, effect);
	}
      }
    }
    break;
  }
#ifdef TRACE_EVAL
  std::cerr << "####################### EVAL FEATURES DONE #######################" << std::endl;
  std::cerr << "<div>" << std::endl;
  this->print(std::cerr);
  std::cerr << std::endl;
  if (resultFeatures)
    resultFeatures->print(std::cerr);
  else
    std::cerr << "NULL";
  std::cerr << "</div>" << std::endl;
#endif
  return resultFeatures;
}

/* **************************************************
 *
 ************************************************** */
listPtr 
Statement::evalList(itemPtr item, bool replaceVariables)
{
#ifdef TRACE_EVAL
  std::cerr << "####################### EVAL LIST #######################" << std::endl;
  std::cerr << "<div>" << std::endl;
  this->print(std::cerr);
  std::cerr << "</div>" << std::endl;
#endif
  listPtr resultList = List::nil;
  switch (this->op) {
  case STR:
  case DASH:
  case PRINT:
  case PRINTLN:
  case ATTEST:
  case CONSTANT:
  case NIL:
  case NOT_NIL:
  case IF:
  case THENELSE:
  case AFF:
  case SUBSUME:
  case INSET:
  case DOWN:
  case UP2:
  case FEATURES:
  case GUARD:
  case UP:
  case DOWN2:
  case UNIF:
  case STMS:
  case DOUBLE:
  case FCT:
  case FINISHED:
    FATAL_ERROR_STM;
    break;
  case SORT:
    {
      valuePtr v = lhs->evalValue(item, replaceVariables);
      valuePtr with = rhs ? rhs->evalValue(item, replaceVariables) : valuePtr();
      if (!v)
	resultList = listPtr();
      else if (v->isNil())
	resultList = List::nil;
      else if (v->isList())
	resultList = v->getList()->clone();
      else {
	WARNING_STM;
      }
      if (with
	  && (!with->isNil())
	  && (with->isConstant())) {
	resultList->sort(with->getBits());
      }
      else if (!with)
	resultList->sort(bitsetPtr());
      else
	WARNING_STM;
    }
    break;
  case REVERSE:
    {
      valuePtr v = lhs->evalValue(item, replaceVariables);
      if (!v)
	resultList = listPtr();
      else if (v->isNil())
	resultList = List::nil;
      else if (v->isList())
	resultList = v->getList()->clone();
      else {
	WARNING_STM;
      }
      resultList->reverse();
    }
    break;
  case LIST:
    resultList = getList()->clone();
    if (replaceVariables && item->getEnvironment() && item->getEnvironment()->size() > 0) {
      bool effect = false;
      item->getEnvironment()->replaceVariables(resultList, effect);
    }
    break;
  case VARIABLE:
    if (item->getEnvironment()) {
      valuePtr value = item->getEnvironment()->find(getBits());
      if (!value) {
	FATAL_ERROR_STM;
	resultList = listPtr();
      }
      else if (value->isNil())
	resultList = List::nil;
      else if (value->isList())
	resultList = value->getList()->clone();
      else
	{
	  std::ostringstream oss1, oss2;
	  this->print(oss1);
	  item->getRule()->print(oss2, -1, true);
	  WARNING_STM "<P>Variable " + oss1.str() + " not initialized in</P>" + oss2.str();
	}
    }
    break;
  }
#ifdef TRACE_EVAL
  std::cerr << "####################### EVAL LIST DONE #######################" << std::endl;
  std::cerr << "<div>" << std::endl;
  this->print(std::cerr);
  std::cerr << std::endl;
  if (resultList)
    resultList->print(std::cerr);
  else
    std::cerr << "NULL";
  std::cerr << "</div>" << std::endl;
#endif
  return resultList;
}

/* **************************************************
 *
 ************************************************** */
valuePtr  
Statement::evalValue(itemPtr item, bool replaceVariables)
{
#ifdef TRACE_EVAL
  std::cerr << "####################### EVAL VALUE #######################" << std::endl;
  std::cerr << "<div>" << std::endl;
  this->print(std::cerr, 0);
  item->print(std::cerr);
  std::cerr << "</div>" << std::endl;
#endif
  valuePtr resultValue = valuePtr();
  featuresPtr resultFeatures = featuresPtr();
  listPtr resultList = listPtr();
  switch (this->op) {
  case NIL:
    resultValue = Value::_nil;
    break;
  case NOT_NIL:
    resultValue = Value::_true;
    break;
  case FINISHED:
    if (item->isCompleted())
      resultValue = Value::_true;
    else
      resultValue = Value::_nil;
    break;

  case PRINT:
  case PRINTLN:
  case IF:
  case THENELSE:
  case AFF:
  case SUBSUME:
  case INSET:
  case GUARD:
  case STMS:
    FATAL_ERROR_STM;
    break;

  case DASH:
    {
      class Terms *t = item->getTerms(getFirst());
      // if (#i) false
      if (t->isOptional())
	resultValue = Value::_nil;
      else {
	// if (#i)
	if (getSecond()==UINT_MAX) {
	  resultValue = Value::_true;
	}
	//if (#i:j)
	else{
	  if (getSecond() == item->getIndexTerms()[getFirst()]) {
	    resultValue = Value::_true;
	  }
	  else{
	    resultValue = Value::_nil;
	  }
	}
      }
      goto valueBuilt;
    }
    break;

  case DOUBLE:
    resultValue = Value::create(Value::DOUBLE, getNumber());
    goto valueBuilt;
    break;

  case STR:
    resultValue = Value::create(Value::STR, getStr());
    goto valueBuilt;
    break;

  case FEATURES:
    resultFeatures = getFeatures();
    break;

  case UP:
    resultFeatures = item->getInheritedFeatures();
    break;

  case UP2:
    resultFeatures = item->getSynthesizedFeatures();
    break;

  case VARIABLE:
    if (replaceVariables && item->getEnvironment()) {
      valuePtr value = item->getEnvironment()->find(getBits());
      resultValue = value;
      goto valueBuilt;
    }
    else if (replaceVariables) {
      resultValue = valuePtr();
      goto valueBuilt;
    }
    else{
      resultValue = Value::create(Value::VARIABLE, getBits());
    }
    break;

  case CONSTANT:
    resultValue = Value::create(Value::CONSTANT, getBits());
    break;

  case DOWN2:
    resultFeatures=(*item->getSynthesizedSonFeatures())[getFirst()];
    break;

  case DOWN:
    resultFeatures=(*item->getInheritedSonFeatures())[getFirst()];
    break;

  case ATTEST:
    FATAL_ERROR;
    goto valueBuilt;
    break;

  case UNIF: {
    featuresPtr fs1=lhs->evalFeatures(item, replaceVariables);
    if (!fs1) {
      resultValue = valuePtr();
      goto valueBuilt;
    }
    else{
      featuresPtr fs2=rhs->evalFeatures(item, replaceVariables);
      if (!fs2) {
	resultValue = valuePtr();
	goto valueBuilt;
	
      }
      else{
	fs1->subFlags(Flags::SEEN);
	fs2->subFlags(Flags::SEEN);
	resultFeatures = unif(fs1, fs2, item);
      }
    }
  }
    break;

  case LIST:
  case SORT:
  case REVERSE:
    resultList = evalList(item, replaceVariables);
    break;

  case FCT:
    switch (getFct()) {
    case NOP:
      break;
    case PLUS:
      {
	valuePtr v1=lhs->evalValue(item, replaceVariables);
	bool isv1astring = false;
	std::string v1str;
	if (v1) {
	  isv1astring = true;
	  if (v1->isVariable())
	    v1str = v1->getBits()->_toString();
	  else if (v1->isIdentifier())
	    v1str = Vartable::intToStr(v1->getIdentifier());
	  else if (v1->isStr())
	    v1str = v1->getStr();
	  else
	    isv1astring = false;
	}
	valuePtr v2=rhs->evalValue(item, replaceVariables);
	bool isv2astring = false;
	std::string v2str;
	if (v2) {
	  isv2astring = true;
	  if (v2->isVariable())
	    v2str = v2->getBits()->_toString();
	  else if (v2->isIdentifier())
	    v2str = Vartable::intToStr(v2->getIdentifier());
	  else if (v2->isStr())
	    v2str = v2->getStr();
	  else
	    isv2astring = false;
	}
	
	if ((!v1) || (!v2))
	  resultValue = valuePtr();

	else if ((v1->isDouble()) && (v2->isDouble()))
	  resultValue = Value::create(Value::DOUBLE, v1->getDouble() + v2->getDouble());
	
	else if (isv1astring && isv2astring)
	  resultValue = Value::create(Value::STR, v1str + v2str);

	else if ((v1->isList()) && (v2->isList())) {
	  WARNING_STM;
	  resultValue = valuePtr();
	}

	else {
	  std::cerr << v1->getType() << std::endl;
	  FATAL_ERROR;
	  //WARNING_STM;
	  //resultValue = valuePtr();
	}
	goto valueBuilt;
      }
      break;
    case MINUS:
      {
	valuePtr v1=lhs->evalValue(item, replaceVariables);
	valuePtr v2=rhs->evalValue(item, replaceVariables);
	if ((!v1) || (!v2))
	  resultValue = valuePtr();
	else if ((v1->isDouble()) && (v2->isDouble()))
	  resultValue = Value::create(Value::DOUBLE, v1->getDouble() - v2->getDouble());
	else
	  resultValue = valuePtr();
	goto valueBuilt;
      }
      break;
    case TIMES:
      {
	valuePtr v1=lhs->evalValue(item, replaceVariables);
	valuePtr v2=rhs->evalValue(item, replaceVariables);
	if ((!v1) || (!v2))
	  resultValue = valuePtr();
	else if ((v1->isDouble()) && (v2->isDouble()))
	  resultValue = Value::create(Value::DOUBLE, v1->getDouble() * v2->getDouble());
	else
	  resultValue = valuePtr();
	goto valueBuilt;
      }
      break;
    case DIVIDE:
      {
	valuePtr v1=lhs->evalValue(item, replaceVariables);
	valuePtr v2=rhs->evalValue(item, replaceVariables);
	if ((!v1) || (!v2))
	  resultValue = valuePtr();
	else if ((v1->isDouble()) && (v2->isDouble()))
	  resultValue = Value::create(Value::DOUBLE, v1->getDouble() / v2->getDouble());
	else
	  resultValue = valuePtr();
	goto valueBuilt;
      }
      break;
    case MODULO:
      {
	valuePtr v1=lhs->evalValue(item, replaceVariables);
	valuePtr v2=rhs->evalValue(item, replaceVariables);
	if ((!v1) || (!v2))
	  resultValue = valuePtr();
	else if ((v1->isDouble()) && (v2->isDouble()))
	  resultValue = Value::create(Value::DOUBLE, fmod(v1->getDouble(), v2->getDouble()));
	else
	  resultValue = valuePtr();
	goto valueBuilt;
      }
      break;
    case MINUS_U:
      {
	valuePtr v1=lhs->evalValue(item, replaceVariables);
	if (!v1)
	  resultValue = valuePtr();
	else if ((v1->isDouble()))
	  resultValue = Value::create(Value::DOUBLE, -v1->getDouble());
	else
	  resultValue = valuePtr();
	goto valueBuilt;
      }
      break;
    case AND:
      {
	valuePtr v1=lhs->evalValue(item, replaceVariables);
	valuePtr v2=rhs->evalValue(item, replaceVariables);
	if ((!v1) || (!v2))
	  resultValue = valuePtr();
	else if ((v1->isFalse()) || (v2->isFalse()))
	  resultValue = Value::_nil;
	else
	  resultValue = Value::_true;
	goto valueBuilt;
      }
      break;
    case OR:
      {
	valuePtr v1=lhs->evalValue(item, replaceVariables);
	valuePtr v2=rhs->evalValue(item, replaceVariables);
	if ((!v1) || (!v2))
	  resultValue = valuePtr();
	else if ((v1->isFalse()) && (v2->isFalse()))
	  resultValue = Value::_nil;
	else
	  resultValue = Value::_true;
	goto valueBuilt;
      }
      break;
    case EQ:
      {
	valuePtr v1=lhs->evalValue(item, replaceVariables);
	valuePtr v2=rhs->evalValue(item, replaceVariables);
	if ((!v1) && (!v2))
	  resultValue = Value::_true;
	
	else if ((!v1) || (!v2))
	  resultValue = valuePtr();
	
	else if ((v1->isAnonymous()) && (v2->isAnonymous()))
	  resultValue = Value::_true;
	
	else if ((v1->isAnonymous()) || (v2->isAnonymous()))
	  resultValue = Value::_nil;
	
	else if (v1->eq(v2))
	  resultValue = Value::_true;

	else 
	  resultValue = Value::_nil;
	
	goto valueBuilt;
      }
      break;
    case DIFF:
      {
	valuePtr v1=lhs->evalValue(item, replaceVariables);
	valuePtr v2=rhs->evalValue(item, replaceVariables);
	if ((!v1) && (!v2)) {
	  resultValue = Value::_nil;
	}

	else if ((!v1) || (!v2)) {
	  resultValue = Value::_true;
	}

	else if ((v1->isAnonymous()) && (v2->isAnonymous()))
	  resultValue = Value::_nil;
	

	else if ((v1->isAnonymous()) || (v2->isAnonymous()))
	  resultValue = Value::_true;
	
	else if (v1->eq(v2)) {
	  resultValue = Value::_nil;
	}

	else {
	  resultValue = Value::_true;
	}
	goto valueBuilt;
      }
      break;
    case LT:
      {
	valuePtr v1=lhs->evalValue(item, replaceVariables);
	valuePtr v2=rhs->evalValue(item, replaceVariables);
	// si l'une est variable libre
	if ((!v1) || (!v2)) {
	  resultValue = Value::_nil;
	}
	else if (v1->lt(v2))
	  resultValue = Value::_true;
	else
	  resultValue = Value::_nil;
	goto valueBuilt;
      }
      break;
    case LE:
      {
	valuePtr v1=lhs->evalValue(item, replaceVariables);
	valuePtr v2=rhs->evalValue(item, replaceVariables);
	// si l'une est variable libre
	if ((!v1) || (!v2)) {
	  resultValue = Value::_nil;
	}
	else if ((v1->lt(v2)) || (v1->eq(v2)))
	  resultValue = Value::_true;
	else
	  resultValue = Value::_nil;
	goto valueBuilt;
      }
      break;
    case GT:
      {
	valuePtr v1=lhs->evalValue(item, replaceVariables);
	valuePtr v2=rhs->evalValue(item, replaceVariables);
	// si l'une est variable libre
	if ((!v1) || (!v2)) {
	  resultValue = Value::_nil;
	}
	else if (!(v1->lt(v2)) && (!(v1->eq(v2))))
	  resultValue = Value::_true;
	else
	  resultValue = Value::_nil;
	goto valueBuilt;
      }
      break;
    case GE:
      {
	valuePtr v1=lhs->evalValue(item, replaceVariables);
	valuePtr v2=rhs->evalValue(item, replaceVariables);
	// si l'une est variable libre
	if ((!v1) || (!v2)) {
	  resultValue = Value::_nil;
	}
	else if (!(v1->lt(v2)))
	  resultValue = Value::_true;
	else
	  resultValue = Value::_nil;
	goto valueBuilt;
      }
      break;
    case NOT:
      {
	valuePtr v1=lhs->evalValue(item, replaceVariables);
	if (!v1
	    || v1->isFalse())
	  resultValue = Value::_true;
	else
	  resultValue = Value::_nil;
	goto valueBuilt;
      }
      break;
    case RAND:
      {
	resultValue = Value::create(Value::DOUBLE, (double)rand());
	goto valueBuilt;
      }
      break;
    }
    break;
  
  }

  if (!resultFeatures && !resultValue && !resultList) {
    FATAL_ERROR_STM;
  }

  if (resultList) {
    if (replaceVariables && item->getEnvironment() && item->getEnvironment()->size() > 0) {
      bool effect = false;
      item->getEnvironment()->replaceVariables(resultList, effect);
    }
    resultValue = Value::create(Value::LIST, resultList);
  }
  else if (resultFeatures) {
    if (resultFeatures->isNil())
      resultValue = Value::_nil;
    else if (resultFeatures->isBottom())
      resultValue = Value::_nil;
    else{
      if (replaceVariables && item->getEnvironment() && item->getEnvironment()->size() > 0) {
	bool effect = false;
	item->getEnvironment()->replaceVariables(resultFeatures, effect);
      }
      resultValue = Value::create(Value::FEATURES, resultFeatures);
    }
  }
 valueBuilt:
#ifdef TRACE_EVAL
  std::cerr << "####################### EVAL VALUE DONE #######################" << std::endl;
  std::cerr << "<div>" << std::endl;
  this->print(std::cerr);
  std::cerr << "<H3>";
  if (resultValue)
    resultValue->print(std::cerr);
  else
    std::cerr << "NULL";
  std::cerr << "</H3>";
  std::cerr << "</div>" << std::endl;
#endif
  return resultValue;
}

/* **************************************************
 *
 ************************************************** */
featuresPtr  
Statement::unif(featuresPtr fs1, featuresPtr fs2, itemPtr item)
{
#ifdef TRACE_EVAL
  std::cerr << "####################### EVAL UNIF #######################" << std::endl;
  std::cerr << "<table border=\"1\"><tr><th>fs1</th><th>fs2</th><th>Environment</th></tr>";
  std::cerr << "<tr><td>";
  if (fs1)
    fs1->print(std::cerr);
  std::cerr << "</td><td>";
  if (fs2)
    fs2->print(std::cerr);
  std::cerr << "</td><td>";
  if (item->getEnvironment())
    item->getEnvironment()->print(std::cerr);
  std::cerr << "</td></tr></table>";
#endif

  featuresPtr result = featuresPtr();

  if (fs1->isBottom() || fs2->isBottom()) {
    result = Features::_bottom;
    goto endUnif;
  }
  if (fs1->isNil() && fs2->isNil()) {
    result = Features::_nil;
    goto endUnif;
  }
  if (fs1->isNil()) {
    result = fs2;
    goto endUnif;
  }
  if (fs2->isNil()) {
    result = fs1;
    goto endUnif;
  }
  result = Features::create();
  for (std::list< featurePtr >::const_iterator i1=fs1->begin();
       i1!=fs1->end();
       ++i1) {

    if ((*i1)->getType()==Feature::PRED) {
      std::list< featurePtr >::const_iterator i2=fs2->begin();
      while(i2!=fs2->end()) {
	if ((*i2)->getType()==Feature::PRED) {
	  (*i2)->addFlags(Flags::SEEN);
	  switch ((*i1)->getValue()->getType()) {
	    
	  case Value::IDENTIFIER:
	    {
	      switch ((*i2)->getValue()->getType()) {
	      case Value::IDENTIFIER:
		if ((*i1)->getValue()->getIdentifier() != (*i2)->getValue()->getIdentifier()) {
		  result = Features::_bottom;
		  goto endUnif;
		}
		break;

	      case Value::VARIABLE:
		result->addFeature(Feature::create(Feature::PRED, bitsetPtr(), (*i1)->getValue()));
		if (!item->getEnvironment())
		  item->setEnvironment(Environment::create());
		item->getEnvironment()->add((*i2)->getValue()->getBits(), (*i1)->getValue());
		break;
		
	      default:
		FATAL_ERROR_STM;
		break;
	      }
	    }
	    break;

	  case Value::VARIABLE:

	    if (((*i2)->getValue()->getType()==Value::VARIABLE) &&
		(*(*i1)->getValue()->getBits()) == (*(*i2)->getValue()->getBits()))
	      {} /* empty */
	    else {
	      if (item) {
		if (!item->getEnvironment())
		  item->setEnvironment(Environment::create());
		item->getEnvironment()->add((*i1)->getValue()->getBits(), (*i2)->getValue());
	      }
	    }
	    result->addFeature(Feature::create(Feature::PRED, bitsetPtr(), (*i2)->getValue()));
	    break;

	  case Value::ANONYMOUS:
	    result->addFeature(Feature::create(Feature::PRED, bitsetPtr(), (*i2)->getValue()));
	    break;

	  default:
	    FATAL_ERROR_STM;
	    break;
	  }

	  break;
	}
	++i2;
      }
      result->addFeature(*i1);
    }
    
    else if ((*i1)->getType()==Feature::FORM) {
      std::list< featurePtr >::const_iterator i2=fs2->begin();
      while(i2!=fs2->end()) {
	if ((*i2)->getType()==Feature::FORM) {

	  (*i2)->addFlags(Flags::SEEN);
	  if (!(*i1)->getValue()->isStr() || !(*i2)->getValue()->isStr())
	    FATAL_ERROR_STM;

	  if ((*i1)->getValue()->getStr() != (*i2)->getValue()->getStr()) {
	    result = Features::_bottom;
	    goto endUnif;
	  }
	  break;
	}
	
	++i2;
      }
      result->addFeature(*i1);
    }

    else if ((*i1)->getType()==Feature::CONSTANT) {
      std::list< featurePtr >::const_iterator i2=fs2->begin();
      while (i2!=fs2->end()) {
	if (((*i2)->getType()==Feature::CONSTANT)
	    && (*(*i1)->getAttribute() & *(*i2)->getAttribute() ).any()) {
	  (*i2)->addFlags(Flags::SEEN);
	  if ((!(*i1)->getValue())
	      || (!(*i2)->getValue())) {
	    result = Features::_bottom;
	    goto endUnif;
	  }

	  switch ((*i1)->getValue()->getType()) {

	  case Value::STR:
	    switch ((*i2)->getValue()->getType()) {
	    case Value::STR:
	      if ((*i1)->getValue()->getStr() != (*i2)->getValue()->getStr()) {
		result = Features::_bottom;
		goto endUnif;
	      }
	      result->addFeature(Feature::create(Feature::CONSTANT, (*i1)->getAttribute(), (*i1)->getValue()));
	      break;

	    case Value::VARIABLE:
	      FATAL_ERROR_STM;
	      /*
		result->addFeature(new Feature((*i2)->getAttribute(), (*i1)->getValue(), Feature::CONSTANT));
		if (item->getEnvironment()==NULL)
		item->setEnvironment(new Environment());
		item->getEnvironment()->add(*(*i2)->getValue()->getBits(), (*i1)->getValue());
	      */
	      break;

	    default:
	      FATAL_ERROR_STM;
	      break;

	    }
	    break;

	  case Value::BOOL:
	    {
	      switch ((*i2)->getValue()->getType()) {
	      case Value::BOOL:
		if ((*i1)->getValue()->isNil() != (*i2)->getValue()->isNil()) {
		  result = Features::_bottom;
		  goto endUnif;
		}

		result->addFeature(Feature::create(Feature::CONSTANT, (*i1)->getAttribute(), (*i1)->getValue()));
		break;
	      case Value::VARIABLE:
		result->addFeature(Feature::create(Feature::CONSTANT, (*i2)->getAttribute(), (*i1)->getValue()));
		if (!item->getEnvironment())
		  item->setEnvironment(Environment::create());
		item->getEnvironment()->add((*i2)->getValue()->getBits(), (*i1)->getValue());
		break;
	      default:
		FATAL_ERROR_STM;
		break;
	      }
	    }
	    break;

	  case Value::DOUBLE:
	    {
	      switch ((*i2)->getValue()->getType()) {
	      case Value::DOUBLE:
		if ((*i1)->getValue()->getDouble() != (*i2)->getValue()->getDouble()) {
		  result = Features::_bottom;
		  goto endUnif;
		}

		result->addFeature(Feature::create(Feature::CONSTANT, (*i1)->getAttribute(), Value::create(Value::DOUBLE, (*i1)->getValue()->getDouble())));
		break;
	      case Value::VARIABLE:
		result->addFeature(Feature::create(Feature::CONSTANT, (*i2)->getAttribute(), (*i1)->getValue()));
		if (!item->getEnvironment())
		  item->setEnvironment(Environment::create());
		item->getEnvironment()->add((*i2)->getValue()->getBits(), (*i1)->getValue());
		break;
	      default:
		FATAL_ERROR_STM;
		break;
	      }
	    }
	    break;

	  case Value::IDENTIFIER:
	    {
	      switch ((*i2)->getValue()->getType()) {
	      case Value::IDENTIFIER:
		if ((*i1)->getValue()->getIdentifier() != (*i2)->getValue()->getIdentifier()) {
		  result = Features::_bottom;
		  goto endUnif;
		}

		result->addFeature(Feature::create(Feature::CONSTANT, (*i1)->getAttribute(), Value::create(Value::IDENTIFIER, (*i1)->getValue()->getIdentifier())));
		break;
	      case Value::VARIABLE:
		result->addFeature(Feature::create(Feature::CONSTANT, (*i2)->getAttribute(), (*i1)->getValue()));
		if (!item->getEnvironment())
		  item->setEnvironment(Environment::create());
		item->getEnvironment()->add((*i2)->getValue()->getBits(), (*i1)->getValue());
		break;
	      default:
		FATAL_ERROR_STM;
		break;
	      }
	    }
	    break;

	  case Value::CONSTANT:
	    {
	      switch ((*i2)->getValue()->getType()) {
	      case Value::CONSTANT:
		if (((*(*i1)->getValue()->getBits()) & (*(*i2)->getValue()->getBits())).none()) {
		  result = Features::_bottom;
		  goto endUnif;
		}

		result->addFeature(Feature::create(Feature::CONSTANT, (*i1)->getAttribute(), Value::create(Value::CONSTANT, Bitset::create(*(*i1)->getValue()->getBits() & *(*i2)->getValue()->getBits()))));
		break;
	      case Value::VARIABLE:
		result->addFeature(Feature::create(Feature::CONSTANT, (*i2)->getAttribute(), (*i1)->getValue()));
		if (!item->getEnvironment())
		  item->setEnvironment(Environment::create());
		item->getEnvironment()->add((*i2)->getValue()->getBits(), (*i1)->getValue());
		break;
	      case Value::ANONYMOUS:
		result->addFeature(Feature::create(Feature::CONSTANT, (*i2)->getAttribute(), (*i1)->getValue()));
		break;
	      default:
		FATAL_ERROR_STM;
		break;
	      }
	    }
	    break;

	  case Value::VARIABLE:

	    if (((*i2)->getValue()->getType()==Value::VARIABLE) &&
		(*(*i1)->getValue()->getBits()) == (*(*i2)->getValue()->getBits()))
	      {} /* empty */
	    else {
	      if (item) {
		if (!item->getEnvironment())
		  item->setEnvironment(Environment::create());
		item->getEnvironment()->add((*i1)->getValue()->getBits(), (*i2)->getValue());
	      }
	    }
	    result->addFeature(Feature::create(Feature::CONSTANT, (*i1)->getAttribute(), (*i2)->getValue()));
	    break;

	  case Value::ANONYMOUS:
	    result->addFeature(Feature::create(Feature::CONSTANT, (*i1)->getAttribute(), (*i2)->getValue()));
	    break;

	  case Value::FEATURES:
	    {
	      featuresPtr features = unif((*i1)->getValue()->getFeatures(), (*i2)->getValue()->getFeatures(), item);
	      if (features->isBottom()) {
		result = features;
		goto endUnif;
	      }
	      else
		result->addFeature(Feature::create(Feature::CONSTANT, (*i1)->getAttribute(), Value::create(Value::FEATURES, features)));
	    }
	    break;

	  case Value::LIST:
	    result->addFeature(Feature::create(Feature::CONSTANT, (*i1)->getAttribute(), (*i1)->getValue()));
	    break;
	  }

	  break;
	}
	++i2;
      }
      if (i2==fs2->end()) {
	result->addFeature(*i1);
      }
    }
  }
  for (std::list< featurePtr >::const_iterator i2=fs2->begin();
       i2!=fs2->end();
       ++i2) {
    if ((*i2)->isUnsetFlags(Flags::SEEN))
      result->addFeature(*i2);
  }

  for (std::list< featurePtr >::const_iterator i1=fs1->begin();
       i1!=fs1->end();
       ++i1) {
    (*i1)->subFlags(Flags::SEEN);
  }
  for (std::list< featurePtr >::const_iterator i2=fs2->begin();
       i2!=fs2->end();
       ++i2) {
    (*i2)->subFlags(Flags::SEEN);
  }

 endUnif:

#ifdef TRACE_EVAL
  std::cerr << "####################### EVAL UNIF DONE #######################" << std::endl;
  std::cerr << "<table border=\"1\"><tr><th>R&eacute;sultat</th><th>Environment</th></tr>";
  std::cerr << "<tr><td>";
  if (result)
    result->print(std::cerr);
  std::cerr << "</td><td>";
  if (item->getEnvironment())
    item->getEnvironment()->print(std::cerr);
  std::cerr << "</td></tr></table>";
#endif
  return result;
}

/* ************************************************************
 * ↓1 = … 
 ************************************************************ */
void
Statement::buildInheritedSonFeatures(itemPtr item, bool &result)
{
  /*** 
       std::cerr << "buildInheritedSonFeatures: ";
       print(std::cerr);
       std::cerr << std::endl;
  ***/
  featuresPtr features = rhs->evalFeatures(item, true);
  if (features->isNil())
    result = false;
  else
    item->getInheritedSonFeatures()->add(lhs->getFirst(), features);
}

/* ************************************************************
 * ⇑ = …
 ************************************************************ */
void
Statement::buildSynthesizedFeatures(itemPtr item, bool &result)
{
  if (!item->getSynthesizedFeatures()->isNil()) {
    this->print(std::cerr);
    FATAL_ERROR_STM;
  }
  featuresPtr features = rhs->evalFeatures(item, true);
  if (features->isNil())
    result = false;
  else{
    item->setSynthesizedFeatures(features);
  }
}

/* ************************************************************
 * [ … X … ] ⊂ ⇓1;
 * X = ⇓1;
 ************************************************************ */
void
Statement::buildEnvironmentWithSynthesize(itemPtr item, bool &result)
{
  switch (this->op) {
  case AFF:
    {
      // X = ⇓1;
      environmentPtr environment;
      if (item->getEnvironment()) {
	environment = item->getEnvironment();
      }
      else {
	environment = Environment::create();
	item->setEnvironment(environment);
      }
      featuresPtr sonSynth = rhs->evalFeatures(item, true);
      if (sonSynth) {
	environment->add(lhs->getBits(), Value::create(Value::FEATURES, sonSynth));
      }
      else
	FATAL_ERROR_STM;
    }
    break;

  case SUBSUME:
    {
      // [ … X … ] ⊂ ⇓1;
      featuresPtr left = lhs->evalFeatures(item, false);
      if (!left) {
	WARNING_STM;
      }
      else {
	environmentPtr environment;
	if (item->getEnvironment())
	  environment = item->getEnvironment();
	else{
	  environment = Environment::create();
	  item->setEnvironment(environment);
	}
	featuresPtr sonSynth = rhs->evalFeatures(item, true);
	if (sonSynth) {
	  if (!left->buildEnvironment(environment, sonSynth, true, true)) {
	    result = false;
	  }
	}
	else{
	  FATAL_ERROR_STM;
	}
      }
    }
    break;

  default:
    FATAL_ERROR_STM;
    break;
  }
}

/* ************************************************************
 * [ … X … ] ⊂ ↑;
 * X = ↑;
 ************************************************************ */
void
Statement::buildEnvironmentWithInherited(itemPtr item, bool &result)
{
  /***
      std::cerr << "<DIV>buildEnvironmentWithInherited ";
      this->print(std::cerr, "", TRUE_ROOT);
      std::cerr << "</DIV>";
  ***/
  switch (this->op) {
  case AFF:
    {
      // X = ↑;
      featuresPtr right = rhs->evalFeatures(item, true);
      if (!right) {
	WARNING_STM;
      }
      else {
	environmentPtr environment;
	if (item->getEnvironment()) {
	  environment = item->getEnvironment();
	}
	else {
	  environment = Environment::create();
	  item->setEnvironment(environment);
	}
	environment->add(lhs->getBits(), Value::create(Value::FEATURES, right));
      }
    }
    break;

  case SUBSUME:
    {
      featuresPtr left = lhs->evalFeatures(item, false);
      if (!left) {
	WARNING_STM;
      }
      else{
	featuresPtr right = rhs->evalFeatures(item, true);
	if (!right) {
	  WARNING_STM;
	}
	else{
	  environmentPtr environment;
	  if (item->getEnvironment()) {
	    environment = item->getEnvironment();
	  }
	  else{
	    environment = Environment::create();
	    item->setEnvironment(environment);
	  }
	  if (!left->buildEnvironment(environment, right, true, true)) {
	    result = false;
	  }
	}
      }
    }
    break;

  default:
    FATAL_ERROR_STM;
    break;
  }
}

/* ************************************************************
 * [ … X … ] ⊂ Y;
 * [ … X … ] ⊂ [ … ];
 * X = a;
 * X = [ … ];
 * X = (...);
 * X = sort X with a;
 * X = reverse X
 * X = <expr>
 * ( … ) = ( … )
 * ( … ) = sort X with a;
 * ( … ) = reverse X;
 * ( … ) = X;
 ************************************************************ */
void
Statement::buildEnvironmentWithValue(itemPtr item, bool &result)
{
  /***
  std::cerr << "<DIV>buildEnvironmentWithValue</DIV>";
  std::cerr << "<DIV>";
  this->print(std::cerr, 0);
  std::cerr << "</DIV>";
  ***/
  switch (this->op) {
  case AFF:
    // 	 X = a;
    // 	 X = Y;
    // 	 X = … ∪ … ;
    // 	 X = [ … ];
    // 	 X = <expr>;
    // 	 X = ( … )
    // 	 X = sort X with a;
    // 	 X = reverse X;

    if (lhs->getOp()==VARIABLE) {
      //*effect = true;
      valuePtr right = rhs->evalValue(item, true);
      if (!right) {
	this->print(std::cerr, 0);
	WARNING_STM;
      }
      else {
	environmentPtr environment;
	if (item->getEnvironment()) {
	  environment = item->getEnvironment();
	}
	else {
	  environment = Environment::create();
	  item->setEnvironment(environment);
	}
	environment->add(lhs->getBits(), right);
      }
    }

    // 	 ( … ) = X;
    // 	 ( … ) = ( … )
    // 	 ( … ) = sort X with a;
    // 	 ( … ) = reverse X;
    else if (lhs->getOp()==LIST) {
      //*effect = true;
      listPtr right = rhs->evalList(item, true);
      if (!right) {
	FATAL_ERROR_STM;
	WARNING_STM;
      }
      else {
	if (right->isNil()) {
	  FATAL_ERROR_STM;
	  result = false;
	}
	listPtr left = lhs->evalList(item, false);
	if (!left) {
	  WARNING_STM;
	}
	else{
	  environmentPtr environment;
	  if (item->getEnvironment()) {
	    environment = item->getEnvironment();
	  }
	  else{
	    environment = Environment::create();
	    item->setEnvironment(environment);
	  }
	  if (!left->buildEnvironment(environment, right, true, true)) {
	    result = false;
	  }
	}
      }
    }

    else
      FATAL_ERROR_STM;
    break;

  case SUBSUME:
    {
      featuresPtr right = rhs->evalFeatures(item, true);
      if (!right) {
	WARNING_STM;
      }
      else {
	if (right->isNil())
	  {} // empty
	featuresPtr left = lhs->evalFeatures(item, false);
	if (left) {
	  environmentPtr environment;
	  if (item->getEnvironment()) {
	    environment = item->getEnvironment();
	  }
	  else {
	    environment = Environment::create();
	    item->setEnvironment(environment);
	  }
	  if (!left->buildEnvironment(environment, right, true, true)) {
	    result = false;
	  }
	}
      }
    }
    break;

  default:
    FATAL_ERROR_STM;
    break;
  }
}

/* ************************************************************
 * attest
 ************************************************************ */
void
Statement::attest(itemPtr item, bool &result)
{
  /*** 
       std::cerr << "<DIV>*** attest</DIV>";
       std::cerr << "<DIV>";
       this->print(std::cerr);
       std::cerr << "</DIV>";
  ***/
  switch (this->op) {
  case ATTEST:
    {
      valuePtr res = lhs->evalValue(item, true);
      if ((!res)
	  || (res == Value::_nil)
	  || (res == Value::_anonymous)
	  || ((res->getType()==Value::FEATURES) && (res->getFeatures()->isBottom()))) {
	result = false;
      }
    }
    break;
  default:
    FATAL_ERROR_STM;
    break;
  }
}

/* ************************************************************
 * guard
 ************************************************************ */
void
Statement::guard(itemPtr item, bool &result, bool trace)
{
  /***
      STD::CERR_LINE;
      std::cerr << "<DIV>guard ";
      item->print(std::cerr, NULL);
      print(std::cerr);
      std::cerr << "</DIV>";
  ***/
  if (isSetFlags(Flags::DISABLED | Flags::SEEN)) {
    FATAL_ERROR_STM;
  }
  else{
    featuresPtr features = getFeatures();
    if (!features) {
      FATAL_ERROR_STM;
    }
    environmentPtr environment;
    if (item->getEnvironment())
      environment = item->getEnvironment();
    else{
      environment = Environment::create();
      item->setEnvironment(environment);
    }
    featuresPtr rhs = item->getInheritedFeatures();
    if (!features->buildEnvironment(environment, rhs, false, true))
      result = false;
    else {
      if (trace) {
	std::cerr << "*** Guard evaluated to true " << item->getFilename() << '(' << item->getLineno() << ')' << std::endl;
      }
    }
    if (item->getEnvironment()->size()==0) {
      item->getEnvironment().reset();
      item->setEnvironment(environmentPtr());
    }
  }
  /***
      std::cerr << "<DIV>guard done";
      item->print(std::cerr, NULL);
      std::cerr << "</DIV>";
  ***/
}

/* ************************************************************
 * 
 ************************************************************ */
void
Statement::stmPrint(itemPtr item)
{
  addFlags(Flags::SEEN);
  if (lhs->getOp()==STR) {
    std::cout << lhs->getStr();
  }
  else{
    valuePtr value = lhs->evalValue(item, true);
    value->print(std::cout, true, true);
  }
}

/* ************************************************************
 * 
 ************************************************************ */
void
Statement::stmPrintln(itemPtr item)
{
  stmPrint(item);
  std::cout << std::endl;
}

/* **************************************************
 *
 ************************************************** */
void
Statement::renameVariables(unsigned int i)
{
  switch (this->op) {
  case VARIABLE:
    {
      //ostringstream oss;
      //oss << getBits()->toString() << "_" << i;
      //string str = oss.str();
      std::string str = getBits()->_toString() + "_" + std::to_string(i);
      bitsetPtr variableBits = Vartable::varTableAdd(str);
      bits = variableBits;
      //resetSerialID();
    }
    break;
  case CONSTANT:
  case NIL:
  case STR:
  case NOT_NIL:
  case DOUBLE:
  case UP:
  case UP2:
  case DASH:
  case DOWN2:
  case DOWN:
  case FINISHED:
    break;
  case AFF:
  case SUBSUME:
  case INSET:
  case FCT:
  case UNIF:
  case SORT:
  case REVERSE:
  case ATTEST:
  case PRINT:
  case PRINTLN:
  case IF:
  case THENELSE:
    if (lhs)
      lhs->renameVariables(i);
    if (rhs)
      rhs->renameVariables(i);
    break;
  case FEATURES:
  case GUARD:
    getFeatures()->renameVariables(i);
    break;
  case LIST:
    getList()->renameVariables(i);
    break;
  case STMS:
    getStatements()->renameVariables(i);
    break;
  }
}

/* ************************************************************
 *
 ************************************************************ */
void Statement::enable(statementPtr root, itemPtr item, bool &effect, bool on)
{
  switch (this->op) {
    
  case STMS:
    getStatements()->enable(item, effect, on);
    break;

  case IF:
    lhs->enable(shared_from_this(), item, effect, on);
    rhs->enable(rhs, item, effect, on);
    break;

  case THENELSE:
    lhs->enable(lhs, item, effect, on);
    if (rhs)
      rhs->enable(rhs, item, effect, on);
    break;
    
  case GUARD:
    if (on) {
      if (item->getInheritedFeatures()->isNil()) {
	this->addFlags(Flags::DISABLED);
	effect = true;
      }
    }
    else{
      this->subFlags(Flags::DISABLED);
    }
    break;

  case AFF:
  case SUBSUME:
  case INSET:
    rhs->enable(shared_from_this(), item, effect, on);
    break;

  case FCT:
  case UNIF:
    if (lhs)
      lhs->enable(root, item, effect, on);
    if (rhs)
      rhs->enable(root, item, effect, on);
    break;

  case ATTEST:
  case PRINT:
  case PRINTLN:
    lhs->enable(root, item, effect, on);
    break;

  case DASH:
    // if (#1)   NP -> [det] N { if (#1) ↓1 = ↑ ∪ ⇓2 ∪ [qual:$Qual, part:$Part]; else [detNum:NIL, det:no]; }
    // if (#2)   VP -> VP [NP] {   if (#2) { ↓1 = $Rest; ↓2 = [pcas:$pcas, $PObj];} else { attest ($Pred == _pro); ↓1 = [prep_objCl:$PObj, $Rest];} }
    if (on) {
      if (item->getTerms(getFirst())
	  && ((!item->getTerms(getFirst())->isOptional() && item->getTerms(getFirst())->size()==1)
	      || (item->getTerms(getFirst())->isOptional() && item->getForestIdentifiers()[getFirst()])
	      )
	  ) {
      }
      else{
	root->addFlags(Flags::DISABLED);
	effect = true;
      }
    }
    else {
      root->subFlags(Flags::DISABLED);
      effect = true;
    }
    break;
    
  case VARIABLE:
    // ??? Une variable seule est évaluable, même si elle n'est pas instanciée: elle vaut _nil
    if (on) {
      if ((!item->getEnvironment())
	  ||!(item->getEnvironment()->find(getBits()))) {
	root->addFlags(Flags::DISABLED);
	effect = true;
      }
    }
    else {
      root->subFlags(Flags::DISABLED);
      effect = true;
    }
    break;
    
  case LIST:
    getList()->enable(root, item, effect, on);
    break;
    
  case FEATURES:
    getFeatures()->enable(root, item, effect, on);
    break;
    
  case DOWN:
    if (on) {
      if ((*item->getInheritedSonFeatures())[getFirst()]->isNil()) {
	root->addFlags(Flags::DISABLED);
	effect = true;
      }
    }
    else {
      root->subFlags(Flags::DISABLED);
      effect = true;
    }
    break;
    
  case DOWN2:
    if (on) {
      if ((*item->getSynthesizedSonFeatures())[getFirst()]->isNil()) {
	root->addFlags(Flags::DISABLED);
	effect = true;
      }
    }
    else {
      root->subFlags(Flags::DISABLED);
      effect = true;
    }
    break;
    
  case UP:
    if (on) {
      if (item->getInheritedFeatures()->isNil()) {
	root->addFlags(Flags::DISABLED);
	effect = true;
      }
    }
    else {
      root->subFlags(Flags::DISABLED);
      effect = true;
    }
    break;
    
  case UP2:
    if (on) {
      if (item->getSynthesizedFeatures()->isNil()) {
	root->addFlags(Flags::DISABLED);
	effect = true;
      }
    }
    else {
      root->subFlags(Flags::DISABLED);
      effect = true;
    }
    break;
    
  case SORT:
  case REVERSE:
  case CONSTANT:
  case NIL:
  case NOT_NIL:
  case STR:
  case FINISHED:
  case DOUBLE:
    break;
  }
}
  
/* **************************************************
 * true if effect
 ************************************************** */
void
Statement::apply(itemPtr item, bool &result, bool &effect, bool trace)
{
#ifdef TRACE_EVAL
  std::cerr << "####################### APPLY STATEMENT #######################" << std::endl;
  std::cerr << "<DIV>";
  print(std::cerr);
  std::cerr << "</DIV>";
#endif

  if (isSetFlags(Flags::SEEN | DISABLED))
    return;

  if (item->isSetFlags(Flags::BOTTOM))
    return;

  if (getOp()==Statement::IF) {
    statementPtr left = getRhs()->getLhs();
    statementPtr right = getRhs()->getRhs();

    int resif=0;// 0:none 1:then 2:else
    if (left->isSetFlags(Flags::CHOOSEN))
      resif=1;
    else if (right && right->isSetFlags(Flags::CHOOSEN))
      resif=2;
    else {
      valuePtr res = getLhs()->evalValue(item, true);
      if (!res)
	resif=0;
      else if (res == Value::_nil
	       || res == Value::_anonymous) {
	resif=2;
	left->addFlags(Flags::REJECTED);
	if (right)
	  right->addFlags(Flags::CHOOSEN);
      }
      else {
	resif=1;
	left->addFlags(Flags::CHOOSEN);
	if (right)
	  right->addFlags(Flags::REJECTED);
      }
    }
    bool localResult = true;
    switch (resif) {
    case 1:
      left->apply(item, localResult, effect, trace);
      if (left->isSetFlags(Flags::BOTTOM))
	item->addFlags(Flags::BOTTOM);
      break;
    case 2:
      if (right) {
	right->apply(item, localResult, effect, trace);
	if (right->isSetFlags(Flags::BOTTOM))
	  item->addFlags(Flags::BOTTOM);
      }
      break;
    }
  }

  // […]
  else if (getOp()==Statement::GUARD) {
    guard(item, result, trace);
    effect = true;
    addFlags(Flags::SEEN);
  }

  // ↓1 = …
  else if ((getOp()==Statement::AFF)
	   && (getLhs()->getOp()==Statement::DOWN)) {
    buildInheritedSonFeatures(item, result);
    effect = true;
    addFlags(Flags::SEEN);
  }

  // [ … X … ] ⊂ ⇓1
  // X = ⇓1
  else if (((getOp()==Statement::SUBSUME)
	    && (getRhs()->getOp()==Statement::DOWN2)
	    && (getLhs()->getOp()==Statement::FEATURES))
	   ||
	   ((getOp()==Statement::AFF)
	    && (getRhs()->getOp()==Statement::DOWN2)
	    && (getLhs()->getOp()==Statement::VARIABLE))) {
    buildEnvironmentWithSynthesize(item, result);
    effect = true;
    addFlags(Flags::SEEN);
  }

  // [ … X … ] ⊂ ↑
  // X = ↑
  else if (((getOp()==Statement::SUBSUME)
	    && (getRhs()->getOp()==Statement::UP)
	    && (getLhs()->getOp()==Statement::FEATURES))
	   ||
	   ((getOp()==Statement::AFF)
	    && (getRhs()->getOp()==Statement::UP)
	    && (getLhs()->getOp()==Statement::VARIABLE))) {
    buildEnvironmentWithInherited(item, result);
    effect = true;
    addFlags(Flags::SEEN);
  }

  // X = a;
  // X = Y;
  // X = … ∪ … ;
  // X = [ … ];
  // X = <expr>;
  // X = ( … )
  // X = sort Y with a;
  // X = reverse Y;
  // X = combination Y;
  //
  // ( … ) = X;
  // ( … ) = ( … )
  // ( … ) = sort X with a;
  // ( … ) = reverse X;
  //
  // […X…] ⊂ Y
  // […X…] ⊂ […]
  else if (((getOp()==Statement::AFF)
	    && (getLhs()->getOp()==Statement::VARIABLE)
	    && ((getRhs()->getOp()==Statement::CONSTANT)
		||(getRhs()->getOp()==Statement::VARIABLE)
		||(getRhs()->getOp()==Statement::UNIF)
		||(getRhs()->getOp()==Statement::FEATURES)
		||(getRhs()->getOp()==Statement::DOUBLE)
		||(getRhs()->getOp()==Statement::FCT)
		||(getRhs()->getOp()==Statement::LIST)
		||(getRhs()->getOp()==Statement::SORT)
		||(getRhs()->getOp()==Statement::REVERSE)))
	   ||((getOp()==Statement::AFF)
	      && (getLhs()->getOp()==Statement::LIST)
	      && ((getRhs()->getOp()==Statement::VARIABLE)
		  ||(getRhs()->getOp()==Statement::LIST)
		  ||(getRhs()->getOp()==Statement::SORT)
		  ||(getRhs()->getOp()==Statement::REVERSE)))
	   ||((getOp()==Statement::SUBSUME)
	      && (getLhs()->getOp()==Statement::FEATURES)
	      && ((getRhs()->getOp()==Statement::VARIABLE)
		  ||(getRhs()->getOp()==Statement::FEATURES)))) {
    buildEnvironmentWithValue(item, result);
    effect = true;
    addFlags(Flags::SEEN);
  }

  // ⇑ = …
  else if ((getOp()==Statement::AFF)
	   && (getLhs()->getOp()==Statement::UP2)) {
    buildSynthesizedFeatures(item, result);
    effect = true;
    addFlags(Flags::SEEN);
  }

  // attest …
  else if (getOp()==Statement::ATTEST) {
    attest(item, result);
    effect = true;
    addFlags(Flags::SEEN);
  }

  // print
  else if (getOp()==Statement::PRINT) {
    stmPrint(item);
    effect = true;
    addFlags(Flags::SEEN);
  }

  // println
  else if (getOp()==Statement::PRINTLN) {
    stmPrintln(item);
    effect = true;
    addFlags(Flags::SEEN);
  }

  // statements
  else if (getOp()==Statement::STMS) {
    getStatements()->apply(item, effect, trace);
  }

  else{
    cerr << "Not yet implemented" << endl;
    cerr << this->serialize() << endl;
    FATAL_ERROR_STM;
  }

  if (!result) {
    addFlags(Flags::BOTTOM);
    //item->addFlags(Flags::BOTTOM);
  }

#ifdef TRACE_EVAL
  std::cerr << "####################### APPLY STATEMENT DONE #######################" << std::endl;
  std::cerr << "<DIV>";
  item->print(std::cerr);
  print(std::cerr);
  std::cerr << "</DIV>";
#endif
}

/* **************************************************
 *
 ************************************************** */
void
Statement::lookingForAssignedInheritedSonFeatures(std::vector< bool > &assignedInheritedSonFeatures)
{
  switch (this->op) {
  case AFF:
    // ↓1 = …
    if ((this->getOp()==Statement::AFF) && (this->getLhs()->getOp()==Statement::DOWN))
      assignedInheritedSonFeatures[this->getLhs()->getFirst()] = true;
    break;

  case IF:
    {
      statementPtr left = getRhs()->getLhs();
      statementPtr right = getRhs()->getRhs();
      if (left->isSetFlags(Flags::CHOOSEN)) {
	left->lookingForAssignedInheritedSonFeatures(assignedInheritedSonFeatures);
      }
      else if (right && right->isSetFlags(Flags::CHOOSEN)) {
	right->lookingForAssignedInheritedSonFeatures(assignedInheritedSonFeatures);
      }
    }
    break;

  case STMS:
    getStatements()->lookingForAssignedInheritedSonFeatures(assignedInheritedSonFeatures);
    break;

  default:
    break;
  }
}

/* ************************************************************
 *
 ************************************************************ */
bool Statement::findVariable(bitsetPtr variable)
{
  switch (this->op) {

  case STMS:
    if (getStatements()->findVariableElsewhere(statementPtr(), variable))
      return true;
    break;

  case IF:
    if (rhs->findVariable(variable))
      return true;
    break;

  case THENELSE:
    if (lhs->findVariable(variable))
      return true;
    if (rhs)
      if (rhs->findVariable(variable))
	return true;
    break;
    
  case GUARD:
    if (getFeatures()->findVariable(variable))
      return true;
    break;
    
  case AFF:
  case SUBSUME:
  case INSET:
    if(rhs->findVariable(variable))
      return true;
    break;

  case FCT:
  case UNIF:
    if (lhs && lhs->findVariable(variable))
      return true;
    if (rhs && rhs->findVariable(variable))
      return true;
    break;

  case ATTEST:
  case PRINT:
  case PRINTLN:
    if(lhs->findVariable(variable))
      return true;
    break;

  case VARIABLE:
    if (getBits() == variable)
      return true;
    break;
    
  case LIST:
    if(getList()->findVariable(variable))
      return true;
    break;
    
  case FEATURES:
    if (getFeatures()->findVariable(variable))
      return true;
    break;
    
  case DOWN:
    FATAL_ERROR;
    break;
    
  case DASH:
  case DOWN2:
  case SORT:
  case REVERSE:
  case CONSTANT:
  case NIL:
  case NOT_NIL:
  case UP2:
  case STR:
  case UP:
  case FINISHED:
  case DOUBLE:
    break;
  }
  return false;
}
  
