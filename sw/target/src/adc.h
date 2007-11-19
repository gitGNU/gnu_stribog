/*ADC input
This file is a part the stribog project.

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

Copyright (C) 2006, 2007 Ineiev<ineiev@users.sourceforge.net>, super V 93*/
enum{
 ADC_MX=4, ADC_MY=5, ADC_MZ=0,
 ADC_WX=2, ADC_WY=3, ADC_WZ=1,
 ADC_TX=10,ADC_TY=15,ADC_TZ=7,
 ADC_2048=14
};
void init_adc(void);const unsigned*get_adc(void);
