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

#include <iostream>
#include <utility>
#include "pairp.hpp"
#include "value.hpp"
#include "environment.hpp"
#include "messages.hpp"
#include "shared_ptr.hpp"
#include "statement.hpp"
#include "item.hpp"

pairpPtr Pairp::NIL = Pairp::create();

/* **************************************************
 *
 ************************************************** */
Pairp::Pairp(enum Pairp::Type type, valuePtr _value, pairpPtr _car, pairpPtr _cdr)
{
    NEW;
    this->type = type;
    this->value = _value;
    this->pairp.car = _car;
    this->pairp.cdr = _cdr;
}

/* **************************************************
 *
 ************************************************** */
Pairp::~Pairp()
{
    DELETE;
    if (pairp.car)
        pairp.car.reset();
    if (pairp.cdr)
        pairp.cdr.reset();
}

/* **************************************************
 *
 ************************************************** */
pairpPtr Pairp::create()
{
    return std::make_shared<Pairp>(Pairp::_NIL_);
}

/* **************************************************
 *
 ************************************************** */
pairpPtr Pairp::create(valuePtr value)
{
    return std::make_shared<Pairp>(Pairp::_ATOM_, value);
}

/* **************************************************
 *
 ************************************************** */
pairpPtr Pairp::create(pairpPtr car, pairpPtr cdr)
{
    return std::make_shared<Pairp>(Pairp::_PAIRP_, valuePtr(), car, cdr);
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
Pairp::Type Pairp::getType() const
{
    return type;
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
void Pairp::setType(Type _type)
{
    this->type = _type;
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
valuePtr Pairp::getValue() const
{
    return value;
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
void Pairp::setValue(valuePtr _value)
{
    this->value = _value;
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
pairpPtr Pairp::getCar() const
{
    return this->pairp.car;
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
pairpPtr Pairp::getCdr() const
{
    return pairp.cdr;
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
bool Pairp::isNil() const
{
    return (this->type == Pairp::_NIL_);
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
bool Pairp::isAtom() const
{
    return (this->type == Pairp::_ATOM_);
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
bool Pairp::isVariable() const
{
    return (this->type == Pairp::_ATOM_) && (this->value->isVariable());
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
bool Pairp::isPairp() const
{
    return (this->type == _PAIRP_);
}

/* **************************************************
 *
 ************************************************** */
void Pairp::makeSerialString()
{
    switch (type)
    {
    case _NIL_:
        serialString = '-';
        break;
    case _ATOM_:
        serialString = value->peekSerialString();
        break;
    case _PAIRP_:
        serialString = '-' + pairp.car->peekSerialString();
        if (pairp.cdr->isAtom())
        {
            serialString += '-' + pairp.cdr->peekSerialString();
        }
        else if (pairp.cdr->isNil())
        {
        }
        else
        {
            serialString += '-' + pairp.cdr->peekSerialString();
        }
        serialString += '-';
        break;
    }
}

/* **************************************************
 *
 ************************************************** */
void Pairp::print(std::ostream &outStream) const
{
    switch (type)
    {
    case _NIL_:
        outStream << "<>";
        break;
    case _ATOM_:
        value->print(outStream);
        break;
    case _PAIRP_:
        pairp.car->print(outStream);
        if (pairp.cdr->isAtom())
        {
            outStream << "::";
            pairp.cdr->print(outStream);
        }
        else if (!pairp.cdr->isNil())
        {
            pairp.cdr->print(outStream);
        }
        break;
    }
}

/* **************************************************
 *
 ************************************************** */
void Pairp::flatPrint(std::ostream &outStream, bool par) const
{
    switch (type)
    {
    case _NIL_:
        outStream << "<>";
        break;

    case _ATOM_:
        value->flatPrint(outStream);
        break;

    case _PAIRP_:
        if (par || pairp.cdr->isAtom())
        {
            outStream << '<';
        }
        pairp.car->flatPrint(outStream, true);
        if (pairp.cdr->isAtom())
        {
            outStream << "::";
            pairp.cdr->flatPrint(outStream, true);
        }
        else if (!pairp.cdr->isNil())
        {
            outStream << ",";
            pairp.cdr->flatPrint(outStream, false);
        }
        if (par || pairp.cdr->isAtom())
        {
            outStream << '>';
        }
        break;
    }
}

/* **************************************************
 *
 ************************************************** */
bool Pairp::buildEnvironment(statementPtr statement, const environmentPtr &environment, const pairpPtr &otherPairp, bool acceptToFilterNULLVariables, bool root, bool verbose)
{
    bool ret = true;
#ifdef TRACE_BUILD_ENVIRONMENT
    COUT_LINE;
    std::cout << "<H4>Pairp::buildEnvironment</H4>" << std::endl;
    std::cout << "<table border = \"1\"><tr><th>this</th><th>otherPairp</th><th>Environment</th></tr>";
    std::cout << "<tr><td>";
    this->flatPrint(std::cout, true);
    std::cout << "</td><td>";
    otherPairp->flatPrint(std::cout, true);
    std::cout << "</td><td>";
    environment->print(std::cout);
    std::cout << "</td></tr></table>";
#endif

    switch (this->type)
    {

    case _NIL_:
        if (otherPairp->isNil())
        {
            ret = true;
        }
        else if ((otherPairp->isAtom()) && (otherPairp->value->isVariable()))
        {
            environment->add(statement, otherPairp->value->getCode(), Value::STATIC_NIL, verbose);
        }
        else
        {
            ret = false;
        }
        break;

    case _ATOM_:
        if (this->value->isVariable())
        {
            if (!otherPairp)
            {
                FATAL_ERROR_UNEXPECTED
            }
            else
            {
                switch (otherPairp->getType())
                {
                case _NIL_:
                    environment->add(statement, this->value->getCode(), Value::STATIC_NIL, verbose);
                    break;
                case _ATOM_:
                    environment->add(statement, this->value->getCode(), otherPairp->getValue(), verbose);
                    break;
                case _PAIRP_:
                    environment->add(statement, this->value->getCode(), Value::createPairp(otherPairp), verbose);
                    break;
                }
            }
        }
        else if (otherPairp->isNil())
        {
            FATAL_ERROR_UNEXPECTED;
        }
        else if (!otherPairp)
        {
            ret = false;
        }
        else if (otherPairp->isAtom())
        {
            if (otherPairp->value->isVariable())
                environment->add(statement, otherPairp->value->getCode(), this->getValue(), verbose);
            else if (!this->value->buildEnvironment(statement, environment, otherPairp->value, acceptToFilterNULLVariables,
                                                    root, verbose))
                ret = false;
        }
        else
            ret = false;
        break;

    case _PAIRP_:
        if (otherPairp->isPairp())
        {
            if ((this->pairp.car->isNil()) && (otherPairp->pairp.car->isNil()))
            {
                ret = true;
            }
            else if (!this->pairp.car->buildEnvironment(statement, environment, otherPairp->pairp.car,
                                                        acceptToFilterNULLVariables, root, verbose))
            {
                ret = false;
            }
            else if ((this->pairp.cdr->isNil()) && (otherPairp->pairp.cdr->isNil()))
            {
                ret = true;
            }
            else if (!this->pairp.cdr->buildEnvironment(statement, environment, otherPairp->pairp.cdr,
                                                        acceptToFilterNULLVariables, root, verbose))
            {
                ret = false;
            }
        }
        else if (otherPairp->isNil())
        {
            if ((this->pairp.car->isNil()))
            {
                ret = true;
            }
            else if (!this->pairp.car->buildEnvironment(statement, environment, otherPairp,
                                                        acceptToFilterNULLVariables, root, verbose))
            {
                ret = false;
            }
            ret = true;
        }
        else if (otherPairp->isAtom())
        {
            FATAL_ERROR_UNEXPECTED;
        }
        else
            ret = false;
        break;
    }

#ifdef TRACE_BUILD_ENVIRONMENT
    std::cout << "<H4>Result Pairp::buildEnvironment</H4>" << std::endl;
    std::cout << "<table border = \"1\"><tr><th>R&eacute;sultat</th><th>Environment</th></tr>";
    std::cout << "<tr><td>" << (ret ? "TRUE" : "FALSE") << "</td><td>";
    environment->print(std::cout);
    std::cout << "</td></tr></table>";
#endif
    return ret;
}

/* **************************************************
 *
 ************************************************** */
void Pairp::deleteAnonymousVariables()
{
    switch (type)
    {
    case _NIL_:
        break;
    case _ATOM_:
        if (value)
            value->deleteAnonymousVariables();
        break;
    case _PAIRP_:
        pairp.car->deleteAnonymousVariables();
        pairp.cdr->deleteAnonymousVariables();
        break;
    }
}

/* **************************************************
 *
 ************************************************** */
void Pairp::deleteVariables()
{
    switch (type)
    {
    case _NIL_:
        break;
    case _ATOM_:
        if (value)
            value->deleteVariables();
        break;
    case _PAIRP_:
        pairp.car->deleteVariables();
        pairp.cdr->deleteVariables();
        break;
    }
}

/* **************************************************
 *
 ************************************************** */
bool Pairp::renameVariables(uint32_t code)
{
    bool effect = false;
    switch (type)
    {
    case _NIL_:
        break;
    case _ATOM_:
        if (value)
            if (value->renameVariables(code))
                effect = true;
        break;
    case _PAIRP_:
        if (pairp.car->renameVariables(code))
            effect = true;
        if (pairp.cdr->renameVariables(code))
            effect = true;
        break;
    }
    resetSerial();
    return effect;
}

#ifdef OUTPUT_XML
/* ************************************************************
 *                                                            *
 ************************************************************ */
void Pairp::toXML(xmlNodePtr nodeRoot)
{
    xmlNodePtr l = xmlNewChild(nodeRoot, NULL, (const xmlChar *)"LIST", NULL);
    switch (type)
    {
    case _NIL_:
        break;
    case _ATOM_:
        value->toXML(l);
        break;
    case _PAIRP_:
        pairp.car->toXML(l);
        pairp.cdr->toXML(l);
        break;
    }
}
#endif

/* **************************************************
 *
 ************************************************** */
pairpPtr Pairp::clone() const
{
    switch (type)
    {
    case _NIL_:
        return NIL;
    case _ATOM_:
        if (value)
            return create(value->clone());
        break;
    case _PAIRP_:
        return create(pairp.car->clone(), pairp.cdr->clone());
    }
    return pairpPtr();
}

/* ************************************************************
 * this < o
 ************************************************************ */
bool Pairp::subsumes(statementPtr from, const pairpPtr &o, const environmentPtr &environment, bool verbose)
{
    /***
     COUT_LINE;
     this->print(std::cout);
     std::cout << " ";
     o->print(std::cout);
     std::cout << std::endl;
     ***/
    switch (type)
    {
    // NIL < L
    case _NIL_:
        if (o->getType() != _NIL_)
            return false;
        break;
        // atom < L
    case _ATOM_:
        if (o->getType() != _ATOM_)
            return false;
        else if (!value->subsumes(from, o->getValue(), environment, verbose))
            return false;
        break;
        // (a1::a2) < L
    case _PAIRP_:
        if (o->getType() != _PAIRP_)
            return false;
        else if (!pairp.car->subsumes(from, o->pairp.car, environment, verbose))
            return false;
        else if (!pairp.cdr->subsumes(from, o->pairp.cdr, environment, verbose))
            return false;
        break;
    }
    return true;
}

/* **************************************************
 *
 ************************************************** */
pairpPtr Pairp::pushFront(valuePtr _value)
{
    switch (type)
    {
    case _NIL_:
        WARNING("pushFront fails")
        break;
    case _ATOM_:
        WARNING("pushFront fails")
        break;
    case _PAIRP_:
    {
        pairpPtr n = create(create(_value), shared_from_this());
        return n;
    }
    }
    return pairpPtr();
}

/* **************************************************
 *
 ************************************************** */
pairpPtr Pairp::pushBack(valuePtr _value)
{
    switch (type)
    {
    case _NIL_:
        WARNING("pushBack fails")
        break;
    case _ATOM_:
        WARNING("pushBack fails")
        break;
    case _PAIRP_:
    {
        pairpPtr m = this->clone();
        pairpPtr n = m;
        while (n->pairp.cdr != Pairp::NIL)
            n = n->pairp.cdr;
        n->pairp.cdr = create(create(_value), Pairp::NIL);
        return m;
    }
    }
    return pairpPtr();
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
void Pairp::enable(const statementPtr &root, class Item *item, Generator *generator, bool &effect, bool on)
{
    switch (type)
    {
    case _NIL_:
        break;
    case _ATOM_:
        value->enable(root, item, generator, effect, on);
        break;
    case _PAIRP_:
        if (pairp.car)
            pairp.car->enable(root, item, generator, effect, on);
        if (pairp.cdr)
            pairp.cdr->enable(root, item, generator, effect, on);
        break;
    }
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
bool Pairp::findVariable(uint32_t key) const
{
    switch (type)
    {
    case _NIL_:
        break;
    case _ATOM_:
        if (value->findVariable(key))
            return true;
        break;
    case _PAIRP_:
        if (pairp.car && pairp.car->findVariable(key))
            return true;
        if (pairp.cdr && pairp.cdr->findVariable(key))
            return true;
        break;
    }
    return false;
}

/* ************************************************************
 *                                                            *
 ************************************************************ */
void Pairp::apply(statementPtr from, class Item *item, class Parser &parser, class Generator *generator, uint32_t code, statementPtr statement,
                  bool &effect, bool verbose)
{
    switch (type)
    {
    case _NIL_:
        break;
    case _ATOM_:
    {
        environmentPtr save = item->getEnvironment();
        item->setEnvironment(item->getEnvironment() ? item->getEnvironment()->clone(nullptr, verbose) : environmentPtr());
        value->apply(from, item, parser, generator, code, statement->clone(0), effect, verbose);
        item->getEnvironment().reset();
        item->setEnvironment(save);
    }
    break;
    case _PAIRP_:
        if (pairp.car)
            pairp.car->apply(from, item, parser, generator, code, statement, effect, verbose);
        if (pairp.cdr)
            pairp.cdr->apply(from, item, parser, generator, code, statement, effect, verbose);
        break;
    }
}

/* **************************************************
 *
 ************************************************** */
bool Pairp::containsVariable()
{
    /***
     std::cout << "<H4>Pairp::containsVariable</H4>" << std::endl;
     std::cout << "<table border = \"1\"><tr><th>this</th></tr>";
     std::cout << "<tr><td>";
     this->flatPrint(std::cout, true);
     std::cout << "</td><td>";
     std::cout << "</td></tr></table>";
     ***/
    if (this->variableFlag.containsVariable())
        return true;
    bool result = false;
    switch (type)
    {
    case _NIL_:
        result = false;
        break;
    case _ATOM_:
        if (isVariable())
        {
            result = true;
        }
        else if (this->getValue()->getFeatures()->containsVariable())
        {
            result = true;
        }
        else
        {
            result = false;
        }
        break;
    case _PAIRP_:
        if (pairp.car->containsVariable() || pairp.cdr->containsVariable())
        {
            result = true;
        }
        else
        {
            result = false;
        }
        break;
    }
    if (result)
        this->variableFlag.setFlag(VariableFlag::CONTAINS);
    else
        this->variableFlag.setFlag(VariableFlag::DOES_NOT_CONTAIN);
    /***
     std::cout << "<H4>Pairp::containsVariable done</H4>" << std::endl;
     std::cout << (result ? "TRUE" : "FALSE");
     ***/
    return result;
}

/* **************************************************
 *
 ************************************************** */
void Pairp::setVariableFlag(enum VariableFlag::flagValues flag)
{
    this->variableFlag.setFlag(flag);
}
