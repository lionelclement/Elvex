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
#include <utility>
#include <cctype>

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
#include "item.hpp"

valuePtr Value::STATIC_NIL = Value::createStatic(Value::NIL_VALUE);
valuePtr Value::STATIC_TRUE = Value::createStatic(Value::TRUE_VALUE);
valuePtr Value::STATIC_FALSE = Value::createStatic(Value::FALSE_VALUE);
valuePtr Value::STATIC_ANONYMOUS_VARIABLE = Value::createStatic(Value::ANONYMOUS_VARIABLE_VALUE);

namespace
{
    bool isVariableStart(unsigned char c)
    {
        return std::isalpha(c) || c == '_' || c >= 128;
    }

    bool stringContainsVariable(const std::string &data)
    {
        size_t i = 0;

        while (i < data.size())
        {
            if (data[i] != '$')
            {
                ++i;
                continue;
            }

            if (i + 1 >= data.size())
            {
                ++i;
                continue;
            }

            const unsigned char first = static_cast<unsigned char>(data[i + 1]);

            if (isVariableStart(first))
            {
                return true;
            }

            ++i;
        }

        return false;
    }
}

/* **************************************************
 *
 ************************************************** */
Value::Value(Value::Type const type, const std::string &string)
{
    NEW;
    this->type = type;
    this->code = 0;
    this->number = 0;
    if (type == IDENTIFIER_VALUE)
    {
        this->code = Vartable::nameToCode(string);
    }
    else if (type == STRING_VALUE)
    {
        this->string = string;
    }
}

/* **************************************************
 *
 ************************************************** */
Value::Value(Value::Type const type, uint32_t code, double number, bitsetPtr _bits, featuresPtr _features,
             pairpPtr _list /*, listFeaturesPtr _listFeatures*/)
{
    NEW;
    this->type = type;
    this->code = code;
    this->number = number;
    this->bitset = _bits ? _bits : bitsetPtr();
    this->features = _features ? _features : featuresPtr();
    this->pairp = _list ? _list : pairpPtr();
}

/* **************************************************
 *
 ************************************************** */
Value::~Value()
{
    DELETE;
    if (bitset)
        bitset.reset();
    if (features)
        features.reset();
    if (pairp)
        pairp.reset();
    if (statement)
        statement.reset();
}

/* **************************************************
 *
 ************************************************** */
valuePtr Value::createStatic(const enum Type type)
{
    return valuePtr(new Value(type));
}

/* **************************************************
 *
 ************************************************** */
valuePtr Value::createNumber(double number)
{
    return valuePtr(new Value(NUMBER_VALUE, 0, number));
}

/* **************************************************
 *
 ************************************************** */
valuePtr Value::createVariable(uint32_t code)
{
    return valuePtr(new Value(VARIABLE_VALUE, code));
}

/* **************************************************
 *
 ************************************************** */
valuePtr Value::createIdentifier(uint32_t code)
{
    return valuePtr(new Value(IDENTIFIER_VALUE, code));
}

/* **************************************************
 *
 ************************************************** */
valuePtr Value::createIdentifier(const std::string &name)
{
    return valuePtr(new Value(IDENTIFIER_VALUE, Vartable::nameToCode(name)));
}

/* **************************************************
 *
 ************************************************** */
valuePtr Value::createString(const std::string &str)
{
    return valuePtr(new Value(STRING_VALUE, str));
}

/* **************************************************
 *
 ************************************************** */
valuePtr Value::createConstant(bitsetPtr bitset)
{
    return valuePtr(new Value(CONSTANT_VALUE, 0, 0, bitset));
}

/* **************************************************
 *
 ************************************************** */
valuePtr Value::createFeatures(featuresPtr features)
{
    return valuePtr(new Value(Value::FEATURES_VALUE, 0, 0, bitsetPtr(), features));
}

/* **************************************************
 *
 ************************************************** */
valuePtr Value::createPairp(pairpPtr lst)
{
    return valuePtr(new Value(Value::PAIRP_VALUE, 0, 0, bitsetPtr(), featuresPtr(), lst));
}

