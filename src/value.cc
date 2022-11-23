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
#include <utility>
#include "value.hpp"
#include "environment.hpp"
#include "pairp.hpp"
#include "features.hpp"
#include "listfeatures.hpp"
#include "statement.hpp"
#include "statements.hpp"
#include "messages.hpp"
#include "item.hpp"
#include "shared_ptr.hpp"
#include "synthesizer.hpp"
#include "vartable.hpp"

valuePtr Value::NIL_VALUE = Value::create(Value::_NIL_);
valuePtr Value::TRUE_VALUE = Value::create(Value::_TRUE_);
valuePtr Value::ANONYMOUS_VALUE = Value::create(Value::_ANONYMOUS_);

/* **************************************************
 *
 ************************************************** */
Value::Value(Value::Type const type, const std::string &str) {
    NEW;
    this->type = type;
    this->code = 0;
    this->number = 0;
    if (type == _CODE_) {
        this->code = Vartable::stringToCode(str);
    } else if (type == _FORM_) {
        this->str = str;
    }
}

/* **************************************************
 *
 ************************************************** */
Value::Value(Value::Type const type, unsigned int code, double number, bitsetPtr _bits, featuresPtr _features,
             pairpPtr _list, listFeaturesPtr _listFeatures) {
    NEW;
    this->type = type;
    this->code = code;
    this->number = number;
    this->bits = _bits ? std::move(_bits) : bitsetPtr();
    this->features = _features ? std::move(_features) : featuresPtr();
    this->pairp = _list ? std::move(_list) : pairpPtr();
    this->listFeatures = _listFeatures ? std::move(_listFeatures) : listFeaturesPtr();
}

/* **************************************************
 *
 ************************************************** */
