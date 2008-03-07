#stribog: configure.ac 
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
AC_INIT([stribog],[0.0-minus],[stribog-bug@nongnu.org])
AM_INIT_AUTOMAKE

AC_CONFIG_SRCDIR([config.h.in])
AC_CONFIG_HEADER([config.h])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([fcntl.h stdlib.h sys/ioctl.h termios.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST
AC_C_INLINE
AC_C_VOLATILE

AC_MSG_CHECKING([if stribog argp implementation is asked for])
AC_ARG_ENABLE([own-argp],
 AS_HELP_STRING([--enable-own-argp],
  [Use stribog implementation of argp library when building host tools [[no]]]),,
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
export build_own_argp
export recursive_stribog_build=yes
# Checks for library functions.
AC_CHECK_FUNCS([sqrt])

AC_CONFIG_FILES([Makefile])
#AC_CONFIG_FILES([sw/auxilia/coil/Makefile
#                 sw/auxilia/odo/Makefile
#                 sw/auxilia/odo/host/Makefile
#                 sw/target/Makefile])
AC_CONFIG_SUBDIRS([sw/host])
AC_OUTPUT
cat sw/host/summary
