/*parse_tsipex: parse_tsip module test
Copyright (C) 2007, 2008 Ineiev<ineiev@users.sourceforge.net>, super V 93
This program is a part of the stribog host software section

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
#include"parse_tsip.h"
#include<stribog_error.h>
#include"crc32.h"
#define hostside_form_fix
#include"../../common/form_fix.h"
#include"get_u.h"
#include<stdio.h>
#include<stdlib.h>
static unsigned long long bytes_processed;
crc32_input_array_token buf[0x121];int message_length;
int
lege(unsigned char*s,int n)
{int len,i;message_length=(1+(random()%5))<<2;
 if(n<(message_length+4)*2+4)return 0;
 for(i=0;i<message_length;i++)buf[i]=random();
 form_fix(buf,message_length>>2,(char*)s,&len);bytes_processed+=len;return len;
}void
expone(const unsigned char*s,int size)
{static unsigned long long u;int i;
 unsigned long crc,cr;
 ++u;crc=form_crc(s,(size>>2)-1);cr=get_u(s+size-4);
 if(crc!=cr)
  error("wrong checksum (0x%8.8lX, received 0x%8.8lX), size %i\n",crc,cr,size);
 if(size!=message_length+4)
  error("message length changed (%i, received %i)\n",message_length,size-4);
 for(i=0;i<message_length;i++)if(buf[i]!=s[i])
  error("message changed (pos %llu: 0x%2.2X, received 0x%2.2X)\n",
   bytes_processed,buf[i],s[i]);
 if(u%83521==0)
 {printf("messages processed: %lluKi (%llu Kibytes)\r",
   u>>10,bytes_processed>>10);
  fflush(stdout);
 }
}int
main(int argc,char**argv)
{tsip_buf*tb;int size,n,j;const unsigned char*_;unsigned char s[0x121];
 init_error(*argv);
 if(argc>1)
 {printf("escapes enabled\n");enable_escapes(!0);enable_push_esc=!0;}
 else printf("default behaviour (no escapes)\n");
 tb=new_tsip();
 while(1)if(0<(n=lege(s,sizeof s)))for(j=0;j<n;j++)
  if((_=parse_tsip(tb,s[j],&size)))expone(_,size);
 free_tsip(tb);return 0;
}
