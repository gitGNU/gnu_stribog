/*decode magexp messages
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
#include"exp.h"
#include<stdint.h>
#include"error.h"
#include<stdio.h>
int init_exp(int x){return 0;}void close_exp(void){}
void expone(const unsigned char*s,int size)
{int mag[3],missed,i;unsigned char sum;
 if(size!=6){error("wrong size (%i for 6)\n",size);return;}
 for(i=sum=0;i<5;sum+=s[i++]);
 if((sum^s[5])&0xFF)
 {error("wrong checksum (%2.2X, received %2.2X)\n",sum,s[5]);return;}
 *mag=0;if(s[1]&(1<<3))*mag=-1&~(0xFFF);*mag|=*s|((((int)s[1])&0xF)<<8);
 mag[1]=0;if(s[2]&(1<<7))mag[1]=-1&~(0xFFF);
 mag[1]|=((s[1]>>4)&0xF)|(((int)s[2])<<4);
 mag[2]=0;if(s[4]&(1<<3))mag[2]=-1&~(0xFFF);mag[2]|=s[3]|((((int)s[4])&0xF)<<8);
 if(s[4]&(1<<7))missed=!0;else missed=0;
 printf("mag: %i %i %i %i\n",missed,*mag,mag[1],mag[2]);
}
