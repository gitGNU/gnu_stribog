#include"parse_tsip.h"/*parse_tsipex: parse_tsip module test*/
#include"error.h"
#include<stdint.h>
#include"crc32.h"
#define hostside_form_fix
#include"../../target/src/form_fix.h"
#include<stdio.h>
#include<stdlib.h>
static unsigned long long bytes;
static uint8_t buf[0x121];static int k;
static int lege(unsigned char*s,int n)
{int len,i;k=(1+(random()%5))<<2;if(n<(k+4)*2+4)return 0;
 for(i=0;i<k;i++)buf[i]=random();
 form_fix(buf,k>>2,(char*)s,&len);bytes+=len;return len;
}static uint32_t get_u(const unsigned char*s)
{return*s|(((uint32_t)s[1])<<8)|(((uint32_t)s[2])<<16)|(((uint32_t)s[3])<<24);}
static void expone(const unsigned char*s,int size)
{static unsigned long long u;int i;++u;
 unsigned long crc,cr;crc=form_crc(s,(size>>2)-1);cr=get_u(s+size-4);
 if(crc!=cr)
  error("wrong checksum (0x%8.8lX, received 0x%8.8lX), size %i\n",crc,cr,size);
 if(size!=k+4)
  error("message length changed (%i, received %i)\n",k,size-4);
 for(i=0;i<k;i++)if(buf[i]!=s[i])
  error("message changed (pos %i: 0x%2.2X, received 0x%2.2X)\n",buf[i],s[i]);
 if(u%83521==0)
 {printf("messages processed: %lluk (%llu kbytes)\r",u>>10,bytes>>10);
  fflush(stdout);
 }
}
int main(int argc,char**argv)
{tsip_buf*tb;int size,n,j;const unsigned char*_;
 unsigned char s[0x121];
 if(argc>1)
 {printf("escapes enabled\n");enable_escapes(!0);enable_push_esc=!0;}
 else printf("default behaviour (no escapes)\n");
 tb=new_tsip();
 while(1)if(0<(n=lege(s,sizeof s)))for(j=0;j<n;j++)
  if((_=parse_tsip(tb,s[j],&size)))expone(_,size);
 free_tsip(tb);return 0;
}/*This program is a part of the stribog host software section

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

Copyright (C) 2007 Ineiev <ineiev@users.sourceforge.net>*/
