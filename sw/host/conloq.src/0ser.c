/* dummy serial port module
Copyright (C) 2006, 2007, 2008, 2009\
 Ineiev<ineiev@users.berlios.de>, super V 93
This file is a part of the stribog host software section

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
#if HAVE_CONFIG_H
# include<config.h>
#endif
#include"serialia.h"
#include"verb_level.h"
#include<stdio.h>
#include<string.h>
int
initserialia(const char*tty)
{if(get_verbosity()>=pretty_verbose)
  printf("(dummy code) set up port\n");
 return 0;
}void
closeserialia(void){}
int
lege(void*p,int n){return 0;}
int
scribe(const void*p,int n){return n;}
