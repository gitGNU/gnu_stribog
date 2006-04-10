/*expon: decode magex messages
This program is a part of the stribog host software section

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Copyright (C) 2006 D.Ineiev <ineiev@yahoo.co.uk>*/
#include"parse_tsip.h"
#include"exp.h"
#include<stdio.h>
int main(void)
{tsip_buf*tb=new_tsip();int size;const unsigned char*_;init_exp(!0);
 while(!feof(stdin)){if((_=parse_tsip(tb,getchar(),&size)))expone(_,size);}
 close_exp();free_tsip(tb);return 0;
}
