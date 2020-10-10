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

#include "compact-lexicon.h"
#include "compact-lexicon-tree.h"
#include "compact-lexicon-fsa.h"
#include "compact-lexicon-buffer.h"
#include "messages.h"
#include "vartable.h"
#include "entries.h"
#include "entry.h"
#include "lexicon.h"
#include "parser.h"
#include "statement.h"

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
   this->compactLexicon = new CompactLexiconTree(NULL, NULL, NULL, '\0');
   this->compactLexicon->setChild(new CompactLexiconTree(NULL, NULL, NULL, '\0'));
   this->lexiconInit = compactLexicon;
   this->compactLexicon = compactLexicon->getChild();
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
      FATAL_ERROR_UNEXPECTED
#ifdef TRACE_DIFF
      std::cout << "nbreBytes:" << nbrBytes << std::endl;
#endif //TRACE_DIFF
   unsigned long int maxSize = (unsigned long int)~0UL;
   if (!fwrite(&maxSize, sizeof(maxSize), 1, fsaFile))
      FATAL_ERROR_UNEXPECTED
#ifdef TRACE_DIFF
      std::cout << "maxSize:" << maxSize << std::endl;
#endif //TRACE_DIFF
   // nombre d'offsets du fsa
   unsigned long int sizeFsa = 0;
   lexiconInit->setIndexStaticFSA(sizeFsa);
   if (!fwrite(&sizeFsa, sizeof(sizeFsa), 1, fsaFile))
      FATAL_ERROR_UNEXPECTED
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
      FATAL_ERROR_UNEXPECTED
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
      FATAL_ERROR_UNEXPECTED
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
      FATAL_ERROR_UNEXPECTED
#ifdef TRACE_DIFF
      std::cout << "nbreBytes:" << nbrBytes << std::endl;
#endif //TRACE_DIFF
   unsigned long int maxSize;
   if (!fread(&maxSize, sizeof(maxSize), 1, fsaFile))
      FATAL_ERROR_UNEXPECTED
#ifdef TRACE_DIFF
      std::cout << "maxSize:" << maxSize << std::endl;
#endif //TRACE_DIFF
   if (nbrBytes != (sizeof(unsigned long int)) || (maxSize != (unsigned long int)~0UL)) {
      std::cerr << "*** lexicon compiled with an incompatible system" << std::endl;
      throw "";
   }
   unsigned long int sizeFsa;
   if (!fread(&sizeFsa, sizeof(sizeFsa), 1, fsaFile))
      FATAL_ERROR_UNEXPECTED
#ifdef TRACE_DIFF
      std::cout << "sizeFsa:" << sizeFsa << std::endl;
#endif //TRACE_DIFF
   unsigned long int sizeInfo;
   if (!fread(&sizeInfo, sizeof(sizeInfo), 1, fsaFile))
      FATAL_ERROR_UNEXPECTED
#ifdef TRACE_DIFF
      std::cout << "sizeInfo:" << sizeInfo << std::endl;
#endif //TRACE_DIFF

#ifdef TRACE_DIFF
   std::cout << "---FSA---" << std::endl;
#endif //TRACE_DIFF
   fsa = new CompactLexiconFsa[sizeFsa + 1]();
   if (!fread(fsa, sizeof(CompactLexiconFsa), sizeFsa, fsaFile))
      FATAL_ERROR_UNEXPECTED
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
      FATAL_ERROR_UNEXPECTED
#ifdef TRACE_DIFF
      for(unsigned long int sizeSy=0;sizeSy<sizeInfo;sizeSy++) {
         std::cout << sizeSy << ' ';
         info[sizeSy].print(std::cout);
      }
