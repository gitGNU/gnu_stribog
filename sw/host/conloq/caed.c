/*caed: split stribog data file on pieces
Copyright (C) 2006, 2007, 2008\
 Ineiev<ineiev@users.sourceforge.net>, super V 93
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
#include"parse_tsip.h"/* the filename is argv[1]; main board time moments */
#include"crc32.h"     /* when to split go from stdin */
#include<stribog_error.h>
#include"get_u.h"
#include<stdio.h>
static double freq=14745600.+8550;static unsigned leaps;
static unsigned long long time_stamp;
static double
mcu_stamp(void){return time_stamp/freq;}
static double
mcu_time(unsigned long t)
{static int cycled=!0;if(t<(1<<30)&&!cycled){leaps++;cycled=1;}
 if(t>(~0)-(1<<30))cycled=0;time_stamp=t|(((unsigned long long)leaps)<<32);
 return mcu_stamp();
}static void
exp_adc(const unsigned char*s)
{static int period;mcu_time(get_u(s));
 if(!(period++&byte_mask))printf("%.8f\n",mcu_stamp());
}static void
expone(const unsigned char*s,int size)
{unsigned long crc,cr;crc=form_crc(s,(size>>2)-1);cr=get_u(s+size-4);
 if(crc!=cr)
 {error("wrong checksum (0x%8.8lX, received 0x%8.8lX), size %i\n",
  (unsigned long)crc,(unsigned long)cr,size);return;
 }if(size==adc_message_size)exp_adc(s);
}int
main(int argc,char**argv)
{tsip_buf*tb;int size,c,i=0;const unsigned char*_;
 FILE*f,*log;double t=0;char file_name[289];
 init_error(*argv);tb=new_tsip();
 if(argc<2){error("no file specified\n");return 1;}scanf("%lg",&t);
 snprintf(file_name,sizeof file_name,"%s.%3.3i",argv[1],i++);
 log=fopen(file_name,"wb");
 if(!(f=fopen(argv[1],"rb"))){printf("can't open \"%s\"\n",argv[1]);return 2;}
 while(!feof(f))
 {if((_=parse_tsip(tb,c=getc(f),&size)))
  {expone(_,size);
   if(!feof(stdin))if(mcu_stamp()>t)
   {if(log)fclose(log);
    snprintf(file_name,sizeof file_name,"%s.%3.3i",argv[1],i++);
    log=fopen(file_name,"wb");scanf("%lg",&t);
   }
  }if(log)putc(c,log);
 }if(log)fclose(log);fclose(f);free_tsip(tb);return 0;
}
