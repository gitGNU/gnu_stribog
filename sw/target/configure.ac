#stribog target: configure.ac 
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
AC_INIT([stribog-target],[0.0-minus],[stribog-bug@nongnu.org])
AM_INIT_AUTOMAKE([-Wall])
AC_CONFIG_SRCDIR([src/dacex.c])
AC_CONFIG_HEADER([config.h])
if test "z$build_target_programs" = "z";then
 AC_MSG_CHECKING([if stribog target build is asked for])
 AC_ARG_ENABLE([target-programs],
  AS_HELP_STRING([--enable-target-programs],
   [Rebuild software [[yes]]]),,
 )
 if test "z$enable_target_programs" != "zno";then
  enable_target_programs=yes
 fi
 AC_MSG_RESULT([$enable_target_programs])
 AC_CHECK_PROG([arm_elf_tools],[arm-elf-gcc],[yes],[no],,)
 if test "z$arm_elf_tools" = "zno";then
  AC_MSG_RESULT([no usable ARM crosstools found; the distributed programs will be installed])
  build_target_programs=no
 fi
fi
if test "z$build_target_programs" = "zyes";then
 CC=arm-elf-gcc
fi
AM_CONDITIONAL([build_target_programs], test "z$build_target_programs" = "zyes")
# Checks for programs.
# Checks for libraries.

# Checks for header files.
# Checks for typedefs, structures, and compiler characteristics.

# to tell the truth there is absolutely no need
# to check all these things when we are not 
# building the programs; however,
# the host tools do need gcc and
# autoreconf does not build correct 'configure'
# if we make the tests conditionally, so
# we do not test whether we are really building
# the programs. perhaps this is not the right way
#if test "z$build_target_programs" = "zyes";then
 AC_C_CONST
 AC_C_INLINE
 AC_C_VOLATILE

# Checks for library functions.
#sqrt is used in host-side test only
 #AC_CHECK_FUNCS([sqrt])

 CFLAGS="-O2 -Wall"
#fi# test "z$build_target_programs" = "zyes";then
AC_CONFIG_FILES([Makefile])
AC_OUTPUT
echo "Configuration summary for ${PACKAGE} ${VERSION}:" >summary
echo >>summary
echo "prefix:               ${prefix}">>summary
echo "whether to build:     ${build_target_programs}">>summary
echo "CFLAGS:               ${CFLAGS}">>summary
echo "LDFLAGS:              ${LDFLAGS}">>summary
echo "LIBS:                 ${LIBS}">>summary
echo >>summary

if test "z$recursive_stribog_build" != "zyes";then
 AC_MSG_RESULT([[$(cat summary)]])
fi
