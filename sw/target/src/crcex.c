/*CRC32 test
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
#include"crc32.h"
#include"led.h"
#include"pll.h"
#include"uart1.h"
static fix_data f;static int i;
int main(void)
{start_pll();init_led();connect_pll();
 while(1)
 {f.d[0]=i++;f.d[FIX_LENGTH]=form_crc((unsigned*)(f.d),FIX_LENGTH);
  if(i&(1<<16))leds_set(1);else leds_clr(1);
 }
}
