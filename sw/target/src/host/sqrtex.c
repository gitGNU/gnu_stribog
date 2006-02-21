/*integer sqrt test (on a host)
This file is a part of the stribog project.

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
#include<math.h>
#include<stdio.h>
#include"sqrt.h"
const unsigned _05=1l<<31;
static double f2d(unsigned x){return(double)(x);}
static unsigned d2f(double x){return x;}
static double l2d(unsigned x){return(double)(x);}
static unsigned d2l(double x){return x;}
int main(void)
{double x,q,qn;unsigned i;
 for(i=0;i<0x7<<(32-3);i+=1ul<<20)
 {x=l2d(i);q=sqrt(x);qn=l2d(sqrtu(d2l(x)));
  if(fabs(q-qn)>l2d(1)/2)printf("%X %f %f %g %g\n",i,x,q,qn,q-qn);
 }return 0;
}
