# ##################################################
#
# ELVEX
#
# Copyright 2019 LABRI, 
# CNRS (UMR 5800), the University of Bordeaux,
# and the Bordeaux INP
#
# Author: 
# Lionel Clément
# LaBRI -- Université Bordeaux 
# 351, cours de la Libération
# 33405 Talence Cedex - France
# lionel.clement@labri.fr
# 
# This file is part of ELVEX.
#
################################################## #

SUFFIXES = .ll .yy
#############################################
# Do not edit
AUTOMAKE_OPTIONS = foreign

NAME= elvex

YFLAGS = -v --defines --report=all
LFLAGS = -8
CXXFLAGS = -std=c++11 -O3 -Wall -Wno-unused-label -Wno-unneeded-internal-declaration -Wno-deprecated-register  

bin_PROGRAMS = elvex elvexdebug elvexbuildlexicon elvexpostedition_fr elvexpostedition_en

elvex_SOURCES=\
rulesyacc.cpp\
ruleslex.cpp\
bitset.cpp\
compact-lexicon-buffer.cpp\
compact-lexicon-fsa.cpp\
compact-lexicon-info.cpp\
compact-lexicon-tree.cpp\
compact-lexicon.cpp\
entries.cpp\
entry.cpp\
environment.cpp\
feature.cpp\
features.cpp\
flags.cpp\
forest.cpp\
forestidentifier.cpp\
forestmap.cpp\
grammar.cpp\
id.cpp\
item.cpp\
itemset.cpp\
lexicon.cpp\
list.cpp\
listfeatures.cpp\
main.cpp\
memoization-map.cpp\
memoization-value.cpp\
node.cpp\
parser.cpp\
rule.cpp\
serializable.cpp\
statement.cpp\
statements.cpp\
synthesizer.cpp\
term.cpp\
terms.cpp\
value.cpp\
variableflag.cpp\
vartable.cpp

elvex_OPTIONS =
elvex_OPTIONS += -DRESTORE_MEMORY
elvex_OPTIONS += -DMEMOIZATION
elvex_OPTIONS += -DMAXLENGTH=1000
elvex_OPTIONS += -DMAXUSAGES=10000
elvex_OPTIONS += -DMAXCARDINAL=1000000
elvex_OPTIONS += -DMAXATTEMPTS=100
elvex_OPTIONS += -DMAXBITS=512

elvex_CXXFLAGS = -std=c++11 -O3 -Wall $(elvex_OPTIONS)
elvex_LDADD =

elvexdebug_SOURCES =\
rulesyacc.cpp\
ruleslex.cpp\
bitset.cpp\
compact-lexicon-buffer.cpp\
compact-lexicon-fsa.cpp\
compact-lexicon-info.cpp\
compact-lexicon-tree.cpp\
compact-lexicon.cpp\
entries.cpp\
entry.cpp\
environment.cpp\
feature.cpp\
features.cpp\
flags.cpp\
forest.cpp\
forestidentifier.cpp\
forestmap.cpp\
grammar.cpp\
id.cpp\
item.cpp\
itemset.cpp\
lexicon.cpp\
list.cpp\
listfeatures.cpp\
main.cpp\
memoization-map.cpp\
memoization-value.cpp\
node.cpp\
parser.cpp\
rule.cpp\
serializable.cpp\
statement.cpp\
statements.cpp\
synthesizer.cpp\
term.cpp\
terms.cpp\
value.cpp\
variableflag.cpp\
vartable.cpp 

elvexdebug_OPTIONS =
elvexdebug_OPTIONS += -DTRACE_OPTION
#elvexdebug_OPTIONS += -DTRACE_DIFF
#elvexdebug_OPTIONS += -DTRACE_MALLOC
#elvexdebug_OPTIONS += -DTRACE_SUCCESSOR
#elvexdebug_OPTIONS += -DTRACE_INSERT
#elvexdebug_OPTIONS += -DTRACE_UNHIDE
#elvexdebug_OPTIONS += -DTRACE_UNFOLD
#elvexdebug_OPTIONS += -DTRACE_EVAL
#elvexdebug_OPTIONS += -DTRACE_APPLY
#elvexdebug_OPTIONS += -DTRACE_LEXICON
#elvexdebug_OPTIONS += -DTRACE_MEMOIZATION
elvexdebug_OPTIONS += -DRESTORE_MEMORY
elvexdebug_OPTIONS += -DOUTPUT_XML
elvexdebug_OPTIONS += -DMEMOIZATION
elvexdebug_OPTIONS += -DMAXLENGTH=10000
elvexdebug_OPTIONS += -DMAXUSAGES=10000
elvexdebug_OPTIONS += -DMAXCARDINAL=1000000
elvexdebug_OPTIONS += -DMAXATTEMPTS=100
elvexdebug_OPTIONS += -DMAXBITS=512

elvexdebug_CXXFLAGS = -std=c++11 -Wall -O3 `xml2-config --cflags` $(elvexdebug_OPTIONS)
elvexdebug_LDADD = -lxml2

elvexbuildlexicon_SOURCES = \
rulesyacc.cpp\
ruleslex.cpp\
bitset.cpp\
buildlexicon.cpp\
compact-lexicon-buffer.cpp\
compact-lexicon-fsa.cpp\
compact-lexicon-info.cpp\
compact-lexicon-tree.cpp\
compact-lexicon.cpp\
entries.cpp\
entry.cpp\
environment.cpp\
feature.cpp\
features.cpp\
flags.cpp\
forest.cpp\
forestidentifier.cpp\
forestmap.cpp\
grammar.cpp\
id.cpp\
item.cpp\
itemset.cpp\
lexicon.cpp\
list.cpp\
listfeatures.cpp\
node.cpp\
parser.cpp\
rule.cpp\
serializable.cpp\
statement.cpp\
statements.cpp\
synthesizer.cpp\
term.cpp\
terms.cpp\
value.cpp\
variableflag.cpp\
vartable.cpp 

elvexbuildlexicon_OPTIONS =
#elvexbuildlexicon_OPTIONS += -DTRACE_DIFF
elvexbuildlexicon_OPTIONS += -DRESTORE_MEMORY
elvexbuildlexicon_CXXFLAGS = -std=c++11 -Wall -O3 -Wno-deprecated-register -Wno-unneeded-internal-declaration $(elvexbuildlexicon_OPTIONS)
elvexbuildlexicon_LDADD =

elvexpostedition_fr_SOURCES = postedition_fr.cpp

elvexpostedition_en_SOURCES = postedition_en.cpp

BUILT_SOURCES = 

DIST_COMMON = Makefile.in Makefile.am

EXTRA_DIST = 	

CLEANFILES = rulesyacc.cpp rulesyacc.h rulesyacc.output ruleslex.cpp postedition_fr.cpp postedition_en.cpp

$(elvex_OBJECTS): Makefile
$(elvexdebug_OBJECTS): Makefile
$(elvexbuildlexicon_OBJECTS): Makefile
$(elvexpostedition_OBJECTS): Makefile
$(elvexpostedition_fr_OBJECTS): Makefile
$(elvexpostedition_en_OBJECTS): Makefile

%.cpp: %.yy
	$(YACC) $(YFLAGS) -p rules -o $@ $<

%.cpp: %.ll
	$(LEX) $(LFLAGS) -Prules -o $@ $<
