#Makefile for target software part of the stribog
#
#This program is free software; you can redistribute it and/or modify
#it under the terms of the GNU General Public License as published by
#the Free Software Foundation; either version 2 of the License, or
#(at your option) any later version.
#
#This program is distributed in the hope that it will be useful,
#but WITHOUT ANY WARRANTY; without even the implied warranty of
#MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#GNU General Public License for more details.
#
#You should have received a copy of the GNU General Public License
#along with this program; if not, write to the Free Software
#Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
#
#Copyright (C) 2006 D.Ineiev <ineiev@yahoo.co.uk>
ram_based=1
ifndef MCU_UNOFFENDED
 PPS_BURNT=1
endif
CC=arm-elf-gcc
AS=arm-elf-as
LD=arm-elf-ld
OBJCOPY=arm-elf-objcopy
ASFLAGS=-mcpu=arm7tdmi
CFLAGS=-mcpu=arm7tdmi -Wall -O2
ifdef PPS_BURNT
 CFLAGS+=-DPPS_BURNT
endif
ifdef ram_based
 ldscript=$(src)/ram2138.ld
else
 ldscript=$(src)/2138.ld
endif
LDFLAGS=-s -Map $@.map -nostartup -nostdlib -T$(ldscript) -static -O2
src=src
o=o
bin=bin
TARGETS=pllex inledex ledex tempusex uart1ex crcex adcex dacex powerex multa\
 accelex magex mag_response lm74ex
ifdef ram_based
 targets=$(foreach t,$(TARGETS), $(bin)/$(t).bin $(bin)/$(t).vectors)
else
 targets=$(foreach t,$(TARGETS), $(bin)/$(t).bin)
endif
.PHONY: all clean maintainer-clean
all: autodeps.mk $(targets)
autodeps.mk: $(src)/*.c
	rm -f $@
	for i in `ls $(src)|grep "\.c$$"|sed -e"s/..$$//"`;\
 do $(CC) $(CFLAGS) -M -MT $(o)/$$i.o $(src)/$$i.c >>$@;done
include autodeps.mk
$(o)/%.elf:$(o)/boot.o $(o)/%.o 
	$(LD) $(LDFLAGS) -o $@ $^ `$(CC) -print-libgcc-file-name`
$(o)/%.o:$(src)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<
%.s:$(src)/%.c
	$(CC) $(CFLAGS) -S -o $@ $<
$(o)/%.o:$(src)/%.s
	$(AS) $(ASFLAGS) -o $@ $<
clean:
	rm -f o/*
maintainer-clean: clean
	rm -f *.* bin/*
$(bin)/%.bin: $(o)/%.elf
	$(OBJCOPY) -I elf32-littlearm -O binary -R startup $< $@
$(bin)/%.vectors: $(o)/%.elf 
	$(OBJCOPY)\
 --set-section-flags vectors=contents,alloc,load,readonly,code -j vectors\
 -I elf32-littlearm -O binary $< $@
$(o)/ledex.elf:$(o)/led.o
$(o)/pllex.elf:$(o)/pll.o $(o)/led.o
$(o)/tempusex.elf:$(o)/pll.o $(o)/led.o
$(o)/uart1ex.elf:$(o)/pll.o $(o)/led.o $(o)/uart1.o $(o)/crc32.o\
 $(o)/tempus.o $(o)/power.o $(o)/lm74.o
$(o)/crcex.elf:$(o)/pll.o $(o)/led.o $(o)/crc32.o
$(o)/inledex.elf:$(o)/pll.o
$(o)/adcex.elf:$(o)/adc.o $(o)/led.o $(o)/pll.o $(o)/dac.o
$(o)/magex.elf:$(o)/adc.o $(o)/led.o $(o)/pll.o $(o)/dac.o $(o)/mag.o \
 $(o)/uart1out.o
$(o)/dacex.elf:$(o)/led.o $(o)/pll.o $(o)/dac.o
$(o)/lm74ex.elf:$(o)/lm74.o $(o)/pll.o $(o)/led.o $(o)/tempus.o
$(o)/powerex.elf:$(o)/power.o
$(o)/multa.elf:$(o)/pll.o $(o)/led.o $(o)/uart1.o $(o)/crc32.o $(o)/dac.o\
 $(o)/tempus.o $(o)/power.o $(o)/lm74.o $(o)/adc.o $(o)/accel.o $(o)/mag.o\
 $(o)/uart0.o
$(o)/mag_response.elf:$(o)/pll.o $(o)/led.o $(o)/uart1.o $(o)/crc32.o\
 $(o)/dac.o $(o)/tempus.o $(o)/power.o $(o)/adc.o
$(o)/accelex.elf:$(o)/accel.o $(o)/led.o $(o)/pll.o
