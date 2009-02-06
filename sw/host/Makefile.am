#stribog host tools: Makefile.am
#Copyright (C) 2008, 2009\
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
 elk_serial_source=elk.src/wser.c
 conloq_serial_source=conloq.src/wser.c
else
#using POSIX RS-232 UART API by default
 elk_serial_source=elk.src/serialia.c
 conloq_serial_source=conloq.src/serialia.c
endif
conloq_extra_serial=conloq.src/serialia.c conloq.src/wser.c
AM_CPPFLAGS=-DPACKAGE_DATA_DIR="\"$(datadir)\""\
 -DSOURCE_DIR="\"$(srcdir)\""
bin_PROGRAMS=elk\
 caed conloq elig magex-conloq magexp odo parse_tsipex\
 50hz drift fdif lpfilter stat
noinst_LIBRARIES=libstribog.a
dist_bin_SCRIPTS=conloq.src/scripts/expon utils/cutdrift
noinst_PROGRAMS=expon.legacy save_wdex signalex
EXTRA_DIST=tests/serial.c tests/term.c
if build_own_argp
noinst_LIBRARIES+=libargp.a
noinst_PROGRAMS+=argpex
endif
libargp_a_SOURCES=lib/argp/argp.c
argpex_SOURCES=lib/argp/argpex.c
argpex_LDADD=libargp.a
caed_SOURCES=conloq.src/caed.c conloq.src/get_u.h\
 conloq.src/parse_tsip.c conloq.src/parse_tsip.h
caed_LDADD=$(argp_lib) libstribog.a
conloq_SOURCES=conloq.src/conloq.c\
 conloq.src/exp-brief.c conloq.src/exp.h\
 conloq.src/exp_gps.h conloq.src/get_u.h\
 conloq.src/process_keypress.c conloq.src/process_keypress.h\
 conloq.src/garmin_nmea.c conloq.src/hodo.c conloq.src/hodo.h\
 conloq.src/lla.c conloq.src/lla.h\
 conloq.src/parse_tsip.c conloq.src/parse_tsip.h\
 conloq.src/preproc_gps.c conloq.src/preproc_gps.h\
 $(conloq_serial_source) conloq.src/serialia.h conloq.src/usage.h\
 conloq.src/verbosity_level.c conloq.src/verbosity_level.h
EXTRA_conloq_SOURCES=$(conloq_extra_serial)
conloq_LDADD=$(argp_lib) libstribog.a
elig_SOURCES=conloq.src/elig.c\
 conloq.src/parse_tsip.c conloq.src/parse_tsip.h
elig_LDADD=$(argp_lib) libstribog.a
expon_legacy_SOURCES=conloq.src/expon.c\
 conloq.src/exp.c conloq.src/exp.h\
 conloq.src/garmin_nmea.c conloq.src/exp_gps.h\
 conloq.src/hodo.c conloq.src/hodo.h\
 conloq.src/lla.c conloq.src/lla.h\
 conloq.src/parse_tsip.c conloq.src/parse_tsip.h\
 conloq.src/preproc_gps.c conloq.src/preproc_gps.h\
 conloq.src/verbosity_level.c conloq.src/verbosity_level.h
expon_legacy_LDADD=libstribog.a
magex_conloq_SOURCES=conloq.src/magex-conloq.c\
 conloq.src/magexp.c conloq.src/exp.h\
 $(conloq_serial_source) conloq.src/serialia.h\
 conloq.src/parse_tsip.c conloq.src/parse_tsip.h\
 conloq.src/verbosity_level.c conloq.src/verbosity_level.h
magex_conloq_LDADD=$(argp_lib) libstribog.a
EXTRA_magex_conloq_SOURCES=$(conloq_extra_serial)
magexp_SOURCES=conloq.src/expon.c\
 conloq.src/parse_tsip.c conloq.src/parse_tsip.h\
 conloq.src/magexp.c conloq.src/exp.h\
 conloq.src/verbosity_level.c conloq.src/verbosity_level.h
magexp_LDADD=libstribog.a
odo_SOURCES=conloq.src/odo.c conloq.src/verbosity_level.c\
 $(conloq_serial_source) conloq.src/serialia.h
EXTRA_odo_SOURCES=$(conloq_extra_serial)
parse_tsipex_SOURCES=conloq.src/parse_tsipex.c\
 conloq.src/get_u.h conloq.src/parse_tsip.c conloq.src/parse_tsip.h 
parse_tsipex_LDADD=libstribog.a
##elk_CPPFLAGS is needed to make Automake distinguish
##names of the serial object module for elk and conloq; 
##otherwise the names will conflict
elk_CPPFLAGS=$(AM_CPPFLAGS) -DBUILDING_ELK=1
elk_SOURCES=elk.src/elk.c elk.src/serial.c $(elk_serial_source)\
 elk.src/serialia.h elk.src/ram_loader.c elk.src/ram_loader.h\
 elk.src/lpc_loader.c elk.src/lpc_loader.h
elk_LDADD=$(argp_lib) libstribog.a
EXTRA_elk_SOURCES=elk.src/serialia.c elk.src/wser.c
libstribog_a_SOURCES=lib/error.c lib/stribog_error.h\
 lib/snprintf_checked.c lib/snprintf_checked.h\
 lib/save_wd.c lib/save_wd.h lib/crc32.c lib/crc32.h\
 lib/stribog_signal.h lib/signal.c
save_wdex_SOURCES=lib/save_wdex.c lib/save_wd.c lib/save_wd.h
signalex_SOURCES=lib/signalex.c lib/signal.c lib/stribog_signal.h
#small utilities
50hz_SOURCES=utils/50hz.c
drift_SOURCES=utils/drift.c
fdif_SOURCES=utils/fdif.c
lpfilter_SOURCES=utils/lpfilter.c
stat_SOURCES=utils/stat.c
nodist_pkgdata_DATA=summary
DISTCLEANFILES=summary
