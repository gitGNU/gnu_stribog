#stribog data loggers and parsers: Makefile.am
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
#
#Copyright (C) 2005, 2006, 2007, 2008\
# Ineiev<ineiev@users.sourceforge.net>, super V 93
if the_host_is_windows
#forced to use non-free OS API
 serial_source=wser.c
else
#using POSIX RS-232 UART API by default
 serial_source=serialia.c
endif
AM_CPPFLAGS=-DSOURCE_DIR="\"$(srcdir)\""
bin_PROGRAMS=caed conloq elig magex-conloq magexp parse_tsipex
dist_bin_SCRIPTS=expon
noinst_PROGRAMS=expon.legacy
caed_SOURCES=caed.c crc32.c crc32.h get_u.h\
 parse_tsip.c parse_tsip.h
caed_LDADD=$(argp_lib) $(stribog_lib)
caed_DEPENDENCIES=$(argp_lib) $(stribog_lib)
conloq_SOURCES=conloq.c crc32.c crc32.h\
 exp-brief.c exp.h\
 exp_gps.h get_u.h\
 process_keypress.c process_keypress.h garmin_nmea.c hodo.c hodo.h\
 lla.c lla.h parse_tsip.c parse_tsip.h\
 preproc_gps.c preproc_gps.h\
 $(serial_source) serialia.h usage.h\
 verbosity_level.c verbosity_level.h
EXTRA_conloq_SOURCES=serialia.c wser.c
conloq_LDADD=$(argp_lib) $(stribog_lib)
conloq_DEPENDENCIES=$(argp_lib) $(stribog_lib)
elig_SOURCES=elig.c parse_tsip.c parse_tsip.h
elig_LDADD=$(argp_lib) $(stribog_lib)
elig_DEPENDENCIES=$(argp_lib) $(stribog_lib)
expon_legacy_SOURCES=expon.c crc32.c crc32.h exp.c exp.h\
 garmin_nmea.c exp_gps.h hodo.c hodo.h lla.c lla.h\
 parse_tsip.c parse_tsip.h preproc_gps.c preproc_gps.h\
 verbosity_level.c verbosity_level.h
expon_legacy_LDADD=$(stribog_lib)
expon_legacy_DEPENDENCIES=$(stribog_lib)
magex_conloq_SOURCES=magex-conloq.c $(serial_source) serialia.h\
 parse_tsip.c parse_tsip.h magexp.c exp.h\
 verbosity_level.c verbosity_level.h
magex_conloq_LDADD=$(argp_lib) $(stribog_lib)
magex_conloq_DEPENDENCIES=$(argp_lib) $(stribog_lib)
EXTRA_magex_conloq_SOURCES=serialia.c wser.c
magexp_SOURCES=expon.c\
 parse_tsip.c parse_tsip.h magexp.c exp.h\
 verbosity_level.c verbosity_level.h
magexp_LDADD=$(stribog_lib)
magexp_DEPENDENCIES=$(stribog_lib)
parse_tsipex_SOURCES=parse_tsipex.c crc32.c crc32.h\
 get_u.h parse_tsip.c parse_tsip.h 
parse_tsipex_DEPENDENCIES=$(stribog_lib) ../../common/form_fix.h
parse_tsipex_LDADD=$(stribog_lib)
