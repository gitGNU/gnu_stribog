/*LPC2138: here many things are collected
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
#include"uart1.h"
#include"uart0.h"
#include"led.h"
#include"pll.h"
#include"tempus.h"
#include"power.h"
#include"lm74.h"
#include"adc.h"
#include"accel.h"
#include"mag.h"
#define FIX_LENGTH	(5)
#define GPS_DATA_LENGTH	(3)
#define TEMP_LENGTH	(2)
#define PPS_LENGTH	(1)
static unsigned adxrs_temp[3],_2048;
static void send_pps(void)
{static int pps_got;static unsigned pps,k;const unsigned*_;
 if((_=get_pps())){pps=*_;pps_got=!0;k++;}
 if(pps_got)pps_got=send_fix(&pps,PPS_LENGTH);
}
static void check_gps_data(void)
{static unsigned _[GPS_DATA_LENGTH];char*s=(char*)_;
 static int data_got;if(data_got){data_got=send_fix(_,GPS_DATA_LENGTH);return;}
 if(!(data_got=receive0(s,sizeof(_)-1)))return;s[sizeof(_)-1]=data_got;
 data_got=send_fix(_,GPS_DATA_LENGTH);
}
static void correct_adc(unsigned w[3],unsigned t[3],unsigned _2048)
{static unsigned _8192,_,n,v,k;int i,d;static const int a0=641;
 _+=_2048;if(n++==3){v=!0;n=0;_8192=(_>>2)-a0;_=0;}
 if(v)d=_8192;else d=_2048-a0;k=((a0*a0-d*(a0+20)+d*d)*5+(42<<10));
 for(i=0;i<3;i++){w[i]=((w[i]*k)>>21);t[i]=((t[i]*k)>>21);}
}
/*static inline int median(int*a)//we want a better program to filter spurs
{if(*a>=a[1])
 {if(a[1]>=a[2])return a[1];else{if(a[2]<=*a)return a[2];else return*a;}
 }else
 {if(*a>=a[2])return*a;else{if(a[2]<=a[1])return a[2];else return a[1];}}
 return*a;
}
static void process_accel(unsigned*out)
{const unsigned*acc;static int i,a[3][3],j,v,spur[3];if(!(acc=get_accel()))return;
 if(++i>2){i=0;v=!0;}if(!v){for(j=0;j<3;j++){a[j][i]=out[j]=acc[j];}return;}
 for(j=0;j<3;j++)
 {if(spur[j]){a[j][i]=acc[j];spur[j]=0;}
  else{int d=a[j][i]-(int)acc[j];if(d<-1000||d>1000){spur[j]=d;continue;}else a[j][i]=acc[j];}
  out[j]=median(a[j]);
 }
}*/
/*static void process_accel(unsigned*out)//this will cut blows. design it at the host side first
{int j,d;const unsigned*acc;static int i,spur[3];if(!(acc=get_accel()))return;
 for(j=0;j<3;j++)
 {d=(int)acc[j]-out[j];
  if(d<-1000||d>1000){if(spur[j]&0x7==0x7)out[j]=acc[j];spur[j]|=1<<i;}
  else{out[j]=acc[j];spur[j]=0;}
 }if(i++>2)i=0;
}*/
static void process_accel(unsigned*out)
{int j;const unsigned*a;if(!(a=get_accel()))return;for(j=0;j<3;j++)out[j]=a[j];}
static int send_msmt(void)
{static unsigned f[FIX_LENGTH],a[3];const int*mag;unsigned*s=f,w[3];int t;
 const unsigned*adc;static int i,pending;static int b[3];
 if(pending){pending=send_fix(f,FIX_LENGTH);/*if(!pending){led1_set();led1_clr();}*/}
 if(!(adc=get_adc()))return 0;_2048=adc[ADC_2048];
 adxrs_temp[0]=adc[ADC_TX];adxrs_temp[1]=adc[ADC_TY];adxrs_temp[2]=adc[ADC_TZ];
 if((mag=process_mag(adc))){if(i++&3)return 0;}else return 0;
 *b=*mag;b[1]=mag[1];b[2]=mag[2];t=get_temperature();
 w[0]=adc[ADC_WX];w[1]=adc[ADC_WY];w[2]=adc[ADC_WZ];
 correct_adc(w,adxrs_temp,_2048);process_accel(a);
 *s++=iunius_tempus();*s++=(b[0]&0xFFF)|((b[1]&0xFFF)<<12)|((t&0xFF)<<24);
 *s++=(b[2]&0xFFF)|((a[0]&0x3FFF)<<12)|((t&0x1F00)<<(26-8));
 *s++=(a[1]&0x3FFF)|((a[2]&0x3FFF)<<14);
 *s=(w[0]&0x3FF)|((w[1]&0x3FF)<<10)|((w[2]&0x3FF)<<20);
 pending=send_fix(f,FIX_LENGTH);/*if(!pending){led1_set();led1_clr();}//ne micet*/
 return!0;
}
static void send_temp(int ms)
{static unsigned t[2],i;unsigned*s=t;static const unsigned N=100;
 if(ms)i++;if(i<N)return;*s++=_2048;
 *s=adxrs_temp[0]|(adxrs_temp[1]<<10)|(adxrs_temp[2]<<20);
 if(!send_fix(t,TEMP_LENGTH))i=0;
}
int main(void)
{int j=0,ms;start_pll();init_power();init_led();init_lm74();init_accel();//led1_clr();
 init_mag();connect_pll();init_adc();init_uart1();init_uart0();init_tempus();
 while(1)
 {ms=send_msmt();send_temp(ms);send_pps();check_gps_data();
  if((j++&(1<<15)))led0_set();else led0_clr();
 }return 0;
}
