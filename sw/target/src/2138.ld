/*LPC2138 linker script for ROM-based program
TODO: move all to >ram AT>rom
This file has been written for the stribog project.

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
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Copyright (C) 2006 D.Ineiev <ineiev@yahoo.co.uk>*/
/*sections fill should be 0x4E4F2043414D454C0A, if any*/
OUTPUT_FORMAT("elf32-littlearm")
MEMORY
{ ram (!r) : o = 0x40000000, l = 32k /* l = 8k for LPC2131, 
                                           16k for LPC213[24], 
                                           32k for LPC213[68] */
  rom (rx) : o = 0, l = 512k  /* l = 32k for LPC2131, 
                                     64k for LPC2132, 
                                    128k for LPC2134, 
                                    256k for LPC2136, 
                                    512k for LPC2138 */
}
_arm_stack_bottom = ORIGIN(ram) + LENGTH(ram) - 4;
_arm_ram_begin =  ORIGIN(ram);
SECTIONS
{.text : {
  *(.vectors) *boot.o(.text)
/* *(.ctors) *(.dtors) *(.jcr) /*these appear when I suddenly use c++*/
  } >rom
 . = ALIGN(4); _rom_data_begin = .;
 .rodata : 
 { *boot.o(.ramvectors) *(.text) *(.rodata) } >ram AT>rom /*rodata will be in RAM*/
 .data : { *(.data) } >ram AT>rom
  _rom_data_end = _rom_data_begin + SIZEOF(.data);
 . = ALIGN(4); _bss_data_begin = .;
 .bss : {*(.bss)} >ram
 . = ALIGN(4); _bss_data_end = .;
}
