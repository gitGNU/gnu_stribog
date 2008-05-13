#stribog target: configure.ac 
# run autoreconf and build to regenerate the build system
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
AC_INIT([stribog-target],[0.0-minus],[stribog-bug@nongnu.org])
# force arm-based host without forcing arm-based build
case "z${target_recursion_trigger}" in
 ztriggered) ;;
 *) export target_recursion_trigger=triggered
 config_guessed=$(echo ${0} | sed "s/configure$/config.guess/")
 config_guessed=$(${config_guessed})
 case "z$ARM_TOOLS_PREFIX" in
  z) export ARM_TOOLS_PREFIX=arm-unknown-elf;;
 esac
 case $# in
  0) ${0} --build=${config_guessed} --host=${ARM_TOOLS_PREFIX};;
 #if --build is set it will override the guessed value
  *) ${0} --build=${config_guessed} $@ --host=${ARM_TOOLS_PREFIX};;
 esac
 result=$?
 export target_recursion_trigger=triggered
 exit $result ;;
esac
AC_MSG_RESULT([NB here we force $host_alias host])
rm -f warnings

AM_INIT_AUTOMAKE([-Wall])
AC_PREFIX_DEFAULT([$HOME/stribog-install])

AC_CONFIG_SRCDIR([src/pll.c])
AC_CONFIG_HEADER([config.h])
AC_CONFIG_LINKS([ram_loader_enums.h:../common/ram_loader_enums.h])

saved_ASFLAGS="$ASFLAGS"
saved_CFLAGS="$CFLAGS"
saved_LDFLAGS="$LDFLAGS"

#Checks for features required via command-line arguments
AC_ARG_WITH([mainboard-mcu],
[AS_HELP_STRING([--with-mainboard-mcu],
 [Configure MCU on the main board 
 (LPC2131 | LPC2132 | LPC2134 | LPC2136 | LPC2138) [LPC2138]])],,
 [with_mainboard_mcu=LPC2138
])
case $with_mainboard_mcu in
 LPC213[[12468]]) ;;
 *) AC_MSG_ERROR([unknown MCU '$with_mainboard_mcu' is requested]) ;;
esac
AC_SUBST([mcu_conf],[$with_mainboard_mcu])
enable_mag_response=yes
enable_magex=yes
enable_multa=yes
adc1_present=yes
case $with_mainboard_mcu in
 LPC2131)
  echo NOTE: LPC2131 has only 8k RAM >> warnings
  enable_multa=no
  ;;
esac
case $with_mainboard_mcu in
 LPC213[[12]])
  echo NOTE: LPC213[[12]] have no ADC1. some parts of programs are disabled\
  >> warnings
  adc1_present=no
  enable_mag_response=no
  enable_magex=no
  enable_multa=no
  ;;
esac
adc1_define=1
case $adc1_present in
 no) adc1_define=0 ;;
esac
AC_DEFINE_UNQUOTED([HAVE_ADC1],$adc1_define,
 [Define to 0 if the MCU has no second ADC])
case $enable_mag_response in
 no)
 echo NOTE: \'mag_response\' program is disabled >>warnings
esac
case $enable_magex in
 no)
 echo NOTE: \'magex\' program is disabled >>warnings
esac
case $enable_multa in
 no)
 echo NOTE: \'multa\' program is disabled >>warnings
esac
AM_CONDITIONAL(mag_response_enabled, test $enable_mag_response = yes)
AM_CONDITIONAL(magex_enabled, test $enable_magex = yes)
AM_CONDITIONAL(multa_enabled, test $enable_multa = yes)

AC_MSG_CHECKING([whether a rule for assembler files is requested])
AC_ARG_ENABLE([assembler-files],
 [AS_HELP_STRING([--enable-assembler-files],
  [Makefile will contain a debugging-purpose rule 
   for assembler files generation 
   (this uses a GNU make extension) [no]])])
case "z$enable_assembler_files" in
 zyes) ;; *) enable_assembler_files=no ;;
esac
AC_MSG_RESULT([$enable_assembler_files])
AM_CONDITIONAL(percent_rules_enabled, test $enable_assembler_files = yes)

AC_MSG_CHECKING([whether original PPS is requested])
AC_ARG_ENABLE([original-pps],
 [AS_HELP_STRING([--enable-original-pps],
  [Input PPS signals through CAP1.1 rather than CAP1.2 [no]])])
current_define=0
case "z$enable_original_pps" in
 zyes) current_define=1 ;;
 *) enable_original_pps=no ;;
esac
AC_MSG_RESULT([$enable_original_pps])
AC_DEFINE_UNQUOTED([HAVE_ORIGINAL_PPS],$current_define,
 [Define to 0 - PPS input is CAP1.1; 1 - CAP1.2])

AC_MSG_CHECKING([whether UARTs should be swapped])
AC_ARG_ENABLE([swap-uarts],
 [AS_HELP_STRING([--enable-swap-uarts],
  [UARTs functions are swapped [no]])])
current_define=0
case "z$enable_swap_uarts" in
 zyes) current_define=1 ;;
 *) enable_swap_uarts=no ;;
esac
AC_MSG_RESULT([$enable_swap_uarts])
AC_DEFINE_UNQUOTED([SWAP_UARTS],$current_define,
 [Define to 0 if UARTs are not swapped])

# Checks for programs.
AC_CHECK_PROG([arm_as_present],[$host_alias-as],[yes],[no])
case $arm_as_present in
 no)
 AC_MSG_ERROR([

 $host_alias-as is not available
 probably no ARM toolchain has been installed
])
 ;;
