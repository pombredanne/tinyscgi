#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([tinyscgi], [0.1], [tonyseek@gmail.com])
LT_INIT
AM_INIT_AUTOMAKE
AC_CONFIG_SRCDIR([config.h.in])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC
AM_PROG_CC_C_O
PKG_CHECK_MODULES([CHECK], [check >= 0.9.4])
AC_ARG_ENABLE([debug],
              [AS_HELP_STRING([--enable-debug],
                              [debug program (default is no)])],
              [CFLAGS="${CFLAGS} -DDEBUG -O0 -g3"],
              [CFLAGS="${CFLAGS}"])

# Checks for libraries.
AC_SEARCH_LIBS(socket, socket)

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_CONFIG_FILES([Makefile
                 src/Makefile
                 tests/Makefile])
AC_OUTPUT
