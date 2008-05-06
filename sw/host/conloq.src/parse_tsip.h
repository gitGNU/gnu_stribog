/*parsing TSIP-like messages (DLE ... DLE DLE ... DLE ETX)
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

Copyright (C) 2007 Ineiev <ineiev@sourceforge.net>, super V 93*/
typedef struct tsip_buf tsip_buf;
void enable_escapes(int);/*enables tsip with first-byte escapes*/
const unsigned char*parse_tsip(tsip_buf*,unsigned char c,int*size);
tsip_buf*new_tsip(void);void free_tsip(tsip_buf*);void reset_tsip(tsip_buf*);
#define error_length(m,n,N) error("wrong message 0x%2.2X length: %i for %i\n",m,n,N)
