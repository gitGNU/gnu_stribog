/*LPC2138: magnetic sensors to DAC change response
 as in mag.c, the 'set-reset' magnetic sensor difference
 is forced to zero periodically, then the DAC values increase
 by 100 units, so we can see how the DAC signal change
 influences the 'set-reset' difference*/
#include"uart1.h"
#include"led.h"
#include"pll.h"
#include"tempus.h"
#include"power.h"
#include"adc.h"
#include"dac.h"
#include"../include/lpc2138.h"
#define SET	(1<<31)
#define RESET	(1<<16)
enum{scale=7};
static const int kx=64,ky=64,kz=64;static int close_loop=!0;
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
{if(!d)return 0;if(d>-(1<<scale)&&d<(1<<scale))return d>0?1:-1;
 return d>>(scale+1);
}
static int*func0(const unsigned*a)
{diff[0]-=a[ADC_MX];diff[1]-=a[ADC_MY];diff[2]-=a[ADC_MZ];
 if(close_loop)
 {x[0]+=reg_func(diff[0]*kx);if(x[0]>2047)x[0]=2047;if(x[0]<-2047)x[0]=-2047;
  x[1]+=reg_func(diff[1]*ky);if(x[1]>2047)x[1]=2047;if(x[1]<-2047)x[1]=-2047;
  x[2]+=reg_func(diff[2]*kz);if(x[2]>2047)x[2]=2047;if(x[2]<-2047)x[2]=-2047;
  load0(-x[2]);load1(-x[0]);load2(x[1]);
 }reset_down();func=func1;return x;
}
static int*func_(const unsigned*a){reset_down();func=func1;return 0;}
const int*process_mag(const unsigned*a){return func(a);}
#define FIX_LENGTH	(5)
static unsigned f[FIX_LENGTH];static int b[3],a[3],w[3];
static void form_data(unsigned d[FIX_LENGTH])
{const int*mag;unsigned*s=d;int t=0;const unsigned*adc;
 while(!(adc=get_adc()));
 if((mag=process_mag(adc)))
 {*a=*mag+(1<<12);a[1]=mag[1]+(1<<12);a[2]=mag[2]+(1<<12);
  *b=*diff;b[1]=diff[1];b[2]=diff[2];
 }*s++=iunius_tempus();
 *s++=(b[0]&0xFFF)|((b[1]&0xFFF)<<12)|((t&0xFF)<<24);
 *s++=(b[2]&0xFFF)|((a[0]&0x3FFF)<<12)|((t&0x1F00)<<(26-8));
 *s++=(a[1]&0x3FFF)|((a[2]&0x3FFF)<<14);
 *s++=(w[0]&0x3FF)|((w[1]&0x3FF)<<10)|((w[2]&0x3FF)<<20);
}
int main(void)
{int j=0;start_pll();init_power();init_led();led1_set();
 init_mag();connect_pll();init_adc();init_uart1();init_tempus();
 while(1)
 {form_data(f);if(send_fix(f,FIX_LENGTH)){j++;led1_set();led1_clr();}
  if(!close_loop){
   if(j&(1<<12))
   {led0_set();load0(-x[2]+100);load1(-x[0]+100);load2(x[1]+100);w[0]=1;}
   else{led0_clr();load0(-x[2]);load1(-x[0]);load2(x[1]);w[0]=0;}
   if(j>1<<15){close_loop=!0;j=0;}
  }else if(j>128)close_loop=0;
 }return 0;
}/*This file is a part of stribog.

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

