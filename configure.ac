#stribog: top configure.ac
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

#initially we used Autoconf-2.61, but it had two limitations,
#a. AC_INIT shifted out command-line arguments;
#b. --help=recursive implementation had a bug
AC_PREREQ(2.62)
AC_INIT([stribog],[0.0-minus],[stribog-bug@nongnu.org])
rm -f warnings
distribution_impossible=no
AM_INIT_AUTOMAKE([-Wall])
AC_PREFIX_DEFAULT([$HOME/stribog-install])

AC_CONFIG_SRCDIR([sw/common/Makefile.am])

#checks for command-line options
# ARM toolchain-specific
AC_MSG_CHECKING([if ARM targets are enabled])
AC_ARG_ENABLE([arm-targets],
 [AS_HELP_STRING([--enable-arm-targets],
  [Build ARM targets @<:@yes when possible@:>@])],,
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
#the same for AVR
AC_MSG_CHECKING([if AVR targets are enabled])
AC_ARG_ENABLE([avr-targets],
 [AS_HELP_STRING([--enable-avr-targets],
  [Build AVR targets @<:@yes when possible@:>@])],,
  [enable_avr_targets=unspecified
])
case "z$enable_avr_targets" in
 zno | zyes) ;;
 *) enable_avr_targets=unspecified ;;
esac
AC_MSG_RESULT([$enable_avr_targets])

AC_MSG_CHECKING([for schematics output resolution])
AC_ARG_ENABLE([schematics-resolution],
 [AS_HELP_STRING([--enable-schematics-resolution],
  [schematics output resolution (actual only if the output is rebuilt)
 @<:@3200x2400@:>@])],,
  [enable_schematics_resolution=3200x2400
])
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

AC_CHECK_PROG([avr_gcc_present],[avr-gcc],[yes],[no])
case $avr_gcc_present in
 no)
  case $enable_avr_targets in
   yes)
    AC_MSG_ERROR([

 AVR targets are requested, but no toolchain is found])
   ;;
  esac
  ;;
 yes)
  case $enable_avr_targets in
   no) ;; *) enable_avr_targets=yes ;;
  esac ;;
esac
AM_CONDITIONAL(enable_avr_targets, test $enable_avr_targets = yes)
case $enable_avr_targets in
 no) distribution_impossible=yes ;;
esac

AC_PROG_MKDIR_P
AC_PROG_LN_S

#TODO check for pcb(?) and for gschem

# Checks for libraries.
# Checks for header files.
# Checks for typedefs, structures, and compiler characteristics.
# Checks for library functions.
#output files setup
export recursive_stribog_build=yes
export ARM_TOOLS_PREFIX=$with_arm_host
image_size=$(echo $enable_schematics_resolution|sed "s/x/ /g")
AC_SUBST([SCHEMATICS_IMAGE_SIZE],[$image_size])
AC_CONFIG_FILES([Makefile hw/Makefile hw/image.scm
                 sw/common/Makefile])

AC_CONFIG_SUBDIRS([sw/host])
case $enable_arm_targets in
 yes)
  AC_CONFIG_SUBDIRS([sw/target])
 ;;
esac
case $enable_avr_targets in
 yes)
  AC_CONFIG_SUBDIRS([sw/auxilia])
 ;;
esac

AC_OUTPUT
#summary output
enabled_subprojects=hosttools
case $enable_arm_targets in
 yes)enabled_subprojects="$enabled_subprojects target";;
esac
case $enable_avr_targets in
 yes)enabled_subprojects="$enabled_subprojects auxilia";;
esac
case $distribution_impossible in
 yes)
  echo "NOTE: some subprojects have been disabled; dist* targets shall fail"\
  >>warnings
 ;;
esac

echo "Configuration summary for ${PACKAGE} ${VERSION}:" >summary
echo "prefix:               ${prefix}">>summary
echo "enabled subprojects:  ${enabled_subprojects}">>summary
cat warnings >>summary
rm -f warnings

echo;cat summary
echo;cat sw/host/summary|grep -v "^prefix:"
case $enable_arm_targets in
 yes) echo; cat sw/target/summary|grep -v "^prefix:" ;;
esac
case $enable_avr_targets in
 yes) echo; cat sw/auxilia/summary|grep -v "^prefix:" ;;
esac
