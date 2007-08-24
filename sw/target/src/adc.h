/*ADC input
This file has been written for the stribog project.

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
#define ADC_MX		(4)
#define ADC_MY		(5)
#define ADC_MZ		(0)
#define ADC_WX		(2)
#define ADC_WY		(3)
#define ADC_WZ		(1)
#define ADC_TX		(10)
#define ADC_TY		(15)
#define ADC_TZ		(7)
#define ADC_2048	(14)
void init_adc(void);const unsigned*get_adc(void);
