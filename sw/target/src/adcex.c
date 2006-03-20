/*LPC2138: ADC module test
When you apply 4.096V to pin 1 and enable AD1.7, AD1 is burnt (?)
 VERY strange things are observed.

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
#include"adc.h"
#include"pll.h"
#include"led.h"
static int j;
int main(void)
{int i=0;start_pll();init_led();led1_set();init_adc();connect_pll();
 while(1)
 {if(get_adc()){led1_set();led1_clr();}//j++;if(j&(1<<12))led1_set();else led1_clr();
  if(i++&(1<<17))led0_set();else led0_clr();
 }return 0;
}
