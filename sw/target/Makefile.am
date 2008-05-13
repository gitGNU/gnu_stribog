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
nodist_pkgdata_DATA=
noinst_PROGRAMS=
nodist_ram_programs_DATA=
nodist_rom_programs_DATA=
EXTRA_PROGRAMS=
ram_programsdir=$(pkgdatadir)/ram_programs
rom_programsdir=$(pkgdatadir)/rom_programs

OBJCOPY=$(arm_unknown_elf_objcopy)
objcopy_bin=$(OBJCOPY) -I elf32-littlearm -O binary -R startup
objcopy_vectors=$(OBJCOPY)\
 --set-section-flags vectors=contents,alloc,load,readonly,code\
 -j vectors -I elf32-littlearm -O binary
common_sources=include/lpc2138.h src/boot.s
#atexit.c is needed for gcc-2.95.3
if atexit_needed
 common_sources+=lib/atexit.c
endif
 AM_CFLAGS=$(arm_ascc_flags) -Wall -O2
 AM_ASFLAGS=$(arm_as_flags)
 AM_CPPFLAGS=-I$(srcdir)/src
 AM_LDFLAGS=-Wl,-Map,$@.map -nostdlib -static
AM_LIBS=-lgcc
ram_flag=-T./ram2138.ld
rom_flag=-T./2138.ld
extra_common_sources=
EXTRA_DIST=src/ram2138.ld.in src/2138.ld.in src/mutex.c\
 Makefile.am.m4 m4/makefile.m4 subst_ldscript
##expanded "accelex" program definition begins
nodist_ram_programs_DATA+= accelex.bin accelex.map
nodist_rom_programs_DATA+=\
 accelex-rom.bin accelex-rom.map
noinst_PROGRAMS+=accelex accelex-rom

accelex_sources=$(common_sources)\
 src/accelex.c src/accel.c src/accel.h\
 src/mutex.h\
 src/led.c src/led.h src/pll.c src/pll.h
accelex_SOURCES=$(accelex_sources)
accelex_LDFLAGS=$(AM_LDFLAGS) $(ram_flag)
EXTRA_accelex_SOURCES=$(extra_common_sources)
accelex_DEPENDENCIES=ram2138.ld 
accelex_rom_SOURCES=$(accelex_sources)
accelex_rom_LDFLAGS=$(AM_LDFLAGS) $(rom_flag)
EXTRA_accelex_rom_SOURCES=$(extra_common_sources)
accelex_rom_DEPENDENCIES=2138.ld 
accelex.bin: $(accelex_sources)
	$(MAKE) $(AM_MAKEFLAGS) accelex
	$(objcopy_bin) accelex accelex.bin
accelex.map: $(accelex_sources)
	$(MAKE) $(AM_MAKEFLAGS) accelex
accelex-rom.bin: $(accelex_sources)
	$(MAKE) $(AM_MAKEFLAGS) accelex-rom
	$(objcopy_bin) accelex-rom accelex-rom.bin
accelex-rom.map: $(accelex_sources)
	$(MAKE) $(AM_MAKEFLAGS) accelex
##expanded "accelex" program definition ends
##expanded "adcex" program definition begins
nodist_ram_programs_DATA+= adcex.bin adcex.map
nodist_rom_programs_DATA+=\
 adcex-rom.bin adcex-rom.map
noinst_PROGRAMS+=adcex adcex-rom

adcex_sources=$(common_sources)\
 src/adcex.c src/adc.c src/adc.h\
 src/dac.c src/dac.h src/mutex.h\
 src/led.c src/led.h src/pll.c src/pll.h
adcex_SOURCES=$(adcex_sources)
adcex_LDFLAGS=$(AM_LDFLAGS) $(ram_flag)
EXTRA_adcex_SOURCES=$(extra_common_sources)
adcex_DEPENDENCIES=ram2138.ld 
adcex_rom_SOURCES=$(adcex_sources)
adcex_rom_LDFLAGS=$(AM_LDFLAGS) $(rom_flag)
EXTRA_adcex_rom_SOURCES=$(extra_common_sources)
adcex_rom_DEPENDENCIES=2138.ld 
adcex.bin: $(adcex_sources)
	$(MAKE) $(AM_MAKEFLAGS) adcex
	$(objcopy_bin) adcex adcex.bin
adcex.map: $(adcex_sources)
	$(MAKE) $(AM_MAKEFLAGS) adcex
