#include<avr/io.h>/*odometer firmware*/
/*Fuse Low Byte = 0xef; Fuse High Byte = 0xc9; Fuse Extended Byte = 0xff*/
#define F_CPU   (14745600ul)
#define BAUD    (9600)
#define PERIOD	((unsigned char)(17))
#define INPUT_MASK	(1<<5)
static unsigned char capta[256],caput,cauda,missa[6],i=sizeof(missa);
static unsigned cnt;
static void init(void)
{UBRRH=0;UBRRL=F_CPU/BAUD/16-1;UCSRB=(1<<RXEN)|(1<<TXEN);
 UCSRC=((1<<UCSZ1)|(1<<UCSZ0)|(1<<URSEL))/*8-bit,No parity*/;
 TCCR0=(1<<CS02)|(1<<CS00);/*clk_io/1024*/
 TCCR1B=(1<<CS12);/*clk_io/256*/
}static void cape(void){if(!(UCSRA&(1<<RXC)))return;capta[caput++]=UDR;}
static void mitte(void)
{if(!(UCSRA&(1<<UDRE)))return;
 if(caput!=cauda)UDR=capta[cauda++];else
 {if(TCNT0<PERIOD&&!(TIFR&(1<<TOV0)))return;TCNT0=0;TIFR|=(1<<TOV0);
  if(i<sizeof(missa))UDR=missa[i++];
 }
}static void pone_mittenda(void)
{unsigned t=TCNT1;
 missa[0]=(cnt>>6)|(3<<6);missa[sizeof(missa)-1]=missa[0];
 missa[1]=(((unsigned char)cnt)|(3<<6));missa[sizeof(missa)-1]^=missa[1];
 missa[2]=((unsigned char)(t>>12))|(3<<6);missa[sizeof(missa)-1]^=missa[2];
 missa[3]=((unsigned char)(t>>6))|(3<<6);missa[sizeof(missa)-1]^=missa[3];
 missa[4]=((unsigned char)t)|(3<<6);missa[sizeof(missa)-1]^=missa[4];
 missa[sizeof(missa)-1]&=~(1<<6);missa[sizeof(missa)-1]|=1<<7;i=0;
}
static void inc_cnt(void)
{static unsigned char c1,c2;unsigned char c=PINC&INPUT_MASK;
 if(!(c1^c)&&(c2^c1))cnt++;c2=c1;c1=c;if(i==sizeof(missa))pone_mittenda();
}int main(void){init();while(1){inc_cnt();cape();mitte();}return 0;}
/*This is an auxiliary part of stribog
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

Copyright (C) 2007 D.Ineiev <ineiev@yahoo.co.uk>*/
