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

#include <sstream>
#include <utility>
#include "value.hpp"
#include "environment.hpp"
#include "list.hpp"
#include "features.hpp"
#include "statement.hpp"
#include "statements.hpp"
#include "messages.hpp"
#include "item.hpp"
#include "shared_ptr.hpp"
#include "synthesizer.hpp"
#include "vartable.hpp"

valuePtr Value::TRUE_VALUE = Value::create(Value::TRUE);
valuePtr Value::NIL_VALUE = Value::create(Value::NIL);
valuePtr Value::ANONYMOUS_VALUE = Value::create(Value::ANONYMOUS);

/* **************************************************
 *
 ************************************************** */
Value::Value(Value::Type const type, const std::string &str) {
    this->type = type;
    this->code = 0;
    this->number = 0;
    //unsigned int found = 0;
    if (type == CODE) {
        this->code = Vartable::identifierToCode(str);
    } else if (type == STR) {
        this->str = str;
    }
    NEW
}

/* **************************************************
 *
 ************************************************** */
Value::Value(Value::Type const type, unsigned int code, double number, bitsetPtr _bits, featuresPtr _features,
             listPtr _list) {
    this->type = type;
    this->code = code;
    this->number = number;
    this->bits = std::move(_bits);
    this->features = std::move(_features);
    this->list = std::move(_list);
    NEW
}

/* **************************************************
 *
 ************************************************** */
Value::~Value() {
    DELETE
    if (bits)
        bits.reset();
    if (features)
        features.reset();
    if (list)
        list.reset();
}

/* **************************************************
 *
 ************************************************** */
valuePtr Value::create(const enum Type type) {
    return valuePtr(new Value(type));
}

/* **************************************************
 *
 ************************************************** */
valuePtr Value::create(const enum Type type, double number) {
    return valuePtr(new Value(type, 0, number));
}

/* **************************************************
 *
 ************************************************** */
valuePtr Value::create(const enum Type type, unsigned int integer) {
    return valuePtr(new Value(type, integer));
}

/* **************************************************
 *
 ************************************************** */
valuePtr Value::create(const enum Type type, const std::string &str) {
    return valuePtr(new Value(type, str));
}

/* **************************************************
 *
 ************************************************** */
valuePtr Value::create(const enum Type type, bitsetPtr bits) {
    return valuePtr(new Value(type, 0, 0, std::move(bits)));
}

/* **************************************************
 *
 ************************************************** */
valuePtr Value::create(const enum Type type, featuresPtr features) {
    return valuePtr(new Value(type, 0, 0, bitsetPtr(), std::move(features)));
}

/* **************************************************
 *
 ************************************************** */
valuePtr Value::create(const enum Type type, listPtr lst) {
    return valuePtr(new Value(type, 0, 0, bitsetPtr(), featuresPtr(), std::move(lst)));
}

/* **************************************************
 *
 ************************************************** */
Value::Type Value::getType() const {
    return type;
}

/* **************************************************
 *
 ************************************************** */
bitsetPtr Value::getBits() const {
    return bits;
}

/* **************************************************
 *
 ************************************************** */
unsigned int Value::getCode() const {
    return code;
}

/* **************************************************
 *
 ************************************************** */
featuresPtr Value::getFeatures() const {
    return features;
}

/* **************************************************
 *
 ************************************************** */
double Value::getNumber() const {
    return number;
}

/* **************************************************
 *
 ************************************************** */
std::string Value::getStr() const {
    return str;
}

/* **************************************************
 *
 ************************************************** */
listPtr Value::getList() const {
    return list;
}

/* **************************************************
 *
 ************************************************** */
bool Value::isNil() const {
    return (type == Value::NIL);
}

/* **************************************************
 *
 ************************************************** */
/*bool Value::isFalse() const {
    return ((type == Value::NIL) || (type == Value::ANONYMOUS));
}
*/
/* **************************************************
 *
 ************************************************** */
bool Value::isTrue() const {
    return (type == Value::TRUE);
}

/* **************************************************
 *
 ************************************************** */
bool Value::isAnonymous() const {
    return (type == Value::ANONYMOUS);
}

/* **************************************************
 *
 ************************************************** */
bool Value::isNumber() const {
    return getType() == NUMBER;
}

/* **************************************************
 *
 ************************************************** */
bool Value::isStr() const {
    return getType() == STR;
}

/* **************************************************
 *
 ************************************************** */
bool Value::isFeatures() const {
    return getType() == FEATURES;
}

/* **************************************************
 *
 ************************************************** */
bool Value::isConstant() const {
    return getType() == CONSTANT;
}

/* **************************************************
 *
 ************************************************** */
