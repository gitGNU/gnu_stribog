/*LPC2138: simple timer1 test
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
#include"led.h"
#include"pll.h"
#include"../include/lpc2138.h"
static int flip,i;
static void temporis_quaestus(void)__attribute__((interrupt("IRQ")));
static void temporis_quaestus(void)
{if(flip^=1)leds_clr(2);else leds_set(2);T1IR=1;VICVectAddr=0;}
void init_tempus(void)
{VICVectAddr5=(unsigned)temporis_quaestus;VICVectCntl5=VIC_CntlEnable|VIC_TIMER1;
 VICIntEnable=1<<VIC_TIMER1;T1PR=0xFF;T1MR0=0x1000;T1MCR=3;T1TCR=0x1;
}
int main(void)
{start_pll();init_led();init_tempus();connect_pll();
 while(1){if(i++&(1<<19))leds_set(1);else leds_clr(1);}return 0;
}
