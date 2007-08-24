/*LPC2138 simple test
This file has been written for the stribog project.

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.

Copyright (C) 2006 D.Ineiev <ineiev@yahoo.co.uk>*/
#include"led.h"
static int i=1;const int j=1;
int main(void)
{int k=11;volatile int l=2,m;init_led();
 while(1)
 {if(i++&(1<<15)){led1_set();led0_clr();}else{led0_set();led1_clr();}
  k++;if(!k)k=1;l+=0x11;m=l/k;
 }return 0;
}
