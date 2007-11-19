#include<stdio.h>/*simple odometer*//*PC (DB9-M)pin 2<-pin 3 (DB9-M) odometer*/
#include<time.h> /*firmware test*/  /*          pin 3->pin 3 (DB9-F)*/
#include"serialia.h"                /*          pin 5<-> GND */
static int nl,j;
void decode(const unsigned char*s)
{unsigned cnt=s[1]|(((unsigned)s[0])<<6),
 t=(((unsigned)s[2])<<12)|(((unsigned)s[3])<<6)|s[4],_,i;static unsigned t0,c0;
 for(_=i=0;i<6;i++)_^=s[i];
 if(_)fprintf(stderr,"%s:%i: checksums don't match\n",__FILE__,__LINE__);
 {unsigned dt=t>t0?(t-t0):(1<<16)+t-t0;t0=t;if(cnt<c0)c0=cnt;
  printf("%4u %04u ",dt,cnt-c0);c0=cnt;
  if(!(++j%8)){putchar('\n');nl=!0;}else nl=0;
 }
}static FILE*log;
void process(int c)
{static unsigned char s[10],nmea[100];static int i,in;if(log)putc(c,log);
 if(c&0x80)
 {s[i++]=c&0x3F;
  if(i>7)
  {i=0;fprintf(stderr,"%s:%i:hodo msg too long\n",__FILE__,__LINE__);return;}
  if(!(c&(1<<6)))
  {if(i>5){decode(s+i-6);}
   else fprintf(stderr,"%s:%i:hodo msg too short (%i)\n",__FILE__,__LINE__,i);
   i=0;
  }
 }
 else
 {nmea[in++]=c;if(in>=sizeof(nmea)){in=0;return;}
  if(c=='\n'){nmea[in]=0;if(!nl)putchar('\n');printf("%s",nmea);in=0;nl=!0;j=0;}
 }if(log)fflush(log);
}
int main(int argc,char**argv)
{char c;FILE*f=0;time_t t=time(0);const char*s=0;if(argc>1)s=argv[1];
 initserialia(s);if(argc>2)f=fopen(argv[2],"rb");log=fopen("hodo.log","wb");
 while(1)
 {if(lege(&c,1)>0)process(c);if(!f)continue;
  if(!feof(f)){if(t!=time(0)){c=getc(f);while(!scribe(&c,1));}}else
  {fclose(f);f=fopen(argv[2],"rb");time(&t);}
 }if(f)fclose(f);if(log)fclose(log);return 0;
}/*This is an auxiliary part of stribog
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

Copyright (C) 2007 Ineiev<ineiev@users.sourceforge.net>, super V 93*/
