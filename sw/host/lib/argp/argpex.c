/*emergency argp implementation test
Copyright (C) 2008\
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
#ifdef HAVE_CONFIG_H
 #include<config.h>
#else
 #define PACKAGE_NAME "unconfigured stribog-hosttools"
 #define PACKAGE_VERSION "unconfigured version"
 #define PACKAGE_BUGREPORT "unconfigured address" 
#endif
#include<stdio.h>
#include<string.h>
#include<argp.h>
const char*argp_program_version=
"argp ("PACKAGE_NAME") "PACKAGE_VERSION"\n"
"Copyright (C) 2008 Ineiev<ineiev@users.sourceforge.net>, super V 93\n"
"stribog comes with NO WARRANTY, to the extent permitted by law.\n"
"You may redistribute copies of stribog\n"
"under the terms of the GNU General Public License V3+.\n"
"For more information about these matters,\n"
"see <http://www.gnu.org/licenses/>.";
#define HELP_STRING "another help message\n"\
"(another help message ends)\n"
const char*argp_program_bug_address ="<"PACKAGE_BUGREPORT">";
void
help(void){printf(HELP_STRING);}
static char doc[]="argp test\v"
 HELP_STRING, args_doc[]="[port]";
enum local_option_keys{hungry_key=4913};
static struct argp_option options[]=
{{"output",'o',"FILE",0,"output help"},
 {"device",'d',"PORT",0,"device help"},
 {"port",'d',"PORT",OPTION_ALIAS},
 {"another-device",0,"PORT",OPTION_ALIAS},
 {0,'p',"PORT",OPTION_ALIAS},
 {"quiet",'q',0,0,"Be quiet"},
 {"silent",'s',0, OPTION_ALIAS},
 {"hungry",hungry_key,0,0,"Be hungry"},
 {"verbose",'v',"LEVEL",OPTION_ARG_OPTIONAL,"Be verbose"},
 {"facunde",0,"GRADUS",OPTION_ARG_OPTIONAL|OPTION_ALIAS},
 {"verbous",'v',"GRADUS",OPTION_ARG_OPTIONAL|OPTION_ALIAS},
 {0,'f',"LEVEL",OPTION_ARG_OPTIONAL|OPTION_ALIAS},
 {0}
};
struct arguments{const char*port_name,*log_name;int verbosity;};
static error_t
parse_opt(int key,char*arg,struct argp_state*state)
{struct arguments*arguments=state->input;
 switch(key)
 {case hungry_key:printf("hungry found\n");break;
  case'd':arguments->port_name=arg;
   printf("d found (%s)\n",arg);break;
  case'o':arguments->log_name=arg;printf("o found (%s)\n",arg);break;
  case'p':arguments->port_name=arg;
   printf("p found (%s)\n",arg);break;
  case'q':arguments->verbosity--;printf("q found\n");break;
  case's':arguments->verbosity--;printf("s found\n");break;
  case'f':case'v':printf("%c found\n",key);
   if(arg)
   {int r,n=0;r=sscanf(arg,"%i%n",&(arguments->verbosity),&n);
    if(1!=r||arg[n])
    {fprintf(stderr,"%s:%i: \"%s\" is not a valid verbosity level"
     " (should be an integer)\n",__FILE__,__LINE__,arg);
     return ARGP_ERR_UNKNOWN;
    }printf("v arg '%s'\n",arg);
   }else
   {arguments->verbosity++;
    printf("no v argument\n");
   }break;
  case ARGP_KEY_ARG:
   printf("KEY_ARG found: arg_num=%i \"%s\"\n",state->arg_num,arg);
   /*if(state->arg_num>=0)argp_usage(state);*/break;
  case ARGP_KEY_END:
   printf("KEY_END found: arg_num=%i\n",state->arg_num);
   if(state->arg_num<0)argp_usage(state);break;
  default:
   printf("default %i",key);
   if(key<128)printf(" '%c'",key);
   printf("\n");
   return ARGP_ERR_UNKNOWN;
 }return 0;
}
static struct argp
argp0={options,parse_opt,args_doc,doc},
argp1={options,parse_opt,0,doc};
int 
main(int argc,char**argv)
{struct arguments arguments;
 arguments.port_name=0;arguments.log_name=0;arguments.verbosity=0;
 argp_parse(&argp0,argc,argv,0,0,&arguments);
 printf("\nsecond argp_parse invocation..\n");
 argp_parse(&argp1,argc,argv,0,0,&arguments);
 return 0;
}
