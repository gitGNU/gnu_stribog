/*LPC2138: magnetic module test
This file is a part of stribog.

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

Copyright (C) 2006, 2007 Ineiev<ineiev@users.sourceforge.net>, super V 93*/
#include"adc.h"
#include"pll.h"
#include"led.h"
#include"mag.h"
#include"uart1out.h"
#include"uart0.h"
#include"tempus.h"
static void send_data(const int*mag_fix)
{static int missed,i;char fix[6];if(!mag_fix)return;led1_set();led1_clr();
 fix[0]=*mag_fix&0xFF;fix[1]=((*mag_fix>>8)&0xF)|((mag_fix[1]&0xF)<<4);
 fix[2]=(mag_fix[1]>>4)&0xFF;fix[3]=mag_fix[2]&0xFF;fix[4]=(mag_fix[2]>>8)&0xF;
 if(missed)fix[4]|=1<<7;
 for(fix[sizeof(fix)-1]=i=0;i<sizeof(fix)-1;fix[sizeof(fix)-1]+=fix[i++]);
 missed=send_fix(fix,sizeof(fix));
}static void 
parse_settings(unsigned char*s,int n)
{int kx,ky=0,kz=0;
 if(n>0)kx=*s;if(n>1)ky=s[1];if(n>2)kz=s[2];set_mag_gains(kx,ky,kz);
}static void
init_all(void)
{unsigned char settings[0x11];int n;
 start_pll();init_led();init_tempus();init_uart1();init_adc();init_mag();
 connect_pll();led1_set();
 n=init_uart0(settings,sizeof(settings));parse_settings(settings,n);
}int 
main(void)
{int i=0;const unsigned*a;init_all();
 while(1)
 {if((a=get_adc()))send_data(process_mag(a));
  if(i++&(1<<17))led0_set();else led0_clr();
 }return 0;
}
