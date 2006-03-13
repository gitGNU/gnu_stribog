/*LPC2138: UART1
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
#include"uart1.h"
#include"mutex.h"
#include"crc32.h"
#include"../include/lpc2138.h"
#define LCRsig	Ux8bit|Ux1stop
#define HiDiv	(0)/*we use a high baud rate*/
#define LoDiv	(14745600/16/115200)/*115200 when freq=14745600*/
#define dle	((char)0x10)
#define etx	((char)0x03)
static mutex tx_mut;static char txbuf[0x100];
static int received,txi,txlen;
static int fill_txbuf(void)
{while((txi<txlen)&&(U1LSR&UxLSR_THRE))U1THR=txbuf[txi++];
 if(txi<txlen)return 0;U1IER=UxIERrx;unlock(&tx_mut);return!0;
}
int get_received(void){return received;}
static void proc_received(int c){received=c;}
static void quaestus(void)__attribute__((interrupt("IRQ")));
static void quaestus(void)
{int iir;
 while(!((iir=U1IIR)&UxIIRnopending))
 {switch(iir&UxIIRidentmask)
  {case UxIIR_RDA:while(U1LSR&UxLSR_RDR)proc_received(U1RBR);break;
   case UxIIR_THRE:fill_txbuf();break;
  }
 }VICVectAddr=0;
}
int init_uart1(void)
{PINSEL0=(PINSEL0&PINSEL0_TXD1MASK&PINSEL0_RXD1MASK)|PINSEL0_TXD1|PINSEL0_RXD1;
 VICVectAddr4=(unsigned)quaestus;VICVectCntl4=VIC_CntlEnable|VIC_UART1;
 VICIntEnable=1<<VIC_UART1;U1LCR=UxDLAB;U1DLL=LoDiv;U1DLM=HiDiv;U1LCR=LCRsig;
 U1IER=UxIERrx;U1FCR=UxFCRfifoenable;return 0;
}
int send_fix(const unsigned*d,int n)
{int i,j;unsigned crc;char*s=(char*)d;if(lock(&tx_mut))return!0;
 crc=form_crc(d,n);j=0;txbuf[j++]=dle;n<<=2;
 for(i=0;i<n;i++,j++)
 {if(s[i]==dle)txbuf[j++]=dle;txbuf[j]=s[i];}
 if((crc&0xFF)==dle)txbuf[j++]=dle;txbuf[j++]=crc&0xFF;crc>>=8;
 if((crc&0xFF)==dle)txbuf[j++]=dle;txbuf[j++]=crc&0xFF;crc>>=8;
 if((crc&0xFF)==dle)txbuf[j++]=dle;txbuf[j++]=crc&0xFF;crc>>=8;
 if((crc&0xFF)==dle)txbuf[j++]=dle;txbuf[j++]=crc&0xFF;crc>>=8;
 txbuf[j++]=dle;txbuf[j++]=etx;txi=0;txlen=j;
 fill_txbuf();U1IER=UxIERrx|UxIERtx;return 0;
}
