/*sample coil with 0 +-I0 current to check linearity
of the magnetic sensors.

We make a coil of non-magnetic linear material to produce 
constant value and different sign field. to do this we switch 
different ends of the coil to gnd and Vcc. the third point is 
zero, when we switch the coil off. it is necessary to check 
that the voltage on the coil has the same value for the
opposite points.

If the sensor is linear it's measurements should differ
by the same value between -I0 and zero and between zero and +I0*/
#include<avr/io.h>/*Fuse bytes are default*/
static void init(void){PORTC=PORTD=0;DDRD=0x01;DDRC=0xF;}
static void momentum(){PORTB|=1;PORTB&=~1;}
static void mora(void){long i;for(i=0;i<0x3FFFF;i++)momentum();}
static void minuta(void)
{long i;PORTD=0x1;for(i=0;i<0x3f;i++)momentum();PORTD=0;}
static void close_all(void){PORTC=0;minuta();}
static void _00(void){close_all();PORTC=0x2|0x8;}
static void _01(void){close_all();PORTC=0x1|0x8;}
static void _10(void){close_all();PORTC=0x2|0x4;}
int main(void)
{init();while(1){_00();mora();_01();mora();_10();mora();}return 0;}
/*This is an auxiliary part of stribog
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

Copyright (C) 2007 D.Ineiev <ineiev@yahoo.co.uk>*/
