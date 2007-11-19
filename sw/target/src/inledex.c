/*LPC2138 inline LED test
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

Copyright (C) 2006 D.Ineiev <ineiev@yahoo.co.uk>*/
#include"../include/lpc2138.h"
#include"pll.h"
#define pin0mask	(1<<19)
#define pin1mask	(1<<29)
static inline void led0_clr(){IO0CLR=pin0mask;}
static inline void led0_set(){IO0SET=pin0mask;}
static inline void led1_clr(){IO1CLR=pin1mask;}
static inline void led1_set(){IO1SET=pin1mask;}
static void init_led(void)
{PINSEL2=0;IO0DIR|=pin0mask;IO1DIR|=pin1mask;led0_set();led1_clr();}
static int i,j=pin0mask;
int main(void)
{start_pll();init_led();led1_set();connect_pll();
 while(1){if(!(i++&0xFF)){IO0SET=j;IO0CLR=j;}}return 0;
}
