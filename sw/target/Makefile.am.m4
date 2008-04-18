divert(-1)
#stribog target tools: Makefile.am.m4
#use autoreconf and build then to regenerate the sources configuration system
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
OBJCOPY=$(arm_unknown_elf_objcopy)
objcopy_bin=$(OBJCOPY) -I elf32-littlearm -O binary -R startup
objcopy_vectors=$(OBJCOPY)\
 --set-section-flags vectors=contents,alloc,load,readonly,code\
 -j vectors -I elf32-littlearm -O binary
common_sources=include/lpc2138.h src/boot.s
#atexit.c is needed for gcc-2.95.3
 common_sources+=lib/atexit.c
 AM_CFLAGS=$(arm_ascc_flags) -Wall -O2
 AM_ASFLAGS=$(arm_as_flags)
 AM_CPPFLAGS=-I$(srcdir)/src
 AM_LDFLAGS=-Wl,-Map,$@.map -nostdlib -static
AM_LIBS=-lgcc
ram_flag=-T./ram2138.ld
rom_flag=-T./2138.ld
extra_common_sources=lib/atexit.c
EXTRA_DIST=src/ram2138.ld.in src/2138.ld.in src/mutex.c\
 Makefile.am.m4 m4/makefile.m4 subst_ldscript
divert(-1)
 ST_TARGET(`program_name', `program_sources', `extra_dependencies')
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
ST_EXTRA_TARGET(`magex',
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
 src/uart1.c src/uart1.h\
 src/led.c src/led.h src/pll.c src/pll.h',
 `../common/form_fix.h')
ST_EXTRA_TARGET(`multa',
`src/multa.c\
 src/accel.c src/accel.h src/adc.c src/adc.h\
 src/crc32.c src/crc32.h src/dac.c src/dac.h\
 src/lm74.c src/lm74.h src/mag.c src/mag.h\
 src/mutex.h src/uart.config.h src/freq.h\
 src/power.c src/power.h src/tempus.c src/tempus.h\
 src/uart0.c src/uart0.h src/uart1.c src/uart1.h\
 src/led.c src/led.h src/pll.c src/pll.h',
 `../common/form_fix.h')
ST_TARGET(`pllex',
`src/pllex.c src/pll.c src/pll.h src/led.c src/led.h')
ST_TARGET(`powerex',`src/powerex.c src/power.c src/power.h')
ST_TARGET(`uart1ex',
`src/uart1ex.c\
 src/crc32.c src/crc32.h src/dac.c src/dac.h\
 src/lm74.c src/lm74.h src/mag.c src/mag.h\
 src/mutex.h src/uart.config.h src/freq.h\
 src/power.c src/power.h src/tempus.c src/tempus.h\
 src/uart1.c src/uart1.h\
 src/led.c src/led.h src/pll.c src/pll.h',
 `../common/form_fix.h')
ST_TARGET(`tempusex',
`src/tempusex.c src/mutex.h\
 src/pll.c src/pll.h src/led.c src/led.h')
#TODO: check whether make accepts %-style rules
#and include the next rule conditionally
%.s: $(srcdir)/src/%.c
	$(COMPILE) -S -o $@ $<
$(srcdir)/Makefile.am: $(srcdir)/Makefile.am.m4 $(srcdir)/m4/makefile.m4
	m4 -I $(srcdir) $(srcdir)/Makefile.am.m4 > $(srcdir)/Makefile.am
nodist_pkgdata_DATA+=summary ram2138.ld 2138.ld config.h
dist-hook:
	$(RM) $(nodist_rom_programs_DATA) $(nodist_ram_programs_DATA)\
 $(nodist_pkgdata_DATA)
ram2138.ld: $(srcdir)/src/ram2138.ld.in $(srcdir)/subst_ldscript
	$(srcdir)/subst_ldscript RAM $(mcu_conf) \
 < $(srcdir)/src/ram2138.ld.in > ram2138.ld
2138.ld: $(srcdir)/src/2138.ld.in $(srcdir)/subst_ldscript
	$(srcdir)/subst_ldscript ROM $(mcu_conf) \
 < $(srcdir)/src/2138.ld.in > 2138.ld
