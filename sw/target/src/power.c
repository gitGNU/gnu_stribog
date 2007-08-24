/*LPC2138: voltage regulators on/off
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
#include"../include/lpc2138.h"
#define _5V	(1<<30)
#define _A3V	(1<<17)
#define _A5V	(1<<7)
void switch_5V(int on){if(on)IO1DIR&=~_5V;else IO1DIR|=_5V;}
void switch_A5V(int on){if(on)IO0DIR&=~_A5V;else IO0DIR|=_A5V;}
void switch_A3V(int on){if(on)IO1DIR&=~_A3V;else IO1DIR|=_A3V;}
void init_power(void)
{IO1CLR=_5V|_A3V;IO1DIR&=~(_5V|_A3V);IO0CLR=_A5V;IO0DIR&=~(_A5V);}
