/*caed: split stribog data file on pieces
Copyright (C) 2006, 2007, 2008, 2009\
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
#include<config.h>
#include"parse_tsip.h"
#include<stribog_crc32.h>
#include<stribog_error.h>
#include<stribog_strings.h>
#include<snprintf_checked.h>
#include"get_u.h"
#include<stdio.h>
#include<argp.h>
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
}
const char*argp_program_version="caed"PACKAGE_VERSION_COMMENTED;
const char*argp_program_bug_address ="<"PACKAGE_BUGREPORT">";
static char doc[]="split stribog data\v"
"caed splits a data file captured from stribog\n"
"into parts at MCU time values given through stdin.\n\n",
 arg_doc[]="input_file";
static struct argp_option options[]=
{
 {"escapes",'e',0,0,
  "enable packet-layer escapes (you don't want to use "
   "this unless you really know what you are doing)"
 },
 {0}
};
struct arguments{char*file_name;int escapes;};
static error_t
parse_opt(int key, char*arg, struct argp_state*state)
{struct arguments*arguments=state->input;
 switch(key)
 {case 'e':arguments->escapes=!0;break;
  case ARGP_KEY_ARG:arguments->file_name=arg;break;
  case ARGP_KEY_END:
   if(!arguments->file_name)
   {error("no input file specified\n");
    argp_usage(state);
   }break;
  default:return ARGP_ERR_UNKNOWN;
 }return 0;
}
static struct argp argp={options,parse_opt,arg_doc,doc};
int
main(int argc,char**argv)
{tsip_buf*tb;int size,c,i=0;const unsigned char*_;
 FILE*f,*log;double t=0;struct arguments arguments;char file_name[0x121];
 arguments.file_name=0;arguments.escapes=0;
 INIT_ERROR(*argv);
 argp_parse(&argp,argc,argv,0,0,&arguments);
 if(arguments.escapes)enable_escapes(!0);
 tb=new_tsip();
 scanf("%lg",&t);
 /*FIXME support long filenames*/
 if(snprintf_checked(__FILE__,__LINE__,
     file_name,sizeof file_name,"%s.%3.3i",arguments.file_name,i++))
  return 4;
 if(!(log=fopen(file_name,"wb")))
 {error("can't open output file '%s'\n",file_name);
  return 3;
 }
 if(!(f=fopen(arguments.file_name,"rb")))
 {printf("can't open input file \"%s\"\n",arguments.file_name);return 2;}
 while(!feof(f))
 {if((_=parse_tsip(tb,c=getc(f),&size)))
  {expone(_,size);
   if(!feof(stdin))if(mcu_stamp()>t)
   {fclose(log);
    if(snprintf_checked(__FILE__,__LINE__,
        file_name,sizeof file_name,"%s.%3.3i",arguments.file_name,i++))
     return 4;
    if(!(log=fopen(file_name,"wb")))
    {error("can't open output file '%s'\n",file_name);
     return 3;
    }scanf("%lg",&t);
   }
  }putc(c,log);
 }fclose(log);fclose(f);free_tsip(tb);return 0;
}
