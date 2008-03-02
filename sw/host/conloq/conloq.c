/*conloq: talk (currently just listen) to a stribog board 
 from UNIX terminal via RS-232 UART
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
#include"serialia.h"
#include"usage.h"
#include"parse_tsip.h"
#include"exp.h"
#include"error.h"
#include"verbosity_level.h"
#include"process_keypress.h"
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<termios.h>
#include<signal.h>
#include<errno.h>
#include<string.h>
#include<argp.h>
enum program_exit_codes
{normal_exit=0,no_log_file=1,no_uart=2,unknown_signal=3,stdin_unsetupable=4};
static FILE*
next_file(const char**file_name)
{static char s[289];int i=0;FILE*f;
 do{snprintf(s,sizeof s,"%iconloq.log",i++);f=fopen(s,"rt");if(f)fclose(f);}
 while(f);*file_name=s;return fopen(s,"wb");
}static tsip_buf*tb;static FILE*f;static struct termios saved_stdin_settings;
static int
setup_stdin(void)
{struct termios nov;
 if(tcgetattr(STDIN_FILENO,&saved_stdin_settings))
 {int err=errno;error("tcgettattr of stdin failed: errno %i",err);
  error("system error message \"%s\"",strerror(err));return!0;
 }nov=saved_stdin_settings;nov.c_lflag&=~(ECHO|ECHOE|ICANON);
 if(tcsetattr(STDIN_FILENO,TCSANOW,&nov))
 {int err=errno;error("tcsettattr of stdin failed: errno %i",err);
  error("system error message \"%s\"",strerror(err));return!0;
 }if(fcntl(STDIN_FILENO,F_SETFL,O_NDELAY))
 {int err=errno;error("fcntl of stdin failed: errno %i",err);
  error("system error message \"%s\"",strerror(err));return!0;
 }return 0;
}static void
reset_stdin(void)
{int err;putchar('\n');
 if(!tcsetattr(STDIN_FILENO,TCSANOW,&saved_stdin_settings))return;
 err=errno;error("note: can't reset stdin errno %i",err);
 error("system error message \"%s\"",strerror(err));
}static void 
close_all(void)
{closeserialia();close_exp();free_tsip(tb);tb=0;
 if(f)fclose(f);f=0;reset_stdin();
}static void 
sig_hunter(int sig)
{int r=normal_exit;
 switch(sig)
 {case SIGINT:fprintf(stderr,"INTERRUPTED\n");break;
  case SIGTERM:fprintf(stderr,"TERMINATED\n");break;
  default:fprintf(stderr,"unregistered signum; exiting\n");r=unknown_signal;
 }exit(r);
}
const char*argp_program_version=
"conloq ("PACKAGE_NAME") "PACKAGE_VERSION"\n"
"Copyright (C) 2008 Ineiev<ineiev@users.sourceforge.net>, super V 93\n"
"stribog comes with NO WARRANTY, to the extent permitted by law.\n"
"You may redistribute copies of stribog\n"
"under the terms of the GNU General Public License V3+.\n"
"For more information about these matters,\n"
"see <http://www.gnu.org/licenses/>.";
#define KEY_ASSIGNMENTS_HELP "some key assignments:\n"\
"'h' Help\n'a' Toggle ADC messages\n'g' Toggle GPS messages\n"\
"'m' Turn off all messages\n'n' Turn on all messages\n"\
"'o' Toggle odo messages\n'p' Toggle PPS messages\n"\
"'s' Toggle stat messages\n"\
"'S' Show which messages are turned on\n"\
"'t' Toggle temp messages\n"\
"'v' Toggle verbosity\n'q' Quit the programme\n"
void
help(void){printf(KEY_ASSIGNMENTS_HELP);}
const char*argp_program_bug_address ="<"PACKAGE_BUGREPORT">";
static char doc[]="talk (currently just listen) to a stribog board\v"
 KEY_ASSIGNMENTS_HELP
/*, args_doc[]=" [port]"*/;
static struct argp_option options[]=
{
 {"output",'o',"FILE",0,
  "Log to FILE instead of guessed [0-9]*conloq.log"
 },
 {"device",'d',"PORT",0,
  "Open PORT instead of default (/dev/ttyS1 on GNU, COM1 on Windows)"
 },
 {"verbose",'v',"LEVEL",OPTION_ARG_OPTIONAL,"Be verbose"},
 {"quiet",'q',0,0,"Be quiet"},
 {0}
};
struct arguments{const char*port_name,*log_name;int verbosity;};
static error_t
parse_opt(int key, char*arg, struct argp_state*state)
{struct arguments*arguments=state->input;char _;
 switch(key)
 {case 'd':arguments->port_name=arg;break;
  case 'o':arguments->log_name=arg;break;
  case 'q':arguments->verbosity--;
   if(arguments->verbosity<minimal_verbosity)
    arguments->verbosity=minimal_verbosity;
   break;
  case 'v':
   if(arg&&1!=sscanf(arg,"%i%c",&(arguments->verbosity),&_))
   {error("\"%s\" is not a valid verbosity level"
     " (should be an integer)\n",arg);
    return ARGP_ERR_UNKNOWN;
   }else arguments->verbosity++;
   if(arguments->verbosity>maximal_verbosity)
    arguments->verbosity=maximal_verbosity;
   break;
  case ARGP_KEY_ARG:if(state->arg_num>=0)argp_usage(state);break;
  case ARGP_KEY_END:if(state->arg_num<0)argp_usage(state);break;
  default:return ARGP_ERR_UNKNOWN;
 }return 0;
}
static struct argp argp={options,parse_opt,0,doc};
int 
main(int argc,char**argv)
{int size,n,j,period=0x3F;const unsigned char*_;
 unsigned char s[11520];struct arguments arg_struct;
 init_error(*argv);
 arg_struct.port_name=0;arg_struct.log_name=0;arg_struct.verbosity=0;
 argp_parse(&argp,argc,argv,0,0,&arg_struct);
 set_verbosity(arg_struct.verbosity);
 if(arg_struct.log_name)
 {if(!(f=fopen(arg_struct.log_name,"wb")))
  {error("can't open log file \"%s\"\n",arg_struct.log_name);
   return no_log_file;
  }
 }else if(!(f=next_file(&(arg_struct.log_name))))
 {error("can't open log file\n");return no_log_file;}
 if(get_verbosity()>=pretty_verbose)
  printf("Log file \"%s\" opened\n",arg_struct.log_name);
 if(setup_stdin())
 {error("can't setup your terminal\n");return stdin_unsetupable;}
 atexit(close_all);
 signal(SIGINT,sig_hunter);signal(SIGTERM,sig_hunter);
 //if(argc>2)sscanf(argv[2],"%i",&period);
 init_exp(0,period);init_turned_on();
 //if(argc>4)enable_escapes(!0);
 tb=new_tsip();
 if(initserialia(arg_struct.port_name))
 {error("can't open serial port \"%s\"\n",
   arg_struct.port_name?arg_struct.port_name:"[default]");
  return no_uart;
 }
 if(get_verbosity()>=pretty_verbose)
  printf("for help on keypresses press 'h'\n");
 do
 {if(0<(n=lege(s,sizeof(s))))for(j=0;j<n;putc(s[j++],f))
   if((_=parse_tsip(tb,s[j],&size)))expone(_,size);
 }while(process_keypress(getc(stdin)));return normal_exit;
}
