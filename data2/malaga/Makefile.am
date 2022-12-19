SUFFIXES = .cc .o .ll .yy
#############################################
# Do not edit
AUTOMAKE_OPTIONS = foreign

NAME= postedition

YFLAGS = -v --defines --report=all
LEX = flex
LFLAGS = -8
CXXFLAGS =

bin_PROGRAMS = postedition

postedition_SOURCES = postedition.cc

BUILT_SOURCES = 

DIST_COMMON = Makefile.in Makefile.am

EXTRA_DIST = 	

CLEANFILES = postedition.cc

$(postedition_OBJECTS): Makefile

%.cc: %.ll
	$(LEX) $(LFLAGS) -o $@ $<
