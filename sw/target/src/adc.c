/*ADC input
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
#include"adc.h"
#include"../include/lpc2138.h"
#define CHANNELS	(16)
static unsigned channels[CHANNELS],*ch0=channels,*ch1=channels+8;
const unsigned*get_adc(void){return channels;}
static void qu0(void)__attribute__((interrupt("IRQ")))
{unsigned c;while((c=AD0DR)&AD_DONE){ch0[(c>>24)&7]=(c>>6)&0x3FF;}
 VICVectAddr=0;
}
static void qu1(void)__attribute__((interrupt("IRQ")))
{unsigned c;while((c=AD1DR)&AD_DONE){ch1[(c>>24)&7]=(c>>6)&0x3FF;}
 VICVectAddr=0;
}
void init_adc(void)
{VICVectAddr6=(unsigned)qu0;VICVectCntl6=VIC_CntlEnable|VIC_AD0;
 VICVectAddr7=(unsigned)qu1;VICVectCntl7=VIC_CntlEnable|VIC_AD1;
 PINSEL1&=PINSEL1_AD00MASK&PINSEL1_AD01MASK&PINSEL1_AD02MASK&
  PINSEL1_AD03MASK&PINSEL1_AD04MASK&PINSEL1_AD05MASK&PINSEL1_AD7MASK;
 PINSEL1|=PINSEL1_AD00|PINSEL1_AD01|PINSEL1_AD02|
  PINSEL1_AD03|PINSEL1_AD04|PINSEL1_AD05|PINSEL1_AD7;
 PINSEL0&=PINSEL0_AD12MASK;PINSEL0|=PINSEL0_AD12;
 AD0CR=(0xBF)|(3<<8)|AD_BURST|AD_PDN;AD1CR=(0xC4)|(3<<8)|AD_BURST|AD_PDN;
}
