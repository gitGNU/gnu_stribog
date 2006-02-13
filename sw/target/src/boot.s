/*LPC2138 boot program
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
.set	mode_usr, 0x10
.set	mode_fiq, 0x11
.set	mode_irq, 0x12
.set	mode_sv, 0x13
.set	mode_abt, 0x17
.set	mode_un, 0x1B
.set	mode_sys, 0x1F
.set	i_bit, 0x80
.set	f_bit, 0x40
.set	un_stack, 0
.set	ab_stack, 0
.set	fiq_stack, 0
.set	irq_stack, 0x400
.set	sv_stack, 0x40
.text
.code 32
.align 0
reset:/*initialize all stacks*/
	ldr	r0, stack_bot
	msr	CPSR_c, #i_bit|f_bit|mode_un
	mov	sp, r0
	sub	r0, r0, #un_stack
	msr	CPSR_c, #i_bit|f_bit|mode_abt
	mov	sp, r0
	sub	r0, r0, #ab_stack
	msr	CPSR_c, #i_bit|f_bit|mode_fiq
	mov	sp, r0
	sub	r0, r0, #fiq_stack
	msr	CPSR_c, #i_bit|f_bit|mode_irq
	mov	sp, r0
	sub	r0, r0, #irq_stack
	msr	CPSR_c, #i_bit|f_bit|mode_sv
	mov	sp, r0
	sub	r0, r0, #sv_stack
	msr	CPSR_c,	#i_bit|f_bit|mode_sys
	mov	sp, r0
/*load initialized variables from ROM: if the program is in RAM, 
  _rom_data_begin = _rom_data_end*/
	ldr	r1, rom_begin
	ldr	r0, rom_end
	ldr	r2, ram_begin
	b	cmp_r01
init_data:
	ldmia	r1!,{r3,r4,r5,r6}
	stmia	r2!,{r3,r4,r5,r6}
cmp_r01:
	cmp	r1,r0
	bmi	init_data
	/*clear uninitialized memory*/
clrbss:	ldr	r0, bss_begin
	ldr	r1, bss_end
	mov	r2, #0
	mov	r3,r2
	mov	r4,r2
	mov	r5,r2
clear_bss:
	cmp	r0, r1
	bpl	tst_pc
	stmia	r0!,{r2,r3,r4,r5}
	b	clear_bss
	mov	fp,r2
	mov	r7,r2
	mov	r0,#4
tst_pc:	tst	pc,r0, lsl #28
	beq	bmain
	/*remap the vectors if the program runs in RAM*/
	mov	r0,#2
	ldr	r1,memmap
	str	r0,[r1]
bmain:	msr	CPSR_c,	#f_bit|mode_sys /*ineiev couldn't make LPC2138 
                                          interrupt in user mode*/
	b	main
memmap:		.word	0xE01FC040
rom_begin:	.word	_rom_data_begin
rom_end:	.word	_rom_data_end
bss_begin:	.word	_bss_data_begin
bss_end:	.word	_bss_data_end
stack_bot:	.word	_arm_stack_bottom
ram_begin:	.word	_arm_ram_begin
.section .vectors
.code 32
.align 0
	ldr	pc,reset_addr
	ldr	pc,undef_addr
	ldr	pc,swi_addr
	ldr	pc,pabt_addr
	ldr	pc,dabt_addr
	nop
	ldr	pc,[pc,#-0xFF0]
	ldr	pc,fiq_addr
reset_addr:	.word reset
undef_addr:
swi_addr:
pabt_addr:
dabt_addr:
irq_addr:
fiq_addr:	.word loop	
loop:	b	./*this is an endless loop*/
.section .ramvectors /*these will be the RAM copy of vectors loaded from ROM*/
.code 32
.align 0
	ldr	pc,ram_reset_addr
	ldr	pc,ram_undef_addr
	ldr	pc,ram_swi_addr
	ldr	pc,ram_pabt_addr
	ldr	pc,ram_dabt_addr
	nop
	ldr	pc,[pc,#-0xFF0]
	ldr	pc,ram_fiq_addr
ram_reset_addr:	.word reset
ram_undef_addr:
ram_swi_addr:
ram_pabt_addr:
ram_dabt_addr:
ram_irq_addr:
ram_fiq_addr:	.word loop	
