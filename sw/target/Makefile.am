#this file is generated with m4 from Automake.am.m4
#use ./regen_configure to regenerate all our build scripts
#
#This file is a part of the stribog project
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
dist_pkgdata_DATA=
noinst_PROGRAMS=

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

#expanded "accelex" program definition begins
dist_pkgdata_DATA+=\
 ram_programs/accelex.bin ram_programs/accelex.vectors\
 rom_programs/accelex-rom.bin
noinst_PROGRAMS+=accelex accelex-rom
accelex_sources=$(common_sources)\
 src/accelex.c src/accel.c src/accel.h\
 src/mutex.h\
 src/led.c src/led.h src/pll.c src/pll.h
accelex_SOURCES=$(accelex_sources)
accelex_LDFLAGS=$(AM_LDFLAGS) $(ram_flag)
EXTRA_accelex_SOURCES=$(extra_common_sources)
accelex_DEPENDENCIES=$(ram_ld)
accelex_rom_SOURCES=$(accelex_sources)
accelex_rom_LDFLAGS=$(AM_LDFLAGS) $(rom_flag)
EXTRA_accelex_rom_SOURCES=$(extra_common_sources)
accelex_rom_DEPENDENCIES=$(rom_ld)
ram_programs/accelex.bin: $(accelex_sources)
	$(MAKE) $(AM_MAKEFLAGS) accelex
	$(objcopy_bin) accelex ram_programs/accelex.bin
	chmod a-x ram_programs/accelex.bin
ram_programs/accelex.vectors: $(accelex_sources)
	$(MAKE) $(AM_MAKEFLAGS) accelex
	$(objcopy_vectors) accelex ram_programs/accelex.vectors
	chmod a-x ram_programs/accelex.vectors
rom_programs/accelex-rom.bin: $(accelex_sources)
	$(MAKE) $(AM_MAKEFLAGS) accelex-rom
	$(objcopy_bin) accelex-rom rom_programs/accelex-rom.bin
	chmod a-x rom_programs/accelex-rom.bin
#expanded "accelex" program definition ends

#expanded "adcex" program definition begins
dist_pkgdata_DATA+=\
 ram_programs/adcex.bin ram_programs/adcex.vectors\
 rom_programs/adcex-rom.bin
noinst_PROGRAMS+=adcex adcex-rom
adcex_sources=$(common_sources)\
 src/adcex.c src/adc.c src/adc.h\
 src/dac.c src/dac.h src/mutex.h\
 src/led.c src/led.h src/pll.c src/pll.h
adcex_SOURCES=$(adcex_sources)
adcex_LDFLAGS=$(AM_LDFLAGS) $(ram_flag)
EXTRA_adcex_SOURCES=$(extra_common_sources)
adcex_DEPENDENCIES=$(ram_ld)
adcex_rom_SOURCES=$(adcex_sources)
adcex_rom_LDFLAGS=$(AM_LDFLAGS) $(rom_flag)
EXTRA_adcex_rom_SOURCES=$(extra_common_sources)
adcex_rom_DEPENDENCIES=$(rom_ld)
ram_programs/adcex.bin: $(adcex_sources)
	$(MAKE) $(AM_MAKEFLAGS) adcex
	$(objcopy_bin) adcex ram_programs/adcex.bin
	chmod a-x ram_programs/adcex.bin
ram_programs/adcex.vectors: $(adcex_sources)
	$(MAKE) $(AM_MAKEFLAGS) adcex
	$(objcopy_vectors) adcex ram_programs/adcex.vectors
	chmod a-x ram_programs/adcex.vectors
rom_programs/adcex-rom.bin: $(adcex_sources)
	$(MAKE) $(AM_MAKEFLAGS) adcex-rom
	$(objcopy_bin) adcex-rom rom_programs/adcex-rom.bin
	chmod a-x rom_programs/adcex-rom.bin
#expanded "adcex" program definition ends

#expanded "crcex" program definition begins
dist_pkgdata_DATA+=\
 ram_programs/crcex.bin ram_programs/crcex.vectors\
 rom_programs/crcex-rom.bin
noinst_PROGRAMS+=crcex crcex-rom
crcex_sources=$(common_sources)\
 src/crcex.c src/crc32.c src/crc32.h\
 src/pll.c src/pll.h src/led.c src/led.h
