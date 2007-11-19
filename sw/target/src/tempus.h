/*LPC2138: timer1 (system clock) setup and queries
 this module is responsible for PPS (signal A, rising edge) capture, too
This file has been written for the stribog project.

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
void init_tempus(void);unsigned long long tempus(void);
unsigned senius_tempus(void);
static inline unsigned 
iunius_tempus(void)
{
#define T1TC_pro_iuniore_tempore (*((volatile unsigned*)(0xE0008008)))
 return T1TC_pro_iuniore_tempore;
}
const unsigned*get_pps(void);
