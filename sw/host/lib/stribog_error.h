/*gnu-like error messages
Copyright (C) 2005, 2008\
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
void error_(const char*fmt,...)
#ifdef __GNUC__
__attribute__((format(printf,1,2)))
#endif
;
void output_prefix_for_error(void);
void init_error(const char*program_name);
#define error output_prefix_for_error(),\
 error_("%s:%i:",__FILE__,__LINE__),error_