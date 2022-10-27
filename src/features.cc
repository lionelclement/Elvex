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

#include <climits>
#include <sstream>
#include "feature.hpp"
#include "features.hpp"
#include "environment.hpp"
#include "value.hpp"
#include "messages.hpp"
#include "bitset.hpp"
#include "synthesizer.hpp"

featuresPtr Features::BOTTOM = createBottom();
featuresPtr Features::NIL = createNil();

/* **************************************************
 *
 ************************************************** */
Features::Features(const featurePtr& feature) {
    if (feature){
        features.push_back(feature);
    }
    this->pred = 0;
    this->form = "";
    NEW
}

/* **************************************************
 *
 ************************************************** */
Features::~Features() {
    DELETE
    for (auto tmp : features) {
        if (tmp)
            tmp.reset();
    }
}

/* ************************************************************
 *
 ************************************************************ */
featuresPtr Features::create(const featurePtr& feature) {
    return featuresPtr(new Features(feature));
}

/* ************************************************************
 *
 ************************************************************ */
featuresPtr Features::createBottom() {
    featuresPtr fs = create();
    fs->addFlags(Flags::BOTTOM);
    return fs;
}

/* ************************************************************
 *
 ************************************************************ */
featuresPtr Features::createNil() {
    featuresPtr fs = create();
    fs->addFlags(Flags::NIL);
    return fs;
}

/* **************************************************
 *
 ************************************************** */
void Features::add(const featurePtr& feature) {
    this->features.push_back(feature);
}

/* **************************************************
 *
 ************************************************** */
void Features::add(const featuresPtr& _features) {
    for (auto j = _features->cbegin() ; j != _features->cend() ; ++j)
        this->features.push_back(*j);
}

/* **************************************************
 *
 ************************************************** */
Features::list_of_feature::iterator Features::erase(Features::list_of_feature::iterator i) {
    return features.erase(i);
}

/* **************************************************
 *
 ************************************************** */
size_t Features::size() const {
    return features.size();
}

/* **************************************************
 *
 ************************************************** */
Features::list_of_feature::const_iterator Features::cbegin() {
    return features.cbegin();
}

/* **************************************************
 *
 ************************************************** */
Features::list_of_feature::const_iterator Features::cend() {
    return features.cend();
}

/* **************************************************
 *
 ************************************************** */
Features::list_of_feature::iterator Features::begin() {
    return features.begin();
}

/* **************************************************
 *
 ************************************************** */
Features::list_of_feature::iterator Features::end() {
    return features.end();
}

/* **************************************************
 *
 ************************************************** */
featurePtr Features::front() const {
    return *(features.begin());
}

/* **************************************************
 *
 ************************************************** */
bool Features::isNil() const {
    return isSetFlags(Flags::NIL);
}

/* **************************************************
 *
 ************************************************** */
bool Features::isBottom() const {
    return isSetFlags(Flags::BOTTOM);
}

/* **************************************************
 *
 ************************************************** */
void Features::print(std::ostream &outStream) const {
    if (isNil())
        outStream << "NIL";
    else if (isBottom())
        outStream << "⊥";
    else {
        outStream << R"(<TABLE border = "1">)";
        outStream << R"(<TBODY align = "left"><TR><TD><TABLE border = "0">)";
        if (!features.empty()) {
            for (int t = Feature::first_type; t <= Feature::last_type; ++t) {
                for (const auto & feature : features) {
                    if (feature->getType() == t) {
                        outStream << "<TR>";
                        feature->print(outStream);
                        outStream << "</TR>";
                    }
                }
            }
        } else {
            outStream << "<TR><TD></TD></TR>";
        }
        outStream << "</TABLE></TD></TR></TBODY>";
        outStream << "</TABLE>";
    }
}

/* **************************************************
 *
 ************************************************** */
void Features::flatPrint(std::ostream &outStream, bool par) const {
    if (isNil())
        outStream << "NIL";
    else if (isBottom())
        outStream << "⊥";
    else {
        if (par)
            outStream << '[';
        bool first = true;
        for (int t = Feature::first_type; t <= Feature::last_type; ++t) {
            for (const auto & feature : features) {
                if (feature->getType() == t) {
                    if (first)
                        first = false;
                    else
                        outStream << ',';
                    feature->flatPrint(outStream);
                }
            }
        }
    }
    if (par)
        outStream << ']';
}

