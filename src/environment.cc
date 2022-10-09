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

#include <regex>
#include <sstream>
#include <list>
#include <utility>
#include "environment.hpp"
#include "messages.hpp"
#include "list.hpp"
#include "feature.hpp"
#include "features.hpp"
#include "value.hpp"
#include "shared_ptr.hpp"
#include "listfeatures.hpp"
#include "bitset.hpp"

/* **************************************************
 *
 ************************************************** */
Environment::Environment() {
    NEW
}

/* **************************************************
 *
 ************************************************** */
Environment::~Environment() {
    DELETE
    for (auto & i : env) {
        valuePtr tmp = i.second;
        if (tmp)
            tmp.reset();
    }
}

/* **************************************************
 *
 ************************************************** */
environmentPtr Environment::create() {
    return environmentPtr(new Environment());
}

/* **************************************************
 *
 ************************************************** */
void Environment::add(const std::string& key, valuePtr value) {
    auto it = env.find(key);
    if (it == env.end()) {
        env.insert(std::make_pair(key, value));
    } else {
        it->second = value;
    }
}

/* **************************************************
 *
 ************************************************** */
void Environment::remove(const std::string& key) {
    env.erase(key);
}

/* **************************************************
 *
 ************************************************** */
void Environment::add(const bitsetPtr& attr, valuePtr value) {
    const std::string key = attr->toString();
    add(key, std::move(value));
}

/* **************************************************
 *
 ************************************************** */
void Environment::add(const environmentPtr& e) {
    for (const auto& i : *e)
        add(i.first, i.second);
}

/* **************************************************
 *
 ************************************************** */
void Environment::add(const environmentPtr& e, const environmentPtr& where) {
    if (where)
        for (const auto& i : *e)
            if (where->env.find(i.first) != where->env.end())
                add(i.first, i.second);
}

/* **************************************************
 *
 ************************************************** */
void Environment::remove(const bitsetPtr& attr) {
    const std::string key = attr->toString();
    remove(key);
}

/* **************************************************
 *
 ************************************************** */
Environment::unordered_map::const_iterator Environment::begin() const {
    return env.begin();
}

/* **************************************************
 *
 ************************************************** */
Environment::unordered_map::const_iterator Environment::end() const {
    return env.end();
}

/* **************************************************
 *
 ************************************************** */
size_t Environment::size() const {
    return env.size();
}

/* **************************************************
 *
 ************************************************** */
