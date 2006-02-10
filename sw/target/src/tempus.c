/*LPC2138: timer1 (system clock) setup
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
#include"tempus.h"
#include"../include/lpc2138.h"
#include"led_inline.h"
void temporis_quaestus(void)__attribute__((interrupt("IRQ")));
static int flip;
void temporis_quaestus(void)
{if(T1IR&1){if(flip^=1)leds_set(1);else leds_clr(1);T1MR0+=0x1000;}
 VICVectAddr=0;
}
void init_tempus(void)
{T1PR=0xF;T1CTCR=0;T1TCR=0x3;T1MR0=0x1000;T1MCR=1;
 VICIntEnable|=VIC_TIMER1;VICSoftInt|=1<<VIC_TIMER1;
 VICVectAddr5=temporis_quaestus;VICVectCntl5=(1<<5)|VIC_TIMER1;
}
unsigned long long tempus(void)/*TODO: check pending interrupt(?)*/
{return (((unsigned long long)T1TC)<<16)|T1PC;
}
