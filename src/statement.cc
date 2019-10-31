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
Statement::Statement(unsigned int lineno, type op, std::string str)
		: Flags() {
	this->lineno = lineno;
	this->op = op;
	this->lhs = statementPtr();
	this->rhs = statementPtr();
	this->pair.first = 0;
	this->pair.second = 0;
	this->features = featuresPtr();
	this->bits = bitsetPtr();
	this->str = str;
	this->fct = NOP;
	this->list = listPtr();
	this->statements = statementsPtr();
	this->number = 0;
	NEW;
}

/* **************************************************
 *
 ************************************************** */
Statement::Statement(unsigned int lineno, type op, statementPtr lhs, statementPtr rhs, unsigned int first, unsigned int second, featuresPtr features, bitsetPtr bits,
		arithmetic_op fct, listPtr list, statementsPtr statements, double number)
		: Flags() {
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
	NEW;
}

/* **************************************************
 *
 ************************************************** */
Statement::~Statement(void) {
	DELETE;
}

/* **************************************************
 *
 ************************************************** */
statementPtr Statement::create(unsigned int lineno, type op, statementPtr lhs, statementPtr rhs) {
	return statementPtr(new Statement(lineno, op, lhs, rhs));
}

/* **************************************************
 *
 ************************************************** */
statementPtr Statement::create(unsigned int lineno, type op, unsigned int first, unsigned int second) {
	return statementPtr(new Statement(lineno, op, statementPtr(), statementPtr(), first, second));
}

/* **************************************************
 *
 ************************************************** */
statementPtr Statement::create(unsigned int lineno, type op, featuresPtr features) {
	return statementPtr(new Statement(lineno, op, statementPtr(), statementPtr(), UINT_MAX,
	UINT_MAX, features));
}

/* **************************************************
 *
 ************************************************** */
statementPtr Statement::create(unsigned int lineno, type op, valuePtr value) {
	return statementPtr(new Statement(lineno, op, statementPtr(), statementPtr(), UINT_MAX,
	UINT_MAX));
}

/* **************************************************
 *
 ************************************************** */
statementPtr Statement::create(unsigned int lineno, type op, bitsetPtr bits, statementPtr lhs) {
	return statementPtr(new Statement(lineno, op, lhs, statementPtr(), UINT_MAX,
	UINT_MAX, featuresPtr(), bits));
}

/* **************************************************
 *
 ************************************************** */
statementPtr Statement::create(unsigned int lineno, type op, std::string str) {
	return statementPtr(new Statement(lineno, op, str));
}

/* **************************************************
 *
 ************************************************** */
statementPtr Statement::create(unsigned int lineno, type op, arithmetic_op fct, statementPtr lhs, statementPtr rhs) {
	return statementPtr(new Statement(lineno, op, lhs, rhs, UINT_MAX, UINT_MAX, featuresPtr(), bitsetPtr(), fct));
}

/* **************************************************
 *
 ************************************************** */
statementPtr Statement::create(unsigned int lineno, type op, listPtr list) {
	return statementPtr(new Statement(lineno, op, statementPtr(), statementPtr(), UINT_MAX,
	UINT_MAX, featuresPtr(), bitsetPtr(), Statement::NOP, list));
}

/* **************************************************
 *
 ************************************************** */
statementPtr Statement::create(unsigned int lineno, type op, statementsPtr statements) {
	return statementPtr(new Statement(lineno, op, statementPtr(), statementPtr(), UINT_MAX,
	UINT_MAX, featuresPtr(), bitsetPtr(), Statement::NOP, listPtr(), statements));
}

/* **************************************************
 *
 ************************************************** */
statementPtr Statement::create(unsigned int lineno, type op, double number) {
	return statementPtr(new Statement(lineno, op, statementPtr(), statementPtr(), UINT_MAX,
	UINT_MAX, featuresPtr(), bitsetPtr(), Statement::NOP, listPtr(), statementsPtr(), number));
}

/* **************************************************
 *
 ************************************************** */
statementPtr Statement::create(void) {
	return statementPtr(new Statement(0, DASH, statementPtr(), statementPtr(), UINT_MAX,
	UINT_MAX, featuresPtr(), bitsetPtr(), Statement::NOP, listPtr(), statementsPtr()));
}

/* **************************************************
 *
 ************************************************** */
const bool Statement::isAff(void) const {
	return op == AFF;
}

/* **************************************************
 *
 ************************************************** */
const bool Statement::isSubsume(void) const {
	return op == SUBSUME;
}

/* **************************************************
 *
 ************************************************** */
const bool Statement::isUp(void) const {
	return op == UP;
}

/* **************************************************
 *
 ************************************************** */
const bool Statement::isUp2(void) const {
	return op == UP2;
}

/* **************************************************
 *
 ************************************************** */
const bool Statement::isDown(void) const {
	return op == DOWN;
}

/* **************************************************
 *
 ************************************************** */
const bool Statement::isSearch(void) const {
	return op == SEARCH;
}

/* **************************************************
 *
 ************************************************** */
const bool Statement::isDown2(void) const {
	return op == DOWN2;
}

/* **************************************************
 *
 ************************************************** */
const bool Statement::isFeatures(void) const {
	return op == FEATURES;
}

/* **************************************************
 *
 ************************************************** */
const bool Statement::isVariable(void) const {
	return op == VARIABLE;
}

/* **************************************************
 *
 ************************************************** */
const bool Statement::isConstant(void) const {
	return op == CONSTANT;
}

/* **************************************************
 *
 ************************************************** */
const bool Statement::isUnif(void) const {
	return op == UNIF;
}

/* **************************************************
 *
 ************************************************** */
const bool Statement::isGuard(void) const {
	return op == GUARD;
}

/* **************************************************
 *
 ************************************************** */
const bool Statement::isPrint(void) const {
	return op == PRINT;
}

/* **************************************************
 *
 ************************************************** */
const bool Statement::isPrintln(void) const {
	return op == PRINTLN;
}

/* **************************************************
 *
 ************************************************** */
const bool Statement::isAttest(void) const {
	return op == ATTEST;
}

/* **************************************************
 *
 ************************************************** */
const bool Statement::isIf(void) const {
	return op == IF;
}

/* **************************************************
 *
 ************************************************** */
const bool Statement::isForeach(void) const {
	return op == FOREACH;
}

/* **************************************************
 *
 ************************************************** */
const bool Statement::isStms(void) const {
	return op == STMS;
}

/* **************************************************
 *
 ************************************************** */
const bool Statement::isStr(void) const {
	return op == STR;
}

/* **************************************************
 *
 ************************************************** */
const bool Statement::isList(void) const {
	return op == LIST;
}

/* **************************************************
 *
 ************************************************** */
const bool Statement::isDouble(void) const {
	return op == DOUBLE;
}

/* **************************************************
 *
 ************************************************** */
const bool Statement::isFct(void) const {
	return op == FCT;
}

/* **************************************************
 *
 ************************************************** */
const Statement::arithmetic_op Statement::getFct(void) const {
	return fct;
}

/* **************************************************
 *
 ************************************************** */
const statementPtr Statement::getLhs(void) const {
	return lhs;
}

