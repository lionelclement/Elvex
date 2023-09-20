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

#include <cstring>
#include <iostream>
#include <fstream>

#include "buildlexicon.hpp"
#include "compacted-lexicon.hpp"
#include "compacted-lexicon-info.hpp"
#include "lexicon.hpp"
#include "messages.hpp"
#include "generator.hpp"
#include "config.hpp"
#include "parser_exception.hpp"
#include "fatal_exception.hpp"
#include "usage_exception.hpp"

Parser parser = Parser();

/* **************************************************
 *
 ************************************************** */
void usage()
{
	std::cerr << "Usage: " << PROJECT_NAME << "buildlexicon [global options] <build|consult|list> <input>\n\
\tGlobal options:\n\
\t-h|--help                                     print this\n\
\t-v|--version                                  print version\n\
\t-compactedLexiconDirectory/-cld <directory>   the directory which contains the compacted lexicon\n\
\t-compactedLexiconFile/-clf <file>             the compacted lexicon prefix name\n\
\t-patternFile <file>                           the pattern file\n\
\t-morphoFile <file>                            the morpho file"
			  << std::endl;
}

/* **************************************************
 *
 ************************************************** */
int main(int argn, char **argv)
{
	try
	{
		CompactedLexicon *lex;
		Buildlexicon::Choice mode = Buildlexicon::NONE;
		std::string inputFileName = std::string();
		std::string prefix;
		std::string directory;
		std::string patternFile = std::string();
		std::string morphoFile = std::string();
		class Lexicon morpho = Lexicon();
		class Lexicon pattern = Lexicon();

		if (argn <= 1)
		{
			throw usage_exception("not enough arguments");
		}
		// generic options
		for (unsigned int arg = 1; argv[arg]; ++arg)
		{
			if (argv[arg][0] == '-')
			{

				if (!strcmp(argv[arg] + 1, "v") || !strcmp(argv[arg] + 1, "-version"))
				{
					std::cout << ELVEX_VERSION << std::endl;
					return EXIT_SUCCESS;
				}
				else if (!strcmp(argv[arg] + 1, "h") || !strcmp(argv[arg] + 1, "-help"))
				{
					usage();
					return EXIT_SUCCESS;
				}
				else if (!strcmp(argv[arg] + 1, "compactedLexiconFile"))
				{
					if ((argv[arg + 1] != nullptr) && (argv[arg + 1][0] != '-'))
					{
						prefix = std::string(argv[++arg]);
					}
					else
					{
						throw usage_exception("bad compactedLexiconFile argument");
					}
				}
				else if (!strcmp(argv[arg] + 1, "clf"))
				{
					if ((argv[arg + 1] != nullptr) && (argv[arg + 1][0] != '-'))
					{
						prefix = std::string(argv[++arg]);
					}
					else
					{
						throw usage_exception("bad compactedLexiconFile argument");
					}
				}
				else if (!strcmp(argv[arg] + 1, "compactedLexiconDirectory"))
				{
					if ((argv[arg + 1] != nullptr) && (argv[arg + 1][0] != '-'))
					{
						directory = std::string(argv[++arg]);
					}
					else
					{
						throw usage_exception("bad compactedLexiconDirectory argument");
					}
				}
				else if (!strcmp(argv[arg] + 1, "cld"))
				{
					if ((argv[arg + 1] != nullptr) && (argv[arg + 1][0] != '-'))
					{
						directory = std::string(argv[++arg]);
					}
					else
					{
						throw usage_exception("bad compactedLexiconDirectory argument");
					}
				}
				else if (!strcmp(argv[arg] + 1, "patternFile"))
				{
					if ((argv[arg + 1] != nullptr) && (argv[arg + 1][0] != '-'))
					{
						patternFile = std::string(argv[++arg]);
					}
					else
					{
						throw usage_exception("bad patternFile argument");
					}
				}
				else if (!strcmp(argv[arg] + 1, "morphoFile"))
				{
					if ((argv[arg + 1] != nullptr) && (argv[arg + 1][0] != '-'))
					{
						morphoFile = std::string(argv[++arg]);
					}
					else
					{
						throw usage_exception("bad morphoFile argument");
					}
				}
			}

			else
			{
				if (!strcmp(argv[arg], "build"))
					mode = Buildlexicon::BUILD;
				else if (!strcmp(argv[arg], "consult"))
					mode = Buildlexicon::CONSULT;
				else if (!strcmp(argv[arg], "list"))
					mode = Buildlexicon::LIST;
				else
					inputFileName = argv[arg];
			}
		}

		if (!morphoFile.empty())
		{
			std::ifstream inputFile;
			inputFile.open(morphoFile.c_str());
			char line[MAXSTRING];
			int lineno = 1;
			while (inputFile.getline(line, MAXSTRING))
			{
				if ((line[0] != '#') && (line[0] != 0))
				{
					std::string input;
					std::string output;

					// Macro
					// @f	gender:fem
					if (line[0] == '@')
					{
						featuresPtr features;

						char line2[MAXSTRING];
						strcpy(line2, line);
						char *form = strchr(line2, '@') + 1;
						char *rhs = strchr(form, '\t');
						if (!rhs)
						{
							std::ostringstream oss;
							oss << "features expected in \"" << line << "\"";
							oss << " " << morphoFile << " (line " << lineno << ")";
							throw fatal_exception(oss);
						}
						*rhs = 0;

						char line4[MAXSTRING];
						strcpy(line4, line);
						char *f = strchr(line4, '\t') + 1;

						std::stringstream stream;
						stream << form;
						std::string input = stream.str();

						stream.str("");
						stream << '[' << f << ']';
						std::string fsString = stream.str();
						try
						{
							parser.parseBuffer("#(", ")", fsString, "morphology");
						}
						catch (parser_exception &e)
						{
							std::ostringstream oss;
							oss << e.what() << ":\"" << f << "\"";
							oss << " " << morphoFile << " (line " << lineno << ")";
							throw fatal_exception(oss);
						}
						features = parser.getLocalFeatures();
						parser.addMacros(input, features);
					}

					// ordinary entry
					else
					{
						char form[MAXSTRING];
						strcpy(form, line);
						char *rhs = strchr(form, '\t');
						if (!rhs)
						{
							std::ostringstream oss;
							oss << "part of speach expected in \"" << line << "\"";
							oss << " " << morphoFile << " (line " << lineno << ")";
							throw fatal_exception(oss);
						}
						*rhs = 0;

						char line2[MAXSTRING];
						strcpy(line2, line);
						char *pos = strchr(line2, '\t') + 1;
						rhs = strchr(pos, '\t');
						if (!rhs)
						{
							std::ostringstream oss;
							oss << "lemma expected in \"" << line << "\"";
							oss << " " << morphoFile << " (line " << lineno << ")";
							throw fatal_exception(oss);
						}
						*rhs = 0;

						char line3[MAXSTRING];
						strcpy(line3, line);
						char *lemma = strchr(line3, '\t') + 1;
						lemma = strchr(lemma, '\t') + 1;
						rhs = strchr(lemma, '\t');
						if (!rhs)
						{
							std::ostringstream oss;
							oss << "features expected in \"" << line << "\"";
							oss << " " << morphoFile << " (line " << lineno << ")";
							throw fatal_exception(oss);
						}
						*rhs = 0;

						char line4[MAXSTRING];
						strcpy(line4, line);
						char *features = strchr(line4, '\t') + 1;
						features = strchr(features, '\t') + 1;
						features = strchr(features, '\t') + 1;

						// std::cerr << "/form:/" << form << '/' << std::endl;
						// std::cerr << "/pos:/" << pos << '/' << std::endl;
						// std::cerr << "/lemma:/" << lemma << '/' << std::endl;
						// std::cerr << "/features:/" << features << '/' << std::endl;

						std::stringstream stream;
						stream << pos << '#' << lemma;
						std::string _input = stream.str();

						stream.str("");
						stream << form << '#' << features;
						std::string _output = stream.str();
						// std::cerr << "morpho/input:/" << _input << "/output:/" << _output << "/" << std::endl;
						morpho.add(_input, _output);
					}
				}
				lineno++;
			}
			inputFile.close();
		}

		// parser.listMacros();

		if (!patternFile.empty())
		{
			std::ifstream inputFile;
			inputFile.open(patternFile.c_str());
			char line[MAXSTRING];
			int lineno = 1;
			while (inputFile.getline(line, MAXSTRING))
			{
				if ((line[0] != '#') && strchr(line, '\t'))
				{

					// std::cerr << line << std::endl;

					char lexeme[MAXSTRING];
					strcpy(lexeme, line);
					char *rhs = strchr(lexeme, '\t');
					*rhs = 0;

					char line2[MAXSTRING];
					strcpy(line2, line);
					char *pos = strchr(line2, '\t') + 1;
					rhs = strchr(pos, '\t');
					if (!rhs)
					{
						std::ostringstream oss;
						oss << "lemma expected in \"" << line << "\"";
						oss << " " << patternFile << " (line " << lineno << ")";
						throw fatal_exception(oss);
					}
					*rhs = 0;

					char line3[MAXSTRING];
					strcpy(line3, line);
					char *lemma = strchr(line3, '\t') + 1;
					lemma = strchr(lemma, '\t') + 1;
					rhs = strchr(lemma, '\t');
					if (!rhs)
					{
						std::ostringstream oss;
						oss << "features expected in \"" << line << "\"";
						oss << " " << patternFile << " (line " << lineno << ")";
						throw fatal_exception(oss);
					}
					*rhs = 0;

					char line4[MAXSTRING];
					strcpy(line4, line);
					char *features = strchr(line4, '\t') + 1;
					features = strchr(features, '\t') + 1;
					features = strchr(features, '\t') + 1;

					// std::cerr << "/lexeme:/" << lexeme << '/' << std::endl;
					// std::cerr << "/pos:/" << pos << '/' << std::endl;
					// std::cerr << "/lemma:/" << lemma << '/' << std::endl;
					// std::cerr << "/features:/" << features << '/' << std::endl;

					std::stringstream stream;
					stream << pos << '#' << lexeme;
					std::string input = stream.str();

					stream.str("");
					stream << lemma << '#' << features;
					std::string output = stream.str();

					// std::cerr << "pattern/input:/" << input << '/' << "/output:/" << output << '/' << std::endl;

					pattern.add(input, output);
				}
				lineno++;
			}
			inputFile.close();
		}

		switch (mode)
		{

		case Buildlexicon::BUILD:
		{
			lex = new CompactedLexicon(directory, prefix);
			lex->openFiles("w");
			lex->buildEntries(pattern, morpho);
			lex->saveFsa();
			lex->closeFiles();
			return EXIT_SUCCESS;
		}

		case Buildlexicon::CONSULT:
		{
			lex = new CompactedLexicon(directory, prefix);
			lex->openFiles("r");
			lex->loadFsa();
			lex->loadData();
			lex->consult();
			lex->closeFiles();
			return EXIT_SUCCESS;
		}

		case Buildlexicon::LIST:
		{
			lex = new CompactedLexicon(directory, prefix);
			lex->openFiles("r");
			lex->loadFsa();
			lex->loadData();
			lex->print(std::cout);
			lex->closeFiles();
			return EXIT_SUCCESS;
		}

		case Buildlexicon::NONE:
		{
			throw usage_exception("bad action argument");
		}
		}
		usage();
	}
	catch (usage_exception &e)
	{
		std::cerr << "*** usage error: " << e.what() << std::endl;
		usage();
		std::flush(std::cerr);
		return EXIT_FAILURE;
	}
	catch (parser_exception &e)
	{
		std::cerr << "*** " << e.what() << std::endl;
		std::flush(std::cerr);
		return EXIT_FAILURE;
	}
	catch (fatal_exception &e)
	{
		std::cerr << "*** fatal error: " << e.what() << std::endl;
		std::flush(std::cerr);
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
