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
AM_INIT_AUTOMAKE([-Wall])

AC_CONFIG_SRCDIR([config.h.in])
AC_CONFIG_HEADER([config.h])

# Checks for programs.
AC_PROG_CC
# Checks for libraries.
# Checks for header files.
# Checks for typedefs, structures, and compiler characteristics.

export recursive_stribog_build=yes
# Checks for library functions.

AC_CONFIG_FILES([Makefile])
#AC_CONFIG_FILES([sw/auxilia/coil/Makefile
#                 sw/auxilia/odo/Makefile
#                 sw/auxilia/odo/host/Makefile
#                 ])
AC_CONFIG_SUBDIRS([sw/host sw/target])
AC_OUTPUT
cat sw/host/summary sw/target/summary
