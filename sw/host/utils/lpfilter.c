/*simple low-pass filter for files
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

Copyright (C) 2006, 2007 Ineiev<ineiev@users.sourceforge.net>*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
static int N=200,n,i,j;static unsigned prec=2;static double*s;
static void process_string(const char*u)
{double x;int j;const char*_=u;while(*_==' ')++_;
 for(j=0;j<n;j++){sscanf(_,"%lf",&x);s[j]+=x;_=strchr(_+1,' ');}
 if(++i==N)
 {i=0;for(j=0;j<n;s[j++]=0)printf("%.*f ",prec,s[j]/N);putchar('\n');}
}
static void init_n(const char*u)
{const char*_=u;while(*_==' ')++_;do{n++;_=strchr(_+1,' ');}while(_);
 s=calloc(n,sizeof(*s));for(j=0;j<n;s[j++]=0);
}void free_all(void){if(s)free(s);}
int main(int argc,char**argv)
{static char str[4913];if(argc>1)sscanf(argv[1],"%i",&N);if(N<1)return 1;
 if(argc>2)sscanf(argv[2],"%u",&prec);
 fgets(str,sizeof(str),stdin);init_n(str);process_string(str);
 while(1)
 {fgets(str,sizeof(str),stdin);if(feof(stdin))break;process_string(str);}
 free_all();return 0;
}
