#stribog: configure.ac for AVR targets
# Run autoreconf to regenerate the build system
#Copyright (C) 2008 Ineiev<ineiev@users.sourceforge.net>, super V 93
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
AC_PREREQ(2.62)
AC_INIT([stribog-auxilia], [0.0-minus], [stribog-bug@nongnu.org])
# force avr-based host without forcing avr-based build
case "z${target_recursion_trigger}" in
 ztriggered) ;;
 *) export target_recursion_trigger=triggered
 config_guessed=$(echo ${0} | sed "s/configure$/config.guess/")
 config_guessed=$(${config_guessed})
 case $# in
  0) ${0} --build=${config_guessed} --host=avr;;
 #if --build is set it will override the guessed value
  *) ${0} --build=${config_guessed} $@ --host=avr;;
 esac
 result=$?
 export target_recursion_trigger=triggered
 exit $result ;;
esac
AC_MSG_RESULT([NB here we force $host_alias host])
echo >warnings

AC_CONFIG_SRCDIR([coil/sampler.c])
AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE([-Wall])
AC_PREFIX_DEFAULT([$HOME/stribog-install])

# Checks for programs.

AC_PROG_CC
case "z$GCC" in
 zyes) CFLAGS="-O3 -Wall" ;;
esac
# Checks for libraries.

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.
AC_C_INLINE

# Checks for library functions.

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
echo "Configuration summary for ${PACKAGE} ${VERSION}:" >summary
echo "prefix:               ${prefix}">>summary
echo "CFLAGS:               ${CFLAGS}">>summary
echo "LDFLAGS:              ${LDFLAGS}">>summary
echo "detected tools versions:">>summary
avr-as --version |grep assembler >>summary
${CC} --version |grep ${CC} >>summary

case "z$recursive_stribog_build" in
 zyes) ;; *) cat summary;;
esac
