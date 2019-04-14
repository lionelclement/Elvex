/* **************************************************
 *
 * ELVEX
 *
 * Copyright 2018 LABRI, 
 * CNRS (UMR 5800), the University of Bordeaux,
 * and the Bordeaux INP
 *
 * Author: Lionel Clément,
 * Labri -- 351, cours de la Libération
 * 33405 Talence Cedex - France
 * lionel.clement@labri.fr
 * 
 * This file is part of ELVEX.
 *
 ************************************************** */

#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <map>

#include "lex.hh"
#include "messages.hh"
#include "vartable.hh"
#include "entries.hh"
#include "entry.hh"
#include "fsa.hh"
#include "infobuff.hh"
#include "tree.hh"

/* **************************************************
 *
 ************************************************** */
void 
Lex::printResults (std::ostream &output, unsigned long int index, bool sep) const
{
  char tag[MAXSTRING];
  if (sep)
    output << SEP_PREF;
  if (index == (unsigned long int)(~(0UL))){
    output << SEP_UW;
    if (sep)
      output << SEP_SUFF;
    return;
  }
  while (index != (unsigned long int)(~(0UL))){
    // an other element will be describe
    strcpy (tag, buffer+(info[index].offset));
    output << tag;
    if (info[index].next!=(unsigned long int)(~(0UL)))
      output << SEP_OR;
    if ((info[index].next)!=(unsigned long int)(~(0UL)))
      index=info[index].next;
    else
      index=(unsigned long int)(~(0UL));
  }
  if (sep)
    output << SEP_SUFF;
}

////////////////////////////////////////////////////////////
// input: string
// output: info
////////////////////////////////////////////////////////////
unsigned long int 
Lex::searchStatic(unsigned long int index, std::string s) const
{
  char *str = strdup(s.c_str());
  char *str2 = str;
  index=fsa[index].child;
  // for each letter of the suffix
  while (*str){
    // parse the brothers while founding the actual char
    while (*str != fsa[index].letter){
      if (fsa[index].sibling != (unsigned long int)(~(0UL)))
	index=fsa[index].sibling;
      else
	return (unsigned long int)(~(0UL));
    }
    if (*str != fsa[index].letter)
      return ((unsigned long int)(~(0UL)));
    if (*(str+1)){
      if (fsa[index].child != (unsigned long int)(~(0UL)))
	index=fsa[index].child;
      else
	return (unsigned long int)(~(0UL));

    }
    else
      if (fsa[index].info != (unsigned long int)(~(0UL)))
	return fsa[index].info;
    str++;

  }

  delete str2;
  return (unsigned long int)(~(0UL));
}

/* **************************************************
 *
 ************************************************** */
bool
Lex::saveFsa(FILE *file)
{
  int nbrBytes=sizeof(unsigned long int);;
  // encodage des offsets (16 ou 32 bits)
  if (!fwrite(&nbrBytes, sizeof(nbrBytes), 1, file))
    FATAL_ERROR;
#ifdef TRACE_DIFF
  fprintf(stdout, "nbreBytes: %X\n", nbrBytes);
#endif //TRACE_DIFF
  unsigned long int maxSize=(unsigned long int)~0UL;
  if (!fwrite(&maxSize, sizeof(maxSize), 1, file))
    FATAL_ERROR;
#ifdef TRACE_DIFF
  fprintf(stdout, "maxSize: %lX\n", maxSize);
#endif //TRACE_DIFF
  // nombre d'offsets du fsa
  //unsigned long int nbreItem=0;
  unsigned long int sizeFsa=0;
  lexiconInit->setIndexStaticFSA(sizeFsa);
  if (!fwrite(&sizeFsa, sizeof(sizeFsa), 1, file))
    FATAL_ERROR;
#ifdef TRACE_DIFF
  fprintf(stdout, "sizeFsa: %lX\n", sizeFsa);
#endif //TRACE_DIFF
  if (sizeFsa == (unsigned long int)~0UL){
    fputs ("*** Error: Lexicon too large\n", stderr);
    return false;

  }
  unsigned long int sizeInfo=0;
  lexiconInit->setIndexStaticInfo(sizeInfo);
  if (!fwrite(&sizeInfo, sizeof(sizeInfo), 1, file))
    FATAL_ERROR;
#ifdef TRACE_DIFF
  fprintf(stdout, "sizeInfo: %lX\n", sizeInfo);
#endif //TRACE_DIFF
  if(sizeInfo == (unsigned long int)~0UL){
    fputs("*** Error: Data too large\n", stderr);
    return false;

  }
#ifdef TRACE_DIFF
  fprintf(stdout, "---FSA---\n");
#endif //TRACE_DIFF
  lexiconInit->printStaticFSA(file, this);

#ifdef TRACE_DIFF
  fprintf(stdout, "---Info---\n");
#endif //TRACE_DIFF
  lexiconInit->printStaticInfo(file);
  fputs("*** Writing Data\n", stderr);
  // table
  fflush(file);
  if (!fwrite(&init, sizeof(init), 1, file))
    FATAL_ERROR;
#ifdef TRACE_DIFF
  fprintf(stdout, "Init: %lX\n", init);
#endif //TRACE_DIFF
  return true;
}

