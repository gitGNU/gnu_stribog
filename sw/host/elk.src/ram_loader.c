/*elk the LPC21x programmer: 2nd stage RAM bootloader communications
Copyright (C) 2006, 2007, 2008\
 Ineiev<ineiev@users.sourceforge.net>, super V 93
This program is a part of the stribog host software section

stribog is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.*/
#include"ram_loader.h"
#include"serialia.h"
#include"snprintf_checked.h"
#include<stribog_crc32.h>
#include<stdio.h>
#include<time.h>
#include<ram_ldr.h>
static int
check_signature(const char*s)
{return*s==SOT&&s[1]==ACK;}
static int
sync_ram_loader(void)
{char s[2],c=SOT;int i,n;time_t t;
 static const int timeout=2;i=0;s[0]=s[1]=NACK;
 printf("synchronizing bootloader");
 while(1)
 {send_bytes(&c,1);
  printf("\nsync char sent; received:");fflush(stdout);
  t=time(0);
  while(time(0)-t<timeout)
  {for(n=0;n<sizeof(s)-1;n++)s[n]=s[n+1];
   n=lege(s-1+sizeof s,1);
   if(n>0)
   {printf(" %2.2X",0xFF&s[sizeof(s)-1]);fflush(stdout);
    if(check_signature(s))
    {printf("\nbootloader in sync\n");return 0;}
   }
  }
 }return!0;
}
static void
pack_num(char*s,unsigned long n)
{int i=0;
 for(i=0;i<bytes_per_word;i++,n>>=bits_per_byte)
  s[bytes_per_word-1-i]=n&((1<<bits_per_byte)-1);
}
static int
wait_for_ack(void)
{unsigned char c;int n=0;time_t t=time(0);
 while(time(0)-t<2){n=lege(&c,1);if(n==1)break;}
 if(n<1){printf("timeout\n");return-1;}
 if(c==ACK)return 0;printf("NACK %2.2X\n",c);
 t=time(0);drain_uart();return 1;
}
static int
send_block(unsigned long addr,char*s)
{char c[bytes_per_word];unsigned long crc;
 printf("%8.8lX..%8.8lX: ",addr,addr+packet_size-1);fflush(stdout);
 while(1)
 {c[0]=SOH;send_bytes(c,1);
  pack_num(c,addr);send_bytes(c,4);
  crc=form_crc((const crc32_input_array_token*)(&addr),1);
  pack_num(c,crc);send_bytes(c,4);
  if(wait_for_ack()){sync_ram_loader();continue;}
  send_bytes(s,packet_size);
  crc=form_crc((const crc32_input_array_token*)s,packet_size>>2);
  pack_num(c,crc);send_bytes(c,4);
  if(!wait_for_ack()){printf("ACK\n");return 0;}
  sync_ram_loader();
 }return 0;
}
static int
launch_program(unsigned long addr)
{char c[bytes_per_word];unsigned long crc; 
 do
 {c[0]=EOT;send_bytes(c,1);
  pack_num(c,addr);send_bytes(c,4);
  crc=form_crc((const crc32_input_array_token*)(&addr),1);
  pack_num(c,crc);send_bytes(c,4);printf("address sent\n");
 }while(wait_for_ack());
 printf("program launched\n");return 0;
}
int
load_target(const char*target_name)
{static const unsigned long ram_org=0x40000000;
 int i,ret=0;FILE*f=0;unsigned long addr;char s[packet_size];
 if(snprintf_checked(__FILE__,__LINE__,s,sizeof s,"%s.bin",target_name))
  return!0;
 if(sync_ram_loader())return!0;
 f=fopen(s,"rb");ret=!f;if(ret)goto x;
 if(!f){printf("no programme '%s' found\n",s);goto x;}
 addr=ram_org;
 do
 {for(i=0;i<packet_size;i++)
  {int c=getc(f);if(c==EOF)c=0;s[i]=c;}
  ret=send_block(addr,s);if(ret)goto x;
  addr+=packet_size;
 }while(!(feof(f)||ret));if(ret)goto x;
 ret=launch_program(ram_org);
 x:if(f)fclose(f);return ret;
}
