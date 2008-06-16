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
#include<time.h>
static struct termios vet;/* previous port settings */
static int saved_flags;/* previous fcntl flags*/
static const char*dv="/dev/ttyS0";/* default device name */
static int port=-1;/* device file descriptor */
static void
close_port(void){close(port);port=-1;}
static void
report_error(const char*action)
{int err=errno;fprintf(stderr,"%s failed: errno %i\n",action,err);
 fprintf(stderr,"system error message \"%s\"",strerror(err));
}
int
init(const char*tty)
{struct termios nov;if(tty)dv=tty;
 printf("UART device \"%s\": ",dv);
#ifndef O_NDELAY
 #define O_NDELAY (0)
#endif
 /*workaround for OpenBSD(3.9): it hangs without O_NDELAY*/
 port=open(dv,O_RDWR|O_NOCTTY|O_NDELAY);
 printf("open\n");
 if(port==-1){report_error("open");return-1;}
 if(O_NDELAY)
 {errno=0;
  printf("get flags..\n");
  saved_flags=fcntl(port,F_GETFL,0);
  if(errno)
  {report_error("get flags");close_port();return-1;}
  printf("set flags..\n");
  if(-1==fcntl(port,F_SETFL,saved_flags&~O_NDELAY))
  {report_error("set flags");close_port();return-1;}
 }
 printf("get attr..\n");
 if(tcgetattr(port,&vet))
 {report_error("tcgetattr");close_port();return-1;
 }nov=vet;
 cfsetospeed(&nov,B300);cfsetispeed(&nov,B300);

 nov.c_cflag|=CLOCAL|CREAD;nov.c_cflag&=~PARENB;
 nov.c_cflag&=~CSIZE;nov.c_cflag|=CS8;nov.c_oflag&=~OPOST;
 nov.c_lflag=0;nov.c_iflag=0;
 /*actually, GNU/Hurd ignores c_cc[VTIME] and waits forever*/
 nov.c_cc[VMIN]=0;nov.c_cc[VTIME]=2;
 printf("set attr..\n");
 if(tcsetattr(port,TCSANOW,&nov))
 {report_error("tcsetattr");close_port();return-1;}
 return 0;
}void
close_all(void)
{if(0>port)return;printf("\nclosing port..");
 if(close(port)){report_error("closing port");port=-1;return;}
 if(0)
 {/*GNU/Hurd does not like this;
  and simply setting saved attributes, too*/
  printf("\nopening again..");
  port=open(dv,O_RDWR|O_NOCTTY|O_NDELAY);
  if(-1==port){report_error("open");return;}
  printf("\nresetting port attributes..");
  if(tcsetattr(port,TCSANOW,&vet))report_error("tcsetattr");
  printf("\nresetting fcntl flags..");
  if(-1==fcntl(port,F_SETFL,saved_flags))report_error("fcntl(..,F_SETFL..");
  printf("\nclosing port the second time..\n");
  if(close(port))report_error("close");
 }port=-1;
}int
lege(void*p,int n){return read(port,p,n);}
int
scribe(const void*p,int n){return write(port,p,n);}
static volatile sig_atomic_t terminate_program,signal_value;
static void
sig_hunter(int sig)
{signal_value=sig;terminate_program=!0;}
static void
go_out(void)
{switch(signal_value)
 {case SIGINT:fprintf(stderr,"INTERRUPTED\n");break;
  case SIGTERM:fprintf(stderr,"TERMINATED\n");break;
  default:
   fprintf(stderr,"unregistered signum %i; exiting\n",signal_value);
 }exit(1);
}static void
loop(void)
{int n,i;char s[0x11];const char tx[]="no camel";
 time_t t=time(0)-2;long transmitted=0,received=0;
 printf("start loop\n");
 while(1)
 {if(terminate_program)go_out();
  if(time(0)-t>1&&received==transmitted)
  {t=time(0);
   n=scribe(tx,sizeof(tx)-1);
   if(n>0)
   {transmitted+=n;printf("transmitted %li: ",transmitted);
    for(i=0;i<n;i++)printf("%c",tx[i]);putchar('\n');
   }
  }
  n=transmitted-received;if(n>sizeof s)n=sizeof s;
  if(n)n=lege(s,n);
  if(n>0)
  {received+=n;printf("received %li: ",received);
   for(i=0;i<n;i++)printf("%c",s[i]);putchar('\n');
  }
 }
}static sigset_t sa_mask;/*accumulated mask for all handled signals*/
static void
setup_signal(int sig,sighandler_t h)
{struct sigaction sa;
 if(sigaction(sig,0,&sa))return!0;
 if(SIG_IGN==sa.sa_handler)return 0;
 if(sigaddset(&sa_mask,sig))return!0;
 sa.sa_mask=sa_mask;sa.sa_handler=h;
 sa.sa_flags=0;return sigaction(sig,&sa,0);
}int
main(int argc,char**argv)
{sigemptyset(&sa_mask);
 setup_signal(SIGINT,sig_hunter);setup_signal(SIGTERM,sig_hunter);
 if(init(argv[1]))return 1;atexit(close_all);loop();return 0;
}
