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

#include <cstring>
#include <cstdlib>
#include <fstream>
#include <initializer_list>
#include <iostream>
#include <sstream>
#include <string>

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

Parser parser;

namespace
{
	bool isOption(const char *arg, std::initializer_list<const char *> names)
	{
		for (const char *name : names)
		{
			if (std::strcmp(arg, name) == 0)
			{
				return true;
			}
		}

		return false;
	}

	char *readOptionValue(int &arg, char **argv, const std::string &optionName)
	{
		if (argv[arg + 1] != nullptr && argv[arg + 1][0] != '-')
		{
			return argv[++arg];
		}

		throw usage_exception("bad " + optionName + " argument");
	}

	void usage()
	{
		std::cerr << "Usage: " << PROJECT_NAME << "buildlexicon [global options] <build|consult|list> [<input>]\n";
		std::cerr << "\
Global options:\n\
\t-h, --help                                       print this help message\n\
\t-v, --version                                    print version\n\
\t-V, --verbose                                    enable verbose mode\n\
\t--compacted-lexicon-file, --clf <path/file>      compacted lexicon file prefix\n\
\t--macros-file <file>                             macros file\n\
\t--pattern-file <file>                            pattern file\n\
\t--morpho-file <file>                             morpho file\n";
	}

	/* **************************************************
	 * # form    pos    lemma    features
	 ************************************************** */
	void addMorpho(const std::string &line, const std::string &morphoFile, int lineno, Lexicon *morpho)
	{
		auto pos1 = line.find('\t');
		auto pos2 = line.find('\t', pos1 + 1);
		auto pos3 = line.find('\t', pos2 + 1);

		std::string form(line);

		if (pos1 == std::string::npos)
		{
			std::ostringstream oss;
			oss << "part of speech expected in \"" << line << "\"";
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
		std::string features = line.substr(pos3 + 1);

		std::string input = pos + '#' + lemma;
		std::string output = form + '#' + features;
		morpho->add(input, output);
	}

	/* **************************************************
	 * # lexeme    pos    lemma    features
	 ************************************************** */
	void addPattern(const std::string &line, const std::string &patternFile, int lineno, Lexicon *pattern)
	{
		auto pos1 = line.find('\t');
		auto pos2 = line.find('\t', pos1 + 1);
		auto pos3 = line.find('\t', pos2 + 1);

		std::string lexeme(line);

		if (pos1 == std::string::npos)
		{
			std::ostringstream oss;
			oss << "part of speech expected in \"" << line << "\"";
			oss << " " << patternFile << " (line " << lineno << ")";
			throw fatal_exception(oss.str());
		}

		lexeme.resize(pos1);

		if (pos2 == std::string::npos)
		{
			std::ostringstream oss;
			oss << "lemma expected in \"" << line << "\"";
			oss << " " << patternFile << " (line " << lineno << ")";
			throw fatal_exception(oss.str());
		}

		std::string pos = line.substr(pos1 + 1, pos2 - pos1 - 1);

		if (pos3 == std::string::npos)
		{
			std::ostringstream oss;
			oss << "features expected in \"" << line << "\"";
			oss << " " << patternFile << " (line " << lineno << ")";
			throw fatal_exception(oss.str());
		}

		std::string lemma = line.substr(pos2 + 1, pos3 - pos2 - 1);
		std::string features = line.substr(pos3 + 1);

		std::string input = pos + '#' + lexeme;
		std::string output = lemma + '#' + features;
		pattern->add(input, output);
	}

	void readMorphoFile(const std::string &morphoFile, Lexicon *morpho)
	{
		std::ifstream inputFile(morphoFile);
		std::string line;
		int lineno = 1;

		while (std::getline(inputFile, line))
		{
			size_t commentPos = line.find("//");
			if (commentPos != std::string::npos)
			{
				line = line.substr(0, commentPos);
			}

			if (!line.empty())
			{
				addMorpho(line, morphoFile, lineno, morpho);
			}

			++lineno;
		}
	}

	void readPatternFile(const std::string &patternFile, Lexicon *pattern)
	{
		std::ifstream inputFile(patternFile);
		std::string line;
		int lineno = 1;

		while (std::getline(inputFile, line))
		{
			size_t commentPos = line.find("//");
			if (commentPos != std::string::npos)
			{
				line = line.substr(0, commentPos);
			}

			if (!line.empty())
			{
				addPattern(line, patternFile, lineno, pattern);
			}

			++lineno;
		}
	}
}

int main(int argn, char **argv)
{
	try
	{
		CompactedLexicon *compactedLexicon = nullptr;
		Buildlexicon::Choice mode = Buildlexicon::NONE;
		std::string compactedLexiconFileName;
		std::string macrosFileName;
		std::string patternFile;
		std::string morphoFile;
		Lexicon *morpho = nullptr;
		Lexicon *pattern = nullptr;
		bool verbose = false;

		if (argn <= 1)
		{
			throw usage_exception("not enough arguments");
		}

		for (int arg = 1; argv[arg] != nullptr; ++arg)
		{
			if (argv[arg][0] != '-')
			{
				if (std::strcmp(argv[arg], "build") == 0)
				{
					mode = Buildlexicon::BUILD;
				}
				else if (std::strcmp(argv[arg], "consult") == 0)
				{
					mode = Buildlexicon::CONSULT;
				}
				else if (std::strcmp(argv[arg], "list") == 0)
				{
					mode = Buildlexicon::LIST;
				}
				else
				{
					// The historical command line accepts a final <input> argument,
					// but the current implementation does not use it directly.
				}

				continue;
			}

			const char *option = argv[arg];

			if (isOption(option, {"-V", "--verbose"}))
			{
				verbose = true;
			}
			else if (isOption(option, {"-v", "--version"}))
			{
				std::cout << ELVEX_VERSION << std::endl;
				return EXIT_SUCCESS;
			}
			else if (isOption(option, {"-h", "--help"}))
			{
				usage();
				return EXIT_SUCCESS;
			}
			else if (isOption(option, {"--macros-file", "-macrosFile"}))
			{
				macrosFileName = readOptionValue(arg, argv, "macros-file");
			}
			else if (isOption(option, {"--compacted-lexicon-file",
									   "--clf",
									   "-compactedLexiconFile",
									   "-clf"}))
			{
				compactedLexiconFileName = readOptionValue(arg, argv, "compacted-lexicon-file");
			}
			else if (isOption(option, {"--pattern-file", "-patternFile"}))
			{
				patternFile = readOptionValue(arg, argv, "pattern-file");
			}
			else if (isOption(option, {"--morpho-file", "-morphoFile"}))
			{
				morphoFile = readOptionValue(arg, argv, "morpho-file");
			}
			else
			{
				std::ostringstream oss;
				oss << "Unknown argument: " << option;
				throw usage_exception(oss);
			}
		}

		if (!macrosFileName.empty())
		{
			parser.parseFile("@macros (", ")", macrosFileName);
			parser.getRules().analyseTerms(parser);
		}

		if (!morphoFile.empty())
		{
			morpho = new Lexicon(morphoFile);
			readMorphoFile(morphoFile, morpho);
		}

		if (!patternFile.empty())
		{
			pattern = new Lexicon(patternFile);
			readPatternFile(patternFile, pattern);
		}

		if (compactedLexiconFileName.empty())
		{
			throw usage_exception("compacted-lexicon-file argument expected");
		}

		switch (mode)
		{
		case Buildlexicon::BUILD:
		{
compactedLexicon = new CompactedLexicon(compactedLexiconFileName);
			compactedLexicon->openFiles("w");

			if (!morpho)
			{
				throw usage_exception("morpho-file argument expected");
			}

			if (!pattern)
			{
				throw usage_exception("pattern-file argument expected");
			}

			compactedLexicon->buildEntries(*pattern, *morpho, verbose);
			compactedLexicon->saveFsa(verbose);
			compactedLexicon->closeFiles();
			return EXIT_SUCCESS;
		}

		case Buildlexicon::CONSULT:
		{
compactedLexicon = new CompactedLexicon(compactedLexiconFileName);
			compactedLexicon->openFiles("r");
			compactedLexicon->loadFsa(verbose);
			compactedLexicon->loadData(verbose);
			compactedLexicon->consult();
			compactedLexicon->closeFiles();
			return EXIT_SUCCESS;
		}

		case Buildlexicon::LIST:
		{
			compactedLexicon = new CompactedLexicon(compactedLexiconFileName);
			compactedLexicon->openFiles("r");
			compactedLexicon->loadFsa(verbose);
			compactedLexicon->loadData(verbose);
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
