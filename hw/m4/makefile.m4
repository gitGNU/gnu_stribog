divert(-1)
#stribog hardware design: m4 macros to generate Makefile.am
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
define(ST_BOARD,
`###board $1 expanded definition begins
EXTRA_DIST+=$1.pcb $1.proj
board$1dir=$(pkgdatadir)/$1
board$1gerberdir=$(board$1dir)/gerber
board$1psdir=$(board$1dir)/ps
##board $1 gerbers begin
dist_board$1gerber_DATA=$1/$1.back.gbr\
 $1/$1.backpaste.gbr\
 $1/$1.fab.gbr\
 $1/$1.frontmask.gbr\
 $1/$1.frontsilk.gbr\
 $1/$1.backmask.gbr\
 $1/$1.backsilk.gbr\
 $1/$1.front.gbr\
 $1/$1.frontpaste.gbr\
 $1/$1.plated-drill.cnc
if use_pcb
$1/$1.fab.gbr: $1.pcb
	$(MKDIR_P) $1
	pcb -x gerber --gerberfile $1/$1 $(srcdir)/$1.pcb
$1/$1.back.gbr\
 $1/$1.backpaste.gbr\
 $1/$1.frontmask.gbr\
 $1/$1.frontsilk.gbr\
 $1/$1.backmask.gbr\
 $1/$1.backsilk.gbr\
 $1/$1.front.gbr\
 $1/$1.frontpaste.gbr\
 $1/$1.plated-drill.cnc\
 : $1/$1.fab.gbr
	if test -f $@; then touch $@; else\
  rm -f $1/$1.fab.gbr;\
  $(MAKE) $(AM_MAKEFLAGS) $1/$1.fab.gbr; fi
endif
##board $1 gerbers end
##board $1 PS/PDFs begin
dist_board$1ps_DATA=$1/$1.ps $1/$1.pdf
if use_pcb
$1/$1.ps: $1.pcb
	$(MKDIR_P) $1
	pcb -x ps --psfile $1/$1.ps $(srcdir)/$1.pcb
endif
$1/$1.pdf: $1/$1.ps
	cd $1;ps2pdf $1.ps $1.pdf
##board $1 PS/PDFs end
###board $1 expanded definition ends'
)
define(ST_SCHEMATIC,
`###schematic $1 expanded definition begins
EXTRA_DIST+=$1.sch schematics/$1.png
schematics_DATA+=schematics/$1.png
if use_gschem
schematics/$1.png: $1.sch
	$(MKDIR_P) schematics
	gschem -p -o $(abs_builddir)/schematics/$1.png\
 -s $(abs_builddir)/image.scm $(srcdir)/$1.sch 2>/dev/null
	$(RM) gschem.log
endif
###schematic $1 expanded definition ends
')
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
