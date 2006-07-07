/*parsing TSIP-like messages (DLE ... DLE DLE ... DLE ETX)
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

Copyright (C) 2005 D.Ineiev <ineiev@yahoo.co.uk>, super V 93*/
#include"parse_tsip.h"
#include"error.h"
#include<stdlib.h>
#include<stdio.h>
static const unsigned char dle=0x10,etx=3;
struct tsip_buf{unsigned char s[256],pr,pqpr;int n,in,par;};
const unsigned char*parse_tsip(tsip_buf*t,unsigned char c,int*size)
{unsigned char*s=0;
 if(t->in)
 {t->s[(t->n)++]=t->pr;
  if(t->n>=sizeof(t->s)){error("too long message\n");t->in=0;}
  if(c==dle){if(!(t->par=!t->par))--(t->n);}
  if(c==etx&&t->pr==dle&&t->par){*size=t->n-1;t->in=0;s=t->s;}
 }else
 {if(c!=dle&&t->pr==dle&&t->pqpr==etx){t->in=!0;t->n=0;t->par=0;}
 }t->pqpr=t->pr;t->pr=c;return s;
}
void reset_tsip(tsip_buf*t){t->in=0;t->pqpr=dle;t->pr=etx;}
tsip_buf*new_tsip(void)
{tsip_buf*t=malloc(sizeof(tsip_buf));if(!t)return 0;reset_tsip(t);return t;}
void free_tsip(tsip_buf*t){if(t)free(t);}
