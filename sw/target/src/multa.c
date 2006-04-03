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
static unsigned f[FIX_LENGTH],adxrs_temp[3],_2048;static int b[3],a[3];
static void send_pps(void)
{static int pps_got;static unsigned pps,k;const unsigned*_;
 if((_=get_pps())){pps=*_;pps_got=!0;k++;}
 if(pps_got){pps_got=send_fix(&pps,PPS_LENGTH);}
}
static void check_gps_data(void)
{static unsigned _[GPS_DATA_LENGTH];char*s=(char*)_;
 static int data_got;if(data_got){data_got=send_fix(_,GPS_DATA_LENGTH);return;}
 if(!(data_got=receive0(s,sizeof(_)-1)))return;s[sizeof(_)-1]=data_got;
 data_got=send_fix(_,GPS_DATA_LENGTH);
}
static void form_data(unsigned d[FIX_LENGTH])
{const int*mag;unsigned*s=d;int t,w[3];const unsigned*adc,*acc;
 while(!(adc=get_adc()));_2048=adc[ADC_2048];
 adxrs_temp[0]=adc[ADC_TX];adxrs_temp[1]=adc[ADC_TY];adxrs_temp[2]=adc[ADC_TZ];
 if((mag=process_mag(adc))){*b=*mag;b[1]=mag[1];b[2]=mag[2];}
 t=get_temperature();w[0]=adc[ADC_WX];w[1]=adc[ADC_WY];w[2]=adc[ADC_WZ];
 if((acc=get_accel())){a[0]=acc[0];a[1]=acc[1];a[2]=acc[2];}
 *s++=iunius_tempus();
 *s++=(b[0]&0xFFF)|((b[1]&0xFFF)<<12)|((t&0xFF)<<24);
 *s++=(b[2]&0xFFF)|((a[0]&0x3FFF)<<12)|((t&0x1F00)<<(26-8));
 *s++=(a[1]&0x3FFF)|((a[2]&0x3FFF)<<14);
 *s=(w[0]&0x3FF)|((w[1]&0x3FF)<<10)|((w[2]&0x3FF)<<20);
}
static void form_temp(void)
{unsigned*s=f;*s++=_2048;
 *s=adxrs_temp[0]|(adxrs_temp[1]<<10)|(adxrs_temp[2]<<20);
}
int main(void)
{int j=0;unsigned t=0;
 start_pll();init_power();init_led();init_lm74();init_accel();led1_clr();
 init_mag();connect_pll();init_adc();init_uart1();init_uart0();init_tempus();
 while(1)
 {form_data(f);if(!(j&((1<<6)-1))){send_fix(f,FIX_LENGTH);led1_set();led1_clr();}
  send_pps();check_gps_data();
  if((1<<5)==(j&((1<<13)-1))){form_temp();send_fix(f,TEMP_LENGTH);}
  if(t>tempus())ask_ephm();t=tempus();
  if(j++&(1<<12))led0_set();else led0_clr();
 }return 0;
}
