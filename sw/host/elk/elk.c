/*elk the LPC21x programmer: main function
Copyright (C) 2006, 2007, 2008\
 Ineiev<ineiev@users.sourceforge.net>, super V 93
This program is a part of stribog

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.*/
#include<stdlib.h>
#include<stdio.h>
#include"serialia.h"
#include"usage.h"
#include<unistd.h>
#include<string.h>
#include<time.h>
#include<stdarg.h>
int 
init(const char*s,int f)
{int err=0;printf("setting up port \"%s\"...",s);
 if(init_serialia(s,f)){err=-1;printf(" failed\n");}
 else printf("port setup ok\n");return err;
}/*NB (24 Oct 2007) it is not good, but the serial port is setup 
 without no timeouts, so the programme is polling CPU cycles, 
 therefore clock() difference will show something not too far 
 from real time. if we setup the timeouts like in ../conloq, 
 this programme doesn't work under the GNU/Hurd/Mach at all*/
int 
wait_for_chars(char*s,int N,int timeout)
{clock_t t;int i=0,n;char*_=s;t=clock();
 do{n=lege(_,N-i);if(n>0){i+=n;_+=n;}}
 while(i<N&&clock()-t<timeout*CLOCKS_PER_SEC/5);return i;
}const char*
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
}static int mute;/*if 0, some commands will be more verbous*/
int 
test_code(const char*s)
{int n=-1;const char*cs=0;if(sscanf(s,"%i",&n)==1)cs=code_string(n);
 if(n||!mute)
 {if(NULL!=cs)printf("%s\n",cs);else printf("unknown return code %s\n",s);}
 switch(n)
 {case 0:if(!mute)printf("CMD_SUCCESS\n");break;
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
}int 
echo_off(void)
{char s[289];const char k[]="A 0\r\n";int n;
 printf("sent %s",k);scribe(k,strlen(k));n=wait_for_chars(s,3,1);s[n]=0;
 printf("received %i bytes: %s",n,s);return test_code(s);
}void 
read_partid(void)
{char s[289];const char k[]="J\r\n";long n;
 printf("sent %s",k);scribe(k,3);n=wait_for_chars(s,sizeof(s)-1,1);s[n]=0;
 printf("received %li bytes: %s",n,s);
 if(test_code(s))return;sscanf(s+3,"%li",&n);printf("The part is ");
 switch(n)
 {case 196353:printf("LPC2131\n");break;case 196369:printf("LPC2132\n");break;
  case 196370:printf("LPC2134\n");break;case 196387:printf("LPC2136\n");break;
  case 196389:printf("LPC2138\n");break;default:printf("unknown\n");
 } 
}int 
unlock(void)
{char s[289];const char k[]="U 23130\r\n";int n;
 printf("sent %s",k);scribe(k,strlen(k));n=wait_for_chars(s,3,1);s[n]=0;
 printf("received %i bytes: %s",n,s);return test_code(s);
}
#define snprintf_checked(s,size,fmt,...) output_snprintf_error(\
 __FILE__,__LINE__,s,size,fmt,__VA_ARGS__)
int output_snprintf_error(const char*file,int line,char*s,unsigned size,
 const char*fmt,...)
#ifdef __GNUC__
__attribute__((format(printf,5,6)));
int 
output_snprintf_error(const char*file,int line,char*s,unsigned size,
 const char*fmt,...)
