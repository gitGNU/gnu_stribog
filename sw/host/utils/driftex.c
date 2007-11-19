/*test generator for "drift"*/
#include<stdio.h>
static void usage(void){fprintf(stderr,"usage: driftex a n(0) x1 x2\n");}
void print_file(double a,double x,double n,const char*name)
{const double dt=0x11,t0=-400,t1=120;FILE*f=fopen(name,"wt");int i;double t;
 if(!f)return;for(i=0,t=t0;t<t1;t+=dt/(1+(++i)/7))fprintf(f,"%f %f\n",t,n+a*t+x);fclose(f);
}
int main(int argc,char**argv)
{double a,n,x1,x2;if(argc<5){usage();return 1;}
 if(1!=sscanf(argv[1],"%lg",&a)){fprintf(stderr,"no a specified\n");return 1;}
 if(1!=sscanf(argv[2],"%lg",&n)){fprintf(stderr,"no n(t0) specified\n");return 2;}
 if(1!=sscanf(argv[3],"%lg",&x1)){fprintf(stderr,"no x1 specified\n");return 3;}
 if(1!=sscanf(argv[4],"%lg",&x2)){fprintf(stderr,"no x2 specified\n");return 4;}
 print_file(a,x1,n,"driftex0");print_file(a,x2,n,"driftex1");
 return 0;
}
/*This program is a part of the stribog host software section

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

Copyright (C) 2006 D.Ineiev <ineiev@yahoo.co.uk>*/

