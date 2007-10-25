/*CRC32(CCITT-32): adjusted to 32-bit words algorithm from
Robert L. Hummel 
Programmer's Technical Reference: Data and Fax Communication
This implementation should be portable (within C99 standard)

This file is a part of stribog.

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

Copyright (C) 2006, 2007 Ineiev<ineiev@users.sourceforge.net>*/
#include<stdint.h>
#include"crc32.h"
static const uint8_t*get_u(crc32_input_array_type msg,uint32_t*x)
{*x=((uint32_t)(*msg++));*x|=((uint32_t)(*msg++))<<8;
 *x|=((uint32_t)(*msg++))<<16;*x|=((uint32_t)(*msg++))<<24;return msg;
}
unsigned long form_crc(crc32_input_array_type msg,unsigned n)
{uint32_t crc=~0,x;int j,k;const uint32_t poly=0xEDB88320;
 while(n--)
 {msg=get_u(msg,&x);crc^=x;for(j=0;j<32;j++){k=crc&1;crc>>=1;if(k)crc^=poly;}}
 crc=~crc;return crc;
}
