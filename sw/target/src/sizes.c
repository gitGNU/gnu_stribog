/*ARM: types sizes (make sizes.s to learn them)
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

int charsize(void){return sizeof(char);}
int ucharsize(void){return sizeof(unsigned char);}
int shortsize(void){return sizeof(short);}
int ushortsize(void){return sizeof(unsigned short);}
int intsize(void){return sizeof(int);}
int uintsize(void){return sizeof(unsigned);}
int longsize(void){return sizeof(long);}
int ulongsize(void){return sizeof(unsigned long);}
int llongsize(void){return sizeof(long long);}
int ullongsize(void){return sizeof(unsigned long long);}
