#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([super-awesome-casm-usage], [0.0.0], [youremail@here])
AC_CONFIG_SRCDIR([src/main.cpp])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([build-aux/m4])
AM_INIT_AUTOMAKE([subdir-objects])

AC_PROG_RANLIB

#Allow renaming programs
AC_ARG_PROGRAM

# Checks for programs.
AC_PROG_CXX
AX_CXX_COMPILE_STDCXX_11

# Checks for libraries.
BOOSTV=1.52
AX_BOOST_BASE([$BOOSTV],[],[AC_MSG_ERROR(You need Boost $BOOSTV libraries or higher.)])
AX_BOOST_FILESYSTEM
AX_BOOST_SYSTEM
AX_BOOST_REGEX
AX_BOOST_CHRONO
AX_BOOST_PROGRAM_OPTIONS

AC_CHECK_LIB([casm],[main], [], [AC_MSG_ERROR(The CASM libraries are required!)])

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
