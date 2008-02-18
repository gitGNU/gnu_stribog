/*parse strings from preprocessed log files
Copyright (C) 2006, 2008 Ineiev <ineiev@users.sourceforge.net>

This program is a part of the stribog host software section

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.*/
typedef enum
{fin_com=0,cet_com,gyro_com,vel_com,loc_com,temp_com,xpos_com,mag_com,mag_bias_com,
 mag_corr_com,acc_calib_com,gyro_calib_com,hodo_calib_com,hodo_com,
 hodo_angle_source_com,alg_control_com
}commentarium;
commentarium lege_lineam(const char**s);

