/*LPC2138: ADC module test
This file is a part of stribog.

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

Copyright (C) 2006, 2007 D.Ineiev <ineiev@yahoo.co.uk>*/
#include"adc.h"
#include"pll.h"
#include"led.h"
int main(void)
{int i=0;start_pll();init_led();//led1_set();
 init_adc();connect_pll();
 while(1)
 {if(get_adc()){led1_set();led1_clr();}
  if(i++&(1<<17))led0_set();else led0_clr();
 }return 0;
}
