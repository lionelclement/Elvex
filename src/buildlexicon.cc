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
void addMacro(std::string line, std::string morphoFile, int lineno)
{
	// Macro
	// @f	gender:fem
	featuresPtr features;

	auto pos1 = line.find('@');
	auto pos2 = line.find('\t');
	if (pos2 == std::string::npos)
	{
		std::ostringstream oss;
		oss << "No '\\t' found in line: \"" << line << "\"";
		oss << " " << morphoFile << " (line " << lineno << ")";
		throw fatal_exception(oss.str());
	}

	std::string input = line.substr(pos1 + 1, pos2 - 1);
	std::string f = "[" + line.substr(pos2 + 1, line.size() - 1) + "]";
	try
	{
		parser.parseBuffer("#(", ")", f, "morphology");
	}
	catch (parser_exception &e)
	{

		std::ostringstream oss;
		oss << e.what() << ":\"" << f << "\"";
		oss << " " << morphoFile << " (line " << lineno << ")";
		throw fatal_exception(oss);
	}
	features = parser.getLocalFeatures();
	// CERR_LINE;
	// std::cerr << '@' << input << " => ";
	// features->flatPrint(std::cerr);
	// std::cerr << std::endl;
	parser.addMacros(input, features);
}

/* **************************************************
 * # form	pos	lemma	features
 ************************************************** */
void addMorpho(std::string line, std::string morphoFile, int lineno, Lexicon *morpho)
{
	auto pos1 = line.find('\t');
	auto pos2 = line.find('\t', pos1 + 1);
	auto pos3 = line.find('\t', pos2 + 1);
	std::string form(line);
	if (pos1 == std::string::npos)
	{
		std::ostringstream oss;
		oss << "part of speach expected in \"" << line << "\"";
		oss << " " << morphoFile << " (line " << lineno << ")";
		throw fatal_exception(oss.str());
	}
	form.resize(pos1);

	if (pos2 == std::string::npos)
	{
		std::ostringstream oss;
		oss << "lemma expected in \"" << line << "\"";
		oss << " " << morphoFile << " (line " << lineno << ")";
		throw fatal_exception(oss.str());
	}
	std::string pos = line.substr(pos1 + 1, pos2 - pos1 - 1);

	if (pos3 == std::string::npos)
	{
		std::ostringstream oss;
		oss << "features expected in \"" << line << "\"";
		oss << " " << morphoFile << " (line " << lineno << ")";
		throw fatal_exception(oss.str());
	}
	std::string lemma = line.substr(pos2 + 1, pos3 - pos2 - 1);
	std::string features = line.substr(pos3 + 1, line.size() - 1);

	// CERR_LINE;
	// std::cerr << "/form:/" << form << '/' << std::endl;
	// std::cerr << "/pos:/" << pos << '/' << std::endl;
	// std::cerr << "/lemma:/" << lemma << '/' << std::endl;
	// std::cerr << "/features:/" << features << '/' << std::endl;

	std::string input = pos + '#' + lemma;
	std::string output = form + '#' + features;
	morpho->add(input, output);
}

/* **************************************************
 * # lexeme	pos	lemma	features
 ************************************************** */
void addPattern(std::string line, std::string morphoFile, int lineno, Lexicon *pattern)
{
	auto pos1 = line.find('\t');
	auto pos2 = line.find('\t', pos1 + 1);
	auto pos3 = line.find('\t', pos2 + 1);
	std::string lexeme(line);
	if (pos1 == std::string::npos)
	{
		std::ostringstream oss;
		oss << "part of speach expected in \"" << line << "\"";
		oss << " " << morphoFile << " (line " << lineno << ")";
		throw fatal_exception(oss.str());
	}
	lexeme.resize(pos1);

	if (pos2 == std::string::npos)
	{
		std::ostringstream oss;
		oss << "lemma expected in \"" << line << "\"";
		oss << " " << morphoFile << " (line " << lineno << ")";
		throw fatal_exception(oss.str());
	}
	std::string pos = line.substr(pos1 + 1, pos2 - pos1 - 1);

	if (pos3 == std::string::npos)
	{
		std::ostringstream oss;
		oss << "features expected in \"" << line << "\"";
		oss << " " << morphoFile << " (line " << lineno << ")";
		throw fatal_exception(oss.str());
	}
	std::string lemma = line.substr(pos2 + 1, pos3 - pos2 - 1);
	std::string features = line.substr(pos3 + 1, line.size() - 1);
	// CERR_LINE
	// std::cerr << "/lexeme:/" << lexeme << '/' << std::endl;
	// std::cerr << "/pos:/" << pos << '/' << std::endl;
	// std::cerr << "/lemma:/" << lemma << '/' << std::endl;
	// std::cerr << "/features:/" << features << '/' << std::endl;

	std::string input = pos + '#' + lexeme;
	std::string output = lemma + '#' + features;
	pattern->add(input, output);
}

/* **************************************************
 *
 ************************************************** */
int main(int argn, char **argv)
{
	try
	{
		CompactedLexicon *compactedLexicon;
		Buildlexicon::Choice mode = Buildlexicon::NONE;
		std::string inputFileName = std::string();
		std::string prefix;
		std::string directory;
		std::string patternFile = std::string();
		std::string morphoFile = std::string();
		Lexicon *morpho = nullptr;
		Lexicon *pattern = nullptr;

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
			morpho = new Lexicon(morphoFile);
			std::ifstream inputFile;
			inputFile.open(morphoFile.c_str());
			std::string line;
			int lineno = 1;
			while (std::getline(inputFile, line))
			{
				if (!line.empty() && line[0] != '#')
				{
					if (line[0] == '@')
						addMacro(line, morphoFile, lineno);
					else
						addMorpho(line, morphoFile, lineno, morpho);
				}
				lineno++;
			}
			inputFile.close();
		}

		if (!patternFile.empty())
		{
			pattern = new Lexicon(patternFile);
			std::ifstream inputFile(patternFile);
			std::string line;
			int lineno = 1;

			while (std::getline(inputFile, line))
			{
				if (!line.empty() && line[0] != '#')
				{
					if (line[0] == '@')
						addMacro(line, patternFile, lineno);
					else {
						addPattern(line, patternFile, lineno, pattern);
					}
				}
				lineno++;
			}
			inputFile.close();
		}

		switch (mode)
		{

		case Buildlexicon::BUILD:
		{
			compactedLexicon = new CompactedLexicon(directory, prefix);
			compactedLexicon->openFiles("w");
			if (!morpho)
				throw usage_exception("morphoFile argument expected");
			if (!pattern)
				throw usage_exception("patternFile argument expected");
			compactedLexicon->buildEntries(*pattern, *morpho);
			compactedLexicon->saveFsa();
			compactedLexicon->closeFiles();
			return EXIT_SUCCESS;
		}

		case Buildlexicon::CONSULT:
		{
			compactedLexicon = new CompactedLexicon(directory, prefix);
			compactedLexicon->openFiles("r");
			compactedLexicon->loadFsa();
			compactedLexicon->loadData();
			compactedLexicon->consult();
			compactedLexicon->closeFiles();
			return EXIT_SUCCESS;
		}

		case Buildlexicon::LIST:
		{
			compactedLexicon = new CompactedLexicon(directory, prefix);
			compactedLexicon->openFiles("r");
			compactedLexicon->loadFsa();
			compactedLexicon->loadData();
			compactedLexicon->print(std::cout);
			compactedLexicon->closeFiles();
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
