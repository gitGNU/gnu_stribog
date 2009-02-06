/*elk the LPC21x programmer: LPC21xx bootloader communications
Copyright (C) 2006, 2007, 2008\
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
#include"snpr_ck.h"
#include<stdio.h>
#include"lpc_loader.h"
#include<time.h>
#include<string.h>
#include<stribog_error.h>
static const char*
code_string(int n)
{switch(n)
 {case 0:return"CMD_SUCCESS";
  case 1:return"INVALID_COMMAND";
  case 2:return"SRC_ADDR_ERROR";
  case 3:return"DST_ADDR_ERROR";
  case 4:return"SRC_ADDR_NOT_MAPPED";
  case 5:return"DST_ADDR_NOT_MAPPED";
  case 6:return"COUNT_ERROR";
  case 7:return"INVALID_SECTOR";
  case 8:return"SECTOR_NOT_BLANK";
  case 9:return"SECTOR_NOT_PREPARED_FOR_WRITE_OPERATION";
  case 10:return"COMPARE_ERROR";
  case 11:return"BUSY";
  case 12:return"PARAM_ERROR";
  case 13:return"ADDR_ERROR";
  case 14:return"ADDR_NOT_MAPPED";
  case 15:return"CMD_LOCKED";
  case 16:return"INVALID_CODE";
  case 17:return"INVALID_BAUD_RATE";
  case 18:return"INVALID_STOP_BIT";
  case 19:return"CODE_READ_PROTECTION_ENABLED";
 }return 0;
}int mute;/*if 0, some commands will be more verbous*/
static int 
test_code(const char*s)
{int n=-1;const char*cs=0;if(sscanf(s,"%i",&n)==1)cs=code_string(n);
 if(n||!mute)
 {if(cs)printf("%s\n",cs);else printf("unknown return code %s\n",s);}
 return n;
}enum{test_code_strlen=3};
int 
echo_off(int primary_call)
{char s[289];const char k[]="A 0\r\n";int n;drain_uart();
 printf("sent '%s'; ",k);scribe(k,strlen(k));
 n=test_code_strlen;if(primary_call)n+=strlen(k);
 n=wait_for_chars(s,n,1);s[n]=0;
 printf("received %i bytes: '%s'; ",n,s);
 if(primary_call&&n==8)return test_code(s+strlen(k));
 return test_code(s);
}
static enum mcu_type partid=UNDEFINED_MCU_TYPE;
enum mcu_type
get_partid(void){return partid;}
enum mcu_type
read_partid__(void)
{char s[289];const char k[]="J\r\n";long n;drain_uart();
 printf("sent %s",k);scribe(k,3);n=wait_for_chars(s,sizeof(s)-1,1);s[n]=0;
 printf("received %li bytes: %s",n,s);
 if(test_code(s))return UNDEFINED_MCU_TYPE;
 sscanf(s+test_code_strlen,"%li",&n);printf("The part is ");
 switch(n)
 {case 196353:printf("LPC2131\n");return LPC2131_ID;
  case 196369:printf("LPC2132\n");return LPC2132_ID;
  case 196370:printf("LPC2134\n");return LPC2134_ID;
  case 196387:printf("LPC2136\n");return LPC2136_ID;
  case 196389:printf("LPC2138\n");return LPC2138_ID;
  default:printf("unknown\n");
 }return UNDEFINED_MCU_TYPE;
}enum mcu_type
read_partid(void){partid=read_partid__();return partid;}
int 
unlock(void)
{char s[289];const char k[]="U 23130\r\n";int n;drain_uart();
 printf("sent %s",k);scribe(k,strlen(k));
 n=wait_for_chars(s,test_code_strlen,1);s[n]=0;
 printf("received %i bytes: %s",n,s);return test_code(s);
}int
synchronize(unsigned long freq)
{const char query[]="?",sy[]="Synchronized\r\n",
  ok[]="Synchronized\r\nOK\r\n";char s[289],s0[289];int n,i=0,vex;
 drain_uart();
 printf("Synchronizing baud rate...\n");while(wait_for_chars(s,14,2));
 do
 {scribe(query,1);printf("? sent %i\r\n",i++);n=wait_for_chars(s,14,2);
  if(n>0){s[n]=0;printf("received %i bytes: %s",n,s);}
 }while(strcmp(sy,s));
 scribe(sy,sizeof(sy)-1);printf("sent '%s'; ",sy);
 n=wait_for_chars(s,18,1);s[n]=0;printf("received %i bytes: '%s'; ",n,s);
 if(strcmp(ok,s))return!0;
 if(snprintf_checked(__FILE__,__LINE__,s,sizeof s,"%lu\r\n",freq))return!0;
 printf("sent '%lu'; ",freq);scribe(s,strlen(s));i=strlen(s)+4;
 n=wait_for_chars(s,i,2);s[n]=0;
 printf("received %i bytes: '%s'; ",n,s);
 if(snprintf_checked(__FILE__,__LINE__,s0,sizeof s0,"%lu\r\nOK\r\n",freq))
  return!0;
 if(!(vex=strcmp(s0,s)))echo_off(1);
 unlock();read_partid();return vex;
}void
read_version(void)
{char s[289];const char k[]="K\r\n";int n;drain_uart();
 printf("sent %s",k);scribe(k,3);n=wait_for_chars(s,sizeof(s)-1,1);
 s[n]=0;printf("received %i bytes: %s",n,s);test_code(s);
}int
prepare_sectors(unsigned start,unsigned end)
{char s[289];int n;
 if(snprintf_checked(__FILE__,__LINE__,s,sizeof s,"P %u %u\r\n",start,end))
  return!0;
 drain_uart();
 printf("sent %s",s);scribe(s,strlen(s));
 n=wait_for_chars(s,test_code_strlen,1);s[n]=0;
 printf("received %i bytes: %s",n,s);return test_code(s);
}int
erase_sectors(unsigned start,unsigned end)
{char s[289];int n;if(prepare_sectors(start,end))return-1;
 if(snprintf_checked(__FILE__,__LINE__,s,sizeof s,"E %u %u\r\n",start,end))
  return!0;
 drain_uart();printf("sent %s",s);scribe(s,strlen(s));
 n=wait_for_chars(s,test_code_strlen,3);s[n]=0;
 printf("received %i bytes: %s",n,s);return test_code(s);
}void
erase(void)
{unsigned start,end;printf("erase start: ");scanf("%u",&start);
 printf("end: ");scanf("%u",&end);erase_sectors(start,end);
}void
prepare(void)
{unsigned start,end;printf("prepare start: ");scanf("%u",&start);
 printf("end: ");scanf("%u",&end);prepare_sectors(start,end);
}static int
receive_uuenc_string(char*s,int timeout)
{clock_t t;int i=0,n;const int N=64;char*_=s;t=clock();
 do{n=lege(_,1);if(n>0){i+=n;_+=n;if(_[-1]=='\n')break;}}
 while(i<N&&clock()-t<timeout*CLOCKS_PER_SEC/5);
 if(!i)return!0;s[i]=0;return _[-1]!='\n';
}static int
receive_test_code(char*s)
{int n;n=wait_for_chars(s,test_code_strlen,1);s[n]=0;
 printf("received %i bytes: %s",n,s);
 if(n<3)return!0;return test_code(s);
}static inline char
uud(char c){return (c-0x20)&0x3F;}
static int
decode_string(char*s,int*k,int*checksum,FILE*f)
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
int
read_memory(unsigned long addr,unsigned l,FILE*f)
{char s[289];int n,vex=0,r=0,cs=0;l-=l%4;
 if(snprintf_checked(__FILE__,__LINE__,s,sizeof s,"R %lu %u\r\n",addr,l))
  return!0;
 drain_uart();
 printf("sent %s",s);scribe(s,strlen(s));
 if(receive_test_code(s))return!0;
 do{if(receive_uuenc_string(s,1))break;vex|=decode_string(s,&r,&cs,f);}
 while(r!=l);n=wait_for_chars(s,sizeof(s)-1,1);s[n]=0;
 scribe(OK,strlen(OK));sscanf(s,"%i",&n);printf("checksum: %i (%i)\n",cs,n);
 n=wait_for_chars(s,strlen(OK),1);s[n]=0;return vex||cs!=n;
}int
read_mem(void)
{unsigned long addr,end;unsigned l;FILE*f=0;
 printf("read start: 0x");scanf("%lX",&addr);
 printf("end: 0x");scanf("%lX",&end);l=(unsigned)(end-addr);
 return read_memory(addr,l,f);
}int
write_string(const char*s,unsigned long addr,int n)
{int i,j;char t[289];unsigned long cs;
 drain_uart();
 do
 {if(snprintf_checked(__FILE__,__LINE__,t,sizeof t,"W %lu %i\r\n",addr,n))
   return!0;
  scribe(t,strlen(t));
  i=wait_for_chars(t,test_code_strlen,1);t[i]=0;
  if(!mute)printf("received %i: %s",i,t);
  if(test_code(t))return!0;
  while(1)
  {if(snprintf_checked(__FILE__,__LINE__,t,sizeof t,"%c",n+0x20))return!0;
   j=strlen(t);
   for(i=cs=0;i<n;i+=3)
   {cs+=(s[i]&0xFF)+(s[i+1]&0xFF)+(s[i+2]&0xFF);t[j++]=0x20+((s[i]>>2)&0x3F);
    t[j++]=0x20+(((s[i]<<4)&0x30)|((s[i+1]>>4)&0xF));
    t[j++]=0x20+(((s[i+1]<<2)&0x3C)|((s[i+2]>>6)&0x3));
    t[j++]=0x20+(s[i+2]&0x3F);
   }
   if(snprintf_checked(__FILE__,__LINE__,t+j,-j-1+sizeof t,"\r\n%lu\r\n",cs))
    return!0;
   scribe(t,strlen(t));i=wait_for_chars(t,4,1);t[i]=0;
   if(!mute)printf("received %i: %s",i,t);if(!strcmp(t,OK))break;
   if(mute)printf("received %i: %s",i,t);i=strlen(t);
   i+=wait_for_chars(t+i,sizeof(t)-i,1);t[i]=0;if(strcmp(t,RESEND))return!0;
  }
 }while(strcmp(t,OK));return 0;
}static const unsigned long ram=0x40000400,block=4096;
enum {step=36,vectors_string_size=step*2,vectors_size=0x20,
 checksum_size=4,checksum_offset=0x14};
