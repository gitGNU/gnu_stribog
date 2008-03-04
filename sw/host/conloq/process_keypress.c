/*conloq: parse user commands from keyboard
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
#include"process_keypress.h"
#include"verbosity_level.h"
#include"usage.h"
#include<stdio.h>
#include<stribog_error.h>
static int original_process(int);
static int(*
process)(int)=original_process;
int 
process_keypress(int c){if(EOF==c)return!0;return process(c);}
static enum verbosity_level stacked_verbosity;
static int
help_process(int c)
{process=original_process;set_verbosity(stacked_verbosity);return!0;}
static void
toggle_verbosity(void)
{if(normal_verbosity==get_verbosity())set_verbosity(relatively_mute);
 else set_verbosity(normal_verbosity);
}static void
toggle_message(enum stribog_message_type t)
{turn_message(t,!stribog_message_turned_on(t));}
static void
show_turned_on(void)
{putchar('\n');
 switch(get_verbosity())
 {case absolutely_mute:printf("absolutely mute");break;
  case relatively_mute:printf("relatively mute");break;
  case normal_verbosity:printf("normal");break;
  default:error("unknown (%i)",get_verbosity());
 }printf(" verbosity level\n");
 if(stribog_message_turned_on(any_message))printf("turned on:");
 else printf("no message is turned on");
 if(stribog_message_turned_on(adc_message))printf(" adc;");
 if(stribog_message_turned_on(pps_message))printf(" pps;");
 if(stribog_message_turned_on(gps_message))printf(" gps;");
 if(stribog_message_turned_on(temp_message))printf(" temp;");
 if(stribog_message_turned_on(stat_message))printf(" stat;");
 if(stribog_message_turned_on(odo_message))printf(" odo;");putchar('\n');
}static int
original_process(int c)
{switch(c)
 {case 'h':process=help_process;help();
   printf(" press any key to continue\n");
   stacked_verbosity=set_verbosity(absolutely_mute);break;
  case 'v':toggle_verbosity();break;
  case 'a':toggle_message(adc_message);break;
  case 'g':toggle_message(gps_message);break;
  case 'o':toggle_message(odo_message);break;
  case 'm':turn_message(any_message,0);break;
  case 'n':turn_message(any_message,!0);break;
  case 'p':toggle_message(pps_message);break;
  case 's':toggle_message(stat_message);break;
  case 'S':show_turned_on();break;
  case 't':toggle_message(temp_message);break;
  case 'q':return 0;
 }return!0;
}
