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

valuePtr Value::NIL_VALUE = Value::create(Value::_NIL);
valuePtr Value::TRUE_VALUE = Value::create(Value::_TRUE);
valuePtr Value::ANONYMOUS_VALUE = Value::create(Value::_ANONYMOUS);

/* **************************************************
 *
 ************************************************** */
Value::Value(Value::Type const type, const std::string &str) {
    this->type = type;
    this->code = 0;
    this->number = 0;
    //unsigned int found = 0;
    if (type == _CODE) {
        this->code = Vartable::stringToCode(str);
    } else if (type == _FORM) {
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
bool Value::_isNil() const {
    return (type == _NIL);
}

/* **************************************************
 *
 ************************************************** */
bool Value::_isFalse() const {
    return ((type == _NIL) || (type == _ANONYMOUS));
}

/* **************************************************
 *
 ************************************************** */
bool Value::_isTrue() const {
    return (type == _TRUE);
}

/* **************************************************
 *
 ************************************************** */
bool Value::_isAnonymous() const {
    return type == _ANONYMOUS;
}

/* **************************************************
 *
 ************************************************** */
bool Value::_isNumber() const {
    return type == _NUMBER;
}

/* **************************************************
 *
 ************************************************** */
bool Value::_isForm() const {
    return type == _FORM;
}

/* **************************************************
 *
 ************************************************** */
bool Value::_isFeatures() const {
    return type == _FEATURES;
}

/* **************************************************
 *
 ************************************************** */
bool Value::_isConstant() const {
    return type == _CONSTANT;
}

/* **************************************************
 *
 ************************************************** */
bool Value::_isVariable() const {
    return type == _VARIABLE;
}

/* **************************************************
 *
 ************************************************** */
bool Value::_isIdentifier() const {
    return type == _CODE;
}

/* **************************************************
 *
 ************************************************** */
bool Value::_isList() const {
    return type == _LIST;
}

/* **************************************************
 *
 ************************************************** */
void Value::print(std::ostream &outStream) const {
    switch (type) {
        case _NIL:
            outStream << "NIL";
            break;
        case _TRUE:
            outStream << "TRUE";
            break;
        case _CONSTANT:
            outStream << bits->toString();
            break;
        case _VARIABLE:
            outStream << bits->toString();
            break;
        case _ANONYMOUS:
            outStream << '_';
            break;
        case _CODE:
            outStream << Vartable::codeToString(code);
            break;
        case _NUMBER:
            outStream << number;
            break;
        case _FORM:
            outStream << "&quot;" << getStr() << "&quot;";
            break;
        case _FEATURES:
            getFeatures()->print(outStream);
            break;
        case _LIST:
            getList()->flatPrint(outStream, true);
            break;
    }
}

/* **************************************************
 *
 ************************************************** */
void Value::flatPrint(std::ostream &outStream) const {
    switch (type) {
        case _NIL:
            outStream << "NIL";
            break;
        case _TRUE:
            outStream << "TRUE";
            break;
        case _CONSTANT:
        case _VARIABLE:
            outStream << bits->toString();
            break;
        case _ANONYMOUS:
            outStream << '_';
            break;
        case _CODE:
            outStream << Vartable::codeToString(code);
            break;
        case _NUMBER:
            outStream << number;
            break;
        case _FORM:
            outStream << '"' << getStr() << '"';
            break;
        case _FEATURES:
            getFeatures()->flatPrint(outStream);
            break;
        case _LIST:
            getList()->flatPrint(outStream, true);
            break;
    }
}

/* **************************************************
 *
 ************************************************** */
void Value::makeSerialString() {
    switch (type) {
        case _NIL:
            serialString = 'N';
            break;
        case _TRUE:
            serialString = 'T';
            break;
        case _CONSTANT:
            serialString = bits->peekSerialString();
            break;
        case _VARIABLE:
            serialString = '$' + bits->peekSerialString();
            break;
        case _ANONYMOUS:
            serialString = '_';
            break;
        case _CODE:
            serialString = std::to_string(code);
            break;
        case _NUMBER:
            serialString = number;
            break;
        case _FORM:
            serialString = str;
            break;
        case _FEATURES:
            serialString = getFeatures()->peekSerialString();
            break;
        case _LIST:
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
  case _NIL:
    xmlSetProp(v, (xmlChar*)"type", (const xmlChar*)"nil");
    bits->toXML(v);
    break;
  case _TRUE:
    xmlSetProp(v, (xmlChar*)"type", (const xmlChar*)"true");
    bits->toXML(v);
    break;
  case _CONSTANT:
    xmlSetProp(v, (xmlChar*)"type", (const xmlChar*)"constant");
    bits->toXML(v);
    break;
  case _VARIABLE:
    xmlSetProp(v, (xmlChar*)"type", (const xmlChar*)"variable");
    bits->toXML(v);
    break;
  case _ANONYMOUS:
    xmlSetProp(v, (xmlChar*)"type", (const xmlChar*)"anonymous");
    bits->toXML(v);
    break;
  case _CODE:
    xmlSetProp(v, (xmlChar*)"type", (const xmlChar*)"identifier");
    xmlNewChild(v, NULL, (const xmlChar*)"VAL", (const xmlChar*)Vartable::codeToString(getCode()).c_str());
    break;
  case _NUMBER:
    xmlSetProp(v, (xmlChar*)"type", (const xmlChar*)"double");
    xmlSetProp(v, (xmlChar*)"value",(const xmlChar*)std::to_string(number).c_str());
    break;
  case _FORM:
    xmlSetProp(v, (xmlChar*)"type", (const xmlChar*)"form");
    xmlNewChild(v, NULL, (const xmlChar*)"VAL", (const xmlChar*)getStr().c_str());
    break;
  case _FEATURES:
    xmlSetProp(v, (xmlChar*)"type", (const xmlChar*)"fs");
    getFeatures()->toXML(v);
    break;
  case _LIST:
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
        case _NIL:
        case _TRUE:
        case _CONSTANT:
        case _CODE:
        case _FORM:
        case _NUMBER:
        case _ANONYMOUS:
            result = shared_from_this();
            break;
        case _FEATURES:
            result = Value::create(Value::_FEATURES, getFeatures()->clone());
            break;
        case _LIST:
            result = Value::create(Value::_LIST, getList()->clone());
            break;
        case _VARIABLE:
            result = Value::create(_VARIABLE, bits);
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

        case _TRUE: FATAL_ERROR_UNEXPECTED
/*            if (value->type == VARIABLE) {
                environment->add(value->bits, shared_from_this());
            } else if (value->type == _TRUE) {
            } else if (value->type == ANONYMOUS) {
            } else {
                ret = false;
            }
            break;
*/

        case _NIL:
            if (value->type == _VARIABLE) {
                environment->add(value->bits, shared_from_this());
            } else if (value->type == _NIL) {
            } else if (value->type == _ANONYMOUS) {
            } else {
                ret = false;
            }
            break;

        case _FEATURES:
            if (value->type == _VARIABLE) {
                environment->add(value->bits, shared_from_this());
            } else if (value->type == _FEATURES) {
                if (!this->getFeatures()->buildEnvironment(environment, value->getFeatures(),
                                                           acceptToFilterNULLVariables/*, root*/))
                    ret = false;
            } else if (value->type == _ANONYMOUS) {
                if (!this->getFeatures()->buildEnvironment(environment, Features::create(),
                                                           acceptToFilterNULLVariables/*,
                                                           root*/))
                    ret = false;
            } else {
                ret = false;
            }
            break;

        case _CONSTANT:
            if (value->type == _VARIABLE) {
                environment->add(value->bits, shared_from_this());
            } else if (value->type == _CONSTANT) {
                if ((*bits & *value->bits).none())
                    ret = false;
            } else if (value->type == _CODE) {
                if (bits->toString() != Vartable::codeToString(value->getCode()))
                    ret = false;
            } else if (value->type == _ANONYMOUS) {
            } else {
                ret = false;
            }
            break;

        case _CODE:
            if (value->type == _VARIABLE) {
                environment->add(value->bits, shared_from_this());
            } else if (value->type == _CONSTANT) {
                if (Vartable::codeToString(code) != value->bits->toString())
                    ret = false;
            } else if (value->type == _CODE) {
                if (code != value->getCode())
                    ret = false;
            } else if (value->type == _ANONYMOUS) {
            } else {
                ret = false;
            }
            break;

        case _NUMBER:
            if (value->type == _VARIABLE) {
                environment->add(value->bits, shared_from_this());
            } else if (value->type == _NUMBER) {
                if (number != value->number) {
                    ret = false;
                }
            } else if (value->type == _ANONYMOUS) {
            } else {
                ret = false;
            }
            break;

        case _FORM:
            if (value->type == _VARIABLE) {
                environment->add(value->bits, shared_from_this());
            } else if (value->type == _FORM) {
                if (getStr() != value->getStr()) {
                    ret = false;
                }
            } else if (value->type == _ANONYMOUS) {
            } else {
                ret = false;
            }
            break;

        case _LIST:
            if (value->type == _LIST) {
                if (!this->getList()->buildEnvironment(environment, value->getList(),
                                                       acceptToFilterNULLVariables,
                                                       root))
                    ret = false;
            } else if (value->type == _VARIABLE) {
                environment->add(value->bits, shared_from_this());
            } else if (value->type == _ANONYMOUS) {
            } else {
                ret = false;
            }
            break;

        case _VARIABLE:
            if (!value) {
                environment->add(this->bits, NIL_VALUE);
            } else {
                environment->add(this->bits, value);
            }
            break;

        case _ANONYMOUS:
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

    // $X < …
    if (type == _VARIABLE) {
        environment->add(bits, o);
    }

        // … < $X
    else if (o->type == _VARIABLE) {
        environment->add(o->bits, shared_from_this());
    }

        // NIL < NIL
    else if (_isNil() && o->_isNil()) {
    }

        // NIL < …
        // … < NIL
    else if (_isNil() || o->_isNil()) {
    }

        // TRUE < TRUE
    else if (_isTrue() && o->_isTrue()) {

    }

        // TRUE < …
        // … < TRUE
    else if (_isTrue() || o->_isTrue()) {
        ret = false;

    } else if ((type != o->type)) {
        ret = false;

    } else {
        switch (o->type) {
            // a < a
            case _CODE:
                if (code != o->getCode())
                    ret = false;
                break;
            case _NUMBER:
                if (number != o->number)
                    ret = false;
                break;
            case _CONSTANT:
                if ((*bits & *o->bits).none())
                    ret = false;
                break;
            case _FORM:
                if (getStr() != o->getStr())
                    ret = false;
                break;
            case _FEATURES:
                ret = getFeatures()->subsumes(o->getFeatures(), environment);
                break;
            case _LIST:
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
    /* **
        CERR_LINE;
        this->flatPrint(std::cerr);
        std::cerr << " = ";
        o->flatPrint(std::cerr);
        std::cerr << std::endl;
     ** */

    bool ret = false;

    if (o->_isNil() && this->_isNil())
        ret = true;

    else if (o->_isNil() || this->_isNil())
        ret = false;

    else if (o->type == _ANONYMOUS || this->type == _ANONYMOUS)
        ret = true;

    else {
        switch (o->type) {
            case _CODE:
                if ((type == _CODE) && ((code == o->getCode())))
                    ret = true;
                break;
            case _CONSTANT:
                if ((type == _CONSTANT) && ((*bits & *o->bits).any()))
                    ret = true;
                else if ((type == _CODE) && (o->bits->toString() == Vartable::codeToString(code)))
                    ret = true;
                break;
            case _FORM:
                if ((type == _FORM) && (getStr() == o->getStr()))
                    ret = true;
                break;
            case _NUMBER:
                if ((type == _NUMBER) && (number == o->number))
                    ret = true;
                break;
            case _FEATURES:
                if ((type == _FEATURES) &&
                    (getFeatures()->peekSerialString() == o->getFeatures()->peekSerialString()))
                    ret = true;
                break;
            default:
                FATAL_ERROR_UNEXPECTED
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
    if (_isNumber() && o->_isNumber())
        return (number < o->getNumber());
    else FATAL_ERROR_UNEXPECTED
    //return ret;
}

/* ************************************************************
 *
 ************************************************************ */
void Value::deleteAnonymousVariables() const {
    switch (type) {
        case _TRUE:
        case _NIL:
        case _CODE:
        case _CONSTANT:
        case _FORM:
        case _VARIABLE:
        case _ANONYMOUS:
        case _NUMBER:
            break;
        case _FEATURES:
            getFeatures()->deleteAnonymousVariables();
            break;
        case _LIST:
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
        case _NIL:
        case _TRUE:
        case _CONSTANT:
        case _CODE:
        case _FORM:
        case _NUMBER:
        case _ANONYMOUS:
            break;
        case _VARIABLE: {
            std::ostringstream oss;
            oss << bits->toString() << "_" << i;
            std::string _str = oss.str();
            bitsetPtr variableBits = Vartable::createVariable(_str);
            this->bits = variableBits;
            resetSerial();
            effect = true;
        }
            break;
        case _FEATURES:
            if (getFeatures())
                if (getFeatures()->renameVariables(i))
                    effect = true;
            break;
        case _LIST:
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
void Value::enable(const statementPtr &root, class Item* item, Synthesizer* synthesizer, bool& effect, bool on) {
    switch (type) {
        case _NIL:
        case _TRUE:
        case _CODE:
        case _FORM:
        case _CONSTANT:
        case _NUMBER:
        case _ANONYMOUS:
            break;
        case _VARIABLE:
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
        case _FEATURES:
            getFeatures()->enable(root, item, synthesizer, effect, on);
            break;
        case _LIST:
            getList()->enable(root, item, synthesizer, effect, on);
            break;
    }
}

/* **************************************************
 *
 ************************************************** */
bool Value::findVariable(const bitsetPtr &variable) const {
    switch (type) {
        case _NIL:
        case _TRUE:
        case _CODE:
        case _FORM:
        case _CONSTANT:
        case _NUMBER:
        case _ANONYMOUS:
            break;
        case _VARIABLE:
            if (*bits == *variable)
                return true;
            break;
        case _FEATURES:
            if (getFeatures()->findVariable(variable))
                return true;
            break;
        case _LIST:
            if (getList()->findVariable(variable))
                return true;
            break;
    }
    return false;
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
void Value::apply(class Item* item, Parser &parser, Synthesizer *synthesizer, const statementPtr &variable,
                  const statementPtr& body,
                  bool &effect) {
    switch (type) {
        case _FEATURES:
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
        case _TRUE:
        case _NIL:
        case _CODE:
        case _FORM:
        case _CONSTANT:
        case _NUMBER:
        case _ANONYMOUS:
            break;
        case _VARIABLE:
            result = true;
            break;
        case _LIST:
            if (this->getList()->containsVariable()) {
                result = true;
            }
            break;
        case _FEATURES:
            if (this->getFeatures()->containsVariable()) {
                result = true;
            }
            break;
    }
    if (result)
        this->variableFlag.setFlag(VariableFlag::CONTAINS);
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
