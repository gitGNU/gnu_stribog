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
#include<sbg_error.h>
#include<sbg_str.h>
#include"verb_level.h"
#include"proc_kp.h"
#include<stdlib.h>
#include<stdio.h>
#if HAVE_TERMIOS_H
# include<unistd.h>
# include<fcntl.h>
# include<termios.h>
# define IGNORE_KEYPRESSES (0)
#else
/*no termios: usual keypresses will be ignored*/
# define IGNORE_KEYPRESSES (1)
#endif
#include<sbg_signal.h>
#include<snpr_ck.h>
#include<errno.h>
#include<string.h>
#include<time.h>
#include<argp.h>
enum program_exit_codes
{normal_exit=0,no_log_file=1,no_uart=2,
 terminated_via_signal=3,stdin_unsetupable=4,
 signals_unsetupable=5
};
static FILE*
next_file(const char**file_name)
{static char s[289];int i=0;FILE*f;
 do
 {if(snprintf_checked(__FILE__,__LINE__,s,sizeof s,"%iconloq.log",i++))
   return 0;
  f=fopen(s,"rt");if(f)fclose(f);
 }while(f);*file_name=s;return fopen(s,"wb");
}static tsip_buf*tb;static FILE*f;
#if HAVE_TERMIOS_H
static struct termios saved_stdin_settings;
#endif
static int
setup_stdin(void)
{
#if HAVE_TERMIOS_H
 struct termios nov;
 if(tcgetattr(STDIN_FILENO,&saved_stdin_settings))
 {int err=errno;error("tcgettattr of stdin failed: errno %i\n",err);
  error("system error message \"%s\"\n",strerror(err));return!0;
 }nov=saved_stdin_settings;nov.c_lflag&=~(ECHO|ECHOE|ICANON);
 if(tcsetattr(STDIN_FILENO,TCSANOW,&nov))
 {int err=errno;error("tcsettattr of stdin failed: errno %i\n",err);
  error("system error message \"%s\"\n",strerror(err));return!0;
 }if(fcntl(STDIN_FILENO,F_SETFL,O_NDELAY))
 {int err=errno;error("fcntl of stdin failed: errno %i\n",err);
  error("system error message \"%s\"\n",strerror(err));return!0;
 }
#endif
 return 0;
}static void
reset_stdin(void)
{
#if HAVE_TERMIOS_H
 int err;putchar('\n');
 if(!tcsetattr(STDIN_FILENO,TCSANOW,&saved_stdin_settings))return;
 err=errno;error("note: can't reset stdin errno %i\n",err);
 error("system error message \"%s\"\n",strerror(err));
#endif
}struct arguments
{const char*port_name,*log_name;double dfreq;
 int verbosity,escapes,file_input,deafitude;
 long period,timeout;
};
static struct arguments arguments;
static void 
close_all(void)
{int interactive=get_interaction_mode()==interactive_mode;
 if(!arguments.file_input)
 {if(get_verbosity()>=pretty_verbose)printf("closing serial port\n");
  closeserialia();
 }
 if(get_verbosity()>=pretty_verbose)printf("closing parser\n");
 close_exp();free_tsip(tb);tb=0;
 if(f)
 {if(get_verbosity()>=pretty_verbose)printf("closing log\n");
  fclose(f);f=0;
 }
 if(interactive)
 {if(get_verbosity()>=pretty_verbose)printf("resetting stdin\n");
  reset_stdin();
 }
}
const char*argp_program_version="conloq"PACKAGE_VERSION_COMMENTED;
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
 "This is an interactive programme for stribog data acquisition.\n"
 "It shows the incoming data and allows displayed messages filtering.\n"
 "conloq assumes that the main application (multa.elf) runs on stribog.\n\n"
 KEY_ASSIGNMENTS_HELP;
