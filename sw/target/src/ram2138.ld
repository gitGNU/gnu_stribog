/*LPC2138 linker script for RAM-based program
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
along with this program. If not, see <http://www.gnu.org/licenses/>.

Copyright (C) 2006 D.Ineiev <ineiev@yahoo.co.uk>*/
/*sections fill should be 0x4E4F2043414D454C0A, if any*/
OUTPUT_FORMAT("elf32-littlearm")
MEMORY
{ ram (!r) : o = 0x40000200, 
   l = -0x200/*low memory used by the bootstrap loader*/
   -32-256/*high memory used by the bootstrap loader*/
   -8/*two words more to be sure*/
   +32k /*l = 8k for LPC2131, 16k for LPC213[24], 32k for LPC213[68]*/
  lowram(!r) : o = 0x4000000, l = 0x40
  rom (rx) : o = 0, l = 512k/* l = 32k for LPC2131, 64k for LPC2132, 
                                   128k for LPC2134, 
                                   256k for LPC2136, 
                                   512k for LPC2138 */
}
_arm_stack_bottom = ORIGIN(ram) + LENGTH(ram) - 4;
_arm_ram_begin = ORIGIN(ram);
SECTIONS
{vectors : {*(.vectors) }>lowram
 .text : {
  *boot.o(.text)
  *(.text)
  *(.rodata)
/* *(.ctors) *(.dtors) *(.jcr) /*these appear when I suddenly use c++*/
  } >ram
 . = ALIGN(4);
 .data : { *(.data) } >ram
 . = ALIGN(4); _bss_data_begin = .;
 .bss : {*(.bss)} >ram
 . = ALIGN(4); _bss_data_end = .;
 _rom_data_begin = .; _rom_data_end = .;
}
