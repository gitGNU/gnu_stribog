int initlla(void);/*LatLonAlt<->XYZ transforms for WGS-84*/
int xyz2lla(double lla[],const double xyz[]);
int lla2xyz(double xyz[],const double lla[]);
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

Copyright (C) 1998-2000, 2005-2006 D.Ineiev <ineiev@yahoo.co.uk>, super V 93*/