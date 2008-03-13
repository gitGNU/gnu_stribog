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
AM_CFLAGS="-mcpu=arm7tdmi -Wall -O2"
AM_LDFLAGS="-Map $@.map -nostartup -nostdlib -static"
AM_LIBS=$(libgcc)
ram_ldscript=$(srcdir)/src/ram2138.ld
ram_script_flag="-T$(ldscript)"
rom_ldscript=$(srcdir)/src/2138.ld
rom_script_flag="-T$(rom_ldscript)"