/* **************************************************
 *
 ************************************************** */
valuePtr Value::createDoubleDown(uint32_t code)
{
    return valuePtr(new Value(Value::SYNTHESIZED_CHILD_FEATURES_VALUE, code));
}

/* **************************************************
 *
 ************************************************** */
valuePtr Value::createStatement(const statementPtr &statement)
{
    valuePtr value = valuePtr(new Value(Value::STATEMENT_VALUE));
    value->statement = statement;
    return value;
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
bitsetPtr Value::getBitset() const
{
    return bitset;
}

/* **************************************************
 *
 ************************************************** */
uint32_t Value::getCode() const
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
double Value::getNumber() const
{
    return number;
}

/* **************************************************
 *
 ************************************************** */
std::string &Value::getString()
{
    return string;
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
statementPtr Value::getStatement() const
{
    return statement;
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
    return ((type == FALSE_VALUE) || (type == NIL_VALUE) || (type == ANONYMOUS_VARIABLE_VALUE));
}

/* **************************************************
 *
 ************************************************** */
bool Value::isAnonymousVariable() const
{
    return type == ANONYMOUS_VARIABLE_VALUE;
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
bool Value::isString() const
{
    return type == STRING_VALUE;
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
bool Value::isSynthesizedChildFeatures() const
{
    return type == SYNTHESIZED_CHILD_FEATURES_VALUE;
}

/* **************************************************
 *
 ************************************************** */
void Value::toHTML(std::ostream &outStream) const
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
        outStream << bitset->toString();
        break;
    case VARIABLE_VALUE:
        outStream << '$' << Vartable::codeToName(code);
        break;
    case ANONYMOUS_VARIABLE_VALUE:
        outStream << '_';
        break;
    case IDENTIFIER_VALUE:
        outStream << Vartable::codeToName(code);
        break;
    case NUMBER_VALUE:
        outStream << number;
        break;
    case STRING_VALUE:
        outStream << string;
        break;
    case FEATURES_VALUE:
        getFeatures()->toHTML(outStream);
        break;
    case PAIRP_VALUE:
        getPairp()->flatPrint(outStream, true);
        break;
    case SYNTHESIZED_CHILD_FEATURES_VALUE:
        outStream << "⇓" << code + 1;
        break;
    case STATEMENT_VALUE:
        getStatement()->toHTML(outStream);
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
        outStream << bitset->toString();
        break;
    case ANONYMOUS_VARIABLE_VALUE:
        outStream << '_';
        break;
    case IDENTIFIER_VALUE:
        outStream << Vartable::codeToName(code);
        break;
    case VARIABLE_VALUE:
        outStream << '$' << Vartable::codeToName(code);
        break;
    case NUMBER_VALUE:
        outStream << number;
        break;
    case STRING_VALUE:
        outStream << '"' << string << '"';
        break;
    case FEATURES_VALUE:
        getFeatures()->flatPrint(outStream);
        break;
    case PAIRP_VALUE:
        getPairp()->flatPrint(outStream, true);
        break;
    case SYNTHESIZED_CHILD_FEATURES_VALUE:
        outStream << "⇓" << code + 1;
        break;
    case STATEMENT_VALUE:
        getStatement()->flatPrint(outStream);
        break;
    }
}

/* **************************************************
 *
 ************************************************** */
void Value::makeCoreSerialString()
{
    switch (type)
    {
    case NIL_VALUE:
        coreSerialString = 'a';
        break;
    case TRUE_VALUE:
        coreSerialString = 'b';
        break;
    case FALSE_VALUE:
        coreSerialString = 'c';
        break;
    case ANONYMOUS_VARIABLE_VALUE:
        coreSerialString = 'd';
        break;
    case CONSTANT_VALUE:
        coreSerialString = 'e' + bitset->peekCoreSerialString();
        break;
    case VARIABLE_VALUE:
        coreSerialString = 'f' + std::to_string(code);
        break;
    case IDENTIFIER_VALUE:
        coreSerialString = 'g' + std::to_string(code);
        break;
    case NUMBER_VALUE:
        coreSerialString = 'h' + std::to_string(number);
        break;
    case STRING_VALUE:
        coreSerialString = 'i' + string;
        break;
    case FEATURES_VALUE:
        coreSerialString = 'j' + getFeatures()->peekCoreSerialString();
        break;
    case PAIRP_VALUE:
        coreSerialString = 'l' + getPairp()->peekCoreSerialString();
        break;
    case SYNTHESIZED_CHILD_FEATURES_VALUE:
        coreSerialString = 'n' + std::to_string(code);
        break;
    case STATEMENT_VALUE:
        coreSerialString = 'o' + (getStatement() ? getStatement()->peekCoreSerialString() : std::string("0"));
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
        break;
    case TRUE_VALUE:
        xmlSetProp(v, (xmlChar *)"type", (const xmlChar *)"true");
        break;
    case FALSE_VALUE:
        xmlSetProp(v, (xmlChar *)"type", (const xmlChar *)"false");
        break;
    case CONSTANT_VALUE:
        xmlSetProp(v, (xmlChar *)"type", (const xmlChar *)"constant");
        bitset->toXML(v);
        break;
    case VARIABLE_VALUE:
        xmlSetProp(v, (xmlChar *)"type", (const xmlChar *)"variable");
        xmlNewChild(v, NULL, (const xmlChar *)"VAL", (const xmlChar *)Vartable::codeToName(getCode()).c_str());
        break;
    case ANONYMOUS_VARIABLE_VALUE:
        xmlSetProp(v, (xmlChar *)"type", (const xmlChar *)"anonymous");
        break;
    case IDENTIFIER_VALUE:
        xmlSetProp(v, (xmlChar *)"type", (const xmlChar *)"identifier");
        xmlNewChild(v, NULL, (const xmlChar *)"VAL", (const xmlChar *)Vartable::codeToName(getCode()).c_str());
        break;
    case NUMBER_VALUE:
        xmlSetProp(v, (xmlChar *)"type", (const xmlChar *)"double");
        xmlSetProp(v, (xmlChar *)"value", (const xmlChar *)std::to_string(number).c_str());
        break;
    case STRING_VALUE:
        xmlSetProp(v, (xmlChar *)"type", (const xmlChar *)"string");
        xmlNewChild(v, NULL, (const xmlChar *)"VAL", (const xmlChar *)string.c_str());
        break;
    case FEATURES_VALUE:
        xmlSetProp(v, (xmlChar *)"type", (const xmlChar *)"fs");
        getFeatures()->toXML(v);
        break;
    case PAIRP_VALUE:
        xmlSetProp(v, (xmlChar *)"type", (const xmlChar *)"list");
        getPairp()->toXML(v);
        break;
    case SYNTHESIZED_CHILD_FEATURES_VALUE:
        xmlSetProp(v, (xmlChar *)"type", (const xmlChar *)"down2");
        xmlNewChild(v, NULL, (const xmlChar *)"VAL", (const xmlChar *)Vartable::codeToName(getCode()).c_str());
        break;

    case STATEMENT_VALUE:
        xmlSetProp(v, (xmlChar *)"type", (const xmlChar *)"statement");
        getStatement()->toXML(v);
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
    case ANONYMOUS_VARIABLE_VALUE:
        result = shared_from_this();
        break;

    case CONSTANT_VALUE:
        result = Value::createConstant(bitset);
        break;

    case IDENTIFIER_VALUE:
        result = Value::createIdentifier(code);
        break;

    case STRING_VALUE:
        result = Value::createString(string);
        break;

    case NUMBER_VALUE:
        result = Value::createNumber(number);
        break;

    case FEATURES_VALUE:
        result = Value::createFeatures(getFeatures()->clone());
        break;

    case PAIRP_VALUE:
        result = Value::createPairp(getPairp()->clone());
        break;

    case VARIABLE_VALUE:
        result = Value::createVariable(code);
        break;

    case SYNTHESIZED_CHILD_FEATURES_VALUE:
        result = Value::createDoubleDown(code);
        break;

    case STATEMENT_VALUE:
        result = Value::createStatement(getStatement() ? getStatement()->clone() : statementPtr());
        break;
    }
    return result;
}

/* ************************************************************
 *
 ************************************************************ */
bool Value::buildEnvironment(statementPtr statementRoot, const environmentPtr &environment, const valuePtr &value, bool acceptToFilterNULLVariables, bool root, bool verbose)
{
#ifdef TRACE_BUILD_ENVIRONMENT
    COUT_LINE;
    std::cout << "<H4>Value::buildEnvironment</H4>" << std::endl;
    std::cout << "<table border=\"1\"><tr><th>this</th><th>value</th><th>Environment</th></tr>";
    std::cout << "<tr><td>";
    this->toHTML(std::cout);
    std::cout << "</td><td>";
    if (value)
        value->toHTML(std::cout);
    else
        std::cout << "NULL";
    std::cout << "</td><td>";
    environment->toHTML(std::cout);
    std::cout << "</td></tr></table>";
#endif

    bool ret = true;
    switch (type)
    {

    case TRUE_VALUE:
    case FALSE_VALUE:
    case SYNTHESIZED_CHILD_FEATURES_VALUE:
        FATAL_ERROR_UNEXPECTED

    case NIL_VALUE:
        if (value->type == VARIABLE_VALUE)
        {
            environment->add(statementRoot, value->code, shared_from_this(), verbose);
        }
        else if (value->type == NIL_VALUE)
        {
        }
        else if (value->type == ANONYMOUS_VARIABLE_VALUE)
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
            environment->add(statementRoot, value->code, shared_from_this(), verbose);
        }
        else if (value->type == FEATURES_VALUE)
        {
            if (!this->getFeatures()->buildEnvironment(statementRoot, environment, value->getFeatures(),
                                                       acceptToFilterNULLVariables
#ifdef TRACE_BUILD_ENVIRONMENT
                                                       ,
                                                       true
#endif
                                                       ,
                                                       verbose))
                ret = false;
        }
        else if (value->type == ANONYMOUS_VARIABLE_VALUE)
        {
            if (!this->getFeatures()->buildEnvironment(statementRoot, environment, Features::create(),
                                                       acceptToFilterNULLVariables
#ifdef TRACE_BUILD_ENVIRONMENT
                                                       ,
                                                       root
#endif
                                                       ,
                                                       verbose))
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
            environment->add(statementRoot, value->code, shared_from_this(), verbose);
        }
        else if (value->type == CONSTANT_VALUE)
        {
            if ((*bitset & *value->bitset).none())
                ret = false;
        }
        else if (value->type == IDENTIFIER_VALUE)
        {
            if (bitset->toString() != Vartable::codeToName(value->getCode()))
                ret = false;
        }
        else if (value->type == ANONYMOUS_VARIABLE_VALUE)
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
            environment->add(statementRoot, value->code, shared_from_this(), verbose);
        }
        else if (value->type == CONSTANT_VALUE)
        {
            if (Vartable::codeToName(code) != value->bitset->toString())
                ret = false;
        }
        else if (value->type == IDENTIFIER_VALUE)
        {
            if (code != value->getCode())
                ret = false;
        }
        else if (value->type == ANONYMOUS_VARIABLE_VALUE)
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
            environment->add(statementRoot, value->code, shared_from_this(), verbose);
        }
        else if (value->type == NUMBER_VALUE)
        {
            if (number != value->number)
            {
                ret = false;
            }
        }
        else if (value->type == ANONYMOUS_VARIABLE_VALUE)
        {
        }
        else
        {
            ret = false;
        }
        break;

    case STRING_VALUE:
        if (value->type == VARIABLE_VALUE)
        {
            environment->add(statementRoot, value->code, shared_from_this(), verbose);
        }
        else if (value->type == STRING_VALUE)
        {
            if (string != value->string)
            {
                ret = false;
            }
        }
        else if (value->type == ANONYMOUS_VARIABLE_VALUE)
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
            if (!pairp->buildEnvironment(statementRoot, environment, value->getPairp(),
                                         acceptToFilterNULLVariables,
                                         root, verbose))
                ret = false;
        }
        else if (value->type == VARIABLE_VALUE)
        {
            environment->add(statementRoot, value->code, shared_from_this(), verbose);
        }
        else if (value->type == ANONYMOUS_VARIABLE_VALUE)
        {
            if (!pairp->buildEnvironment(statementRoot, environment, Pairp::NIL,
                                         acceptToFilterNULLVariables,
                                         root, verbose))
                ret = false;
        }
        else
        {
            ret = false;
        }
        break;

    case VARIABLE_VALUE:
        if (!value)
        {
            ret = environment->add(statementRoot, code, STATIC_NIL, verbose);
        }
        else
        {
            ret = environment->add(statementRoot, code, value, verbose);
        }
        break;

    case ANONYMOUS_VARIABLE_VALUE:
        break;

    case STATEMENT_VALUE:
        if (value->type == VARIABLE_VALUE)
        {
            environment->add(statementRoot, value->code, shared_from_this(), verbose);
        }
        else if (value->type == STATEMENT_VALUE)
        {
            if (!getStatement() || !value->getStatement())
            {
                if (getStatement() != value->getStatement())
                    ret = false;
            }
            else if (getStatement()->peekCoreSerialString() !=
                     value->getStatement()->peekCoreSerialString())
            {
                ret = false;
            }
        }
        else if (value->type == ANONYMOUS_VARIABLE_VALUE)
        {
        }
        else
        {
            ret = false;
        }
        break;
    }
