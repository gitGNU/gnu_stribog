/*tsip-with-escapes messages creation*/
/*here are two options: stick to the previous message,
which is not very error-proof, and add to the messages beginning
with DLE or ETX or EsC an extra EsC character. in the latter case
we assign EsC=0x17 because analysis of our data shows this character
to be one of the most rarely occuring at the very beginnings.

However, the former option is reliable enough and the latter brakes
compatibility, this is why the default one is the former.

To choose the latter on the target side #define enable_push_escape;

To compile this for tests on the host side (32- or 64- or 128-bit),
#define hostside_form_fix; then the enable_push_esc=0 disables
escapes, enable_push_esc=!0 enables this behaviour.*/
enum{dle=0x10,etx=0x3,esc=0x17};
static inline int push_byte(char**s,char c,int i)
{if(c==dle){*(*s)++=dle;++i;}*(*s)++=c;return 1+i;}
static inline int push_esc_(char**s,char c,int i)
{if(dle==c||etx==c||esc==c){*(*s)++=esc;++i;}return i;}
#ifdef hostside_form_fix
static int enable_push_esc;
static inline int push_esc(char**s,char c,int i)
{if(!enable_push_esc)return i;return push_esc_(s,c,i);}
#else
 #ifdef enable_push_escape
  static inline int push_esc(char**s,char c,int i){return push_esc_(s,c,i);}
 #else
  static inline int push_esc(char**s,char c,int i){return(void)s,(void)c,i;}
 #endif
#endif
static inline void form_fix(crc32_input_array_type d,int n,char*txbuf,int*len)
{int i,j;unsigned crc;char*s=(char*)d;*txbuf++=dle;j=push_esc(&txbuf,*s,1);
 crc=form_crc(d,n);n<<=2;for(i=0;i<n;i++)j=push_byte(&txbuf,s[i],j);
 j=push_byte(&txbuf,crc&0xFF,j);crc>>=8;
 j=push_byte(&txbuf,crc&0xFF,j);crc>>=8;
 j=push_byte(&txbuf,crc&0xFF,j);crc>>=8;
 j=push_byte(&txbuf,crc&0xFF,j);*txbuf++=dle;*txbuf++=etx;*len=j+2;
}/*This file has been written for the stribog project.

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.

Copyright (C) 2006, 2007 Ineiev <ineiev@users.sourceforge.net>*/

