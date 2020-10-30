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

#include <sys/stat.h>
#include <cstring>
#include <cmath>
#include <utility>

#include "compacted-lexicon.hpp"
#include "compacted-lexicon-tree.hpp"
#include "compacted-lexicon-fsa.hpp"
#include "compacted-lexicon-buffer.hpp"
#include "messages.hpp"
#include "vartable.hpp"
#include "entries.hpp"
#include "entry.hpp"
#include "lexicon.hpp"
#include "parser.hpp"
#include "statement.hpp"

/* **************************************************
 *
 ************************************************** */
CompactedLexicon::CompactedLexicon(std::string directoryName, std::string fileName) {
    this->directoryName = std::move(directoryName);
    this->fileName = std::move(fileName);
    this->dataFile = nullptr;
    this->fsaFile = nullptr;
    this->buffer = nullptr;
    this->fsa = nullptr;
    this->info = nullptr;
    this->init = 0;
    this->compactedLexicon = new CompactedLexiconTree(nullptr, nullptr, nullptr, '\0');
    this->compactedLexicon->setChild(new CompactedLexiconTree(nullptr, nullptr, nullptr, '\0'));
    this->lexiconInit = compactedLexicon;
    this->compactedLexicon = compactedLexicon->getChild();
}

/* **************************************************
 *
 ************************************************** */
void CompactedLexicon::printResults(std::ostream &output, unsigned long int index, bool sep) const {
    char tag[MAXSTRING];
    if (sep)
        output << SEP_PREF;
    if (index == (unsigned long int) (~0UL)) {
        output << SEP_UW;
        if (sep)
            output << SEP_SUFF;
        return;
    }
    while (index != (unsigned long int) (~0UL)) {
        // an other element will be describe
        strcpy(tag, buffer + (info[index].getOffset()));
        output << tag;
        if (info[index].isNext())
            output << SEP_OR;
        if (info[index].isNext())
            index = info[index].getNext();
        else
            index = (unsigned long int) (~0UL);
    }
    if (sep)
        output << SEP_SUFF;
}

////////////////////////////////////////////////////////////
// input: string
// output: info
////////////////////////////////////////////////////////////
unsigned long int CompactedLexicon::searchStatic(unsigned long int index, const std::string &s) const {
    char *str = strdup(s.c_str());
    char *str2 = str;
    index = fsa[index].getChild();
    // for each letter of the suffix
    while (*str) {
        // parse the brothers while founding the actual char
        while (!fsa[index].equalsThisChar(*str)) {
            if (fsa[index].hasNext())
                index = fsa[index].getNext();
            else
                return (unsigned long int) (~0UL);
        }
        if (!fsa[index].equalsThisChar(*str))
            return ((unsigned long int) (~0UL));
        if (*(str + 1)) {
            if (fsa[index].hasChild())
                index = fsa[index].getChild();
            else
                return (unsigned long int) (~0UL);

        } else if (fsa[index].hasInfo())
            return fsa[index].getInfo();
        str++;

    }
    delete str2;
    return (unsigned long int) (~0UL);
}

/* **************************************************
 *
 ************************************************** */
void CompactedLexicon::saveFsa() {
    int nbrBytes = sizeof(unsigned long int);
    std::cerr << "*** Writing Finite State Automata " << std::endl;
    // encodage des offsets (16 ou 32 bits)
    if (!fwrite(&nbrBytes, sizeof(nbrBytes), 1, fsaFile)) FATAL_ERROR_UNEXPECTED
#ifdef TRACE_DIFF
    std::cout << "nbreBytes:" << nbrBytes << std::endl;
#endif //TRACE_DIFF
    auto maxSize = (unsigned long int) ~0UL;
    if (!fwrite(&maxSize, sizeof(maxSize), 1, fsaFile)) FATAL_ERROR_UNEXPECTED
#ifdef TRACE_DIFF
    std::cout << "maxSize:" << maxSize << std::endl;
#endif //TRACE_DIFF
    // nombre d'offsets du fsa
    unsigned long int sizeFsa = 0;
    lexiconInit->setIndexStaticFSA(sizeFsa);
    if (!fwrite(&sizeFsa, sizeof(sizeFsa), 1, fsaFile)) FATAL_ERROR_UNEXPECTED
#ifdef TRACE_DIFF
    std::cout << "sizeFsa:" << sizeFsa << std::endl;
#endif //TRACE_DIFF
    if (sizeFsa == (unsigned long int) ~0UL) {
        std::cerr << "*** Error: Lexicon too large" << std::endl;
        throw "";
    }
    unsigned long int sizeInfo = 0;
    lexiconInit->setIndexStaticInfo(sizeInfo);
    if (!fwrite(&sizeInfo, sizeof(sizeInfo), 1, fsaFile)) FATAL_ERROR_UNEXPECTED
#ifdef TRACE_DIFF
    std::cout << "sizeInfo:" << sizeInfo << std::endl;
#endif //TRACE_DIFF
    if (sizeInfo == (unsigned long int) ~0UL) {
        FATAL_ERROR("*** Error: Data too large")
    }
#ifdef TRACE_DIFF
    std::cout << "---FSA---" << std::endl;
#endif //TRACE_DIFF
    lexiconInit->printStaticFSA(fsaFile, this);

#ifdef TRACE_DIFF
    std::cout << "---Info---" << std::endl;
#endif //TRACE_DIFF
    lexiconInit->printStaticInfo(fsaFile);
    std::cerr << "*** Writing Data" << std::endl;
    // table
    fflush(fsaFile);
    if (!fwrite(&init, sizeof(init), 1, fsaFile)) FATAL_ERROR_UNEXPECTED
#ifdef TRACE_DIFF
    std::cout << "init:" << init << std::endl;
#endif //TRACE_DIFF
}