valuePtr Environment::find(const bitsetPtr& attr) const {
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
void Environment::print(std::ostream &out) const {
    bool first = true;
    out << "<TABLE border=\"1\"><TR>";
    for (auto & i : env) {
        if (first)
            first = false;
        else
            out << "</TR><TR>";
        out << "<TD>";
        out << i.first;
        if (i.second) {
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
void Environment::replaceVariables(const featuresPtr& features, bool &effect) {
    /***
     std::cerr << "<H4>Environment::replaceVariables(features)</H4>" << std::endl;
     std::cerr << "<table border=\"1\"><tr><th>featurePtrs</th><th>Environment</th></tr>";
     std::cerr << "<tr><td>";
     features->print(std::cerr);
     std::cerr << "</td><td>";
     this->print(std::cerr);
     std::cerr << "</td></tr></table>";
     ***/
    if (!features->containsVariable())
        return;

    redo:
    for (auto it = features->begin() ; it != features->end() ; ++it) {
        featurePtr feature = *it;
        switch (feature->getType()) {
            case Feature::PRED:
            case Feature::LEMMA:
                if (feature->getValue())
                    replaceVariables(feature->getValue(), effect);
                break;
            case Feature::FORM:
            case Feature::CONSTANT:
                if (feature->getValue()) {
                    replaceVariables(feature->getValue(), effect);
                }
                break;
            case Feature::VARIABLE: {
                if (feature->getValue()) {
                    effect = true;
                    replaceVariables(feature->getValue(), effect);
                }

                valuePtr value = find(feature->getAttribute());
                if (!value) {
                    /* do nothing */
                } else if (value->_isNil()) {
                    /* do nothing */
                } else if (value->_isFeatures()) {
                    features->erase(it);
                    for (const auto& f : *value->getFeatures()) {
                        features->add(f);
                    }
                    effect = true;
                    goto redo;
                } else if (value->_isConstant()) {
                    feature->setType(Feature::CONSTANT);
                    feature->setAttribute(value->getBits());
                } else if (value->_isAnonymous()) {
                    features->erase(it);
                    effect = true;
                    goto redo;
                } else {
                    throw fatal_exception("environment: variable substitution failed");
                }
            }
                break;
        }
        features->setVariableFlag(VariableFlag::DOES_NOT_CONTAIN);
    }
    /***
     std::cerr << "<H4>Environment::replaceVariables(features) DONE</H4>" << std::endl;
     std::cerr << "<table border=\"1\"><tr><th>Features</th><th>Environment</th></tr>";
     std::cerr << "<tr><td>";
     features->print(std::cerr);
     std::cerr << "</td><td>";
     this->print(std::cerr);
     std::cerr << "</td></tr></table>";
     ***/
    if (effect)
        features->resetSerial();
}

/* **************************************************
 *
 ************************************************** */
void Environment::replaceVariables(const listFeaturesPtr& listFeatures, bool &effect) {
    for (auto & vf : *listFeatures)
        this->replaceVariables(vf, effect);
}

/* **************************************************
 *
 ************************************************** */
void Environment::replaceVariables(const valuePtr& value, bool &effect) {
    /***
     std::cerr << "<H4>Environment::replaceVariables(value)</H4>" << std::endl;
     std::cerr << "<table border=\"1\"><tr><th>Value</th><th>Environment</th></tr>";
     std::cerr << "<tr><td>";
     value->print(std::cerr);
     std::cerr << "</td><td>";
     this->print(std::cerr);
     std::cerr << "</td></tr></table>";
     ***/
    if (!value->containsVariable())
        return;
    if (!value->_isNil() && !value->_isAnonymous()) {
        switch (value->getType()) {
            case Value::_NIL:
            case Value::_TRUE:
            case Value::_FORM:
            case Value::_CONSTANT:
            case Value::_CODE:
            case Value::_ANONYMOUS:
            case Value::_NUMBER:
                break;
            case Value::_FEATURES:
                replaceVariables(value->getFeatures(), effect);
                break;
            case Value::_LIST:
                replaceVariables(value->getList(), effect);
                break;
            case Value::_VARIABLE:
                valuePtr val = find(value->getBits());
                if (val && (val != value)) {
                    effect = true;
                    *value = *val;
                    replaceVariables(value, effect);
                }
                break;
        }
        value->setVariableFlag(VariableFlag::DOES_NOT_CONTAIN);
    }
    /***
     std::cerr << "<H4>Environment::replaceVariables(value) result</H4>" << std::endl;
     std::cerr << "<table border=\"1\"><tr><th>Std::List</th></tr>";
     std::cerr << "<tr><td>";
     std::cerr << "</td></tr></table>";
     ***/
    if (effect)
        value->resetSerial();
}

/* **************************************************
 *
 ************************************************** */
void Environment::replaceVariables(const listPtr& list, bool &effect) {
    /***
     std::cerr << "<H4>Environment::replaceVariables(list)</H4>" << std::endl;
     std::cerr << "<table border=\"1\"><tr><th>List</th><th>Environment</th></tr>";
     std::cerr << "<tr><td>";
     list->flatPrint(std::cerr, 0);
     std::cerr << "</td><td>";
     this->print(std::cerr);
     std::cerr << "</	td></tr></table>";
     ***/
    if (!list->containsVariable())
        return;
    switch (list->getType()) {
        case List::ATOM:
            if (list->isVariable()) {
                valuePtr value = this->find(list->getValue()->getBits());
                if (value->_isList()) {
                    *list = *(value->getList());
                } else if (value->_isNil()) {
                    *list = *List::NIL_LIST;
                } else {
                    list->setValue(value);
                }
            } else
                //if (list->containsVariable())
                replaceVariables(list->getValue(), effect);
            break;

        case List::PAIRP:
            //if (list->getCar()->containsVariable())
            replaceVariables(list->getCar(), effect);
            //if (list->getCdr()->containsVariable())
            replaceVariables(list->getCdr(), effect);
            break;

        case List::NIL:
            break;
    }
    list->setVariableFlag(VariableFlag::DOES_NOT_CONTAIN);
    /***
     std::cerr << "<H4>Environment::replaceVariables(list) result</H4>" << std::endl;
     std::cerr << "<table border=\"1\"><tr><th>List</th></tr>";
     std::cerr << "<tr><td>";
     list->flatPrint(std::cerr, 0);
     std::cerr << "</td></tr></table>";
     ***/
    if (effect)
        list->resetSerial();
}

/* **************************************************
 *
 ************************************************** */
void Environment::replaceVariables(std::string &str, bool &effect) {
    /***
     std::cerr << "<H4>Environment::replaceVariables(list)</H4>" << std::endl;
     std::cerr << "<table border=\"1\"><tr><th>std::string</th><th>Environment</th></tr>";
     std::cerr << "<tr><td>";
     std::cerr << str;
     std::cerr << "</td><td>";
     this->print(std::cerr);
     std::cerr << "</td></tr></table>";
     ***/
    std::string pattern =
            std::string(
                    "(\\$([a-zA-Z_]|à|á|â|ã|ä|å|æ|ç|è|é|ê|ë|ì|í|î|ï|ð|ñ|ò|ó|ô|õ|ö|ø|ù|ú|û|ü|ý|ÿ|À|Á|Â|Ã|Ä|Å|Æ|Ç|È|É|Ë|Ì|Í|Î|Ï|Ð|Ñ|Ò|Ó|Ô|Õ|Ö|Ø|Ù|Ú|Û|Ü|Ý|Ÿ|ß)([a-zA-Z0-9_]|à|á|â|ã|ä|å|æ|ç|è|é|ê|ë|ì|í|î|ï|ð|ñ|ò|ó|ô|õ|ö|ø|ù|ú|û|ü|ý|ÿ|À|Á|Â|Ã|Ä|Å|Æ|Ç|È|É|Ë|Ì|Í|Î|Ï|Ð|Ñ|Ò|Ó|Ô|Õ|Ö|Ø|Ù|Ú|Û|Ü|Ý|Ÿ|ß)+)");
    std::cmatch match;

    try {
        std::regex regexpression(pattern, std::regex_constants::ECMAScript);
        while (std::regex_search(str.c_str(), match, regexpression, std::regex_constants::format_first_only)) {
            const std::string key = match[1];
            auto i = this->env.find(key);
            if (i == this->env.end()) {
                //std::cerr << "*** error variable " << match[1] << " not found" << std::endl;
                std::string s = "?";
                str = std::regex_replace(str, regexpression, s, std::regex_constants::format_first_only);
            } else {
                std::ostringstream oss;
                i->second->print(oss);
                str = std::regex_replace(str, regexpression, oss.str(), std::regex_constants::format_first_only);
            }
            effect = true;
        }
    }

    catch (const std::regex_error &e) {
        std::cout << "regex_error caught: " << e.what() << '(' << e.code() << ')' << std::regex_constants::error_brack
                  << '\n';
    }
    /***
     std::cerr << "<H4>Environment::replaceVariables(list) result</H4>" << std::endl;
     std::cerr << "<table border=\"1\"><tr><th>Std::List</th></tr>";
     std::cerr << "<tr><td>";
     this->print(std::cerr);
     std::cerr << "</td></tr></table>";
     ***/
}

/* **************************************************
 *
 ************************************************** */
environmentPtr Environment::clone() const {
    environmentPtr environment = Environment::create();
    for (const auto & i : *this) {
        environment->add(i.first, (i.second) ? i.second->clone() : valuePtr());
    }
    return environment;
}
