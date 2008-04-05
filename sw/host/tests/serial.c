/*POSIX serial port test resembling the serial module of conloq
 short RX and TX lines of your UART when running this program
Copyright (C) 2006, 2007, 2008\
 Ineiev<ineiev@users.sourceforge.net>, super V 93
This file is a part of the stribog host software section

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
#include<unistd.h>
#include<sys/fcntl.h>
#include<termios.h>
#include<signal.h>
#include<errno.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
static struct termios vet;/* previous port settings */
static const char*dv="/dev/ttyS1";/* default device name */
static int port=-1;/* file descriptor */
static void
report_error(const char*action)
{int err=errno;fprintf(stderr,"%s failed: errno %i\n",action,err);
 fprintf(stderr,"system error message \"%s\"",strerror(err));
}
int
init(const char*tty)
{struct termios nov;if(tty)dv=tty;
 printf("UART device \"%s\"..\n",dv);
#ifdef O_NDELAY
 /*workaround for OpenBSD(3.9): it hangs when there is no O_NDELAY*/
 port=open(dv,O_RDWR|O_NOCTTY|O_NDELAY);
 if(port!=-1)
 {int flags;
  printf("getting flags..\n");
  errno=0;flags=fcntl(port,F_GETFL)&~O_NDELAY;
  if(errno)
  {printf("failed to get flags\n");close(port)return-1;}
  printf("setting flags..\n");
  if(-1==fcntl(port,F_SETFL,flags))
  {printf("failed to set flags\n");close(port);return-1;}
 }
#else
 port=open(dv,O_RDWR|O_NOCTTY);
#endif
 if(port<0){report_error("open");return-1;}
 printf("opened\n");
 if(tcgetattr(port,&vet)){report_error("tcgetattr");return-1;}
 nov=vet;
 cfsetospeed(&nov,B300);cfsetispeed(&nov,B300);
 nov.c_cflag|=CLOCAL|CREAD;nov.c_cflag&=~PARENB;
 nov.c_cflag&=~CSIZE;nov.c_cflag|=CS8;nov.c_oflag&=~OPOST;
 nov.c_lflag=nov.c_iflag=0;nov.c_cc[VMIN]=0;nov.c_cc[VTIME]=2;
 printf("setting attr..\n");
 tcsetattr(port,TCSANOW,&nov);
 printf("%s\n",port<0?"fail":"success");
 return port<0;
}void
close_all(void)
{if(0>port)return;
 if(0)
 {/*GNU/Hurd hangs here. we prefer not to reset old settings*/
  tcsetattr(port,TCSANOW,&vet);
 }close(port);port=-1;
}int
lege(void*p,int n){return read(port,p,n);}
int
scribe(const void*p,int n){return write(port,p,n);}
static void 
sig_hunter(int sig)
{switch(sig)
 {case SIGINT:fprintf(stderr,"INTERRUPTED\n");break;
  case SIGTERM:fprintf(stderr,"TERMINATED\n");break;
  default:fprintf(stderr,"unknown signum %i; exiting\n",sig);exit(1);
 }exit(0);
}static void
loop(void)
{int n,i;char s[0x11];const char transmitted[]="no camel";
 long N=0;while(lege(s,sizeof s)>0);printf("line drained\n");
 while(1)
 {n=lege(s,sizeof s);
  if(n>0)
  {printf("received %i: ",n);
   for(i=0;i<n;i++)printf("%c",s[i]);putchar('\n');
  }
  if(n<=0)
  {n=scribe(transmitted,sizeof(transmitted)-1);
   if(n>0)
   {printf("transmitted %i: ",n);
    for(i=0;i<n;i++)printf("%c",transmitted[i]);putchar('\n');
   }
  }
 }
}int
main(int argc,char**argv)
{signal(SIGINT,sig_hunter);signal(SIGTERM,sig_hunter);
 if(init(argv[1]))return 1;atexit(close_all);loop();return 0;
}
