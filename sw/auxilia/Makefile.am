##Makefile.am is generated with m4 from Makefile.am.m4
#Makefile.in is generated with automake from Makefile.am
#Makefile is produced with configure script from Makefile.in
#Copyright (C) 2008 Ineiev<ineiev@users.sourceforge.net>, super V 93
#use autoreconf to regenerate all our build scripts
#
#This file is a part of the stribog project
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
nodist_pkgdata_DATA=
noinst_PROGRAMS=

mcu=atmega8
AM_CFLAGS=-mmcu=$(mcu)
AM_LDFLAGS=-mmcu=$(mcu)
OBJCOPY=avr-objcopy
EXTRA_DIST=Makefile.am.m4 m4/makefile.m4
##expanded "sampler" program definition begins
nodist_pkgdata_DATA+=sampler.hex
#sampler.map
noinst_PROGRAMS+=sampler
sampler_SOURCES=coil/sampler.c
sampler_LDFLAGS=$(AM_LDFLAGS)
EXTRA_sampler_SOURCES=$(extra_common_sources)
sampler.hex: $(sampler_sources)
	$(MAKE) $(AM_MAKEFLAGS) sampler
	$(OBJCOPY) -O ihex -R .eeprom sampler sampler.hex
#sampler.map: $(sampler_sources)
#	$(MAKE) $(AM_MAKEFLAGS) sampler
##expanded "sampler" program definition ends
##expanded "hodo" program definition begins
nodist_pkgdata_DATA+=hodo.hex
#hodo.map
noinst_PROGRAMS+=hodo
hodo_SOURCES=odo/hodo.c
hodo_LDFLAGS=$(AM_LDFLAGS)
EXTRA_hodo_SOURCES=$(extra_common_sources)
hodo.hex: $(hodo_sources)
	$(MAKE) $(AM_MAKEFLAGS) hodo
	$(OBJCOPY) -O ihex -R .eeprom hodo hodo.hex
#hodo.map: $(hodo_sources)
#	$(MAKE) $(AM_MAKEFLAGS) hodo
##expanded "hodo" program definition ends

$(srcdir)/Makefile.am: $(srcdir)/Makefile.am.m4 $(srcdir)/m4/makefile.m4
	m4 -I $(srcdir) $(srcdir)/Makefile.am.m4 > $(srcdir)/Makefile.am
nodist_pkgdata_DATA+=summary config.h
dist-hook:
	$(RM) $(nodist_pkgdata_DATA)
