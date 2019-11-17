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

SUFFIXES = .cc .o .ll .yy
#############################################
# Do not edit
AUTOMAKE_OPTIONS = foreign

NAME= elvex

YFLAGS = -v --defines --report=all
LFLAGS = -8
CXXFLAGS = -g -std=c++11 -O3 -Wall -Wno-unused-label -Wno-unneeded-internal-declaration -Wno-deprecated-register  

bin_PROGRAMS = elvex elvexdebug elvexbuildlexicon elvexpostedition

elvex_SOURCES=\
rulesyacc.cc\
ruleslex.cc\
bitset.cc\
entries.cc\
entry.cc\
environment.cc\
feature.cc\
features.cc\
listfeatures.cc\
flags.cc\
forest.cc\
forestidentifier.cc\
forestmap.cc\
item.cc\
itemset.cc\
grammar.cc\
id.cc\
fsa.cc\
info.cc\
infobuff.cc\
lex.cc\
main.cc\
memoizationvalue.cc\
memoizationmap.cc\
node.cc\
parser.cc\
pattern.cc\
rule.cc\
serializable.cc\
statement.cc\
statements.cc\
synthesizer.cc\
term.cc\
terms.cc\
tree.cc\
value.cc\
list.cc\
variableflag.cc\
vartable.cc

elvex_OPTIONS =
#elvex_OPTIONS += -DTRACE_MALLOC
elvex_OPTIONS += -DMEMOIZATION
elvex_OPTIONS += -DMEMOIZATION_SHIFT
elvex_OPTIONS += -DMEMOIZATION_REDUCE
elvex_OPTIONS += -DMAXLENGTH=1000
elvex_OPTIONS += -DMAXUSAGES=10000
elvex_OPTIONS += -DMAXCARDINAL=1000000
elvex_OPTIONS += -DMAXATTEMPTS=1000
elvex_OPTIONS += -DMAXBITS=512

elvex_CXXFLAGS = -std=c++11 -O5 -Wall $(elvex_OPTIONS)
elvex_LDADD =

elvexdebug_SOURCES =\
rulesyacc.cc\
ruleslex.cc\
bitset.cc\
entries.cc\
entry.cc\
environment.cc\
feature.cc\
features.cc\
flags.cc\
forest.cc\
forestidentifier.cc\
forestmap.cc\
fsa.cc\
grammar.cc\
id.cc\
info.cc\
infobuff.cc\
item.cc\
itemset.cc\
lex.cc\
list.cc\
listfeatures.cc\
main.cc\
memoizationmap.cc\
memoizationvalue.cc\
node.cc\
pattern.cc\
parser.cc\
rule.cc\
serializable.cc\
statement.cc\
statements.cc\
synthesizer.cc\
term.cc\
terms.cc\
tree.cc\
value.cc\
variableflag.cc\
vartable.cc 

elvexdebug_OPTIONS =
elvexdebug_OPTIONS += -DTRACE
#elvexdebug_OPTIONS += -DTRACE_DIFF
#elvexdebug_OPTIONS += -DTRACE_MALLOC
#elvexdebug_OPTIONS += -DTRACE_SUCCESSOR
#elvexdebug_OPTIONS += -DTRACE_INSERT
#elvexdebug_OPTIONS += -DTRACE_UNHIDE
#elvexdebug_OPTIONS += -DTRACE_UNFOLD
#elvexdebug_OPTIONS += -DTRACE_EVAL
#elvexdebug_OPTIONS += -DTRACE_APPLY
#elvexdebug_OPTIONS += -DTRACE_ACTION
#elvexdebug_OPTIONS += -DTRACE_LEXICON
#elvexdebug_OPTIONS += -DTRACE_MEMOIZATION
elvexdebug_OPTIONS += -DOUTPUT_XML
elvexdebug_OPTIONS += -DMEMOIZATION
elvexdebug_OPTIONS += -DMEMOIZATION_SHIFT
elvexdebug_OPTIONS += -DMEMOIZATION_REDUCE
elvexdebug_OPTIONS += -DMAXLENGTH=10000
elvexdebug_OPTIONS += -DMAXUSAGES=10000
elvexdebug_OPTIONS += -DMAXCARDINAL=1000000
elvexdebug_OPTIONS += -DMAXATTEMPTS=10000
elvexdebug_OPTIONS += -DMAXBITS=512

elvexdebug_CXXFLAGS = -std=c++11 -Wall -O3 `xml2-config --cflags` $(elvexdebug_OPTIONS)
elvexdebug_LDADD = -lxml2

elvexbuildlexicon_SOURCES = \
buildlexicon.cc\
bitset.cc\
entries.cc\
entry.cc\
environment.cc\
feature.cc\
features.cc\
flags.cc\
fsa.cc\
forest.cc\
forestidentifier.cc\
forestmap.cc\
grammar.cc\
id.cc\
info.cc\
infobuff.cc\
item.cc\
itemset.cc\
lex.cc\
list.cc\
listfeatures.cc\
node.cc\
parser.cc\
pattern.cc\
rule.cc\
rulesyacc.cc\
ruleslex.cc\
serializable.cc\
statement.cc\
statements.cc\
synthesizer.cc\
term.cc\
terms.cc\
tree.cc\
value.cc\
variableflag.cc\
vartable.cc 

elvexbuildlexicon_OPTIONS =
#elvexbuildlexicon_OPTIONS += -DTRACE_DIFF
elvexbuildlexicon_CXXFLAGS = -std=c++11 -Wall -O5 -Wno-deprecated-register -Wno-unneeded-internal-declaration $(elvexbuildlexicon_OPTIONS)
elvexbuildlexicon_LDADD =

elvexpostedition_SOURCES = postedition.cc

BUILT_SOURCES = 

DIST_COMMON = Makefile.in Makefile.am

EXTRA_DIST = 	

CLEANFILES = rulesyacc.cc rulesyacc.hh rulesyacc.output ruleslex.cc postedition.cc

$(elvex_OBJECTS): Makefile
$(elvexdebug_OBJECTS): Makefile
$(elvexbuildlexicon_OBJECTS): Makefile
$(elvexpostedition_OBJECTS): Makefile

%.cc: %.yy
	$(YACC) $(YFLAGS) -p rules -o $@ $<

%.cc: %.ll
	$(LEX) $(LFLAGS) -Prules -o $@ $<
