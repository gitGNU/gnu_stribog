/*emergency argp implementation
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
/*NB this library is NOT under the LGPL, it is under the GPL. 
there is absolutely no need to release it under the LGPL:
if you want an LGPLed implementation,
get GLibC, it is much better to begin with*/
#ifdef HAVE_CONFIG_H
 #include<config.h>
#endif
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<argp.h>
error_t argp_err_exit_status;
static int
printable_option_key(int key){return(key>' '&&key<0x7F);}
static int
new_line(void){printf("\n");return printf("            ");}
static int
valid_option(const struct argp_option*o)
{return o->long_option||o->key;}
void
argp_usage(struct argp_state*state)
{int chars_printed,line_length=51,aliased_key=0;
 struct argp_option*options=state->argp->options,*option;
 chars_printed=printf("Usage: %s [-?V",state->prog_name);
 if(options)
  for(option=options;valid_option(option);option++)
 {if(option->arg_name||aliased_key==option->key)continue;
  if(!(option->flags&OPTION_ALIAS))aliased_key=option->key;
  if(printable_option_key(option->key))
   chars_printed+=printf("%c",option->key);
  if(chars_printed>=line_length)
  {printf("]");chars_printed=new_line();
   chars_printed+=printf("[-");
  }
 }chars_printed+=printf("] ");
 if(chars_printed>=line_length)chars_printed=new_line();
 if(options)
  for(option=options;valid_option(option);option++)
 {int opt=option->flags&OPTION_ARG_OPTIONAL;
  if(aliased_key==option->key||!option->arg_name)continue;
  if(!(option->flags&OPTION_ALIAS))aliased_key=option->key;
  if(!printable_option_key(option->key))continue;
  chars_printed+=printf("[-%c",option->key);
  if(opt)chars_printed+=printf("[");
  else chars_printed+=printf(" ");
  chars_printed+=printf("%s",option->arg_name);
  if(opt)chars_printed+=printf("]");
  chars_printed+=printf("] ");
  if(chars_printed>=line_length)chars_printed=new_line();
 }
 if(options)
  for(option=options;valid_option(option);option++)
 {int opt=option->flags&OPTION_ARG_OPTIONAL;
  if(!option->long_option)continue;
  chars_printed+=printf("[--%s",option->long_option);
  if(!option->arg_name)
  {chars_printed+=printf("] ");
   if(chars_printed>=line_length)chars_printed=new_line();
   continue;
  }
  if(opt)chars_printed+=printf("[");
   chars_printed+=printf("=%s",option->arg_name);
  if(opt)chars_printed+=printf("]");
  chars_printed+=printf("] ");
  if(chars_printed>=line_length)chars_printed=new_line();
 }
 chars_printed+=printf("[--help] [--usage]");
 if(chars_printed>=line_length)chars_printed=new_line();
 if(state->argp->args_doc)printf(" %s",state->argp->args_doc);
 printf("\n");exit(argp_err_exit_status);
}
static void
print_help(struct argp_state*state)
{const char*help_string=state->argp->doc;
 struct argp_option*option=state->argp->options;
 const char null_delimiter[]="",next_delimiter[]=", ";
 printf("Usage: %s [OPTION...]",state->prog_name);
 if(state->argp->args_doc)printf(" %s",state->argp->args_doc);
 printf("\n");
 if(help_string)while(*help_string&&*help_string!='\v')
  printf("%c",*(help_string++));
 printf("\n\n");
 if(option)for(;valid_option(option);option++)
 {struct argp_option*next_option;
  int opt=option->flags&OPTION_ARG_OPTIONAL,n,aliased_key=0;
  const char*delimiter=null_delimiter;
  if(option->flags&OPTION_ALIAS)continue;
  n=printf("  ");next_option=option;
  do
  {if(aliased_key!=next_option->key&&printable_option_key(next_option->key))
   {n+=printf("%s-%c",delimiter,next_option->key);
    delimiter=next_delimiter;
   }aliased_key=option->key;next_option++;
  }while(valid_option(next_option)&&
    (next_option->flags&OPTION_ALIAS));
  next_option=option;
  if(null_delimiter==delimiter)n+=printf("    ");
  do
  {if(next_option->long_option)
    {n+=printf("%s--%s",delimiter,next_option->long_option);
     delimiter=next_delimiter;
    if(option->arg_name)
    {if(opt)n+=printf("[");
     n+=printf("=%s",next_option->arg_name);
     if(opt)n+=printf("]");
    }delimiter=next_delimiter;
   }next_option++;
  }while(valid_option(next_option)&&(next_option->flags&OPTION_ALIAS));
  if(n>29){printf("\n");n=0;}
  printf("%*c",29-n,' ');
  printf("%s\n",option->help);
 }
 printf(
  "  -?, --help                 Give this help list\n"
  "      --usage                Give a short usage message\n"
  "  -V, --version              Print program version\n\n"
  "Mandatory or optional arguments to long options "
  "are also mandatory or optional\n"
  "for corresponding short options.\n\n");
 if(help_string)printf("%s\n",help_string);
 if(argp_program_bug_address)
  printf("Report bugs to %s.\n",argp_program_bug_address);
 exit(0);
}
static void
print_version(struct argp_state*state)
{printf("%s\n",argp_program_version);exit(0);}
static int
options_match(char*option,const char*pattern,
 int arg_possible,char**arg)
{if(!pattern)return 0;
 while(*pattern&&*pattern==*option){pattern++;option++;}
 if(*option=='=')*arg=option+1;else*arg=0;
 return*pattern==*option||(arg_possible&&*option=='='&&!*pattern);
}
static void/*parse the next option possibly with it's argument*/
parse_arg(struct argp*argp,int*argc,char**argv,
 struct argp_state*state,struct arguments*arguments)
{char*current,*arg;struct argp_option*option=state->argp->options;
 int arg_possible=0,arg_optional=0;
 state->arg_num=*argc-1;current=argv[(*argc)++];
 if(*current!='-')/*not an option*/
 {argp->parse_option(ARGP_KEY_ARG,current,state);return;}
 if(current[1]=='-')/*long option*/
 {/*predefined options; any of them terminates the program with exit();*/
  if(!strcmp("help",current+2))print_help(state);
  if(!strcmp("usage",current+2))
  {argp_err_exit_status=0;
   argp_usage(state);
  }
  if(!strcmp("version",current+2))print_version(state);
  /*application-defined options*/
  if(state->argp->options)for(;valid_option(option);option++)
  {if(!(option->flags&OPTION_ALIAS))
   {arg_possible=option->arg_name!=0;
    arg_optional=option->flags&OPTION_ARG_OPTIONAL;
   }
   if(options_match(current+2,option->long_option,arg_possible,&arg))
   {if(arg&&!arg_possible)/*FIXME error output*/return;
    if(arg_possible&&!arg&&!arg_optional)arg=argv[(*argc)++];
    argp->parse_option(option->key,arg,state);return;
   }
  }
  fprintf(stderr,"%s: undefined long option %s (argument no %i)\n",
    *argv,current,*argc-1);
  return;
 }/*long option*/
 while(*++current)/*short options*/
 {if('?'==*current)print_help(state);if('V'==*current)print_version(state);
  if(state->argp->options)
   for(option=state->argp->options;valid_option(option);option++)
  {if(!(option->flags&OPTION_ALIAS))
   {arg_possible=option->arg_name!=0;
    arg_optional=option->flags&OPTION_ARG_OPTIONAL;
   }if(*current==option->key)break;
  }
  if(*current!=option->key)
  {fprintf(stderr,"%s: undefined short option %c (argument no %i)\n",
    *argv,*current,*argc-1);
   argp_usage(state);
  }
  if(!arg_possible){argp->parse_option(option->key,0,state);continue;}
  if(arg_optional)
  {if(current[1]){current++;argp->parse_option(option->key,current,state);}
   else argp->parse_option(option->key,0,state);
   continue;
  }
  if(current[1]){argp->parse_option(option->key,current+1,state);break;}
  if(argv[*argc])
  {argp->parse_option(option->key,argv[(*argc)++],state);continue;}
  fprintf(stderr,"%s: short option %c requires an argument\n",*argv,*current);
  argp_usage(state);
 }/*short options*/
}
void
argp_parse(struct argp*argp,int argc,
 char**argv,int a,int b,struct arguments*arguments)
{struct argp_state state;int i=1;
 state.input=arguments;state.argp=argp;
 state.arg_num=0;argp_err_exit_status=EX_USAGE;state.prog_name=*argv;
 while(argv[i])parse_arg(argp,&i,argv,&state,arguments);
 argp->parse_option(ARGP_KEY_END,0,&state);
}
