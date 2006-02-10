#elk the LPC21x programmer: Makefile
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
LFLAGS=
CFLAGS=-Wall
.PHONY: all clean maintainer-clean
all: elk
clean:
	rm -f *.o
maintainer-clean: clean
	rm -f elk
elk: elk.o serialia.o usage.o
	$(CC) $(LFLAGS) $^ -o $@
elk.o:elk.c serialia.h usage.h
serialia.o:serialia.c serialia.h
usage.o:usage.c usage.h
