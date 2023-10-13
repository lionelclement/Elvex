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

#include <climits>
#include <sstream>
#include "feature.hpp"
#include "features.hpp"
#include "environment.hpp"
#include "value.hpp"
#include "messages.hpp"
#include "bitset.hpp"
#include "generator.hpp"
#include "item.hpp"
#include "statement.hpp"
#include "value.hpp"
#include "vartable.hpp"

featuresPtr Features::BOTTOM = createBottom();
featuresPtr Features::NIL = createNil();

/* **************************************************
 *
 ************************************************** */
Features::Features(const featurePtr &feature)
{
    NEW;
    if (feature)
    {
        features.push_back(feature);
    }
    this->head = 0;
    this->form = "";
}

/* **************************************************
 *
 ************************************************** */
Features::~Features()
{
    DELETE;
    for (auto tmp : features)
    {
        if (tmp)
            tmp.reset();
    }
}

/* ************************************************************
 *
 ************************************************************ */
featuresPtr Features::create(const featurePtr &feature)
{
    return featuresPtr(new Features(feature));
}

/* ************************************************************
 *
 ************************************************************ */
featuresPtr Features::createBottom()
{
    featuresPtr fs = create();
    fs->addFlags(Flags::BOTTOM);
    return fs;
}

/* ************************************************************
 *
 ************************************************************ */
featuresPtr Features::createNil()
{
    featuresPtr fs = create();
    fs->addFlags(Flags::NIL);
    return fs;
}

/* **************************************************
 *
 ************************************************** */
void Features::add(const featurePtr &feature)
{
    this->features.push_back(feature);
}

/* **************************************************
 *
 ************************************************** */
void Features::add(const featuresPtr &_features)
{
    for (auto j = _features->cbegin(); j != _features->cend(); ++j)
        this->features.push_back(*j);
}

/* **************************************************
 *
 ************************************************** */
Features::list_of_feature::iterator Features::erase(Features::list_of_feature::iterator i)
{
    return features.erase(i);
}

/* **************************************************
 *
 ************************************************** */
size_t Features::size() const
{
    return features.size();
}

/* **************************************************
 *
 ************************************************** */
Features::list_of_feature::const_iterator Features::cbegin() const
{
    return features.cbegin();
}

/* **************************************************
 *
 ************************************************** */
Features::list_of_feature::const_iterator Features::cend() const
{
    return features.cend();
}

/* **************************************************
 *
 ************************************************** */
Features::list_of_feature::iterator Features::begin()
{
    return features.begin();
}

/* **************************************************
 *
 ************************************************** */
Features::list_of_feature::iterator Features::end()
{
    return features.end();
}

/* **************************************************
 *
 ************************************************** */
featurePtr Features::front() const
{
    return *(features.begin());
}

/* **************************************************
 *
 ************************************************** */
bool Features::isNil() const
{
    return isSetFlags(Flags::NIL);
}

/* **************************************************
 *
 ************************************************** */
bool Features::isBottom() const
{
    return isSetFlags(Flags::BOTTOM);
}

/* **************************************************
 *
 ************************************************** */
void Features::print(std::ostream &outStream) const
{
    if (isNil())
        outStream << "NIL";
    else if (isBottom())
        outStream << "⊥";
    else
    {
        outStream << R"(<TABLE border = "1">)";
        outStream << R"(<TBODY align = "left"><TR><TD><TABLE border = "0">)";
        if (!features.empty())
        {
            for (int t = Feature::first_type; t <= Feature::last_type; ++t)
            {
                for (const auto &feature : features)
                {
                    if (feature->getType() == t)
                    {
                        outStream << "<TR>";
                        feature->print(outStream);
                        outStream << "</TR>";
                    }
                }
            }
        }
        else
        {
            outStream << "<TR><TD></TD></TR>";
        }
        outStream << "</TABLE></TD></TR></TBODY>";
        outStream << "</TABLE>";
    }
}

/* **************************************************
 *
 ************************************************** */
