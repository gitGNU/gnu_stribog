typedef enum/*parse strings from preprocessed log files*/
{fin_com=0,cet_com,gyro_com,vel_com,loc_com,temp_com,xpos_com,mag_com,mag_bias_com,
 mag_corr_com,acc_calib_com,gyro_calib_com
}commentarium;
commentarium lege_lineam(const char**s);
/*This program is a part of the stribog host software section

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
