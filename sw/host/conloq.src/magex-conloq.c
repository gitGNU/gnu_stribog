/*magex-conloq: listen to magex from UNIX terminal via RS-232 UART
Copyright (C) 2006, 2007, 2008, 2009\
 Ineiev<ineiev@users.berlios.de>, super V 93
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
#if HAVE_CONFIG_H
# include<config.h>
#endif
#include"serialia.h"
#include"parse_tsip.h"
#include"exp.h"
#include<stribog_error.h>
#include<stribog_strings.h>
#include<stdlib.h>
#include<stdio.h>
#include<stribog_signal.h>
#include<snprintf_checked.h>
#include<argp.h>
enum exit_codes
{normal_exit=0,no_log_file=1,no_uart=2,
 terminated_via_signal=3
};
static FILE*
next_file(void)
{char s[289];int i=0;FILE*f;
 do
 {if(snprintf_checked(__FILE__,__LINE__,s,sizeof s,"%imagex-conloq.log",i++))
   return 0;
  f=fopen(s,"rt");if(f)fclose(f);
 }while(f);return fopen(s,"wb");
}static tsip_buf*tb;static FILE*f;
static void 
close_all(void)
{closeserialia();close_exp();free_tsip(tb);tb=0;if(f)fclose(f);f=0;}
const char*argp_program_version="magex-conloq"PACKAGE_VERSION_COMMENTED;
const char*argp_program_bug_address ="<"PACKAGE_BUGREPORT">";
static char doc[]="listen to a stribog board\v"
 "magex-conloq shows the incoming data and saves them in a file.\n"
 "It assumes that magex.elf runs on stribog.\n\n",
 arg_doc[]="[port]";
struct arguments{const char*port;};
static error_t
parse_opt(int key,char*arg,struct argp_state*state)
{struct arguments*arguments=state->input;
 switch(key)
 {case ARGP_KEY_ARG:arguments->port=arg;break;
  case ARGP_KEY_END:break;
  default:return ARGP_ERR_UNKNOWN;
 }return 0;
 return 0;
}
static struct argp argp={0,parse_opt,arg_doc,doc};
int 
main(int argc,char**argv)
{int size,i=0,n,j;const unsigned char*_;unsigned char s[0x121];
 struct arguments arguments;
 arguments.port=0;
 INIT_ERROR(*argv);
 argp_parse(&argp,argc,argv,0,0,&arguments);
 f=next_file();tb=new_tsip();atexit(close_all);
 if(init_signals()){error("can't setup signal handlers\n");return 4;}
 if(!f){error("can't open log file\n");return 1;}init_exp(0);
 if(initserialia(arguments.port))
 {error("can't open serial port\n");return 2;}
 while(1)
 {check_signals(terminated_via_signal);
  if(0<(n=lege(s,sizeof(s))))
  for(j=0;j<n;putc(s[j++],f))if((_=parse_tsip(tb,s[j],&size)))
   if(!(i++&0x3F))expone(_,size);
 }return 0;
}
