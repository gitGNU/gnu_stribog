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
CC=arm-elf-gcc
AS=arm-elf-as
LD=arm-elf-ld
OBJCOPY=arm-elf-objcopy
ASFLAGS=-mcpu=arm7tdmi
CFLAGS=-mcpu=arm7tdmi -Wall -O2
ifdef ram_based
 LFLAGS=-s -Map $@.map -nostartup -nostdlib -T$(src)/ram2138.ld -static -O2
else
 LFLAGS=-s -Map $@.map -nostartup -nostdlib -T$(src)/2138.ld -static -O2
endif
src=src
o=o
bin=bin
TARGETS=pllex ledex tempusex uart1ex crcex
ifdef ram_based
 targets=$(foreach t,$(TARGETS), $(bin)/$(t).bin $(bin)/$(t).vectors)
else
 targets=$(foreach t,$(TARGETS), $(bin)/$(t).bin)
endif
.PHONY: all clean maintainer-clean
#how ugly! I can't setup libgcc and add her manually.
all: libpath.mk autodeps.mk $(targets)
libpath.mk:
	echo -n "libpath=">$@
	find `which arm-elf-gcc|sed -e "s/bin\/arm-elf-gcc//"`\
 -name libgcc.a|grep -v "thumb">>$@
autodeps.mk: $(src)/*.c
	rm -f $@
	for i in `ls $(src)|grep "\.c$$"|sed -e"s/..$$//"`;\
 do $(CC) $(CFLAGS) -M -MT $(o)/$$i.o $(src)/$$i.c >>$@;done
include libpath.mk
include autodeps.mk
$(o)/%.elf:$(o)/boot.o $(o)/%.o 
	$(LD) $(LFLAGS) -o $@ $^ $(libpath)
$(o)/%.o:$(src)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<
%.s:$(src)/%.c
	$(CC) $(CFLAGS) -S -o $@ $<
$(o)/%.o:$(src)/%.s
	$(AS) $(ASFLAGS) -o $@ $<
clean:
	rm o/*
maintainer-clean: clean
	rm *.* bin/*
$(bin)/%.bin: $(o)/%.elf
	$(OBJCOPY) -I elf32-littlearm -O binary -R startup $< $@
$(bin)/%.vectors: $(o)/%.elf 
	$(OBJCOPY)\
 --set-section-flags vectors=contents,alloc,load,readonly,code -j vectors\
 -I elf32-littlearm -O binary $< $@
$(o)/ledex.elf:$(o)/led.o
$(o)/pllex.elf:$(o)/pll.o $(o)/led.o
$(o)/tempusex.elf:$(o)/pll.o $(o)/led.o
$(o)/uart1ex.elf:$(o)/pll.o $(o)/led.o $(o)/uart1.o
$(o)/crcex.elf:$(o)/pll.o $(o)/led.o $(o)/crc32.o