crcex_SOURCES=$(crcex_sources)
crcex_LDFLAGS=$(AM_LDFLAGS) $(ram_flag)
EXTRA_crcex_SOURCES=$(extra_common_sources)
crcex_DEPENDENCIES=$(ram_ld)
crcex_rom_SOURCES=$(crcex_sources)
crcex_rom_LDFLAGS=$(AM_LDFLAGS) $(rom_flag)
EXTRA_crcex_rom_SOURCES=$(extra_common_sources)
crcex_rom_DEPENDENCIES=$(rom_ld)
ram_programs/crcex.bin: $(crcex_sources)
	$(MAKE) $(AM_MAKEFLAGS) crcex
	$(objcopy_bin) crcex ram_programs/crcex.bin
	chmod a-x ram_programs/crcex.bin
ram_programs/crcex.vectors: $(crcex_sources)
	$(MAKE) $(AM_MAKEFLAGS) crcex
	$(objcopy_vectors) crcex ram_programs/crcex.vectors
	chmod a-x ram_programs/crcex.vectors
rom_programs/crcex-rom.bin: $(crcex_sources)
	$(MAKE) $(AM_MAKEFLAGS) crcex-rom
	$(objcopy_bin) crcex-rom rom_programs/crcex-rom.bin
	chmod a-x rom_programs/crcex-rom.bin
#expanded "crcex" program definition ends

#expanded "dacex" program definition begins
dist_pkgdata_DATA+=\
 ram_programs/dacex.bin ram_programs/dacex.vectors\
 rom_programs/dacex-rom.bin
noinst_PROGRAMS+=dacex dacex-rom
dacex_sources=$(common_sources)\
 src/dacex.c src/dac.c src/dac.h\
 src/led.c src/led.h src/pll.c src/pll.h
dacex_SOURCES=$(dacex_sources)
dacex_LDFLAGS=$(AM_LDFLAGS) $(ram_flag)
EXTRA_dacex_SOURCES=$(extra_common_sources)
dacex_DEPENDENCIES=$(ram_ld)
dacex_rom_SOURCES=$(dacex_sources)
dacex_rom_LDFLAGS=$(AM_LDFLAGS) $(rom_flag)
EXTRA_dacex_rom_SOURCES=$(extra_common_sources)
dacex_rom_DEPENDENCIES=$(rom_ld)
ram_programs/dacex.bin: $(dacex_sources)
	$(MAKE) $(AM_MAKEFLAGS) dacex
	$(objcopy_bin) dacex ram_programs/dacex.bin
	chmod a-x ram_programs/dacex.bin
ram_programs/dacex.vectors: $(dacex_sources)
	$(MAKE) $(AM_MAKEFLAGS) dacex
	$(objcopy_vectors) dacex ram_programs/dacex.vectors
	chmod a-x ram_programs/dacex.vectors
rom_programs/dacex-rom.bin: $(dacex_sources)
	$(MAKE) $(AM_MAKEFLAGS) dacex-rom
	$(objcopy_bin) dacex-rom rom_programs/dacex-rom.bin
	chmod a-x rom_programs/dacex-rom.bin
#expanded "dacex" program definition ends

#expanded "inledex" program definition begins
dist_pkgdata_DATA+=\
 ram_programs/inledex.bin ram_programs/inledex.vectors\
 rom_programs/inledex-rom.bin
noinst_PROGRAMS+=inledex inledex-rom
inledex_sources=$(common_sources)\
 src/inledex.c src/pll.c src/pll.h
inledex_SOURCES=$(inledex_sources)
inledex_LDFLAGS=$(AM_LDFLAGS) $(ram_flag)
EXTRA_inledex_SOURCES=$(extra_common_sources)
inledex_DEPENDENCIES=$(ram_ld)
inledex_rom_SOURCES=$(inledex_sources)
inledex_rom_LDFLAGS=$(AM_LDFLAGS) $(rom_flag)
EXTRA_inledex_rom_SOURCES=$(extra_common_sources)
inledex_rom_DEPENDENCIES=$(rom_ld)
ram_programs/inledex.bin: $(inledex_sources)
	$(MAKE) $(AM_MAKEFLAGS) inledex
	$(objcopy_bin) inledex ram_programs/inledex.bin
	chmod a-x ram_programs/inledex.bin
ram_programs/inledex.vectors: $(inledex_sources)
	$(MAKE) $(AM_MAKEFLAGS) inledex
	$(objcopy_vectors) inledex ram_programs/inledex.vectors
	chmod a-x ram_programs/inledex.vectors
