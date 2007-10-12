#include"lege_lineam.h"/*parse strings from preprocessed log files*/
#include<string.h>
#include<stdio.h>
static char s[289];
commentarium lege_lineam(const char**t)
{int i,c=getchar();char*com;s[sizeof(s)-1]=0;*t=0;
 for(i=0;i<sizeof(s)-2&&c!=EOF&&c!='\n';i++,c=getchar())s[i]=c;
 s[i]=0;if(c==EOF)return fin_com;while(c!=EOF&&c!='\n');
 if(!(com=strchr(s,':')))return cet_com;*com=0;*t=com+1;
 if(!strcmp(s,"adc"))return gyro_com;if(!strcmp(s,"lla"))return loc_com;
 if(!strcmp(s,"tempus"))return temp_com;
 if(!strcmp(s,"vel"))return vel_com;if(!strcmp(s,"xvel"))return xpos_com;
 if(!strcmp(s,"mag_bias"))return mag_bias_com;
 if(!strcmp(s,"mag_corr"))return mag_corr_com;
 if(!strcmp(s,"acc_calib"))return acc_calib_com;
 if(!strcmp(s,"gyro_calib"))return gyro_calib_com;
 if(!strcmp(s,"hodo_calib"))return hodo_calib_com;
 if(!strcmp(s,"hodo_angle_source"))return hodo_angle_source_com;
 if(!strcmp(s,"odo"))return hodo_com;
 if(!strcmp(s,"mag"))return mag_com;
 return cet_com;
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
