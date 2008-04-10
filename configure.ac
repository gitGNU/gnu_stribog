#stribog: configure.ac 
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
AC_INIT([stribog],[0.0-minus],[stribog-bug@nongnu.org])
echo >warnings
distribution_impossible=no
AM_INIT_AUTOMAKE([-Wall])
AC_PREFIX_DEFAULT([$HOME/stribog-install])

AC_CONFIG_SRCDIR([sw/common/Makefile.am])

#checks for command-line options
AC_MSG_CHECKING([if ARM targets are enabled])
AC_ARG_ENABLE([arm-targets],
 [AS_HELP_STRING([--enable-arm-targets],
  [Build ARM targets @<:@decided based on the toolchain presence@:>@])],,
  [enable_arm_targets=unspecified
])
case "z$enable_arm_targets" in
 zno | zyes) ;;
 *) enable_arm_targets=unspecified ;;
esac
AC_MSG_RESULT([$enable_arm_targets])
AC_MSG_CHECKING([for ARM toolchain affix])
AC_ARG_WITH([arm-host],
[AS_HELP_STRING([--with-arm-host],
[affix for ARM toolchain [arm-unknown-elf]])],
[case $enable_arm_targets in
  no)
   AC_MSG_RESULT([$with_arm_host])
   AC_MSG_ERROR([

 Please either don't disable ARM targets or don't specify ARM toolchain affix])
   ;; 
 esac
 arm_host_specified=yes
],
 [with_arm_host=arm-unknown-elf
  arm_host_specified=no
])
AC_MSG_RESULT([$with_arm_host])
# Checks for programs.
AC_CHECK_PROG([arm_gcc_present],[$with_arm_host-gcc],[yes],[no])
case $arm_gcc_present in
 no)
  case $enable_arm_targets in
   yes)
    AC_MSG_ERROR([

 ARM targets are requested, but no toolchain is found])
   ;;
  esac
  case $arm_host_specified in
   no) enable_arm_targets=no ;;
   yes)
    AC_MSG_ERROR([

 ARM toolchain affix is specified, but no toolchain is found])
  ;;
  esac ;;
 yes)
  case $enable_arm_targets in
   no) ;; *) enable_arm_targets=yes ;;
  esac ;;
esac
AM_CONDITIONAL(enable_arm_targets, test $enable_arm_targets = yes)
case $enable_arm_targets in
 no) distribution_impossible=yes ;;
esac

AC_PROG_MKDIR_P

#TODO check for pcb(?)

# Checks for libraries.
# Checks for header files.
# Checks for typedefs, structures, and compiler characteristics.
# Checks for library functions.
#output files setup
export recursive_stribog_build=yes
export ARM_TOOLS_PREFIX=$with_arm_host
AC_CONFIG_FILES([Makefile hw/Makefile
                 sw/common/Makefile])
#AC_CONFIG_FILES([sw/auxilia/coil/Makefile
#                 sw/auxilia/odo/Makefile
#                 sw/auxilia/odo/host/Makefile
#                 ])
AC_CONFIG_SUBDIRS([sw/host])
case $enable_arm_targets in
 yes)
  AC_CONFIG_SUBDIRS([sw/target])
 ;;
esac

AC_OUTPUT
#summary output
enabled_subprojects=hosttools
case $enable_arm_targets in
 yes)enabled_subprojects="$enabled_subprojects target";;
esac
case $distribution_impossible in
 yes)
  echo "NOTE: some subprojects have been disabled; dist* targets shall fail"\
  >>warnings
 ;;
esac

echo "Configuration summary for ${PACKAGE} ${VERSION}:" >summary
echo >>summary
echo "enabled subprojects:  ${enabled_subprojects}">>summary
cat warnings >>summary
rm -f warnings

echo;cat summary
echo;cat sw/host/summary

case $enable_arm_targets in
 yes)
 echo;cat sw/target/summary
 ;;
esac
