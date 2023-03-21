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
 * LaBRI -- Université Bordeaux
 * 351, cours de la Libération
 * 33405 Talence Cedex - France
 * lionel.clement@u-bordeaux.fr
 *
 * This file is part of ELVEX.
 *
 ************************************************** */

#include <regex>
#include <string>
#include <iostream>
#include <sstream>
#include <list>
#include <utility>
#include "environment.hpp"
#include "messages.hpp"
#include "pairp.hpp"
#include "feature.hpp"
#include "features.hpp"
#include "value.hpp"
#include "shared_ptr.hpp"
#include "listfeatures.hpp"
#include "bitset.hpp"

/* **************************************************
 *
 ************************************************** */
Environment::Environment()
{
    NEW;
}

/* **************************************************
 *
 ************************************************** */
Environment::~Environment()
{
    DELETE;
    for (auto &i : env)
    {
        valuePtr tmp = i.second;
        if (tmp)
            tmp.reset();
    }
}

/* **************************************************
 *
 ************************************************** */
environmentPtr Environment::create()
{
    return environmentPtr(new Environment());
}

/* **************************************************
 *
 ************************************************** */
bool Environment::_add(const std::string &key, valuePtr value)
{
    auto it = env.find(key);
    if (it == env.end())
    {
        env.insert(std::make_pair(key, value));
    }
    else
    {
        if (it->second->isAnonymous()) {
            it->second = value;
        }
        else {
            COUT_LINE;
            std::cout << "*** Error: " << key << " already done !!!" << std::endl;
            it->second->print(std::cout);
            std::cout << std::endl;
            FATAL_ERROR_UNEXPECTED;
            //return false;
            //it->second = value;
        }   
    }
    return true;
}

/* **************************************************
 *
 ************************************************** */
bool Environment::remove(const std::string &key)
{
    return (env.erase(key) > 0);
}

/* **************************************************
 *
 ************************************************** */
bool Environment::_add(const bitsetPtr &attr, valuePtr value)
{
    const std::string key = attr->toString();
    return _add(key, std::move(value));
}

/* **************************************************
 *
 ************************************************** */
bool Environment::_add(const environmentPtr &e)
{
    bool ok = true;
    for (const auto &i : *e)
        ok &= _add(i.first, i.second);
    return ok;
}

/* **************************************************
 *
 ************************************************** */
bool Environment::_add(const environmentPtr &e, const environmentPtr &where)
{
    bool ok = true;
    if (where)
        for (const auto &i : *e)
            if (where->env.find(i.first) != where->env.end())
                ok &= _add(i.first, i.second);
    return ok;
}

/* **************************************************
 *
 ************************************************** */
bool Environment::remove(const bitsetPtr &attr)
{
    const std::string key = attr->toString();
    return remove(key);
}

/* **************************************************
 *
 ************************************************** */
Environment::unordered_map::const_iterator Environment::begin() const
{
    return env.begin();
}

/* **************************************************
 *
 ************************************************** */
Environment::unordered_map::const_iterator Environment::end() const
{
    return env.end();
}

/* **************************************************
 *
 ************************************************** */
size_t Environment::size() const
{
    return env.size();
}

/* **************************************************
 *
 ************************************************** */
valuePtr Environment::find(const bitsetPtr &attr) const
{
    const std::string key = attr->toString();
    auto it = env.find(key);
    if (it != env.end())
        return it->second;
    else
        return valuePtr();
}

/* **************************************************
 *
 ************************************************** */
void Environment::print(std::ostream &out) const
{
    bool first = true;
    out << "<TABLE border=\"1\"><TR>";
    for (auto &i : env)
    {
        if (first)
            first = false;
        else
            out << "</TR><TR>";
        out << "<TD>" << i.first;
        if (i.second)
        {
            out << "</TD><TD>";
            i.second->print(out);
        }
        out << "</TD>";
    }
    out << "</TR></TABLE>";
}

/* **************************************************
 *
 ************************************************** */