adcex-rom.bin: $(adcex_sources)
	$(MAKE) $(AM_MAKEFLAGS) adcex-rom
	$(objcopy_bin) adcex-rom adcex-rom.bin
adcex-rom.map: $(adcex_sources)
	$(MAKE) $(AM_MAKEFLAGS) adcex
##expanded "adcex" program definition ends
##expanded "crcex" program definition begins
nodist_ram_programs_DATA+= crcex.bin crcex.map
nodist_rom_programs_DATA+=\
 crcex-rom.bin crcex-rom.map
noinst_PROGRAMS+=crcex crcex-rom

crcex_sources=$(common_sources)\
 src/crcex.c src/crc32.c src/crc32.h\
 src/pll.c src/pll.h src/led.c src/led.h
crcex_SOURCES=$(crcex_sources)
crcex_LDFLAGS=$(AM_LDFLAGS) $(ram_flag)
EXTRA_crcex_SOURCES=$(extra_common_sources)
crcex_DEPENDENCIES=ram2138.ld 
crcex_rom_SOURCES=$(crcex_sources)
crcex_rom_LDFLAGS=$(AM_LDFLAGS) $(rom_flag)
EXTRA_crcex_rom_SOURCES=$(extra_common_sources)
crcex_rom_DEPENDENCIES=2138.ld 
crcex.bin: $(crcex_sources)
	$(MAKE) $(AM_MAKEFLAGS) crcex
	$(objcopy_bin) crcex crcex.bin
crcex.map: $(crcex_sources)
	$(MAKE) $(AM_MAKEFLAGS) crcex
crcex-rom.bin: $(crcex_sources)
	$(MAKE) $(AM_MAKEFLAGS) crcex-rom
	$(objcopy_bin) crcex-rom crcex-rom.bin
crcex-rom.map: $(crcex_sources)
	$(MAKE) $(AM_MAKEFLAGS) crcex
##expanded "crcex" program definition ends
##expanded "dacex" program definition begins
nodist_ram_programs_DATA+= dacex.bin dacex.map
nodist_rom_programs_DATA+=\
 dacex-rom.bin dacex-rom.map
noinst_PROGRAMS+=dacex dacex-rom

dacex_sources=$(common_sources)\
 src/dacex.c src/dac.c src/dac.h\
 src/led.c src/led.h src/pll.c src/pll.h
dacex_SOURCES=$(dacex_sources)
dacex_LDFLAGS=$(AM_LDFLAGS) $(ram_flag)
EXTRA_dacex_SOURCES=$(extra_common_sources)
dacex_DEPENDENCIES=ram2138.ld 
dacex_rom_SOURCES=$(dacex_sources)
dacex_rom_LDFLAGS=$(AM_LDFLAGS) $(rom_flag)
EXTRA_dacex_rom_SOURCES=$(extra_common_sources)
dacex_rom_DEPENDENCIES=2138.ld 
dacex.bin: $(dacex_sources)
	$(MAKE) $(AM_MAKEFLAGS) dacex
	$(objcopy_bin) dacex dacex.bin
dacex.map: $(dacex_sources)
	$(MAKE) $(AM_MAKEFLAGS) dacex
dacex-rom.bin: $(dacex_sources)
	$(MAKE) $(AM_MAKEFLAGS) dacex-rom
	$(objcopy_bin) dacex-rom dacex-rom.bin
dacex-rom.map: $(dacex_sources)
	$(MAKE) $(AM_MAKEFLAGS) dacex
##expanded "dacex" program definition ends
##expanded "inledex" program definition begins
nodist_ram_programs_DATA+= inledex.bin inledex.map
nodist_rom_programs_DATA+=\
 inledex-rom.bin inledex-rom.map
noinst_PROGRAMS+=inledex inledex-rom

inledex_sources=$(common_sources)\
 src/inledex.c src/pll.c src/pll.h
inledex_SOURCES=$(inledex_sources)
inledex_LDFLAGS=$(AM_LDFLAGS) $(ram_flag)
EXTRA_inledex_SOURCES=$(extra_common_sources)
inledex_DEPENDENCIES=ram2138.ld 
inledex_rom_SOURCES=$(inledex_sources)
inledex_rom_LDFLAGS=$(AM_LDFLAGS) $(rom_flag)
EXTRA_inledex_rom_SOURCES=$(extra_common_sources)
inledex_rom_DEPENDENCIES=2138.ld 
inledex.bin: $(inledex_sources)
	$(MAKE) $(AM_MAKEFLAGS) inledex
	$(objcopy_bin) inledex inledex.bin