/* **************************************************
 *
 ************************************************** */
void CompactedLexicon::loadFsa() {
    std::cerr << "*** Loading Finite State Automata" << std::endl;
    int nbrBytes;
    if (!fread(&nbrBytes, sizeof(nbrBytes), 1, fsaFile)) FATAL_ERROR_UNEXPECTED
#ifdef TRACE_DIFF
    std::cout << "nbreBytes:" << nbrBytes << std::endl;
#endif //TRACE_DIFF
    unsigned long int maxSize;
    if (!fread(&maxSize, sizeof(maxSize), 1, fsaFile)) FATAL_ERROR_UNEXPECTED
#ifdef TRACE_DIFF
    std::cout << "maxSize:" << maxSize << std::endl;
#endif //TRACE_DIFF
    if (nbrBytes != (sizeof(unsigned long int)) || (maxSize != (unsigned long int) ~0UL)) {
        FATAL_ERROR("*** lexicon compiled with an incompatible system")
    }
    unsigned long int sizeFsa;
    if (!fread(&sizeFsa, sizeof(sizeFsa), 1, fsaFile)) FATAL_ERROR_UNEXPECTED
#ifdef TRACE_DIFF
    std::cout << "sizeFsa:" << sizeFsa << std::endl;
#endif //TRACE_DIFF
    unsigned long int sizeInfo;
    if (!fread(&sizeInfo, sizeof(sizeInfo), 1, fsaFile)) FATAL_ERROR_UNEXPECTED
#ifdef TRACE_DIFF
    std::cout << "sizeInfo:" << sizeInfo << std::endl;
#endif //TRACE_DIFF

#ifdef TRACE_DIFF
    std::cout << "---FSA---" << std::endl;
#endif //TRACE_DIFF
    fsa = new CompactedLexiconFsa[sizeFsa + 1]();
    if (!fread(fsa, sizeof(CompactedLexiconFsa), sizeFsa, fsaFile)) FATAL_ERROR_UNEXPECTED
#ifdef TRACE_DIFF
    for(unsigned long int sizeSy=0;sizeSy<sizeFsa;sizeSy++) {
       fsa[sizeSy].print(std::cout);
    }
#endif //TRACE_DIFF

#ifdef TRACE_DIFF
    std::cout << "---Info---" << std::endl;
#endif //TRACE_DIFF
    info = new CompactedLexiconBuffer[sizeInfo + 1]();
    if (!fread(info, sizeof(CompactedLexiconBuffer), sizeInfo, fsaFile)) FATAL_ERROR_UNEXPECTED
#ifdef TRACE_DIFF
    for(unsigned long int sizeSy=0;sizeSy<sizeInfo;sizeSy++) {
       std::cout << sizeSy << ' ';
       info[sizeSy].print(std::cout);
    }
#endif //TRACE_DIFF
    if (!fread(&init, sizeof(init), 1, fsaFile)) FATAL_ERROR_UNEXPECTED
#ifdef TRACE_DIFF
    std::cout << "init:" << init << std::endl;
#endif //TRACE_DIFF
}

/* **************************************************
 *
 ************************************************** */