#endif //TRACE_DIFF
   if (!fread(&init, sizeof(init), 1, fsaFile))
      FATAL_ERROR_UNEXPECTED
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
std::string CompactLexicon::unif(std::string fs1, std::string fs2) {
   extern Parser parser;
   std::stringstream stringStream;
   featuresPtr features1;
   if (fs1.size()) {
      stringStream.str("");
      stringStream << '[' << fs1 << ']';
      std::string fsString = stringStream.str();
      if (parser.parseBuffer("#", fsString, "morphology")) {
         stringStream.str("");
         stringStream << "error in lexicon: " << fs1 << std::endl;
         FATAL_ERROR(stringStream.str())
      }
      features1 = parser.getLocalFeatures();
   }
   else
      features1 = featuresPtr();

   featuresPtr features2;
   if (fs2.size()) {
      stringStream.str("");
      stringStream << '[' << fs2 << ']';
      std::string fsString = stringStream.str();
      if (parser.parseBuffer("#", fsString, "morphology")) {
         stringStream.str("");
         stringStream << "error in lexicon: " << fs2 << std::endl;
         FATAL_ERROR(stringStream.str())
      }
      features2 = parser.getLocalFeatures();
   }
   else
      features2 = featuresPtr();

   statementPtr statement;
   featuresPtr unif;
   if (features1 && features2) {
      unif = statement->unif(features1, features2, itemPtr());
   }
   else if (features1) {
      unif = features1;
   }
   else {
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
void CompactLexicon::addToData(std::string input, std::string form, std::string features) {
   //std::cerr << "add:" << form << "[input:" << input << ",form:" << form << ",features:" << features << std::endl;
   std::stringstream stringStream;
   stringStream.str("");
   stringStream << form << '#' << '[' << features << ']';
   std::string output = stringStream.str();
   unsigned long int offset;
   offset = ftell(dataFile);
   compactLexicon->add(input.c_str(), offset);
   fprintf(dataFile, "%s%c", output.c_str(), 0);
   //std::cerr << output.c_str() << std::endl;
}

/* **************************************************
 *
 ************************************************** */
void CompactLexicon::addForms(std::string input, std::string inputSearch, std::string patternFs/*, Lexicon &pattern*/, Lexicon &morpho) {
   //std::cerr << "addForms " << inputSearch << std::endl;

   std::list<std::string> *o = morpho.find(inputSearch);
   for (std::list<std::string>::const_iterator it = o->begin(); it != o->end(); ++it) {

      char form[MAXSTRING];
      strcpy(form, it->c_str());
      char *rhs = strchr(form, '#');
      *rhs = 0;

      char line[MAXSTRING];
      strcpy(line, it->c_str());
      char *morphoFs = strchr(line, '#') + 1;

      //std::cerr << "addToData " << input << " => " << form << ' ' << unif(patternFs, morphoFs) << std::endl;
      addToData("_" + input, form, unif(patternFs, morphoFs) );
   }
}

/* **************************************************
 *
 ************************************************** */
void CompactLexicon::addPattern(Lexicon &pattern, Lexicon &morpho, std::string input, std::string patternFs, std::string lemma, std::string pos) {
  //std::cerr << "addPattern with " << '(' << input << ',' << patternFs << ',' << lemma << ',' << pos << ')' << std::endl;
   std::stringstream stringStream;
   stringStream.str("");
   stringStream << lemma << '#' << pos;
   std::string inputSearch = std::string(stringStream.str());
   if (morpho.count(inputSearch) ) {
      //std::cerr << "addForms with " << inputSearch << '(' << input << ',' << lemma << ',' << pos << ',' << patternFs << ')' << std::endl;
      addForms(input, inputSearch, patternFs/*, pattern*/, morpho);
   }
   else if (pattern.count(inputSearch)) {
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
void CompactLexicon::buildEntries(Lexicon &pattern, Lexicon &morpho) {
   extern Parser parser;
   std::stringstream inputStream;
   std::size_t size = pattern.size();
   std::size_t range = 0;
   for (Lexicon::unordered_map::const_iterator patternIt = pattern.cbegin(); patternIt != pattern.cend(); ++patternIt) {
     //std::cerr << "pattern:" << patternIt->first << std::endl;
      for (std::list<std::string>::const_iterator it2 = patternIt->second->begin(); it2 != patternIt->second->end(); ++it2) {
	//std::cerr << "str:" << *it2 << std::endl;

	char lexeme[MAXSTRING];
         strcpy(lexeme, patternIt->first.c_str());
         char *rhs = strchr(lexeme, '#');
         *rhs = 0;

         char line2[MAXSTRING];
         strcpy(line2, patternIt->first.c_str());
         char *pos = strchr(line2, '#') + 1;

         char lemma[MAXSTRING];
         strcpy(lemma, it2->c_str());
         rhs = strchr(lemma, '#');
         *rhs = 0;

         char line4[MAXSTRING];
         strcpy(line4, it2->c_str());
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
      FATAL_ERROR_UNEXPECTED
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
      printResults(std::cout, info, 1);
      fflush(stdout);
   }
}

