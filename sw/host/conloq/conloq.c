/*conloq: talk (currently just listen) to a stribog board 
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
#include"usage.h"
#include"parse_tsip.h"
#include"exp.h"
#include"error.h"
#include"verbosity_level.h"
#include"process_keypress.h"
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<termios.h>
#include<signal.h>
#include<errno.h>
#include<string.h>
enum exit_codes/*return values for programme*/
{normal_exit=0,no_log_file=1,no_uart=2,unknown_sig=3,stdin_unsetupable=4};
static FILE*
next_file(void)
{char s[289];int i=0;FILE*f;
 do{snprintf(s,sizeof s,"%iconloq.log",i++);f=fopen(s,"rt");if(f)fclose(f);}
 while(f);return fopen(s,"wb");
}static tsip_buf*tb;static FILE*f;static struct termios saved_stdin_settings;
static int
setup_stdin(void)
{struct termios nov;
 if(tcgetattr(STDIN_FILENO,&saved_stdin_settings))
 {int err=errno;error("tcgettattr of stdin failed: errno %i",err);
  error("system error message \"%s\"",strerror(err));return!0;
 }nov=saved_stdin_settings;nov.c_lflag&=~(ECHO|ECHOE|ICANON);
 if(tcsetattr(STDIN_FILENO,TCSANOW,&nov))
 {int err=errno;error("tcsettattr of stdin failed: errno %i",err);
  error("system error message \"%s\"",strerror(err));return!0;
 }if(fcntl(STDIN_FILENO,F_SETFL,O_NDELAY))
 {int err=errno;error("fcntl of stdin failed: errno %i",err);
  error("system error message \"%s\"",strerror(err));return!0;
 }return 0;
}static void
reset_stdin(void)
{int err;putchar('\n');
 if(!tcsetattr(STDIN_FILENO,TCSANOW,&saved_stdin_settings))return;
 err=errno;error("note: can't reset stdin errno %i",err);
 error("system error message \"%s\"",strerror(err));
}static void 
close_all(void)
{closeserialia();close_exp();free_tsip(tb);tb=0;
 if(f)fclose(f);f=0;reset_stdin();
}static void 
sig_hunter(int sig)
{int r=normal_exit;
 switch(sig)
 {case SIGINT:fprintf(stderr,"INTERRUPTED\n");break;
  case SIGTERM:fprintf(stderr,"TERMINATED\n");break;
  default:fprintf(stderr,"unregistered signum; exiting\n");r=unknown_sig;
 }exit(r);
}int 
main(int argc,char**argv)
{int size,n,j,period=0x3F;const unsigned char*_;
 unsigned char s[11520];usage();
 f=next_file();
 if(NULL==f){error("can't open log file\n");return no_log_file;}
 if(setup_stdin())return stdin_unsetupable;atexit(close_all);
 signal(SIGINT,sig_hunter);signal(SIGTERM,sig_hunter);
 if(argc>2)sscanf(argv[2],"%i",&period);init_exp(0,period);init_turned_on();
 if(argc>4)enable_escapes(!0);tb=new_tsip();
 if(initserialia(argc>1?argv[1]:0))
 {error("can't open serial port\n");return no_uart;}
 do
 {if(0<(n=lege(s,sizeof(s))))for(j=0;j<n;putc(s[j++],f))
   if((_=parse_tsip(tb,s[j],&size)))expone(_,size);
 }while(process_keypress(getc(stdin)));return normal_exit;
}