rom_programs/inledex-rom.bin: $(inledex_sources)
	$(MAKE) $(AM_MAKEFLAGS) inledex-rom
	$(objcopy_bin) inledex-rom rom_programs/inledex-rom.bin
	chmod a-x rom_programs/inledex-rom.bin
#expanded "inledex" program definition ends

#expanded "ledex" program definition begins
dist_pkgdata_DATA+=\
 ram_programs/ledex.bin ram_programs/ledex.vectors\
 rom_programs/ledex-rom.bin
noinst_PROGRAMS+=ledex ledex-rom
ledex_sources=$(common_sources)\
 src/ledex.c src/led.c src/led.h
ledex_SOURCES=$(ledex_sources)
ledex_LDFLAGS=$(AM_LDFLAGS) $(ram_flag)
EXTRA_ledex_SOURCES=$(extra_common_sources)
ledex_DEPENDENCIES=$(ram_ld)
ledex_rom_SOURCES=$(ledex_sources)
ledex_rom_LDFLAGS=$(AM_LDFLAGS) $(rom_flag)
EXTRA_ledex_rom_SOURCES=$(extra_common_sources)
ledex_rom_DEPENDENCIES=$(rom_ld)
ram_programs/ledex.bin: $(ledex_sources)
	$(MAKE) $(AM_MAKEFLAGS) ledex
	$(objcopy_bin) ledex ram_programs/ledex.bin
	chmod a-x ram_programs/ledex.bin
ram_programs/ledex.vectors: $(ledex_sources)
	$(MAKE) $(AM_MAKEFLAGS) ledex
	$(objcopy_vectors) ledex ram_programs/ledex.vectors
	chmod a-x ram_programs/ledex.vectors
rom_programs/ledex-rom.bin: $(ledex_sources)
	$(MAKE) $(AM_MAKEFLAGS) ledex-rom
	$(objcopy_bin) ledex-rom rom_programs/ledex-rom.bin
	chmod a-x rom_programs/ledex-rom.bin
#expanded "ledex" program definition ends

#expanded "lm74ex" program definition begins
dist_pkgdata_DATA+=\
 ram_programs/lm74ex.bin ram_programs/lm74ex.vectors\
 rom_programs/lm74ex-rom.bin
noinst_PROGRAMS+=lm74ex lm74ex-rom
lm74ex_sources=$(common_sources)\
 src/lm74ex.c src/lm74.c src/lm74.h src/mutex.h\
 src/tempus.c src/tempus.h\
 src/pll.c src/pll.h src/led.c src/led.h
lm74ex_SOURCES=$(lm74ex_sources)
lm74ex_LDFLAGS=$(AM_LDFLAGS) $(ram_flag)
EXTRA_lm74ex_SOURCES=$(extra_common_sources)
lm74ex_DEPENDENCIES=$(ram_ld)
lm74ex_rom_SOURCES=$(lm74ex_sources)
lm74ex_rom_LDFLAGS=$(AM_LDFLAGS) $(rom_flag)
EXTRA_lm74ex_rom_SOURCES=$(extra_common_sources)
lm74ex_rom_DEPENDENCIES=$(rom_ld)
ram_programs/lm74ex.bin: $(lm74ex_sources)
	$(MAKE) $(AM_MAKEFLAGS) lm74ex
	$(objcopy_bin) lm74ex ram_programs/lm74ex.bin
	chmod a-x ram_programs/lm74ex.bin
ram_programs/lm74ex.vectors: $(lm74ex_sources)
	$(MAKE) $(AM_MAKEFLAGS) lm74ex
	$(objcopy_vectors) lm74ex ram_programs/lm74ex.vectors
	chmod a-x ram_programs/lm74ex.vectors
rom_programs/lm74ex-rom.bin: $(lm74ex_sources)
	$(MAKE) $(AM_MAKEFLAGS) lm74ex-rom
	$(objcopy_bin) lm74ex-rom rom_programs/lm74ex-rom.bin
	chmod a-x rom_programs/lm74ex-rom.bin
#expanded "lm74ex" program definition ends

#expanded "magex" program definition begins
dist_pkgdata_DATA+=\
 ram_programs/magex.bin ram_programs/magex.vectors\
 rom_programs/magex-rom.bin
noinst_PROGRAMS+=magex magex-rom
magex_sources=$(common_sources)\
 src/magex.c src/mag.c src/mag.h\
 src/adc.c src/adc.h src/dac.c src/dac.h\
 src/mutex.h src/uart.config.h src/freq.h\
 src/uart0.c src/uart0.h src/uart1out.c src/uart1out.h\
 src/tempus.c src/tempus.h\
 src/led.c src/led.h src/pll.c src/pll.h
