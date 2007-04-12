#include<stdio.h>/*simple odometer firmware test*/
#include"serialia.h"/*Note: you should connect PC to DB9-M rather than DB9-F*/
void decode(const unsigned char*s)
{unsigned cnt=s[1]|(((unsigned)s[0])<<6),
 t=(((unsigned)s[4])<<12)|(((unsigned)s[3])<<6)|s[2],_,i;
 for(_=i=0;i<6;i++)_^=s[i];
 if(_)fprintf(stderr,"%s:%i: checksums don't match\n",__FILE__,__LINE__);
 printf("%.7u %u\n",t,cnt);
}
void process(int c)
{static unsigned char s[10];static int i;
 s[i++]=c&0x3F;if(i>8)i=0;if(!(c&(1<<6))){if(i>5)decode(s+i-6);i=0;}
}
int main(void)
{char c;initserialia("/dev/ttyS0");while(1)if(lege(&c,1)>0)process(c);return 0;}
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
