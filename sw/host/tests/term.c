/*term: terminal test
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
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<termios.h>
#include<signal.h>
#include<errno.h>
#include<string.h>
static struct termios saved_stdin_settings;
static void
report_error(const char*action)
{int err=errno;fprintf(stderr,"%s failed: errno %i\n",action,err);
 fprintf(stderr,"system error message \"%s\"",strerror(err));
}static int
setup_stdin(void)
{struct termios nov;
 if(tcgetattr(STDIN_FILENO,&saved_stdin_settings))
 {report_error("tcgettattr of stdin");return!0;}
 nov=saved_stdin_settings;nov.c_lflag&=~(ECHO|ECHOE|ICANON);
 if(tcsetattr(STDIN_FILENO,TCSANOW,&nov))
 {report_error("tcsettattr of stdin");return!0;}
 if(fcntl(STDIN_FILENO,F_SETFL,O_NDELAY))
 {report_error("fcntl of stdin");return!0;}return 0;
}static void
reset_stdin(void)
{putchar('\n');
 if(tcsetattr(STDIN_FILENO,TCSANOW,&saved_stdin_settings))
  report_error("resetting stdin");
}static void 
sig_hunter(int sig)
{switch(sig)
 {case SIGINT:fprintf(stderr,"INTERRUPTED\n");break;
  case SIGTERM:fprintf(stderr,"TERMINATED\n");break;
  default:fprintf(stderr,"unknown signum %i; exiting\n",sig);exit(1);
 }exit(0);
}static int
keypress_check(void)
{int k=getc(stdin);if(EOF!=k)printf("'%c' pressed\n",k);return k!='q';}
static int
data_lege(unsigned char*s,int n){return n;}
int 
main(int argc,char**argv)
{signal(SIGINT,sig_hunter);signal(SIGTERM,sig_hunter);
 if(setup_stdin())
 {fprintf(stderr,"can't setup your terminal\n");return 2;}
 atexit(reset_stdin);
 {unsigned char s[0x11];unsigned long long N=0;
  while(keypress_check())if(0<data_lege(s,sizeof s))
   if(++N==1l<<20){N=0;printf("chunk received\n");}
 }return 0;
}