bool Value::isVariable() const {
    return getType() == VARIABLE;
}

/* **************************************************
 *
 ************************************************** */
bool Value::isIdentifier() const {
    return getType() == CODE;
}

/* **************************************************
 *
 ************************************************** */
bool Value::isList() const {
    return getType() == LIST;
}

/* **************************************************
 *
 ************************************************** */
void Value::print(std::ostream &outStream) const {
    switch (type) {
        case NIL:
            outStream << "NIL";
            break;
        case TRUE:
            outStream << "TRUE";
            break;
        case CONSTANT:
            outStream << bits->toString();
            break;
        case VARIABLE:
            outStream << bits->toString();
            break;
        case ANONYMOUS:
            outStream << '_';
            break;
        case CODE:
            outStream << Vartable::codeToIdentifier(code);
            break;
        case NUMBER:
            outStream << number;
            break;
        case STR:
            outStream << "&quot;" << getStr() << "&quot;";
            break;
        case FEATURES:
            getFeatures()->print(outStream);
            break;
        case LIST:
            getList()->flatPrint(outStream, true);
            break;
    }
}

/* **************************************************
 *
 ************************************************** */
void Value::flatPrint(std::ostream &outStream) const {
    switch (type) {
        case NIL:
            outStream << "NIL";
            break;
        case TRUE:
            outStream << "TRUE";
            break;
        case CONSTANT:
            outStream << bits->toString();
            break;
        case VARIABLE:
            outStream << bits->toString();
            break;
        case ANONYMOUS:
            outStream << '_';
            break;
        case CODE:
            outStream << Vartable::codeToIdentifier(code);
            break;
        case NUMBER:
            outStream << number;
            break;
        case STR:
            outStream << '"' << getStr() << '"';
            break;
        case FEATURES:
            getFeatures()->flatPrint(outStream);
            break;
        case LIST:
            getList()->flatPrint(outStream, true);
            break;
    }
}

/* **************************************************
 *
 ************************************************** */
void Value::makeSerialString() {
    switch (type) {
        case NIL:
            serialString = 'N';
            break;
        case TRUE:
            serialString = 'T';
            break;
        case CONSTANT:
            serialString = bits->peekSerialString();
            break;
        case VARIABLE:
            serialString = '$' + bits->peekSerialString();
            break;
        case ANONYMOUS:
            serialString = '_';
            break;
        case CODE:
            serialString = std::to_string(code);
            break;
        case NUMBER:
            serialString = number;
            break;
        case STR:
            serialString = str;
            break;
        case FEATURES:
            serialString = getFeatures()->peekSerialString();
            break;
        case LIST:
            serialString = getList()->peekSerialString();
            break;
    }
}

#ifdef OUTPUT_XML
/* **************************************************
 *
 *************************************************!* */
void
Value::toXML(xmlNodePtr nodeRoot) const
{
  xmlNodePtr v = xmlNewChild(nodeRoot, NULL, (const xmlChar*)"VAL", NULL);
  switch(type) {
  case NIL:
    xmlSetProp(v, (xmlChar*)"type", (const xmlChar*)"nil");
    bits->toXML(v);
    break;
  case TRUE:
    xmlSetProp(v, (xmlChar*)"type", (const xmlChar*)"true");
    bits->toXML(v);
    break;
  case CONSTANT:
    xmlSetProp(v, (xmlChar*)"type", (const xmlChar*)"constant");
    bits->toXML(v);
    break;
  case VARIABLE:
    xmlSetProp(v, (xmlChar*)"type", (const xmlChar*)"variable");
    bits->toXML(v);
    break;
  case ANONYMOUS:
    xmlSetProp(v, (xmlChar*)"type", (const xmlChar*)"anonymous");
    bits->toXML(v);
    break;
  case CODE:
    xmlSetProp(v, (xmlChar*)"type", (const xmlChar*)"identifier");
    xmlNewChild(v, NULL, (const xmlChar*)"VAL", (const xmlChar*)Vartable::codeToIdentifier(getCode()).c_str());
    break;
  case NUMBER:
    xmlSetProp(v, (xmlChar*)"type", (const xmlChar*)"double");
    xmlSetProp(v, (xmlChar*)"value",(const xmlChar*)std::to_string(number).c_str());
    break;
  case STR:
    xmlSetProp(v, (xmlChar*)"type", (const xmlChar*)"str");
    xmlNewChild(v, NULL, (const xmlChar*)"VAL", (const xmlChar*)getStr().c_str());
    break;
  case FEATURES:
    xmlSetProp(v, (xmlChar*)"type", (const xmlChar*)"fs");
    getFeatures()->toXML(v);
    break;
  case LIST:
    xmlSetProp(v, (xmlChar*)"type", (const xmlChar*)"list");
    getList()->toXML(v);
    break;

  }
}
#endif