/* **************************************************
 *
 ************************************************** */
void Features::makeSerialString() {
    if (isNil())
        serialString = '#';
    else if (isBottom())
        serialString = '&';
    else {
        serialString = '[';
        if (!features.empty()) {
            bool first = true;
            for (const auto& f : features) {
                if (first)
                    first = false;
                else
                    serialString += ',';
                serialString += f->peekSerialString();
            }
        }
        serialString += ']';
    }
}

/* **************************************************
 *
 ************************************************** */
unsigned int Features::assignPred() {
    unsigned int ret = UINT_MAX;
    if (this->pred)
        return this->pred;
    for (const auto& f : features) {
        // […, PRED = …, …]
        if (f->getType() == Feature::PRED) {
            ret = f->getValue()->getCode();
            break;
        }
    }
    this->pred = ret;
    return ret;
}

/* **************************************************
 *
 ************************************************** */
std::string *Features::assignForm() {
    if (!form.empty())
        return &form;
    for (const auto& f : features) {
        if (f->getType() == Feature::FORM) {
            form = f->getValue()->getStr();
            return &form;
        }
    }
    return nullptr;
}

#ifdef OUTPUT_XML
/* **************************************************
 *
 ************************************************** */
void
Features::toXML(xmlNodePtr nodeRoot)
{
   xmlNodePtr f = xmlNewChild(nodeRoot, nullptr, (const xmlChar*)"FS", nullptr);
   xmlSetProp(f, (xmlChar*)"id", (xmlChar*)std::to_string(this->getId()).c_str());
   if (!features.empty())
   for (list_of_feature::const_iterator i = features.begin();
         i != features.end();
         ++i)
   (*i)->toXML(f);
}
#endif

/* **************************************************
 *
 ************************************************** */
featuresPtr Features::clone() const {
    if (isNil())
        return NIL;
    if (isBottom())
        return BOTTOM;
    featuresPtr result = Features::create();
    for (const auto & feature : features)
        result->features.push_back(feature->clone());
    result->pred = pred;
    result->form = form;
    return result;
}

/* **************************************************
 *
 ************************************************** */
valuePtr Features::find(const bitsetPtr& code) const {
    for (const auto & feature : features) {
        if (((*feature->getAttribute()) & *code).any()) {
            return feature->getValue();
        }
    }
    return valuePtr();
}

/* **************************************************
 *
 ************************************************** */
