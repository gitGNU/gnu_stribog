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
AC_INIT([stribog-auxilia], [0.1-minus], [stribog-bug@nongnu.org])
# force avr-based host without forcing avr-based build
AS_CASE(["z${avr_recursion_trigger}"],
 [ztriggered],,[
 export avr_recursion_trigger=triggered
 config_guessed=$(echo ${0} | sed "s/configure$/config.guess/")
 config_guessed=$(${config_guessed})
 AS_CASE([$#],
  [0],[${0} --build=${config_guessed} --host=avr],
  [
 #if --build is set it will override the guessed value
  ${0} --build=${config_guessed} $@ --host=avr
  ])
 result=$?
 export avr_recursion_trigger=triggered
 exit $result
])
AC_MSG_RESULT([NB here we force $host_alias host])

AC_CONFIG_SRCDIR([coil/sampler.c])

AH_TOP(
[/* Copyright (C) 2008 Ineiev<ineiev@users.sourceforge.net>, super V 93
 This file is an object-code part of stribog: it is produced
 automatically with autoheader when invoking autoreconf
 stribog is free design; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 3 of the License, or
 (at your option) any later version.*/
])

AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE([-Wall])
AC_PREFIX_DEFAULT([$HOME/stribog-install])
#checks for configured features

AC_MSG_CHECKING([for odometer MCU clock frequency])
AC_ARG_WITH([odo-clock],
[AS_HELP_STRING([--with-odo-clock],
 [Odometer MCU clock frequency in Hz [14745600]])],,
 [with_odo_clock=14745600
])
AC_MSG_RESULT([$with_odo_clock])
AC_DEFINE_UNQUOTED([ODO_F_CPU],(${with_odo_clock}ul),
 [Define as odometer MCU clock frequency in Hz])

AC_MSG_CHECKING([for odometer baud rate])
AC_ARG_WITH([odo-baud],
[AS_HELP_STRING([--with-odo-baud],
 [Odometer UART baud rate in Hz [9600]])],,
 [with_odo_baud=9600
])
AC_MSG_RESULT([$with_odo_baud])
AC_DEFINE_UNQUOTED([ODO_BAUD],(${with_odo_baud}ul),
 [Define as odometer UART baud rate in Hz])

AC_MSG_CHECKING([for odometer input mask])
AC_ARG_WITH([odo-mask],
[AS_HELP_STRING([--with-odo-mask],
 [Port C input mask for odometer pulses ['1<<5']])],,
 [with_odo_mask='1<<5'
])
AC_MSG_RESULT([$with_odo_mask])
AC_DEFINE_UNQUOTED([ODO_INPUT_MASK],
 [((unsigned char)(${with_odo_mask}))],
 [Define as PINC input mask for odometer pulses
  (typically one non-null bit)]
)

# Checks for programs.

AC_PROG_CC
AS_CASE(["z$GCC"],[zyes],[CFLAGS="-O3 -Wall"])
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

AS_CASE(["z$recursive_stribog_build"],[zyes],,[cat summary])
