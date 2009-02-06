/*elk the LPC21x programmer: 2nd stage RAM bootloader constants
Copyright (C) 2008, 2009\
 Ineiev<ineiev@users.sourceforge.net>, super V 93
This program is a part of the stribog host software section

stribog is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.*/
enum ram_loader_constants
{SOH=1,SOT=4,EOT=5,ACK=6,NACK=0x15,
 packet_size=1<<10,bytes_per_word=4,bits_per_byte=8
};
