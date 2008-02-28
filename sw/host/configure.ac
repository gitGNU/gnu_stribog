#                                               -*- Autoconf -*-
# Run autoreconf to regenerate the build system

AC_PREREQ(2.61)
AC_INIT([stribog-hosttools], [0.0.0-rc0], [stribog-bug@nongnu.org])
AC_CANONICAL_HOST
AM_INIT_AUTOMAKE

AC_CONFIG_SRCDIR([config.h.in])
AC_CONFIG_HEADER([config.h])


# Checks for programs.
AC_PROG_CC

if test "z$GCC" = "zyes"; then
 CFLAGS="${CFLAGS} -Wall"
fi

# Checks for libraries.

AC_CHECK_LIB([m], [sqrt])

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([fcntl.h float.h stdint.h stdlib.h string.h termios.h unistd.h])

#argp library configuration
AC_MSG_CHECKING([if stribog argp implementation is asked for])
AC_ARG_ENABLE([own-argp],
 AS_HELP_STRING([--enable-own-argp],
  [Use stribog implementation of argp library [[no]]]),,
)
if test "z$enable_own_argp" != "zyes";then
 enable_own_argp=no
fi
AC_MSG_RESULT([$enable_own_argp])
build_own_argp=$enable_own_argp
if test "z$enable_own_argp" = "zno";then
 AC_CHECK_HEADER([argp.h],,
  [AC_MSG_RESULT([no usable argp.h found; stribog version will be used])
   build_own_argp=yes
 ])
fi
if test "z$build_own_argp" = "zyes";then
 CPPFLAGS="$CPPFLAGS -I$srcdir/lib/argp"
fi

# Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST
AC_C_INLINE
AC_TYPE_UINT16_T

# Checks for library functions.
AC_FUNC_ERROR_AT_LINE
AC_FUNC_MALLOC
AC_FUNC_MEMCMP
AC_TYPE_SIGNAL
AC_FUNC_VPRINTF
AC_CHECK_FUNCS([atexit memmove sqrt strchr strerror])

#Checks for system services
case $host in
        *-*-mingw32* | *-*-cygwin* | *-*-windows*)
		the_host_is_windows=true
		;;
esac
AM_CONDITIONAL(the_host_is_windows, test "x$the_host_is_windows" = "xtrue")

AC_CONFIG_FILES([Makefile
                 conloq/Makefile
                 elk/Makefile
                 intlpc/Makefile
                 postproc/Makefile
                 utils/Makefile])
AC_OUTPUT

AC_MSG_RESULT([

Configuration summary for ${PACKAGE} ${VERSION}:

prefix:               ${prefix}
host:                 ${host}
CPPFLAGS:             ${CPPFLAGS}
CFLAGS:               ${CFLAGS}
LIBS:                 ${LIBS}
])
