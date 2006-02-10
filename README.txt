Stribog the sensing platform README file.

ATTENTION stribog is in his pre-alpha stage. it is not functional yet.

The end of this file contains license and copyright notes for the project.

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

    Copyright (C) 2005-2006 D.Ineiev <ineiev@yahoo.co.uk>

Note: actually the next version of the GPL is to be released the next term. 
stribog's author believes they both will be able to use this new version then.
however, the first drafts don't seem to be much better than GPL v2.

It is not certain, whether a printed board contains a "derived" from
the sources "work". stribog's author thinks that a PCB layout files 
(as hw/main_board.pcb) do form a derived work, but the result of PCB print 
command (GERBER/EXCELLON, PostScript files) contains no "derived work", to say 
nothing of printed boards and assembled devices. that is, this license does 
not restrict any use of these items. neither does the copyright holder.

Nonetheless, any schematic diagram in any form does contain such a "work".

This may look inconsistent, this can be argued, but the author considers this
approach to be the most correct one. the copyright holder may change this 
point of view in future releases to make it more consistent, but for no past 
release.

The software part is accurately released under the terms of the GNU GPL v2.

The following non-text source files possibly contain no copyright notices, 
because stribog's author decided to move those notices here for convenience, 
namely:

hw/main_board.pcb
hw/stribog.sch
hw/sym/JTAG.sym
hw/sym/adm202.sym
hw/sym/adxl210.sym
hw/sym/bat54c.sym
hw/sym/dac7612.sym
hw/sym/hmc1021.sym
hw/sym/hmc1022.sym
hw/sym/ina118.sym
hw/sym/irf7317.sym
hw/sym/irlml.sym
hw/sym/lm74.sym
hw/sym/lp2980AIM5-3.sym
hw/sym/lp2980AIM5-5.sym
hw/sym/lpc2138.sym
hw/sym/ref195.sym
hw/sym/tps76316.sym
hw/packages/0.125W_resistor
hw/packages/0603
hw/packages/0805
hw/packages/1210
hw/packages/2.5mm_10pin_header
hw/packages/QFP64
hw/packages/adxl210
hw/packages/crystal
hw/packages/hmc1021z
hw/packages/jtag1.27x1
hw/packages/lp2980
hw/packages/tanA
hw/packages/tanC
hw/packages/tp

To all these files the copyright and license notice placed earlier
in this file is applied.

NB most of the gEDA symbols (in hw/sym) and PCB footprints (in hw/packages) were
not originally developped by stribog's author: usually he just slightly corrected
files from gEDA and PCB libraries.
