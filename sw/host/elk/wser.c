/*stribog host part: Windows serial module

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

Copyright (C) 2006, 2007 Ineiev<ineiev@users.sourceforge.net>, super V 93*/
#include"serialia.h"
#include<windows.h>
static HANDLE port;
void
close_serialia(void){CloseHandle(port);port=0;}
int
init_serialia(const char*port_name,int freq)
{DCB dcb;COMMTIMEOUTS to;if(!port_name)port_name="COM1";
 port=CreateFile(port_name,GENERIC_READ|GENERIC_WRITE,0,0,OPEN_EXISTING,
  FILE_ATTRIBUTE_NORMAL,0);
 if(INVALID_HANDLE_VALUE==port)return-1;
 if(!GetCommState(port,&dcb)){close_serialia();return-2;}
 dcb.BaudRate=CBR_115200;dcb.fBinary=1;dcb.fParity=0;
 dcb.fOutxCtsFlow=0;dcb.fOutxDsrFlow=0;dcb.fDtrControl=DTR_CONTROL_DISABLE;
 dcb.fDsrSensitivity=0;dcb.fTXContinueOnXoff=0;
 dcb.fOutX=0;dcb.fInX=0;dcb.fErrorChar=0;dcb.fNull=0;
 dcb.fRtsControl=RTS_CONTROL_DISABLE;dcb.fAbortOnError=0;
 dcb.wReserved=0;dcb.XonLim=1024;dcb.XoffLim=128;
 dcb.ByteSize=8;dcb.Parity=NOPARITY;dcb.StopBits=TWOSTOPBITS;
 if(!SetCommState(port,&dcb)){close_serialia();return-3;}
 GetCommTimeouts(port,&to);to.ReadIntervalTimeout=MAXDWORD;
 to.ReadTotalTimeoutConstant=0x33;to.ReadTotalTimeoutMultiplier=0;
 to.WriteTotalTimeoutConstant=to.WriteTotalTimeoutMultiplier=0;
 SetCommTimeouts(port,&to);return 0;
}int
lege(void*s,int n)
{DWORD N=0;if(NULL==port)return-1;ReadFile(port,s,n,&N,0);return N;}
int
scribe(const void*s,int n)
{DWORD N=0;if(NULL==port)return-1;WriteFile(port,s,n,&N,0);return N;}