void Environment::replaceVariables(const featuresPtr &features, bool &effect)
{
#ifdef TRACE_ENVIRONMENT
     std::cout << "<H4>Environment::replaceVariables(features)</H4>" << std::endl;
     std::cout << "<table border=\"1\"><tr><th>featurePtrs</th><th>Environment</th></tr>";
     std::cout << "<tr><td>";
     features->print(std::cout);
     std::cout << "</td><td>";
     this->print(std::cout);
     std::cout << "</td></tr></table>";
#endif
    if (!features->containsVariable())
        return;

redo:
    for (auto it = features->begin(); it != features->end(); ++it)
    {
        featurePtr feature = *it;
        switch (feature->_getType())
        {
        case Feature::_HEAD_:
        case Feature::_LEMMA_:
            if (feature->getValue())
                replaceVariables(feature->getValue(), effect);
            break;
        case Feature::_FORM_:
        case Feature::_CONSTANT_:
            if (feature->getValue())
            {
                replaceVariables(feature->getValue(), effect);
            }
            break;
        case Feature::_VARIABLE_:
        {
            if (feature->getValue())
            {
                effect = true;
                replaceVariables(feature->getValue(), effect);
            }

            valuePtr value = find(feature->getAttribute());
            if (!value)
            {
                /* do nothing */
            }
            else if (value->isNil())
            {
                /* do nothing */
            }
            else if (value->isFeatures())
            {
                features->erase(it);
                for (const auto &f : *value->getFeatures())
                {
                    features->add(f);
                }
                effect = true;
                goto redo;
            }
            else if (value->isConstant())
            {
                feature->setType(Feature::_CONSTANT_);
                feature->setAttribute(value->getBits());
            }
            else if (value->isAnonymous())
            {
                features->erase(it);
                effect = true;
                goto redo;
            }
            else
            {
                throw fatal_exception("environment: variable substitution failed");
            }
        }
        break;
        }
        features->setVariableFlag(VariableFlag::DOES_NOT_CONTAIN);
    }
#ifdef TRACE_ENVIRONMENT
     std::cout << "<H4>Environment::replaceVariables(features) DONE</H4>" << std::endl;
     std::cout << "<table border=\"1\"><tr><th>Features</th><th>Environment</th></tr>";
     std::cout << "<tr><td>";
     features->print(std::cout);
     std::cout << "</td><td>";
     this->print(std::cout);
     std::cout << "</td></tr></table>";
#endif
    if (effect)
        features->resetSerial();
}

/* **************************************************
 *
 ************************************************** */
void Environment::replaceVariables(const listFeaturesPtr &listFeatures, bool &effect)
{
    for (auto &vf : *listFeatures)
        this->replaceVariables(vf, effect);
}

/* **************************************************
 *
 ************************************************** */
void Environment::replaceVariables(const valuePtr &value, bool &effect)
{
#ifdef TRACE_ENVIRONMENT
     std::cout << "<H4>Environment::replaceVariables(value)</H4>" << std::endl;
     std::cout << "<table border=\"1\"><tr><th>Value</th><th>Environment</th></tr>";
     std::cout << "<tr><td>";
     value->print(std::cout);
     std::cout << "</td><td>";
     this->print(std::cout);
     std::cout << "</td></tr></table>";
#endif
    if (!value->containsVariable())
        return;
    if (!value->isNil() && !value->isAnonymous())
    {
        switch (value->_getType())
        {
        case Value::NIL_VALUE:
        case Value::TRUE_VALUE:
        case Value::FORM_VALUE:
        case Value::CONSTANT_VALUE:
        case Value::IDENTIFIER_VALUE:
        case Value::ANONYMOUS_VALUE:
        case Value::NUMBER_VALUE:
            break;
        case Value::FEATURES_VALUE:
            replaceVariables(value->getFeatures(), effect);
            break;
        case Value::LIST_FEATURES_VALUE:
            replaceVariables(value->getListFeatures(), effect);
            break;
        case Value::PAIRP_VALUE:
            replaceVariables(value->getPairp(), effect);
            break;
        case Value::VARIABLE_VALUE:
            valuePtr val = find(value->getBits());
            if (val && (val != value))
            {
                effect = true;
                *value = *val;
                replaceVariables(value, effect);
            }
            break;
        }
        value->setVariableFlag(VariableFlag::DOES_NOT_CONTAIN);
    }
#ifdef TRACE_ENVIRONMENT
     std::cout << "<H4>Environment::replaceVariables(value) result</H4>" << std::endl;
     std::cout << "<table border=\"1\"><tr><th>Std::List</th></tr>";
     std::cout << "<tr><td>";
     std::cout << "</td></tr></table>";
#endif
    if (effect)
        value->resetSerial();
}

/* **************************************************
 *
 ************************************************** */
