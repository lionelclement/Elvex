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

#ifndef COMPACTEDLEXICON_H
#define COMPACTEDLEXICON_H

#define SEP_PREF ""
#define SEP_UW "UNKNOWN"
#define SEP_SUFF "\n"
#define SEP_OR "|"

#include <string>
#include <iostream>
#include "compacted-lexicon-tree.hpp"
#include "lexicon.hpp"

extern bool isLexString;
extern char *lexString;
extern char *currentLexString;

extern class Entry *localEntry;

/**
 * Builds, stores and queries the finite-state representation of lexical entries.
 * The index identifies candidate analyses; feature constraints are checked later
 * by the generator, not by this lexical search.
 */
class CompactedLexicon
{

private:
std::string filePrefix;
    FILE *fsaFile;
    std::string fsaFileName;
    FILE *dataFile;
    std::string dataFileName;
    std::istream *inputStream = &std::cin;
    CompactedLexiconTree *compactedLexicon;

public:
    char *buffer;
    struct CompactedLexiconFsa *fsa;
    struct CompactedLexiconBuffer *info;
    uint32_t init;
    class CompactedLexiconTree *lexiconInit;

public:
    CompactedLexicon(const std::string &filePrefix);

    /** Decode all alternatives from a lexical payload link into the stream. */
    void printResults(std::ostream &, uint32_t index, bool sep) const;

    /**
     * Follow the FSA from a given node and return its lexical payload link.
     * The sentinel value denotes an absent lexical key.
     */
    uint32_t search(uint32_t index, const std::string &) const;

    /** Serialize the constructed trie and metadata to the compacted index. */
    void saveFsa(bool verbose);

    /** Load the serialized index and verify its binary format compatibility. */
    void loadFsa(bool verbose);

    void openFiles(const std::string &mode);

    void closeFiles();

    /** Unify two feature descriptions while constructing a lexical entry. */
    static std::string unif(const std::string &fs1, const std::string &fs2, bool verbose);

    void addToData(const std::string &entry, const std::string &form, const std::string &features);

    void addPattern(Lexicon &pattern, Lexicon &morpho, const std::string &input, const std::string &fs, const std::string &lemma,
                    const std::string &pos, bool verbose);

    void addForms(const std::string &input, std::string inputSearch, const std::string &features, Lexicon &morpho, bool verbose);

    /** Combine lexical patterns and morphology into indexable entries. */
    void buildEntries(class Lexicon &pattern, class Lexicon &morpho, bool verbose);

    void loadData(bool verbose);

    void consult();

    void print(std::ostream &);

private:
    void print(unsigned int, const std::string &, std::ostream &);
};

#endif // COMPACTEDLEXICON_H
