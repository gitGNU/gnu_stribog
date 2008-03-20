/*elk the LPC21x programmer: copyleft and help output
This program is a part of the stribog host software section

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.

Copyright (C) 2006, 2007, 2008\
 Ineiev<ineiev@users.sourceforge.net>, super V 93*/
#include"usage.h"
#include<stdio.h>
void 
usage(void)
{printf("elk 0?F ("__DATE__") the LPC2138 programmer (hardly functional)\n"
"This program is a part of the stribog host software section\n"
"This program is free software; you can redistribute it and/or modify\n"
"it under the terms of the GNU General Public License as published by\n"
"the Free Software Foundation; either version 3 of the License, or\n"
"(at your option) any later version.\n"
"This program is distributed in the hope that it will be useful,\n"
"but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
"MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
"GNU General Public License for more details.\n"
"You should have received a copy of the GNU General Public License\n"
"along with this program. If not, see <http://www.gnu.org/licenses/>.\n"
"Copyright (C) 2006, 2007, 2008\\\n"
" Ineiev <ineiev@users.sourceforge.net>, super V 93\n"
"usage: elk [port [cryst. freq in kHz]]\n"
" default port on a POSIX system is /dev/ttyS0; on Windows -- COM1\n"
" default frequency is 14746; on POSIX systems the port baud rate is set\n"
" according to the crystal frequency; on Windows it is 115200\n"
"If frequency is negative, it synchronizes, runs RAM-based program and quits\n"
"To output info on interactive commands, press h\n"
  );
}void
help(void)
{printf(
" j: read part ID\n k: read version\n s: synchronize\n"
" l: load and run RAM-based program\n u: unlock uC for writing\n"
" p: prepare to erase ROM;  e: erase ROM\n b: load ROM-based program\n"
" r: dump MCU memory on screen\n q: quit\n h: commands info\n"
" t: toggle preferences loading\n"
"For more info, see elk sources and LPC21xx bootstrap loader documentation\n"
 );
}
