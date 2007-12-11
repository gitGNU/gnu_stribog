/* uint32_t extraction from array of bytes */
enum get_u_local_constants
{byte_bits=8,byte_mask=(1<<byte_bits)-1,adc_message_size=24};
static inline unsigned long
get_u(const unsigned char*s)
{return(byte_mask&*s)|(((unsigned long)byte_mask&s[1])<<byte_bits)|
  (((unsigned long)byte_mask&s[2])<<(byte_bits*2))|
   (((unsigned long)byte_mask&s[3])<<(byte_bits*3));
}/*This program is a part of the stribog host software section

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

Copyright (C) 2007 Ineiev<ineiev@users.sourceforge.net>, super V 93*/
