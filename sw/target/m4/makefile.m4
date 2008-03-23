divert(-1)
#stribog target tools: m4 macros to generate Makefile.am
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
define(ST_TARGET_PROGRAM,
`$1_sources=$(common_sources)\
 $2
$1_SOURCES=$($1_sources)
$1_LDFLAGS=$(AM_LDFLAGS) $(ram_flag)
EXTRA_$1_SOURCES=$(extra_common_sources)
$1_DEPENDENCIES=ram2138.ld $3
$1_rom_SOURCES=$($1_sources)
$1_rom_LDFLAGS=$(AM_LDFLAGS) $(rom_flag)
EXTRA_$1_rom_SOURCES=$(extra_common_sources)
$1_rom_DEPENDENCIES=2138.ld $3
$1.bin: $($1_sources)
	$(MAKE) $(AM_MAKEFLAGS) $1
	$(objcopy_bin) $1 $1.bin
$1.map: $($1_sources)
	$(MAKE) $(AM_MAKEFLAGS) $1
$1.vectors: $($1_sources)
	$(MAKE) $(AM_MAKEFLAGS) $1
	$(objcopy_vectors) $1 $1.vectors
$1-rom.bin: $($1_sources)
	$(MAKE) $(AM_MAKEFLAGS) $1-rom
	$(objcopy_bin) $1-rom $1-rom.bin
$1-rom.map: $($1_sources)
	$(MAKE) $(AM_MAKEFLAGS) $1
#expanded "$1" program definition ends')

define(ST_ENABLE_TARGET,
`nodist_pkgdata_DATA+=\
 $1.bin $1.vectors $1.map\
 $1-rom.bin $1-rom.map
noinst_PROGRAMS+=$1 $1-rom
')
define(ST_TARGET,
`#expanded "$1" program definition begins
ST_ENABLE_TARGET($1)
ST_TARGET_PROGRAM($1,$2,$3)')
define(ST_EXTRA_TARGET,
`#conditional "$1" program definition begins
EXTRA_PROGRAMS+=$1 $1-rom
if $1_enabled
 ST_ENABLE_TARGET($1)
endif
ST_TARGET_PROGRAM($1,$2,$3)')
divert`'dnl
#Makefile.am is generated with m4 from Automake.am.m4
#use ./regen_configure to regenerate all our build scripts
#
#This file is a part of the stribog project
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
nodist_pkgdata_DATA=
noinst_PROGRAMS=
EXTRA_PROGRAMS=
