/*calculate max, min, mean and stdev for every column
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
along with this program. If not, see <http://www.gnu.org/licenses/>.

Copyright (C) 2006, 2007 Ineiev<ineiev@users.sourceforge.net>, super V 93*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
static long N,n,j;double*s,*ss,*s0,*mx,*mn;
static void process_string(const char*u)
{double x;const char*_=u;while(*_==' ')++_;N++;
 for(j=0;j<n;j++)
 {sscanf(_,"%lf",&x);if(N==1){s0[j]=mx[j]=mn[j]=x;}
  if(mx[j]<x)mx[j]=x;if(mn[j]>x)mn[j]=x;
  x-=s0[j];s[j]+=x;ss[j]+=x*x;_=strchr(_+1,' ');
 }
}
static void print_results(void)
{printf("N: %li\n",N);if(!N)return;
 printf("min: ");for(j=0;j<n;j++)printf("%.8g ",mn[j]);putchar('\n');
 printf("max: ");for(j=0;j<n;j++)printf("%.8g ",mx[j]);putchar('\n');
 printf("mean: ");
 for(j=0;j<n;j++)printf("%.8g ",s[j]/N+s0[j]);putchar('\n');if(N<2)return;
 for(j=0;j<n;j++)printf("%.8g ",sqrt((ss[j]-s[j]*s[j]/N)/(N-1)));putchar('\n');
}void free_all(void)
{if(s)free(s);if(ss)free(ss);if(s0)free(s0);if(mx)free(mx);if(mn)free(mn);}
static int init_n(const char*u)
{const char*_=u;while(*_==' ')++_;do{n++;_=strchr(_+1,' ');}while(_);
 s=calloc(n,sizeof(*s));ss=calloc(n,sizeof(*s));s0=calloc(n,sizeof(*s));
 mn=calloc(n,sizeof(*s));mx=calloc(n,sizeof(*s));
 for(j=0;j<n;j++)s[j]=ss[j]=0;
 if(NULL!=s&&NULL!=ss&&NULL!=s0&&NULL!=mn&&NULL!=mx)return 0;
 free_all();return!0;
}
int main(int argc,char**argv)
{char str[4913];fgets(str,sizeof(str),stdin);if(init_n(str))return!0;
 while(1){process_string(str);fgets(str,sizeof(str),stdin);if(feof(stdin))break;}
 print_results();free_all();return 0;
}
