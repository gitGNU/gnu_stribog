/*LPC2138: here many things are collected
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
enum message_lengths
{pps_length=1,temp_length=2,gps_data_length=3,stat_length=4,fix_length=5};
static unsigned adxrs_temp[3],_2048;
static void 
send_pps(void)
{static int pps_got;static unsigned pps[pps_length],k;const unsigned*_;
 if((_=get_pps())){pps[0]=*_;pps_got=!0;k++;}
 if(pps_got)pps_got=send_fix(pps,pps_length);
}static void 
check_gps_data(void)
{static unsigned _[gps_data_length];char*s=(char*)_;static int data_gotten;
 if(data_gotten){data_gotten=send_fix(_,gps_data_length);return;}
 if(!(data_gotten=receive0(s,sizeof(_)-1)))return;s[sizeof(_)-1]=data_gotten;
 {int remainder=data_gotten-1-sizeof _;
  if(remainder>0)
  {char*rem;const char*ov=(const char*)&uart0_overflows;int i;
   if(remainder>sizeof uart0_overflows)remainder=sizeof uart0_overflows;
   rem=s+(sizeof _)-1;for(i=0;i<remainder;i++)*--rem=*ov++;
  }
 }data_gotten=send_fix(_,gps_data_length);
}static void 
correct_adc(unsigned w[3],unsigned t[3],unsigned _2048)
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
static void 
process_accel(unsigned*out)
{int j;const unsigned*a;if(!(a=get_accel()))return;for(j=0;j<3;j++)out[j]=a[j];}
static int adc_missed;
static int 
send_msmt(void)
{static unsigned f[fix_length],a[3];const int*mag;unsigned*s=f,w[3];int t;
 const unsigned*adc;static int i,pending;static int b[3];
 if(pending){pending=send_fix(f,fix_length);}
 if(!(adc=get_adc()))return 0;_2048=adc[ADC_2048];
 adxrs_temp[0]=adc[ADC_TX];adxrs_temp[1]=adc[ADC_TY];adxrs_temp[2]=adc[ADC_TZ];
 if(!(mag=process_mag(adc)))return 0;if(3&++i)return 0;if(pending)adc_missed++;
 *b=*mag;b[1]=mag[1];b[2]=mag[2];t=get_temperature();
 w[0]=adc[ADC_WX];w[1]=adc[ADC_WY];w[2]=adc[ADC_WZ];
 correct_adc(w,adxrs_temp,_2048);process_accel(a);
 *s++=iunius_tempus();*s++=(b[0]&0xFFF)|((b[1]&0xFFF)<<12)|((t&0xFF)<<24);
 *s++=(b[2]&0xFFF)|((a[0]&0x3FFF)<<12)|((t&0x1F00)<<(26-8));
 *s++=(a[1]&0x3FFF)|((a[2]&0x3FFF)<<14);
 *s=(w[0]&0x3FF)|((w[1]&0x3FF)<<10)|((w[2]&0x3FF)<<20);
 pending=send_fix(f,fix_length);return!0;
}static void 
send_temp(int ms)
{static unsigned t[temp_length],i;unsigned*s=t;static const unsigned N=100;
 if(ms)i++;if(i<N)return;*s++=_2048;
 *s=adxrs_temp[0]|(adxrs_temp[1]<<10)|(adxrs_temp[2]<<20);
 if(!send_fix(t,temp_length))i=0;
}static void
parse_settings(const unsigned char*s,int n)
{int kx,ky=0,kz=0,acc_prescaler=9;
 if(n>0)kx=*s;if(n>1)ky=s[1];if(n>2)kz=s[2];set_mag_gains(kx,ky,kz);
 if(n>3)acc_prescaler=s[3];init_accel(acc_prescaler);
}static void
init_all(void)
{unsigned char settings[0x11];int n;
 start_pll();init_power();init_led();init_lm74();
 init_mag();connect_pll();init_adc();init_uart1();//led1_set();
 init_tempus();n=init_uart0(settings,sizeof(settings));
 if(n>0)parse_settings(settings,n);
}enum multa_constants
{ushort_bits=16,ushort_mask=(1<<ushort_bits)-1,
 tmin_initial=ushort_mask
};
static unsigned tmax,tmin=tmin_initial,tsum,tsum_N;
static void 
send_stat(int ms)
{static unsigned st[stat_length],i;static const unsigned N=400;
 if(ms)i++;if(i<N)return;
 if(!st[0])
 {st[0]=tmax|(tmin<<ushort_bits);
  st[1]=(adc_missed&ushort_mask)|((uart0_overflows<<16)&ushort_mask);
  st[2]=(accel_error_count&ushort_mask)|((tsum>>ushort_bits)<<ushort_bits);
  st[3]=tsum_N;tsum=tmax=tsum_N=0;tmin=tmin_initial;
 }if(!send_fix(st,stat_length))st[0]=i=0;
}int 
main(void)
{int j=0,ms;init_all();
 while(1)
 {unsigned t=iunius_tempus();
  ms=send_msmt();send_temp(ms);send_pps();check_gps_data();send_stat(ms);
  if((j++&(1<<15)))led0_set();else led0_clr();
  t=iunius_tempus()-t;if(t>tmax)tmax=t;if(tmin>t)tmin=t;
  tsum+=t;tsum_N++;
 }return 0;
}
