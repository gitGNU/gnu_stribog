/*fake mutex: THIS DOESN'T WORK, provided just to make
 dependency tracking work
Copyright (C) 2008\
 Ineiev <ineiev@users.sourceforge.net>, super V 93
This file has been written for <http://savannah.nongnu.org/projects/stribog>

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
#define UNLOCKED	(0)/*static mutices are born unlocked by default*/
#define LOCKED		(1)
typedef int mutex;
static inline int
lock(mutex*m){int r=LOCKED,r1;r1=*m;*m=r;return r1;}
static inline void
unlock(mutex*m){*m=(mutex)UNLOCKED;}