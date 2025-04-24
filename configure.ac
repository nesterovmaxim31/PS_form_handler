dnl Minimal version required (Not tested on older version)
AC_PREREQ([2.72])

dnl PS form hadler, version 1.0
AC_INIT([psform_handler], [1.0], [maxgoonfuture@gmail.com])
AC_CONFIG_SRCDIR([src/psform.c])

dnl Language 
AC_LANG(C)

dnl Check for C compiler
AC_PROG_CC

dnl Check for included default C libraries
AC_CHECK_INCLUDES_DEFAULT

dnl CFLAGS
CFLAGS="$CFLAGS -march=native -mtune=native -Wall -fsigned-char"  

dnl Check for debug flag
AC_ARG_ENABLE([debug],
  [AS_HELP_STRING([--enable-debug],
                  [whether to include debug symbols (default is no)])],
  [CFLAGS="$CFLAGS -g0 -O0"],
  [CFLAGS="$CFLAGS -O3"]
)

dnl Config file and output
AC_CONFIG_FILES([Makefile])
AC_OUTPUT