/* **************************************************
 *
 ************************************************** */
const statementPtr Statement::getRhs(void) const {
	return rhs;
}

/* **************************************************
 *
 ************************************************** */
const featuresPtr Statement::getFeatures(void) const {
	return features;
}
;

/* **************************************************
 *
 ************************************************** */
const bitsetPtr Statement::getBits(void) const {
	return bits;
}

/* **************************************************
 *
 ************************************************** */
const unsigned int Statement::getFirst(void) const {
	return pair.first;
}

/* **************************************************
 *
 ************************************************** */
const unsigned int Statement::getSecond(void) const {
	return pair.second;
}

/* **************************************************
 *
 ************************************************** */
const std::string Statement::getStr(void) const {
	return str;
}

/* **************************************************
 *
 ************************************************** */
const listPtr Statement::getList(void) const {
	return list;
}

/* **************************************************
 *
 ************************************************** */
const statementsPtr Statement::getStatements(void) const {
	return statements;
}

/* **************************************************
 *
 ************************************************** */
const double Statement::getNumber(void) const {
	return number;
}

/* **************************************************
 *
 ************************************************** */
const unsigned int Statement::getLineno(void) const {
	return lineno;
}

/* **************************************************
 *
 ************************************************** */
void Statement::print(std::ostream &outStream, unsigned int tabulation, int yetColored) const {
	switch (this->op) {
		case ATTEST:
		case AFF:
		case SUBSUME:
		case PRINT:
		case PRINTLN:
		case GUARD:
		case IF:
		case THENELSE:
		case FOREACH:
			for (unsigned int j = 1; j <= tabulation; j++)
				outStream << "&nbsp;";
			break;
		default:
			break;
	}
	int color = yetColored;
	if (isSetFlags(Flags::SEEN)) {
		color |= 0x0000FF;
	}
	if (isSetFlags(Flags::DISABLED)) {
		color |= 0xC0C0C0;
	}
	if (isSetFlags(Flags::BOTTOM)) {
		color |= 0xFF0000;
	}
	if (color != 0)
		outStream << "<SPAN style=\"color:#" << std::setfill('0') << std::setw(6) << std::hex << color << ";\">";
	if (isSetFlags(Flags::REJECTED)) {
		outStream << "<S>";
	}
	switch (this->op) {
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
			outStream << getBits()->toString();
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
			getFeatures()->flatPrint(outStream);
			break;
		case LIST:
			getList()->flatPrint(outStream, true);
			break;
		case GUARD:
			getFeatures()->flatPrint(outStream);
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
			outStream << '#' << getFirst() + 1;
			if (getSecond() != UINT_MAX) {
				outStream << ":" << getSecond() + 1;
			}
			break;
		case DOWN:
			outStream << "↓" << getFirst() + 1;
			if (getSecond() != UINT_MAX) {
				outStream << "." << getSecond() + 1;
			}
			break;
		case DOWN2:
			outStream << "⇓";
			outStream << getFirst() + 1;
			break;
		case IF:
			outStream << "if&nbsp;(";
			lhs->print(outStream);
			outStream << ')';
			rhs->print(outStream, tabulation);
			break;
		case THENELSE:
			outStream << "<DIV";
			if (color != 0)
				outStream << " style=\"color:" << std::hex << color << "\"";
			outStream << ">";
			lhs->print(outStream, tabulation + 3);
			outStream << "</DIV>";
			if (rhs) {
				for (unsigned int j = 1; j <= tabulation; j++)
					outStream << "&nbsp;";
				outStream << "else ";
				outStream << "<DIV>";
				rhs->print(outStream, tabulation + 3);
				outStream << "</DIV>";
			}
			break;
		case FOREACH:
			outStream << "foreach&nbsp;";
			lhs->print(outStream);
			outStream << "&nbsp;";
			rhs->print(outStream);
			break;
		case IN:
			outStream << "in&nbsp;";
			lhs->print(outStream);
			rhs->print(outStream, tabulation + 3);
			break;
		case STR:
			outStream << "&quot;" << getStr() << "&quot;";
			break;
		case STMS:
			getStatements()->print(outStream, tabulation);
			break;
		case DOUBLE:
			outStream << getNumber();
			break;
		case SEARCH:
			outStream << "search&nbsp;";
			lhs->print(outStream);
			break;
	}
	switch (this->op) {
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
	if (color != 0)
		outStream << "</SPAN>";
}

/* **************************************************
 *
 ************************************************** */
void Statement::makeSerialString() {
	serialString = std::string();
	switch (this->op) {
		case ATTEST:
			serialString = 'A' + lhs->peekSerialString();
			break;
		case NIL:
			serialString = 'N';
			break;
		case NOT_NIL:
			serialString = '~';
			break;
		case FINISHED:
			serialString = 'F';
			break;
		case AFF:
			serialString = lhs->peekSerialString() + '=' + rhs->peekSerialString();
			break;
		case SUBSUME:
			serialString = lhs->peekSerialString() + "⊂" + rhs->peekSerialString();
			break;
		case INSET:
			serialString = lhs->peekSerialString() + "∈" + rhs->peekSerialString();
			break;
		case FCT:
			switch (this->getFct()) {
				case NOP:
					serialString = ';';
					break;
				case NOT:
					serialString = "¬(" + lhs->peekSerialString() + ')';
					break;
				case AND:
					serialString = '(' + lhs->peekSerialString() + "∧" + rhs->peekSerialString() + ')';
					break;
				case OR:
					serialString = '(' + lhs->peekSerialString() + "∨" + rhs->peekSerialString() + ')';
					break;
				case DIFF:
					serialString = '(' + lhs->peekSerialString() + "≠" + rhs->peekSerialString() + ')';
					break;
				case EQ:
					serialString = '(' + lhs->peekSerialString() + "==" + rhs->peekSerialString() + ')';
					break;
				case PLUS:
					serialString = '(' + lhs->peekSerialString() + '+' + rhs->peekSerialString() + ')';
					break;
				case MINUS:
					serialString = '(' + lhs->peekSerialString() + '-' + rhs->peekSerialString() + ')';
					break;
				case TIMES:
					serialString = '(' + lhs->peekSerialString() + '*' + rhs->peekSerialString() + ')';
					break;
				case DIVIDE:
					serialString = '(' + lhs->peekSerialString() + '/' + rhs->peekSerialString() + ')';
					break;
				case MODULO:
					serialString = '(' + lhs->peekSerialString() + '%' + rhs->peekSerialString() + ')';
					break;
				case LT:
					serialString = '(' + lhs->peekSerialString() + '<' + rhs->peekSerialString() + ')';
					break;
				case LE:
					serialString = '(' + lhs->peekSerialString() + "≤" + rhs->peekSerialString() + ')';
					break;
				case GT:
					serialString = '(' + lhs->peekSerialString() + '>' + rhs->peekSerialString() + ')';
					break;
				case GE:
					serialString = '(' + lhs->peekSerialString() + "≥" + rhs->peekSerialString() + ')';
					break;
				case MINUS_U:
					serialString = '-' + lhs->peekSerialString();
					break;
				case RAND:
					serialString = "r()";
					break;
			}
			break;
		case CONSTANT:
		case VARIABLE:
			serialString = getBits()->peekSerialString();
			break;
		case PRINT:
			serialString = "P " + lhs->peekSerialString();
			break;
		case PRINTLN:
			serialString = "PL " + lhs->peekSerialString();
			break;
		case FEATURES:
			serialString = getFeatures()->peekSerialString();
			break;
		case LIST:
			serialString = getList()->peekSerialString();
			break;
		case GUARD:
			serialString = "G " + getFeatures()->peekSerialString();
			break;
		case UNIF:
			serialString = '(' + lhs->peekSerialString() + "∪" + rhs->peekSerialString() + ')';
			break;
		case UP:
			serialString = "↑";
			break;
		case UP2:
			serialString = "⇑";
			break;
		case DASH:
			serialString = '#' + std::to_string(getFirst() + 1);
			if (getSecond() != UINT_MAX)
				serialString += ":" + std::to_string(getSecond() + 1);
			break;
		case DOWN:
			serialString = "↓" + std::to_string(getFirst() + 1);
			if (getSecond() != UINT_MAX)
				serialString += '.' + std::to_string(getSecond() + 1);
			break;
		case DOWN2:
			serialString = "⇓" + std::to_string(getFirst() + 1);
			break;
		case IF:
			serialString = "I(" + lhs->peekSerialString() + ')' + rhs->peekSerialString();
			break;
		case THENELSE:
			serialString = "T(" + lhs->peekSerialString() + ')';
			if (rhs) {
				serialString += "E(" + rhs->peekSerialString() + ')';
			}
			break;
		case FOREACH:
			serialString = "O(" + lhs->peekSerialString() + ')' + rhs->peekSerialString();
			break;
		case IN:
			serialString = "IN(" + lhs->peekSerialString() + ')';
			if (rhs) {
				serialString += "D(" + rhs->peekSerialString() + ')';
			}
			break;
		case STR:
			serialString = '"' + getStr() + '"';
			break;
		case STMS:
			serialString = getStatements()->peekSerialString();
			break;
		case DOUBLE:
			serialString = getNumber();
			break;
		case SEARCH:
			CERR_LINE
			;
			serialString = "S(" + lhs->peekSerialString() + ')';
			break;
	}
}

/* **************************************************
 *
 ************************************************** */
statementPtr Statement::clone(const std::bitset<Flags::FLAGS>& protectedFlags) {
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
			statement = Statement::create(this->lineno, this->op, lhs ? lhs->clone(protectedFlags) : statementPtr());
			break;
		case IF:
		case THENELSE:
		case FOREACH:
		case IN:
		case UNIF:
		case AFF:
		case SUBSUME:
		case INSET:
			statement = Statement::create(this->lineno, this->op, lhs ? lhs->clone(protectedFlags) : statementPtr(), rhs ? rhs->clone(protectedFlags) : statementPtr());
			break;
		case FCT:
			statement = Statement::create(this->lineno, this->op, this->getFct(), lhs ? lhs->clone(protectedFlags) : statementPtr(), rhs ? rhs->clone(protectedFlags) : statementPtr());
			break;
		case STMS:
			statement = Statement::create(this->lineno, this->op, getStatements()->clone(protectedFlags));
			break;
		case SEARCH:
			statement = Statement::create(this->lineno, this->op, lhs ? lhs->clone(protectedFlags) : statementPtr());
			break;
	}
	statement->addFlags(protectedFlags & this->getFlags());
	return statement;
}

