#include"preproc_gps.h"/*print GPS data*/
#include"lla.h"
#include<stdio.h>
#include<math.h>
static double t,dt,ecf0[3],xyz[3],lla0[3]={-10,0,0},lla[3],rot[3][3];
static void rotate(double enu[],const double xyz[])
{int i,j;for(i=0;i<3;i++)for(j=0,enu[i]=0;j<3;j++)enu[i]+=xyz[j]*rot[i][j];}
static void init_rot(void)
{rot[0][0]=-sin(lla0[1]);rot[0][1]=cos(lla[1]);rot[0][2]=0;
 rot[1][0]=-cos(lla0[1])*sin(*lla0);rot[1][1]=-sin(lla0[1])*sin(*lla0);
 rot[1][2]=cos(*lla0);
 rot[2][0]=cos(lla0[1])*cos(*lla0);rot[2][1]=sin(lla0[1])*cos(*lla0);
 rot[2][2]=sin(*lla);
}
static void init_lla0(void)
{int i;for(i=0;i<3;i++)lla0[i]=lla[i];
 printf("l0l0a0: 0 %.17f %.17f %.17f\n",*lla0,lla0[1],lla0[2]);initlla();
 lla2xyz(ecf0,lla0);
 printf("ecef0: 0 %.5f %.5f %.5f\n",ecf0[0],ecf0[1],ecf0[2]);init_rot();
}
static void print_xyz(void)
{double dx[3],ecf[3];int i;lla2xyz(ecf,lla);
 for(i=0;i<3;i++)dx[i]=ecf[i]-ecf0[i];rotate(xyz,dx);
 printf("lxyz: %.2f %.5f %.5f %.5f %.5f\n",t,*xyz,xyz[1],xyz[2],dt);
}
void add_gps_point(const gps_point*p)
{*lla=p->lat;lla[1]=p->lon;lla[2]=p->alt;if(*lla0<-9)init_lla0();
 print_xyz();
 printf("xvel: %.2f %.5f %.5f %.5f %.5f %.5f %.5f\n",
   t,*xyz,xyz[1],xyz[2],p->east_vel,p->north_vel,p->up_vel);
}/*This program is a part of the stribog host software section

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

Copyright (C) 2005-2006 D.Ineiev <ineiev@yahoo.co.uk>*/