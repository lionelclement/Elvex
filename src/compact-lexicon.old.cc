/* **************************************************
 *
 * ELVEX
 *
 * Copyright 2019 LABRI, 
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
#include <string.h>
#include <cmath>

#include "compact-lexicon.hh"
#include "compact-lexicon-tree.hh"
#include "compact-lexicon-fsa.hh"
#include "compact-lexicon-buffer.hh"
#include "messages.hh"
#include "vartable.hh"
#include "entries.hh"
#include "entry.hh"
#include "lexicon.hh"
#include "parser.hh"
#include "statement.hh"

/* **************************************************
 *
 ************************************************** */
CompactLexicon::CompactLexicon(std::string directoryName, std::string fileName) {
   this->directoryName = directoryName;
   this->fileName = fileName;
   this->dataFile = NULL;
   this->fsaFile = NULL;
   this->buffer = NULL;
   this->fsa = NULL;
   this->info = NULL;
   this->init = 0;
   this->InputFileStreamSize = 0;
   this->compactLexicon = new CompactLexiconTree(NULL, NULL, NULL, '\0');
   this->compactLexicon->setChild(new CompactLexiconTree(NULL, NULL, NULL, '\0'));
   this->lexiconInit = compactLexicon;
   this->compactLexicon = compactLexicon->getChild();
}

/* **************************************************
 *
 ************************************************** */
CompactLexicon::CompactLexicon(std::string directoryName, std::string fileName, const std::string inputFileName)
      : CompactLexicon(directoryName, fileName) {
   if (inputFileName.size() == 0) {
      std::cerr << "*** Searching from stdin" << std::endl;
      this->inputStream = &std::cin;
   }
   else {
      this->inputFile.open(inputFileName, std::ifstream::in);
      if (!this->inputFile.is_open()) {
         throw(new std::string("arg"));
      }
      this->inputStream = &this->inputFile;
      this->inputFile.seekg(0, std::ios::end);
      this->InputFileStreamSize = this->inputFile.tellg();
      this->inputFile.seekg(0, std::ios::beg);
   }
}

/* **************************************************
 *
 ************************************************** */
void CompactLexicon::printResults(std::ostream &output, unsigned long int index, bool sep) const {
   char tag[MAXSTRING];
   if (sep)
      output << SEP_PREF;
   if (index == (unsigned long int)(~0UL)) {
      output << SEP_UW;
      if (sep)
         output << SEP_SUFF;
      return;
   }
   while (index != (unsigned long int)(~0UL)) {
      // an other element will be describe
      strcpy(tag, buffer + (info[index].getOffset()));
      output << tag;
      if (info[index].isNext())
         output << SEP_OR;
      if (info[index].isNext())
         index = info[index].getNext();
      else
         index = (unsigned long int)(~0UL);
   }
   if (sep)
      output << SEP_SUFF;
}

////////////////////////////////////////////////////////////
// input: string
// output: info
////////////////////////////////////////////////////////////
unsigned long int CompactLexicon::searchStatic(unsigned long int index, std::string s) const {
   char *str = strdup(s.c_str());
   char *str2 = str;
   index = fsa[index].getChild();
   // for each letter of the suffix
   while (*str) {
      // parse the brothers while founding the actual char
      while (!fsa[index].isThisChar(*str)) {
         if (fsa[index].isSibling())
            index = fsa[index].getSibling();
         else
            return (unsigned long int)(~0UL);
      }
      if (!fsa[index].isThisChar(*str))
         return ((unsigned long int)(~0UL));
      if (*(str + 1)) {
         if (fsa[index].isChild())
            index = fsa[index].getChild();
         else
            return (unsigned long int)(~0UL);

      }
      else if (fsa[index].isInfo())
         return fsa[index].getInfo();
      str++;

   }
   delete str2;
   return (unsigned long int)(~0UL);
}

/* **************************************************
 *
 ************************************************** */
