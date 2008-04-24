/*UART0 (program setup and external sensors connection)
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

/*the data are written in a buffer and
someone running in system (rather than interrupt) mode
will empty the buffer.*/
#include"uart0.h"
#include<mutex.h>
#include"../include/lpc2138.h"
#include"uart.config.h"
#include"freq.h"
#include"tempus.h"
#define BAUD_RATE	(9600)
#define LOADER_RATE	(115200)
#define LCRsig	Ux8bit|Ux1stop
#define DIVISOR(a)	(PCLK_FREQUENCY/16/a)
#define HI_DIV(a)	(DIVISOR(a)>>8)
#define LO_DIV(a)	(DIVISOR(a)&0xFF)
#define Loader_Hi_Div	HI_DIV(LOADER_RATE)
#define Loader_Lo_Div	LO_DIV(LOADER_RATE)
#define Hi_Div		HI_DIV(BAUD_RATE)
#define Lo_Div		LO_DIV(BAUD_RATE)
enum{chips_per_byte=10};
static char rxbuf[0x20];static int caput,cauda;int uart0_overflows;
/*static mutex tx0_mut;static int tx0i,tx0len;
static const char tx0buf[]={0x10,0xD,4,2,0xC,0,0,0xE1,0x10,3};
static int fill_tx0buf(void)
{while((tx0i<tx0len)&&(ULSR_0&UxLSR_THRE))UTHR_0=tx0buf[tx0i++];
 if(tx0i<tx0len)return 0;UIER_0=UxIERrx;unlock(&tx0_mut);return!0;
}*/
static void proc_received(char c)
{rxbuf[caput++]=c;if(caput==sizeof(rxbuf))caput=0;
 if(caput==cauda)++uart0_overflows;
}
static void quaest(void)__attribute__((interrupt("IRQ")));
static void quaest(void)
{int iir;
 while(!((iir=UIIR_0)&UxIIRnopending))
 {switch(iir&UxIIRidentmask)
  {case UxIIR_RDA:while(ULSR_0&UxLSR_RDR)proc_received(URBR_0);break;
   /*case UxIIR_THRE:fill_tx0buf();break;*/
  }
 }VICVectAddr=0;
}enum control_characters{reset=0,end=0xFF};
static void 
push_ack(unsigned char c){while(!(U0LSR&UxLSR_THRE));U0THR=c;}
static void
terminate(void){push_ack(end);}
static int 
poll_char(void)
{unsigned t0=iunius_tempus();int c;enum{timeout=83521};
 while(!(U0LSR&UxLSR_RDR)
  &&iunius_tempus()-t0<PCLK_FREQUENCY/LOADER_RATE*chips_per_byte*timeout);
 if(U0LSR&UxLSR_RDR){c=U0RBR;push_ack(c);return c&0xFF;}
 terminate();return-1;
}static int 
get_settings(unsigned char*s,int size)
{int i;for(i=0;i<size;i++)
 {int c;if((c=poll_char())<0)return-1;
  if(end==c)return i;s[i]=c;if(reset==c)i=-1;
 }if(i==size){terminate();return-2;}return i;
}int 
init_uart0(unsigned char*settings,int size)
{int r=0;uart0_overflows=0;SELECT_LOADER_PIN;
 U0LCR=UxDLAB;U0DLL=Loader_Lo_Div;U0DLM=Loader_Hi_Div;
 U0LCR=LCRsig;U0FCR=UxFCRfifoenable;
 if(size>0&&settings!=(unsigned char*)0)
 {unsigned t;r=get_settings(settings,size);t=iunius_tempus();
  while(iunius_tempus()-t<PCLK_FREQUENCY/LOADER_RATE*chips_per_byte*3);
 }SELECT_UART_0_PIN;
 VICVectAddr8=(unsigned)quaest;VICVectCntl8=VIC_CntlEnable|VIC_UART_0;
 VICIntEnable=1<<VIC_UART_0;ULCR_0=UxDLAB;
 UDLL_0=Lo_Div;UDLM_0=Hi_Div;ULCR_0=LCRsig;
 UFCR_0=UxFCRfifoenable;UIER_0=UxIERrx;return r;
}int 
receive0(char*d,int n)
{enum{timeout=12};static unsigned t0;unsigned t;int i,cau;
 for(cau=cauda,i=0;i<n&&caput!=cau;i++)
 {*d++=rxbuf[cau++];if(cau==sizeof(rxbuf))cau=0;}t=iunius_tempus();
 if(i<n-4&&t>t0&&t-t0<PCLK_FREQUENCY/BAUD_RATE*chips_per_byte*timeout)
  return 0;cauda=cau;t0=t;return i;
}int 
ask_ephm(void)
{/*if(lock(&tx0_mut))return!0;tx0i=0;tx0len=sizeof(tx0buf);
 fill_tx0buf();UIER_0=UxIERrx|UxIERtx;*/return 0;
}