/* **************************************************
 *
 ************************************************** */
valuePtr Value::clone() {
    valuePtr result = valuePtr();
    switch (type) {
        case NIL:
        case TRUE:
        case CONSTANT:
        case CODE:
        case STR:
        case NUMBER:
        case ANONYMOUS:
            result = shared_from_this();
            break;
        case FEATURES:
            result = Value::create(Value::FEATURES, getFeatures()->clone());
            break;
        case LIST:
            result = Value::create(Value::LIST, getList()->clone());
            break;
        case VARIABLE:
            result = Value::create(VARIABLE, bits);
            break;
    }
    return result;
}

/* ************************************************************
 *
 ************************************************************ */
bool Value::buildEnvironment(const environmentPtr &environment, const valuePtr &value, bool acceptToFilterNULLVariables,
                             bool root) {
    /***
    CERR_LINE;
    std::cerr << "<H4>Value::buildEnvironment</H4>" << std::endl;
    std::cerr << "<table border=\"1\"><tr><th>this</th><th>value</th><th>Environment</th></tr>";
    std::cerr << "<tr><td>";
    this->print(std::cerr);
    std::cerr << "</td><td>";
    if (value)
      value->print(std::cerr);
    else
      std::cerr << "NULL";
    std::cerr << "</td><td>";
    environment->print(std::cerr);
    std::cerr << "</td></tr></table>";
    ***/

    bool ret = true;
    switch (type) {

        case TRUE:
            if (value->type == VARIABLE) {
                environment->add(value->bits, shared_from_this());
            } else if (value->type == TRUE) {
            } else if (value->type == ANONYMOUS) {
            } else {
                ret = false;
            }
            break;

        case NIL:
            if (value->type == VARIABLE) {
                environment->add(value->bits, shared_from_this());
            } else if (value->type == NIL) {
            } else if (value->type == ANONYMOUS) {
            } else {
                ret = false;
            }
            break;

        case FEATURES:
            if (value->type == VARIABLE) {
                environment->add(value->bits, shared_from_this());
            } else if (value->type == FEATURES) {
                if (!this->getFeatures()->buildEnvironment(environment, value->getFeatures(),
                                                           acceptToFilterNULLVariables/*, root*/))
                    ret = false;
            } else if (value->type == ANONYMOUS) {
                if (!this->getFeatures()->buildEnvironment(environment, Features::create(),
                                                           acceptToFilterNULLVariables/*,
                                                           root*/))
                    ret = false;
            } else if (value->type == TRUE) {
                environment->add(value->bits, shared_from_this());
            } else {
                ret = false;
            }
            break;

        case CONSTANT:
            if (value->type == VARIABLE) {
                environment->add(value->bits, shared_from_this());
            } else if (value->type == CONSTANT) {
                if ((*bits & *value->bits).none())
                    ret = false;
            } else if (value->type == CODE) {
                if (bits->toString() != Vartable::codeToIdentifier(value->getCode()))
                    ret = false;
            } else if (value->type == ANONYMOUS) {
            } else {
                ret = false;
            }
            break;

        case CODE:
            if (value->type == VARIABLE) {
                environment->add(value->bits, shared_from_this());
            } else if (value->type == CONSTANT) {
                if (Vartable::codeToIdentifier(code) != value->bits->toString())
                    ret = false;
            } else if (value->type == CODE) {
                if (code != value->getCode())
                    ret = false;
            } else if (value->type == ANONYMOUS) {
            } else {
                ret = false;
            }
            break;

        case NUMBER:
            if (value->type == VARIABLE) {
                environment->add(value->bits, shared_from_this());
            } else if (value->type == NUMBER) {
                if (number != value->number) {
                    ret = false;
                }
            } else if (value->type == ANONYMOUS) {
            } else {
                ret = false;
            }
            break;

        case STR:
            if (value->type == VARIABLE) {
                environment->add(value->bits, shared_from_this());
            } else if (value->type == STR) {
                if (getStr() != value->getStr()) {
                    ret = false;
                }
            } else if (value->type == ANONYMOUS) {
            } else {
                ret = false;
            }
            break;

        case LIST:
            if (value->type == LIST) {
                if (!this->getList()->buildEnvironment(environment, value->getList(),
                                                       acceptToFilterNULLVariables,
                                                       root))
                    ret = false;
            } else if (value->type == VARIABLE) {
                environment->add(value->bits, shared_from_this());
            } else if (value->type == ANONYMOUS) {
            } else {
                ret = false;
            }
            break;

        case VARIABLE:
            if (!value) {
                environment->add(this->bits, NIL_VALUE);
            } else {
                environment->add(this->bits, value);
            }
            break;

        case ANONYMOUS:
            break;
    }
    /***
         std::cerr << "<H4>Result Value::buildEnvironment</H4>" << std::endl;
         std::cerr << "<table border=\"1\"><tr><th>R&eacute;sultat</th><th>Environment</th></tr>";
         std::cerr << "<tr><td>" << (ret?"TRUE":"FALSE") << "</td><td>";
         environment->print(std::cerr);
         std::cerr << "</td></tr></table>";
    ***/
    return ret;
}

