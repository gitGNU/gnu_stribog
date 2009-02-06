/*signal library test and usage example
Copyright (C) 2008, 2009\
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
#if HAVE_CONFIG_H
# include<config.h>
#endif
#include"sbg_signal.h"
#include<stdio.h>
#include<stdlib.h>
static void
close_all(void){printf("terminating the program\n");}
int
main(void)
{atexit(close_all);init_signals();printf("kill me!\n");
 while(1)check_signals(1);return 0;
}
