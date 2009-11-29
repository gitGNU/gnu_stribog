##Makefile.am is generated with m4 from Makefile.am.m4
#Makefile.in is generated with automake from Makefile.am
#Makefile is produced with configure script from Makefile.in
#Copyright (C) 2008, 2009 Ineiev<ineiev@users.berlios.de>, super V 93
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
sym/3.3V-plus-1s.sym sym/A5V-plus-1s.sym\
sym/ATmega8-1s.sym sym/DB9-1s.sym sym/JTAG.sym\
sym/README sym/adm202.sym sym/adxl210.sym sym/adxrs300.sym\
sym/bat54c.sym sym/capacitor-1s.sym sym/capacitor-4s.sym sym/coil-1s.sym\
sym/crystal-1s.sym sym/dac7612.sym sym/dual-opamp-1s.sym\
sym/gnd-1s.sym sym/header10-2s.sym sym/hmc1021.sym\
sym/hmc1022.sym sym/idg300.sym sym/idg500.sym sym/ina118.sym\
sym/irf7317.sym sym/irf7507.sym sym/irlml.sym\
sym/irlml-p.sym sym/led.sym sym/lis3lv02dl.sym sym/lisy300al.sym\
sym/lm74.sym sym/lm7805-1s.sym sym/lp2980AIM5-3.sym\
sym/lp2980AIM5-5.sym sym/lpc2138.sym sym/opamp-1s.sym\
sym/quad_opamp-1s.sym sym/ref195.sym sym/resistor-2s.sym\
sym/testpt-1s.sym sym/tmp101.sym sym/tps76316.sym sym/VddAcc-1s.sym\
packages/0.125W_resistor packages/0603\
packages/0805 packages/1210\
packages/2.5mm_10pin_header packages/IDG-300 packages/IDG-500\
packages/LGA16 packages/LGA28 packages/README\
packages/adxl210 packages/crystal\
packages/hmc1021z packages/jtag1.27x1\
packages/led0805 packages/lp2980\
packages/msop8 packages/pin\
packages/qfp64 packages/tanA packages/tanC packages/tmp101 packages/tp
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
if use_pcb
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
endif
##board main_board gerbers end
##board main_board PS/PDFs begin
dist_boardmain_boardps_DATA=main_board/main_board.ps main_board/main_board.pdf
if use_pcb
main_board/main_board.ps: main_board.pcb
	$(MKDIR_P) main_board
	pcb -x ps --psfile main_board/main_board.ps $(srcdir)/main_board.pcb
endif
if use_ps2pdf
main_board/main_board.pdf: main_board/main_board.ps
	cd main_board; $(PS2PDF) main_board.ps main_board.pdf
endif
##board main_board PS/PDFs end
###board main_board expanded definition ends

###board main_board_bis expanded definition begins
EXTRA_DIST+=main_board_bis.pcb main_board_bis.proj
boardmain_board_bisdir=$(pkgdatadir)/main_board_bis
boardmain_board_bisgerberdir=$(boardmain_board_bisdir)/gerber
boardmain_board_bispsdir=$(boardmain_board_bisdir)/ps
##board main_board_bis gerbers begin
dist_boardmain_board_bisgerber_DATA=main_board_bis/main_board_bis.back.gbr\
 main_board_bis/main_board_bis.backpaste.gbr\
 main_board_bis/main_board_bis.fab.gbr\
 main_board_bis/main_board_bis.frontmask.gbr\
 main_board_bis/main_board_bis.frontsilk.gbr\
 main_board_bis/main_board_bis.backmask.gbr\
 main_board_bis/main_board_bis.backsilk.gbr\
 main_board_bis/main_board_bis.front.gbr\
 main_board_bis/main_board_bis.frontpaste.gbr\
 main_board_bis/main_board_bis.plated-drill.cnc
if use_pcb
main_board_bis/main_board_bis.fab.gbr: main_board_bis.pcb
	$(MKDIR_P) main_board_bis
	pcb -x gerber --gerberfile main_board_bis/main_board_bis $(srcdir)/main_board_bis.pcb
main_board_bis/main_board_bis.back.gbr\
 main_board_bis/main_board_bis.backpaste.gbr\
 main_board_bis/main_board_bis.frontmask.gbr\
 main_board_bis/main_board_bis.frontsilk.gbr\
 main_board_bis/main_board_bis.backmask.gbr\
 main_board_bis/main_board_bis.backsilk.gbr\
 main_board_bis/main_board_bis.front.gbr\
 main_board_bis/main_board_bis.frontpaste.gbr\
 main_board_bis/main_board_bis.plated-drill.cnc\
 : main_board_bis/main_board_bis.fab.gbr
	if test -f main_board_bis; then touch main_board_bis; else\
  rm -f main_board_bis/main_board_bis.fab.gbr;\
  $(MAKE) $(AM_MAKEFLAGS) main_board_bis/main_board_bis.fab.gbr; fi
endif
##board main_board_bis gerbers end
##board main_board_bis PS/PDFs begin
dist_boardmain_board_bisps_DATA=main_board_bis/main_board_bis.ps main_board_bis/main_board_bis.pdf
if use_pcb
main_board_bis/main_board_bis.ps: main_board_bis.pcb
	$(MKDIR_P) main_board_bis
	pcb -x ps --psfile main_board_bis/main_board_bis.ps $(srcdir)/main_board_bis.pcb
