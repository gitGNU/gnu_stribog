/*ARM: mutices (compiler test: real code is in mutex.h)
This file has been written for the stribog project.

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
#include"mutex.h"
int lock(mutex*m)
{int r=LOCKED,r1;asm("swp %0, %1, [%2]":"=r"(r1):"r"(r),"r"(m));return r1;}
void unlock(mutex*m){*m=(mutex)UNLOCKED;}
