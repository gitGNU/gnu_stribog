/*LPC2138: board-to-host UART
Copyright (C) 2006, 2007, 2008\
 Ineiev <ineiev@users.sourceforge.net>, super V 93
This file has been written for the stribog project.

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
#include"uart1.h"
#include<mutex.h>
#include"crc32.h"
#include"../../common/form_fix.h"
#include"../include/lpc2138.h"
#include"freq.h"
#include"uart.config.h"
#define LCRsig	Ux8bit|Ux1stop
#define HiDiv	(0)/*we use a high baud rate*/
#define LoDiv	(PCLK_FREQUENCY/16/115200)
static mutex tx_mut;static char txbuf[0x80];static int received,txi,txlen;
static int fill_txbuf(void)
{while((txi<txlen)&&(ULSR_1&UxLSR_THRE))UTHR_1=txbuf[txi++];
 if(txi<txlen)return 0;UIER_1=UxIERrx;unlock(&tx_mut);return!0;
}
int get_received(void){return received;}
static void proc_received(int c){received=c;}
static void quaestus(void)__attribute__((interrupt("IRQ")));
static void quaestus(void)
{int iir;
 while(!((iir=UIIR_1)&UxIIRnopending))
 {switch(iir&UxIIRidentmask)
  {case UxIIR_RDA:while(ULSR_1&UxLSR_RDR)proc_received(URBR_1);break;
   case UxIIR_THRE:fill_txbuf();break;
  }
 }VICVectAddr=0;
}
int init_uart1(void)
{SELECT_PIN_1;
 VICVectAddr7=(unsigned)quaestus;VICVectCntl7=VIC_CntlEnable|VIC_UART_1;
 VICIntEnable=1<<VIC_UART_1;ULCR_1=UxDLAB;
 UDLL_1=LoDiv;UDLM_1=HiDiv;ULCR_1=LCRsig;
 UFCR_1=UxFCRfifoenable;UIER_1=UxIERrx;return 0;
}
int send_fix(const unsigned*d,int n)
{if(lock(&tx_mut))return!0;form_fix(d,n,txbuf,&txlen);txi=0;
 fill_txbuf();UIER_1=UxIERrx|UxIERtx;return 0;
}
