/* wrap-around standard signal handling routines
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
#include<signal.h>
int init_signals(void);/*hangs handler on signals to be caught*/
enum check_signals_return_values
{indefinite_signal=-1,no_signal=0};
/*if any signal has been caught, outputs the signal name
 to stderr and terminates the program with exit_code*/
void check_signals(int exit_code);
