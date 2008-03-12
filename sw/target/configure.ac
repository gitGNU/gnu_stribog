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
AC_CONFIG_SRCDIR([src/dacex.c])
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
if test "z$build_target_programs" = zyes;then
 AC_CHECK_PROG([arm_elf_tools],[arm-elf-gcc],[yes],[no],,)
 if test "z$arm_elf_tools" != zno;then
  AC_MSG_CHECKING([the arm-elf-gcc version])
  arm_gcc_version=$(arm-elf-gcc --version|head -1|sed "s/^.* //")
dnl        autoconf removes quotes even here: note double [[ ]]
  arm_gcc_version_maior=$(($(echo $arm_gcc_version|sed "s/[[.]].*//")+0))
  AC_MSG_RESULT([$arm_gcc_version])
  if test $arm_gcc_version_maior -lt 3;then
   #we see gcc 2.x or gcc 1.x or gcc 0.x or less which is suspicious
   echo "arm-elf-gcc version '$arm_gcc_version' less than minimal tested (3.4.6)" >warnings
   echo "arm-elf-gcc version_maior '$arm_gcc_version_maior'"
  fi
 else
  AC_MSG_RESULT([no usable ARM crosstools found; the distributed programs will be installed])
  build_target_programs=no
 fi
fi
if test "z$build_target_programs" = zyes;then
#make our minimalistic crosstools generate executables
 export ldscript="${srcdir}/src/2138.ld"
 export ldscript_rom="${srcdir}/src/2138.ld"
 export libgcc="$(arm-elf-gcc -print-libgcc-file-name)"
#FIXME these variables should be completely defined by the user
 ASFLAGS="$ASFLAGS -mcpu=arm7tdmi"
 CFLAGS="$CFLAGS -mcpu=arm7tdmi -Wall -O2"
 LDFLAGS="$LDFLAGS -nostartup -nostdlib -static -T${ldscript}"
 LIBS="$LIBS ${libgcc}"
fi
AM_CONDITIONAL([build_target_programs], test "z$build_target_programs" = zyes)

#would anybody like to install the distributed target programs 
#on a system with no native compiler available? this script can't do it
AC_PROG_CC

# Checks for libraries.

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.
#actually there is absolutely no need to check this when
#we are just to install the distributed executables,
#but this 'configure' won't work when no tests are run
 AC_C_CONST
if test "z$build_target_programs" = zyes;then
 AC_C_INLINE
 AC_C_VOLATILE
fi

AC_CONFIG_FILES([Makefile])
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
