divert(-1)
#stribog auxilia tools: Makefile.am.m4
#use autoreconf and then build to regenerate the sources configuration system
#Copyright (C) 2008 Ineiev<ineiev@users.sourceforge.net>, super V 93
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
include(`m4/makefile.m4')
mcu=atmega8
AM_CFLAGS=-mmcu=$(mcu)
AM_LDFLAGS=-mmcu=$(mcu)
OBJCOPY=avr-objcopy
EXTRA_DIST=Makefile.am.m4 m4/makefile.m4
divert(-1)
 ST_AVR_TARGET(`program_name', `program_sources')
 It expands into a sequence of automake commands that define 
 this target program. 
divert`'dnl
ST_AVR_TARGET(`sampler',`coil/sampler.c')
ST_AVR_TARGET(`hodo', `odo/hodo.c')

$(srcdir)/Makefile.am: $(srcdir)/Makefile.am.m4 $(srcdir)/m4/makefile.m4
	m4 -I $(srcdir) $(srcdir)/Makefile.am.m4 > $(srcdir)/Makefile.am
nodist_pkgdata_DATA+=summary config.h
dist-hook:
	$(RM) $(nodist_pkgdata_DATA)
