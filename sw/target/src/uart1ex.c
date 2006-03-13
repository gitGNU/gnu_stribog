/*LPC2138: UART1 test
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
#include"uart1.h"
#include"led.h"
#include"pll.h"
#include"tempus.h"
#include"power.h"
#include"lm74.h"
#define FIX_LENGTH	(5)
static unsigned f[FIX_LENGTH];static int a[3],w[3],b[3];
static void form_data(unsigned d[FIX_LENGTH],const int a[3],
 const int w[3],const int b[3])
{unsigned*s=d;int t=get_temperature();
 *s++=iunius_tempus();
 *s++=(b[0]&0xFFF)|((b[1]&0xFFF)<<12)|((t&0xFF)<<24);
 *s++=(b[2]&0xFFF)|((a[0]&0xFFF)<<12)|((t&0xF00)<<(24-8));
 *s++=(a[1]&0xFFF)|((a[2]&0xFFF)<<12);
 *s++=(w[0]&0x3FF)|((w[1]&0x3FF)<<10)|((w[2]&0x3FF)<<20);
}
int main(void)
{start_pll();init_power();init_led();init_lm74();connect_pll();
 init_uart1();init_tempus();led1_set();
 while(1){form_data(f,a,w,b);while(send_fix(f,FIX_LENGTH));led0_set();led0_clr();}
 return 0;
}
