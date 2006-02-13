/*LPC2138: leds output (pins A and B of J1 are to be connected to LEDs)
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
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Copyright (C) 2006 D.Ineiev <ineiev@yahoo.co.uk>*/
#include"led.h"
#include"../include/lpc2138.h"
#define pinmask	(3)
#define shift (16)
void leds_clr(int mask){IO0CLR=(mask&pinmask)<<shift;}
void leds_set(int mask){IO0SET=(mask&pinmask)<<shift;}
void init_led(void){IO0DIR|=pinmask<<shift;leds_set(3);}
