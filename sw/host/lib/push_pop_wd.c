/*push-pop current working directory
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
#include"push_pop_wd.h"
#include<unistd.h>
/*open/fchdir: the preferable mean*/
#if HAVE_FCHDIR
#include<fcntl.h>
enum fd_values{INVALID_FD=-1};
static int fd=INVALID_FD;
static int
valid_fd(int fd){return fd>=0;}
int
push_wd(void)
{if(valid_fd(fd))return!0;
 fd=open(".",O_RDONLY);return!valid_fd(fd);
}
int
pop_wd(void)
{int ret;if(!valid_fd(fd))return!0;
 ret=fchdir(fd);fd=INVALID_FD;return ret;
}
#else/*no fchdir: we'll try get_current_dir_name*/
 #ifdef HAVE_GET_CURRENT_DIR_NAME
#include<stdlib.h>
static char*pushed_wd;
int
push_wd(void)
{if(pushed_wd)return!0;
 pushed_wd=get_current_dir_name();
 return!pushed_wd;
}
int
pop_wd(void)
{int ret;if(!pushed_wd)return!0;
 ret=chdir(pushed_wd);free(pushed_wd);
 pushed_wd=0;return ret; 
}
 #else /*no get_current_dir_name: hope getcwd is available*/
static char buffer[4913],*pushed_wd;
int
push_wd(void)
{if(pushed_wd)return!0;
 pushed_wd=getcwd(buffer,sizeof buffer);
 return!pushed_wd;
}
int
pop_wd(void)
{int ret;if(!pushed_wd)return!0;
 ret=chdir(pushed_wd);
 pushed_wd=0;return ret; 
}
 #endif
#endif
