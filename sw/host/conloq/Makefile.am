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
bin_PROGRAMS=caed conloq elig expon magex-conloq magexp parse_tsipex
caed_SOURCES=caed.c crc32.c error.c parse_tsip.c
caed_LDADD=-lm
conloq_SOURCES=conloq.c crc32.c error.c exp-brief.c\
 process_keypress.c garmin_nmea.c hodo.c parse_tsip.c\
 serialia.c usage.c verbosity_level.c
conloq_LDADD=-lm
elig_SOURCES=elig.c error.c parse_tsip.c
elig_LDADD=-lm
expon_SOURCES=expon.c crc32.c error.c exp.c garmin_nmea.c hodo.c lla.c\
 parse_tsip.c preproc_gps.c verbosity_level.c
expon_LDADD=-lm
magex_conloq_SOURCES=magex-conloq.c serialia.c error.c parse_tsip.c magexp.c
magex_conloq_LDADD=-lm
magexp_SOURCES=expon.c parse_tsip.c error.c magexp.c
magexp_LDADD=-lm
parse_tsipex_SOURCES=parse_tsipex.c crc32.c error.c parse_tsip.c
parse_tsipex_LDADD=-lm
