/*bootloader
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
#include"../include/lpc2138.h"
#include"crc32.h"
#include"freq.h"
#define BAUD_RATE	(115200)
#define LCRsig	Ux8bit|Ux1stop
#define DIVISOR(a)	(PCLK_FREQUENCY/16/a)
#define HI_DIV(a)	(DIVISOR(a)>>8)
#define LO_DIV(a)	(DIVISOR(a)&0xFF)
#define Lo_Div	LO_DIV(BAUD_RATE)
#define Hi_Div	HI_DIV(BAUD_RATE)
#define pin0mask	(1<<19)
#define pin1mask	(1<<29)
static inline void
led0_clr(void){IO0CLR=pin0mask;}
static inline void
led0_set(void){IO0SET=pin0mask;}
static inline void
led1_clr(void){IO1CLR=pin1mask;}
static inline void
led1_set(void){IO1SET=pin1mask;}
static void
init_led(void)
{PINSEL2=0;IO0DIR|=pin0mask;IO1DIR|=pin1mask;
 led0_clr();led1_clr();
}
static inline unsigned 
tempus(void){return T1TC;}
static void
init_tempus(void){T1PR=0xFF;T1MR0=0x1000;T1MCR=3;T1TCR=0x1;}
enum global_constants
{SOH=1,EOT=5,ACK=6,NACK=0x15,
 packet_size=1<<10,bytes_per_word=4,bits_per_byte=8
};
static void
init_uart(void)
{PINSEL0=(PINSEL0&PINSEL0_TXD0MASK&PINSEL0_RXD0MASK)
  |PINSEL0_TXD0|PINSEL0_RXD0;
 U0LCR=UxDLAB;U0DLL=Lo_Div;U0DLM=Hi_Div;
 U0LCR=LCRsig;U0FCR=UxFCRfifoenable;
}
static void 
push_char(unsigned char c){while(!(U0LSR&UxLSR_THRE));U0THR=c;}
static void
push_ack(void){push_char(ACK);}
static void
cancel(void){push_char(NACK);}
static int 
pull_char(void)
{unsigned t0=tempus();enum{chips_per_byte=10,timeout=83521};
 while(!(U0LSR&UxLSR_RDR)
  &&tempus()-t0<PCLK_FREQUENCY/BAUD_RATE*chips_per_byte*timeout);
 if(U0LSR&UxLSR_RDR)return U0RBR&0xFF;return-1;
}
static int
pull_number(unsigned*x)
{int i,c;
 for(i=*x=0;i<bytes_per_word;i++)
 {c=pull_char();if(c<0)return!0;
  *x<<=bits_per_byte;*x|=c;
 }return 0;
}
static void
load_and_go(void)
{unsigned address,i,crc;unsigned char*s;int c,h;
 h=pull_char();if(h<0)goto out;
 if(h!=SOH&&h!=EOT)goto out;
 if(pull_number(&address))goto out;
 if(pull_number(&crc))goto out;
 if(crc!=form_crc(&address,1))goto out;
 s=(unsigned char*)address;
 if(h==EOT)
 {push_ack();push_ack();led1_set();
  /*asm("ldr pc, %0"::"m"(address));*/
  while(1);
 }
 for(i=0;i<packet_size;i++)
 {c=pull_char();if(c<0)goto out;s[i]=c;}
 if(pull_number(&crc))goto out;
 if(crc!=form_crc((const crc32_input_array_token*)s,packet_size>>2))
  goto out;
 push_ack();return;out:cancel();
}int main(void)__attribute__((naked));
int
main(void)
{int i=0;init_led();led1_set();init_tempus();init_uart();led1_clr();
 while(1){if(i++&1)led0_set();else led0_clr();load_and_go();}return 0;
}
