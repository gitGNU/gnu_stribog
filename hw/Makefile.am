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

EXTRA_DIST=Makefile.am.m4 m4/makefile.m4 gafrc\
sym/ATmega8-1.sym sym/JTAG.sym sym/README sym/adm202.sym sym/adxl210.sym\
sym/adxrs300.sym sym/bat54c.sym sym/dac7612.sym sym/hmc1021.sym\
sym/hmc1022.sym sym/ina118.sym sym/irf7317.sym sym/irf7507.sym\
sym/irlml.sym sym/led.sym sym/lm74.sym sym/lp2980AIM5-3.sym\
sym/lp2980AIM5-5.sym sym/lpc2138.sym sym/ref195.sym sym/tps76316.sym\
packages/0.125W_resistor packages/0603\
packages/0805 packages/1210\
packages/2.5mm_10pin_header packages/README\
packages/adxl210 packages/crystal\
packages/hmc1021z packages/jtag1.27x1\
packages/led0805 packages/lp2980\
packages/msop8 packages/pin\
packages/qfp64 packages/tanA packages/tanC packages/tp
###board main_board expanded definition begins
EXTRA_DIST+=main_board.pcb main_board.proj
boardmain_boarddir=$(pkgdatadir)/main_board
boardmain_boardgerberdir=$(boardmain_boarddir)/gerber
boardmain_boardpsdir=$(boardmain_boarddir)/ps
##board main_board gerbers begin
dist_boardmain_boardgerber_DATA=main_board/main_board.back.gbr\
 main_board/main_board.backpaste.gbr\
 main_board/main_board.fab.gbr\
 main_board/main_board.frontmask.gbr\
 main_board/main_board.frontsilk.gbr\
 main_board/main_board.backmask.gbr\
 main_board/main_board.backsilk.gbr\
 main_board/main_board.front.gbr\
 main_board/main_board.frontpaste.gbr\
 main_board/main_board.plated-drill.cnc
main_board/main_board.fab.gbr: main_board.pcb
	$(MKDIR_P) main_board
	pcb -x gerber --gerberfile main_board/main_board $(srcdir)/main_board.pcb
main_board/main_board.back.gbr\
 main_board/main_board.backpaste.gbr\
 main_board/main_board.frontmask.gbr\
 main_board/main_board.frontsilk.gbr\
 main_board/main_board.backmask.gbr\
 main_board/main_board.backsilk.gbr\
 main_board/main_board.front.gbr\
 main_board/main_board.frontpaste.gbr\
 main_board/main_board.plated-drill.cnc\
 : main_board/main_board.fab.gbr
	if test -f main_board; then touch main_board; else\
  rm -f main_board/main_board.fab.gbr;\
  $(MAKE) $(AM_MAKEFLAGS) main_board/main_board.fab.gbr; fi
##board main_board gerbers end
##board main_board PS/PDFs begin
dist_boardmain_boardps_DATA=main_board/main_board.ps main_board/main_board.pdf
main_board/main_board.ps: main_board.pcb
	$(MKDIR_P) main_board
	pcb -x ps --psfile main_board/main_board.ps $(srcdir)/main_board.pcb
main_board/main_board.pdf: main_board/main_board.ps
	cd main_board;ps2pdf main_board.ps main_board.pdf
##board main_board PS/PDFs end
###board main_board expanded definition ends

###board main_board.bis expanded definition begins
EXTRA_DIST+=main_board.bis.pcb main_board.bis.proj
boardmain_board.bisdir=$(pkgdatadir)/main_board.bis
boardmain_board.bisgerberdir=$(boardmain_board.bisdir)/gerber
boardmain_board.bispsdir=$(boardmain_board.bisdir)/ps
##board main_board.bis gerbers begin
dist_boardmain_board.bisgerber_DATA=main_board.bis/main_board.bis.back.gbr\
 main_board.bis/main_board.bis.backpaste.gbr\
 main_board.bis/main_board.bis.fab.gbr\
 main_board.bis/main_board.bis.frontmask.gbr\
 main_board.bis/main_board.bis.frontsilk.gbr\
 main_board.bis/main_board.bis.backmask.gbr\
 main_board.bis/main_board.bis.backsilk.gbr\
 main_board.bis/main_board.bis.front.gbr\
 main_board.bis/main_board.bis.frontpaste.gbr\
 main_board.bis/main_board.bis.plated-drill.cnc
main_board.bis/main_board.bis.fab.gbr: main_board.bis.pcb
	$(MKDIR_P) main_board.bis
	pcb -x gerber --gerberfile main_board.bis/main_board.bis $(srcdir)/main_board.bis.pcb
main_board.bis/main_board.bis.back.gbr\
 main_board.bis/main_board.bis.backpaste.gbr\
 main_board.bis/main_board.bis.frontmask.gbr\
 main_board.bis/main_board.bis.frontsilk.gbr\
 main_board.bis/main_board.bis.backmask.gbr\
 main_board.bis/main_board.bis.backsilk.gbr\
 main_board.bis/main_board.bis.front.gbr\
 main_board.bis/main_board.bis.frontpaste.gbr\
 main_board.bis/main_board.bis.plated-drill.cnc\
 : main_board.bis/main_board.bis.fab.gbr
	if test -f main_board.bis; then touch main_board.bis; else\
  rm -f main_board.bis/main_board.bis.fab.gbr;\
  $(MAKE) $(AM_MAKEFLAGS) main_board.bis/main_board.bis.fab.gbr; fi
##board main_board.bis gerbers end
##board main_board.bis PS/PDFs begin
dist_boardmain_board.bisps_DATA=main_board.bis/main_board.bis.ps main_board.bis/main_board.bis.pdf
main_board.bis/main_board.bis.ps: main_board.bis.pcb
	$(MKDIR_P) main_board.bis
	pcb -x ps --psfile main_board.bis/main_board.bis.ps $(srcdir)/main_board.bis.pcb
main_board.bis/main_board.bis.pdf: main_board.bis/main_board.bis.ps
	cd main_board.bis;ps2pdf main_board.bis.ps main_board.bis.pdf
##board main_board.bis PS/PDFs end
###board main_board.bis expanded definition ends

$(srcdir)/Makefile.am: $(srcdir)/Makefile.am.m4 $(srcdir)/m4/makefile.m4
	m4 -I $(srcdir) $(srcdir)/Makefile.am.m4 > $(srcdir)/Makefile.am
