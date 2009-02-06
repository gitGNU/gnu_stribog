/*elk the LPC21x programmer: LPC21xx bootloader communications
Copyright (C) 2006, 2007, 2008, 2009\
 Ineiev<ineiev@users.sourceforge.net>, super V 93
This program is a part of the stribog host software section

stribog is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.*/
extern int mute;/*if 0, some commands will be more verbous*/
enum mcu_type{LPC2131_ID,LPC2132_ID,LPC2134_ID,
 LPC2136_ID,LPC2138_ID,UNDEFINED_MCU_TYPE};
int echo_off(int primary_call);int unlock(void);
enum mcu_type get_partid(void);
enum mcu_type read_partid(void);
int synchronize(unsigned long mcu_freq);
void read_version(void);
int prepare_sectors(unsigned start,unsigned end);
int erase_sectors(unsigned start,unsigned end);
void erase(void),prepare(void);
int read_memory(unsigned long addr,unsigned l,FILE*f);
int read_mem(void);
int write_string(const char*s,unsigned long addr,int n);
int copy_memory(unsigned long addr);
int write_file(const char*target_name);
int run(unsigned long addr);int load_ram_loader(void);