inledex.map: $(inledex_sources)
	$(MAKE) $(AM_MAKEFLAGS) inledex
inledex-rom.bin: $(inledex_sources)
	$(MAKE) $(AM_MAKEFLAGS) inledex-rom
	$(objcopy_bin) inledex-rom inledex-rom.bin
inledex-rom.map: $(inledex_sources)
	$(MAKE) $(AM_MAKEFLAGS) inledex
##expanded "inledex" program definition ends
##expanded "ledex" program definition begins
nodist_ram_programs_DATA+= ledex.bin ledex.map
nodist_rom_programs_DATA+=\
 ledex-rom.bin ledex-rom.map
noinst_PROGRAMS+=ledex ledex-rom

ledex_sources=$(common_sources)\
 src/ledex.c src/led.c src/led.h
ledex_SOURCES=$(ledex_sources)
ledex_LDFLAGS=$(AM_LDFLAGS) $(ram_flag)
EXTRA_ledex_SOURCES=$(extra_common_sources)
ledex_DEPENDENCIES=ram2138.ld 
ledex_rom_SOURCES=$(ledex_sources)
ledex_rom_LDFLAGS=$(AM_LDFLAGS) $(rom_flag)
EXTRA_ledex_rom_SOURCES=$(extra_common_sources)
ledex_rom_DEPENDENCIES=2138.ld 
ledex.bin: $(ledex_sources)
	$(MAKE) $(AM_MAKEFLAGS) ledex
	$(objcopy_bin) ledex ledex.bin
ledex.map: $(ledex_sources)
	$(MAKE) $(AM_MAKEFLAGS) ledex
ledex-rom.bin: $(ledex_sources)
	$(MAKE) $(AM_MAKEFLAGS) ledex-rom
	$(objcopy_bin) ledex-rom ledex-rom.bin
ledex-rom.map: $(ledex_sources)
	$(MAKE) $(AM_MAKEFLAGS) ledex
##expanded "ledex" program definition ends
##expanded "lm74ex" program definition begins
nodist_ram_programs_DATA+= lm74ex.bin lm74ex.map
nodist_rom_programs_DATA+=\
 lm74ex-rom.bin lm74ex-rom.map
noinst_PROGRAMS+=lm74ex lm74ex-rom

lm74ex_sources=$(common_sources)\
 src/lm74ex.c src/lm74.c src/lm74.h src/mutex.h\
 src/tempus.c src/tempus.h\
 src/pll.c src/pll.h src/led.c src/led.h
lm74ex_SOURCES=$(lm74ex_sources)
lm74ex_LDFLAGS=$(AM_LDFLAGS) $(ram_flag)
EXTRA_lm74ex_SOURCES=$(extra_common_sources)
lm74ex_DEPENDENCIES=ram2138.ld 
lm74ex_rom_SOURCES=$(lm74ex_sources)
lm74ex_rom_LDFLAGS=$(AM_LDFLAGS) $(rom_flag)
EXTRA_lm74ex_rom_SOURCES=$(extra_common_sources)
lm74ex_rom_DEPENDENCIES=2138.ld 
lm74ex.bin: $(lm74ex_sources)
	$(MAKE) $(AM_MAKEFLAGS) lm74ex
	$(objcopy_bin) lm74ex lm74ex.bin
lm74ex.map: $(lm74ex_sources)
	$(MAKE) $(AM_MAKEFLAGS) lm74ex
lm74ex-rom.bin: $(lm74ex_sources)
	$(MAKE) $(AM_MAKEFLAGS) lm74ex-rom
	$(objcopy_bin) lm74ex-rom lm74ex-rom.bin
lm74ex-rom.map: $(lm74ex_sources)
	$(MAKE) $(AM_MAKEFLAGS) lm74ex
##expanded "lm74ex" program definition ends
##conditional "magex" program definition begins
EXTRA_PROGRAMS+=magex magex-rom
if magex_enabled
 nodist_ram_programs_DATA+= magex.bin magex.map
nodist_rom_programs_DATA+=\
 magex-rom.bin magex-rom.map
noinst_PROGRAMS+=magex magex-rom

endif
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
magex_DEPENDENCIES=ram2138.ld 
magex_rom_SOURCES=$(magex_sources)
magex_rom_LDFLAGS=$(AM_LDFLAGS) $(rom_flag)
EXTRA_magex_rom_SOURCES=$(extra_common_sources)
magex_rom_DEPENDENCIES=2138.ld 
magex.bin: $(magex_sources)
	$(MAKE) $(AM_MAKEFLAGS) magex
	$(objcopy_bin) magex magex.bin
