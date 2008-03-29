#elk the LPC21x programmer: Makefile.am
#Copyright (C) 2005, 2006, 2007, 2008\
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
if the_host_is_windows
#forced to use non-free OS API
 serial_source=wser.c
else
#using POSIX RS-232 UART API by default
serial_source=serialia.c
endif
AM_CPPFLAGS=-DPACKAGE_DATA_DIR="\"$(datadir)\"" -DSOURCE_DIR="\"$(srcdir)\""
bin_PROGRAMS=elk
elk_SOURCES=elk.c $(serial_source) serialia.h usage.h\
 ../lib/save_wd.c ../lib/save_wd.h
elk_LDADD=$(argp_lib) $(stribog_lib)
elk_DEPENDENCIES=$(argp_lib) $(stribog_lib)
EXTRA_elk_SOURCES=serialia.c wser.c
