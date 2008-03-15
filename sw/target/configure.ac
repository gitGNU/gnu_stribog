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
AC_MSG_RESULT([NB here we force cross-build])

#'warnings' is the file where some notanda will be written
echo > warnings

AM_INIT_AUTOMAKE([-Wall])
AC_CONFIG_SRCDIR([src/pll.c])
AC_CONFIG_HEADER([config.h])

# Checks for programs.
if test "z$recursive_stribog_build" != zyes;then
 AC_MSG_CHECKING([if stribog target build is asked for])
 AC_ARG_ENABLE([target-programs],
  AS_HELP_STRING([--enable-target-programs],
   [Rebuild software [[yes]]]),,
 )
 if test "z$enable_target_programs" != zno;then
  enable_target_programs=yes
 fi
 AC_MSG_RESULT([$enable_target_programs])
 build_target_programs=$enable_target_programs
fi
AC_CHECK_PROG([arm_elf_tools],[arm-elf-gcc],[yes],[no],,)
if test "z$arm_elf_tools" = zyes;then
 AC_MSG_CHECKING([the arm-elf-gcc version])
 arm_gcc_version=$(arm-elf-gcc --version|head -1|sed "s/^.* //")
dnl       autoconf removes quotes even here: note double [[ ]]
 arm_gcc_version_maior=$(($(echo $arm_gcc_version|sed "s/[[.]].*//")+0))
 AC_MSG_RESULT([$arm_gcc_version])
 if test $arm_gcc_version_maior -lt 3;then
  if "z$build_target_programs" = z;then
   #we see gcc 2.x or gcc 1.x or gcc 0.x or less which is suspicious
   echo "NOTE: arm-elf-gcc version '$arm_gcc_version' less than minimal tested (3.4.6)" >warnings
   echo "arm-elf-gcc version_maior '$arm_gcc_version_maior'"
  fi
 fi
else
 AC_MSG_RESULT([no usable ARM crosstools found; the distributed programs will be installed])
 build_target_programs=no
fi
saved_ASFLAGS="$ASFLAGS"
saved_CFLAGS="$CFLAGS"
saved_LDFLAGS="$LDFLAGS"
if test "z$arm_elf_tools" = zyes;then
#make our minimalistic crosstools generate executables
 ldscript="${srcdir}/src/ram2138.ld"
 export libgcc="$(arm-elf-gcc -print-libgcc-file-name)"
 ASFLAGS="$ASFLAGS -mcpu=arm7tdmi"
 CFLAGS="$CFLAGS -mcpu=arm7tdmi"
 LDFLAGS="$LDFLAGS -nostdlib -static -T${ldscript}"
 LIBS="${libgcc}"
 if test $arm_gcc_version_maior = 2;then
  #libgcc of gcc-2.95.3 needs atexit, 
  #which can safely be stubbed in embedded programs
  #TODO: check if the programs built with gcc-2.95.3 really work
  arm-elf-gcc -c -o atexit.o ${CFLAGS} "${srcdir}/lib/atexit.c"
  arm-elf-as -o boot.o ${ASFLAGS} "${srcdir}/src/boot.s"
  LDFLAGS="$LDFLAGS atexit.o boot.o"
 fi
fi
AM_CONDITIONAL([add_own_atexit], test "z$arm_gcc_version_maior" = z2)
AM_CONDITIONAL([build_target_programs], test "z$build_target_programs" = zyes)
AM_CONDITIONAL([arm_elf_tools], test "z$arm_elf_tools" = zyes)
if test "z$arm_elf_tools" != zyes;then
#FIXME wouldn't it be better to point to lib/fake-cc
#when there is no ARM assembler?
 AS=as
 CC=lib/fake-cc
 for i in cl egcs cc gcc;do
  echo $PATH |sed "s/:/\n/g"|while read j;do
   if test -x "$j/$i";then echo $i>cc_name;fi
  done
 done
 CC=$(cat cc_name)
 AC_MSG_RESULT([we cowardly return to native CC='$CC'])
fi

#these tools are needed to check dependencies even when
#we are just to install the distributed executables;
#if we have not been provided with native compiler,
#we can't build ../host subproject so the process necessarily fails.
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

#copy distributed arm-elf "executables" to builddir
AS_MKDIR_P(ram_programs)
cp ${srcdir}/ram_programs/* ram_programs
AS_MKDIR_P(rom_programs)
cp ${srcdir}/rom_programs/* rom_programs
#remove temporarily generated files
#so user will rebuild them with user-defined FLAGS
rm -f atexit.o boot.o
AC_CONFIG_FILES([Makefile])
if test "z$arm_elf_tools" != zyes;then
 AC_CONFIG_FILES([mutex.h:lib/mutex.h])
fi
AC_OUTPUT
echo "Configuration summary for ${PACKAGE} ${VERSION}:" >summary
echo >>summary
echo "prefix:               ${prefix}">>summary
echo "whether to build:     ${build_target_programs}">>summary
echo "CFLAGS:               ${CFLAGS}">>summary
echo "LDFLAGS:              ${LDFLAGS}">>summary
echo "LIBS:                 ${LIBS}">>summary
cat warnings >>summary

if test "z$recursive_stribog_build" != zyes;then
 AC_MSG_RESULT([[$(cat summary)]])
fi
