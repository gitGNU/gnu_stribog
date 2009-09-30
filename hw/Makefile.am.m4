divert(-1)
#stribog hardware design: Makefile.am.m4
#to initially make Makefile.am, run m4 -I . Makefile.am.m4 > Makefile.am
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
ST_BOARD(main_board)
ST_BOARD(main_board_bis)
$(srcdir)/Makefile.am: $(srcdir)/Makefile.am.m4 $(srcdir)/m4/makefile.m4
	m4 -I $(srcdir) $(srcdir)/Makefile.am.m4 > $(srcdir)/Makefile.am
schematicsdir=$(pkgdatadir)/schematics
schematics_DATA=
ST_SCHEMATIC(stribog)
ST_SCHEMATIC(odo)
ST_SCHEMATIC(gyro)
DISTCLEANFILES=image.scm
