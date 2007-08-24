/*conloq: talk (currently just listen) to a stribog board 
 from UNIX terminal via RS-232 UART
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

Copyright (C) 2006 D.Ineiev <ineiev@yahoo.co.uk>*/
#include"serialia.h"
#include"usage.h"
#include"parse_tsip.h"
#include"exp.h"
#include"error.h"
#include<stdio.h>
static FILE*next_file(void)
{char s[289];int i=0;FILE*f;
 do{sprintf(s,"%iconloq.log",i++);f=fopen(s,"rt");if(f)fclose(f);}while(f);
 return fopen(s,"wb");
}
int main(int argc,char**argv)
{tsip_buf*tb=new_tsip();int size,n,j,period=0x3F;const unsigned char*_;
 unsigned char s[0x121];FILE*f=next_file();
 if(!f){error("can't open log file\n");free_tsip(tb);return 1;}
 if(argc>2)sscanf(argv[2],"%i",&period);init_exp(0,period);
 if(initserialia(argc>1?argv[1]:0))
 {fclose(f);free_tsip(tb);close_exp();error("can't open serial port\n");return 2;}
 while(1)if(0<(n=lege(s,sizeof(s))))for(j=0;j<n;putc(s[j++],f))
  if((_=parse_tsip(tb,s[j],&size)))expone(_,size);
 closeserialia();close_exp();fclose(f);free_tsip(tb);return 0;
}
