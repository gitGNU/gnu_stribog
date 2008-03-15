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
nodist_pkgdata_DATA=
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
 AM_LIBS=$(libgcc)
 ram_flag=-T$(ram_ldscript)
 rom_flag=-T$(rom_ldscript)
extra_common_sources=lib/atexit.c lib/mutex.h src/boot.s
EXTRA_DIST=lib/fake-cc src/mutex.c\
 Makefile.am.m4 m4/makefile.m4 $(rom_ld) $(ram_ld)

#expanded "accelex" program definition begins
nodist_pkgdata_DATA+=\
 ram_programs/accelex.bin ram_programs/accelex.vectors accelex.map\
 rom_programs/accelex-rom.bin accelex-rom.map
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
ram_programs/accelex.map: $(accelex_sources)
	$(MAKE) $(AM_MAKEFLAGS) accelex
ram_programs/accelex.vectors: $(accelex_sources)
	$(MAKE) $(AM_MAKEFLAGS) accelex
	$(objcopy_vectors) accelex ram_programs/accelex.vectors
rom_programs/accelex-rom.bin: $(accelex_sources)
	$(MAKE) $(AM_MAKEFLAGS) accelex-rom
	$(objcopy_bin) accelex-rom rom_programs/accelex-rom.bin
rom_programs/accelex-rom.map: $(accelex_sources)
	$(MAKE) $(AM_MAKEFLAGS) accelex
#expanded "accelex" program definition ends

#expanded "adcex" program definition begins
nodist_pkgdata_DATA+=\
 ram_programs/adcex.bin ram_programs/adcex.vectors adcex.map\
 rom_programs/adcex-rom.bin adcex-rom.map
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
ram_programs/adcex.map: $(adcex_sources)
	$(MAKE) $(AM_MAKEFLAGS) adcex
ram_programs/adcex.vectors: $(adcex_sources)
	$(MAKE) $(AM_MAKEFLAGS) adcex
	$(objcopy_vectors) adcex ram_programs/adcex.vectors
rom_programs/adcex-rom.bin: $(adcex_sources)
	$(MAKE) $(AM_MAKEFLAGS) adcex-rom
	$(objcopy_bin) adcex-rom rom_programs/adcex-rom.bin
rom_programs/adcex-rom.map: $(adcex_sources)
	$(MAKE) $(AM_MAKEFLAGS) adcex
#expanded "adcex" program definition ends

#expanded "crcex" program definition begins
nodist_pkgdata_DATA+=\
 ram_programs/crcex.bin ram_programs/crcex.vectors crcex.map\
 rom_programs/crcex-rom.bin crcex-rom.map
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
ram_programs/crcex.map: $(crcex_sources)
	$(MAKE) $(AM_MAKEFLAGS) crcex
ram_programs/crcex.vectors: $(crcex_sources)
	$(MAKE) $(AM_MAKEFLAGS) crcex
	$(objcopy_vectors) crcex ram_programs/crcex.vectors
rom_programs/crcex-rom.bin: $(crcex_sources)
	$(MAKE) $(AM_MAKEFLAGS) crcex-rom
	$(objcopy_bin) crcex-rom rom_programs/crcex-rom.bin
rom_programs/crcex-rom.map: $(crcex_sources)
	$(MAKE) $(AM_MAKEFLAGS) crcex
#expanded "crcex" program definition ends

#expanded "dacex" program definition begins
nodist_pkgdata_DATA+=\
 ram_programs/dacex.bin ram_programs/dacex.vectors dacex.map\
 rom_programs/dacex-rom.bin dacex-rom.map
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
ram_programs/dacex.map: $(dacex_sources)
	$(MAKE) $(AM_MAKEFLAGS) dacex
ram_programs/dacex.vectors: $(dacex_sources)
	$(MAKE) $(AM_MAKEFLAGS) dacex
	$(objcopy_vectors) dacex ram_programs/dacex.vectors
rom_programs/dacex-rom.bin: $(dacex_sources)
	$(MAKE) $(AM_MAKEFLAGS) dacex-rom
	$(objcopy_bin) dacex-rom rom_programs/dacex-rom.bin
rom_programs/dacex-rom.map: $(dacex_sources)
	$(MAKE) $(AM_MAKEFLAGS) dacex
#expanded "dacex" program definition ends

#expanded "inledex" program definition begins
nodist_pkgdata_DATA+=\
 ram_programs/inledex.bin ram_programs/inledex.vectors inledex.map\
 rom_programs/inledex-rom.bin inledex-rom.map
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
ram_programs/inledex.map: $(inledex_sources)
	$(MAKE) $(AM_MAKEFLAGS) inledex
ram_programs/inledex.vectors: $(inledex_sources)
	$(MAKE) $(AM_MAKEFLAGS) inledex
	$(objcopy_vectors) inledex ram_programs/inledex.vectors
