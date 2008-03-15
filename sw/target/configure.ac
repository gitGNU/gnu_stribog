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
#make our minimalistic crosstools generate executables
 ldscript="${srcdir}/src/ram2138.ld"
 export libgcc="$(arm-elf-gcc -print-libgcc-file-name)"
 ASFLAGS="$ASFLAGS -mcpu=arm7tdmi"
 CFLAGS="$CFLAGS -mcpu=arm7tdmi"
 LDFLAGS="$LDFLAGS -nostdlib -static -T${ldscript}"
 LIBS="${libgcc}"
  #libgcc of gcc-2.95.3 needs atexit, 
  #which can safely be stubbed in our programs
  #TODO: check if the programs built with gcc-2.95.3 really work
  arm-elf-gcc -c -o atexit.o ${CFLAGS} "${srcdir}/lib/atexit.c"
  arm-elf-as -o boot.o ${ASFLAGS} "${srcdir}/src/boot.s"
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
echo "tools versions:">>summary
${AS} --version>>summary
${CC} --version>>summary

if test "z$recursive_stribog_build" != zyes;then
 AC_MSG_RESULT([[$(cat summary)]])
fi