/* ************************************************************
 * this < o
 ************************************************************ */
bool Value::subsumes(const valuePtr &o, const environmentPtr &environment) {
    bool ret = true;
    /***
        std::cerr << "<DIV>";
        std::cerr << "Value::subsumes (" << this << ")";
        std::cerr << "<TABLE><TR>";
        std::cerr << "<TD>";
        this->print(std::cerr);
        std::cerr << "</TD>&lt;<TD>";
        o->print(std::cerr);
        std::cerr << "</TD>";
        std::cerr << "</TR></TABLE>";
        std::cerr << "</DIV>";
    ***/

    // X < …
    if (type == VARIABLE) {
        environment->add(bits, o);
    }

        // … < X
    else if (o->type == VARIABLE) {
        //FATAL_ERROR;
        environment->add(o->bits, shared_from_this());
        //FATAL_ERROR;

    }

        // NIL < NIL
    else if (isNil() && o->isNil()) {

    }

        // NIL < …
        // … < NIL
    else if (isNil() || o->isNil()) {
        //FATAL_ERROR;

    }

        // TRUE < TRUE
    else if (isTrue() && o->isTrue()) {

    }

        // TRUE < …
        // … < TRUE
    else if (isTrue() || o->isTrue()) {
        ret = false;

    } else if ((type != o->type)) {
        ret = false;

    } else {
        switch (o->type) {
            // a < a
            case CODE:
                if (code != o->getCode())
                    ret = false;
                break;
            case NUMBER:
                if (number != o->number)
                    ret = false;
                break;
            case CONSTANT:
                if ((*bits & *o->bits).none())
                    ret = false;
                break;
            case STR:
                if (getStr() != o->getStr())
                    ret = false;
                break;
            case FEATURES:
                ret = getFeatures()->subsumes(o->getFeatures(), environment);
                break;
            case LIST:
                ret = getList()->subsumes(o->getList(), environment);
                break;

            default: FATAL_ERROR_UNEXPECTED

        }

    }
    /***
        std::cerr << "<DIV>";
        std::cerr << "result: (" << shared_from_this() << ")";
        std::cerr << "</DIV>";
    ***/
    return ret;
}

/* ************************************************************
 *
 ************************************************************ */
bool Value::eq(valuePtr o) const {
    /***
        STD::CERR_LINE;
        this->print(std::cerr);
        std::cerr << " = ";
        o->print(std::cerr);
        std::cerr << std::endl;
    ***/

    bool ret = false;

    if (o->isNil() && this->isNil())
        ret = true;

    else if (o->isNil() || this->isNil())
        ret = false;

    else if (o->type == ANONYMOUS || this->type == ANONYMOUS)
        ret = true;

    else {
        switch (o->type) {
            case TRUE: FATAL_ERROR_UNEXPECTED

            case CODE:
                if ((type == CODE) && ((code == o->getCode())))
                    ret = true;
                break;
            case CONSTANT:
                if ((type == CONSTANT) && ((*bits & *o->bits).any()))
                    ret = true;
                else if ((type == CODE) && (o->bits->toString() == Vartable::codeToIdentifier(code)))
                    ret = true;
                break;
            case STR:
                if ((type == STR) && (getStr() == o->getStr()))
                    ret = true;
                break;
            case NUMBER:
                if ((type == NUMBER) && (number == o->number))
                    ret = true;
                break;
            case FEATURES:
                if ((type == FEATURES) &&
                    (getFeatures()->peekSerialString() == o->getFeatures()->peekSerialString()))
                    ret = true;
                break;
            default: FATAL_ERROR_UNEXPECTED
        }
    }
    return ret;
}

/* ************************************************************
 *
 ************************************************************ */
bool Value::lt(const valuePtr &o) const {
    //bool ret = false;
    /***
        STD::CERR_LINE;
        this->print(std::cerr);
        std::cerr << " < ";
        o->print(std::cerr);
        std::cerr << std::endl;
    ***/
    if (isNumber() && o->isNumber())
        return (number < o->getNumber());
    else FATAL_ERROR_UNEXPECTED
    //return ret;
}

