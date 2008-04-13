/*POSIX serial port module
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
#include<config.h>
#include"serialia.h"
#include"verbosity_level.h"
#include<unistd.h>
#include<sys/fcntl.h>
#include<termios.h>
#include<stdio.h>
#include<errno.h>
#include<string.h>
static struct termios vet;/* previous port settings */
static int saved_flags;/* previous fcntl flags*/
static const char*dv=CONLOQ_PORT;/* default device name */
static int port=-1;/* device file descriptor */
static void
close_port(void){close(port);port=-1;}
static void
report_error(const char*action)
{int err=errno;if(get_verbosity()<pretty_verbose)return;
 printf("%s failed: errno %i\n",action,err);
 printf("system error message \"%s\"",strerror(err));
}
static void
report_action(const char*action)
{if(get_verbosity()<pretty_verbose)return;printf("%s\n");}
int
initserialia(const char*tty)
{struct termios nov;if(tty)dv=tty;
 if(get_verbosity()>=pretty_verbose)printf("UART device \"%s\": ",dv);
#ifndef O_NDELAY
 #define O_NDELAY (0)
#endif
 /*workaround for OpenBSD(3.9): it hangs without O_NDELAY*/
 port=open(dv,O_RDWR|O_NOCTTY|O_NDELAY);
 if(port==-1){report_error("failed to open");return-1;}
 if(O_NDELAY)
 {errno=0;saved_flags=fcntl(port,F_GETFL,0);
  if(errno)
  {report_error("failed to get flags");close_port();return-1;}
  if(-1==fcntl(port,F_SETFL,saved_flags&~O_NDELAY))
  {report_error("failed to set flags");close_port();return-1;}
 }
 report_action("getting port attributes");
 if(tcgetattr(port,&vet));
 {report_error("tcgetattr");close_port();return-1;}
 nov=vet;
 cfsetospeed(&nov,B115200);cfsetispeed(&nov,B115200);
 nov.c_cflag|=CLOCAL|CREAD;nov.c_cflag&=~PARENB;
 nov.c_cflag&=~CSIZE;nov.c_cflag|=CS8;nov.c_oflag&=~OPOST;
 /*actually, GNU/Hurd (0.3 GNU-Mach 1.3.99/Hurd-0.3 i686-AT386 GNU)
  ignores c_cc[VTIME] and waits forever.
  this is not fatal because we expect bytes to arrive from the port
  often enough (typically, thousands per second)*/
 nov.c_lflag=nov.c_iflag=0;nov.c_cc[VMIN]=0;nov.c_cc[VTIME]=2;
 report_action("getting port attributes");
 if(tcsetattr(port,TCSANOW,&nov))
 {report_error("tcsetattr");close_port();return-1;}
 if(get_verbosity()>=pretty_verbose)
  report_action("%s",port<0?"fail":"success");
 return port<0;
}void
closeserialia(void)
{if(0>port)return;report_action("closing port");
 /*GNU/Hurd hangs on tcsetattr of port for the second time.
  we need to close the file first, then reopen it and set previous attrs*/
 if(close(port)){report_error("close port");port=-1;return;}
 report_action("opening port again");
 port=open(dv,O_RDWR|O_NOCTTY|O_NDELAY);
 if(-1==port){report_error("open port");return;}
 report_action("resetting tty attributes");
 if(tcsetattr(port,TCSANOW,&vet))report_error("tcsetattr");
 report_action("resetting fcntl flags");
 if(-1==fcntl(port,F_SETFL,saved_flags))
  report_error("fcntl(port,F_SETFL,saved_flags)");
 report_action("closing port the second time");
 if(close(port))report_error("close");
 else report_action("port has been successfully closed");
 port=-1;
}int
lege(void*p,int n){return read(port,p,n);}
int
scribe(const void*p,int n){return write(port,p,n);}
