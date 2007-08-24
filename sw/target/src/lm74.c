/*LPC2138: LM74 (temperature sensor) control
the interface is slow; delays have to be inserted
Timer1 is assumed to be initiated

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
along with this program. If not, see <http://www.gnu.org/licenses/>.

Copyright (C) 2006 D.Ineiev <ineiev@yahoo.co.uk>*/
#include"lm74.h"
#include"../include/lpc2138.h"
#define CS	(1<<23)
#define CLK	(1<<24)
#define SIO	(1<<12)
void init_lm74(void){IO1DIR|=CS|CLK;IO1SET=CS;}
static void delay(void)
{static const int dt=4;unsigned t=T1TC;
 if(t+dt>t)while(T1TC<t+dt);else{while(T1TC>1<<30);while(T1TC<dt);}
}
int get_temperature(void)
{int i,c;IO1CLR=CS;delay();IO1SET=CLK;delay();if(IO0PIN&SIO)c=1;else c=0;
 for(i=0;i<15;i++)
 {IO1CLR=CLK;delay();c<<=1;if(IO0PIN&SIO)c|=1;IO1SET=CLK;delay();}
 IO1SET=CS;IO1CLR=CLK;return c>>3;
}
void turn_lm74(int off){/*not implemented yet*/}
