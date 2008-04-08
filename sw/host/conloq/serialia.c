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
static struct termios vet;/* previous port settings */
static const char*dv=CONLOQ_PORT;/* default device name */
static int port=-1;/* device file descriptor */
static void
report_error(const char*report)
{if(get_verbosity()>=pretty_verbose)printf("%s\n",report);}
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
 {int flags;errno=0;flags=fcntl(port,F_GETFL,0)&~O_NDELAY;
  if(errno)
  {report_error("failed to get flags");close(port);port=-1;return-1;}
  if(-1==fcntl(port,F_SETFL,flags))
  {report_error("failed to set flags");close(port);port=-1;return-1;}
 }
 tcgetattr(port,&vet);nov=vet;
 cfsetospeed(&nov,B115200);cfsetispeed(&nov,B115200);
 nov.c_cflag|=CLOCAL|CREAD;nov.c_cflag&=~PARENB;
 nov.c_cflag&=~CSIZE;nov.c_cflag|=CS8;nov.c_oflag&=~OPOST;
 nov.c_lflag=nov.c_iflag=0;nov.c_cc[VMIN]=0;nov.c_cc[VTIME]=2;
 tcsetattr(port,TCSANOW,&nov);
 if(get_verbosity()>=pretty_verbose)
  printf("%s\n",port<0?"fail":"success");
 return port<0;
}void
closeserialia(void)
{if(0>port)return;
 if(0)
 {/*GNU/Hurd hangs here. we prefer not to return to old settings*/
  /*TODO as a workaround: close port, open, apply old settings, close again*/
  report_error("resetting tty attributes..");
  if(tcsetattr(port,TCSANOW,&vet))
   report_error("failed to reset attributes");
 }report_error("closing port..");
 if(close(port))report_error("fail");else report_error("success");
 port=-1;
}int
lege(void*p,int n){return read(port,p,n);}
int
scribe(const void*p,int n){return write(port,p,n);}
