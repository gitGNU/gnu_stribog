/*LPC2138: magnetic module test
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
#include"adc.h"
#include"pll.h"
#include"led.h"
#include"mag.h"
#include"uart1out.h"
static void send_data(const int*mag_fix)
{static int missed,i;unsigned char fix[6];if(!mag_fix)return;led1_set();led1_clr();
 fix[0]=*mag_fix&0xFF;fix[1]=((*mag_fix>>8)&0xF)|((mag_fix[1]&0xF)<<4);
 fix[2]=(mag_fix[1]>>4)&0xFF;fix[3]=mag_fix[2]&0xFF;fix[4]=(mag_fix[2]>>8)&0xF;
 if(missed)fix[4]|=1<<7;
 for(fix[sizeof(fix)-1]=i=0;i<sizeof(fix)-1;fix[sizeof(fix)-1]+=fix[i++]);
 missed=send_fix(fix,sizeof(fix));
}
int main(void)
{int i=0;const unsigned*a;start_pll();init_led();init_uart1();led1_set();
 init_mag();init_adc();connect_pll();
 while(1)
 {if((a=get_adc()))send_data(process_mag(a));
  if(i++&(1<<17))led0_set();else led0_clr();
 }return 0;
}
