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

#include <sys/stat.h>
#include <cstring>
#include <cmath>
#include <utility>
#include <string>
#include <ostream>
#include <sstream>

#include "compacted-lexicon.hpp"
#include "compacted-lexicon-tree.hpp"
#include "compacted-lexicon-fsa.hpp"
#include "compacted-lexicon-buffer.hpp"
#include "messages.hpp"
// #include "vartable.hpp"
// #include "entries.hpp"
// #include "entry.hpp"
// #include "lexicon.hpp"
#include "parser.hpp"
#include "statement.hpp"
#include "parser_exception.hpp"

/* **************************************************
 *
 ************************************************** */
CompactedLexicon::CompactedLexicon(std::string &directoryName, std::string &fileName)
{
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
void CompactedLexicon::printResults(std::ostream &output, uint32_t index, bool sep) const
{
    if (sep)
        output << SEP_PREF;

    if (index == static_cast<uint32_t>(~0UL))
    {
        output << SEP_UW;
        if (sep)
            output << SEP_SUFF;
        return;
    }

    while (index != static_cast<uint32_t>(~0UL))
    {
        // An element will be described.
        const char *tag = buffer + info[index].getOffset();
        output << tag;

        if (info[index].isNext())
            output << SEP_OR;

        if (info[index].isNext())
            index = info[index].getNext();
        else
            index = static_cast<uint32_t>(~0UL);
    }

    if (sep)
        output << SEP_SUFF;
}

////////////////////////////////////////////////////////////
// input: string
// output: info
////////////////////////////////////////////////////////////
uint32_t CompactedLexicon::search(uint32_t index, const std::string &s) const
{
    char *str = strdup(s.c_str());
    char *str2 = str;
    index = fsa[index].getChild();
    // for each letter of the suffix
    while (*str)
    {
        // parse the brothers while founding the actual char
        while (!fsa[index].equalsThisChar(*str))
        {
            if (fsa[index].hasNext())
                index = fsa[index].getNext();
            else
                return (uint32_t)(~0UL);
        }
        if (!fsa[index].equalsThisChar(*str))
            return ((uint32_t)(~0UL));
        if (*(str + 1))
        {
            if (fsa[index].hasChild())
                index = fsa[index].getChild();
            else
                return (uint32_t)(~0UL);
        }
        else if (fsa[index].hasInfo())
            return fsa[index].getInfo();
        str++;
    }
    free(str2);
    return (uint32_t)(~0UL);
}

/* **************************************************
 *
 ************************************************** */
void CompactedLexicon::saveFsa(bool verbose)
{
    int nbrBytes = sizeof(uint32_t);
    if (verbose)
        std::cout << "*** writing Finite State Automata " << std::endl;
    // encodage des offsets (16 ou 32 bits)
    if (!fwrite(&nbrBytes, sizeof(nbrBytes), 1, fsaFile))
        FATAL_ERROR_UNEXPECTED
#ifdef TRACE_DIFF
    std::cout << "nbreBytes:" << nbrBytes << std::endl;
#endif // TRACE_DIFF
    auto maxSize = (uint32_t)~0UL;
    if (!fwrite(&maxSize, sizeof(maxSize), 1, fsaFile))
        FATAL_ERROR_UNEXPECTED
#ifdef TRACE_DIFF
    std::cout << "maxSize:" << maxSize << std::endl;
#endif // TRACE_DIFF
    // nombre d'offsets du fsa
    uint32_t sizeFsa = 0;
    lexiconInit->setIndexStaticFSA(sizeFsa);
    if (!fwrite(&sizeFsa, sizeof(sizeFsa), 1, fsaFile))
        FATAL_ERROR_UNEXPECTED
#ifdef TRACE_DIFF
    std::cout << "sizeFsa:" << sizeFsa << std::endl;
#endif // TRACE_DIFF
    if (sizeFsa == (uint32_t)~0UL)
    {
        std::cerr << "*** Error: Lexicon too large" << std::endl;
        throw "";
    }
    uint32_t sizeInfo = 0;
    lexiconInit->setIndexStaticInfo(sizeInfo);
    if (!fwrite(&sizeInfo, sizeof(sizeInfo), 1, fsaFile))
        FATAL_ERROR_UNEXPECTED
#ifdef TRACE_DIFF
    std::cout << "sizeInfo:" << sizeInfo << std::endl;
#endif // TRACE_DIFF
    if (sizeInfo == (uint32_t)~0UL)
    {
        throw fatal_exception("Data too large");
    }
#ifdef TRACE_DIFF
    std::cout << "---FSA---" << std::endl;
#endif // TRACE_DIFF
    lexiconInit->printStaticFSA(fsaFile, this);

#ifdef TRACE_DIFF
    std::cout << "---Info---" << std::endl;
#endif // TRACE_DIFF
    lexiconInit->printStaticInfo(fsaFile);
    if (verbose)
        std::cout << "*** writing Data" << std::endl;
    // table
    fflush(fsaFile);
    if (!fwrite(&init, sizeof(init), 1, fsaFile))
        FATAL_ERROR_UNEXPECTED;
#ifdef TRACE_DIFF
    std::cout << "init:" << init << std::endl;
#endif // TRACE_DIFF
}

/* **************************************************
 *
 ************************************************** */
void CompactedLexicon::loadFsa(bool verbose)
{
    if (verbose)
        std::cout << "*** loading Finite State Automata" << std::endl;
    int nbrBytes;
    if (!fread(&nbrBytes, sizeof(nbrBytes), 1, fsaFile))
        FATAL_ERROR_UNEXPECTED;
#ifdef TRACE_DIFF
    std::cout << "nbreBytes:" << nbrBytes << std::endl;
#endif // TRACE_DIFF
    uint32_t maxSize;
    if (!fread(&maxSize, sizeof(maxSize), 1, fsaFile))
        FATAL_ERROR_UNEXPECTED;
#ifdef TRACE_DIFF
    std::cout << "maxSize:" << maxSize << std::endl;
#endif // TRACE_DIFF
    if (nbrBytes != (sizeof(uint32_t)) || (maxSize != (uint32_t)~0UL))
    {
        throw fatal_exception("lexicon compiled with an incompatible system");
    }
    uint32_t sizeFsa;
    if (!fread(&sizeFsa, sizeof(sizeFsa), 1, fsaFile))
        FATAL_ERROR_UNEXPECTED;
#ifdef TRACE_DIFF
    std::cout << "sizeFsa:" << sizeFsa << std::endl;
#endif // TRACE_DIFF
    uint32_t sizeInfo;
    if (!fread(&sizeInfo, sizeof(sizeInfo), 1, fsaFile))
        FATAL_ERROR_UNEXPECTED;
#ifdef TRACE_DIFF
    std::cout << "sizeInfo:" << sizeInfo << std::endl;
#endif // TRACE_DIFF

#ifdef TRACE_DIFF
    std::cout << "---FSA---" << std::endl;
#endif // TRACE_DIFF
    fsa = new CompactedLexiconFsa[sizeFsa + 1]();
    if (!fread(fsa, sizeof(CompactedLexiconFsa), sizeFsa, fsaFile))
        FATAL_ERROR_UNEXPECTED;
#ifdef TRACE_DIFF
    for (uint32_t sizeSy = 0; sizeSy < sizeFsa; sizeSy++)
    {
        fsa[sizeSy].print(std::cout);
    }
#endif // TRACE_DIFF

#ifdef TRACE_DIFF
    std::cout << "---Info---" << std::endl;
#endif // TRACE_DIFF
    info = new CompactedLexiconBuffer[sizeInfo + 1]();
    if (!fread(info, sizeof(CompactedLexiconBuffer), sizeInfo, fsaFile))
        FATAL_ERROR_UNEXPECTED;
#ifdef TRACE_DIFF
    for (uint32_t sizeSy = 0; sizeSy < sizeInfo; sizeSy++)
    {
        std::cout << sizeSy << ' ';
        info[sizeSy].print(std::cout);
    }
#endif // TRACE_DIFF
    if (!fread(&init, sizeof(init), 1, fsaFile))
        FATAL_ERROR_UNEXPECTED
#ifdef TRACE_DIFF
    std::cout << "init:" << init << std::endl;
#endif // TRACE_DIFF
}

/* **************************************************
 *
 ************************************************** */
void CompactedLexicon::openFiles(const std::string &mode)
{
    std::ostringstream oss;

    oss << this->directoryName << "/" << this->fileName << ".tbl";
    dataFileName = oss.str();
    dataFile = fopen(dataFileName.c_str(), mode.c_str());
    if (dataFile == nullptr)
    {
        std::ostringstream oss;
        oss << "Unable to open file " << dataFileName << " for writing";
        throw fatal_exception(oss);
    }

    oss.str("");
    oss << this->directoryName << "/" << this->fileName << ".fsa";
    fsaFileName = oss.str();
    fsaFile = fopen(fsaFileName.c_str(), mode.c_str());
    if (fsaFile == nullptr)
    {
        std::ostringstream oss;
        oss << "Unable to open file " << fsaFileName << " for writing";
        throw fatal_exception(oss);
    }
}

/* **************************************************
 *
 ************************************************** */
void CompactedLexicon::closeFiles()
{
    fclose(fsaFile);
    fclose(dataFile);
}

/* **************************************************
 *
 ************************************************** */
std::string CompactedLexicon::unif(const std::string &fs1, const std::string &fs2, bool verbose)
{
    extern Parser parser;
    std::stringstream stringStream;
    featuresPtr features1;
    if (!fs1.empty())
    {
        // CERR_LINE;
        // std::cerr << fs1 << std::endl;
        stringStream.str("");
        stringStream << '[' << fs1 << ']';
        std::string fsString = stringStream.str();
        try
        {
            parser.parseBuffer("#(", ")", fsString, "morphology");
        }
        catch (parser_exception &e)
        {
            std::ostringstream oss;
            oss << e.what() << ":\"" << fs1 << "\"";
            throw fatal_exception(oss);
        }
        features1 = parser.getLocalFeatures();
    }
    else
    {
        // CERR_LINE;
        features1 = featuresPtr();
    }

    featuresPtr features2;
    if (!fs2.empty())
    {
        // CERR_LINE;
        // std::cerr << fs2 << std::endl;
        stringStream.str("");
        stringStream << '[' << fs2 << ']';
        std::string fsString = stringStream.str();
        try
        {
            parser.parseBuffer("#(", ")", fsString, "morphology");
        }
        catch (parser_exception &e)
        {
            std::ostringstream oss;
            oss << e.what() << ":\"" << fs2 << "\"";
            throw fatal_exception(oss);
        }
        features2 = parser.getLocalFeatures();
    }
    else
    {
        // CERR_LINE;
        features2 = featuresPtr();
    }

    statementPtr statement;
    featuresPtr unif;
    if (features1 && features2)
    {
        unif = statement->unif(statement, features1, features2, nullptr, verbose);
    }
    else if (features1)
    {
        unif = features1;
    }
    else
    {
        unif = features2;
    }
    stringStream.str("");
    if (unif && !unif->isBottom())
    {
        // CERR_LINE;
        // unif->flatPrint(std::cerr, false);

        unif->flatPrint(stringStream, false);
    }
    features1.reset();
    features2.reset();
    unif.reset();
    return stringStream.str();
}

/* **************************************************
 *
 ************************************************** */
void CompactedLexicon::addToData(const std::string &input, const std::string &form, const std::string &features)
{
    //CERR_LINE;
    //std::cerr << "CompactedLexicon::addToData:"
    //          << "[input:" << input << ",form:" << form << ",features:" << features << std::endl;
    std::stringstream stringStream;
    stringStream.str("");
    stringStream << form << '#' << '[' << features << ']';
    std::string output = stringStream.str();
    uint32_t offset;
    offset = ftell(dataFile);
    compactedLexicon->add(input.c_str(), offset);
    fprintf(dataFile, "%s%c", output.c_str(), 0);
    // std::cerr << output.c_str() << std::endl;
}

/* **************************************************
 *
 ************************************************** */
void CompactedLexicon::addForms(const std::string &input, std::string inputSearch,
                                const std::string &features,
                                Lexicon &morpho, bool verbose)
{
    // CERR_LINE
    // std::cerr << "CompactedLexicon::addForms[input:" << input << ",inputSearch:" << inputSearch << ",features:" << features << ']' << std::endl;
    std::vector<std::string> o = morpho.find(std::move(inputSearch));
    for (std::vector<std::string>::const_iterator it = o.cbegin(); it != o.cend(); ++it)
    {

        std::string form = *it;
        // CERR_LINE
        // std::cerr << "form found: [" << form << "]" << std::endl;
        auto rhsPos = form.find('#');
        if (rhsPos != std::string::npos)
        {
            std::string form2 = form.substr(0, rhsPos);
            std::string morphoFs = form.substr(rhsPos + 1);
            addToData(input, form2, unif(features, morphoFs, verbose));
        }
    }
}

/* **************************************************
 *
 ************************************************** */
void CompactedLexicon::addPattern(Lexicon &pattern, Lexicon &morpho, const std::string &input, const std::string &features,
                                  const std::string &lemma, const std::string &pos, bool verbose)
{
    // CERR_LINE;
    // std::cerr << "addPattern with " << "[input:" << input << ";features:\"" << features << "\";lemma:\"" << lemma << "\";pos:\"" << pos << "\"]" << std::endl;
    std::stringstream stringStream;
    stringStream.str("");
    stringStream << pos << '#' << lemma;
    std::string inputSearch = std::string(stringStream.str());
    if (morpho.count(inputSearch))
    {
        addForms(input, inputSearch, features, morpho, verbose);
    }
    else if (pattern.count(inputSearch))
    {
        std::vector<std::string> o = pattern.find(inputSearch);
        for (auto &it : o)
        {
            std::string patternLemma = it;
            auto rhsPos = patternLemma.find('#');
            if (rhsPos != std::string::npos)
            {
                std::string features2 = patternLemma.substr(rhsPos + 1);
                if (features != features2)
                {
                    // CERR_LINE;
                    // std::cerr << "addPattern with " << inputSearch << '(' << input << ',' << patternLemma << ',' << pos << ',' << features << '-' << features2 << ')' << std::endl;
                    addPattern(pattern, morpho, input, unif(features, features2, verbose), patternLemma, pos, verbose);
                }
            }
        }
    }
}

/* **************************************************
 *
 ************************************************** */
void CompactedLexicon::buildEntries(Lexicon &pattern, Lexicon &morpho, bool verbose)
{
    std::size_t size = pattern.size();
    std::size_t range = 0;

    for (auto patternIt = pattern.cbegin(); patternIt != pattern.cend(); ++patternIt)
    {
        // CERR_LINE;
        // std::cerr << patternIt->first << std::endl;

        // Extraire la partie "pos" de la clé
        std::string pos = patternIt->first;
        auto rhsPos = pos.find('#');
        if (rhsPos != std::string::npos)
        {
            pos.resize(rhsPos); // Tronquer la chaîne à la position de '#'
        }

        // CERR_LINE;
        // std::cerr << '[' << pos << ']' << std::endl;
        for (const auto &it2 : patternIt->second)
        {
            // Extraire la partie "lemma" de la valeur
            std::string lemma = it2;
            auto lemmaPos = lemma.find('#');
            if (lemmaPos != std::string::npos)
            {
                lemma.resize(lemmaPos); // Tronquer la chaîne à la position de '#'
            }

            // CERR_LINE;
            // std::cerr << '[' << lemma << ']' << std::endl;
            //  Extraire la partie "features" de la valeur
            std::string features;
            if (lemmaPos != std::string::npos)
            {
                features = it2.substr(lemmaPos + 1); // Prendre tout après '#'
            }

            // CERR_LINE;
            // std::cerr << '[' << features << ']' << std::endl;
            // void CompactedLexicon::addPattern(Lexicon &pattern, Lexicon &morpho, const std::string &input, const std::string &features,
            //                       const std::string &lemma, const std::string &pos)

            addPattern(pattern, morpho, patternIt->first, features, lemma, pos, verbose);
        }

        if ((range++ % 1009) == 0)
        {
            unsigned int k = 40 * range / size;
            std::cerr << " " << round(2.5 * k) << "%[";
            int i = 0;
            while (i++ <= k)
                std::cerr << '#';
            while (i++ <= 40)
                std::cerr << ' ';
            std::cerr << "]\r";
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
void CompactedLexicon::loadData(bool verbose)
{
    if (verbose)
        std::cout << "*** loading Data" << std::endl;
    struct stat *statbuf;
    statbuf = (struct stat *)malloc(sizeof(struct stat));
    stat(dataFileName.c_str(), statbuf);
    size_t size = statbuf->st_size;
    free(statbuf);
    buffer = new char[size];
    buffer[0] = 0;
    if (!fread(buffer, 1, size, dataFile))
        FATAL_ERROR_UNEXPECTED
}

/* **************************************************
 *
 ************************************************** */
void CompactedLexicon::consult()
{
    uint32_t _info;
    std::string str;
    while (!this->inputStream->eof())
    {
        *this->inputStream >> str;
        _info = search(init, str);
        printResults(std::cout, _info, true);
        fflush(stdout);
    }
}

/* **************************************************
 *
 ************************************************** */
void CompactedLexicon::print(std::ostream &os)
{
    print(init + 1, "", os);
}

/* **************************************************
 *
 ************************************************** */
void CompactedLexicon::print(unsigned int index, const std::string &prefix, std::ostream &os)
{
    if (fsa[index].hasChild())
        print(fsa[index].getChild(), prefix + fsa[index].getCharacter(), os);
    if (fsa[index].hasNext())
        print(fsa[index].getNext(), prefix, os);
    if (fsa[index].hasInfo())
    {
        os << prefix + fsa[index].getCharacter() << "\t=>\t";
        this->printResults(os, fsa[index].getInfo(), false);
        os << std::endl;
    }
}
