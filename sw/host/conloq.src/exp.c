/*decode stribog messages
Copyright (C) 2006, 2007, 2008, 2009\
 Ineiev <ineiev@users.sourceforge.net>, super V 93
This program is a part of the stribog host software section

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.*/
#include"exp.h"
#include<stribog_crc32.h>
#include<stribog_error.h>
#include<stdio.h>
#include"exp_gps.h"
#include"get_u.h"
#include"verbosity_level.h"
static double freq=14745600.+8794;static FILE*gps_extracted;
static unsigned leaps;static int period=1,verbous=0;
static unsigned long long time_stamp;
static double
mcu_stamp(void){return time_stamp/freq;}
static double
mcu_time(unsigned long t)
{static int cycled=!0;if(t<(1<<30)&&!cycled){leaps++;cycled=1;}
 if(t>(~0)-(1<<30))cycled=0;time_stamp=t|(((unsigned long long)leaps)<<32);
 return mcu_stamp();
}int
init_exp(int p)
{init_gps();
 if(get_interaction_mode()!=interactive_mode)
  gps_extracted=/*FIXME customize this*/fopen("gps.log","wb");
 if(p>0)period=p;else verbous=-p+1;return 0;
}void
close_exp(void){close_gps();if(gps_extracted)fclose(gps_extracted);}
static unsigned temperature[4];
static int
exp_temp(const unsigned char*s)
{unsigned _2048,t[3];_2048=get_u(s);s+=4;t[0]=get_u(s);
 t[2]=t[0]>>20;t[1]=(t[0]>>10)&0x3FF;t[0]&=0x3FF;
 printf("temp: %.8f %u %u %u %u\n",mcu_stamp(),
  temperature[0]=t[0],temperature[1]=t[1],
  temperature[2]=t[2],temperature[3]=_2048);return 0;
}static double latest_pps=-1;
double
correct_utc_second(double utc,double t_mcu)
{static double dutc=-3.*24*3600;int i,j;double dt;if(latest_pps<0)return t_mcu;
 i=t_mcu-latest_pps;dt=t_mcu-latest_pps-i;
 while(dt<0){i--;dt=t_mcu-latest_pps-i;}j=i;
 if(dutc>-2.*24*3600)
 {while(dutc-(utc-latest_pps-i)<-.5)++i;while(dutc-(utc-latest_pps-i)>.5)--i;}
 if(j-i<-3||j-i>3)
  error("t_mcu=%.4f: something wrong with our time difference\n",t_mcu);
 dutc=utc-latest_pps-i;
 printf("corr.sec: %.8f %.8f %i %.8f %.8f %.8f\n",
   t_mcu,latest_pps,i,dt,utc-t_mcu-dt,dutc);
 return t_mcu-dt;
}static int
nearest_int(double x){return x+.5;}
static int
exp_pps(const unsigned char*s)
{static unsigned t0,t0f,loops,v,vf;static double df;
 double d,thr,tmcu;unsigned t=get_u(s),dt,l=0;
 if(t0>t){l=1;loops++;}dt=nearest_int((t-t0)/freq);
 tmcu=t+(double)((unsigned long long)loops*(1ull<<32));
 d=v?(double)l*(1ull<<32)+t-t0-dt*freq:0;
 printf("pps_in:  %.8f %.0f %g\n",mcu_time(tmcu),tmcu,d);
 if(!v){t0=t;v=!0;return 0;}
 if(!vf)
 {t0=t0f=t;df=d;if(d>10000||d<-10000)return 0;
  vf=!0;printf("ppsdf0: %.8f %.0f %g\n",mcu_stamp(),tmcu,d);
 }dt=nearest_int((t-t0f)/(freq+df));l=t0f>t;
 d=(double)l*(1ull<<32)+t-t0f-dt*(freq+df);thr=dt*1+3;
 if(d<-thr||d>thr)
 {t0f=t0=t;printf("ppsr: %.8f %.0f %g %g\n",mcu_stamp(),tmcu,d,thr);return 0;}
 printf("pps: %.8f %.0f %g\n",mcu_stamp(),tmcu,d);latest_pps=mcu_stamp();
 if(dt){df+=.25*d/dt;printf("ppsdf: %.8f %.0f %g\n",mcu_stamp(),tmcu,df);}
 t0f=t0=t;return 0;
}static int
exp_adc(const unsigned char*s)
{static int i;int a[3],b[3],w[3],T,j;unsigned long t,x;
 static double mcu_t,a_[3],b_[3],w_[3],T_;for(j=0;j<3;j++)b[j]=w[j]=0;
 if(period<0)return 0;t=get_u(s);x=get_u(s+=4);
 if(x&0x800)b[0]=-1&~(0xFFF);b[0]|=x&0xFFF;x>>=12;
 if(x&0x800)b[1]=-1&~(0xFFF);b[1]|=x&0xFFF;x>>=12;T=x&0xFF;x=get_u(s+=4);
 if(x&0x800)b[2]=-1&~(0xFFF);b[2]|=x&0xFFF;x>>=12;
 a[0]=x&0x3FFF;x>>=14;T|=(x&0x1F)<<8;
 if(T&0x1000)T=(-1&~(0x1FFF))|T;x=get_u(s+=4);
 a[1]=x&0x3FFF;x>>=14;a[2]=x&0x3FFF;x=get_u(s+=4);
 w[0]=x&0x3FF;x>>=10;w[1]=x&0x3FF;x>>=10;w[2]=x&0x3FF;
 T_+=T;mcu_t+=mcu_time(t);for(j=0;j<3;j++){a_[j]+=a[j];b_[j]+=b[j];w_[j]+=w[j];}
 if(++i!=period)return 0;i=0;
 printf("adc:  %.8f %.0f %.0f %.0f"" %+05.0f %+05.0f %+05.0f"
   " %04.0f %04.0f %04.0f"" %3.4f",
  mcu_t/period,a_[0]/period,a_[1]/period,a_[2]/period,
  b_[0]/period,b_[1]/period,b_[2]/period,
  w_[0]/period,w_[1]/period,w_[2]/period,T_/16/period);
 if(period<=1)for(j=0;j<4;j++)printf(" %u",temperature[j]);putchar('\n');
 for(j=0;j<3;j++)a_[j]=b_[j]=w_[j]=0;T_=0;mcu_t=0;return 0;
}static int
check_gps_overflows(const unsigned char*s)
{unsigned long n=0,k,sh=0;static unsigned long n0;int r=0;
 if(!verbous)return 0;
 printf("gps_cont: %2.2X %2.2X %2.2X %2.2X %2.2X\n",s[7],s[8],s[9],s[10],s[11]);
 s+=12;k=*--s;
 if(verbous>2)printf("gps_message_length: %.8f %lu\n",mcu_stamp(),k);
 printf("gps_ascii: %.8f ",mcu_stamp());
 if(verbous>3)
 {for(n=0;n<k;n++)if(s[n-11]<0x80&&s[n-11]>' ')printf("%c",s[n-11]);
  putchar('\n');
 }k=11-k;
 if(k)
 {printf("gps_uart_ovfl: %.8f %lu ",mcu_stamp(),k);if(k>4)k=4;
  while(k--){n|=((unsigned long)*--s)<<sh;sh+=8;}printf("%lu\n",n);
  if(n!=n0)r=!0;n0=n;
 }return 0;
}static int
exp_stat(const unsigned char*s)
{unsigned long tmax=get_u(s),adc_missed=get_u(s+=4),accel_errors=get_u(s+=4),
  tsum_N=get_u(s+=4),tsum,tmin,uart0_overflows;
 static const double sec_to_us=1e6;
 tmin=(tmax>>16)&((1<<16)-1);tmax&=((1<<16)-1);
 uart0_overflows=(adc_missed>>16)&((1<<16)-1);adc_missed&=((1<<16)-1);
 tsum=(accel_errors>>16)&((1<<16)-1);accel_errors&=((1<<16)-1);
 printf("stat: %.8f %.3f %.3f %lu %.3f %lu %lu %lu\n",
  mcu_stamp(),(double)tmin/freq*sec_to_us,
  (double)tsum*(1<<16)/tsum_N/freq*sec_to_us,tsum_N,
  (double)tmax/freq*sec_to_us,
  adc_missed,accel_errors,uart0_overflows);return 0;
}int
expone(const unsigned char*s,int size)
{unsigned long crc,cr;crc=form_crc(s,(size>>2)-1);cr=get_u(s+size-4);
 if(crc!=cr)
 {error("wrong checksum (0x%8.8lX, received 0x%8.8lX), size %i\n",
  (unsigned long)crc,(unsigned long)cr,size);return!0;
 }
 switch(size)
 {case 8:return exp_pps(s);case 12:return exp_temp(s);
  case 16:
  {int r=check_gps_overflows(s);r|=exp_gps(mcu_stamp(),s,gps_extracted);return r;}
  case 20:return exp_stat(s);case 24:return exp_adc(s);
  default:error("wrong size (%i for 24 or 20 or 16 or 12 or 8)\n",size);
 }return!0;
}
