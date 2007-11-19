/*LPC2138: magnetic sensors control
 magnetic field sampling rate is 798.37 Hz
This file is a part of stribog.

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

Copyright (C) 2006, 2007 Ineiev<ineiev@users.sourceforge.net>, super V 93*/
#include"mag.h"
#include"adc.h"
#include"dac.h"
#include"../include/lpc2138.h"
#define SET	(1<<31)
#define RESET	(1<<16)
enum{scale=7};static int kx,ky,kz;
static inline void 
set_down(void){IO0CLR=SET;}
static inline void 
reset_down(void){IO1CLR=RESET;}
static inline void 
set_up(void){IO0SET=SET;}
static inline void 
reset_up(void){IO1SET=RESET;}
void 
set_mag_gains(int x,int y,int z){if(x)kx=x;if(y)ky=y;if(z)kz=z;}
void 
init_mag(void)
{IO0DIR|=SET;IO1DIR|=RESET;set_down();reset_up();kx=1<<scale;ky=100;kz=91;}
static int diff[3],x[3];
static int*func_(const unsigned*),*func0(const unsigned*);
static int*(*func)(const unsigned*)=func_;
static int*
func3(const unsigned*a){reset_up();func=func0;return 0;}
static int*
func2(const unsigned*a)
{diff[0]=a[ADC_MX];diff[1]=a[ADC_MY];diff[2]=a[ADC_MZ];
 set_down();func=func3;return 0;
}static int*
func1(const unsigned*a){set_up();func=func2;return 0;}
static int 
reg_func(int d)
{if(!d)return 0;if(d>-(1<<scale)&&d<(1<<scale))return d>0?1:-1;
 return d>>(scale+1);/*the portable (according to C99) way is
 {unsigned u=d<0?-d:d;u>>=scale+1;d=d<0?-(int)u:u;}return d;
 however, I tested gcc's for avr, m68k, arm, mips, msp430, ia32, powerpc
 and the shift always was arithmetical for signed int. 
 I believe any other behaviour is too strongly out of mainstream*/
}static int*
func0(const unsigned*a)
{diff[0]-=a[ADC_MX];diff[1]-=a[ADC_MY];diff[2]-=a[ADC_MZ];
 x[0]+=reg_func(diff[0]*kx);if(x[0]>2047)x[0]=2047;if(x[0]<-2047)x[0]=-2047;
 x[1]-=reg_func(diff[1]*ky);if(x[1]>2047)x[1]=2047;if(x[1]<-2047)x[1]=-2047;
 x[2]-=reg_func(diff[2]*kz);if(x[2]>2047)x[2]=2047;if(x[2]<-2047)x[2]=-2047;
 load0(x[2]);load1(-x[0]);load2(-x[1]);reset_down();func=func1;return x;
}static int*
func_(const unsigned*a){reset_down();func=func1;return 0;}
const int*
process_mag(const unsigned*a){return func(a);}
