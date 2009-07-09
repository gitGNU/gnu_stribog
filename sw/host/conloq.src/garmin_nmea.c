/*decode GARMIN GPS25 LP series NMEA messages
 uses GPGGA, PGRMV
Copyright (C) 2006, 2007, 2008, 2009\
 Ineiev <ineiev@users.berlios.de>, super V 93
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
#include<stdio.h>
#include"hodo.h"
#include"exp_gps.h"
#include"preproc_gps.h"
#include<sbg_error.h>
#include"verb_level.h"
#include<string.h>
#include<math.h>
#ifndef M_PI
#define M_PI 3.14159265358979323844
#endif
static double t_pos=-2,lla[3],vel[3],mcut_gga=-1;
static int gga_outage=1,brief;static const int reaq_time=4;
static void
add_point(void)
{gps_point g;g.t_mcu=mcut_gga;
 g.utc=t_pos;g.lat=lla[0];g.lon=lla[1];g.alt=lla[2];
 g.east_vel=vel[0];g.north_vel=vel[1];g.up_vel=vel[2];add_gps_point(&g);
}int
init_gps(void){brief=get_interaction_mode()==interactive_mode;return 0;}
void
close_gps(void){}
static int field_cmp(const char*s,const char*c)
{const char*_=strchr(s,',');if(!_)return!0;return strncmp(s,c,_-s);}
static const char*nmea_field(const char*s,int n)
{int i;const char*_=s;for(i=0;i<n&&_;i++)_=strchr(_+1,',');if(_&&n)_++;return _;}
static int parse_gga(const char*s,double t)
{const char*_;char c;double d,x;
 int h,m;enum verbosity_level verb=get_verbosity();
 if(!stribog_message_turned_on(gps_message))return 0;
 if(verb>=relatively_mute){printf("GGA:");fflush(stdout);}
 if(verb<normal_verbosity)return 0;printf(" %.8f %s\n",t,s);if(brief)return 0;
 if(!(_=nmea_field(s,5))){gga_outage=reaq_time;return!0;}
 if(*_=='0'/*||*_=='6'*/){gga_outage=reaq_time;return!0;}
 if((_=nmea_field(s,0)))
 {sscanf(_,"%lf,",&x);h=x/10000;x-=h*10000;m=x/100;
  x-=m*100;t_pos=h*3600.+m*60+x;
 }else return!0;
 if((_=nmea_field(s,1)))
 {sscanf(_,"%lf,%c,",&x,&c);h=x/100;x-=h*100;x/=60;x+=h;lla[0]=x*M_PI/180;
  if(c=='S')lla[0]=-lla[0];
 }else return!0;
 if((_=nmea_field(s,3)))
 {sscanf(_,"%lf,%c,",&x,&c);h=x/100;x-=h*100;x/=60;x+=h;lla[1]=x*M_PI/180;
  if(c=='W')lla[1]=-lla[1];
 }else return!0;
 if((_=nmea_field(s,8))){d=0;sscanf(_,"%lf,M,%lf",&x,&d);lla[2]=x+d;}
 else return!0;mcut_gga=t;--gga_outage;return 0;
}static int
parse_pgrmv(const char*s,double t)
{enum verbosity_level verb=get_verbosity();
 if(!stribog_message_turned_on(gps_message))return 0;
 if(verb>=relatively_mute){printf("RMV:");fflush(stdout);}
 if(verb<normal_verbosity)return 0;printf(" %.8f %s\n",t,s);if(brief)return 0;
 sscanf(s,"%lf,%lf,%lf",vel,vel+1,vel+2);
 if(gga_outage<=0&&mcut_gga>0){add_point();gga_outage=1;}
 return 0;
}static int
nmea_switch(const char*s,double t)
{if(!field_cmp(++s,"GPGGA,"))return parse_gga(s+6,t);
 if(!field_cmp(s,"PGRMV,"))return parse_pgrmv(s+6,t);return 0;
}int 
exp_gps(double t,const unsigned char*s,FILE*gps)
{int n=s[11],i;static char nmea[0x100];static int k,silent_hodo;
 static double mute_time=-1,t_mess=-1;int r=0;
 for(i=0;i<n;i++)
 {if(gps)putc(s[i],gps);
  if(s[i]&0x80)
  {r|=proc_hodo(s[i],silent_hodo&&brief,t);
   silent_hodo=(t-mute_time<1);if(!silent_hodo)mute_time=t;
  }else nmea[k++]=s[i];
  if(k>=sizeof(nmea)){error("too long message t=%f\n",t);k=0;r=!0;continue;}
  if(s[i]=='\n')
  {if(*nmea=='$'){nmea[k-3]=0;nmea_switch(nmea,t_mess);}}
  if(s[i]=='$')
  {k=1;*nmea='$';t_mess=t;}
 }return r;
}