/* **************************************************
 *
 ************************************************** */
bool
Lex::loadFsa(FILE *file)
{
  //fputs("*** Loading Finite State Automata\n", stderr);
  int nbrBytes;
  if (!fread(&nbrBytes, sizeof(nbrBytes), 1, file))
    FATAL_ERROR;
#ifdef TRACE_DIFF
  fprintf(stdout, "nbreBytes: %X\n", nbrBytes);
#endif //TRACE_DIFF
  unsigned long int maxSize;
  if (!fread(&maxSize, sizeof(maxSize), 1, file))
    FATAL_ERROR;
#ifdef TRACE_DIFF
  fprintf(stdout, "maxSize: %lX\n", maxSize);
#endif //TRACE_DIFF
  if (nbrBytes!=(sizeof(unsigned long int)) || (maxSize!=(unsigned long int)~0UL)){
    fputs("*** lexicon compiled with an incompatible system\n", stderr);
    return false;

  }
  unsigned long int sizeFsa;
  if (!fread(&sizeFsa, sizeof(sizeFsa), 1, file))
    FATAL_ERROR;
#ifdef TRACE_DIFF
  fprintf(stdout, "sizeFsa: %lX\n", sizeFsa);
#endif //TRACE_DIFF
  unsigned long int sizeInfo;
  if (!fread(&sizeInfo, sizeof(sizeInfo), 1, file))
    FATAL_ERROR;
#ifdef TRACE_DIFF
  fprintf(stdout, "sizeInfo: %lX\n", sizeInfo);
#endif //TRACE_DIFF

#ifdef TRACE_DIFF
  fprintf(stdout, "---FSA---\n");
#endif //TRACE_DIFF
  fsa = new Fsa[sizeFsa+1];
  if (!fread(fsa, sizeof(Fsa), sizeFsa, file))
    FATAL_ERROR;
#ifdef TRACE_DIFF
  for(unsigned long int sizeSy=0;sizeSy<sizeFsa;sizeSy++){
    fprintf(stdout, "%lX ch:%lX sb:%lX in:%lX <%c>\n", sizeSy, fsa[sizeSy].child, fsa[sizeSy].sibling, fsa[sizeSy].info, fsa[sizeSy].letter);

  }
#endif //TRACE_DIFF

#ifdef TRACE_DIFF
  fprintf(stdout, "---Info---\n");
#endif //TRACE_DIFF
  info = new InfoBuff [sizeInfo+1];
  if (!fread(info, sizeof(InfoBuff), sizeInfo, file))
    FATAL_ERROR;
#ifdef TRACE_DIFF
  for(unsigned long int sizeSy=0;sizeSy<sizeInfo;sizeSy++){
    fprintf(stdout, "%lX su:%lX of:%lX\n", sizeSy, info[sizeSy].next, info[sizeSy].offset);

  }
#endif //TRACE_DIFF
  if (!fread(&init, sizeof(init), 1, file))
    FATAL_ERROR;
#ifdef TRACE_DIFF
  fprintf(stdout, "Init: %lX\n", init);
#endif //TRACE_DIFF
  return true;
}

/* **************************************************
 *
 ************************************************** */