rom_programs/inledex-rom.bin: $(inledex_sources)
	$(MAKE) $(AM_MAKEFLAGS) inledex-rom
	$(objcopy_bin) inledex-rom rom_programs/inledex-rom.bin
rom_programs/inledex-rom.map: $(inledex_sources)
	$(MAKE) $(AM_MAKEFLAGS) inledex
#expanded "inledex" program definition ends

#expanded "ledex" program definition begins
nodist_pkgdata_DATA+=\
 ram_programs/ledex.bin ram_programs/ledex.vectors ledex.map\
 rom_programs/ledex-rom.bin ledex-rom.map
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
ram_programs/ledex.map: $(ledex_sources)
	$(MAKE) $(AM_MAKEFLAGS) ledex
ram_programs/ledex.vectors: $(ledex_sources)
	$(MAKE) $(AM_MAKEFLAGS) ledex
	$(objcopy_vectors) ledex ram_programs/ledex.vectors
rom_programs/ledex-rom.bin: $(ledex_sources)
	$(MAKE) $(AM_MAKEFLAGS) ledex-rom
	$(objcopy_bin) ledex-rom rom_programs/ledex-rom.bin
rom_programs/ledex-rom.map: $(ledex_sources)
	$(MAKE) $(AM_MAKEFLAGS) ledex
#expanded "ledex" program definition ends

#expanded "lm74ex" program definition begins
nodist_pkgdata_DATA+=\
 ram_programs/lm74ex.bin ram_programs/lm74ex.vectors lm74ex.map\
 rom_programs/lm74ex-rom.bin lm74ex-rom.map
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
ram_programs/lm74ex.map: $(lm74ex_sources)
	$(MAKE) $(AM_MAKEFLAGS) lm74ex
ram_programs/lm74ex.vectors: $(lm74ex_sources)
	$(MAKE) $(AM_MAKEFLAGS) lm74ex
	$(objcopy_vectors) lm74ex ram_programs/lm74ex.vectors
rom_programs/lm74ex-rom.bin: $(lm74ex_sources)
	$(MAKE) $(AM_MAKEFLAGS) lm74ex-rom
	$(objcopy_bin) lm74ex-rom rom_programs/lm74ex-rom.bin
rom_programs/lm74ex-rom.map: $(lm74ex_sources)
	$(MAKE) $(AM_MAKEFLAGS) lm74ex
#expanded "lm74ex" program definition ends

#expanded "magex" program definition begins
nodist_pkgdata_DATA+=\
 ram_programs/magex.bin ram_programs/magex.vectors magex.map\
 rom_programs/magex-rom.bin magex-rom.map
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
ram_programs/magex.map: $(magex_sources)
	$(MAKE) $(AM_MAKEFLAGS) magex
ram_programs/magex.vectors: $(magex_sources)
	$(MAKE) $(AM_MAKEFLAGS) magex
	$(objcopy_vectors) magex ram_programs/magex.vectors
rom_programs/magex-rom.bin: $(magex_sources)
	$(MAKE) $(AM_MAKEFLAGS) magex-rom
	$(objcopy_bin) magex-rom rom_programs/magex-rom.bin
rom_programs/magex-rom.map: $(magex_sources)
	$(MAKE) $(AM_MAKEFLAGS) magex
#expanded "magex" program definition ends

#expanded "mag_response" program definition begins
nodist_pkgdata_DATA+=\
 ram_programs/mag_response.bin ram_programs/mag_response.vectors mag_response.map\
 rom_programs/mag_response-rom.bin mag_response-rom.map
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
ram_programs/mag_response.map: $(mag_response_sources)
	$(MAKE) $(AM_MAKEFLAGS) mag_response
ram_programs/mag_response.vectors: $(mag_response_sources)
	$(MAKE) $(AM_MAKEFLAGS) mag_response
	$(objcopy_vectors) mag_response ram_programs/mag_response.vectors
rom_programs/mag_response-rom.bin: $(mag_response_sources)
	$(MAKE) $(AM_MAKEFLAGS) mag_response-rom
	$(objcopy_bin) mag_response-rom rom_programs/mag_response-rom.bin
rom_programs/mag_response-rom.map: $(mag_response_sources)
	$(MAKE) $(AM_MAKEFLAGS) mag_response
#expanded "mag_response" program definition ends

#expanded "multa" program definition begins
nodist_pkgdata_DATA+=\
 ram_programs/multa.bin ram_programs/multa.vectors multa.map\
 rom_programs/multa-rom.bin multa-rom.map
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
ram_programs/multa.map: $(multa_sources)
	$(MAKE) $(AM_MAKEFLAGS) multa
ram_programs/multa.vectors: $(multa_sources)
	$(MAKE) $(AM_MAKEFLAGS) multa
	$(objcopy_vectors) multa ram_programs/multa.vectors
