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
AC_INIT([stribog-hosttools], [0.0-minus], [stribog-bug@nongnu.org])
AC_CANONICAL_HOST
AM_INIT_AUTOMAKE([-Wall])
AC_PREFIX_DEFAULT([$HOME/stribog-install])

AC_CONFIG_SRCDIR([utils/lpfilter.c])
AC_CONFIG_HEADER([config.h])
#Checks for features required via command-line arguments
AC_ARG_WITH([elk-port],
[AS_HELP_STRING([--with-elk-port],
 [Set default port for elk program [/dev/ttyS0]])],,
 [with_elk_port=/dev/ttyS0
])
AC_ARG_WITH([conloq-port],
[AS_HELP_STRING([--with-conloq-port],
 [Set default port for conloq programs [/dev/ttyS1]])],,
 [with_conloq_port=/dev/ttyS1
])
AC_DEFINE_UNQUOTED([CONLOQ_PORT],["$with_conloq_port"],
 [Default port for conloq programs])
AC_DEFINE_UNQUOTED([ELK_PORT],["$with_elk_port"],
 [Default port for elk])
AC_GNU_SOURCE
# Checks for programs.
AC_PROG_CC
AM_PROG_CC_C_O
AC_PROG_RANLIB

if test "z$GCC" = zyes; then
 CFLAGS="${CFLAGS} -Wall"
fi

# Checks for libraries.
AC_CHECK_LIB([m], [sqrt])

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([errno.h fcntl.h float.h stdint.h stdlib.h])
AC_CHECK_HEADERS([string.h termios.h unistd.h sysexits.h])

#argp library configuration
AC_MSG_CHECKING([if stribog argp implementation is asked for])
AC_ARG_ENABLE([own-argp],
 [AS_HELP_STRING([--enable-own-argp],
  [Use stribog implementation of argp library [no]])],
  [
   case "z$enable_own_argp" in
    zyes | zno) ;;
    *) AC_MSG_ERROR([--enable-own-argp should be either 'yes' or 'no'])
    ;;
   esac
],
  [enable_own_argp=unspecified
])
#$enable_own_argp is (yes | no | unspecified)
AC_MSG_RESULT([$enable_own_argp])
AC_CHECK_HEADER([argp.h],,
[AC_MSG_RESULT([no usable argp.h found; stribog version should be used])
 case $enable_own_argp in
  no)
   AC_MSG_ERROR([own argp disabled and no usable system argp available])
  ;;
 esac
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
AC_CHECK_FUNCS([get_current_dir_name getcwd])

#Checks for system services
#FIXME test headers and functions instead?
AC_CHECK_HEADERS([windows.h],
[
the_host_is_windows=yes
],[
the_host_is_windows=no
])
case $enable_own_argp in
 yes)
 AC_CONFIG_LINKS([argp.h:lib/argp/argp.h])
 AC_SUBST(argp_lib,[libargp.a])
 ;;
esac
AM_CONDITIONAL(the_host_is_windows, test $the_host_is_windows = yes)
AM_CONDITIONAL(build_own_argp, test $enable_own_argp = yes)

#common headers are linked to top build directory
#to be available the same as config.h
AC_CONFIG_LINKS([stribog_error.h:lib/stribog_error.h
                 stribog_strings.h:lib/stribog_strings.h
                 stribog_save_wd.h:lib/save_wd.h
                 form_fix.h:../common/form_fix.h
                 ram_loader_enums.h:../common/ram_loader_enums.h
		 stribog_crc32.h:lib/crc32.h])
#Makefiles are generated
AC_CONFIG_FILES([Makefile
                 postproc/Makefile])
AC_OUTPUT
case $enable_own_argp in
 yes) argp_type="supplied with stribog" ;;
 *) argp_type="built in host OS (typically, GNU)" ;;
esac

echo "Configuration summary for ${PACKAGE} ${VERSION}:" >summary
echo "prefix:               ${prefix}">>summary
echo "host:                 ${host}">>summary
echo "conloq port:          '${with_conloq_port}'">>summary
echo "elk port:             '${with_elk_port}'">>summary
echo "argv parser:          ${argp_type}">>summary
echo "CFLAGS:               ${CFLAGS}">>summary
echo "LDFLAGS:              ${LDFLAGS}">>summary
echo "LIBS:                 ${LIBS}">>summary

case "z$recursive_stribog_build" in
 zyes) ;; *) cat summary ;;
esac