/* **************************************************
 *
 ************************************************** */
featuresPtr Statement::evalFeatures(itemPtr item, Synthesizer *synthesizer, bool replaceVariables) {
#ifdef TRACE_EVAL
	std::cout << "####################### EVAL FEATURES #######################" << std::endl;
	std::cout << "<div>" << std::endl;
	this->print(std::cout);
	std::cout << std::endl;
	item->print(std::cout);
	std::cout << "</div>" << std::endl;
#endif

	featuresPtr resultFeatures = Features::NIL;
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
		case FOREACH:
		case IN:
		case AFF:
		case SUBSUME:
		case INSET:
		case DOWN:
		case UP2:
		case LIST:
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
				featuresPtr fs1=lhs->evalFeatures(item, synthesizer, replaceVariables);
				featuresPtr fs2=rhs->evalFeatures(item, synthesizer, replaceVariables);
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
			case SEARCH:
			{
				featuresPtr fs = lhs->evalFeatures(item, synthesizer, replaceVariables);
				if (!fs) {
					resultFeatures = featuresPtr();
				}
				resultFeatures = synthesizer->findMacros(Vartable::intToStr(fs->assignPred()));
			}
			break;

		}
#ifdef TRACE_EVAL
		std::cout << "####################### EVAL FEATURES DONE #######################" << std::endl;
		std::cout << "<div>" << std::endl;
		this->print(std::cout);
		std::cout << std::endl;
		if (resultFeatures)
		resultFeatures->print(std::cout);
		else
		std::cout << "NULL";
		std::cout << "</div>" << std::endl;
#endif
	return resultFeatures;
}

/* **************************************************
 *
 ************************************************** */
listPtr Statement::evalList(itemPtr item, bool replaceVariables) {
#ifdef TRACE_EVAL
	std::cout << "####################### EVAL LIST #######################" << std::endl;
	std::cout << "<div>" << std::endl;
	this->print(std::cout);
	std::cout << "</div>" << std::endl;
#endif
	listPtr resultList = List::NIL_LIST;
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
		case FOREACH:
		case IN:
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
		case SEARCH:
			FATAL_ERROR_STM;
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
				resultList = List::NIL_LIST;
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
		std::cout << "####################### EVAL LIST DONE #######################" << std::endl;
		std::cout << "<div>" << std::endl;
		this->print(std::cout);
		std::cout << std::endl;
		if (resultList)
		resultList->print(std::cout);
		else
		std::cout << "NULL";
		std::cout << "</div>" << std::endl;
#endif
	return resultList;
}

/* **************************************************
 *
 ************************************************** */
