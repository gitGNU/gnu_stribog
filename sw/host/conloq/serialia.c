#include"serialia.h"/*conloq: POSIX serial port module*/
#include<unistd.h>
#include<sys/fcntl.h>
#include<termios.h>
#include<stdio.h>
static struct termios vet;/* previous port settings */
static char dv[]="/dev/ttyS1";/* default device name */
static int port=-1;/* file descriptor */
int
initserialia(const char*tty)
{struct termios nov;port=open(tty?tty:dv,O_RDWR|O_NOCTTY);
 if(port<0)return-1;tcgetattr(port,&vet);nov=vet;
 cfsetospeed(&nov,B115200);cfsetispeed(&nov,B115200);
 nov.c_cflag|=CLOCAL|CREAD;nov.c_cflag&=~PARENB;
 nov.c_cflag&=~CSIZE;nov.c_cflag|=CS8;nov.c_oflag&=~OPOST;
 nov.c_lflag=nov.c_iflag=0;nov.c_cc[VMIN]=0;nov.c_cc[VTIME]=2;
 tcsetattr(port,TCSANOW,&nov);return port<0;
}void
closeserialia(void)
{if(0>port)return;tcsetattr(port,TCSANOW,&vet);
 fcntl(port,F_SETFL,0);close(port);port=-1;
}int
lege(void*p,int n){return read(port,p,n);}
int
scribe(const void*p,int n){return write(port,p,n);}
/*This source file is a part of the stribog host software section

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
