#stribog: configure.ac 
# Run ./regen_configure to regenerate the build system
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
echo >warnings
distribution_impossible=no
AM_INIT_AUTOMAKE([-Wall])
AC_PREFIX_DEFAULT([$HOME/stribog-install])

AC_CONFIG_SRCDIR([sw/common/Makefile.am])

AC_MSG_CHECKING([if ARM targets are enabled])
AC_ARG_ENABLE([arm-targets],
 AS_HELP_STRING([--enable-arm-targets],
  [[Build ARM targets [yes]]]))
case "z$enable_arm_targets" in
 zno)
 distribution_impossible=yes
 ;;
 *) enable_arm_targets=yes
 ;;
esac
AC_MSG_RESULT([$enable_arm_targets])
AM_CONDITIONAL(enable_arm_targets, test $enable_arm_targets = yes)
AC_ARG_WITH([arm-host],
AS_HELP_STRING([--with-arm-host],
[[affix for ARM toolchain [arm-unknown-elf]]]))
# Checks for programs.
# Checks for libraries.
# Checks for header files.
# Checks for typedefs, structures, and compiler characteristics.
# Checks for library functions.
#output files setup
export recursive_stribog_build=yes
export ARM_TOOLS_PREFIX=$with_arm_host
AC_CONFIG_FILES([Makefile
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
  echo "NOTE: you disabled some subprojects; dist* targets shall fail"\
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
