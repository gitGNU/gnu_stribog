/*odometer firmware
Copyright (C) 2007, 2008 
 Ineiev <ineiev@users.sourceforge.net>, super V 93

This is an auxiliary part of stribog

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
/*See ../../host/conloq/odo.c for a sample host-side program*/
/*atmega8 fuses:Low = 0xef; High = 0xc9; Extended = 0xff*/
/*with decimation constant 0x3 it reliably counts pulses wider than
 17 us with frequencies up to 17 kHz; filters out pulses narrower than 2 us
Note: this was tested for ODO_F_CPU=14745600;ODO_BAUD=9600*/
#ifdef HAVE_CONFIG_H
 #include<config.h>
#else
 #define ODO_F_CPU	(14745600ul)
 #define ODO_BAUD	(9600)
 #define ODO_INPUT_MASK	((unsigned char)(1<<5))
#endif
#define UART_DIVISOR	(ODO_F_CPU/ODO_BAUD/16-1)
#if UART_DIVISOR>0xFFFF
 #error "Too low UART baud rate"
#endif
#include<avr/io.h>
static unsigned char capta[668],missa[6],i=sizeof(missa);
static unsigned cnt,caput,cauda;
static void
moram_iube(void){TCNT0=0;TIFR|=(1<<TOV0);}
static unsigned char
mora(void)
{static const unsigned char period=170;return TCNT0<period&&!(TIFR&(1<<TOV0));}
static void
pone_mittenda(void)
{unsigned t=TCNT1;missa[0]=(cnt>>6)|(3<<6);missa[sizeof(missa)-1]=missa[0];
 missa[1]=(((unsigned char)cnt)|(3<<6));missa[sizeof(missa)-1]^=missa[1];
 missa[2]=((unsigned char)(t>>12))|(3<<6);missa[sizeof(missa)-1]^=missa[2];
 missa[3]=((unsigned char)(t>>6))|(3<<6);missa[sizeof(missa)-1]^=missa[3];
 missa[4]=((unsigned char)t)|(3<<6);missa[sizeof(missa)-1]^=missa[4];
 missa[sizeof(missa)-1]&=~(1<<6);missa[sizeof(missa)-1]|=1<<7;i=0;
}
static void
init(void)
{UBRRH=(UART_DIVISOR>>8)&0xFF;UBRRL=UART_DIVISOR&0xFF;
 UCSRB=(1<<RXEN)|(1<<TXEN);
 UCSRC=((1<<UCSZ1)|(1<<UCSZ0)|(1<<URSEL))/*8-bit,No parity*/;
 TCCR0=(1<<CS02)|(1<<CS00);/*clk_io/1024*/
 TCCR1B=(1<<CS12);/*clk_io/256*/
 DDRB=1;moram_iube();pone_mittenda();
}
static inline void
ch_adde(unsigned char c)
{capta[caput++]=c;if(caput>=sizeof(capta))caput=0;}
static inline unsigned char
ch_redde(void)
{unsigned char c=capta[cauda++];if(cauda>=sizeof(capta))cauda=0;return c;}
static unsigned char
mittenda_redde(void)
{if(i>=sizeof(missa))pone_mittenda();return missa[i++];}
static void
cape(void){if(!(UCSRA&(1<<RXC)))return;ch_adde(UDR);}
static void
mitte(void)
{static unsigned char v,p=3;char _=caput!=cauda;
 if(!(UCSRA&(1<<UDRE)))return;
 if(_){if(++v==p)v=0;}
 else{v=0;if(mora())return;if(i==sizeof(missa))moram_iube();}
 UDR=v?ch_redde():mittenda_redde();
}
static void
inc_cnt(void)
{static unsigned char c1,c2,c3;unsigned char c=PINC&ODO_INPUT_MASK;
 PORTB=1;if(c!=c2&&c1==c&&c2==c3)cnt++;c3=c2;c2=c1;c1=c;PORTB=0;
}
int
main(void){init();while(1){inc_cnt();cape();mitte();}return 0;}

