Stribog the sensing platform README file.
The end of this file contains license and copyright notes for the project.

ATTENTION stribog is in his alpha stage. he is not functional yet.

The project is located at http://savannah.nongnu.org/projects/stribog

SOME TECHNICAL NOTES FOLLOW

This project consists of hardware and software sections. the former is
developed with gEDA, the latter with GNU toolchains.

Hardware contains a 3-axis {magnetoresistive compass, accelerometer,
(optionally) gyroscope} and an ARM-based microcontroller to manage all.

Software includes programs for MCU to test and align hardware parts,
to perform the measurements; the software part also has some programs
for POSIX host to receive obtained data.

Stribog is primarily designed on LPC2138, but actually LPC213[46] can be used,
too. the only change will be in ld scripts (2138.ld and ram2138.ld), as shown 
in comments there.

The board will be programmed via serial port using bootstrap loader.
you can use any existing one (on Unix live 
lpc_host_tools by Holly Gates <hgates@eink.com>, 
lpc21isp by Martin Maurer <Martin.Maurer@clibb.de> 
 and Aeolus Development http://aeolusdevelopment.com
lpc2k_pgm by Paul Stoffregen (http://www.pjrc.com/arm/lpc2k_pgm)

on Windows they have Philips flash ISP utility)

If you use them, you'll have to adjust input files format (.hex, .srec 
and so on) with arm-elf-objcopy(1).

I wrote my own host tools (see sw/host/*) because
 1) some of those programs (like lpc21isp) lack clear terms of use,
 2) other (like Philips utility) are neither free nor capable to run 
    on a free OS,
 3) some (like lpc2k_pgm) have graphic user interface and I don't like this,
 4) I wouldn't add external dependencies when possible.

My tools are hardly functional, but they work somehow for me and they are free.

There are two linker scripts in sw/target/src directory: ram2138.ld and
2138.ld. the former is currently used (the program is to be just loaded into RAM
and run), the latter was tested some time ago and will be corrected again when 
stribog needs to keep his program in ROM.

The program is written in C (the ld scripts don't support C++). 
main() is executed in supervisor mode. no THUMB code. fast interrupt reserved. 
VPB divider equals 4, as by default. PLL is configured to multiply by 4.

The program will run from RAM, when possible. even when written in ROM, boot.s
will copy it to RAM. the program uses single library: libgcc.a. 
all computations should be in fixed point.

Busy VIC slots: 3 (UART0), 4 (UART1), 5 (timer1), 6 and 7 (ADC), 8 (timer0)

Time functions (tempus.h) are based on timer1. it uses VIC vectored interrupt
slot 5. this module receives PPS at CAP1.2 (signal A), too.

UART0 is the auxiliary port to get GPS data; uses VIC slot 3

UART1 is the basic port; uses VIC slot 4

ADC use VIC slots 6 and 7; magnetic module functions used in such way
(see magex.c, multa.c) that ADC sampling frequency defines frequency of
set/reset pulses. this frequency is adjusted to be an integer of 50 Hz.

Magnetoresistive sensors work not so far from the absolute maximum value 
for set/reset strap duty cycle. carelessly increasing the sampling frequency 
can DAMAGE the sensors.

Timer0 is occupied by accelerometers; VIC slot 8

HOW TO INSTALL DEVELOPMENT TOOLS

First, we shall need binutils and gcc for ARM. we go to http://www.gnu.org and
get binutils and gcc. generally, we use the latest releases, though there is 
nothing dependent on any supernew features in stribog. currently we use 
binutils-2.17 with gcc-4.1.2. we used also
binutils-2.16.1, binutils-2.16, gcc-3.4.6, gcc-4.0.1, gcc-4.0.3, gcc-4.1.1.
they should work, too. once we tried binutils-2.15 and they failed; maybe,
we had not configured them properly.

Follow (with some changes) instructions from http://www.gnuarm.com
($ is for our shell prompt)
$ export armprefix=$HOME/arm
                   (or where you want them to live. you must have write access
		    thither)
$ gpg --verify binutils-2.17.tar.bz2.sig && tar xjf binutils-2.17.tar.bz2
$ mkdir bui;cd bui
$ ../binutils-2.17/configure --target=arm-elf --prefix=$armprefix --enable-interwork --enable-multilib
$ make all install
$ export PATH=$PATH:$armprefix/bin; rm -fr *;cd ..
         (add this path in your shell profile after install, too)
$ gpg --verify gcc-4.1.2.tar.bz2.sig && tar xjf gcc-4.1.2.tar.bz2;cd bui
$ ../gcc-4.1.2/configure --target=arm-elf --prefix=$armprefix --enable-interwork --enable-multilib --enable-languages=c
$ make all-gcc install-gcc

That's all. we don't need newlib, and stribog main board has no contacts 
to connect with gdb.

This sequence worked on RedHat 7.3 and Fedora Core 4 (32-bit).

It is more difficult to install gEDA and friends. I possibly shall never 
tell about this here.

LICENSE AND COPYRIGHT NOTES FOLLOW

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

    Copyright (C) 2005, 2006, 2007 D.Ineiev <ineiev@yahoo.co.uk>

Note: actually the next version of the GPL is to be released this summer. 
stribog's author has strong intention to use this new version since then. 
currently, stribog is distributed by D.Ineiev under the terms of 
the GNU GPL v2.

It is not certain, whether a printed board contains a "derived" from
the sources "work". stribog's author believes that a PCB layout files 
(as hw/main_board.pcb) do form a derived work, but the result of PCB print 
command (GERBER/EXCELLON, PostScript files) contains no "derived work", to say 
nothing of printed boards and assembled devices. that is, this license does 
not restrict any use of these items. neither does the copyright holder.

Nonetheless, any schematic diagram in any form does contain such a "work".

This may look inconsistent, this can be argued, but the author considers this
approach to be the most correct one. the copyright holder may change this 
point of view in future to make it more consistent, but for no files released
earlier.

The software part is released right under the terms of the GNU GPL v2.

The following non-text source files possibly contain no copyright notices, 
because stribog's author decided to move those notices here for convenience, 
namely:

hw/main_board.pcb hw/main_board.bis.pcb hw/stribog.sch hw/gyro.sch
hw/sym/JTAG.sym hw/sym/adm202.sym hw/sym/adxl210.sym
hw/sym/adxrs300.sym hw/sym/bat54c.sym hw/sym/dac7612.sym
hw/sym/hmc1021.sym hw/sym/hmc1022.sym hw/sym/ina118.sym
hw/sym/irf7317.sym hw/sym/irf7507.sym hw/sym/irlml.sym hw/sym/lm74.sym
hw/sym/lp2980AIM5-3.sym hw/sym/lp2980AIM5-5.sym hw/sym/lpc2138.sym
hw/sym/ref195.sym hw/sym/tps76316.sym hw/packages/0.125W_resistor
hw/packages/0603 hw/packages/0805 hw/packages/1210
hw/packages/2.5mm_10pin_header hw/packages/QFP64 hw/packages/adxl210
hw/packages/crystal hw/packages/hmc1021z hw/packages/jtag1.27x1
hw/packages/lp2980 hw/packages/pin hw/packages/tanA hw/packages/tanC
hw/packages/tp

To all these files is applied the copyright and license notice placed earlier
in this file.

NB most of the gEDA symbols (in hw/sym) and PCB footprints (in hw/packages) were
not originally developped by stribog's author: usually he just slightly 
corrected files from gEDA and PCB libraries.
