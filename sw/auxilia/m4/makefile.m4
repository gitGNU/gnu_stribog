divert(-1)
#stribog AVR programs: m4 macros to generate Makefile.am
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
define(ST_AVR_TARGET,
`##expanded "$1" program definition begins
nodist_pkgdata_DATA+=$1.hex
#$1.map
noinst_PROGRAMS+=$1
$1_SOURCES=$2
$1_LDFLAGS=$(AM_LDFLAGS)
EXTRA_$1_SOURCES=$(extra_common_sources)
$1.hex: $($1_sources)
	$(MAKE) $(AM_MAKEFLAGS) $1
	$(OBJCOPY) -O ihex -R .eeprom $1 $1.hex
#$1.map: $($1_sources)
#	$(MAKE) $(AM_MAKEFLAGS) $1
##expanded "$1" program definition ends')
divert`'dnl
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
