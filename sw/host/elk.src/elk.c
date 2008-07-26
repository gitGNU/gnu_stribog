/*elk the LPC21x programmer: main function
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
#include<config.h>
#include<stdlib.h>
#include<stdio.h>
#include"serialia.h"
#include<unistd.h>
#include<string.h>
#include<time.h>
#include<argp.h>
#include<stribog_strings.h>
#include<stribog_error.h>
#include<stribog_save_wd.h>
#include"ram_loader.h"
#include"lpc_loader.h"
#include<snprintf_checked.h>
const char 
 prefs_file_name[]=".elk.prefs.rc",/*default loaded preferences name*/
 target_subdir[]="stribog-target",/*ARM stuff subdirectory*/
 ram_subdir[]="ram_programs",/*RAM programs subdirectory*/
 rom_subdir[]="rom_programs";/*ROM programs subdirectory*/
enum program_exit_codes
{normal_exit=0,no_uart=2,no_directory=3,wrong_args=4};
enum program_exit_codes 
init(const char*s,int f)
{printf("setting up port \"%s\"...",s);
 if(init_serialia(s,f)){printf(" failed\n");return no_uart;}
 printf("port setup ok\n");drain_uart();return normal_exit;
}
struct arguments
{const char*port_name,*target_name,
  *directory,*package_data_dir;
 int verbosity,file_input,run,write,freq;
}args;
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
write_target(void)
{int r=chdir_to_programs(rom_subdir);
 if(!r)r=write_file(args.target_name);
 if(reload_wd())
  error("couldn't return to working directory\n");
 return r;
}
enum{byte_mask=0xFF,reset=0,end=0xFF};
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
{int ret;if(chdir_to_programs(ram_subdir))return!0;
 ret=load_ram_loader()||load_target(args.target_name)||load_prefs();
 if(reload_wd())
  error("couldn't return to working directory after a failure\n");
 return ret;
}
void
close_all(void)
{if(preferences_file)fclose(preferences_file);
 close_serialia();close_wd();
}
const char*argp_program_version="elk"PACKAGE_VERSION_COMMENTED;
#define KEY_ASSIGNMENTS_HELP "some key assignments:\n"\
" j: read part ID\n k: read version\n s: synchronize\n"\
" l: load and run RAM-based program\n u: unlock uC for writing\n"\
" p: prepare to erase ROM;  e: erase ROM\n b: load ROM-based program\n"\
" r: dump MCU memory on screen\n q: quit\n h: commands info\n"\
" t: toggle preferences loading\n"\
"For more info, see elk sources and LPC21xx bootstrap loader documentation\n"
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
static void
kbd_loop(void)
{char c;
 do
 {printf(">");scanf("%c",&c);
  switch(c)
  {case's':synchronize(args.freq);break;
   case'j':read_partid();break;case'k':read_version();break;
   case'f':printf("enter crystal frequency (kHz): ");scanf("%i",&(args.freq));
    printf("frequency assumed %i kHz\n",args.freq);break;
   case'e':erase();break;case'u':unlock();break;
   case'p':prepare();break;case'r':read_mem();break;
   case'a':echo_off(0);break;case'c':copy_memory(0);break;
   case'b':write_target();break;case'l':load_and_go();break;
   case'h':printf(KEY_ASSIGNMENTS_HELP);break;
   case't':no_preferences=!0;
    printf("%spreferences will be loaded\n",no_preferences?"no ":"");
    break;
  } 
 }while(c!='q');
}
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
 INIT_ERROR(*argv);
 args.run=args.write=0;
 args.freq=14746;args.target_name="multa";
 args.directory=args.package_data_dir=args.port_name=0;
 argp_parse(&argp,argc,argv,0,0,&args);
 printf("crystal frequency assumed %i kHz\n",args.freq);
 if(!args.target_name&&(args.write||args.run))
 {error("target not specified\n");return wrong_args;}
 atexit(close_all);
 preferences_file=fopen(prefs_file_name,"rb");
 err=init(args.port_name,args.freq);if(normal_exit!=err)return err;
 if(args.write||args.run)
 {/*clock_t t; FIXME: check if this works everywhere*/
  synchronize(args.freq);
  /*t=clock();while(clock()-t<CLOCKS_PER_SEC);*/
 }
 if(args.write)
 {unlock();prepare_sectors(0,8);erase_sectors(0,8);write_target();}
 if(args.run)load_and_go();
 if(args.write||args.run)return normal_exit;
 kbd_loop();return normal_exit;
}
