/*decode stribog messages
This program is a part of the stribog host software section

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
#include"exp.h"
#include<stdint.h>
#include"crc32.h"
#include"error.h"
#include<stdio.h>
#include"exp_gps.h"
static double freq=14745600.+8550;static unsigned leaps;static int period=1;
static unsigned long long time_stamp;static FILE*gps_extracted;
static double mcu_stamp(void){return time_stamp/freq;}
static double mcu_time(uint32_t t)
{static int cycled=!0;if(t<(1<<30)&&!cycled){leaps++;cycled=1;}
 if(t>(~0)-(1<<30))cycled=0;time_stamp=t|(((unsigned long long)leaps)<<32);
 return mcu_stamp();
}
int init_exp(int x,int p)
{init_gps(x);if(x)gps_extracted=fopen("gps.log","wb");if(p)period=p;return 0;}
void close_exp(void){close_gps();if(gps_extracted)fclose(gps_extracted);}
static uint32_t get_u(const unsigned char*s)
{return*s|(((uint32_t)s[1])<<8)|(((uint32_t)s[2])<<16)|(((uint32_t)s[3])<<24);}
static void exp_temp(const unsigned char*s)
{unsigned _2048,t[3];_2048=get_u(s);s+=4;t[0]=get_u(s);
 t[2]=t[0]>>20;t[1]=(t[0]>>10)&0x3FF;t[0]&=0x3FF;
 printf("temp: %.8f %u %u %u %u\n",
   mcu_stamp(),t[0],t[1],t[2],_2048);
}
static void exp_pps(const unsigned char*s)
{static unsigned t0,loops,v;double d;unsigned t=get_u(s),dt,l=0;
 if(t0>t){l=1;loops++;}dt=((double)(t-t0)+.5*freq)/freq;
 d=v?(double)l*(1ull<<32)+t-t0-dt*freq:0;
 printf("pps:  %.8f %.0f %g\n",mcu_stamp(),
  t+(double)((unsigned long long)loops*(1ull<<32)),d);
 t0=t;v=!0;
}
static void exp_adc(const unsigned char*s)
{static int i;int a[3],b[3],w[3],T,j;unsigned long t,x;
 static double mcu_t,a_[3],b_[3],w_[3],T_;for(j=0;j<3;j++)b[j]=w[j]=0;
 if(period<0)return;t=get_u(s);x=get_u(s+=4);
 if(x&0x800)b[0]=-1&~(0xFFF);b[0]|=x&0xFFF;x>>=12;
 if(x&0x800)b[1]=-1&~(0xFFF);b[1]|=x&0xFFF;x>>=12;T=x&0xFF;x=get_u(s+=4);
 if(x&0x800)b[2]=-1&~(0xFFF);b[2]|=x&0xFFF;x>>=12;
 a[0]=x&0x3FFF;x>>=14;T|=(x&0x1F)<<8;
 if(T&0x1000)T=(-1&~(0x1FFF))|T;x=get_u(s+=4);
 a[1]=x&0x3FFF;x>>=14;a[2]=x&0x3FFF;x=get_u(s+=4);
 w[0]=x&0x3FF;x>>=10;w[1]=x&0x3FF;x>>=10;w[2]=x&0x3FF;
 T_+=T;mcu_t+=mcu_time(t);for(j=0;j<3;j++){a_[j]+=a[j];b_[j]+=b[j];w_[j]+=w[j];}
 if(++i!=period)return;i=0;
 printf("adc:  %.8f %.0f %.0f %.0f"" %+05.0f %+05.0f %+05.0f"
   " %04.0f %04.0f %04.0f"" %3.4f\n",
  mcu_t/period,a_[0]/period,a_[1]/period,a_[2]/period,
  b_[0]/period,b_[1]/period,b_[2]/period,
  w_[0]/period,w_[1]/period,w_[2]/period,T_/16/period);
 for(j=0;j<3;j++)a_[j]=b_[j]=w_[j]=0;T_=0;mcu_t=0;
}
void expone(const unsigned char*s,int size)
{uint32_t crc,cr;crc=form_crc(s,(size>>2)-1);cr=get_u(s+size-4);
 if(crc!=cr)
 {error("wrong checksum (0x%8.8lX, received 0x%8.8lX), size %i\n",
  (unsigned long)crc,(unsigned long)cr,size);return;
 }
 switch(size)
 {case 8:exp_pps(s);break;case 12:exp_temp(s);break;
  case 16:exp_gps(mcu_stamp(),s,gps_extracted);break;case 24:exp_adc(s);break;
  default:error("wrong size (%i for 24 or 16 or 12 or 8)\n",size);
 }
}