magex.map: $(magex_sources)
	$(MAKE) $(AM_MAKEFLAGS) magex
magex-rom.bin: $(magex_sources)
	$(MAKE) $(AM_MAKEFLAGS) magex-rom
	$(objcopy_bin) magex-rom magex-rom.bin
magex-rom.map: $(magex_sources)
	$(MAKE) $(AM_MAKEFLAGS) magex
##expanded "magex" program definition ends
##expanded "mag_response" program definition begins
nodist_ram_programs_DATA+= mag_response.bin mag_response.map
nodist_rom_programs_DATA+=\
 mag_response-rom.bin mag_response-rom.map
noinst_PROGRAMS+=mag_response mag_response-rom

mag_response_sources=$(common_sources)\
 src/mag_response.c\
 src/adc.c src/adc.h src/crc32.c src/crc32.h\
 src/dac.c src/dac.h\
 src/mutex.h src/uart.config.h src/freq.h\
 src/power.c src/power.h\
 src/tempus.c src/tempus.h\
 src/uart1.c src/uart1.h\
 src/led.c src/led.h src/pll.c src/pll.h
mag_response_SOURCES=$(mag_response_sources)
mag_response_LDFLAGS=$(AM_LDFLAGS) $(ram_flag)
EXTRA_mag_response_SOURCES=$(extra_common_sources)
mag_response_DEPENDENCIES=ram2138.ld ../common/form_fix.h
mag_response_rom_SOURCES=$(mag_response_sources)
mag_response_rom_LDFLAGS=$(AM_LDFLAGS) $(rom_flag)
EXTRA_mag_response_rom_SOURCES=$(extra_common_sources)
mag_response_rom_DEPENDENCIES=2138.ld ../common/form_fix.h
mag_response.bin: $(mag_response_sources)
	$(MAKE) $(AM_MAKEFLAGS) mag_response
	$(objcopy_bin) mag_response mag_response.bin
mag_response.map: $(mag_response_sources)
	$(MAKE) $(AM_MAKEFLAGS) mag_response
mag_response-rom.bin: $(mag_response_sources)
	$(MAKE) $(AM_MAKEFLAGS) mag_response-rom
	$(objcopy_bin) mag_response-rom mag_response-rom.bin
mag_response-rom.map: $(mag_response_sources)
	$(MAKE) $(AM_MAKEFLAGS) mag_response
##expanded "mag_response" program definition ends
##conditional "multa" program definition begins
EXTRA_PROGRAMS+=multa multa-rom
if multa_enabled
 nodist_ram_programs_DATA+= multa.bin multa.map
nodist_rom_programs_DATA+=\
 multa-rom.bin multa-rom.map
noinst_PROGRAMS+=multa multa-rom

endif
multa_sources=$(common_sources)\
 src/multa.c\
 src/accel.c src/accel.h src/adc.c src/adc.h\
 src/crc32.c src/crc32.h src/dac.c src/dac.h\
 src/lm74.c src/lm74.h src/mag.c src/mag.h\
 src/mutex.h src/uart.config.h src/freq.h\
 src/power.c src/power.h src/tempus.c src/tempus.h\
 src/uart0.c src/uart0.h src/uart1.c src/uart1.h\
 src/led.c src/led.h src/pll.c src/pll.h
multa_SOURCES=$(multa_sources)
multa_LDFLAGS=$(AM_LDFLAGS) $(ram_flag)
EXTRA_multa_SOURCES=$(extra_common_sources)
multa_DEPENDENCIES=ram2138.ld ../common/form_fix.h
multa_rom_SOURCES=$(multa_sources)
multa_rom_LDFLAGS=$(AM_LDFLAGS) $(rom_flag)
EXTRA_multa_rom_SOURCES=$(extra_common_sources)
multa_rom_DEPENDENCIES=2138.ld ../common/form_fix.h
multa.bin: $(multa_sources)
	$(MAKE) $(AM_MAKEFLAGS) multa
	$(objcopy_bin) multa multa.bin
multa.map: $(multa_sources)
	$(MAKE) $(AM_MAKEFLAGS) multa
multa-rom.bin: $(multa_sources)
	$(MAKE) $(AM_MAKEFLAGS) multa-rom
	$(objcopy_bin) multa-rom multa-rom.bin
multa-rom.map: $(multa_sources)
	$(MAKE) $(AM_MAKEFLAGS) multa
