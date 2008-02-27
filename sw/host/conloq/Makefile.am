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
bin_PROGRAMS=caed conloq elig expon magex-conloq magexp parse_tsipex
caed_SOURCES=caed.c crc32.c crc32.h error.c error.h get_u.h\
 parse_tsip.c parse_tsip.h
conloq_SOURCES=conloq.c crc32.c crc32.h error.c error.h exp-brief.c exp.h\
 exp_gps.h prepeoc_gps.h get_u.h\
 process_keypress.c process_keypress.h garmin_nmea.c hodo.c hodo.h\
 parse_tsip.c parse_tsip.h\
 $(serial_source) serialia.h usage.h\
 verbosity_level.c verbosity_level.h
elig_SOURCES=elig.c error.c error.h parse_tsip.c parse_tsip.h
expon_SOURCES=expon.c crc32.c crc32.h error.c error.h exp.c exp.h\
 garmin_nmea.c exp_gps.h hodo.c hodo.h lla.c lla.h\
 parse_tsip.c parse_tsip.h preproc_gps.c preproc_gps.h\
 verbosity_level.c verbosity_level.h
magex_conloq_SOURCES=magex-conloq.c $(serial_source) serialia.h\
 error.c error.h parse_tsip.c parse_tsip.h magexp.c exp.h
magexp_SOURCES=expon.c verbosity_level.h\
 parse_tsip.c parse_tsip.h error.c error.h magexp.c exp.h
parse_tsipex_SOURCES=parse_tsipex.c crc32.c crc32.h\
 error.c error.h get_u.h parse_tsip.c parse_tsip.h ../../common/form_fix.h