magex_SOURCES=$(magex_sources)
magex_LDFLAGS=$(AM_LDFLAGS) $(ram_flag)
EXTRA_magex_SOURCES=$(extra_common_sources)
magex_DEPENDENCIES=$(ram_ld)
magex_rom_SOURCES=$(magex_sources)
magex_rom_LDFLAGS=$(AM_LDFLAGS) $(rom_flag)
EXTRA_magex_rom_SOURCES=$(extra_common_sources)
magex_rom_DEPENDENCIES=$(rom_ld)
ram_programs/magex.bin: $(magex_sources)
	$(MAKE) $(AM_MAKEFLAGS) magex
	$(objcopy_bin) magex ram_programs/magex.bin
	chmod a-x ram_programs/magex.bin
ram_programs/magex.vectors: $(magex_sources)
	$(MAKE) $(AM_MAKEFLAGS) magex
	$(objcopy_vectors) magex ram_programs/magex.vectors
	chmod a-x ram_programs/magex.vectors
rom_programs/magex-rom.bin: $(magex_sources)
	$(MAKE) $(AM_MAKEFLAGS) magex-rom
	$(objcopy_bin) magex-rom rom_programs/magex-rom.bin
	chmod a-x rom_programs/magex-rom.bin
#expanded "magex" program definition ends

#expanded "mag_response" program definition begins
dist_pkgdata_DATA+=\
 ram_programs/mag_response.bin ram_programs/mag_response.vectors\
 rom_programs/mag_response-rom.bin
noinst_PROGRAMS+=mag_response mag_response-rom
mag_response_sources=$(common_sources)\
 src/mag_response.c\
 src/adc.c src/adc.h src/crc32.c src/crc32.h\
 src/dac.c src/dac.h\
 src/mutex.h src/uart.config.h src/freq.h\
 src/power.c src/power.h\
 src/tempus.c src/tempus.h\
 src/uart1.c src/uart1.h include/form_fix.h\
 src/led.c src/led.h src/pll.c src/pll.h
mag_response_SOURCES=$(mag_response_sources)
mag_response_LDFLAGS=$(AM_LDFLAGS) $(ram_flag)
EXTRA_mag_response_SOURCES=$(extra_common_sources)
mag_response_DEPENDENCIES=$(ram_ld)
mag_response_rom_SOURCES=$(mag_response_sources)
mag_response_rom_LDFLAGS=$(AM_LDFLAGS) $(rom_flag)
EXTRA_mag_response_rom_SOURCES=$(extra_common_sources)
mag_response_rom_DEPENDENCIES=$(rom_ld)
ram_programs/mag_response.bin: $(mag_response_sources)
	$(MAKE) $(AM_MAKEFLAGS) mag_response
	$(objcopy_bin) mag_response ram_programs/mag_response.bin
	chmod a-x ram_programs/mag_response.bin
ram_programs/mag_response.vectors: $(mag_response_sources)
	$(MAKE) $(AM_MAKEFLAGS) mag_response
	$(objcopy_vectors) mag_response ram_programs/mag_response.vectors
	chmod a-x ram_programs/mag_response.vectors
rom_programs/mag_response-rom.bin: $(mag_response_sources)
	$(MAKE) $(AM_MAKEFLAGS) mag_response-rom
	$(objcopy_bin) mag_response-rom rom_programs/mag_response-rom.bin
	chmod a-x rom_programs/mag_response-rom.bin
#expanded "mag_response" program definition ends

#expanded "multa" program definition begins
dist_pkgdata_DATA+=\
 ram_programs/multa.bin ram_programs/multa.vectors\
 rom_programs/multa-rom.bin
noinst_PROGRAMS+=multa multa-rom
multa_sources=$(common_sources)\
 src/multa.c\
 src/accel.c src/accel.h src/adc.c src/adc.h\
 src/crc32.c src/crc32.h src/dac.c src/dac.h\
 src/lm74.c src/lm74.h src/mag.c src/mag.h\
 src/mutex.h src/uart.config.h src/freq.h\
 src/power.c src/power.h src/tempus.c src/tempus.h\
 src/uart0.c src/uart0.h src/uart1.c src/uart1.h include/form_fix.h\
 src/led.c src/led.h src/pll.c src/pll.h
