/*LPC2138: UART0; the data are written in a buffer and someone running in
 system (rather than interrupt) mode will empty the buffer. 
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
along with this program. If not, see <http://www.gnu.org/licenses/>.

Copyright (C) 2006 D.Ineiev <ineiev@yahoo.co.uk>*/
#include"uart0.h"
#include"mutex.h"
#include"../include/lpc2138.h"
#include"freq.h"
#include"tempus.h"
#define BAUD_RATE	(9600)
#define LCRsig	Ux8bit|Ux1stop
#define DivValue	(PCLK_FREQUENCY/16/BAUD_RATE)
#define HiDiv	(DivValue>>8)
#define LoDiv	(DivValue&0xFF)
static char rxbuf[0x20];static int caput,cauda;
/*static mutex tx0_mut;static int tx0i,tx0len;
static const char tx0buf[]={0x10,0xD,4,2,0xC,0,0,0xE1,0x10,3};
static int fill_tx0buf(void)
{while((tx0i<tx0len)&&(U0LSR&UxLSR_THRE))U0THR=tx0buf[tx0i++];
 if(tx0i<tx0len)return 0;U0IER=UxIERrx;unlock(&tx0_mut);return!0;
}*/
static void proc_received(char c)
{rxbuf[caput++]=c;if(caput==sizeof(rxbuf))caput=0;}
static void quaest(void)__attribute__((interrupt("IRQ")));
static void quaest(void)
{int iir;
 while(!((iir=U0IIR)&UxIIRnopending))
 {switch(iir&UxIIRidentmask)
  {case UxIIR_RDA:while(U0LSR&UxLSR_RDR)proc_received(U0RBR);break;
   /*case UxIIR_THRE:fill_tx0buf();break;*/
  }
 }VICVectAddr=0;
}
int init_uart0(void)
{PINSEL0=(PINSEL0&PINSEL0_TXD0MASK&PINSEL0_RXD0MASK)|PINSEL0_TXD0|PINSEL0_RXD0;
 VICVectAddr3=(unsigned)quaest;VICVectCntl3=VIC_CntlEnable|VIC_UART0;
 VICIntEnable=1<<VIC_UART0;U0LCR=UxDLAB;U0DLL=LoDiv;U0DLM=HiDiv;U0LCR=LCRsig;
 U0IER=UxIERrx;U0FCR=UxFCRfifoenable;return 0;
}
int receive0(char*d,int n)
{static unsigned t;unsigned dt;int i,cau=cauda;for(i=0;i<n&&caput!=cau;i++)
 {*d++=rxbuf[cau++];if(cau==sizeof(rxbuf))cau=0;}dt=tempus()-t;
 if(i<n-4&&t<PCLK_FREQUENCY/BAUD_RATE/10/12)return 0;
 cauda=cau;t=tempus();return i;
}
int ask_ephm(void)
{/*if(lock(&tx0_mut))return!0;tx0i=0;tx0len=sizeof(tx0buf);
 fill_tx0buf();U0IER=UxIERrx|UxIERtx;*/return 0;
}
