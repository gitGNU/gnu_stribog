/*save-reload current working directory
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
#if HAVE_CONFIG_H
 #include<config.h>
#endif
#include"save_wd.h"
#include<unistd.h>
#if HAVE_FCHDIR
/*open/fchdir: the preferable means*/
#include<fcntl.h>
enum fd_values{INVALID_FD=-1};
typedef int/*file descriptor*/ saved_wd_type;
enum{initial_value=INVALID_FD};
static int
valid_wd(saved_wd_type wd){return wd>=0;}
static int
close_wd_instance(saved_wd_type*wd){return close(*wd);}
static void
observe_wd(saved_wd_type*wd){*wd=open(".",O_RDONLY);}
static int
change_to_saved_wd(saved_wd_type*wd)
{return fchdir(*wd);}
#else/*no fchdir: we'll try get_current_dir_name*/
 #if HAVE_GET_CURRENT_DIR_NAME
#include<stdlib.h>
typedef const char*saved_wd_type;
enum{initial_value=0};
static int
valid_wd(saved_wd_type wd){return wd;}
static int
close_wd_instance(saved_wd_type*wd){free(*wd);return 0;}
static void
observe_wd(saved_wd_type*wd)
{*wd=get_currrent_dir_name();}
static int
change_to_saved_wd(saved_wd_type*wd)
{return chdir(*wd);}
 #else /*no get_current_dir_name: hope getcwd is available*/
#if !HAVE_GETCWD
 #error "no known functions to save current path in host system"
#endif
typedef char*saved_wd_type;
static char buffer[4913];
enum{initial_value=0};
static int
valid_wd(saved_wd_type wd){return wd;}
static int
close_wd_instance(saved_wd_type*wd){return 0;}
static void
observe_wd(saved_wd_type*wd)
{*wd=getcwd(buffer,sizeof buffer);}
static int
change_to_saved_wd(saved_wd_type*wd){return chdir(*wd);}
 #endif
#endif
static saved_wd_type wd=initial_value;
int
save_wd(void)
{if(valid_wd(wd))return 0;
 observe_wd(&wd);return!valid_wd(wd);
}
int
reload_wd(void)
{if(!valid_wd(wd))return!0;return change_to_saved_wd(&wd);}
int
close_wd(void)
{int r=0;
 if(valid_wd(wd))r=close_wd_instance(&wd);
 wd=initial_value;return r;
}
