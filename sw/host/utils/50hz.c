#include<stdio.h>/*50Hz detector for magnetic data*/
#include<math.h>
int main(void)
{while(!feof(stdin))
 {int j,c=EOF;double i[3],q[3],t;i[0]=i[1]=i[2]=q[0]=q[1]=q[2]=0;
  for(j=0;j<10;j++)
  {double _[3];
   scanf("%lf %*f %*f %*f %lf %lf %lf",&t,_,_+1,_+2);do c=getchar();while(c!='\n'&&c!=EOF);
   i[0]+=_[0];i[1]+=_[1];i[2]+=_[2];
   if(c!=EOF)scanf("%*f %*f %*f %*f %lf %lf %lf",_,_+1,_+2);do c=getchar();while(c!='\n'&&c!=EOF);
   q[0]+=_[0];q[1]+=_[1];q[2]+=_[2];
   if(c!=EOF)scanf("%*f %*f %*f %*f %lf %lf %lf",_,_+1,_+2);do c=getchar();while(c!='\n'&&c!=EOF);
   i[0]-=_[0];i[1]-=_[1];i[2]-=_[2];
   if(c!=EOF)scanf("%*f %*f %*f %*f %lf %lf %lf",_,_+1,_+2);do c=getchar();while(c!='\n'&&c!=EOF);
   q[0]-=_[0];q[1]-=_[1];q[2]-=_[2];
  }
  if(c!=EOF)
   printf("%f %f %f %f\n",t,sqrt(i[0]*i[0]+q[0]*q[0]),
    sqrt(i[1]*i[1]+q[1]*q[1]),sqrt(i[2]*i[2]+q[2]*q[2]));
 }return 0;
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
along with this program. If not, see <http://www.gnu.org/licenses/>.

Copyright (C) 2006 D.Ineiev <ineiev@yahoo.co.uk>*/
