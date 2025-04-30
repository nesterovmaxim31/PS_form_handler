dnl Minimal version required (Not tested on older version)
AC_PREREQ([2.71])

dnl PS form hadler, version 1.0
AC_INIT([psform_handler],[1.0],[maxgoonfuture@gmail.com])
AC_CONFIG_SRCDIR([src/psform.c])

dnl Language 
AC_LANG(C)

dnl Check for C compiler
AC_PROG_CC

dnl Check for const
AC_C_CONST
AC_C_INLINE

dnl Check for included default C libraries
AC_CHECK_INCLUDES_DEFAULT

dnl CFLAGS
CFLAGS="-march=native -mtune=native -Wall -fsigned-char -std=gnu11"  

dnl TESTTOOLS
AC_SUBST(TESTTOOLS, "")

dnl Check for debug flag
AC_ARG_ENABLE([debug],
  [AS_HELP_STRING([--enable-debug],
                  [whether to include debug symbols (default is no)])],
  [CFLAGS="$CFLAGS -g -O0"],
  [CFLAGS="$CFLAGS -O3"]
)

dnl Check for test tools
AC_CHECK_PROG([TIME], [time], [yes], [no])
AC_ARG_ENABLE([benchmark],
  [AS_HELP_STRING([--enable-benchmark],
                  [whether to enable benchmark (default is no).
				  Make sure you have INSTALLED time utility, not
				  a shell keywork])],
  [if test "$TIME" = "yes"; then
  	  TESTTOOLS="$TESTTOOLS time"
   else
      AC_MSG_ERROR([time utility isn't installed])
   fi],
  [TESTTOOLS="$TESTTOOLS"]
)

dnl Check for benchmark operation
AC_ARG_ENABLE([benchmark-operation],
  [AS_HELP_STRING([--enable-benchmark-operation],
                  [whether to enable benchmark only
				  for math operation (default is no)])],
  [CFLAGS="$CFLAGS -DENABLE_BENCHMARK_OPERATION"],		
  [CFLAGS="$CFLAGS"]
)

dnl Check for valgrind
AC_CHECK_PROG([VALGRIND], [valgrind], [yes], [no])
AC_ARG_ENABLE([valgrind],
  [AS_HELP_STRING([--enable-valgrind],
                  [whether to enable valgrind (default is no)])],
				  
  [if test "$VALGRIND" = "yes"; then
  	  TESTTOOLS="$TESTTOOLS valgrind --track-origins=yes --leak-check=full"
   else
      AC_MSG_ERROR([valgrind isn't installed])
   fi],
  [TESTTOOLS="$TESTTOOLS"]
)

dnl Check for address sanitizer
AC_ARG_ENABLE([AddressSanitizer],
  [AS_HELP_STRING([--enable-AddressSanitizer],
                  [whether to enable address sanitizer (default is no)])],
  [CFLAGS="$CFLAGS -fsanitize=address"],
  [CFLAGS="$CFLAGS"]
)

dnl Check for memory sanitizer (Only for clang as CC)
AC_ARG_ENABLE([MemorySanitizer],
  [AS_HELP_STRING([--enable-MemorySanitizer],
                  [whether to enable memory sanitizer (default is no)])],	  
  [if test "$CC" = "clang"; then 
  	  CFLAGS="$CFLAGS -fsanitize=memory"
   else
	  AC_MSG_ERROR([Memory sanitizer is enable only for clang])
   fi],
  [CFLAGS="$CFLAGS"]
)

dnl Config file and output
AC_CONFIG_FILES([Makefile])
AC_OUTPUT