void CompactedLexicon::openFiles(const std::string &mode) {
    std::ostringstream oss;

    oss << this->directoryName << "/" << this->fileName << ".tbl";
    dataFileName = oss.str();
    dataFile = fopen(dataFileName.c_str(), mode.c_str());
    if (dataFile == nullptr) {
        FATAL_ERROR("Unable to open file " << dataFileName << " for writing")
    }

    oss.str("");
    oss << this->directoryName << "/" << this->fileName << ".fsa";
    fsaFileName = oss.str();
    fsaFile = fopen(fsaFileName.c_str(), mode.c_str());
    if (fsaFile == nullptr) {
        FATAL_ERROR("Unable to open file " << fsaFileName << " for writing")
    }
}

/* **************************************************
 *
 ************************************************** */
void CompactedLexicon::closeFiles() {
    fclose(fsaFile);
    fclose(dataFile);
}

/* **************************************************
 *
 ************************************************** */
std::string CompactedLexicon::unif(const std::string &fs1, const std::string &fs2) {
    extern Parser parser;
    std::stringstream stringStream;
    featuresPtr features1;
    if (!fs1.empty()) {
        stringStream.str("");
        stringStream << '[' << fs1 << ']';
        std::string fsString = stringStream.str();
        if (parser.parseBuffer("#", fsString, "morphology")) {
            //stringStream.str("");
            //stringStream <<  << std::endl;
            FATAL_ERROR("error in lexicon: " << fs1)
            //stringStream.str())
        }
        features1 = parser.getLocalFeatures();
    } else
        features1 = featuresPtr();

    featuresPtr features2;
    if (!fs2.empty()) {
        stringStream.str("");
        stringStream << '[' << fs2 << ']';
        std::string fsString = stringStream.str();
        if (parser.parseBuffer("#", fsString, "morphology")) {
            stringStream.str("");
            stringStream << "error in lexicon: " << fs2 << std::endl;
            FATAL_ERROR(stringStream.str())
        }
        features2 = parser.getLocalFeatures();
    } else
        features2 = featuresPtr();

    statementPtr statement;
    featuresPtr unif;
    if (features1 && features2) {
        unif = statement->unif(features1, features2, itemPtr());
    } else if (features1) {
        unif = features1;
    } else {
        unif = features2;
    }
    stringStream.str("");
    if (unif && !unif->isBottom()) {
        unif->flatPrint(stringStream, false);
    }
    return stringStream.str();
}

/* **************************************************
 *
 ************************************************** */
void CompactedLexicon::addToData(const std::string &input, const std::string &form, const std::string &features) {
    //std::cerr << "add:" << form << "[input:" << input << ",form:" << form << ",features:" << features << std::endl;
    std::stringstream stringStream;
    stringStream.str("");
    stringStream << form << '#' << '[' << features << ']';
    std::string output = stringStream.str();
    unsigned long int offset;
    offset = ftell(dataFile);
    compactedLexicon->add(input.c_str(), offset);
    fprintf(dataFile, "%s%c", output.c_str(), 0);
    //std::cerr << output.c_str() << std::endl;
}

/* **************************************************
 *
 ************************************************** */
void CompactedLexicon::addForms(const std::string &input, std::string inputSearch,
                                const std::string &patternFs/*, Lexicon &pattern*/,
                                Lexicon &morpho) {
    //std::cerr << "addForms " << inputSearch << std::endl;

    std::list<std::string> *o = morpho.find(std::move(inputSearch));
    for (std::list<std::string>::const_iterator it = o->begin(); it != o->end(); ++it) {

        char form[MAXSTRING];
        strcpy(form, it->c_str());
        char *rhs = strchr(form, '#');
        *rhs = 0;

        char line[MAXSTRING];
        strcpy(line, it->c_str());
        char *morphoFs = strchr(line, '#') + 1;

        //std::cerr << "addToData " << input << " => " << form << ' ' << unif(patternFs, morphoFs) << std::endl;
        addToData(input, form, unif(patternFs, morphoFs));
    }
}

/* **************************************************
 *
 ************************************************** */
