#program for gnuplot to output processed traces
set grid xtics ytics
set ylabel'northing';set xlabel'easting';
plot'xvel'us($2):($3)w p ps 4 t'GPS sensor',\
'acc_pos'us($2):($3)w lp lt 3 pt 3 t'INS',\
'extra_pos'us($2):($3)w p lt 3 pt 4 ps 2 t'INS at GPS fix time',\
'hodo_pos'us($2):($3)w lp lt 4 pt 3 t'HODO',\
'extra_hodo_pos'us($2):($3)w p lt 4 pt 4 ps 2 t'HODO at GPS fix time';
#'gyro_pos'us($2):($3)w lp t'GYRO','extra_gyro_pos'us($2):($3)w p t'GYRO at GPS fix time',\
#This program is a part of the stribog host software section
#
#This program is free software; you can redistribute it and/or modify
#it under the terms of the GNU General Public License as published by
#the Free Software Foundation; either version 2 of the License, or
#(at your option) any later version.
#
#This program is distributed in the hope that it will be useful,
#but WITHOUT ANY WARRANTY; without even the implied warranty of
#MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#GNU General Public License for more details.
#
#You should have received a copy of the GNU General Public License
#along with this program. If not, see <http://www.gnu.org/licenses/>.
#
#Copyright (C) 2006, 2007 Ineiev <ineiev@users.sourceforge.net>