#endif
{va_list ap;int result;
 va_start(ap,fmt);result=vsnprintf(s,size,fmt,ap);va_end(ap);
 if(result<0||result>=size)
 {fprintf(stderr,"%s:%i: snprintf() failed: ",file,line);
  if(result>=size)
   fprintf(stderr,"too short buffer (%i chars, %i needed)\n",size,result);
  if(result<0)fprintf(stderr,"conversion error %i\n",result);return!0;
 }return 0;
}int
synchronize(int f)
{const char query[]="?",sy[]="Synchronized\r\n",
  ok[]="Synchronized\r\nOK\r\n";char s[289],s0[289];int n,i=0,vex;
 printf("Synchronizing baud rate...\n");while(wait_for_chars(s,14,2));
 do
 {scribe(query,1);printf("? sent %i\r\n",i++);n=wait_for_chars(s,14,2);
  if(n>0){s[n]=0;printf("received %i bytes: %s",n,s);}
 }while(strcmp(sy,s));
 scribe(sy,sizeof(sy)-1);printf("Synchronized sent; ");
 n=wait_for_chars(s,18,1);s[n]=0;printf("received %i bytes: %s",n,s);
 if(strcmp(ok,s))return!0;if(snprintf_checked(s,sizeof s,"%i\r\n",f))return!0;
 printf("sent %i; ",f);scribe(s,strlen(s));i=strlen(s)+4;
 n=wait_for_chars(s,i,2);s[n]=0;printf("received %i bytes: %s",n,s);
 if(snprintf_checked(s0,sizeof s0,"%i\r\nOK\r\n",f))return!0;
 if(!(vex=strcmp(s0,s)))echo_off();unlock();read_partid();return vex;
}void
read_version(void)
{char s[289];const char k[]="K\r\n";int n;
 printf("sent %s",k);scribe(k,3);n=wait_for_chars(s,sizeof(s)-1,1);s[n]=0;
 printf("received %i bytes: %s",n,s);test_code(s);
}int
prepare_sectors(unsigned start,unsigned end)
{char s[289];int n;if(snprintf_checked(s,sizeof s,"P %u %u\r\n",start,end))return!0;
 printf("sent %s",s);scribe(s,strlen(s));n=wait_for_chars(s,3,1);s[n]=0;
 printf("received %i bytes: %s",n,s);return test_code(s);
}int
erase_sectors(unsigned start,unsigned end)
{char s[289];int n;if(prepare_sectors(start,end))return-1;
 if(snprintf_checked(s,sizeof s,"E %u %u\r\n",start,end))return!0;
 printf("sent %s",s);scribe(s,strlen(s));n=wait_for_chars(s,3,1);s[n]=0;
 printf("received %i bytes: %s",n,s);return test_code(s);
}void
erase(void)
{unsigned start,end;printf("erase start: ");scanf("%u",&start);
 printf("end: ");scanf("%u",&end);erase_sectors(start,end);
}void
prepare(void)
{unsigned start,end;printf("prepare start: ");scanf("%u",&start);
 printf("end: ");scanf("%u",&end);prepare_sectors(start,end);
}int
receive_uuenc_string(char*s,int timeout)
{clock_t t;int i=0,n;const int N=64;char*_=s;t=clock();
 do{n=lege(_,1);if(n>0){i+=n;_+=n;if(_[-1]=='\n')break;}}
 while(i<N&&clock()-t<timeout*CLOCKS_PER_SEC/5);
 if(!i)return!0;s[i]=0;return _[-1]!='\n';
}int
receive_test_code(char*s)
{int n;n=wait_for_chars(s,3,1);s[n]=0;
 printf("received %i bytes: %s",n,s);
 if(n<3)return!0;return test_code(s);
}inline char
uud(char c){return (c-0x20)&0x3F;}
int
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
 if(snprintf_checked(s,sizeof s,"R %lu %u\r\n",addr,l))return!0;
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
 do
 {if(snprintf_checked(t,sizeof t,"W %lu %i\r\n",addr,n))return!0;scribe(t,strlen(t));
  i=wait_for_chars(t,3,1);t[i]=0;if(!mute)printf("received %i: %s",i,t);
  if(test_code(t))return!0;
  while(1)
  {if(snprintf_checked(t,sizeof t,"%c",n+0x20))return!0;j=strlen(t);
   for(i=cs=0;i<n;i+=3)
   {cs+=(s[i]&0xFF)+(s[i+1]&0xFF)+(s[i+2]&0xFF);t[j++]=0x20+((s[i]>>2)&0x3F);
    t[j++]=0x20+(((s[i]<<4)&0x30)|((s[i+1]>>4)&0xF));
    t[j++]=0x20+(((s[i+1]<<2)&0x3C)|((s[i+2]>>6)&0x3));
    t[j++]=0x20+(s[i+2]&0x3F);
   }if(snprintf_checked(t+j,-j-1+sizeof t,"\r\n%lu\r\n",cs))return!0;
   scribe(t,strlen(t));i=wait_for_chars(t,4,1);t[i]=0;
   if(!mute)printf("received %i: %s",i,t);if(!strcmp(t,OK))break;
   if(mute)printf("received %i: %s",i,t);i=strlen(t);
   i+=wait_for_chars(t+i,sizeof(t)-i,1);t[i]=0;if(strcmp(t,RESEND))return!0;
  }
 }while(strcmp(t,OK));return 0;
}static const unsigned long ram=0x40000400,block=4096,step=36;
int
copy_memory(unsigned long addr)
{char s[289];int k,n;unsigned long bs,ra;if(prepare_sectors(0,8))return-1;
 if(snprintf_checked(s,sizeof s,"C %lu %lu %lu\r\n",addr,ram,block))return!0;k=strlen(s);
 printf("sent %s",s);scribe(s,strlen(s));n=wait_for_chars(s,3,1);s[n]=0;
 printf("received %i bytes: %s",n,s);if(test_code(s))return test_code(s);
 ra=ram;bs=block;if(addr<64){ra+=64-addr;addr=64;bs-=64;}
 if(snprintf_checked(s,sizeof s,"M %lu %lu %lu\r\n",addr,ra,bs))return!0;k=strlen(s);
 printf("sent %s",s);scribe(s,strlen(s));n=wait_for_chars(s,3,1);s[n]=0;
 printf("received %i bytes: %s",n,s);return test_code(s);
}int
write_file(void)
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
}int 
run(unsigned long addr)
{char s[289];int n,r;if(snprintf_checked(s,sizeof s,"G %lu A\r\n",addr))return!0;
 printf("sent %s",s);scribe(s,strlen(s));n=wait_for_chars(s,3,1);s[n]=0;
 printf("received %i bytes: %s",n,s);r=test_code(s);
 n=wait_for_chars(s,sizeof(s),1);s[n]=0;
 printf("received %i bytes: %s",n,s);return r;
}enum{byte_mask=0xFF,reset=0,end=0xFF};
static void
print_array(char*s,int n)
{int i;for(i=0;i<n;i++)printf(" %2.2X",s[i]&byte_mask);printf("\n");
}int
reset_prefs_once(void)
{char c=0,s[0x11];int n;while(wait_for_chars(s,sizeof s,1));
 printf("sending reset\n");scribe(&c,1);n=wait_for_chars(s,sizeof s,1);
 printf("received on reset: ");print_array(s,n);
 if(n>1){printf("too verbous answer\n");return!0;}
 if(n==1){printf("%s\n",*s?"nack":"preferences reset done");return*s;}
 return!0;
}int
reset_prefs(void)
{int i;printf("\n");for(i=0;i<0x11;i++)if(!reset_prefs_once())return 0;
 printf("can't reset connection\n");return!0;
}void
send_empty_prefs(void){char c[2]={reset,end};scribe(c,2);}
int
load_prefs(void)
{const char format[]="mag=%i,%i,%i\nacc=%i",prefs_file[]="prefs.dat";
 enum{prefs_num=4/*NB this depends on format*/};char c[prefs_num+1],s[0x11];
 int n,x[prefs_num],i;FILE*f=fopen(prefs_file,"r");
 if(NULL==f)
 {printf("no file \"%s\"",prefs_file);send_empty_prefs();return 0;}
 if(prefs_num!=fscanf(f,format,x,x+1,x+2,x+3))
 {fprintf(stderr,"%s:%i: wrong preferences format\n",__FILE__,__LINE__);
  fprintf(stderr,"%s:%i: should be \"%s\"\n",__FILE__,__LINE__,format);return!0;
 }if(x[3]<=0)x[3]=9;c[(sizeof c)-1]=end;for(i=0;i<sizeof x/sizeof*x;i++)c[i]=x[i];
 for(i=0;i<0x11;i++)
 {if(reset_prefs())return!0;
  scribe(c,(sizeof c)-1);printf("sent:    ");print_array(c,(sizeof c)-1);
  n=wait_for_chars(s,sizeof s,1);printf("received:");print_array(s,n);
  if(n<(sizeof c)-1)printf("too few received\n");
  if(n>(sizeof c)-1){printf("too verbous answer\n");}
  if(n>=(sizeof c)-1)
  {if(!memcmp(s,c,(sizeof c)-1))
   {scribe(c+(sizeof c)-1,1);printf("end (%2.2X) sent\n",byte_mask&c[(sizeof c)-1]);
    n=wait_for_chars(s,1,1);
    if(n>0&&(byte_mask&*s)==end){printf("preferences loaded\n");return 0;}
   }if(n>0){printf("nack:");print_array(s,n);}
  }
 }return 0;
}int
load_and_go(void)
{static const unsigned long ram_org=0x40000000,used_ram=0x40000200;
 int i,m=mute;FILE*f;unsigned long addr;char s[289];mute=1;
 if(!(f=fopen("vectors","rb")))
 {printf("no interrupt vectors in current directory\n");return !0;}
 for(addr=ram_org;!feof(f);addr+=step)
 {for(i=0;i<step&&!feof(f);i++)fscanf(f,"%c",s+i);
  printf("loading %i bytes at addr=0x%lX",i,addr);
  if(write_string(s,addr,step)){fclose(f);return!0;}putchar('\n');
 }fclose(f);
 if(!(f=fopen("elk.bin","rb")))
 {printf("no programme in current directory\n");return !0;}
 for(addr=used_ram;!feof(f);addr+=step)
 {for(i=0;i<step;i++)fscanf(f,"%c",s+i);
  printf("loading %i bytes at addr=0x%lX",i,addr);
  if(write_string(s,addr,step)){fclose(f);return!0;}putchar('\n');
 }fclose(f);mute=m;i=run(used_ram);if(i)return i;return load_prefs();
}int
copy_mem(void){return copy_memory(0);}
void
close_all(void){close_serialia();}
void
program_ram(int f)
{clock_t t;synchronize(f);t=clock();while(clock()-t<CLOCKS_PER_SEC);
 echo_off();read_partid();unlock();load_and_go();
}int
main(int argc,char**argv)
{char c=!0;int err,f=14746;
 if(argc>2){sscanf(argv[2],"%i",&err);if((c=err>10))f=err;}
 usage();printf("crystal frequency assumed %i kHz\n",f);
 if((err=init(argc<2?0:argv[1],f)))return err;
 if(!c){program_ram(f);close_all();return 0;}echo_off();read_partid();
 do
 {printf(">");scanf("%c",&c);
  switch(c)
  {case's':synchronize(f);break;
   case'j':read_partid();break;case'k':read_version();break;
   case'f':printf("enter crystal frequency (kHz): ");scanf("%i",&f);
    printf("frequency assumed %i kHz\n",f);break;
   case'e':erase();break;case'u':unlock();break;
   case'p':prepare();break;case'r':read_mem();break;
   case'a':echo_off();break;case'c':copy_mem();break;
   case'b':write_file();break;case'l':load_and_go();break;case'h':help();
  } 
 }while(c!='q');close_all();return err;
}
