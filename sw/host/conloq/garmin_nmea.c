/*decode GARMIN GPS25 LP series NMEA messages
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
#include<stdio.h>
#include"exp_gps.h"
#include"error.h"
#include<stdint.h>
#include<string.h>
int init_gps(int exp){return 0;}void close_gps(void){}
static int field_cmp(const char*s,const char*c)
{const char*_=strchr(s,',');if(!_)return!0;return strncmp(s,c,_-s);}
static int parse_gga(const char*s,double t)
{printf("GGA %.7f %s\n",t,s);return 0;}
static int parse_pgrmv(const char*s,double t)
{printf("RMV %.7f %s\n",t,s);return 0;}
static int nmea_switch(const char*s,double t)
{if(!field_cmp(++s,"GPGGA,"))return parse_gga(s+6,t);
 if(!field_cmp(s,"PGRMV,"))return parse_pgrmv(s+6,t);return 0;
}
void exp_gps(double time,const unsigned char*s,FILE*gps)
{int n=s[11],i;static char nmea[0x100];static int k;
 for(i=0;i<n;i++)
 {if(gps)putc(s[i],gps);nmea[k++]=s[i];
  if(k>=sizeof(nmea)){error("too long message");k=0;continue;}
  if(s[i]=='$')
  {if(*nmea=='$'){nmea[k-3]=0;nmea_switch(nmea,time);}k=1;*nmea='$';}
 }
}
