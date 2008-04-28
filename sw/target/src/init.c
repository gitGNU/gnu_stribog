/*bootloader initialisation routines
Copyright (C) 2006, 2007, 2008\
 Ineiev<ineiev@users.sourceforge.net>, super V 93
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
along with this program. If not, see <http://www.gnu.org/licenses/>.*/
#include"pll.h"
#include"../include/lpc2138.h"
#include"init.h"
#include"freq.h"
#define use_pll	1
#define BAUD_RATE	(115200)
#define LCRsig	Ux8bit|Ux1stop
#if use_pll
 #define FREQ		(PCLK_FREQUENCY)
#else
 #define FREQ		(PCLK_FREQUENCY/4)
#endif
#define DIVISOR(a)	(FREQ/16/a)
#define HI_DIV(a)	(DIVISOR(a)>>8)
#define LO_DIV(a)	(DIVISOR(a)&0xFF)
#define Lo_Div	LO_DIV(BAUD_RATE)
#define Hi_Div	HI_DIV(BAUD_RATE)
#define pin0mask	(1<<19)
#define pin1mask	(1<<29)
static inline void
led0_clr(void){IO0CLR=pin0mask;}
static inline void
led1_clr(void){IO1CLR=pin1mask;}
static void
init_led(void)
{PINSEL2=0;IO0DIR|=pin0mask;IO1DIR|=pin1mask;
 led0_clr();led1_clr();
}
static inline void
flush_uart(void)
{while(!(U0LSR&UxLSR_TSRE));
 while((U0LSR&UxLSR_RDR)){(void)U0THR;}
}
static void
init_uart(void)
{PINSEL0=(PINSEL0&PINSEL0_TXD0MASK&PINSEL0_RXD0MASK)
  |PINSEL0_TXD0|PINSEL0_RXD0;
 U0LCR=UxDLAB;U0DLL=Lo_Div;U0DLM=Hi_Div;
 U0LCR=LCRsig;U0FCR=UxFCRfifoenable;U0IER=0;flush_uart();
}
static void
init_tempus(void){T1PR=0x1FFFF;T1MR0=0x1000;T1MCR=3;T1TCR=0x1;}
void
init_bootloader(void)
{if(use_pll)start_pll();init_led();init_tempus();
 if(use_pll)connect_pll();init_uart();
}