static char vectors[vectors_string_size];
static unsigned long
getul(char*s)/*lpc21xx are little-endian*/
{return(((unsigned long)*s)&0xFF)|((((unsigned long)s[1])&0xFF)<<8)|
 ((((unsigned long)s[2])&0xFF)<<16)|((((unsigned long)s[3])&0xFF)<<24);
}
static void
putul(unsigned long u,char*s)
{*s++=u&0xFF;u>>=8;*s++=u&0xFF;u>>=8;*s++=u&0xFF;u>>=8;*s=u&0xFF;}
static void
put_cksum(char s[vectors_size])
{unsigned long cs;int i;
 for(i=checksum_offset;i<checksum_offset+checksum_size;s[i++]=0);
 for(cs=i=0;i<vectors_size;i+=4)cs+=getul(s+i);putul(0-cs,s+checksum_offset);
}
static int
cache_checksum(FILE*f)
{int i;
 for(i=0;i<sizeof vectors;i++)vectors[i]=getc(f);
 if(feof(f))
 {error("too short ARM program file\n");return!0;}
 put_cksum(vectors);return 0;
}int
copy_memory(unsigned long addr)
{char s[289];int k,n;unsigned long bs,ra;if(prepare_sectors(0,8))return-1;
 if(snprintf_checked(__FILE__,__LINE__,
     s,sizeof s,"C %lu %lu %lu\r\n",addr,ram,block))
  return!0;
 k=strlen(s);
 printf("sent %s",s);scribe(s,strlen(s));
 n=wait_for_chars(s,test_code_strlen,1);s[n]=0;
 printf("received %i bytes: %s",n,s);if(test_code(s))return test_code(s);
 ra=ram;bs=block;if(addr<64){ra+=64-addr;addr=64;bs-=64;}
 if(snprintf_checked(__FILE__,__LINE__,
     s,sizeof s,"M %lu %lu %lu\r\n",addr,ra,bs))
  return!0;
 k=strlen(s);
 printf("sent %s",s);scribe(s,strlen(s));
 n=wait_for_chars(s,test_code_strlen,1);s[n]=0;
 printf("received %i bytes: %s",n,s);return test_code(s);
}int
write_file(const char*target_name)
{char s[289];FILE*f;int i,n=0;unsigned long addr=ram;
 /*it is impractical to have longer target names*/
 if(snprintf_checked(__FILE__,__LINE__,s,sizeof s,"%s-rom.bin",target_name))
  return!0;
 f=fopen(s,"rb");
 if(!f){error("can't open file '%s'\n",s);return!0;}
 if(cache_checksum(f))
 {error("error while caching checksum for '%s' file\n",s);
  fclose(f);return!0;
 }
 for(addr=ram,i=0;i<sizeof vectors;i+=step,addr+=step)
 {write_string(vectors+i,addr,step);printf("^%i^",i);}
 while(!feof(f))
 {for(;addr<ram+block;addr+=step)
  {for(i=0;i<step&&!feof(f);i++)fscanf(f,"%c",s+i);printf("^%li^",ftell(f));
   if(feof(f))
   {fclose(f);write_string(s,addr,step);copy_memory(n*block);return 0;}
   if(write_string(s,addr,step)){fclose(f);return!0;}
  }copy_memory(n++*block);if(fseek(f,n*block,SEEK_SET))break;
 }fclose(f);return 0;
}int 
run(unsigned long addr)
{char s[289];int n,r;
 if(snprintf_checked(__FILE__,__LINE__,s,sizeof s,"G %lu A\r\n",addr))return!0;
 drain_uart();
 printf("sent %s",s);scribe(s,strlen(s));
 n=wait_for_chars(s,test_code_strlen,1);s[n]=0;
 printf("received %i bytes: %s\n",n,s);r=test_code(s);return r;
}int
load_ram_loader(void)
{static const unsigned long ram_base=0x40000000;
 static const unsigned long init_size=0,loader_size=(1<<10)+(1<<9),
  ram_size=32<<10,ram_org=ram_base+ram_size-loader_size-init_size,
  start_addr=ram_org+init_size;
 int i,m=mute,ret;FILE*f=0;unsigned long addr;char s[289];
 const char program_name[]="loader.bin";mute=1;
 f=fopen(program_name,"rb");ret=!f;
 if(ret){printf("no programme '%s' found\n",program_name);goto x;}
 for(addr=ram_org;!feof(f);addr+=step)
 {for(i=0;i<step&&!feof(f);i++)fscanf(f,"%c",s+i);
  printf("loading %i bytes at addr=0x%lX",i,addr);
  ret=write_string(s,addr,step);if(ret)goto x;putchar('\n');
 }mute=m;ret=run(start_addr);
 x:if(f)fclose(f);return ret;
}
