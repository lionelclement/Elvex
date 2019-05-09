#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])

# ====================
# Version informations
# ====================
m4_define([elvex_version_major],[2])
m4_define([elvex_version_minor],[10])
m4_define([elvex_version_micro],[1])
m4_define([elvex_version],[elvex_version_major.elvex_version_minor.elvex_version_micro])

# =============
# Automake init
# =============
AC_INIT([elvex],[elvex_version])
AM_INIT_AUTOMAKE([-Wno-portability])
AM_SILENT_RULES([yes])
AC_LANG([C++])

# Checks for programs.
AC_PROG_INSTALL
AC_PROG_CXX
AC_PROG_CC_C_O
AC_PROG_LEX
AC_PROG_MAKE_SET
AC_PROG_YACC

# Checks for header files.
AC_FUNC_ALLOCA
AC_CHECK_HEADERS([errno.h], [], [AC_MSG_ERROR(Elvex needs <errno.h>)])
AC_CHECK_HEADERS([signal.h], [], [AC_MSG_ERROR(Elvex needs <signal.h>)])
AC_CHECK_HEADERS([stdio.h], [], [AC_MSG_ERROR(Elvex needs <stdio.h>)])
AC_CHECK_HEADERS([stdlib.h], [], [AC_MSG_ERROR(Elvex needs <stdlib.h>)])
AC_CHECK_HEADERS([string.h], [], [AC_MSG_ERROR(Elvex needs <string.h>)])
AC_CHECK_HEADERS([sys/resource.h], [], [AC_MSG_ERROR(Elvex needs <sys/resource.h>)])
AC_CHECK_HEADERS([sys/stat.h], [], [AC_MSG_ERROR(Elvex needs <sys/stat.h>)])
AC_CHECK_HEADERS([time.h], [], [AC_MSG_ERROR(Elvex needs <time.h>)])
AC_CHECK_HEADERS([unistd.h], [], [AC_MSG_ERROR(Elvex needs <unistd.h>)])
# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_ERROR_AT_LINE
AC_FUNC_FORK
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_CHECK_FUNCS([alarm bzero gethostbyname inet_ntoa memset strdup strtol])

AC_CONFIG_FILES([Makefile
                 src/Makefile
		 data/Makefile
		 data/lefff/Makefile
		 ])
AC_OUTPUT
