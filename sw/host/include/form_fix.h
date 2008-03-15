enum{dle=0x10,etx=0x3,esc=0x17};/*tsip-with-escapes messages creation*/
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
static inline void form_fix(const crc32_input_array_token*d,int n,char*txbuf,int*len)
{int i,j;unsigned crc;char*s=(char*)d;*txbuf++=dle;j=push_esc(&txbuf,*s,1);
 crc=form_crc(d,n);n<<=2;for(i=0;i<n;i++)j=push_byte(&txbuf,s[i],j);
 j=push_byte(&txbuf,crc&0xFF,j);crc>>=8;
 j=push_byte(&txbuf,crc&0xFF,j);crc>>=8;
 j=push_byte(&txbuf,crc&0xFF,j);crc>>=8;
 j=push_byte(&txbuf,crc&0xFF,j);*txbuf++=dle;*txbuf++=etx;*len=j+2;
}/*This file has been written for the stribog project.

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

Copyright (C) 2006, 2007 Ineiev <ineiev@users.sourceforge.net>*/

