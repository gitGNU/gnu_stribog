/*LPC2138: PLL setup: multiplies frequency by 4;
 M=4; P=2 (should work for crystals from 10 to 15MHz)
 if crystal from 15 to 20 MHz needed, I propose M=3; P=2;
 if 20..25 MHz --- M=2; P=1; I like 14.7456MHz.

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
#include"pll.h"
#include"../include/lpc2138.h"
static inline void feed_pll(void)
{PLLFEED=PLLFEED_FIRST;PLLFEED=PLLFEED_SECOND;}
void start_pll(void)
{PLLCON=PLLCON_PLLE;feed_pll();PLLCFG=MSEL(4)|PSEL_2;feed_pll();}
void connect_pll(void)
{while(!(PLLSTAT&PLLSTAT_PLOCK));PLLCON=PLLCON_PLLE|PLLCON_PLLC;feed_pll();}
