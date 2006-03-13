/*expon: decode stribog messages
This program is a part of the stribog host software section

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
#include"exp.h"
#include<stdint.h>
#include"crc32.h"
#include"parse_tsip.h"
#include"error.h"
#include<stdio.h>
#define FIX_LENGTH	(5)
static uint32_t get_u(const unsigned char*s)
{return*s|(((uint32_t)s[1])<<8)|(((uint32_t)s[2])<<16)|(((uint32_t)s[3])<<24);}
void expone(const unsigned char*s,int size)
{uint32_t crc,cr;if(size!=24){error("wrong size (%i for 24)\n",size);return;}
 crc=form_crc(s,FIX_LENGTH);cr=get_u(s+5*4);
 if(crc!=cr)
 {error("wrong checksum (0x%8.8lX, received 0x%8.8lX)\n",
  (unsigned long)crc,(unsigned long)cr);return;
 }
 {int a[3],b[3],w[3],T;unsigned long t,x;for(T=0;T<3;T++)b[T]=w[T]=0;
  t=get_u(s);x=get_u(s+=4);
  if(x&0x800)b[0]=-1&~(0xFFF);b[0]|=x&0xFFF;x>>=12;
  if(x&0x800)b[1]=-1&~(0xFFF);b[1]|=x&0xFFF;x>>=12;T=x&0xFF;x=get_u(s+=4);
  if(x&0x800)b[2]=-1&~(0xFFF);b[2]|=x&0xFFF;x>>=12;
  a[0]=x&0x3FFF;x>>=14;T|=(x&0x1F)<<8;
  if(T&0x1000)T=(-1&~(0x1FFF))|T;x=get_u(s+=4);
  a[1]=x&0x3FFF;x>>=14;a[2]=x&0x3FFF;x=get_u(s+=4);
  w[0]=x&0x3FF;x>>=10;w[1]=x&0x3FF;x>>=10;w[2]=x&0x3FF;
  printf("%lu %i %i %i"" %i %i %i"" %i %i %i"" %i.%4.4i\n",t,a[0],a[1],a[2],
   b[0],b[1],b[2],w[0],w[1],w[2],T>>4,(T&0xF)*625);
 }
}
