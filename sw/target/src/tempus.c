/*LPC2138: timer1 (system clock) setup and queries
 PPS (rising edge) from a GPS receiver can go through CAP1.2 pin (signal A)
TODO: test PPS capture
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
#include"mutex.h"
#include"../include/lpc2138.h"
#ifndef PPS_BURNT
 #define PPS_IR		TxIR_CR2
 #define PPS_CR 	T1CR2
 #define CCR_val	TxCAP2RE|TxCAP2I
#else
 #define PPS_IR		TxIR_CR1
 #define PPS_CR		T1CR1
 #define CCR_val	TxCAP1RE|TxCAP1I
#endif
static mutex pps_read;static unsigned aetas,pps;
const unsigned*get_pps(void){if(lock(&pps_read))return 0;return&pps;}
static void temporis_quaestus(void)__attribute__((interrupt("IRQ")));
static void temporis_quaestus(void)
{if(T1IR&PPS_IR){pps=PPS_CR;unlock(&pps_read);T1IR=PPS_IR;}
 if(T1IR&TxIR_MR0){aetas++;T1IR=TxIR_MR0;}VICVectAddr=0;
}
void init_tempus(void)
{T1PR=0;T1CTCR=0;T1TCR=0x1;T1MR0=0;T1MCR=1;T1CCR=CCR_val;
 VICIntEnable=1<<VIC_TIMER1;
 VICVectAddr5=(unsigned)temporis_quaestus;VICVectCntl5=VIC_CntlEnable|VIC_TIMER1;
#ifndef PPS_BURNT
 PINSEL1&=PINSEL1_CAP12_P017MASK;PINSEL1|=PINSEL1_CAP12_P017;
#else
 PINSEL0&=PINSEL0_CAP11_11MASK;PINSEL0|=PINSEL0_CAP11_11;
#endif
 lock(&pps_read);
}
unsigned long long tempus(void)/*TODO: rewrite reliably*/
{return T1TC|(((unsigned long long)aetas)<<32);
/*unsigned ti,ts;VICIntEnClear=1<<VIC_TIMER1;ti=T1TC;ts=aetas;
 if(VICIRQStatus&(1<<VIC_TIMER1)){ts++;ti=T1TC;}VICIntEnable=1<<VIC_TIMER1;
 return ti|(((unsigned long long)ts)<<32); //this won't work either*/
}
inline unsigned senius_tempus(void){return aetas;}
inline unsigned iunius_tempus(void){return T1TC;}
