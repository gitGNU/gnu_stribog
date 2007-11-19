#include"led.h"/*LPC2138: accelerometer module test*/
#include"pll.h"
#include"accel.h"
static int i=1;
int main(void)
{start_pll();init_led();init_accel(9);led1_set();connect_pll();led1_set();
 while(1)
 {if(i++&(1<<17))led1_set();else led1_clr();
  if(get_accel()){led0_set();led0_clr();}
 }return 0;
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

