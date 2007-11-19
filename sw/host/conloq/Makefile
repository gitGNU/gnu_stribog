#stribog data loggers and parsers: Makefile
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
#Copyright (C) 2005, 2006, 2007\
# Ineiev<ineiev@users.sourceforge.net>, super V 93
LD=gcc
LDFLAGS=-lm -s
CFLAGS=-Wall -O2
.PHONY: all clean maintainer-clean
src=.
o=o
bin=bin
TARGETS=caed conloq elig expon magex-conloq magexp parse_tsipex
targets=$(foreach t,$(TARGETS),$(bin)/$(t))
all: $(o)/autodeps.mk $(targets)
$(o)/dirs_stamp:
	mkdir -p $(o) $(bin);echo >$@
sources=caed conloq crc32 elig error exp-brief exp expon\
 garmin_bin garmin_nmea hodo lla magex-conloq magexp parse_tsip\
 parse_tsipex preproc_gps process_keypress serialia usage verbosity_level
pathed_sources=$(foreach t,$(sources), $(src)/$(t).c)
$(o)/autodeps.mk: $(o)/dirs_stamp $(pathed_sources)
	echo "#automatically generated: don't try to edit by hand">$@
	for i in $(sources);\
 do $(CC) $(CFLAGS) -MM -MT $(o)/$$i.o $(src)/$$i.c >>$@;done
include $(o)/autodeps.mk
clean:
	$(RM) $(o)/*.o $(o)/autodeps.mk
maintainer-clean: clean
	$(RM) -r $(bin) $(o) *.log *.dat
$(bin)/caed:$(o)/crc32.o $(o)/error.o $(o)/parse_tsip.o
$(bin)/conloq:$(o)/crc32.o $(o)/error.o $(o)/exp-brief.o\
 $(o)/process_keypress.o $(o)/garmin_nmea.o $(o)/hodo.o $(o)/parse_tsip.o\
 $(o)/serialia.o $(o)/usage.o $(o)/verbosity_level.o
$(bin)/elig:$(o)/error.o $(o)/parse_tsip.o
$(bin)/expon:$(o)/crc32.o $(o)/error.o $(o)/exp.o $(o)/garmin_nmea.o $(o)/hodo.o $(o)/lla.o\
 $(o)/parse_tsip.o $(o)/preproc_gps.o $(o)/verbosity_level.o
$(bin)/magex-conloq:$(o)/serialia.o $(o)/error.o $(o)/parse_tsip.o $(o)/magexp.o
$(bin)/magexp:$(o)/expon.o $(o)/parse_tsip.o $(o)/error.o $(o)/magexp.o
$(bin)/parse_tsipex:$(o)/crc32.o $(o)/error.o $(o)/parse_tsip.o
$(o)/%.o:$(src)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<
$(bin)/%:$(o)/%.o
	$(LD) $(LDFLAGS) -o $@ $^
