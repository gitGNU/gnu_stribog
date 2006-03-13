/*LPC2138: voltage regulators on/off example
 power on times is about 0.1ms; power off --- 0.1s
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
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Copyright (C) 2006 D.Ineiev <ineiev@yahoo.co.uk>*/
#include"power.h"
int main(void)
{int i=0;init_power();
 while(1)
  if(i++&(1<<16)){switch_5V(0);switch_A3V(0);switch_A5V(0);}
  else{switch_5V(1);switch_A3V(1);switch_A5V(1);}
 return 0;
}