void Environment::replaceVariables(const pairpPtr &pairp, bool &effect)
{
#ifdef TRACE_ENVIRONMENT
     std::cout << "<H4>Environment::replaceVariables(list)</H4>" << std::endl;
     std::cout << "<table border=\"1\"><tr><th>List</th><th>Environment</th></tr>";
     std::cout << "<tr><td>";
     pairp->flatPrint(std::cout, 0);
     std::cout << "</td><td>";
     this->print(std::cout);
     std::cout << "</	td></tr></table>";
#endif
    if (!pairp->containsVariable())
        return;
    switch (pairp->getType())
    {
    case Pairp::_ATOM_:
        if (pairp->isVariable())
        {
            valuePtr value = this->find(pairp->getValue()->getBits());
            if (value->isPairp())
            {
                *pairp = *(value->getPairp());
            }
            else if (value->isNil())
            {
                *pairp = *Pairp::NIL;
            }
            else
            {
                pairp->setValue(value);
            }
        }
        else
            // if (list->containsVariable())
            replaceVariables(pairp->getValue(), effect);
        break;

    case Pairp::_PAIRP_:
        // if (list->getCar()->containsVariable())
        replaceVariables(pairp->getCar(), effect);
        // if (list->getCdr()->containsVariable())
        replaceVariables(pairp->getCdr(), effect);
        break;

    case Pairp::_NIL_:
        break;
    }
    pairp->setVariableFlag(VariableFlag::DOES_NOT_CONTAIN);
#ifdef TRACE_ENVIRONMENT
     std::cout << "<H4>Environment::replaceVariables(list) result</H4>" << std::endl;
     std::cout << "<table border=\"1\"><tr><th>List</th></tr>";
     std::cout << "<tr><td>";
     pairp->flatPrint(std::cout, 0);
     std::cout << "</td></tr></table>";
#endif
    if (effect)
        pairp->resetSerial();
}

/* **************************************************
 *
 ************************************************** */
void Environment::replaceVariables(std::string &str, bool &effect)
{
#ifdef TRACE_ENVIRONMENT
     std::cout << "<H4>Environment::replaceVariables(list)</H4>" << std::endl;
     std::cout << "<table border=\"1\"><tr><th>std::string</th><th>Environment</th></tr>";
     std::cout << "<tr><td>";
     std::cout << str;
     std::cout << "</td><td>";
     this->print(std::cout);
     std::cout << "</td></tr></table>";
#endif
    std::string pattern =
        std::string(
            "(\\$([a-zA-Z_]|à|á|â|ã|ä|å|æ|ç|è|é|ê|ë|ì|í|î|ï|ð|ñ|ò|ó|ô|õ|ö|ø|ù|ú|û|ü|ý|ÿ|À|Á|Â|Ã|Ä|Å|Æ|Ç|È|É|Ë|Ì|Í|Î|Ï|Ð|Ñ|Ò|Ó|Ô|Õ|Ö|Ø|Ù|Ú|Û|Ü|Ý|Ÿ|ß)([a-zA-Z0-9_]|à|á|â|ã|ä|å|æ|ç|è|é|ê|ë|ì|í|î|ï|ð|ñ|ò|ó|ô|õ|ö|ø|ù|ú|û|ü|ý|ÿ|À|Á|Â|Ã|Ä|Å|Æ|Ç|È|É|Ë|Ì|Í|Î|Ï|Ð|Ñ|Ò|Ó|Ô|Õ|Ö|Ø|Ù|Ú|Û|Ü|Ý|Ÿ|ß)+)");
    std::cmatch match;

    try
    {
        std::regex regexpression(pattern, std::regex_constants::ECMAScript);
        while (std::regex_search(str.c_str(), match, regexpression, std::regex_constants::format_first_only))
        {
            const std::string key = match[1];
            auto i = this->env.find(key);
            if (i == this->env.end())
            {
                // std::cerr << "*** error variable " << match[1] << " not found" << std::endl;
                std::string s = "?";
                str = std::regex_replace(str, regexpression, s, std::regex_constants::format_first_only);
            }
            else
            {
                std::ostringstream oss;
                i->second->print(oss);
                str = std::regex_replace(str, regexpression, oss.str(), std::regex_constants::format_first_only);
            }
            effect = true;
        }
    }

    catch (const std::regex_error &e)
    {
        std::cout << "regex_error caught: " << e.what() << '(' << e.code() << ')' << std::regex_constants::error_brack
                  << '\n';
    }
#ifdef TRACE_ENVIRONMENT
     std::cout << "<H4>Environment::replaceVariables(list) result</H4>" << std::endl;
     std::cout << "<table border=\"1\"><tr><th>Std::List</th></tr>";
     std::cout << "<tr><td>";
     this->print(std::cout);
     std::cout << "</td></tr></table>";
#endif
}

/* **************************************************
 *
 ************************************************** */
environmentPtr Environment::clone() const
{
    environmentPtr environment = Environment::create();
    for (const auto &i : *this)
    {
        if (!environment->_add(i.first, (i.second) ? i.second->clone() : valuePtr()))
            throw fatal_exception("environment not clonable");
    }
    return environment;
}
