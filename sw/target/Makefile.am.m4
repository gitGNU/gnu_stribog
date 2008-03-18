divert(-1)
#stribog target tools: Makefile.am.m4
#use ./regen_configure to regenerate the sources configuration system
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
include(`m4/makefile.m4')
OBJCOPY=arm-unknown-elf-objcopy
objcopy_bin=$(OBJCOPY) -I elf32-littlearm -O binary -R startup
objcopy_vectors=$(OBJCOPY)\
 --set-section-flags vectors=contents,alloc,load,readonly,code\
 -j vectors -I elf32-littlearm -O binary
common_sources=include/lpc2138.h
 common_sources+=lib/atexit.c
#ifndef MCU_UNOFFENDED
#TODO make this work
#  PPS_BURNT=1
#endif
 AM_CFLAGS=-mcpu=arm7tdmi -Wall -O2
 AM_CPPFLAGS=-I$(srcdir)/src
#if PPS_BURNT
#  AM_CFLAGS+=-DPPS_BURNT=1
#endif
 common_sources+=src/boot.s
 AM_LDFLAGS=-Wl,-Map,$@.map -nostdlib -static
AM_LIBS=-lgcc
ram_flag=-T./ram2138.ld
rom_flag=-T./2138.ld
extra_common_sources=lib/atexit.c lib/mutex.h src/boot.s
EXTRA_DIST=src/ram2138.ld.in src/2138.ld.in src/mutex.c\
 Makefile.am.m4 m4/makefile.m4
divert(-1)
 ST_TARGET(`name_of_program', `program_sources')
 It expands into a sequence of automake commands that define 
 this target program. 
divert`'dnl
ST_TARGET(`accelex',
`src/accelex.c src/accel.c src/accel.h\
 src/mutex.h\
 src/led.c src/led.h src/pll.c src/pll.h')
ST_TARGET(`adcex',
`src/adcex.c src/adc.c src/adc.h\
 src/dac.c src/dac.h src/mutex.h\
 src/led.c src/led.h src/pll.c src/pll.h')
ST_TARGET(`crcex',
`src/crcex.c src/crc32.c src/crc32.h\
 src/pll.c src/pll.h src/led.c src/led.h')
ST_TARGET(`dacex',
`src/dacex.c src/dac.c src/dac.h\
 src/led.c src/led.h src/pll.c src/pll.h')
ST_TARGET(`inledex',`src/inledex.c src/pll.c src/pll.h')
ST_TARGET(`ledex',`src/ledex.c src/led.c src/led.h')
ST_TARGET(`lm74ex',
`src/lm74ex.c src/lm74.c src/lm74.h src/mutex.h\
 src/tempus.c src/tempus.h\
 src/pll.c src/pll.h src/led.c src/led.h')
ST_TARGET(`magex',
`src/magex.c src/mag.c src/mag.h\
 src/adc.c src/adc.h src/dac.c src/dac.h\
 src/mutex.h src/uart.config.h src/freq.h\
 src/uart0.c src/uart0.h src/uart1out.c src/uart1out.h\
 src/tempus.c src/tempus.h\
 src/led.c src/led.h src/pll.c src/pll.h')
ST_TARGET(`mag_response',
`src/mag_response.c\
 src/adc.c src/adc.h src/crc32.c src/crc32.h\
 src/dac.c src/dac.h\
 src/mutex.h src/uart.config.h src/freq.h\
 src/power.c src/power.h\
 src/tempus.c src/tempus.h\
 src/uart1.c src/uart1.h include/form_fix.h\
 src/led.c src/led.h src/pll.c src/pll.h')
ST_TARGET(`multa',
`src/multa.c\
 src/accel.c src/accel.h src/adc.c src/adc.h\
 src/crc32.c src/crc32.h src/dac.c src/dac.h\
 src/lm74.c src/lm74.h src/mag.c src/mag.h\
 src/mutex.h src/uart.config.h src/freq.h\
 src/power.c src/power.h src/tempus.c src/tempus.h\
 src/uart0.c src/uart0.h src/uart1.c src/uart1.h include/form_fix.h\
 src/led.c src/led.h src/pll.c src/pll.h')
ST_TARGET(`pllex',
`src/pllex.c src/pll.c src/pll.h src/led.c src/led.h')
ST_TARGET(`powerex',`src/powerex.c src/power.c src/power.h')
ST_TARGET(`uart1ex',
`src/uart1ex.c\
 src/crc32.c src/crc32.h src/dac.c src/dac.h\
 src/lm74.c src/lm74.h src/mag.c src/mag.h\
 src/mutex.h src/uart.config.h src/freq.h\
 src/power.c src/power.h src/tempus.c src/tempus.h\
 src/uart1.c src/uart1.h include/form_fix.h\
 src/led.c src/led.h src/pll.c src/pll.h')
ST_TARGET(`tempusex',
`src/tempusex.c src/mutex.h\
 src/pll.c src/pll.h src/led.c src/led.h')

$(srcdir)/Makefile.am: $(srcdir)/Makefile.am.m4 $(srcdir)/m4/makefile.m4
	m4 -I $(srcdir) $(srcdir)/Makefile.am.m4 > $(srcdir)/Makefile.am
nodist_pkgdata_DATA+=summary ram2138.ld 2138.ld
dist-hook:
	$(RM) $(nodist_pkgdata_DATA)
ram2138.ld: $(srcdir)/src/ram2138.ld.in
	@echo NOTE: ram2138.ld is generated from src/ram2138.ld.in during configuration.
	@echo NOTE: your 'make' decided that ram2138.ld.in is newer, so ram2138.ld
	@echo NOTE: must be regenerated. this currently can be done via configure script
	@echo NOTE: run only. 
	@echo NOTE: Please configure the package again. if you really don't want
	@echo NOTE: to regenerate ram2138.ld, touch it. 
	exit 1
2138.ld: $(srcdir)/src/2138.ld.in
	@echo NOTE: 2138.ld is generated from src/2138.ld.in during configuration.
	@echo NOTE: your 'make' decided that 2138.ld.in is newer, so 2138.ld
	@echo NOTE: must be regenerated. this currently can be done via configure script
	@echo NOTE: run only.
	@echo NOTE: Please configure the package again. if you really don't want
	@echo NOTE: to regenerate 2138.ld, touch it. 
	exit 1;