Value::~Value() {
    DELETE;
    if (bits)
        bits.reset();
    if (features)
        features.reset();
    if (pairp)
        pairp.reset();
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
valuePtr Value::create(featuresPtr features) {
    return valuePtr(new Value(Value::_FEATURES_, 0, 0, bitsetPtr(), std::move(features)));
}

/* **************************************************
 *
 ************************************************** */
valuePtr Value::create(listFeaturesPtr listFeatures) {
    return valuePtr(new Value(Value::_LISTFEATURES_, 0, 0, bitsetPtr(), featuresPtr(), pairpPtr(), std::move(listFeatures)));
}

/* **************************************************
 *
 ************************************************** */
valuePtr Value::create(pairpPtr lst) {
    return valuePtr(new Value(Value::_PAIRP_, 0, 0, bitsetPtr(), featuresPtr(), std::move(lst)));
}

/* **************************************************
 *
 ************************************************** */
Value::Type Value::_getType() const {
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
listFeaturesPtr Value::getListFeatures() const {
    return listFeatures;
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
pairpPtr Value::getPairp() const {
    return pairp;
}

/* **************************************************
 *
 ************************************************** */
bool Value::isNil() const {
    return (type == _NIL_);
}

/* **************************************************
 *
 ************************************************** */
bool Value::isFalse() const {
    return ((type == _NIL_) || (type == _ANONYMOUS_));
}

/* **************************************************
 *
 ************************************************** */
bool Value::isTrue() const {
    return (type == _TRUE_);
}

/* **************************************************
 *
 ************************************************** */
bool Value::isAnonymous() const {
    return type == _ANONYMOUS_;
}

/* **************************************************
 *
 ************************************************** */
bool Value::isNumber() const {
    return type == _NUMBER_;
}

/* **************************************************
 *
 ************************************************** */
bool Value::isForm() const {
    return type == _FORM_;
}

/* **************************************************
 *
 ************************************************** */
bool Value::isFeatures() const {
    return type == _FEATURES_;
}

/* **************************************************
 *
 ************************************************** */
bool Value::isConstant() const {
    return type == _CONSTANT_;
}

/* **************************************************
 *
 ************************************************** */
bool Value::isVariable() const {
    return type == _VARIABLE_;
}

/* **************************************************
 *
 ************************************************** */
bool Value::isIdentifier() const {
    return type == _CODE_;
}

/* **************************************************
 *
 ************************************************** */
bool Value::isPairp() const {
    return type == _PAIRP_;
}

/* **************************************************
 *
 ************************************************** */
bool Value::isListFeatures() const {
    return type == _LISTFEATURES_;
}

/* **************************************************
 *
 ************************************************** */
void Value::print(std::ostream &outStream) const {
    switch (type) {
        case _NIL_:
            outStream << "NIL";
            break;
        case _TRUE_:
            outStream << "TRUE";
            break;
        case _CONSTANT_:
            outStream << bits->toString();
            break;
        case _VARIABLE_:
            outStream << bits->toString();
            break;
        case _ANONYMOUS_:
            outStream << '_';
            break;
        case _CODE_:
            outStream << Vartable::codeToString(code);
            break;
        case _NUMBER_:
            outStream << number;
            break;
        case _FORM_:
            outStream << "&quot;" << getStr() << "&quot;";
            break;
        case _FEATURES_:
            getFeatures()->print(outStream);
            break;
        case _LISTFEATURES_:
            getListFeatures()->print(outStream);
            break;
        case _PAIRP_:
            getPairp()->flatPrint(outStream, true);
            break;
    }
}

/* **************************************************
 *
 ************************************************** */
void Value::flatPrint(std::ostream &outStream) const {
    switch (type) {
        case _NIL_:
            outStream << "NIL";
            break;
        case _TRUE_:
            outStream << "TRUE";
            break;
        case _CONSTANT_:
        case _VARIABLE_:
            outStream << bits->toString();
            break;
        case _ANONYMOUS_:
            outStream << '_';
            break;
        case _CODE_:
            outStream << Vartable::codeToString(code);
            break;
        case _NUMBER_:
            outStream << number;
            break;
        case _FORM_:
            outStream << '"' << getStr() << '"';
            break;
        case _FEATURES_:
            getFeatures()->flatPrint(outStream);
            break;
        case _LISTFEATURES_:
            getListFeatures()->flatPrint(outStream);
            break;
        case _PAIRP_:
            getPairp()->flatPrint(outStream, true);
            break;
    }
}

/* **************************************************
 *
 ************************************************** */
void Value::makeSerialString() {
    switch (type) {
        case _NIL_:
            serialString = '\0';
            break;
        case _TRUE_:
            serialString = '\1';
            break;
        case _CONSTANT_:
            serialString = bits->peekSerialString();
            break;
        case _VARIABLE_:
            serialString = '\2' + bits->peekSerialString();
            break;
        case _ANONYMOUS_:
            serialString = '\3';
            break;
        case _CODE_:
            serialString = std::to_string(code);
            break;
        case _NUMBER_:
            serialString = std::to_string(number);
            break;
        case _FORM_:
            serialString = str;
            break;
        case _FEATURES_:
            serialString = getFeatures()->peekSerialString();
            break;
        case _LISTFEATURES_:
            serialString = getListFeatures()->peekSerialString();
            break;
        case _PAIRP_:
            serialString = getPairp()->peekSerialString();
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
  case _NIL_:
    xmlSetProp(v, (xmlChar*)"type", (const xmlChar*)"nil");
    bits->toXML(v);
    break;
  case _TRUE_:
    xmlSetProp(v, (xmlChar*)"type", (const xmlChar*)"true");
    bits->toXML(v);
    break;
  case _CONSTANT_:
    xmlSetProp(v, (xmlChar*)"type", (const xmlChar*)"constant");
    bits->toXML(v);
    break;
  case _VARIABLE_:
    xmlSetProp(v, (xmlChar*)"type", (const xmlChar*)"variable");
    bits->toXML(v);
    break;
  case _ANONYMOUS_:
    xmlSetProp(v, (xmlChar*)"type", (const xmlChar*)"anonymous");
    bits->toXML(v);
    break;
  case _CODE_:
    xmlSetProp(v, (xmlChar*)"type", (const xmlChar*)"identifier");
    xmlNewChild(v, NULL, (const xmlChar*)"VAL", (const xmlChar*)Vartable::codeToString(getCode()).c_str());
    break;
  case _NUMBER_:
    xmlSetProp(v, (xmlChar*)"type", (const xmlChar*)"double");
    xmlSetProp(v, (xmlChar*)"value",(const xmlChar*)std::to_string(number).c_str());
    break;
  case _FORM_:
    xmlSetProp(v, (xmlChar*)"type", (const xmlChar*)"form");
    xmlNewChild(v, NULL, (const xmlChar*)"VAL", (const xmlChar*)getStr().c_str());
    break;
  case _FEATURES_:
    xmlSetProp(v, (xmlChar*)"type", (const xmlChar*)"fs");
    getFeatures()->toXML(v);
    break;
  case _LISTFEATURES_:
    xmlSetProp(v, (xmlChar*)"type", (const xmlChar*)"lfs");
    getListFeatures()->toXML(v);
    break;
  case _PAIRP_:
    xmlSetProp(v, (xmlChar*)"type", (const xmlChar*)"list");
    getPairp()->toXML(v);
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
        case _NIL_:
        case _TRUE_:
        case _CONSTANT_:
        case _CODE_:
        case _FORM_:
        case _NUMBER_:
        case _ANONYMOUS_:
            result = shared_from_this();
            break;
        case _FEATURES_:
            result = Value::create(getFeatures()->clone());
            break;
        case _LISTFEATURES_:
            result = Value::create(getListFeatures()->clone());
            break;
        case _PAIRP_:
            result = Value::create(getPairp()->clone());
            break;
        case _VARIABLE_:
            result = Value::create(_VARIABLE_, bits);
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

        case _LISTFEATURES_:
        case _TRUE_: 
            FATAL_ERROR_UNEXPECTED
/*            if (value->type == VARIABLE) {
                environment->add(value->bits, shared_from_this());
            } else if (value->type == _TRUE) {
            } else if (value->type == ANONYMOUS) {
            } else {
                ret = false;
            }
            break;
*/

        case _NIL_:
            if (value->type == _VARIABLE_) {
                environment->add(value->bits, shared_from_this());
            } else if (value->type == _NIL_) {
            } else if (value->type == _ANONYMOUS_) {
            } else {
                ret = false;
            }
            break;

        case _FEATURES_:
            if (value->type == _VARIABLE_) {
                environment->add(value->bits, shared_from_this());
            } else if (value->type == _FEATURES_) {
                if (!this->getFeatures()->buildEnvironment(environment, value->getFeatures(),
                                                           acceptToFilterNULLVariables/*, root*/))
                    ret = false;
            } else if (value->type == _ANONYMOUS_) {
                if (!this->getFeatures()->buildEnvironment(environment, Features::create(),
                                                           acceptToFilterNULLVariables/*,
                                                           root*/))
                    ret = false;
            } else {
                ret = false;
            }
            break;

        case _CONSTANT_:
            if (value->type == _VARIABLE_) {
                environment->add(value->bits, shared_from_this());
            } else if (value->type == _CONSTANT_) {
                if ((*bits & *value->bits).none())
                    ret = false;
            } else if (value->type == _CODE_) {
                if (bits->toString() != Vartable::codeToString(value->getCode()))
                    ret = false;
            } else if (value->type == _ANONYMOUS_) {
            } else {
                ret = false;
            }
            break;

        case _CODE_:
            if (value->type == _VARIABLE_) {
                environment->add(value->bits, shared_from_this());
            } else if (value->type == _CONSTANT_) {
                if (Vartable::codeToString(code) != value->bits->toString())
                    ret = false;
            } else if (value->type == _CODE_) {
                if (code != value->getCode())
                    ret = false;
            } else if (value->type == _ANONYMOUS_) {
            } else {
                ret = false;
            }
            break;

        case _NUMBER_:
            if (value->type == _VARIABLE_) {
                environment->add(value->bits, shared_from_this());
            } else if (value->type == _NUMBER_) {
                if (number != value->number) {
                    ret = false;
                }
            } else if (value->type == _ANONYMOUS_) {
            } else {
                ret = false;
            }
            break;

        case _FORM_:
            if (value->type == _VARIABLE_) {
                environment->add(value->bits, shared_from_this());
            } else if (value->type == _FORM_) {
                if (getStr() != value->getStr()) {
                    ret = false;
                }
            } else if (value->type == _ANONYMOUS_) {
            } else {
                ret = false;
            }
            break;

        case _PAIRP_:
            if (value->type == _PAIRP_) {
                if (!this->getPairp()->buildEnvironment(environment, value->getPairp(),
                                                       acceptToFilterNULLVariables,
                                                       root))
                    ret = false;
            } else if (value->type == _VARIABLE_) {
                environment->add(value->bits, shared_from_this());
            } else if (value->type == _ANONYMOUS_) {
            } else {
                ret = false;
            }
            break;

        case _VARIABLE_:
            if (!value) {
                environment->add(this->bits, NIL_VALUE);
            } else {
                environment->add(this->bits, value);
            }
            break;

        case _ANONYMOUS_:
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
    if (type == _VARIABLE_) {
        environment->add(bits, o);
    }

        // … < $X
    else if (o->type == _VARIABLE_) {
        environment->add(o->bits, shared_from_this());
    }

        // NIL < NIL
    else if (isNil() && o->isNil()) {
    }

        // NIL < …
        // … < NIL
    else if (isNil() || o->isNil()) {
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
            case _CODE_:
                if (code != o->getCode())
                    ret = false;
                break;
            case _NUMBER_:
                if (number != o->number)
                    ret = false;
                break;
            case _CONSTANT_:
                if ((*bits & *o->bits).none())
                    ret = false;
                break;
            case _FORM_:
                if (getStr() != o->getStr())
                    ret = false;
                break;
            case _FEATURES_:
                ret = getFeatures()->subsumes(o->getFeatures(), environment);
                break;
            case _PAIRP_:
                ret = getPairp()->subsumes(o->getPairp(), environment);
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

    if (o->isNil() && this->isNil())
        ret = true;

    else if (o->isNil() || this->isNil())
        ret = false;

    else if (o->type == _ANONYMOUS_ || this->type == _ANONYMOUS_)
        ret = true;

    else {
        switch (o->type) {
            case _CODE_:
                if ((type == _CODE_) && ((code == o->getCode())))
                    ret = true;
                break;
            case _CONSTANT_:
                if ((type == _CONSTANT_) && ((*bits & *o->bits).any()))
                    ret = true;
                else if ((type == _CODE_) && (o->bits->toString() == Vartable::codeToString(code)))
                    ret = true;
                break;
            case _FORM_:
                if ((type == _FORM_) && (getStr() == o->getStr()))
                    ret = true;
                break;
            case _NUMBER_:
                if ((type == _NUMBER_) && (number == o->number))
                    ret = true;
                break;
            case _FEATURES_:
                if ((type == _FEATURES_) &&
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
        case _TRUE_:
        case _NIL_:
        case _CODE_:
        case _CONSTANT_:
        case _FORM_:
        case _VARIABLE_:
        case _ANONYMOUS_:
        case _NUMBER_:
        case _LISTFEATURES_:
            break;
        case _FEATURES_:
            getFeatures()->deleteAnonymousVariables();
            break;
        case _PAIRP_:
            getPairp()->deleteAnonymousVariables();
            break;
    }
}

/* **************************************************
 *
 ************************************************** */
bool Value::renameVariables(size_t i) {
    bool effect = false;
    switch (type) {
        case _NIL_:
        case _TRUE_:
        case _CONSTANT_:
        case _CODE_:
        case _FORM_:
        case _NUMBER_:
        case _ANONYMOUS_:
        case _LISTFEATURES_:
            break;
        case _VARIABLE_: {
            std::ostringstream oss;
            oss << bits->toString() << "_" << i;
            std::string _str = oss.str();
            bitsetPtr variableBits = Vartable::createVariable(_str);
            this->bits = variableBits;
            resetSerial();
            effect = true;
        }
            break;
        case _FEATURES_:
            if (getFeatures())
                if (getFeatures()->renameVariables(i))
                    effect = true;
            break;
        case _PAIRP_:
            if (getPairp())
                if (getPairp()->renameVariables(i))
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
        case _NIL_:
        case _TRUE_:
        case _CODE_:
        case _FORM_:
        case _CONSTANT_:
        case _NUMBER_:
        case _ANONYMOUS_:
        case _LISTFEATURES_:
            break;
        case _VARIABLE_:
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
        case _FEATURES_:
            getFeatures()->enable(root, item, synthesizer, effect, on);
            break;
        case _PAIRP_:
            getPairp()->enable(root, item, synthesizer, effect, on);
            break;
    }
}

/* **************************************************
 *
 ************************************************** */
bool Value::findVariable(const bitsetPtr &variable) const {
    switch (type) {
        case _NIL_:
        case _TRUE_:
        case _CODE_:
        case _FORM_:
        case _CONSTANT_:
        case _NUMBER_:
        case _ANONYMOUS_:
        case _LISTFEATURES_:
            break;
        case _VARIABLE_:
            if (*bits == *variable)
                return true;
            break;
        case _FEATURES_:
            if (getFeatures()->findVariable(variable))
                return true;
            break;
        case _PAIRP_:
            if (getPairp()->findVariable(variable))
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
        case _FEATURES_:
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
        case _TRUE_:
        case _NIL_:
        case _CODE_:
        case _FORM_:
        case _CONSTANT_:
        case _NUMBER_:
        case _ANONYMOUS_:
        case _LISTFEATURES_:
            break;
        case _VARIABLE_:
            result = true;
            break;
        case _PAIRP_:
            if (this->getPairp()->containsVariable()) {
                result = true;
            }
            break;
        case _FEATURES_:
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
