/*CRC32(CCITT-32) checksum
NB: this implementation tailored for and works on 
32-bit little-endian architectures only.*/
typedef unsigned crc32_input_array_token;
unsigned long form_crc(const crc32_input_array_token*msg,unsigned n);
/*This file is a part of the stribog project.

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

Copyright (C) 2006, 2007 Ineiev <ineiev@users.sourceforge.net>, super V 93*/
