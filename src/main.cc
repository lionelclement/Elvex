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

#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include "lex.hh"
#include "synthesizer.hh"
#include "vartable.hh"
#include "node.hh"
#include "forest.hh"
#include "messages.hh"

#ifndef PACKAGE_NAME
#define	PACKAGE_NAME "elvex"
#endif

#ifndef PACKAGE_VERSION
#define PACKAGE_VERSION "?.?.?"
#endif

Synthesizer synthesizer;

time_t start, end;
Vartable vartable;
#ifdef OUTPUT_XML
xmlNodePtr xmlNodeRoot;
xmlDocPtr document;
#endif

/* **************************************************
 *
 ************************************************** */
void Usage(char **argv) {
  std::cerr << "Usage: " << PACKAGE_NAME << " [options] [<input>]*\n";
  std::cerr << "\
options\n\
\t--help|-h                   print this\n\
\t--version|-v                print version\n\
\t--reduceAll|-a              reduce all rules\n\
\t--trace|-t                  trace the generation process\n\
\t--random|-r                 outputs one sentence randomly selected\n";
#ifdef TRACE
  std::cerr << "\
\t--traceStage\n\
\t--traceClose\n\
\t--traceShift\n\
\t--traceReduce\n\
\t--traceAction\n";
#endif
  std::cerr << "\
\t-maxLength <number>         max number of length\n\
\t-maxUsages <number>         max number of rule usage\n\
\t-maxCardinal <number>       max number of items per set\n\
\t-maxTime <seconds>          max time in seconds\n\
\t-grammarFile <file>\n\
\t-lexiconFile <file>\n\
\t-inputFile <file>\n\
\t-compactDirectory <directory>\n\
\t-compactLexiconFile <file>\n\
";
#ifdef OUTPUT_XML
  std::cerr << "\t-xml <file>                 the XML file\n";
#endif
}

/* **************************************************
 *
 ************************************************** */
void seq(int i) {
  std::cerr << std::endl << "ALARM SIGNAL: OUT OF TIME" << std::endl;
  exit(EXIT_SUCCESS);
}

/* **************************************************
 *
 ************************************************** */
void generate(void) {
  if (synthesizer.getStartTerm())
    synthesizer.generate();
#ifdef TRACE
  std::cout << "<ul>" << std::endl;
#endif
  if (synthesizer.getNodeRoot() && synthesizer.getNodeRoot()->getForests().size() > 0) {
    std::vector<forestPtr>::const_iterator forestIt = synthesizer.getNodeRoot()->getForests().begin();
    forestPtr forest;
    if (synthesizer.getRandom()) {
      int rv = std::rand()/((RAND_MAX + 1u)/synthesizer.getNodeRoot()->getForests().size());
      forest = synthesizer.getNodeRoot()->getForests().at(rv);
    }
    while (forestIt != synthesizer.getNodeRoot()->getForests().end()) {
      if (!synthesizer.getRandom())
	forest = *forestIt;
      for (std::vector<std::string>::const_iterator i = forest->getOutput().begin();
	   i != forest->getOutput().end();
	   ++i){
#ifdef TRACE
	std::cout << "<li>" << std::endl;
#endif
	std::cout << *i << std::endl;
#ifdef TRACE
	std::cout << "</li>" << std::endl;
#endif
      }
      if (synthesizer.getRandom()) 
	break;
      ++forestIt;
    }
  }
#ifdef TRACE
  std::cout << "</ul>" << std::endl;
#endif
}

/* **************************************************
 *
 ************************************************** */
