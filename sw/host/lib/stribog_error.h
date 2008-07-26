/*gnu-like error messages
Copyright (C) 2008 Ineiev<ineiev@users.sourceforge.net>, super V 93
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
void error_location(const char*file,int line);
void init_error_dir(const char*prog_name,const char*srcdir);
#define INIT_ERROR(prog_name) init_error_dir(prog_name,SOURCE_DIR)
#define stribog_error_at(file,line) output_prefix_for_error(),\
 error_location(file,line),error_
#define error stribog_error_at(__FILE__,__LINE__)
