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
OBJCOPY=arm-elf-objcopy
objcopy_bin=$(OBJCOPY) -I elf32-littlearm -O binary -R startup
objcopy_vectors=$(OBJCOPY)\
 --set-section-flags vectors=contents,alloc,load,readonly,code\
 -j vectors -I elf32-littlearm -O binary
common_sources=include/lpc2138.h
ram_ld=src/ram2138.ld
ram_ldscript=$(srcdir)/$(ram_ld)
rom_ld=src/2138.ld
rom_ldscript=$(srcdir)/$(rom_ld)
if arm_elf_tools
if add_own_atexit
 common_sources+=lib/atexit.c
endif
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
 AM_LIBS=$(libgcc)
 ram_flag=-T$(ram_ldscript)
 rom_flag=-T$(rom_ldscript)
endif
extra_common_sources=lib/atexit.c lib/mutex.h src/boot.s
EXTRA_DIST=lib/fake-cc src/mutex.c\
 Makefile.am.m4 m4/makefile.m4 $(rom_ld) $(ram_ld)
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
