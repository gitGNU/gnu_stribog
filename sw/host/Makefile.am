#stribog host tools: Makefile.am
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
SUBDIRS=postproc
if the_host_is_windows
#forced to use non-free OS API
 elk_serial_source=elk/wser.c
 conloq_serial_source=conloq/wser.c
else
#using POSIX RS-232 UART API by default
 elk_serial_source=elk/serialia.c
 conloq_serial_source=conloq/serialia.c
endif
AM_CPPFLAGS=-DPACKAGE_DATA_DIR="\"$(datadir)\""\
 -DSOURCE_DIR="\"$(srcdir)\""
bin_PROGRAMS=elk\
 caed conloq elig magex-conloq magexp odo parse_tsipex\
 50hz drift fdif lpfilter stat
noinst_LIBRARIES=libstribog.a
dist_bin_SCRIPTS=conloq/expon utils/cutdrift
noinst_PROGRAMS=expon.legacy save_wdex
EXTRA_DIST=tests/serial.c tests/term.c
if build_own_argp
noinst_LIBRARIES+=libargp.a
noinst_PROGRAMS+=argpex
endif
libargp_a_SOURCES=lib/argp/argp.c
argpex_SOURCES=lib/argp/argpex.c
argpex_LDADD=libargp.a
caed_SOURCES=conloq/caed.c conloq/get_u.h\
 conloq/parse_tsip.c conloq/parse_tsip.h
caed_LDADD=$(argp_lib) libstribog.a
conloq_SOURCES=conloq/conloq.c\
 conloq/exp-brief.c conloq/exp.h\
 conloq/exp_gps.h conloq/get_u.h\
 conloq/process_keypress.c conloq/process_keypress.h\
 conloq/garmin_nmea.c conloq/hodo.c conloq/hodo.h\
 conloq/lla.c conloq/lla.h\
 conloq/parse_tsip.c conloq/parse_tsip.h\
 conloq/preproc_gps.c conloq/preproc_gps.h\
 $(conloq_serial_source) conloq/serialia.h conloq/usage.h\
 conloq/verbosity_level.c conloq/verbosity_level.h
EXTRA_conloq_SOURCES=conloq/serialia.c conloq/wser.c
conloq_LDADD=$(argp_lib) libstribog.a
elig_SOURCES=conloq/elig.c conloq/parse_tsip.c conloq/parse_tsip.h
elig_LDADD=$(argp_lib) libstribog.a
expon_legacy_SOURCES=conloq/expon.c\
 conloq/exp.c conloq/exp.h\
 conloq/garmin_nmea.c conloq/exp_gps.h\
 conloq/hodo.c conloq/hodo.h conloq/lla.c conloq/lla.h\
 conloq/parse_tsip.c conloq/parse_tsip.h\
 conloq/preproc_gps.c conloq/preproc_gps.h\
 conloq/verbosity_level.c conloq/verbosity_level.h
expon_legacy_LDADD=libstribog.a
magex_conloq_SOURCES=conloq/magex-conloq.c\
 conloq/magexp.c conloq/exp.h\
 $(conloq_serial_source) conloq/serialia.h\
 conloq/parse_tsip.c conloq/parse_tsip.h\
 conloq/verbosity_level.c conloq/verbosity_level.h
magex_conloq_LDADD=$(argp_lib) libstribog.a
EXTRA_magex_conloq_SOURCES=conloq/serialia.c conloq/wser.c
magexp_SOURCES=conloq/expon.c\
 conloq/parse_tsip.c conloq/parse_tsip.h\
 conloq/magexp.c conloq/exp.h\
 conloq/verbosity_level.c conloq/verbosity_level.h
magexp_LDADD=libstribog.a
odo_SOURCES=conloq/odo.c conloq/verbosity_level.c\
 $(conloq_serial_source) conloq/serialia.h
EXTRA_odo_SOURCES=conloq/serialia.c conloq/wser.c
parse_tsipex_SOURCES=conloq/parse_tsipex.c\
 conloq/get_u.h conloq/parse_tsip.c conloq/parse_tsip.h 
parse_tsipex_LDADD=libstribog.a
##elk_CPPFLAGS is needed to make Automake distinguish
##names of the serial object module for elk and conloq; 
##otherwise the names will conflict
elk_CPPFLAGS=$(AM_CPPFLAGS) -DBUILDING_ELK=1
elk_SOURCES=elk/elk.c $(elk_serial_source)\
 elk/serialia.h elk/usage.h
elk_LDADD=$(argp_lib) libstribog.a
EXTRA_elk_SOURCES=elk/serialia.c elk/wser.c
libstribog_a_SOURCES=lib/error.c lib/stribog_error.h\
 lib/save_wd.c lib/save_wd.h lib/crc32.c lib/crc32.h
save_wdex_SOURCES=lib/save_wdex.c lib/save_wd.c lib/save_wd.h
#small utilities
50hz_SOURCES=utils/50hz.c
drift_SOURCES=utils/drift.c
fdif_SOURCES=utils/fdif.c
lpfilter_SOURCES=utils/lpfilter.c
stat_SOURCES=utils/stat.c
nodist_pkgdata_DATA=summary
dist-hook:
	$(RM) $(nodist_pkgdata_DATA)
