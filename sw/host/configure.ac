#stribog host tools: configure.ac 
# Run autoreconf to regenerate the build system
#Copyright (C) 2008\
# Ineiev<ineiev@users.sourceforge.net>, super V 93
#
#This program is free software; you can redistribute it and/or modify
#it under the terms of the GNU General Public License as published by
#the Free Software Foundation; either version 3 of the License, or
#(at your option) any later version.
#
#This program is distributed in the hope that it will be useful,
#but WITHOUT ANY WARRANTY; without even the implied warranty of
#MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#GNU General Public License for more details.
#
#You should have received a copy of the GNU General Public License
#along with this program. If not, see <http://www.gnu.org/licenses/>.

AC_PREREQ(2.61)
AC_INIT([stribog-hosttools], [0.0-minus], [stribog-bug@nongnu.org])
AC_CANONICAL_HOST
AM_INIT_AUTOMAKE([-Wall])

AC_CONFIG_SRCDIR([config.h.in])
AC_CONFIG_HEADER([config.h])

# Checks for programs.
AC_PROG_CC
AC_PROG_RANLIB

if test "z$GCC" = "zyes"; then
 CFLAGS="${CFLAGS} -Wall"
fi

# Checks for libraries.
AC_CHECK_LIB([m], [sqrt])

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([fcntl.h float.h stdint.h stdlib.h string.h termios.h unistd.h])

#argp library configuration
if test "z$build_own_argp" = "z";then
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
else
 AC_MSG_RESULT([argp implementation seems to have been already selected])
fi
if test "z$build_own_argp" = "zyes";then
 AC_CHECK_TYPES([error_t])
 AC_CONFIG_FILES([argp.h:lib/argp/argp.h])
 AC_SUBST(argp_lib,["\$(top_builddir)/lib/argp/libargp.a"])
 AC_CHECK_HEADERS([sysexits.h])
fi
AM_CONDITIONAL(build_own_argp, test "z$build_own_argp" = "zyes")

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
		the_host_is_windows=yes
		;;
esac
AM_CONDITIONAL(the_host_is_windows, test "z$the_host_is_windows" = "zyes")

AC_SUBST(stribog_lib,["\$(top_builddir)/lib/libstribog.a"])
#common headers are copied to top build directory
#to be available the same as config.h
AC_CONFIG_FILES([stribog_error.h:lib/stribog_error.h])
AC_CONFIG_FILES([stribog_strings.h:lib/stribog_strings.h])
#Makefiles are generated
AC_CONFIG_FILES([Makefile
                 conloq/Makefile
                 elk/Makefile
                 intlpc/Makefile
                 lib/Makefile
                 lib/argp/Makefile
                 postproc/Makefile
                 utils/Makefile])
AC_OUTPUT
if test "z$build_own_argp" = "zyes"; then
 argp_type=built-in
else
 argp_type=GNU
fi

echo >summary;echo >>summary
echo "Configuration summary for ${PACKAGE} ${VERSION}:" >>summary
echo >>summary
echo "prefix:               ${prefix}">>summary
echo "host:                 ${host}">>summary
echo "argv parser:          ${argp_type}">>summary
echo "CFLAGS:               ${CFLAGS}">>summary
echo "LDFLAGS:              ${LDFLAGS}">>summary
echo "LIBS:                 ${LIBS}">>summary
echo >>summary

if test "z$recursive_stribog_build" != "zyes";then
 AC_MSG_RESULT([[$(cat summary)]])
fi
