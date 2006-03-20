/*LPC2138: magnetic sensors control
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
#include"mag.h"
#include"adc.h"
#include"dac.h"
#include"../include/lpc2138.h"
#define SET	(1<<31)
#define RESET	(1<<16)
static inline void set_down(void){IO0CLR=SET;}
static inline void reset_down(void){IO1CLR=RESET;}
static inline void set_up(void){IO0SET=SET;}
static inline void reset_up(void){IO1SET=RESET;}
void init_mag(void)
{IO0DIR|=SET;IO1DIR|=RESET;set_down();reset_up();}
static int diff[3],x[3];
static int*func_(const unsigned*),*func0(const unsigned*);
static int*(*func)(const unsigned*)=func_;
static int*func3(const unsigned*a){reset_up();func=func0;return 0;}
int*func2(const unsigned*a)
{diff[0]=a[ADC_MX];diff[1]=a[ADC_MY];diff[2]=a[ADC_MZ];
 set_down();func=func3;return 0;
}
static int*func1(const unsigned*a){set_up();func=func2;return 0;}
static int reg_func(int d)
{if(!d)return 0;if(d>-4&&d<4)return d>0?1:-1;return d>>2;}
static int*func0(const unsigned*a)
{diff[0]-=a[ADC_MX];diff[1]-=a[ADC_MY];diff[2]-=a[ADC_MZ];
 x[0]-=reg_func(diff[0]);if(x[0]>2047)x[0]=2047;if(x[0]<-2047)x[0]=-2047;
 x[1]+=reg_func(diff[1]);if(x[1]>2047)x[1]=2047;if(x[1]<-2047)x[1]=-2047;
 x[2]-=reg_func(diff[2]);if(x[2]>2047)x[2]=2047;if(x[2]<-2047)x[2]=-2047;
 load0(x[2]);load1(x[0]);load2(x[1]);
 reset_down();func=func1;return x;
}
static int*func_(const unsigned*a){reset_down();func=func1;return 0;}
const int*process_mag(const unsigned*a)
{static int j;if(j++&0x1F)return 0;return func(a);}