esac
ARM_MCU_FLAGS=-mcpu=arm7tdmi
ASFLAGS="${saved_ASFLAGS} ${ARM_MCU_FLAGS}"
AC_MSG_CHECKING(
 [if $host_alias-as accepts '${ARM_MCU_FLAGS}' option])
if $host_alias-as -o boot.o ${ASFLAGS} ${srcdir}/src/boot.s 2>/dev/null;then
 arm_elf_as=yes;else arm_elf_as=no;
fi
AC_MSG_RESULT([$arm_elf_as])
case $arm_elf_as in
 no)
 #older gases like 2.11.2 prefer this form of option
 ARM_MCU_FLAGS=-marm7tdmi
 ASFLAGS="${saved_ASFLAGS} ${ARM_MCU_FLAGS}"
 AC_MSG_CHECKING(
  [if $host_alias-as accepts '${ARM_MCU_FLAGS}' option])
 if ! $host_alias-as -o boot.o ${ASFLAGS} ${srcdir}/src/boot.s 2>/dev/null;then
  AC_MSG_RESULT([no])
  AC_MSG_ERROR([

 $host_alias-as can't assemble startup program.
 probably the ARM binutils installed are too old
 (binutils-2.11.2 to 2.18 should work)
])
 fi
 AC_MSG_RESULT([yes])
 ;;
esac
#on OpenBSD arm-unknown-elf-objcopy once installed itself as mere objcopy
AC_CHECK_PROGS([ARM_OBJCOPY],[$host_alias-objcopy objcopy],[no])
case ${ARM_OBJCOPY} in
 no)
  AC_MSG_ERROR([[

 objcopy tool is not available
 probably no ARM toolchain has been installed
]])
 ;;
esac
AC_MSG_CHECKING([whether ${ARM_OBJCOPY} accepts '-I elf32-littlearm'])
if ! ${ARM_OBJCOPY} -I elf32-littlearm -O binary -R startup\
 boot.o /dev/null 2>/dev/null;then
  AC_MSG_RESULT([no])
  AC_MSG_ERROR([

 ${ARM_OBJCOPY} can't manage elf32-littlearm object files.
 Probably no ARM toolchain has been installed properly.
 If you think it has been, try to place path to the toolchain
 before path to the system objcopy in your PATH variable
])
fi
AC_MSG_RESULT([yes])
AC_SUBST([arm_unknown_elf_objcopy],[${ARM_OBJCOPY}])

#make our minimalistic crosstools generate executables
${srcdir}/subst_ldscript ROM $with_mainboard_mcu\
 < ${srcdir}/src/2138.ld.in > 2138.ld
CFLAGS="${saved_CFLAGS} -Wa,${ARM_MCU_FLAGS}"
AC_SUBST([arm_as_flags],[${ARM_MCU_FLAGS}])
AC_SUBST([arm_ascc_flags],[-Wa,${ARM_MCU_FLAGS}])
BASIC_LDFLAGS="${LDFLAGS} -nostdlib -static -T./2138.ld boot.o"
#libgcc of gcc-2.95.3 needs atexit, 
#which can safely be stubbed in our programs
#TODO: make the programs built with gcc-2.95.3 work
ROBUST_LDFLAGS="${BASIC_LDFLAGS} ${srcdir}/lib/atexit.c"
LIBS=-lgcc
LDFLAGS=${ROBUST_LDFLAGS}

AC_PROG_CC
AM_PROG_AS

# Checks for libraries.

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.
LDFLAGS=${BASIC_LDFLAGS}
AC_MSG_CHECKING([whether we can do without src/lib/atexit.c])
reject_atexit_c=yes
AC_LANG_CONFTEST(
[AC_LANG_PROGRAM([[static int no_camel;]],[[no_camel=!0;]])]
)
if ! ${CC} ${CFLAGS} ${LDFLAGS} ${LIBS} conftest.c \
-o /dev/null 2>/dev/null;then
 LDFLAGS=${ROBUST_LDFLAGS}
 reject_atexit_c=no
fi
AC_MSG_RESULT([$reject_atexit_c])
AM_CONDITIONAL(atexit_needed, test $reject_atexit_c = no)

 AC_C_CONST
 AC_C_INLINE
 AC_C_VOLATILE
#remove temporary object file so it will be remade with user-defined FLAGS
rm boot.o
#return to user-defined values
ASFLAGS="$saved_CFLAGS"
CFLAGS="$saved_CFLAGS"
LDFLAGS="$saved_LDFLAGS"
AC_CONFIG_FILES([Makefile])
AC_OUTPUT
echo "Configuration summary for ${PACKAGE} ${VERSION}:" >summary
echo "prefix:               ${prefix}">>summary
echo "crosstools affix:     ${host_alias}">>summary
echo "MCU:                  $with_mainboard_mcu">>summary
echo "CFLAGS:               ${CFLAGS}">>summary
echo "LDFLAGS:              ${LDFLAGS}">>summary
echo "LIBS:                 ${LIBS}">>summary
echo "detected tools versions:">>summary
$host_alias-as --version |grep assembler >>summary
${ARM_OBJCOPY} --version |grep objcopy >>summary
${CC} --version |grep ${CC} >>summary
cat warnings >>summary 2>/dev/null
rm -f warnings

case "z$recursive_stribog_build" in
 zyes) ;; *) cat summary;;
esac