rom_programs/multa-rom.bin: $(multa_sources)
	$(MAKE) $(AM_MAKEFLAGS) multa-rom
	$(objcopy_bin) multa-rom rom_programs/multa-rom.bin
rom_programs/multa-rom.map: $(multa_sources)
	$(MAKE) $(AM_MAKEFLAGS) multa
#expanded "multa" program definition ends

#expanded "pllex" program definition begins
nodist_pkgdata_DATA+=\
 ram_programs/pllex.bin ram_programs/pllex.vectors pllex.map\
 rom_programs/pllex-rom.bin pllex-rom.map
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
ram_programs/pllex.map: $(pllex_sources)
	$(MAKE) $(AM_MAKEFLAGS) pllex
ram_programs/pllex.vectors: $(pllex_sources)
	$(MAKE) $(AM_MAKEFLAGS) pllex
	$(objcopy_vectors) pllex ram_programs/pllex.vectors
rom_programs/pllex-rom.bin: $(pllex_sources)
	$(MAKE) $(AM_MAKEFLAGS) pllex-rom
	$(objcopy_bin) pllex-rom rom_programs/pllex-rom.bin
rom_programs/pllex-rom.map: $(pllex_sources)
	$(MAKE) $(AM_MAKEFLAGS) pllex
#expanded "pllex" program definition ends

#expanded "powerex" program definition begins
nodist_pkgdata_DATA+=\
 ram_programs/powerex.bin ram_programs/powerex.vectors powerex.map\
 rom_programs/powerex-rom.bin powerex-rom.map
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
ram_programs/powerex.map: $(powerex_sources)
	$(MAKE) $(AM_MAKEFLAGS) powerex
ram_programs/powerex.vectors: $(powerex_sources)
	$(MAKE) $(AM_MAKEFLAGS) powerex
	$(objcopy_vectors) powerex ram_programs/powerex.vectors
rom_programs/powerex-rom.bin: $(powerex_sources)
	$(MAKE) $(AM_MAKEFLAGS) powerex-rom
	$(objcopy_bin) powerex-rom rom_programs/powerex-rom.bin
rom_programs/powerex-rom.map: $(powerex_sources)
	$(MAKE) $(AM_MAKEFLAGS) powerex
#expanded "powerex" program definition ends

#expanded "uart1ex" program definition begins
nodist_pkgdata_DATA+=\
 ram_programs/uart1ex.bin ram_programs/uart1ex.vectors uart1ex.map\
 rom_programs/uart1ex-rom.bin uart1ex-rom.map
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
ram_programs/uart1ex.map: $(uart1ex_sources)
	$(MAKE) $(AM_MAKEFLAGS) uart1ex
ram_programs/uart1ex.vectors: $(uart1ex_sources)
	$(MAKE) $(AM_MAKEFLAGS) uart1ex
	$(objcopy_vectors) uart1ex ram_programs/uart1ex.vectors
rom_programs/uart1ex-rom.bin: $(uart1ex_sources)
	$(MAKE) $(AM_MAKEFLAGS) uart1ex-rom
	$(objcopy_bin) uart1ex-rom rom_programs/uart1ex-rom.bin
rom_programs/uart1ex-rom.map: $(uart1ex_sources)
	$(MAKE) $(AM_MAKEFLAGS) uart1ex
#expanded "uart1ex" program definition ends

#expanded "tempusex" program definition begins
nodist_pkgdata_DATA+=\
 ram_programs/tempusex.bin ram_programs/tempusex.vectors tempusex.map\
 rom_programs/tempusex-rom.bin tempusex-rom.map
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
ram_programs/tempusex.map: $(tempusex_sources)
	$(MAKE) $(AM_MAKEFLAGS) tempusex
ram_programs/tempusex.vectors: $(tempusex_sources)
	$(MAKE) $(AM_MAKEFLAGS) tempusex
	$(objcopy_vectors) tempusex ram_programs/tempusex.vectors
rom_programs/tempusex-rom.bin: $(tempusex_sources)
	$(MAKE) $(AM_MAKEFLAGS) tempusex-rom
	$(objcopy_bin) tempusex-rom rom_programs/tempusex-rom.bin
rom_programs/tempusex-rom.map: $(tempusex_sources)
	$(MAKE) $(AM_MAKEFLAGS) tempusex
#expanded "tempusex" program definition ends

$(srcdir)/Makefile.am: $(srcdir)/Makefile.am.m4 $(srcdir)/m4/makefile.m4
	m4 -I $(srcdir) $(srcdir)/Makefile.am.m4 > $(srcdir)/Makefile.am
nodist_pkgdata_DATA+=summary
dist-hook:
	$(RM) ram_programs/* rom_programs/* *.map summary
