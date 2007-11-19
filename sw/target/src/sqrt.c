/*integer sqrt for ARM with no hardware divider
This file is a part of the stribog project.

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.

Copyright (C) 2006 D.Ineiev <ineiev@yahoo.co.uk>*/
#include"sqrt.h"
unsigned sqrtu(unsigned u) 
{unsigned x,t,l=1<<30;do{t=l|x;x>>=1;if(t<=u){u-=t;x|=l;}}while(l>>=2);
 if(u>x)++x;return x;
}
