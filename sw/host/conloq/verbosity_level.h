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
enum verbosity_level
{absolutely_mute=-2,relatively_mute=-1,
 normal_verbosity=0,pretty_verbose=1
};
enum verbosity_level set_verbosity(enum verbosity_level verb);
enum verbosity_level get_verbosity(void);
enum stribog_message_type
{any_message=-1,pps_message=0,temp_message=1,gps_message=2,stat_message=3,
 adc_message=4,odo_message=5
};
void turn_message(enum stribog_message_type type,int on);
int stribog_message_turned_on(enum stribog_message_type t);
void init_turned_on(void);
enum interaction_mode{deaf_mode=1,interactive_mode=0};
void set_interaction_mode(enum interaction_mode);
enum interaction_mode get_interaction_mode(void);
