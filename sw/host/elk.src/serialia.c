/*elk the LPC21x programmer: POSIX serial port module
Copyright (C) 2006, 2007, 2008
 Ineiev<ineiev@users.sourceforge.net>, super V 93
This program is a part of the stribog host software section

stribog is free software; you can redistribute it and/or modify
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
#include<unistd.h>
#include<fcntl.h>
#include<termios.h>
#include<stdio.h>
static struct termios vet;/* saved port settings */
static char dv[]=ELK_PORT;/* default port name */
static int portd=-1;/* file descriptor */
int
baud(int f)
{if(f<14745+14745/20&&f>14745-14745/20)
 {printf("baud rate 115200\n");return B115200;}
 if((f<11059+11059/20&&f>11059-11059/20)||
    (f<18432+18432/20&&f>18432-18432/20))
 {printf("baud rate 57600\n");return B57600;}
 if((f<10000+10000/20&&f>10000-10000/20)||
    (f<12288+12288/20&&f>12288-12288/20)||
    (f<19661+19661/20&&f>19661-19661/20)||
    (f<24576+24576/20&&f>24576-24576/20)||
    (f<25000+25000/20&&f>25000-25000/20))
 {printf("baud rate 38400\n");return B38400;}
 if(f<15360+15360/20&&f>15360-15360/20)
 {printf("baud rate 9600\n");return B9600;}
 printf("unknown frequency: I'll try baud rate B9600\n");return B9600;
}int
init_serialia(const char*tty,int freq)
{struct termios nov;portd=open(tty?tty:dv,O_RDWR|O_NOCTTY|O_NDELAY);
 if(portd<0)return-1;tcgetattr(portd,&vet);nov=vet;
 cfsetospeed(&nov,baud(freq));cfsetispeed(&nov,baud(freq));
 nov.c_cflag|=CLOCAL|CREAD;nov.c_cflag&=~PARENB;
 nov.c_cflag&=~CSIZE;nov.c_cflag|=CS8;nov.c_oflag&=~OPOST;
 nov.c_lflag=nov.c_iflag=0;tcsetattr(portd,TCSANOW,&nov);return portd<0;
}void
close_serialia(void)
{if(0>portd)return;
 tcsetattr(portd,TCSADRAIN,&vet);fcntl(portd,F_SETFL,0);
 close(portd);portd=-1;
}int
lege(void*p,int n){return read(portd,p,n);}
int
scribe(const void*p,int n){return write(portd,p,n);}
