/*intlpc: writes checksum at address 0x14
  the input/output data format is binary
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
#include<stdio.h>
static unsigned long getul(char*s)/*lpc21xx are little-endian*/
{return(((unsigned long)*s)&0xFF)|((((unsigned long)s[1])&0xFF)<<8)|
 ((((unsigned long)s[2])&0xFF)<<16)|((((unsigned long)s[3])&0xFF)<<24);
}
static void putul(unsigned long u,char*s)
{*s++=u&0xFF;u>>=8;*s++=u&0xFF;u>>=8;*s++=u&0xFF;u>>=8;*s=u&0xFF;}
static void place_cksum(char s[0x20])
{unsigned long cs;int i;for(i=0x14;i<0x18;s[i++]=0);
 for(cs=i=0;i<0x20;i+=4)cs+=getul(s+i);putul(0-cs,s+0x14);
}
int main(void)
{int c,i;char s[0x20];for(i=0;i<sizeof(s);i++)s[i]=getchar();place_cksum(s);
 for(i=0;i<sizeof(s);i++)putchar(s[i]);
 do{c=getchar();if(c!=EOF)putchar(c);}while(c!=EOF);return 0;
}