void CompactLexicon::saveFsa() {
   int nbrBytes = sizeof(unsigned long int);
   std::cerr << "*** Writing Finite State Automata " << std::endl;
   // encodage des offsets (16 ou 32 bits)
   if (!fwrite(&nbrBytes, sizeof(nbrBytes), 1, fsaFile))
      UNEXPECTED
#ifdef TRACE_DIFF
            std::cout << "nbreBytes:" << nbrBytes << std::endl;
#endif //TRACE_DIFF
   unsigned long int maxSize = (unsigned long int)~0UL;
   if (!fwrite(&maxSize, sizeof(maxSize), 1, fsaFile))
      UNEXPECTED
#ifdef TRACE_DIFF
            std::cout << "maxSize:" << maxSize << std::endl;
#endif //TRACE_DIFF
            // nombre d'offsets du fsa
   unsigned long int sizeFsa = 0;
   lexiconInit->setIndexStaticFSA(sizeFsa);
   if (!fwrite(&sizeFsa, sizeof(sizeFsa), 1, fsaFile))
      UNEXPECTED
#ifdef TRACE_DIFF
            std::cout << "sizeFsa:" << sizeFsa << std::endl;
#endif //TRACE_DIFF
   if (sizeFsa == (unsigned long int)~0UL) {
      std::cerr << "*** Error: Lexicon too large" << std::endl;
      throw "";
   }
   unsigned long int sizeInfo = 0;
   lexiconInit->setIndexStaticInfo(sizeInfo);
   if (!fwrite(&sizeInfo, sizeof(sizeInfo), 1, fsaFile))
      UNEXPECTED
#ifdef TRACE_DIFF
            std::cout << "sizeInfo:" << sizeInfo << std::endl;
#endif //TRACE_DIFF
   if (sizeInfo == (unsigned long int)~0UL) {
      std::cerr << "*** Error: Data too large" << std::endl;
      throw "";
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
   if (!fwrite(&init, sizeof(init), 1, fsaFile))
      UNEXPECTED
#ifdef TRACE_DIFF
            std::cout << "init:" << init << std::endl;
#endif //TRACE_DIFF
}

/* **************************************************
 *
 ************************************************** */
void CompactLexicon::loadFsa() {
   std::cerr << "*** Loading Finite State Automata" << std::endl;
   int nbrBytes;
   if (!fread(&nbrBytes, sizeof(nbrBytes), 1, fsaFile))
      UNEXPECTED
#ifdef TRACE_DIFF
            std::cout << "nbreBytes:" << nbrBytes << std::endl;
#endif //TRACE_DIFF
   unsigned long int maxSize;
   if (!fread(&maxSize, sizeof(maxSize), 1, fsaFile))
      UNEXPECTED
#ifdef TRACE_DIFF
            std::cout << "maxSize:" << maxSize << std::endl;
#endif //TRACE_DIFF
   if (nbrBytes != (sizeof(unsigned long int)) || (maxSize != (unsigned long int)~0UL)) {
      std::cerr << "*** lexicon compiled with an incompatible system" << std::endl;
      throw "";
   }
   unsigned long int sizeFsa;
   if (!fread(&sizeFsa, sizeof(sizeFsa), 1, fsaFile))
      UNEXPECTED
#ifdef TRACE_DIFF
            std::cout << "sizeFsa:" << sizeFsa << std::endl;
#endif //TRACE_DIFF
   unsigned long int sizeInfo;
   if (!fread(&sizeInfo, sizeof(sizeInfo), 1, fsaFile))
      UNEXPECTED
#ifdef TRACE_DIFF
            std::cout << "sizeInfo:" << sizeInfo << std::endl;
#endif //TRACE_DIFF

#ifdef TRACE_DIFF
            std::cout << "---FSA---" << std::endl;
#endif //TRACE_DIFF
   fsa = new CompactLexiconFsa[sizeFsa + 1]();
   if (!fread(fsa, sizeof(CompactLexiconFsa), sizeFsa, fsaFile))
      UNEXPECTED
#ifdef TRACE_DIFF
            for(unsigned long int sizeSy=0;sizeSy<sizeFsa;sizeSy++) {
               fsa[sizeSy].print(std::cout);
            }
#endif //TRACE_DIFF

#ifdef TRACE_DIFF
            std::cout << "---Info---" << std::endl;
#endif //TRACE_DIFF
   info = new CompactLexiconBuffer[sizeInfo + 1]();
   if (!fread(info, sizeof(CompactLexiconBuffer), sizeInfo, fsaFile))
      UNEXPECTED
#ifdef TRACE_DIFF
            for(unsigned long int sizeSy=0;sizeSy<sizeInfo;sizeSy++) {
               std::cout << sizeSy << ' ';
               info[sizeSy].print(std::cout);
            }
#endif //TRACE_DIFF
   if (!fread(&init, sizeof(init), 1, fsaFile))
      UNEXPECTED
#ifdef TRACE_DIFF
            std::cout << "init:" << init << std::endl;
#endif //TRACE_DIFF
}

/* **************************************************
 *
 ************************************************** */
void CompactLexicon::openFiles(std::string mode) {
   std::ostringstream oss;

   oss << this->directoryName << "/" << this->fileName << ".tbl";
   dataFileName = oss.str();
   dataFile = fopen(dataFileName.c_str(), mode.c_str());
   if (dataFile == NULL) {
      std::cerr << "Unable to open file " << dataFileName << " for writing" << std::endl;
      throw "";
   }

   oss.str("");
   oss << this->directoryName << "/" << this->fileName << ".fsa";
   fsaFileName = oss.str();
   fsaFile = fopen(fsaFileName.c_str(), mode.c_str());
   if (fsaFile == NULL) {
      std::cerr << "Unable to open file " << fsaFileName << " for writing" << std::endl;
      throw "";
   }
}

/* **************************************************
 *
 ************************************************** */
void CompactLexicon::closeFiles() {
   fclose(fsaFile);
   fclose(dataFile);
}

/* **************************************************
 *
 ************************************************** */
void CompactLexicon::buildPredEntries(Lexicon &lexicon) {
   extern Parser parser;
   std::stringstream inputStream;
   unsigned long int offset;
   for (Lexicon::unordered_map::const_iterator it = lexicon.unordered_map.begin(); it != lexicon.unordered_map.end(); ++it) {
      offset = ftell(dataFile);
      compactLexicon->add(it->first.c_str(), offset);
      for (std::list<std::string>::const_iterator it2 = it->second->begin(); it2 != it->second->end(); ++it2) {
         std::stringstream fsStream;
         fsStream << '[' << *it2 << "]";
         if (parser.parseBuffer("#", fsStream.str().c_str(), "features")) {
            std::stringstream errorStream;
            errorStream << "*** error in lexicon: " << it->first << " => " << fsStream.str() << std::endl;
            throw std::string(errorStream.str());
         }
         featuresPtr features = parser.getLocalFeatures();
         inputStream.str("");
         inputStream << '[';
         features->flatPrint(inputStream, false);
         inputStream << ']';
         fprintf(dataFile, "%s%c", inputStream.str().c_str(), 0);
      }
   }
}

/* **************************************************
 *
 ************************************************** */
void CompactLexicon::addForms(Lexicon &lexicon, std::string line, std::string form, std::string input, std::string pos, std::string predicate, std::string morpho) {

   //std::cerr << "addForms(" << " form:" << form << " input:" << input << " pos:" << pos << " predicate:" << predicate << " morpho:" << morpho << ")" << std::endl;


   unsigned long int offset;
   std::stringstream stringStream;

   extern Parser parser;
   featuresPtr features;
   if (morpho.size()) {
      std::stringstream fsStream;
      fsStream << '[' << morpho << ']';
      std::string fsString = fsStream.str();
      if (parser.parseBuffer("#", fsString, "morphology")) {
         fsStream.str("");
         fsStream << "error in lexicon: " << line << std::endl;
         ERROR(fsStream.str())
      }
      features = parser.getLocalFeatures();
   }
   else
      features = featuresPtr();

   stringStream.str("");
   stringStream << form << "#[";
   if (morpho.size()) {
      parser.getLocalFeatures()->flatPrint(stringStream, false);
   }
   stringStream << ']';
   std::string output =  stringStream.str();

   stringStream.str("");
   stringStream << pos << "#_" << predicate;
   std::string inputSearch = std::string(stringStream.str());
   //std::cerr << "Search " << inputSearch << std::endl;
   std::list<std::string> *o = lexicon.find(inputSearch);
   if (o->size()) {
      //features->flatPrint(std::cerr);
      //std::cerr << "OK" << std::endl;

      for (std::list<std::string>::const_iterator it = o->cbegin(); it != o->cend(); ++it) {

         char predicatePattern[MAXSTRING];
         strcpy(predicatePattern, it->c_str());
         char *rhs = strchr(predicatePattern, '#');
         *rhs = 0;

         char fsPatternLine[MAXSTRING];
         strcpy(fsPatternLine, it->c_str());
         char *fsPattern = strchr(fsPatternLine, '#') + 1;
         stringStream.str("");
         stringStream << '[' << fsPattern << ']';
         std::string fsPatternString = stringStream.str();
         if (parser.parseBuffer("#", fsPatternString, "features"))
            std::cerr << "*** error in pattern: " << fsPatternString << std::endl;
         featuresPtr featuresPattern = parser.getLocalFeatures();

         stringStream.str("");
         stringStream << pos << "#_" << predicatePattern;
         std::string input3 = std::string(stringStream.str());

         statementPtr statement;
         featuresPtr unif;
         if (features && featuresPattern) {
            unif = statement->unif(features, featuresPattern, itemPtr());
         }
         else if (featuresPattern) {
            unif = featuresPattern;
         }
         else {
            unif = features;
         }

         //unif->flatPrint(std::cerr);
         //std::cerr << std::endl;
         if (!unif->isBottom()) {
            offset = ftell(dataFile);
            compactLexicon->add(input3.c_str(), offset);
            stringStream.str("");
            stringStream << form << '#' << '[';
            unif->flatPrint(stringStream, false);
            stringStream << ']';
            std::string output2 = stringStream.str();
            fprintf(dataFile, "%s%c", output2.c_str(), 0);
            std::cerr << input << " -> " << output2.c_str() << std::endl;

            if (predicatePattern != predicate) {
               stringStream.str("");
               unif->flatPrint(stringStream, false);
               std::string fs = stringStream.str();
               addForms(lexicon, line, form, input, pos, predicatePattern, fs);
            }

         }

      }
      // std::cerr << "/line:/" << line << '/' << std::endl;
      // std::cerr << "/pos:/" << pos << '/' << std::endl;
      // std::cerr << "/predicate:/" << predicate << '/' << std::endl;
      // std::cerr << "/form:/" << form << '/' << std::endl;
      // std::cerr << "/fs:/" << fs << '/' << std::endl;
   }
   else {
      offset = ftell(dataFile);
      compactLexicon->add(input.c_str(), offset);
      fprintf(dataFile, "%s%c", output.c_str(), 0);
      //std::cerr << input << " -> " << output.c_str() << std::endl;
   }

}

/* **************************************************
 *
 ************************************************** */
void CompactLexicon::buildFormEntries(Lexicon &lexicon) {
   std::string line;
   unsigned int range = 0;
   //unsigned long int offset;
   while (std::getline(*this->inputStream, line)) {
      if ((line.length() == 0) || (line.find('#') != std::string::npos))
         continue;
      //std::cout << "/line:/" << line << '/' << std::endl;
      char form[MAXSTRING];
      strcpy(form, line.c_str());
      char *rhs = strchr(form, '\t');
      *rhs = 0;

      char line2[MAXSTRING];
      strcpy(line2, line.c_str());
      char *pos = strchr(line2, '\t') + 1;
      rhs = strchr(pos, '\t');
      *rhs = 0;

      char line3[MAXSTRING];
      char line4[MAXSTRING];
      strcpy(line3, line.c_str());
      char *lemma = strchr(line3, '\t') + 1;
      lemma = strchr(lemma, '\t') + 1;
      rhs = strchr(lemma, '\t');
      char *morpho = NULL;
      if (rhs) {
         *rhs = 0;
         strcpy(line4, line.c_str());
         morpho = strchr(line4, '\t') + 1;
         morpho = strchr(morpho, '\t') + 1;
         morpho = strchr(morpho, '\t') + 1;
      }

      std::stringstream stringStream;
            stringStream << pos << "#_" << lemma;
            std::string input = std::string(stringStream.str());

            addForms(lexicon, line, form, input, pos, lemma, morpho);

      //nbrItem += strlen(line) + 1;
      if (!(range++ % 997)) {
         int k = (40 * (unsigned long int)(inputStream->tellg())) / (unsigned long int)this->InputFileStreamSize;
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
void CompactLexicon::loadData() {
   std::cerr << "*** Loading Data" << std::endl;
   struct stat *statbuf;
   statbuf = (struct stat *)malloc(sizeof(struct stat));
   stat(dataFileName.c_str(), statbuf);
   size_t size = statbuf->st_size;
   free(statbuf);
   buffer = new char[size];
   buffer[0] = 0;
   if (!fread(buffer, 1, size, dataFile))
      UNEXPECTED
}

/* **************************************************
 *
 ************************************************** */
void CompactLexicon::consult() {
   unsigned long int info;
   std::string str;
   while (!this->inputStream->eof()) {
      *this->inputStream >> str;
      info = searchStatic(init, str);
      //std::cerr << info << std::endl;
      printResults(std::cout, info, 1);
      fflush(stdout);
   }
}

