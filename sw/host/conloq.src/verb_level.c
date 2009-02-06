/*programme output control
Copyright (C) 2007, 2008\
 Ineiev <ineiev@users.sourceforge.net>, super V 93
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
#include"verb_level.h"
#include<stribog_error.h>
static enum verbosity_level verbosity;
enum verbosity_level
set_verbosity(enum verbosity_level v)
{enum verbosity_level r=verbosity;verbosity=v;return r;}
enum verbosity_level
get_verbosity(void){return verbosity;}
static int turned_on;
static int
turned(enum stribog_message_type t)
{if(any_message==t)return turned_on;return turned_on&(1<<t);}
int
stribog_message_turned_on(enum stribog_message_type t)
{switch(t)
 {case any_message:case pps_message:case temp_message:
  case gps_message:case stat_message:case adc_message:
  case odo_message:return turned(t);
 }return 0;
}void
turn_message(enum stribog_message_type type,int on)
{if(any_message==type)
 {if(on)turned_on=(1<<pps_message)|(1<<temp_message)|(1<<gps_message)|
   (1<<stat_message)|(1<<adc_message)|(1<<odo_message);else turned_on=0;
  return;
 }if(on)turned_on|=1<<type;else turned_on&=~(1<<type);
}void
init_turned_on(void){turn_message(any_message,1);}
static enum interaction_mode interaction_mode=deaf_mode;
void
set_interaction_mode(enum interaction_mode m){interaction_mode=m;}
enum interaction_mode
get_interaction_mode(void){return interaction_mode;}
