#include"lla.h"/*LatLonAlt<->XYZ transforms for WGS-84*/
#include<math.h>
#include<float.h>
static double alpha=1./298.257223563,axis=6378137.;
int initlla(void){return 0;}
int xyz2lla(double lla[],const double xyz[])
{double x0=sqrt(xyz[0]*xyz[0]+xyz[1]*xyz[1]),y0=xyz[2],y,k,dk,x,sqk,
  ba_2=(1-alpha)*(1-alpha),r[2];int sign=0,n=0;
 lla[1]=atan2(xyz[1],xyz[0]);
 if(x0/axis<DBL_EPSILON*100/*accuratior sit exp(log(DBL_EPSILON)/3)*6*/)
 {dk=x0/axis;lla[0]=(M_PI/2-dk)*(y0<0?-1:1);lla[2]=y0*(1+dk*dk/2)-axis*(1-alpha);return 0;}
 if(y0/axis<DBL_EPSILON*100)
 {lla[0]=y0/axis;lla[2]=x0*(1+lla[0]*lla[0]/2)-axis;return 0;}
 if(y0<0){sign=!0;y0=-y0;}k=y0/x0/ba_2;x0/=axis;y0/=axis;sqk=sqrt(1+k*k);
 do
 {x=1/sqrt(1+k*k*ba_2);y=k*ba_2*x;*r=x0-x;r[1]=y0-y;
  dk=r[1]-*r*k;k+=dk*sqk;n++;
 }while(fabs(dk)>DBL_EPSILON*10);
 lla[0]=atan(k);if(sign)lla[0]=-lla[0];lla[2]=sqrt(*r**r+r[1]*r[1])*axis;
 return n;
}
int lla2xyz(double xyz[],const double lla[])
{double x0,y0,tl,lat=lla[0],lon=lla[1],alt=lla[2];
 if(fabs(lat)>M_PI/2)return-1;
 if(fabs(lat)<DBL_EPSILON*100){x0=axis*(1-lat*lat/2);y0=lat*axis;}
 else if(fabs(fabs(lat)-M_PI/2)<DBL_EPSILON*100)
 {tl=M_PI/2-fabs(lat);x0=axis*tl;y0=axis*(1-alpha)*(1-tl*tl/2);if(lat<0)y0=-y0;}
 else{tl=tan(lat)*(1-alpha);x0=axis/sqrt(1+tl*tl);y0=x0*(1-alpha)*tl;}
 x0+=alt*cos(lat);y0+=alt*sin(lat);
 xyz[0]=x0*cos(lon);xyz[1]=x0*sin(lon);xyz[2]=y0;return 0;
}/*This program is a part of the stribog host software section

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.

Copyright (C) 1998-2000, 2005-2006 D.Ineiev <ineiev@yahoo.co.uk>, super V 93*/
