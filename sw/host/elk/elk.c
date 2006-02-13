/*elk the LPC21x programmer: main function --- to be written
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
#include<stdlib.h>
#include<stdio.h>
#include"serialia.h"
#include"usage.h"
#include<sys/ioctl.h>
#include<unistd.h>
#include<string.h>
#include<time.h>
int init(const char*s,int f)
{int err=0;printf("setting up port \"%s\"...",s);
 if(initserialia(s,f)){err=-1;printf(" failed\n");}
 else printf("port setup ok\n");return err;
}
static int wait_for_chars(char*s,int N,int timeout)
{clock_t t;int i=0,n;char*_=s;t=clock();
 do{n=lege(_,N-i);if(n>0){i+=n;_+=n;}}
 while(i<N&&clock()-t<timeout*CLOCKS_PER_SEC/100);return i;
}int test_code(const char*s)
{int n;sscanf(s,"%i",&n);
 switch(n)
 {case 0:printf("CMD_SUCCESS: command complete\n");break;
  case 1:printf("INVALID_COMMAND\n");break;
  case 2:printf("SRC_ADDR_ERROR\n");break;
  case 3:printf("DST_ADDR_ERROR\n");break;
  case 4:printf("SRC_ADDR_NOT_MAPPED\n");break;
  case 5:printf("DST_ADDR_NOT_MAPPED\n");break;
  case 6:printf("COUNT_ERROR\n");break;
  case 7:printf("INVALID_SECTOR\n");break;
  case 8:printf("SECTOR_NOT_BLANK\n");break;
  case 9:printf("SECTOR_NOT_PREPARED_FOR_WRITE_OPERATION\n");break;
  case 10:printf("COMPARE_ERROR\n");break;
  case 11:printf("BUSY\n");break;
  case 12:printf("PARAM_ERROR\n");break;
  case 13:printf("ADDR_ERROR\n");break;
  case 14:printf("ADDR_NOT_MAPPED\n");break;
  case 15:printf("CMD_LOCKED\n");break;
  case 16:printf("INVALID_CODE\n");break;
  case 17:printf("INVALID_BAUD_RATE\n");break;
  case 18:printf("INVALID_STOP_BIT\n");break;
  case 19:printf("CODE_READ_PROTECTION_ENABLED\n");break;
 }return n;
}
int echo_off(void)
{char s[289];const char k[]="A 0\r\n";int n;
 printf("sent %s",k);scribe(k,strlen(k));
 n=wait_for_chars(s,3,50);s[n]=0;
 printf("received %i bytes: %s",n,s);return test_code(s);
}
void read_partid(void)
{char s[289];const char k[]="J\r\n";long n;
 printf("sent %s",k);scribe(k,3);n=wait_for_chars(s,sizeof(s)-1,50);s[n]=0;
 printf("received %li bytes: %s",n,s);
 if(test_code(s))return;sscanf(s+3,"%li",&n);printf("The part is ");
 switch(n)
 {case 196353:printf("LPC2131\n");break;case 196369:printf("LPC2132\n");break;
  case 196370:printf("LPC2134\n");break;case 196387:printf("LPC2136\n");break;
  case 196389:printf("LPC2138\n");break;default:printf("unknown\n");
 } 
}
int unlock(void)
{char s[289];const char k[]="U 23130\r\n";int n;
 printf("sent %s",k);scribe(k,strlen(k));
 n=wait_for_chars(s,3,50);s[n]=0;
 printf("received %i bytes: %s",n,s);return test_code(s);
}
static int syncronize(int f)
{const char query[]="?",sy[]="Synchronized\r\n",
  ok[]="Synchronized\r\nOK\r\n";char s[289],s0[289];int n,i=0,vex;
 printf("Syncronizing baud rate...\n");
 do
 {scribe(query,1);printf("? sent %i\r",i++);n=wait_for_chars(s,14,50);
  if(n>0){s[n]=0;printf("received %i bytes: %s",n,s);}
 }while(strcmp(sy,s));
 scribe(sy,sizeof(sy)-1);printf("Synchronized sent; ");
 n=wait_for_chars(s,18,50);s[n]=0;
 printf("received %i bytes: %s",n,s);
 if(strcmp(ok,s))return!0;sprintf(s,"%i\r\n",f);
 printf("sent %i; ",f);scribe(s,strlen(s));i=strlen(s)+4;
 n=wait_for_chars(s,i,100);s[n]=0;
 printf("received %i bytes: %s",n,s);sprintf(s0,"%i\r\nOK\r\n",f);
 if(!(vex=strcmp(s0,s)))echo_off();unlock();read_partid();return vex;
}
void read_version(void)
{char s[289];const char k[]="K\r\n";int n;
 printf("sent %s",k);scribe(k,3);n=wait_for_chars(s,sizeof(s)-1,50);s[n]=0;
 printf("received %i bytes: %s",n,s);test_code(s);
}
int prepare_sectors(unsigned start,unsigned end)
{char s[289];int n,k;sprintf(s,"P %u %u\r\n",start,end);k=strlen(s);
 printf("sent %s",s);scribe(s,strlen(s));
 n=wait_for_chars(s,3,50);s[n]=0;
 printf("received %i bytes: %s",n,s);return test_code(s);
}
int erase_sectors(unsigned start,unsigned end)
{char s[289];int n,k;if(prepare_sectors(start,end))return-1;
 sprintf(s,"E %u %u\r\n",start,end);k=strlen(s);
 printf("sent %s",s);scribe(s,strlen(s));
 n=wait_for_chars(s,3,50);s[n]=0;
 printf("received %i bytes: %s",n,s);return test_code(s);
}
void erase(void)
{unsigned start,end;printf("erase start: ");scanf("%u",&start);
 printf("end: ");scanf("%u",&end);erase_sectors(start,end);
}
void prepare(void)
{unsigned start,end;printf("prepare start: ");scanf("%u",&start);
 printf("end: ");scanf("%u",&end);prepare_sectors(start,end);
}
int receive_uuenc_string(char*s,int timeout)
{clock_t t;int i=0,n;const int N=64;char*_=s;t=clock();
 do{n=lege(_,1);if(n>0){i+=n;_+=n;if(_[-1]=='\n')break;}}
 while(i<N&&clock()-t<timeout*CLOCKS_PER_SEC/100);
 if(!i)return!0;s[i]=0;return _[-1]!='\n';
}
int receive_test_code(char*s)
{int n;n=wait_for_chars(s,3,50);s[n]=0;
 printf("received %i bytes: %s",n,s);
 if(n<3)return!0;return test_code(s);
}static inline char uud(char c){return (c-0x20)&0x3F;}
int decode_string(char*s,int*k,int*checksum,FILE*f)
{int n=strlen(s),i,a,b,c,num_chars,nc,cs;
 printf("string (%i): %s",num_chars=*s-0x20,s);
 for(cs=nc=0,i=1;i<n&&num_chars>nc;i+=4)
 {a=0xFF&((uud(s[i])<<2)|(uud(s[i+1])>>4));
  if(nc==num_chars)putchar('|');if(nc++<num_chars){cs+=a;if(f)putc(a,f);}
  printf("%2.2X ",a);b=0xFF&((uud(s[i+1])<<4)|(uud(s[i+2])>>2));
  if(nc==num_chars)putchar('|');if(nc++<num_chars){cs+=b;if(f)putc(b,f);}
  printf("%2.2X ",b);c=0xFF&((uud(s[i+2])<<6)|uud(s[i+3]));
  if(nc==num_chars)putchar('|');if(nc++<num_chars){cs+=c;if(f)putc(c,f);}
  printf("%2.2X ",c);
 }*checksum+=cs;*k+=num_chars;return 0;
}static const char OK[]="OK\r\n",RESEND[]="RESEND\r\n";
int read_memory(unsigned long addr,unsigned l,FILE*f)
{char s[289];int n,k,vex=0,r=0,cs=0;l-=l%4;
 sprintf(s,"R %lu %u\r\n",addr,l);k=strlen(s);
 printf("sent %s",s);scribe(s,strlen(s));
 if(receive_test_code(s))return!0;
 do{if(receive_uuenc_string(s,50))break;vex|=decode_string(s,&r,&cs,f);}
 while(r!=l);
 n=wait_for_chars(s,sizeof(s)-1,50);s[n]=0;
 scribe(OK,strlen(OK));
 sscanf(s,"%i",&n);printf("checksum: %i (%i)\n",cs,n);
 n=wait_for_chars(s,strlen(OK),50);s[n]=0;return vex||cs!=n;
}
int read_mem(void)
{unsigned long addr,end;unsigned l;FILE*f=0;
 printf("read start: 0x");scanf("%lX",&addr);
 printf("end: 0x");scanf("%lX",&end);l=(unsigned)(end-addr);
 return read_memory(addr,l,f);
}
int write_string(const char*s,unsigned long addr,int n)
{int i,j;char t[289];unsigned long cs;
 do
 {sprintf(t,"W %lu %i\r\n",addr,n);scribe(t,strlen(t));
  i=wait_for_chars(t,3,50);t[i]=0;printf("received %i: %s",i,t);
  if(test_code(t))return!0;
  while(1)
  {sprintf(t,"%c",n+0x20);j=strlen(t);
   for(i=cs=0;i<n;i+=3)
   {cs+=(s[i]&0xFF)+(s[i+1]&0xFF)+(s[i+2]&0xFF);t[j++]=0x20+((s[i]>>2)&0x3F);
    t[j++]=0x20+(((s[i]<<4)&0x30)|((s[i+1]>>4)&0xF));
    t[j++]=0x20+(((s[i+1]<<2)&0x3C)|((s[i+2]>>6)&0x3));
    t[j++]=0x20+(s[i+2]&0x3F);
   }sprintf(t+j,"\r\n%lu\r\n",cs);scribe(t,strlen(t));
   i=wait_for_chars(t,4,50);t[i]=0;printf("received %i: %s",i,t);
   if(!strcmp(t,OK))break;
   i=strlen(t);i+=wait_for_chars(t+i,sizeof(t)-i,50);t[i]=0;
   if(strcmp(t,RESEND))return!0;
  }
 }while(strcmp(t,OK));return 0;
}
static const unsigned long ram=0x40000400,block=4096,step=36;
int copy_memory(unsigned long addr)
{char s[289];int k,n;unsigned long bs,ra;if(prepare_sectors(0,8))return-1;
 sprintf(s,"C %lu %lu %lu\r\n",addr,ram,block);k=strlen(s);
 printf("sent %s",s);scribe(s,strlen(s));n=wait_for_chars(s,3,50);s[n]=0;
 printf("received %i bytes: %s",n,s);if(test_code(s))return test_code(s);
 ra=ram;bs=block;if(addr<64){ra+=64-addr;addr=64;bs-=64;}
 sprintf(s,"M %lu %lu %lu\r\n",addr,ra,bs);k=strlen(s);
 printf("sent %s",s);scribe(s,strlen(s));n=wait_for_chars(s,3,50);s[n]=0;
 printf("received %i bytes: %s",n,s);return test_code(s);
}int write_file(void)
{char s[289];FILE*f=fopen("elk.bin","rb");int i,n=0;unsigned long addr=ram;
 if(!f)return!0;
 while(!feof(f))
 {for(addr=ram;addr<ram+block;addr+=step)
  {for(i=0;i<step&&!feof(f);i++)fscanf(f,"%c",s+i);printf("^%li^",ftell(f));
   if(feof(f))
   {fclose(f);write_string(s,addr,step);copy_memory(n*block);return 0;}
   if(write_string(s,addr,step)){fclose(f);return!0;}
  }copy_memory(n++*block);if(fseek(f,n*block,SEEK_SET))break;
 }fclose(f);return 0;
}
static int run(unsigned long addr)
{char s[289];int n,r;sprintf(s,"G %lu A\r\n",addr);
 printf("sent %s",s);scribe(s,strlen(s));n=wait_for_chars(s,3,50);s[n]=0;
 printf("received %i bytes: %s",n,s);r=test_code(s);
 n=wait_for_chars(s,sizeof(s),50);s[n]=0;printf("received %i bytes: %s",n,s);
 return r;
}
int load_and_go(void)
{static const unsigned long ram_org=0x40000000,used_ram=0x40000200;
 int i;FILE*f;unsigned long addr;char s[289];
 addr=used_ram;f=fopen("elk.bin","rb");
 for(addr=used_ram;!feof(f);addr+=step)
 {for(i=0;i<step&&!feof(f);i++)fscanf(f,"%c",s+i);printf("#%lX#%i#",addr,i);
  if(write_string(s,addr,step)){fclose(f);return!0;}
 }fclose(f);f=fopen("vectors","rb");
 for(addr=ram_org;!feof(f);addr+=step)
 {for(i=0;i<step&&!feof(f);i++)fscanf(f,"%c",s+i);printf("#%lX#%i#",addr,i);
  if(write_string(s,addr,step)){fclose(f);return!0;}
 }fclose(f);
 return run(used_ram);
}
int copy_mem(void){return copy_memory(0);}
void closeall(void){closeserialia();}
int main(int argc,char**argv)
{char c;int err,f=11059;if(argc>2)sscanf(argv[3],"%i",&f);
 usage();printf("crystal frequency assumed %i kHz\n",f);
 if((err=init(argc<2?0:argv[1],f)))return err;echo_off();
 read_partid();
 do
 {printf(">");scanf("%c",&c);
  switch(c)
  {case's':syncronize(f);break;
   case'j':read_partid();break;case'k':read_version();break;
   case'f':printf("enter crystal frequency (kHz): ");scanf("%i",&f);
    printf("frequency assumed %i kHz\n",f);break;
   case'e':erase();break;case'u':unlock();break;
   case'p':prepare();break;case'r':read_mem();break;
   case'a':echo_off();break;case'c':copy_mem();break;
   case'b':write_file();break;case'l':load_and_go();break;
  } 
 }while(c!='q');
 closeall();return err;
}
