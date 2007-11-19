/*elig: output every k-th stribog "adc" message; other messages unchanged
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

Copyright (C) 2006 D.Ineiev <ineiev@yahoo.co.uk>*/
#include"parse_tsip.h"
#include"error.h"
#include<stdio.h>
static const unsigned char dle=0x10,etx=0x03;static int k=200;
static void put_message(const unsigned char*c,int size)
{int i;putchar(dle);for(i=0;i<size;putchar(c[i++]))if(c[i]==dle)putchar(dle);
 putchar(dle);putchar(etx);
}
static void expone(const unsigned char*c,int size)
{static int i;if(size==24){if(++i==k)i=0;else return;}put_message(c,size);}
int main(int argc,char**argv)
{tsip_buf*tb=new_tsip();int size;const unsigned char*_;
 if(argc>1)sscanf(argv[1],"%i",&k);
 while(!feof(stdin)){if((_=parse_tsip(tb,getchar(),&size)))expone(_,size);}
 free_tsip(tb);return 0;
}
