/*CRC32(CCITT-32): adjusted to 32-bit words algorithm from
Robert L. Hummel 
Programmer's Technical Reference: Data and Fax Communication
This file has been written for the stribog project.

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

Copyright (C) 2006 D.Ineiev <ineiev@yahoo.co.uk>*/
unsigned long form_crc(const unsigned*msg,unsigned n)
/*NB this works on 32-bit little-endian architectures only*/
{unsigned crc=~0,j,k;const unsigned poly=0xEDB88320;
 while(n--)
 {crc^=*msg++;for(j=0;j<32;j++){k=crc&1;crc>>=1;if(k)crc^=poly;}}
 return~crc;
}