/* ************************************************************
 *
 ************************************************************ */
void Value::deleteAnonymousVariables() const {
    switch (type) {
        case NIL:
            FATAL_ERROR_UNEXPECTED
        case TRUE:
        case CODE:
        case CONSTANT:
        case STR:
        case VARIABLE:
        case ANONYMOUS:
        case NUMBER:
            break;
        case FEATURES:
            getFeatures()->deleteAnonymousVariables();
            break;
        case LIST:
            getList()->deleteAnonymousVariables();
            break;
    }
}

/* **************************************************
 *
 ************************************************** */
bool Value::renameVariables(size_t i) {
    bool effect = false;
    switch (type) {
        case NIL:
            FATAL_ERROR_UNEXPECTED

            case CONSTANT:
        case CODE:
        case STR:
        case TRUE:
        case NUMBER:
        case ANONYMOUS:
            break;
        case VARIABLE: {
            std::ostringstream oss;
            oss << bits->toString() << "_" << i;
            std::string _str = oss.str();
            bitsetPtr variableBits = Vartable::createVariable(_str);
            this->bits = variableBits;
            resetSerial();
            effect = true;
        }
            break;
        case FEATURES:
            if (getFeatures())
                if (getFeatures()->renameVariables(i))
                    effect = true;
            break;
        case LIST:
            if (getList())
                if (getList()->renameVariables(i))
                    effect = true;
            break;
    }
    return effect;
}

/* **************************************************
 *
 ************************************************** */
void Value::enable(const statementPtr &root, const itemPtr &item, Synthesizer *synthesizer, bool &effect, bool on) {
    switch (type) {
        case NIL:
            FATAL_ERROR_UNEXPECTED
        case TRUE:
        case CODE:
        case STR:
        case CONSTANT:
        case NUMBER:
        case ANONYMOUS:
            break;
        case VARIABLE:
            if (on) {
                if ((!item->getEnvironment()) || (!item->getEnvironment()->find(bits))) {
                    root->addFlags(Flags::DISABLED);
                    effect = true;
                }
            } else {
                root->subFlags(Flags::DISABLED);
                effect = true;
            }
            break;
        case FEATURES:
            getFeatures()->enable(root, item, synthesizer, effect, on);
            break;
        case LIST:
            getList()->enable(root, item, synthesizer, effect, on);
            break;
    }
}

/* **************************************************
 *
 ************************************************** */
bool Value::findVariable(const bitsetPtr &variable) const {
    switch (type) {
        case NIL: FATAL_ERROR_UNEXPECTED
        case TRUE:
        case CODE:
        case STR:
        case CONSTANT:
        case NUMBER:
        case ANONYMOUS:
            break;
        case VARIABLE:
            if (*bits == *variable)
                return true;
            break;
        case FEATURES:
            if (getFeatures()->findVariable(variable))
                return true;
            break;
        case LIST:
            if (getList()->findVariable(variable))
                return true;
            break;
    }
    return false;
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
void Value::apply(const itemPtr &item, Parser &parser, Synthesizer *synthesizer, const statementPtr &variable,
                  statementPtr body,
                  bool &effect) {
    switch (type) {
        case FEATURES:
            CERR_LINE
            item->getEnvironment()->add(variable->getBits(), shared_from_this());
            effect = true;
            body->apply(item, parser, synthesizer, effect);
            item->getEnvironment()->remove(variable->getBits());
            break;
        default: FATAL_ERROR_UNEXPECTED
    }
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
bool Value::containsVariable() {
    bool result = false;
    if (variableFlag.containsVariable())
        return true;
    switch (type) {
        case NIL: FATAL_ERROR_UNEXPECTED
        case TRUE:
        case CODE:
        case STR:
        case CONSTANT:
        case NUMBER:
        case ANONYMOUS:
            break;
        case VARIABLE:
            result = true;
            break;
        case LIST:
            if (this->getList()->containsVariable()) {
                result = true;
            }
            break;
        case FEATURES:
            if (this->getFeatures()->containsVariable()) {
                result = true;
            }
            break;
    }
    if (result)
        this->variableFlag.setFlag(VariableFlag::DOES_CONTAIN);
    else
        this->variableFlag.setFlag(VariableFlag::DOES_NOT_CONTAIN);
    return result;
}

/* **************************************************
 *
 ************************************************** */
void Value::setVariableFlag(enum VariableFlag::flagValues flag) {
    this->variableFlag.setFlag(flag);
}
