#include"hodo.h"/*decode odometer messages*/
#include"error.h"
#include<stdio.h>
static int output_next;static unsigned char s[8],i;
static unsigned _0=~0;static unsigned long long x;
void proc_hodo(unsigned char c,int silent,double t)
{if(!silent)output_next=!0;s[i++]=c&0x3F;if(i>sizeof(s))i=0;
 if(!(c&(1<<6)))
 {if(i>5)
  {unsigned _,d,ts;unsigned char sum;i-=6;
   for(_=sum=0;_<6;_++)sum^=s[i+_];if(sum)error("hodo checksums don't match\n");
   _=s[i+1]|(((unsigned)s[i])<<6);
   ts=(((unsigned)s[i+2])<<12)|(((unsigned)s[i+3])<<6)|s[i+4];
   if(~_0)
   {d=(_<_0?(1<<12):0)+_-_0;x+=d;
    if(output_next)printf("odo: %.8f %u %llu\n",t,ts,x);output_next=0;
   }_0=_;
  }i=0;
 }
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
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Copyright (C) 2007 D.Ineiev <ineiev@yahoo.co.uk>*/
