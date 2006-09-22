/*prints temperature drift(to be complete).
 input: two file names, the central temperature (real number), 
  null at the central temperature (real number).
 input file format: two-column text 
 (the first column is current value, the second is temperature)
 temperature should increase with column number
 output is three-column: [temperature] [scale factor drift] [null drift]*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
static void usage(void){fprintf(stderr,"usage: drift file0 file1\n");}
static FILE*f0,*f1;static double x0,x1,y0,y1,x,y;
static int get_x1(void)
{if(feof(f1))return!0;return 2!=fscanf(f1,"%lg %lg",&y1,&x1);}
static int get_x(void)
{if(feof(f0))return!0;return 2!=fscanf(f0,"%lg %lg",&y,&x);}
static int fill_x0(void)
{x0=x1;y0=y1;do if(get_x1())return 0;while(x0>=x1);return!0;}
static void free_all(void){if(f1)fclose(f1);if(f0)fclose(f0);}
static int print_interval(void)
{static double dx,ax0;static int k,dx_vex;
 if(feof(f1))return!0;while(x<x0&&!feof(f0))get_x();while(x>x1&&!feof(f1))fill_x0();
 if(!k)
 {k=1;dx=((x1-x)*y0+(x-x0)*y1)/(x1-x0)-y;ax0=y;}if(dx<10&&dx>-10)dx_vex=!0;
 while(x0<=x&&x<x1)
 {printf("%.6f %.6f %.6f\n",x,dx_vex?0:(((x1-x)*y0+(x-x0)*y1)/(x1-x0)-y)/dx-1,y-ax0);
  if(get_x())return!0;if(feof(f0))return!0;
 }return feof(f1);
}
int main(int argc,char**argv)
{if(argc<3){usage();return 1;}
 f0=fopen(argv[1],"rt");
 if(!f0){free_all();fprintf(stderr,"can't open %s for reading\n",argv[1]);return 2;}
 f1=fopen(argv[2],"rt");
 if(!f1){free_all();fprintf(stderr,"can't open %s for reading\n",argv[2]);return 3;}
 if(get_x1()||get_x())goto the_end;
 while(fill_x0())if(print_interval())break;the_end:free_all();return 0;
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

Copyright (C) 2006 D.Ineiev <ineiev@yahoo.co.uk>*/

