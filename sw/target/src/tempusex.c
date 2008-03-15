/*LPC2138: simple timer1 test
Copyright (C) 2006, 2008\
 Ineiev <ineiev@users.sourceforge.net>, super V 93
This file is a part of the stribog project.

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.*/
/*FIXME configure PPS pin*/
#include"led.h"
#include"pll.h"
#include"../include/lpc2138.h"
#include<mutex.h>
static mutex pps_read;static unsigned aetas,pps;
static void temporis_quaestus(void)__attribute__((interrupt("IRQ")));
static void temporis_quaestus(void)
{static int i;
 if(T1IR&TxIR_CR2)
 {pps=T1CR2;unlock(&pps_read);
  T1IR=TxIR_CR2;if(++i&(1<<0))led1_set();else led1_clr();
 }if(T1IR&TxIR_MR0){aetas++;T1IR=TxIR_MR0;}VICVectAddr=0;
}
void init_tempus(void)
{VICVectAddr5=(unsigned)temporis_quaestus;VICVectCntl5=VIC_CntlEnable|VIC_TIMER1;
 VICIntEnable=1<<VIC_TIMER1;T1PR=0xFF;T1MR0=0x1000;T1MCR=3;T1TCR=0x1;
 T1CCR=TxCAP2RE|TxCAP2I;
 PINSEL1&=PINSEL1_CAP12_P017MASK;PINSEL1|=PINSEL1_CAP12_P017;
}static int i;
int main(void)
{start_pll();init_led();init_tempus();connect_pll();//led1_set();
 while(1){if(i++&(1<<19))led0_set();else led0_clr();}return 0;
}