##expanded "multa" program definition ends
##expanded "pllex" program definition begins
nodist_ram_programs_DATA+= pllex.bin pllex.map
nodist_rom_programs_DATA+=\
 pllex-rom.bin pllex-rom.map
noinst_PROGRAMS+=pllex pllex-rom

pllex_sources=$(common_sources)\
 src/pllex.c src/pll.c src/pll.h src/led.c src/led.h
pllex_SOURCES=$(pllex_sources)
pllex_LDFLAGS=$(AM_LDFLAGS) $(ram_flag)
EXTRA_pllex_SOURCES=$(extra_common_sources)
pllex_DEPENDENCIES=ram2138.ld 
pllex_rom_SOURCES=$(pllex_sources)
pllex_rom_LDFLAGS=$(AM_LDFLAGS) $(rom_flag)
EXTRA_pllex_rom_SOURCES=$(extra_common_sources)
pllex_rom_DEPENDENCIES=2138.ld 
pllex.bin: $(pllex_sources)
	$(MAKE) $(AM_MAKEFLAGS) pllex
	$(objcopy_bin) pllex pllex.bin
pllex.map: $(pllex_sources)
	$(MAKE) $(AM_MAKEFLAGS) pllex
pllex-rom.bin: $(pllex_sources)
	$(MAKE) $(AM_MAKEFLAGS) pllex-rom
	$(objcopy_bin) pllex-rom pllex-rom.bin
pllex-rom.map: $(pllex_sources)
	$(MAKE) $(AM_MAKEFLAGS) pllex
##expanded "pllex" program definition ends
##expanded "powerex" program definition begins
nodist_ram_programs_DATA+= powerex.bin powerex.map
nodist_rom_programs_DATA+=\
 powerex-rom.bin powerex-rom.map
noinst_PROGRAMS+=powerex powerex-rom

powerex_sources=$(common_sources)\
 src/powerex.c src/power.c src/power.h
powerex_SOURCES=$(powerex_sources)
powerex_LDFLAGS=$(AM_LDFLAGS) $(ram_flag)
EXTRA_powerex_SOURCES=$(extra_common_sources)
powerex_DEPENDENCIES=ram2138.ld 
powerex_rom_SOURCES=$(powerex_sources)
powerex_rom_LDFLAGS=$(AM_LDFLAGS) $(rom_flag)
EXTRA_powerex_rom_SOURCES=$(extra_common_sources)
powerex_rom_DEPENDENCIES=2138.ld 
powerex.bin: $(powerex_sources)
	$(MAKE) $(AM_MAKEFLAGS) powerex
	$(objcopy_bin) powerex powerex.bin
powerex.map: $(powerex_sources)
	$(MAKE) $(AM_MAKEFLAGS) powerex
powerex-rom.bin: $(powerex_sources)
	$(MAKE) $(AM_MAKEFLAGS) powerex-rom
	$(objcopy_bin) powerex-rom powerex-rom.bin
powerex-rom.map: $(powerex_sources)
	$(MAKE) $(AM_MAKEFLAGS) powerex
##expanded "powerex" program definition ends
##expanded "uart1ex" program definition begins
nodist_ram_programs_DATA+= uart1ex.bin uart1ex.map
nodist_rom_programs_DATA+=\
 uart1ex-rom.bin uart1ex-rom.map
noinst_PROGRAMS+=uart1ex uart1ex-rom

uart1ex_sources=$(common_sources)\
 src/uart1ex.c\
 src/crc32.c src/crc32.h src/dac.c src/dac.h\
 src/lm74.c src/lm74.h src/mag.c src/mag.h\
 src/mutex.h src/uart.config.h src/freq.h\
 src/power.c src/power.h src/tempus.c src/tempus.h\
 src/uart1.c src/uart1.h\
 src/led.c src/led.h src/pll.c src/pll.h
uart1ex_SOURCES=$(uart1ex_sources)
uart1ex_LDFLAGS=$(AM_LDFLAGS) $(ram_flag)
EXTRA_uart1ex_SOURCES=$(extra_common_sources)
uart1ex_DEPENDENCIES=ram2138.ld ../common/form_fix.h
uart1ex_rom_SOURCES=$(uart1ex_sources)
uart1ex_rom_LDFLAGS=$(AM_LDFLAGS) $(rom_flag)
EXTRA_uart1ex_rom_SOURCES=$(extra_common_sources)
uart1ex_rom_DEPENDENCIES=2138.ld ../common/form_fix.h
uart1ex.bin: $(uart1ex_sources)
	$(MAKE) $(AM_MAKEFLAGS) uart1ex
	$(objcopy_bin) uart1ex uart1ex.bin
