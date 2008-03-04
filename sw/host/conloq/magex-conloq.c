/*magex-conloq: listen to magex from UNIX terminal via RS-232 UART
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
#include<config.h>
#include"serialia.h"
#include"parse_tsip.h"
#include"exp.h"
#include<stribog_error.h>
#include<stdlib.h>
#include<stdio.h>
#include<signal.h>
#include<argp.h>
enum exit_codes{normal_exit=0,no_log_file=1,no_uart=2,unknown_sig=3};
static FILE*
next_file(void)
{char s[289];int i=0;FILE*f;
 do
 {snprintf(s,sizeof s,"%imagex-conloq.log",i++);
  f=fopen(s,"rt");if(f)fclose(f);
 }while(f);return fopen(s,"wb");
}static tsip_buf*tb;static FILE*f;
static void 
close_all(void)
{closeserialia();close_exp();free_tsip(tb);tb=0;if(f)fclose(f);f=0;}
static void 
sighunter(int sig)
{int r=normal_exit;
 switch(sig)
 {case SIGINT:fprintf(stderr,"INTERRUPTED\n");break;
  case SIGTERM:fprintf(stderr,"TERMINATED\n");break;
  default:fprintf(stderr,"unregistered signum; exiting\n");r=unknown_sig;
 }exit(r);
}
const char*argp_program_version=
"magex-conloq ("PACKAGE_NAME") "PACKAGE_VERSION"\n"
"Copyright (C) 2008 Ineiev<ineiev@users.sourceforge.net>, super V 93\n"
"stribog comes with NO WARRANTY, to the extent permitted by law.\n"
"You may redistribute copies of stribog\n"
"under the terms of the GNU General Public License V3+.\n"
"For more information about these matters,\n"
"see <http://www.gnu.org/licenses/>.";
const char*argp_program_bug_address ="<"PACKAGE_BUGREPORT">";
static char doc[]="listen to a stribog board\v"
 "magex-conloq shows the incoming data and saves them in a file.\n"
 "It assumes that magex.elf runs on stribog.\n\n",
 arg_doc[]="[port]";
static error_t
parse_opt(int key, char*arg, struct argp_state*state){return 0;}
static struct argp argp={0,parse_opt,arg_doc,doc};
int 
main(int argc,char**argv)
{int size,i=0,n,j;const unsigned char*_;unsigned char s[0x121];
 init_error(*argv);
 argp_parse(&argp,argc,argv,0,0,0);
 f=next_file();tb=new_tsip();atexit(close_all);
 signal(SIGINT,sighunter);signal(SIGTERM,sighunter);
 if(!f){error("can't open log file\n");return 1;}init_exp(0,0);
 if(initserialia(argc>1?argv[1]:0))
 {error("can't open serial port\n");return 2;}
 while(1)if(0<(n=lege(s,sizeof(s))))for(j=0;j<n;putc(s[j++],f))
  if((_=parse_tsip(tb,s[j],&size)))if(!(i++&0x3F))expone(_,size);
 return 0;
}
