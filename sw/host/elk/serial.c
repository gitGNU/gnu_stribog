/*elk the LPC21x programmer: platform-independent functions
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
#include"serialia.h"
#include<time.h>
int
send_bytes(char*s,int n)
{while(n>0){int k=scribe(s,n);if(k>0){s+=k;n-=k;}}
 return 0;
}
void
drain_uart(void){char s[0x11];while(0<lege(s,sizeof s));}
/*NB (24 Oct 2007) it is not good, but the serial port is setup 
 without no timeouts, so the programme is drawing CPU cycles, 
 therefore clock() difference will show something not too far 
 from real time. if we setup the timeouts like in ../conloq, 
 this programme doesn't work under the GNU/Hurd/Mach at all*/
int 
wait_for_chars(char*s,int N,int timeout)
{clock_t t;int i=0,n;char*_=s;t=clock();
 do{n=lege(_,N-i);if(n>0){i+=n;_+=n;}}
 while(i<N&&clock()-t<timeout*CLOCKS_PER_SEC/5);return i;
}
