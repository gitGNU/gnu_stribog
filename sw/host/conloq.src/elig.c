/*elig: output every k-th stribog "adc" message; other messages unchanged
Copyright (C) 2006, 2008\
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
#include"parse_tsip.h"
#include<stribog_error.h>
#include<stribog_strings.h>
#include<stdio.h>
#include<argp.h>
const char*argp_program_version="elig"PACKAGE_VERSION_COMMENTED;
const char*argp_program_bug_address ="<"PACKAGE_BUGREPORT">";
static char doc[]="decimate ADC messages from a stribog file\v"
"elig puts every n-th ADC message from stdin to stdout\n"
"while copying the rest messages as they are.\n"
"the default decimation count is 200.\n"
"this utility was to reduce volumes of certain stribog data files.\n\n",
 arg_doc[]="[decimation_count]";
static struct argp_option options[]=
{
 {"escapes",'e',0,0,
  "enable packet-layer escapes (you don't want to use "
   "this unless you really know what you are doing)"
 },
 {0}
};
static int k=200;
struct arguments{int escapes;};
static error_t
parse_opt(int key, char*arg, struct argp_state*state)
{struct arguments*arguments=state->input;int n=0,r;
 switch(key)
 {case 'e':arguments->escapes=!0;break;
  case ARGP_KEY_ARG:
   r=sscanf(arg,"%i%n",&k,&n);
   if(1!=r||arg[n]||k<=0)
   {error("'%s' is not a valid decimation count "
     "(should be a positive integer)\n",arg);
    argp_usage(state);
   }break;
  case ARGP_KEY_END:break;
  default:return ARGP_ERR_UNKNOWN;
 }return 0;
}
static struct argp argp={options,parse_opt,arg_doc,doc};
static const unsigned char dle=0x10,etx=0x03;
static void put_message(const unsigned char*c,int size)
{int i;putchar(dle);for(i=0;i<size;putchar(c[i++]))if(c[i]==dle)putchar(dle);
 putchar(dle);putchar(etx);
}
static void expone(const unsigned char*c,int size)
{static int i;if(size==24){if(++i==k)i=0;else return;}put_message(c,size);}
int main(int argc,char**argv)
{tsip_buf*tb;int size;const unsigned char*_;
 struct arguments arguments;arguments.escapes=0;
 init_error(*argv);
 argp_parse(&argp,argc,argv,0,0,&arguments);
 if(arguments.escapes)enable_escapes(!0);
 tb=new_tsip();
 while(!feof(stdin)){if((_=parse_tsip(tb,getchar(),&size)))expone(_,size);}
 free_tsip(tb);return 0;
}
