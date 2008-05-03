/*elk the LPC21x programmer: snprintf with errors output to stderr
Copyright (C) 2006, 2007, 2008\
 Ineiev<ineiev@users.sourceforge.net>, super V 93
This program is a part of the stribog host software section

stribog is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.*/
#define snprintf_checked(s,size,fmt,...)\
 output_snprintf_error(\
 __FILE__,__LINE__,s,size,fmt,__VA_ARGS__)
#ifdef __GNUC__
int output_snprintf_error(const char*file,int line,
 char*s,unsigned size,const char*fmt,...)
__attribute__((format(printf,5,6)));
#endif
int 
output_snprintf_error(const char*file,int line,
 char*s,unsigned size,const char*fmt,...);