bool Features::buildEnvironment(const environmentPtr& environment, const featuresPtr& _features, bool acceptToFilterNULLVariables/*,
                                bool root*/) {
    bool ret = true;
    //	if (environment){
    //		bool effect  =  false;
    //		CERR_LINE;
    //		//environment->replaceVariables(shared_from_this(), effect);
    //		//environment->replaceVariables(features, effect);
    //	}

    /***
     if (root) {
     CERR_LINE;
     std::cerr << "<H4>Features::buildEnvironment</H4>" << std::endl;
     std::cerr << "<table border = \"1\"><tr><th>this</th><th>features</th><th>Environment</th></tr>";
     std::cerr << "<tr><td>";
     print(std::cerr);
     std::cerr << "</td><td>";
     if (features)
     features->print(std::cerr);
     else
     std::cerr << "NULL";
     std::cerr << "</td><td>";
     environment->print(std::cerr);
     std::cerr << "</td></tr></table>";
     }
     ***/

    // Traite tous les attributs constants
    for (const auto & i1 : features) {
        if ((i1->getType() == Feature::LEMMA) || (i1->getType() == Feature::PRED) || (i1->getType() == Feature::CONSTANT)) {
            bool stop = false;
            for (auto & i2 : *_features) {
                // Si deux constantes matchent
                // ou deux PRED matchent
                if (((i2->getType() == Feature::CONSTANT) && (i1->getType() == Feature::CONSTANT) &&
                     ((*i1->getAttribute() & *i2->getAttribute()).any()))
                    || ((i1->getType() == Feature::PRED) && (i2->getType() == Feature::PRED))
                    || ((i1->getType() == Feature::LEMMA) && (i2->getType() == Feature::LEMMA))
                    ) {
                    i2->addFlags(Flags::SEEN);

                    // If both are NIL
                    if ((i1->getValue()->_isNil()) && (i2->getValue()->_isNil())) {
                    }
                        // If both are TRUE
                    //else if ((i1->getValue()->isTrue()) && (i2->getValue()->isTrue())) {
                    //}

                        // If one is ANONYMOUS
                        //else if ((i1->getValue()->isAnonymous()) || (i2->getValue()->isAnonymous())) {
                        //}

                        // Else build environment with the two values
                    else if (!i1->getValue()->buildEnvironment(environment, i2->getValue(),
                                                                  acceptToFilterNULLVariables, false)) {
                        ret = false;
                    }
                    stop = true;
                    break;
                }
            }
            // Trait i1 inexistant
            if (!stop) {
                // i1: a = $X
                if ((i1->getType() == Feature::CONSTANT) || i1->getType() == Feature::LEMMA || i1->getType() == Feature::PRED) {
                    if (i1->getValue()->getType() == Value::_VARIABLE) {
                        //  = > $X = NIL
                        if (acceptToFilterNULLVariables) {
                            environment->add(i1->getValue()->getBits(), Value::ANONYMOUS_VALUE);
                        } else {
                            ret = false;
                        }
                    } else if (i1->getValue()->_isNil()) {
                    }
                        // i1: a = ...
                    else {
                        if (!acceptToFilterNULLVariables) {
                            ret = false;
                        } else {
                            if (!i1->getValue()->buildEnvironment(environment, Value::ANONYMOUS_VALUE,
                                                                     acceptToFilterNULLVariables, false)) {
                                ret = false;
                            }
                        }
                    }
                }
            }
        }
    }

    // traite les variables de structures
    for (const auto& i1 : features) {
        // i1: X
        if (i1->getType() == Feature::VARIABLE) {
            if (i1->getValue()) {
                throw fatal_exception("A variable attribute is not allowed in this context: " +
                      i1->getAttribute()->toString());
                //if (!i1->getValue()->buildEnvironment(environment, i2->getValue(), acceptToFilterNULLVariables, false)){
                //ret = false;
                //}
                /*featuresPtr nFeatures = Features::create();
                Features::std::list<featurePtr>::const_iterator i2 = _features->begin();
                while (i2 != _features->end()) {
                    if (i2->isUnsetFlags(Flags::SEEN)) {
                        i2->addFlags(Flags::SEEN);
                        nFeatures->addi2;
                    }
                    ++i2;
                }*/
                //environment->add(i1->getAttribute(), new Value(nFeatures, Value::FEATURES));
            } else {
                featuresPtr nFeatures = Features::create();
                for (auto & i2 : *_features) {
                    if (i2->isUnsetFlags(Flags::SEEN)) {
                        i2->addFlags(Flags::SEEN);
                        nFeatures->add(i2);
                    }
                }
                environment->add(i1->getAttribute(), Value::create(Value::_FEATURES, nFeatures));
            }
        }
    }
    _features->subFlags(Flags::SEEN);

    /***
     if (root) {
     std::cerr << "<H4>Result Features::buildEnvironment</H4>" << std::endl;
     std::cerr << "<table border = \"1\"><tr><th>R&eacute;sultat</th><th>Environment</th></tr>";
     std::cerr << "<tr><td>" << (ret?"TRUE":"FALSE") << "</td><td>";
     environment->print(std::cerr);
     std::cerr << "</td></tr></table>";
     }
     ***/
    return ret;
}

/* **************************************************
 *true if this subsumes o
 *if it does, change variables in this
 ************************************************** */