multa_SOURCES=$(multa_sources)
multa_LDFLAGS=$(AM_LDFLAGS) $(ram_flag)
EXTRA_multa_SOURCES=$(extra_common_sources)
multa_DEPENDENCIES=$(ram_ld)
multa_rom_SOURCES=$(multa_sources)
multa_rom_LDFLAGS=$(AM_LDFLAGS) $(rom_flag)
EXTRA_multa_rom_SOURCES=$(extra_common_sources)
multa_rom_DEPENDENCIES=$(rom_ld)
ram_programs/multa.bin: $(multa_sources)
	$(MAKE) $(AM_MAKEFLAGS) multa
	$(objcopy_bin) multa ram_programs/multa.bin
	chmod a-x ram_programs/multa.bin
ram_programs/multa.vectors: $(multa_sources)
	$(MAKE) $(AM_MAKEFLAGS) multa
	$(objcopy_vectors) multa ram_programs/multa.vectors
	chmod a-x ram_programs/multa.vectors
rom_programs/multa-rom.bin: $(multa_sources)
	$(MAKE) $(AM_MAKEFLAGS) multa-rom
	$(objcopy_bin) multa-rom rom_programs/multa-rom.bin
	chmod a-x rom_programs/multa-rom.bin
#expanded "multa" program definition ends

#expanded "pllex" program definition begins
dist_pkgdata_DATA+=\
 ram_programs/pllex.bin ram_programs/pllex.vectors\
 rom_programs/pllex-rom.bin
noinst_PROGRAMS+=pllex pllex-rom
pllex_sources=$(common_sources)\
 src/pllex.c src/pll.c src/pll.h src/led.c src/led.h
pllex_SOURCES=$(pllex_sources)
pllex_LDFLAGS=$(AM_LDFLAGS) $(ram_flag)
EXTRA_pllex_SOURCES=$(extra_common_sources)
pllex_DEPENDENCIES=$(ram_ld)
pllex_rom_SOURCES=$(pllex_sources)
pllex_rom_LDFLAGS=$(AM_LDFLAGS) $(rom_flag)
EXTRA_pllex_rom_SOURCES=$(extra_common_sources)
pllex_rom_DEPENDENCIES=$(rom_ld)
ram_programs/pllex.bin: $(pllex_sources)
	$(MAKE) $(AM_MAKEFLAGS) pllex
	$(objcopy_bin) pllex ram_programs/pllex.bin
	chmod a-x ram_programs/pllex.bin
ram_programs/pllex.vectors: $(pllex_sources)
	$(MAKE) $(AM_MAKEFLAGS) pllex
	$(objcopy_vectors) pllex ram_programs/pllex.vectors
	chmod a-x ram_programs/pllex.vectors
rom_programs/pllex-rom.bin: $(pllex_sources)
	$(MAKE) $(AM_MAKEFLAGS) pllex-rom
	$(objcopy_bin) pllex-rom rom_programs/pllex-rom.bin
	chmod a-x rom_programs/pllex-rom.bin
#expanded "pllex" program definition ends

#expanded "powerex" program definition begins
dist_pkgdata_DATA+=\
 ram_programs/powerex.bin ram_programs/powerex.vectors\
 rom_programs/powerex-rom.bin
noinst_PROGRAMS+=powerex powerex-rom
powerex_sources=$(common_sources)\
 src/powerex.c src/power.c src/power.h
powerex_SOURCES=$(powerex_sources)
powerex_LDFLAGS=$(AM_LDFLAGS) $(ram_flag)
EXTRA_powerex_SOURCES=$(extra_common_sources)
powerex_DEPENDENCIES=$(ram_ld)
powerex_rom_SOURCES=$(powerex_sources)
powerex_rom_LDFLAGS=$(AM_LDFLAGS) $(rom_flag)
EXTRA_powerex_rom_SOURCES=$(extra_common_sources)
powerex_rom_DEPENDENCIES=$(rom_ld)
ram_programs/powerex.bin: $(powerex_sources)
	$(MAKE) $(AM_MAKEFLAGS) powerex
	$(objcopy_bin) powerex ram_programs/powerex.bin
	chmod a-x ram_programs/powerex.bin
ram_programs/powerex.vectors: $(powerex_sources)
	$(MAKE) $(AM_MAKEFLAGS) powerex
	$(objcopy_vectors) powerex ram_programs/powerex.vectors
	chmod a-x ram_programs/powerex.vectors
rom_programs/powerex-rom.bin: $(powerex_sources)
	$(MAKE) $(AM_MAKEFLAGS) powerex-rom
	$(objcopy_bin) powerex-rom rom_programs/powerex-rom.bin
	chmod a-x rom_programs/powerex-rom.bin
