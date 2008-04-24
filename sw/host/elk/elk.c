/*elk the LPC21x programmer: main function
Copyright (C) 2006, 2007, 2008\
 Ineiev<ineiev@users.sourceforge.net>, super V 93
This program is a part of the stribog host software section

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
#include<config.h>
#include<stdlib.h>
#include<stdio.h>
#include"serialia.h"
#include"usage.h"
#include<unistd.h>
#include<string.h>
#include<time.h>
#include<stdarg.h>
#include<argp.h>
#include<stribog_strings.h>
#include<stribog_error.h>
#include<stribog_save_wd.h>
const char 
 prefs_file_name[]=".elk.prefs.rc",/*default loaded preferences name*/
 target_subdir[]="stribog-target",/*ARM stuff subdirectory*/
 ram_subdir[]="ram_programs",/*RAM programs subdirectory*/
 rom_subdir[]="rom_programs";/*ROM programs subdirectory*/
enum program_exit_codes
{normal_exit=0,no_uart=2,no_directory=3,wrong_args=4};
static void
drain_uart(void){char s[0x11];while(0<lege(s,sizeof s));}
enum program_exit_codes 
init(const char*s,int f)
{printf("setting up port \"%s\"...",s);
 if(init_serialia(s,f)){printf(" failed\n");return no_uart;}
 printf("port setup ok\n");drain_uart();return normal_exit;
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
}
const char*
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
 {if(cs)printf("%s\n",cs);else printf("unknown return code %s\n",s);}
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
{char s[289];const char k[]="A 0\r\n";int n;drain_uart();
 printf("sent %s",k);scribe(k,strlen(k));n=wait_for_chars(s,3,1);s[n]=0;
 printf("received %i bytes: %s",n,s);return test_code(s);
}void 
read_partid(void)
{char s[289];const char k[]="J\r\n";long n;drain_uart();
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
{char s[289];const char k[]="U 23130\r\n";int n;drain_uart();
 printf("sent %s",k);scribe(k,strlen(k));n=wait_for_chars(s,3,1);s[n]=0;
 printf("received %i bytes: %s",n,s);return test_code(s);
}
#define snprintf_checked(s,size,fmt,...) output_snprintf_error(\
 __FILE__,__LINE__,s,size,fmt,__VA_ARGS__)
#ifdef __GNUC__
int output_snprintf_error(const char*file,int line,char*s,unsigned size,
 const char*fmt,...)
