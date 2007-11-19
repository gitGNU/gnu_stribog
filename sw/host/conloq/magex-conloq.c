/*magex-conloq: listen to magex
 from UNIX terminal via RS-232 UART
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
along with this program. If not, see <http://www.gnu.org/licenses/>.

Copyright (C) 2006, 2007 Ineiev<ineiev@users.sourceforge.net>, super V 93*/
#include"serialia.h"
#include"parse_tsip.h"
#include"exp.h"
#include"error.h"
#include<stdlib.h>
#include<stdio.h>
#include<signal.h>
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
}int 
main(int argc,char**argv)
{int size,i=0,n,j;const unsigned char*_;
 unsigned char s[0x121];f=next_file();tb=new_tsip();atexit(close_all);
 signal(SIGINT,sighunter);signal(SIGTERM,sighunter);
 if(!f){error("can't open log file\n");return 1;}init_exp(0,0);
 if(initserialia(argc>1?argv[1]:0))
 {error("can't open serial port\n");return 2;}
 while(1)if(0<(n=lege(s,sizeof(s))))for(j=0;j<n;putc(s[j++],f))
  if((_=parse_tsip(tb,s[j],&size)))if(!(i++&0x3F))expone(_,size);
 return 0;
}