#expanded "powerex" program definition ends

#expanded "uart1ex" program definition begins
dist_pkgdata_DATA+=\
 ram_programs/uart1ex.bin ram_programs/uart1ex.vectors\
 rom_programs/uart1ex-rom.bin
noinst_PROGRAMS+=uart1ex uart1ex-rom
uart1ex_sources=$(common_sources)\
 src/uart1ex.c\
 src/crc32.c src/crc32.h src/dac.c src/dac.h\
 src/lm74.c src/lm74.h src/mag.c src/mag.h\
 src/mutex.h src/uart.config.h src/freq.h\
 src/power.c src/power.h src/tempus.c src/tempus.h\
 src/uart1.c src/uart1.h include/form_fix.h\
 src/led.c src/led.h src/pll.c src/pll.h
uart1ex_SOURCES=$(uart1ex_sources)
uart1ex_LDFLAGS=$(AM_LDFLAGS) $(ram_flag)
EXTRA_uart1ex_SOURCES=$(extra_common_sources)
uart1ex_DEPENDENCIES=$(ram_ld)
uart1ex_rom_SOURCES=$(uart1ex_sources)
uart1ex_rom_LDFLAGS=$(AM_LDFLAGS) $(rom_flag)
EXTRA_uart1ex_rom_SOURCES=$(extra_common_sources)
uart1ex_rom_DEPENDENCIES=$(rom_ld)
ram_programs/uart1ex.bin: $(uart1ex_sources)
	$(MAKE) $(AM_MAKEFLAGS) uart1ex
	$(objcopy_bin) uart1ex ram_programs/uart1ex.bin
	chmod a-x ram_programs/uart1ex.bin
ram_programs/uart1ex.vectors: $(uart1ex_sources)
	$(MAKE) $(AM_MAKEFLAGS) uart1ex
	$(objcopy_vectors) uart1ex ram_programs/uart1ex.vectors
	chmod a-x ram_programs/uart1ex.vectors
rom_programs/uart1ex-rom.bin: $(uart1ex_sources)
	$(MAKE) $(AM_MAKEFLAGS) uart1ex-rom
	$(objcopy_bin) uart1ex-rom rom_programs/uart1ex-rom.bin
	chmod a-x rom_programs/uart1ex-rom.bin
#expanded "uart1ex" program definition ends

#expanded "tempusex" program definition begins
dist_pkgdata_DATA+=\
 ram_programs/tempusex.bin ram_programs/tempusex.vectors\
 rom_programs/tempusex-rom.bin
noinst_PROGRAMS+=tempusex tempusex-rom
tempusex_sources=$(common_sources)\
 src/tempusex.c src/mutex.h\
 src/pll.c src/pll.h src/led.c src/led.h
tempusex_SOURCES=$(tempusex_sources)
tempusex_LDFLAGS=$(AM_LDFLAGS) $(ram_flag)
EXTRA_tempusex_SOURCES=$(extra_common_sources)
tempusex_DEPENDENCIES=$(ram_ld)
tempusex_rom_SOURCES=$(tempusex_sources)
tempusex_rom_LDFLAGS=$(AM_LDFLAGS) $(rom_flag)
EXTRA_tempusex_rom_SOURCES=$(extra_common_sources)
tempusex_rom_DEPENDENCIES=$(rom_ld)
ram_programs/tempusex.bin: $(tempusex_sources)
	$(MAKE) $(AM_MAKEFLAGS) tempusex
	$(objcopy_bin) tempusex ram_programs/tempusex.bin
	chmod a-x ram_programs/tempusex.bin
ram_programs/tempusex.vectors: $(tempusex_sources)
	$(MAKE) $(AM_MAKEFLAGS) tempusex
	$(objcopy_vectors) tempusex ram_programs/tempusex.vectors
	chmod a-x ram_programs/tempusex.vectors
rom_programs/tempusex-rom.bin: $(tempusex_sources)
	$(MAKE) $(AM_MAKEFLAGS) tempusex-rom
	$(objcopy_bin) tempusex-rom rom_programs/tempusex-rom.bin
	chmod a-x rom_programs/tempusex-rom.bin
#expanded "tempusex" program definition ends

$(srcdir)/Makefile.am: $(srcdir)/Makefile.am.m4 $(srcdir)/m4/makefile.m4
	m4 -I $(srcdir) $(srcdir)/Makefile.am.m4 > $(srcdir)/Makefile.am