void Features::flatPrint(std::ostream &outStream, bool par) const
{
    if (isNil())
        outStream << "NIL";
    else if (isBottom())
        outStream << "⊥";
    else
    {
        if (par)
            outStream << '[';
        bool first = true;
        for (int t = Feature::first_type; t <= Feature::last_type; ++t)
        {
            for (const auto &feature : features)
            {
                if (feature->getType() == t)
                {
                    if (first)
                        first = false;
                    else
                        outStream << ", ";
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
void Features::makeSerialString()
{
    std::ostringstream stream;
    stream.clear();
    if (isNil())
        stream << 'N';
    else if (isBottom())
        stream << 'B';
    else
    {
        for (const auto &feature : features)
        {
            stream << '_' << feature->peekSerialString();
        }
    }
    serialString = stream.str();
}

/* **************************************************
 *
 ************************************************** */
uint16_t Features::assignHead()
{
    if (this->head)
        return this->head;
    for (const auto &f : features)
    {
        // […, HEAD = …, …]
        if (f->isHead())
        {
            return this->head = f->getValue()->getCode();
        }
    }
    return this->head = Vartable::DOES_NOT_CONTAIN_A_HEAD;
}

/* **************************************************
 *
 ************************************************** */
std::string *Features::assignForm()
{
    if (!form.empty())
        return &form;
    for (const auto &f : features)
    {
        if (f->isForm())
        {
            form = f->getValue()->getString();
            return &form;
        }
    }
    return nullptr;
}

#ifdef OUTPUT_XML
/* **************************************************
 *
 ************************************************** */
void Features::toXML(xmlNodePtr nodeRoot)
{
    xmlNodePtr f = xmlNewChild(nodeRoot, nullptr, (const xmlChar *)"FS", nullptr);
    xmlSetProp(f, (xmlChar *)"id", (xmlChar *)this->getIdStr().c_str());
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
featuresPtr Features::clone() const
{
    if (isNil())
        return NIL;
    if (isBottom())
        return BOTTOM;
    featuresPtr result = Features::create();
    for (const auto &feature : features)
        result->features.push_back(feature->clone());
    result->head = head;
    result->form = form;
    return result;
}

/* **************************************************
 *
 ************************************************** */
valuePtr Features::find(const bitsetPtr &code) const
{
    for (const auto &feature : features)
    {
        if (((*feature->getAttribute()) & *code).any())
        {
            return feature->getValue();
        }
    }
    return valuePtr();
}

/* **************************************************
 *
 ************************************************** */
bool Features::buildEnvironment(statementPtr statementRoot, const environmentPtr &environment, const featuresPtr &other_features, bool acceptToFilterNULLVariables
#ifdef TRACE_BUILD_ENVIRONMENT
                                ,
                                bool root
#endif
                                , bool verbose)
{
    bool ret = true;
    //	if (environment){
    //		bool effect  =  false;
    //		CERR_LINE;
    //		//environment->replaceVariables(shared_from_this(), effect);
    //		//environment->replaceVariables(features, effect);
    //	}

#ifdef TRACE_BUILD_ENVIRONMENT
    if (root)
    {
        COUT_LINE;
        std::cout << "<H4>Features::buildEnvironment</H4>" << std::endl;
        std::cout << "<table border = \"1\"><tr><th>this</th><th>features</th><th>Environment</th></tr>";
        std::cout << "<tr><td>";
        print(std::cout);
        std::cout << "</td><td>";
        if (other_features)
            other_features->print(std::cout);
        else
            std::cout << "NULL";
        std::cout << "</td><td>";
        environment->print(std::cout);
        std::cout << "</td></tr></table>";
    }
#endif

    // Traite tous les attributs constants
    for (const auto &this_feature : features)
    {
        if ((this_feature->isLemma()) || (this_feature->isHead()) || (this_feature->isConstant()))
        {
            bool stop = false;
            for (auto &other_feature : *other_features)
            {
                // Si deux constantes matchent
                // ou deux HEAD matchent
                if (((other_feature->isConstant()) && (this_feature->isConstant()) &&
                     ((*this_feature->getAttribute() & *other_feature->getAttribute()).any())) ||
                    ((this_feature->isHead()) && (other_feature->isHead())) || ((this_feature->isLemma()) && (other_feature->isLemma())))
                {
                    other_feature->addFlags(Flags::SEEN);

                    // If both are NIL
                    if ((this_feature->getValue()->isNil()) && (other_feature->getValue()->isNil()))
                    {
                    }
                    // If both are TRUE
                    // else if ((i1->getValue()->isTrue()) && (i2->getValue()->isTrue())) {
                    //}

                    // If one is ANONYMOUS
                    else if ((this_feature->getValue()->isAnonymous()) || (other_feature->getValue()->isAnonymous()))
                    {
                    }

                    // Else build environment with the two values
                    else if (!this_feature->getValue()->buildEnvironment(statementRoot, environment, other_feature->getValue(),
                                                               acceptToFilterNULLVariables, false, verbose))
                    {
                        ret = false;
                    }
                    stop = true;
                    break;
                }
            }
            // Trait this_feature inexistant
            if (!stop)
            {
                // this_feature: a = $X
                if ((this_feature->isConstant()) || this_feature->isLemma() || this_feature->isHead())
                {
                    if (this_feature->getValue()->isVariable())
                    {
                        //  = > $X = NIL
                        if (acceptToFilterNULLVariables)
                        {
                            environment->add(statementRoot, this_feature->getValue()->getBits(), Value::STATIC_ANONYMOUS, verbose);
                        }
                        else
                        {
                            ret = false;
                        }
                    }
                    else if (this_feature->getValue()->isNil())
                    {
                    }
                    // this_feature: a = ...
                    else
                    {
                        if (!acceptToFilterNULLVariables)
                        {
                            ret = false;
                        }
                        else
                        {
                            if (!this_feature->getValue()->buildEnvironment(statementRoot, environment, Value::STATIC_ANONYMOUS,
                                                                  acceptToFilterNULLVariables, false, verbose))
                            {
                                ret = false;
                            }
                        }
                    }
                }
            }
        }
    }

    // traite les variables de structures
    for (const auto &this_feature : features)
    {
        // this_feature: X
        if (this_feature->isVariable())
        {
            if (this_feature->getValue())
            {
                throw fatal_exception("A variable attribute is not allowed in this context: " +
                                      this_feature->getAttribute()->toString());
            }
            else
            {
                featuresPtr nFeatures = Features::create();
                for (auto &other_feature : *other_features)
                {
                    if (other_feature->isUnsetFlags(Flags::SEEN))
                    {
                        other_feature->addFlags(Flags::SEEN);
                        nFeatures->add(other_feature);
                    }
                }
                environment->add(statementRoot, this_feature->getAttribute(), Value::create(nFeatures), verbose);
            }
        }
    }
    other_features->subFlags(Flags::SEEN);

#ifdef TRACE_BUILD_ENVIRONMENT
    if (root)
    {
        std::cout << "<H4>Result Features::buildEnvironment</H4>" << std::endl;
        std::cout << "<table border = \"1\"><tr><th>R&eacute;sultat</th><th>Environment</th></tr>";
        std::cout << "<tr><td>" << (ret ? "TRUE" : "FALSE") << "</td><td>";
        environment->print(std::cout);
        std::cout << "</td></tr></table>";
    }
#endif
    return ret;
}

/* **************************************************
 *true if this subsumes o
 *if it does, change variables in this
 ************************************************** */
bool Features::subsumes(statementPtr statementRoot, const featuresPtr &other_features, const environmentPtr &environment, bool verbose)
{
#ifdef TRACE_FEATURES
    COUT_LINE;
    std::cout << "<DIV>";
    std::cout << "Subsumes (";
    this->flatPrint(std::cout);
    std::cout << "<TABLE border=\"1\"><TR><TH>this</TH><TH></TH><TH>other</TH><TH>env</TH></TR><TR>";
    std::cout << "<TD>";
    this->print(std::cout);
    std::cout << "</TD><TD>&lt;</TD><TD>";
    other_features->print(std::cout);
    std::cout << "</TD>";
    std::cout << "<TD>";
    environment->print(std::cout);
    std::cout << "</TD>";
    std::cout << "</TR></TABLE>";
    std::cout << "</DIV>";
    std::flush(std::cout);

#endif
    
    bool ret = true;
    // NIL < NIL
    if (isNil() && other_features->isNil())
    {
    }

    // NIL < […]
    // […] < NIL
    else if (isNil() || other_features->isNil())
    {
        ret = false;
    }
    // ⊥ < […]
    // […] < ⊥
    else if (isBottom() || other_features->isBottom())
    {
        ret = false;
    }
    else
    {
        for (auto &feature : features)
        {
            for (auto &other_feature : other_features->features)
            {
                // [HEAD:X] << [HEAD:Y]
                // [LEMMA:X] << [LEMMA:Y]
                // [att:X] << [att:Y]
                // X << Y
                if (((feature->isLemma()) && (other_feature->isLemma())) 
                    || ((feature->isHead()) && (other_feature->isHead())) 
                    || ((feature->isConstant()) && (other_feature->isConstant()) && ((*feature->getAttribute() & *other_feature->getAttribute()).any())))
                {
                    valuePtr v1 = feature->getValue();
                    valuePtr v2 = other_feature->getValue();
                    if (!v1->subsumes(statementRoot, v2, environment, verbose))
                    {
                        ret = false;
                    }
                    break;
                }
            }
        }
    }
#ifdef TRACE_FEATURES
    std::cout << "<DIV>";
    std::cout << "result: (" << shared_from_this() << ")";
    std::cout << (ret ? "true" : "false") << std::endl;
    environment->print(std::cout);
    std::cout << "</DIV>";
#endif
    return ret;
}

/* **************************************************
 *
 ************************************************** */
void Features::subFlags(const std::bitset<MAX_FLAGS> &flags)
{
    for (auto &i : features)
        i->subFlags(flags);
}

/* **************************************************
 *
 ************************************************** */
bool Features::renameVariables(uint32_t code)
{
    bool effect = false;
    for (auto &feature : features)
    {
        if (feature->renameVariables(code))
            effect = true;
    }
    if (effect)
        resetSerial();
    return effect;
}

/* **************************************************
 *
 ************************************************** */
void Features::enable(statementPtr statementRoot, class Item *item, Generator *synthesizer, bool &effect, bool on)
{
    for (auto &feature : features)
        feature->enable(statementRoot, item, synthesizer, effect, on);
}

/* **************************************************
 *
 ************************************************** */
void Features::deleteAnonymousVariables()
{
    bool redo = true;
    while (redo)
    {
        redo = false;

        for (auto feature = cbegin(); feature != cend() && !redo; ++feature)
        {
            switch ((*feature)->getType())
            {
            case Feature::_HEAD_:
            case Feature::_LEMMA_:
            case Feature::_FORM_:
            case Feature::_VARIABLE_:
            case Feature::_CONSTANT_:
                if ((*feature)->getValue())
                {
                    (*feature)->getValue()->deleteAnonymousVariables();
                    if ((*feature)->getValue() && ((*feature)->getValue()->isAnonymous()))
                    {
                        features.erase(feature);
                        redo = true;
                    }
                }
                break;
            }
        }
    }
}

/* **************************************************
 *
 ************************************************** */
void Features::deleteVariables()
{
    bool redo = true;
    while (redo)
    {
        redo = false;
        for (auto feature = cbegin(); feature != cend() && !redo; ++feature)
        {
            switch ((*feature)->getType())
            {
            case Feature::_HEAD_:
            case Feature::_LEMMA_:
            case Feature::_FORM_:
            case Feature::_VARIABLE_:
            case Feature::_CONSTANT_:
                if ((*feature)->getValue())
                {
                    (*feature)->getValue()->deleteVariables();
                    if ((*feature)->isVariable() || (*feature)->getValue()->isVariable())
                    {
                        features.erase(feature);
                        redo = true;
                    }
                }
                break;
            }
        }
    }
}

/* **************************************************
 *
 ************************************************** */
bool Features::findVariable(const bitsetPtr &variable)
{
    for (auto &iterator : features)
        if (iterator->findVariable(variable))
            return true;
    return false;
}

/* **************************************************
 *
 ************************************************** */
bool Features::containsVariable()
{
    bool result = false;
    if (variableFlag.containsVariable())
        return true;
    for (auto &iterator : features)
    {
        if (iterator->containsVariable())
        {
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
void Features::setVariableFlag(enum VariableFlag::flagValues flag)
{
    this->variableFlag.setFlag(flag);
}

/* **************************************************
 *
 ************************************************** */
void Features::apply(statementPtr statementRoot, class Item *item, Parser &parser, Generator *synthesizer, const statementPtr &variable,
                     const statementPtr &statement,
                     bool &effect, bool verbose)
{
    item->getEnvironment()->add(statementRoot, variable->getBits(), Value::create(shared_from_this()), verbose);
    effect = true;
    statement->toggleEnable(statement, item, synthesizer, effect, false);
    statement->apply(statementRoot, item, parser, synthesizer, effect, verbose);
    item->getEnvironment()->remove(variable->getBits());
}
