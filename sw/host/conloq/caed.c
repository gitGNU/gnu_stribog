/*caed: split stribog data flow*/
#include"parse_tsip.h"
#include<stdint.h>
#include"crc32.h"
#include"error.h"
#include<stdio.h>
static double freq=14745600.+8550;static unsigned leaps;
static unsigned long long time_stamp;
static double mcu_stamp(void){return time_stamp/freq;}
static double mcu_time(uint32_t t)
{static int cycled=!0;if(t<(1<<30)&&!cycled){leaps++;cycled=1;}
 if(t>(~0)-(1<<30))cycled=0;time_stamp=t|(((unsigned long long)leaps)<<32);
 return mcu_stamp();
}static uint32_t get_u(const unsigned char*s)
{return*s|(((uint32_t)s[1])<<8)|(((uint32_t)s[2])<<16)|(((uint32_t)s[3])<<24);}
static void exp_adc(const unsigned char*s)
{static int period;mcu_time(get_u(s));if(!(period++&0xFF))printf("%.8f\n",mcu_stamp());}
static void expone(const unsigned char*s,int size)
{uint32_t crc,cr;crc=form_crc(s,(size>>2)-1);cr=get_u(s+size-4);
 if(crc!=cr)
 {error("wrong checksum (0x%8.8lX, received 0x%8.8lX), size %i\n",
  (unsigned long)crc,(unsigned long)cr,size);return;
 }switch(size){case 24:exp_adc(s);break;}
}
int main(int argc,char**argv)
{tsip_buf*tb=new_tsip();int size,c,i=0;const unsigned char*_;FILE*f,*log;double t=0;
 char file_name[289];
 if(argc<2){error("no file specified\n");return 1;}scanf("%lg",&t);
 sprintf(file_name,"%s.%3.3i",argv[1],i++);log=fopen(file_name,"wb");
 if(!(f=fopen(argv[1],"rb"))){printf("can't open \"%s\"\n",argv[1]);return 2;}
 while(!feof(f))
 {if((_=parse_tsip(tb,c=getc(f),&size)))
  {expone(_,size);
   if(!feof(stdin))if(mcu_stamp()>t)
   {if(log)fclose(log);sprintf(file_name,"%s.%3.3i",argv[1],i++);log=fopen(file_name,"wb");
    scanf("%lg",&t);
   }
  }if(log)putc(c,log);
 }if(log)fclose(log);fclose(f);free_tsip(tb);return 0;
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
