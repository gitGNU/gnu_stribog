/*LPC2138: LM74 (temperature sensor) test
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
#include"lm74.h"
#include"led.h"
#include"pll.h"
#include"tempus.h"
int main(void)
{int j=0;start_pll();init_led();init_tempus();init_lm74();connect_pll();
 //led1_clr();
 while(1)
 {get_temperature();led1_set();led1_clr();
  if(j++&(1<<12))led0_set();else led0_clr();
 }return 0;
}
