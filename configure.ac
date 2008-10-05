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
rm -f warnings;touch warnings
distribution_impossible=no
AM_INIT_AUTOMAKE([-Wall])
AC_PREFIX_DEFAULT([$HOME/stribog-install])

AC_CONFIG_SRCDIR([sw/common/Makefile.am])

#checks for command-line options
AC_MSG_CHECKING([if documentation is enabled])
AC_ARG_ENABLE([doc],
 [AS_HELP_STRING([--enable-doc],
  [Manage documentation @<:@yes when available@:>@])])
AS_CASE(["z$enable_doc"],[zno | zyes],,[enable_doc=unspecified])
AC_MSG_RESULT([$enable_doc])
AC_MSG_CHECKING([if documentation is available])
AS_IF([test -f ${srcdir}/doc/stribog.texinfo],
 [AC_MSG_RESULT([yes])
  AS_CASE([$enable_doc],[no],,[enable_doc=yes])],
[AC_MSG_RESULT([no])
  AS_CASE([$enable_doc],
  [yes],[ 
   AC_MSG_RESULT([$enable_doc])
   AC_MSG_ERROR([

 Documentation is requested, but unavailable
])],[enable_doc=no])dnl AS_CASE
])dnl AS_IF([test -f ${srcdir}/doc/stribog.texinfo],
AS_CASE([$enable_doc],[no],[distribution_impossible=yes])
AM_CONDITIONAL([enable_doc],[test $enable_doc = yes])

# ARM toolchain-specific command-line options
AC_MSG_CHECKING([if ARM targets are enabled])
AC_ARG_ENABLE([arm-targets],
 [AS_HELP_STRING([--enable-arm-targets],
  [Build ARM targets @<:@yes when possible@:>@])])
AS_CASE(["z$enable_arm_targets"],
 [zno | zyes],,[enable_arm_targets=unspecified])
AC_MSG_RESULT([$enable_arm_targets])
AC_MSG_CHECKING([for ARM toolchain affix])
AC_ARG_WITH([arm-host],
 [AS_HELP_STRING([--with-arm-host],
 [affix for ARM toolchain [arm-unknown-elf]])],
 [AS_CASE([$enable_arm_targets],
   [no],[
    AC_MSG_RESULT([$with_arm_host])
    AC_MSG_ERROR([

 Please either don't disable ARM targets or don't specify ARM toolchain affix
])])dnl AS_CASE([$enable_arm_targets],
 arm_host_specified=yes
],
 [with_arm_host=arm-unknown-elf
  arm_host_specified=no
])dnl AC_ARG_WITH([arm-host],
AC_MSG_RESULT([$with_arm_host])

# AVR toolchain-specific command-line options
AC_MSG_CHECKING([if AVR targets are enabled])
AC_ARG_ENABLE([avr-targets],
 [AS_HELP_STRING([--enable-avr-targets],
  [Build AVR targets @<:@yes when possible@:>@])])
AS_CASE(["z$enable_avr_targets"],
 [zno | zyes],,[enable_avr_targets=unspecified])
AC_MSG_RESULT([$enable_avr_targets])

#gEDA tools-specific command-line options
AC_MSG_CHECKING([whether to use pcb])
AC_ARG_WITH([pcb],
 [AS_HELP_STRING([--without-pcb],[Do not invoke pcb])]
)
AS_CASE(["z$with_pcb"],[zno | zyes],,[with_pcb=unspecified])
AC_MSG_RESULT([$with_pcb])

AC_MSG_CHECKING([whether to use gschem])
AC_ARG_WITH([gschem],
 [AS_HELP_STRING([--without-gschem],[Do not invoke gschem])])
AS_CASE(["z$with_gschem"],[zno | zyes],,[with_gschem=unspecified])
AC_MSG_RESULT([$with_gschem])

AC_MSG_CHECKING([whether to use ps2pdf])
AC_ARG_WITH([ps2pdf],
 [AS_HELP_STRING([--without-ps2pdf],[Do not invoke ps2pdf])])
AS_CASE(["z$with_ps2pdf"],[zno | zyes],,[with_ps2pdf=unspecified])
AC_MSG_RESULT([$with_ps2pdf])

AC_MSG_CHECKING([for schematics output resolution])
AC_ARG_ENABLE([schematics-resolution],
 [AS_HELP_STRING([--enable-schematics-resolution],
  [schematics output resolution (actual only if the output is rebuilt)
 @<:@3200x2400@:>@])],,
  [enable_schematics_resolution=3200x2400
])
AC_MSG_RESULT([$enable_schematics_resolution])

# Checks for programs.

# general OS programs
AC_PROG_MKDIR_P
AC_PROG_LN_S

# ARM toolchain-specific programs
AC_CHECK_PROG([arm_gcc_present],[$with_arm_host-gcc],[yes],[no])
AS_CASE([$arm_gcc_present],
 [no],[
  AS_CASE([$enable_arm_targets],
   [yes],[
    AC_MSG_ERROR([

 ARM targets are requested, but no toolchain is found])])
  AS_CASE([$arm_host_specified],
   [no],[enable_arm_targets=no],
   [yes],[
    AC_MSG_ERROR([

 ARM toolchain affix is specified, but no toolchain is found
])])dnl AS_CASE([$arm_host_specified],
  ],dnl  [no],[
 [yes],[
  AS_CASE([$enable_arm_targets],[no],,[enable_arm_targets=yes])
])dnl AS_CASE([$arm_gcc_present],
AM_CONDITIONAL([enable_arm_targets],[test $enable_arm_targets = yes])
AS_CASE([$enable_arm_targets],[no],[distribution_impossible=yes])

# AVR toolchain-specific programs
AC_CHECK_PROG([avr_gcc_present],[avr-gcc],[yes],[no])
AS_CASE([$avr_gcc_present],
 [no],[
  AS_CASE([$enable_avr_targets],
   [yes],[
    AC_MSG_ERROR([

 AVR targets are requested, but no toolchain is found])
])dnl AS_CASE([$enable_avr_targets],
],
 [yes],
  [AS_CASE([$enable_avr_targets],[no],,[enable_avr_targets=yes])]
)dnl AS_CASE([$avr_gcc_present],
AM_CONDITIONAL([enable_avr_targets], [test $enable_avr_targets = yes])
AS_CASE([$enable_avr_targets],[no],[distribution_impossible=yes])

#gEDA-specific programs
#TODO: check for pcb, gschem and ps2pdf capabilities
AC_CHECK_PROGS([PCB], [pcb], [no])
AS_CASE([$PCB],
 [no],[we_have_pcb=no
  AS_CASE([$with_pcb],
   [yes],[
    AC_MSG_ERROR([
 
  pcb invocation is requested, but no pcb is found])
  ])],dnl AS_CASE(["$with_pcb"],
 [we_have_pcb=yes]
)dnl AS_CASE([$PCB],
AS_CASE([$with_pcb],[no],[use_pcb=no],[use_pcb=$we_have_pcb])
AM_CONDITIONAL([use_pcb],[test $use_pcb = yes])

AC_CHECK_PROGS([PS2PDF], [ps2pdf], [no])
AS_CASE([$PS2PDF],
 [no],[we_have_ps2pdf=no
  AS_CASE([$with_ps2pdf],
   [yes],[
    AC_MSG_ERROR([
 
  ps2pdf invocation is requested, but no ps2pdf is found
])
])],dnl AS_CASE([$with_ps2pdf],
  [we_have_ps2pdf=yes]
)dnl AS_CASE([$PS2PDF],

AS_CASE([$with_ps2pdf],
 [no],[use_ps2pdf=no],[use_ps2pdf=$we_have_ps2pdf])
AM_CONDITIONAL([use_ps2pdf],[test $use_ps2pdf = yes])

AC_CHECK_PROGS([GSCHEM], [gschem], [no])
AS_CASE([$GSCHEM],
 [no],[we_have_gschem=no
  AS_CASE([$with_gschem],
   [yes],[
    AC_MSG_ERROR([
 
  gschem invocation is requested, but no gschem is found
])])dnl AS_CASE([$with_gschem],
],[we_have_gschem=yes]
)dnl AS_CASE([$GSCHEM],
AS_CASE([$with_gschem],
 [no],[use_gschem=no],[use_gschem=$we_have_gschem])
AM_CONDITIONAL([use_gschem],[test $use_gschem = yes])

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
AS_CASE([$enable_doc],[yes],[AC_CONFIG_SUBDIRS([doc])])

AS_CASE([$enable_arm_targets],[yes],[AC_CONFIG_SUBDIRS([sw/target])])
AS_CASE([$enable_avr_targets],[yes],[AC_CONFIG_SUBDIRS([sw/auxilia])])

AC_OUTPUT
#summary output
enabled_subprojects=hosttools
AS_CASE([$enable_doc],[yes],
 [enabled_subprojects="$enabled_subprojects doc"])
AS_CASE([$enable_arm_targets],[yes],
 [enabled_subprojects="$enabled_subprojects target"])
AS_CASE([$enable_avr_targets],[yes],
 [enabled_subprojects="$enabled_subprojects auxilia"])
AS_CASE([$distribution_impossible],
 [yes],[
  echo "NOTE: some subprojects have been disabled -" >>warnings
  echo "      dist* targets shall fail" >>warnings
])
AS_CASE([$use_pcb],
 [no],[ 
  AS_CASE([$we_have_pcb],[no],
   [echo "NOTE: no suitable pcb program -" >>warnings;],
   [echo "NOTE: pcb program will not be used -" >>warnings;]
  )
  echo   "      make will not update PCB images" >>warnings
])
AS_CASE([$use_ps2pdf],
 [no],[
  AS_CASE([$we_have_ps2pdf],
   [no],[
    echo "NOTE: no suitable ps2pdf program -" >>warnings
	],[
    echo "NOTE: ps2pdf will not be used -" >>warnings
	])
  echo   "      make will not update PCB PDFs" >>warnings
])
AS_CASE([$use_gschem],
 [no],[
  AS_CASE([$we_have_gschem],
   [no],[
    echo "NOTE: no suitable gschem program -" >>warnings
   ],[
    echo "NOTE: gschem will not be used -" >>warnings
   ])
  echo   "      make will not update schematics PNGs" >>warnings
])

echo "***Configuration summary for ${PACKAGE} ${VERSION}:" >summary
echo "prefix:               ${prefix}">>summary
echo "enabled subprojects:  ${enabled_subprojects}">>summary
cat warnings >>summary
rm -f warnings

echo;cat summary
echo;cat sw/host/summary|grep -v "^prefix:"
AS_CASE([$enable_arm_targets],
 [yes],[echo; cat sw/target/summary|grep -v "^prefix:"])
AS_CASE([$enable_avr_targets],
 [yes],[echo; cat sw/auxilia/summary|grep -v "^prefix:"])
