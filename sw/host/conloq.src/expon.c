/*expon: decode stribog messages
Copyright (C) 2006, 2007, 2008\
 Ineiev <ineiev@users.sourceforge.net>, super V 93
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
#include"parse_tsip.h"
#include"exp.h"
#include<stribog_error.h>
#include"verb_level.h"
#include<stdio.h>
int main(int argc,char**argv)
{tsip_buf*tb;int size,period=1;const unsigned char*_;unsigned long long n=0;
 INIT_ERROR(*argv);
 if(argc>1)sscanf(argv[1],"%i",&period);
 init_turned_on();init_exp(period);
 if(argc>3)enable_escapes(!0);tb=new_tsip();
 while(!feof(stdin))
 {if((_=parse_tsip(tb,getchar(),&size)))if(expone(_,size))
   error("(error at position %llu)\n",n);n++;
 }close_exp();free_tsip(tb);return 0;
}