__attribute__((format(printf,5,6)));
#endif
int 
output_snprintf_error(const char*file,int line,char*s,unsigned size,
 const char*fmt,...)
{va_list ap;int result;
 va_start(ap,fmt);result=vsnprintf(s,size,fmt,ap);va_end(ap);
 if(result<0||result>=size)
 {fprintf(stderr,"%s:%i: snprintf() failed: ",file,line);
  if(result>=size)
   fprintf(stderr,"too short buffer (%i chars, %i needed)\n",size,result);
  if(result<0)fprintf(stderr,"conversion error %i\n",result);return!0;
 }return 0;
}
struct arguments
{const char*port_name,*target_name,
  *directory,*package_data_dir;
 int verbosity,file_input,run,write,freq;
}args;
int
synchronize(void)
{const char query[]="?",sy[]="Synchronized\r\n",
  ok[]="Synchronized\r\nOK\r\n";char s[289],s0[289];int n,i=0,vex;
 drain_uart();
 printf("Synchronizing baud rate...\n");while(wait_for_chars(s,14,2));
 do
 {scribe(query,1);printf("? sent %i\r\n",i++);n=wait_for_chars(s,14,2);
  if(n>0){s[n]=0;printf("received %i bytes: %s",n,s);}
 }while(strcmp(sy,s));
 scribe(sy,sizeof(sy)-1);printf("Synchronized sent; ");
 n=wait_for_chars(s,18,1);s[n]=0;printf("received %i bytes: %s",n,s);
 if(strcmp(ok,s))return!0;
 if(snprintf_checked(s,sizeof s,"%i\r\n",args.freq))return!0;
 printf("sent %i; ",args.freq);scribe(s,strlen(s));i=strlen(s)+4;
 n=wait_for_chars(s,i,2);s[n]=0;printf("received %i bytes: %s",n,s);
 if(snprintf_checked(s0,sizeof s0,"%i\r\nOK\r\n",args.freq))return!0;
 if(!(vex=strcmp(s0,s)))echo_off();unlock();read_partid();return vex;
}void
read_version(void)
{char s[289];const char k[]="K\r\n";int n;
 drain_uart();
 printf("sent %s",k);scribe(k,3);n=wait_for_chars(s,sizeof(s)-1,1);s[n]=0;
 printf("received %i bytes: %s",n,s);test_code(s);
}int
prepare_sectors(unsigned start,unsigned end)
{char s[289];int n;
 if(snprintf_checked(s,sizeof s,"P %u %u\r\n",start,end))return!0;
 drain_uart();
 printf("sent %s",s);scribe(s,strlen(s));n=wait_for_chars(s,3,1);s[n]=0;
 printf("received %i bytes: %s",n,s);return test_code(s);
}int
erase_sectors(unsigned start,unsigned end)
{char s[289];int n;if(prepare_sectors(start,end))return-1;
 if(snprintf_checked(s,sizeof s,"E %u %u\r\n",start,end))return!0;
 drain_uart();
 printf("sent %s",s);scribe(s,strlen(s));n=wait_for_chars(s,3,3);s[n]=0;
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
 {if(snprintf_checked(t,sizeof t,"W %lu %i\r\n",addr,n))return!0;
  scribe(t,strlen(t));
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
}
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
}
static int
chdir_to_package_data(void)
{int ret;
 if(save_wd())
 {error("can't save current working directory\n");
  return!0;
 }
 if(args.directory)
 {ret=chdir(args.directory);
  if(ret)error("can't cd to '%s'\n",args.directory);
  return ret;
 }
 ret=chdir(PACKAGE_DATA_DIR);
 if(ret)
 {error("can't cd to '%s' (package data dir)\n",PACKAGE_DATA_DIR);
  return ret;
 }
 ret=chdir(target_subdir);
 if(ret)
  error("can't cd to '%s' (ARM programs dir)\n",target_subdir);
 return ret;
}
static int
chdir_to_programs(const char*subdir)
{int r=chdir_to_package_data();
 if(args.directory)return r;if(r)return r;
 r=chdir(subdir);
 if(r)error("can't cd to '%s'\n",subdir);return r;
}
static int
write_file(void)
{char s[289];FILE*f;int i,n=0;unsigned long addr=ram;
 if(chdir_to_programs(rom_subdir))
 {if(reload_wd())
   error("couldn't return to working directory after a failure\n");
  return!0;
 }
 /*it is impractical to have longer target names*/
 strncpy(s,args.target_name,sizeof s);strncat(s,"-rom.bin",sizeof s);
 f=fopen(s,"rb");
 if(reload_wd())error("can't return back to working directory\n");
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
{char s[289];int n,r;if(snprintf_checked(s,sizeof s,"G %lu A\r\n",addr))return!0;
 drain_uart();
 printf("sent %s",s);scribe(s,strlen(s));n=wait_for_chars(s,3,1);s[n]=0;
 printf("received %i bytes: %s",n,s);r=test_code(s);
 n=wait_for_chars(s,sizeof(s),1);s[n]=0;
 printf("received %i bytes: %s",n,s);return r;
}enum{byte_mask=0xFF,reset=0,end=0xFF};
static void
print_array(char*s,int n)
{int i;for(i=0;i<n;i++)printf(" %2.2X",s[i]&byte_mask);printf("\n");}
int
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
static int no_preferences;static FILE*preferences_file;
int
load_prefs(void)
{const char format[]="mag=%i,%i,%i\nacc=%i";
 enum{prefs_num=4/*NB this depends on format*/};char c[prefs_num+1],s[0x11];
 int n,x[prefs_num],i;if(no_preferences)return 0;
 if(!preferences_file)
 {error("no preferences file; sending empty preferences\n");
  send_empty_prefs();return 0;
 }
 if(prefs_num!=fscanf(preferences_file,format,x,x+1,x+2,x+3))
 {error("wrong preferences format\n");
  error("should be \"%s\"\n",format);return!0;
 }fclose(preferences_file);preferences_file=0;
 if(x[3]<=0)x[3]=9;c[(sizeof c)-1]=end;
 for(i=0;i<sizeof x/sizeof*x;i++)c[i]=x[i];
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
}
int
load_and_go(void)
{static const unsigned long ram_org=0x40000000,used_ram=0x40000200;
 int i,m=mute;FILE*f=0;unsigned long addr;char s[289];mute=1;
 if(chdir_to_programs(ram_subdir))goto fail;
 strncpy(s,args.target_name,sizeof s);strncat(s,".vectors",sizeof s);
 if(!(f=fopen(s,"rb")))
 {error("no interrupt vectors file '%s' found\n",s);
  goto fail;
 }
 for(addr=ram_org;!feof(f);addr+=step)
 {for(i=0;i<step&&!feof(f);i++)fscanf(f,"%c",s+i);
  printf("loading %i bytes at addr=0x%lX",i,addr);
  if(write_string(s,addr,step))goto fail;putchar('\n');
 }
 strncpy(s,args.target_name,sizeof s);strncat(s,".bin",sizeof s);
 fclose(f);f=fopen(s,"rb");
 if(!f){printf("no programme '%s' found\n",s);goto fail;}
 for(addr=used_ram;!feof(f);addr+=step)
 {for(i=0;i<step;i++)fscanf(f,"%c",s+i);
  printf("loading %i bytes at addr=0x%lX",i,addr);
  if(write_string(s,addr,step))goto fail;putchar('\n');
 }mute=m;
 if(run(used_ram)||load_prefs())goto fail;fclose(f);
 if(reload_wd())
 {error("can't return back to working directory\n");return!0;}
 return 0;
 fail:if(f)fclose(f);
 if(reload_wd())
  error("couldn't return to working directory after a failure\n");
 return!0;
}
void
close_all(void)
{if(preferences_file)fclose(preferences_file);close_serialia();
 close_wd();
}
static void
kbd_loop(void)
{char c;
 do
 {printf(">");scanf("%c",&c);
  switch(c)
  {case's':synchronize();break;
   case'j':read_partid();break;case'k':read_version();break;
   case'f':printf("enter crystal frequency (kHz): ");scanf("%i",&(args.freq));
    printf("frequency assumed %i kHz\n",args.freq);break;
   case'e':erase();break;case'u':unlock();break;
   case'p':prepare();break;case'r':read_mem();break;
   case'a':echo_off();break;case'c':copy_memory(0);break;
   case'b':write_file();break;case'l':load_and_go();break;
   case'h':help();break;
   case't':no_preferences=!0;
    printf("%spreferences will be loaded\n",no_preferences?"no ":"");
    break;
  } 
 }while(c!='q');
}
const char*argp_program_version="elk"PACKAGE_VERSION_COMMENTED;
#define KEY_ASSIGNMENTS_HELP "some key assignments:\n"\
" j: read part ID\n k: read version\n s: synchronize\n"\
" l: load and run RAM-based program\n u: unlock uC for writing\n"\
" p: prepare to erase ROM;  e: erase ROM\n b: load ROM-based program\n"\
" r: dump MCU memory on screen\n q: quit\n h: commands info\n"\
" t: toggle preferences loading\n"\
"For more info, see elk sources and LPC21xx bootstrap loader documentation\n"
void
help(void){printf(KEY_ASSIGNMENTS_HELP);}
const char*argp_program_bug_address ="<"PACKAGE_BUGREPORT">";
static char doc[]="LPC213x programmer (hardly functional)\v"
 "On POSIX systems the port baud rate is set according\n"
 "to the crystal frequency; on Windows it is 115200\n\n"
 KEY_ASSIGNMENTS_HELP;
static struct argp_option options[]=
{{"device",'d',"PORT",0,
  "Open PORT instead of '"ELK_PORT"'"
 },
 {"directory",'D',"DIR",0,
  "Search for programs in DIR [build-time defined]"
 },
 {"print-configuration",'c',0,0,
  "Print build-time configuration and exit"
 },
 {"frequency",'f',"FREQ",0,
  "Assume MCU crystal frequency to be FREQ kHz [14746]"
 },
 {"target",'t',"PROGRAM",0,
  "Name of the program to be loaded [multa]"},
 {"write",'w',0,0,
  "Write the program into the flash and quit"
 },
 {"run",'r',0,0,"Load the program into RAM, run it and quit"},
 {"no-prefs",'n',0,0,
  "Don't load preferences after the program is loaded into RAM"
 },
 {"verbose",'v',"LEVEL",OPTION_ARG_OPTIONAL,"Be verbose"},
 {"verbous",0,"LEVEL",OPTION_ALIAS},
 {"quiet",'q',0,0,"Be quiet"},
 {0}
};
static error_t
parse_opt(int key,char*arg,struct argp_state*state)
{struct arguments*arguments=state->input;int n=0,r;
 switch(key)
 {case'c':
   printf("data prefix:               '%s'\n",PACKAGE_DATA_DIR);
   printf("sources directory:         '%s'\n",SOURCE_DIR);
   printf("ARM programs directory:    '%s'\n",target_subdir);
   printf("RAM programs subdirectory: '%s'\n",ram_subdir);
   printf("ROM programs subdirectory: '%s'\n",rom_subdir);
   printf("preferences file name:     '%s'\n",prefs_file_name);
   printf("default port name:         '%s'\n",ELK_PORT);
   exit(normal_exit);
   break;
  case'd':arguments->port_name=arg;break;
  case'D':
   arguments->directory=arg;arguments->package_data_dir=0;
   break;
  case'f':r=sscanf(arg,"%i%n",&(arguments->freq),&n);
   if(r!=1||arg[n]||arguments->freq<=10)
   {error("'%s' is not a valid frequency (should be an integer > 10)\n",arg);
    return ARGP_ERR_UNKNOWN;
   }break;
  case'n':no_preferences=!0;break;
  case'q':arguments->verbosity--;break;
  case'r':arguments->run=!0;break;
  case't':arguments->target_name=arg;break; 
  case'v':if(!arg){arguments->verbosity++;break;}
   r=sscanf(arg,"%i%n",&(arguments->verbosity),&n);
   if(r!=1||arg[n])
   {error("'%s' is not a valid verbosity level"
     " (should be an integer)\n",arg);
    return ARGP_ERR_UNKNOWN;
   }break; 
  case'w':arguments->write=!0;break;
  case ARGP_KEY_ARG:if(state->arg_num>=0)argp_usage(state);break;
  case ARGP_KEY_END:if(state->arg_num<0)argp_usage(state);break;
  default:return ARGP_ERR_UNKNOWN;
 }return 0;
}static struct argp argp={options,parse_opt,0,doc};
int
main(int argc,char**argv)
{enum program_exit_codes err;
 args.run=args.write=0;
 args.freq=14746;args.target_name="multa";
 args.directory=args.package_data_dir=args.port_name=0;
 init_error_dir(*argv,SOURCE_DIR);
 argp_parse(&argp,argc,argv,0,0,&args);
 printf("crystal frequency assumed %i kHz\n",args.freq);
 if(!args.target_name&&(args.write||args.run))
 {error("target not specified\n");return wrong_args;}
 atexit(close_all);
 preferences_file=fopen(prefs_file_name,"rb");
 err=init(args.port_name,args.freq);if(normal_exit!=err)return err;
 if(args.write||args.run)
 {clock_t t;synchronize();t=clock();while(clock()-t<CLOCKS_PER_SEC);
  echo_off();read_partid();unlock();
 }
 if(args.write)
 {prepare_sectors(0,8);erase_sectors(0,8);write_file();}
 if(args.run)load_and_go();
 if(args.write||args.run)return normal_exit;
 echo_off();read_partid();kbd_loop();return normal_exit;
}
