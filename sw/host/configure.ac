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
 CFLAGS="$(echo $CFLAGS |sed -e "s/ -Wall\>//g") -Wall"
fi

# Checks for libraries.

AC_CHECK_LIB([m], [sqrt])

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([fcntl.h float.h stdint.h stdlib.h string.h termios.h unistd.h])

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

case $host in
        *-*-mingw32* | *-*-cygwin* | *-*-windows*)
		the_target_is_windows=true
		;;
esac
AM_CONDITIONAL(the_host_is_windows, test x$the_host_is_windows = xtrue)

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
CFLAGS:               ${CFLAGS}
])
