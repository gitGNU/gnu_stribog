#conloq (talk to stribog from a Unix terminal): Makefile
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
LFLAGS=-s
CFLAGS=-Wall
.PHONY: all clean maintainer-clean
all: bin/conloq bin/expon
clean:
	rm -f *.o
maintainer-clean: clean
bin/%:%.o
	$(LD) $(LFLAGS) $^ -o $@
bin/conloq:serialia.o usage.o crc32.o error.o parse_tsip.o exp.o
bin/expon:parse_tsip.o error.o crc32.o exp.o
conloq.o:serialia.h usage.h error.h parse_tsip.h exp.h
expon.o:parse_tsip.h exp.h
serialia.o:serialia.h
usage.o:usage.h
