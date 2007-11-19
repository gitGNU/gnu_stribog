/*DAC functions
signals initial state before loading: LOAD=SC=HIGH

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
#include"pll.h"
#include"led.h"
#include"../include/lpc2138.h"
#define LOAD0	(1<<23)
#define LOAD1	(1<<18)
#define SC	(1<<28)
#define SDI	(1<<27)
static void _load0(unsigned addr,unsigned x)
{int i;IO1CLR=SC;IO1SET=SDI;IO1SET=SC;
 IO1CLR=SC;if(addr&1)IO1SET=SDI;else IO1CLR=SDI;IO1SET=SC;
 for(i=0;i<12;i++,x<<=1)
 {IO1CLR=SC;if(x&(1<<11))IO1SET=SDI;else IO1CLR=SDI;IO1SET=SC;}
 IO0CLR=LOAD0;IO0SET=LOAD0;
}
static void _load1(unsigned addr,unsigned x)
{int i;IO1CLR=SC;IO1SET=SDI;IO1SET=SC;
 IO1CLR=SC;if(addr&1)IO1SET=SDI;else IO1CLR=SDI;IO1SET=SC;
 for(i=0;i<12;i++,x<<=1)
 {IO1CLR=SC;if(x&(1<<11))IO1SET=SDI;else IO1CLR=SDI;IO1SET=SC;}
 IO0CLR=LOAD1;IO0SET=LOAD1;
}
static void reset_dacs(void)
{int i,x=2048;IO1SET=SC;IO0SET=LOAD0|LOAD1;
 IO1CLR=SC;IO1CLR=SDI;IO1SET=SC;IO1CLR=SC;IO1SET=SC;
 for(i=0;i<12;i++,x<<=1)
 {IO1CLR=SC;if(x&(1<<11))IO1SET=SDI;else IO1CLR=SDI;IO1SET=SC;}
 IO0CLR=LOAD0|LOAD1;IO0SET=LOAD0|LOAD1;
}
void init_dac(void)
{IO0DIR|=LOAD0|LOAD1;IO1DIR|=SC|SDI;IO1SET=SC;IO0SET=LOAD0|LOAD1;reset_dacs();}
void load0(int x){_load0(1,x+2048);}
void load1(int x){_load1(0,x+2048);}
void load2(int x){_load1(1,x+2048);}