bool Features::subsumes(const featuresPtr& o, const environmentPtr& environment) {
    /***
     CERR_LINE;
     cerr << "<DIV>";
     cerr << "Subsumes (" << this << ")";
     cst	err << "<TABLE><TR>";
     cerr << "<TD>";
     this->print(cerr);
     cerr << "</TD><TD>&lt;</TD><TD>";
     o->print(cerr);
     cerr << "</TD>";
     cerr << "</TR></TABLE>";
     cerr << "</DIV>";
     ***/

    bool ret = true;
    // NIL < NIL
    if (isNil() && o->isNil()) {
        // OK
    }

        // NIL < […]
        // […] < NIL
    else if (isNil() || o->isNil()) {
        ret = false;
    }
        // ⊥ < […]
        // […] < ⊥
    else if (isBottom() || o->isBottom()) {
        ret = false;
    } else {
        for (auto & i1 : features) {
            for (auto & i2 : o->features) {
                // [PRED:X]  < [PRED:Y]
                // [LEMMA:X]  < [LEMMA:Y]
                // [att:X] < [att:Y]
                // X < Y
                if (((i1->getType() == Feature::LEMMA) && (i2->getType() == Feature::LEMMA))
                    || ((i1->getType() == Feature::PRED) && (i2->getType() == Feature::PRED))
                    || ((i1->getType() == Feature::CONSTANT) && (i2->getType() == Feature::CONSTANT) &&
                        ((*i1->getAttribute() & *i2->getAttribute()).any()))) {
                    valuePtr v1 = i1->getValue();
                    valuePtr v2 = i2->getValue();
                    if (!v1->subsumes(v2, environment)) {
                        ret = false;
                    }
                    break;
                }
            }
        }
    }
    /***
     cerr << "<DIV>";
     cerr << "result: (" << shared_from_this() << ")";
     cerr << (ret?"true":"false") << endl;
     //environment->print(cerr);
     cerr << "</DIV>";
     ***/
    return ret;
}

/* **************************************************
 *
 ************************************************** */
void Features::subFlags(const std::bitset<FLAGS> &flags) {
    for (auto & i : features)
        i->subFlags(flags);
}

/* **************************************************
 *
 ************************************************** */
bool Features::renameVariables(size_t i) {
    bool effect = false;
    for (auto & feature : features) {
        if (feature->renameVariables(i))
            effect = true;
    }
    if (effect)
        resetSerial();
    return effect;
}

/* **************************************************
 *
 ************************************************** */
void Features::enable(const statementPtr& root, const itemPtr& item, Synthesizer *synthesizer, bool &effect, bool on) {
    for (auto & feature : features)
        feature->enable(root, item, synthesizer, effect, on);
}

/* **************************************************
 *
 ************************************************** */
void Features::deleteAnonymousVariables() {
    redo:
    for (auto iterator = cbegin() ; iterator != cend() ; ++iterator) {
        switch ((*iterator)->getType()) {
            case Feature::PRED:
            case Feature::LEMMA:
            case Feature::FORM:
            case Feature::VARIABLE:
            case Feature::CONSTANT:
                if ((*iterator)->getValue()) {
                    (*iterator)->getValue()->deleteAnonymousVariables();
                    if ((*iterator)->getValue() && ((*iterator)->getValue()->_isAnonymous())) {
                        features.erase(iterator);
                        goto redo;
                    }
                }
                break;
        }
    }
}

/* **************************************************
 *
 ************************************************** */
bool Features::findVariable(const bitsetPtr& variable) {
    for (auto & iterator : features)
        if (iterator->findVariable(variable))
            return true;
    return false;
}

/* **************************************************
 *
 ************************************************** */
bool Features::containsVariable() {
    bool result = false;
    if (variableFlag.containsVariable())
        return true;
    for (auto & iterator : features) {
        if (iterator->containsVariable()) {
            result = true;
        }
    }
    if (result)
        variableFlag.setFlag(VariableFlag::CONTAINS);
    else
        variableFlag.setFlag(VariableFlag::DOES_NOT_CONTAIN);
    return result;
}

/* **************************************************
 *
 ************************************************** */
void Features::setVariableFlag(enum VariableFlag::flagValues flag) {
    this->variableFlag.setFlag(flag);
}
