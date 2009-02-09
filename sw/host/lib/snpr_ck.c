/*snprintf with errors output to stderr
Copyright (C) 2006, 2007, 2008, 2009\
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
#include"snpr_ck.h"
#include<sbg_error.h>
#include<stdio.h>
#if !HAVE_VSNPRINTF
/* this should serve rather ancient cases; on the other hand,
 * even some early snprintf() implementations
 * were not more secure than sprintf() */
# define vsnprintf(s,size,fmt,ap) vsprintf(s,fmt,ap)
#endif
int 
snprintf_checked(const char*file,int line,
 char*s,unsigned size,const char*fmt,...)
{va_list ap;int result;
 va_start(ap,fmt);result=vsnprintf(s,size,fmt,ap);va_end(ap);
 if(result<0)
 {stribog_error_at(file,line)
  ("snprintf() failed: conversion error %i\n",result);
  return!0;
 }
 if(result>=size)
 {stribog_error_at(file,line)
  ("snprintf() failed: too short buffer (%i chars, %i needed)\n",
   size,result);
  return!0;
 }return 0;
}
