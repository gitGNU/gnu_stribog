/*ADC input
This file is a part of stribog.

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
#include"dac.h"
#include"../include/lpc2138.h"
#include"mutex.h"
#define CHANNELS	(16)
static unsigned channels[CHANNELS],*ch0=channels,*ch1=channels+8;
static mutex data_read;
const unsigned*get_adc(void){if(lock(&data_read))return 0;return channels;}
static void qu0(void)__attribute__((interrupt("IRQ")));
static void qu0(void)
{unsigned c,cn;
 while((c=AD0DR)&AD_DONE)
 {ch0[cn=(c>>24)&7]=(c>>6)&0x3FF;if(cn==7)unlock(&data_read);}
 VICVectAddr=0;
}
static void qu1(void)__attribute__((interrupt("IRQ")));
static void qu1(void)
{unsigned c;while((c=AD1DR)&AD_DONE)ch1[(c>>24)&7]=(c>>6)&0x3FF;VICVectAddr=0;}
void init_adc(void)
{init_dac();
 VICVectAddr6=(unsigned)qu0;VICVectCntl6=VIC_CntlEnable|VIC_AD0;
 VICVectAddr7=(unsigned)qu1;VICVectCntl7=VIC_CntlEnable|VIC_AD1;
 VICIntEnable=(1<<VIC_AD0)|(1<<VIC_AD1);
 PINSEL0&=PINSEL0_AD12MASK&PINSEL0_AD07MASK;PINSEL0|=PINSEL0_AD07|PINSEL0_AD12;
 PINSEL1&=PINSEL1_AD00MASK&PINSEL1_AD01MASK&PINSEL1_AD02MASK&
  PINSEL1_AD03MASK&PINSEL1_AD04MASK&PINSEL1_AD05MASK&PINSEL1_AD17MASK;
 PINSEL1|=PINSEL1_AD00|PINSEL1_AD01|PINSEL1_AD02|
  PINSEL1_AD03|PINSEL1_AD04|PINSEL1_AD05|PINSEL1_AD16|PINSEL1_AD17;
 AD0CR=(0xBF)|(16<<8)|AD_PDN|AD_BURST;
 AD1CR=(0xC4)|(32<<8)|AD_PDN|AD_BURST;lock(&data_read);
}
