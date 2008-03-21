/*CRC32 test
Copyright (C) 2006, 2008\
 Ineiev <ineiev@users.sourceforge.net>, super V 93
This file is a part of stribog.

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
#include"crc32.h"
#include"led.h"
#include"pll.h"
static int i;static unsigned data[289];
int main(void)
{int j;start_pll();init_led();led1_set();
 for(j=0;j<sizeof(data)/sizeof(*data);j++)data[j]=j;led1_clr();connect_pll();
 while(1)
 {data[0]=form_crc(data+1,sizeof(data)/sizeof(*data)-1);
  if(i++&(1<<5))led0_clr();else led0_set();
 }
}
