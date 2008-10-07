#stribog host tools: configure.ac 
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
AC_INIT([stribog-hosttools], [0.0.0-rc1-minus], [stribog-bug@nongnu.org])
AC_CANONICAL_HOST
AM_INIT_AUTOMAKE([-Wall])
AC_PREFIX_DEFAULT([$HOME/stribog-install])

AC_CONFIG_SRCDIR([utils/lpfilter.c])

AH_TOP(
[/* Copyright (C) 2008 Ineiev<ineiev@users.sourceforge.net>, super V 93
 This file is an object-code part of stribog: it is produced
 automatically with autoheader when invoking autoreconf
 stribog is free design; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 3 of the License, or
 (at your option) any later version.*/
])

AC_CONFIG_HEADER([config.h])
#Checks for features required via command-line arguments
AC_MSG_CHECKING([default port for board loading (elk-port)])
AC_ARG_WITH([elk-port],
[AS_HELP_STRING([--with-elk-port],
 [Set default port for elk program [/dev/ttyS0]])],,
 [with_elk_port=/dev/ttyS0
])
AC_MSG_RESULT([$with_elk_port])
AC_DEFINE_UNQUOTED([ELK_PORT],
 ["$with_elk_port"],[Default port for board uploading (elk)])
AC_MSG_CHECKING([default port for board communication (conloq-port)])
AC_ARG_WITH([conloq-port],
[AS_HELP_STRING([--with-conloq-port],
 [Set default port for conloq programs [/dev/ttyS1]])],,
 [with_conloq_port=/dev/ttyS1
])
AC_MSG_RESULT([$with_conloq_port])
AC_DEFINE_UNQUOTED([CONLOQ_PORT],
 ["$with_conloq_port"],[Default port for board communication])
#argp library configuration
AC_MSG_CHECKING([if stribog argp implementation is asked for])
AC_ARG_ENABLE([own-argp],
 [AS_HELP_STRING([--enable-own-argp],
  [Use stribog implementation of argp library @<:@no when possible@:>@])
 ]
)
AS_CASE(["z$enable_own_argp"],[zyes | zno],,
 [enable_own_argp=unspecified]
)
AC_MSG_RESULT([$enable_own_argp])

AC_GNU_SOURCE
# Checks for programs.
AC_PROG_CC
AM_PROG_CC_C_O
AC_PROG_RANLIB

AS_CASE(["z$GCC"],[zyes],[CFLAGS="${CFLAGS} -Wall"])

# Checks for libraries.
AC_CHECK_LIB([m], [sqrt])

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([errno.h fcntl.h float.h stdint.h stdlib.h])
AC_CHECK_HEADERS([string.h termios.h unistd.h sysexits.h])

AC_CHECK_HEADER([argp.h],,
[AC_MSG_RESULT([no usable argp.h found; stribog version should be used])
 AS_CASE([$enable_own_argp],
  [no],[
   AC_MSG_ERROR([own argp disabled and no usable system argp available])]
 )
 enable_own_argp=yes
])
# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_TYPES([error_t],,,
[AC_INCLUDES_DEFAULT()
[@%:@ifdef HAVE_ERRNO_H
@%:@ include<errno.h>
@%:@endif
]] 
)
AC_C_CONST
AC_C_INLINE
AC_TYPE_UINT16_T

# Checks for library functions.
#FIXME configure the sources accordingly
AC_FUNC_ERROR_AT_LINE
AC_FUNC_MALLOC
AC_FUNC_MEMCMP
AC_TYPE_SIGNAL
AC_FUNC_VPRINTF
AC_CHECK_FUNCS([atexit memmove sqrt strchr strerror fchdir])
AC_CHECK_FUNCS([get_current_dir_name getcwd sigaction])

#Checks for system services
AC_CHECK_HEADERS([windows.h],
[
the_host_is_windows=yes
],[
the_host_is_windows=no
])
AS_CASE([$enable_own_argp],
 [yes],[
 AC_CONFIG_LINKS([argp.h:lib/argp/argp.h])
 AC_SUBST(argp_lib,[libargp.a])
])
AM_CONDITIONAL([the_host_is_windows],[test $the_host_is_windows = yes])
AM_CONDITIONAL([build_own_argp],[test $enable_own_argp = yes])

#common headers are linked to top build directory
#to be available the same as config.h
AC_CONFIG_LINKS([stribog_error.h:lib/stribog_error.h
                 snprintf_checked.h:lib/snprintf_checked.h
                 stribog_strings.h:lib/stribog_strings.h
                 stribog_save_wd.h:lib/save_wd.h
                 stribog_signal.h:lib/stribog_signal.h
                 form_fix.h:../common/form_fix.h
                 ram_loader_enums.h:../common/ram_loader_enums.h
                 stribog_crc32.h:lib/crc32.h])
#Makefiles are generated
AC_CONFIG_FILES([Makefile
                 postproc/Makefile])
AC_OUTPUT
AS_CASE([$enable_own_argp],
 [yes],[argp_type="supplied with stribog"],
 [argp_type="built in host OS (typically, GNU)"])

echo "Configuration summary for ${PACKAGE} ${VERSION}:" >summary
echo "prefix:               ${prefix}">>summary
echo "host:                 ${host}">>summary
echo "conloq port:          '${with_conloq_port}'">>summary
echo "elk port:             '${with_elk_port}'">>summary
echo "argv parser:          ${argp_type}">>summary
echo "CFLAGS:               ${CFLAGS}">>summary
echo "LDFLAGS:              ${LDFLAGS}">>summary
echo "LIBS:                 ${LIBS}">>summary

AS_CASE(["z$recursive_stribog_build"],[zyes],,[cat summary])