int main(int argn, char **argv) {
#ifdef TRACE
  std::cout << "<html><head><title>Elvex</title><meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\"></head><body>" << std::endl;
#endif
  try {
    vartable.init();
#ifdef OUTPUT_XML
    synthesizer.setOutXML(NULL);
#endif
    if (argn <= 1) {
      Usage(argv);
      return EXIT_SUCCESS;
    }
    else {
      for (unsigned int arg = 1;argv[arg];++arg) {
	if (argv[arg][0] == '-') {
	  if (!strcmp(argv[arg]+1, "v") || !strcmp(argv[arg] + 1, "-version")) {
	    std::cout << PACKAGE_VERSION << std::endl;
	    return EXIT_SUCCESS;
	  }
	  
	  else if (!strcmp(argv[arg]+1, "h") || !strcmp(argv[arg] + 1, "-help")) {
	    Usage(argv);
	    return EXIT_SUCCESS;
	  }

	  else if (!strcmp(argv[arg]+1, "t") || !strcmp(argv[arg] + 1, "-trace")) {
	    synthesizer.setTrace(true);
	  }

	  else if (!strcmp(argv[arg]+1, "a") || !strcmp(argv[arg] + 1, "-reduceAll")) {
	    synthesizer.setReduceAll(true);
	  }

	  else if (!strcmp(argv[arg]+1, "r") || !strcmp(argv[arg] + 1, "-random")) {
	    std::srand(time(nullptr));
	    synthesizer.setRandom(true);
	  }
	  
#ifdef TRACE
	  else if (!strcmp(argv[arg] + 1, "-traceStage")) {
	    synthesizer.setTraceStage(true);
	  }

	  else if (!strcmp(argv[arg] + 1, "-traceClose")) {
	    synthesizer.setTraceClose(true);
	  }

	  else if (!strcmp(argv[arg] + 1, "-traceShift")) {
	    synthesizer.setTraceShift(true);
	  }

	  else if (!strcmp(argv[arg] + 1, "-traceReduce")) {
	    synthesizer.setTraceReduce(true);
	  }

	  else if (!strcmp(argv[arg] + 1, "-traceAction")) {
	    synthesizer.setTraceAction(true);
	  }

#endif

	  else if (!strcmp(argv[arg] + 1, "lexiconFile")) {
	    if ((argv[arg + 1] != NULL) && (argv[arg + 1][0]!='-'))
	      synthesizer.setLexiconFileName(argv[++arg]);
	    else {
	      Usage(argv);
	      return EXIT_FAILURE;
	    }
	  }

	  else if (!strcmp(argv[arg] + 1, "grammarFile")) {
	    if ((argv[arg + 1] != NULL) && (argv[arg + 1][0]!='-'))
	      synthesizer.setGrammarFileName(argv[++arg]);
	    else {
	      Usage(argv);
	      return EXIT_FAILURE;
	    }
	  }
	  
	  else if (!strcmp(argv[arg] + 1, "inputFile")) {
	    if ((argv[arg + 1] != NULL) && (argv[arg + 1][0]!='-'))
	      synthesizer.setInputFileName(argv[++arg]);
	    else {
	      Usage(argv);
	      return EXIT_FAILURE;
	    }
	  }
	  
	  else if (!strcmp(argv[arg] + 1, "maxLength")) {
	    if ((argv[arg + 1] != NULL) && (argv[arg + 1][0]!='-'))
	      synthesizer.setMaxLength(atoi(argv[++arg]));
	    else {
	      Usage(argv);
	      return EXIT_FAILURE;
	    }
	  }
	  
	  else if (!strcmp(argv[arg] + 1, "maxUsages")) {
	    if ((argv[arg + 1] != NULL) && (argv[arg + 1][0]!='-'))
	      synthesizer.setMaxUsages(atoi(argv[++arg]));
	    else {
	      Usage(argv);
	      return EXIT_FAILURE;
	    }
	  }
	  
	  else if (!strcmp(argv[arg] + 1, "maxCardinal")) {
	    if ((argv[arg + 1] != NULL) && (argv[arg + 1][0]!='-'))
	      synthesizer.setMaxCardinal(atoi(argv[++arg]));
	    else {
	      Usage(argv);
	      return EXIT_FAILURE;
	    }
	  }
	  
	  else if (!strcmp(argv[arg] + 1, "maxTime")) {
	    if ((argv[arg + 1] != NULL) && (argv[arg + 1][0]!='-')) {
	      signal(SIGALRM, seq);
	      alarm(atoi(argv[++arg]));
	      time(&start);
	    } else {
	      Usage(argv);
	      return EXIT_FAILURE;
	    }
	  }
	  
	  else if (!strcmp(argv[arg] + 1, "compactDirectory")) {
	    if ((argv[arg + 1] != NULL) && (argv[arg + 1][0]!='-'))
	      synthesizer.setCompactDirectoryName(argv[++arg]);
	    else {
	      Usage(argv);
	      return EXIT_FAILURE;
	    }
	  }
	  
	  else if (!strcmp(argv[arg] + 1, "compactLexiconFile")) {
	    if ((argv[arg + 1] != NULL) && (argv[arg + 1][0]!='-'))
	      synthesizer.setCompactLexiconFileName(argv[++arg]);
	    else {
	      Usage(argv);
	      return EXIT_FAILURE;
	    }
	  }
	  
#ifdef OUTPUT_XML
	  else if (!strcmp (argv[arg]+1, "xml")) {
	    if ((argv[arg + 1] != NULL) && (argv[arg + 1][0]!='-')) {
	      synthesizer.setOutXML(strdup(argv[++arg]));
	    } else {
	      Usage(argv);
	      return EXIT_FAILURE;
	    }
	  }
#endif
	  
	  else {
	    CERR_LINE;
	    std::cerr << "Unknown argument: " << argv[arg] + 1 << std::endl;
	    Usage(argv);
	    return EXIT_FAILURE;
	  }
	}

	else {
	  synthesizer.addInput(argv[arg]);
	}
      }
      
      if (synthesizer.getLexiconFileName().length() > 0) {
#ifdef TRACE_INIT
	std::cerr << "load lexicon" << "<BR>" << std::endl;
#endif
	synthesizer.parseFile(synthesizer.getLexiconFileName());
      }

      if (synthesizer.getGrammarFileName().length() > 0) {
#ifdef TRACE_INIT
	std::cerr << "load grammar" << "<BR>" << std::endl;
#endif
	synthesizer.parseFile(synthesizer.getGrammarFileName());
      }
      
      if (synthesizer.getCompactLexiconFileName().length() > 0) {
#ifdef TRACE_INIT
	std::cerr << "load compact lexicon" << "<BR>" << std::endl;
#endif
	synthesizer.setCompactLexicon(new Lex());
	char *dir = strdup((synthesizer.getCompactDirectoryName().length() > 0) ?
			   synthesizer.getCompactDirectoryName().c_str() :
			   ".");
	char *file = strdup(synthesizer.getCompactLexiconFileName().c_str());
	if (!synthesizer.getCompactLexicon()->load(dir, file))
	  return EXIT_FAILURE;
      }

#ifdef OUTPUT_XML
      if (synthesizer.getOutXML()) {
	document = xmlNewDoc ((xmlChar*)"1.0");
	xmlDocSetRootElement(document, xmlNewNode(NULL, (xmlChar*)"ROOT"));
	xmlNodeRoot = xmlDocGetRootElement(document);
      }
#endif
      
    }
    srand (time(NULL));
    if (synthesizer.getInputFileName().length() > 0) {
#ifdef TRACE_INIT
      std::cerr << "load input" << "<BR>" << std::endl;
#endif
      synthesizer.parseFile(synthesizer.getInputFileName());
      generate();
    }
    
    for (std::list<std::string>::const_iterator i = synthesizer.getInputs().begin() ; i != synthesizer.getInputs().end() ; ++i) {
      synthesizer.parseString("@input " + *i, std::string("Input"));
      generate();
    }
    
#ifdef OUTPUT_XML
    if (synthesizer.getOutXML()) {
      std::string encoding="UTF-8";
      xmlSaveFormatFileEnc(synthesizer.getOutXML(), document, encoding.c_str(), 1);
    }
#endif
    
#ifdef TRACE_INIT
    std::cerr << std::endl << "EXIT_SUCCESS" << "<BR>" << std::endl;
#endif
  } catch (std::string &message) {
    std::cerr << message << std::endl;
  } catch (char const *message) {
    std::cerr << message << std::endl;
  }
#ifdef TRACE
  std::cout << "</body></html>" << std::endl;
#endif
  return EXIT_SUCCESS;
}
