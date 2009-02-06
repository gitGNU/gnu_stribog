/*decode odometer messages
Copyright (C) 2007, 2008\
 Ineiev<ineiev@users.sourceforge.net>, super V 93
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
#include"hodo.h"
#include<sbg_error.h>
#include"verb_level.h"
#include<stdio.h>
static int output_next;static unsigned char s[8];static int i=-1;
static unsigned _0=~0;static unsigned long long x;
static unsigned long t_loops;static const double freq0=57600.+5;
static int cmp(double dx,double thr){if(dx<0)dx=-dx;return dx<-thr||dx>thr;}
int proc_hodo(unsigned char c,int silent,double t)
{static double t_prev=-1,dt0,t_mess=-1;static long ts0=-1;
 static int dt0v,filter_count;enum verbosity_level verb=get_verbosity();
 int r=0,turned_on=stribog_message_turned_on(odo_message);
 if(i<0){if(!(c&(1<<6)))i=0;t_mess=-1;return 0;}if(t_mess<0)t_mess=t;
 if(!silent)output_next=turned_on;s[i++]=c&0x3F;
 if(i>sizeof(s))
 {error("hodo message too long t=%f\n",t);i=0;t_mess=-1;return!0;}
 if(c&(1<<6))return r;
 if(i<=5)
 {error("hodo message too short t=%.8f (%i bytes:"
   " %2.2X %2.2X %2.2X %2.2X %2.2X)\n",t,i,s[0],s[1],s[2],s[3],s[4]);r=!0;
 }else
 {unsigned _,d;long ts;long l=0;unsigned char sum;i-=6;
  for(_=sum=0;_<6;_++)sum^=s[i+_];
  if(sum)
  {error("hodo checksums don't match (diff=%2.2X) t=%f\n",sum,t);return!0;}
  _=s[i+1]|(((unsigned)s[i])<<6);
  ts=((((unsigned)s[i+2])<<12)|(((unsigned)s[i+3])<<6)|s[i+4])&0xFFFF;
  if(ts<ts0){t_loops++;l=1;}
  if(~_0)
  {unsigned long long t_full=ts+(((unsigned long long)t_loops)<<16);
   d=(_<_0?(1<<12):0)+_-_0;x+=d;
   if(t_prev>-.1&&cmp(t_mess-t_prev,1e-5))
   {if(dt0v)
    {double dt=t_mess-t_full/freq0-dt0;
     dt0+=dt/(filter_count+2);if(filter_count<1000)filter_count++;
     if(cmp(dt,.05))
     {error("hodo time jump t=%f dt=%.8f\n",t,dt);
      t_prev=-1;ts0=-1;dt0v=0;i=0;t_mess=-1;filter_count=0;_0=~0;return!0;
     }
     if(output_next&&verb>relatively_mute)
      printf("ododt: %.8f %llu %.8f %.8f\n",t,t_full,dt,dt0);
    }else if(ts0>=0)
    {dt0v=!0;dt0=t_mess-t_full/freq0;
     if(output_next&&verb>relatively_mute)
      printf("ododt0: %.8f %llu %.8f\n",t,t_full,dt0);
    }
   }if(output_next)
   {double t_corrected=t_full/freq0+dt0;
    if(verb>absolutely_mute){printf("odo:");fflush(stdout);}
    if(verb>relatively_mute)
     printf(" %.8f %llu %llu %li %li\n",t_corrected,t_full,x,ts,ts0);
   }output_next=0;
  }_0=_;ts0=ts;t_prev=t_mess;
 }i=0;t_mess=-1;return r;
}