uart1ex.map: $(uart1ex_sources)
	$(MAKE) $(AM_MAKEFLAGS) uart1ex
uart1ex-rom.bin: $(uart1ex_sources)
	$(MAKE) $(AM_MAKEFLAGS) uart1ex-rom
	$(objcopy_bin) uart1ex-rom uart1ex-rom.bin
uart1ex-rom.map: $(uart1ex_sources)
	$(MAKE) $(AM_MAKEFLAGS) uart1ex
##expanded "uart1ex" program definition ends
##expanded "tempusex" program definition begins
nodist_ram_programs_DATA+= tempusex.bin tempusex.map
nodist_rom_programs_DATA+=\
 tempusex-rom.bin tempusex-rom.map
noinst_PROGRAMS+=tempusex tempusex-rom

tempusex_sources=$(common_sources)\
 src/tempusex.c src/mutex.h\
 src/pll.c src/pll.h src/led.c src/led.h
tempusex_SOURCES=$(tempusex_sources)
tempusex_LDFLAGS=$(AM_LDFLAGS) $(ram_flag)
EXTRA_tempusex_SOURCES=$(extra_common_sources)
tempusex_DEPENDENCIES=ram2138.ld 
tempusex_rom_SOURCES=$(tempusex_sources)
tempusex_rom_LDFLAGS=$(AM_LDFLAGS) $(rom_flag)
EXTRA_tempusex_rom_SOURCES=$(extra_common_sources)
tempusex_rom_DEPENDENCIES=2138.ld 
tempusex.bin: $(tempusex_sources)
	$(MAKE) $(AM_MAKEFLAGS) tempusex
	$(objcopy_bin) tempusex tempusex.bin
tempusex.map: $(tempusex_sources)
	$(MAKE) $(AM_MAKEFLAGS) tempusex
tempusex-rom.bin: $(tempusex_sources)
	$(MAKE) $(AM_MAKEFLAGS) tempusex-rom
	$(objcopy_bin) tempusex-rom tempusex-rom.bin
tempusex-rom.map: $(tempusex_sources)
	$(MAKE) $(AM_MAKEFLAGS) tempusex
##expanded "tempusex" program definition ends

nodist_ram_programs_DATA+=loader.bin loader.map
noinst_PROGRAMS+=loader
loader_sources=src/loader.boot.s include/lpc2138.h\
 src/loader.c src/freq.h src/crc32.c src/crc32.h\
 src/pll.c src/pll.h src/init.c src/init.h
loader_SOURCES=$(loader_sources)
loader_LDFLAGS=$(AM_LDFLAGS) -T./loader.ld
loader_DEPENDENCIES=loader.ld
loader.bin: $(loader_sources)
	$(MAKE) $(AM_MAKEFLAGS) loader
	$(objcopy_bin) loader loader.bin
loader.map: $(loader_sources)
	$(MAKE) $(AM_MAKEFLAGS) loader
if percent_rules_enabled
#the next is a debugging purpose rule; 
#it is disabled by default at configure time.
#it is OK to need GNU make here.
%.s: $(srcdir)/src/%.c
	$(COMPILE) -S -o $@ $<
endif
$(srcdir)/Makefile.am: $(srcdir)/Makefile.am.m4 $(srcdir)/m4/makefile.m4
	m4 -I $(srcdir) $(srcdir)/Makefile.am.m4 > $(srcdir)/Makefile.am
nodist_pkgdata_DATA+=summary ram2138.ld 2138.ld config.h
dist-hook:
	$(RM) $(nodist_rom_programs_DATA) $(nodist_ram_programs_DATA)\
 $(nodist_pkgdata_DATA)
ram2138.ld: $(srcdir)/src/ram2138.ld.in $(srcdir)/subst_ldscript
	$(srcdir)/subst_ldscript RAM $(mcu_conf) \
 < $(srcdir)/src/ram2138.ld.in > ram2138.ld
loader.ld: $(srcdir)/src/loader.ld.in $(srcdir)/subst_ldscript
	$(srcdir)/subst_ldscript RAM $(mcu_conf) \
 < $(srcdir)/src/loader.ld.in > loader.ld
2138.ld: $(srcdir)/src/2138.ld.in $(srcdir)/subst_ldscript
	$(srcdir)/subst_ldscript ROM $(mcu_conf) \
 < $(srcdir)/src/2138.ld.in > 2138.ld