void
CompactedLexicon::addPattern(Lexicon &pattern, Lexicon &morpho, const std::string &input, const std::string &patternFs,
                             const std::string &lemma, const std::string &pos) {
    //std::cerr << "addPattern with " << '(' << input << ',' << patternFs << ',' << lemma << ',' << pos << ')' << std::endl;
    std::stringstream stringStream;
    stringStream.str("");
    stringStream << lemma << '#' << pos;
    std::string inputSearch = std::string(stringStream.str());
    if (morpho.count(inputSearch)) {
        //std::cerr << "addForms with " << inputSearch << '(' << input << ',' << lemma << ',' << pos << ',' << patternFs << ')' << std::endl;
        addForms(input, inputSearch, patternFs/*, pattern*/, morpho);
    } else if (pattern.count(inputSearch)) {
        //std::cerr << "find " << inputSearch << std::endl;
        std::list<std::string> *o = pattern.find(inputSearch);
        for (std::list<std::string>::const_iterator it = o->begin(); it != o->end(); ++it) {
            char patternLemma[MAXSTRING];
            strcpy(patternLemma, it->c_str());
            char *rhs = strchr(patternLemma, '#');
            *rhs = 0;
            char line2[MAXSTRING];
            strcpy(line2, it->c_str());
            std::string pattern2Fs = strchr(line2, '#') + 1;
            if (patternFs != pattern2Fs) {
                //std::cerr << "addPattern with " << inputSearch << '(' << input << ',' << patternLemma << ',' << pos << ',' << patternFs << '-' << pattern2Fs << ')' << std::endl;
                addPattern(pattern, morpho, input, unif(patternFs, pattern2Fs), patternLemma, pos);
            }
        }
    }
}

/* **************************************************
 *
 ************************************************** */
void CompactedLexicon::buildEntries(Lexicon &pattern, Lexicon &morpho) {

    std::stringstream _inputStream;
    std::size_t size = pattern.size();
    std::size_t range = 0;
    for (auto patternIt = pattern.cbegin();
         patternIt != pattern.cend(); ++patternIt) {
        //std::cerr << "pattern:" << patternIt->first << std::endl;
        for (auto it2 : *patternIt->second) {

            //std::cerr << "str:" << it2 << std::endl;

            char lexeme[MAXSTRING];
            strcpy(lexeme, patternIt->first.c_str());
            char *rhs = strchr(lexeme, '#');
            *rhs = 0;

            char line2[MAXSTRING];
            strcpy(line2, patternIt->first.c_str());
            char *pos = strchr(line2, '#') + 1;

            char lemma[MAXSTRING];
            strcpy(lemma, it2.c_str());
            rhs = strchr(lemma, '#');
            *rhs = 0;

            char line4[MAXSTRING];
            strcpy(line4, it2.c_str());
            char *features = strchr(line4, '#') + 1;

            std::string patternFs = ((*features) ? features : std::string());
            //std::cerr << "lexeme:" << lexeme << " patternFs:" << patternFs << " lemma:" << lemma << " pos:" << pos << std::endl;
            addPattern(pattern, morpho, patternIt->first, patternFs, lemma, pos);

        }

        if (!(range++ % 1009)) {
            int k = 40 * range / size;
            std::cerr << " " << round(2.5 * k) << "%[";
            int i = 0;
            for (; i <= k; i++)
                std::cerr << '#';
            for (; i <= 40; i++)
                std::cerr << ' ';
            std::cerr << ']' << "\r";
        }

    }

    std::cerr << " 100%[";
    int i = 0;
    for (; i <= 40; i++)
        std::cerr << '#';
    std::cerr << ']' << std::endl;
}

/* **************************************************
 *
 ************************************************** */
void CompactedLexicon::loadData() {
    std::cerr << "*** Loading Data" << std::endl;
    struct stat *statbuf;
    statbuf = (struct stat *) malloc(sizeof(struct stat));
    stat(dataFileName.c_str(), statbuf);
    size_t size = statbuf->st_size;
    free(statbuf);
    buffer = new char[size];
    buffer[0] = 0;
    if (!fread(buffer, 1, size, dataFile)) FATAL_ERROR_UNEXPECTED
}

/* **************************************************
 *
 ************************************************** */
void CompactedLexicon::consult() {
    unsigned long int _info;
    std::string str;
    while (!this->inputStream->eof()) {
        *this->inputStream >> str;
        _info = searchStatic(init, str);
        printResults(std::cout, _info, 1);
        fflush(stdout);
    }
}

/* **************************************************
 *
 ************************************************** */
void CompactedLexicon::list() {
    list(init + 1, "");
}

/* **************************************************
 *
 ************************************************** */
void CompactedLexicon::list(unsigned int index, std::string prefix) {
    if (fsa[index].hasChild())
        list(fsa[index].getChild(), prefix + fsa[index].getCharacter());
    if (fsa[index].hasNext())
        list(fsa[index].getNext(), prefix);
    if (fsa[index].hasInfo()) {
        std::cout << prefix + fsa[index].getCharacter() << '\t';
        this->printResults(std::cout, fsa[index].getInfo(), false);
        std::cout << std::endl;
    }
}
