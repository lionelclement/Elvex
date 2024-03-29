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

class CompactedLexicon
{

private:
    std::string directoryName;
    std::string fileName;
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
    CompactedLexicon(std::string &directoryName, std::string &fileName);

    void printResults(std::ostream &, uint32_t index, bool sep) const;

    uint32_t search(uint32_t index, const std::string &) const;

    void saveFsa(bool verbose);

    void loadFsa(bool verbose);

    void openFiles(const std::string &mode);

    void closeFiles();

    static std::string unif(const std::string &fs1, const std::string &fs2, bool verbose);

    void addToData(const std::string &entry, const std::string &form, const std::string &features);

    void addPattern(Lexicon &pattern, Lexicon &morpho, const std::string &input, const std::string &fs, const std::string &lemma,
                    const std::string &pos, bool verbose);

    void addForms(const std::string &input, std::string inputSearch, const std::string &features, Lexicon &morpho, bool verbose);

    void buildEntries(class Lexicon &pattern, class Lexicon &morpho, bool verbose);

    void loadData(bool verbose);

    void consult();

    void print(std::ostream &);

private:
    void print(unsigned int, const std::string &, std::ostream &);
};

#endif // COMPACTEDLEXICON_H
