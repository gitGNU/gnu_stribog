/*LPC2138: timer1 (system clock) test
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
#include"led_inline.h"
static int flip;
void temporis_quaestus(void)__attribute__((interrupt("IRQ")));
void temporis_quaestus(void)
{/*if(T1IR&1){*//*if(flip^=1)leds_set(1);else leds_clr(1);*/leds_clr(2);/*T1MR0+=0x100;}*/
 VICVectAddr=0;
}
void init_tempus(void)
{T1PR=0xF;T1MR0=0x100;T1MCR=3;T1TCR=0x1;
 //VICDefVectAddr= 
  VICVectAddr0=(unsigned)temporis_quaestus;VICVectCntl0=(1<<5)|VIC_TIMER1;
 VICIntEnable=1<<VIC_TIMER1;
}
static int i;
int main(void)
{start_pll();init_led();leds_set(3);init_tempus();connect_pll();
 while(1)
 {if(i++&(1<<19))leds_clr(1);else leds_set(1);
//  if(T1TC&0x10000)leds_clr(2);else leds_set(2);
 }return 0;
}
