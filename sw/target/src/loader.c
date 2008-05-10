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
#include"init.h"
#include<ram_loader_enums.h>
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
static inline unsigned 
tempus(void){return T1TC;}
static void 
push_char(unsigned char c){while(!(U0LSR&UxLSR_THRE));U0THR=c;}
static inline void
push_ack(void){push_char(ACK);}
static inline void
push_nack(void){push_char(NACK);}
static int 
pull_char(void)
{unsigned t0=tempus();enum{chips_per_byte=10,timeout=83521};
 while(!(U0LSR&UxLSR_RDR)
  &&tempus()-t0<128*chips_per_byte*timeout);
 if(U0LSR&UxLSR_RDR)return U0RBR&0xFF;return-1;
}
static int
pull_number(unsigned*x)
{int i,c;unsigned y=0;
 for(i=0;i<bytes_per_word;i++)
 {c=pull_char();if(c<0)return!0;
  y<<=bits_per_byte;y|=c;
 }*x=y;
 return 0;
}
static int
load_and_go(void)
{unsigned address,i,crc;unsigned char*s;int c,h;
 h=pull_char();if(h<0)return 0;
 if(h!=SOH&&h!=EOT)goto nack;
 if(pull_number(&address))goto nack;
 if(pull_number(&crc))goto nack;
 if(crc!=form_crc(&address,1))goto nack;
 push_ack();s=(unsigned char*)address;
 if(h==EOT)
 {push_ack();push_ack();
  asm("ldr pc, %0"::"m"(address));
 }
 for(i=0;i<packet_size;i++)
 {c=pull_char();if(c<0)goto nack;s[i]=c;}
 if(pull_number(&crc))goto nack;
 if(crc!=form_crc((crc32_input_array_token*)s,packet_size>>2))
  goto nack;
 push_ack();return 0;nack:push_nack();return!0;
}
static void
get_in_sync(void)
{int h;do h=pull_char();while(h!=SOT);
 push_char(SOT);push_ack();
}
int
main(void)
{int h=1;init_bootloader();
 while(1){if(h)get_in_sync();h=load_and_go();}
 return 0;
}
