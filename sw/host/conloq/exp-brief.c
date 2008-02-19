/*briefly decoding stribog messages with interactive output control
Copyright (C) 2006, 2007, 2008\
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
#include"crc32.h"
#include"error.h"
#include<stdio.h>
#include"verbosity_level.h"
#include"exp_gps.h"
#include"preproc_gps.h"
#include"get_u.h"
void
add_gps_point(const gps_point*p){}
static double freq=14745600.+8550;static unsigned leaps;
static int period=1;static unsigned long long time_stamp;
static double
mcu_stamp(void){return time_stamp/freq;}
static double
mcu_time(unsigned long t)
{static int cycled=!0;if(t<(1<<30)&&!cycled){leaps++;cycled=1;}
 if(t>(~0)-(1<<30))cycled=0;time_stamp=t|(((unsigned long long)leaps)<<32);
 return mcu_stamp();
}int
init_exp(int x,int p){init_gps(x);if(p)period=p;return 0;}
void
close_exp(void){close_gps();}
static unsigned temperature[4];
static void
exp_temp(const unsigned char*s)
{unsigned _2048,t[3];enum verbosity_level verb;
 _2048=get_u(s);s+=4;t[0]=get_u(s);
 t[2]=t[0]>>20;t[1]=(t[0]>>10)&0x3FF;t[0]&=0x3FF;
 verb=get_verbosity();
 temperature[0]=t[0];temperature[1]=t[1];
 temperature[2]=t[2];temperature[3]=_2048;
 if(!stribog_message_turned_on(temp_message))return;
 if(verb>=relatively_mute)printf("temp:");
 if(verb<normal_verbosity){fflush(stdout);return;}
 printf(" %.8f %u %u %u %u\n",mcu_stamp(),
  temperature[0],temperature[1],temperature[2],temperature[3]);
}double 
correct_second(double utc,double t_mcu){return t_mcu;}
static void
exp_pps(const unsigned char*s)
{static unsigned t0,loops,v;double d;unsigned t=get_u(s),dt,l=0;
 enum verbosity_level verb=get_verbosity();
 if(t0>t){l=1;loops++;}dt=((double)(t-t0)+.5*freq)/freq;
 d=v?((double)l*(1ull<<32)+t-t0-dt*freq):0;if(dt)d/=dt;t0=t;v=!0;
 if(!stribog_message_turned_on(pps_message))return;
 if(verb>=relatively_mute)printf("pps:");
 if(verb<normal_verbosity){fflush(stdout);return;}
 printf("  %.8f %.0f %g\n",mcu_stamp(),
  t+(double)((unsigned long long)loops*(1ull<<32)),d);
}static void
exp_adc(const unsigned char*s)
{static int i;int a[3],b[3],w[3],T,j,turned_on;unsigned long t,x;
 static double mcu_t,a_[3],b_[3],w_[3],T_;
 enum verbosity_level verb;
 for(j=0;j<3;j++)b[j]=w[j]=0;
 verb=get_verbosity();
 turned_on=stribog_message_turned_on(adc_message);
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
 if(verb>=relatively_mute&&turned_on)printf("adc:");
 if(verb<normal_verbosity||!turned_on){fflush(stdout);goto exit;}
 printf("  %.8f %.0f %.0f %.0f"" %+05.0f %+05.0f %+05.0f"
  " %04.0f %04.0f %04.0f"" %3.4f",
  mcu_t/period,a_[0]/period,a_[1]/period,a_[2]/period,
  b_[0]/period,b_[1]/period,b_[2]/period,
  w_[0]/period,w_[1]/period,w_[2]/period,T_/16/period);
 if(period<=1)for(j=0;j<4;j++)printf(" %u",temperature[j]);putchar('\n');
 exit:for(j=0;j<3;j++)a_[j]=b_[j]=w_[j]=0;T_=0;mcu_t=0;
}static int
exp_stat(const unsigned char*s)
{unsigned long tmax=get_u(s),adc_missed=get_u(s+=4),accel_errors=get_u(s+=4),
  tsum_N=get_u(s+=4),tsum,tmin,uart0_overflows;
 static const double sec_to_us=1e6;
 enum verbosity_level verb=get_verbosity();
 int turned_on=stribog_message_turned_on(stat_message);
 tmin=(tmax>>16)&((1<<16)-1);tmax&=((1<<16)-1);
 uart0_overflows=(adc_missed>>16)&((1<<16)-1);adc_missed&=((1<<16)-1);
 tsum=(accel_errors>>16)&((1<<16)-1);accel_errors&=((1<<16)-1);
 if(verb>=relatively_mute&&turned_on)printf("stat:");
 if(verb<normal_verbosity){fflush(stdout);return 0;}
 if(!turned_on)return 0;
 printf(" %.8f %.3f %.3f %.3f %.3f %lu %lu %lu\n",
  mcu_stamp(),(double)tmin/freq*sec_to_us,
  (double)tsum*(1<<16)/tsum_N/freq*sec_to_us,2e6/tsum_N,
  (double)tmax/freq*sec_to_us,
  adc_missed,accel_errors,uart0_overflows);return 0;
}int
expone(const unsigned char*s,int size)
{unsigned long crc,cr;crc=form_crc(s,(size>>2)-1);cr=get_u(s+size-4);
 if(crc!=cr)
 {error("wrong checksum (0x%8.8lX, received 0x%8.8lX), size %i\n",
  (unsigned long)crc,(unsigned long)cr,size);return 0;
 }
 switch(size)
 {case 8:exp_pps(s);break;case 12:exp_temp(s);break;
  case 16:exp_gps(mcu_stamp(),s,0);break;
  case 20:exp_stat(s);break;case 24:exp_adc(s);break;
  default:error("wrong size (%i for 24 or 20 or 16 or 12 or 8)\n",size);
 }return 0;
}