valuePtr Statement::evalValue(itemPtr item, Synthesizer *synthesizer, bool replaceVariables) {
#ifdef TRACE_EVAL
	std::cout << "####################### EVAL VALUE #######################" << std::endl;
	std::cout << "<div>" << std::endl;
	this->print(std::cout, 0);
	item->print(std::cout);
	std::cout << "</div>" << std::endl;
#endif
	valuePtr resultValue = valuePtr();
	featuresPtr resultFeatures = featuresPtr();
	listPtr resultList = listPtr();
	switch (this->op) {
		case NIL:
			resultValue = Value::NIL_VALUE;
			break;
		case NOT_NIL:
			resultValue = Value::TRUE_VALUE;
			break;
		case FINISHED:
			if (item->isCompleted())
				resultValue = Value::TRUE_VALUE;
			else
				resultValue = Value::NIL_VALUE;
			break;

		case PRINT:
		case PRINTLN:
		case IF:
		case THENELSE:
		case FOREACH:
		case IN:
		case AFF:
		case SUBSUME:
		case INSET:
		case GUARD:
		case STMS:
			FATAL_ERROR_STM;
			break;

			case DASH:
			{
				termsPtr t = item->getTerms(getFirst());
				// if (#i) false
				if (t->isOptional())
				resultValue = Value::NIL_VALUE;
				else {
					// if (#i)
					if (getSecond()==UINT_MAX) {
						resultValue = Value::TRUE_VALUE;
					}
					//if (#i:j)
					else {
						if (getSecond() == item->getIndexTerms()[getFirst()]) {
							resultValue = Value::TRUE_VALUE;
						}
						else {
							resultValue = Value::NIL_VALUE;
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
			else {
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

			case UNIF:
			{
				featuresPtr fs1 = lhs->evalFeatures(item, synthesizer, replaceVariables);
				if (!fs1) {
					resultValue = valuePtr();
					goto valueBuilt;
				}
				else {
					featuresPtr fs2=rhs->evalFeatures(item, synthesizer, replaceVariables);
					if (!fs2) {
						resultValue = valuePtr();
						goto valueBuilt;

					}
					else {
						fs1->subFlags(Flags::SEEN);
						fs2->subFlags(Flags::SEEN);
						resultFeatures = unif(fs1, fs2, item);
					}
				}
			}
			break;

			case SEARCH:
			case ATTEST:
			FATAL_ERROR_STM;
			goto valueBuilt;
			break;

			case LIST:
			resultList = evalList(item, replaceVariables);
			break;

			case FCT:
			switch (getFct()) {
				case NOP:
				break;
				case PLUS:
				{
					valuePtr v1=lhs->evalValue(item, synthesizer, replaceVariables);
					bool isv1astring = false;
					std::string v1str;
					if (v1) {
						isv1astring = true;
						if (v1->isVariable())
						v1str = v1->getBits()->toString();
						else if (v1->isIdentifier())
						v1str = Vartable::intToStr(v1->getIdentifier());
						else if (v1->isStr())
						v1str = v1->getStr();
						else
						isv1astring = false;
					}
					valuePtr v2=rhs->evalValue(item, synthesizer, replaceVariables);
					bool isv2astring = false;
					std::string v2str;
					if (v2) {
						isv2astring = true;
						if (v2->isVariable())
						v2str = v2->getBits()->toString();
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
					valuePtr v1=lhs->evalValue(item, synthesizer, replaceVariables);
					valuePtr v2=rhs->evalValue(item, synthesizer, replaceVariables);
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
					valuePtr v1=lhs->evalValue(item, synthesizer, replaceVariables);
					valuePtr v2=rhs->evalValue(item, synthesizer, replaceVariables);
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
					valuePtr v1=lhs->evalValue(item, synthesizer, replaceVariables);
					valuePtr v2=rhs->evalValue(item, synthesizer, replaceVariables);
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
					valuePtr v1=lhs->evalValue(item, synthesizer, replaceVariables);
					valuePtr v2=rhs->evalValue(item, synthesizer, replaceVariables);
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
					valuePtr v1=lhs->evalValue(item, synthesizer, replaceVariables);
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
					valuePtr v1=lhs->evalValue(item, synthesizer, replaceVariables);
					valuePtr v2=rhs->evalValue(item, synthesizer, replaceVariables);
					if ((!v1) || (!v2))
					resultValue = valuePtr();
					else if ((v1->isFalse()) || (v2->isFalse()))
					resultValue = Value::NIL_VALUE;
					else
					resultValue = Value::TRUE_VALUE;
					goto valueBuilt;
				}
				break;
				case OR:
				{
					valuePtr v1=lhs->evalValue(item, synthesizer, replaceVariables);
					valuePtr v2=rhs->evalValue(item, synthesizer, replaceVariables);
					if ((!v1) || (!v2))
					resultValue = valuePtr();
					else if ((v1->isFalse()) && (v2->isFalse()))
					resultValue = Value::NIL_VALUE;
					else
					resultValue = Value::TRUE_VALUE;
					goto valueBuilt;
				}
				break;
				case EQ:
				{
					valuePtr v1=lhs->evalValue(item, synthesizer, replaceVariables);
					valuePtr v2=rhs->evalValue(item, synthesizer, replaceVariables);
					if ((!v1) && (!v2))
					resultValue = Value::TRUE_VALUE;

					else if ((!v1) || (!v2))
					resultValue = valuePtr();

					else if ((v1->isAnonymous()) && (v2->isAnonymous()))
					resultValue = Value::TRUE_VALUE;

					else if ((v1->isAnonymous()) || (v2->isAnonymous()))
					resultValue = Value::NIL_VALUE;

					else if (v1->eq(v2))
					resultValue = Value::TRUE_VALUE;

					else
					resultValue = Value::NIL_VALUE;

					goto valueBuilt;
				}
				break;
				case DIFF:
				{
					valuePtr v1=lhs->evalValue(item, synthesizer, replaceVariables);
					valuePtr v2=rhs->evalValue(item, synthesizer, replaceVariables);
					if ((!v1) && (!v2)) {
						resultValue = Value::NIL_VALUE;
					}

					else if ((!v1) || (!v2)) {
						resultValue = Value::TRUE_VALUE;
					}

					else if ((v1->isAnonymous()) && (v2->isAnonymous()))
					resultValue = Value::NIL_VALUE;

					else if ((v1->isAnonymous()) || (v2->isAnonymous()))
					resultValue = Value::TRUE_VALUE;

					else if (v1->eq(v2)) {
						resultValue = Value::NIL_VALUE;
					}

					else {
						resultValue = Value::TRUE_VALUE;
					}
					goto valueBuilt;
				}
				break;
				case LT:
				{
					valuePtr v1=lhs->evalValue(item, synthesizer, replaceVariables);
					valuePtr v2=rhs->evalValue(item, synthesizer, replaceVariables);
					// si l'une est variable libre
					if ((!v1) || (!v2)) {
						resultValue = Value::NIL_VALUE;
					}
					else if (v1->lt(v2))
					resultValue = Value::TRUE_VALUE;
					else
					resultValue = Value::NIL_VALUE;
					goto valueBuilt;
				}
				break;
				case LE:
				{
					valuePtr v1=lhs->evalValue(item, synthesizer, replaceVariables);
					valuePtr v2=rhs->evalValue(item, synthesizer, replaceVariables);
					// si l'une est variable libre
					if ((!v1) || (!v2)) {
						resultValue = Value::NIL_VALUE;
					}
					else if ((v1->lt(v2)) || (v1->eq(v2)))
					resultValue = Value::TRUE_VALUE;
					else
					resultValue = Value::NIL_VALUE;
					goto valueBuilt;
				}
				break;
				case GT:
				{
					valuePtr v1=lhs->evalValue(item, synthesizer, replaceVariables);
					valuePtr v2=rhs->evalValue(item, synthesizer, replaceVariables);
					// si l'une est variable libre
					if ((!v1) || (!v2)) {
						resultValue = Value::NIL_VALUE;
					}
					else if (!(v1->lt(v2)) && (!(v1->eq(v2))))
					resultValue = Value::TRUE_VALUE;
					else
					resultValue = Value::NIL_VALUE;
					goto valueBuilt;
				}
				break;
				case GE:
				{
					valuePtr v1=lhs->evalValue(item, synthesizer, replaceVariables);
					valuePtr v2=rhs->evalValue(item, synthesizer, replaceVariables);
					// si l'une est variable libre
					if ((!v1) || (!v2)) {
						resultValue = Value::NIL_VALUE;
					}
					else if (!(v1->lt(v2)))
					resultValue = Value::TRUE_VALUE;
					else
					resultValue = Value::NIL_VALUE;
					goto valueBuilt;
				}
				break;
				case NOT:
				{
					valuePtr v1=lhs->evalValue(item, synthesizer, replaceVariables);
					if (!v1
							|| v1->isFalse())
					resultValue = Value::TRUE_VALUE;
					else
					resultValue = Value::NIL_VALUE;
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
			resultValue = Value::NIL_VALUE;
		else if (resultFeatures->isBottom())
			resultValue = Value::NIL_VALUE;
		else {
			if (replaceVariables && item->getEnvironment() && item->getEnvironment()->size() > 0) {
				bool effect = false;
				item->getEnvironment()->replaceVariables(resultFeatures, effect);
			}
			resultValue = Value::create(Value::FEATURES, resultFeatures);
		}
	}
	valueBuilt:
#ifdef TRACE_EVAL
	std::cout << "####################### EVAL VALUE DONE #######################" << std::endl;
	std::cout << "<div>" << std::endl;
	this->print(std::cout);
	std::cout << "<H3>";
	if (resultValue)
	resultValue->print(std::cout);
	else
	std::cout << "NULL";
	std::cout << "</H3>";
	std::cout << "</div>" << std::endl;
#endif
	return resultValue;
}

/* **************************************************
 *
 ************************************************** */
featuresPtr Statement::unif(featuresPtr fs1, featuresPtr fs2, itemPtr item) {
#ifdef TRACE_EVAL
	std::cout << "####################### EVAL UNIF #######################" << std::endl;
	std::cout << "<table border=\"1\"><tr><th>fs1</th><th>fs2</th><th>Environment</th></tr>";
	std::cout << "<tr><td>";
	if (fs1)
	fs1->print(std::cout);
	std::cout << "</td><td>";
	if (fs2)
	fs2->print(std::cout);
	std::cout << "</td><td>";
	if (item->getEnvironment())
	item->getEnvironment()->print(std::cout);
	std::cout << "</td></tr></table>";
#endif

	featuresPtr result = featuresPtr();

	if (fs1->isBottom() || fs2->isBottom()) {
		result = Features::BOTTOM;
		goto endUnif;
	}
	if (fs1->isNil() && fs2->isNil()) {
		result = Features::NIL;
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
	for (std::list<featurePtr>::const_iterator i1 = fs1->begin(); i1 != fs1->end(); ++i1) {

		if ((*i1)->getType() == Feature::PRED) {
			std::list<featurePtr>::const_iterator i2 = fs2->begin();
			while (i2 != fs2->end()) {
				if ((*i2)->getType() == Feature::PRED) {
					(*i2)->addFlags(Flags::SEEN);
					switch ((*i1)->getValue()->getType()) {

						case Value::IDENTIFIER: {
							switch ((*i2)->getValue()->getType()) {
								case Value::IDENTIFIER:
									if ((*i1)->getValue()->getIdentifier() != (*i2)->getValue()->getIdentifier()) {
										result = Features::BOTTOM;
										goto endUnif;
									}
									break;

								case Value::VARIABLE:
									result->add(Feature::create(Feature::PRED, bitsetPtr(), (*i1)->getValue()));
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
							result->add(Feature::create(Feature::PRED, bitsetPtr(), (*i2)->getValue()));
							break;

							case Value::ANONYMOUS:
							result->add(Feature::create(Feature::PRED, bitsetPtr(), (*i2)->getValue()));
							break;

							default:
							FATAL_ERROR_STM;
							break;
						}

					break;
				}
				++i2;
			}
			result->add(*i1);
		}

		else if ((*i1)->getType() == Feature::FORM) {
			std::list<featurePtr>::const_iterator i2 = fs2->begin();
			while (i2 != fs2->end()) {
				if ((*i2)->getType() == Feature::FORM) {

					(*i2)->addFlags(Flags::SEEN);
					if (!(*i1)->getValue()->isStr() || !(*i2)->getValue()->isStr())
						FATAL_ERROR_STM;

					if ((*i1)->getValue()->getStr() != (*i2)->getValue()->getStr()) {
						result = Features::BOTTOM;
						goto endUnif;
					}
					break;
				}

				++i2;
			}
			result->add(*i1);
		}

		else if ((*i1)->getType() == Feature::CONSTANT) {
			std::list<featurePtr>::const_iterator i2 = fs2->begin();
			while (i2 != fs2->end()) {
				if (((*i2)->getType() == Feature::CONSTANT) && (*(*i1)->getAttribute() & *(*i2)->getAttribute()).any()) {
					(*i2)->addFlags(Flags::SEEN);
					if ((!(*i1)->getValue()) || (!(*i2)->getValue())) {
						result = Features::BOTTOM;
						goto endUnif;
					}

					switch ((*i1)->getValue()->getType()) {

						case Value::STR:
							switch ((*i2)->getValue()->getType()) {
								case Value::STR:
									if ((*i1)->getValue()->getStr() != (*i2)->getValue()->getStr()) {
										result = Features::BOTTOM;
										goto endUnif;
									}
									result->add(Feature::create(Feature::CONSTANT, (*i1)->getAttribute(), (*i1)->getValue()));
									break;

								case Value::VARIABLE:
									FATAL_ERROR_STM;
									/*
									 result->add(new Feature((*i2)->getAttribute(), (*i1)->getValue(), Feature::CONSTANT));
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
											result = Features::BOTTOM;
											goto endUnif;
										}

										result->add(Feature::create(Feature::CONSTANT, (*i1)->getAttribute(), (*i1)->getValue()));
										break;
										case Value::VARIABLE:
										result->add(Feature::create(Feature::CONSTANT, (*i2)->getAttribute(), (*i1)->getValue()));
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
											result = Features::BOTTOM;
											goto endUnif;
										}

										result->add(Feature::create(Feature::CONSTANT, (*i1)->getAttribute(), Value::create(Value::DOUBLE, (*i1)->getValue()->getDouble())));
										break;
										case Value::VARIABLE:
										result->add(Feature::create(Feature::CONSTANT, (*i2)->getAttribute(), (*i1)->getValue()));
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
											result = Features::BOTTOM;
											goto endUnif;
										}

										result->add(Feature::create(Feature::CONSTANT, (*i1)->getAttribute(), Value::create(Value::IDENTIFIER, (*i1)->getValue()->getIdentifier())));
										break;
										case Value::VARIABLE:
										result->add(Feature::create(Feature::CONSTANT, (*i2)->getAttribute(), (*i1)->getValue()));
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
											result = Features::BOTTOM;
											goto endUnif;
										}

										result->add(Feature::create(Feature::CONSTANT, (*i1)->getAttribute(), Value::create(Value::CONSTANT, Bitset::create(*(*i1)->getValue()->getBits() & *(*i2)->getValue()->getBits()))));
										break;
										case Value::VARIABLE:
										result->add(Feature::create(Feature::CONSTANT, (*i2)->getAttribute(), (*i1)->getValue()));
										if (!item->getEnvironment())
										item->setEnvironment(Environment::create());
										item->getEnvironment()->add((*i2)->getValue()->getBits(), (*i1)->getValue());
										break;
										case Value::ANONYMOUS:
										result->add(Feature::create(Feature::CONSTANT, (*i2)->getAttribute(), (*i1)->getValue()));
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
								result->add(Feature::create(Feature::CONSTANT, (*i1)->getAttribute(), (*i2)->getValue()));
								break;

								case Value::ANONYMOUS:
								result->add(Feature::create(Feature::CONSTANT, (*i1)->getAttribute(), (*i2)->getValue()));
								break;

								case Value::FEATURES:
								{
									featuresPtr features = unif((*i1)->getValue()->getFeatures(), (*i2)->getValue()->getFeatures(), item);
									if (features->isBottom()) {
										result = features;
										goto endUnif;
									}
									else
									result->add(Feature::create(Feature::CONSTANT, (*i1)->getAttribute(), Value::create(Value::FEATURES, features)));
								}
								break;

								case Value::LIST:
								result->add(Feature::create(Feature::CONSTANT, (*i1)->getAttribute(), (*i1)->getValue()));
								break;
							}

					break;
				}
				++i2;
			}
			if (i2 == fs2->end()) {
				result->add(*i1);
			}
		}
	}
	for (std::list<featurePtr>::const_iterator i2 = fs2->begin(); i2 != fs2->end(); ++i2) {
		if ((*i2)->isUnsetFlags(Flags::SEEN))
			result->add(*i2);
	}

	for (std::list<featurePtr>::const_iterator i1 = fs1->begin(); i1 != fs1->end(); ++i1) {
		(*i1)->subFlags(Flags::SEEN);
	}
	for (std::list<featurePtr>::const_iterator i2 = fs2->begin(); i2 != fs2->end(); ++i2) {
		(*i2)->subFlags(Flags::SEEN);
	}

	endUnif:

#ifdef TRACE_EVAL
	std::cout << "####################### EVAL UNIF DONE #######################" << std::endl;
	std::cout << "<table border=\"1\"><tr><th>R&eacute;sultat</th><th>Environment</th></tr>";
	std::cout << "<tr><td>";
	if (result)
	result->print(std::cout);
	std::cout << "</td><td>";
	if (item->getEnvironment())
	item->getEnvironment()->print(std::cout);
	std::cout << "</td></tr></table>";
#endif
	return result;
}

/* ************************************************************
 * ↓1 = … 
 ************************************************************ */
void Statement::buildInheritedSonFeatures(itemPtr item, class Synthesizer *synthesizer) {
	/***
	 std::cerr << "buildInheritedSonFeatures: ";
	 print(std::cerr);
	 std::cerr << std::endl;
	 ***/
	featuresPtr features = rhs->evalFeatures(item, synthesizer, true);
	if (features->isNil())
		addFlags(Flags::BOTTOM);
	else
		item->getInheritedSonFeatures()->add(lhs->getFirst(), features);
}

/* ************************************************************
 * ⇑ = …
 ************************************************************ */
void Statement::buildSynthesizedFeatures(itemPtr item, Synthesizer *synthesizer) {
	if (!item->getSynthesizedFeatures()->isNil()) {
		this->print(std::cerr);
		FATAL_ERROR_STM;
	}
	featuresPtr features = rhs->evalFeatures(item, synthesizer, true);
	if (features->isNil())
		addFlags(Flags::BOTTOM);
	else {
		item->setSynthesizedFeatures(features);
	}
}

/* ************************************************************
 * [ … $X … ] ⊂ ⇓1;
 * $X = ⇓1;
 ************************************************************ */
void Statement::buildEnvironmentWithSynthesize(itemPtr item, Synthesizer *synthesizer) {
	switch (this->op) {
		case AFF: {
			// $X = ⇓1;
			environmentPtr environment;
			if (item->getEnvironment()) {
				environment = item->getEnvironment();
			}
			else {
				environment = Environment::create();
				item->setEnvironment(environment);
			}
			featuresPtr sonSynth = rhs->evalFeatures(item, synthesizer, true);
			if (sonSynth) {
				environment->add(lhs->getBits(), Value::create(Value::FEATURES, sonSynth));
			}
			else
				FATAL_ERROR_STM;
		}
			break;

		case SUBSUME: {
			// [ … $X … ] ⊂ ⇓1;
			featuresPtr left = lhs->evalFeatures(item, synthesizer, false);
			if (!left) {
				WARNING_STM
				;
			}
			else {
				environmentPtr environment;
				if (item->getEnvironment())
					environment = item->getEnvironment();
				else {
					environment = Environment::create();
					item->setEnvironment(environment);
				}
				featuresPtr sonSynth = rhs->evalFeatures(item, synthesizer, true);
				if (sonSynth) {
					if (!left->buildEnvironment(environment, sonSynth, true, true)) {
						addFlags(Flags::BOTTOM);
					}
				}
				else {
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
 * [ … $X … ] ⊂ ↑;
 * $X = ↑;
 ************************************************************ */
void Statement::buildEnvironmentWithInherited(itemPtr item, Synthesizer *synthesizer) {
	/***
	 std::cerr << "<DIV>buildEnvironmentWithInherited ";
	 this->print(std::cerr, "", TRUE_ROOT);
	 std::cerr << "</DIV>";
	 ***/
	switch (this->op) {
		case AFF: {
			// $X = ↑;
			featuresPtr right = rhs->evalFeatures(item, synthesizer, true);
			if (!right) {
				WARNING_STM
				;
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

		case SUBSUME: {
			featuresPtr left = lhs->evalFeatures(item, synthesizer, false);
			if (!left) {
				WARNING_STM
				;
			}
			else {
				featuresPtr right = rhs->evalFeatures(item, synthesizer, true);
				if (!right) {
					WARNING_STM
					;
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
					if (!left->buildEnvironment(environment, right, true, true)) {
						addFlags(Flags::BOTTOM);
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
	 * [ … $X … ] ⊂ Y;
	 * [ … $X … ] ⊂ [ … ];
	 * $X = a;
	 * $X = [ … ];
	 * $X = < … >;
	 * $X = sort $X with a;
	 * $X = reverse X
	 * $X = <expr>
	 * < … > = < … >
	 * < … > = sort $X with a;
	 * < … > = reverse $X;
	 * < … > = $X;
	 ************************************************************ */
void Statement::buildEnvironmentWithValue(itemPtr item, Synthesizer *synthesizer) {
	/***
	 std::cerr << "<DIV>buildEnvironmentWithValue</DIV>";
	 std::cerr << "<DIV>";
	 this->print(std::cerr, 0);
	 std::cerr << "</DIV>";
	 ***/
	switch (this->op) {
		case AFF:
			// 	 $X = a;
			// 	 $X = $Y;
			// 	 $X = … ∪ … ;
			// 	 $X = [ … ];
			// 	 $X = <expr>;
			// 	 $X = < … >
			// 	 $X = sort $X with a;
			// 	 $X = reverse $X;

			if (lhs->isVariable()) {
				valuePtr right = rhs->evalValue(item, synthesizer, true);
				if (!right) {
					this->print(std::cerr, 0);
					WARNING_STM
					;
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

			// 	 < … > = $X;
			// 	 < … > = ( … )
			// 	 < … > = sort $X with a;
			// 	 < … > = reverse $X;
			else if (lhs->isList()) {
				listPtr right = rhs->evalList(item, true);
				if (!right) {
					FATAL_ERROR_STM;
					WARNING_STM;
				}
				else {
					if (right->isNil()) {
						FATAL_ERROR_STM;
						addFlags(Flags::BOTTOM);
					}
					listPtr left = lhs->evalList(item, false);
					if (!left) {
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
						if (!left->buildEnvironment(environment, right, true, true)) {
							addFlags(Flags::BOTTOM);
						}
					}
				}
			}

			else
			FATAL_ERROR_STM;
			break;

			case SUBSUME:
			{
				featuresPtr right = rhs->evalFeatures(item, synthesizer, true);
				if (!right) {
					WARNING_STM;
				}
				else {
					if (right->isNil())
					{} // empty
					featuresPtr left = lhs->evalFeatures(item, synthesizer, false);
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
							addFlags(Flags::BOTTOM);
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
void Statement::stmAttest(itemPtr item, class Synthesizer *synthesizer) {
	/***
	 std::cerr << "<DIV>*** attest</DIV>";
	 std::cerr << "<DIV>";
	 this->print(std::cerr);
	 std::cerr << "</DIV>";
	 ***/
	switch (this->op) {
		case ATTEST: {
			valuePtr res = lhs->evalValue(item, synthesizer, true);
			if ((!res) || (res == Value::NIL_VALUE) || (res == Value::ANONYMOUS_VALUE) || ((res->getType() == Value::FEATURES) && (res->getFeatures()->isBottom()))) {
				addFlags(Flags::BOTTOM);
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
void Statement::stmGuard(itemPtr item, bool trace) {
	/***
	 CERR_LINE;
	 std::cerr << "<DIV>guard ";
	 item->print(std::cerr);
	 print(std::cerr);
	 std::cerr << "</DIV>";
	 ***/
	if (isSetFlags(Flags::DISABLED | Flags::SEEN)) {
		FATAL_ERROR_STM;
	}
	else {
		featuresPtr features = getFeatures();
		if (!features) {
			FATAL_ERROR_STM;
		}
		environmentPtr environment;
		if (item->getEnvironment())
		environment = item->getEnvironment();
		else {
			environment = Environment::create();
			item->setEnvironment(environment);
		}
		featuresPtr rhs = item->getInheritedFeatures();
		if (!features->buildEnvironment(environment, rhs, false, true))
		addFlags(Flags::BOTTOM);
		else {
			if (trace) {
				std::cerr << "*** Guard clause checked " << item->getFilename() << '(' << item->getLineno() << ')' << std::endl;
			}
		}
		if (item->getEnvironment()->size()==0) {
			item->getEnvironment().reset();
			item->setEnvironment(environmentPtr());
		}
	}
	/***
	 std::cerr << "<DIV>guard done";
	 item->print(std::cerr);
	 std::cerr << "</DIV>";
	 ***/
}

/* ************************************************************
 * foreach
 ************************************************************ */
void Statement::stmForeach(itemPtr item, Synthesizer *synthesizer, bool trace) {
	/***
	 std::cerr << "<DIV>foreach";
	 item->print(std::cerr);
	 print(std::cerr);
	 std::cerr << "</DIV>";
	 ***/

	statementPtr variable = getLhs();
	valuePtr value = getRhs()->getLhs()->evalValue(item, synthesizer, true);
	statementPtr body = getRhs()->getRhs();
	if (!value->isList())
		FATAL_ERROR_MSG_STM("foreach does'nt apply a list");
	listPtr list = value->getList();
	list->apply(item, synthesizer, trace, variable, body);

	/***
	 std::cerr << "<DIV>foreach done";
	 item->print(std::cerr);
	 std::cerr << "</DIV>";
	 ***/
}

/* ************************************************************
 * if
 ************************************************************ */
void Statement::stmIf(itemPtr item, Synthesizer *synthesizer, bool trace) {
	statementPtr lhs = getRhs()->getLhs();
	statementPtr rhs = getRhs()->getRhs();

	unsigned int resif = 0;    // 0:none 1:then 2:else
	if (lhs->isSetFlags(Flags::CHOOSEN))
		resif = 1;
	else if (rhs && rhs->isSetFlags(Flags::CHOOSEN))
		resif = 2;
	else {
		valuePtr res = getLhs()->evalValue(item, synthesizer, true);
		if (!res)
			resif = 0;
		else if (res == Value::NIL_VALUE || res == Value::ANONYMOUS_VALUE) {
			resif = 2;
			lhs->addFlags(Flags::REJECTED);
			if (rhs)
				rhs->addFlags(Flags::CHOOSEN);
		}
		else {
			resif = 1;
			lhs->addFlags(Flags::CHOOSEN);
			if (rhs)
				rhs->addFlags(Flags::REJECTED);
		}
	}
	//bool localResult = true;
	switch (resif) {
		case 1:
			lhs->apply(item, synthesizer, trace);
			if (lhs->isSetFlags(Flags::BOTTOM)) {
				this->addFlags(Flags::BOTTOM);
			}
			if (lhs->isSetFlags(Flags::SEEN))
				this->addFlags(Flags::SEEN);
			break;
		case 2:
			if (rhs) {
				rhs->apply(item, synthesizer, trace);
				if (rhs->isSetFlags(Flags::BOTTOM))
					this->addFlags(Flags::BOTTOM);
				if (rhs->isSetFlags(Flags::SEEN))
					this->addFlags(Flags::SEEN);
			}
			else {
				this->addFlags(Flags::SEEN);
			}
			break;
	}
}

/* ************************************************************
 * print
 ************************************************************ */
void Statement::stmPrint(itemPtr item, class Synthesizer *synthesizer) {
	addFlags(Flags::SEEN);
	if (lhs->isStr()) {
		std::cout << lhs->getStr();
	}
	else {
		valuePtr value = lhs->evalValue(item, synthesizer, true);
		value->print(std::cout);
	}
}

/* ************************************************************
 * println
 ************************************************************ */
void Statement::stmPrintln(itemPtr item, class Synthesizer *synthesizer) {
	stmPrint(item, synthesizer);
	std::cout << std::endl;
}

/* **************************************************
 *
 ************************************************** */
void Statement::renameVariables(unsigned int i) {
	switch (this->op) {
		case VARIABLE: {
			//ostringstream oss;
			//oss << getBits()->toString() << "_" << i;
			//string str = oss.str();
			std::string str = getBits()->toString() + "_" + std::to_string(i);
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
		case SEARCH:
		case FINISHED:
			break;
		case AFF:
		case SUBSUME:
		case INSET:
		case FCT:
		case UNIF:
		case ATTEST:
		case PRINT:
		case PRINTLN:
		case IF:
		case THENELSE:
		case IN:
			if (lhs)
				lhs->renameVariables(i);
			if (rhs)
				rhs->renameVariables(i);
			break;
		case FOREACH:
			//if (rhs)
			//rhs->renameVariables(i);
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
void Statement::enable(statementPtr root, itemPtr item, bool &effect, bool on) {
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

		case FOREACH:
			//lhs->enable(shared_from_this(), item, effect, on);
			rhs->enable(rhs, item, effect, on);
			break;

		case IN:
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
			else {
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

		case PRINT:
		case PRINTLN:
			lhs->enable(root, item, effect, on);
			break;

		case ATTEST:
			lhs->enable(root, item, effect, on);
			break;

		case DASH:
			// if (#1)   NP -> [det] N { if (#1) ↓1 = ↑ ∪ ⇓2 ∪ [qual:$Qual, part:$Part]; else [detNum:NIL, det:no]; }
			// if (#2)   VP -> VP [NP] {   if (#2) { ↓1 = $Rest; ↓2 = [pcas:$pcas, $PObj];} else { attest ($Pred == _pro); ↓1 = [prep_objCl:$PObj, $Rest];} }
			if (on) {
				if (item->getTerms(getFirst())
						&& ((!item->getTerms(getFirst())->isOptional() && item->getTerms(getFirst())->size() == 1)
								|| (item->getTerms(getFirst())->isOptional() && item->getForestIdentifiers()[getFirst()]))) {
				}
				else {
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
			if (on) {
				if ((!item->getEnvironment()) || !(item->getEnvironment()->find(getBits()))) {
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

		case SEARCH:
			if (lhs)
				lhs->enable(root, item, effect, on);
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
void Statement::apply(itemPtr item, Synthesizer *synthesizer, bool trace) {
#ifdef TRACE_APPLY
	if (synthesizer->getTraceAction()) {
		std::cout << "<H3>####################### APPLY #######################</H3>" << std::endl;
		print(std::cout);
		std::cout << std::endl;
	}
#endif

	if (isSetFlags(Flags::SEEN | Flags::DISABLED | Flags::BOTTOM)) {
		FATAL_ERROR
		;
		return;
	}

	// if
	if (isIf()) {
		stmIf(item, synthesizer, trace);
	}

	// foreach $i in $list
	else if (isForeach()) {
		stmForeach(item, synthesizer, trace);
		addFlags(Flags::SEEN);
	}

	// […]
	else if (isGuard()) {
		stmGuard(item, trace);
		addFlags(Flags::SEEN);
	}

	// ↓1 = …
	else if ((isAff()) && (getLhs()->isDown())) {
		buildInheritedSonFeatures(item, synthesizer);
		addFlags(Flags::SEEN);
	}

	// [ … $X … ] ⊂ ⇓1
	// $X = ⇓1
	else if (((isSubsume()) && (getRhs()->isDown2()) && (getLhs()->isFeatures())) || ((isAff()) && (getRhs()->isDown2()) && (getLhs()->isVariable()))) {
		buildEnvironmentWithSynthesize(item, synthesizer);
		addFlags(Flags::SEEN);
	}

	// [ … $X … ] ⊂ ↑
	// $X = ↑
	else if (((isSubsume()) && (getRhs()->isUp()) && (getLhs()->isFeatures())) || ((isAff()) && (getRhs()->isUp()) && (getLhs()->isVariable()))) {
		buildEnvironmentWithInherited(item, synthesizer);
		addFlags(Flags::SEEN);
	}

	// $X = a;
	// $X = Y;
	// $X = … ∪ … ;
	// $X = [ … ];
	// $X = <expr>;
	// $X = < … >
	// $X = sort Y with a;
	// $X = reverse Y;
	// $X = combination Y;
	// $X = search Y;
	//
	// < … > = $X;
	// < … > = < … >
	// < … > = sort $X with a;
	// < … > = reverse $X;
	//
	// [ … $X … ] ⊂ Y
	// [ … $X … ] ⊂ [ … ]
	// [ … $X … ] ⊂ search Y
	else if (((isAff()) && (getLhs()->isVariable())
			&& ((getRhs()->isConstant()) || (getRhs()->isVariable()) || (getRhs()->isUnif()) || (getRhs()->isFeatures()) || (getRhs()->isDouble()) || (getRhs()->isFct())
					|| (getRhs()->isList()) || (getRhs()->isSearch()))) || ((isAff()) && (getLhs()->isList()) && ((getRhs()->isVariable()) || (getRhs()->isList())))
			|| ((isSubsume()) && (getLhs()->isFeatures()) && ((getRhs()->isVariable()) || (getRhs()->isFeatures()) || (getRhs()->isSearch())))) {
		buildEnvironmentWithValue(item, synthesizer);
		//effect = true;
		addFlags(Flags::SEEN);
	}

	// ⇑ = …
	else if ((isAff()) && (getLhs()->isUp2())) {
		buildSynthesizedFeatures(item, synthesizer);
		addFlags(Flags::SEEN);
	}

	// attest …
	else if (isAttest()) {
		stmAttest(item, synthesizer);
		addFlags(Flags::SEEN);
	}

	// print
	else if (isPrint()) {
		stmPrint(item, synthesizer);
		addFlags(Flags::SEEN);
	}

	// println
	else if (isPrintln()) {
		stmPrintln(item, synthesizer);
		addFlags(Flags::SEEN);
	}

	// statements
	else if (isStms()) {
		this->statements->apply(item, synthesizer, trace);
		if (this->statements->isSetFlags(Flags::BOTTOM))
			this->addFlags(Flags::BOTTOM);
		if (this->statements->isSetFlags(Flags::SEEN))
			this->addFlags(Flags::SEEN);
	}

	// else error
	else {
		std::cerr << "Not yet implemented" << std::endl;
		this->print(std::cerr);
		FATAL_ERROR_STM;
	}

#ifdef TRACE_APPLY
	if (synthesizer->getTraceAction()) {
		std::cout << "<H3>####################### APPLY DONE #######################</H3>" << std::endl;
		item->print(std::cout);
		std::cout << std::endl;
	}
#endif

}

/* **************************************************
 *
 ************************************************** */
void Statement::lookingForAssignedInheritedSonFeatures(std::vector<bool> &assignedInheritedSonFeatures) {
	switch (this->op) {
		case AFF:
			// ↓1 = …
			if ((this->isAff()) && (this->getLhs()->isDown()))
				assignedInheritedSonFeatures[this->getLhs()->getFirst()] = true;
			break;

		case IF: {
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
const bool Statement::findVariable(bitsetPtr variable) {
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

		case FOREACH:
			if (rhs->findVariable(variable))
				return true;
			break;

		case IN:
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
			if (rhs->findVariable(variable))
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
			if (lhs->findVariable(variable))
				return true;
			break;

		case VARIABLE:
			if (getBits() == variable)
				return true;
			break;

		case LIST:
			if (getList()->findVariable(variable))
				return true;
			break;

		case FEATURES:
			if (getFeatures()->findVariable(variable))
				return true;
			break;

		case DOWN:
		case SEARCH:
			FATAL_ERROR
			;
			break;

		default:
			break;
	}
	return false;
}

