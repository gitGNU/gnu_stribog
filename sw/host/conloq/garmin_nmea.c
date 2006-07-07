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
#include"preproc_gps.h"
#include"error.h"
#include<string.h>
#include<math.h>
static double t_pos=-2,lla[3],vel[3];static int brief;
static void add_point(void)
{gps_point g;g.utc=t_pos;g.lat=lla[0];g.lon=lla[1];g.alt=lla[2];
 g.east_vel=vel[0];g.north_vel=vel[1];g.up_vel=vel[2];add_gps_point(&g);
}
int init_gps(int exp){brief=!exp;return 0;}void close_gps(void){}
static int field_cmp(const char*s,const char*c)
{const char*_=strchr(s,',');if(!_)return!0;return strncmp(s,c,_-s);}
static const char*nmea_field(const char*s,int n)
{int i;const char*_=s;for(i=0;i<n&&_;i++)_=strchr(_+1,',');if(_&&n)_++;return _;}
static int parse_gga(const char*s,double t)
{const char*_;char c;double d,x;int h,m;printf("GGA: %.8f %s\n",t,s);
 if(brief)return 0;
 if(!(_=nmea_field(s,5)))return!0;if(*_=='0'||*_=='6')return!0;
 if((_=nmea_field(s,0)))
 {sscanf(_,"%lf,",&x);h=x/10000;x-=h*10000;m=x/100;
  x-=m*100;t_pos=h*3600.+m*60+x;
 }
 if((_=nmea_field(s,1)))
 {sscanf(_,"%lf,%c,",&x,&c);h=x/100;x-=h*100;x/=60;x+=h;lla[0]=x*M_PI/180;
  if(c=='S')lla[0]=-lla[0];
 }
 if((_=nmea_field(s,3)))
 {sscanf(_,"%lf,%c,",&x,&c);h=x/100;x-=h*100;x/=60;x+=h;lla[1]=x*M_PI/180;
  if(c=='W')lla[1]=-lla[1];
 }
 if((_=nmea_field(s,8))){d=0;sscanf(_,"%lf,M,%lf",&x,&d);lla[2]=x+d;}
 return 0;
}
static int parse_pgrmv(const char*s,double t)
{printf("RMV: %.8f %s\n",t,s);if(brief)return 0;
 sscanf(s,"%lf,%lf,%lf",vel,vel+1,vel+2);add_point();return 0;
}static int parse_zda(const char*s,double t)
{printf("ZDA: %.8f %s\n",t,s);return 0;}
static int nmea_switch(const char*s,double t)
{if(!field_cmp(++s,"GPGGA,"))return parse_gga(s+6,t);
 if(!field_cmp(s,"PGRMV,"))return parse_pgrmv(s+6,t);
 if(!brief)if(!field_cmp(s,"GPZDA,"))return parse_zda(s+6,t);
 return 0;
}
void exp_gps(double time,const unsigned char*s,FILE*gps)
{int n=s[11],i;static char nmea[0x100];static int k;
 for(i=0;i<n;i++)
 {nmea[k++]=s[i];if(k>=sizeof(nmea)){error("too long message");k=0;continue;}
  if(s[i]=='$')
  {if(*nmea=='$'){nmea[k-3]=0;nmea_switch(nmea,time);}k=1;*nmea='$';}
 }
}
