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

#include <iostream>
#include <cstdio>
#include <cstdlib>

#include "compacted-lexicon.hpp"
#include "compacted-lexicon-fsa.hpp"
#include "compacted-lexicon-info.hpp"
#include "compacted-lexicon-buffer.hpp"
#include "messages.hpp"

/* **************************************************
 *
 ************************************************** */
CompactedLexiconTree::CompactedLexiconTree(CompactedLexiconTree *child, CompactedLexiconTree *next,
                                       class CompactedLexiconInfo *info, char character) {
    NEW
    this->address = 0;
    this->child = child;
    this->next = next;
    this->info = info;
    this->character = character;
}

/* **************************************************
 *
 ************************************************** */
CompactedLexiconTree::~CompactedLexiconTree() {
    DELETE
}

/* **************************************************
 *
 ************************************************** */
CompactedLexiconTree *
CompactedLexiconTree::getChild() const {
    return child;
}

/* **************************************************
 *
 ************************************************** */
void CompactedLexiconTree::setChild(CompactedLexiconTree *_child) {
    this->child = _child;
}

/* **************************************************
 // Compute offsets of FSA array
 ************************************************** */
void CompactedLexiconTree::setIndexStaticFSA(unsigned long int &index) {
    for (class CompactedLexiconTree *lexiconSy = this; lexiconSy != nullptr; lexiconSy = lexiconSy->next) {
        lexiconSy->address = index++;
        if (lexiconSy->child)
            lexiconSy->child->setIndexStaticFSA(index);
    }
}

/* **************************************************
 // write record of FSA
 ************************************************** */
void CompactedLexiconTree::printStaticFSA(FILE *out, class CompactedLexicon *lex) const {
    const class CompactedLexiconTree *lexiconSy;
    if (this == lex->lexiconInit) {
        lex->init = this->address;
    }
    for (lexiconSy = this; lexiconSy; lexiconSy = lexiconSy->next) {
        auto *elt = new CompactedLexiconFsa(
                (lexiconSy->child == nullptr) ? (unsigned long int) ~0UL : lexiconSy->child->address,
                (lexiconSy->next == nullptr) ? (unsigned long int) ~0UL : lexiconSy->next->address,
                (lexiconSy->info == nullptr) ? (unsigned long int) ~0UL : lexiconSy->info->getAddress(),
                lexiconSy->character);
        if (!fwrite(elt, sizeof(CompactedLexiconFsa), 1, out)) {
            FATAL_ERROR_UNEXPECTED
        }
#ifdef TRACE_DIFF
        elt->print(std::cout);
#endif //TRACE_DIFF
        free(elt);
        if (lexiconSy->child)
            lexiconSy->child->printStaticFSA(out, lex);
    }
}

/* **************************************************
 // Calculate offsets of the array
 ************************************************** */
void CompactedLexiconTree::setIndexStaticInfo(unsigned long int &index) {
    for (CompactedLexiconTree *lexiconSy = this; lexiconSy != nullptr; lexiconSy = lexiconSy->next) {
        if (lexiconSy->child)
            lexiconSy->child->setIndexStaticInfo(index);
    }
    for (CompactedLexiconTree *lexiconSy = this; lexiconSy != nullptr; lexiconSy = lexiconSy->next) {
        for (CompactedLexiconInfo *infoSy = lexiconSy->info; infoSy != nullptr; infoSy = infoSy->getNext()) {
            infoSy->setAddress(index++);
        }
    }
}

/* **************************************************
 // write the records
 // offsets are calculated on 32 (vs 16) bits if long==1
 ************************************************** */
void CompactedLexiconTree::printStaticInfo(FILE *out) const {
    for (const CompactedLexiconTree *lexiconSy = this; lexiconSy != nullptr; lexiconSy = lexiconSy->next) {
        if (lexiconSy->child)
            lexiconSy->child->printStaticInfo(out);
    }
    for (const CompactedLexiconTree *lexiconSy = this; lexiconSy != nullptr; lexiconSy = lexiconSy->next) {
        for (CompactedLexiconInfo *infoSy = lexiconSy->info; infoSy != nullptr; infoSy = infoSy->getNext()) {
            auto *elt = new CompactedLexiconBuffer(
                    (infoSy->getNext() != nullptr) ? infoSy->getNext()->getAddress() : (unsigned long int) (~(0UL)),
                    infoSy->getOffset());
            if (!fwrite(elt, sizeof(CompactedLexiconBuffer), 1, out)) {
                FATAL_ERROR_UNEXPECTED
            }
#ifdef TRACE_DIFF
            std::cout << infoSy->getAddress() << ' ';
            elt->print(std::cout);
#endif //TRACE_DIFF
        }
    }
}

/* **************************************************
 // add a word
 ************************************************** */
void CompactedLexiconTree::add(const char *str, unsigned long int offset) {
    if (!this->character) {
        this->character = str[0];
        if (!str[1]) {
            this->info = new CompactedLexiconInfo(this->info, offset);
        } else {
            if (!this->child)
                this->child = new CompactedLexiconTree(nullptr, nullptr, nullptr, str[1]);
            this->child->add((char *) str + 1, offset);
        }
    } else if (this->character == str[0]) {
        if (!str[1]) {
            this->info = new CompactedLexiconInfo(this->info, offset);
        } else {
            if (!this->child)
                this->child = new CompactedLexiconTree(nullptr, nullptr, nullptr, str[1]);
            this->child->add((char *) str + 1, offset);
        }
    } else if (this->next)
        this->next->add(str, offset);
    else {
        this->next = new CompactedLexiconTree(nullptr, nullptr, nullptr, str[0]);
        this->next->add(str, offset);
    }
}
