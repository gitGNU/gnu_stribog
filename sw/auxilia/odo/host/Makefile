#Makefile for odometer firmware test
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
#along with this program. If not, see <http://www.gnu.org/licenses/>.
#
#Copyright (C) 2007 Ineiev <ineiev@users.sourceforge.net>
.PHONY: all clean maintainer-clean
CC=gcc
CFLAGS=-Wall
all:hodo
hodo:hodo.o serialia.o
hodo.o:serialia.h
serialia.o:serialia.h
clean:
	rm *.o
maintainer-clean:clean
	rm *.log hodo