#ifdef TRACE_BUILD_ENVIRONMENT
    std::cout << "<H4>Result Value::buildEnvironment</H4>" << std::endl;
    std::cout << "<table border=\"1\"><tr><th>R&eacute;sultat</th><th>Environment</th></tr>";
    std::cout << "<tr><td>" << (ret ? "TRUE" : "FALSE") << "</td><td>";
    environment->toHTML(std::cout);
    std::cout << "</td></tr></table>";
#endif
    return ret;
}

/* ************************************************************
 * this ⊂ o
 ************************************************************ */
bool Value::subsumes(statementPtr statementRoot, const valuePtr &other_value, const environmentPtr &environment, bool verbose)
{
    bool ret = true;
#ifdef TRACE_BUILD_ENVIRONMENT
    COUT_LINE;
    std::cout << "<DIV>";
    std::cout << "Value::subsumes (" << this << ")";
    std::cout << "<TABLE><TR>";
    std::cout << "<TD>";
    this->toHTML(std::cout);
    std::cout << "</TD>&lt;<TD>";
    other_value->toHTML(std::cout);
    std::cout << "</TD>";
    std::cout << "</TR></TABLE>";
    std::cout << "</DIV>";
    std::flush(std::cout);
#endif

    // $X ⊂ …
    if (this->isVariable())
    {
        environment->add(statementRoot, code, other_value, verbose);
    }

    // … ⊂ $X
    else if (other_value->isVariable())
    {
        environment->add(statementRoot, other_value->code, shared_from_this(), verbose);
    }

    // _ ⊂ …
    else if (this->isAnonymousVariable())
    {
    }

    // … ⊂ _
    else if (other_value->isAnonymousVariable())
    {
    }

    else if ((type != other_value->type))
    {
        // std::cout << type << " " << o->type << std::endl;
        // FATAL_ERROR_UNEXPECTED;
        ret = false;
    }

    else
    {
        switch (other_value->type)
        {
        // a ⊂ a
        case IDENTIFIER_VALUE:
            if (code != other_value->getCode())
                ret = false;
            break;
        case NUMBER_VALUE:
            if (number != other_value->number)
                ret = false;
            break;
        case CONSTANT_VALUE:
            if ((*bitset & *other_value->bitset).none())
                ret = false;
            break;
        case STRING_VALUE:
            if (string != other_value->string)
                ret = false;
            break;
        case FEATURES_VALUE:
            ret = getFeatures()->subsumes(statementRoot, other_value->getFeatures(), environment, verbose);
            break;
        case PAIRP_VALUE:
            ret = getPairp()->subsumes(statementRoot, other_value->getPairp(), environment, verbose);
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
 * this == o
 ************************************************************ */
bool Value::equal(valuePtr o) const
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

    else
    {
        switch (o->type)
        {
        case IDENTIFIER_VALUE:
            if ((type == IDENTIFIER_VALUE) && ((code == o->code)))
                ret = true;
            break;
        case CONSTANT_VALUE:
            if ((type == CONSTANT_VALUE) && ((*bitset & *o->bitset).any()))
                ret = true;
            else if ((type == IDENTIFIER_VALUE) && (o->bitset->toString() == Vartable::codeToName(code)))
                ret = true;
            break;
        case STRING_VALUE:
            if ((type == STRING_VALUE) && (string == o->string))
                ret = true;
            break;
        case NUMBER_VALUE:
            if ((type == NUMBER_VALUE) && (number == o->number))
                ret = true;
            break;
        case FEATURES_VALUE:
            if ((type == FEATURES_VALUE) &&
                (getFeatures()->peekCoreSerialString() == o->getFeatures()->peekCoreSerialString()))
                ret = true;
            break;
        case PAIRP_VALUE:
            if ((type == PAIRP_VALUE) &&
                (getPairp()->peekCoreSerialString() == o->getPairp()->peekCoreSerialString()))
                ret = true;
            break;
        case STATEMENT_VALUE:
            if (type == STATEMENT_VALUE)
            {
                if (!getStatement() || !o->getStatement())
                    ret = (getStatement() == o->getStatement());
                else
                    ret = (getStatement()->peekCoreSerialString() ==
                           o->getStatement()->peekCoreSerialString());
            }
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
bool Value::lessThan(const valuePtr &o) const
{
    // bool ret = false;
    /***
        STD::CERR_LINE;
        this->toHTML(std::cerr);
        std::cerr << " < ";
        o->toHTML(std::cerr);
        std::cerr << std::endl;
    ***/
    if (isNumber() && o->isNumber())
        return (number < o->getNumber());
    else
        FATAL_ERROR_UNEXPECTED
    // return ret;
}

/* **************************************************
 *
 ************************************************** */
bool Value::renameVariables(uint32_t key)
{
    bool effect = false;
    switch (type)
    {
    case NIL_VALUE:
    case TRUE_VALUE:
    case FALSE_VALUE:
    case CONSTANT_VALUE:
    case IDENTIFIER_VALUE:
    case NUMBER_VALUE:
    case ANONYMOUS_VARIABLE_VALUE:
    case SYNTHESIZED_CHILD_FEATURES_VALUE:
        break;
    case STRING_VALUE:
        Vartable::renameVariables(string, key);
        resetCoreSerial();
        effect = true;
        break;
    case VARIABLE_VALUE:
        code = Vartable::nameToCode(Vartable::codeToName(code), key);
        resetCoreSerial();
        effect = true;
        break;
    case FEATURES_VALUE:
        if (getFeatures())
            if (getFeatures()->renameVariables(key))
            {
                resetCoreSerial();
                effect = true;
            }
        break;
    case PAIRP_VALUE:
        if (getPairp())
            if (getPairp()->renameVariables(key))
            {
                resetCoreSerial();
                effect = true;
            }
        break;
    case STATEMENT_VALUE:
        if (getStatement())
        {
            getStatement()->renameVariables(key);
            resetCoreSerial();
            effect = true;
        }
        break;
    }
    return effect;
}

/* **************************************************
 *
 ************************************************** */
void Value::testEnable(const statementPtr &root, class Item *item, Generator *synthesizer, bool &effect, bool on)
{
    switch (type)
    {
    case NIL_VALUE:
    case TRUE_VALUE:
    case FALSE_VALUE:
    case IDENTIFIER_VALUE:
    case STRING_VALUE:
    case CONSTANT_VALUE:
    case NUMBER_VALUE:
    case ANONYMOUS_VARIABLE_VALUE:
        break;
    case VARIABLE_VALUE:
        if (on)
        {
            if (!item->environmentGet(code))
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
        getFeatures()->testEnable(root, item, synthesizer, effect, on);
        break;
    case PAIRP_VALUE:
        getPairp()->testEnable(root, item, synthesizer, effect, on);
        break;
    case SYNTHESIZED_CHILD_FEATURES_VALUE:
        if (on)
        {
            if ((*item->getSynthesizedChildFeatures())[code] == Features::NIL)
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
    case STATEMENT_VALUE:
        if (getStatement())
            getStatement()->testEnable(root, item, synthesizer, effect, on);
        break;
    }
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
bool Value::containsVariable()
{
    bool result = false;
    if (isSetFlags(Flags::CONTAINS_VARIABLE))
        return true;
    if (isSetFlags(Flags::DOES_NOT_CONTAIN_VARIABLE))
        return false;
    switch (type)
    {
    case NIL_VALUE:
    case TRUE_VALUE:
    case FALSE_VALUE:
    case IDENTIFIER_VALUE:
    case CONSTANT_VALUE:
    case NUMBER_VALUE:
    case ANONYMOUS_VARIABLE_VALUE:
    case SYNTHESIZED_CHILD_FEATURES_VALUE:
    case STATEMENT_VALUE:
        break;
    case VARIABLE_VALUE:
        result = true;
        break;
        case STRING_VALUE:
        if (stringContainsVariable(string))
        {
            result = true;
        }
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
        addFlags(Flags::CONTAINS_VARIABLE);
    else
        addFlags(Flags::DOES_NOT_CONTAIN_VARIABLE);
    return result;
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
void Value::apply(statementPtr statementRoot, class Item *item, Parser &parser, Generator *synthesizer, uint32_t code,
                  const statementPtr &statement,
                  bool &effect, bool verbose)
{
#ifdef TRACE_BUILD_ENVIRONMENT
    COUT_LINE;
    std::cout << "<DIV>";
    std::cout << "Value::apply ()";
    std::cout << "<TABLE><TR>";
    std::cout << "<TD>";
    this->toHTML(std::cout);
    std::cout << "</TD>";
    std::cout << "</TR></TABLE>";
    std::cout << "</DIV>";
#endif

    switch (type)
    {
    case FEATURES_VALUE:
    {
        item->environmentAdd(statementRoot, code, shared_from_this(), verbose);
        bool b = false;
        statement->testEnable(statement, item, synthesizer, b, false);
        statement->apply(statementRoot, item, parser, synthesizer, effect, true, verbose);
        item->environmentRemove(code);
    }
    break;
    default:
        FATAL_ERROR_UNEXPECTED
    }
}

// /* ************************************************************
//  *                                                            *
//  ************************************************************ */
// bool Value::containsAnonymousVariable()
// {
//     bool result = false;
//     if (isSetFlags(Flags::CONTAINS_ANONYMOUS_VARIABLE))
//         return true;
//     if (isSetFlags(Flags::DOES_NOT_CONTAIN_ANONYMOUS_VARIABLE))
//         return false;
//     switch (type)
//     {
//     case NIL_VALUE:
//     case TRUE_VALUE:
//     case FALSE_VALUE:
//     case IDENTIFIER_VALUE:
//     case FORM_VALUE:
//     case CONSTANT_VALUE:
//     case NUMBER_VALUE:
//     case SYNTHESIZED_CHILD_FEATURES_VALUE:
//     case STATEMENT_VALUE:
//     case VARIABLE_VALUE:
//         break;
//     case ANONYMOUS_VARIABLE_VALUE:
//         result = true;
//         break;
//     case PAIRP_VALUE:
//         if (this->getPairp()->containsAnonymousVariable())
//         {
//             result = true;
//         }
//         break;
//     case FEATURES_VALUE:
//         if (this->getFeatures()->containsAnonymousVariable())
//         {
//             result = true;
//         }
//         break;
//     }
//     if (result)
//         addFlags(Flags::CONTAINS_ANONYMOUS_VARIABLE);
//     else
//         addFlags(Flags::DOES_NOT_CONTAIN_ANONYMOUS_VARIABLE);
//     return result;
// }
