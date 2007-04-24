#Makefile for AVR targets
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
#Copyright (C) 2007 D.Ineiev <ineiev@yahoo.co.uk>
CC	= avr-gcc
LD	= avr-gcc
ifndef MCU
 mcu=-mmcu=atmega8
else
 mcu=-mmcu=$(MCU)
endif
CFLAGS	= $(mcu) -O3 -Wall 
LDFLAGS = $(mcu) -Wl
%.elf:%.o
	$(LD) $(LDFLAGS) $^ -o $@
%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@
%.S:%.c
	$(CC) $(CFLAGS) -S $< -o $@
%.hex:%.elf
	avr-objcopy -O ihex -R .eeprom $< $@
.PHONY: all clean maintainer-clean
all:$(TARGETS)
clean:
	-rm -f *.o *.elf
maintainer-clean: clean
	-rm -f $(TARGETS)
