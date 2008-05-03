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
#include<stdarg.h>
#include"snprintf_checked.h"
#include<stdio.h>
int 
output_snprintf_error(const char*file,int line,
 char*s,unsigned size,const char*fmt,...)
{va_list ap;int result;
 va_start(ap,fmt);result=vsnprintf(s,size,fmt,ap);va_end(ap);
 if(result<0||result>=size)
 {fprintf(stderr,"%s:%i: snprintf() failed: ",file,line);
  if(result>=size)
   fprintf(stderr,"too short buffer (%i chars, %i needed)\n",size,result);
  if(result<0)fprintf(stderr,"conversion error %i\n",result);return!0;
 }return 0;
}
