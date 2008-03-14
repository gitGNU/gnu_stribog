#stribog target tools: Makefile.am
#Copyright (C) 2008\
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
EXTRA_DIST=lib/fake-cc
common_sources=src/boot.s include/lpc2138.h
if add_own_atexit
 common_sources+=lib/atexit.c
endif
extra_common_sources=lib/atexit.c
AM_CFLAGS=-mcpu=arm7tdmi -Wall -O2
AM_LDFLAGS=-Wl,-Map,$@.map -nostdlib -static
AM_LIBS=$(libgcc)
ram_ld=src/ram2138.ld
ram_ldscript=$(srcdir)/$(ram_ld)
ram_flag=-T$(ram_ldscript)
rom_ld=src/2138.ld
rom_ldscript=$(srcdir)/$(rom_ld)
rom_flag=-T$(rom_ldscript)
noinst_PROGRAMS=pllex pllex-rom
pllex_sources=$(common_sources)\
 src/pllex.c src/pll.c src/pll.h src/led.c src/led.h
pllex_SOURCES=$(pllex_sources)
pllex_LDFLAGS=$(AM_LDFLAGS) $(ram_flag)
EXTRA_pllex_SOURCES=$(extra_common_sources)
pllex_DEPENDENCIES=$(ram_ld)
pllex_rom_SOURCES=$(pllex_sources)
pllex_rom_LDFLAGS=$(AM_LDFLAGS) $(rom_flag)
EXTRA_pllex_rom_SOURCES=$(extra_common_sources)
pllex_rom_DEPENDENCIES=$(rom_ld)