static struct argp_option options[]=
{
 {"output",'o',"FILE",0,
  "Log to FILE instead of guessed [0-9]*conloq.log"
 },
 {"device",'d',"PORT",0,
  "Open PORT instead of '"CONLOQ_PORT"'"
 },
 {"force-deaf-mode",'D',0,0,
  "don't process keypresses (the program is terminated with Ctrl-C or "
  "other external signals only)"
 },
 {"stdin",'c',0,0,
  "Read non-interactively from stdin instead of UART device (implies -D)"
 },
 {"adc-decimation",'n',"N",0,
  "ADC messages decimation number"
 },
 {"frequency",'f',"dFREQ",0,
  "MCU ticks frequency adjustment in Hz"
 },
 {"escapes",'e',0,0,
  "enable packet-layer escapes (don't use this unless you "
   "really know what you are doing)"
 },
 {"timeout",'t',"TIMEOUT",0,
  "quit when there has been no input for TIMEOUT seconds "
  "(TIMEOUT = 0 disables the feature)"
 },
 {"verbose",'v',"LEVEL",OPTION_ARG_OPTIONAL,"Be verbose"},
 {"verbous",0,"LEVEL",OPTION_ALIAS},
 {"quiet",'q',0,0,"Be quiet"},
 {0}
};
static error_t
parse_opt(int key, char*arg, struct argp_state*state)
{struct arguments*arguments=state->input;int n=0,r;
 switch(key)
 {case 'd':arguments->port_name=arg;arguments->file_input=0;break;
  case'c':arguments->port_name=0;arguments->file_input=!0;
   /*fall to next case*/
  case'D':arguments->deafitude=!0;break;
  case 'f':r=sscanf(arg,"%lg%n",&(arguments->dfreq),&n);
   if(r!=1||arg[n])
   {error("'%s' is not a valid frequency adjustment"
     " (should be a real number)\n",arg);
    return ARGP_ERR_UNKNOWN;
   }break;
  case 'n':r=sscanf(arg,"%li%n",&(arguments->period),&n);
   if(r!=1||arg[n]||arguments->period<=0)
   {error("'%s' is not a valid decimation number"
     " (should be an integer > 0)\n",arg);
    return ARGP_ERR_UNKNOWN;
   }break;
  case 'o':arguments->log_name=arg;break;
  case 'q':arguments->verbosity--;break;
  case 'e':arguments->escapes=!0;break;
  case 't':r=sscanf(arg,"%li%n",&(arguments->timeout),&n);
   if(r!=1||arg[n]||arguments->timeout<0)
   {error("'%s' is not a valid timeout "
     "(should be an integer >= 0)\n",arg);
    return ARGP_ERR_UNKNOWN;
   }break;
  case 'v':if(!arg){arguments->verbosity++;break;}
   r=sscanf(arg,"%i%n",&(arguments->verbosity),&n);
   if(r!=1||arg[n])
   {error("'%s' is not a valid verbosity level"
     " (should be an integer)\n",arg);
    return ARGP_ERR_UNKNOWN;
   }break; 
  case ARGP_KEY_ARG:if(state->arg_num>=0)argp_usage(state);break;
  case ARGP_KEY_END:if(state->arg_num<0)argp_usage(state);break;
  default:return ARGP_ERR_UNKNOWN;
 }return 0;
}
static struct argp argp={options,parse_opt,0,doc};
static FILE*input_file;/*input if the file is not an UART device*/
static int
there_is_something_to_read(void)
{return!(feof(input_file)||ferror(input_file));}
static int
keypress_check(void)
{return IGNORE_KEYPRESSES||process_keypress(getc(stdin));}
static int
forever(void){return 1;}
static int(*
dont_exit)(void)=keypress_check;
static int
data_lege(unsigned char*s,int n){return lege(s,n);}
static int
read_data_from_file(unsigned char*s,int n)
{return fread(s,1,n,input_file);}
static int(*
get_next_data)(unsigned char*,int)=data_lege;
int 
main(int argc,char**argv)
{long period;
 INIT_ERROR(*argv);
 arguments.dfreq=8550;arguments.port_name=arguments.log_name=0;
 arguments.escapes=arguments.verbosity=arguments.file_input=0;
 arguments.timeout=arguments.deafitude=0;
 arguments.period=-1;
 argp_parse(&argp,argc,argv,0,0,&arguments);
 set_verbosity(arguments.verbosity);
 set_interaction_mode(arguments.deafitude?
  deaf_mode:interactive_mode);
 if(get_verbosity()>=pretty_verbose)
 {if(get_interaction_mode()==deaf_mode)
   printf("Note: the programme is deaf to keypresses\n");
  else printf("Note: the mode is interactive\n");
 }
 period=(get_interaction_mode()==deaf_mode)?1:0x3F;
 init_turned_on();
 if(arguments.period>0)period=arguments.period;
 if(arguments.log_name)
 {if(!(f=fopen(arguments.log_name,"wb")))
  {error("can't open log file \"%s\"\n",arguments.log_name);
   return no_log_file;
  }
 }else if(!(f=next_file(&(arguments.log_name))))
 {error("can't open log file\n");return no_log_file;}
 if(get_verbosity()>=pretty_verbose)
  printf("Log file \"%s\" opened\n",arguments.log_name);
 if(get_interaction_mode()==interactive_mode)
 {if(setup_stdin())
  {error("can't setup your terminal\n");return stdin_unsetupable;}
 }atexit(close_all);
 if(!arguments.file_input)if(initserialia(arguments.port_name))
 {error("can't open serial port \"%s\"\n",
   arguments.port_name?arguments.port_name:"[default]");
  return no_uart;
 }
 if(get_interaction_mode()==deaf_mode)dont_exit=forever;
 if(arguments.file_input)
 {input_file=stdin;
  dont_exit=there_is_something_to_read;
  get_next_data=read_data_from_file;
  if(get_verbosity()>=pretty_verbose)
   printf("the data are waited to come from stdin\n");
 }
 if(get_verbosity()>=pretty_verbose&&get_interaction_mode()!=deaf_mode)
  printf("for help on keypresses press 'h'\n");
 if(init_signals())
 {error("can't setup signal handlers\n");
  return signals_unsetupable;
 }
 if(arguments.escapes)enable_escapes(!0);
 if(get_verbosity()>=pretty_verbose)
 {printf(arguments.escapes?
    "escapes are enabled\n":"escapes are disabled\n");
  printf("the assumed MCU frequency is adjusted by %.3f Hz\n",
   arguments.dfreq);
  if(arguments.timeout)
   printf("timeout is %li s\n",arguments.timeout);
  else printf("no timeout\n");
  printf("ADC messages decimation number is %li\n",period);
 }
 tb=new_tsip();init_exp(period);
 adjust_frequency(arguments.dfreq);
 {static int size,n,j;const unsigned char*_;
  unsigned char s[1152];unsigned long long N=0;
  time_t t=time(0);
  while(dont_exit())
  {check_signals(terminated_via_signal);
   if(0<(n=get_next_data(s,sizeof s)))
   {for(j=0;j<n;putc(s[j++],f),N++)
     if((_=parse_tsip(tb,s[j],&size)))if(expone(_,size))
      error("(error at position %llu)\n",N);
    t=time(0);
   }if(arguments.timeout&&time(0)-t>arguments.timeout)break;
  }
 }return normal_exit;
}