endif
if use_ps2pdf
main_board_bis/main_board_bis.pdf: main_board_bis/main_board_bis.ps
	cd main_board_bis; $(PS2PDF) main_board_bis.ps main_board_bis.pdf
endif
##board main_board_bis PS/PDFs end
###board main_board_bis expanded definition ends

$(srcdir)/Makefile.am: $(srcdir)/Makefile.am.m4 $(srcdir)/m4/makefile.m4
	m4 -I $(srcdir) $(srcdir)/Makefile.am.m4 > $(srcdir)/Makefile.am
schematicsdir=$(pkgdatadir)/schematics
schematics_DATA=
###schematic stribog expanded definition begins
EXTRA_DIST+=stribog.sch schematics/stribog.png schematics/stribog.ps schematics/stribog.pdf
schematics_DATA+=schematics/stribog.png schematics/stribog.ps schematics/stribog.pdf
if use_gschem
schematics/stribog.png: stribog.sch
	$(MKDIR_P) schematics
	gschem -p -o $(abs_builddir)/schematics/stribog.png\
 -s $(abs_builddir)/image.scm $(srcdir)/stribog.sch 2>/dev/null
	$(RM) gschem.log
schematics/stribog.ps: stribog.sch
	$(MKDIR_P) schematics
	gschem -p -o $(abs_builddir)/schematics/stribog.ps\
 -s $(srcdir)/ps.scm $(srcdir)/stribog.sch 2>/dev/null
	$(RM) gschem.log
if use_ps2pdf
schematics/stribog.pdf: schematics/stribog.ps
	cd schematics; $(PS2PDF) stribog.ps stribog.pdf
endif
endif
###schematic stribog expanded definition ends

###schematic stribog_1 expanded definition begins
EXTRA_DIST+=stribog_1.sch schematics/stribog_1.png schematics/stribog_1.ps schematics/stribog_1.pdf
schematics_DATA+=schematics/stribog_1.png schematics/stribog_1.ps schematics/stribog_1.pdf
if use_gschem
schematics/stribog_1.png: stribog_1.sch
	$(MKDIR_P) schematics
	gschem -p -o $(abs_builddir)/schematics/stribog_1.png\
 -s $(abs_builddir)/image.scm $(srcdir)/stribog_1.sch 2>/dev/null
	$(RM) gschem.log
schematics/stribog_1.ps: stribog_1.sch
	$(MKDIR_P) schematics
	gschem -p -o $(abs_builddir)/schematics/stribog_1.ps\
 -s $(srcdir)/ps.scm $(srcdir)/stribog_1.sch 2>/dev/null
	$(RM) gschem.log
if use_ps2pdf
schematics/stribog_1.pdf: schematics/stribog_1.ps
	cd schematics; $(PS2PDF) stribog_1.ps stribog_1.pdf
endif
endif
###schematic stribog_1 expanded definition ends

###schematic odo expanded definition begins
EXTRA_DIST+=odo.sch schematics/odo.png schematics/odo.ps schematics/odo.pdf
schematics_DATA+=schematics/odo.png schematics/odo.ps schematics/odo.pdf
if use_gschem
schematics/odo.png: odo.sch
	$(MKDIR_P) schematics
	gschem -p -o $(abs_builddir)/schematics/odo.png\
 -s $(abs_builddir)/image.scm $(srcdir)/odo.sch 2>/dev/null
	$(RM) gschem.log
schematics/odo.ps: odo.sch
	$(MKDIR_P) schematics
	gschem -p -o $(abs_builddir)/schematics/odo.ps\
 -s $(srcdir)/ps.scm $(srcdir)/odo.sch 2>/dev/null
	$(RM) gschem.log
if use_ps2pdf
schematics/odo.pdf: schematics/odo.ps
	cd schematics; $(PS2PDF) odo.ps odo.pdf
endif
endif
###schematic odo expanded definition ends

###schematic gyro expanded definition begins
EXTRA_DIST+=gyro.sch schematics/gyro.png schematics/gyro.ps schematics/gyro.pdf
schematics_DATA+=schematics/gyro.png schematics/gyro.ps schematics/gyro.pdf
if use_gschem
schematics/gyro.png: gyro.sch
	$(MKDIR_P) schematics
	gschem -p -o $(abs_builddir)/schematics/gyro.png\
 -s $(abs_builddir)/image.scm $(srcdir)/gyro.sch 2>/dev/null
	$(RM) gschem.log
schematics/gyro.ps: gyro.sch
	$(MKDIR_P) schematics
	gschem -p -o $(abs_builddir)/schematics/gyro.ps\
 -s $(srcdir)/ps.scm $(srcdir)/gyro.sch 2>/dev/null
	$(RM) gschem.log
if use_ps2pdf
schematics/gyro.pdf: schematics/gyro.ps
	cd schematics; $(PS2PDF) gyro.ps gyro.pdf
endif
endif
###schematic gyro expanded definition ends

DISTCLEANFILES=image.scm
