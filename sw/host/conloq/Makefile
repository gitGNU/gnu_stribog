#stribog data loggers and parsers: Makefile
#
#This program is free software; you can redistribute it and/or modify
#it under the terms of the GNU General Public License as published by
#the Free Software Foundation; either version 2 of the License, or
#(at your option) any later version.
#
#This program is distributed in the hope that it will be useful,
#but WITHOUT ANY WARRANTY; without even the implied warranty of
#MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#GNU General Public License for more details.
#
#You should have received a copy of the GNU General Public License
#along with this program; if not, write to the Free Software
#Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
#
#Copyright (C) 2005-2006 D.Ineiev <ineiev@yahoo.co.uk>
CC=gcc
LD=gcc
LDFLAGS=-lm
CFLAGS=-Wall
.PHONY: all clean maintainer-clean
all: bin/conloq bin/caed bin/elig bin/expon bin/magex-conloq bin/magexpon
clean:
	rm -f *.o
maintainer-clean: clean
	rm -f bin/* *.log *.dat
bin/%:%.o
	$(LD) $(LDFLAGS) $^ -o $@
bin/conloq:crc32.o error.o exp-brief.o garmin_nmea.o\
 parse_tsip.o serialia.o usage.o
bin/magex-conloq:serialia.o error.o parse_tsip.o magexp.o
bin/caed:crc32.o error.o parse_tsip.o
bin/elig:error.o parse_tsip.o
bin/expon:crc32.o error.o exp.o garmin_nmea.o lla.o parse_tsip.o preproc_gps.o
bin/magexpon:expon.o parse_tsip.o error.o magexp.o
	$(LD) $(LDFLAGS) $^ -o $@
caed.o:crc32.h error.h parse_tsip.h
conloq.o:error.h exp.h parse_tsip.h serialia.h usage.h
magex-conloq.o:error.h exp.h parse_tsip.h serialia.h
expon.o:exp.h parse_tsip.h
magexpon.o:exp.h parse_tsip.h
serialia.o:serialia.h
usage.o:usage.h
elig.o:error.h parse_tsip.h
exp.o:error.h exp.h exp_gps.h
exp-brief.o:error.h exp.h exp_gps.h
garmin_bin.o:exp_gps.h parse_tsip.h
garmin_nmea.o:error.h exp_gps.h preproc_gps.h
lla.o:lla.h
preproc_gps.o:lla.h preproc_gps.h
