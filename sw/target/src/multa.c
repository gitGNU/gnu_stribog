/*LPC2138: here many things are collected
This file is a part of stribog.

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
#include"adc.h"
#include"accel.h"
#define FIX_LENGTH	(5)
static unsigned f[FIX_LENGTH];static int b[3],a[3];
static void form_data(unsigned d[FIX_LENGTH],const int b[3])
{unsigned*s=d;int t,w[3];const unsigned*adc,*acc;while(!(adc=get_adc()));
 t=get_temperature();w[0]=adc[ADC_WX];w[1]=adc[ADC_WY];w[2]=adc[ADC_WZ];
 if((acc=get_accel())){a[0]=acc[0];a[1]=acc[1];a[2]=acc[2];}
 *s++=iunius_tempus();
 *s++=(b[0]&0xFFF)|((b[1]&0xFFF)<<12)|((t&0xFF)<<24);
 *s++=(b[2]&0xFFF)|((a[0]&0x3FFF)<<12)|((t&0x1F00)<<(26-8));
 *s++=(a[1]&0x3FFF)|((a[2]&0x3FFF)<<14);
 *s++=(w[0]&0x3FF)|((w[1]&0x3FF)<<10)|((w[2]&0x3FF)<<20);
}
int main(void)
{start_pll();init_power();init_led();init_lm74();init_accel();led1_set();connect_pll();
 init_adc();init_uart1();init_tempus();led1_set();
 while(1){form_data(f,b);while(send_fix(f,FIX_LENGTH));led0_set();led0_clr();}
 return 0;
}
