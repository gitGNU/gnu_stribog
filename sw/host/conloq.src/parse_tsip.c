/*parsing TSIP-like messages (DLE ... DLE DLE ... DLE ETX)
Copyright (C) 2007, 2008, 2009\
 Ineiev <ineiev@users.sourceforge.net>, super V 93
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
along with this program. If not, see <http://www.gnu.org/licenses/>.

When the message begins with ESC=0x17 the first byte should be
swallowed and the second should be DLE, ETX or ESC*/
#include"parse_tsip.h"
#include<stribog_error.h>
#include<stdlib.h>
static const unsigned char dle=0x10,etx=3,esc=0x17;static int fix_escapes;
struct tsip_buf
{unsigned char s[0x22],pr,pqpr;int n,in,par,chained_in,f_esc;
 unsigned long long count;
};const unsigned char*
parse_tsip(tsip_buf*t,unsigned char c,int*size)
{unsigned char*s=0;t->count++;
 if(t->in)
 {if(t->n==1)
  {if(t->s[0]!=esc||!t->f_esc){t->s[1]=t->s[0];++(t->n);}else
   {if(t->s[0]==esc&&!(dle==t->pr||esc==t->pr||etx==t->pr))
     error("escape used for wrong (%2.2X) byte at %llu\n",t->pr,t->count);
   }
  }t->s[(t->n)++]=t->pr;
  if(t->n>=sizeof(t->s)){error("too long message at %llu\n",t->count);t->in=0;}
  if(c==dle)if((t->par=!t->par))--(t->n);
  if(c==etx&&t->pr==dle&&!t->par){*size=t->n-2;t->in=0;t->chained_in=!0;s=t->s+1;}
 }else
 {if(((c!=dle&&c!=etx)||t->chained_in)&&t->pr==dle&&t->pqpr==etx)
  {t->in=!0;t->n=0;t->par=!0;}t->chained_in=0;
 }t->pqpr=t->pr;t->pr=c;return s;
}void
reset_tsip(tsip_buf*t)
{t->chained_in=0;t->in=0;t->pqpr=dle;t->pr=etx;t->count=0;t->f_esc=fix_escapes;}
void
enable_escapes(int x){fix_escapes=x;}
tsip_buf*new_tsip(void)
{tsip_buf*t=malloc(sizeof(tsip_buf));if(!t)return 0;reset_tsip(t);return t;}
void
free_tsip(tsip_buf*t){if(t)free(t);}

