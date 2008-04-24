/*CRC32(CCITT-32): restricted to N 32-bit words in message algorithm from
Robert L. Hummel 
Programmer's Technical Reference: Data and Fax Communication
This implementation should be portable (within C89 standard),
from 8-bit to 4913-bit architectures and higher*/
#include"crc32.h"
enum lesser_constants
{bits_per_byte=8,byte_mask=(1<<bits_per_byte)-1,bits_per_word=32};
static const unsigned long ul_mask=0xFFFFFFFFul;
static const unsigned char*
get_u(const crc32_input_array_token*msg,unsigned long*x)
{*x =((unsigned long)(byte_mask&*msg++))<<(bits_per_byte*0);
 *x|=((unsigned long)(byte_mask&*msg++))<<(bits_per_byte*1);
 *x|=((unsigned long)(byte_mask&*msg++))<<(bits_per_byte*2);
 *x|=((unsigned long)(byte_mask&*msg++))<<(bits_per_byte*3);return msg;
}unsigned long
form_crc(const crc32_input_array_token*msg,unsigned n)
{unsigned long crc=ul_mask,x;int j,k;const unsigned long poly=0xEDB88320ul;
 while(n--)
 {msg=get_u(msg,&x);crc^=x;
  for(j=0;j<bits_per_word;j++){k=crc&1;crc>>=1;if(k)crc^=poly;}
 }crc=(~crc)&ul_mask;return crc;
}/*This file is a part of stribog.

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

Copyright (C) 2006, 2007 Ineiev<ineiev@users.sourceforge.net>, super V 93*/

