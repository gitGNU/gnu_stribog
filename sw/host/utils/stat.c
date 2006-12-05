/*calculate mean and stdev for every column
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
#include<stdlib.h>
#include<string.h>
#include<math.h>
static int N,n,j;double *s,*ss;
static void process_string(const char*u)
{double x;int j;const char*_=u;while(*_==' ')++_;N++;
 for(j=0;j<n;j++){sscanf(_,"%lf",&x);s[j]+=x;ss[j]+=x*x;_=strchr(_+1,' ');}
}
static void print_results(void)
{if(!N)return;for(j=0;j<n;j++)printf("%f ",s[j]/N);putchar('\n');if(N<2)return;
 for(j=0;j<n;j++)printf("%f ",sqrt((ss[j]-s[j]*s[j]/N)/(N-1)));putchar('\n');
}
static void init_n(const char*u)
{const char*_=u;while(*_==' ')++_;do{n++;_=strchr(_+1,' ');}while(_);
 s=calloc(n,sizeof(*s));ss=calloc(n,sizeof(*s));for(j=0;j<n;j++)s[j]=ss[j]=0;
}void free_all(void){if(s)free(s);}
int main(int argc,char**argv)
{static char str[4913];
 fgets(str,sizeof(str),stdin);init_n(str);process_string(str);
 while(1){fgets(str,sizeof(str),stdin);if(feof(stdin))break;process_string(str);}
 print_results();free_all();return 0;
}
