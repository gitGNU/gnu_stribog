/*decode GARMIN GPS25 LP series binary messages (not tested)
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
#include"parse_tsip.h"
#include<stdio.h>
#include"exp_gps.h"
#include<stdint.h>
#include<string.h>
static tsip_buf*gps_buf;static int expone;
int init_gps(int exp){expone=exp;gps_buf=new_tsip();return 0;}
void close_gps(void){free_tsip(gps_buf);}
static uint16_t get_hu(const unsigned char*s){return*s|(((uint16_t)s[1])<<8);}
static float get_f(const unsigned char*s)/*for little-endian IEEE-754 only*/
{float x;memmove(&x,s,4);return x;}
static double get_d(const unsigned char*s)/*for little-endian IEEE-754 only*/
{double x;memmove(&x,s,4);return x;}
static void exp_28(const unsigned char*s,int size,unsigned long long ticks)
{double lat,lon,t;float alt,vlat,vlon,valt;int fix;printf("gps: %llu ",ticks);
 alt=get_f(s+=2);fix=get_hu(s+=16);t=get_d(s+=2);lat=get_d(s+=8);
 lon=get_d(s+=8);vlat=get_f(s+=8);vlon=get_f(s+=4);valt=get_f(s+4);
 printf("%i %.3f %.6f %.6f %.3f ",fix,t,lat,lon,alt); 
 printf("%.3f %.3f %.3f\n",vlat,vlon,valt);
}
static void exp_29(const unsigned char*s,int size,unsigned long long ticks)
{printf("gps_phase... %llu\n",ticks);}
static void exp_garmin(const unsigned char*s,int size,unsigned long long t)
{if(!expone){printf("gps_message: %llu %2.2X %i bytes\n",t,*s,size);return;}
 switch(*s)
 {case 0x28:exp_28(s,size,t);break;case 0x29:exp_29(s,size,t);break;}
}
void exp_gps(unsigned long long time,const unsigned char*s,FILE*gps)
{int n=s[11],i,size;const unsigned char*_;
 for(i=0;i<n;i++)
 {if((_=parse_tsip(gps_buf,s[i],&size)))exp_garmin(_,size,time);
  if(gps)putc(s[i],gps);
 }
}
