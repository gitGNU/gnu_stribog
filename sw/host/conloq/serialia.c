/*conloq: POSIX serial port module
This program is a part of the stribog host software section

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Copyright (C) 2006 D.Ineiev <ineiev@yahoo.co.uk>*/
#include"serialia.h"
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/ioctl.h>
#include<fcntl.h>
#include<termios.h>
#include<stdlib.h>
#include<stdio.h>
static struct termios vet,nov;static char dv[]="/dev/ttyS1";
static int portd=-1;
int initserialia(const char*tty)
{portd=open(tty?tty:dv,O_RDWR|O_NOCTTY|O_NDELAY|O_NONBLOCK);
 if(portd<0)return-1;tcgetattr(portd,&vet);nov=vet;
 cfsetospeed(&nov,B115200);cfsetispeed(&nov,B115200);
 nov.c_cflag|=CLOCAL|CREAD;nov.c_cflag&=~PARENB;
 nov.c_cflag&=~CSIZE;nov.c_cflag|=CS8;
 nov.c_lflag&=~(ICANON|ECHO|ECHOE|ISIG);nov.c_oflag&=~OPOST;
 nov.c_iflag&=~(INLCR|ICRNL|IUCLC|IXON|IXOFF);
 tcsetattr(portd,TCSANOW,&nov);fcntl(portd,F_SETFL,FNDELAY);
 return portd<0;
}
void closeserialia(void)
{if(0>portd)return;
 tcsetattr(portd,TCSADRAIN,&vet);fcntl(portd,F_SETFL,0);close(portd);
}
int lege(void*p,int n){return read(portd,p,n);}
int scribe(const void*p,int n){return write(portd,p,n);}
