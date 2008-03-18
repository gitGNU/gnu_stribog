#stribog target: configure.ac 
# run ./regen_configure regenerate the build system
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
#the cross-build is forced in configure.pre which is
#written at the begin of 'configure'
AC_MSG_RESULT([NB here we force arm-elf host])

AM_INIT_AUTOMAKE([-Wall])
AC_CONFIG_SRCDIR([src/pll.c])
AC_CONFIG_HEADER([config.h])

# Checks for programs.
saved_ASFLAGS="$ASFLAGS"
saved_CFLAGS="$CFLAGS"
saved_LDFLAGS="$LDFLAGS"
AC_ARG_WITH([mainboard-mcu],
AS_HELP_STRING([--with-mainboard-mcu],
[Configure MCU on the main board (LPC2131 | LPC2132 | LPC2134
 | LPC2136 | LPC2138) [[LPC2138]]]),,
[with_mainboard_mcu=LPC2138
]
)
case $with_mainboard_mcu in
 LPC2131) 
  ram_length=8k
  rom_length=32k
  ;;
 LPC2132)
  ram_length=16k
  rom_length=64k
  ;;
 LPC2134)
  ram_length=16k
  rom_length=128k
  ;;
 LPC2136)
  ram_length=32k
  rom_length=256k
  ;;
 LPC2138)
  ram_length=32k
  rom_length=512k
  ;;
 *)
  AC_MSG_RESULT([unknown MCU '$with_target_mcu' configured])
  exit 1
esac
ROM_ram_origin=0x40000000
ROM_ram_length=$ram_length;
#0x200 is low memory used by the bootstrap loader
#-32-256 is high memory used by the bootstrap loader
#-8  are two words more to be sure
RAM_ram_origin=$ROM_ram_origin+0x200
RAM_ram_length=$ram_length-0x200-32-256-8;

sed "s/\<ORIGIN_ram_\>/$RAM_ram_origin/g" < ${srcdir}/src/ram2138.ld.in | \
sed "s/\<LENGTH_ram_\>/$RAM_ram_length/g" | \
sed "s/\<LENGTH_rom_\>/$rom_length/g" | \
sed "s/\<comment_on_the_cpu\>/the MCU is $with_mainboard_mcu/g" > ram2138.ld

sed "s/\<ORIGIN_ram_\>/$ROM_ram_origin/g" < ${srcdir}/src/2138.ld.in | \
sed "s/\<LENGTH_ram_\>/$ROM_ram_length/g" | \
sed "s/\<LENGTH_rom_\>/$rom_length/g" | \
sed "s/\<comment_on_the_cpu\>/the MCU is $with_mainboard_mcu/g" > 2138.ld

#make our minimalistic crosstools generate executables
 ldscript="./2138.ld"
 ASFLAGS="$ASFLAGS -mcpu=arm7tdmi"
 CFLAGS="$CFLAGS -mcpu=arm7tdmi"
 LDFLAGS="$LDFLAGS -nostdlib -static -T${ldscript}"
 LIBS=-lgcc
  #libgcc of gcc-2.95.3 needs atexit, 
  #which can safely be stubbed in our programs
  #TODO: check if the programs built with gcc-2.95.3 really work
  arm-elf-gcc -c -o atexit.o ${CFLAGS} "${srcdir}/lib/atexit.c"
  #arm-elf-as-2.10 does not assemble boot.s 
AC_MSG_CHECKING([if arm-elf-as can assemble boot.s])
if arm-elf-as -o boot.o ${ASFLAGS} "${srcdir}/src/boot.s" ;then
 arm_elf_as=yes;
else
 arm_elf_as=no;
fi
AC_MSG_RESULT([$arm_elf_as])
if test $arm_elf_as = no;then
 AC_MSG_RESULT([

 arm-elf-as can't assemble startup program.
 probably no arm-elf-as present or binutils are too old
 (binutils-2.16 to 2.18 are known to work; 2.10 does not)
])
 exit 1; 
fi
  LDFLAGS="$LDFLAGS atexit.o boot.o"
AC_PROG_CC
AM_PROG_AS

# Checks for libraries.

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.
 AC_C_CONST
 AC_C_INLINE
 AC_C_VOLATILE

#return to user-defined values
ASFLAGS="$saved_CFLAGS"
CFLAGS="$saved_CFLAGS"
LDFLAGS="$saved_LDFLAGS"
#remove temporarily generated files
#so user will rebuild them with user-defined FLAGS
rm -f atexit.o boot.o
AC_CONFIG_FILES([Makefile])
AC_OUTPUT
echo "Configuration summary for ${PACKAGE} ${VERSION}:" >summary
echo >>summary
echo "prefix:               ${prefix}">>summary
echo "whether to build:     ${build_target_programs}">>summary
echo "CFLAGS:               ${CFLAGS}">>summary
echo "LDFLAGS:              ${LDFLAGS}">>summary
echo "LIBS:                 ${LIBS}">>summary
echo "MCU:                  $with_mainboard_mcu">>summary
echo "tools versions:">>summary
arm-elf-as --version>>summary
${CC} --version>>summary

if test "z$recursive_stribog_build" != zyes;then
 AC_MSG_RESULT([[$(cat summary)]])
fi