bool
Lex::build(char *directory, char *prefix, std::istream *input) 
{
  bool result=true;
  FILE *fsaFile;
  FILE *tableFile;
  char str [MAXSTRING];
  char graphie [MAXSTRING];
  char oldStr [MAXSTRING];
  unsigned int i;
  unsigned int range;
  unsigned long int offset;

  offset = 0;
  range = 0;

  std::ostringstream oss;
  oss << directory << "/" << prefix << ".tbl";
  std::string osss = oss.str();
  tableFile = fopen(osss.c_str(), "w");//tableFileName.c_str(), "w");
  if (tableFile==NULL) {
    std::cerr << "Unable to open file " << osss << " for writing" << std::endl;
    result=false;

  }
  else {

    input->seekg(0, std::ios::end);
    long int size=(int)input->tellg();
    input->seekg(0, std::ios::beg);

    class Tree *lexicon;
    lexicon=new Tree(NULL, NULL, NULL, '\0');
    lexicon->setChild(new Tree(NULL, NULL, NULL, '\0'));
    lexiconInit=lexicon;
    lexicon=lexicon->getChild();

    int nbrItem=0;
    while (input->getline(str, MAXSTRING)) {
      if (!*str)
	continue;
      for (i = 0; i <= strlen(str) && (!strchr ("\t", str[i])); i++)
	/* empty */;
      strcpy (graphie, str);
      graphie[i] = 0;
      if (i < strlen (str)) {
	graphie[i]=0;
	if (!strcmp(str+i+1, oldStr)) {
	  lexicon->add(graphie, offset);

	}
	else {
	  // Adds one entry
	  offset = ftell(tableFile);
	  lexicon->add(graphie, offset);
	  fprintf(tableFile, "%s%c", str+i+1, 0);

	}
	strcpy (oldStr, str+i+1);

      }
      else {
	// the entry of one word without any information is the same as the previous:
	// aaa info_of_aaa
	// bbb
	//
	// bbb -> info_of_aaa
	lexicon->add(graphie, offset);

      }
      nbrItem+=strlen(str)+1;
      if (!(range++ % 1357)){
	int k = (100*(unsigned long int)(input->tellg())) / (unsigned long int)size;
	std::cerr << " " << k << "%\r";

      }

    }
    fclose(tableFile);

  }

  oss.str("");
  oss << directory << "/" << prefix << ".fsa";
  osss = oss.str();
  std::cerr << "*** Writing Finite State Automata " << osss << std::endl;
  fsaFile = fopen(osss.c_str(), "w");
  if (fsaFile == NULL) {
    std::cerr << "Unable to open file " << osss << " for writing" << std::endl;
    result=false;

  }
  else {
    if (!saveFsa(fsaFile))
      result=false;
    fclose(fsaFile);

  }
  return result;
}

/* **************************************************
 *
 ************************************************** */
bool
Lex::load(char *directory, char *prefix)
{
  unsigned long int size;

  std::ostringstream oss;
  oss << directory << "/" << prefix << ".fsa";
  std::string osss = oss.str();
  FILE *fsaFile = fopen(osss.c_str(), "r");
  if (fsaFile == NULL) {
    std::cerr << "File " << osss << " not found" << std::endl;
    exit (EXIT_FAILURE);

  }
  else {
    if (!loadFsa(fsaFile)) {
      return false;

    }

    fclose(fsaFile);

  }
  oss.str("");
  oss << directory << "/" << prefix << ".tbl";
  osss = oss.str();
  FILE *tableFile=fopen(osss.c_str(), "r");
  if (tableFile == NULL) {
    std::cerr << "File " << osss << " not found" << std::endl;
    exit (EXIT_FAILURE);

  }
  else {
    //cerr << "*** Load buffer in memory" << endl;

    struct stat *statbuf;
    statbuf = (struct stat *)malloc(sizeof(struct stat));
    stat(osss.c_str(), statbuf);
    size = statbuf->st_size;
    free(statbuf);

    buffer = new char [size];
    buffer[0] = 0;

    if (!fread (buffer, 1, size, tableFile))
      FATAL_ERROR;
    fclose (tableFile);

  }

  return true;
}

/* **************************************************
 *
 ************************************************** */
bool
Lex::consult(std::string inputFileName)
{
  FILE *inputFile=NULL;
  if (inputFileName=="-") {
    std::cerr << "*** Searching from stdin" << std::endl;
    inputFile = stdin;
  }

  else if (inputFileName!="") {
    std::cerr << "*** Seaching " << inputFileName << std::endl;
    inputFile = fopen (inputFileName.c_str(), "r");
    if (!inputFile) {
      std::cerr << "Unable to open file " << inputFileName << " for reading" << std::endl;
      exit (EXIT_FAILURE);
    }

  }
  unsigned long int info;
  char str[MAXSTRING];
  if (inputFile){
    while (fgets (str, MAXSTRING, inputFile)) {
      str[strlen(str)-1]=0;
      info = searchStatic(init, str);
      printResults(std::cout, info, 1);
      fflush(stdout);
    }
    fclose (inputFile);

  }

  return true;
}

