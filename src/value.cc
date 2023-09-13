/* **************************************************
 *
 * ELVEX
 *
 * Copyright 2014-2023 LABRI,
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
#include "generator.hpp"
#include "vartable.hpp"

valuePtr Value::STATIC_NIL = Value::create(Value::NIL_VALUE);
valuePtr Value::STATIC_TRUE = Value::create(Value::TRUE_VALUE);
valuePtr Value::STATIC_FALSE = Value::create(Value::FALSE_VALUE);
valuePtr Value::STATIC_ANONYMOUS = Value::create(Value::ANONYMOUS_VALUE);

/* **************************************************
 *
 ************************************************** */
Value::Value(Value::Type const type, const std::string &str)
{
    NEW;
    this->type = type;
    this->code = 0;
    this->number = 0;
    if (type == IDENTIFIER_VALUE)
    {
        this->code = Vartable::stringToCode(str);
    }
    else if (type == FORM_VALUE)
    {
        this->str = str;
    }
}

/* **************************************************
 *
 ************************************************** */
Value::Value(Value::Type const type, unsigned int code, double number, bitsetPtr _bits, featuresPtr _features,
             pairpPtr _list, listFeaturesPtr _listFeatures)
{
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
Value::~Value()
{
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
valuePtr Value::create(const enum Type type)
{
    return valuePtr(new Value(type));
}

/* **************************************************
 *
 ************************************************** */
valuePtr Value::create(const enum Type type, double number)
{
    return valuePtr(new Value(type, 0, number));
}

/* **************************************************
 *
 ************************************************** */
valuePtr Value::create(const enum Type type, unsigned int integer)
{
    return valuePtr(new Value(type, integer));
}

/* **************************************************
 *
 ************************************************** */
valuePtr Value::create(const enum Type type, const std::string &str)
{
    return valuePtr(new Value(type, str));
}

/* **************************************************
 *
 ************************************************** */
valuePtr Value::create(const enum Type type, bitsetPtr bits)
{
    return valuePtr(new Value(type, 0, 0, std::move(bits)));
}

/* **************************************************
 *
 ************************************************** */
valuePtr Value::create(featuresPtr features)
{
    return valuePtr(new Value(Value::FEATURES_VALUE, 0, 0, bitsetPtr(), std::move(features)));
}

/* **************************************************
 *
 ************************************************** */
valuePtr Value::create(listFeaturesPtr listFeatures)
{
    return valuePtr(new Value(Value::LIST_FEATURES_VALUE, 0, 0, bitsetPtr(), featuresPtr(), pairpPtr(), std::move(listFeatures)));
}

/* **************************************************
 *
 ************************************************** */
valuePtr Value::create(pairpPtr lst)
{
    return valuePtr(new Value(Value::PAIRP_VALUE, 0, 0, bitsetPtr(), featuresPtr(), std::move(lst)));
}

/* **************************************************
 *
 ************************************************** */
Value::Type Value::getType() const
{
    return type;
}

/* **************************************************
 *
 ************************************************** */
bitsetPtr Value::getBits() const
{
    return bits;
}

/* **************************************************
 *
 ************************************************** */
unsigned int Value::getCode() const
{
    return code;
}

/* **************************************************
 *
 ************************************************** */
featuresPtr Value::getFeatures() const
{
    return features;
}

/* **************************************************
 *
 ************************************************** */
listFeaturesPtr Value::getListFeatures() const
{
    return listFeatures;
}

/* **************************************************
 *
 ************************************************** */
double Value::getNumber() const
{
    return number;
}

/* **************************************************
 *
 ************************************************** */
std::string Value::getStr() const
{
    return str;
}

/* **************************************************
 *
 ************************************************** */
pairpPtr Value::getPairp() const
{
    return pairp;
}

/* **************************************************
 *
 ************************************************** */
bool Value::isNil() const
{
    return (type == NIL_VALUE);
}

/* **************************************************
 *
 ************************************************** */
bool Value::isTrue() const
{
    return (type == TRUE_VALUE);
}

/* **************************************************
 *
 ************************************************** */
bool Value::isFalse() const
{
    return ((type == FALSE_VALUE) || (type == NIL_VALUE) || (type == ANONYMOUS_VALUE));
}

/* **************************************************
 *
 ************************************************** */
bool Value::isAnonymous() const
{
    return type == ANONYMOUS_VALUE;
}

/* **************************************************
 *
 ************************************************** */
bool Value::isNumber() const
{
    return type == NUMBER_VALUE;
}

/* **************************************************
 *
 ************************************************** */
bool Value::isForm() const
{
    return type == FORM_VALUE;
}

/* **************************************************
 *
 ************************************************** */
bool Value::isFeatures() const
{
    return type == FEATURES_VALUE;
}

/* **************************************************
 *
 ************************************************** */
bool Value::isConstant() const
{
    return type == CONSTANT_VALUE;
}

/* **************************************************
 *
 ************************************************** */
bool Value::isVariable() const
{
    return type == VARIABLE_VALUE;
}

/* **************************************************
 *
 ************************************************** */
bool Value::isIdentifier() const
{
    return type == IDENTIFIER_VALUE;
}

/* **************************************************
 *
 ************************************************** */
bool Value::isPairp() const
{
    return type == PAIRP_VALUE;
}

/* **************************************************
 *
 ************************************************** */
bool Value::isListFeatures() const
{
    return type == LIST_FEATURES_VALUE;
}

/* **************************************************
 *
 ************************************************** */
void Value::print(std::ostream &outStream) const
{
    switch (type)
    {
    case NIL_VALUE:
        outStream << "NIL";
        break;
    case TRUE_VALUE:
        outStream << "TRUE";
        break;
    case FALSE_VALUE:
        outStream << "FALSE";
        break;
    case CONSTANT_VALUE:
        outStream << bits->toString();
        break;
    case VARIABLE_VALUE:
        outStream << bits->toString();
        break;
    case ANONYMOUS_VALUE:
        outStream << '_';
        break;
    case IDENTIFIER_VALUE:
        outStream << Vartable::codeToString(code);
        break;
    case NUMBER_VALUE:
        outStream << number;
        break;
    case FORM_VALUE:
        outStream << getStr();
        break;
    case FEATURES_VALUE:
        getFeatures()->print(outStream);
        break;
    case LIST_FEATURES_VALUE:
        getListFeatures()->print(outStream);
        break;
    case PAIRP_VALUE:
        getPairp()->flatPrint(outStream, true);
        break;
    }
}

/* **************************************************
 *
 ************************************************** */
void Value::flatPrint(std::ostream &outStream) const
{
    switch (type)
    {
    case NIL_VALUE:
        outStream << "NIL";
        break;
    case TRUE_VALUE:
        outStream << "TRUE";
        break;
    case FALSE_VALUE:
        outStream << "FALSE";
        break;
    case CONSTANT_VALUE:
    case VARIABLE_VALUE:
        outStream << bits->toString();
        break;
    case ANONYMOUS_VALUE:
        outStream << '_';
        break;
    case IDENTIFIER_VALUE:
        outStream << Vartable::codeToString(code);
        break;
    case NUMBER_VALUE:
        outStream << number;
        break;
    case FORM_VALUE:
        outStream << '"' << getStr() << '"';
        break;
    case FEATURES_VALUE:
        getFeatures()->flatPrint(outStream);
        break;
    case LIST_FEATURES_VALUE:
        getListFeatures()->flatPrint(outStream);
        break;
    case PAIRP_VALUE:
        getPairp()->flatPrint(outStream, true);
        break;
    }
}

/* **************************************************
 *
 ************************************************** */
void Value::makeSerialString()
{
    switch (type)
    {
    case NIL_VALUE:
        serialString = '\0';
        break;
    case TRUE_VALUE:
        serialString = '\1';
        break;
    case FALSE_VALUE:
        serialString = '\2';
        break;
    case CONSTANT_VALUE:
        serialString = bits->peekSerialString();
        break;
    case VARIABLE_VALUE:
        serialString = '\3' + bits->peekSerialString();
        break;
    case ANONYMOUS_VALUE:
        serialString = '\4';
        break;
    case IDENTIFIER_VALUE:
        serialString = std::to_string(code);
        break;
    case NUMBER_VALUE:
        serialString = std::to_string(number);
        break;
    case FORM_VALUE:
        serialString = str;
        break;
    case FEATURES_VALUE:
        serialString = getFeatures()->peekSerialString();
        break;
    case LIST_FEATURES_VALUE:
        serialString = getListFeatures()->peekSerialString();
        break;
    case PAIRP_VALUE:
        serialString = getPairp()->peekSerialString();
        break;
    }
}

#ifdef OUTPUT_XML
/* **************************************************
 *
 *************************************************!* */
void Value::toXML(xmlNodePtr nodeRoot) const
{
    xmlNodePtr v = xmlNewChild(nodeRoot, NULL, (const xmlChar *)"VAL", NULL);
    switch (type)
    {
    case NIL_VALUE:
        xmlSetProp(v, (xmlChar *)"type", (const xmlChar *)"nil");
        bits->toXML(v);
        break;
    case TRUE_VALUE:
        xmlSetProp(v, (xmlChar *)"type", (const xmlChar *)"true");
        bits->toXML(v);
        break;
    case FALSE_VALUE:
        xmlSetProp(v, (xmlChar *)"type", (const xmlChar *)"false");
        bits->toXML(v);
        break;
    case CONSTANT_VALUE:
        xmlSetProp(v, (xmlChar *)"type", (const xmlChar *)"constant");
        bits->toXML(v);
        break;
    case VARIABLE_VALUE:
        xmlSetProp(v, (xmlChar *)"type", (const xmlChar *)"variable");
        bits->toXML(v);
        break;
    case ANONYMOUS_VALUE:
        xmlSetProp(v, (xmlChar *)"type", (const xmlChar *)"anonymous");
        bits->toXML(v);
        break;
    case IDENTIFIER_VALUE:
        xmlSetProp(v, (xmlChar *)"type", (const xmlChar *)"identifier");
        xmlNewChild(v, NULL, (const xmlChar *)"VAL", (const xmlChar *)Vartable::codeToString(getCode()).c_str());
        break;
    case NUMBER_VALUE:
        xmlSetProp(v, (xmlChar *)"type", (const xmlChar *)"double");
        xmlSetProp(v, (xmlChar *)"value", (const xmlChar *)std::to_string(number).c_str());
        break;
    case FORM_VALUE:
        xmlSetProp(v, (xmlChar *)"type", (const xmlChar *)"form");
        xmlNewChild(v, NULL, (const xmlChar *)"VAL", (const xmlChar *)getStr().c_str());
        break;
    case FEATURES_VALUE:
        xmlSetProp(v, (xmlChar *)"type", (const xmlChar *)"fs");
        getFeatures()->toXML(v);
        break;
    case LIST_FEATURES_VALUE:
        xmlSetProp(v, (xmlChar *)"type", (const xmlChar *)"lfs");
        getListFeatures()->toXML(v);
        break;
    case PAIRP_VALUE:
        xmlSetProp(v, (xmlChar *)"type", (const xmlChar *)"list");
        getPairp()->toXML(v);
        break;
    }
}
#endif

/* **************************************************
 *
 ************************************************** */
valuePtr Value::clone()
{
    valuePtr result = valuePtr();
    switch (type)
    {
    case NIL_VALUE:
    case TRUE_VALUE:
    case FALSE_VALUE:
    case CONSTANT_VALUE:
    case IDENTIFIER_VALUE:
    case FORM_VALUE:
    case NUMBER_VALUE:
    case ANONYMOUS_VALUE:
        result = shared_from_this();
        break;
    case FEATURES_VALUE:
        result = Value::create(getFeatures()->clone());
        break;
    case LIST_FEATURES_VALUE:
        result = Value::create(getListFeatures()->clone());
        break;
    case PAIRP_VALUE:
        result = Value::create(getPairp()->clone());
        break;
    case VARIABLE_VALUE:
        result = Value::create(VARIABLE_VALUE, bits);
        break;
    }
    return result;
}

/* ************************************************************
 *
 ************************************************************ */
bool Value::buildEnvironment(statementPtr from, const environmentPtr &environment, const valuePtr &value, bool acceptToFilterNULLVariables, bool root)
{
#ifdef TRACE_BUILD_ENVIRONMENT
    COUT_LINE;
    std::cout << "<H4>Value::buildEnvironment</H4>" << std::endl;
    std::cout << "<table border=\"1\"><tr><th>this</th><th>value</th><th>Environment</th></tr>";
    std::cout << "<tr><td>";
    this->print(std::cout);
    std::cout << "</td><td>";
    if (value)
      value->print(std::cout);
    else
      std::cout << "NULL";
    std::cout << "</td><td>";
    environment->print(std::cout);
    std::cout << "</td></tr></table>";
#endif

    bool ret = true;
    switch (type)
    {

    case LIST_FEATURES_VALUE:
    case TRUE_VALUE:
    case FALSE_VALUE:
        FATAL_ERROR_UNEXPECTED

    case NIL_VALUE:
        if (value->type == VARIABLE_VALUE)
        {
            environment->add(from, value->bits, shared_from_this());
        }
        else if (value->type == NIL_VALUE)
        {
        }
        else if (value->type == ANONYMOUS_VALUE)
        {
        }
        else
        {
            ret = false;
        }
        break;

    case FEATURES_VALUE:
        if (value->type == VARIABLE_VALUE)
        {
            environment->add(from, value->bits, shared_from_this());
        }
        else if (value->type == FEATURES_VALUE)
        {
            if (!this->getFeatures()->buildEnvironment(from, environment, value->getFeatures(),
                                                       acceptToFilterNULLVariables
#ifdef TRACE_BUILD_ENVIRONMENT
                                                , true
#endif
            ))
                ret = false;
        }
        else if (value->type == ANONYMOUS_VALUE)
        {
            if (!this->getFeatures()->buildEnvironment(from, environment, Features::create(),
                                                       acceptToFilterNULLVariables
#ifdef TRACE_BUILD_ENVIRONMENT
                                                , root
#endif
))
                ret = false;
        }
        else
        {
            ret = false;
        }
        break;

    case CONSTANT_VALUE:
        if (value->type == VARIABLE_VALUE)
        {
            environment->add(from, value->bits, shared_from_this());
        }
        else if (value->type == CONSTANT_VALUE)
        {
            if ((*bits & *value->bits).none())
                ret = false;
        }
        else if (value->type == IDENTIFIER_VALUE)
        {
            if (bits->toString() != Vartable::codeToString(value->getCode()))
                ret = false;
        }
        else if (value->type == ANONYMOUS_VALUE)
        {
        }
        else
        {
            ret = false;
        }
        break;

    case IDENTIFIER_VALUE:
        if (value->type == VARIABLE_VALUE)
        {
            environment->add(from, value->bits, shared_from_this());
        }
        else if (value->type == CONSTANT_VALUE)
        {
            if (Vartable::codeToString(code) != value->bits->toString())
                ret = false;
        }
        else if (value->type == IDENTIFIER_VALUE)
        {
            if (code != value->getCode())
                ret = false;
        }
        else if (value->type == ANONYMOUS_VALUE)
        {
        }
        else
        {
            ret = false;
        }
        break;

    case NUMBER_VALUE:
        if (value->type == VARIABLE_VALUE)
        {
            environment->add(from, value->bits, shared_from_this());
        }
        else if (value->type == NUMBER_VALUE)
        {
            if (number != value->number)
            {
                ret = false;
            }
        }
        else if (value->type == ANONYMOUS_VALUE)
        {
        }
        else
        {
            ret = false;
        }
        break;

    case FORM_VALUE:
        if (value->type == VARIABLE_VALUE)
        {
            environment->add(from, value->bits, shared_from_this());
        }
        else if (value->type == FORM_VALUE)
        {
            if (getStr() != value->getStr())
            {
                ret = false;
            }
        }
        else if (value->type == ANONYMOUS_VALUE)
        {
        }
        else
        {
            ret = false;
        }
        break;

    case PAIRP_VALUE:
        if (value->type == PAIRP_VALUE)
        {
            if (!this->getPairp()->buildEnvironment(from, environment, value->getPairp(),
                                                    acceptToFilterNULLVariables,
                                                    root))
                ret = false;
        }
        else if (value->type == VARIABLE_VALUE)
        {
            environment->add(from, value->bits, shared_from_this());
        }
        else if (value->type == ANONYMOUS_VALUE)
        {
        }
        else
        {
            ret = false;
        }
        break;

    case VARIABLE_VALUE:
        if (!value)
        {
            ret = environment->add(from, this->bits, STATIC_NIL);
        }
        else
        {
            ret = environment->add(from, this->bits, value);
        }
        break;

    case ANONYMOUS_VALUE:
        break;
    }
#ifdef TRACE_BUILD_ENVIRONMENT
         std::cout << "<H4>Result Value::buildEnvironment</H4>" << std::endl;
         std::cout << "<table border=\"1\"><tr><th>R&eacute;sultat</th><th>Environment</th></tr>";
         std::cout << "<tr><td>" << (ret?"TRUE":"FALSE") << "</td><td>";
         environment->print(std::cout);
         std::cout << "</td></tr></table>";
#endif
    return ret;
}

/* ************************************************************
 * this ⊂ o
 ************************************************************ */
bool Value::subsumes(statementPtr from, const valuePtr &o, const environmentPtr &environment)
{
    bool ret = true;
#ifdef TRACE_BUILD_ENVIRONMENT
        COUT_LINE;
        std::cout << "<DIV>";
        std::cout << "Value::subsumes (" << this << ")";
        std::cout << "<TABLE><TR>";
        std::cout << "<TD>";
        this->print(std::cout);
        std::cout << "</TD>&lt;<TD>";
        o->print(std::cout);
        std::cout << "</TD>";
        std::cout << "</TR></TABLE>";
        std::cout << "</DIV>";
#endif

    // $X ⊂ …
    if (this->isVariable())
    {
        environment->add(from, bits, o);
    }

    // … ⊂ $X
    else if (o->isVariable())
    {
        environment->add(from, o->bits, shared_from_this());
    }

    // _ ⊂ …
    else if (this->isAnonymous())
    {
    }

    // … ⊂ _
    else if (o->isAnonymous())
    {
    }

    // NIL ⊂ NIL
    //else if (isNil() && o->isNil())
    //{
    //}

    // NIL ⊂ …
    // … ⊂ NIL
    //else if (isNil() || o->isNil())
    //{
    //}

    // TRUE ⊂ TRUE
    //else if (isTrue() && o->isTrue())
    //{
    //}

    // TRUE ⊂ …
    // … ⊂ TRUE
    //else if (isTrue() || o->isTrue())
    //{
    //    ret = false;
    //}

    else if ((type != o->type))
    {
        //std::cout << type << " " << o->type << std::endl;
        //FATAL_ERROR_UNEXPECTED;
        ret = false;
    }

    else
    {
        switch (o->type)
        {
        // a ⊂ a
        case IDENTIFIER_VALUE:
            if (code != o->getCode())
                ret = false;
            break;
        case NUMBER_VALUE:
            if (number != o->number)
                ret = false;
            break;
        case CONSTANT_VALUE:
            if ((*bits & *o->bits).none())
                ret = false;
            break;
        case FORM_VALUE:
            if (getStr() != o->getStr())
                ret = false;
            break;
        case FEATURES_VALUE:
            ret = getFeatures()->subsumes(from, o->getFeatures(), environment);
            break;
        case PAIRP_VALUE:
            ret = getPairp()->subsumes(from, o->getPairp(), environment);
            break;

        default:
            FATAL_ERROR_UNEXPECTED
        }
    }
#ifdef TRACE_BUILD_ENVIRONMENT
        std::cout << "<DIV>";
        std::cout << "result: (" << shared_from_this() << ")";
        std::cout << "</DIV>";
#endif
    return ret;
}

/* ************************************************************
 *
 ************************************************************ */
bool Value::eq(valuePtr o) const
{
    /* **
        CERR_LINE;
        this->flatPrint(std::cerr);
        std::cerr << " == ";
        o->flatPrint(std::cerr);
        std::cerr << std::endl;
     ** */

    bool ret = false;

    if (o->isNil() && this->isNil())
        ret = true;

    else if (o->isNil() || this->isNil())
        ret = false;

    if (o->isAnonymous() && this->isAnonymous())
        ret = true;

    else if (o->isAnonymous() || this->isAnonymous())
        ret = false;

    else
    {
        switch (o->type)
        {
        case IDENTIFIER_VALUE:
            if ((type == IDENTIFIER_VALUE) && ((code == o->getCode())))
                ret = true;
            break;
        case CONSTANT_VALUE:
            if ((type == CONSTANT_VALUE) && ((*bits & *o->bits).any()))
                ret = true;
            else if ((type == IDENTIFIER_VALUE) && (o->bits->toString() == Vartable::codeToString(code)))
                ret = true;
            break;
        case FORM_VALUE:
            if ((type == FORM_VALUE) && (getStr() == o->getStr()))
                ret = true;
            break;
        case NUMBER_VALUE:
            if ((type == NUMBER_VALUE) && (number == o->number))
                ret = true;
            break;
        case FEATURES_VALUE:
            if ((type == FEATURES_VALUE) &&
                (getFeatures()->peekSerialString() == o->getFeatures()->peekSerialString()))
                ret = true;
            break;
        case PAIRP_VALUE:
            if ((type == PAIRP_VALUE) &&
                (getPairp()->peekSerialString() == o->getPairp()->peekSerialString()))
                ret = true;
            break;
        default:
            FATAL_ERROR_UNEXPECTED
        }
    }
    /*
        CERR_LINE;
        std::cerr << ret << std::endl;
    */
    return ret;
}

/* ************************************************************
 *
 ************************************************************ */
bool Value::lt(const valuePtr &o) const
{
    // bool ret = false;
    /***
        STD::CERR_LINE;
        this->print(std::cerr);
        std::cerr << " < ";
        o->print(std::cerr);
        std::cerr << std::endl;
    ***/
    if (isNumber() && o->isNumber())
        return (number < o->getNumber());
    else
        FATAL_ERROR_UNEXPECTED
    // return ret;
}

/* ************************************************************
 *
 ************************************************************ */
void Value::deleteAnonymousVariables()
{
    switch (type)
    {
    case NIL_VALUE:
    case TRUE_VALUE:
    case FALSE_VALUE:
    case IDENTIFIER_VALUE:
    case CONSTANT_VALUE:
    case FORM_VALUE:
    case VARIABLE_VALUE:
    case ANONYMOUS_VALUE:
    case NUMBER_VALUE:
    case LIST_FEATURES_VALUE:
        break;
    case FEATURES_VALUE:
        getFeatures()->deleteAnonymousVariables();
        break;
    case PAIRP_VALUE:
        getPairp()->deleteAnonymousVariables();
        break;
    }
}

/* ************************************************************
 *
 ************************************************************ */
void Value::deleteVariables()
{
    switch (type)
    {
    case NIL_VALUE:
    case TRUE_VALUE:
    case FALSE_VALUE:
    case IDENTIFIER_VALUE:
    case CONSTANT_VALUE:
    case FORM_VALUE:
    case VARIABLE_VALUE:
    case ANONYMOUS_VALUE:
    case NUMBER_VALUE:
    case LIST_FEATURES_VALUE:
        break;
    case FEATURES_VALUE:
        getFeatures()->deleteVariables();
        break;
    case PAIRP_VALUE:
        getPairp()->deleteVariables();
        break;
    }
}

/* **************************************************
 *
 ************************************************** */
bool Value::renameVariables(size_t i)
{
    bool effect = false;
    switch (type)
    {
    case NIL_VALUE:
    case TRUE_VALUE:
    case FALSE_VALUE:
    case CONSTANT_VALUE:
    case IDENTIFIER_VALUE:
    case FORM_VALUE:
    case NUMBER_VALUE:
    case ANONYMOUS_VALUE:
    case LIST_FEATURES_VALUE:
        break;
    case VARIABLE_VALUE:
    {
        std::ostringstream oss;
        oss << bits->toString() << "_" << i;
        std::string _str = oss.str();
        bitsetPtr variableBits = Vartable::createVariable(_str);
        this->bits = variableBits;
        resetSerial();
        effect = true;
    }
    break;
    case FEATURES_VALUE:
        if (getFeatures())
            if (getFeatures()->renameVariables(i))
                effect = true;
        break;
    case PAIRP_VALUE:
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
void Value::enable(const statementPtr &root, class Item *item, Synthesizer *synthesizer, bool &effect, bool on)
{
    switch (type)
    {
    case NIL_VALUE:
    case TRUE_VALUE:
    case FALSE_VALUE:
    case IDENTIFIER_VALUE:
    case FORM_VALUE:
    case CONSTANT_VALUE:
    case NUMBER_VALUE:
    case ANONYMOUS_VALUE:
    case LIST_FEATURES_VALUE:
        break;
    case VARIABLE_VALUE:
        if (on)
        {
            if ((!item->getEnvironment()) || (!item->getEnvironment()->find(bits)))
            {
                root->addFlags(Flags::DISABLED);
                effect = true;
            }
        }
        else
        {
            root->subFlags(Flags::DISABLED);
            effect = true;
        }
        break;
    case FEATURES_VALUE:
        getFeatures()->enable(root, item, synthesizer, effect, on);
        break;
    case PAIRP_VALUE:
        getPairp()->enable(root, item, synthesizer, effect, on);
        break;
    }
}

/* **************************************************
 *
 ************************************************** */
bool Value::findVariable(const bitsetPtr &variable) const
{
    switch (type)
    {
    case NIL_VALUE:
    case TRUE_VALUE:
    case FALSE_VALUE:
    case IDENTIFIER_VALUE:
    case FORM_VALUE:
    case CONSTANT_VALUE:
    case NUMBER_VALUE:
    case ANONYMOUS_VALUE:
    case LIST_FEATURES_VALUE:
        break;
    case VARIABLE_VALUE:
        if (*bits == *variable)
            return true;
        break;
    case FEATURES_VALUE:
        if (getFeatures()->findVariable(variable))
            return true;
        break;
    case PAIRP_VALUE:
        if (getPairp()->findVariable(variable))
            return true;
        break;
    }
    return false;
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
void Value::apply(statementPtr from, class Item *item, Parser &parser, Synthesizer *synthesizer, const statementPtr &variable,
                  const statementPtr &statement,
                  bool &effect)
{
#ifdef TRACE_BUILD_ENVIRONMENT
        COUT_LINE;
        std::cout << "<DIV>";
        std::cout << "Value::apply ()";
        std::cout << "<TABLE><TR>";
        std::cout << "<TD>";
        this->print(std::cout);
        std::cout << "</TD>";
        std::cout << "</TR></TABLE>";
        std::cout << "</DIV>";
#endif

    switch (type)
    {
    case FEATURES_VALUE:
    {
        if (!item->getEnvironment()){
            item->setEnvironment(Environment::create());
        }
        item->getEnvironment()->add(from, variable->getBits(), shared_from_this());
        bool b = false;
        statement->toggleEnable(statement, item, synthesizer, b, false);
        statement->apply(from, item, parser, synthesizer, effect);
        item->getEnvironment()->remove(variable->getBits());
    }
    break;
    default:
        FATAL_ERROR_UNEXPECTED
    }
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
bool Value::containsVariable()
{
    bool result = false;
    if (variableFlag.containsVariable())
        return true;
    switch (type)
    {
    case NIL_VALUE:
    case TRUE_VALUE:
    case FALSE_VALUE:
    case IDENTIFIER_VALUE:
    case FORM_VALUE:
    case CONSTANT_VALUE:
    case NUMBER_VALUE:
    case ANONYMOUS_VALUE:
    case LIST_FEATURES_VALUE:
        break;
    case VARIABLE_VALUE:
        result = true;
        break;
    case PAIRP_VALUE:
        if (this->getPairp()->containsVariable())
        {
            result = true;
        }
        break;
    case FEATURES_VALUE:
        if (this->getFeatures()->containsVariable())
        {
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
void Value::setVariableFlag(enum VariableFlag::flagValues flag)
{
    this->variableFlag.setFlag(flag);
}
